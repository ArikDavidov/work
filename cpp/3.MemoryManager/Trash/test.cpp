#include <iostream>
using namespace std;

class MemManager {
public:
    virtual ~MemManager() { cout << "Destructor of MemManager" << endl; }
};

class MemPage : public MemManager {
protected:
    ~MemPage() { cout << "Destructor of MemPage" << endl; }
};

MemManager* MemManagerCreate()
{
	return new MemPage;
}


int main() {
    MemManager * bar = MemManagerCreate();
    delete bar;
}



