//
// Created by Burak Ugar on 17.12.2021.
//

#include "Klotski.h"

Klotski::Klotski() {

}

bool Klotski::endGame() const {
    if(!checkFinish())
    return false;
    else
        return true;
}

unsigned int Klotski::boardScore() const {
    int x= rand()%10;
    cout<< x;
    return 0;
}

void Klotski::initialize() {
    cout<< "Enter x-y coordinate and direction : (ex: 01 U)"<<endl;
    Object** temp= create2DArray(5,4);
    vector= create2DArray(5,4);
    temp[0][0]= Object('Y',0,0,0,0,'C');
    temp[0][1]= Object('Z',0,1,0,1,'D');
    temp[0][2]= Object('Z',0,2,0,1,'D');
    temp[0][3]= Object('Y',0,3,0,3,'E');
    temp[1][0]= Object('Y',1,0,0,0,'C');
    temp[1][1]= Object('Z',1,1,0,1,'D');
    temp[1][2]= Object('Z',1,2,0,1,'D');
    temp[1][3]=Object('Y',1,3,0,3,'E');
    temp[2][0]= Object('Y',2,0,2,0,'B');
    temp[2][1]= Object('W',2,1,2,1,'H');
    temp[2][2]= Object('W',2,2,2,1,'H');
    temp[2][3]=Object('Y',2,3,2,3,'F');
    temp[3][0]= Object('Y',3,0,2,0,'B');
    temp[3][1]= Object('X',3,1,3,1,'L');
    temp[3][2]= Object('X',3,2,3,1,'P');
    temp[3][3]=Object('Y',3,3,2,3,'F');
    temp[4][0]= Object('X',4,0,4,0,'A');
    temp[4][1]= Object('S',4,1,4,1,'S');
    temp[4][2]= Object('S',4,2,4,2,'S');
    temp[4][3]= Object('X',4,3,4,3,'G');

    setVector1(temp);
}

