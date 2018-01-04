#include "MyMalloc.h"

#include <stdlib.h>

#define MALLOC_MAGIC		0xAAAA110C
#define MALLOC_CHUNK_MAGIC	0xCAAA222C

struct MyBuffer
{
	size_t		m_magic;
	MyChunk*	m_free;
	size_t		m_chunkSize;
};

struct MyChunk
{
	typedef struct
	{
		size_t		m_magic;
		ChunkMeta*	m_next;
	} ChunkMeta;
	char		m_data[1];
};


void* MyMallocCreate(size_t _chunkSize, size_t NChunks)
{
	MyBuffer* myBuf       = NULL;
	MyChunk* currentChunk = NULL;
	size_t i;
	
	if (0 == _chunkSize || 0 == NChunks)
	{
		return NULL;
	}
	
	myBuf = malloc(sizeof(MyBuffer) + NChunks * ((sizeof(MyChunk) - sizeof(size_t) + _chunkSize)));
	
	myBuf->m_magic = MALLOC_MAGIC;
	myBuf->m_free = myBuf + 1;
	myBuf->m_chunkSize = _chunkSize;
	
	currentChunk = myBuf->m_free;

	for (i = 0; i < NChunks; ++i)
	{
		currentChunk->m_magic = MALLOC_CHUNK_MAGIC;
		currentChunk->m_next  = (char*)&currentChunk->m_data + _chunkSize;
		currentChunk = currentChunk->m_next;
	}
	
	return myBuf->m_free;
}

void* MyMalloc(MyBuffer* _myBuf)
{
	void* tempPtr = NULL;
	
	/* TODO magic */
	tempPtr = &((MyChunk*)_myBuf->m_free)->m_data;
	_myBuf->m_free = ((MyChunk*)_myBuf->m_free)->m_next;
	
	return tempPtr;
}

void MyMallocDestroy(MyBuffer* _myBuf)
{
	free(_myBuf);
}


void MyFree(void* _chunk)
{
	MyChunk* myChunk = NULL;
	
	/* TODO magic */
	myChunk = (char*)_chunk + sizeof(size_t) - sizeof(MyChunk);
	myChunk->

}




