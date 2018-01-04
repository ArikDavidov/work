#include"Lotto.h"

#define NUM_OF_RANDOM_NUMS 6


int main(){

	int randNumArr[NUM_OF_RANDOM_NUMS];

	GenerateRandNums(randNumArr, NUM_OF_RANDOM_NUMS);
	PrintRandNums(randNumArr, NUM_OF_RANDOM_NUMS);
	PrintLottoCard(randNumArr, NUM_OF_RANDOM_NUMS);

	return 0;
}

