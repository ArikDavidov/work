#include "Buffer_t.h"
#include "String_t.h"

#include <iostream>
using namespace std;

#include <stdio.h>
#include <string.h>		/* strcpy, strlen, strcmp */
#include <ctype.h>		/* tolower, toupper */
#include <assert.h>
#include <strings.h>


unsigned int  String_t::m_numOfString_t   = 0;
bool		  String_t::m_caseSens 	      = 1;


String_t::String_t(const char* _str)
: Buffer_t(_str, strlen(_str) + 1)
{
	++m_numOfString_t;
}

String_t::String_t(const String_t& _st)
{
	++m_numOfString_t;
}

String_t::~String_t()
{
	assert(m_numOfString_t);
	--m_numOfString_t;
}
//movetomycppfunctions
//MyStrDup
	//char* tmp = new char[GetDefaultCapacity()];
	//return strcpy(p, src);
	
	
/*
void String_t::CreateFrom(const char* _str)
{
	if (NULL == _str)
	{
		char* tmp = new char[GetDefaultCapacity()];
		if (!tmp)
		{
			//exception
		}
		
		m_buf = tmp;
		m_buf[0] = '\0';
		m_len = 0;
		m_capacity = GetDefaultCapacity();
	}
	else
	{		
		m_len = strlen(_str);
		m_capacity = GetDefaultCapacity();
		
		ENLARGE_CAPACITY_IF_NEEDED(m_len, m_capacity);

		char* tmp = new char[m_capacity];
		if (!tmp)
		{
			//exception
		}
	
		strcpy(tmp, _str);
		m_buf = tmp;
	}
}
String_t & String_t::operator=(const String_t& _st)
{
	if(this == &_st)
	{
		return *this;
	}

	SetTo(_st.m_buf, _st.m_len);

	return *this;
}
		
void String_t::SetString(const char* _str)
{
	if (!_str)
	{
		return;
	}
	
	SetTo(_str, strlen(_str));
}

void String_t::SetTo(const char* _str, unsigned int _len)
{
	if (!_str)
	{
		return;
	}
	
	if (_len < m_capacity)
	{
		strcpy(m_buf, _str);
		m_len = _len;
	}
	else
	{
		char* p = CreateFrom(_str);
		std::swap(p, m_bufing);
		delete[] m_buf;
	}
}		

void String_t::Append(const char* _str, unsigned int _len)
{
	if (!_str)
	{
		return;
	}
	
	unsigned int newLen = m_len + _len;

	if (newLen < m_capacity)
	{
		strcat(m_buf, _str);
		m_len = newLen;
	}
	else
	{
		unsigned int newCapacity = m_capacity;	
		ENLARGE_CAPACITY_IF_NEEDED(newLen, newCapacity);
	
		char* tmp = new char[newCapacity];
		if (!tmp)
		{
			//exception
		}
		
		strcpy(tmp, m_buf);
		strcat(tmp, _str);
	
		delete m_buf;
	
		m_buf = tmp;
		m_len = newLen;
		m_capacity = newCapacity;
	}
}

String_t & String_t::operator+=(const String_t& _st)
{
	Append(_st.m_buf, _st.m_len);
	
	return *this;
}

String_t & String_t::operator+=(const char* _str)
{
	if (!_str)
	{
		return *this;
	}

	Append(_str, strlen(_str));
	
	return *this;
}

bool String_t::operator<(const String_t& _st) const
{
	return (0 > strcmp(m_buf, _st.m_buf));
}

bool String_t::operator>(const String_t& _st) const
{
	return (0 < strcmp(m_buf, _st.m_buf));
}

bool String_t::operator>=(const String_t& _st) const
{
	return (0 <= strcmp(m_buf, _st.m_buf));
}

bool String_t::operator<=(const String_t& _st) const
{
	return (0 >= strcmp(m_buf, _st.m_buf));
}

bool String_t::operator==(const String_t& _st) const
{
	return (0 == strcmp(m_buf, _st.m_buf));
}

bool String_t::operator!=(const String_t& _st) const
{
	return (0 != strcmp(m_buf, _st.m_buf));
}

const char String_t::operator[](const unsigned int _i) const
{
	if (_i >= strlen(m_buf))
	{
		return '\0';
	}
	
	return m_buf[_i];
}

char & String_t::operator[](const unsigned int _i)
{
	if (_i >= m_len)
	{
		return m_buf[m_len];
	}
	
	return m_buf[_i];
}

const char* String_t::GetString() const
{
	return m_buf;
}

const unsigned int String_t::Length() const
{
	return m_len;
}

int String_t::FindFirst(char _char)
{
	const char* first = strchr(m_buf, _char);
	
	return (!first) ? -1 : (first - m_buf);
}

int String_t::FindLast(char _char)
{
	const char* last = strrchr(m_buf, _char);
	
	return (!last) ? -1 : (last - m_buf);
}

*/


