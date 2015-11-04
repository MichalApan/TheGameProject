#ifndef CLASS_HPP_INCLUDED
#define CLASS_HPP_INCLUDED
#include <curses.h>
#include <ctime>
#include <cstdlib>
using namespace std;

enum TypeOfField{NUL,TREE,CHAR_GOOD,CHAR_BAD,BONUS,BONUS2,HEART};
char symbols[]={' ', 'Y', '|', '-', 'O', '+', 'H'};

class Field{
    TypeOfField type;
public:
    void changeField();
};

class Player{
    int positionX;
    int positionY;
    bool status;
public:
    void setPosition(int, int);
    void movePlayer(int);
    void changeStatus(int);
    void writeX();
    void writeY();
    bool getStatus();
    int getX();
    int getY();
};

void Player::setPosition(int x, int y){
    this->status = 1;
    this->positionX = x;
    this->positionY = y;
}

void Player::movePlayer(int direction){
    switch(direction){
        case KEY_LEFT:
            if(this->positionX>0) this->positionX=this->positionX-1;
            break;
        case KEY_UP:
            if(this->positionY>0) this->positionY=this->positionY-1;
            break;
        case KEY_DOWN:
            if(this->positionY<25-1) this->positionY=this->positionY+1;
            break;
        case KEY_RIGHT:
            if(this->positionX<80-1) this->positionX=this->positionX+1;
            break;
        default:
            break;
    }
}

void Player::changeStatus(int stat)
{
    srand(time(NULL));
    if(stat==0) {
        setPosition(-1,-1);
        this->status = 0;
    }else if(stat==1) {
        setPosition(rand()%COLS,rand()%LINES);
        this->status = 1;
    }
}

void Player::writeX(){
    printw("%d",this->positionX);
}

void Player::writeY(){
    printw("%d",this->positionY);
}

int Player::getX(){
    return this->positionX;
}

int Player::getY(){
    return this->positionY;
}

bool Player::getStatus(){
    return this->status;
}

class Stage{
    int maxX;
    int maxY;
    //Field tab[];
public:
    void setSize(int,int);
    void draw(Player, Player, Player);
    int getWidth();
    int getHeight();

};

void Stage::setSize(int width, int height){
    this->maxX = width;
    this->maxY = height;
}

void Stage::draw(Player character, Player target, Player target2){
    int x1 = character.getX();
    int y1 = character.getY();

    int x2 = target.getX();
    int y2 = target.getY();

    int x3 = target2.getX();
    int y3 = target2.getY();

    const char* white = "X";
    const char* black = "O";

    clear();
    if(y1 != -1 && x1 !=-1) mvprintw( y1,x1, white);
    if(y2 != -1 && x2 !=-1) mvprintw( y2,x2, black);
    if(y3 != -1 && x3 !=-1) mvprintw( y3,x3, black);
}

int Stage::getWidth(){
    return this->maxX;
}
int Stage::getHeight(){
    return this->maxY;
}

void start_counting()
{
        clear();
        char start_msg[] = "Sterowanie strzalkami. Cel: Zlap murzynow!";
        mvprintw(LINES/2,COLS/2-sizeof(start_msg)/2,"Sterowanie strzalkami. Cel: Zlap murzynow!\n\t\t\t\t Czas:20sek");
        refresh();
        Sleep(3000);
        clear();
        mvprintw(LINES/2,COLS/2,"3..");
        refresh();
        Sleep(1000);
        clear();
        mvprintw(LINES/2,COLS/2,"2..");
        refresh();
        Sleep(1000);
        clear();
        mvprintw(LINES/2,COLS/2,"1..");
        refresh();
        Sleep(1000);
        clear();
        mvprintw(LINES/2,COLS/2,"START");
        refresh();
        Sleep(100);
}

#endif // CLASS_HPP_INCLUDED
