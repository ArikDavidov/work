#include "HashMap.h"
#include "List.h"
#include "ListFunctions.h"

#include <stdlib.h>
#include <math.h>	/* sqrt */

/* #define NDEBUG 1 */
#include <assert.h>

#define HASH_MAP_MAGIC		0xDEBACCCC
#define IS_A_HASH_MAP(M)	((M) && HASH_MAP_MAGIC == (M)->m_magic)
#define HASH_INDEX(M, K)	((M)->m_hashFunc(K) % (M)->m_capacity)

struct HashMap
{
	size_t m_magic;
    List** m_buckets;
	size_t m_capacity;
	HashFunction     m_hashFunc;
	EqualityFunction m_keysEqualFunc;
	#ifndef NDEBUG
	MapStats m_mapStatus;
	#endif /* NDEBUG */
};

typedef struct
{
	const void* m_key;
	const void* m_value;
} Pair;

typedef struct
{
	EqualityFunction m_equalityFunc;
	const void*      m_searchKey;
} PredicateFunctionContext;


static size_t IsPrime(size_t _num)
{ 
	size_t div;
	
	/* Assumes _num is odd number. */
	assert(_num % 2);
	
	for(div = 3; div <= sqrt(_num); div += 2)
	{
		if (0 == _num % div)
		{
			return 0;
		}
	}
	
	return 1;
}

static size_t CalculateActualCapacity(size_t _capacity)
{
	if (0 == _capacity % 2)
	{
		++_capacity;
	}
	
	while (!IsPrime(_capacity))
	{
		_capacity += 2;
	}
	
	return _capacity;
}

static List** CreateArrayOfBuckets(size_t _capacity)
{
	List** arr = NULL;
	size_t i;
	
	arr = malloc(_capacity * sizeof(void*));
	if(!arr)
	{
		return NULL;
	}
	
	for (i = 0; i < _capacity; ++i)
	{
		if (NULL == (arr[i] = ListCreate()))
		{
			goto CLEANUP;
		}
	}
	
	return arr;
	
	CLEANUP:
		for (--i; i < _capacity; --i)
		{
			ListDestroy(&arr[i], NULL);
		}
	
		free(arr);
	
		return NULL;
}

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* map = NULL;
	
	if (!_capacity || !_hashFunc || !_keysEqualFunc)
	{
		return NULL;
	}	

	map = malloc(sizeof(HashMap));
	if(!map)
	{
		return NULL;
	}
	
	map->m_capacity = CalculateActualCapacity(_capacity);
	
	map->m_buckets = CreateArrayOfBuckets(map->m_capacity);
	if (!map->m_buckets)
	{
		free(map);
		return NULL;
	}
	
	map->m_hashFunc = _hashFunc;
	map->m_keysEqualFunc = _keysEqualFunc;
	map->m_magic = HASH_MAP_MAGIC;
	
	return map;
}

static void BucketDestroy(List* _backet, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	Pair* pair = NULL;

	if (!_backet)
	{
		return;
	}

	while (LIST_LIST_IS_EMPTY != ListPopHead(_backet, (void**)&pair))
	{
		if (_keyDestroy)
		{
			_keyDestroy((void*)pair->m_key);
		}

		if (_valDestroy)
		{
			_valDestroy((void*)pair->m_value);
		}

		free(pair);
	}

	ListDestroy(&_backet, NULL);
}

