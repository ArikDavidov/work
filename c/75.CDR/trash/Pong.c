#include "MsgTransport.h"
#include "MessageQueue.h"
#include "CDR.h"

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


void CdrPrint(Cdr* _cdr)
{
	printf("\n***********************   CDR   ***********************\n");
	printf("IMSI: %s,\t", _cdr->m_imsi);
	printf("IMSI: %s,\t\n", _cdr->m_imsi);
	printf("MSISDN: %s,\t", _cdr->m_msisdn);
	printf("IMEI: %s,\t\n", _cdr->m_imei);
	printf("%s,\t", _cdr->m_operatorBrandName);
	printf("mccMnc: %s,\t\n", _cdr->m_mccMnc);
	printf("testCallType: %d,\n", _cdr->m_callType);
	printf("%s, ", _cdr->m_callDate);
	printf("%s,\t", _cdr->m_callTime);
	printf("duration: %d,\t\n", _cdr->m_duration);
	printf("download: %d,\t", _cdr->m_download);
	printf("upload: %d,\t\n", _cdr->m_upload);
	printf("partyMsisdn: %s,\t", _cdr->m_partyMsisdn);
	printf("partyOperator: %s\t", _cdr->m_partyOperator);
	printf("\n\n");
}



int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	MsgTransportBuf buf;
	int mtid;
	
	ArgsParser(argc, argv, &params);
	
	mtid = MsgQCreate(params.m_ftokPathName, params.m_createMQ, params.m_verbosity);

	/* first recive is in block
	MsgQRecive(qid, 1, &myMsgBuf, params.m_verbosity);
	*/
	MsgTransportGetCdr(mtid, &buf);
	CdrPrint(&buf.m_cdr);
	
	
	/*	
	strncpy(myMsgBuf.m_text, "Pong", MAX_TEXT_LENGTH);
	MsgQSend(qid, 2, &myMsgBuf, params.m_verbosity);
	usleep(1000000);*/

	for(;;)
	{
		/*
        if (-1 == MsgQReciveNoWait(qid, 1, &myMsgBuf, params.m_verbosity))
        {
			usleep(500);
        	continue;
        }
		strcpy(myMsgBuf.m_text, "Pong");
		MsgQSend(qid, 2, &myMsgBuf, params.m_verbosity);
		*/
		MsgTransportGetCdr(mtid, &buf);
		CdrPrint(&buf.m_cdr);
    }
	
	if (params.m_deleteMQ)
	{
		MsgQDestroy(mtid, params.m_verbosity);
	}

	printf("PONG exiting\n");
	
	return 0;
}




