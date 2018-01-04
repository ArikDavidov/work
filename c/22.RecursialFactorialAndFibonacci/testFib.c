#include <stdio.h>
#include "FactorialAndFibonacci.h"

int main()
{
	int i = 0;
	
	printf("Please enter number:\n");
	scanf("%d", &i);
	printf("Fib: %d\n", Fib(i));
	
	return 0;
}
