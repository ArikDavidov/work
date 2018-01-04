#ifndef DYNARR_H
#define DYNARR_H

#include<stdlib.h>

typedef struct{
	int* arr;
	int capacity;
	int noe;
}DynArr;

DynArr* CreateDA(int capacity);
int Insert(DynArr* da, int N);
void Destroy(DynArr* da);

#endif
