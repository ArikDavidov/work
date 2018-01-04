#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* getopt */
#include <sys/msg.h>	/* ftok, msgget, msgsnd, msgrcv */
#include <string.h>		/* strcpy, memset */

#define MSG_FLAGS(C)				(0666 /*| IPC_EXCL*/ | ((C) ? IPC_CREAT : 0))
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
	int i, qid, nByte;
	
	if(ArgsParser(argc, argv, &params))
	{
		exit(EXIT_FAILURE);
	}
	
	qid = OpenMessageQ(params.m_ftokPathName, params.m_createMQ);
		
	myMsgBuf.m_pid = getpid();
	
	MessageQSend(qid, 2, &myMsgBuf);
	printf("PING (PID %d): Registration on type = 2 \n", myMsgBuf.m_pid);
	usleep(params.m_speed);
	
	for (i = 0; i < params.m_nMsgs; ++i)
	{
		InitBuf(&myMsgBuf.m_text, DATA_SIZE);
		nByte = MessageQSend(qid, 0, &myMsgBuf);
		printf("PING (PID %d): Sending MessageQ Bytes sent: %d \n", myMsgBuf.m_pid, nByte);
		usleep(params.m_speed);
	}
	
	if (params.m_deleteMQ)
	{
		printf("Deleting MessageQ\n");
		MessageQDestroy(qid);
	}
	
	printf("PING exiting\n");
	
	return 0;
}





