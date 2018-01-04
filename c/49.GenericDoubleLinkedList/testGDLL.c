#include "GenericDoubleLinkedList.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	FAILED,
	PASSED
} TestResult;

void PrintTestResult(TestResult _res, char* _testName)
{	
	printf("%s: %s\n", (FAILED == _res) ? "FAILED" : "PASSED", _testName);
}

int ElementDestroy(void* _element, void* _context)
{
	if (NULL == _element)
	{
		return -1;
	}
	
	free(_element);

	return 0;
}

void TestCreate()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	if (NULL != list)
	{
		res = PASSED;
		ListDestroy(&list, ElementDestroy);
	}	
	PrintTestResult(res, "TestCreate");
}

void TestDoubleDestroy()
{
	List* list = NULL;

	list = ListCreate();
	ListDestroy(&list, ElementDestroy);
	ListDestroy(&list, ElementDestroy);
	
	/* If no segmentation fault occurred */
	PrintTestResult(PASSED, "TestDoubleDestroy");
}

void TestListPushAndPopHead()
{
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;
	
	num = malloc(sizeof(int));
	*num = 765;
	
	list = ListCreate();
	ListPushHead(list, num);	
	ListPopHead(list, (void**)&ret);
	if (765 == *ret)
	{
		res = PASSED;
	}	
	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListPushAndPopHead");
}

void TestListPushAndPopTail()
{
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;
	
	num = malloc(sizeof(int));
	*num = 345;
	
	list = ListCreate();
	ListPushTail(list, num);	
	ListPopTail(list, (void**)&ret);
	if (345 == *ret)
	{
		res = PASSED;
	}	
	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListPushAndPopTail");
}

void TestListPushesAndPops()
{
	size_t i;
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;
	
	list = ListCreate();
	
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = (int)i;
		ListPushHead(list, num);
	}
	
	res = PASSED;
	for (i = 0; i < 8; ++i)
	{
		ListPopTail(list, (void**)&ret);
		if ((int)i != *ret)
		{
			res = FAILED;
			break;
		}
	}
	
	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListPushesAndPops");
}

void TestListCountItems()
{
	size_t i;
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	
	list = ListCreate();
	
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = (int)i;
		ListPushHead(list, num);
	}
	
	if (8 == ListCountItems(list))
	{
		res = PASSED;
	}
	
	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListCountItems");
}

void TestListIsEmptyWhenEmpty()
{
	TestResult res = FAILED;
	List* list = NULL;

	list = ListCreate();
	if (1 == ListIsEmpty(list))
	{
		res = PASSED;
	}	
	
	ListDestroy(&list, ElementDestroy);

	PrintTestResult(res, "TestListIsEmptyWhenEmpty");
}

void TestListIsEmptyAfterPushesAndPops()
{
	size_t i;
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;
	
	list = ListCreate();
	
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = (int)i;
		ListPushTail(list, num);
	}
	
	for (i = 0; i < 8; ++i)
	{
		ListPopHead(list, (void**)&ret);
	}
	
	if (1 == ListIsEmpty(list))
	{
		res = PASSED;
	}

	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListIsEmptyAfterPushesAndPops");
}

void TestListIsEmptyAfterPushesAndPops()
{
	size_t i;
	TestResult res = FAILED;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;
	
	list = ListCreate();
	
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = (int)i;
		ListPushTail(list, num);
	}
	
	for (i = 0; i < 8; ++i)
	{
		FindFirstForward(list, _predicateFunc, _context, _item);
	}
	
	if (1 == ListIsEmpty(list))
	{
		res = PASSED;
	}

	ListDestroy(&list, ElementDestroy);
	
	PrintTestResult(res, "TestListIsEmptyAfterPushesAndPops");
}

int main()
{	
	TestCreate();
	TestDoubleDestroy();
	TestListPushAndPopHead();
	TestListPushAndPopTail();
	TestListPushesAndPops();
	TestListCountItems();
	TestListIsEmptyWhenEmpty();
	TestListIsEmptyAfterPushesAndPops();
	
	return 0;
}
