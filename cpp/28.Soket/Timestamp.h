#ifndef __TIME_STAMP_H__
#define __TIME_STAMP_H__

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>      // std::setprecision


namespace net
{


class Timestamp
{
public:
    explicit Timestamp();
    explicit Timestamp(const struct timeval& _tv);
    ~Timestamp();

    operator struct timeval() const;
    Timestamp& operator=(const Timestamp& _tv);
    Timestamp& operator=(const struct timeval& _tv);
    Timestamp& operator-=(const struct timeval& _tv);

private:
    struct timeval m_tv;
};


inline std::ostream& operator<<(std::ostream& _os, const struct timeval& _tv)
{
    _os << _tv.tv_sec << "."
        << std::setfill('0') << std::setw(6) << _tv.tv_usec;
    
    return _os;
}

inline bool operator<=(const struct timeval& _left, const struct timeval& _right)
{
    return timercmp(&_left, &_right, <=);
}

inline Timestamp::operator struct timeval() const
{
    return m_tv;
}

inline Timestamp& Timestamp::operator=(const Timestamp& _ts)
{
    m_tv = _ts.m_tv;

    return *this;
}

inline Timestamp& Timestamp::operator=(const struct timeval& _tv)
{
    m_tv = _tv;

    return *this;
}

inline Timestamp& Timestamp::operator-=(const struct timeval& _tv)
{
    timersub(&m_tv, &_tv, &m_tv);
    
    return *this;
}

inline Timestamp operator-(const struct timeval& _left, const struct timeval& _right)
{
    Timestamp tmp(_left);

    tmp -= _right;
    
    return tmp;
}




}   // namespace net

#endif // __TIME_STAMP_H__


// struct Less {
//         bool operator() (std::tr1::shared_ptr<Socket> _left,
//                                  std::tr1::shared_ptr<Socket> _right) const {
//             return _left->m_sock < _right->m_sock;
//         }
// };