#include "MemManager_t.h"
#include "MemPool_t.h"
#include "MemPage_t.h"

#include <vector>
#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <assert.h>

MemPool_t::MemPool_t()
{
	MemPage_t* page = new MemPage_t();
	if (!page)
	{
        cerr << "Pool:InsertNewPage failure" << endl;
		exit(EXIT_FAILURE);
	}

	m_pool.push_back(page);
	//m_pool.insert(m_pool.end(), page);
}

MemPool_t::~MemPool_t()
{
	for(vector<MemPage_t*>::iterator itr = m_pool.begin(); itr != m_pool.end(); ++itr)
    {
        delete (*itr);
    }
}

void MemPool_t::InsertNewPage()
{
	MemPage_t* page = new MemPage_t();
	if (!page)
	{
        cerr << "Pool:InsertNewPage failure" << endl;
		exit(EXIT_FAILURE);
	}

	m_pool.push_back(page);
}

vector<MemPage_t*>::iterator MemPool_t::GetPage(unsigned int _position)
{
	vector<MemPage_t*>::iterator itr = m_pool.begin();
	unsigned int currentCapacity = (**itr).GetCapacity();

	while (_position >= currentCapacity)
	{
		_position -= currentCapacity;
		++itr;
		currentCapacity = (**itr).GetCapacity();
	}
	
	SetPosition(_position);

	return itr;
}

vector<MemPage_t*>::iterator MemPool_t::GetNextPage(vector<MemPage_t*>::iterator _itr)
{	
	if (_itr == m_pool.end())
	{
		InsertNewPage();
	}

	++_itr;
	SetPosition(0);

	return _itr;
}

unsigned int MemPool_t::Write(const void* _src, size_t _nBytes, unsigned int _position)
{
	if (!_src)
	{
        cerr << "Pool:Write failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (_position > m_actualSize)
	{
        cerr << "Pool:Write failure" << endl;
        return 0;
	}

	SetPosition(_position);

	return Write(_src, _nBytes);
}
/*
unsigned int MemPool_t::Write(const void* _src, size_t _nBytes)
{
	if (!_src)
	{
        cerr << "Pool:Write failure" << endl;
        exit(EXIT_FAILURE);
	}

	if (m_position > m_actualSize)
	{
        cerr << "Pool:Write failure" << endl;
        return 0;
	}

	vector<MemPage_t*>::iterator itr = GetPage(m_position);
	unsigned int bytesWritten = (**itr).Write(_src, _nBytes);

	while(bytesWritten < _nBytes)
	{
		itr = GetNextPage(itr);
		bytesWritten += (**itr).Write((char*)_src + bytesWritten, _nBytes - bytesWritten);
	}

	m_position += bytesWritten;
	m_actualSize = (m_actualSize < m_position) ? m_position : m_actualSize;
}
*/
unsigned int MemPool_t::Read(void* _dest, size_t _nBytes, unsigned int _position)
{
	return 0;
}

	/*
unsigned int MemPool_t::Read(void* _dest, size_t _nBytes)
{
	if (!_dest)
	{
        cerr << "Pool:Read failure" << endl;
        exit(EXIT_FAILURE);
	}
	if (m_position + _nBytes > m_capacity)
	{
        cerr << "Pool:Read failure" << endl;
        exit(EXIT_FAILURE);
	}
	*/
	
	/*
	_nBytes -= WriteToPage(_dest, _nBytes, m_position)
	WriteToNextPagesIfNeeded(_src, _nWrittenBytes);
	
	return 0;
}
	*/



	
