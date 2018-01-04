#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "stack.h"
#include "ADTErr.h"
struct Stack
{

    Vector *m_vector;

} ;

Stack* StackCreate( size_t _size, size_t _blockSize)
{
	Vector* newVect;
	Stack* newStack = malloc(sizeof(Stack));
	if(!newStack)
	{
		return NULL;
	}
	newVect = VectorCreate(_size, _blockSize);
	if(!newVect)
	{
		free(newStack);
		return NULL;
	}
	(*newStack).m_vector = newVect;
	return newStack;
}

void StackDestroy(Stack* _stack)
{
	if(_stack)
	{
		if((*_stack).m_vector)
		{
			VectorDestroy((*_stack).m_vector);
		}
		free(_stack);
	}
}

ADTErr StackPush(Stack* _stack, int  _item)
{
	if(!_stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorAdd((*_stack).m_vector,  _item);
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	if(!_stack)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete((*_stack).m_vector,  _item);
}

ADTErr StackTop(Stack* _stack)
{
	Vector* myVec;
	if(!_stack || !(*_stack).m_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	myVec = (*_stack).m_vector;
	return VectorGet(myVec, (*myVec).m_nItems, _item);
}

int StackIsEmpty(Stack *_stack)
{
	int result = 0;
	ADTErr error;
	Vector* myVec;
	if(!_stack || !(*_stack).m_vector)
	{
		return 1;
	}
	myVec = (*_stack).m_vector;
	error = VectorGet(myVec, 1, &result);
	if(ERR_OK != error)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*  Unit-Test functions  */

void StackPrint(Stack *_stack)
{
	if(_stack && (*_stack).m_vector)
	{
		VectorPrint((*_stack).m_vector);
	}

}

int isBraketCorrect(char* string)
{
	
}


