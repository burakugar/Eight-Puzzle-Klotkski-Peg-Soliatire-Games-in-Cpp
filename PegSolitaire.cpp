//
// Created by Burak Ugar on 13.12.2021.
//
#include "BoardGame2D.h"
#include "PegSolitaire.h"
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>
void PegSolitaire ::playAuto()  {
    std::vector<std::vector<grid_type> > boardb(getBoard2());
    int random_col, random_row, capacity;
    do
    {
        capacity = static_cast<int>(getBoard2().capacity());
        int k = 0;
        int cd, cu, cr, cl, last_shuffle, last_random, last_index;
        std::vector<int> filled_id; // this vector holds the possible moving directions of the given cell as indexes
        auto shuffle_vector = filled_id;
        random_col = rand() % capacity;
        random_row = rand() % capacity;
        do
        {
            random_col = rand() % capacity;
            random_row = rand() % capacity;
            cu = check_up(boardb, random_row, random_col);
            cd = check_down(boardb, random_row, random_col);
            cr = check_right(boardb, random_row, random_col);
            cl = check_left(boardb, random_row, random_col);
        } while (cd + cu + cr + cl == 0 || boardb[random_row][random_col] != grid_type::peg);
        std::vector<int> direction_control = {cr, cl, cd, cu};
        // directions: cr: right, cl: left, cd: down, cu: up
        for (int i = 0; i < 4; i++)
        {
            if (direction_control[i] != 0)
            {
                filled_id.push_back(i);
                k++;
            }
        }

        auto random = std::default_random_engine{};
        std::shuffle(std::begin(shuffle_vector), std::end(shuffle_vector), random);
        last_random = rand() % k;
        last_index = filled_id[last_random];

        if (last_index == 0)
        {
            boardb[random_row][random_col + 2] = boardb[random_row][random_col];
            boardb[random_row][random_col] = grid_type::space;
            boardb[random_row][random_col + 1] = grid_type::space;
        }

        else if (last_index == 1)
        {
            boardb[random_row][random_col - 2] = boardb[random_row][random_col];
            boardb[random_row][random_col] = grid_type::space;
            boardb[random_row][random_col - 1] = grid_type::space;
        }

        else if (last_index == 2)
        {
            boardb[random_row + 2][random_col] = boardb[random_row][random_col];
            boardb[random_row][random_col] = grid_type::space;
            boardb[random_row + 1][random_col] = grid_type::space;
        }
        else if (last_index == 3)
        {
            boardb[random_row - 2][random_col] = boardb[random_row][random_col];
            boardb[random_row][random_col] = grid_type::space;
            boardb[random_row - 1][random_col] = grid_type::space;
        }
        else
            std::cout << "Mistake happened";
        setBoard2(boardb);
        print();
    } while (!(check_game_is_done(boardb)));

    std::cout << "Game is done! Score is: " << calculateScore(boardb);
}

bool PegSolitaire::endGame() const {
    bool res= check_game_is_done(getBoard2());
    return false;
}

unsigned int PegSolitaire::boardScore() const {
    if(check_game_is_done((getBoard2()))){
        return 0;
    }
    else{
        return number_of_peg_left(getBoard2());
    }
}

void PegSolitaire::initialize() {
    print();
}

void PegSolitaire::playUser( string &command) {
    board2= getBoard2();
    do
    {
        print();
        int row,col;
        char direction;
        parse_command(&row, &direction, &col);
        manage_game(&board2, row, direction, col);
        if (number_of_peg_left(board2) == 1)
        {
            std::cout << "You win the game!" << std::endl;
        }
        setBoard2(board2);
    } while (number_of_peg_left(board2) != 0 && !(check_game_is_done(board2)));

    std::cout << "Score is : " << calculateScore(board2);
    std::cout << "The game is over" << std::endl;
}
void PegSolitaire::print() const {
    // function that firstly determines the board type using
    // capacity function then prints it into the screen. Also, it is returning the capacity which is the one dimension of
    //  9

    int ascii;
    int counter = 1;
    vector<vector<grid_type>> board = getBoard2();
    int capacity = static_cast <int>( board.capacity());
       ascii = static_cast<int>('a'); // casting
       cout << std::endl;
        for (int i = 0; i < 9; i++)
        {
            while (i == 0 && ascii != (char)'a' + capacity)
            {
                if (ascii == (char)'a')
                {
                    cout << "  ";
                }
                cout << (char)ascii << "";
                ascii++;
                if (ascii == (char)'a' + capacity)
                {
                    cout << std::endl;
                }
            }
                cout << i + 1 << ' ';
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == grid_type::peg) // pegs are shown as *
                {
                    cout << "P";
                }
                else if (board[i][j] == grid_type::wall) // walls are shown as whitespaces
                {
                    cout << " ";
                }
                else if (board[i][j] == grid_type::space) // spaces are shown as *
                {
                    cout << "*";
                }
            }
                cout << std::endl;
        }
    }

