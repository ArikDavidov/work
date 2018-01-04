#include "Players_t.h"

#include <iostream>
using namespace std;

#include <stdlib.h>


Players_t::Players_t(unsigned int _nPlayers)
{
    cout << "Players_t constructor" << endl;

    for (int i = 0; i < _nPlayers; ++i)
    {
        Player_t* player = new Player_t(i);
        if (!player)
        {
            cerr << "Player_t creation faild" << endl;
            exit(EXIT_FAILURE);
        }

        m_players.push_back(player);
    }
}

Players_t::~Players_t ()
{
    cout << "Players_t destructor" << endl;

    for(vector<Player_t*>::iterator itr = m_players.begin(); itr != m_players.end(); ++itr)
    {
        delete (*itr);
    }
}

Player_t* Players_t::GetNextAttacker(const unsigned  _turnCount)
{
    cout << "GetNextAttacker" << endl;

    return m_players[_turnCount % m_players.size()];
}

Player_t* Players_t::GetNextDefender(const unsigned  _turnCount)
{
    cout << "GetNextDefender" << endl;
    
    return m_players[(_turnCount + 1) % m_players.size()];
}

Player_t* Players_t::operator[](const unsigned int _i) const
{
    if (_i >= m_players.size())
    {
        cerr << "Players_t::operator[]: invalid index" << endl;
        exit(EXIT_FAILURE);
    }

	return (Player_t*)m_players[_i];
}





