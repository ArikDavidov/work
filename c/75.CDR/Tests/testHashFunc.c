#include <stdio.h>


static size_t HashFunc(const void* _key)
{
	int sum;
	char* str = (char*)_key;
	
	for (sum = 0; '\0' != str[0]; ++str)
	{
		sum += (int)str[0];
	}
	
	return (size_t)sum;
}

/*
TODO nice hash function to test later
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; / * hash * 33 + c * /

    return hash;
}
*/

int main()
{
	char* str = "Zero bug approach"; /* 1644 */
	
	printf("%d\n", HashFunc((void*)str));

	return 0;
}






