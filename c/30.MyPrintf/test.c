#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int MyPrintf(char* _format, char* name, int age, double pi)
{
	char outputStr[1024], buffer[8];
	char* token;

	strcpy(outputStr, strtok(_format, "%%"));
	while (1)
	{		
		token = strtok (NULL, "%%");
		if (NULL == token)
		{
			break;
		}
		switch(token[0])
		{
			case 'd':
				sprintf(buffer, "%d", age);
				strcat(outputStr, buffer);
				strcat(outputStr, token + 1);				break;
			case 'f':
				sprintf(buffer, "%.2f", pi);
				strcat(outputStr, buffer);
				strcat(outputStr, token + 1);				break;
			case 's':
				strcat(outputStr, name);
				strcat(outputStr, token + 1);				break;
			case '%':
				sprintf(buffer, "%d", age);
				strcat(outputStr, buffer);
				strcat(outputStr, token + 1);				break;		
			default:
				return -1;
		}
	}
	puts(outputStr);

	return 0;
}

int main()
{
	char* name = "Yosi";
	int age = 25;
	double pi = 3.14;
	char str[] = "%s is %d years old and likes pi (%f).\n";
	
	MyPrintf(str, name, age, pi);

	return 0;

}


