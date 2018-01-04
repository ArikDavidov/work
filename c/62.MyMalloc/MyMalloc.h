#ifndef __MY_MALLOC_h__
#define __MY_MALLOC_h__

#include <stddef.h>  /* size_t */


typedef struct MyBuffer MyBuffer;
typedef struct MyChunk MyChunk;

void* MyMallocCreate(size_t _chunkSize, size_t _numOfChunks);

void* MyMalloc(MyBuffer* _myBuf);

void MyMallocDestroy(MyBuffer* _myBuf);



#endif /* #ifndef __MY_MALLOC_h__ */


