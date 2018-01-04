#include "CondVar.h"
#include <iostream>
#include <stdexcept>    // std::runtime_error

#ifdef __linux
	#include <pthread.h>
#endif // __linux
#ifdef _WIN32
	#include <windows.h>
#endif // _WIN32


namespace advcpp
{
namespace sync
{

CondVar::CondVar(Mutex& _mutex)
: m_nativeMutex(_mutex)
{
	std::cout << "CondVar::CondVar" << std::endl;
#ifdef __linux
	if (pthread_cond_init(&m_cond, 0))
	{
		throw std::runtime_error("CondVar init Failed");
	}
#endif // __linux
#ifdef _WIN32
	InitializeConditionVariable(&m_cond);
#endif // _WIN32
}

CondVar::~CondVar()
{
	std::cout << "CondVar::~CondVar" << std::endl;
#ifdef __linux
	pthread_cond_destroy(&m_cond);
#endif // __linux
#ifdef _WIN32
	// No need to destroy
#endif // _WIN32
}

void CondVar::Wait()
{
	std::cout << "CondVar::Wait" << std::endl;
#ifdef __linux__
	if (pthread_cond_wait(&m_cond, m_nativeMutex.RawPtr()))
	{
		throw std::runtime_error("CondVar Wait Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	SleepConditionVariableCS(&m_cond, m_nativeMutex.RawPtr(), INFINITE);
#endif // !_WIN32
}

void CondVar::Broadcast()
{
	std::cout << "CondVar::Broadcast" << std::endl;
#ifdef __linux__
	if (pthread_cond_broadcast(&m_cond))
	{
		throw std::runtime_error("CondVar Broadcast Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	WakeAllConditionVariable(&m_cond);
#endif // !_WIN32
}

void CondVar::Signal()
{
	std::cout << "CondVar::Signal" << std::endl;
#ifdef __linux__
	if (pthread_cond_signal(&m_cond))
	{
		throw std::runtime_error("CondVar Signal Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	WakeConditionVariable(&m_cond);
#endif // !_WIN32
}


}  // namespace sync

}  // namespace advcpp    

