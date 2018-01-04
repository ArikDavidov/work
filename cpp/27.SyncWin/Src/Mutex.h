#ifndef __MUTEX_H__
#define __MUTEX_H__

#ifdef __linux__
#include <pthread.h>
#endif // !__linux__
#ifdef _WIN32
#include <Windows.h>
#endif // !_WIN32

#include "uncopyable.h"


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


class Mutex : private uncopyable
{
	friend class NativeMutex;
public:
	explicit Mutex();
	~Mutex();
	void Lock();
	void Unlock();

private:
	Mutex_t* RawPtr();

	Mutex_t m_mutex;
};


inline Mutex_t* Mutex::RawPtr()
{
	return &m_mutex;
}


}  // namespace sync

}  // namespace advcpp

#endif // __MUTEX_H__

