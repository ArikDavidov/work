#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


typedef struct Context
{
	int					m_temp;
	pthread_mutex_t		m_mutex;
	pthread_cond_t		m_cond;
	/*int				m_nSensors;*/
} Context;


void* SensorRoutine(void* _context)
{
	Context* context = (Context*)_context;
	int randNum;
	printf("Sensor created\n");
	
	for (;;)
	{		
		pthread_mutex_lock(&context->m_mutex);
		randNum = rand() % 3 - 1;
		context->m_temp += randNum;
		
		printf("%d %d\n", randNum, context->m_temp);
		
		if (context->m_temp > 25 || context->m_temp < 21)
		{
			pthread_cond_signal(&context->m_cond);
			printf("signal! %d\n", context->m_temp);
		}
		
		pthread_mutex_unlock(&context->m_mutex);
		usleep(500000);
		
	}	

	pthread_exit(NULL);
}

void* ControllerRoutine(void* _context)
{
	Context* context = (Context*)_context;
	printf("Controller created\n");
	
	while(1)
	{
		pthread_mutex_lock(&context->m_mutex);

		if (context->m_temp <= 25 && context->m_temp >= 21)
		{
			pthread_cond_wait(&context->m_cond, &context->m_mutex);
			printf("Controller: temp was %d changed to 23\n", context->m_temp);
			context->m_temp = 23;	
		}
		pthread_mutex_unlock(&context->m_mutex);
	}	
	pthread_exit(NULL);
}

int main()
{
	int i, status;
	Context* context = NULL;
	pthread_t sensors[5];
	pthread_t controllers[3];
	
	
	context = malloc(sizeof(Context));
	context->m_temp = 20;
	pthread_mutex_init(&context->m_mutex, NULL);
	pthread_cond_init(&context->m_cond, NULL);
	

	for (i = 0; i < 5; ++i)
	{
		if (0 != pthread_create(&sensors[i], NULL, SensorRoutine, (void*)context))
		{
			return 1;
		}
	}
	for (i = 0; i < 3; ++i)
	{
		if (0 != pthread_create(&controllers[i], NULL, ControllerRoutine, (void*)context))
		{
			return 1;
		}
	}
		

	for (i = 0; i < 5; ++i)
	{
		pthread_join(sensors[i], NULL);
		printf("sensor %d joined\n", i);
	}
		
	for (i = 0; i < 3; ++i)
	{
		pthread_join(controllers[i], NULL);
		printf("controllers %d joined\n", i);
	}
	
	pthread_cond_destroy(&context->m_cond);
	pthread_mutex_destroy(&context->m_mutex);
	free(context);
	
	return 0;
}



