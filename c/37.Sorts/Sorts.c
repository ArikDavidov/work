#include "Sorts.h"
#include "ADTErr.h"

#include <stdlib.h>

#define MAX_LEFT_INDEX (_begin + (_end - _begin) / 2)

static int SwapIfNeeded(Vector* _vec, size_t _i, size_t _j)
{
	int left = 0, right = 0;
	
	VectorGet(_vec, _i, &left);
	VectorGet(_vec, _j, &right);
	if (left <= right)
	{
		return 0;
	}
	
	VectorSet(_vec, _i, right);	
	VectorSet(_vec, _j, left);

	return 1;
}

static void Swap(int* x, int* y)
{
	int temp;

	temp = *x;
	*x   = *y;
	*y   = temp;
}

static size_t Partition(Vector* _vec, size_t _begin, size_t _end)
{
	int pivotValue, leftValue, rightValue;
	size_t leftIndex   = _begin + 1;
	size_t rightIndex = _end;
	
	VectorGet(_vec, _begin, &pivotValue);
	VectorGet(_vec, leftIndex, &leftValue);
	VectorGet(_vec, rightIndex, &rightValue);

	while (leftIndex < rightIndex)
	{
		while (leftValue <= pivotValue && leftIndex < _end)
		{
			++leftIndex;
			VectorGet(_vec, leftIndex, &leftValue);
		}
		while (rightValue > pivotValue)
		{
			--rightIndex;
			VectorGet(_vec, rightIndex, &rightValue);
		}
	
		if (leftIndex < rightIndex)
		{
			Swap(&leftValue, &rightValue);
			VectorSet(_vec, leftIndex, leftValue);
			VectorSet(_vec, rightIndex, rightValue);
			/* InsertionSortSwap(_vec, j - 1, j, leftValue, rightValue); */
		}
	}
	if (pivotValue > rightValue)
	{
		VectorSet(_vec, rightIndex, pivotValue);
		VectorSet(_vec, _begin, rightValue);
	}
	/* p {pivotValue, leftValue, rightValue, _begin, leftIndex, rightIndex} */
	return rightIndex;
}

static void QuickRec(Vector* _vec, size_t _begin, size_t _end)
{
	size_t pivot;
	
	/* Partition size is 1 or 0. */
	if (_begin >= _end || 0 == _end + 1 )
	{ 
		return;
	}
	
	pivot = Partition(_vec, _begin, _end);

	QuickRec(_vec, _begin, pivot - 1);
	QuickRec(_vec, pivot + 1, _end);
}

static void InsertionSortSwap(Vector* _vec, size_t _leftIndex, size_t _rightIndex, int _leftValue, int _rightValue)
{
	VectorSet(_vec, _leftIndex, _rightValue);
	VectorSet(_vec, _rightIndex, _leftValue);
}

ADTErr BobbleSort(Vector* _vec)
{
	size_t numOfItems, i, j, swaped;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);

	for (i = 0; i < numOfItems -1; ++i)
	{
		swaped = 0;
		for (j = 0; j < numOfItems -1 - i; ++j)
		{
			swaped += SwapIfNeeded(_vec, j, j + 1);
		}
		/* The array is already sorted. */
		if (!swaped)
		{
			break;
		}
	}

	return ERR_OK;
}

/*
ADTErr BobbleSort(Vector* _vec)
{
	size_t numOfItems, i, j, swaped;
	int left, right;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);

	for (i = 0; i < numOfItems -1; ++i)
	{
		swaped = 0;
		for (j = 0; j < numOfItems -1 - i; ++j)
		{
			VectorGet(_vec, _j, &left);
			VectorGet(_vec, _j + 1, &right);
			if (left > right)
			{
				InsertionSortSwap(_vec, j, j + 1, leftValue, rightValue);
				swaped = 1;
			}
		}
		if (!swaped)
		{
			break;
		}
	}

	return ERR_OK;
}
*/

			
ADTErr ShakeSort(Vector* _vec)
{
	size_t numOfItems, i, j, swaped;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	
	for (i = 0; i < numOfItems / 2; ++i)
	{
		swaped = 0;
		for (j = i; j < numOfItems - 1 - i; ++j)
		{
			swaped += SwapIfNeeded(_vec, j, j + 1);
		}
		/* The array is already sorted. */
		if (!swaped)
		{
			break;
		}
	
		swaped = 0;
		for (j = numOfItems -2 -i; j > i; --j)
		{
			swaped += SwapIfNeeded(_vec, j - 1, j);
		}
		/* The array is already sorted. */
		if (!swaped)
		{
			break;
		}		
	}

	return ERR_OK;
}

