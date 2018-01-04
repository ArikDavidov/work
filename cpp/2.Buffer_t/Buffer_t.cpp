#include "Buffer_t.h"

#include <string.h>
#include <assert.h>



unsigned int Buffer_t::m_defaultCapacity = 16;
float        Buffer_t::m_growthFactor    = 1.3f;


Buffer_t::Buffer_t(unsigned int _capacity)
: m_numOfChars(0), m_capacity(_capacity)
{
	m_buf = new char[m_capacity];
}

Buffer_t::Buffer_t(const Buffer_t& _buf)
: m_numOfChars(_buf.m_numOfChars), m_capacity(_buf.m_capacity)
{
	m_buf = new char[m_capacity];
	assert(m_buf);

	memcpy(m_buf, _buf.m_buf, m_numOfChars);
}

Buffer_t::Buffer_t(const char* _src, unsigned int _len,
					unsigned int _destOffset = 0)
: m_numOfChars(_len + _destOffset)
{
	m_capacity = CalculateCapacity(m_numOfChars);

	m_buf = new char[m_capacity];
	assert(m_buf);

	memcpy(m_buf + _destOffset, _src, _len);
}

unsigned int Buffer_t::CalculateCapacity(unsigned int _numOfChars)
{
	unsigned int capacity = m_defaultCapacity;

	while (_numOfChars > capacity)
	{
		capacity *= m_growthFactor;
	}

	return capacity;
}

Buffer_t::~Buffer_t()
{
	delete[] m_buf;
}
/*
const char Buffer_t::operator[](const unsigned int _i) const
{
	if (_i >= strlen(m_str))
	{
		return '\0';
	}
	
	return m_str[_i];
}

char & Buffer_t::operator[](const unsigned int _i)
{
	if (_i >= m_numOfChars)
	{
		return m_str[m_numOfChars];
	}
	
	return m_str[_i];
}
*/
/**********************    static member functions    **********************/


unsigned int Buffer_t::GetDefaultCapacity()
{
	return m_defaultCapacity;
}

unsigned int Buffer_t::SetDefaultCapacity(unsigned int _defaultCapacity)
{
	unsigned int prevDefaultCapacity = m_defaultCapacity;

	m_defaultCapacity = _defaultCapacity;

	return prevDefaultCapacity;
}

float Buffer_t::GetGrowthFactor()
{
	return m_growthFactor;
}

float Buffer_t::SetGrowthFactor(float _growthFactor)
{
	float prevGrowthFactor = m_growthFactor;

	m_growthFactor = _growthFactor;

	return prevGrowthFactor;
}



/*

MyStrDup
	char* tmp = new char[GetDefaultCapacity()];
	return strcpy(buf, src);
prepend
	calculate newLen
	newCapacity = EnlargeCapacityIfNeeded(newLen)
		no need to ennlarge
			return memncopy to offset
			void * memmove ( void * destination, const void * source, size_t num );
		need to enlarge
			copy create src, offset, m_numOfChars, 
			void *memccpy(void *dest, const void *src, int c, size_t n);
	memccppy _len - 1 chars to 


Buffer_t::Buffer_t(Buffer_t& _buf, unsigned int _destOffset = 0)
: m_numOfChars(_buf.m_numOfChars + _destOffset)
{
	m_capacity = CalculateCapacity(m_numOfChars);

	m_buf = new char[m_capacity];
	assert(m_buf);

	memcpy(m_buf + _destOffset, _buf.m_buf, _len);
}




Buffer_t::Buffer_t(const char* _src, unsigned int _len,
					int _terminatingChar = 0, unsigned int _destOffset = 0)
{
	unsigned int nCharsToCopy = CalculateNumCharsToCopy(_src, _len, _terminatingChar);	
	m_numOfChars = nCharsToCopy + _offset;

	m_capacity = CalculateCapacity(m_numOfChars);
	m_buf = new char[m_capacity];
	assert(m_buf);

	memcpy(m_buf + _offset, _src, nCharsToCopy);
}

unsigned int CalculateNumCharsToCopy(const char* _src, unsigned int _len, int _terminatingChar)
{
	if (0 > _terminatingChar)
	{
		return _len;
	}

	unsigned int nCharsToCopy = LengthWithTerminator(_src, _terminatingChar);

	return (_len < nCharsToCopy) ? _len : nCharsToCopy;
}
*/
/**
 * @warning If an instance of _terminatingChar is not found,
 * 			the results are unpredictable.
 */
/*
int Buffer_t::LengthWithTerminator(const char* _src, int _terminatingChar)
{
	return rawmemchr(_src, _terminatingChar) - _src + 1;
}
*/























