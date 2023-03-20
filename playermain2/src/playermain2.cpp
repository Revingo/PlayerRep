#include <ncurses.h>
#include "player.hpp"
#include <iostream>
#include <pthread.h>
using namespace std;

typedef void * (*THREADFUNCPTR)(void *);

int main(int argc, char ** argv) {
	initscr();
	noecho();
	cbreak();

	int yMax=30, xMax=120;

	WINDOW * pwin = newwin(yMax, xMax, 0, 0);
	refresh();
	box(pwin, 0, 0);
	refresh();
	wrefresh(pwin);
	keypad(pwin, true);

	//sintassi: (finestra, y da cui il personagio spawna, x da cui il personaggio spawna, icona del personaggio)
	player * p = new player(pwin, yMax-3, 1, 'P');

	//Inizializzazione del thread giocatore
	pthread_t playerthread;
	do{
		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);
		//Aspetta che il thread finisca di elaborare
		pthread_join(playerthread, NULL);
		//Refresha la finestra
		wrefresh(pwin);

	}while(p->move()!=27);

	int prova;
	//Guardare il file "player.cpp" per sapere l'utilizzo di questa funzione
	//POTREBBE ESSERE MOLTO UTILE SORPATUTTO PER LUCA
	prova=p->playeroutput(5);

	getch();
	endwin();
	return 0;
}
