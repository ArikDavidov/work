#include "Producers.h"
#include "ProtectedQueue.h"
#include "Message.h"
#include "Context.h"

#include <stdlib.h>
#include <pthread.h>		/* pthread_create */


#define DEFAULT_REQUEST			"Static: Wazzaap!"


struct Producers
{
	pthread_t*	m_threadIDs;		/* ID returned by pthread_create() */
	size_t		m_nProducers;
};
	
	
Producers* ProducersCreate(size_t _numOfProducers, void* _context)
{
	Producers* producers = NULL;
	size_t i;
	
	if (0 == _numOfProducers)
	{
		return NULL;
	}	

	producers = malloc(sizeof(Producers));
	if (!producers)
	{
		return NULL;
	}
	
	producers->m_threadIDs = malloc(_numOfProducers * sizeof(pthread_t));
	if (!producers->m_threadIDs)
	{
		free(producers);
		return NULL;
	}
	
	for (i = 0; i < _numOfProducers; ++i)
	{
		if (0 != pthread_create(&producers->m_threadIDs[i], NULL, (void* (*)(void *))ProducerRoutine, _context));
		{
			/* TODO Destroy everything*/
			return NULL;
		}
	}

	producers->m_nProducers = _numOfProducers;

	return producers;
}

void* ProducerRoutine(Context* _context)
{
	size_t i;
	Message* msg = NULL;

	if (!_context)
	{
		return NULL;
	}

	for (i = 0; i < _context->m_nMsgs; ++i)
	{
		msg = MsgCreate(DEFAULT_REQUEST);

		ProtectedQueueInsert(_context->m_requestsQ, (void*)msg);
		/* The reply is not necessarily to this thread message */
		ProtectedQueueRemove(_context->m_replyQ, (void**)&msg);

		MsgDestroy(msg);
	}

	pthread_exit(NULL);
}

void ProducersJoin(Producers* _producers)
{
	size_t i;
	
	if (!_producers)
	{
		return;
	}
	
	for (i = 0; i < _producers->m_nProducers; ++i)
	{
		pthread_join(_producers->m_threadIDs[i], NULL);
	}
}	
	
void ProducersDestroy(Producers* _producers)
{
	if (!_producers)
	{
		return;
	}

	free(_producers->m_threadIDs);
	_producers->m_threadIDs = NULL;
	free(_producers);
}













