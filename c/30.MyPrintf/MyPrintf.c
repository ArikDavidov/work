#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int MyPrintf(char* _format, ...)
{
	va_list args;
	va_start(args, _format);
	char outputStr[1024], buffer[8];
	char* pch;
	char* str;
	int nextParamInt = 0;
	double nextParamDouble  = 0.0;	
	
	pch = strtok(_format, "%");
	/* strcpy(outputStr, pch); */
	while (pch != NULL)
	{
		
		switch(pch[0])
		{
			case 'd':
				nextParamInt = va_arg(args, int);
				sprintf(buffer, "%d", nextParamInt);		continue;
			case 'f':
				nextParamDouble = va_arg(args, double);
				sprintf(buffer, "%f", nextParamDouble);		continue;
			case 's':
				str = va_arg(args, char*);				
				strcat(outputStr, str);						continue;
			case '%':
				str[0] = '%';
				strcat(outputStr, str);						continue;
			default:
				return -1;			
		}
		strcat(outputStr, buffer);
		pch = strtok (NULL, "%");
	}
	puts(outputStr);
	va_end(args);

	return 0;
}

int main()
{
	int age = 25;
	char str[] = "Yosi is %d years old.\n";
	
	/* pch = strtok(str, "i"); */
	MyPrintf(str, age);

	return 0;

}

