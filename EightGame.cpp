//
// Created by Burak Ugar on 14.12.2021.
//

#include "EightGame.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

enum Move{
    left=1,
    right=2,
    up=3,
    down=4
}move;

#define N 3 /*defining the matrix size */
EightGame::EightGame() = default;
EightGame::EightGame(int flagx,int flagy,int is_it_ok):isitok(is_it_ok),flag_x(flagx),flag_y(flagy){};
int EightGame:: MakeMove(int ret_value,int x,int y){
    unsigned int** board= get_board();
    int space_x= getFlagX();
    int space_y= getFlagY();
    unsigned int temp,temp1;
    unsigned int space_temp;
    if(ret_value==1){
        space_temp= board[space_x][space_y];
        temp=board[x][y];
        board[space_x][space_y]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }
    else if(ret_value==2){
        if(y==0)
            return 0;
        space_temp= board[space_x][space_y];
        temp=board[x][y];
        temp1=board[x][y-1];
        board[space_x][space_y]=temp1;
        board[x][y-1]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

    else if(ret_value==3){
        space_temp= board[space_x][space_y];
        temp= board[x][y];
        board[space_x][space_y]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

    else if(ret_value==4){
        if(y==2)
            return 0;
        space_temp= board[space_x][space_y];
        temp= board[x][y];
        temp1= board[x][y+1];
        board[space_x][space_y]=temp1;
        board[x][y]=space_temp;
        board[x][y+1]=temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

    else if(ret_value==5){ // if the space is 1 flat  left our point
        space_temp= board[space_x][space_y];
        temp=board[x][y];
        board[space_x][space_y]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

    else if(ret_value==6){
        if(x==2)
            return 0;
        space_temp= board[space_x][space_y];
        temp=board[x][y];
        temp1=board[x+1][y];
        board[space_x][space_y]=temp1;
        board[x+1][y]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

    else if(ret_value==7){
        space_temp= board[space_x][space_y];
        temp= board[x][y];
        board[space_x][space_y]=temp;
        board[x][y]=space_temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }
    else if(ret_value==8){
        if(x==0)
            return 0;
        space_temp= board[space_x][space_y];
        temp= board[x][y];
        temp1= board[x-1][y];
        board[space_x][space_y]=temp1;
        board[x][y]=space_temp;
        board[x-1][y]=temp;
        setFlagX(x);
        setFlagY(y);
        set_board(board);
        return 1;
    }

}
int EightGame::checkMove(int x,int y,int* ret) {
    unsigned int **board = get_board();
    int space_x = getFlagX();
    int space_y = getFlagY();
    if (space_x == x && space_y == y) {
        *ret=0;
        return 0;
    }

    if (space_x == x) {
        if (space_y < y && y - space_y == 1) { // if the space is 1 flat  left our point
            *ret=1;
            return 1;
        } else if (space_y < y && y - space_y == 2) { // if the space is 2 flat left our point
            *ret=2;
            return 2;
        } else if (space_y > y && space_y - y == 1) { // if the space is 1 flat right our point
            *ret=3;
            return 3;
        } else if (space_y > y && space_y - y == 2) { // if the space is 1 flat right our point
            *ret=4;
            return 4;
        }
    } else if (space_y == y) {
        {
            if (space_x < x && x - space_x == 1) { // if the space is 1 flat  left our point
                *ret=5;
                return 5;
            } else if (space_x < x && x - space_x == 2) { // if the space is 2 flat left our point
                *ret=6;
                return 6;
            } else if (space_x > x && space_x - x == 1) { // if the space is 1 flat right our point
                *ret=7;
                return 7;
            } else if (space_x > x && space_x - x == 2) { // if the space is 1 flat right our point
                *ret=8;
                return 8;
            }
        }
    }
}
void EightGame::playAuto() {
    int space_x = getFlagX();
    int space_y = getFlagY();
    int ret;
    int random_x = rand() % N;
    int random_y = rand() % N;
    int control;
    int i;
    while(1){
        if (((random_x != space_x || random_y != space_y) && ((space_x == random_x || space_y == random_y)))) {
            checkMove(random_x, random_y, &ret);
            control = MakeMove(ret, random_x,
                               random_y); // icindeki kontrol fonkiyonlarının sınırlarına göre bu fonksiyonun bir return değeri olucak sonra da for döngüsüne buna göre bir sonraki iterasyona gidiceksin
            if (control == 1)
                goto at;
        }
        random_x = rand() % N;
        random_y = rand() % N;
    }
    at:;
    print();
}
bool EightGame::endGame() const {
    unsigned int** temp;
    temp= get_board();
    if(temp[0][0]==1 && temp[0][1]==2 && temp[0][2]==3 && temp[1][0]==4 &&  temp[1][1]==5 && temp[1][2]== 6 &&  temp[2][0]==7 &&  temp[2][1]==8){
        return true;
    }
    else{
        return false;
    }
}

unsigned int EightGame::boardScore() const {
    unsigned int** temp;
    temp= get_board();
    int cons =10;
    int total= abs((int)temp[0][0]-1)+abs((int)temp[0][1]-2)+abs((int)temp[0][2]-3)+abs((int)temp[1][0]-4)+abs((int)temp[1][1]-5)+abs((int)temp[1][2] - 6)+ abs((int)temp[2][0]-7)+ abs((int)temp[2][1]-8);
    cout<< "Score:" << total;
    return total;
}

void EightGame::playUser( string &command) {
    int x;
    int y;
    int direction;
    cout<<"Please enter the x coordinate of the point: ";
    cin>> x;
    while(x<0||x>N-1){
        cin>> x;
        cout<< "Please enter a x valid coordinate: ";
    }
    cout<<"Please enter the y coordinate of the point: ";
    cin>> y;
    while(y<0||y>N-1){
        cin>> y;
        cout<< "Please enter a y valid coordinate: ";
    }
    cout<< ("Please enter the direction to move (left:1,right:2,up:3,down:4):"); /*receiving input from the user as integer */
    cin>> direction;
    controlMove(x,y,direction);
}

void EightGame::swap1 (unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}
void EightGame::randomize (unsigned int arr[], int n)
{
    // Use a different seed value so that
    // we don't get same result each time
    // we run this program
    srand (time(NULL));

    // Start from the last element and swap
    // one by one. We don't need to run for
    // the first element that's why i > 0
    for (int i = n - 1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);

        // Swap arr[i] with the element
        // at random index
        swap1(&arr[i], &arr[j]);
    }
}

void EightGame::initialize(){
    unsigned int** temp= create2DArray(N,N);
   // unsigned int* arr=create1DArray(9);
    unsigned int arr[9];
    int i,j,k=0;
    srand(time(NULL)); /* to fill the matrix randomly */
    for(i=0;i<9;i++){
        arr[i]=i+1;
    }

    randomize(arr,9);

    k=0;
    for (i = 0; i < N; i++){
        for(j=0;j< N;j++){
            if(arr[k]==9){ /* array's last element is space such as if the matrix is 3x3 last, our array starts from 0 and goes to 8 since when
					we come across with N*N that means it's the last element and also space's itself */
                k++;
                setFlagX(i); /* flag_x and flag_y values are space's coordinates */
                setFlagY(j);
            }
            else{
                temp[i][j]= arr[k];
                k++;
            }
        }
    }
    set_board(temp);
}

int EightGame::getFlagX() const {
    return flag_x;
}

void EightGame::setFlagX(int flagX) {
    flag_x = flagX;
}

int EightGame::getFlagY() const {
    return flag_y;
}

void EightGame::setFlagY(int flagY) {
    flag_y = flagY;
}
/*You will write a function that checks if the puzzle is solved/correct. It should return a
logical value.*/

bool EightGame::checkOk(unsigned int* arr2 ){ /* function controls the puzzle is solved or not */
    unsigned int** board= create2DArray(N,N);
    int i,j,count=0,k=0;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(board[i][j]==arr2[k]){
                count++;
            }
            k++; /*check if the puzzle is done or not */
        }
    }
    if(count==N*N-1){
        return true;
    }
    else{
        return false;
    }
}
int EightGame::checkSpace(int x,int y) const{
    int i,j,result;

    if(getFlagX()==x && getFlagY()!= y){ /* if x coordinates are same */
        return 1;
    }
    else if(getFlagY()==y && getFlagX()!=x){
        return 2;	 /* if y coordinates are same */
    }
    else
        return 0;
}
/* this function controls the move */
/*You will write a function that performs the desired move on the puzzle board. The
movement parameters are
a. The direction of the movement: towards {left, right, up, down} enumerated
type.
b. Movement start location: Movement will start at this location (you will need
two parameters for this).*/
void EightGame::controlMove(int x,int y,int direction){
    int is_it_ok= getIsitok();
    unsigned int** M1;
    M1=get_board();
    int i,j,value;
    int temp_x1=getFlagX(); /*temp_x1: x coordinate of the space */
    int temp_y1=getFlagY(); /*temp_y1: y coordinate of the space */
    int temp_x2=x; /* temp_x2: x coordinate of the given point */
    int temp_y2=y; /* temp_y2: y coordinate of the given point */

    if(checkSpace(x,y)==1){ /* if x coordinates are same */
        if(direction == Move::right  && (getFlagY() > y)){	/*if the given direction is right and space is in the right direction of the given point */
            setIsitok(0);
            for(i=getFlagY()-1;i>=y;i--){
                M1[temp_x1][i+1]=M1[temp_x1][i]; /*IF USER DECIDES TO GO TROUGH RIGHT */
            }
            setFlagX(temp_x2);
            setFlagY(temp_y2); /* assign the new space to the given point because it will move */
            set_board(M1);
            setIsitok(1);
        }
        else if(direction == Move::left && (getFlagY() < y)){ /*if the given direction is left and space is in the left direction of the given point */
            setIsitok(0);
            for(i=getFlagY()+1;i<=y;i++){
                M1[temp_x2][i-1]=M1[temp_x2][i];
            }
            setFlagX(temp_x2);
            setFlagY(temp_y2); /*assign the new space to the given point because it will move */
            setIsitok(1);
            set_board(M1);
        }
        else{
            cout<<"Please choose a valid point or direction to move";
        }
    }
    else if(checkSpace(x,y)==2){ /* if y coordinates are same */ /* bizim algoritma olarak yukarı asagi gidip gidemeyeceğimizi kontrol eden bir algo yazmamiz lazimö */
        if(direction == up && (getFlagX() < temp_x2)){ /*IF USER DECIDES TO GO TROUGH UPWARD */
            setIsitok(0);
            for(i=temp_x1;i<temp_x2+1;i++){
                M1[i][temp_y2]=M1[i+1][temp_y2];
            }
            setFlagX(temp_x2);
            setFlagY(temp_y2); /* assign the new space to the given point because it will move */
            setIsitok(1);
            set_board(M1);
        }
        else if(direction == down && (getFlagX() > temp_x2)){ /*IF USER DECIDES TO GO TROUGH DOWNWARD */
            /* assign the new space to the given point because it will move	*/
            setIsitok(0);
            for(i=temp_x1-1;i>temp_x2-1;i--){
                M1[i+1][temp_y2]=M1[i][temp_y2];
            }
            setFlagX(temp_x2);
            setFlagY(temp_y2); /* assign the new space to the given point because it will move */
            setIsitok(1);
            set_board(M1);
        }
        else{
            cout<< "Please choose a valid point or direction to move";
        }
    }
    else{
        cout<<"Please choose a valid point or direction to move";
    }
}

int EightGame::getIsitok() const {
    return isitok;
}

void EightGame::setIsitok(int ok) {
    EightGame::isitok = ok;
}
unsigned int ** EightGame::create2DArray(unsigned height, unsigned width) const {
    unsigned int** array2D = 0;
    array2D = new unsigned int*[height];

    for (int h = 0; h < height; h++)
    {
        array2D[h] = new unsigned int[width];

        for (int w = 0; w < width; w++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            array2D[h][w] = 0;
        }
    }
    return array2D;
}

void EightGame::print() const{
    unsigned int** temp= create2DArray(N,N);
    unsigned int** board= create2DArray(N,N);
    board=get_board();
    int isitok= getIsitok();
    int flag_x1=getFlagX();
    int flag_y1=getFlagY();
    int i,j=0,l;
    int count = 5*N;
    for (i = 0; i < count+2; i ++) { /*printing the stars */
        cout<<"*";
    }
    cout<<endl;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cout<< "*";
            if(i==flag_x1 && j== flag_y1 ){ //
                cout<< "    "; /* when come across with space then print the space */
                continue;
            }
            else{
                cout<<"   "<< board[i][j]  ;
            }
        }
        cout<< " *";
        cout<<endl; /* printing the right star and space patterns */
        for (l = 0; l < count+2; l ++) {
            cout<< "*";
        }
        cout<<endl;
    }
}

void EightGame::set_board(unsigned int** a ) {
    M= create2DArray(N,N);
    for(int i=0;i<N;i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = a[i][j];
        }
    }
}

unsigned int** EightGame::get_board() const{
    unsigned int** temp= create2DArray(N,N);
    for(int i=0;i<N;i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = M[i][j];
        }
    }
    return temp;
}



