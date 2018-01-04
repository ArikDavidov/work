#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
#ifdef __linux__
#include <sys/syscall.h>    // syscall(SYS_gettid)
#endif // !__linux__

namespace advcpp
{
namespace sync
{


class Task
{
public:
    explicit Task();
    virtual ~Task();
    
    virtual void DoSomeWork();
};
    
    
inline Task::Task()
{
//    std::cout << "Task::Task" << std::endl;
}

inline Task::~Task()
{
//    std::cout << "Task::~Task" << std::endl;
}

inline void Task::DoSomeWork()
{
    std::cout << "Task::DoSomeWork: "
#ifdef __linux__
			  << syscall(SYS_gettid)
#endif // !__linux__
			  << std::endl;
}


// template <typename T>
// struct Task
// {
// 	std::tr1::shared_ptr<T> m_obj;
// 	void (T::*m_routine)();
// }

  
}  // namespace sync
    
}  // namespace advcpp

#endif // __TASK_H__


