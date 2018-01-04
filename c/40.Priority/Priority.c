#include <stdlib.h>
#include <string.h>
#include <stdio.h>	
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int i;
	float a = 5.99;
	
	for (i = 0; i < 500000; ++i)
	{
		if (10000 == i)
		{
			nice(10);
		}
		a *= 6.99;
		a /= 4.99;	
	}
	
	return 0;
}
