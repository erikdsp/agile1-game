#include <iostream>
#include <vector>
#include <string>
// #include <curses.h>

enum TILE {
    EMPTY,
    PLAYER1,
    PLAYER2
};

class Player {
    public:
    std::string name;
    int blasts;    
};

struct Coord
{
    int x;
    int y;
};

int find_valid_row_position(int column, std::vector<std::vector<TILE>> &b);
Coord drop_tile_action(int column, std::vector<std::vector<TILE>> &b, TILE player);
void print_ncurses();
void print_board_test(auto b);

int main()
{
    // game board structure
    std::vector<std::vector<TILE>> board (7, std::vector<TILE>(6, TILE::EMPTY));

    // adding som tiles for testing
    board[0][5] = PLAYER1;
    board[0][4] = PLAYER1;

    // call to drop_tile_action for testing
    drop_tile_action(0, board, PLAYER1);
    drop_tile_action(1, board, PLAYER2);
    drop_tile_action(1, board, PLAYER2);

    // printing for test/debug purpose
    print_board_test(board);

    return 0;
}


int find_valid_row_position(int column, std::vector<std::vector<TILE>> &b)
{
    int first_free_row = -1;
    for (int i = b[column].size() - 1; i >= 0 ; i--)
    {
        if (b[column][i] == EMPTY) 
        {
            first_free_row = i;
            break;
        }
    }
    return first_free_row;  // returns -1 if ther is no available slot
}

Coord drop_tile_action(int column, std::vector<std::vector<TILE>> &b, TILE player)
{   
    Coord tile_drop;
    tile_drop.x = column;
    int row = find_valid_row_position(column, b);
    tile_drop.y = row;  // if row -1 this will also be saved in tile_crop
    if (row >= 0) b[column][row] = player;  // only update b if valid row
    return tile_drop;       
}


void print_board_test(auto b)
{
    for (int y = 0 ; y < b.size() ; y++)
    {
        for (int x = 0 ; x < b[y].size() ; x++)
        {
            std::cout << b[x][y] << " ";
        }
        std::cout << "\n";
    }
}

void print_ncurses()
{
 /*    
 initscr();
    cbreak();
    noecho();

    mvaddch(0, 0, '+');
    mvaddch(LINES - 1, 0, '-');
    mvaddstr(10, 30, "press any key to quit");
    refresh();

    getch();

    endwin();
 */
}
