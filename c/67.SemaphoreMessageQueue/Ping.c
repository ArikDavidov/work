#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* getopt */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>	/* ftok, msgget, msgsnd, msgrcv */
#include <string.h>		/* strcpy, memset */
#include <errno.h>

#define MSG_FLAGS(C)				(0666 /*| IPC_EXCL*/ | ((C) ? IPC_CREAT : 0))
#define	MSG_LENGTH(B)				(sizeof(B) - sizeof(long))
#define DATA_SIZE					32

#define DEFAULT_CREATE_MQ			1
#define DEFAULT_DELETE_MQ			1
#define DEFAULT_N_MSGS				4
#define DEFAULT_VERBOSITY			1
#define DEFAULT_SPEED				200000
#define DEFAULT_FTOK_PATH_NAME		"/tmp"
#define DEFAULT_PARAMS				{DEFAULT_CREATE_MQ, DEFAULT_DELETE_MQ, DEFAULT_N_MSGS,	\
										DEFAULT_VERBOSITY, DEFAULT_SPEED, DEFAULT_FTOK_PATH_NAME}

/*
static void InitBuf(void* _buf, size_t _dataSize)
{
	static char c = 'A';
	
	memset(_buf, 0, _dataSize);
	++c;

	((char*)_buf)[_dataSize] = '\0';
}
typedef struct InParams InParams;
*/



int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	MsgBuf myMsgBuf;
	int i, j, qid, nBytes;
	size_t len;
	
	ArgsParser(argc, argv, &params);
	
	qid = MsgQOpen(params.m_ftokPathName, params.m_verbosity);
	
	/*myMsgBuf.m_data.m_pid = getpid();*/
	
	/*
	MsgQSend(qid, 3, &myMsgBuf, params.m_verbosity);
	printf("PING (PID %d): Registration on type = 3 \n", myMsgBuf.m_pid);
	usleep(params.m_speed);
	*/
	
	for (i = 0; i < params.m_nMsgs; ++i)
	{
		
		usleep(params.m_speed);

		strcpy(myMsgBuf.m_text, "Zero bug approach");
		len = strlen("Zero bug approach");
		myMsgBuf.m_text[len] = '\0';

		MsgQSend(qid, 1, &myMsgBuf, params.m_verbosity);
		
		for (j = 0; j < 10 && nBytes < 1; ++j)
		{
			nBytes = MsgQReciveNoWait(qid, 2, &myMsgBuf, params.m_verbosity);
			usleep(500);
		}

		break;
		printf("%d\n", j);
	}

	/*sem_wait*/
	printf("PING exiting\n");
	
	return 0;
}





