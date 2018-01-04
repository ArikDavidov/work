#ifndef __NATIVE_MUTEX_H__
#define __NATIVE_MUTEX_H__

#include "Mutex.h"

#include <iostream>

namespace advcpp
{
namespace sync
{

#ifdef __linux__
	typedef pthread_mutex_t Mutex_t;
#endif // !__linux__
#ifdef _WIN32
	typedef CRITICAL_SECTION Mutex_t;
#endif // !_WIN32


class NativeMutex : private uncopyable
{
public:
	explicit NativeMutex(Mutex& _mtx);
	~NativeMutex();

	Mutex_t* RawPtr();

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

inline Mutex_t* NativeMutex::RawPtr()
{
	//    std::cout << "NativeMutex::RawPtr" << std::endl;
	return m_mutex.RawPtr();
}



}  // namespace sync

}  // namespace advcpp

#endif // __NATIVE_MUTEX_H__

