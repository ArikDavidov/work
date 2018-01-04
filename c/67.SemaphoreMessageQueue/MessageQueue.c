#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>			/* atoi, exit */
#include <unistd.h>			/* getopt */
#include <string.h>			/* strcpy, memset */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>		/* ftok, msgget, msgsnd, msgrcv */
#include <semaphore.h>		/* Link with -pthread */

#define PROJ_ID								'A'
#define DEFAULT_FTOK_PATH_NAME				"/tmp"
#define SEMAPHORE_NAME						"mysemaphore"

#define MSG_FLAGS(C)						(0666 | IPC_EXCL | ((C) ? IPC_CREAT : 0))
#define	MSG_LENGTH(B)						(sizeof(B) - sizeof(long))
#define	VERBOSITY_MESSAGE_PRINT(V, D, M)	do{if(V){MsgQPrint(D, M);}}	\
												while(0)
#define	VERBOSITY_PRINT(V, T)				do{if(V){printf(T);printf("\n");}}	\
												while(0)
#define HANDLE_ERROR(M)						do{perror(M);exit(EXIT_FAILURE);}	\
												while(0)
/*
	VERBOSITY("Deleting MessageQ");

struct InParams
{
	int			m_createMQ;
	int			m_deleteMQ;
	int			m_nMsgs;
	int			m_verbosity;
	useconds_t	m_speed;
	char		m_ftokPathName[PATH_MAX];
};
*/


void ArgsParser(int argc, char *argv[], InParams* _params)
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
				exit(EXIT_FAILURE);
		}
	}
}

int MsgQCreate(char* _pathName, int _createMQ, int _verbocity)
{
	key_t key;
	int qid;

	atexit(MsgQDestroyAtExit);

	/* TODO sem_open
	sem_t sem;
	if (SEM_FAILED == (sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 0)))
	{
		HANDLE_ERROR("semaphore initilization");
	}
	*/

	if (-1 == (key = ftok(DEFAULT_FTOK_PATH_NAME, PROJ_ID)))
	{
		HANDLE_ERROR("ftok");
	}
	
	if (-1 == (qid = msgget(key, 0644 | IPC_CREAT)))
	{
		HANDLE_ERROR("msgget");
	}
	
	printf("Message Queue was created. key: %d, qid:%d\n", key, qid);

	return qid;
}

int MsgQOpen(char* _pathName, int _verbocity)
{
	key_t key;
	int qid;

	/* TODO sem_post(&sem);
	if (SEM_FAILED == (sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 0)))
	{
		HANDLE_ERROR("semaphore initilization");
	}
	sem_t sem;
	*/
	
	if (-1 == (key = ftok(DEFAULT_FTOK_PATH_NAME, PROJ_ID)))
	{
		HANDLE_ERROR("ftok");
	}

	if (-1 == (qid = msgget(key, 0644)))
	{
		HANDLE_ERROR("msgget");
	}

	printf("Message Queue was opend. key: %d, qid:%d\n", key, qid);

	return qid;
}

int MsgQSend(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity)
{
	int size;
	/*size_t len;
	len = strlen(_myMsgBuf->m_text);
	*/

	_myMsgBuf->m_type = _type;

	if(-1 == (size = msgsnd(_qid, _myMsgBuf, sizeof(_myMsgBuf->m_text), 0)))
	{
		HANDLE_ERROR("msgsnd");
	}
	
	VERBOSITY_MESSAGE_PRINT(_verbocity, "SENT", _myMsgBuf);

	return size;
}

int MsgQReciveNoWait(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity)
{
	int size;

	memset(_myMsgBuf->m_text, 0, sizeof(_myMsgBuf->m_text));

	if(-1 == (size = msgrcv(_qid, _myMsgBuf, sizeof(_myMsgBuf->m_text), _type, IPC_NOWAIT)))
	{
		return -1;
	}
	
	VERBOSITY_MESSAGE_PRINT(_verbocity, "RCVD", _myMsgBuf);
	
	return size;
}

int MsgQRecive(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity)
{
	int size;

	memset(_myMsgBuf->m_text, 0, sizeof(_myMsgBuf->m_text));

	if(-1 == (size = msgrcv(_qid, _myMsgBuf, sizeof(_myMsgBuf->m_text), _type, 0)))
	{
		HANDLE_ERROR("msgrcv");
	}
	
	VERBOSITY_MESSAGE_PRINT(_verbocity, "RCVD", _myMsgBuf);
			
	return size;
}

void MsgQDestroy(int _qid, int _verbocity)
{
    /* TODO sem_unlink*/

    if (-1 == msgctl(_qid, IPC_RMID, NULL))
    {
		HANDLE_ERROR("msgctl");
    }

	VERBOSITY_PRINT(_verbocity, "Deleting MessageQ");
}

void MsgQPrint(char* _direction, MsgBuf* _myMsgBuf)
{
	/*, Msg#: %d, PID: %d*/
	printf("%s Type: %ld | %s\n", 
			_direction, _myMsgBuf->m_type,/* _myMsgBuf->m_data.m_MsgNum,
			_myMsgBuf->m_data.m_pid,*/ _myMsgBuf->m_text);
}

void MsgQDestroyAtExit()
{
	key_t key;
	int qid;

	if (-1 == (key = ftok(DEFAULT_FTOK_PATH_NAME, PROJ_ID)))
	{
		printf("ftok failure during exit");
	}

	if (-1 == (qid = msgget(key, 0666)))
	{
		return;
	}
	
	printf("Deleting qid: %d\n", qid);

	if (-1 == msgctl(qid, IPC_RMID, NULL))
	{
		printf("msgctl error");
	}
}




