#include <stdio.h>



void GetUserData()
{
	int i;
	char buffer[10];
	
	for (i = 0; i < 10; ++i)
	{
		printf("Please enterstring\n");
		scanf("%s", buffer);
		printf("%s\n", buffer);
	}
}


int main()
{
	GetUserData();
	
	/*
	*** stack smashing detected ***: ./a.out terminated
	Aborted (core dumped)
	*/
	
	printf("returned to main\n");
	
	return 0;
}


