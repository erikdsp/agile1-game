#include <iostream>
#include <vector>
#include <string>
#include <limits>  // Include this for std::numeric_limits
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

int user_input(std::vector<std::vector<TILE>>& board);

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

int user_input(std::vector<std::vector<TILE>>& board)
{
    int column_to_drop_tile = -1;
    while (true)
    {
        std::cin >> column_to_drop_tile;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (column_to_drop_tile >= 1 && column_to_drop_tile <= COLUMNS)
        {
            if (board[(column_to_drop_tile - 1)][0] == TILE::EMPTY)
            {
                std::cout << "Column " << column_to_drop_tile << " was picked." << std::endl;
                return column_to_drop_tile;
            }
            else
            {
                std::cout << "Column " << column_to_drop_tile << " is invalid or full." << std::endl;
            }
        }
        else 
        {
            std::cout << "Invalid column! Please enter a number between 1 and " << COLUMNS << ".\n";
        }
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