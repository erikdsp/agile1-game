#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "Tile.hpp"

#include <limits>  // Include this for std::numeric_limits
#ifdef _WIN32 // Windows -> Compile with g++ -std=c++20 .\main.cpp -o .\main -lncursesw
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

const int ROWS = 6;
const int COLUMNS = 7;

using Board = std::vector<std::vector<TILE>>;

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

char get_player_char_representation(TILE tile);
void print_board(Board &board);

int user_input(std::vector<std::vector<TILE>>& board);
int find_valid_row_position(int column, std::vector<std::vector<TILE>> &b);
Coord drop_tile_action(int column, std::vector<std::vector<TILE>> &b, TILE player);
TILE has_four_in_row_tile(std::vector<std::vector<TILE>> &b, Coord played_tile);

int main()
{
    Board board { 7, std::vector<TILE>(6, TILE::EMPTY) };
    TILE winner{};

    // adding som tiles for testing
    board[0][5] = PLAYER1;
    board[0][4] = PLAYER1;

    // call to drop_tile_action for testing
    // drop_tile_action(0, board, PLAYER1);
    drop_tile_action(0, board, PLAYER1);
    drop_tile_action(1, board, PLAYER2);
    drop_tile_action(2, board, PLAYER2);
    drop_tile_action(3, board, PLAYER2);
    drop_tile_action(2, board, PLAYER2);
    drop_tile_action(3, board, PLAYER1);
    drop_tile_action(3, board, PLAYER2);
    drop_tile_action(4, board, PLAYER1);
    drop_tile_action(4, board, PLAYER1);
    drop_tile_action(4, board, PLAYER1);
    drop_tile_action(4, board, PLAYER2);

    // drop_tile_action(0, board, PLAYER2);

    // printing for test/debug purpose
    print_board(board);

    // printing for test/debug purpose
    Coord played_tile{4, 2};
    winner = has_four_in_row_tile(board, played_tile);

    std::cout << "The winner is: " << winner << "\n";
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


/**
 * Print the whole board.
 */
void print_board(Board &board)
{
    for (int y = 0 ; y < board[0].size() ; y++)
    {
        for (int x = 0 ; x < board.size() ; x++)
        {
            std::cout << get_player_char_representation(board[x][y]) << " ";
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


// function to check for winner after TILE action
TILE has_four_in_row_tile(std::vector<std::vector<TILE>> &b, Coord played_tile)
{
    int cols = b.size();                // not using global const COLUMNS because vector is dynamic
    int rows = b[played_tile.y].size(); // not using global const ROWS because vector is dynamic
    TILE prev{};
    int count{0};
    int x{};
    int y{};

    // check vertical
    x = played_tile.x;
    prev = EMPTY;
    count = 0;
    for (y = 0 ; y < ROWS ; y++)
        {       
            if (b[x][y] == 0)
            {
                prev = EMPTY;
                count = 0;
            }
            else if (b[x][y] == prev)
            {
                count++;
            }
            else
            {
                prev = b[x][y];
                count = 1;
            }
            if (count == 4) return prev;
        }

    // check horizontal
    y = played_tile.y;
    prev = EMPTY;
    count = 0;
    for (x = 0 ; x < COLUMNS ; x++)
        {
            if (b[x][y] == 0)
            {
                prev = EMPTY;
                count = 0;
            }
            else if (b[x][y] == prev)
            {
                count++;
            }
            else
            {
                prev = b[x][y];
                count = 1;
            }
            if (count == 4) return prev;
        }

    // check diagonal backslash
    x = played_tile.x;
    y = played_tile.y;
    std::cout << "Diagonal backslash:\n";
    while(y > 0)
    {
        x--;
        y--;   
        std::cout << "x: " << x << " y: " << y << "\n"; 
    }
    if (x >= -(rows-4) && x < cols - 3)
    {
        for ( ; y < rows ; x++, y++)
        {   
            if (x < 0 || x > cols-1) {}           // don't read outside of vector
            else if (b[x][y] == 0)
            {
                prev = EMPTY;
                count = 0;
            }
            else if (b[x][y] == prev)
            {
                count++;
            }
            else
            {
                prev = b[x][y];
                count = 1;
            }
            if (count == 4) return prev;
        }
    }

    // check diagonal slash
    x = played_tile.x;
    y = played_tile.y;
    std::cout << "Diagonal slash:\n";
    while(y < rows-1)
    {
        x--;
        y++;   
        std::cout << "x: " << x << " y: " << y << "\n"; 
    }
        if (x >= -(rows-4) && x < cols - 3)
    {
        for ( ; y < rows ; x++, y--)
        {   
            if (x < 0 || x > cols-1) {}           // don't read outside of vector
            else if (b[x][y] == 0)
            {
                prev = EMPTY;
                count = 0;
            }
            else if (b[x][y] == prev)
            {
                count++;
            }
            else
            {
                prev = b[x][y];
                count = 1;
            }
            if (count == 4) return prev;
        }
    }
    //
    return TILE::EMPTY;
}