#ifndef DYNPTRARR_H
#define DYNPTRARR_H

#include<stdlib.h>

typedef int* intPtr;

typedef struct{
	intPtr* arr;
	int capacity;
	int noe;
}DynArr;

DynArr* CreateDA(int capacity);
int Insert(DynArr* da, intPtr N);
void Destroy(DynArr* da);

#endif
