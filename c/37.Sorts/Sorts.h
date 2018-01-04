#ifndef __QUICK_SORT__
#define __QUICK_SORT__

#include "Vector.h"
#include "ADTErr.h"

/*
TODO Documentation
Returns:
	0 - The swap is not needed.
*/
typedef int (*Compare)(int, int);
typedef int (*KeyGenerator)(int, void*);
typedef ADTErr (*Sorts)(Vector*);

ADTErr BobbleSort(Vector* _vec);
ADTErr ShakeSort(Vector* _vec);
ADTErr QuickSort(Vector* _vec);
/* ADTErr InsertionSort(Vector* _vec, Compare _isSwapNeeded); */
ADTErr InsertionSort(Vector* _vec, Compare _isSwapNeeded, size_t _startIndex, size_t _gap);
ADTErr ShellSort(Vector* _vec, Compare _isSwapNeeded);
/*
The function sorts integers using the Counting Sort algorithm.
Parameters:
	_vec      - A pointer to a vector.
Returns:
	ERR_OK - If the function suceeds.
Errors:
	ERR_NOT_INITIALIZED   - If the vector pointer is NULL.
	ERR_ALLOCATION_FAILED - If memory allocation of one of the buffers failes.
*/
ADTErr MergeSortRec(Vector* _vec);
/*
The function sorts integers using the Counting Sort algorithm.
Parameters:
	_vec      - A pointer to a vector.
	_maxValue - The value of the largest integer in the vector.
Returns:
	ERR_OK - If the function suceeds.
Errors:
	ERR_NOT_INITIALIZED   - If the vector pointer is NULL.
	ERR_ALLOCATION_FAILED - If memory allocation of one of the buffers failes.
*/
ADTErr CountingSort(Vector* _vec, int _maxValue);
/*
The function sorts integers using the Radix Sort algorithm.
The function assumes all the integers are positive.
Parameters:
	_vec     - A pointer to a vector.
	_nDigits - The number of digits of the largest integer.
Returns:
	ERR_OK - If the function succeeds.
Errors:
	ERR_NOT_INITIALIZED   - If the vector pointer is NULL.
*/
ADTErr RadixSort(Vector* _vec, int _nDigits);

#endif /* #ifndef __QUICK_SORT__ */

