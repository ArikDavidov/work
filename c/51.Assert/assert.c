#include <stdio.h>
#define NDEBUG 1
#include <assert.h>

int main()
{
	int num;
	
	printf("Please enter a number (1-4):\n");
	scanf("%d", &num);
	
	assert(1 != num);
	assert(2 != num);
	assert(3 != num);
	assert(4 != num);
	printf("after assert\n");
		
	return 0;
}

