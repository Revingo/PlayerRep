#include<ncurses.h>
#include<unistd.h>

#ifndef PLAYER_H_
#define PLAYER_H_


class player {
public:
	player(WINDOW * win, int y, int x, char c);

	void mvup();
	void mvdown();
	void mvleft();
	void mvright();
	int move();
	void jump(int direction);

	int leftright(int *dire);

	void display();

private:
	int xLoc, yLoc, xMax, yMax, dir;
	char character;
	WINDOW * curwin;
};

player::player(WINDOW * win, int y, int x, char c){
	curwin = win;
	yLoc=y;
	xLoc = x;
	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character=c;
	dir=2;
}

void player::mvup(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc--;
	if(yLoc<=0)
		yLoc=1;
}

void player::mvdown(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc++;
	if(yLoc>=yMax-1)
		yLoc=yMax-2;
}

void player::mvright(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	if(xLoc>=xMax-1)
		xLoc=xMax-2;

}

void player::mvleft(){
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	if(xLoc<=0)
		xLoc=1;

}

void player::jump(int direction){
	switch(direction){
		case 0:
			for(int cont = 0; cont < 3; cont++){
				mvup();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvleft();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			for(int cont = 0; cont < 3; cont++){
				mvdown();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvleft();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			break;
		case 1:
			for(int cont = 0; cont < 3; cont++){
				mvup();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvright();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			for(int cont = 0; cont < 3; cont++){
				mvdown();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvright();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			break;
		default:
			for(int cont = 0; cont < 3; cont++){
				mvup();
				display();
				usleep(42000);
				wrefresh(curwin);
			}
			for(int cont = 0; cont < 3; cont++){
				mvdown();
				display();
				usleep(42000);
				wrefresh(curwin);
			}
			break;
	}
}
int player::leftright(int *dire){

	int choice = wgetch(curwin);
	switch(choice){
	case KEY_LEFT:
		*dire=0;
		mvleft();
		break;

	case KEY_RIGHT:
		*dire=1;
		mvright();
		break;
	case KEY_UP:
		jump(dir);
		break;

	default:
		*dire=2;
		break;
	}
	return(choice);

}

int player::move(){
	return leftright(&dir);
}

void player::display(){
	mvwaddch(curwin, yLoc, xLoc, character);
}

#endif /* PLAYER_H_ */
