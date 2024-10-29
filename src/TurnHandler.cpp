#include "TurnHandler.hpp"

#include <ncurses.h>

void TurnHandler::TakeTurn()
{
    m_currentPlayerTurnID++;
}

TurnHandler::TurnHandler(Player players[], int playerCount) : m_playerCount(playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        m_players.push_back(players[i]);
    }
}