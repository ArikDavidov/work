#ifndef __PLAYER_T_H__
#define __PLAYER_T_H__

#include "Card_t.h"
#include "Table_t.h"


#include <vector>
using namespace std;


class Player_t
{
public:
    Player_t(unsigned _ID);
    virtual ~Player_t();
    
    void Attack(Table_t& _table);
    bool AttemptDefend(Table_t& _table);

    void TakeCard(const Card_t* _card);
    void TakeCardsFromTable(Table_t & _table);
    bool IsHandEmpty() const;
    unsigned GetID();

    void PrintHand() const;
    
private:
    unsigned m_ID;
    vector<Card_t*> m_hand;
    int m_numOfCards;
};


inline unsigned Player_t::GetID()
{
	return m_ID;
}


ostream& operator<<(ostream& _os, const Player_t& _player);


#endif /* __PLAYER_T_H__ */

