#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include <boost/core/noncopyable.hpp>

namespace advcpp
{
namespace sync
{


class Mutex : private boost::noncopyable
{
	friend class NativeMutex;
public:
    explicit Mutex();
    ~Mutex();
    void Lock();
    void Unlock();

private:
    pthread_mutex_t* RawPtr();

    pthread_mutex_t m_mutex;
};



inline pthread_mutex_t* Mutex::RawPtr()
{
    return &m_mutex;
}



    
}  // namespace sync
    
}  // namespace advcpp

#endif // __MUTEX_H__


