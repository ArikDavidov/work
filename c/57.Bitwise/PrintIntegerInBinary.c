#include <stdio.h>
#include <limits.h> /* CHAR_BIT */

/* #define NDEBUG 1 */

#define BITS_IN_INT (sizeof(int) * CHAR_BIT)
/* Getting the sign bit (the MSB in two's complement)
	using the mask 10000000000000000000000000000000 */
#define IS_NEGATIVE(N) ((N) & (1 << (BITS_IN_INT - 1))
#define BITS_IN_HEX 4

typedef struct
{
	unsigned int black			:1;
	unsigned int yellow			:1;
	unsigned int magenta		:1;
	unsigned int cyan			:1;
	unsigned int 				:1;
	unsigned int paperJam		:1;
	unsigned int paperEmpty		:1;
	unsigned int standBy		:1;
} StatusBits;

typedef union
{
	StatusBits		bits;	/* Bitfield */
	unsigned char 	num;
} PrinterStatus;


void PrintDec2Bin(int _num)
{
	int i;
	
	printf("Binary:");

	/* Iterating from left(MSB) to right(LSB). */
	for (i = BITS_IN_INT - 1; i >= 0; --i)
	{
		printf("%d", ((_num & (1 << i)) ? 1 : 0));
	}

	printf("\n");
}

void PrintDec2Hex(unsigned int _num)
{
	unsigned int i;
	/* 11110000000000000000000000000000 */
	unsigned int mask = (unsigned int)(~0 << (BITS_IN_INT - BITS_IN_HEX));
	char lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	printf("HEX:");
	
	for (i = 0; i < (BITS_IN_INT / BITS_IN_HEX); ++i)
	{
		/**
		 * Geting a chunk of 4 leftmost bits using the mask
		 * and moving them to the rightmost position.
		 * Then printing the coresponding char in the lookup tabel.
		 */
		printf("%c", lut[(_num & mask) >> (BITS_IN_INT - BITS_IN_HEX)]);
		/* Geting the next 4 digits to the leftmost position */
		_num <<= BITS_IN_HEX;
	}

	printf("\n");
}

int MyABS(int _num)
{
	return (IS_NEGATIVE(_num))) ? ~_num + 1 : _num;
}

void PrintPrinterStatus()
{
	int i;
	PrinterStatus status = {0};
	char* lut[] = {"Black color is missing, ", "Yellow color is missing, ", "Magenta color is missing, ",
					"Cyan color is missing, ", "", "Paper jam, ", "Paper tray is empty, ", "Standby, "};
	
	status.num = 34;
	printf("%d\n", status.num);

	printf("Printer Status: ");

	for (i = 0; i < CHAR_BIT; ++i)
	{	
		printf("%s", ((1 << i) & status.num) ? lut[i] : "");
	}
	printf("\n");
}

int main()
{
	int num;
	
	PrintPrinterStatus();
	printf("Please enter an integer: \n");
	scanf("%d", &num);
	
	PrintDec2Bin(num);
	printf("My ABS: %d\n", MyABS(num));	
	PrintDec2Hex((unsigned int)num);
	
	#ifndef NDEBUG
	printf("Hex (debuging): %08x\n", num);
	#endif /* NDEBUG */

	return 0;
}



