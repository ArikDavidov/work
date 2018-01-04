#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "HashMap.h"


#define SIZE 4


/*#define NDEBUG*/ 

size_t HashOne(int* key)
{
	return ((size_t) *key);
}

int equal(int* a, int* b)
{
	return((*a == *b) ? 1 : 0);
}

int PrintInt(int* _elem, void* _context)
{
	printf(" %d ", *(int*)_elem);
	return 1;
}

int DoNothing(int* _elem, void* _context)
{
	return 1;
}

void DestroyInt(void* item)
{
	free(item);
}

void CreateTest()
{
	HashMap* hs;
	hs = HashMapCreate(SIZE, (HashFunction) HashOne, (EqualityFunction)equal );
	if(NULL != hs)
	{
		printf("\npass - create Phash\n");
	}
	else
	{
		printf("\nfail - create Phash\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	return;
}


void NullKeyInsertTest()
{
	HashMap* hs;
	MapResult res;
	int num;
	num = 1;
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	res = HashMapInsert(hs, NULL, (void*)&num);
	
	if(MAP_KEY_NULL_ERROR == res)
	{
		printf("\npass - null key insert Phash\n");
	}
	else
	{
		printf("\nfail - null key insrt Phash\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	return;
}

void NullHashInsertTest()
{
	MapResult res;
	int num;
	int key;
	key = 1;
	num = 1;
	res = HashMapInsert(NULL, (void*)&key, (void*)&num);
	
	if(MAP_UNINITIALIZED_ERROR == res)
	{
		printf("\npass - null hash insert Phash\n");
	}
	else
	{
		printf("\nfail - null hash insrt Phash\n");
	}
	return;
}

void InsertTest()
{
	HashMap* hs;
	MapResult res;
	int num;
	int key;
	key = 1;
	num = 1;
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	res = HashMapInsert(hs, (void*)&key, (void*)&num);
	
	if(MAP_SUCCESS == res)
	{
		printf("\npass - insert Phash\n");
	}
	else
	{
		printf("\nfail - insrt Phash\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	return;
}

void DoubleInsertTest()
{
	HashMap* hs;
	MapResult firstRes;
	MapResult secRes;
	int num;
	int key;
	int doublenum;
	int doublekey;
	key = 1;
	num = 1;
	doublenum = 1;
	doublekey = 1;
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	firstRes = HashMapInsert(hs, (void*)&key, (void*)&num);
	secRes = HashMapInsert(hs, (void*)&doublekey, (void*)&doublenum);
	
	if(MAP_SUCCESS == firstRes && MAP_KEY_DUPLICATE_ERROR == secRes)
	{
		printf("\npass - double key insert Phash\n");
	}
	else
	{
		printf("\nfail - double key insrt Phash\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	return;
}


void TenInsertTest()
{
	HashMap* hs;
	int counte = 0;
	int i;
	MapResult* res;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	res = malloc(sizeof(MapResult) * SIZE);
	
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		res[i] = HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}	
	for(i = 0; i < SIZE; ++i)
	{
		if(MAP_SUCCESS == res[i])
		{
			continue;
		}
		++counte;
	}	
	if(0 == counte)
	{
		printf("\npass - SIZE insert in SIZE lists Phash\n");
	}
	else
	{
		printf("\nfail - SIZE insert in SIZE lists Phash\n");
	}
	free(num);
	free(res);
	free(key);
	HashMapDestroy(&hs, NULL, NULL);
	return;
}

void TenInsertInFiveListsTest()
{
	HashMap* hs;
	int i;
	int counter = 0;
	MapResult* res;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	res = malloc(sizeof(MapResult) * SIZE);
	
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		res[i] = HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}	
	for(i = 0; i < SIZE; ++i)
	{
		if(MAP_SUCCESS == res[i])
		{
			continue;
		}
		++counter;
	}	
	if(0 == counter)
	{
		printf("\npass - SIZE item in SIZE/2 lists insert Phash\n");
	}
	else
	{
		printf("\nfail - SIZE item in SIZE/2 lists insrt Phash\n");
	}
	free(num);
	free(res);
	free(key);
	HashMapDestroy(&hs, NULL, NULL);
	return;
}


/**********************************/

void HashFindWhanOneItemInLIstFoundTest()
{
	HashMap* hs;
	int numsearch = SIZE-2;
	int* search;
	MapResult res;
	int i;
	int ret;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	search = &numsearch;
	
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}	

	res = HashMapFind(hs, (void*)search, (void**)&ret);

	if(MAP_SUCCESS == res && SIZE-2 == ret)
	{
		printf("\npass - Find Whan Item In LIst Found\n");
	}
	else
	{
		printf("\nfail - Find Whan Item In LIst Found\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);

	return;
}

void HashFindWhantwoItemInLIstFoundTest()
{
	HashMap* hs;
	MapResult res;
	int i;
	int ret;
	int* search;
	int numsearch = SIZE-2;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	search = &numsearch;
	
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}	

	res = HashMapFind(hs, (void*)search, (void**)&ret);

	if(MAP_SUCCESS == res && SIZE-2 == ret)
	{
		printf("\npass - Find Whan two Item In each LIst Found\n");
	}
	else
	{
		printf("\nfail - Find Whan two Item In each LIst Found\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(key);
	free(num);

	return;
}

void HashFindWhanNotFoundTest()
{
	HashMap* hs;
	MapResult res;
	int i;
	int ret;
	int* search;
	int numsearch = SIZE+2;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	search = &numsearch;
	
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}	

	res = HashMapFind(hs, (void*)search, (void**)&ret);

	if(MAP_KEY_NOT_FOUND_ERROR == res)
	{
		printf("\npass - Find Whan not Found\n");
	}
	else
	{
		printf("\nfail - Find Whan not Found\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}

void HashFindNullMapTest()
{
	MapResult res;
	int ret;
	int* search;
	int numsearch = SIZE;	 	
	search = &numsearch;

	res = HashMapFind(NULL, (void*)search, (void**)&ret);

	if(MAP_UNINITIALIZED_ERROR == res)
	{
		printf("\npass - Find null map\n");
	}
	else
	{
		printf("\nfail - Find null map\n");
	}
	return;
}
/*
void HashSizeOneItemInListTest()
{
	HashMap* hs;
	int i;
	size_t ret;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	ret = HashMapSize(hs);
	
	if(SIZE == ret)
	{
		printf("\npass - Phash size one item in list\n");
	}
	else
	{
		printf("\nfail - Phash size one item in list\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(key);
	free(num);
	return;
}
void HashSizeTwoItemInListTest()
{
	HashMap* hs;
	int i;
	size_t ret;
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	ret = HashMapSize(hs);
	
	if(SIZE == ret)
	{
		printf("\npass - Phash size two item in each list\n");
	}
	else
	{
		printf("\nfail - Phash size two item in each list\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}
*/


void HashRemoveWhanFoundFirstInListTest()
{
	HashMap* hs;
	MapResult res;
	int i;
	int* search;
	int numsearch = SIZE-2;
	int retK;
	int retV;		 
	int* num;
	int* key;
	search = &numsearch;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	res = HashMapRemove(hs, (void*)search, (void**)&retK, (void**)&retV);	
	
	if(MAP_SUCCESS == res && SIZE-2 == retK && SIZE-2 == retV)
	{
		printf("\npass - PHash Remove whan found first in list\n");
	}
	else
	{
		printf("\nfail - PHash Remove whan found first in list\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}

void HashRemoveWhanFoundSecInListTest()
{
	HashMap* hs;
	MapResult res;
	int i;
	int* search;
	int numsearch = SIZE-2;
	int retK;
	int retV;		 
	int* num;
	int* key;
	search = &numsearch;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	res = HashMapRemove(hs, (void*)search, (void**)&retK, (void**)&retV);	
	
	if(MAP_SUCCESS == res && SIZE-2 == retK && SIZE-2 == retV)
	{
		printf("\npass - PHash Remove whan found second in list\n");
	}
	else
	{
		printf("\nfail - PHash Remove whan found second in list\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}

void HashRemoveTwiceTest()
{
	HashMap* hs;
	MapResult firstRes;
	MapResult secRes;
	int i;
	int* search;
	int numsearch = SIZE-2;
	int retK;
	int retV;		 
	int* num;
	int* key;
	search = &numsearch;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	firstRes = HashMapRemove(hs, (void*)search, (void**)&retK, (void**)&retV);	
	secRes = HashMapRemove(hs, (void*)search, (void**)&retK, (void**)&retV);
	
	if(MAP_SUCCESS == firstRes && MAP_KEY_NOT_FOUND_ERROR == secRes)
	{
		printf("\npass - PHash Remove twice\n");
	}
	else
	{
		printf("\nfail - PHash Remove twice\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}


void HashRemoveWhanNotFoundTest()
{
	HashMap* hs;
	MapResult res;
	int i;
	int* search;
	int numsearch = SIZE+2;
	int retK;
	int retV;		 
	int* num;
	int* key;
	search = &numsearch;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
		
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	res = HashMapRemove(hs, (void*)search, (void**)&retK, (void**)&retV);	
	
	if(MAP_KEY_NOT_FOUND_ERROR == res)
	{
		printf("\npass -PHash Remove whan not found\n");
	}
	else
	{
		printf("\nfail - PHash Remove whan not found\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}
/*
void HashForEachOneInListTest()
{
	HashMap* hs;
	int i;
	size_t numOfAction;		
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);

	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	numOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	
	if(SIZE == numOfAction)
	{
		printf("\npass - PHash for each One item In each List\n");
	}
	else
	{
		printf("\nfail - PHash for each One In each List\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}
void HashForEachtwoInListTest()
{
	HashMap* hs;
	int i;
	size_t numOfAction;		
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE/2, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
		
	numOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	
	if(SIZE== numOfAction)
	{
		printf("\npass - PHash for each two item In each List\n");
	}
	else
	{
		printf("\nfail - PHash for each two item In each List\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(key);
	free(num);
	return;
}

void RehashToSmallerTest()
{
	HashMap* hs;
	MapResult check;
	int i;
	size_t firstNumOfAction;
	size_t secNumOfAction;		
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
	firstNumOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	check = HashMapRehash(hs, SIZE/2);
	secNumOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	
	if(MAP_SUCCESS == check && SIZE == firstNumOfAction && SIZE == secNumOfAction)
	{
		printf("\npass - PHash Rehash to smaller\n");
	}
	else
	{
		printf("\nfail - PHash for Rehash to smaller\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(key);
	free(num);
	return;
}

void RehashToLargerTest()
{
	HashMap* hs;
	MapResult check;
	int i;
	size_t firstNumOfAction;
	size_t secNumOfAction;		
	int* num;
	int* key;
	
	hs = HashMapCreate(SIZE/4, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int) * SIZE);
	num = malloc(sizeof(int) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		num[i] = i;
		key[i] = i;
		HashMapInsert(hs, (void*)&key[i], (void*)&num[i]);
	}
	firstNumOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	check = HashMapRehash(hs, SIZE/2);
	secNumOfAction = HashMapForEach(hs, (KeyValueActionFunction)DoNothing, NULL);
	
	if(MAP_SUCCESS == check && SIZE == firstNumOfAction && SIZE == secNumOfAction)
	{
		printf("\npass - PHash Rehash to larger\n");
	}
	else
	{
		printf("\nfail - PHash for Rehash to larger\n");
	}
	HashMapDestroy(&hs, NULL, NULL);
	free(num);
	free(key);
	return;
}
*/

void DestroyTest()
{
	HashMap* hs;
	int i;
	int** num;
	int** key;
	
	hs = HashMapCreate(SIZE, (HashFunction)HashOne, (EqualityFunction)equal);
	key = malloc(sizeof(int*) * SIZE);
	num = malloc(sizeof(int*) * SIZE);
	for(i = 0; i < SIZE; ++i)
	{
		key[i] = malloc(sizeof(int));
		num[i] = malloc(sizeof(int));

		*num[i] = i;
		*key[i] = i;
		HashMapInsert(hs, (void*)key[i], (void*)num[i]);
	}	
	HashMapDestroy(&hs, DestroyInt, DestroyInt);
	free(key);
	free(num);
	return;
}


 

int main()
{
	int size = SIZE;
	printf("\n\t\tSIZE = %d\n\n", size);
	TenInsertTest();
	CreateTest();
	NullKeyInsertTest();
	NullHashInsertTest();
	TenInsertInFiveListsTest();
	HashFindWhanOneItemInLIstFoundTest();
	HashFindWhantwoItemInLIstFoundTest();
	DoubleInsertTest();
	HashFindWhanNotFoundTest();
	HashFindNullMapTest();
	InsertTest();
	HashRemoveWhanFoundFirstInListTest();
	HashRemoveWhanFoundSecInListTest();
	/*RehashToSmallerTest();
	HashForEachtwoInListTest();
	HashForEachOneInListTest();
	HashSizeOneItemInListTest();
	RehashToLargerTest();*/
	HashRemoveTwiceTest();
	DestroyTest();
	HashRemoveWhanNotFoundTest();
	/*HashSizeTwoItemInListTest();*/

	printf("\n\n");
	return 0;
}








 
