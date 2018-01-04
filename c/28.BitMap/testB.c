#include <stdio.h>
#include "BitMap.h"

int main()
{ 
	unsigned int nof, funcNum, bitNum;
	bitwise bitwiseFunc[3] = {BitOn, BitOff, IsBitOn};
	BitMap_t* bitMap;
	int  res = 0;
		
	printf("Please enter number of features:\n");
	scanf("%u", &nof);
	bitMap = CreateBM(nof);
	if (NULL == bitMap)
	{
		printf("creation failed.\n");
		return -1;
	}
	while (1)
	{
		printf("                                      \n");
		printf("Choose option:                        \n");
		printf("1: BitOn                              \n");
		printf("2: BitOff                             \n");
		printf("3: IsBitOn                            \n");
		printf("Any another number - destroy and stop \n");

		scanf("%u", &funcNum);		
		if (funcNum < 1 || funcNum > 3)
		{
			break;
		}
		printf("\nPlease enter bit number:\n");
		scanf("%u", &bitNum);
		res = Calculate(bitwiseFunc[funcNum - 1], bitMap, bitNum);
		if (-1 == res)
		{
			printf("\nFunction failed!\n");
			continue;
		}
		if (3 == funcNum)
		{
			if (0 == res)
			{
				printf("\nThe bit is off.\n");
			}
			else
			{
				printf("\nThe bit is on.\n");
			}
		}
		PrintBM(bitMap);
	}			
	Destroy(bitMap);
	return 0;
}