const vector<vector<grid_type>> &PegSolitaire::getBoard2() const {
    return board2;
}

void PegSolitaire::setBoard2(const vector<vector<grid_type>> &board) {
    PegSolitaire::board2 = board;
}

vector<vector<grid_type>> PegSolitaire::getBoard2() {
    return board2;
}

PegSolitaire::PegSolitaire() = default;

int PegSolitaire:: check_left(const std::vector<std::vector<grid_type>>& board, int i, int j) const
// function that checks a given cell of the grid 1,2,3,4 and 5 so that
//whether it has a left move or not
{
    int capacity = static_cast<int>( getBoard2().capacity());                                // capacity of the square matrix as one dimension
    if (j >= 2 && j <= capacity - 1 && i >= 0 && i <= capacity - 1) // a cell has at least this conditions to move in left direction
    {
        if (board[i][j - 1] == grid_type::peg && board[i][j - 2] == grid_type::space)
        {
            return 1; // move is eligible
        }
        else
            return 0;
    }
    else
        return 0;
}
int PegSolitaire:: check_down(const std::vector<std::vector<grid_type>>& board, int i, int j) const
// function that checks a given cell of the grid 1,2,3,4 and 5 so that
//whether it has a down move or not
{
    int capacity = static_cast <int>( getBoard2().capacity());

    if (j >= 0 && j <= capacity - 1 && i >= 0 && i <= capacity - 3) // a cell has at least this conditions to move in down direction
    {
        if (board[i + 1][j] == grid_type::peg && board[i + 2][j] == grid_type::space)
        {
            return 1; // move is eligible
        }
        else
            return 0;
    }
    else
        return 0;
}
int PegSolitaire::check_up(const std::vector<std::vector<grid_type>>& board, int i, int j) const
// function that checks a given cell of the grid 1,2,3,4 and 5 so that
//whether it has an up move or not
{
    int capacity = static_cast<int> (getBoard2().capacity());
    if (j >= 0 && j <= capacity - 1 && i >= 2 && i <= capacity - 1)
    {
        if (board[i - 1][j] == grid_type::peg && board[i - 2][j] == grid_type::space) // a cell has at least this conditions to move in up direction
        {
            return 1; // move is eligible
        }
        else
            return 0;
    }
    else
        return 0;
}
int PegSolitaire:: check_right(const std::vector<std::vector<grid_type>>& board, int i, int j) const
// function that checks a given cell of the grid 1,2,3,4 and 5 so that
//whether it has a right move or not
{
    int capacity = static_cast<int>(getBoard2().capacity());
    if (j >= 0 && j <= capacity - 3 && i >= 0 && i <= capacity - 1)
    {
        if (board[i][j + 1] == grid_type::peg && board[i][j + 2] == grid_type::space) // a cell has at least this conditions to move in right direction
        {
            return 1; // move is eligible
        }
        else
            return 0;
    }
    else
        return 0;
}
bool PegSolitaire:: check_game_is_done(std::vector<std::vector<grid_type>> board) const {                                    // this function takes the board and checks whether there is any move left that a user can make
    int capacity = static_cast<int>( board.capacity()); // takes the capacity of the board
    int total = 1;
    int count = 0, number_of_pegs = 0;
    for (int i = 0; i < capacity; i++)
    {
        for (int j = 0; j < capacity; j++)
        {
            if (board[i][j] == grid_type::peg)
            {
                number_of_pegs++; // if a cell is peg, count it
                total = check_left(board, i, j) + check_right(board, i, j) + check_up(board, i, j) + check_down(board, i, j);
                // checking in every direction of the given cell, if the control functions returns 0 that means
                // there is no move that cell can make
                if (total == 0)
                {
                    count++;
                }
            }
        }
    }
    if (number_of_pegs == count)
    {
        return true; // if all the pegs in the board has no move then game is done
    }
    else
        return false; // else game is not done
}
int PegSolitaire::number_of_peg_left(std::vector<std::vector<grid_type>> board)
// this function takes the board 2 and counts the number of pegs
{
    int capacity = static_cast<int>( board.capacity());
    int count = 0;
    for (int i = 0; i < capacity; ++i)
    {
        for (int j = 0; j < capacity; ++j)
        {
            if (board[i][j] == grid_type::peg)
            {
                count++;
            }
        }
    }
    return count;
}
void PegSolitaire::manage_game(std::vector<std::vector<grid_type>> *board, int row, char direction, int col) const
{
    std::vector<std::vector<grid_type> > temp = *board; // we are copying the initial board
    if (direction == 'R' || direction == 'r')           // if the direction was chosen as right, control the right of the given
        // cell, if it is ok to move right, then make the move
    { // changing the peg's location and make the move
        if (check_right(temp, row, col))
        {
            temp[row][col + 2] = temp[row][col];
            temp[row][col] = grid_type::space;
            temp[row][col + 1] = grid_type::space;
        }
        else
            std::cout << "Please choose a valid move !" << std::endl;
    }
    else if (direction == 'L' || direction == 'l') // if the direction was chosen as left, control the left of the given
        // cell, if it is ok to move left, then make the move,if it has a chance to move than it is making the move
        // and returning 1  indicates that cell has a capability to move which is the knowledge we need to hold stopping
        // the game
    {
        if (check_left(temp, row, col))
        {
            temp[row][col - 2] = temp[row][col];
            temp[row][col] = grid_type::space;
            temp[row][col - 1] = grid_type::space;
        }
        else
            std::cout << "Please choose a valid move !" << std::endl;
    }
    else if (direction == 'U' || direction == 'u') // if the direction was chosen as up, control the up of the given
        // cell, if it is ok to move up, then make the move,if it has a chance to move than it is making the move
        // and returning 1 indicates that cell has a capability to move which is the knowledge we need to hold stopping
        // the game
    {
        if (check_up(temp, row, col))
        {
            temp[row - 2][col] = temp[row][col];
            temp[row][col] = grid_type::space;
            temp[row - 1][col] = grid_type::space;
        }
        else
            std::cout << "Please choose a valid move !" << std::endl;
    }
    else if (direction == 'D' || direction == 'd') // if the direction was chosen as down, control the down of the given
        // cell, if it is ok to move down, then make the move,if it has a chance to move than it is making the move
        // and returning 1 indicates that cell has a capability to move which is the knowledge we need to hold stopping
        // the game
    {
        if (check_down(temp, row, col))
        {
            temp[row + 2][col] = temp[row][col];
            temp[row][col] = grid_type::space;
            temp[row + 1][col] = grid_type::space;
        }
        else
            std::cout << "Please choose a valid move !" << std::endl;
    }
    *board = temp;
}
void PegSolitaire::parse_command(int *row, char *direction, int *col)
{ // this function parse the command as string
    std::string command;
    std::cout << "Enter the command: ";
    std::cin >> command;
    *row = (int)command[1] - '0' - 1; // command will be given as b3-r : first char will be the col number
    // second will be the row number and the last one is direction
    if ((int)command[0] >= 65 && (int)command[0] <= 90)
    {
        *col = (int)command[0] - 'A';
    }
    else if ((int)command[0] >= 97 && (int)command[0] <= 122)
    {
        *col = (int)command[0] - 'a';
    }
    *direction = command[3]; // last one is direction
}
int PegSolitaire::calculateScore(std::vector<std::vector<grid_type>> board)
{ // calculating the number of the pegs that left
    int capacity =static_cast<int>  (board.capacity());
    int count = 0;
    for (int i = 0; i < capacity; i++)
    {
        for (int j = 0; j < capacity; j++)
        {
            if (board[i][j] == grid_type::peg)
            {
                count++;
            }
        }
    }
    return count + 1;
}