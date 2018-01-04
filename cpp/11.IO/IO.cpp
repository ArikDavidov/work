#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


ostream& printLine(ostream& _os)
{
    return _os << "---------------------------------------------------" << endl;
}


int main ()
{
	int numOfInputs(2);
	string ID[numOfInputs];
	string name[numOfInputs];
	
	for (int i = 0; i < numOfInputs; ++i)
	{
		cout << "Please enter ID and name" << endl;
		cin >> ID[i];
		cin >> name[i];
	}
	
    ofstream outFile("outFile");
    outFile.fill('.');
	outFile << "|" << setw(16) << right << "ID" << "|" << setw(32) << "Name" << "|" << endl;
	
	for (int i = 0; i < numOfInputs; ++i)
	{
		outFile << "|" << setw(16) << left << ID << "|" << setw(32) << name << "|" << endl;
	}

	outFile << printLine;
	
	outFile.close();
	
	
	return 0;
}
