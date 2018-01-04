#include <iostream>
using namespace std;

class MemManager_t {
public:
    virtual ~MemManager_t() { cout << "Destructor of MemManager_t" << endl; }
protected:
    MemManager_t() { cout << "Constructor of MemManager_t" << endl; }
};

class MemPage_t : public MemManager_t {
protected:
    ~MemPage_t() { cout << "Destructor of MemPage_t" << endl; }
};

class MemPool_t : public MemManager_t {
protected:
    ~MemPool_t() { cout << "Destructor of MemPool_t" << endl; }
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

    delete memManager;
}





