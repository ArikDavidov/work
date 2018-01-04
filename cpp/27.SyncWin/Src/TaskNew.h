#ifndef __TASK_H__
#define __TASK_H__

#include "Runnable.h"

#include <iostream>

namespace advcpp
{
namespace sync
{


class Task : public Runnable
{
public:
    struct Less {
        virtual bool operator() (std::tr1::shared_ptr<Task> _left,
                                 std::tr1::shared_ptr<Task> _right) const {
            return _left->m_priority < _right->m_priority;
        }
    };

    explicit Task(int _priority) : m_priority(_priority) {}
    ~Task() {}
    
    void Run() {
        m_runnable->Run();
        std::cout << "Task::Run " << m_num << " | "
                  << syscall(SYS_gettid) << std::endl;
    }

    int m_priority;
};

template <typename T>
class MyTask : public Task
{
public:
    explicit MyTask(std::tr1::shared_ptr<T> _runnable, int _priority);
     : m_priority(_priority) {}
    std::tr1::shared_ptr<T> _obj, void (T::*_routine)()
    ~Task() {}
    
    void Run() {
        m_runnable->Run();
        std::cout << "Task::Run " << m_num << " | "
                  << syscall(SYS_gettid) << std::endl;
    }

    std::tr1::shared_ptr<T> m_runnable;
    int m_priority;
};



}   // namespace sync

}   // namespace advcpp

#endif // __TASK_H__


