#include <stdio.h>

#include "BinaryTree.h"
#include "ADTErr.h"

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
	Tree* tree = NULL;

	tree = TreeCreate();
	if (NULL != tree)
	{
		res = PASSED;
		TreeDestroy(tree);
	}	
	PrintTestResult(res, "TestCreate");
}

void TestDoubleDestroy()
{
	TestResult res = FAILED;
	Tree* tree = NULL;

	tree = TreeCreate();
	TreeDestroy(tree);
	TreeDestroy(tree);
	
	/* If no segmentation fault occurred */
	res = PASSED;

	PrintTestResult(res, "TestDoubleDestroy");
}

void TestTreeInsertFirst()
{
	TestResult res = FAILED;
	Tree* tree = NULL;

	tree = TreeCreate();
	if (NULL != tree)
	{
		TreeInsert(tree, 16);
		res = PASSED;
		TreeDestroy(tree);
	}	
	PrintTestResult(res, "TestTreeInsert");
}

void TestTreeInsert()
{
	TestResult res = FAILED;
	Tree* tree = NULL;

	tree = TreeCreate();
	if (NULL != tree)
	{
		TreeInsert(tree, 123);
		res = PASSED;
		TreeDestroy(tree);
	}	
	PrintTestResult(res, "TestListPushTail");
}

int main()
{	
	TestCreate();
	TestDoubleDestroy();
	TestTreeInsert();

	return 0;
}
