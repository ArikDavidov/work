#ifndef __MY_MATRIX_H__
#define __MY_MATRIX_H__

//#include <cstddef>

namespace iq
{


template <typename T>
class MyMatrix
{
public:
    explicit MyMatrix(T* _p);
    ~MyMatrix();

private:
    MyMatrix<T> m_p;
};



template <typename T>
inline MyMatrix<T>::MyMatrix(T* _p)
: m_p(_p)
{
}

template <typename T>
inline MyMatrix<T>::~MyMatrix()
{
}

template <typename T>
inline T& MyMatrix<T>::operator[](std::size_t _pos)
{
    
}








}  // namespace iq

#endif // __MY_MATRIX_H__


