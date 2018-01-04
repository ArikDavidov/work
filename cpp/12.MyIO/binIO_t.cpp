#include "binIO_t.h"

#include <stdio.h>

    
binIO_t & binIO_t::operator>>(void* _buf)
{
	ChekIfReadable();
	
	m_writeFlag = false;
	m_buf = _buf;
	
	return *this;
}

binIO_t & binIO_t::operator<<(const void* _buf)
{
	ChekIfWritable();
	
	m_writeFlag = true;
	m_buf = (void*)_buf;
	
	return *this;
}

void binIO_t::operator,(int _len)
{
	if (m_writeFlag)
	{
		ChekIfWritable();
		
		int ret = fwrite(m_buf, 1, _len, m_pFile);
		if (_len != ret)
		{
			SetFileStatus(writeErr_e);
			throw writeErr_e;
		}
	}
	else
	{
		ChekIfReadable();
		
		int ret = fread(m_buf, 1, _len, m_pFile);
		if (_len != ret)
		{
			SetFileStatus(readErr_e);
			throw readErr_e;
		}
	}	
}






