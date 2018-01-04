//#include <stdio.h>
#include "StrManip.h"

#include <ctype.h>
#include <wctype.h>


namespace advcpp
{
namespace StrManip
{


template <>
void Lower<char>(char* _str)
{
    for (int i = 0; _str[i]; ++i)
    {
        _str[i] = (char)tolower(_str[i]);
    }
}

template <>
void Upper<char>(char* _str)
{
    for (int i = 0; _str[i]; ++i)
    {
        _str[i] = (char)toupper(_str[i]);
    }
}

template <>
void Lower<wchar_t>(wchar_t* _str)
{
    for (int i = 0; _str[i]; ++i)
    {
        _str[i] = towlower(_str[i]);
    }
}

template <>
void Upper<wchar_t>(wchar_t* _str)
{
    for (int i = 0; _str[i]; ++i)
    {
        _str[i] = towupper(_str[i]);
    }
}



}   // namespace StrManip

}   // namespace advcpp


