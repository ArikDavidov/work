#include "Guard.h"

Guard::Guard(pthread_mutex_t* _pMutex)
: m_pMutex(_pMutex)
{
    pthread_mutex_lock(m_pMutex);
}

Guard::~Guard()
{
    pthread_mutex_unlock(m_pMutex);
}



