#ifndef __STR_TRAITS_H__
#define __STR_TRAITS_H__

namespace advcpp
{


template <class T>
class StrTraits
{
public:
    static int Length(const T* _str);
    static int Compare(const T* _left, const T* _right);
};



}   // namespace advcpp

#endif    // __STR_TRAITS_H__


