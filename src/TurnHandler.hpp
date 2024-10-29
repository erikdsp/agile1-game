#ifndef __TURN_HANDLER_HPP__
#define __TURN_HANDLER_HPP__

#include <vector>
#include "Player.hpp"

class TurnHandler
{
    TurnHandler(Player players ...);


private:
    std::vector<Player> m_players;

    int m_playerCount;
    int m_currentPlayerTurnID; 
};

#endif