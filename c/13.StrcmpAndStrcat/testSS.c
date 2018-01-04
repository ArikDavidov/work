#include <stdio.h>
#include <string.h>
#include "StringManipulation.h"

int main(){

	char str1[256];
	char str1[256];
	int res = 0, option;
	int cont = 1;			/* trigger to stop loop */

	while (cont) {
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: String compare              \n");
		printf("2: String concatenate          \n");
		printf("Any another number - stop      \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				printf("\nPlease enter the first string:\n");
				scanf("%s", str1);
				printf("\nPlease enter the second string:\n");
				scanf("%s", str2);
				res = strcmp(str1, str2);

				if(res < 0){
				  printf("str1 is less than str2");
				}
				else if(res > 0){
				  printf("str2 is less than str1");
				}
				else{
				  printf("str1 is equal to str2");
				}												break;
			case 2:
				printf("\nPlease enter the first string:\n");
				scanf("%s", str1);
				printf("\nPlease enter the second string:\n");
				scanf("%s", str2);
				res = strcmp(str1, str2);

				if(res < 0){
				  printf("str1 is less than str2");
				}
				else if(res > 0){
				  printf("str2 is less than str1");
				}
				else{
				  printf("str1 is equal to str2");
				}												break;
			default: cont = 0;									break;
			
		}

	}
	return res;
}

