#ifndef __CARD_T_H__
#define __CARD_T_H__

#include <iostream>
//#include <string>
using namespace std;


class Card_t
{
public:
	Card_t(unsigned _suit, unsigned _rank);
	virtual ~Card_t ();
	
	const unsigned GetSuit() const;
	const unsigned GetRank() const;
	
	static const string GetSuitNotation(const unsigned _suit);
	static const char   GetRankNotation(const unsigned _rank);

private:
	const unsigned m_suit;               // 0...3:
    const unsigned m_rank;               // 0...12:
	static string  m_suitNotationLut[];  // {♣, ♦, ♥, ♠}   //{clubs, diamond, hearts, spades}
    static char    m_rankNotationLut[];  // {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'}
};

ostream& operator<<(ostream& _os, const Card_t& _card);


#endif /* __CARD_T_H__ */





