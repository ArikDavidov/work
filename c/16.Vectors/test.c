#include <stdio.h>
#include "ADTErr.h"
#include "Vector.h"


void TestVectorCreate();
void TestVectorAdd();
void TestRealloc();
void TestVectorGet();



int main()
{
	TestVectorCreate();
	TestVectorAdd();
	TestRealloc();
	TestVectorDestroy();
	TestVectorGet();

	return 0;
}

void TestVectorCreate()
{
	Vector*	res = NULL;
	res = VectorCreate(4, 2);
	if (NULL != res)
	{	
		printf("PASSED: TestVectorCreate\n");
		VectorDestroy(res);
	}
	else
	{
		printf("FAILED: TestVectorCreate\n");
	}	
}

void TestVectorAdd()
{
	Vector*	vector = NULL;
	ADTErr	res;

	vector = VectorCreate(4, 2);
	res = VectorAdd(vector, 42);
	if(ERR_OK == res)
	{
		printf("PASSED: TestVectorAdd\n");
	}
	else
	{
		printf("FAILED: TestVectorAdd\n");
	}
	VectorDestroy(vector);
}

void TestVectorGet()
{
	Vector*	vector = NULL;
	ADTErr	res;

	vector = VectorCreate(4, 2);
	VectorAdd(vector, 42);
	res = VectorGet(vector);
	if(ERR_OK == res)
	{
		printf("PASSED: TestVectorAdd\n");
	}
	else
	{
		printf("FAILED: TestVectorAdd\n");
	}
	VectorDestroy(vector);
}


void TestRealloc()
{
	Vector*	vector = NULL;
	ADTErr	res;
	int i;

	vector = VectorCreate(4, 2);	

	for (i = 0; i < 5; ++i)
	{
		res = VectorAdd(vector, i);
		if(ERR_OK != res)
		{
			printf("FAILED: TestRealloc\n");
			break;
		}
	}
	
	if(_vector->m_size > _vector->m_originalSize)
	{
		printf("PASSED: TestRealloc\n");		
	}
}

void TestVectorGet()
{
	Vector*	vector = NULL;
	ADTErr	res;
	int i;

	_vector = VectorCreate(4, 2);
	res = VectorAdd(_vector, 42);
	VectorGet(vector);



	ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
}










