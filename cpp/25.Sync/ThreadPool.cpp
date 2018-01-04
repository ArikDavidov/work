#include "ThreadPool.h"
#include "Thread.h"
#include "Mutex.h"
#include "Guard.h"
#include "Task.h"

#include <vector>
#include <sys/syscall.h>    // syscall(SYS_gettid)
#include <tr1/memory>       // std::tr1::shared_ptr
#include <stdexcept>        // std::runtime_error
#include <limits>
#include <assert.h>
#include <iostream>

namespace advcpp
{
namespace sync
{

//////////////////  TaskRunner  ////////////////////

ThreadPool::TaskRunner::TaskRunner(std::tr1::shared_ptr<SafePriorityQueue<std::tr1::shared_ptr<Task> > > _spQueue,
                                   bool& _shutDownMode)
: m_shutDownMode(_shutDownMode)
, m_spQueue(_spQueue)
{
}

ThreadPool::TaskRunner::~TaskRunner()
{
}

void ThreadPool::TaskRunner::Run()
{
    // std::cout << "TaskRunner::Run" << syscall(SYS_gettid) << std::endl;
    
    while(!__sync_fetch_and_or(&m_shutDownMode, 0))
    {
//        try {
//            ....
//        } catch (std::exception& e) {
//            cerr << e.what();
//        } catch (abi::__forced_unwined& e) {
//            throw;
//        } catch (...)
//            cerr << ThreadPool::UNHANDLED_EXCEPTION_MESSAGE;
//        }
        
        std::tr1::shared_ptr<Task> spTask = m_spQueue->Pop();
        std::cout << "TaskRunner::Run::afterPop" << syscall(SYS_gettid) << std::endl;
        spTask->DoSomeWork();
    }
    std::cout << "ThreadPool::TaskRunner::Run::exiting" << syscall(SYS_gettid) << std::endl;
}

//////////////////  ThreadPool  ////////////////////

ThreadPool::ThreadPool(std::size_t _numOfThreads)
: m_shutDownMode(false)
, m_spQueue(new SafePriorityQueue<std::tr1::shared_ptr<Task> >)
, m_taskRunner(new TaskRunner(m_spQueue, m_shutDownMode))
{
    std::cout << "ThreadPool::ThreadPool" << syscall(SYS_gettid) << std::endl;
    AddThreads(_numOfThreads);
}	

ThreadPool::~ThreadPool()
{
    std::cout << "ThreadPool::~ThreadPool" << std::endl;
}

void ThreadPool::Add(std::tr1::shared_ptr<Task> _task, int _priority)
{
    Guard guard(m_mutex);
    std::cout << "ThreadPool::Add" << std::endl;
    if (__sync_fetch_and_or(&m_shutDownMode, 0))
    {
        throw std::runtime_error("ThreadPool is in ShutDown Mode");
    }
    
    m_spQueue->Push(_task, _priority);
    std::cout << "ThreadPool::Add::AfterPush" << std::endl;
} 

void ThreadPool::GracefulShutDown()
{
    std::cout << "ThreadPool::GracefulShutDown" << syscall(SYS_gettid) << std::endl;

    __sync_fetch_and_add(&m_shutDownMode, 1);
    
    for (std::size_t i = 0; i < m_threads.size(); ++i)
    {
        std::cout << "ThreadPool::ShutDown::Pushing empty Task" << std::endl;
        m_spQueue->Push(std::tr1::shared_ptr<Task>(new Task));
    } 
    
    for (std::size_t i = 0; i < m_threads.size(); ++i)
    {
        std::cout << "ThreadPool::ShutDown::Joining" << std::endl;
        m_threads[i]->Join();
    }   
}

void ThreadPool::BruteForceShutDown()
{
    std::cout << "ThreadPool::BruteForceShutDown" << syscall(SYS_gettid) << std::endl;
	std::cout << "int: " << std::numeric_limits<int>::max() << std::endl;

    for (std::size_t i = 0; i < m_threads.size(); ++i)
    {
        std::cout << "m_threads[m_threads.size()-1]->ThreadId(): "
                  << m_threads[m_threads.size()-1]->ThreadId() << std::endl;
        m_threads.pop_back();
    }
    
    // m_spQueue->Push(_task, _priority);
}



void ThreadPool::Resize(std::size_t _newSize)
{
	if (_newSize > m_threads.size())
	{
		AddThreads(_newSize - m_threads.size());
	}
	else
	{
		RemoveThreads(m_threads.size() - _newSize);
	}
}

void ThreadPool::AddThreads(std::size_t _numOfThreads)
{
    for (std::size_t i = 0; i < _numOfThreads; ++i)
    {
        std::tr1::shared_ptr<Thread<TaskRunner> >
        	sp(new Thread<TaskRunner>(m_taskRunner, &TaskRunner::Run));

        m_threads.push_back(sp);
    }
}

void ThreadPool::RemoveThreads(std::size_t _numOfThreads)
{
    for (std::size_t i = 0; i < _numOfThreads; ++i)
    {
        m_spQueue->Push(std::tr1::shared_ptr<Task>(new Task),
        				std::numeric_limits<int>::max());		//TODO TOP_PRIORITY
    }
}


// void ThreadPool::Remove(pthread_t _threadId)
// {
// 	m_threads.pop_back();
// }
ThreadPool::SuicidTask::SuicidTask(ThreadPool* _threadPool)
: m_threadPool(_threadPool)
{
	
}

ThreadPool::SuicidTask::~SuicidTask()
{

}

void ThreadPool::SuicidTask::DoSomeWork()
{
	CommitSuicid();
}

void ThreadPool::SuicidTask::CommitSuicid()
{
	std::cout << "CommitSuicid: "
              << m_threadPool->m_threads[m_threadPool->m_threads.size()-1]->ThreadId() << std::endl;

  	m_threadPool->m_threads.pop_back();
}

//PoisonedTask





}  // namespace sync
   
}  // namespace advcpp







