#ifndef __THREAD_H__
#define __THREAD_H__

#include "Mutex.h"
#include "Guard.h"
#include "Runnable.h"

#ifdef __linux__
#include <tr1/memory>       // std::tr1::shared_ptr
#include <stdlib.h>         // abort
#endif // __linux__
#include <iostream>
#include <assert.h>

namespace advcpp
{
namespace sync
{


class Thread
{
public:
    explicit Thread(std::tr1::shared_ptr<Runnable> _runnable);
    ~Thread();
    void Detach();
    void Join();
    pthread_t ThreadId() const;
    bool IsJoinable() const;

private:
    static void* Start(void* _runnable);

    pthread_t m_threadId;
    bool m_isJoinable;
    Mutex m_mutex;
    std::tr1::shared_ptr<Runnable> m_runnable;
};



inline Thread::Thread(std::tr1::shared_ptr<Runnable> _runnable)
: m_isJoinable(true)
, m_runnable(_runnable)
{
    pthread_create(&m_threadId, 0, Start, static_cast<void*>(m_runnable.get()));
    std::cout << "Thread: " << pthread_self()
              << " created thread: " << m_threadId << std::endl;

}
    
inline void* Thread::Start(void* _runnable)
{
    std::cout << "Thread::Start: " << pthread_self() << std::endl;
    static_cast<Runnable*>(_runnable)->Run();
}
    
inline Thread::~Thread()
{
    std::cout << "Thread::~Thread: " << pthread_self() << std::endl;
    if (IsJoinable())
    {
        std::cerr << "ERROR: dtor was called on joinable thread" << std::endl;
        abort();
    }
}

inline pthread_t Thread::ThreadId() const
{
    return m_threadId;
}

inline bool Thread::IsJoinable() const
{
    return m_isJoinable;
}

inline void Thread::Join()
{
    Guard guard(m_mutex);
    
    if (!IsJoinable())
    {
        throw std::runtime_error("thread is not joinable");
    }
    
    pthread_join(m_threadId, 0);
    m_isJoinable = false;
}

inline void Thread::Detach()
{
    Guard guard(m_mutex);
    
    if (!IsJoinable())
    {
        throw std::runtime_error("thread is not joinable");
    }
    
    pthread_detach(m_threadId);
    m_isJoinable = false;
}




}   // namespace sync

}   // namespace advcpp

#endif // __THREAD_H__


