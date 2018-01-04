#include "StrManip.h"

#include <iostream>
using namespace advcpp::StrManip;

int main()
{
    char     str[] =  "Zero bug approach";
    wchar_t wstr[] = L"Zero Bug approach";

    Lower(str);
    Lower(wstr);
    
    std::cout << str  << std::endl;
    std::wcout << wstr << std::endl;

    Upper(str);
    Upper(wstr);
    
    std::cout << str  << std::endl;
    std::wcout << wstr << std::endl;
    
    return 0;
}


