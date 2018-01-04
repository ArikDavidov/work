#ifndef __THREAD_H__
#define __THREAD_H__

#include "Mutex.h"
#include "Guard.h"

#include <iostream>
#include <assert.h>

#ifdef __linux__
	#include <tr1/memory>		// std::tr1::shared_ptr
	#include <sys/syscall.h>    // syscall(SYS_gettid)
	#include <unistd.h>   		// syscall(SYS_gettid)
#endif // !__linux__
#ifdef _WIN32
	#include <memory>			// std::tr1::shared_ptr
#endif // _WIN32

namespace advcpp
{
namespace sync
{

#ifdef __linux__
	typedef pthread_t ThreadId_t;
#endif // __linux__
#ifdef _WIN32
	typedef DWORD ThreadId_t;
	typedef HANDLE NativeHandle_t;
#endif // _WIN32


template <typename T>
class Thread
{
	class Context {
	public:
		explicit Context(std::tr1::shared_ptr<T> _obj, void (T::*_routine)());
		std::tr1::shared_ptr<T> m_obj;
		void (T::*m_routine)();
	};
public:
	explicit Thread(std::tr1::shared_ptr<T> _obj, void (T::*_routine)());
	~Thread();
	void Detach();
	void Join();
	ThreadId_t ThreadId() const;
	bool IsJoinable() const;
#ifdef _WIN32
	NativeHandle_t NativeHandle() const;
#endif // _WIN32

private:
	static void* Run(void* _context);

	ThreadId_t m_threadId;
#ifdef _WIN32
	NativeHandle_t m_nativeHandle;
#endif // _WIN32
	bool m_isJoinable;
	Mutex m_mutex;
	Context m_context;
};


template <typename T>
inline Thread<T>::Context::Context(std::tr1::shared_ptr<T> _obj, void (T::*_routine)())
: m_obj(_obj)
, m_routine(_routine)
{
}

template <typename T>
inline void* Thread<T>::Run(void* _context)
{
	std::tr1::shared_ptr<T> obj = static_cast<Context*>(_context)->m_obj;
	void (T::*routine)() = static_cast<Context*>(_context)->m_routine;

	((*obj).*routine)();
}


template <typename T>
inline Thread<T>::Thread(std::tr1::shared_ptr<T> _obj, void (T::*_routine)())
: m_isJoinable(true)
, m_context(_obj, _routine)
{
#ifdef __linux__
	std::cout << "Thread::Thread: " << syscall(SYS_gettid) << std::endl;
	int ret = pthread_create(&m_threadId, 0, Run, static_cast<void*>(&m_context));
	std::cout << "Thread::Thread: " << m_threadId << std::endl;
///////////////////   << " | " << pthread_self() 
	if (ret)
#endif // !__linux__
#ifdef _WIN32
	m_nativeHandle = CreateThread(
		0,		// default security attributes
		0,		// default stack size
		static_cast<LPTHREAD_START_ROUTINE>(Run),
		(LPVOID)&m_context,
		0,		// default creation flags
		&m_threadId);

	if (!m_nativeHandle)
#endif // _WIN32
	{
		throw std::runtime_error("thread creation failed");
	}
}

template <typename T>
inline Thread<T>::~Thread()
{
	std::cout << "Thread::~Thread " << std::endl;
	assert(!m_isJoinable);
}

template <typename T>
inline ThreadId_t Thread<T>::ThreadId() const
{
	return m_threadId;
}

template <typename T>
inline bool Thread<T>::IsJoinable() const
{
	return m_isJoinable;
}

#ifdef _WIN32
	template <typename T>
	inline NativeHandle_t Thread<T>::NativeHandle() const
	{
		return m_nativeHandle;
	}
#endif // _WIN32

template <typename T>
inline void Thread<T>::Join()
{
	Guard guard(m_mutex);

	if (!m_isJoinable)
	{
		throw std::runtime_error("thread is not joinable");
	}

#ifdef __linux__
	int ret = pthread_join(m_threadId, 0);
	assert(!ret);
#endif // !__linux__
#ifdef _WIN32
	WaitForSingleObject(m_nativeHandle, INFINITE);
	CloseHandle(m_nativeHandle);
#endif // _WIN32

	m_isJoinable = false;
}

//////////////////  WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

template <typename T>
inline void Thread<T>::Detach()
{
	Guard guard(m_mutex);

	if (!m_isJoinable)
	{
		throw std::runtime_error("thread is not joinable");
	}

#ifdef __linux__
	int ret = pthread_detach(m_threadId);
	assert(!ret);
#endif // !__linux__
#ifdef _WIN32
	CloseHandle(m_nativeHandle);
#endif // _WIN32

	m_isJoinable = false;
}



}   // namespace sync

}   // namespace advcpp

#endif // __THREAD_H__
