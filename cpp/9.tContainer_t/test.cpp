#include "tContainer_t.h"
//#include "t2Container_t.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
using namespace std;



bool IsOdd (int i)
{
  return ((i%2)==1);
}



int main ()
{
	//vector<int> myvector;
	//tContainer_t<int,vector<int> > iArr1;
	
	/*
	myvector.push_back(10);
	myvector.push_back(25);
	myvector.push_back(40);
	myvector.push_back(55);
	
	iArr1.push_back(10);
	iArr1.push_back(25);
	iArr1.push_back(40);
	iArr1.push_back(55);
	
	
	std::vector<int>::iterator it = std::find_if (iArr1.begin(), iArr1.end(), IsOdd);
	std::cout << "The first odd value is " << *it << '\n';
	*/

	tContainer_t<int, vector<int*> > iArr11;
	
	int a = 40;	
	iArr11.push_back(&a);
	
	int i = 40;
	int* ip = iArr11.find(i);
	cout << *ip << endl;

	cout << *iArr11[0] << endl;	

	int* ip2 = iArr11.remove(i);
	cout << *ip2 << endl;
	
	tContainer_t<int, list<int*> > ilist11;
	
	int b = 40;	
	ilist11.push_back(&b);
	
	int c = 40;
	int* cp = ilist11.find(c);
	cout << *cp << endl;

	cout << *ilist11[0] << endl;	
	
		
	return 0;
}


