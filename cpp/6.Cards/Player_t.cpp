#include "Player_t.h"
#include "Table_t.h"

#include <iostream>
#include <cstdlib>
using namespace std;



Player_t::Player_t(unsigned _ID)
: m_ID(_ID)
{
    cout << "Player_t constructor - ID: " << m_ID << endl;
}

Player_t:: ~Player_t()
{
    cout << "Player_t destructor - ID: " << m_ID << endl;
    for(vector<Card_t*>::iterator itr = m_hand.begin(); itr != m_hand.end(); ++itr)
    {
        delete (*itr);
    }
}

void Player_t::TakeCard(const Card_t* _card)
{
    // TODO sorted insert
    cout << "Player_t - " << m_ID << ": TakeCard: " << *_card << endl;
    m_hand.push_back((Card_t*)_card);
}

void Player_t::Attack(Table_t& _table)
{
    int i = rand() % m_hand.size();        
    Card_t* card = m_hand[i];
    cout << "Player_t - " << m_ID << ": Attacking with: " << *card << endl;
    
    m_hand.erase(m_hand.begin() + i);

    _table.AddCardToAttack(card);
}

bool Player_t::AttemptDefend(Table_t& _table)
{
    Card_t* attackingCard = (Card_t*)_table.GetAttackingCard();
 
    for (int i = 0; i < m_hand.size(); ++i)
    {
        if (m_hand[i]->GetSuit() == attackingCard->GetSuit())
        {
            for (; i < m_hand.size(); ++i)
            {
                if (m_hand[i]->GetRank() > attackingCard->GetRank())
                {
                    cout << "Player_t - " << m_ID << ": Defending with: " << *m_hand[i] << endl;
                    m_hand.erase(m_hand.begin() + i);
                    _table.AddCardToDefence(m_hand[i]);
                    return true;                    
                }
            }

            break;
        }
    }

    return false;
}

void Player_t::TakeCardsFromTable(Table_t & _table)
{
    while (!_table.IsTableEmpty())
    {
        m_hand.push_back((Card_t*)_table.GetCard());
    }
}

bool Player_t::IsHandEmpty() const
{
    return (0 == m_hand.size());
}

void Player_t::PrintHand() const
{
    for (int i = 0; i < m_hand.size(); ++i)
    {
        cout << *m_hand[i] << " ";
    }
}


ostream& operator<<(ostream& _os, const Player_t& _player)
{
    _os << "Player " << ((Player_t&)_player).GetID() << " : ";
    _player.PrintHand();
    _os << endl;

    return _os;
}



