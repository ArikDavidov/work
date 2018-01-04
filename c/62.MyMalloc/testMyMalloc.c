#include "MyMalloc.h"
#include "mu_test.h"

#include <stdio.h>
#include <assert.h>


UNIT(TestMyMallocCreate)
	MyMallocCreate(16, 4);
END_UNIT

UNIT(TestMyMalloc)
	void* myBuf = NULL;
	void* chunk = NULL;

	myBuf = MyMallocCreate(16, 8);
	chunk = MyMalloc(myBuf);
	assert(chunk);
	ASSERT_THAT(1);
END_UNIT


TEST_SUITE(framework test)
	TEST(TestMyMallocCreate)
END_SUITE
