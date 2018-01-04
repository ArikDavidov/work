#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* PrintFunc(void* _tid)
{
	int a = 0;
	
	printf("Process %d: %p\n", *(int*)_tid, (void*)&a);
	pthread_exit(NULL);
	
}

int main()
{
	int status, i = 0;
	pthread_t thread;
	
	while (1)
	{
		status = pthread_create(&thread, NULL, PrintFunc, (void*)&i);
		if (0 != status)
		{
			return 1;
		}
		++i;
	}
	return 0;	
}


