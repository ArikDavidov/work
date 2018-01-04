#ifndef __STRING_T_H__
#define __STRING_T_H__

#include "Buffer.h"
#include "StrTraits.h"

namespace advcpp
{

template <class T>
class String_t
{
public:
    explicit String_t();
    String_t(const T* _str);
    String_t(const String_t& _str);
    ~String_t();

    bool operator==(const T* _str) const;
    bool operator==(const String_t& _str) const;
    bool operator<(const T* _str) const;
    bool operator<(const String_t& _str) const;

    T& operator[](std::size_t _i);
    const T& operator[](std::size_t _i) const;
    
    String_t operator+(const T* _str) const;    // move out of class
    String_t operator+(const String_t&) const;  // move out of class
    String_t& operator=(const T* _str);
    String_t& operator=(const String_t&);
    // String_t& operator+=(const T* _str);
    // String_t& operator+=(const String_t&);
    
    const T* c_str() const;
    inline unsigned Length() const;

private:
    Buffer<T> m_buffer;
};


std::ostream& operator<<(std::ostream& _os, const String_t& _str)
{
    _os << _str.c_str();

    return _os;
}

std::wostream& operator<<(std::wostream& _wos, const String_t& _str)
{
    _wos << _str.c_str();

    return _wos;
}


// String_t<T> operator+(const T* _left, const String_t<T>& _left);



template <class T>
String_t<T>::String_t()
: m_buffer(16)
{
    m_buffer[0] = '\0';
}

template <class T>
String_t<T>::String_t(const String_t& _str)
{
    std::size_t len = _str.Length();
    m_buffer.EnsureCapacity(len + 1);
    
    for (std::size_t i = 0; i < len + 1; ++i)
    {
        m_buffer[i] = _str[i];
    }
}

template <class T>
String_t<T>::String_t(const T* _str)
{
    if (!_str)
    {
        throw std::runtime_error("Invalid argument");
    }

    std::size_t len = StrTraits<T>::Length(_str);
    m_buffer.EnsureCapacity(len + 1);

    for (std::size_t i = 0; i < len + 1; ++i)
    {
        m_buffer[i] = _str[i];
    }
}

template <class T>
String_t<T>::~String_t()
{
}

template <class T>
inline unsigned String_t<T>::Length() const
{
    return StrTraits<T>::Length(c_str());
}

template <class T>
inline bool String_t<T>::operator==(const T* _str) const
{
    return !StrTraits<T>::Compare(c_str(),_str);
}

template <class T>
inline bool String_t<T>::operator==(const String_t& _str) const
{
    return !StrTraits<T>::Compare(c_str(),_str.c_str());
}

template <class T>
inline bool String_t<T>::operator<(const T* _str) const
{
    return 0 > StrTraits<T>::Compare(c_str(), _str);
}

template <class T>
inline bool String_t<T>::operator<(const String_t& _str) const
{
    return 0 > StrTraits<T>::Compare(c_str(), _str.c_str());
}

template <class T>
inline const T* String_t<T>::c_str() const
{
    return m_buffer.Ptr();
}

template <class T>
inline T& String_t<T>::operator[](std::size_t _i)
{
    if (_i > Length())
    {
        throw std::runtime_error("Out of range");
    }

    return m_buffer[_i];
}

template <class T>
inline const T& String_t<T>::operator[](std::size_t _i) const
{
    if (_i > Length())
    {
        throw std::runtime_error("Out of range");
    }

    return m_buffer[_i];
}

template <class T>
String_t& String_t<T>::operator+(const T* _str) const
{
    if (!_str)
    {
        throw std::runtime_error("Invalid argument");
    }

    std::size_t len = Length();
    std::size_t addedLen = StrTraits<T>::Length(_str);

    m_buffer.EnsureCapacity(len + addedLen + 1);

    for (std::size_t i = 0; i < addedLen + 1; ++i)
    {
        m_buffer[len + i] = _str[i];
    }

    return *this;
    
}

template <class T>
String_t& String_t<T>::operator+(const String_t&) const
{
    std::size_t len = Length();
    std::size_t addedLen = _str.Length();
    
    m_buffer.EnsureCapacity(len + addedLen + 1);

    for (std::size_t i = 0; i < addedLen + 1; ++i)
    {
        m_buffer[len + i] = _str[i];
    }

    return *this;
}   

template <class T>
String_t& String_t<T>::operator=(const T* _str)
{
    if (!_str)
    {
        throw std::runtime_error("Invalid argument");
    }

    std::size_t len = StrTraits<T>::Length(_str);
    m_buffer.EnsureCapacity(len + 1);

    for (std::size_t i = 0; i < len + 1; ++i)
    {
        m_buffer[i] = _str[i];
    }
}

template <class T>
String_t& String_t<T>::operator=(const String_t&)
{
    std::size_t len = StrTraits<T>::Length(_str);
    m_buffer.EnsureCapacity(len + 1);

    for (std::size_t i = 0; i < len + 1; ++i)
    {
        m_buffer[i] = _str[i];
    }
}


// template <class T>
// inline bool Print(const String_t& _str) const
// {
// }



}   // namespace advcpp

#endif    // __STRING_T__H__






