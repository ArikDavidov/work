#include <ctype.h>
#include <string.h>
#include "Arguments.h"

int IsNumber(const char* str)
{	
	int i, res = 1;
	
	for (i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i]))
		{
			res = 0;
			break;
		}
	}
	return res;
}

int IsName(const char* str)
{	
	int i, res = 0;
	
	if (isupper(str[0]))
	{
		res = 1;
		for (i = 1; i < strlen(str); ++i)
		{
			if (!islower(str[i]))
			{
				res = 0;
				break;
			}
		}		
	}
	return res;
}






