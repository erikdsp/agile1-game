#include <iostream>
#include <vector>
#include <string>
#include <curses.h>
#include "Tile.hpp"
#include "BoardDisplayUpdater.hpp"

class Player {
    std::string name;
    int blasts;    
};

void print_ncurses();
void print_board_test(auto b);

int main()
{
    std::vector<std::vector<TILE>> board (7, std::vector<TILE>(6, TILE::EMPTY));

    WINDOW *window = initscr();

    BoardDisplayUpdater boardUpdater = { board, window, { 2, 1 } };
    boardUpdater.Print();

    boardUpdater.UpdateColumn(0);

    getch();
    
    endwin();

    return 0;
}

void print_board_test(auto b)
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