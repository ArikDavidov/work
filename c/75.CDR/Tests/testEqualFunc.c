#include <stdio.h>
#include <string.h>

static int KeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	return !strcmp((char*)_firstKey, (char*)_secondKey);
}


int main()
{
	char* a = "0000";
	char* b = "0000";
	char* c = "A";
	char* d = "F";
	char* e = "F";
	
	printf("%d\n", KeysEqualFunc((void*)a, (void*)b));
	printf("%d\n", KeysEqualFunc((void*)c, (void*)d));
	printf("%d\n", KeysEqualFunc((void*)d, (void*)e));	

	return 0;
}






