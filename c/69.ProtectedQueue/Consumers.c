#include "Consumers.h"

#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE		128
/*
#definne BUF_INSERT(B, S) do{strncpy(B->m_str, S, B->m_maxLen);}while(0)
*/

struct Consumers
{
	pthread_t*	m_threadIDs;			/* ID returned by pthread_create() */
	size_t		m_nTotalConsumers;		/* TODO decide if needed */
	sem_t		m_nCurrentConsumers;
	/*
	Queue*		m_requestsQ;
	Queue*		m_replyQ;
	
	*/
};

typedef struct Buffer
{
	char[MAX_BUFFER_SIZE]	m_str;
	size_t					m_maxLen;
} Buffer;


/*, void* (*_consumerRoutine)(void *)*/
Consumers* ConsumersCreate(size_t _numOfConsumers, void (*ProssesMsg)(void*))
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
	{
		free(consumers);
		return NULL;
	}
	
	for (i = 0; i < _numOfConsumers; ++i)
	{
		if (0 != pthread_create(&consumers->m_threadIDs[i], NULL, ConsumerRoutine, NULL));
		{
			/* TODO Destroy everything*/
			return NULL;
		}
	}
	
	return consumers;
}

void ConsumerRoutine(void* _arg)
{
	Buffer
	for (;;)
	{
		QueueRemove();

		

		QueueInsert();

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
	
	for (i = 0; i < _consumers->m_nTotalConsumers; ++i)
	{
		pthread_join(_consumers->m_threadIDs[i], NULL);
	}
}	
	


























