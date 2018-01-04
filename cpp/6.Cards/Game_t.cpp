#include "Game_t.h"
//#include "Players_t.h"


#include <iostream>
using namespace std;

Game_t::Game_t(bool _printingMode, int _maxGameCycles)
: m_running(true), m_printingMode(_printingMode), m_maxGameCycles(_maxGameCycles),
  m_turnCount(0)
{
    cout << "Game constructor" << endl;
    //cout << "m_maxGameCycles: " << m_maxGameCycles << endl;
}

Game_t::~Game_t()
{
    cout << "Game destructor" << endl;
}

void Game_t::Init()
{
    cout << "Initialising game" << endl;

    m_deck.Shuffle();

    int nPlayers = m_players.GetNumOfPlayers();
    int nCards = m_deck.GetNumOfCards();

    for (int i = 0; i < nCards; ++i)
    {
        m_players[i % nPlayers]->TakeCard(m_deck.DrawCard());
    }
}

void Game_t::PlayTurn()
{
    cout << "Playing Turn: " << m_turnCount << endl;

    m_attacker = m_players.GetNextAttacker(m_turnCount);
    m_defender = m_players.GetNextDefender(m_turnCount);
    
    m_attacker->Attack(m_table);

    if (m_defender->AttemptDefend(m_table))
    {
        m_table.MoveCardsToDiscardPile();
        ++m_turnCount;
    }
    else
    {
        m_defender->TakeCardsFromTable(m_table);
        //defender looses his turn
        m_turnCount += 2;
    }
}

void Game_t::PrintIfInPintingMode() const
{
    if (!m_printingMode)
    {
        return;
    }

    for (int i = 0; i < m_players.GetNumOfPlayers(); ++i)
    {
        cout << *m_players[i];
    }

    m_table.PrintDiscardPile();
}


void Game_t::CheckState()
{    
    CheckNumOfGameCycles();
    CheckIfPlayersFinished();
}

void Game_t::CheckNumOfGameCycles()
{    
    cout << "CheckState" << endl;

    if ((m_turnCount / m_players.GetNumOfPlayers())  >= m_maxGameCycles)
    {
        m_running = false;
        return;
    }
}

void Game_t::CheckIfPlayersFinished()
{    
    for (int i = 0; i < m_players.GetNumOfPlayers(); ++i)
    {
        if (m_players[i]->IsHandEmpty())
        {
            m_running = false;
            return;
        }
    }
}

void Game_t::DeclareWinners() const
{
    //TODO DeclareWinners when no hand is empty
    for (int i = 0; i < m_players.GetNumOfPlayers(); ++i)
    {
        if (m_players[i]->IsHandEmpty())
        {
            cout << "Player " << m_players[i]->GetID() << " wins!" << endl;
        }
    }
}



