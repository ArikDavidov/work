#include "Table_t.h"
#include "Card_t.h"

#include <iostream>
#include <vector>
using namespace std;

#include <stdlib.h>


Table_t::Table_t()
{
    cout << "Table_t constructor" << endl;
}

Table_t::~Table_t()
{
    cout << "Table_t destructor" << endl;

    delete m_attackingCard;
    m_attackingCard = 0;
    delete m_defendingCard;
    m_defendingCard = 0;

    for(vector<Card_t*>::iterator itr = m_discardPile.begin(); itr != m_discardPile.end(); ++itr)
    {
        delete (*itr);
    }
}

void Table_t::MoveCardsToDiscardPile()
{
    cout << "MoveCardsToDiscardPile" << endl;

    if (m_attackingCard)
    {
        m_discardPile.push_back(m_attackingCard);
        m_attackingCard = 0;
    }
    if (m_defendingCard)
    {
        m_discardPile.push_back(m_defendingCard);
        m_defendingCard = 0;
    }
}

void Table_t::PrintDiscardPile() const
{
    cout << "DiscardPile : ";

    for (int i = 0; i < m_discardPile.size(); ++i)
    {
        cout << *m_discardPile[i] << " ";
    }
    
    cout << endl;
}









