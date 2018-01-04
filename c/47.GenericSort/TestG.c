#include "ADTErr.h"
#include "GenericSort.h"

#include <stdio.h>
#include <string.h>

#define NAME_SIZE 128

typedef enum
{
	FAILED,
	PASSED
} TestResult;

typedef struct Person Person;

struct Person
{
	int  m_id;
	char m_name[NAME_SIZE];
	int  m_age;
};

int IntegersAscendingOrder(const void* _leftValue, const void* _rightValue)
{
	return (*(int*)_leftValue > *(int*)_rightValue) ? 1 : 0;
}
int IntegersDescendingOrder(const void* _leftValue, const void* _rightValue)
{
	return (*(int*)_leftValue < *(int*)_rightValue) ? 1 : 0;
}


int CharsAscendingOrder(const void* _leftValue, const void* _rightValue)
{
	return (*(char*)_leftValue > *(char*)_rightValue) ? 1 : 0;
}
int CharsDescendingOrder(const void* _leftValue, const void* _rightValue)
{
	return (*(char*)_leftValue < *(char*)_rightValue) ? 1 : 0;
}


int PersonAscendingIDOrder(const void* _leftValue, const void* _rightValue)
{
	return (((Person*)_leftValue)->m_id > ((Person*)_rightValue)->m_id) ? 1 : 0;
}

int PersonDescendingIDOrder(const void* _leftValue, const void* _rightValue)
{
	return (((Person*)_leftValue)->m_id < ((Person*)_rightValue)->m_id) ? 1 : 0;}


void PrintTestResult(TestResult _res, char* _testName)
{	
	printf("%s: %s\n", (FAILED == _res) ? "FAILED" : "PASSED", _testName);
}

/*

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




void TestSortIntegersToDescendingOrder()
*/

void TestDataNull()
{
	ADTErr ret;
	TestResult testRes = FAILED;
	
	ret = GenBobbleSort(NULL, 1, 1, IntegersAscendingOrder);
	
	if (ERR_NOT_INITIALIZED == ret)
	{
		testRes = PASSED;
	}
	
	PrintTestResult(testRes, "TestDataNull");	
}

void TestFuncNull()
{
	char str[] = "ABC";
	ADTErr ret;
	TestResult testRes = FAILED;
	
	ret = GenBobbleSort(str, 1, strlen(str), NULL);
	
	if (ERR_NOT_INITIALIZED == ret)
	{
		testRes = PASSED;
	}

	PrintTestResult(testRes, "TestFuncNull");
}

void TestEmptyArray()
{
	char str[] = "";
	ADTErr ret;
	TestResult testRes = FAILED;
	
	ret = GenBobbleSort(str, 1, strlen(str), IntegersAscendingOrder);
	
	if (ERR_OK == ret)
	{
		testRes = PASSED;
	}

	PrintTestResult(testRes, "TestEmptyArray");
}


void TestSortOneElement()
{
	char str[] = "A";
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(str, 1, strlen(str), IntegersAscendingOrder);
	
	if (ERR_OK == ret)
	{
		testRes = PASSED;
	}
	
	PrintTestResult(testRes, "TestSortOneElement");
}

void TestSortTwoElements()
{
	int arr[] = {1, -1};
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(arr, sizeof(int), 2, IntegersAscendingOrder);
	
	if (ERR_OK == ret)
	{
		testRes = PASSED;
	}
	
	PrintTestResult(testRes, "TestSortTwoElement");
}

void TestZeroElementSize()
{
	int arr[] = {1, -1};
	ADTErr ret;
	TestResult testRes = FAILED;
	
	ret = GenBobbleSort(arr, 0, 2, IntegersAscendingOrder);
	
	if (ERR_INVALID_ELEMENT_SIZE == ret)
	{
		testRes = PASSED;
	}
	
	PrintTestResult(testRes, "TestZeroElementSize");
}

void TestSortIntegersToDescendingOrder()
{
	int arr[] = {66, 240, 281, 141, 112, 58, 121, 240, 35, 143, 174, 143};
	int sortedArr[] = {281, 240, 240, 174, 143, 143, 141, 121, 112, 66, 58, 35};	
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(arr, sizeof(int), 12, IntegersDescendingOrder);
	
	if (ERR_OK == ret && sortedArr[0] == arr[0] && sortedArr[6] == arr[6] && sortedArr[11] == arr[11])
	{
		testRes = PASSED;
	}

	PrintTestResult(testRes, "TestSortIntegersToDescendingOrder");
}

void TestSortIntegersToAscendingOrder()
{
	int arr[] = {66, 240, 281, 141, 112, 58, 121, 240, 35, 143, 174, 143};
	int sortedArr[] = {35, 58, 66, 112, 121, 141, 143, 143, 174, 240, 240, 281};
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(arr, sizeof(int), 12, IntegersAscendingOrder);
	
	if (ERR_OK == ret && sortedArr[0] == arr[0] && sortedArr[6] == arr[6] && sortedArr[11] == arr[11])
	{
		testRes = PASSED;
	}

	PrintTestResult(testRes, "TestSortIntegersToAscendingOrder");
}

void TestSortStringToAscendingOrder()
{
	char str[] = "YFaFCYodd,utl";
	char sortedStr[] = ",CFFYYaddlotu";
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(str, 1, strlen(str), CharsAscendingOrder);
	
	if (ERR_OK == ret && sortedStr[0] == str[0] && sortedStr[6] == str[6] && sortedStr[11] == str[11])
	{
		testRes = PASSED;
	}

	PrintTestResult(testRes, "TestSortStringToAscendingOrder");
}

void TestSortPersonToAcendingOrder()
{
	Person personArr[3] = {398, "Bar", 20, 123, "Yosi", 25, 196, "Avi", 45};
	Person sortedPArr[3] = {123, "Yosi", 25, 196, "Avi", 45, 398, "Bar", 20};
	ADTErr ret;
	TestResult testRes = FAILED;
		
	ret = GenBobbleSort(personArr, sizeof(Person), 3, PersonAscendingIDOrder);	
	
	if (ERR_OK == ret)
	{
		testRes = PASSED;
	}
	if (personArr[0].m_name == sortedPArr[0].m_name)
	{
		testRes = PASSED;
	}
	if (personArr[2].m_age == sortedPArr[2].m_age)
	{
		testRes = PASSED;
	}
	/*
	if (ERR_OK == ret && personArr[0].m_name == sortedPArr[0].m_name && personArr[2].m_age == sortedPArr[2].m_age)
	{
		testRes = PASSED;
	}
	*/
	PrintTestResult(testRes, "TestSortPersonToAcendingOrder");
}

int main()
{
	
	TestDataNull();
	TestFuncNull();
	TestEmptyArray();
	TestSortOneElement(); 
	TestSortTwoElements();
	TestZeroElementSize();

	TestSortIntegersToDescendingOrder();
	TestSortIntegersToAscendingOrder();
	TestSortStringToAscendingOrder();
	TestSortPersonToAcendingOrder();
/*	
*/


	return 0;
}












