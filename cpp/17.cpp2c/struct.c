#include <stdio.h>

typedef struct MyStruct
{
}MyStruct;

int
main (int argc, char *argv[])
{
    MyStruct a;
    MyStruct b;
    
    printf("%p\n", (void*)&a);
    printf("%p\n", (void*)&b);

    return 0;
}

