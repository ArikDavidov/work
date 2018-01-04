#ifndef __GAME_T_H__
#define __GAME_T_H__

#include "Players_t.h"
#include "Player_t.h"
#include "Deck_t.h"
#include "Table_t.h"


//#include <iostream>
//using namespace std


class Game_t
{
public:
	Game_t(bool _printingMode, int _maxGameCycles);
	virtual ~Game_t();
	
	void Init();
	void PlayTurn();
	void DeclareWinners() const;
	
	void PrintIfInPintingMode() const;

	bool IsRunning();
	void CheckState();

private:
	void CheckIfPlayersFinished();
	void CheckNumOfGameCycles();

private:
	Player_t* m_attacker;
	Player_t* m_defender;
	Players_t m_players;
	Deck_t    m_deck;
	Table_t   m_table;
	unsigned  m_turnCount;
	unsigned  m_maxGameCycles;
	bool      m_printingMode;
	bool      m_running;
};


inline bool Game_t::IsRunning()
{
	return m_running;
}
		






#endif /* __GAME_T_H__ */

