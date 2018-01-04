#include<stdlib.h>
#include"DynArr.h"

DynArr* CreateDA(int capacity){
	DynArr* da;
	da = malloc(sizeof(DynArr));
	if (da==0){
		return 0;
	}
	da->noe=0;
	da->capacity = capacity;
	da->arr = malloc(da->capacity*sizeof(int));
	if(da->arr==0){
		return 0;
	}
	return da;
}

int Insert(DynArr* da, int N){
	int* tempip;
	if(da->noe==da->capacity){
		tempip = realloc(da->arr, da->capacity*2*sizeof(int));
		if(tempip==0){	
			return -1;
		}
		da->arr = tempip;
		da->capacity *=2;
	}
	da->arr[da->noe] = N;
	++(da->noe);
	return 0;
}

void Destroy(DynArr* da){
	free(da->arr);
	free(da);
}


