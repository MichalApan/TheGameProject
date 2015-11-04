#include <curses.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "class.hpp"

using namespace std;

int main(){

    //Initialization
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    bool game = 1, play = 1;
    int score = 0;
    int k, t, t2;
    int maxX=COLS, maxY=LINES;
    int timeOfPlay = 20;

    Player first;
    Player target;
    Player target2;

    while(play)
    {
        start_counting();

        srand(time(NULL));

        Stage stageOne;
        stageOne.setSize(maxX,maxY);

        first.setPosition((maxX/2)-1,maxY/2);
        target.setPosition(maxX-5,maxY-5);
        target2.setPosition(5,5);

        stageOne.draw(first,target,target2);

        time_t startTime;
        time(&startTime);
        game = 1;
        score = 0;

        while(game)
        {
            stageOne.draw(first,target,target2);

            timeout(800);
            k = static_cast<int>(getch());
            first.movePlayer(k);

            if(first.getX() == target.getX() &&
               first.getY() == target.getY()) {score++; target.changeStatus(1);}
            if(first.getX() == target2.getX() &&
               first.getY() == target2.getY()) {score++; target2.changeStatus(1);}

            stageOne.draw(first,target,target2);

            //exit
            time_t endTime;
            time(&endTime);
            if(endTime-startTime>timeOfPlay) {
                    game = 0;
                    getch();
            }
            //end exit

            t = (rand()%4 +258);
            if(target.getStatus()) target.movePlayer(t);
            t2 = ((rand()*rand()+8)%4 +258);
            if(target2.getStatus()) target2.movePlayer(t2);

            if(first.getX() == target.getX() &&
               first.getY() == target.getY()) {score++; target.changeStatus(1);}
            if(first.getX() == target2.getX() &&
               first.getY() == target2.getY()) {score++; target2.changeStatus(1);}
        }
        clear();
        char end_msg[] = "Gratulacje!Zdobyles %d punktow.";
        mvprintw(maxY/2,maxX/2-sizeof(end_msg)/2,"Gratulacje! Zdobyles %d punktow.\n \t\t\tNacisnij 'e' aby wyjsc.\n \t\t\tJezeli chcesz zagrac jeszcze raz nacisnij 'n'.", score);
        refresh();
        timeout(1000);

        while(1)
        {
            int ch=getch();
            if(ch=='e') {play = 0; break;}
            else if(ch=='n') {play = 1; break;}
        }
    }

    endwin();
    return 0;
}
