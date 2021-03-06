#include <iostream>
#include <ncurses.h>
#include "../modules/Stanza.hpp"
#include "../modules/Giocatore.hpp"
#include "../modules/Arma.hpp"
#include "../model/Livello.hpp"
#include "../modules/Mostro.hpp"
#include <string>

using namespace std;

class Drawer{
	protected:
		WINDOW *win0; //Finestra iniziale
		WINDOW *win01;//Finestra di informazioni sulla classe
		WINDOW *win1; //Finestra statistiche
		WINDOW *win2; //Finestra messaggi
		WINDOW *win3; //Finestra stanza
		WINDOW *win4; //Finestra livello
		WINDOW *win5; //Finestra equipaggiamento
		WINDOW *win6; //Finestra pop up
		WINDOW *win7; //Finestra di fine gioco
	public:

		Drawer();

		//chiama le funzioni di libreria necessarie per disegnare
		void preparaScr();
		
		//disegna la schermata iniziale con selezione della classe
		void disegnaInizio(int sel);

		//disegna la stanza nell'apposita finestra
		void disegnaStanza(Stanza* s);

		//disegna tutto
		void disegna(Giocatore* g, Livello* l, Stanza* s);

		//disegna le statisctiche del personaggio nell'apposita finestra
		void disegnaStat(Giocatore* g);

		//disegna l'equipaggiamento del personaggio nell'apposita finestra
		void disegnaEquip(Giocatore* g);

		//scrive le stanze già visitate nel livello nell'apposita finestra
		void disegnaLiv(Livello* l);

		//scrive il messaggio, dato in input, nell'apposita finestra
		void disegnaMess(char msg[100]);

		//disegna la finestra pop up, con il messaggio da scrivere, l'elemento selezionato e il numero di stringhe escluso il titolo
		void disegnaPopUp(char msg[20][40], int selected, int nStringhe);

		//mette uno spazio nelle coordinate della matrice della stanza
		void liberaPosizione(Stanza* s, int y, int x);

		//aggiorna la posizione del giocatore nella stanza
		void posizionaGiocatore(Stanza* s, Giocatore* g, bool isAttacked);

		//disegna i mostri con le nuove posizioni nella stanza
		void posizionaMostro(Stanza* s, Mostro* m, bool chasing, bool isAttacked);

		// Schermata di vittoria
		void quitVictory();

		//Schermata di sconfitta
		void quitDefeat();

	private:
		//date dimensioni e coordinate in input, viene creata e visualizzata la finestra
		WINDOW* creaWin(int height, int width, int starty, int startx);

		//pulisce finestra e ridisegna il bordo
		void clearWin(WINDOW* win);

		//imposta tutti gli init_pair dei colori
		void setColor();

};
