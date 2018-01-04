#include "MessageQueue.h"

#include <stdio.h>
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* getopt, pause, write */
#include <sys/msg.h>
#include <assert.h>

#define RW_ONLY_PERMS		0666
#define MSG_FLAGS(C)		(RW_ONLY_PERMS | IPC_EXCL | ((C) ? IPC_CREAT : 0))

#define FTOK_PATH_NAME		"/home/arieldavidov/Desktop/work/	\
								65.MessageQueue/FileForFtok2"

#define DEFAULT_PARAMS		{DEFAULT_CREATE_MQ, DEFAULT_DELETE_MQ,	\
								DEFAULT_N_MSGS, DEFAULT_EOF}
#define DEFAULT_CREATE_MQ	1
#define DEFAULT_DELETE_MQ	1
#define DEFAULT_N_MSGS		4
#define DEFAULT_EOF			0





static int ArgsParser(int argc, char *argv[], InParams* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "c:d:n:e:")))
    {
        switch (opt) 
        {
			case 'c':
				_params->m_createMQ = atoi(optarg);			break;
		    case 'd':
				_params->m_deleteMQ = atoi(optarg);			break;
			case 'n':
				_params->m_nMsgs = atoi(optarg);			break;
			case 'e':
				_params->m_eof = atoi(optarg);				break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-c #] [-d #] [-n #] \
						[-e #]\n", argv[0]);
		    	return 1;
        }
    }

	printf("m_createMQ=%d; m_deleteMQ=%d; m_nMsgs=%d; m_eof=%d\n",
			_params->m_createMQ, _params->m_deleteMQ, _params->m_nMsgs, 
			_params->m_eof);

	return 0;
}

int OpenMessageQ()
{
	int qid;
	key_t key = ftok(FTOK_PATH_NAME, 'm');

	if (-1 == (qid = msgget(key, MSG_FLAGS(params.m_createMQ))))
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	
	return qid;
}

int MessageQSend(int _qid, Msgbuf* _qBuf)
{
	int result, length;

	length = sizeof(_qBuf) - sizeof(long);

	if(-1 == (result = msgsnd(_qid, _qBuf, length, 0)))
	{
		return(-1);
	}
        
	return(result);
}

int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	MsgBuf* msgbuf;
	int i, qid;
	
	if(ArgsParser(argc, argv, &params))
	{
		exit(EXIT_FAILURE);
	}
	
	qid = OpenMessageQ();
	
	
	for (i = 0; i < _params.m_nMsgs; ++i)
	{
	
        if((MessageQSend(qid, &msg)) == -1)
        {
			msgbuf = malloc(sizeof(MsgBuf));
		    perror("send_message");
		    exit(1);
        }
	}
	
	return 0;
}