ADTErr QuickSort(Vector* _vec)
{
	size_t numOfItems;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}

	VectorItemsNum(_vec, &numOfItems);

	QuickRec(_vec, 0, numOfItems - 1);
	
	return ERR_OK;
}
/*
ADTErr InsertionSort(Vector* _vec, Compare _isSwapNeeded)
{
	int leftValue, rightValue;
	size_t numOfItems, i, j;
	
	if (NULL == _vec || NULL == _isSwapNeeded)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);

	for (i = 1; i < numOfItems; ++i)
	{
		for (j = i; j > 0; --j)
		{
			VectorGet(_vec, j,  &rightValue);
			VectorGet(_vec, j - 1, &leftValue);
			
			if (_isSwapNeeded(leftValue, rightValue))
			{
				InsertionSortSwap(_vec, j - 1, j, leftValue, rightValue);
			}
			else
			{
				break;
			}
		}
	}	
	return ERR_OK;	
}
*/
ADTErr ShellSort(Vector* _vec, Compare _isSwapNeeded)
{
	size_t numOfItems, gap, startIndex;
	
	if (NULL == _vec || NULL == _isSwapNeeded)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	
	/* Starting from index 1 because checking with the previous */
	for (gap = numOfItems / 2; gap > 0; gap /= 2)
	{
		for (startIndex = gap; startIndex < gap * 2; startIndex += 1)
		{
			InsertionSort(_vec, _isSwapNeeded, startIndex, gap);
		}
	}
	return ERR_OK;	
}

ADTErr InsertionSort(Vector* _vec, Compare _isSwapNeeded, size_t _startIndex, size_t _gap)
{
	int leftValue, rightValue;
	size_t numOfItems, i, j;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);

	/* Starting from index 1 because checking with the previous */
	for (i = _startIndex; i < numOfItems; i += _gap)
	{
		for (j = i; j >= _gap; j -= _gap)
		{
			VectorGet(_vec, j,  &rightValue);
			VectorGet(_vec, j - _gap, &leftValue);
			
			if (_isSwapNeeded(leftValue, rightValue))
			{
				InsertionSortSwap(_vec, j - _gap, j, leftValue, rightValue);
			}
			else
			{
				break;
			}
		}
	}	
	return ERR_OK;	
}


static void CopySortedToVector(Vector* _vec, int* _arr, size_t _begin, size_t _end)
{
	size_t i;

	for (i = _begin; i <= _end; ++i)
	{
		VectorSet(_vec, i, _arr[i]);
	}
}

static void CopyFromVecToArray(Vector* _vec, int* _arr, size_t _arrIndex, size_t* _vecIndex, int* _valuePtr)
{
	_arr[_arrIndex] = *_valuePtr;
	++(*_vecIndex);
	VectorGet(_vec, *_vecIndex, _valuePtr);
}

static void Merge(Vector* _vec, int* _arr, size_t _begin, size_t _leftEnd, size_t _end)
{
	size_t leftIndex = _begin;
	size_t rightIndex = _leftEnd + 1;
	size_t arrIndex = _begin;
	int leftValue, rightValue;

	VectorGet(_vec, leftIndex, &leftValue);
	VectorGet(_vec, rightIndex, &rightValue);

	while (leftIndex <= _leftEnd)
	{ /* when all left values are inserted, there is no need to insert the rest of the right values (right tail),
		because they are already in their correct place in the vector. */
		if (rightIndex > _end || leftValue <= rightValue)
		{
			CopyFromVecToArray(_vec, _arr, arrIndex, &leftIndex, &leftValue);
		}
		else
		{
			CopyFromVecToArray(_vec, _arr, arrIndex, &rightIndex, &rightValue);
		}
		++arrIndex;
	}
	/* The copying is done up to the rigt tail. */
	CopySortedToVector(_vec, _arr, _begin, rightIndex - 1);
}

static void MergeRec(Vector* _vec, int* _arr, size_t _begin, size_t _end)
{
	if (_begin == _end)
	{
		return;
	}

	MergeRec(_vec, _arr, _begin, MAX_LEFT_INDEX);
	MergeRec(_vec, _arr, MAX_LEFT_INDEX + 1, _end);
	
	Merge(_vec, _arr, _begin, MAX_LEFT_INDEX, _end);
}
/*
static void MergeIterative(Vector* _vec, int* _arr, size_t _begin, size_t _end)
{
	if (_begin == _end)
	{
		return;
	}

	for (i = 2; i < _end - _begin + 1; i *= 2)
	{
		for (j = 0; 
		{
			Merge(_vec, _arr, _begin + j * i, _end);
			Merge(_vec, _arr, _begin + j * i, _end);
		}		
	}	
}
*/
ADTErr MergeSortRec(Vector* _vec)
{
	size_t numOfItems;
	int* arr;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	arr = malloc(numOfItems * sizeof(int));
	if (NULL == arr)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	MergeRec(_vec, arr, 0, numOfItems - 1);
	
	free(arr);
	
	return ERR_OK;
}

