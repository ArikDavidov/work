#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
/* Compile with -pthread */

#define N 100
#define NUM_OF_PRODUCERS 1
#define NUM_OF_CONSUMERS 1

int g_var = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* Producer(void* _arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex); /* Enter critical section */
		sem_wait(&empty);
		++g_var;
		printf("Producer: %d\n", g_var);
		pthread_mutex_unlock(&mutex); /* Exit critical section */
		sem_post(&full);
	}	
	pthread_exit(NULL);
}

void* Consumer(void* _arg)
{
	while (1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex); /* Enter critical section */
		--g_var;
		printf("Consumer: %d\n", g_var);
		pthread_mutex_unlock(&mutex); /* Exit critical section */
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

int main()
{
	int i, status;
	pthread_t producers[NUM_OF_PRODUCERS];
	pthread_t consumers[NUM_OF_CONSUMERS];	

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);
	
	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		status = pthread_create(&producers[i], NULL, Producer, NULL);
		if (0 != status)
		{
			return 1;
		}
	}
	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		status = pthread_create(&consumers[i], NULL, Consumer, NULL);
		if (0 != status)
		{
			return 1;
		}
	}	
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	
	/* Wait for all threads to finish */
	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		pthread_join(producers[i], NULL);
	}
	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		pthread_join(consumers[i], NULL);
	}
	
	return 0;
}


