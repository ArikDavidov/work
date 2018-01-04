#include "Mutex.h"
#include <stdexcept>    // std::runtime_error
//#include <assert.h>
//#include <errno.h>

namespace advcpp
{
namespace sync
{


Mutex::Mutex()
{
    if (pthread_mutex_init(&m_mutex, 0))
    {
        throw std::runtime_error("Mutex Init Failed");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
     if (pthread_mutex_lock(&m_mutex))
     {
         throw std::runtime_error("Mutex Lock Failed");
     }
}

void Mutex::Unlock()
{
    if (pthread_mutex_unlock(&m_mutex))
    {
        throw std::runtime_error("Mutex Unlock Failed");
    }
}


    
}  // namespace sync

}  // namespace advcpp




