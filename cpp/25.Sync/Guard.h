#ifndef __GUARD_H__
#define __GUARD_H__

#include "Mutex.h"

namespace advcpp
{
namespace sync
{


class Guard
{
public:
    explicit Guard(Mutex& _mutex);
    ~Guard();

private:
    Guard(const Guard&);
    Guard& operator=(const Guard&);

private:
    Mutex& m_mutex;
};

 
 
    
    
}  // namespace sync

}  // namespace advcpp

#endif // __GUARD_H__


