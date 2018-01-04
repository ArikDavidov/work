#include <stdio.h>

void swap(int* x, int* y)
{
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
}

int* sort(int* a, int size)
{
	int i=0, j=0;
	
	for(i=0;i<SIZE-1; ++i)
	{
		for(j=i; j>-1; --j)
		{
			if(a[j]>a[j+1])
			{
				swap(&a[j], &a[j+1]);
			}
			else
			{
				break;
			}
		}
	}
	return a;
}

int main(){
	
	int i;
	int arr[] = {3, 11, 631, 0, 99, 737, 2, 54, 80, 101, 200};

	len = sizeof(arr) / sizeof(int);
	
	sort(arr, len));

	printf("\nSorted:");
	for(i = 0; i < len; ++i)
	{
		printf(" %d", arr[i]);
	}
	printf("\n");
	
	return 0;
}

