#ifndef __SAFE_PRIORITY_QUEUE_H__
#define __SAFE_PRIORITY_QUEUE_H__

#include "Mutex.h"
#include "Guard.h"
#include "CondVar.h"

#include <boost/core/noncopyable.hpp>
#include <queue>                        // std::priority_queue
#include <stdexcept>                    // std::runtime_error
#include <iostream>


namespace advcpp
{
namespace sync
{

  
template <typename T>
class SafePriorityQueue : private boost::noncopyable
{
public:
    explicit SafePriorityQueue();
    ~SafePriorityQueue();
    
    void Push(T _element, int _priority = 0);
    T Pop();

private:
    std::priority_queue<std::pair<int, T > > m_priorityQueue;
    Mutex m_mutex;
    CondVar m_condVar;
};



template <typename T>
inline SafePriorityQueue<T>::SafePriorityQueue()
: m_condVar(m_mutex)
{
//    std::cout << "SafePriorityQueue<T>::SafePriorityQueue" << std::endl;
}

template <typename T>
inline SafePriorityQueue<T>::~SafePriorityQueue()
{
//    std::cout << "SafePriorityQueue<T>::~SafePriorityQueue" << std::endl;
}

template <typename T>
inline void SafePriorityQueue<T>::Push(T _element, int _priority)
{
    Guard guard(m_mutex);

//    std::cout << "Push::Before_m_priorityQueue" << std::endl;
    m_priorityQueue.push(std::pair<int, T >(_priority, _element));
//    std::cout << "Push::After_m_priorityQueue" << std::endl;
    
    m_condVar.Signal();
}

template <typename T>
inline T SafePriorityQueue<T>::Pop()
{
    Guard guard(m_mutex);
//    std::cout << "Pop::Before_m_priorityQueue" << std::endl;
    while (m_priorityQueue.empty())
    {
        m_condVar.Wait();    // move the loop inside
    }
    
    T ret = m_priorityQueue.top().second;
    m_priorityQueue.pop();
//    std::cout << "Pop::After_m_priorityQueue" << std::endl;
    return ret;
}
   
    
    
}  // namespace sync
    
}  // namespace advcpp

#endif // __SAFE_PRIORITY_QUEUE_H__


