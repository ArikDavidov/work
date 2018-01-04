#ifndef __BARRIER_H__
#define __BARRIER_H__

#define BARRIER_MAGIC		0xBADEEEEE
#define IS_BARRIER(B)		((B) && BARRIER_MAGIC == (B)->m_magic)
/*#define HANDLE_ERROR(M)		do{perror(M);return -1;}while(0)*/


typedef struct Barrier Barrier;

typedef void* (*Routine)(void*);


Barrier* BarrierCreate(unsigned int _capacity);

void BarrierDestroy(Barrier* _barrier);
	
int BarrierWait(Barrier* _barrier, void* (*Routine)(void*), void* _context);
	
	
	
	
#endif	/* #ifndef __BARRIER_H__ */	
	
	
	
	
	
	
	
	
	
	
	
	
	

