#include <iostream>
using namespace std;

#include <stdlib.h>

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
    MemPage_t(/*unsigned int _capacity*/): m_position(0) { cout << "Constructor of MemPage_t" << endl; }
    
protected:
    virtual ~MemPage_t() { cout << "Destructor of MemPage_t" << endl; }
    unsigned int GetPosition() const { return m_position; }
protected:
    unsigned int m_position;
};

class MemPool_t : public MemManager_t {
public:
    MemPool_t(/*unsigned int _capacity*/) { cout << "Constructor of MemPool_t" << endl; }
    
protected:
    virtual ~MemPool_t() { cout << "Destructor of MemPool_t" << endl; }
};

MemManager_t & MemManagerCreate(unsigned int _capacity = 512)
{
    MemManager_t* memManager = (1024 < _capacity) ? (MemManager_t*)new MemPool_t
                                                  : (MemManager_t*)new MemPage_t;
    if (!memManager)
    {
        cerr << "MemManager_t allocation faild" << endl;
        exit(EXIT_FAILURE);
    }

    return *memManager;
}

void MemManagerDestroy(MemManager_t& _memManager)
{
    delete _memManager;
}


int main() {
    MemManager_t& memManager = MemManagerCreate(1000);
    
    unsigned int p = memManager.GetPosition();
    std::cout << "Position in memory: " << p << endl;

    MemManagerDestroy(memManager);
}





