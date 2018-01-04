#include "Deck_t.h"
//#include "Card_t.h"

#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
using namespace std;

#include <stdlib.h>


Deck_t::Deck_t(int _nPacks, int _nSuits, int _nRanks)
{
    cout << "Deck_t constructor" << endl;

    for (int suit = 0; suit < _nSuits; ++suit)
    {
        for (int rank = 0; rank < _nRanks; ++rank)
        {
            Card_t* card = new Card_t(suit, rank);
            if (!card)
            {
                cerr << "Card creation faild" << endl;
                exit(EXIT_FAILURE);
            }

            cout << *card << " ";

            m_deck.push_back(card);
        }
        cout << endl;
    }
    cout << "m_deck size: " << m_deck.size() << endl;
}

Deck_t::Deck_t(const Deck_t& _deck)
{
    m_deck = _deck.m_deck;
}

Deck_t::~Deck_t()
{
    cout << "Deck_t destructor" << endl;
    for(vector<Card_t*>::iterator itr = m_deck.begin(); itr != m_deck.end(); ++itr)
    {
        delete (*itr);
    }
}

Card_t* Deck_t::DrawCard()
{
    Card_t* tmp = m_deck.back();
    m_deck.pop_back();

    return tmp;
}

void Deck_t::Shuffle()
{
    random_shuffle(m_deck.begin(), m_deck.end());   
}



/*
Deck_t & Deck_t::operator=(const Deck_t& _deck)
{
    if(this == & _deck)
    {
        return *this;
    }

    vector<Card_t*> tmp(_deck.m_deck);

    std::swap(m_deck, tmp);

    return *this;
}
*/











