#include "Hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>	/* sqrt */

#define MIN_HASH_SIZE 10
#define MAGIC_NUM 4121996

struct Hash
{
    int* m_data; 
    size_t m_originalSize;    
    size_t m_hashSize;			/*real array size*/
    size_t m_maxCollisions;		/*maximum ofset*/
    size_t m_numberOfInsertions; /* Number of elements */
    size_t m_totalCollisions;	/*total collisions until now*/
    size_t m_totalInsertion;	/*total insertions until now*/
    size_t m_magicNum;
};

static size_t IsPrime(size_t _num)
{ /* Assumes _num is odd number. */
	size_t div;
	
	for(div = 3; div <= sqrt(_num); div += 2)
	{
		if (0 == _num % div)
		{
			return 0;
		}
	}
	return 1;
}

static size_t CalculateHashSize(const size_t _size)
{
	size_t hashSize;
	
	hashSize = _size * 1.3;	
	if (0 == hashSize % 2)
	{
		hashSize += 1;
	}
	
	while (!IsPrime(hashSize))
	{
		hashSize += 2;
	}
	
	return hashSize;
}

Hash* HashCreate(const size_t _size)
{
	Hash* hash;
	size_t hashSize;
	
	if (MIN_HASH_SIZE < _size)
	{
		return NULL;
	}	
	hash = calloc(1, sizeof(Hash));
	if (NULL == hash)
	{
		return NULL;
	}
	
	hashSize = CalculateHashSize(_size);
	hash->m_data = calloc(hashSize, sizeof(int));
	if (NULL == hash->m_data)
	{
		free(hash);
		return NULL;
	}
	
	hash->m_originalSize = _size;
    hash->m_hashSize = hashSize;
    hash->m_magicNum = MAGIC_NUM;

	return hash;	
}

void HashDestroy(Hash* _hash)
{
	if (NULL == _hash || MAGIC_NUM != _hash->m_magicNum)
	{
		return;
	}
	
	free(_hash->m_data);
	_hash->m_data = NULL;
	free(_hash);

	_hash->m_magicNum = 0;
}

static size_t HashFunction(int _data)
{
	return _data;
}

static size_t Find(Hash* _hash, const int _data)
{
	int i, collisions;
	
	i = HashFunction(_data) % _hash->m_hashSize;
	while (0 != _hash->m_data[i] && collisions <= _hash->m_maxCollisions)
	{
		if (_data == _hash->m_data[i])
		{
			return i;
		}
		++collisions;
		++i;
		i %= _hash->m_hashSize;
	}
	
	return -1;
}

static void Insert(Hash* _hash, int _data)
{
	int i, collisions;
	
	i = HashFunction(_data) % _hash->m_hashSize;
	while (0 < _hash->m_data[i])
	{
		++collisions;
		++i;
		i %= _hash->m_hashSize;
	}
	_hash->m_data[i] = _data;
	
	++_hash->m_numberOfInsertions;
	++_hash->m_totalInsertion;

	_hash->m_totalCollisions += collisions;
	if (collisions > _hash->m_maxCollisions)
	{
		_hash->m_maxCollisions = collisions;
	}
}

ADTErr HashInsert(Hash* _hash, int _data)
{
	int res;
	
	if (NULL == _hash)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_data < 1)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if (_hash->m_numberOfInsertions == _hash->m_originalSize)
	{
		return ERR_HASH_IS_FULL;
	}
	
	res = Find(_hash, _data);
	if (-1 != res)
	{
		return ERR_VALUE_ALREADY_EXISTS;
	}

	Insert(_hash, _data);

	return ERR_OK;
}

static void Remove(Hash* _hash, int _i)
{
	_hash->m_data[_i] = -1;
	--_hash->m_numberOfInsertions;
}


ADTErr HashRemove(Hash* _hash, int _data)
{
	int i;
	
	if (NULL == _hash)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_data < 1)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	i = Find(_hash, _data);
	if (-1 == i)
	{
		return ERR_VALUE_NOT_FOUND;
	}	
	Remove(_hash, i);
	
	return ERR_OK;
}

size_t HashCapacity(const Hash* _hash)
{
	if (NULL == _hash)
	{
		return 0;
	}
	
	return _hash->m_hashSize;
}














