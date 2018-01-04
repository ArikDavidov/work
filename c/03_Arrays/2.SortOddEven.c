#include<stdio.h>
#define SIZE 8

void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int sort(int* a, int size){
	int i=0, j=0, numEven=0;
	for(i=0; i<SIZE-1; ++i){
		for(j=i; j>-1; --j){
			if(a[j]%2!=0 && a[j+1]%2==0){
				swap(&a[j], &a[j+1]);
				numEven = j;
			}
			else{
				break;
			}
		}
	}
	return numEven+1;
}

int main(){
	
	int arr[SIZE], i;
	for(i=0; i<SIZE; ++i){
		printf("Please enter a number:\n");
		scanf("%d",&arr[i]);
	}

	printf("\nSorted: %d\n", sort(arr, SIZE));
	
	return 0;
}

