#ifndef __THREAD_H__
#define __THREAD_H__

#include "Mutex.h"
#include "Guard.h"

#include <sys/syscall.h>    // syscall(SYS_gettid)
#include <tr1/memory>   // std::tr1::shared_ptr
#include <iostream>
#include <assert.h>

namespace advcpp
{
namespace sync
{


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
    explicit Thread(std::tr1::shared_ptr<Runnable> _runnable);
    ~Thread();
    void Detach();
    void Join();
    pthread_t ThreadId() const;
    bool IsJoinable() const;

private:
    static void* Run(void* _context);

    pthread_t m_threadId;
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
    std::cout << "Thread::Thread: " << syscall(SYS_gettid) << std::endl;
    pthread_create(&m_threadId, 0, Run, static_cast<void*>(&m_context));
    std::cout << "Thread::Thread: " << m_threadId << " | " << pthread_self() << std::endl;
}

template <typename T>
inline Thread<T>::Thread(std::tr1::shared_ptr<Runnable> _runnable)
{

}


template <typename T>
inline Thread<T>::~Thread()
{
    std::cout << "Thread::~Thread: " << syscall(SYS_gettid) << std::endl;
    assert(!m_isJoinable);
}

template <typename T>
inline pthread_t Thread<T>::ThreadId() const
{
    return m_threadId;
}

template <typename T>
inline bool Thread<T>::IsJoinable() const
{
    return m_isJoinable;
}

template <typename T>
inline void Thread<T>::Join()
{
    Guard guard(m_mutex);
    
    if (!m_isJoinable)
    {
        throw std::runtime_error("thread is not joinable");
    }
    
    pthread_join(m_threadId, 0);
    m_isJoinable = false;
}

template <typename T>
inline void Thread<T>::Detach()
{
    Guard guard(m_mutex);
    
    if (!m_isJoinable)
    {
        throw std::runtime_error("thread is not joinable");
    }
    
    pthread_detach(m_threadId);
    m_isJoinable = false;
}




}   // namespace sync

}   // namespace advcpp

#endif // __THREAD_H__

