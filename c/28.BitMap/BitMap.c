#include <stdio.h>
#include <stdlib.h>
#include "BitMap.h"

#define SIZE_OF_BYTE 8

struct BitMap_t{
	char*        m_bits;
	unsigned int m_nof;
};

int Calculate(bitwise b, BitMap_t* _bitMap ,  unsigned int _bitNum)
{
	return b(_bitMap, _bitNum);
}

BitMap_t* CreateBM(unsigned int _nof)
{
	BitMap_t* bitMap = NULL;
	
	if(0 == _nof)
	{
		return NULL;
	}
	bitMap = malloc(sizeof(BitMap_t));
	if (NULL != bitMap)
	{
		if (0 == _nof % SIZE_OF_BYTE)
		{
			bitMap->m_bits = calloc(_nof / SIZE_OF_BYTE, sizeof(char));
		}
		else
		{
			bitMap->m_bits = calloc(_nof / SIZE_OF_BYTE + 1, sizeof(char));
		}
		if (NULL == bitMap->m_bits)
		{
			free(bitMap);
		}
		else
		{
			bitMap->m_nof = _nof;
		}
	}
	return bitMap;	
}

void Destroy(BitMap_t* _bitMap)
{
	if(NULL == _bitMap)
	{
		return;
	}	
	free(_bitMap->m_bits);
	_bitMap->m_bits = NULL;
	free(_bitMap);
}

int BitOn(BitMap_t* _bitMap, unsigned int _bitNum)
{
	if(NULL == _bitMap || _bitNum >= _bitMap->m_nof)
	{
		return -1;
	}
	_bitMap->m_bits[_bitNum / SIZE_OF_BYTE] |= 1 << (_bitNum % SIZE_OF_BYTE);
	return 0;
}

int BitOff(BitMap_t* _bitMap, unsigned int _bitNum)
{
	if(NULL == _bitMap || _bitNum >= _bitMap->m_nof)
	{
		return -1;
	}
	_bitMap->m_bits[_bitNum / SIZE_OF_BYTE] &= ~ (1 << (_bitNum % SIZE_OF_BYTE));
	return 0;
}

int IsBitOn(BitMap_t* _bitMap, unsigned int _bitNum)
{
	int res = -1;
	if(NULL == _bitMap || _bitNum >= _bitMap->m_nof)
	{
		return res;
	}
	res = _bitMap->m_bits[_bitNum / SIZE_OF_BYTE] & (1 << (_bitNum % SIZE_OF_BYTE));
	if (0 != res)
	{
		res = 1;
	}
	return res;
}

int PrintBM(BitMap_t* _bitMap)
{
	int i, res = -1;
	if(NULL != _bitMap)
	{
		printf("\nFeatures:");
		for (i = 0; i < _bitMap->m_nof; ++i)
		{
			printf(" %d", IsBitOn(_bitMap, i));
		}
		printf("\n");
		res = 0;
	}
	return res;		
}


