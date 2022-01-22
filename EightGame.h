//
// Created by Burak Ugar on 14.12.2021.
//
#define N 3 /*defining the matrix size */
#ifndef HW5_EIGHTGAME_H
#define HW5_EIGHTGAME_H
#include "BoardGame2D.h"
using namespace burak;
using namespace std;
class EightGame: public BoardGame2D{
public:
    EightGame();
    EightGame(int flagx, int flagy, int is_it_ok);
    void playAuto() override;
    bool endGame() const override;
    unsigned int boardScore() const override;
    void initialize() override;
    ~EightGame() override = default;
    void playUser( string &command) override;
    void print() const override;
    int getFlagX() const;
    void setFlagX(int flagX);
    int getFlagY() const;
    void setFlagY(int flagY);
    int checkSpace(int x, int y) const;
    void controlMove(int x, int y, int direction);
    int getIsitok() const;
    void setIsitok(int);
    unsigned int** get_board() const;
    void set_board(unsigned int** M);
    unsigned int ** create2DArray(unsigned int height, unsigned int width) const;
    void randomize(unsigned int arr[], int n);
    void swap1(unsigned int *a, unsigned int *b);
    bool checkOk(unsigned int *arr2);
    int checkMove(int x, int y,int*);
    int MakeMove(int ret_value, int x, int y);
private:
    unsigned int** M;
    int flag_x;
    int flag_y;
    int isitok;

};


#endif //HW5_EIGHTGAME_H
