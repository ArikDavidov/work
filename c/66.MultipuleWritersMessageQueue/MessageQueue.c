#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>			/* atoi, exit */
#include <unistd.h>			/* getopt */
#include <string.h>			/* strcpy, memset */
#include <sys/msg.h>		/* ftok, msgget, msgsnd, msgrcv */

#define MSG_FLAGS(C)				(0666 /*| IPC_EXCL*/ | ((C) ? IPC_CREAT : 0))
#define	MSG_LENGTH(B)				(sizeof(B) - sizeof(long))


int ArgsParser(int argc, char *argv[], InParams* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "c:d:n:v:s:f:")))
    {
        switch (opt) 
        {
			case 'c':
				_params->m_createMQ = atoi(optarg);				break;
		    case 'd':
				_params->m_deleteMQ = atoi(optarg);				break;
			case 'n':
				_params->m_nMsgs = atoi(optarg);				break;
			case 'v':
				_params->m_verbosity = atoi(optarg);			break;
		    case 's':
				_params->m_speed = (useconds_t)atoi(optarg);	break;
			case 'f':
				strcpy(_params->m_ftokPathName, optarg);		break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-c #] [-d #] [-n #] \
						[-v #] [-s #] [-f #]\n", argv[0]);
				return 1;
		}
	}

	return 0;
}

void InitBuf(void* _buf, size_t _dataSize)
{
	static char c = 'A';
	
	memset(_buf, c, _dataSize);
	++c;

	((char*)_buf)[_dataSize] = '\0';
}

int OpenMessageQ(char* _pathName, int _createMQ)
{
	int qid;
	
	key_t key = ftok(_pathName, 'm');

	if (-1 == (qid = msgget(key, MSG_FLAGS(_createMQ))))
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	
	return qid;
}

int MessageQSend(int _qid, long _type, MsgBuf* _myMsgBuf)
{
	int size;

	if(-1 == (size = msgsnd(_qid, _myMsgBuf, MSG_LENGTH(MsgBuf), 0)))
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	
	printf("SENT Size: %d, PID: %d | %s\n", 
			size, _myMsgBuf->m_pid, _myMsgBuf->m_text);  
	
	return size;
}

int MsgQReciveNoWait(int _qid, MsgBuf* _myMsgBuf, long _type)
{
	int size;
	
	if(-1 == (size = msgrcv(_qid, _myMsgBuf, MSG_LENGTH(MsgBuf), _type, IPC_NOWAIT)))
	{
		perror("msgrcv");
		return -1;
	}
	
	printf("RCVD Size: %d, PID: %d | %s\n", 
			size, _myMsgBuf->m_pid, _myMsgBuf->m_text);
	
	return size;
}

int MessageQRecive(int _qid, long _type, MsgBuf* _myMsgBuf)
{
	int size;


	if(-1 == (size = msgrcv(_qid, _myMsgBuf, MSG_LENGTH(MsgBuf), _type,  0)))
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	
	printf("RCVD Size: %d, PID: %d | %s\n", 
			size, _myMsgBuf->m_pid, _myMsgBuf->m_text);
	
	return size;
}

void MessageQDestroy(int _qid)
{
    printf("Deleting MessageQ\n");
    
    if (-1 == msgctl(_qid, IPC_RMID, NULL))
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
}








