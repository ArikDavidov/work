#ifndef __ASCII_IO_T_H__
#define __ASCII_IO_T_H__

#include "virtIO_t.h"

#include <stdio.h>


class asciiIO_t : public virtIO_t
{
public:
    asciiIO_t() {  }
    asciiIO_t(const string& _path, const string& _mode) : virtIO_t(_path, _mode) {  }
    virtual ~asciiIO_t() {  }

    virtual asciiIO_t& operator<<(char _x)				 	{ return Write(_x, "%c"); }
    virtual asciiIO_t& operator<<(unsigned char _x)			{ return Write(_x, "%uc"); }
    virtual asciiIO_t& operator<<(short _x)					{ return Write(_x, "%d"); }
    virtual asciiIO_t& operator<<(unsigned short _x)		{ return Write(_x, "%u"); }
    virtual asciiIO_t& operator<<(int _x)					{ return Write(_x, "%d"); }
    virtual asciiIO_t& operator<<(unsigned int _x)			{ return Write(_x, "%d"); }
    virtual asciiIO_t& operator<<(long _x)					{ return Write(_x, "%ld"); }
    virtual asciiIO_t& operator<<(unsigned long _x)			{ return Write(_x, "%lu"); }
    virtual asciiIO_t& operator<<(float _x) 				{ return Write(_x, "%f"); }
    virtual asciiIO_t& operator<<(double _x)				{ return Write(_x, "%lf"); }
    
    virtual asciiIO_t& operator>>(char& _dest)              { return Read(_dest, "%c"); }
    virtual asciiIO_t& operator>>(unsigned char& _dest)     { return Read(_dest, "%uc"); }
    virtual asciiIO_t& operator>>(short& _dest)  			{ return Read(_dest, "%d"); }
    virtual asciiIO_t& operator>>(unsigned short& _dest)    { return Read(_dest, "%u"); }
    virtual asciiIO_t& operator>>(int& _dest)     			{ return Read(_dest, "%d"); }
    virtual asciiIO_t& operator>>(unsigned int& _dest)		{ return Read(_dest, "%d"); }
    virtual asciiIO_t& operator>>(long& _dest)				{ return Read(_dest, "%ld"); }
    virtual asciiIO_t& operator>>(unsigned long& _dest)     { return Read(_dest, "%lu"); }
    virtual asciiIO_t& operator>>(float& _dest)				{ return Read(_dest, "%f"); }
    virtual asciiIO_t& operator>>(double& _dest)			{ return Read(_dest, "%lf"); }
    
protected:    
	template <class T> asciiIO_t & Write(const T& _t, string _format);	
    template <class T> asciiIO_t & Read(T& _t, string _format);
    
private:
	asciiIO_t(const asciiIO_t& _io);
    asciiIO_t& operator=(const asciiIO_t& _io);
};

template <class T>
asciiIO_t & asciiIO_t::Write(const T& _t, string _format)
{
	ChekIfWritable();
	
	fprintf(m_pFile, _format.c_str(), _t);
	
	return *this;
}

template <class T>
asciiIO_t & asciiIO_t::Read(T& _t, string _format)
{
	ChekIfReadable();
	
	fscanf(m_pFile, _format.c_str(), &_t);
	
	return *this;
}


#endif /* __ASCII_IO_T_H__ */


