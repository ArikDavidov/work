#include "DoubleBarrier.h"

#include <stdio.h>		/* perror */
#include <stdlib.h>
#include <pthread.h>


#define CLOSE				0
#define	OPEN				1
#define BARRIER_MAGIC		0xBADEEEEE
#define IS_BARRIER(B)		((B) && BARRIER_MAGIC == (B)->m_magic)
/*#define HANDLE_ERROR(M)		do{perror(M);return -1;}while(0)*/

struct Barrier
{
	unsigned int	m_magic;
	pthread_mutex_t	m_mutex;
	pthread_cond_t	m_batchCond;
	pthread_cond_t	m_entranceCond;
	pthread_cond_t	m_exitCond;
	unsigned int	m_capacity;
	unsigned int	m_totalCounter;			/* For calculating batch number of each proccess */
	unsigned int	m_currentBatch;
	unsigned int	m_entranceCounter;	
	unsigned int	m_exitCounter;
	unsigned int	m_entranceGateState;
	unsigned int	m_exitGateState;
};


Barrier* BarrierCreate(unsigned int _capacity)
{
	Barrier* barrier = NULL;
	
	if (0 == _capacity)
	{
		return NULL;
	}
	
	barrier = malloc(sizeof(Barrier));
	if (!barrier)
	{
		return NULL;
	}
	
	if (-1 == pthread_mutex_init(&barrier->m_mutex, NULL));
	{
		perror("pthread_mutex_init");
		return NULL;
	}
	if (-1 == pthread_cond_init(&barrier->m_batchCond, NULL));
	{
		perror("pthread_cond_init");
		return NULL;
	}
	if (-1 == pthread_cond_init(&barrier->m_entranceCond, NULL));
	{
		perror("pthread_cond_init");
		return NULL;
	}
	if (-1 == pthread_cond_init(&barrier->m_exitCond, NULL));
	{
		perror("pthread_cond_init");
		return NULL;
	}
	
	barrier->m_magic				= BARRIER_MAGIC;
	barrier->m_capacity				= _capacity;
	barrier->m_totalCounter			= 0;
	barrier->m_currentBatch			= 0;
	barrier->m_entranceCounter		= 0;
	barrier->m_exitCounter			= 0;
	barrier->m_entranceGateState	= CLOSE;
	barrier->m_exitGateState		= CLOSE;

	return barrier;
}


void BarrierDestroy(Barrier* _barrier)
{
	if (!IS_BARRIER(_barrier))
	{
		return;
	}
	/*
	if (-1 == pthread_mutex_lock(&_barrier->m_mutex))
	{
		perror("pthread_mutex_lock");
		return;
	}

	_barrier->m_magic = 0;
		
	if (-1 == pthread_cond_broadcast(&_barrier->m_cond))
	{
		perror("pthread_cond_broadcast");
		return;
	}
	
	while (0 < _barrier->m_referenceCounter)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_cond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			return;
		}
	}
	if (-1 == pthread_mutex_unlock(&_barrier->m_mutex))
	{
		perror("pthread_mutex_unlock");
		return;
	}
	*/
	
	pthread_cond_destroy(&_barrier->m_exitCond);
	pthread_cond_destroy(&_barrier->m_entranceCond);
	pthread_cond_destroy(&_barrier->m_batchCond);

	pthread_mutex_destroy(&_barrier->m_mutex);
	
	free(_barrier);
}
	
int BarrierWait(Barrier* _barrier, Routine _rutineFunc, void* _context)
{
	unsigned int batch;
	
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
		
	pthread_mutex_lock(&_barrier->m_mutex);
	
	++_barrier->m_totalCounter;	
	batch = _barrier->m_totalCounter / _barrier->m_capacity;	
	printf("m_totalCounter: %d, batch: %d \n",
			 _barrier->m_totalCounter, batch);
			 
	while (batch > _barrier->m_currentBatch)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_batchCond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			pthread_mutex_unlock(&_barrier->m_mutex);
			return -1;
		}		
	}
	
	++_barrier->m_entranceCounter;
	
	while (CLOSE == _barrier->m_entranceGateState && _barrier->m_entranceCounter < _barrier->m_capacity)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_entranceCond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			pthread_mutex_unlock(&_barrier->m_mutex);
			return -1;
		}		
	}
	
	if (_barrier->m_entranceCounter == _barrier->m_capacity)
	{
		_barrier->m_entranceGateState = OPEN;
		if (-1 == pthread_cond_broadcast(&_barrier->m_entranceCond))
		{
			perror("pthread_cond_broadcast");
			pthread_mutex_unlock(&_barrier->m_mutex);
			return -1;
		}
	}
	
	--_barrier->m_entranceCounter;
	
	if (0 == _barrier->m_entranceCounter)
	{
		_barrier->m_entranceGateState = CLOSE;
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
	
	
	if (_rutineFunc)
	{
		_rutineFunc(_context);
	}
	
	
	pthread_mutex_lock(&_barrier->m_mutex);
	
	++_barrier->m_exitCounter;

	while (CLOSE == _barrier->m_exitGateState && _barrier->m_exitCounter < _barrier->m_capacity)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_exitCond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			return -1;
		}		
	}
	
	if (_barrier->m_exitCounter == _barrier->m_capacity)
	{
		_barrier->m_exitGateState = OPEN;
		if (-1 == pthread_cond_broadcast(&_barrier->m_exitCond))
		{
			perror("pthread_cond_broadcast");
			pthread_mutex_unlock(&_barrier->m_mutex);
			return -1;
		}
	}
	
	--_barrier->m_exitCounter;
	
	if (0 == _barrier->m_exitCounter)
	{
		_barrier->m_exitGateState = CLOSE;
		++_barrier->m_currentBatch;
		
		if (-1 == pthread_cond_broadcast(&_barrier->m_batchCond))
		{
			perror("pthread_cond_broadcast");
			pthread_mutex_unlock(&_barrier->m_mutex);
			return -1;
		}
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
	/*
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
	*/
	return 0;
}
	

/*
int BarrierWait(Barrier* _barrier)
{
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
	
	if (-1 == pthread_mutex_lock(&_barrier->m_mutex))
	{
		perror("pthread_mutex_lock");
		return -1;
	}
		
	++_barrier->m_referenceCounter;
	++_barrier->m_entranceCounter;
	printf("m_referenceCounter: %d, m_entranceCounter: %d \n",
			 m_referenceCounter, m_entranceCounter);

	if (_barrier->m_entranceCounter < _barrier->m_capacity)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_cond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			return -1;
		}		
	}
	else
	{
		_barrier->m_entranceCounter = 0;
		
		if (-1 == pthread_cond_broadcast(&_barrier->m_cond))
		{
			perror("pthread_cond_broadcast");
			return -1;
		}
	}
	--_barrier->m_referenceCounter;
	
	
	if (0 == _barrier->m_referenceCounter && !IS_BARRIER(_barrier))
	{
		if (-1 == pthread_cond_broadcast(&_barrier->m_cond))
		{
			perror("pthread_cond_broadcast");
			return -1;
		}
	}
	
	pthread_mutex_unlock(&_barrier->m_mutex);
	
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
	
	return 0;
}
*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

