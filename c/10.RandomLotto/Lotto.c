#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"Lotto.h"

#define MAX_NUM 49
#define ROWS 5
#define COLUMNS 10

int GenerateRandNums(int* _randNumArr, unsigned int _namOfRandomNums){

	int i = 0, j = 0, randNum, res;
	
	if(NULL != _randNumArr)
	{
		srand(time(NULL));
		while(i < _namOfRandomNums)
		{			
			randNum = rand() % MAX_NUM + 1;			/*Generates random number betwen 1 and MAX_NUM*/
			for(j = 0; j <= i; ++j)
			{
				if(i==j)
				{
					_randNumArr[j] = randNum;
					++i;
					break;
				}
				if(_randNumArr[j] == randNum)
				{ /*Check if curent number was allready generated*/
					break;
				}
			}				
		}
	}
	return res;	
}

int PrintRandNums(int* randNumArr, unsigned int namOfRandomNums){
	int i;
	for(i = 0; i < namOfRandomNums; ++i){
		printf(" %d", randNumArr[i]);
	}
	printf("\n\n");
}

int PrintLottoCard(int* randNumArr,unsigned int namOfRandomNums){

	int i = 0, j = 0, lottoPrintMatrix[ROWS][COLUMNS] = {0}, res = -1;

	if(randNumArr != NULL){
		for(i = 0; i < NUM_OF_RANDOM_NUMS; ++i){
			lottoPrintMatrix[(randNumArr[i] -1) / COLUMNS][(randNumArr[i] -1) % COLUMNS] = 1;
		}
		lottoPrintMatrix[ROWS - 1][COLUMNS - 1]=2;			/* Marking the 50th number because it is not part of the 1-49 range*/

		printf("  1 2 3 4 5 6 7 8 9 10\n");
		for(i = 0; i < ROWS; ++i){
			printf("%d", i);
			for(j = 0; j < COLUMNS; ++j){
				if(lottoPrintMatrix[i][j] == 0){
					printf(" -");
				}
				else if(lottoPrintMatrix[i][j] == 1){
					printf(" +");
				}
				else{
					printf("  ");			/* Replaceing the 50th number whith blank*/
				}
			}
			printf("\n\n");
		}
		res = 0;
	}
	return res;
}



