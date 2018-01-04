#include "Mutex.h"
#include <stdexcept>    // std::runtime_error


namespace advcpp
{
namespace sync
{


Mutex::Mutex()
{
#ifdef __linux__
	if (pthread_mutex_init(&m_mutex, 0))
	{
		throw std::runtime_error("Mutex Init Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	InitializeCriticalSection(&m_mutex);
#endif // !_WIN32
}

Mutex::~Mutex()
{
#ifdef __linux__
	pthread_mutex_destroy(&m_mutex);
#endif // !__linux__
#ifdef _WIN32
	DeleteCriticalSection(&m_mutex);
#endif // !_WIN32
}

void Mutex::Lock()
{
#ifdef __linux__
	if (pthread_mutex_lock(&m_mutex))
	{
		throw std::runtime_error("Mutex Lock Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	EnterCriticalSection(&m_mutex);
#endif // !_WIN32
}

void Mutex::Unlock()
{
#ifdef __linux__
	if (pthread_mutex_unlock(&m_mutex))
	{
		throw std::runtime_error("Mutex Unlock Failed");
	}
#endif // !__linux__
#ifdef _WIN32
	LeaveCriticalSection(&m_mutex);
#endif // !_WIN32
}



}  // namespace sync

}  // namespace advcpp

