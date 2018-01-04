#ifndef __COND_VAR_H__
#define __COND_VAR_H__

#include "NativeMutex.h"

//#include <iostream>
#include <pthread.h>

namespace advcpp
{
namespace sync
{

class Mutex;



class CondVar
{
public:
    explicit CondVar(Mutex& _mutex);
    ~CondVar();
	
    void Wait();
    void Broadcast();
    void Signal();

private:
    pthread_cond_t m_cond;
    NativeMutex    m_nativeMutex;
};  
    
    
    
    
}  // namespace sync

}  // namespace advcpp

#endif // __COND_VAR_H__


