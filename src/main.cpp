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
    std::string name{};
    int blasts;
};

struct Coord
{
    int x;
    int y;
};

struct Turn
{
    Coord coord;
    TILE player_tile;
    Player player_stats{};
};

char get_player_char_representation(TILE tile);
int user_input(Board &board);
bool is_board_full(Board &board);
int find_valid_row_position(int column, Board &b);
void ask_for_player_names(Player &player1, Player &player2);
void display_winner(int winner, Player &player1, Player &player2);
void print_board(Board &board);

Coord drop_tile_action(int column, Board &b, TILE player);
TILE has_four_in_row_tile(Board &b, Coord played_tile);

struct Coord take_turn(TILE currentPlayer, Board &board);

int main()
{
    Turn player1, player2;
    player1.player_tile = PLAYER1;
    player2.player_tile = PLAYER2;
    
    ask_for_player_names(player1.player_stats, player2.player_stats);
    char playAgain;
    srand(time(NULL)); // Needed for rand to not always result in player 2 starting
    do
    {
        Board board { 7, std::vector<TILE>(6, TILE::EMPTY) };
        Turn currentPlayer = rand() % 2 ? player2 : player1;
        TILE winner{ EMPTY };   // there might be a different data structure for this later
        do
        {
            std::cout << currentPlayer.player_stats.name << "'s turn (" << get_player_char_representation(currentPlayer.player_tile) << ")\n";
            
            print_board(board);

            currentPlayer.coord = take_turn(currentPlayer.player_tile, board);

            winner = has_four_in_row_tile(board, currentPlayer.coord);

            currentPlayer = currentPlayer.player_tile == PLAYER1 ? player2 : player1;
        } 
        while (winner == TILE::EMPTY && (is_board_full(board) == false));
        
        print_board(board);

        // Call the function to determine the winner and assign to winner
        display_winner(winner, player1.player_stats, player2.player_stats);
      
        std::cout << "Do you want to play again? (Yes/No): ";
        std::cin >> playAgain;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    } while (playAgain == 'y' || playAgain == 'Y');
    
    std::cout << "Program closing.\n";
    return 0;
}

/**
 * @param currentPlayer Which players currently playing
 * @param Board A reference to the board in which to place a tile
 * @returns Returns which player should place a tile next.
 */
struct Coord take_turn(TILE currentPlayer, Board &board)
{
    Coord res {};
    do
    {
        int input = user_input(board);

        if ((res = drop_tile_action( input - 1, board, currentPlayer )).y < 0)
        {
            std::cout << "Column is full, please choose another column\n";
        }
    }
    while (res.y < 0);

    return res;
}   

/*
 * Helper function for drop_tile_action() 
 * @Param column - selected column, @Param b - board
 */
int find_valid_row_position(int column, Board &b)
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

/**
 * Function to find next free slot in selected column
 * @param column - selected column
 * @param b - board
 * @param player - current player
 * returns Coord with played position - If slot is full Coord.y = -1
 */
Coord drop_tile_action(int column, Board &b, TILE player)
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
    for (int i = 0; i < board.size(); i++)
    {
        std::cout << i + 1 << " ";
    }

    std::cout << '\n';

    for (int y = 0 ; y < board[0].size() ; y++)
    {
        for (int x = 0 ; x < board.size() ; x++)
        {
            std::cout << get_player_char_representation(board[x][y]) << " ";
        }
        std::cout << "\n";
    }
}

int user_input(Board &board)
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

void ask_for_player_names(Player &player1, Player &player2){
    std::cout << "Enter name for Player 1: ";
    std::cin >> player1.name;
    std::cout << "Enter name for Player 2: ";
    std::cin >> player2.name;
}

void display_winner(TILE winner, Player &player1, Player &player2){
    if (winner == PLAYER1)
    {
        std::cout << player1.name << " wins! " << std::endl;
    }
    else if (winner == PLAYER2)
    {
        std::cout << player2.name << " wins! " << std::endl;
    }
    else
    {
        return;
    }
}

/* 
 * function to check for winner after TILE action
 * @param b - the board to be checked, 
 * @param played_tile - function only checks rows/columns/diagonals crossing this tile
 * RETURNS winner if any, else TILE::EMPTY
 */
TILE has_four_in_row_tile(Board &b, Coord played_tile)
{
    int cols = b.size();                // not using global const COLUMNS because vector is dynamic
    int rows = b[played_tile.y].size(); // not using global const ROWS because vector is dynamic
    if (played_tile.x >= cols || played_tile.x < 0) 
    {
        std::cout << "Bad call to has_four_in_row_tile()\n";        // crude error handling
        return TILE::EMPTY;  // bad call - should throw exception
    }
    if (played_tile.y >= rows || played_tile.y < 0) 
    {
        std::cout << "Bad call to has_four_in_row_tile()\n";        // crude error handling
        return TILE::EMPTY;  // bad call - should throw exception
    }
    TILE prev{};
    int count{0};
    int x{};
    int y{};

    // check vertical
    x = played_tile.x;
    prev = EMPTY;
    count = 0;
    for (y = 0 ; y < rows ; y++)
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
    for (x = 0 ; x < cols ; x++)
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
    prev = EMPTY;
    count = 0;
    while(y > 0)                                  // find x, y starting position
    {
        x--;
        y--;   
    }
    if (x >= -(rows-4) && x < cols - 3)           // only check diagonals with four or more tiles
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
    prev = EMPTY;
    count = 0;
    while(y < rows-1)                            // find x, y starting position
    {
        x--;
        y++;   
    }
        if (x >= -(rows-4) && x < cols - 3)       // only check diagonals with four or more tiles
    {
        for ( ; y >= 0 ; x++, y--)
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
    return TILE::EMPTY;
}

bool is_board_full(Board &board)
{
    for (const std::vector<TILE> &column : board)
    {
        for (TILE tile : column)
        {
            if (tile == TILE::EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}