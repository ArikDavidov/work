#include "ConfigParser_t.h"

#include <iostream>
#include <string>
using namespace std;


int main()
{
	string str("   3fk 	");

	ConfigParser_t parser;
	string trimed = parser.trim(str);

	cout << trimed << "x" << endl;

	return 0;
}

	// parser.parse("config.txt");
