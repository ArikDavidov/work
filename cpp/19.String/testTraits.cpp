#include "StrTraits.h"

#include <iostream>
using namespace advcpp;

int main()
{
    
    std::cout << StrTraits<char>::Length("Zero bug approach");
    std::cout << StrTraits<wchar_t>::Length(L"Zero bug approach");
        
    return 0;
}


