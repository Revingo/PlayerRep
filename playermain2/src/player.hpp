#include <iostream>
#include<ncurses.h>
#include<unistd.h>

class player {
    protected:
        int xLoc, yLoc, xMax, yMax, life, originx, originy, projx, projy;
        bool s, dir, dirlock, j;
        char character;
        WINDOW * curwin;

    public:
        player(WINDOW * win, int y, int x, char c);

        bool isterrain(char t);
        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int move();
        void jump();
        int leftright();
        void* display(void * arg);
        void stairsup();
        void stairsdown();
        void lifeshow();
        void gravity();
        void shoot();
        int playeroutput(int input);
};
