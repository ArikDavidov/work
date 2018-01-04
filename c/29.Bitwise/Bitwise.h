#ifndef __BITWISE_H__
#define __BITWISE_H__

unsigned char Compliment(unsigned char _byte);
unsigned char Rotate(unsigned char _byte, unsigned int _n);
unsigned char SetBits(unsigned char _x, unsigned int _p, unsigned int _n, unsigned char _y);
unsigned int SetBitsFromTo(unsigned int _int, unsigned int _smallIndex, unsigned int _largeIndex, unsigned int _value);
int PrintByte(unsigned char _byte);
int PrintInt(unsigned int _int);

#endif /* __BITWISE_H__ */

