#include <dlfcn.h>
#include <iostream>
#include "Agent_t.h"
#include "Hub_t.h"

using namespace std;

int main()
{

	void* handle = dlopen("./DigitalCat.so", RTLD_LAZY);
	Agent_t* (*Create)(const string&, const string&, const string&, const string&,
						const string&, Subject*, const string&);
	void (*Destroy)(Agent_t*);

	Create = (Agent_t* (*)(const string&, const string&, const string&, const string&,
						const string&, Subject*, const string&))dlsym(handle, "CreateObj");
	Destroy = (void (*)(Agent_t*))dlsym(handle, "DestroyObj");

	Hub_t& hub = Hub_t::CreateObj();
	Agent_t* agent = (Agent_t*)Create("1", "DigitalCat800", "12", "20", "123", &hub, "log");
	
	// agent->DoSomething();
	Destroy(agent);
}


