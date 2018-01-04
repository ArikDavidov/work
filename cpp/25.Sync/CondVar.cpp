#include "CondVar.h"
#include <iostream>
#include <stdexcept>    // std::runtime_error
#include <pthread.h>


namespace advcpp
{
namespace sync
{

CondVar::CondVar(Mutex& _mutex)
: m_nativeMutex(_mutex)
{
    std::cout << "CondVar::CondVar" << std::endl;
    if (pthread_cond_init(&m_cond, 0))
    {
        throw std::runtime_error("CondVar init Failed");
    }
}

CondVar::~CondVar()
{
    std::cout << "CondVar::~CondVar" << std::endl;
    pthread_cond_destroy(&m_cond);
}

void CondVar::Wait()
{
    std::cout << "CondVar::Wait" << std::endl;
    if (pthread_cond_wait(&m_cond, m_nativeMutex.RawPtr()))
    {
        throw std::runtime_error("CondVar Wait Failed");
    }
}

void CondVar::Broadcast()
{
    std::cout << "CondVar::Broadcast" << std::endl;
    if (pthread_cond_broadcast(&m_cond))
    {
        throw std::runtime_error("CondVar Broadcast Failed");
    }
}

void CondVar::Signal()
{
    std::cout << "CondVar::Signal" << std::endl;
    if (pthread_cond_signal(&m_cond))
    {
        throw std::runtime_error("CondVar Signal Failed");
    }
}


    
}  // namespace sync

}  // namespace advcpp    
    
    
    
