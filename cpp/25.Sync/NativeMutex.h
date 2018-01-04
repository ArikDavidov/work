#ifndef __NATIVE_MUTEX_H__
#define __NATIVE_MUTEX_H__

#include "Mutex.h"

#include <boost/core/noncopyable.hpp>
#include <iostream>

namespace advcpp
{
namespace sync
{


class NativeMutex : private boost::noncopyable
{
public:
    explicit NativeMutex(Mutex& _mtx);
    ~NativeMutex();
    
    pthread_mutex_t* RawPtr();
    
private:
    Mutex& m_mutex;
};


inline NativeMutex::NativeMutex(Mutex& _mtx)
: m_mutex(_mtx)
{
//    std::cout << "NativeMutex::NativeMutex" << std::endl;
}

inline NativeMutex::~NativeMutex()
{
//    std::cout << "NativeMutex::~NativeMutex" << std::endl;
}

inline pthread_mutex_t* NativeMutex::RawPtr()
{
//    std::cout << "NativeMutex::RawPtr" << std::endl;
    return m_mutex.RawPtr();
}


    
}  // namespace sync
    
}  // namespace advcpp

#endif // __NATIVE_MUTEX_H__


