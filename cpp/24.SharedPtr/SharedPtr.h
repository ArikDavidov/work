#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <cstddef>
#include <stdexcept>    // std::runtime_error

namespace advcpp
{

template <typename T>
class SharedPtr
{

template <typename V>
friend class SharedPtr;

    
public:
//    explicit SharedPtr();
    explicit SharedPtr(T* _t);
    SharedPtr(const SharedPtr& _sp = s_null);
    ~SharedPtr();
    
//    SharedPtr(const SharedPtr& _sp);
    SharedPtr& operator=(const SharedPtr& _sp);
    
    template <typename U>
    SharedPtr(const SharedPtr<U>& _sp);
    template <typename U>
    SharedPtr& operator=(const SharedPtr<U>& _sp);

    T& operator*();
    T* operator->();
    T* Ptr() const;
    std::size_t Count() const;
    bool operator==(const SharedPtr& _sp) const;    
//    operator bool() const;

private:
    void Copy(const SharedPtr& _sp);
    void Dec();

    T*   m_ptr;
    int* m_refCount;
    
};

//template <std::size_t B>
//static int* NewCounter()
//{
//    return new int(1);
//}

//template <>
//static int* NewCounter<0>()
//{
//    return 0;
//}

//template<U PT>
//struct NewCounter
//{
//    static int* New()
//    { 
//        return new int(1);
//    }
//};

//template<> 
//struct NewCounter<static_cast<int*>(0)>
//{ 
//    static int* New()
//    { 
//        return 0;
//    }
//};

template <typename T>
inline SharedPtr<T>::SharedPtr()
: m_refCount(0)
, m_ptr(0)
{
}

//template <typename T>
//inline SharedPtr<T>::SharedPtr(T* _t)
//{
//    try
//    {
//        m_refCount = new int(1);
//    }
//    catch(...)
//    {
//        delete _t:  // Very important!!!!!!!!!!!!!!!!!!!!
//    }
//    
//    m_ptr = _t;
//}

template <typename T>
inline SharedPtr<T>::SharedPtr(T* _t)
try : m_refCount(new int(1))
    , m_ptr(_t)
{
}
catch(...)
{
    delete _t:  // Very important!!!!!!!!!!!!!!!!!!!!
    // if we don't throw, the compiler will throw anyway
    // because the ctor failed and all data members are ddestructed;
    throw;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    Dec();
}

template <typename T>
inline void SharedPtr<T>::Dec()
{
    if (!m_ptr)
    {
        return;
    }
    
    if (!__sync_sub_and_fetch(m_refCount, 1))
    {
        delete m_ptr;
        delete m_refCount;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& _sp)
{
    Copy(_sp);
}

template <typename T>
inline void SharedPtr<T>::Copy(const SharedPtr& _sp)
{
    m_refCount = _sp.m_refCount;
    m_ptr = _sp.m_ptr;
    // bug: can be dereferencing null ptr
    __sync_fetch_and_add(_sp.m_refCount, 1);
}

template <typename T>
template <typename U>
inline void SharedPtr<T>::SharedPtr(const SharedPtr<U>& _sp)
{
    m_refCount = _sp.m_refCount;
    m_ptr = _sp.m_ptr;
    __sync_fetch_and_add(_sp.m_refCount, 1);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& _sp)
{
    // copy and swap is better
    if (*this == &_sp)
    {
        return *this;
    }
    
    if (m_refCount)
    {
        Dec();
    }
    
    Copy(_sp);
    
    return *this;
}
 
template <typename T>
inline T* SharedPtr<T>::operator->()
{
//    if (!m_ptr)
//    {
//        throw std::runtime_error("Dereferencing null pointer");
//    }
    
    return m_ptr;
}

template <typename T>
inline T& SharedPtr<T>::operator*()
{
//    if (!m_ptr)
//    {
//        throw std::runtime_error("Dereferencing null pointer");
//    }
    
    return *m_ptr;
}

template <typename T>
inline T* SharedPtr<T>::Ptr() const
{
    return m_ptr;
}
    
template <typename T>
inline bool SharedPtr<T>::operator==(const SharedPtr& _sp) const
{
    return m_ptr == _sp.m_ptr;
}

//template <typename T>
//SharedPtr<T>::operator bool() const
//{
//    return (0 != m_ptr);
//}

template <typename T>
inline std::size_t SharedPtr<T>::Count() const
{
    return *m_refCount;
}

 
 
    
}  // namespace advcpp

#endif // __SHARED_PTR_H__


