#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* getopt */
#include <sys/msg.h>	/* ftok, msgget, msgsnd, msgrcv */
#include <string.h>		/* strcpy, memset */


#define	MSG_LENGTH(B)				(sizeof(B) - sizeof(long))
#define DATA_SIZE					32

#define DEFAULT_CREATE_MQ			1
#define DEFAULT_DELETE_MQ			1
#define DEFAULT_N_MSGS				4
#define DEFAULT_VERBOSITY			1
#define DEFAULT_SPEED				200000
#define DEFAULT_FTOK_PATH_NAME		"/home/arieldavidov/Desktop/work/66.MultipuleWritersMessageQueue/FileForFtok"
#define DEFAULT_PARAMS				{DEFAULT_CREATE_MQ, DEFAULT_DELETE_MQ, DEFAULT_N_MSGS,	\
										DEFAULT_VERBOSITY, DEFAULT_SPEED, DEFAULT_FTOK_PATH_NAME}



int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	MsgBuf myMsgBuf;
	int qid;
	
	if (ArgsParser(argc, argv, &params))
	{
		exit(EXIT_FAILURE);
	}
	
	qid = OpenMessageQ(params.m_ftokPathName, 0);

	/* first recive is in block */
	MessageQRecive(qid, 1, &myMsgBuf);
	
	strcpy(myMsgBuf.m_text, "Pong");
	MessageQSend(qid, 2, &myMsgBuf);
	
	for(;;)
	{
        MsgQReciveNoWait(qid, &myMsgBuf, 1);
        usleep(params.m_speed);
        
        strcpy(myMsgBuf.m_text, "Pong");
		MessageQSend(qid, 2, &myMsgBuf);
		
    }

	printf("PONG exiting\n");
	
	return 0;
}




