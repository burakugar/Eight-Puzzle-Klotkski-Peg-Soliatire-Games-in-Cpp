//
// Created by Burak Ugar on 13.12.2021.
//

#ifndef HW5_BOARDGAME2D_H
#define HW5_BOARDGAME2D_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
// base class turns into abstract class if there is at least one pure virtual function
namespace burak{
    class BoardGame2D{
    public:
        virtual void playUser(string &command)=0;
        virtual void playUser() final;
        virtual void playAuto()=0;
        virtual void playAutoAll() final;
        virtual bool endGame() const=0;
        virtual unsigned int boardScore() const=0;
        virtual void initialize()=0;
        virtual ~BoardGame2D()=default;
        static void playVector(vector<BoardGame2D*>game);
        virtual void print () const=0 ;
        friend ostream & operator << (ostream & outs, const BoardGame2D* game);
    };


}
#endif //HW5_BOARDGAME2D_H
