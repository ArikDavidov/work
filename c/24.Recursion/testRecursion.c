#include <stdio.h>
#include <string.h>
#include "Recursion.h"

#define NUMBER_OF_SOLUTIONS 92

int main()
{
	int i = 0, length = 0, solution, *res = NULL;
	int  intArr[64];
	int arr[8] = {0};
	char str[64];
	int searchValue = 0;
	int option;
	int cont = 1;			/* trigger to stop loop */


	while (cont) 
	{
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: Recursive Binary Search     \n");
		printf("2: Recursive String Reverse    \n");
		printf("3: Eight Queens                \n");
		printf("Any another number - stop      \n");

		scanf("%d", &option);
		/* Remove the '\n' from the stdio left there by scanf so it won't interfere with fgets */
		getc(stdin);
		switch (option) 
		{
			case 1:
				printf("Please enter array size:\n");
				scanf("%d", &length);
				for (i = 0; i < length; ++i)
				{
					printf("Please enter a number:\n");
					scanf("%d", &intArr[i]);
				}
				printf("Please enter search value:\n");
				scanf("%d", &searchValue);	
				res = BinarySearch(intArr, &intArr[length - 1], searchValue);
				if (NULL == res)
				{
					printf("Value not found\n");
				}
				else
				{
					printf("Index: %d\n", res - intArr);
				}															break;
			case 2:
				printf("Please enter a string:\n");
				fgets(str, 64, stdin);
				/* Removing the '\n' from the end of the string */
				str[strlen(str) - 1] = '\0';
				RecursiveStringReverse(str, strlen(str));
				puts(str);													break;
			case 3:
				for (solution = 0; solution < NUMBER_OF_SOLUTIONS; ++solution)
				{
					EightQueens(arr, 0, arr[0]);
					PrintSolution(arr, solution);
					/* Next iteration will contimnue from the next cell in the last row */
					arr[7] += 1;
				}															break;
					
			default: cont = 0;												break;
		}
	}			
	return 0;
}
