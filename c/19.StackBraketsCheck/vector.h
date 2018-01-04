#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "ADTErr.h"

typedef struct Vector Vector;

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);
void VectorDestroy(Vector* _vector);
ADTErr VectorAdd(Vector *_vector,  int  _item);   /* Add item to end. */
ADTErr VectorDelete(Vector *_vector,  int* _item); /* Delete item from the end. */
/* The Index range in the following functions is : 1..numOfItems */
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);
ADTErr VectorItemsNum(Vector *_vector, int*  _numOfItems);

void VectorPrint(Vector *_vector);

#endif /* #ifndef __VECTOR_H__ */

