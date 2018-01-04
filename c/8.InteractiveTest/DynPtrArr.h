#ifndef DYNPTRARR_H
#define DYNPTRARR_H

#include<stdlib.h>

typedef int* intPtr;

typedef struct{
	intPtr* arr;
	int capacity;
	int noe;
}DynArr;

DynArr* CreateDA      (unsigned int capacity);
int     Insert        (DynArr* da, intPtr N);
int     InsertByIndex (DynArr* da, intPtr N, unsigned int index);
intPtr  Find          (DynArr* da, int N);
int     Remove        (DynArr* da, int N);
void    Destroy       (DynArr* da);

#endif
