#ifndef __SAFE_PRIORITY_QUEUE_H__
#define __SAFE_PRIORITY_QUEUE_H__

#include "uncopyable.h"
#include "Mutex.h"
#include "Guard.h"
#include "CondVar.h"

#include <queue>		// std::priority_queue
#include <vector>
#include <iostream>


class vector;

namespace advcpp
{
namespace sync
{


template <typename T, typename Container = std::vector<T>,
	      typename Compare = std::less<typename Container::value_type> >
class SafePriorityQueue : private uncopyable
{
public:
	explicit SafePriorityQueue();
	~SafePriorityQueue();

	void Push(T _element);
	T Pop();

private:
	std::priority_queue<T, Container, Compare> m_queue;
	Mutex m_mutex;
	CondVar m_condVar;
};



template <typename T, typename Container, typename Compare>
inline SafePriorityQueue<T, Container, Compare>::SafePriorityQueue()
: m_mutex()
, m_condVar(m_mutex)
{
    std::cout << "SafePriorityQueue:ctor" << std::endl;
}

template <typename T, typename Container, typename Compare>
inline SafePriorityQueue<T, Container, Compare>::~SafePriorityQueue()
{
    std::cout << "~SafePriorityQueue" << std::endl;
}

template <typename T, typename Container, typename Compare>
inline void SafePriorityQueue<T, Container, Compare>::Push(T _element)
{
	Guard guard(m_mutex);

	std::cout << "Push::Before_m_queue" << std::endl;
	m_queue.push(_element);
	std::cout << "Push::After_m_queue" << std::endl;

	m_condVar.Signal();
}

template <typename T, typename Container, typename Compare>
inline T SafePriorityQueue<T, Container, Compare>::Pop()
{
	Guard guard(m_mutex);
	std::cout << "Pop::Before_m_queue" << std::endl;
	while (m_queue.empty())
	{
		m_condVar.Wait();    // move the loop inside
	}

	T ret = m_queue.top();
	m_queue.pop();
	std::cout << "Pop::After_m_queue" << std::endl;
	return ret;
}


}  // namespace sync

}  // namespace advcpp

#endif // __SAFE_PRIORITY_QUEUE_H__


