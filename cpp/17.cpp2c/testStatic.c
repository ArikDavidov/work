
/*In C language objects with static storage duration have to be initialized with constant*/
/*expressions or with aggregate initializers containing constant expressions.*/
/*A "large" object is never a constant expression in C, even if the object is declared as const.*/
/*Moreover, in C language the term "constant" refers to literal*/
/*constants (like 1, 'a', 0xFF and so on) and enum members.*/
/*Const-qualified objects (of any type) are not constants in C language terminology.*/
/*They cannot be used in initializers of objects with static storage duration, regardless of their type.*/

/*For example, this is NOT a constant*/

/*const int N = 5; /* `N` is not a constant in C */*/

/*The above N would be a constant in C++, but it is not a constant in C. So, if you try doing*/

/*static int j = N; /* ERROR */*/

/*you will get the same error: an attempt to initialize a static object with a non-constant.*/
/*This is the reason why in C language we predominantly use #define to declare named constants,*/
/*and also resort to #define to create named aggregate initializers.*/


int g(int n)
{
    return n * n;
}

void f()
{
    static int s = g(5);    /* error: initializer element is not constant */
}

int main()
{
    f();
    f();    
    
    return 0;
}






