#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef enum
{
	STACK_OK  = 0,
	STACK_NOT_INITIALIZED,
	STACK_INV_ARG,
	STACK_REALLOCATION_FAILED,
	STACK_IS_EMPTY
} StackErr;

typedef struct Stack Stack;

Stack*   StackCreate();
void     StackDestroy(Stack** _stack);
StackErr StackPush(Stack* _stack, void* _item);
StackErr StackPop(Stack* _stack, void** _item);
StackErr StackTop(const Stack* _stack, void** _item);
size_t   StackIsEmpty(const Stack* _stack);

void     StackPrint(Stack *_stack);

#endif /* #ifndef __STACK_H__ */

