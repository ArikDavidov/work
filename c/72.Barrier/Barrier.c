#include <stdio.h>		/* perror */
#include <stdlib.h>
#include <pthread.h>

#define BARRIER_MAGIC		0xBADEEEEE
#define IS_BARRIER(B)		((B) && BARRIER_MAGIC == (B)->m_magic)
/*#define HANDLE_ERROR(M)		do{perror(M);return -1;}while(0)*/


typedef struct Barrier
{
	unsigned int	m_magic;
	pthread_cond_t	m_cond;
	pthread_mutex_t	m_mutex;
	unsigned int	m_capacity;
	unsigned int	m_capacityCounter;
	unsigned int	m_referenceCounter;
} Barrier;


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
	
	if (-1 == pthread_cond_init(&barrier->m_cond, NULL));
	{
		perror("pthread_cond_init");
		return NULL;
	}
	if (-1 == pthread_mutex_init(&barrier->m_mutex, NULL));
	{
		perror("pthread_mutex_init");
		return NULL;
	}
	
	barrier->m_magic = BARRIER_MAGIC;
	barrier->m_capacity = _capacity;
	barrier->m_capacityCounter = 0;
	barrier->m_referenceCounter = 0;
	
	return barrier;
}


void BarrierDestroy(Barrier* _barrier)
{
	if (!IS_BARRIER(_barrier))
	{
		return;
	}
	
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
	
	pthread_mutex_destroy(&_barrier->m_mutex);
	pthread_cond_destroy(&_barrier->m_cond);
	
	free(_barrier);
}	

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
	++_barrier->m_capacityCounter;
	printf("m_referenceCounter: %d, m_capacityCounter: %d \n",
			 m_referenceCounter, m_capacityCounter);

	if (_barrier->m_capacityCounter < _barrier->m_capacity)
	{
		if (-1 == pthread_cond_wait(&_barrier->m_cond, &_barrier->m_mutex))
		{
			perror("pthread_cond_wait");
			return -1;
		}		
	}
	else
	{
		_barrier->m_capacityCounter = 0;
		
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
/*
int BarrierWait(Barrier* _barrier)
{
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
	
	pthread_mutex_lock(&_barrier->m_mutex);
		
	++_barrier->m_referenceCounter;
	++_barrier->m_capacityCounter;
	
	if (_barrier->m_capacityCounter < _barrier->m_capacity)
	{
		pthread_cond_wait(&_barrier->m_cond, &_barrier->m_mutex);
	}
	else
	{
		_barrier->m_capacityCounter = 0;
		pthread_mutex_unlock(&_barrier->m_mutex);
		pthread_cond_broadcast(&_barrier->m_cond);
	}
	
	--_barrier->m_referenceCounter;
	
	if (0 == _barrier->m_referenceCounter)
	{
		pthread_mutex_unlock(&_barrier->m_mutex);
		pthread_cond_broadcast(&_barrier->m_cond);
	}
	
	
	if (!IS_BARRIER(_barrier))
	{
		return 1;
	}
	
	return 0;
}
*/	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

