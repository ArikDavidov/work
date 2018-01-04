#include <stdio.h>
#include "FactorialAndFibonacci.h"

int main()
{
	int i = 0;
	
	printf("Please enter number:\n");
	scanf("%d", &i);
	printf("Factorial: %d\n", Factorial(i));
	
	return 0;
}
