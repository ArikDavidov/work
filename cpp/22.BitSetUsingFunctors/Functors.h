#ifndef __FUNCTORS_H__
#define __FUNCTORS_H__

#include <cstddef>      // std::size_t

namespace advcpp
{
    
template <typename T>
struct OperatorOr
{
    T operator()(const T& _left, const T& _right)
    {
        return _left | _right;
    }
};    

template <typename T>
struct OperatorAnd
{
    T operator()(const T& _left, const T& _right)
    {
        return _left & _right;
    }
};     

template <typename T>
struct OperatorXor
{
    T operator()(const T& _left, const T& _right)
    {
        return _left ^ _right;
    }
};  

template <typename T>
struct NotZero
{
    bool operator()(const T& _t)
    {
        return 0 != _t;
    }
};

template <typename T>
struct NotAllPoped
{
    bool operator()(const T& _t)
    {
        T mask = ~0;
        return mask != _t;
    }
};

template <typename T>
struct DoFlip
{
    void operator()(T& _t)
    {
        _t = ~_t;
    }
};

template <typename T>
struct PopCount {
    std::size_t operator()(T _count, T _t) {
        for (; _t; _t >>= 1)
        {
            _count += _t & 1;
        }
        
        return _count;
    }
};


}   // namespace advcpp

#endif // __FUNCTORS_H__


