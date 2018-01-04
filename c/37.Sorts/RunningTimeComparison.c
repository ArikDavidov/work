#include "Sorts.h"
#include "Vector.h"
#include "ADTErr.h"

#include <stdio.h>
#include <stdlib.h>	/* size_t */
#include <time.h>	/* clock_t, clock, CLOCKS_PER_SEC */

#define NUM_OF_DIGITS 5

int AscendingOrder(int _leftValue, int _rightValue)
{
	return (_leftValue > _rightValue) ? 1 : 0;
}
int DescendingOrder(int _leftValue, int _rightValue)
{
	return (_leftValue < _rightValue) ? 1 : 0;
}

int* GenerateArrayRandNums(size_t _numOfItems)
{
	int* arr;
	size_t i;

	arr = malloc(_numOfItems * sizeof(int));
	
	for (i = 0; i < _numOfItems; ++i)
	{
		arr[i] = rand() % 50000;
	}

	return arr;
}

int* GenerateArrayAscendingNums(size_t _numOfItems)
{
	int* arr;
	size_t i;

	arr = malloc(_numOfItems * sizeof(int));
	
	for (i = 0; i < _numOfItems; ++i)
	{
		arr[i] = i;
	}

	return arr;
}

int* GenerateArrayDescendingNums(size_t _numOfItems)
{
	int* arr;
	size_t i;

	arr = malloc(_numOfItems * sizeof(int));
	
	for (i = 0; i < _numOfItems; ++i)
	{
		arr[i] = _numOfItems - i;
	}

	return arr;
}

Vector* CreateAndFillVector(int* _arr, size_t _numOfItems)
{
	size_t i;
	Vector* vec = NULL;	

	vec = VectorCreate(1024, 1024);
	if (NULL == vec)
	{
		return NULL;
	}
	
	for (i = 0; i < _numOfItems; ++i)
	{
		VectorAdd(vec, _arr[i]);
	}

	return vec;
}

float MeasureRunningTime(Vector* _vec, Sorts _SortingFunc)
{
	clock_t t;
	
	t = clock();	
	
	_SortingFunc(_vec);
	
	t = clock() - t;
	
	return ((float)t)/CLOCKS_PER_SEC;
}

float MeasureRunningTimeInsertion(Vector* _vec)
{
	clock_t t;
	
	t = clock();	
	
	InsertionSort(_vec, AscendingOrder, 1, 1);
	
	t = clock() - t;
	
	return ((float)t)/CLOCKS_PER_SEC;	
}

float MeasureRunningTimeShell(Vector* _vec)
{
	clock_t t;
	
	t = clock();
	
	ShellSort(_vec, AscendingOrder);
	
	t = clock() - t;
	
	return ((float)t)/CLOCKS_PER_SEC;	
}

float MeasureRunningTimeCounting(Vector* _vec, int _maxValue)
{
	clock_t t;
	
	t = clock();
	
	CountingSort(_vec, _maxValue);
	
	t = clock() - t;
	
	return ((float)t)/CLOCKS_PER_SEC;
}

float MeasureRunningTimeRadix(Vector* _vec, int _nDigits)
{
	clock_t t;
	
	t = clock();
	
	RadixSort(_vec, _nDigits);
	
	t = clock() - t;
	
	return ((float)t)/CLOCKS_PER_SEC;
}

