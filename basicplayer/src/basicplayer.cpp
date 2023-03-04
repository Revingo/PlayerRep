#include <ncurses.h>
#include "player.h"
#include <iostream>
using namespace std;

int main(int argc, char ** argv) {
	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * pwin = newwin(yMax, xMax, 0, 0);
	refresh();
	box(pwin, 0, 0);
	refresh();
	wrefresh(pwin);
	keypad(pwin, true);

	player * p = new player(pwin, yMax-2, 1, 'P');
	do{
		p->display();
		wrefresh(pwin);
	}while(p->move()!=27);

	getch();
	endwin();
	return 0;
}
