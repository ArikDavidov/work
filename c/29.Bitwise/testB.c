#include <stdio.h>
#include "Bitwise.h"

int main()
{ 
	unsigned int option, p, n, num, i, j, value;
	unsigned char byte, res, x,  y;
	int  cont = 1;

	while (cont)
	{
		printf("                                      \n");
		printf("Choose option:                        \n");
		printf("1: Compliment                         \n");
		printf("2: Rotate                             \n");
		printf("3: Set bits                           \n");
		printf("4: Set bits From i To j               \n");
		printf("Any another number - stop             \n");

		scanf("%u", &option);
		switch (option) 
		{
			case 1:
				printf("\nPlease enter a number (0-255):\n");
				scanf("%u", &byte);
				PrintByte(byte);
				res = Compliment(byte);
				PrintByte(res);										break;
			case 2:
				printf("\nPlease enter a number (0-255):\n");
				scanf("%u", &byte);
				PrintByte(byte);
				printf("\nPlease enter n (1-8):\n");
				scanf("%u", &n);
				res = Rotate(byte, n);
				PrintByte(res);										break;;
			case 3:
				printf("\nPlease enter x (0-255):\n");
				scanf("%u", &x);
				PrintByte(x);
				printf("\nPlease enter p (1-8):\n");
				scanf("%u", &p);
				printf("\nPlease enter n (1-8):\n");
				scanf("%u", &n);
				printf("\nPlease enter y (0-255):\n");
				scanf("%u", &y);								
				PrintByte(y);
				res = SetBits(x, p, n, y);
				PrintByte(res);										break;
			case 4:
				printf("\nPlease enter int :\n");
				scanf("%u", &num);
				PrintInt(num);
				printf("\nPlease enter i (0-31):\n");
				scanf("%u", &i);
				printf("\nPlease enter j (0-31):\n");
				scanf("%u", &j);
				printf("\nPlease enter value (0 / 1):\n");
				scanf("%u", &value);
				PrintInt(SetBitsFromTo(num, i, j, value));			break;
			default: cont = 0;										break;
		}
	}
	return 0;
}
