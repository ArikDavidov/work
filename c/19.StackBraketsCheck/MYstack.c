#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector *m_vector;
};

Stack*  StackCreate(size_t _size, size_t _blockSize)
{
	Vector* vector = NULL;
	Stack* stack   = NULL;
	Stack* res     = NULL;
	
	vector = VectorCreate(_size, _blockSize);

	if (NULL != vector)
	{
		stack = malloc(sizeof(Stack));
		if (NULL != stack)
		{
			stak->m_vector = vector;
			res = stack;
		}
		else
		{
			free(vector);
		}
	}
	return res;
}


void    StackDestroy(Stack* _stack)
{
	if (NULL == _stack)
	{
		return;
	}	
	free(_stack->m_vector);
	_vector->m_vector = NULL;
	free(_stack);
}

ADTDefs StackPush(Stack* _stack, int _item)
{
	ADTErr res = ERR_OK;

	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	res = ReallocIfReachedCapacity(_vector);

	if(ERR_OK == res)
	{
		_vector->m_items[_vector->m_nItems] = _item;
		++(_vector->m_nItems);
	}
	return res;
}



ADTDefs StackPop(Stack* _stack, int* _item);
ADTDefs StackTop(Stack* _stack, int* _item);
int     StackIsEmpty(Stack* _stack);

void    StackPrint(Stack *_stack);



ADTErr VectorAdd(Vector *_vector, int  _item)
{
	ADTErr res = ERR_OK;

	if(NULL == _vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	res = ReallocIfReachedCapacity(_vector);

	if(ERR_OK == res)
	{
		_vector->m_items[_vector->m_nItems] = _item;
		++(_vector->m_nItems);
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
	int *tempip = NULL;

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




















