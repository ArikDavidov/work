#ifndef __STRING_T_H__
#define __STRING_T_H__

#include "Buffer.h"

namespace advcpp
{


class String_t
{
public:
    explicit String_t();
    explicit String_t(const char* _str);
    explicit String_t(const String_t& _str);
    virtual ~String_t();
    
    unsigned Size() const;
    unsigned Capacity() const;
    void Append(const char&);

    bool operator==(const char* _str) const;
    bool operator==(const String_t& _str) const;
    bool operator<(const char* _str) const;
    bool operator<(const String_t& _str) const;

    char& operator[](const String_t& _str);
    const char& operator[](const char* _str) const;
    
    String_t& operator+(const char* _str);
    String_t& operator+(const String_t&);    
    String_t& operator=(const char* _str);
    String_t& operator=(const String_t&);
    
    cStr() const;
    
    void Upper();   // move to another class
    void Lower();   // move to another class

private:
    Buffer<char>* m_buffer;
};


inline unsigned String_t::Size() const
{
	return m_buffer->Size();
}

inline unsigned String_t::Capacity() const
{
	return m_buffer->Capacity();
}



}   // namespace advcpp

#endif    // __STRING_T__H__






