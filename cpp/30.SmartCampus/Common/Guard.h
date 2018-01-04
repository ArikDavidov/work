#ifndef __GUARD_H__
#define __GUARD_H__

#include <pthread.h>


class Guard
{
public:
    explicit Guard(pthread_mutex_t* _nutex);
    virtual ~Guard();

private:
    Guard(const Guard&);
    Guard& operator=(const Guard&);

private:
    pthread_mutex_t* m_pMutex;
};


#endif    // __GUARD_H__


