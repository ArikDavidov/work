#include<stdio.h>
#include"DynPtrArr.h"

int main(){

	int i=0, tempNum, tempReturned;
	unsigned int option, tempUnsigned;
	DynArr* da;
	intPtr NPtr, tempPtr;
	int cont = 1;			// trigger to stop loop

	printf("Please enter the capacity:\n");
	scanf("%d", &tempUnsigned);
	da = CreateDA(tempUnsigned);
	if(da==NULL){
		printf("Malloc of dynamic array faild!\n");
		return -1;
	}

	while (cont) {
		printf("Choose option:     \n");
		printf("1: Insert          \n");
		printf("2: Insert by index \n");
		printf("3: Find            \n");
		printf("4: Remove          \n");
		printf("5: Print           \n");
		printf("Any another number - stop \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				printf("\nPlease enter an integer:\n");
				NPtr = malloc(sizeof(int));
				if(NPtr==0){
					printf("\nMalloc of NPtr faild!\n");			break;
				}
				scanf("%d", NPtr);
				tempReturned = Insert(da, NPtr);
				if(tempReturned==0){
					printf("\nrealloc function faild!\n");
				}													break;
			case 2:
				NPtr = malloc(sizeof(int));
				if(NPtr==0){
					printf("\nMalloc of NPtr faild!\n");			break;
				}
				printf("\nPlease enter an integer:\n");
				scanf("%d", NPtr);
				printf("\nPlease enter an index:\n");
				scanf("%d", &tempUnsigned);
				tempReturned = InsertByIndex(da, NPtr, tempUnsigned);
				if(tempReturned==0){
					printf("\nRealloc function faild!\n");
				}
				else if(tempReturned==-1){
					printf("\nThe index is too big!\n");
				}													break;
			case 3:
				printf("\nPlease enter an integer to find:\n");
				scanf("%d", &tempNum);
				tempPtr = Find(da, tempNum);
				if(tempPtr==NULL){
					printf("\nInteger was not found\n");			break;
				}
				printf("\nInteger was found\n");					break;
			case 4:
				printf("\nPlease enter an integer to remove:\n");
				scanf("%d", &tempNum);
				tempReturned = Remove(da, tempNum);
				if(tempReturned==0){
					printf("\nInteger was not found\n");			break;
				}
				printf("\nInteger was removed\n");					break;
			case 5:													break;
			default: cont = 0;										break;
		}
		printf("\nArray: ");
		for(i=0; i<(da->noe); ++i){
			printf("%d ", *(da->arr[i]));
		}
		printf("\n\n");
	}
	Destroy(da);
	return 0;
}

