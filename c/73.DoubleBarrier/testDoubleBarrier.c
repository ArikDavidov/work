#include "DoubleBarrier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* usleep */
#include <pthread.h>


#define EXPECTED_VALUE		25


typedef struct Context
{
	int*			m_arr;
	Barrier*		m_barrier;
	int				m_summerizerResult;
	pthread_mutex_t m_mutex;
} Context;


static Context* ContextCreate()
{
	Context* context = NULL;
	
	printf("Creating Context\n");

	context = malloc(sizeof(Context));
	if(!context)
	{
		return NULL;
	}
	
	context->m_arr = calloc(5, sizeof(int));
	context->m_barrier = BarrierCreate(6);
	context->m_summerizerResult = 0;
	pthread_mutex_init(&context->m_mutex, NULL);
	
	return context;
}

static void ContextDestroy(Context* _context)
{
	pthread_mutex_destroy(&_context->m_mutex);
	BarrierDestroy(_context->m_barrier);
	
	free(_context);
}

void GetThreadIndex(unsigned int* _i, pthread_mutex_t* _mutex)
{
	static unsigned int index = 0;
	
	pthread_mutex_lock(_mutex);

	printf("GetIndex: %d\n", index);
	*_i = index++;

	pthread_mutex_unlock(_mutex);
}

static int SumArray(int* _arr)
{
	unsigned int i;
	int sum = 0;

	for (i = 0; i < 5; ++i)
	{
		sum += _arr[i];
	}

	printf("sum: %d\n", sum);
	
	return sum;
}

void* SummerizerRoutine(void* _context)
{
	printf("Summeizer routine\n");

	usleep(20000);

	((Context*)_context)->m_summerizerResult = SumArray(_context->m_arr);

	pthread_exit(NULL);
}


void* CounterRoutine(void* _context)
{
	unsigned int threadIndex;
	unsigned int i, j;

	GetThreadIndex(&threadIndex, _context->m_mutex);
	printf("Counter routine %d\n", threadIndex);

	for (i = 0; i < 5; ++i)
	{
		BarrierWait(_context->m_barrier);

		usleep(20000);

		for (j = 0; j < 5; ++j)
		{
			++_context->m_arr[threadIndex];
		}

		BarrierWait(_context->m_barrier, NULL, NULL);
	}

	pthread_exit(NULL);
}


int main()
{
	pthread_t summerizer;
	pthread_t counters[5];
	Context* context = NULL;
	int i;
	
	context = ContextCreate();
	
	for (i = 0; i < 5; ++i)
	{
		pthread_create(&counters[i], NULL, (void* (*start_routine)(void*))CounterRoutine, (void*)context);
	}

	for (i = 0; i < 5; ++i)
	{
		pthread_create(&summerizer, NULL, (void* (*start_routine)(void*))SummerizerRoutine, (void*)context);
		pthread_join(summerizer, NULL);

		printf("%s", (EXPECTED_VALUE == *context->m_summerizerResult) ? "PASS" : "FAIL");
		printf(": expected value: %d, Summerizer Result: %d\n",
				EXPECTED_VALUE, *context->m_summerizerResult);
	}

	for (i = 0; i < 5; ++i)
	{
		pthread_join(counters[i], NULL);
	}
	
	ContextDestroy(context);

	return 0;
}














