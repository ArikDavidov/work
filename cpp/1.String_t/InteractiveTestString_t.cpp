#include "String_t.h"

//#include <string.h>
//#include <stdio.h>

#include <iostream>
using namespace std;

int main()
{	
	String_t firstString;
	String_t secondString;
	int cont = 1;					// trigger to stop loop
	unsigned int option, i; 
	
	while (cont)
	{
		cout << "                               \n";
		cout << "Choose option:                 \n";
		cout << "1: Insert string               \n";
		cout << "2: Prepend                     \n";
		cout << "3: Convert to lower case       \n";
		cout << "4: Convert to upper case       \n";
		cout << "5: Print i'th character        \n";
		cout << "6: Contains                    \n";
		cout << "7: Length	                    \n";
		cout << "8: Operator =                  \n";
		cout << "9: Operator +=                 \n";
		cout << "10: operator >                 \n";
		/*
		*/
		cout << "Any another number - stop      \n";

		cin >> option;
		switch (option)
		{
			case 1:
				cout << "\nPlease enter the first string:\n";
				cin >> firstString;
				cout << "\nPlease enter the second string:\n";
				cin >> secondString;								break;
			case 2:
				firstString.Prepend(secondString);					break;
			case 3:
				firstString.Lower();								break;
			case 4:
				firstString.Upper();								break;
			case 5:
				cout << "\nPlease enter i:\n";
				cin >> i;
				cout << "\"" << firstString[i] << "\"" 
					 << endl;										break;
			case 6:
				cout << firstString.Contains(secondString)
					 << endl;										break;
			case 7:
				cout << firstString.Length() << endl;				break;
			case 8:
				firstString = secondString;							break;
			case 9:
				firstString += secondString;						break;
			case 10:
				cout << (firstString > secondString)
					 << endl;										break;

			/*
			*/
			default: cont = 0;										break;
		}
		
		cout << "\nFirst string:  " << "\"" << firstString << "\""
			 << "\nSecond string: " << "\"" << secondString << "\""
			 << endl;
	}
	return 0;
}




