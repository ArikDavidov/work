#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int g_var = 0;

int main()
{
	int l_var = 0;
	int n, i;
	
	n = fork();
	if (n < 0)
	{
		printf("Fork failed\n");
	}
	else if (n > 0)
	{
		for (i = 0; i < 15; ++i)
		{
			++g_var;
			printf("Parent g_var: %d\n", g_var);
			++l_var;
			printf("Parent l_var: %d\n", l_var);
			sleep(2);
		}
		/*wait(&n);*/
	}
	else
	{
		for (i = 0; i < 15; ++i)
		{
			--g_var;
			printf("Son g_var: %d\n", g_var);
			--l_var;
			printf("Son l_var: %d\n", l_var);
			sleep(1);
		}
	}
	
	return 1;
}

