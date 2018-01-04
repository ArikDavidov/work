#include "Tree.h"

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

int Less(void* _left, void* _right)
{
	return (*(int*)_left < *(int*)_right);
}

void Destroyer(void* _data)
{
	free(_data);
}
/*
static void TreePrint(BSTree* _tree, TreeTransverse _transverseMode)
{
	if (NULL != _tree)
	{
		printf("No tree was found.\n");
	}
	if (NULL != _tree->m_root)
	{
		printf("Tree is empty.\n");
	}

	switch(_transverseMode)
	{
		case PRE_ORDER:
			TreePrintPreOrder(_tree->m_root);		break;
		case IN_ORDER:
			TreePrintInOrder(_tree->m_root);		break;
		case POST_ORDER:
			TreePrintPostOrder(_tree->m_root);		break;
	}
	printf("\n");
}
*/
void TestCreate()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;

	tree = BSTreeCreate(Less);
	if (NULL != tree)
	{
		res = PASSED;
		BSTreeDestroy(tree, Destroyer);
	}	
	PrintTestResult(res, "TestCreate");
}

void TestCreateNullLessFunc()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;

	tree = BSTreeCreate(NULL);
	if (NULL == tree)
	{
		res = PASSED;
	}	

	PrintTestResult(res, "TestCreateNullLessFunc");
}

void TestDestroyNullDestroyer()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;

	tree = BSTreeCreate(Less);
	BSTreeDestroy(tree, NULL);
	
	/* If no segmentation fault occurred */
	res = PASSED;

	PrintTestResult(res, "TestDestroyNullDestroyer");
}

void TestDoubleDestroy()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;

	tree = BSTreeCreate(Less);
	BSTreeDestroy(tree, Destroyer);
	BSTreeDestroy(tree, Destroyer);
	
	/* If no segmentation fault occurred */
	res = PASSED;

	PrintTestResult(res, "TestDoubleDestroy");
}

void TestTreeInsertFirst()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;
	int* num = NULL;
	BSTreeItr ret = NULL;

	tree = BSTreeCreate(Less);
	
	num = malloc(sizeof(int));
	*num = 16;
	
	ret = BSTreeInsert(tree, (void*)num);
	if (NULL != ret)
	{
		res = PASSED;
	}
	
	BSTreeDestroy(tree, Destroyer);

	PrintTestResult(res, "TestTreeInsertFirst");
}

/*
void TestTreeInsert()
{
	TestResult res = FAILED;
	BSTree* tree = NULL;

	tree = TreeCreate();
	if (NULL != tree)
	{
		TreeInsert(tree, 123);
		res = PASSED;
		TreeDestroy(tree);
	}	
	PrintTestResult(res, "TestListPushTail");
}
*/
int main()
{	
	TestCreate();
	TestCreateNullLessFunc();
	TestDestroyNullDestroyer();
	TestDoubleDestroy();
	TestTreeInsertFirst();
	/*
	TestTreeInsert();
	*/
	return 0;
}
