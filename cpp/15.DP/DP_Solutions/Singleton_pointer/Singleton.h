#ifndef SINGLETON_H
#define SINGLETON_H

// pointer based implementation
// --------------------------------

class Singleton { 
public: 
	static void Destroy()	{ delete sngPtr; sngPtr = 0; } 
	static Singleton* createObj() { 
		if (sngPtr == 0)	{ sngPtr = new Singleton; } // if already exists can't create one more
			return sngPtr; 
	} 
protected: 
	virtual ~Singleton()	{ } 
private: 
	static Singleton* sngPtr; 
private: 
	Singleton() { }					// PRIVATE!!!  Doesn't allow to write  -  Singleton s1;
	Singleton(const Singleton&);	// no  copy	   Doesn't allow to write  -  Singleton s2 = s1;
	void operator=(Singleton&);		// no copy	    Doesn't allow to write -  s2 = s1;
}; 

#endif
