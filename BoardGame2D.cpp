//
// Created by Burak Ugar on 13.12.2021.
//
#include <vector>
#include <iostream>
#include "BoardGame2D.h"
// playUser takes a string as a parameter and plays the game accordingly.
// The parameter depends on the game, for the game of Peg Solitaire the string could be “2B UP”

//Another overload of playUser is a final function. It does not take any parameters,
// it takes a string from the user for the next move in a loop and plays the game until it is over.
// It also prints the board between the moves.
void burak::BoardGame2D::playUser() {
    string command;
    //while(!endGame()){
        cout <<"Enter the command :"<< endl;
        cin>> command;
        playUser(command);
    //}
}

// playAutoAll is a final function. It plays the game until it is over. This one calls playAuto for all
//the moves. It also prints the board between the moves after some pause.
void burak::BoardGame2D::playAutoAll() {
    int numb=0;
    while(!endGame()){
        playAuto();

    }
}
// endGame returns true if the game is ended.

//boardScore returns an int score value for the current board. It returns a positive integer that
//indicates the goodness of the current board. Smaller the returned value, better the board. If the game is
//finished for the current board, it returns return 0, which is the best case.


//static playVector function takes a vector of BoardGame2D * objects. It plays all the games in the
//vector until they end.
void burak::BoardGame2D::playVector(vector<BoardGame2D *> game) {
    game[1]->initialize();
    game[1]->playAutoAll();
    game[1]->boardScore();
    game[2]->initialize();
    game[2]->playAutoAll();
    game[2]->boardScore();

}

ostream &burak::operator<<(ostream &outs, const burak::BoardGame2D *game) {
    game->print();
    return outs;
}





