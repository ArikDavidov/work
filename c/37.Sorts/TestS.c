
#include "Sorts.h"
#include "Vector.h"

#include <stdio.h>
#include <stdlib.h> /* srand, rand */

#define IDENTICAL_VALUES {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}
#define ASCENDING_VALUES {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
#define DESCENDING_VALUES {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}

#define ARR_NUM_OF_ITEMS (sizeof(arr) / sizeof(int))

#define DEFAULT_NUM_OF_ITEMS (12)
#define MAX_RAND_NUM (300)
#define SEED (42)

typedef enum
{
	FAILED,
	PASSED
} TestResult;

int AscendingOrder(int _leftValue, int _rightValue)
{
	return (_leftValue > _rightValue) ? 1 : 0;
}
int DescendingOrder(int _leftValue, int _rightValue)
{
	return (_leftValue < _rightValue) ? 1 : 0;
}

void PrintTestResult(TestResult _res, char* _testName)
{	
	printf("%s: %s\n", (FAILED == _res) ? "FAILED" : "PASSED", _testName);
}

int* GenerateArrayRandNums(int _numOfItems, int _maxRandNum)
{	/* Random numbers array: {66, 240, 281, 141, 112, 58, 121, 240, 35, 143, 174, 143} */
	/* (_numOfItems = 12, _maxRandNum = 300, SEED = 42)	*/

	int* arr;
	int i;

	arr = malloc(_numOfItems * sizeof(int));

	srand(SEED);

	for (i = 0; i < _numOfItems; ++i)
	{
		arr[i] = rand() % _maxRandNum;
	}

	return arr;
}

Vector* CreateAndFillVector(int* _arr, size_t _numOfItems)
{
	int i;
	Vector* vec = NULL;	

	vec = VectorCreate(32, 16);
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

int VectorCompareToArray(Vector* _vec, int* _arr, size_t _len)
{
	int i, currentValue;

	for (i = 0; i < _len; ++i)
	{
		VectorGet(_vec, i, &currentValue);
		
		if (currentValue != _arr[i])
		{
			return 0;
		}
	}
	
	return 1;
}
/*
void TestInsertionSortTwoElementsToAscendingOrder();
{
	int arr[] = ;
}
*/
void TestInsertionSortIdenticalValuesToAscendingOrder()
{
	int arr[] = IDENTICAL_VALUES;
	Compare isSwapNeeded[] = {AscendingOrder, DescendingOrder};
	TestResult res = FAILED;
	Vector* vec = NULL;	
	
	vec = CreateAndFillVector(arr, ARR_NUM_OF_ITEMS);
	InsertionSort(vec, isSwapNeeded[0], 1, 1);
	
	if (VectorCompareToArray(vec, arr, ARR_NUM_OF_ITEMS))
	{
		res = PASSED;
	}
	
	PrintTestResult(res, "TestInsertionSortIdenticalValuesToAscendingOrder");
}

void TestInsertionSortAscendingValuesToAscendingOrder()
{
	int arr[] = ASCENDING_VALUES;
	int compareArr[] = DESCENDING_VALUES;
	Compare isSwapNeeded[] = {AscendingOrder, DescendingOrder};
	TestResult res = FAILED;
	Vector* vec = NULL;
	
	vec = CreateAndFillVector(arr, ARR_NUM_OF_ITEMS);

	InsertionSort(vec, isSwapNeeded[1], 1, 1);

	if (VectorCompareToArray(vec, compareArr, ARR_NUM_OF_ITEMS))
	{
		res = PASSED;
	}
	
	PrintTestResult(res, "TestInsertionSortAscendingValuesToAscendingOrder");
}

void TestInsertionSortDescendingValuesToAscendingOrder()
{
	int arr[] = DESCENDING_VALUES;
	int compareArr[] = ASCENDING_VALUES;
	Compare isSwapNeeded[] = {AscendingOrder, DescendingOrder};
	TestResult res = FAILED;
	Vector* vec = NULL;
	
	vec = CreateAndFillVector(arr, ARR_NUM_OF_ITEMS);

	InsertionSort(vec, isSwapNeeded[0], 1, 1);

	if (VectorCompareToArray(vec, compareArr, ARR_NUM_OF_ITEMS))
	{
		res = PASSED;
	}
	
	PrintTestResult(res, "TestInsertionSortDescendingValuesToAscendingOrder");
}

void TestInsertionSortRandomElementsToAscendingOrder()
{
	int* arr;
	int compareArr[] = {35, 58, 66, 112, 121, 141, 143, 143, 174, 240, 240, 281};
	Compare isSwapNeeded[] = {AscendingOrder, DescendingOrder};
	TestResult res = FAILED;
	Vector* vec = NULL;

	arr = GenerateArrayRandNums(DEFAULT_NUM_OF_ITEMS, MAX_RAND_NUM);
	vec = CreateAndFillVector(arr, DEFAULT_NUM_OF_ITEMS);

	InsertionSort(vec, isSwapNeeded[0], 1, 1);

	if (VectorCompareToArray(vec, compareArr, DEFAULT_NUM_OF_ITEMS))
	{
		res = PASSED;
	}
	
	PrintTestResult(res, "TestInsertionSortRandomElementsToAscendingOrder");
}

int main()
{
	
	TestQuickSortOneElement(); 
	 TestQuickSortTwoElements();
	 TestQuickSortIdenticalValues();
	 TestQuickSortAscendingValues();
	 TestQuickSortDescendingValues();
	 TestQuickSortRandomElements();
	 

	TestInsertionSortOneElementToAscendingOrder();
	TestInsertionSortTwoElementsToAscendingOrder();
	TestInsertionSortIdenticalValuesToAscendingOrder();
	TestInsertionSortAscendingValuesToAscendingOrder();
	TestInsertionSortDescendingValuesToAscendingOrder();
	TestInsertionSortRandomElementsToAscendingOrder();

	return 0;
}


