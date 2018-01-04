#include "Timestamp.h"

#include <iomanip>      // std::setprecision

namespace net
{


Timestamp::Timestamp()
{
    gettimeofday(&m_tv, 0);
    // printf("Timestamp ctor: %ld.%06ld\n", m_tv.tv_sec, m_tv.tv_usec);
    std::cout << "Timestamp ctor: " << m_tv.tv_sec << "."
              << std::setfill('0') << std::setw(6) << m_tv.tv_usec
              << std::endl;
}

Timestamp::Timestamp(const struct timeval& _tv)
: m_tv(_tv)
{
    std::cout << "Timestamp ctor(const struct timeval&): " << m_tv << std::endl;
}

Timestamp::~Timestamp()
{
}


}   // namespace net


// static struct timeval* CalculateTimeout(struct timeval* _nextExpiration, struct timeval* _timeout)
// {
//     struct timeval current;
    
//     assert(_nextExpiration);
//     assert(_timeout);
        

//     gettimeofday(&current, 0);

//     printf("current: %ld.%06ld\n", current.tv_sec, current.tv_usec);
    
//     if (timercmp(_nextExpiration, &current, >=))
//     {
//         timersub(&current, _nextExpiration, _timeout);
//     }
//     else
//     {
//          select() will return immediately 
//         timerclear(_timeout);
//     }
    
//     return _timeout;
// }

// static struct timeval* GetTimeout(List* _clients, struct timeval* _timeout)
// {
//     struct timeval* nextExpiration;

//     assert(_clients);
//     assert(_timeout);

//     if (ListIsEmpty(_clients))
//     {0;    /* select() will block */
//     }

//     // NEXT_EXPIRATION(_clients)
//     nextExpiration = GetNextExpiration(_clients);

//     return CalculateTimeout(nextExpiration, _timeout);
// }

