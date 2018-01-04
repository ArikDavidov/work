int g(int n)
{
    return n * n;
}

void f()
{
    static int s = g(5);
}

int main()
{
    f();
    f();    
    
    return 0;
}


