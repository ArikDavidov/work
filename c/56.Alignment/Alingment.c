#include <stdio.h>

struct Foo
{
	char x;
	int y;
	char z;
	int i;
};

#pragma pack(push, 1) /* exact fit - no padding */
struct Bar
{
	char x;
	int y;
	char z;
	int i;
};
#pragma pack(pop) /* back to whatever the previous packing mode was */

struct Coocoo
{
	int y;
	int i;
	char x;
	char z;
};

int main()
{
	struct Foo    f;
	struct Bar    b;
	struct Coocoo c;

	/* pragma */
	
	printf("Size of struct containing {char, int, char, int}:	%d\n", sizeof(f));
	printf("Size of struct containing {char, char int, int}:	%d\n", sizeof(b));	 
	printf("Size of struct containing {int, int, char, char}:	%d\n", sizeof(c));

	return 0;
}	 
	 
	 
	 

