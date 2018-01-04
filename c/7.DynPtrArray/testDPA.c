#include<stdio.h>
#include"DynPtrArr.h"

int main(){
	int i=0, tempNum, tempCapacity;
	int tempIns;
	DynArr* da;
	intPtr NPtr;

	printf("Please enter the number of integers:\n");
	scanf("%d", &tempCapacity);
	da = CreateDA(tempCapacity);
	if(da==0){
		printf("Malloc of da faild!\n");
		return -1;
	}

	while(1){
		printf("Please enter an integer:\n");
		scanf("%d", &tempNum);
		if(tempNum==666){
			break;
		}
		NPtr = malloc(sizeof(int));
		if(NPtr==0){
			printf("Malloc of NPtr faild!\n");
			return -1;
		}
		*NPtr=tempNum;
		tempIns = Insert(da, NPtr);
		if(tempIns==0){
			printf("realloc function faild!\n");
			continue;
		}
		printf("Array: ");
		for(i=0; i<(da->noe); ++i){
			printf("%d ", *(da->arr[i]));
		}
		printf("\n");
	}
	Destroy(da);
	return 0;
}

