#include<stdlib.h>
#include"DynPtrArr.h"

DynArr* CreateDA(int capacity){
	DynArr* da;
	da = malloc(sizeof(DynArr));
	if (da==0){
		return 0;
	}
	da->noe=0;
	da->capacity = capacity;
	da->arr = malloc(da->capacity*sizeof(intPtr));
	if(da->arr==0){
		return 0;
	}
	return da;
}

int Insert(DynArr* da, intPtr N){
	intPtr* tempip;
	if(da->noe==da->capacity){
		tempip = realloc(da->arr, da->capacity*2*sizeof(intPtr));
		if(tempip==0){	
			return 0;
		}
		da->arr = tempip;
		da->capacity *=2;
	}
	da->arr[da->noe] = N;
	++(da->noe);
	return 1;
}

void Destroy(DynArr* da){
	int i;
	for(i=0; i<(da->noe); ++i){
		free(da->arr[i]);
	}
	free(da->arr);
	free(da);
}


