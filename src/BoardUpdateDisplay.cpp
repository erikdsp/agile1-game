#include "BoardDisplayUpdater.hpp"
#include <assert.h>
#include <ncurses.h>
#include <iostream>

/**
 * @param board A referens to a board.
 * @param window The pointer to the created window
 * @param tile_size The size of a tile
 */
BoardDisplayUpdater::BoardDisplayUpdater( tile_array &board, WINDOW *window, Vector2 tile_size )
    : m_board(board), m_window(window), m_size(tile_size) 
{

}

/**
 * This function updates a column to display correct values.
 * @param column The column to be updated
 */
void BoardDisplayUpdater::UpdateColumn(unsigned int column)
{
    assert(column < m_board.size());
    for (int y = 0; y < m_board[column].size(); y++)
    {
        mvwaddch(m_window, y * m_size.y, column * m_size.x, GetToken(m_board[column][y]));
    }
}

/**
 * Prints or updates the whole board.
 */
void BoardDisplayUpdater::Print()
{
    for (int x = 0; x < m_board.size(); x++)
    {
        for (int y = 0; y < m_board[x].size(); y++)
        {
            mvwaddch(m_window, y * m_size.y, x * m_size.x, GetToken(m_board[x][y]));
        }
    }
}

/**
 * @param tile The tile to get representing token
 * @returns The token according to tile
 */
char BoardDisplayUpdater::GetToken(TILE tile)
{
    switch (tile)
    {
        case TILE::EMPTY:
            return '-';
        case TILE::PLAYER1:
            return 'X';
        case TILE::PLAYER2:
            return 'O';
        default:
            break;
    }
}