#include <ncurses.h>
#include <parser.hpp>
#include <iostream>

/* main.cpp
 * Cameron Peek
 * 9/12/26
 *
 **/

WINDOW* win;

int main(int argc, char* argv[]){
//	setupCurses();
    if(argc < 2){
        std::cerr << "no arguments :(((\n";
        return 1;
    }
    readAsm(argv[1]);
	return 0;
}

void setupCurses(){
	initscr();
	cbreak();
	noecho();

	curs_set(0);

	int height = 10;
	int width = 30;
	int startX = 2;
	int startY = 4;

	win = newwin(height, width, startY, startX);
	box(win, 0, 0);

	mvwprintw(win, 1, 2, "Registers");
	mvwprintw(win, 3, 2, "A:   000000");
	mvwprintw(win, 4, 2, "X:   000000");
	mvwprintw(win, 5, 2, "PC:  000000");

	wrefresh(win);

	int ch;
	while( (ch = wgetch(win)) != 'q' && ch != 'Q'){
		// :))))
	}

	delwin(win);
	endwin();
}
