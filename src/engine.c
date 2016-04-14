#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "engine.h"

void inicia_ncurses(){
    initscr();
    start_color();
    
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_GREEN,COLOR_BLACK);
    init_pair(5,COLOR_YELLOW,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
}

void finaliza_ncurses(){
    erase();
    endwin();
}

int pega_input(int input){
    while(input != KEY_LEFT && input != KEY_RIGHT && input != KEY_DOWN){
        input = getch();
    }
    return input;
}