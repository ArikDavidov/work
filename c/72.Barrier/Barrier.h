
#define BARRIER_MAGIC		0xBADEEEEE
#define IS_BARRIER(B)		((B) && BARRIER_MAGIC == (B)->m_magic)
/*#define HANDLE_ERROR(M)		do{perror(M);return -1;}while(0)*/


typedef struct Barrier
{
	unsigned int	m_magic;
	unsigned int	m_capacity;
	unsigned int	m_capacityCount;
	unsigned int	m_referenceCounter;
	pthread_cond_t	m_cond;
	pthread_mutex_t	m_mutex;
} Barrier;


Barrier* BarrierCreate(int _capacity);

void BarrierDestroy(Barrier* _barrier);
	
int BarrierWait(Barrier* _barrier);


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

