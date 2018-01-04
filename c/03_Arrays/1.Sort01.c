#include<stdio.h>
#include<stdlib.h>

void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int* sort(int* a, int size){
	int i=0, j=size-1;
	while(1){
		while(a[i]==0){
			if(i==j){
				return a;
			}
			++i;
		}
		while(a[j]==1){
			if(i==j){
				return a;
			}
			--j;
		}	
		swap(&a[i], &a[j]);
	}
}

int main(){
	
	int i, sizeOfArray;
	int* array;

	printf("Please enter size of array:\n");
	scanf("%d", &sizeOfArray);
	array = malloc(sizeOfArray*sizeof(int));
	if(array==0){
		return -1;
	}
	
	for(i=0; i<sizeOfArray; ++i){		
		printf("Please enter 0 or 1:\n");
		scanf("%d", &array[i]);
		if(array[i] != 0 && array[i] != 1){
			printf("Illegal input\n");
			return -1;
		}
	}

	sort(array, sizeOfArray);

	printf("\nSorted:\n");
	for(i=0; i<sizeOfArray; ++i){
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	
	return 0;
}

