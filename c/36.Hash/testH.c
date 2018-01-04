#include <stdio.h>

#include "Hash.h"

int main()
{
	size_t size = 8;
	Hash* hash;
	
	hash = HashCreate(size);
	printf("%d\n", HashCapacity(hash));
	HashDestroy(hash);
	
	return 0;
}


/*
struct Hash
{
    int* m_data; 
    size_t m_originalSize;    
    size_t m_hashSize;			 real array size
    size_t m_maxCollisions;		 maximum ofset
    size_t m_numberOfInsertions; Number of elements
    size_t m_totalCollisions;	 total collisions until now
    size_t m_totalInsertion;	 total insertions until now
    size_t m_magicNum;
};
*/

