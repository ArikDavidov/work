#include <time.h>
#include <stdlib.h>

#define NUM_OF_ITEMS 1000
#define RANGE 10000
#define JUMPS_IN_RANGE 20

int* CreateRandArr(size_t _numOfItems)
{
	size_t i;
	
	/* Add one more place at the end of the array for the searched value. */
	arr = malloc((_numOfItems + 1) * sizeof(int));
	if (NULL == arr)
	{
		return NULL;
	}
	
	for (i = 0; i < _numOfItems; ++i)
	{
		arr[i] = rand() % RANGE;
	}
	
	return arr;	
}

size_t LiniarSearch(int* _arr, int _value)
{
	size_t i = 0;
	
	arr[NUM_OF_ITEMS] = _value;
	
	while (_value != arr[i])
	{	
		++i;
	}
	
	return i;
}



void swap(int* _arr, int* _itemInArr, size_t _numOfItems)
{
	int jump = _numOfItems / JUMPS_IN_RANGE;
	
	if (

}


int main()
{
	int* arr;
	
	arr = CreateRandArr(NUM_OF_ITEMS);
	
	
	
	
}



