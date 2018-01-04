#include "Loader.h"

#include <iostream>
using namespace std;


int main ()
{
	Loader loader;
	loader.ObtainSupportedTypes();
	loader.GetHandle("DigitalCat800");
	
	return 0;
}