static void DestroyAllBuckets(HashMap* _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t i, numOfLists;
	
	numOfLists = _map->m_capacity;
	
	for (i = 0; i < numOfLists; ++i)
	{
		BucketDestroy(_map->m_buckets[i], _keyDestroy, _valDestroy);
	}
	
	free(_map->m_buckets);
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{	
	if (!_map || !IS_A_HASH_MAP(*_map))
	{
		return;
	}
	
	DestroyAllBuckets(*_map, _keyDestroy, _valDestroy);	
	
	(*_map)->m_magic = 0;
	free(*_map);
	*_map = NULL;
}

static int HashMapPredicateFunc(void* _pair, void* _context)
{
	PredicateFunctionContext* context = NULL;
	Pair* pair = NULL;

	assert(_pair);
	assert(_context);

	context = (PredicateFunctionContext*)_context;
	pair = (Pair*)_pair;

	return context->m_equalityFunc(pair->m_key, context->m_searchKey);
}

static ListItr* IfItrExistAlready(List* _ls, void* _key, EqualityFunction _func)
{
    ListItr itr;
    ListItr itrEnd;
    Pair* elm;  

    itrEnd = ListItrEnd(_ls);
    itr = ListItrBegin(_ls);    

    while(itr != itrEnd)
    {
        elm = (Pair*)ListItrGet(itr);
        if(1 == ((int)_func(_key, elm->m_key)))
        {
            return itr; 
        }
        itr =ListItrNext(itr);
    }
    return NULL;
}

static ListItr FindKey(const HashMap* _map, const void* _searchKey)
{
	PredicateFunctionContext context;
	ListItr itr   = NULL;
	ListItr end   = NULL;
	List* bucket;

	assert(_map);
	assert(_searchKey);
	
	bucket = _map->m_buckets[HASH_INDEX(_map, _searchKey)];
	itr = ListItrBegin(bucket);
	end = ListItrEnd(bucket);

	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;
	
	/*itr = ListItrFindFirst(itr, end, HashMapPredicateFunc, (void*)&context);*/
	itr = IfItrExistAlready(bucket, _searchKey, _map->m_keysEqualFunc);
	if (itr == NULL)
	{
		return NULL;
	}

	return itr;
}
static void PairDestroy(Pair* _pair, void** _pKey, void** _pValue)
{
	assert(_pair);
	assert(_pKey);
	assert(_pValue);
	
	*_pKey   = (void*)_pair->m_key;
	*_pValue = (void*)_pair->m_value;

	free(_pair);
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr itr = NULL;
	Pair* pair  = NULL;
	
	if (!IS_A_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if (!_pKey || !_pValue)
	{
		return MAP_INV_ARG_ERROR;
	}
	
	itr = FindKey(_map, _searchKey);
	if (!itr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	pair = ListItrRemove(itr);
	PairDestroy(pair, _pKey, _pValue);
	
	return MAP_SUCCESS;
}

MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	ListItr itr = NULL;
	Pair* pair  = NULL;

	if (!IS_A_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}	
	if (!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if(!_pValue)
	{		
		return MAP_INV_ARG_ERROR;
	}	

	itr = FindKey(_map, _searchKey);
	if (!itr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	pair = ListItrGet(itr);
	*_pValue = (void*)pair->m_value;

	return MAP_SUCCESS;
}

static Pair* PairCreate(const void* _key, const void* _value)
{
	Pair* pair;

	assert(_key);
	assert(_value);

	pair = malloc(sizeof(Pair));
	if (!pair)
	{
		return NULL;
	}

	pair->m_key   = _key;
	pair->m_value = _value;

	return pair;
}

static Pair* PairCreateAndPush(HashMap* _map, const void* _key, const void* _value)
{
	Pair* pair   = NULL;
	List* bucket = NULL;

	assert(_map);
	assert(_key);
	assert(_value);	
	
	pair = PairCreate(_key, _value);
	if (!pair)
	{
		return NULL;
	}
	
	bucket = _map->m_buckets[HASH_INDEX(_map, _key)];
	if (LIST_OK != ListPushHead(bucket, (void*)pair))
	{
		return NULL;
	}

	return pair;
}

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	if (!IS_A_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if (!_value)
	{
		return MAP_INV_ARG_ERROR;
	}
	
	if (FindKey(_map, _key))
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	if (!PairCreateAndPush(_map, _key, _value))
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	return MAP_SUCCESS;
}



/*
static ListItr FindKey(const HashMap* _map, const void* _searchKey)
{
	PredicateFunctionContext context;
	ListItr itr   = NULL;
	ListItr end   = NULL;
	List* bucket;

	assert(_map);
	assert(_searchKey);
	
	
	bucket = _map->m_buckets[HASH_INDEX(_map, _searchKey)];

	
	
	itr = ListItrFindFirst(itr, end, HashMapPredicateFunc, (void*)&context);
	if (itr == end)
	{
		return NULL;
	}

	return itr;
}


static ListItr FindKey(const HashMap* _map, const void* _searchKey)
{
	PredicateFunctionContext context;
	ListItr itr   = NULL;
	ListItr end   = NULL;
	List* bucket;

	assert(_map);
	assert(_searchKey);
	
	bucket = _map->m_buckets[HASH_INDEX(_map, _searchKey)];
	itr = ListItrBegin(bucket);
	end = ListItrEnd(bucket);

	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;
	
	itr = ListItrFindFirst(itr, end, HashMapPredicateFunc, (void*)&context);
	if (itr == end)
	{
		return NULL;
	}

	return itr;
}
*/



















/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
size_t HashMapSize(const HashMap* _map)
{
	
}
 */

/** 
 * This method is optional in the homework 
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.  
 * Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	capacity = _map->m_cpacity;
	for (i = 0; i < capacity; ++i)
	{
		BucketForEach(_map->m_buckets[i], _action, _context)
	}
}
 */

/*
static BucketForEach(Bucket _bucket, KeyValueActionFunction _action, void* _context)
{
	
}

	bucket = _map->m_buckets[HASH_INDEX(_map, _searchKey)];
	
	
	itr = ListItrBegin(bucket);
	end = ListItrEnd(bucket);

	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;
*/




/*
MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t i;
	PredicateFunctionContext context;
	
	if (!IS_A_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}	
	if (!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if(!_pValue)
	{		
		return MAP_INV_ARG_ERROR;
	}	
	
	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;

	i = _map->m_hashFunc(_searchKey) % _map->m_capacity;
	
	FindFirstForward(_map->m_buckets[i], HashMapPredicateFunc, (void*)&context , _pValue);
	if (!_pValue)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	return MAP_SUCCESS;
}
static Pair* RemovePairFromBucket(List* _bucket, void* _context)
{
	ListItr itr   = NULL;
	ListItr end   = NULL;

	assert(_bucket);
	assert(_context);
	
	itr = ListItrBegin(_bucket);
	end = ListItrEnd(_bucket);
	
	itr = ListItrFindFirst(itr, end, HashMapPredicateFunc, _context);
	if (itr == end)
	{
		return NULL;
	}

	return ListItrRemove(itr);
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	PredicateFunctionContext context;
	Pair* pair    = NULL;
	size_t i;
	
	if (!IS_A_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if (!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	if (!_pKey || !_pValue)
	{
		return MAP_INV_ARG_ERROR;
	}
	
	i = _map->m_hashFunc(_searchKey) % _map->m_capacity;

	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;
	
	pair = RemovePairFromBucket(_map->m_buckets[i], (void*)&context);
	if (!pair)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	PairDestroy(pair, _pKey, _pValue);
	
	return MAP_SUCCESS;
}


static ListItr* FindKey(HashMap* _map, const void* _searchKey)
{
	PredicateFunctionContext context;
	size_t i;

	assert(_map);
	assert(_searchKey);

	i = _map->m_hashFunc(_searchKey) % _map->m_capacity;
	
	context.m_equalityFunc = _map->m_keysEqualFunc;
	context.m_searchKey    = _searchKey;
	
	itr = FindPairinBucket(_map->m_buckets[i], (void*)&context);
	if (itr == end)
	{
		return NULL;
	}

	return itr;
}
static Pair* FindPairInBucket(HashMap* _map, void* _context)
{
	ListItr itr   = NULL;
	ListItr end   = NULL;

	itr = ListItrBegin(_map->m_buckets[i]);
	end = ListItrEnd(_map->m_buckets[i]);
	
	itr = ListItrFindFirst(itr, end, HashMapPredicateFunc, (void*)&context);
}
*/