/**  
 * @brief returns substring which starts in 'start' position in original string and has a length 'len'
 * @param[in] _start
 * @param[in] _len
 * @return the string up to the '\0'
 * @retval
 * @warning
 * @example String_t s("123456789");
 *          String_t t = s(3, 4);     ---> "5678"
 *          String_t t = s(300000, 4); ---> ""
 *          String_t t = s(3, 400000); returns the string up to the '\0' ---> "56789"
 */
/*
String_t operator()(int _start, unsigned int _len) const
{
	const char* pSrc = 0;
	unsigned int newLen = m_buf + _start;
	if (_start >= m_len)
	{
		return String_t();
	}	
	else if (_start + _len)
	{
		return String_t(m_buf + _start);
	}
	return String_t(m_buf + _start, _len);
}

void String_t::Upper()
{
	for (unsigned int i = 0; i < m_len; ++i)
	{
		m_buf[i] = (char)toupper(m_buf[i]);
	}
}

void String_t::Lower()
{
	for (unsigned int i = 0; i < m_len; ++i)
	{
		m_buf[i] = (char)tolower(m_buf[i]);
	}
}

bool String_t::Contains(const String_t& _st) const
{
	if (_st.m_buf > m_buf)
	{
		return 0;
	}
	
	return !strstr(m_buf, _st.m_buf) ? 0 : 1;
}

void String_t::Print() const
{
	printf("%s", m_buf);
}

int String_t::Compare(const String_t& _st) const
{
	int ret = strcmp(m_buf, _st.m_buf);

	return (0 == ret) ? 0
					  : (ret < 0 ? 1 : 2);
}

void String_t::Prepend(const String_t& _st)
{
	InsertBefor(_st.m_buf, _st.m_len);
}

void String_t::Prepend(const char* _str)
{
	if (!_str)
	{
		return;
	}

	InsertBefor(_str, strlen(_str));
}
//memmove
void String_t::InsertBefor(const char* _str, unsigned int _len)
{
	if (!_str)
	{
		return;
	}
	
	unsigned int newLen = m_len + _len;
	unsigned int newCapacity = m_capacity;
	
	ENLARGE_CAPACITY_IF_NEEDED(newLen, newCapacity);

	char* tmp = new char[newCapacity];
	if (!tmp)
	{
		return;
	}
	
	strcpy(tmp, _str);
	strcat(tmp, m_buf);
	
	delete[] m_buf;
	
	m_buf = tmp;
	m_len = newLen;
	m_capacity = newCapacity;
}
*/
ostream& operator<<(ostream& _os, const String_t& _st)
{
	_os << _st.GetString();

	return _os;
}

istream& operator>>(istream& _is, String_t& _st)
{
	char buf[128];
	
	_is >> buf;
	_st.SetString(buf);

	return _is;
}

/**********************    static member functions    **********************/


bool String_t::GetCaseSens()
{
	return m_caseSens;
}

bool String_t::SetCaseSens(bool _caseSene)
{
	bool prevCaseSens = m_caseSens;

	m_caseSens = _caseSene;

	return prevCaseSens;
}
















