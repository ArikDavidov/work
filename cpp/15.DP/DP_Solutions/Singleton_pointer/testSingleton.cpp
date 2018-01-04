#include "Singleton.h"
 
int main() { 
	Singleton* ps1 = Singleton::createObj();	// can create many pointers but to the same object
	Singleton* ps2 = Singleton:: createObj (); 


	Singleton::Destroy();	// was created by static mem-function, so have to be destroyed in similar way

	Singleton s1,s2;	// can't be compiled, CTOR is Private
	Singleton s3 = s2;  // can't be compiled, copy CTOR is Private
	s3 = s2;			// can't be compiled, operator= is Private
} 



