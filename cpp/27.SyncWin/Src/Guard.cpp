#include "Guard.h"
#include <iostream>

#ifdef __linux__
#include <unistd.h>			// syscall(SYS_gettid)
#include <sys/syscall.h>	// syscall(SYS_gettid)
#endif // __linux__

namespace advcpp
{
namespace sync
{


Guard::Guard(Mutex& _mutex)
: m_mutex(_mutex)
{
	m_mutex.Lock();
	std::cout << std::endl << "Guard::Guard: "
#ifdef __linux__
		      << syscall(SYS_gettid)
#endif // !__linux__
		      << std::endl;
}

Guard::~Guard()
{
	std::cout << "Guard::~Guard: "
#ifdef __linux__
		      << syscall(SYS_gettid)
#endif // !__linux__
		      << std::endl;
	m_mutex.Unlock();
}


}  // namespace sync

}  // namespace advcpp

