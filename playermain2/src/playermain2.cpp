#include <ncurses.h>
#include "player.hpp"
#include "basicenemy.hpp"
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

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, icona del nemico (lasciala 'e'))
	basicenemy * e1 = new basicenemy(pwin, yMax-3, 20, 1, 'e');

	basicenemy * e2 = new basicenemy(pwin, yMax-3, 25, 1, 'e');

	basicenemy * e3 = new basicenemy(pwin, yMax-3, 30, 3, 'e');

	//Inizializzazione del thread giocatore e nemici
	pthread_t playerthread, enemythread1, enemythread2, enemythread3;

	//pthread_attr_setguardsize(&playerthread, 3);

	e1->display();
	do{
		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);

		pthread_create(&enemythread1, NULL, (THREADFUNCPTR) &basicenemy::behaviour, e1);

		//pthread_create(&enemythread2, NULL, (THREADFUNCPTR) &basicenemy::behaviour, e2);

		//Aspetta che il thread finisca di elaborare

		pthread_join(enemythread1, NULL);

		//pthread_join(enemythread2, NULL);

		/*
		 *      ___ ___  ___      __    __        ___
 	 	 	/\   |   |  |__  |\ |  / | /  \ |\ | |__
		 * /~~\  |   |  |___ | \| /_ | \__/ | \| |___
		 *
		 * Potete provare a eliminare "pthread_join(playerthread, NULL)" ma non è assicurato funzioni
		 * Potrebbe comunque essere una buona idea se il gioco ha bug strani
		 */

		//pthread_join(playerthread, NULL);

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
