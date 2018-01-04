#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"
#include "Heap.h"

#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*(i)+2)
#define LAST_PARENT PARENT(heap->m_heapSize - 1)

#define MAGIC_NUM 4121996


struct Heap
{
    Vector* m_vector;
    size_t  m_heapSize;
    size_t  m_magicNum;
};

static void Swap(Vector* _vec, size_t _i, size_t _j)
{
	int x, y;
	
	VectorGet(_vec, _i, &x);
	VectorGet(_vec, _j, &y);
	
	VectorSet(_vec, _i, y);
	VectorSet(_vec, _j, x);
}

static ADTErr GetValues(Vector* _vec, size_t _i, int* _parent, int* _left, int* _right)
{
	VectorGet(_vec, _i, _parent);
	VectorGet(_vec, LEFT(_i), _left);
	/* ERR_OK if the right node exists */
	return VectorGet(_vec, RIGHT(_i), _right);
}

static void Heapify(Vector* _vec, size_t _i)
{
	int parent, left, right;
	ADTErr res;

	/* ERR_OK will mean that the right node exists */
	res = GetValues(_vec, _i, &parent, &left, &right);	
	if (parent < left || (ERR_OK == res && parent < right))
	{
		if (ERR_OK == res && right > left)
		{
			Swap(_vec, _i, LEFT(_i));
			Heapify(_vec, LEFT(_i));
		}
		else
		{
			Swap(_vec, _i, RIGHT(_i));
			Heapify(_vec, RIGHT(_i));
		}
	}
	return;
}

Heap* HeapBuild(Vector* _vec)
{
	Heap* heap;
	int i;
	
	if (NULL == _vec)
	{
		return NULL;	
	}
	heap = malloc(sizeof(Heap));
	if (NULL == heap)
	{
		return NULL;	
	}
	
	heap->m_vector = _vec;
	VectorItemsNum(_vec, (int*)&heap->m_heapSize);
	heap->m_magicNum = MAGIC_NUM;

	for (i = LAST_PARENT; i >= 0; --i)
	{
		Heapify(_vec, i);
	}
	return heap;
}

void HeapDestroy(Heap* _heap)
{
	if (NULL != _heap && MAGIC_NUM == _heap->m_magicNum)
	{
		_heap->m_magicNum = 0;
		free(_heap);
	}
}


ADTErr HeapMax(const Heap* _heap, int* _data)
{
	if (NULL == _heap || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}

	return VectorGet(_heap->m_vector, 0, _data);
}

ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	if (NULL == _heap || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (0 == _heap->m_heapSize)
	{
		return ERR_TREE_IS_EMPTY;
	}

	Swap(_heap->m_vector, 0, _heap->m_heapSize - 1);

	VectorDelete(_heap->m_vector, _data);
	Heapify(_vec, 0);

	return ERR_OK;
}

size_t HeapItemsNum(Heap* _heap)
{
	if (NULL == _heap)
	{
		return 0;
	}
	return _heap->m_heapSize;
}

void HeapPrint(Heap* _heap)
{
	if (NULL == _heap)
	{
		printf("No heap was found.\n");
		return; 
	}
	if (0 == _heap->m_heapSize)
	{
		printf("Tree is empty.\n");
		return;
	}
	VectorPrint(_heap->m_vector);
}

