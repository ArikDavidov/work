#include <stdio.h>
#include "DoubleLinkedList.h"

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

void TestCreate()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	if (NULL != list)
	{
		res = PASSED;
		ListDestroy(list);
	}	
	PrintTestResult(res, "TestCreate");
}

void TestDoubleDestroy()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	ListDestroy(list);
	ListDestroy(list);
	
	/* If no segmentation fault occurred */
	res = PASSED;

	PrintTestResult(res, "TestDoubleDestroy");
}

void TestListPushHead()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	if (NULL != list)
	{
		ListPushHead(list, 765);
		res = PASSED;		
		ListDestroy(list);
	}	
	PrintTestResult(res, "TestListPushHead");
}


void TestListPushTail()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	if (NULL != list)
	{
		ListPushTail(list, 123);
		res = PASSED;
		ListDestroy(list);
	}	
	PrintTestResult(res, "TestListPushTail");
}

int main()
{	
	TestCreate();
	TestDoubleDestroy();
	TestListPushHead();
	TestListPushTail();

	return 0;
}
