#include "Game_t.h"

#include <iostream>
using namespace std;


void GameLoop(bool _pintingMode, int _maxGameCycles)
{
	Game_t game(_pintingMode, _maxGameCycles);

	game.Init();

	while (game.IsRunning())
	{
		game.PlayTurn();
		game.PrintIfInPintingMode();
		game.CheckState();
	}

	game.DeclareWinners();
}


int main()
{
	int  maxGameCycles = 3;
	int  option;

	bool cont = true;	// trigger to stop loop
	while (cont)
	{
		cout << "                            \n";
		cout << "Choose option:              \n";
		cout << "1: Run Game                 \n";
		cout << "2: Run Game [printing mode] \n";
		cout << "3: Set max game cycles      \n";
		cout << "Any another number - quit   \n";
		
		cin >> option;
		switch (option)
		{
			case 1:
				GameLoop(0, maxGameCycles);					break;
			case 2:
				GameLoop(1, maxGameCycles);					break;
			case 3:
				cout << "Please enter max game cycles: \n";
				cin >> maxGameCycles;						break;
			
			default: cont = false;							break;
		}
	}

	return 0;
}
