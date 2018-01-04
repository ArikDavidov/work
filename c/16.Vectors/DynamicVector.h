#ifndef __DYNAMYC_VECTOR_H__
#define __DYNAMYC_VECTOR_H__

#include<stdlib.h>

typedef struct Vector Vector;

typedef enum
{
    /* General ADT Errors */
    ERR_OK              =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    /* Vector Errors */
    /* Stack  Errors */
    ERR_STACK_BBBBB = 30,
    /* LinkedList  Errors */
    /* Bit Vector*/
} ADTErr;

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);
void VectorDestroy(Vector* _vector);
ADTErr VectorAdd(Vector *_vector,  int  _item);   /* Add item to end. */
ADTErr VectorDelete(Vector *_vector,  int* _item); /* Delete item from the end. */
/* The Index range in the following functions is : 1..numOfItems */
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);
ADTErr VectorItemsNum(Vector *_vector, int*  _numOfItems);

void VectorPrint(Vector *_vector);

#endif /* #ifndef __DYNAMYC_VECTOR_H__ */

