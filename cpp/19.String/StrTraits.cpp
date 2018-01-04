#include "StrTraits.h"

#include <string.h>
#include <iostream>

namespace advcpp
{

template <>
int StrTraits<char>::Length(const char* _str)
{
    return strlen(_str);
}

template <>
int StrTraits<char>::Compare(const char* _left, const char* _right)
{
    return strcmp(_left, _right);
}


template <>
int StrTraits<wchar_t>::Length(const wchar_t* _str)
{
    return wcslen(_str);
}

template <>
int StrTraits<wchar_t>::Compare(const wchar_t* _left, const wchar_t* _right)
{
    return wcscmp(_left, _right);
}



}   // namespace advcpp


