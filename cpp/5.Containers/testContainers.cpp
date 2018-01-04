#include "Container_t.h"
#include "Vector_t.h"

#include <iostream>
using namespace std;

int main()
{
	Vector_t<int> vec(16, 8);
	
	int* n = new int;
	*n = 5;
	
	vec.Insert(n);
	cout << vec.Find(5) << endl;
	
	return 0;
}
	






