#include <iostream>
#include<ncurses.h>
#include<unistd.h>

class basicenemy{
protected:
	int yLoc, xLoc, yMax, xMax, projy, projx, dirlock;
	bool s;
	char enemy;
	WINDOW * curwin;
public:
	int life, money;
	basicenemy(WINDOW * win, int y, int x, int l, char e, int m){
		curwin=win;
		yLoc=y;
		xLoc=x;

		//Vita del nemico
		life=l;
		enemy=e;
		money=m;

		//Indica se si sta sparando un proiettile
		s=false;

		//Coordinate x e y del proiettile
		projx=0;
		projy=0;

		getmaxyx(curwin, yMax, xMax);
		dirlock=0;

		//setto rand
		srand(time(0));
	}
	void display();
	int playerfinder();
	void mvleft();
	void mvright();
	void* behaviour(void*);
	void shoot(int dir);
    bool isterrain(char t);
    void takedamage();
};

class jumpingenemy: public basicenemy{
protected:
	bool j=false;
public:
	jumpingenemy(WINDOW * win, int y, int x, int l, char e, int m) : basicenemy(win, y, x, l, e, m){
		j=false;
	}
	void mvup();
	void mvdown();
	int playerfinder();
    void jump(bool dir);
	void* behaviour(void*);
    void takedamage();
    void gravity();
};
