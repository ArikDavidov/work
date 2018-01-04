#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>

struct Vector
{
    int*    m_items;
    size_t  m_originalSize; /* original allocated space for items) */
    size_t  m_size;         /* actual allocated space for items) */
    size_t  m_nItems;       /* actual number of items */
    size_t  m_blockSize;    /* the chunk size to be allocated when no space */
};

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	Vector* vec = NULL;

	if (0 == _initialSize && 0 == _extensionBblockSize)
	{
		return NULL;
	}
	vec = malloc(sizeof(Vector));
	if (NULL == vec)
	{
		
		return NULL;
	}
	vec->m_items = malloc(_initialSize * sizeof(int));
	if (NULL == vec->m_items)
	{
		free(vec);
		return NULL;
	}

	vec->m_nItems       = 0;
	vec->m_originalSize = _initialSize;
	vec->m_size         = _initialSize;
	vec->m_blockSize    = _extensionBblockSize;

	return vec;
}

void VectorDestroy(Vector* _vector)
{
	if (NULL == _vector)
	{
		return;
	}	
	free(_vector->m_items);
	_vector->m_items = NULL;
	free(_vector);
}

static ADTErr ReallocIfReachedCapacity(Vector *_vector)
{
	int* tempip;

	if(_vector->m_nItems < _vector->m_size)
	{
		return ERR_OK;
	}
	if (0 == _vector->m_blockSize)
	{
		return ERR_VECTOR_IS_FULL;
	}

	tempip = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize) * sizeof(int));
	if(NULL == tempip)
	{
		return ERR_REALLOCATION_FAILED;
	}

	_vector->m_items = tempip;
	_vector->m_size += _vector->m_blockSize;

	return ERR_OK;
}

ADTErr VectorAdd(Vector *_vector, int  _item)
{
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL == _vector)
	{
		return res;
	}

	res = ReallocIfReachedCapacity(_vector);
	if(ERR_OK != res)
	{
		return res;
	}

	_vector->m_items[_vector->m_nItems] = _item;
	++_vector->m_nItems;

	return res;
}

ADTErr VectorDelete(Vector* _vector, int* _item)
{
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL != _vector)
	{
		if (NULL != _item)
		{
			free(_item);
			--(_vector->m_nItems);

			/* resize */

			res = ERR_OK;
		}
		else
		{
			res = ERR_GENERAL;
		}	
	}
	return res;
}

ADTErr VectorGet(Vector *_vector, size_t _index, int* _item)
{
	if(NULL == _vector || NULL == _item)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index < 0)
	{
		return ERR_UNDERFLOW;
	}
	if(_index > _vector->m_nItems - 1)
	{
		return ERR_OVERFLOW;
	}

	*_item = _vector->m_items[_index];

	return ERR_OK;
}

ADTErr VectorSet(Vector* _vector, size_t _index, int _item)
{
	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index < 0)
	{
		return ERR_UNDERFLOW;
	}
	if(_index > _vector->m_nItems - 1)
	{
		return ERR_OVERFLOW;
	}
	
	_vector->m_items[_index] = _item;

	return ERR_OK;
}

ADTErr VectorItemsNum(Vector* _vector, size_t* _numOfItems)
{
	if(NULL == _vector || NULL == _numOfItems)
	{
		return ERR_NOT_INITIALIZED;
	}

	*_numOfItems = _vector->m_nItems;

	return ERR_OK;
}

void VectorPrint(Vector* _vector)
{
	int i;

	if(NULL == _vector)
	{
		return;
	}

	printf("Vector:");		
	for (i = 0; i < _vector->m_nItems; ++i)
	{
		printf(" %d", _vector->m_items[i]);
	}
	printf("\n");
}




















