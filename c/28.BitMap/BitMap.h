#ifndef __BITMAP_H__
#define __BITMAP_H__

typedef struct BitMap_t BitMap_t;
typedef int (*bitwise)(BitMap_t*, unsigned int);

int Calculate(bitwise b, BitMap_t* _bitMap, unsigned int _bitNum);
BitMap_t* CreateBM(unsigned int _nof);
void Destroy(BitMap_t* _bitMap);
int BitOn(BitMap_t* _bitMap, unsigned int _bitNum);
int BitOff(BitMap_t* _bitMap, unsigned int _bitNum);
int IsBitOn(BitMap_t* _bitMap, unsigned int _bitNum);
int PrintBM(BitMap_t* _bitMap);

#endif /* __BITMAP_H__ */

