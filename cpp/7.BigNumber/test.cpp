#include "BigNumber_t.h"

#include <iostream>
using namespace std;
//#include <string>
//include <cstdio>
//#include <string.h>
//include <ctype.h>


int main()
{
	BigNumber_t bi1("123");
	BigNumber_t bi2(345);
	BigNumber_t bi3(bi1);
		
	cout << bi1;
	cout << bi2;
	cout << bi3;
	
	bi3 = bi2;
	cout << bi3;
	
	bi3 = 17;
	cout << bi3;
	
	return 0;

}


