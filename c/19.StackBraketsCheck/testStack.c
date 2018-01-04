#include <stdio.h>
#include "stack.h"
#define DEFAULT_SIZE 4
#define DEFAULT_BLOCK_SIZE 2


void TestCreate();
void TestCreateZeroSize();
void TestCreateZeroBlockSize();
void TestCreateZeroSizeAndBlockSize();

void TestPush();
void TestPushWithRealloc();
void TestPushNULL();
void TestPushWithZeroBlockSize();
void TestPushWithZeroSize();

void TestIsEmptyWhenEmpty();
void TestIsEmptyWhenNotEmpty();
void TestIsEmptyStackNULL();

void TestTop();
void TestTopStackEmpty();
void TestTopStackNULL();

void TestPop();
void TestPopTooMuch();
void TestPopStackNULL();
void TestPopItemPtrNULL();
void TestPopShrink();

void TestPopAndPushSeveralTimes();

int main()
{
	TestCreate();
	TestCreateZeroSize();
	TestCreateZeroBlockSize();
	TestCreateZeroSizeAndBlockSize();

	TestPush();
	TestPushWithRealloc();
	TestPushNULL();
	TestPushWithZeroBlockSize();
	TestPushWithZeroSize();

	TestIsEmptyWhenEmpty();
	TestIsEmptyWhenNotEmpty();
	TestIsEmptyStackNULL();

	TestTop();
	TestTopStackEmpty();
	TestTopStackNULL();

	TestPop();
	TestPopTooMuch();
	TestPopStackNULL();
	TestPopItemPtrNULL();
	TestPopShrink();

	TestPopAndPushSeveralTimes();

	return 0;
}

void TestCreate()
{
	Stack* res = NULL;

	res = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != res)
	{	
		printf("PASSED: TestCreate\n");
		StackDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreate\n");
	}	
}

void TestCreateZeroSize()
{
	Stack* res = NULL;

	res = StackCreate(0, DEFAULT_BLOCK_SIZE);
	if (NULL != res)
	{	
		printf("PASSED: TestCreateZeroSize\n");
		StackDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroSize\n");
	}	
}

void TestCreateZeroBlockSize()
{
	Stack* res = NULL;

	res = StackCreate(DEFAULT_SIZE, 0);
	if (NULL != res)
	{	
		printf("PASSED: TestCreateZeroBlockSize\n");
		StackDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroBlockSize\n");
	}	
}

void TestCreateZeroSizeAndBlockSize()
{
	Stack* res = NULL;

	res = StackCreate(0, 0);
	if (NULL == res)
	{	
		printf("PASSED: TestCreateZeroSizeAndBlockSize\n");
		StackDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroSizeAndBlockSize\n");
		StackDestroy(res);
	}	
}

void TestPush()
{
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		res = StackPush(stack, 42);
		if(ERR_OK == res)
		{
			printf("PASSED: TestPush\n");
		}
		else
		{
			printf("FAILED: TestPush\n");
		}
		StackDestroy(stack);
	}
}

void TestPushWithRealloc()
{
	int i;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		for (i = 0; i < 5; ++i)
		{
			res = StackPush(stack, i);
			if(ERR_OK != res)
			{
				printf("FAILED: TestPushWithRealloc\n");
				break;
			}	
		}
		if(ERR_OK == res)
		{
			printf("PASSED: TestPushWithRealloc\n");
		}

		StackDestroy(stack);
	}
}


void TestPushNULL()
{
	ADTDefs res;

	res = StackPush(NULL, 42);
	if(ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestPushNULL\n");
	}
	else
	{
		printf("FAILED: TestPushNULL\n");
	}
}

void TestPushWithZeroBlockSize()
{
	int i;
	Stack* stack = NULL;
	ADTDefs res;

	stack = StackCreate(DEFAULT_SIZE, 0);
	if (NULL != stack)
	{
		for (i = 0; i < 5; ++i)
		{
			res = StackPush(stack, i);
			if(ERR_OK != res)
			{
				printf("PASSED: TestPushWithZeroBlockSize\n");
				break;
			}
		}
		if(ERR_OK == res)
		{
			printf("FAILED: TestPushWithZeroBlockSize\n");
		}
		StackDestroy(stack);
	}
}

void TestPushWithZeroSize()
{
	Stack* stack = NULL;
	ADTDefs res;

	stack = StackCreate(0, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		res = StackPush(NULL, 42);
		if(ERR_OK == res)
		{
			printf("PASSED: TestPushWithZeroSize\n");
		}
		else
		{
			printf("FAILED: TestPushWithZeroSize\n");
		}

		StackDestroy(stack);
	}
}

