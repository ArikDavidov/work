#ifndef __BIN_IO_T_H__
#define __BIN_IO_T_H__

#include "virtIO_t.h"

#include <stdio.h>


class binIO_t : public virtIO_t
{
public:
    binIO_t() {  }
    binIO_t(const string& _path, const string& _mode) : virtIO_t(_path, _mode) {  }
    virtual ~binIO_t() {  }
    
    binIO_t & operator>>(void* _buf);
    binIO_t & operator<<(const void* _buf);
    void      operator,(int _len);

    virtual binIO_t& operator<<(char _x)				{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(unsigned char _x)		{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(short _x)				{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(unsigned short _x)		{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(int _x)					{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(unsigned int _x)		{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(long _x)				{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(unsigned long _x)		{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(float _x)				{ *this << &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator<<(double _x)				{ *this << &_x, sizeof(_x); return *this; }
    
    virtual binIO_t& operator>>(char& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(unsigned char& _x)		{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(short& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(unsigned short& _x)		{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(int& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(unsigned int& _x)		{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(long& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(unsigned long& _x)		{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(float& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    virtual binIO_t& operator>>(double& _x)				{ *this >> &_x, sizeof(_x); return *this; }
    
private:
	binIO_t(const binIO_t& _io);
    binIO_t& operator=(const binIO_t& _io);
    
private:
	bool  m_writeFlag;
	void* m_buf;
};




#endif /* __BIN_IO_T_H__ */

