#include "Building_t.h"
#include "Street_t.h"

#include <iostream>
using namespace std;

int main()
{

	Building_t<int> building(5);
	Building_t<int> tower(3);
	tower = building;
	cout << tower.GetBuildingID() << endl;
	
	return 0;
}
	






