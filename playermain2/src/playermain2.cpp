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

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, icona del nemico (lasciala 'e'), soldi rilasciati alla morte)
	basicenemy * e1 = new basicenemy(pwin, yMax-3, 20, 1, 'e', 100);

	basicenemy * e2 = new basicenemy(pwin, yMax-3, 25, 1, 'e', 100);

	basicenemy * e3 = new basicenemy(pwin, yMax-3, 30, 3, 'e', 300);

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, icona del nemico (lasciala 'e'),
	//soldi rilasciati alla morte, difficoltà del nemico !PIU IL NUMERO E' BASSO PIU E' DIFFICILE! (non usare numeri negativi)
	//sconsiglio di scendere sotto a 3)
	jumpingenemy * e4 = new jumpingenemy (pwin, yMax-3, 35, 3, 'e', 600, 4);

	//Inizializzazione del thread giocatore e nemici
	pthread_t playerthread, enemythread1, enemythread2, enemythread3, enemythread4;

	int contmoney=0;
	//e1->display();
	e4->display();
	do{

		if(e4->life==0 && contmoney==0){
			p->money+=e4->money;
			contmoney++;
		}

		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);

		//pthread_create(&enemythread1, NULL, (THREADFUNCPTR) &basicenemy::behaviour, e1);

		//pthread_create(&enemythread2, NULL, (THREADFUNCPTR) &basicenemy::behaviour, e2);

		pthread_create(&enemythread4, NULL, (THREADFUNCPTR) &jumpingenemy::behaviour, e4);

		//Aspetta che il thread finisca di elaborare

		//pthread_join(enemythread1, NULL);

		//pthread_join(enemythread2, NULL);

		pthread_join(enemythread4, NULL);



		/*
		        ___ ___  ___      __    __        ___
 	 	 	/\   |   |  |__  |\ |  / | /  \ |\ | |__
		   /~~\  |   |  |___ | \| /_ | \__/ | \| |___

		 * Potete provare a eliminare "pthread_join(playerthread, NULL)" ma non è assicurato funzioni
		 * Potrebbe comunque essere una buona idea se il gioco ha bug strani
		 */

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
