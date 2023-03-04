#include<ncurses.h>
#include<unistd.h>
#include<thread>
#ifndef PLAYER_H_
#define PLAYER_H_
using namespace std::this_thread;

class player {
public:
	player(WINDOW * win, int y, int x, char c);

	void mvup();
	void mvdown();
	void mvleft();
	void mvright();
	int move();
	void jump();

	void leftright();

	void display();

private:
	int xLoc, yLoc, xMax, yMax, dir;
	char character;
	bool nomv;
	WINDOW * curwin;
};

player::player(WINDOW * win, int y, int x, char c){
	curwin = win;
	yLoc=y;
	xLoc = x;
	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character=c;
	nomv=false;
	dir=0;
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

void player::jump(){
	int direction = wgetch(curwin);
	if(nomv==false && direction==KEY_UP){
		nomv=true;
		switch(dir){
			case 0:
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
			case 1:
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
			case 2:
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
			default:
				break;
		}
	}

}

void player::leftright(){
	if(nomv==false){
		int choice = wgetch(curwin);

		switch(choice){
		case KEY_LEFT:
			dir=1;
			mvleft();
			break;

		case KEY_RIGHT:
			dir=2;
			mvright();
			break;

		default:
			dir=0;
			break;
		}

	}

}

int player::move(){
	int escape = wgetch(curwin);
	std::thread m(leftright);
	std::thread j(jump);
	return escape;
}

void player::display(){
	mvwaddch(curwin, yLoc, xLoc, character);
}

#endif /* PLAYER_H_ */
