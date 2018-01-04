#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* getopt */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>	/* ftok, msgget, msgsnd, msgrcv */
#include <string.h>		/* strcpy, memset */
#include <errno.h>


#define	MSG_LENGTH(B)				(sizeof(B) - sizeof(long))
#define MAX_TEXT_LENGTH				256

#define DEFAULT_CREATE_MQ			1
#define DEFAULT_DELETE_MQ			1
#define DEFAULT_N_MSGS				4
#define DEFAULT_VERBOSITY			1
#define DEFAULT_SPEED				200000
#define DEFAULT_FTOK_PATH_NAME		"/tmp"
#define DEFAULT_PARAMS				{DEFAULT_CREATE_MQ, DEFAULT_DELETE_MQ, DEFAULT_N_MSGS,	\
										DEFAULT_VERBOSITY, DEFAULT_SPEED, DEFAULT_FTOK_PATH_NAME}


int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	MsgBuf myMsgBuf;
	int qid;
	
	ArgsParser(argc, argv, &params);
	
	qid = MsgQCreate(params.m_ftokPathName, params.m_createMQ, params.m_verbosity);

	/* first recive is in block */
	MsgQRecive(qid, 1, &myMsgBuf, params.m_verbosity);
	
	strncpy(myMsgBuf.m_text, "Pong", MAX_TEXT_LENGTH);
	MsgQSend(qid, 2, &myMsgBuf, params.m_verbosity);
	/*usleep(1000000);*/

	for(;;)
	{
        if (-1 == MsgQReciveNoWait(qid, 1, &myMsgBuf, params.m_verbosity))
        {
			usleep(500);
        	continue;
        }

		strcpy(myMsgBuf.m_text, "Pong");
		MsgQSend(qid, 2, &myMsgBuf, params.m_verbosity);
    }
	
	if (params.m_deleteMQ)
	{
		MsgQDestroy(qid, params.m_verbosity);
	}

	printf("PONG exiting\n");
	
	return 0;
}




