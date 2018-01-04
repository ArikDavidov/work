#include "List.h"
#include "ListFunctions.h"
#include "mu_test.h"

#include <stdio.h>
#include <stdlib.h>

int ElementDestroy(void* _element, void* _context)
{
	if (NULL == _element)
	{
		return -1;
	}	
	free(_element);
	return 0;
}

UNIT(TestCreate)
	ASSERT_THAT(NULL != ListCreate());
END_UNIT

UNIT(TestDoubleDestroy)
	List* list = NULL;
	list = ListCreate();
	ListDestroy(&list, ElementDestroy);
	ListDestroy(&list, ElementDestroy);	
	/* If no segmentation fault occurred */
	ASSERT_THAT(1);
END_UNIT

UNIT(TestListPushAndPopHead)
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;	
	num = malloc(sizeof(int));
	*num = 765;	
	list = ListCreate();
	ListPushHead(list, num);
	ListPopHead(list, (void**)&ret);
	ASSERT_THAT(765 == *ret);
	ListDestroy(&list, ElementDestroy);	
END_UNIT

UNIT(TestListPushAndPopTail)
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;	
	num = malloc(sizeof(int));
	*num = 345;	
	list = ListCreate();
	ListPushTail(list, num);	
	ListPopTail(list, (void**)&ret);
	ASSERT_THAT(345 == *ret);
	ListDestroy(&list, ElementDestroy);
END_UNIT

UNIT(TestListPushesAndPops)
	int i;
	List* list = NULL;
	int* num = NULL;
	int* ret = NULL;	
	list = ListCreate();
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = i;
		ListPushHead(list, num);
	}	
	for (i = 0; i < 8; ++i)
	{
		ListPopTail(list, (void**)&ret);
		ASSERT_THAT(i == *ret);
	}	
	ListDestroy(&list, ElementDestroy);
END_UNIT

UNIT(TestListCountItems)
	int i;
	List* list = NULL;
	int* num = NULL;	
	list = ListCreate();
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = i;
		ListPushHead(list, num);
	}	
	ASSERT_THAT(8 == ListCountItems(list));
	ListDestroy(&list, ElementDestroy);
END_UNIT

UNIT(TestListIsEmptyWhenEmpty)
	List* list = NULL;
	list = ListCreate();
	ASSERT_THAT(ListIsEmpty(list));
	ListDestroy(&list, ElementDestroy);
END_UNIT

UNIT(TestListItrBeginNullInput)
	ListItr itr;
	itr = ListItrBegin(NULL);
	ASSERT_THAT(NULL == itr);
END_UNIT

UNIT(TestListItrBeginDestroyedList)
	List* list;
	ListItr itr;
	list = ListCreate();
	ListDestroy(&list, ElementDestroy);
	itr = ListItrBegin(list);
	ASSERT_THAT(NULL == itr);
END_UNIT

UNIT(TestListItrEndNullInput)
	ListItr itr;
	itr = ListItrEnd(NULL);
	ASSERT_THAT(NULL == itr);
END_UNIT

UNIT(TestListItrEndDestroyedList)
	List* list;
	ListItr itr;
	list = ListCreate();
	ListDestroy(&list, ElementDestroy);
	itr = ListItrEnd(list);	
	ASSERT_THAT(NULL == itr);
END_UNIT

UNIT(TestListItrEqualsListEmpty)
	List* list;
	ListItr a = NULL;
	ListItr b = NULL;
	list = ListCreate();
	a = ListItrBegin(list);
	b = ListItrEnd(list);
	ASSERT_THAT(1 == ListItrEquals(a, b));
	ListDestroy(&list, ElementDestroy);
END_UNIT


UNIT(TestListItrEqualsTrue)
	List* list;
	size_t i;
	int* num = NULL;
	ListItr a = NULL;
	ListItr b = NULL;	
	list = ListCreate();
	for (i = 0; i < 8; ++i)
	{
		num = malloc(sizeof(int));
		*num = (int)i;
		ListPushTail(list, num);
	}
	a  = ListItrBegin(list);
	for (i = 0; i < 4; ++i)
	{
		a = ListItrNext(a);
	}
	b  = ListItrEnd(list);
	for (i = 0; i < 4; ++i)
	{
		b = ListItrPrev(b);
	}
	ASSERT_THAT(1 == ListItrEquals(a, b));
END_UNIT

TEST_SUITE(framework test)
	TEST(TestCreate)
	TEST(TestDoubleDestroy)
	TEST(TestListPushAndPopHead)
	TEST(TestListPushAndPopTail)
	TEST(TestListPushesAndPops)
	TEST(TestListCountItems)
	TEST(TestListIsEmptyWhenEmpty)
	
	TEST(TestListItrBeginNullInput)
	TEST(TestListItrBeginDestroyedList)
	TEST(TestListItrEndNullInput)
	TEST(TestListItrEndDestroyedList)
	TEST(TestListItrEqualsListEmpty)
	TEST(TestListItrEqualsTrue)
END_SUITE


