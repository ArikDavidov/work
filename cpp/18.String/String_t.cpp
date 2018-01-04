#include "String_t.h"

#include <stdexcept>    // std::runtime_error
#include <cstring>

namespace advcpp
{


String_t::String_t()
{
	m_buffer = new Buffer<char>;
	m_buffer[0] = '\0';
}

String_t::String_t(const String_t& _str)
{
	m_buffer = new Buffer<char>(_str->m_buffer);
}

String_t::String_t(const char* _str)
{
	if (!_str)
	{
		throw std::runtime_error("Invalid argument");
	}

	unsigned len = strlen(_str);
	m_buffer = new Buffer<char>(len);
	
	for (unsigned i = 0; i < len; ++i)
	{
		m_buffer->Append(_str[i]);
	}
}

String_t::~String_t()
{
		delete m_buffer;
}



// void Append(const T&);
// {
// 	return m_buffer->Size();
// }



}	// namespace advcpp
