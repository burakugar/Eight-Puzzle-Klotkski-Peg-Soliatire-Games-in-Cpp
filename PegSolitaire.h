//
// Created by Burak Ugar on 13.12.2021.
//

#ifndef HW5_PEGSOLITAIRE_H
#define HW5_PEGSOLITAIRE_H
#include "BoardGame2D.h"
enum class grid_type // grid type for boards
{
    space = 0,
    peg = 1,
    wall = 2
};
using namespace burak;
using namespace std;
class PegSolitaire: public BoardGame2D{
public:
    PegSolitaire();
    void playAuto() override;
    bool endGame() const override;
    unsigned int boardScore() const override;
    void initialize() override;
    ~PegSolitaire() override = default;
    void playUser( string &command) override;
    void print() const override;
    const vector<vector<grid_type>> &getBoard2() const;
    void setBoard2(const vector<vector<grid_type>> &board);
    vector<vector<grid_type>> getBoard2();
    int check_left(const vector<vector<grid_type>>& board, int i, int j) const; // control functions
    int check_down(const vector<vector<grid_type>>& board, int i, int j) const;
    int check_up(const vector<vector<grid_type>>& board, int i, int j) const;
    int check_right(const vector<vector<grid_type>>& board, int i, int j) const;
    bool check_game_is_done(vector<vector<grid_type>> board) const;
    static int number_of_peg_left(vector<vector<grid_type>> board) ;
    void manage_game(vector<vector<grid_type>> *board, int row, char direction, int col) const;
    static void parse_command(int *row, char *direction, int *col);
    static int calculateScore(vector<vector<grid_type>> board);
private:
    vector<vector<grid_type>> board2 = { // 9x9 board
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall},
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall},
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall},
            {grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg},
            {grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::space, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg},
            {grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::peg},
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall},
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall},
            {grid_type::wall, grid_type::wall, grid_type::wall, grid_type::peg, grid_type::peg, grid_type::peg, grid_type::wall, grid_type::wall, grid_type::wall}};
};
#endif //HW5_PEGSOLITAIRE_H

