#include <stdio.h>
#include <stdlib.h>
#include "StringManipulation.h"

int main(){
	char string[256];
	int res = 0, option	, integer, base;
	int cont = 1;			/* trigger to stop loop */

	while (cont) {
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: Reversed string             \n");
		printf("2: Create Meeting              \n");
		printf("3: Convrt String to integer    \n");
		printf("4: Convert integer to string   \n");
		printf("Any another number - stop      \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				printf("\nPlease enter a string:\n");
				//scanf("%s", string);
				gets(string);
				res = ReverseString(string);
				if(res == 0){
					printf("\nReversed string: %s\n", string);
				}
				else{
					printf("\nReverseString failed\n");
				}												break;
			case 2:
				printf("\nPlease enter a string:\n");
				gets(string);
				res = IsPalindrom(string);
				if(res == 1){
					printf("\nIt's a palindrom!\n");
				}	
				else if(res == 0){
					printf("\nIt's not a palindrom!\n");
				}
				else{
					printf("\nIsPalindrom failed\n");
				}												break;
			case 3:
				printf("\nPlease enter a string:\n");
				gets(string);
				res = MyAToI(string);
				if(res == -1){
					printf("\nError!\n");
				}
				else{
					printf("\nResult: %d\n", res);
				}												break;
			case 4:
				printf("\nPlease enter an integer:\n");
				scanf("%d", &integer);
				printf("\nPlease enter the base:\n");
				scanf("%d", &base);
				MyIToA(integer, string, base);
				if(string == NULL){
					printf("\nError!\n");
				}
				else{
					printf("\nResult: %s\n", string);
				}												break;
			default: cont = 0;									break;
			
		}

	}
	return res;
}

