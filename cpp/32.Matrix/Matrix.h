#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "MyMatrix"

#include <cstddef>

namespace iq
{


template <std::size_t R, std::size_t C>
class Matrix
{
public:
    template <typename T>
    explicit Matrix(T* _p);
    ~Matrix();

private:
    template <typename T>
    MyMatrix<T> m_p;
};



template <std::size_t R, std::size_t C>
template <typename T>
inline Matrix<R, C>::Matrix(T* _p)
: m_p(_p)
{
}

template <std::size_t R, std::size_t C>
inline Matrix<R, C>::~Matrix()
{
}



 
}  // namespace iq

#endif // __MATRIX_H__





