#include "Consumers.h"
#include "ProtectedQueue.h"
#include "Message.h"
#include "Context.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define DEFAULT_REPLY			"Ben El: Tudo boom!"


struct Consumers
{
	pthread_t*	m_threadIDs;		/* ID returned by pthread_create() */
	size_t		m_nConsumers;
};


Consumers* ConsumersCreate(size_t _numOfConsumers, Context* _context)
{
	Consumers* consumers = NULL;
	size_t i;
	
	if (0 == _numOfConsumers)
	{
		return NULL;
	}	

	consumers = malloc(sizeof(Consumers));
	if (!consumers)
	{
		return NULL;
	}
	
	consumers->m_threadIDs = malloc(_numOfConsumers * sizeof(pthread_t));
	if (!consumers->m_threadIDs){
		free(consumers);
		return NULL;
	}
	
	for (i = 0; i < _numOfConsumers; ++i)
	{
		if (0 != pthread_create(&consumers->m_threadIDs[i], NULL,  (void* (*)(void *))ConsumerRoutine, _context));
		{
			/* TODO Destroy everything*/
			return NULL;
		}
	}
	
	consumers->m_nConsumers = _numOfConsumers;

	return consumers;
}

void ConsumerRoutine(Context* _context)
{
	Message* msg = NULL;

	if (!_context)
	{
		return;
	}

	for (;;)
	{
		ProtectedQueueRemove(_context->m_requestsQ, (void**)&msg);
		printf("Consumer %lu recived a message\n", pthread_self());
		MsgUpdate(msg, DEFAULT_REPLY);
		ProtectedQueueInsert(_context->m_replyQ, (void*)msg);
	}

	pthread_exit(NULL);
}

void ConsumersJoin(Consumers* _consumers)
{
	size_t i;
	
	if (!_consumers)
	{
		return;
	}
	
	for (i = 0; i < _consumers->m_nConsumers; ++i)
	{
		pthread_join(_consumers->m_threadIDs[i], NULL);
		printf("Consumer %ld join.\n", pthread_self());

	}
}	
	
void ConsumersDestroy(Consumers* _consumers)
{
	if (!_consumers)
	{
		return;
	}

	free(_consumers->m_threadIDs);
	_consumers->m_threadIDs = NULL;
	free(_consumers);
	printf("ConsumersDestroy\n");
}



















