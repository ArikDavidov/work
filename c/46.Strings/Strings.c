#include "MyStrings.h"

#include <stddef.h>
#include <string.h>

size_t StrLen(const char* _str)
{
	size_t i = 0;
	
	if (NULL == _str)
	{
		return 0;	
	}
	
	while (_str[i] != '\0')
	{
		++i;
	}
	
	return i;
}

static size_t StrLenRecursive(const char* _str)
{
	if ('\0' == _str[0])
	{
		return 0;
	} 

	return 1 + StrLenRecursive(_str + 1);
}

size_t StrLenRec(const char* _str)
{
	if (NULL == _str)
	{
		return 0;
	} 

	return StrLenRecursive(_str);
}

int StrCompare(const char* _s1, const char* _s2)
{
	int i = 0;
	
	if (NULL == _s1 && NULL == _s2)
	{
		return 0;
	}
	if (NULL == _s1)
	{
		return -_s2[0];
	}
	if (NULL == _s2)
	{
		return _s1[0];
	}
	
	while ('\0' != _s1[i] && '\0' != _s2[i])
	{
		if (_s1[i] != _s2[i])
		{
			break;
		}
		++i;
	}
	
	return _s1[i] - _s2[i];
}

static int StrCompareRecursion(const char* _s1, const char* _s2)
{
	if ((_s1[0] != _s2[0]) || ('\0' == _s1))
	{
		return _s1[0] - _s2[0];
	}
	
	return StrCompareRecursion(_s1 + 1, _s2 +1);	
}

int StrCompareRec(const char* _s1, const char* _s2)
{
	if (NULL == _s1 && NULL == _s2)
	{
		return 0;
	}
	if (NULL == _s1)
	{
		return -_s2[0];
	}
	if (NULL == _s2)
	{
		return _s1[0];
	}
	
	return StrCompareRecursion(_s1, _s2);
}

char* StrCopy(char* _destination, const char* _source)
{
	int i;
	
	if (NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	for (i = 0; '\0' != _source[i]; ++i)
	{
		_destination[i] = _source[i];
	}

	_destination[i] = '\0';
	
	return 0;
}
static void StrCopyRecursive(char* _destination, const char* _source)
{
	if ('\0' == _source[0])
	{
		_destination[0] = '\0';
		return;
	}

	StrCopyRecursive(_destination + 1, _source + 1);
}

char* StrCopyRec(char* _destination, const char* _source)
{
	if (NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	StrCopyRecursive(_destination, _source);

	return _destination;
}

char* StrNCopy(char* _destination, const char* _source, size_t _num)
{
	size_t i;
	
	if (NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	for (i = 0; i < _num && '\0' != _source[i]; ++i)
	{
		_destination[i] = _source[i];
	}
	
	for (i = 0; i < _num; ++i)	/* padding */
	{
		_destination[i] = '\0';
	}
	
	return _destination;
}

static void StrNCopyRecursive(char* _destination, const char* _source, size_t _num)
{
	if (0 == _num + 1)
	{
		return;
	}
	
	_destination[0] = _source[0];

	StrNCopyRecursive(_destination + 1, (_source == '\0') ? '\0' : _source + 1, _num);
}

char* StrNCopyRec(char* _destination, const char* _source, size_t _num)
{
	if (NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	StrNCopyRecursive(_destination, _source, _num);

	return _destination;
}

char* StrConcat(char* _destination, char const* _source)
{
	size_t i;
	
	if (NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	i = strlen(_destination);
	
	StrCopy(_destination + i, _source);

	return _destination;
}

char* StrSubString(char const* _str, char const* _search)
{
	size_t i, stringLen, searchLen;

	if (NULL == _str || NULL == _search)
	{
		return NULL;
	}
	
	stringLen = strlen(_str);
	searchLen = strlen(_search);
		
	for (i = 0; i + searchLen <= stringLen; ++i)
	{
		if (!strncmp(_str + i, _search, searchLen))
		{
			return (char*)_str + i; /* Because returning const */
		}
	}

	return NULL;
}
















