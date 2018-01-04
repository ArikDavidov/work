#include <stdio.h>
#include "Queue.h"
#define DEFAULT_SIZE 8

void TestCreate();
void TestCreateZeroSize();

void TestInsert();
void TestInsertNULL();

void TestIsEmptyAfterCreate();
void TestIsEmptyWhenNotEmpty();
void TestIsEmptyQueueNULL();

void TestRemove();
void TestRemoveTooMuch();
void TestRemoveQueueNULL();
void TestRemoveItemPtrNULL();

void TestRemoveAndInsertSeveralTimes();

int main()
{
	TestCreate();
	TestCreateZeroSize();
/*
	TestInsert();
	TestInsertNULL();


	TestIsEmptyWhenEmpty();
	TestIsEmptyWhenNotEmpty();
	TestIsEmptyQueueNULL();

	TestTop();
	TestTopQueueEmpty();
	TestTopQueueNULL();

	TestRemove();
	TestRemoveTooMuch();
	TestRemoveQueueNULL();
	TestRemoveItemPtrNULL();
	
	TestRemoveAndInsertSeveralTimes();
*/
	return 0;
}

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
	Queue* queue = NULL;

	queue = QueueCreate(DEFAULT_SIZE);
	if (NULL != queue)
	{
		res = PASSED;
	}
	PrintTestResult(res, "TestCreate");
}

