#ifndef __UPDATE_BOARD_HPP__
#define __UPDATE_BOARD_HPP__

#include <vector>
#include <curses.h>
#include <string>
#include "Tile.hpp"

using tile_array = std::vector<std::vector<TILE>>;

class BoardUpdater
{
    struct Vector2 { int x, y; };
public:
    void UpdateColumn(unsigned int column);

    void Print();

    BoardUpdater(tile_array &board, WINDOW *window, Vector2 size );

private:
    char GetToken(TILE tile);

    tile_array &m_board;
    WINDOW *m_window;
    struct Vector2 m_size;
};

#endif