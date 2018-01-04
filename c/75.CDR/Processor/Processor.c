#include "Processor.h"
#include "Subscribers.h"
#include "Operators.h"
#include "MsgTransport.h"
#include "CGF.h"
#include "CDR.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define PROCESSOR_THREADS_NUM	8
#define MAX_TEXT_LENGTH			256


typedef void (*QueryHandlerFunc)(Processor* _processor, char* _buf);


Processor* ProcessorCreate()
{
	Processor* processor = NULL;
	
	processor = calloc(1, sizeof(Processor));
	if (!processor)
	{
		goto EXIT;
	}
	
	processor->m_subscribers = SubscribersCreate();
	if (!processor->m_subscribers)
	{
		goto FREE_PROCESSOR;
	}

	processor->m_operators = OperatorsCreate();
	if (!processor->m_operators)
	{
		goto DESTROY_SUBSCRIBERS;
	}
	
	processor->m_mtid = MsgTransportCreate();
	if (!processor->m_operators)
	{
		goto DESTROY_OPERATORS;
	}
	
	return processor;
	
	/* 
	TODO Destroys
	*/
	FREE_PROCESSOR:
		free(processor);
	DESTROY_OPERATORS:
		/*OperatorsDestroy(processor->m_operators);*/
		
	DESTROY_SUBSCRIBERS:
		/*SubscribersDestroy(processor->m_subscribers);*/
	EXIT:
		fprintf(stderr, "ProcessorCreate failed\n");
		exit(EXIT_FAILURE);
}

void* ProcessorRoutine(void* _context)
{	
	MsgTransportBuf buf;
	Processor* processor = (Processor*)_context;
	
	printf("Processor routine\n");
	
	while(1/*!processor->m_shutDownMode*/)
	{
		usleep(200);
		/*printf("Getting CDR\n");*/
		MsgTransportGetCdr(processor->m_mtid, &buf);
		SubscribersProcess(processor->m_subscribers, &buf.m_cdr);
		OperatorsProcess(processor->m_operators, &buf.m_cdr);
		/*
		CdrPrint(&buf.m_cdr);
		*/
	}
	
	pthread_exit(NULL);
}

void* CgfRoutine(void* _context)
{	
	int i;
	MsgTransportBuf buf;
	Processor* processor = (Processor*)_context;
	QueryHandlerFunc QueryHandler[] = {CgfSubscriberRetrieveQuery, CgfOperatorRetrieveQuery/*,
										CgfOperatorsReport, CgfSubscribersReport*/};
	
	while(1/*!processor->m_shutDownMode*/)
	{
		usleep(200);

		MsgTransportGetQuery(processor->m_mtid, &buf);
		printf("CgfRoutine:ResivedQuery: %s\n", (char*)&buf.m_cdr);
		
		sscanf((char*)&buf.m_cdr, "%d", &i);
		printf("%d\n", i);
		QueryHandler[i](processor, (char*)&buf.m_cdr);
		
		printf("CgfRoutine:QueryReply: %s\n", (char*)&buf.m_cdr);
		MsgTransportSendReply(processor->m_mtid, &buf);
		printf("CgfRoutine:ReplySent\n");

	}
	
	pthread_exit(NULL);
}

void ProcessorRun(Processor* _processor)
{
	size_t i;
	
	printf("Processor is Running...\n");
	
	for (i = 0; i < PROCESSOR_THREADS_NUM; ++i)
	{
		pthread_create(&_processor->m_processorThreads[i], NULL, ProcessorRoutine, (void*)_processor);
	}
	
	pthread_create(&_processor->m_cgfThread, NULL, CgfRoutine, (void*)_processor);
	
	usleep(200);
}

void ProcessorShutDown(Processor* _processor)
{
	size_t i;
	
	_processor->m_shutDownMode = 1;	/* TODO Add mutex protection */
	printf("Processor is joining...\n");
	
	for (i = 0; i < PROCESSOR_THREADS_NUM; ++i)
	{
		pthread_join(_processor->m_processorThreads[i], NULL);
	}
	
	pthread_join(_processor->m_cgfThread, NULL);
	
	/* TODO Destroys
	MsgTransportDestroy(processor->m_mtid);
	OperatorsDestroy(processor->m_operators);
	SubscribersDestroy(processor->m_subscribers);
	*/	
	printf("Joined All threads\n");
}


int main()
{
	Processor* processor = NULL;
	
	processor = ProcessorCreate();
	ProcessorRun(processor);
	ProcessorShutDown(processor);
	
	printf("Main thread is Exiting...\n");
	
	return 0;
}





	






