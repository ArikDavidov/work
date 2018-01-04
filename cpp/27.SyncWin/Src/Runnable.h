#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

#include <iostream>
#ifdef __linux__
#include <sys/syscall.h>    // syscall(SYS_gettid)
#endif // !__linux__

namespace advcpp
{
namespace sync
{


class Runnable
{
public:
    virtual ~Runnable();
    
    virtual void Run() = 0;
};
    




  
}  // namespace sync
    
}  // namespace advcpp

#endif // __RUNNABLE_H__



