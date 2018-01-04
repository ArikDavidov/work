#ifndef __TABLE_T_H__
#define __TABLE_T_H__

#include "Card_t.h"

#include <vector>
using namespace std;


class Table_t
{
public:
    Table_t();
    virtual ~Table_t();

    const Card_t* GetCard();

    void AddCardToAttack(const Card_t* _card);
    void AddCardToDefence(const Card_t* _card);
    const Card_t* GetAttackingCard() const;
    void MoveCardsToDiscardPile();
    bool IsTableEmpty() const;

    void PrintDiscardPile() const;

private:
	Card_t* m_attackingCard;
	Card_t* m_defendingCard;
    vector<Card_t*> m_discardPile;
};


inline bool Table_t::IsTableEmpty() const
{
    return (0 == m_attackingCard);
}

inline const Card_t* Table_t::GetCard()
{
    Card_t* tmp = m_attackingCard;
    m_attackingCard = 0;

    return tmp;
}

inline void Table_t::AddCardToAttack(const Card_t* _card)
{
    m_attackingCard = (Card_t*)_card;
}

inline void Table_t::AddCardToDefence(const Card_t* _card)
{
    m_defendingCard = (Card_t*)_card;
}


inline const Card_t* Table_t::GetAttackingCard() const
{
    return m_attackingCard;
}


#endif /* __TABLE_T_H__ */

