#include <string.h>
#include <stdio.h>


static const int s_curvature = 1;

struct foo
{
	const char* bar;
} foo;


int main (int argc, char *argv[])
{
	foo.bar = "origin";
	int* pCurvaturfe = (int*)&s_curvature;
	*pCurvaturfe = 2;
	printf("%s\n", foo.bar);
	printf("%d\n", *pCurvaturfe);


    return 0;
}


