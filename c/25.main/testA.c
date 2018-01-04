#include <stdio.h>
#include "Arguments.h"

int main(int argc, char *argv[])
{
	int res = -1;
	
	if (3 != argc)
	{
		printf("Wrong numeber of arguments\n");
	}
	else if	((IsNumber(argv[1]) && IsName(argv[2])) || (IsNumber(argv[2]) && IsName(argv[1])))
	{
		printf("Valid Parameters\n");
		printf("%s %s\n", argv[1], argv[2]);
		res = 0;
	}	
	else
	{
		printf("Invalid Parameters\n");
	}
	return res;
}