void TestCreateZeroSize()
{
	TestResult res = FAILED;
	Queue* queue = NULL;

	queue = QueueCreate(0);
	if (NULL == queue)
	{
		res = PASSED;
	}
	QueueDestroy(queue);
	PrintTestResult(res, "TestCreateZeroSize");
}
/*
void TestCreateZeroSize()
{
	Queue* res = NULL;

	res = QueueCreate(0, DEFAULT_BLOCK_SIZE);
	if (NULL != res)
	{	
		printf("PASSED: TestCreateZeroSize\n");
		QueueDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroSize\n");
	}	
}

void TestCreateZeroBlockSize()
{
	Queue* res = NULL;

	res = QueueCreate(DEFAULT_SIZE, 0);
	if (NULL != res)
	{	
		printf("PASSED: TestCreateZeroBlockSize\n");
		QueueDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroBlockSize\n");
	}	
}

void TestCreateZeroSizeAndBlockSize()
{
	Queue* res = NULL;

	res = QueueCreate(0, 0);
	if (NULL == res)
	{	
		printf("PASSED: TestCreateZeroSizeAndBlockSize\n");
		QueueDestroy(res);
	}
	else
	{
		printf("FAILED: TestCreateZeroSizeAndBlockSize\n");
		QueueDestroy(res);
	}	
}

void TestInsert()
{
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		res = QueueInsert(Queue, 42);
		if(ERR_OK == res)
		{
			printf("PASSED: TestInsert\n");
		}
		else
		{
			printf("FAILED: TestInsert\n");
		}
		QueueDestroy(Queue);
	}
}

void TestInsertWithRealloc()
{
	int i;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		for (i = 0; i < 5; ++i)
		{
			res = QueueInsert(Queue, i);
			if(ERR_OK != res)
			{
				printf("FAILED: TestInsertWithRealloc\n");
				break;
			}	
		}
		if(ERR_OK == res)
		{
			printf("PASSED: TestInsertWithRealloc\n");
		}

		QueueDestroy(Queue);
	}
}


void TestInsertNULL()
{
	ADTDefs res;

	res = QueueInsert(NULL, 42);
	if(ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestInsertNULL\n");
	}
	else
	{
		printf("FAILED: TestInsertNULL\n");
	}
}

void TestInsertWithZeroBlockSize()
{
	int i;
	Queue* Queue = NULL;
	ADTDefs res;

	Queue = QueueCreate(DEFAULT_SIZE, 0);
	if (NULL != Queue)
	{
		for (i = 0; i < 5; ++i)
		{
			res = QueueInsert(Queue, i);
			if(ERR_OK != res)
			{
				printf("PASSED: TestInsertWithZeroBlockSize\n");
				break;
			}
		}
		if(ERR_OK == res)
		{
			printf("FAILED: TestInsertWithZeroBlockSize\n");
		}
		QueueDestroy(Queue);
	}
}

void TestInsertWithZeroSize()
{
	Queue* Queue = NULL;
	ADTDefs res;

	Queue = QueueCreate(0, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		res = QueueInsert(NULL, 42);
		if(ERR_OK == res)
		{
			printf("PASSED: TestInsertWithZeroSize\n");
		}
		else
		{
			printf("FAILED: TestInsertWithZeroSize\n");
		}

		QueueDestroy(Queue);
	}
}

void TestIsEmptyWhenEmpty()
{
	Queue* Queue = NULL;
	int	res;

	Queue = QueueCreate(4, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		res = QueueIsEmpty(Queue);
		if (1 == res)
		{
			printf("PASSED: TestIsEmpty\n");
		}
		else
		{
			printf("FAILED: TestIsEmpty\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestIsEmptyWhenNotEmpty()
{
	Queue* Queue = NULL;
	int	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		QueueInsert(Queue, 42);
		res = QueueIsEmpty(Queue);
		if (0 == res)
		{
			printf("PASSED: TestIsEmpty\n");
		}
		else
		{
			printf("FAILED: TestIsEmpty\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestIsEmptyQueueNULL()
{
	int	res;

	res = QueueIsEmpty(NULL);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestIsEmptyQueueNULL\n");
	}
	else
	{
		printf("FAILED: TestIsEmptyQueueNULL\n");
	}	
}

void TestTop()
{
	int item;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		QueueInsert(Queue, 42);
		res = QueueTop(Queue, &item);
		if (ERR_OK == res)
		{
			printf("PASSED: TestTop\n");
		}
		else
		{
			printf("FAILED: TestTop\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestTopQueueEmpty()
{
	int item;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		res = QueueTop(Queue, &item);
		if (ERR_OVERFLOW == res)
		{
			printf("PASSED: TestTopQueueEmpty\n");
		}
		else
		{
			printf("FAILED: TestTopQueueEmpty\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestTopQueueNULL()
{
	int item;
	ADTDefs	res;

	res = QueueTop(NULL, &item);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestRemoveQueueNULL\n");
	}
	else
	{
		printf("FAILED: TestRemoveQueueNULL\n");
	}
}

void TestRemove()
{
	int item;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		QueueInsert(Queue, 42);
		res = QueueRemove(Queue, &item);
		if (ERR_OK == res)
		{
			printf("PASSED: TestRemove\n");
		}
		else
		{
			printf("FAILED: TestRemove\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestRemoveTooMuch()
{
	int item;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		QueueInsert(Queue, 42);
		res = QueueRemove(Queue, &item);
		res = QueueRemove(Queue, &item);
		if (ERR_UNDERFLOW == res)
		{
			printf("PASSED: TestRemoveTooMuch\n");
		}
		else
		{
			printf("FAILED: TestRemoveTooMuch\n");
		}
		QueueDestroy(Queue);	
	}
}

void TestRemoveQueueNULL()
{
	int item;
	ADTDefs	res;

	res = QueueRemove(NULL, &item);
	if (ERR_NOT_INITIALIZED == res)
	{
		printf("PASSED: TestRemoveQueueNULL\n");
	}
	else
	{
		printf("FAILED: TestRemoveQueueNULL\n");
	}
}

void TestRemoveItemPtrNULL()
{
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		res = QueueRemove(Queue, NULL);
		if (ERR_OK == res)
		{
			printf("PASSED: TestRemoveItemPtrNULL\n");
		}
	
		else
		{
			printf("FAILED: TestRemoveItemPtrNULL\n");
		}
		QueueDestroy(Queue);
	}
}

void TestRemoveShrink()
{
	int i, item;
	Queue* Queue = NULL;
	ADTDefs	res;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		for (i = 0; i < 9; ++i)
		{
			QueueInsert(Queue, i);
		}
		for (i = 9; i < 5; --i)
		{
			res = QueueRemove(Queue, &item);
			if(ERR_OK != res)
			{				
				printf("FAILED: TestRemoveShrink\n");
				break;				
			}	
		}
		if(ERR_OK == res)
		{
			printf("PASSED: TestRemoveShrink\n");
		}
		QueueDestroy(Queue);
	}
}

void TestRemoveAndInsertSeveralTimes()
{
	int i, item;
	Queue* Queue = NULL;

	Queue = QueueCreate(DEFAULT_SIZE, DEFAULT_BLOCK_SIZE);
	if (NULL != Queue)
	{
		for (i = 0; i < 8; ++i)
		{
			QueueInsert(Queue, i);
			QueueInsert(Queue, i);
			QueueRemove(Queue, &item);
		}
		for (i = 0; i < 4; ++i)
		{
			QueueInsert(Queue, i);
			QueueRemove(Queue, &item);
		}
		for (i = 0; i < 8; ++i)
		{
			QueueRemove(Queue, &item);
			if(7 - i != item)
			{
				printf("FAILED: TestRemoveAndInsertSeveralTimes\n");
				QueueDestroy(Queue);
				return;
			}
		}		
		printf("PASSED: TestRemoveAndInsertSeveralTimes\n");
		QueueDestroy(Queue);
	}
}

*/
