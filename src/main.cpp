#include <iostream>
#include <vector>
#include <string>
#include <curses.h>
#include "Tile.hpp"
#include <sstream>
#include <assert.h>

using Board = std::vector<std::vector<TILE>>;

class Player {
    std::string name;
    int blasts;    
};

char get_player_char_representation(TILE tile);
void update_board_column(Board &board, unsigned int column);
void print_board(Board &board);

int main()
{
    Board board { 6, std::vector<TILE>(7, TILE::EMPTY) };

    std::stringstream stream{  };

    // board[1][6] = TILE::PLAYER1;
    // board[5][4] = TILE::PLAYER2;
    
    board[0][1] = TILE::PLAYER1;

    print_board(board);

    return 0;
}

/**
 * Print the whole board.
 */
void print_board(Board &board)
{
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[y].size(); y++)
        {
            std::cout << " " << board[x][y] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * @param tile The tile to get representing token
 * @returns The token according to tile
 */
char get_player_char_representation(TILE tile)
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
    return '-';
}
