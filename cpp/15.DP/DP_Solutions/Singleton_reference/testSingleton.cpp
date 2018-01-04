#include "Singleton.h"
 
int main() { 
	Singleton& s1 = Singleton::createObj();	// can create many references but to the same object
	Singleton& s2 = Singleton::createObj (); 

	Singleton s3;		// can't be compiled, CTOR is Private
	Singleton s3 = s2;  // can't be compiled, copy CTOR is Private
	s3 = s2;			// can't be compiled, operator= is Private
} 



