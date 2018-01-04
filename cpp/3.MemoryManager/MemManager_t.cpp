#include "MemManager_t.h"
#include "MemPage_t.h"
#include "MemPool_t.h"

#include <iostream>
using namespace std;

#include <stdlib.h>


MemManager_t::MemManager_t()
: m_position(0), m_actualSize(0)
{
	//object of type MemManager_t can't be constructed
}

MemManager_t::~MemManager_t()
{
    //empty DTOR
}

//unsigned int MemManager_t::SetPosition(unsigned int _position)
void MemManager_t::SetPosition(unsigned int _position)
{
	if (_position > m_actualSize)
	{
        throw "MemManager_t:SetPosition failure";
        
        //cerr << "MemManager_t:SetPosition failure" << endl;
        //return m_position;
	}

	unsigned int prevPosition = m_position;

	m_position = _position;

	return prevPosition;
}

/*
MemManager_t::MemManager_t(const MemManager_t& _memManager)
{
	//object of type MemManager_t can't be constructed
}

MemManager_t & MemManager_t::operator=(const MemManager_t& _memManager)
{
    //copy of object of type MemPage_t is forbidden
	return *this;
}
*/





