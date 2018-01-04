#include "String_t.h"

//#include <string.h>
//#include <stdio.h>

#include <iostream>
using namespace std;

int main()
{	
	int cont = 1;					// trigger to stop loop
	unsigned int option; 
	
	while (cont)
	{
		cout << "									\n";
		cout << "Choose option:						\n";
		cout << "1: create vector using version 1	\n";
		cout << "2: create vector using version 2	\n";
		cout << "3: create list using version 1		\n";
		cout << "4: create list using version 2		\n";
		cout << "5: push back						\n";
		cout << "6: empty							\n";
		cout << "7: size							\n";
		cout << "8: front							\n";
		cout << "9: back							\n";
		cout << "10: clear							\n";
		cout << "11: find							\n";
		cout << "12: remove							\n";
		cout << "13: remove and delete				\n";
		cout << "14: remove and delete all			\n";
		cout << "Any another number - stop			\n";

		cin >> option;
		switch (option)
		{
			case 1:
				tContainer_t<int, vector<int*> > container;			break;
			case 2:
				tContainer_t<int, vector> container;
			case 3:
				tContainer_t<int, list<int*> > container;			break;
			case 4:
				tContainer_t<int, list> container					break;
			case 5:
				cout << "\nPlease enter a number:\n";
				int* ip = new int;
				cin >> *ip;
				container.push_back(ip);							break;
			case 6:
				cout << container.empty()
					 << endl;										break;
			case 7:
				cout << container.size()
					 << endl;										break;
			case 8:
				cout << container.front()
					 << endl;										break;
			case 9:
				cout << container.back()
					 << endl;										break;
			case 10:
				container.clear();									break;
 			case 11:
				cout << "\nPlease enter a number to find:\n";
 				int c;
				cin >> c;
				int* cp = ilist11.find(c);
				cout << "found: " << *cp << endl;					break;
			case 12:
				container.remove();									break;
			case 13:
				container.remove();									break;
			case 14:
				container.remove();									break;
			/*
			*/
			default: cont = 0;										break;
		}
	}
	return 0;
}




