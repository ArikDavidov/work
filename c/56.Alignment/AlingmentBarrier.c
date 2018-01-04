#include <stdio.h>
#include <pthread.h>


struct Foo
{
	unsigned int	m_magic;
	pthread_cond_t	m_cond;
	pthread_mutex_t	m_mutex;
	unsigned int	m_capacity;
	unsigned int	m_capacityCounter;
	unsigned int	m_referenceCounter;
};

struct Bar
{
	unsigned int	m_magic;
	unsigned int	m_capacity;
	unsigned int	m_capacityCounter;
	unsigned int	m_referenceCounter;
	pthread_cond_t	m_cond;
	pthread_mutex_t	m_mutex;
	char 		m_c;
};

struct Coocoo
{
	pthread_cond_t	m_cond;
	pthread_mutex_t	m_mutex;
	unsigned int	m_magic;
	char 		m_c;
	unsigned int	m_capacity;
	unsigned int	m_capacityCounter;
	unsigned int	m_referenceCounter;
};


int main()
{
	struct Foo    f1;
	struct Foo    f2;
	struct Bar    b1;
	struct Bar    b2;
	struct Coocoo c1;
	struct Coocoo c2;

	
	printf("Size of struct Foo:     %d\n", sizeof(f1));
	printf("Size of struct Bar:     %d\n", sizeof(b1));	 
	printf("Size of struct Coocoo:  %d\n", sizeof(c1));
	printf("\n");
	printf("Size of struct Foo:     %d\n", (void*)&f2 - (void*)&f1);
	printf("Size of struct Bar:     %d\n", (void*)&b2 - (void*)&b1);
	printf("Size of struct Coocoo:  %d\n", (void*)&c2 - (void*)&c1);
	printf("\n");
	printf("Size of struct pthread_cond_t: %d\n", sizeof(pthread_cond_t));
	printf("Size of struct pthread_mutex_t: %d\n", sizeof(pthread_mutex_t));

	return 0;
}	 
	 
	 
	 

