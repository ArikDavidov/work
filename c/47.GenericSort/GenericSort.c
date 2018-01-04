#include "ADTErr.h"
#include "GenericSort.h"

#include <stdlib.h>
#include <string.h>	/* memcpy */

static void Swap(void* _a, void* _b, void* _swapBlock, size_t _elementSize)
{
	memcpy(_swapBlock, _a, _elementSize);
	memcpy(_a, _b, _elementSize);
	memcpy(_b, _swapBlock, _elementSize);
}

static int Bobble(char* _start, char* _end, size_t _elementSize, sortMethod _isSwapNeeded, void* _swapBlock)
{	
	int swaped = 0;
	
	while (_start != _end) 
	{
		if (_isSwapNeeded(_start, _start + _elementSize))
		{
			Swap(_start, _start + _elementSize, _swapBlock, _elementSize);
			swaped = 1;
		}
		_start += _elementSize;
	}	
	
	/* If swaped == 0 the array is already sorted.*/
	return (!swaped) ? 1 : 0;
}

	
ADTErr GenBobbleSort(void* _data, size_t _elementSize, size_t _noe, sortMethod _isSwapNeeded)
{
	void* swapBlock = NULL;
	void* end = NULL;
	
	if (NULL == _data || NULL == _isSwapNeeded)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (0 == _elementSize)
	{
		return ERR_INVALID_ELEMENT_SIZE;
	}
	if (0 == _noe || 1 == _noe)
	{
		return ERR_OK;
	}	
	
	swapBlock = malloc(_elementSize);
	if (NULL == swapBlock)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	
	end = (char*)_data + _elementSize * (_noe - 1);
	
	while (!Bobble((char*)_data, (char*)end, _elementSize, _isSwapNeeded, swapBlock))
	{
		end = (char*)end - _elementSize;
	}

	free(swapBlock);

	return ERR_OK;
}








