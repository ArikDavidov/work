#include <stdio.h>
#include <stdlib.h>
#include "DynamicVector.h"

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
	Vector* v   = NULL;
	Vector* res = NULL;

	if (0 != _initialSize || 0 != _extensionBblockSize)
	{
		v = malloc(sizeof(Vector));
		if (NULL != v)
		{
			v->m_originalSize = _initialSize;
			v->m_size         = _initialSize;
			v->m_nItems       = 0;
			v->m_blockSize    = _extensionBblockSize;
			v->m_items        = malloc(v->m_originalSize * sizeof(Vector*));
			if (NULL != v->m_items)
			{
				res = v;
			}
			else
			{
				free(v);			
			}
		}
	}
	return res;
}

void VectorDestroy(Vector* _vector)
{	
	free(_vector->m_items);
	free(_vector);
}

ADTErr VectorAdd(Vector *_vector, int  _item)
{
	int* tempip;
	int i=0;
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL != _vector)
	{
		if(_vector->m_nItems == _vector->m_size)
		{
			tempip = realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize) * sizeof(int));
			if(NULL != tempip)
			{
				_vector->m_items = tempip;
				_vector->m_size += _vector->m_blockSize;
			}
			else
			{
				res = ERR_REALLOCATION_FAILED;
			}
		}
		_vector->m_items[_vector->m_nItems] = _item;
		++(_vector->m_nItems);
		res = ERR_OK;
	}
	return res;
}

ADTErr VectorDelete(Vector *_vector, int* _item)
{
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL != _vector)
	{
		if (NULL != _item)
		{
			free(_item);
			--(_vector->m_nItems);

			/* resize */
			/* resize */
			/* resize */
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

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL != _vector)
	{
		if (NULL != _item)
		{
			if(_index -1 < 0) /* The Index range is : 1..numOfItems */
			{
				res = ERR_UNDERFLOW;
			}
			else if(_index > _vector->m_nItems) /* The Index range is : 1..numOfItems */
			{
				res = ERR_OVERFLOW;
			}
			else
			{
				*_item = _vector->m_items[_index];
				res = ERR_OK;
			}
		}
	}
	return res;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	ADTErr res;
	int *tempip;

	res = VectorGet(_vector, _index, tempip);
	if (ERR_OK == res)
	{
		_vector->m_items[_index] = _item;
	}
	return res;
}

ADTErr VectorItemsNum(Vector *_vector, int* _numOfItems)
{
	ADTErr res = ERR_NOT_INITIALIZED;

	if(NULL != _vector)
	{
		*_numOfItems = _vector->m_nItems;
		res = ERR_OK;
	}
	return res;
}

void VectorPrint(Vector *_vector)
{
	int i;
	if(NULL != _vector)
	{
		printf("Vector:");		
		for (i = 0; i < _vector->m_nItems; ++i)
		{
			printf(" %d", _vector->m_items[i]);
		}
		printf("\n");
	}
}

void TestVectorDestroy(Vector* _vector)
{
	VectorDestroy(_vector);
	printf("PASSED: TestVectorDestroy\n");
}

void TestVectorCreate()
{
	Vector*	res = NULL;
	res = VectorCreate(4, 2);
	if (NULL != res)
	{	
		printf("PASSED: TestVectorCreate\n");
		TestVectorDestroy(res);
	}
	else
	{
		printf("FAILED: TestVectorCreate\n");
	}	
}



void TestVectorAdd()
{
	Vector*	_vector = NULL;
	ADTErr	res;

	_vector = VectorCreate(4, 2);
	res = VectorAdd(_vector, 42);
	printf("ERR: %d\n", res);	
	if(ERR_OK == res)
	{
		printf("PASSED: TestVectorAdd\n");		
	}
	else
	{
		printf("FAILED: TestVectorAdd\n");
	}
	VectorDestroy(_vector);
}

void TestRealloc()
{
	Vector*	_vector = NULL;
	ADTErr	res;

	_vector = VectorCreate(4, 2);
	int i;

	for (i = 0; i < 5; ++i)
	{
		res = VectorAdd(_vector, i);
		if(ERR_OK != res)
		{
			printf("FAILED: TestRealloc\n");
			break;
		}
	}
	
	if(_vector->m_size > _vector->m_originalSize)
	{
		printf("PASSED: TestRealloc\n");		
	}
}


