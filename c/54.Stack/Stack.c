#include "List.h"
#include "Stack.h"

#include <stdlib.h>

/* #define NDEBUG 1 */
#include <assert.h>

#define IS_A_STACK(s) (s)

typedef List Stack;


Stack* StackCreate(void)
{
	return ListCreate();
}

void StackDestroy(Stack** _stack)
{
	if (!_stack || !IS_A_STACK(*_stack))
	{
		return;
	}
	
	ListDestroy(&(*_stack)->m_list, NULL);
	free(*_stack);
	*_stack = NULL;
}

StackErr StackPush(Stack* _stack, void* _item)
{
	ListErrors res;
	
	if (!IS_A_STACK(_stack))
	{
		return STACK_NOT_INITIALIZED;
	}
	
	res = ListPushHead(_stack->m_list, _item);
	if (LIST_OK != res)
	{
		return STACK_ALLOCATION_FAILED;
	}
	
	return STACK_OK;	
}

StackErr StackPop(Stack* _stack, void** _item)
{
	ListErrors res;
	
	if (!IS_A_STACK(_stack))
	{
		return STACK_NOT_INITIALIZED;
	}
	if (!_item)
	{
		return STACK_INV_ARG;
	}
	
	if (1 == ListIsEmpty(_stack->m_list))
	{
		return STACK_IS_EMPTY;
	}
	
	ListPopHead(_stack->m_list, _item);
		
	
		
		
		
		
		
}
/*
ADTDefs StackTop(const Stack* _stack, void** _item);
void*     StackIsEmpty(const Stack* _stack);

void    StackPrint(Stack *_stack);

*/









