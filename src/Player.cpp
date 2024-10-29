#include "Player.hpp"

int Player::getColor()
{
    return m_color;
}

char Player::getSymbol()
{
    return m_symbol;
}

Player::Player(int color, char symbol) : m_color(color), m_symbol(symbol)
{

}