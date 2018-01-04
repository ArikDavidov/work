#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>

#define VECTOR_MAGIC 0xDABBAD00

struct Vector
{
    size_t  m_magicNum;
    void**  m_items;
    size_t  m_originalCapacity;
    size_t  m_capacity;
    size_t  m_nItems;
    size_t  m_blockSize;
};

/**  
 * @brief Iterate over all elements in the vector.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.
 * @param[in] _vec - vector to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns number of times the user functions was invoked
 */
static size_t VectorForEach(const Vector* _vec, VectorElementAction _action, void* _context)
{
	size_t i;
	void* item = NULL;

	for(i = 0; i < _vec->m_nItems; ++i)
	{
		VectorGet(_vec, i, &item);
		if(_action(item, i,_context) == 0)
		{
			break;
		}
	}
	return i;
}

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector* vec = NULL;

	if (0 == _initialCapacity && 0 == _blockSize)
	{
		return NULL;
	}
	vec = malloc(sizeof(Vector));
	if (NULL == vec)
	{		
		return NULL;
	}
	vec->m_items = malloc(_initialCapacity * sizeof(void*));
	if (NULL == vec->m_items)
	{
		free(vec);
		return NULL;
	}

	vec->m_magicNum         = VECTOR_MAGIC;
	vec->m_nItems           = 0;
	vec->m_originalCapacity = _initialCapacity;
	vec->m_capacity         = _initialCapacity;
	vec->m_blockSize        = _blockSize;

	return vec;
}

void VectorDestroy(Vector** _vec, void (*_elementDestroy)(void* _item))
{
	size_t i;
	void* item = NULL;

	if (NULL == _vec || NULL == *_vec || (*_vec)->m_magicNum == VECTOR_MAGIC)
	{
		return;
	}
	
	(*_vec)->m_magicNum = 0;

	for (i = 0; i < (*_vec)->m_nItems; ++i)
	{
		VectorGet(*_vec, i, &item);
		_elementDestroy(item);
	}
	
	free((*_vec)->m_items);
	free(*_vec);
	*_vec = NULL;
}

static VectorErr GrowIfNeeded(Vector *_vec)
{
	void** tempPtr;

	if(_vec->m_nItems < _vec->m_capacity)
	{
		return VECTOR_OK;
	}
	if (0 == _vec->m_blockSize)
	{
		return VECTOR_VECTOR_IS_FULL;
	}

	tempPtr = realloc(_vec->m_items, (_vec->m_capacity + _vec->m_blockSize) * sizeof(void*));
	if(NULL == tempPtr)
	{
		return VECTOR_REALLOCATION_FAILED;
	}

	_vec->m_items = tempPtr;
	_vec->m_capacity += _vec->m_blockSize;

	return VECTOR_OK;
}

VectorErr VectorAppend(Vector* _vec, void* _item)
{
	VectorErr res;
	
	if(NULL == _vec || NULL == _item)
	{
		return VECTOR_NOT_INITIALIZED;
	}

	res = GrowIfNeeded(_vec);
	if(VECTOR_OK != res)
	{
		return res;
	}

	_vec->m_items[_vec->m_nItems] = _item;
	++_vec->m_nItems;

	return VECTOR_OK;
}
	
/**
 * The vector will shrink by one block size if the capaity exceeds the num of items
 * by at least 2 block sizes.
 * The vector will not shrink below it's original capacity.
 */
static void ShrinkIfNeeded(Vector* _vec)
{
	void** tempPtr;

	if (_vec->m_capacity - _vec->m_nItems < 2 * _vec->m_blockSize)
	{
		return;
	}
	if (_vec->m_capacity == _vec->m_originalCapacity)
	{
		return;
	}

	tempPtr = realloc(_vec->m_items, (_vec->m_capacity - _vec->m_blockSize) * sizeof(void*));
	if(NULL == tempPtr)
	{
		return;
	}
	_vec->m_items = tempPtr;
	_vec->m_capacity -= _vec->m_blockSize;
}

VectorErr VectorRemove(Vector* _vec, void** _item)
{
	if(NULL == _vec || NULL == _item)
	{
		return VECTOR_NOT_INITIALIZED;
	}

	*_item = _vec->m_items[_vec->m_nItems - 1];
	--(_vec->m_nItems);

	ShrinkIfNeeded(_vec);

	return VECTOR_OK;
}

VectorErr VectorGet(const Vector *_vec, size_t _index, void** _item)
{
	if(NULL == _vec || NULL == _item)
	{
		return VECTOR_NOT_INITIALIZED;
	}

	if(_index > _vec->m_nItems - 1)
	{
		return VECTOR_OVERFLOW;
	}

	*_item = _vec->m_items[_index];

	return VECTOR_OK;
}

VectorErr VectorSet(Vector* _vec, size_t _index, void* _item)
{
	if(NULL == _vec || NULL == _item)
	{
		return VECTOR_NOT_INITIALIZED;
	}

	if(_index > _vec->m_nItems - 1)
	{
		return VECTOR_OVERFLOW;
	}
	
	_vec->m_items[_index] = _item;
	
	return VECTOR_OK;
}

size_t VectorSize(const Vector* _vec)
{
	return (NULL != _vec) ? _vec->m_nItems : 0;
}

size_t VectorCapacity(const Vector* _vec)
{
	return (NULL != _vec) ? _vec->m_capacity : 0;
}

void VectorPrint(Vector* _vec, VectorElementAction _printElement)
{
	if(NULL == _vec)
	{
		return;
	}

	printf("Vector:");

	VectorForEach(_vec, _printElement, NULL);

	printf("\n");
}









