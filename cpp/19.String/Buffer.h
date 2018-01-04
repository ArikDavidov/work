#ifndef __buf_T_H__
#define __buf_T_H__

#include <cstddef>      // size_t
#include <stdexcept>    // std::runtime_error

namespace advcpp
{


template<typename T>
class Buffer
{
public:
    explicit Buffer(std::size_t _size);
    // Buffer(const Buffer<T>& _buf);
    ~Buffer();

    std::size_t Capacity() const;
    std::size_t Size() const;
    // void Append(const T&);

    T* Ptr();
    void EnsureCapacity(std::size_t _size);
    
    T& operator[](std::size_t _i);
    const T& operator[](std::size_t _i) const;
    
    // no need to return const because in c++: (i = j) = k is allowd 
    Buffer<T>& operator=(const Buffer& _buf);
    
    // TODO iterators

private:
    std::size_t m_capacity;
    std::size_t m_size;
    T*          m_array;
};


template <typename T>
Buffer<T>::Buffer(std::size_t _size)
: m_capacity(_size), m_size(_size)
{
	m_array = new T[m_capacity];
}

// template <typename T>
// Buffer<T>::Buffer(const Buffer& _buf)
// : m_capacity(_buf->m_capacity), m_size(_buf->m_size)
// {
// 	m_array = new T[m_capacity];
// 	for (int i = 0; i < m_size; ++i)
// 	{
//         m_array[i] = _buf->m_array[i];
//     }
// }

template <typename T>
Buffer<T>& Buffer<T>::operator=(const Buffer<T>& _buf)
{
    T* tmp = new T[_buf->m_size];

    for (std::size_t i = 0; i < m_size; ++i)
    {
        tmp[i] = _buf->m_array[i];
    }

    m_capacity(_buf->m_size);
    m_size(_buf->m_size);
    
    delete[] m_array;    
    m_array = tmp;
}

template <typename T>
Buffer<T>::~Buffer()
{
	delete[] m_array;
}

template<typename T>
inline std::size_t Buffer<T>::Size() const
{
    return m_size;
}

template<typename T>
inline std::size_t Buffer<T>::Capacity() const
{
    return m_capacity;
}

// template<typename T>
// void Buffer<T>::Append(const T& _element)
// {
//     GrowIfNeeded();

//     m_array[m_size++] = _element;
// }

template<typename T>
void Buffer<T>::EnsureCapacity(std::size_t _size)
{
    if (m_size < m_capacity)
    {
        return;
    }

    std::size_t newCapacity = _size; // TODO round up
    T* tmp = new T[newCapacity];

    for (std::size_t i = 0; i < m_capacity; ++i)
    {
        tmp[i] = m_array[i];
    }

    delete[] m_array;
    m_array = tmp;
    m_capacity = newCapacity;
}

template<typename T>
T& Buffer<T>::operator[](std::size_t _i)
{
    if (_i >= m_size)
    {
        throw std::runtime_error("out_of_range");
    }

    return m_array[_i];
}

template<typename T>
const T& Buffer<T>::operator[](std::size_t _i) const
{
    if (_i >= m_size)
    {
        throw std::runtime_error("out_of_range");
    }

    return m_array[_i];
}





}   // namespace advcpp

#endif    // __buf_T_H__

