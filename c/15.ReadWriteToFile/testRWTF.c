#include <stdio.h>
#include "ReadWriteToFile.h"

int main(){
	FILE*	fp = NULL;
	int		n, option, res = -1;
	int cont = 1;			/* trigger to stop loop */

	while (cont) {
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: Print last N Lines          \n");
		printf("2: Print letters frequency     \n");
		printf("3: String concatenate          \n");		
		printf("Any another number - stop      \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				if((fp = fopen("data.txt", "r")) != NULL){
					printf("\nPlease enter the number of lines to print:\n");
					scanf("%d", &n);
					PrintLastNLines(fp, n);
					fclose(fp);
				}
				else{
					printf("\nCannot open file\n");
				}												break;
			case 2:
				if((fp = fopen("data.txt", "r")) != NULL){
					res = LetterFrequencyInFile(fp);
					fclose(fp);
				}
				else{
					printf("\nCannot open file\n");
				}												break;
			case 3:
				if((fp = fopen("data.txt", "r")) != NULL){
					res = WordFrequencyInFile(fp);
					fclose(fp);
				}
				else{
					printf("\nCannot open file\n");
				}												break;				
			default: cont = 0;									break;
			
		}

	}
	return res;
}

