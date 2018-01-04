#include "MemPool_t.h"
#include "MemPage_t.h"
#include "MemPool_t.h"
#include "mu_test.h"

#include <stdio.h>
#include <string.h>

#include <iostream>
using namespace std;


UNIT(PageGetAndSetPosition)
	MemPage_t memPage;
	ASSERT_THAT(0 == memPage.GetPosition());
	int input = 123456;
	memPage.Write(&input, sizeof(int), 0);
	try {
		memPage.SetPosition(60);
	} catch (const char* ex){cout << "Handleing...";}
	ASSERT_THAT(2 == memPage.GetPosition());
END_UNIT
/*
UNIT(PageReadAndWriteCurrentPosition)
	MemPool_t& memPool = MemManagerCreate(128);
	memPool.SetPosition(8);
	int input = 123456;
	memPool.Write(&input, sizeof(int));
	int output = 0;
	memPool.Read(&output, sizeof(int));
	ASSERT_THAT(123456 == output);
    MemManagerDestroy(memPool);
END_UNIT
UNIT(PageReadAndWriteUserProvidedPosition)
	MemPool_t& memPool = MemManagerCreate(128);
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
	int output = 0;
	memPool.Read(&output, sizeof(int), 0);
	ASSERT_THAT(123456 == output);
    MemManagerDestroy(memPool);
END_UNIT

UNIT(PageActualSize)
	MemPool_t& memPool = MemManagerCreate(128);
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
	ASSERT_THAT(4 == memPool.GetActualSize());
    MemManagerDestroy(memPool);
END_UNIT

UNIT(PageIsEmptyIsFull)
	MemPool_t& memPool = MemManagerCreate(4);
	ASSERT_THAT(1 == memPool.IsEmpty());
	ASSERT_THAT(0 == memPool.IsFull());
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
	ASSERT_THAT(0 == memPool.IsEmpty());
	ASSERT_THAT(1 == memPool.IsFull());
    MemManagerDestroy(memPool);
END_UNIT

UNIT(PoolGetAndSetPosition)
	MemPool_t& memPool = MemManagerCreate(2048);
	cout << memPool.GetPosition() << endl;
	ASSERT_THAT(0 == memPool.GetPosition());
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
	memPool.SetPosition(2);
	ASSERT_THAT(2 == memPool.GetPosition());
    MemManagerDestroy(memPool);
END_UNIT
*/



/*
UNIT(PageCapcity)
	MemPool_t& memPool = MemManagerCreate(3);
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
    MemManagerDestroy(memPool);
END_UNIT

UNIT(PoolGetAndSetPosition)
	MemPool_t& memPool = MemManagerCreate(2048);
	ASSERT_THAT(0 == memPool.GetPosition());
	int input = 123456;
	memPool.Write(&input, sizeof(int), 0);
	memPool.SetPosition(2);
	ASSERT_THAT(2 == memPool.GetPosition());
    MemManagerDestroy(memPool);
END_UNIT

UNIT(SetAndGet)
	String_t string;
	string.SetString("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetBuf(), "Zero Bug Approach"));
END_UNIT

UNIT(CTORFromCharPtr)
	String_t string("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetBuf(), "Zero Bug Approach"));
END_UNIT
*/

TEST_SUITE(framework test)
	TEST(PageGetAndSetPosition)
	/*
	TEST(PageReadAndWriteUserProvidedPosition)
	TEST(PageActualSize)
	TEST(PageIsEmptyIsFull)
	TEST(PoolGetAndSetPosition)
	TEST(PageCapcity)
	TEST(Length)
	TEST(Upper)
	TEST(Lower)
	TEST(Contains)
	TEST(PrependFromCharPtr)
	TEST(PrependFromString)
	TEST(SqareBracketsOperator)
	TEST(FindFirst)
	TEST(FindLast)
	*/
END_SUITE











