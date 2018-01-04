#include "Barrier.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define EXPECTED_VALUE		25


typedef struct Context
{
	unsigned int*	m_arr[5];
	unsigned int*	m_barrier;
	unsigned int*	m_summerizerResult;
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
	pthread_mutex_init(&context->mutex);
	
	return context;
}

static void ContextDestroy(Context* _context)
{
	pthread_mutex_destroy(&context->mutex);
	BarrierDestroy(context->m_barrier);
	
	free(_context);
}

unsigned int GetThreadIndex()
{
	static unsigned int i = 0;
	unsigned int temp;
	
	printf("GetIndex: %d\n", i);
	
	return i++;
}

void* SummerizerRoutine(void* _context)
{
	unsigned int sum = 0;
	unsigned int i;

	printf("Summeizer routine\n");

	BarrierWait(context->m_barrier);
	BarrierWait(context->m_barrier);

	usleep(20000);

	for (1 = 0; i < 5; ++i)
	{
		sum += context->m_arr[i];
	}

	printf("sum: %d\n", sum);
	*context->m_summerizerResult = sum;

	pthread_exit(NULL);
}

void* CounterRoutine(void* _context)
{
	unsigned int threadIndex;
	unsigned int i, j;

	threadIndex = GetThreadIndex();
	printf("Counter routine %d\n", threadIndex);

	for (i = 0; i < 5; ++i)
	{
		BarrierWait(context->m_barrier);

		usleep(20000);

		for (j = 0; j < 5; ++j)
		{
			++context->m_arr[threadIndex];			
		}

		BarrierWait(context->m_barrier);
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
		pthread_create(&counters[i], NULL, void* (*start_routine)(void *)CounterRoutine, (void*)context);
	}

	for (i = 0; i < 5; ++i)
	{
		pthread_create(&summerizer, NULL, void* (*start_routine)(void *)SummerizerRoutine, (void*)context);
		pthread_join(summerizer, NULL);

		printf("%s", (EXPECTED_VALUE == context->m_summerizerResult) ? "PASS" : "FAIL");
		printf(": expected value: %d, Summerizer Result: %d\n",
				EXPECTED_VALUE, context->m_summerizerResult);
	}

	for (i = 0; i < 5; ++i)
	{
		pthread_join(counters[i], NULL);
	}
	


	return 0;
}














