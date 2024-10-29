#include <iostream>
#include <vector>
#include <string>
#ifdef _WIN32 // Windows -> Compile with g++ -std=c++20 .\main.cpp -o .\main -lncursesw
    #include <ncurses/ncurses.h>
#else
    #include <curses.h>
#endif

const int ROWS = 6;
const int COLUMNS = 7;

enum TILE {
    EMPTY,
    PLAYER1,
    PLAYER2
};

class Player {
    std::string name;
    int blasts;    
};

void print_ncurses();
void print_board_test(auto b);

int main()
{
    std::vector<std::vector<TILE>> board (7, std::vector<TILE>(6, TILE::EMPTY));
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

int user_Input(int)
{
    int column_to_drop_tile = -1;
    std::cin >> column_to_drop_tile;
    if (column_to_drop_tile <= COLUMNS || column_to_drop_tile > 0)
    {
        return column_to_drop_tile;
    }
    else
    {
        std::cout << "You make doo-doo move please make good move!" << std::endl;
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