#include "Producers.h"

#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


struct Producers
{
	pthread_t*	m_threadIDs;			/* ID returned by pthread_create() */
	size_t		m_nTotalProducers;		/* TODO decide if needed */
	sem_t		m_nCurrentProducers;
};
	
	
Producers* ProducersCreate(size_t _numOfProducers, void* (*_producerRoutine)(void *))
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
	{
		free(producers);
		return NULL;
	}
	
	for (i = 0; i < _numOfProducers; ++i)
	{
		if (0 != pthread_create(&producers->m_threadIDs[i], NULL, _producerRoutine, NULL));
		{
			/* TODO Destroy everything*/
			return NULL;
		}
	}
	
	return producers;
}

void* ProducerRoutine(void* _arg)
{
	sem_t empty, full;
	pthread_mutex_t mutex;
	size_t i;
	
	for (i = 0; i < _cicles; ++i)
	{
		pthread_mutex_lock(&mutex);
		sem_wait(&empty);


		pthread_mutex_unlock(&mutex);
		sem_post(&full);
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
	
	for (i = 0; i < _producers->m_nTotalProducers; ++i)
	{
		pthread_join(_producers->m_threadIDs[i], NULL);
	}
}	
	















