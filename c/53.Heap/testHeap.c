#include "Vector.h"
#include "Heap.h"

#include "mu_test.h"

#include <stdio.h>
#include <stdlib.h>

int Less(const void* _left, const void* _right)
{
	return (*(int*)_left < *(int*)_right) ? 1 : 0;
}

void Destroyer(void* _data)
{
	free(_data);
}


UNIT(TestExtract)
	Vector* vec = NULL;
	Heap* heap = NULL;
	int* num = NULL;
	void* ret = NULL;

	vec = VectorCreate(32, 16);
	heap = HeapBuild(vec, Less);

	num = malloc(sizeof(int));
	*num = 1;
	
	HeapInsert(heap, (void*)num);

	ret = HeapExtract(heap);
	ASSERT_THAT(1 == *(int*)ret);

	HeapDestroy(&heap);
	VectorDestroy(&vec, Destroyer);
END_UNIT


TEST_SUITE(framework test)
	TEST(TestExtract)
END_SUITE




