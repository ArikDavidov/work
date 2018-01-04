#include "BigNumber_t.h"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

#include <string.h>
#include <ctype.h>


BigNumber_t::BigNumber_t()
: m_str("0")
{
	cout << "BigNumber_t()" << endl;
}


BigNumber_t::BigNumber_t(const char* _str)
: m_str(_str)
{
	if (!IsNum(_str))
	{
		m_str = "0";
	}
	
	cout << "BigNumber_t(const char* _str)" << endl;
}

BigNumber_t::BigNumber_t(const int _n)
: m_str("0")
{
	char buffer[16];
	sprintf(buffer, "%d", _n);
	
	string str(buffer);
	
	swap(str, m_str);
	
	cout << "BigNumber_t(const int _n)" << endl;
}

BigNumber_t::BigNumber_t(const BigNumber_t& _str)
{
	m_str = _str.GetString();
	
	cout << "BigNumber_t(const BigNumber_t& _str)" << endl;
}

BigNumber_t::~BigNumber_t()
{
	cout << "~BigNumber_t()" << endl;
}

const BigNumber_t & BigNumber_t::operator=(const BigNumber_t& _str)
{
	if (this == &_str)
	{
		return *this;
	}

	m_str = _str.GetString();
	
	return *this;
}

const BigNumber_t & BigNumber_t::operator=(const int _n)
{
	*this = BigNumber_t(_n);
	
	return *this;
}





bool BigNumber_t::IsNum(const char* _str) const
{
	int len = strlen(_str);

	for (int i = 0; i < len; ++i)
	{
		if (!isdigit(_str[i]))
		{
			return false;
		}
	}
	
	return true;
}

ostream& operator<<(ostream& _os, const BigNumber_t& _bigNum)
{
    _os << _bigNum.GetString() << endl;

    return _os;
}

