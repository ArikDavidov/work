#include <pthread.h>
#include <stdio.h>

#define NUM_OF_THREADS 10

int g_var = 0;

void* PrintFunc(void* tid)
{
	int i;
	int var = 0;
	
	for(i = 0; i < 100; ++i)
	{
		printf("Tread ID: %d, local var: %d, global var: %d\n", *(int*)tid, var, g_var);
		++var;
		++g_var;
	}

	pthread_exit(NULL);
}

int main()
{
	int i, status;
	pthread_t threads[NUM_OF_THREADS];

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, PrintFunc, (void*)&i);
		if (0 != status)
		{
			return 1;
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	return 0;
}