void Klotski::playUser( string &command) {
    int x= command[0]-'0';
    int y= command[1]-'0';
    char direction= command[2];
    MakeMove(x,y,direction);
    print();
}
void Klotski::playAuto() {
    srand(time(NULL));
    Object** vector= getVector1();
    int random_x,random_y,random;
    char direction;
    char chararr[4];
    chararr[0]= 'D';
    chararr[1]= 'L';
    chararr[2]= 'R';
    chararr[3]= 'U';
    random_x=  rand()%5;
    random_y= rand()%4;
    random= rand()%4;
    direction= chararr[random];

    do{
        random_x=  rand()%5;
        random_y= rand()%4;
        random= rand()%4;
        direction= chararr[random];
    } while(!(MakeMove(random_x,random_y,direction)) ); 

    print();
}
void Klotski::setValues(int new_row, int new_col,int s_point_row,int s_point_col){
    Object** board= getVector1();
    board[new_row][new_col].setCol(new_col);
    board[new_row][new_col].setRow(new_row);
    board[new_row][new_col].setStartPointCol(s_point_col);
    board[new_row][new_col].setStartPointRow(s_point_row);
}
int Klotski::MakeMove(int row,int col,char direction) {

    Object **temp = getVector1();
    if (temp[row][col].getType() == 'X') { // 1x1 square move control
        if (direction == 'u' || direction == 'U') {
            if (temp[row][col].getRow() == 0) {
                return 0;
            }
            if (temp[temp[row][col].getRow() - 1][col].getType() == 'S') {
                Object temp1('S', row, col, row, col, 'S');
                temp[row - 1][col] = temp[row][col];
                temp[row][col] = temp1;
                setValues(row - 1, col, row - 1, col);
                setVector1(temp);
                return 1;
            }
            return 0;
        } else if (direction == 'd' || direction == 'D') {

            if (temp[row][col].getRow() == 4) {

                return 0;
            }
            if (temp[temp[row][col].getRow() + 1][col].getType() == 'S') {
                Object temp1('S', row, col, row, col, 'S');
                temp[row + 1][col] = temp[row][col];
                temp[row][col] = temp1;
                setValues(row + 1, col, row + 1, col);
                setVector1(temp);
                return 1;
            }
            return 0;
        } else if (direction == 'l' || direction == 'L') {
            if (temp[row][col].getCol() == 0) {
                return 0;
            }

            if (temp[temp[row][col].getCol() - 1][col].getType() == 'S') {
                Object temp1('S', row, col, row, col, 'S');
                temp[row][col - 1] = temp[row][col];
                temp[row][col] = temp1;
                setValues(row, col - 1, row, col - 1);
                setVector1(temp);
                return 1;
            }
            return 0;
        } else if (direction == 'r' || direction == 'R') {
            if (temp[row][col].getCol() == 4) {
                return 0;
            }
            if (temp[temp[row][col].getCol() + 1][col].getType() == 'S') {
                Object temp1('S', row, col, row, col, 'S');
                temp[row][col + 1] = temp[row][col];
                temp[row][col] = temp1;
                setValues(row, col + 1, row, col + 1);
                setVector1(temp);
                return 1;
            }
            return 0;
        }
    } else if (temp[row][col].getType() == 'Y') { // 1x2 square move control
        if (direction == 'u' || direction == 'U')
        {
            if (temp[row][col].getStartPointRow() <=1) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row - 1][col].getType() == 'S') {
                    Object temp1('S', row + 1, col, row + 1, col, 'S');
                    temp[row - 1][col] = temp[row][col];
                    temp[row][col] = temp[row + 1][col];
                    temp[row + 1][col] = temp1;
                    setValues(row - 1, col, row - 1, col);
                    setValues(row, col, row - 1, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;

            } else {
                if (temp[row - 2][col].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    temp[row - 1][col] = temp[row][col];
                    temp[row - 2][col] = temp[row - 1][col];
                    temp[row][col] = temp1;
                    setValues(row - 2, col, row - 2, col);
                    setValues(row - 1, col, row - 2, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }
        } else if (direction == 'd' || direction == 'D') {
            if (temp[row][col].getRow() >=3) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row + 2][col].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    temp[row + 2][col] = temp[row + 1][col];
                    temp[row + 1][col] = temp[row][col];
                    temp[row][col] = temp1;
                    setValues(row + 2, col, row + 1, col);
                    setValues(row + 1, col, row + 1, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else {
                if (temp[row + 1][col].getType() == 'S') {
                    Object temp1('S', row - 1, col, row - 1, col, 'S');
                    temp[row + 1][col] = temp[row][col];
                    temp[row][col] = temp[row - 1][col];
                    temp[row - 1][col] = temp1;
                    setValues(row, col, row, col);
                    setValues(row + 1, col, row, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }

        } else if (direction == 'l' || direction == 'L') {
            if (temp[row][col].getCol() <=1 ) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row][col - 1].getType() == 'S' &&
                    temp[row + 1][col - 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row + 1, col, row, col, 'S');
                    temp[row][col - 1] = temp[row][col];
                    temp[row + 1][col - 1] = temp[row + 1][col];
                    temp[row][col] = temp1;
                    temp[row + 1][col] = temp2;
                    setValues(row, col - 1, row, col - 1);
                    setValues(row + 1, col - 1, row, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else {
                if (temp[row - 1][col - 1].getType() == 'S' &&
                    temp[row][col - 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row - 1, col, row - 1, col, 'S');
                    temp[row][col - 1] = temp[row][col];
                    temp[row - 1][col - 1] = temp[row - 1][col];
                    temp[row][col] = temp1;
                    temp[row - 1][col] = temp2;
                    setValues(col - 1, row - 1, row - 1, col - 1);
                    setValues(col - 1, row, row - 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }
        } else if (direction == 'r' || direction == 'R') {
            if (temp[row][col].getCol() >=2) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row][col + 1].getType() == 'S' &&
                    temp[row + 1][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row + 1, col, row + 1, col, 'S');
                    temp[row][col + 1] = temp[row][col];
                    temp[row + 1][col + 1] = temp[row + 1][col];
                    temp[row][col] = temp1;
                    temp[row + 1][col + 1] = temp2;
                    setValues(row, col + 1, row, col + 1);
                    setValues(row + 1, col + 1, row, col + 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else {
                if (temp[row][col + 1].getType() == 'S' &&
                    temp[row - 1][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row - 1, col, row - 1, col, 'S');
                    temp[row][col + 1] = temp[row][col];
                    temp[row - 1][col + 1] = temp[row - 1][col];
                    temp[row][col] = temp1;
                    temp[row - 1][col] = temp2;
                    setValues(row - 1, col + 1, row - 1, col + 1);
                    setValues(row, col + 1, row - 1, col + 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }
        }
    } else if (temp[row][col].getType() == 'W') { // 2x1 square move control
        if (direction == 'l' || direction == 'L') {
            if (temp[row][col].getStartPointCol() <=1 ) {
                return 0;
            }
            if (temp[row][temp[row][col].getStartPointCol() - 1].getType() == 'S') {
                if (col == temp[row][col].getStartPointCol()) { // current point is the start point
                    Object temp1('S', row, col - 1, row, col - 1, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col - 1] = temp[row][col];
                    temp[row][col] = temp[row][col + 1];
                    temp[row][col + 1] = temp1;
                    setValues(col - 1, row, col - 1, row);
                    setValues(col, row, col - 1, row);
                    setVector1(temp);
                    return 1;
                } else {
                    Object temp1('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col - 2] = temp[row][col - 1];
                    temp[row][col - 1] = temp[row][col];
                    temp[row][col] = temp1;
                    setValues(col - 2, row, col - 2, row);
                    setValues(col - 1, row, col - 2, row);
                    setVector1(temp);
                    return 1;
                }
            }
            return 0;
        } else if (direction == 'r' || direction == 'R') {
            if (temp[row][col].getStartPointCol() >=2) {
                return 0;
            }
            if (temp[row][temp[row][col].getStartPointCol() + 2].getType() == 'S') {
                if (col == temp[row][col].getStartPointCol()) { // current point is the start point
                    Object temp1('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col + 2] = temp[row][col + 1];
                    temp[row][col + 1] = temp[row][col];
                    temp[row][col] = temp1;
                    setValues(row, col + 2, row, col + 2);
                    setValues(row, col + 1, row, col + 2);
                    setVector1(temp);
                    return 1;
                } else {
                    Object temp1('S', row, col - 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col] = temp[row][col - 1];
                    temp[row][col + 1] = temp[row][col];
                    temp[row][col - 1] = temp1;
                    setValues(row, col + 1, row, col + 1);
                    setValues(row, col, row, col + 1);
                    setVector1(temp);
                    return 1;
                }
            }
            return 0;
        } else if (direction == 'u' || direction == 'U') {
            if (temp[row][col].getStartPointRow() >=1) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row - 1][col].getType() == 'S' && temp[row - 1][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row, col + 1, row, col + 1, 'S');
                    temp[row - 1][col] = temp[row][col];
                    temp[row - 1][col + 1] = temp[row][col + 1];
                    temp[row][col] = temp1;
                    temp[row][col + 1] = temp2;
                    setValues(row - 1, col, row - 1, col);
                    setValues(row - 1, col + 1, row - 1, col);
                    setVector1(temp);
                    return 1;
                }
            } else {
                if (temp[row - 1][col].getType() == 'S' && temp[row - 1][col - 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row, col - 1, row, col, 'S');
                    temp[row - 1][col] = temp[row][col];
                    temp[row - 1][col - 1] = temp[row][col - 1];
                    temp[row][col] = temp1;
                    temp[row][col - 1] = temp2;
                    setValues(row - 1, col, row - 1, col - 1);
                    setValues(row - 1, col - 1, row - 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
            }
            return 0;
        } else if (direction == 'D' || direction == 'd') {
            if (temp[row][col].getStartPointRow() >=3) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow()) {
                if (temp[row + 1][col].getType() == 'S' && temp[row + 1][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row, col + 1, row, col, 'S');
                    temp[row + 1][col] = temp[row][col];
                    temp[row + 1][col + 1] = temp[row][col + 1];
                    temp[row][col] = temp1;
                    temp[row][col + 1] = temp2;
                    setValues(row + 1, col, row + 1, col);
                    setValues(row + 1, col + 1, row + 1, col);
                    setVector1(temp);
                    return 1;
                }
            } else {
                if (temp[row + 1][col].getType() == 'S' && temp[row + 1][col - 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S');
                    Object temp2('S', row, col - 1, row, col, 'S');
                    temp[row + 1][col] = temp[row][col];
                    temp[row + 1][col - 1] = temp[row][col - 1];
                    temp[row][col] = temp1;
                    temp[row][col - 1] = temp2;
                    setValues(row + 1, col - 1, row + 1, col - 1);
                    setValues(row + 1, col, row + 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
            }
            return 0;
        }
    }
    else if (temp[row][col].getType() == 'Z') { // 4x4 square move control
        if (direction == 'D' || direction == 'd') {
            if (temp[row][col].getStartPointRow() >= 3) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col].getType() == 'S' && temp[row + 2][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row + 2][col] = temp[row + 1][col];
                    temp[row + 2][col + 1] = temp[row + 1][col + 1];
                    temp[row + 1][col] = temp[row][col];
                    temp[row + 1][col + 1] = temp[row][col + 1];
                    temp[row][col] = temp1;
                    temp[row][col + 1] = temp2;
                    setValues(row + 2, col, row + 1, col);
                    setValues(row + 2, col + 1, row + 1, col);
                    setValues(row + 1, col, row + 1, col);
                    setValues(row + 1, col + 1, row + 1, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col - 1].getType() == 'S' && temp[row + 2][col].getType() == 'S') {
                    Object temp1('S', row, col - 1, row, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row + 2][col - 1] = temp[row + 1][col - 1];
                    temp[row + 2][col] = temp[row + 1][col];
                    temp[row + 1][col - 1] = temp[row][col - 1];
                    temp[row + 1][col] = temp[row][col];
                    temp[row][col - 1] = temp1;
                    temp[row][col] = temp2;
                    setValues(row + 2, col - 1, row + 1, col - 1);
                    setValues(row + 1, col, row + 1, col - 1);
                    setValues(row + 2, col, row + 1, col - 1);
                    setValues(row + 2, col - 1, row + 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row + 1][col - 1].getType() == 'S' && temp[row + 1][col].getType() == 'S') {
                    Object temp1('S', row - 1, col - 1, row - 1, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row - 1, col, row - 1, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row + 1][col - 1] = temp[row][col - 1];
                    temp[row + 1][col] = temp[row][col];
                    temp[row][col] = temp[row - 1][col];
                    temp[row][col - 1] = temp[row - 1][col - 1];
                    temp[row - 1][col - 1] = temp1;
                    temp[row - 1][col] = temp2;
                    setValues(row + 1, col, row + 1, col - 1);
                    setValues(row + 1, col - 1, row + 1, col - 1);
                    setValues(row, col, row + 1, col - 1);
                    setValues(row, col - 1, row + 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row + 1][col].getType() == 'S' && temp[row + 1][col + 1].getType() == 'S') {
                    Object temp1('S', row - 1, col + 1, row - 1, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row - 1, col, row - 1, col + 1, 'S'); // spacelerde row ve col önemli değil
                    temp[row + 1][col] = temp[row][col];
                    temp[row][col + 1] = temp[row - 1][col + 1];
                    temp[row][col] = temp[row - 1][col];
                    temp[row + 1][col + 1] = temp[row][col + 1];
                    temp[row - 1][col + 1] = temp1;
                    temp[row - 1][col] = temp2;
                    setValues(row, col, row, col);
                    setValues(row, col + 1, row, col);
                    setValues(row + 1, col, row, col);
                    setValues(row + 1, col + 1, row, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }

        }
        else if (direction == 'U' || direction == 'u') {
            if (temp[row][col].getStartPointRow()<=1) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col].getType() == 'S' && temp[row + 2][col + 1].getType() == 'S') {
                    Object temp1('S', row + 1, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col] = temp[row][col];
                    temp[row - 1][col + 1] = temp[row][col + 1];
                    temp[row][col + 1] = temp[row + 1][col + 1];
                    temp[row][col] = temp[row + 1][col];
                    temp[row + 1][col] = temp1;
                    temp[row + 1][col + 1] = temp2;
                    setValues(row - 1, col, row - 1, col);
                    setValues(row - 1, col + 1, row - 1, col);
                    setValues(row, col + 1, row - 1, col);
                    setValues(row, col, row - 1, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col - 1].getType() == 'S' && temp[row + 2][col].getType() == 'S') {
                    Object temp1('S', row + 1, col - 1, row + 1, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col, row + 1, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col - 1] = temp[row][col - 1];
                    temp[row - 1][col] = temp[row][col];
                    temp[row][col - 1] = temp[row + 1][col - 1];
                    temp[row][col] = temp[row + 1][col];
                    temp[row + 1][col - 1] = temp1;
                    temp[row + 1][col] = temp2;
                    setValues(row - 1, col - 1, row - 1, col - 1);
                    setValues(row - 1, col, row - 1, col - 1);
                    setValues(row, col - 1, row - 1, col - 1);
                    setValues(row, col, row - 1, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row - 2][col - 1].getType() == 'S' && temp[row - 2][col - 1].getType() == 'S') {
                    Object temp1('S', row, col - 1, row, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 2][col - 1] = temp[row - 1][col - 1];
                    temp[row - 2][col] = temp[row - 1][col];
                    temp[row - 1][col - 1] = temp[row][col - 1];
                    temp[row - 1][col] = temp[row][col];
                    temp[row][col - 1] = temp1;
                    temp[row][col] = temp2;
                    setValues(row - 2, col - 1, row - 2, col - 1);
                    setValues(row - 2, col, row - 2, col - 1);
                    setValues(row - 1, col - 1, row - 2, col - 1);
                    setValues(row - 1, col, row - 2, col - 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row - 2][col].getType() == 'S' && temp[row - 2][col + 1].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col + 1, row, col + 1, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 2][col] = temp[row - 1][col];
                    temp[row - 1][col] = temp[row][col];
                    temp[row - 2][col + 1] = temp[row - 1][col + 1];
                    temp[row - 1][col + 1] = temp[row][col + 1];
                    temp[row][col] = temp1;
                    temp[row][col + 1] = temp2;
                    setValues(row - 2, col, row - 2, col);
                    setValues(row - 1, col, row - 2, col);
                    setValues(row - 2, col + 1, row - 2, col);
                    setValues(row - 1, col + 1, row - 2, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }

        }
        else if (direction == 'L' || direction == 'l') {
            if (temp[row][col].getStartPointCol() <= 1) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row][col - 1].getType() == 'S' && temp[row + 1][col - 1].getType() == 'S') {
                    Object temp1('S', row, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col - 1] = temp[row][col];
                    temp[row + 1][col - 1] = temp[row + 1][col];
                    temp[row + 1][col] = temp[row + 1][col + 1];
                    temp[row][col] = temp[row][col + 1];
                    temp[row][col + 1] = temp1;
                    temp[row + 1][col + 1] = temp2;
                    setValues(row + 1, col, row, col - 1);
                    setValues(row + 1, col - 1, row, col - 1);
                    setValues(row, col - 1, row, col - 1);
                    setValues(row, col, row, col - 1);
                    return 1;
                }
                return 0;
            } else if (row == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col - 1].getType() == 'S' && temp[row + 2][col].getType() == 'S') {
                    Object temp1('S', row, col, row + 1, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col, row + 1, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col - 2] = temp[row][col - 1];
                    temp[row][col - 1] = temp[row][col];
                    temp[row + 1][col - 2] = temp[row + 1][col - 1];
                    temp[row + 1][col - 1] = temp[row + 1][col];
                    temp[row][col] = temp1;
                    temp[row + 1][col] = temp2;
                    setValues(row, col - 2, row - 1, col - 1);
                    setValues(row, col - 1, row - 1, col - 1);
                    setValues(row + 1, col - 2, row - 1, col - 1);
                    setValues(row + 1, col - 1, row - 1, col - 1);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row - 2][col - 1].getType() == 'S' && temp[row - 2][col - 1].getType() == 'S') {
                    Object temp1('S', row - 1, col, row, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col - 2] = temp[row - 1][col - 1];
                    temp[row][col - 2] = temp[row][col - 1];
                    temp[row][col - 1] = temp[row][col];
                    temp[row - 1][col - 1] = temp[row - 1][col];
                    temp[row - 1][col] = temp1;
                    temp[row][col] = temp2;
                    setValues(row - 1, col - 2, row - 1, col - 2);
                    setValues(row, col - 2, row - 1, col - 2);
                    setValues(row, col - 1, row - 1, col - 2);
                    setValues(row - 1, col - 1, row - 1, col - 2);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row - 2][col].getType() == 'S' && temp[row - 2][col + 1].getType() == 'S') {
                    Object temp1('S', row - 2, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row - 1, col + 1, row, col + 1, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col - 1] = temp[row - 1][col];
                    temp[row - 2][col - 1] = temp[row - 2][col];
                    temp[row - 2][col] = temp[row - 2][col + 1];
                    temp[row - 1][col] = temp[row - 1][col + 1];
                    temp[row - 2][col + 1] = temp1;
                    temp[row - 1][col + 1] = temp2;
                    setValues(row - 1, col - 1, row - 1, col - 2);
                    setValues(row, col - 2, row - 1, col - 2);
                    setValues(row - 1, col - 1, row - 1, col - 2);
                    setValues(row, col - 1, row - 1, col - 2);
                    return 1;
                }
                return 0;
            }
        }
        else if (direction == 'R' || direction == 'r') {
            if (temp[row][col].getStartPointCol() >= 2) {
                return 0;
            }
            if (row == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row][col + 2].getType() == 'S' && temp[row + 1][col + 2].getType() == 'S') {
                    Object temp1('S', row, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col + 2] = temp[row][col + 1];
                    temp[row + 1][col + 2] = temp[row + 1][col + 1];
                    temp[row][col + 1] = temp[row][col];
                    temp[row + 1][col + 1] = temp[row + 1][col];
                    temp[row][col] = temp1;
                    temp[row + 1][col] = temp2;
                    setValues(row, col + 2, row, col + 1);
                    setValues(row + 1, col + 2, row, col + 1);
                    setValues(row, col + 1, row, col + 1);
                    setValues(row + 1, col + 1, row, col + 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row + 2][col - 1].getType() == 'S' && temp[row + 2][col].getType() == 'S') {
                    Object temp1('S', row, col - 1, row + 1, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row + 1, col - 1, row + 1, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row][col + 1] = temp[row][col];
                    temp[row + 1][col + 1] = temp[row + 1][col];
                    temp[row + 1][col] = temp[row + 1][col - 1];
                    temp[row][col] = temp[row][col - 1];
                    temp[row][col - 1] = temp1;
                    temp[row + 1][col - 1] = temp2;
                    setValues(row, col + 1, row, col);
                    setValues(row + 1, col + 1, row, col);
                    setValues(row + 1, col, row, col);
                    setValues(row, col, row, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col - 1 == temp[row][col].getStartPointCol()) {
                if (temp[row - 2][col - 1].getType() == 'S' && temp[row - 2][col - 1].getType() == 'S') {
                    Object temp1('S', row - 1, col - 1, row, col - 1, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row, col - 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col + 1] = temp[row - 1][col];
                    temp[row][col + 1] = temp[row][col];
                    temp[row][col] = temp[row][col - 1];
                    temp[row - 1][col] = temp[row - 1][col - 1];
                    temp[row - 1][col - 1] = temp1;
                    temp[row][col - 1] = temp2;
                    setValues(row - 1, col + 1, row - 1, col);
                    setValues(row, col + 1, row - 1, col);
                    setValues(row, col, row - 1, col);
                    setValues(row - 1, col, row - 1, col);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            } else if (row - 1 == temp[row][col].getStartPointRow() && col == temp[row][col].getStartPointCol()) {
                if (temp[row][col + 2].getType() == 'S' && temp[row - 1][col + 2].getType() == 'S') {
                    Object temp1('S', row - 2, col + 1, row, col, 'S'); // spacelerde row ve col önemli değil
                    Object temp2('S', row - 1, col + 1, row, col + 1, 'S'); // spacelerde row ve col önemli değil
                    temp[row - 1][col + 1] = temp[row - 1][col];
                    temp[row][col + 1] = temp[row][col];
                    temp[row - 1][col + 2] = temp[row - 1][col + 1];
                    temp[row][col + 2] = temp[row][col + 1];
                    temp[row - 2][col + 1] = temp1;
                    temp[row - 1][col + 1] = temp2;
                    setValues(row - 1, col + 1, row - 1, col + 1);
                    setValues(row, col + 1, row - 1, col + 1);
                    setValues(row - 1, col + 2, row - 1, col + 1);
                    setValues(row, col + 1, row - 1, col + 1);
                    setVector1(temp);
                    return 1;
                }
                return 0;
            }
        }
    }
}

void Klotski::print() const {
    Object** temp= getVector1();
    cout<< endl<< "  0   1   2   3 "<<endl;
    for(int i=0;i<5;i++){
        cout<<"***************"<<endl;
        for(int j=0;j<4;j++){
            if(j==0) cout<< i;
            if(temp[i][j].getType()=='S'){
                cout<<"    ";
            }
            else
            cout<< " "<<temp[i][j].getType()<<"  ";
        }
        cout<<endl;
    }
    cout<<"***************"<<endl;
}

Klotski::Object** Klotski::create2DArray(unsigned height, unsigned width) const {
    Object **array2D ;
    array2D = new Object *[height];

    for (int h = 0; h < height; h++) {
        array2D[h] = new Object[width];

        for (int w = 0; w < width; w++) {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            array2D[h][w] = Object();
        }
    }
    return array2D;
}

Klotski::Object** Klotski::getVector1() const {
    Object** temp= create2DArray(5,4);
    for(int i=0;i<5;i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = vector[i][j];
        }
    }
    return temp;
}

