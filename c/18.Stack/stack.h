#ifndef __STACK_H__
#define __STACK_H__

#include "ADTDefs.h"

typedef struct Stack Stack;


Stack*  StackCreate(size_t _size, size_t _blockSize);
void    StackDestroy(Stack* _stack);
ADTDefs StackPush(Stack* _stack, int _item);
ADTDefs StackPop(Stack* _stack, int* _item);
ADTDefs StackTop(Stack* _stack, int* _item);
int     StackIsEmpty(Stack* _stack);

void    StackPrint(Stack *_stack);

#endif /* #ifndef __STACK_H__ */

