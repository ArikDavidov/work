#ifndef SINGLETON_H
#define SINGLETON_H

// Reference based implementation
// --------------------------------

class Singleton { 
public: 
	static Singleton& createObj() { return sng; }
	} 
protected: 
	virtual ~Singleton()	{ } 
private: 
	static Singleton sng; 
private: 
	Singleton() { }					// PRIVATE!!!  Doesn't allow to write  -  Singleton s1;
	Singleton(const Singleton&);	// no  copy	   Doesn't allow to write  -  Singleton s2 = s1;
	void operator=(Singleton&);		// no copy	    Doesn't allow to write -  s2 = s1;
}; 

#endif
