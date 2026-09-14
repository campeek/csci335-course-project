#include <ncurses.h>

/* main.cpp
 * Cameron Peek
 * 9/12/26
 *
 **/

WINDOW* win;

int main(){
	setupCurses();
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
