//
// Created by Burak Ugar on 17.12.2021.
//

#ifndef HW5_KLOTSKI_H
#define HW5_KLOTSKI_H
#include "BoardGame2D.h"
using namespace burak;
using namespace std;
class Klotski: public BoardGame2D{
public:

    class Object{
    public:
        Object();
        Object(char type, int row, int col, int startPointRow, int startPointCol, char name);
        char getType() const;

        void setType(char type);

        int getRow() const;

        void setRow(int row);

        int getCol() const;

        void setCol(int col);

        int getStartPointRow() const;

        void setStartPointRow(int startPointRow);

        int getStartPointCol() const;

        void setStartPointCol(int startPointCol);

        char getName() const;

        void setName(char name);

    private:
        char type;
        int row;
        int col;
        int start_point_row;
        int start_point_col;
        char name;
    };
    Klotski();
    Klotski(Object **vector);
    void playAuto() override;
    bool endGame() const override;
    bool checkFinish() const;
    unsigned int boardScore() const override;
    void initialize() override;
    ~Klotski() override = default;
    void playUser( string &command) override;
    void print() const override;
    Object** getVector1() const;
    void setVector1( Object** vector1);
    Object ** create2DArray(unsigned int height, unsigned int width) const;
        int MakeMove(int row, int col, char direction);
    void setValues(int new_row, int new_col, int s_point_row, int s_point_col);
private:
    Object** vector;

};

#endif //HW5_KLOTSKI_H