void TestIsEmptyWhenEmpty()
{
	Stack* stack = NULL;
	int	res;

	stack = StackCreate(4, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		res = StackIsEmpty(stack);
		if (1 == res)
		{
			printf("PASSED: TestIsEmpty\n");
		}
		else
		{
			printf("FAILED: TestIsEmpty\n");
		}
		StackDestroy(stack);	
	}
}

void TestIsEmptyWhenNotEmpty()
{
	Stack* stack = NULL;
	int	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		StackPush(stack, 42);
		res = StackIsEmpty(stack);
		if (0 == res)
		{
			printf("PASSED: TestIsEmpty\n");
		}
		else
		{
			printf("FAILED: TestIsEmpty\n");
		}
		StackDestroy(stack);	
	}
}

void TestIsEmptyStackNULL()
{
	int	res;

	res = StackIsEmpty(NULL);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestIsEmptyStackNULL\n");
	}
	else
	{
		printf("FAILED: TestIsEmptyStackNULL\n");
	}	
}

void TestTop()
{
	int item;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		StackPush(stack, 42);
		res = StackTop(stack, &item);
		if (ERR_OK == res)
		{
			printf("PASSED: TestTop\n");
		}
		else
		{
			printf("FAILED: TestTop\n");
		}
		StackDestroy(stack);	
	}
}

void TestTopStackEmpty()
{
	int item;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		res = StackTop(stack, &item);
		if (ERR_OVERFLOW == res)
		{
			printf("PASSED: TestTopStackEmpty\n");
		}
		else
		{
			printf("FAILED: TestTopStackEmpty\n");
		}
		StackDestroy(stack);	
	}
}

void TestTopStackNULL()
{
	int item;
	ADTDefs	res;

	res = StackTop(NULL, &item);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestPopStackNULL\n");
	}
	else
	{
		printf("FAILED: TestPopStackNULL\n");
	}
}

void TestPop()
{
	int item;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		StackPush(stack, 42);
		res = StackPop(stack, &item);
		if (ERR_OK == res)
		{
			printf("PASSED: TestPop\n");
		}
		else
		{
			printf("FAILED: TestPop\n");
		}
		StackDestroy(stack);	
	}
}

void TestPopTooMuch()
{
	int item;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		StackPush(stack, 42);
		res = StackPop(stack, &item);
		res = StackPop(stack, &item);
		if (ERR_UNDERFLOW == res)
		{
			printf("PASSED: TestPopTooMuch\n");
		}
		else
		{
			printf("FAILED: TestPopTooMuch\n");
		}
		StackDestroy(stack);	
	}
}

void TestPopStackNULL()
{
	int item;
	ADTDefs	res;

	res = StackPop(NULL, &item);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestPopStackNULL\n");
	}
	else
	{
		printf("FAILED: TestPopStackNULL\n");
	}
}

void TestPopItemPtrNULL()
{
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		res = StackPop(stack, NULL);
		if (ERR_OK == res)
		{
			printf("PASSED: TestPopItemPtrNULL\n");
		}
	
		else
		{
			printf("FAILED: TestPopItemPtrNULL\n");
		}
		StackDestroy(stack);
	}
}

void TestPopShrink()
{
	int i, item;
	Stack* stack = NULL;
	ADTDefs	res;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		for (i = 0; i < 9; ++i)
		{
			StackPush(stack, i);
		}
		for (i = 9; i < 5; --i)
		{
			res = StackPop(stack, &item);
			if(ERR_OK != res)
			{				
				printf("FAILED: TestPopShrink\n");
				break;				
			}	
		}
		if(ERR_OK == res)
		{
			printf("PASSED: TestPopShrink\n");
		}
		StackDestroy(stack);
	}
}

void TestPopAndPushSeveralTimes()
{
	int i, item;
	Stack* stack = NULL;

	stack = StackCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != stack)
	{
		for (i = 0; i < 8; ++i)
		{
			StackPush(stack, i);
			StackPush(stack, i);
			StackPop(stack, &item);
		}
		for (i = 0; i < 4; ++i)
		{
			StackPush(stack, i);
			StackPop(stack, &item);
		}
		for (i = 0; i < 8; ++i)
		{
			StackPop(stack, &item);
			if(7 - i != item)
			{
				printf("FAILED: TestPopAndPushSeveralTimes\n");
				StackDestroy(stack);
				return;
			}
		}		
		printf("PASSED: TestPopAndPushSeveralTimes\n");
		StackDestroy(stack);
	}
}


