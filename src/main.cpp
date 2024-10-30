#include <iostream>
#include <vector>
#include <string>
#include <curses.h>
#include "Tile.hpp"
#include <sstream>
#include <assert.h>


#define INDV_TILE_H 1 // Rows between every row/value in board when printing
#define INDV_TILE_W 2 // Space between every column/value in board when printing

using Board = std::vector<std::vector<TILE>>;

class Player {
    std::string name;
    int blasts;    
};

void print_ncurses();
void print_board_test(Board b);
char get_player_char_representation(TILE tile);
void update_board_column(Board &board, unsigned int column);
void print_board(Board &board);

int main()
{
    Board board { 7, std::vector<TILE>(6, TILE::EMPTY) };

    WINDOW *window = initscr();

    std::stringstream stream{  };

    board[0][5] = TILE::PLAYER1;
    board[0][4] = TILE::PLAYER2;
    print_board(board);

    stream << "Hello, " << "World!";

    int y, x;
    y = getmaxy(window);
    mvaddstr(y - 1, 0, stream.str().c_str());

    getch();
    
    endwin();

    return 0;
}

void print_board_test(Board b)
{
    for (int y = 0 ; y < 6 ; y++)
    {
        for (int x = 0 ; x < 7 ; x++)
        {
            std::cout << b[x][y] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * This function updates a column to display correct values.
 * @param column The column to be updated
 */
void update_board_column(Board &board, unsigned int column)
{
    assert(column < board.size());
    for (int y = 0; y < board[column].size(); y++)
    {
        mvaddch(y * INDV_TILE_H, column * INDV_TILE_W, get_player_char_representation(board[column][y]));
    }
}

/**
 * Prints or updates the whole board.
 */
void print_board(Board &board)
{
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[x].size(); y++)
        {
            mvaddch(y * INDV_TILE_H, x * INDV_TILE_W, get_player_char_representation(board[x][y]));
        }
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
}

void print_ncurses()
{
    initscr();
    cbreak();
    noecho();

    mvaddch(0, 0, '+');
    mvaddch(LINES - 1, 0, '-');
    mvaddstr(10, 30, "press any key to quit");
    refresh();

    getch();

    endwin();

}
