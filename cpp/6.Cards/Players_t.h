#ifndef __PLAYERS_T_H__
#define __PLAYERS_T_H__

#include "Player_t.h"


class Players_t
{
public:
    Players_t(unsigned int _nPlayers = 4);
    virtual ~Players_t();
    
    Player_t* GetNextAttacker(const unsigned  _turnCount);
    Player_t* GetNextDefender(const unsigned  _turnCount);
    Player_t* operator[](const unsigned _i) const;

    unsigned  GetNumOfPlayers() const;

private:
    vector<Player_t*> m_players;
};


inline unsigned Players_t::GetNumOfPlayers() const
{
    return m_players.size();
}


#endif /* __PLAYERS_T_H__ */




