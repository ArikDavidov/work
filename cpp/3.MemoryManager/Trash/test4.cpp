#include <iostream>
using namespace std;

class MemManager_t {
public:
    virtual ~MemManager_t() { cout << "Destructor of MemManager_t" << endl; }
protected:
    MemManager_t() { cout << "Constructor of MemManager_t" << endl; }
    MemManager_t(const MemManager_t& _memManager) { cout << "Copy Constructor of MemManager_t" << endl; }
    MemManager_t & operator=(const MemManager_t& _memManager) { cout << "operator= of MemManager_t" << endl; return *this;}

private:

};

class MemPage_t : public MemManager_t {
public:
    MemPage_t(/*unsigned int _capacity*/) { cout << "Constructor of MemPage_t" << endl; }
    
protected:
    virtual ~MemPage_t() { cout << "Destructor of MemPage_t" << endl; }
};

class MemPool_t : public MemManager_t {
public:
    MemPool_t(/*unsigned int _capacity*/) { cout << "Constructor of MemPool_t" << endl; }
    
protected:
    virtual ~MemPool_t() { cout << "Destructor of MemPool_t" << endl; }
};

MemManager_t* MemManagerCreate(unsigned int _capacity = 512)
{
	//return new MemPage_t;
	return (1024 < _capacity) ? (MemManager_t*)new MemPool_t
							  : (MemManager_t*)new MemPage_t;
}

int main() {

    //object of type MemManager_t can't be constructed
    //MemManager_t* memManager = new MemManager_t; //compilation error

    MemManager_t* memManager = MemManagerCreate(1000);
    //MemManager_t secondManager = *memManager;

    delete memManager;
}





