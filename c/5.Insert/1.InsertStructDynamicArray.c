#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int* arr;
	int capacity;
	int noe;
}DynArr;

int* Insert(DynArr* da, int N){
	int* tempip;
	if(da->noe==da->capacity){
		tempip = realloc(da->arr, da->capacity*2*sizeof(int));
		if(tempip==0){			
			return tempip;
		}
		da->arr = tempip;
		da->capacity *=2;
	}
	da->arr[da->noe] = N;
	++(da->noe);
	return da->arr;
}

int main(){	
	DynArr da;
	int i=0, tempNum;
	int* tempip;

	da.noe=0;
	printf("Please enter the number of integers:\n");
	scanf("%d", &(da.capacity));
	da.arr = malloc(da.capacity*sizeof(int));
	if(da.arr==0){
		return -1;
	}

	while(1){
		printf("Please enter an integer:\n");
		scanf("%d", &tempNum);
		if(tempNum==666){
			break;
		}
		tempip = Insert(&da, tempNum);		
		if(tempip==0){
			printf("realloc function faild!\n");
			continue;
		}
		printf("Array: ");
		for(i=0; i<da.noe; ++i){
			printf("%d ", da.arr[i]);
		}
		printf("\n");
	}
	free(da.arr);
	return 0;
}

