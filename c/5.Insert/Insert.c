#include<stdio.h>
#include<stdlib.h>

int* Insert(int* Arr, int N, int* NOE, int* capacity){
	int* tempip;
	if(*NOE==*capacity){
		tempip = realloc(Arr, *capacity*2*sizeof(int));
		if(tempip==0){			
			return tempip;
		}
		Arr = tempip;
		*capacity *=2;
	}
	Arr[*NOE] = N;
	++(*NOE);
	return Arr;
}

int main(){	
	int i=0, NOE=0, capacity, tempNum;
	int* Arr, *tempip;

	printf("Please enter the number of integers:\n");
	scanf("%d", &capacity);
	Arr = malloc(capacity*sizeof(int));
	if(Arr==0){
		return -1;
	}
	while(1){
		printf("Please enter an integer:\n");
		scanf("%d", &tempNum);
		if(tempNum==666){
			break;
		}
		tempip = Insert(Arr, tempNum, &NOE, &capacity);
		if(tempip==0){
			printf("realloc function faild!\n");
			continue;
		}
		printf("Array: ");
		for(i=0; i<NOE; ++i){
			printf("%d ", Arr[i]);
		}
		printf("\n");
	}
	free(Arr);	
	return 0;
}

