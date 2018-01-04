#include "ADTErr.h"

#include <stddef.h>

typedef int(*sortMethod)(const void*, const void*);

/*
Generic function that preforms a bubble sort on array of any type of elements
using _IsSwapNeeded sorting method.
Parameters:
	_data         - Pointer to the array where the elements are to be sorted, type-casted
					to a pointer of type void*.
	_elementSize  - Size of each element in bytes.
	_noe          - Number of elements in the array.
	_IsSwapNeeded - Pointer to a function that recives pointers to two elements
					and returns 1 if they need to be swaped, or 0 if no swap is deeded.
Returns:
	ERR_OK - If the sort was successful.
           - If the number of elements in the array is 1 or 0.
Errors:
	ERR_NOT_INITIALIZED      - If one of the parameters _data or _IsSwapNeeded is NULL.
	ERR_INVALID_ELEMENT_SIZE - If the _elementSize parameter is 0.
	ERR_ALLOCATION_FAILED    - If allocation of a buffer failed.
*/
ADTErr GenBobbleSort(void* _data, size_t _elementSize, size_t _noe, sortMethod _IsSwapNeeded);