float TestRunningTimeRand(size_t _numOfItems, Sorts _SortingFunc)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayRandNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTime(vec, _SortingFunc);

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeAscending(size_t _numOfItems, Sorts _SortingFunc)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayAscendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTime(vec, _SortingFunc);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeDescending(size_t _numOfItems, Sorts _SortingFunc)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayDescendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTime(vec, _SortingFunc);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeInsertionAscending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayAscendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	
	res = MeasureRunningTimeInsertion(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeInsertionDescending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayDescendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	
	res = MeasureRunningTimeInsertion(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeInsertionRand(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayRandNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	
	res = MeasureRunningTimeInsertion(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeShellAscending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayAscendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTimeShell(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeShellDescending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayDescendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTimeShell(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeShellRand(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayRandNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);

	res = MeasureRunningTimeShell(vec);	

	VectorDestroy(vec);
	free(arr);

	return res;
}


float TestRunningTimeCountingAscending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	size_t i;
	int max = 0;
	float res;
	
	arr = GenerateArrayAscendingNums(_numOfItems);
	for (i = 0; i < _numOfItems; ++i)
	{
		max = (max > arr[i]) ? max : arr[i];
	}
	vec = CreateAndFillVector(arr, _numOfItems);
	res = MeasureRunningTimeCounting(vec, max);

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeCountingDescending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	size_t i;
	int max = 0;
	float res;
	
	arr = GenerateArrayDescendingNums(_numOfItems);
	for (i = 0; i < _numOfItems; ++i)
	{
		max = (max > arr[i]) ? max : arr[i];
	}
	vec = CreateAndFillVector(arr, _numOfItems);
	res = MeasureRunningTimeCounting(vec, max);

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeCountingRand(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	size_t i;
	int max = 0;
	float res;
	
	arr = GenerateArrayRandNums(_numOfItems);
	for (i = 0; i < _numOfItems; ++i)
	{
		max = (max > arr[i]) ? max : arr[i];
	}
	vec = CreateAndFillVector(arr, _numOfItems);;
	res = MeasureRunningTimeCounting(vec, max);	

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeRadixAscending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayAscendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	res = MeasureRunningTimeRadix(vec, NUM_OF_DIGITS);

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeRadixDescending(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayDescendingNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	res = MeasureRunningTimeRadix(vec, NUM_OF_DIGITS);

	VectorDestroy(vec);
	free(arr);

	return res;
}

float TestRunningTimeRadixRand(size_t _numOfItems)
{
	int* arr = NULL;
	Vector* vec = NULL;
	float res;
	
	arr = GenerateArrayRandNums(_numOfItems);
	vec = CreateAndFillVector(arr, _numOfItems);
	res = MeasureRunningTimeRadix(vec, NUM_OF_DIGITS);
	
	VectorDestroy(vec);
	free(arr);

	return res;
}

int main()
{
	printf("\n1,000 items:\n");
	printf("    BobbleSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(1000, BobbleSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(1000, BobbleSort));
	printf("        Typical: %f\n", TestRunningTimeRand(1000, BobbleSort));
	printf("    ShakeSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(1000, ShakeSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(1000, ShakeSort));
	printf("        Typical: %f\n", TestRunningTimeRand(1000, ShakeSort));
	printf("    QuickSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRand(1000, QuickSort));
	printf("        Worst:   %f\n", TestRunningTimeAscending(1000, QuickSort));
	printf("        Typical: %f\n", TestRunningTimeRand(1000, QuickSort));
	printf("    InsertionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeInsertionAscending(1000));
	printf("        Worst:   %f\n", TestRunningTimeInsertionDescending(1000));
	printf("        Typical: %f\n", TestRunningTimeInsertionRand(1000));
	printf("    ShellSort:\n");
	printf("        Best:    %f\n", TestRunningTimeShellAscending(1000));
	printf("        Worst:   %f\n", TestRunningTimeShellDescending(1000));
	printf("        Typical: %f\n", TestRunningTimeShellRand(1000));
	/*
	printf("    SelectionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(1000, SelectionSort);
	printf("        Worst:   %f\n", TestRunningTimeDescending(1000, SelectionSort);
	printf("        Typical: %f\n", TestRunningTimeRand(1000, SelectionSort));
	*/
	printf("    MergeSortRec:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(10, MergeSortRec));
	printf("        Worst:   %f\n", TestRunningTimeDescending(10, MergeSortRec));
	printf("        Typical: %f\n", TestRunningTimeRand(10, MergeSortRec));
	printf("    CountingSort:\n");
	printf("        Best:    %f\n", TestRunningTimeCountingAscending(1000));
	printf("        Worst:   %f\n", TestRunningTimeCountingDescending(1000));
	printf("        Typical: %f\n", TestRunningTimeCountingRand(1000));
	printf("    RadixSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRadixAscending(1000));
	printf("        Worst:   %f\n", TestRunningTimeRadixDescending(1000));
	printf("        Typical: %f\n", TestRunningTimeRadixRand(1000));	

	printf("\n10,000 items:\n");
	printf("    BobbleSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(10000, BobbleSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(10000, BobbleSort));
	printf("        Typical: %f\n", TestRunningTimeRand(10000, BobbleSort));
	printf("    ShakeSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(10000, ShakeSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(10000, ShakeSort));
	printf("        Typical: %f\n", TestRunningTimeRand(10000, ShakeSort));
	printf("    QuickSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRand(10000, QuickSort));
	printf("        Worst:   %f\n", TestRunningTimeAscending(10000, QuickSort));
	printf("        Typical: %f\n", TestRunningTimeRand(10000, QuickSort));
	printf("    InsertionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeInsertionAscending(10000));
	printf("        Worst:   %f\n", TestRunningTimeInsertionDescending(10000));
	printf("        Typical: %f\n", TestRunningTimeInsertionRand(10000));
	printf("    ShellSort:\n");
	printf("        Best:    %f\n", TestRunningTimeShellAscending(10000));
	printf("        Worst:   %f\n", TestRunningTimeShellDescending(10000));
	printf("        Typical: %f\n", TestRunningTimeShellRand(10000));
	/*
	printf("    SelectionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(10000, SelectionSort);
	printf("        Worst:   %f\n", TestRunningTimeDescending(10000, SelectionSort);
	printf("        Typical: %f\n", TestRunningTimeRand(10000, SelectionSort));
	*/
	printf("    MergeSortRec:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(10000, MergeSortRec));
	printf("        Worst:   %f\n", TestRunningTimeDescending(10000, MergeSortRec));
	printf("        Typical: %f\n", TestRunningTimeRand(10000, MergeSortRec));
	printf("    CountingSort:\n");
	printf("        Best:    %f\n", TestRunningTimeCountingAscending(10000));
	printf("        Worst:   %f\n", TestRunningTimeCountingDescending(10000));
	printf("        Typical: %f\n", TestRunningTimeCountingRand(10000));
	printf("    RadixSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRadixAscending(10000));
	printf("        Worst:   %f\n", TestRunningTimeRadixDescending(10000));
	printf("        Typical: %f\n", TestRunningTimeRadixRand(10000));		

	printf("\n50,000 items:\n");
	printf("    BobbleSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(50000, BobbleSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(50000, BobbleSort));
	printf("        Typical: %f\n", TestRunningTimeRand(50000, BobbleSort));
	printf("    ShakeSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(50000, ShakeSort));
	printf("        Worst:   %f\n", TestRunningTimeDescending(50000, ShakeSort));
	printf("        Typical: %f\n", TestRunningTimeRand(50000, ShakeSort));
	printf("    QuickSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRand(50000, QuickSort));
	printf("        Worst:   %f\n", TestRunningTimeAscending(50000, QuickSort));
	printf("        Typical: %f\n", TestRunningTimeRand(50000, QuickSort));
	printf("    InsertionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeInsertionAscending(50000));
	printf("        Worst:   %f\n", TestRunningTimeInsertionDescending(50000));
	printf("        Typical: %f\n", TestRunningTimeInsertionRand(50000));
	printf("    ShellSort:\n");
	printf("        Best:    %f\n", TestRunningTimeShellAscending(50000));
	printf("        Worst:   %f\n", TestRunningTimeShellDescending(50000));
	printf("        Typical: %f\n", TestRunningTimeShellRand(50000));
	/*
	printf("    SelectionSort:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(50000, SelectionSort);
	printf("        Worst:   %f\n", TestRunningTimeDescending(50000, SelectionSort);
	printf("        Typical: %f\n", TestRunningTimeRand(50000, SelectionSort));
	*/
	printf("    MergeSortRec:\n");
	printf("        Best:    %f\n", TestRunningTimeAscending(50000, MergeSortRec));
	printf("        Worst:   %f\n", TestRunningTimeDescending(50000, MergeSortRec));
	printf("        Typical: %f\n", TestRunningTimeRand(50000, MergeSortRec));
	printf("    CountingSort:\n");
	printf("        Best:    %f\n", TestRunningTimeCountingAscending(50000));
	printf("        Worst:   %f\n", TestRunningTimeCountingDescending(50000));
	printf("        Typical: %f\n", TestRunningTimeCountingRand(50000));
	printf("    RadixSort:\n");
	printf("        Best:    %f\n", TestRunningTimeRadixAscending(50000));
	printf("        Worst:   %f\n", TestRunningTimeRadixDescending(50000));
	printf("        Typical: %f\n", TestRunningTimeRadixRand(50000));	
	
	return 0;
}



