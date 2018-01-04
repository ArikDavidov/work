#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "SafePriorityQueue.h"
#include "Mutex.h"
#include "Thread.h"
#include "Task.h"


#ifdef __linux__
#include <pthread.h>
#endif // !__linux__
#ifdef _WIN32
#include <windows.h>
#endif // !_WIN32

#include <vector>
#include <memory>   // std::tr1::shared_ptr

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

class ThreadPool : private uncopyable
{
    class TaskRunner{
    public:
        TaskRunner(std::tr1::shared_ptr<SafePriorityQueue<std::tr1::shared_ptr<Task> > > _spQueue,
			       bool& _shutDownMode);
        ~TaskRunner();
        void Run();
    private:
        bool& m_shutDownMode;
        std::tr1::shared_ptr<SafePriorityQueue<std::tr1::shared_ptr<Task> > > m_spQueue;
    };
    class SuicidTask : public Task {
    public:
        SuicidTask();
        ~SuicidTask();
        void CommitSuicid();
        ThreadPool* m_threadPool;
    };
public:
    explicit ThreadPool(std::size_t _numOfThreads);
    ~ThreadPool();
    
    void Add(std::tr1::shared_ptr<Task> _task, int _priority = 0);
//    void ShutDown();
    void GracefulShutDown();
    void BruteForceShutDown();

    // move to separet class
    void Resize(std::size_t _newSize);
    void AddThreads(std::size_t _numOfThreads);
    void RemoveThreads(std::size_t _numOfThreads);
    void Remove(ThreadId_t _threadId);

private:
    bool m_shutDownMode;    // TODO remove from here
    Mutex m_mutex;
    std::tr1::shared_ptr<SafePriorityQueue<std::tr1::shared_ptr<Task> > > m_spQueue;
    std::tr1::shared_ptr<TaskRunner> m_taskRunner;
    std::tr1::shared_ptr<SuicidTask> m_suicidTask;
    std::vector<std::tr1::shared_ptr<Thread<TaskRunner> > > m_threads;
};



}  // namespace sync
   
}  // namespace advcpp

#endif // __THREAD_POOL_H__