void Klotski::setVector1( Klotski::Object **vector1) {
    for(int i=0;i<5;i++) {
        for (int j = 0; j < 4; j++) {
            vector[i][j] = vector1[i][j];
        }
    }
}

Klotski::Klotski(Klotski::Object **vector) : vector(vector) {}

bool Klotski::checkFinish() const {
    Object** temp= getVector1();
    if(temp[4][1].getName()=='L' && temp[4][2].getName()=='L' && temp[3][1].getName()=='L' &&temp[3][2].getName()=='L' ){
        return true;
    }
    return false;
}


char Klotski::Object::getType() const {
    return type;
}

void Klotski::Object::setType(char type) {
    Object::type = type;
}

int Klotski::Object::getRow() const {
    return row;
}

void Klotski::Object::setRow(int row) {
    Object::row = row;
}

int Klotski::Object::getCol() const {
    return col;
}

void Klotski::Object::setCol(int col) {
    Object::col = col;
}

int Klotski::Object::getStartPointRow() const {
    return start_point_row;
}

void Klotski::Object::setStartPointRow(int startPointRow) {
    start_point_row = startPointRow;
}

int Klotski::Object::getStartPointCol() const {
    return start_point_col;
}

void Klotski::Object::setStartPointCol(int startPointCol) {
    start_point_col = startPointCol;
}

char Klotski::Object::getName() const {
    return name;
}

void Klotski::Object::setName(char name) {
    Object::name = name;
}

Klotski::Object::Object(char type, int row, int col, int startPointRow, int startPointCol, char name) : type(type),
                                                                                                        row(row),
                                                                                                        col(col),
                                                                                                        start_point_row(
                                                                                                                startPointRow),
                                                                                                        start_point_col(
                                                                                                                startPointCol),
                                                                                                        name(name) {}

Klotski::Object::Object() = default;
