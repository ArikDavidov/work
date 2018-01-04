#include <stdio.h>
#include <limits.h>
#include "Bitwise.h"

const int BITS_IN_INT = sizeof(int) * CHAR_BIT;

unsigned char Compliment(unsigned char _byte)
{
	int i;
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		_byte ^= 1 << i;
	}
	return _byte;
}

unsigned char Rotate(unsigned char _byte, unsigned int _n)
{
	int i, bit;
	
	for (i = 0; i < _n; ++i)
	{
		bit = _byte % 2;
		_byte >>= 1;
		_byte ^= (bit << (CHAR_BIT - 1));
	}
	return _byte;
}

unsigned char SetBits(unsigned char _x, unsigned int _p, unsigned int _n, unsigned char _y)
{
	int i;
	unsigned char num = 0;
	
	if (_p > CHAR_BIT || _n > CHAR_BIT || _n > _p)
	{
		return 0;
	}
	for (i = 0; i < _n; ++i)
	{
		num <<= 1;
		num |= 1;
	}
	/* num = (~ 0) >> (CAR_BIT - _n); */
	_x &= ~ (num << (_p - _n));   
	_x |= (_y & num) << (_p - _n);	
	
	return _x;
}

unsigned int SetBitsFromTo(unsigned int _int, unsigned int _smallIndex, unsigned int _largeIndex, unsigned int _value)
{
	int i;
	unsigned int num = 1;
	
	if (_smallIndex > _largeIndex || _largeIndex > (BITS_IN_INT - 1) || _value > 1)
	{
		return 0;
	}
	for (i = _smallIndex; i < _largeIndex; ++i)
	{
		num <<= 1;
		num |= 1;
	}
	num <<= _smallIndex;
	if (0 == _value)
	{
		_int &= (~ num);
	}
	else
	{
		_int |= num;
	}
	
	return _int;
}

int PrintByte(unsigned char _byte)
{
	int i;

	printf("\n");
	for (i = CHAR_BIT - 1; i >= 0; --i)
	{
		printf("%d", (_byte & (1 << i)) >> i);
	}
	printf("\n");

	return 0;		
}

int PrintInt(unsigned int _int)
{
	int i;

	printf("\n");
	for (i = BITS_IN_INT - 1; i >= 0; --i)
	{
		printf("%d", (_int & (1 << i)) >> i);
	}
	printf("\n");

	return 0;		
}



