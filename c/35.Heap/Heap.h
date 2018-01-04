#ifndef __HEAP_H__
#define __HEAP_H__

#include "ADTErr.h"

typedef struct Heap Heap;
/* typedef struct Vector Vector; */

/*
The function creates heap from vector.
Parameters:
	_vec - Pointer to a vector.
Returns:
	Heap* - Pointer to the heap.*/
Heap*  HeapBuild(Vector* _vec);
/*
The function destroys a heap whithout destroying it's vector.
Parameters:
	_heap - Pointer to a heap.
Returns:
	void */
void   HeapDestroy(Heap* _heap);

ADTErr HeapInsert(Heap* _heap, int _data);
ADTErr HeapMax(const Heap* _heap, int* _data);
ADTErr HeapExtractMax(Heap* _heap, int* _data);
/*
The function returns the number of items in the heap.
Parameters:
	_heap - Pointer to a heap. */
size_t HeapItemsNum(Heap* _heap);

void HeapPrint(Heap* _heap);

#endif /* #ifndef __HEAP_H__ */


