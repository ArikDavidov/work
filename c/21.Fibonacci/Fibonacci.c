#include <stdio.h>

unsigned int Fib(unsigned int _n)
{
	int arr[] = {0, 1};
	int i;

	for (i = 2; i <= _n; ++i)
	{
		arr[i % 2] = arr[0] + arr[1];
	}
	return arr[_n % 2];
}

int main()
{
	int i = 0;

	printf("Please enter a number:\n");
	scanf("%d", &i);
	printf("Fibonacci: %d\n", Fib(i));

	return 0;
}















