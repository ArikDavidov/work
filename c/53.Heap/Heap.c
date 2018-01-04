#include "Vector.h"
#include "Heap.h"

#include <stdlib.h>

/* #define NDEBUG 1 */
#include <assert.h>

#define LAST_PARENT(h) (PARENT((h)->m_size - 1))

#define PARENT(i)	(((i)-1)/2)
#define LEFT(i)		(2*(i)+1)
#define RIGHT(i)	(2*(i)+2)


#define IS_A_HEAP(h) ((h) && HEAP_MAGIC == (h)->m_magic)
#define HEAP_MAGIC 0xBEEEEEEF

struct Heap
{
    size_t  m_magic;
    Vector* m_vec;
    size_t  m_size;
    LessThanComparator m_less;
};

static Heap* HeapAllocateAndInitialize(Vector* _vec, LessThanComparator _pfLess)
{
	Heap* heap = NULL;
	
	assert(_vec);
	assert(_pfLess);
		
	heap = malloc(sizeof(Heap));
	if (!heap)
	{
		return NULL;
	}
	
	heap->m_magic = HEAP_MAGIC;
	heap->m_vec   = _vec;
	heap->m_less  = _pfLess;
	heap->m_size  = VectorSize(_vec);

	return heap;
}

static void Swap(Vector* _vec, size_t _i,  size_t _j, void* _a, void* _b)
{
	assert(_vec);

	VectorSet(_vec, _i, _b);
	VectorSet(_vec, _j, _a);
}
/* TODO
static void Heapify(Heap* _heap, size_t _i, void* _parent)
{
	if (_i > LAST_PARENT(_heap))
	{
		return;
	}
	
	if (PARENT == FindMax(PARENT, LEFT, RIGHT))
	{
		return;
	}
	Swap(PARENT, maxIndex);
	Heapify(_heap, PARENT);
}
*/
static void Heapify(Heap* _heap, size_t _i, void* _parent)
{
	void*  left   = NULL;
	void*  right  = NULL;
	size_t IndexOfMax;
	void*  max = _parent;
	
	assert(_heap);

	VectorGet(_heap->m_vec, LEFT(_i), &left);
	VectorGet(_heap->m_vec, RIGHT(_i), &right);

    if (LEFT(_i) <= _heap->m_size && _heap->m_less(max, left))
    {
    	IndexOfMax = LEFT(_i);
    	max = left;
    }
    if (RIGHT(_i) <= _heap->m_size && _heap->m_less(max, right))
    {
    	IndexOfMax = RIGHT(_i);
    	max = right;
    }
    if (IndexOfMax != _i)
    {
		Swap(_heap->m_vec, _i, IndexOfMax, _parent, max);
		Heapify(_heap, IndexOfMax, _parent);
    }
}

Heap* HeapBuild(Vector* _vec, LessThanComparator _pfLess)
{	
	Heap* heap = NULL;
	void* parent = NULL;
	size_t noe, i;
	
	if (!_vec || !_pfLess)
	{
		return NULL;
	}
	
	heap = HeapAllocateAndInitialize(_vec, _pfLess);
	if (!heap)
	{
		return NULL;
	}

	noe = VectorSize(_vec);
	
	/* No heapify needed */
	if (noe < 2)
	{
		return heap;
	}

	for (i = LAST_PARENT(heap); i < noe; --i)
	{
		VectorGet(_vec, i, &parent);
		Heapify(heap, i, parent);
	}

	return heap;
}

Vector* HeapDestroy(Heap** _heap)
{
	Vector* vec = NULL;

	if (!_heap || !IS_A_HEAP(*_heap))
	{
		return NULL;
	}

	vec = (*_heap)->m_vec;
	(*_heap)->m_magic = 0;
	free(*_heap);

	return vec;

}

static void BobbleUp(Heap* _heap, size_t _i, void* _element)
{
	void* parent = NULL;

	assert(_heap);
	assert(_i < _heap->m_size);
	assert(_heap->m_size > 1);

	if (0 == _i)
	{
		return;
	}
	
	VectorGet(_heap->m_vec, PARENT(_i), &parent);
	
	if (_heap->m_less(parent, _element))
	{
		Swap(_heap->m_vec, _i, PARENT(_i), _element, parent);
		BobbleUp(_heap, PARENT(_i), _element);
	}
}

HeapResult HeapInsert(Heap* _heap, void* _element)
{
	VectorErr ret;

	if (!IS_A_HEAP(_heap))
	{
		return HEAP_NOT_INITIALIZED;
	}
	/* TODO if not out of bounce use VectorSet*/
	ret = VectorAppend(_heap->m_vec, _element);
	if (ret != VECTOR_OK)
	{
		return HEAP_REALLOCATION_FAILED;
	}

	++_heap->m_size;

	if (_heap->m_size > 1)
	{
		BobbleUp(_heap, _heap->m_size - 1, _element);
	}

	return HEAP_SUCCESS;
}

const void* HeapPeek(const Heap* _heap)
{
	void* item;
	VectorErr ret;

	if (!IS_A_HEAP(_heap) || 0 == _heap->m_size)
	{
		return NULL;
	}

	ret = VectorGet(_heap->m_vec, 0, &item);
	if (VECTOR_OK != ret)
	{
		return NULL;
	}

	return (const void*)item;
}

void* HeapExtract(Heap* _heap)
{
	void* first = NULL;
	void* last = NULL;


	if (!IS_A_HEAP(_heap) || 0 == _heap->m_size)
	{
		return NULL;
	}

	VectorGet(_heap->m_vec, 0, &first);
	VectorGet(_heap->m_vec, _heap->m_size - 1, &last);

	Swap(_heap->m_vec, 0, _heap->m_size - 1, first, last);
	--_heap->m_size;
	Heapify(_heap, 0, last);

	return first;
}

size_t HeapSize(const Heap* _heap)
{
	return (!IS_A_HEAP(_heap)) ? 0 : _heap->m_size;
}