/*
ADTErr MergeSort(Vector* _vec)
{
	size_t numOfItems;
	int* arr;
	
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	arr = malloc(numOfItems * sizeof(int));
	if (NULL == arr)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	MergeIterative(_vec, arr, 0, numOfItems - 1);
	
	free(arr);
	
	return ERR_OK;
}
*/

ADTErr CheckParametersAndInitialiseArrays(Vector* _vec,int _maxValue, int** _helperArr, int** _countArr)
{
	size_t numOfItems;
	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec, &numOfItems);
	*_helperArr = malloc(numOfItems * sizeof(size_t));
	if (NULL == _helperArr)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	/* Range: from 0 to _maxValue */
	*_countArr = calloc(_maxValue + 1, sizeof(size_t)); 
	if (NULL == _countArr)
	{
		free(_helperArr);
		return ERR_ALLOCATION_FAILED;
	}
	
	return ERR_OK;
}

static int GetKey(int _value, void* _sortingDigit)
{
	int i;
	
	if (NULL == _sortingDigit)
	{
		return _value;
	}

	for (i = 0; i < *(int*)_sortingDigit; ++i)
	{
		_value /= 10;
	}

	return _value % 10;
}

static void CountOccurrencesAndCopyToHelperArr(Vector* _vec, int* _countArr, int* _helperArr, KeyGenerator _GetKey, void* _keyParam)
{
	size_t i, numOfItems;
	int	currentValue, key;
	
	VectorItemsNum(_vec, &numOfItems);
	
	for (i = 0; i < numOfItems; ++i)
	{
		VectorGet(_vec, i, &currentValue);

		if (NULL == _GetKey)
		{
			key = currentValue;
		}
		else
		{
			key = _GetKey(currentValue, _keyParam);
		}
		++_countArr[key];
		
		_helperArr[i] = currentValue;
	}
}

static void ConvertArrToCumulativeSums(int* _countArr, int _maxValue)
{
	int i;
	
	for (i = 1; i <= _maxValue; ++i)
	{
		_countArr[i] += _countArr[i - 1];
	}
}

static void SortToVec(Vector* _vec, int* _countArr, int* _helperArr, KeyGenerator _GetKey, void* _keyParam)
{
	size_t numOfItems, insertionIndex;
	int i, key;
		
	VectorItemsNum(_vec, &numOfItems);
	
	for (i = numOfItems - 1; i >= 0; --i)
	{
		if (NULL == _GetKey)
		{
			key = _helperArr[i];
		}
		else
		{
			key = _GetKey(_helperArr[i], _keyParam);
		}
		insertionIndex = _countArr[key] - 1;
		VectorSet(_vec, insertionIndex, _helperArr[i]);
		--_countArr[key];
	}
}

static ADTErr CountingSortByKey(Vector* _vec, int _maxValue, KeyGenerator _GetKey, void* _keyParam)
{
	ADTErr res;
	int* helperArr;
	int* countArr;
	
	res = CheckParametersAndInitialiseArrays(_vec, _maxValue, &helperArr, &countArr);
	if (res != ERR_OK)
	{
		return res;
	}
	
	CountOccurrencesAndCopyToHelperArr(_vec, countArr, helperArr, _GetKey, _keyParam);
	ConvertArrToCumulativeSums(countArr, _maxValue);
	SortToVec(_vec, countArr, helperArr, _GetKey, _keyParam);
	
	free(countArr);
	free(helperArr);
	
	return ERR_OK;
}

ADTErr CountingSort(Vector* _vec, int _maxValue)
{
	return CountingSortByKey(_vec, _maxValue, NULL, NULL);
}

ADTErr RadixSort(Vector* _vec, int _nDigits)
{
	int i;

	if (NULL == _vec)
	{
		return ERR_NOT_INITIALIZED;
	}

	for (i = 0; i < _nDigits; ++i)
	{
		CountingSortByKey(_vec, 9, GetKey, (void*)&i);
	}

	return ERR_OK;
}





