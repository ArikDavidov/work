#include "virtIO_t.h"

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;


virtIO_t::virtIO_t()
: m_fStatus(cant_open_file_e)
{
}

virtIO_t::virtIO_t(const string& _path, const string& _mode)
: m_fStatus(cant_open_file_e)
{
	m_pFile = fopen(_path.c_str(), _mode.c_str());
	if (0 == m_pFile)
	{
		return;
	}
	
	m_path    = _path;
	m_mode    = _mode;
	m_fStatus = ok_e;
}

virtIO_t::~virtIO_t()
{
	Close();
}

virtIO_t::FileStatus virtIO_t::Open(const string& _path, const string& _mode)
{
	if (m_pFile)
	{
		throw cant_open_file_e;
	}
	
	m_pFile = fopen(_path.c_str(), _mode.c_str());
	if (0 == m_pFile)
	{
		SetFileStatus(cant_open_file_e);
		throw cant_open_file_e;
	}
	
	m_path    = _path;
	m_mode    = _mode;
    m_fStatus = ok_e;
    
    return ok_e;
}

void virtIO_t::Close()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = 0;
		m_fStatus = bad_access_e;
	}
}

long virtIO_t::GetLength() const
{
	if (!m_pFile)
	{
		throw bad_access_e;
	}
	
	long tmp = ftell(m_pFile);
	
	fseek(m_pFile, 0L, SEEK_END);
	long length = ftell(m_pFile);
	
	fseek(m_pFile, tmp, SEEK_SET);
	
	return length;
}

void virtIO_t::ChekIfReadable() const
{
	if(!m_pFile)
	{
		throw bad_access_e;
	}

	if (m_mode == "w" || m_mode == "a" || m_mode == "wb" || m_mode == "ab")
	{
		throw bad_access_e;
	}
}

void virtIO_t::ChekIfWritable() const
{
	if(!m_pFile)
	{
		throw bad_access_e;
	}

	if (m_mode == "r" || m_mode == "rb")
	{
		throw bad_access_e;
	}
}



