#include "HashMap.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>


typedef enum
{
	FAILED,
	PASSED
} TestResult;

void PrintTestResult(TestResult res, char* testName)
{	
	if(FAILED == res)
	{	
		printf("FAILED: %s\n", testName);
	}
	else
	{
		printf("PASSED: %s\n", testName);
	}
}

static size_t HashFunc(const void* _key)
{
	return *(size_t*)_key;
}

static int KeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	return *(size_t*)_firstKey == *(size_t*)_secondKey;
}
/*
static int (*KeyValueActionFunction)(const void* _key, void* _value, void* _context)
{
	
}

*/

void TestCreate()
{
	TestResult res = FAILED;
	HashMap* map = NULL;
	
	map = HashMapCreate(128, HashFunc, KeysEqualFunc);
	if (map)
	{
		res = PASSED;
	}
	
	PrintTestResult(res, "TestCreate");
}



int main()
{
	TestCreate();
	/*
	HashMapFindNotFound();
	HashMapFindFoundAfterOneInsert();
	HashMapFindFoundAfterMultipuleInserts();
	*/
	return 0;
}


