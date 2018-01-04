#include <stdio.h>

void* g_arg = NULL;


void Hack(int _y)
{
	printf("I am in Hack\n");
	
	*((void**)(&_y - 1)) = g_arg;
	
}
 
int foo(int _x)
{
	int k = 5;
	int i;
	
	printf("I am in foo\n");
	
	for (i = 0; i <= 7; ++i)
	{
		printf("%p	%p	%d\n", (void*)(&_x - i), (void*)*(&_x - i), *(&_x - i));
	}
	printf("\n");
	
	printf("%p %d\n", (void*)&k, k);
	
	printf("\n");
	
	for (i = 0; i <= 7; ++i)
	{
		printf("%p	%p	%d\n", (void*)(&_x + i), (void*)*(&_x + i), *(&_x + i));
	}
	printf("\n");

	g_arg = *((void**)(&_x - 1));
	*((void**)(&_x - 1)) = Hack;	
			
	return i + _x;
}

int main()
{
	int a = 777;
	
	printf("I am in main\n");	
	foo(2);
	printf("Got back to main\n");
	
	return 0;
}



