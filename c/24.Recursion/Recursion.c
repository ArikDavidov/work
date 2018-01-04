#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHESS_BOARD_SIZE 8

int* RecursiveBinarySearch(int* _lowPtr, int* _highPtr, int _searchValue)
{
	int* midlePtr = NULL;
	
	if (_searchValue == *_lowPtr)
	{
		return _lowPtr;
	}
	if (_searchValue == *_highPtr)
	{
		return _highPtr;
	}
	if(_lowPtr == _highPtr)
	{
		return NULL;
	}
	midlePtr += (_highPtr - _lowPtr)/2;
	if(_searchValue == *midlePtr)
	{
		return midlePtr;
	}
	if(_searchValue < *midlePtr)
	{
		_highPtr = midlePtr - 1;
	}
	else
	{
		_lowPtr = midlePtr + 1;
	}
	
	return RecursiveBinarySearch(_lowPtr, _highPtr, _searchValue);
}

int* BinarySearch(int* _lowPtr, int* _highPtr, int _searchValue)
{
	if (_searchValue < *_lowPtr || _searchValue > *_highPtr)
	{
		return NULL;
	}
	return RecursiveBinarySearch(_lowPtr, _highPtr, _searchValue);
}

void swap(char* _char1, char* _char2)
{
	char tempChar;
	tempChar = *_char1;
	*_char1 = *_char2;
	*_char2 = tempChar;	
}

int RecursiveStringReverse(char* _str, unsigned int _length)
{	
	if (1 == _length)
	{
		return 0;
	}
	if (0 == _length)
	{
		return 0;
	}
	swap(_str, &_str[_length - 1]);
	
	return RecursiveStringReverse(_str + 1, _length - 2);
}

int CheckInterference(int* _arr, int _currentRow, int _currentColumn)
{
	int i, columnDistance, rowDistance, ret = 0;

	for (i = 0; i < _currentRow; ++i)
	{
		columnDistance = abs(_currentColumn - _arr[i]);
		if (0 == columnDistance)	/* If on the same column */
		{
			ret = 1;
			break;
		}
		rowDistance   = abs(_currentRow - i);
		if (rowDistance == columnDistance)	/* If on the same diagonal */
		{
			ret = 1;
			break;
		}
	}
	return ret;
}

int EightQueens(int* _arr, int _currentRow, int _currentColumn)
{
	int ret;

	/* Completed insertion of all queens */
	if(CHESS_BOARD_SIZE == _currentRow)	
	{
		return 1;
	}
	/* Reached end of row (failure)*/
	if(CHESS_BOARD_SIZE == _currentColumn)
	{
		_arr[_currentRow] = 0;
		return 0;
	}
	if (0 == CheckInterference(_arr, _currentRow, _currentColumn))
	{
		_arr[_currentRow] = _currentColumn;
		ret = EightQueens(_arr, _currentRow + 1, _arr[_currentRow + 1]);
		if (1 == ret)
		{
			return 1;
		}
	}
	return EightQueens(_arr, _currentRow, _currentColumn + 1);
}

void PrintSolution(int* _arr, int _solutionNumber)
{
	int row, column;	

	printf("\nSolution %d:\n", _solutionNumber);
	for (row = 0; row < CHESS_BOARD_SIZE; ++row)
	{
		printf(" %d", _arr[row]);
	}
	printf("\n\n ");
	for (row = 0; row < CHESS_BOARD_SIZE; ++row)
	{
		printf(" %d", row);
	}
	printf("\n");
	for (row = 0; row < CHESS_BOARD_SIZE; ++row)
	{
		printf("%d|", row);
		for (column = 0; column < CHESS_BOARD_SIZE; ++column)
		{
			if (_arr[row] == column)
			{
				printf("Q|");
			}
			else
			{
				printf("_|");					
			}
		}
		printf("\n");
	}	
}








