#include<stdlib.h>
#include"DynPtrArr.h"

DynArr* CreateDA(unsigned int capacity){
	DynArr* da;
	DynArr* res=NULL;

	da = malloc(sizeof(DynArr));
	if (da!=0){
		da->noe=0;
		da->capacity = capacity;
		da->arr = malloc(da->capacity*sizeof(intPtr));
		if(da->arr!=0){
			res=da;
		}
		else{
			free(da);
		}
	}
	return res;
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

int InsertByIndex(DynArr* da, intPtr N, unsigned int index){
	int i;
	intPtr* tempip;

	if(da->noe==da->capacity){
		tempip = realloc(da->arr, da->capacity*2*sizeof(intPtr));
		if(tempip==0){	
			return 0;
		}
		da->arr = tempip;
		da->capacity *=2;
	}	
	if(index==da->noe){
		Insert(da, N);
	}
	else if(index>(da->noe)){
		return -1;
	}
	else{
		for(i=(da->noe); i>index; --i){
			da->arr[i] = da->arr[i-1];
		}
		da->arr[index] = N;
		++(da->noe);
		return 1;
	}
}

intPtr Find(DynArr* da, int N){
	int i=0;
	intPtr res=NULL;

	if(da!=NULL){
		for(i=0; i<(da->noe); ++i){
			if(*(da->arr[i])==N){
				res = da->arr[i];
				break;
			}
		}
	}
	return res;
}

int getIndex(DynArr* da, intPtr NPtr){
	int i=0, res = -1;
	if(da!=NULL && NPtr!=NULL){
		for(i=0; i<(da->noe); ++i){
			if((da->arr[i])==NPtr){
				res=i;
			}
		}
	}
	return res;
}

int Remove(DynArr* da, int N){
	int i=0, index, res=0;
	intPtr NPtr;

	if(da!=NULL){
		NPtr = Find(da, N);
		if(NPtr!=NULL){
			index = getIndex(da, NPtr);
			for(i=index; i<(da->noe)-1; ++i){
				da->arr[i] = da->arr[i+1];		
			}
			free(NPtr);
			--(da->noe);
			res=1;
		}
	}
	return res;
}

void Destroy(DynArr* da){	
	if(da==NULL){
		return;
	}
	int i;
	for(i=0; i<(da->noe); ++i){
		free(da->arr[i]);
	}
	free(da->arr);
	free(da);
}


