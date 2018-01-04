#include <iostream>


template <std::size_t N>
struct Fib
{
    static const std::size_t fib = Fib<N - 1>::fib + Fib<N - 2>::fib;
};

template <>
struct Fib<0>
{
    static const std::size_t fib = 0;
};

template <>
struct Fib<1>
{
    static const std::size_t fib = 1;
};


int main ()
{

    std::cout << Fib<10>::fib << std::endl;
    return 0;
}


