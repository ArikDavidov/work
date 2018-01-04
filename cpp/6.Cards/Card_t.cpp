#include "Card_t.h"


string Card_t::m_suitNotationLut[] = {"\xe2\x99\xa3", "\xe2\x99\xa6",
                                      "\xe2\x99\xa5", "\xe2\x99\xa0"};
char   Card_t::m_rankNotationLut[] = {'2', '3', '4', '5', '6', '7',
                                      '8', '9', 'T', 'J', 'Q', 'K', 'A'};


Card_t::Card_t(unsigned _suit, unsigned _rank)
: m_rank(_rank), m_suit(_suit)
{

}

Card_t::~Card_t ()
{

}

const unsigned Card_t::GetSuit() const
{
    return m_suit;
}

const unsigned Card_t::GetRank() const
{
    return m_rank;
}

const string Card_t::GetSuitNotation(const unsigned _suit)
{
    return m_suitNotationLut[_suit];
}

const char Card_t::GetRankNotation(const unsigned _rank)
{
    return m_rankNotationLut[_rank];
}

ostream& operator<<(ostream& _os, const Card_t& _card)
{
    _os << _card.GetSuitNotation(_card.GetSuit()) << " "
        << _card.GetRankNotation(_card.GetRank());

    return _os;
}



