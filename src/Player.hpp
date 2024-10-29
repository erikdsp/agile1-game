#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

class Player
{

    int getColor();
    char getSymbol();

    Player(int color, char symbol);

private:
    char m_symbol;
    int m_color;
};

#endif