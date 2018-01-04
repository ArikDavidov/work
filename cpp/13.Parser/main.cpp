#include "Parser_t.h"

#include <string>
#include <iostream>
using namespace std;


int main(int argc, char const* argv[])
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " path_0 path_1 ..." << endl;
        return 1;
    }
    
    Parser_t parser;
    
	for (int i = 1; i < argc; ++i)
	{
		cout << "Parsing file: " << argv[i] << endl;
		parser.Parse(argv[i]);
	}
	
	return 0;
}








