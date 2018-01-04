#include <stdio.h>
#include <string.h>

unsigned int IsPalindrom(char* _arr, unsigned int _length);

int main()
{
	char str[128];
	
	printf("Please enter string:\n");
	fgets(str, 128, stdin);
	if (IsPalindrom(str, strlen(str) - 1))
	{
		printf("It's a palindrom! \n");
	}
	else
	{
		printf("It's not a palindrom! \n");	
	}	
	return 0;
}
