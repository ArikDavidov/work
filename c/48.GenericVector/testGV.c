#include "Vector.h"
#include "mu_test.h"

#include <stdio.h>
#include <stdlib.h>


void ElementDestroy(void* _item)
{
	if (NULL != _item)
	{
		free(_item);
	}
}

UNIT(TestVectorCreate)
	Vector*	vec = NULL;
	
	vec = VectorCreate(32, 16);
	ASSERT_THAT(vec);
	VectorDestroy(&vec, ElementDestroy);
END_UNIT

UNIT(TestVectorAppendAndGet)
	Vector*	vec = NULL;
	int* item;
	int* ret;
	
	vec = VectorCreate(32, 16);
	item = malloc(sizeof(int));
	*item = 5;
	VectorAppend(vec, (void*)item);
	VectorGet(vec, 0, (void**)&ret);
	ASSERT_THAT(5 == *ret);
	VectorDestroy(&vec, ElementDestroy);
END_UNIT

UNIT(TestVectorGrow)
	Vector*	vec = NULL;
	int* item;
	int* ret;
	size_t i;
	
	vec = VectorCreate(2, 2);
	for (i = 0; i < 6; ++i)
	{
		item = malloc(sizeof(int));
		*item = (int)i;
		VectorAppend(vec, (void*)item);
	}
	for (i = 0; i < 6; ++i)
	{
		VectorGet(vec, i, (void**)&ret);
		ASSERT_THAT(*ret == (int)i);
	}
	VectorDestroy(&vec, ElementDestroy);
END_UNIT

UNIT(TestVectorRemove)
	Vector*	vec = NULL;
	int* item = NULL;
	int* ret = NULL;
	
	vec = VectorCreate(32, 16);
	item = malloc(sizeof(int));
	*item = 5;
	VectorAppend(vec, (void*)item);
	VectorRemove(vec, (void**)&ret);
	ASSERT_THAT(item == ret);
	VectorDestroy(&vec, ElementDestroy);
	free(item);
END_UNIT


TEST_SUITE(framework test)
	TEST(TestVectorCreate)
	TEST(TestVectorAppendAndGet)
	TEST(TestVectorGrow)
	TEST(TestVectorRemove)
END_SUITE








