#include <iostream>

unsigned Factorial(unsigned _n)
{
    if (0 == _n)
    {
        return 1;
    }

    return _n * Factorial(_n - 1);
}


template <std::size_t N>
struct TemplateFactorial
{
        static const std::size_t fuct = N * TemplateFactorial<N - 1>::fuct;
};


template <>
struct TemplateFactorial<0>
{
    static const std::size_t fuct = 1;
};


int main ()
{
    std::cout << Factorial(4) << std::endl;
    
    std::cout << TemplateFactorial<33>::fuct << std::endl;
    
    
    return 0;
}


