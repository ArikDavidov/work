#include "TException_t.h"
##include "iostream"


using namespace std;


foo()
{
	cout << "foo()" << endl;
	TException_t ex("_object", "throwing...", __FILE__, __LINE__);
	throw(ex);
}


int main()
{

	try
	{
		foo();
	}
	catch
	{
		
	}
