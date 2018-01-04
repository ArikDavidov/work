#include "Guard.h"
#include <iostream>
#include <sys/syscall.h>		/* syscall(SYS_gettid) */

namespace advcpp
{
namespace sync
{


Guard::Guard(Mutex& _mutex)
: m_mutex(_mutex)
{
    m_mutex.Lock();
    std::cout  << std::endl << "Guard::Guard: " << syscall(SYS_gettid) << std::endl;
}

Guard::~Guard()
{
    std::cout << "Guard::~Guard: " << syscall(SYS_gettid)  << std::endl << std::endl;
    m_mutex.Unlock();
}


    
    
}  // namespace sync

}  // namespace advcpp


