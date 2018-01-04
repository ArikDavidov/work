#include "MemManager_t.h"
#include "MemPage_t.h"

#include <iostream>
#include <string.h>
using namespace std;

#include <stdlib.h>


unsigned int MemPage_t::m_defaultCapacity = 6;


MemPage_t::MemPage_t()
: m_capacity(m_defaultCapacity)
{
	m_page = new char[m_capacity];
}

MemPage_t::~MemPage_t()
{
	delete m_page;
}

unsigned int MemPage_t::Write(const void* _src, size_t _nBytes, unsigned int _position)
{
	if (!_src)
	{
        cerr << "Page:Write failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (_position > m_actualSize)
	{
        cerr << "Page:Write failure" << endl;
        return 0;
	}

	SetPosition(_position);

	return Write(_src, _nBytes);
}

unsigned int MemPage_t::Write(const void* _src, size_t _nBytes)
{
	if (!_src)
	{
        cerr << "Page:Write failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (m_position > m_capacity)
	{
        cerr << "Page:Write failure" << endl;
        exit(EXIT_FAILURE);
	}

	unsigned int bytesToCopy = ((m_position + _nBytes) > m_capacity) ? 
									m_capacity - m_position : _nBytes;
	memcpy(m_page + m_position, _src, bytesToCopy);
	
	//update position

	return bytesToCopy;
}

unsigned int MemPage_t::Read(void* _dest, size_t _nBytes, unsigned int _position)
{
	if (!_dest)
	{
        cerr << "Page:Read failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (_position >= m_capacity)
	{
        cerr << "Page:Read failure" << endl;
        return 0;
	}

	SetPosition(_position);

	return Read(_dest, _nBytes);
}

unsigned int MemPage_t::Read(void* _dest, size_t _nBytes)
{
	if (!_dest)
	{
        cerr << "Page:Read failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (m_position >= m_capacity)
	{
        cerr << "Page:Read failure" << endl;
        exit(EXIT_FAILURE);
	}

	unsigned int bytesToCopy = ((m_position + _nBytes) > m_actualSize) ? 
									m_actualSize - m_position : _nBytes;
	memcpy(_dest, m_page + m_position, bytesToCopy);

	//update position
	
	return bytesToCopy;
}


/**********************    static member functions    **********************/


unsigned int MemPage_t::SetDefaultCapacity(unsigned int _defaultCapacity)
{
	unsigned int prevDefaultCapacity = m_defaultCapacity;

	m_defaultCapacity = _defaultCapacity;

	return prevDefaultCapacity;
}

unsigned int MemPage_t::GetDefaultCapacity()
{
	return m_defaultCapacity;
}







