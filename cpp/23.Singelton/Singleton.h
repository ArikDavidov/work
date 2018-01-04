#ifndef __SINGELTON_H__
#define __SINGELTON_H__

#include "Guard.h"


#include <pthread.h>
#include <tr1/memory>   // std::tr1::shared_ptr

namespace advcpp
{
    

template <typename T>
class Singleton
{
public:
    static std::tr1::shared_ptr<T> GetInstance();
	
private:
    explicit Singleton();
    ~Singleton();
	Singleton(const Singleton&);
	T operator=(const Singleton&);

private:
    static std::tr1::shared_ptr<T> m_class;
    static pthread_mutex_t         m_mutex;
    // no need to use volatile because we use builtins
    static int                     m_wasCreated;    
};

template <typename T>
std::tr1::shared_ptr<T> Singleton<T>::m_class;

template <typename T>
pthread_mutex_t Singleton<T>::m_mutex = PTHREAD_MUTEX_INITIALIZER;

template <typename T>
int Singleton<T>::m_wasCreated = 0;


template <typename T>
std::tr1::shared_ptr<T> Singleton<T>::GetInstance()
{ 
    if (!__sync_fetch_and_or(&m_wasCreated, 0))
	{
        Guard guard(&m_mutex);
        
	    if (!__sync_fetch_and_or(&m_wasCreated, 0))
	    {
	        m_class = std::tr1::shared_ptr<T>(new T);
	        __sync_fetch_and_add(&m_wasCreated, 1);
        }
    }
    return m_class;
} 




}  // namespace advcpp

#endif // __SINGELTON_H__








