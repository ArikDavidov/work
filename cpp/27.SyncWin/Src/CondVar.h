#ifndef __COND_VAR_H__
#define __COND_VAR_H__

#ifdef __linux__
	#include <pthread.h>
#endif // !__linux__
#ifdef _WIN32
	#include <windows.h>
#endif // !_WIN32

#include "NativeMutex.h"

namespace advcpp
{
namespace sync
{

#ifdef __linux__
	typedef pthread_cond_t Cond_t;
#endif // !__linux__
#ifdef _WIN32
	typedef CONDITION_VARIABLE Cond_t;
#endif // !_WIN32

class Mutex;


class CondVar : private uncopyable
{
public:
	explicit CondVar(Mutex& _mutex);
	~CondVar();

	void Wait();
	void Broadcast();
	void Signal();

private:
	Cond_t m_cond;
	NativeMutex m_nativeMutex;
};



}  // namespace sync

}  // namespace advcpp

#endif // __COND_VAR_H__

