#ifndef __ATOMIC_DOG_H__
#define __ATOMIC_DOG_H__

#include <iostream>
#include <unistd.h>         // sleep
#include "Singleton.h"

namespace advcpp
{
	
class Dog
{

friend class Singleton<Dog>;

public:
	static unsigned int dogs;
	unsigned int thisDog;
	
private:
	Dog ()
	{	
		thisDog = ++dogs;
		
		// working .. 
		sleep(1);
		
		std::cout << "dog no. " << thisDog << "constructed\n";
	}
};	
	
unsigned int Dog::dogs = 0;	
	
}


#endif // __ATOMIC_DOG_H__

