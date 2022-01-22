#include "PegSolitaire.h"
#include "BoardGame2D.h"
#include "EightGame.h"
#include "Klotski.h"
using namespace burak;
using namespace std;
int main(){
    string command,command1;
    BoardGame2D* object = new PegSolitaire;
    BoardGame2D* object1= new PegSolitaire;
    object->initialize();
    object->print();
    object->playUser();
    object->boardScore();
    object->initialize();
    object->playAuto();
    object->print();
    object->boardScore();
    object->initialize();
    object->playUser(command);
    object->print();
    object->initialize();
    object->playAutoAll();
    object->print();
    object->boardScore();


    return 0;
}