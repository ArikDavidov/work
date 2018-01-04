#ifndef __DECK_T_H__
#define __DECK_T_H__

#include "Card_t.h"

#include <vector>
using namespace std;


class Deck_t
{
public:
    Deck_t(int _nPacks = 1, int _nSuits = 4, int _nRanks = 13);
    Deck_t(const Deck_t& _deck);
    //Deck_t & operator=(const Deck_t& _deck);
    virtual ~Deck_t();
    
    unsigned GetNumOfCards();
    Card_t*  DrawCard();
    void     Shuffle();

private:
    vector<Card_t*> m_deck;
};


inline unsigned Deck_t::GetNumOfCards()
{
	return m_deck.size();
}

#endif /* __DECK_T_H__ */

