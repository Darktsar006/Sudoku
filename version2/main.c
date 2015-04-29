/************************************************
 * Module: main.c				*
 * Ce modulue est la principale elle fait	*
 * Intervenir toutes les autres fonctions pour	*
 * le deroulement du programme
 * Auteur: TRAORE Oumar         *
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <malloc.h>

#include "Regle1.h"
#include "Regle2.h
#include "Regle3.h"
#include "Regle4.h
#include "verification.h"
#include "types_et_constantes.h"
#include "interface_graphiqueV2.h"
#include "interface_graphique.h"
#include "id_case.h"


int main()
{	
	WINDOW *menu_win;
	WINDOW *regle_win;
	
	int highlight = 1;
	int highlignt_menu = 1;
	
	int choice = 0;
	int regle = 0;
	
	int choix=0;
	
	int c;
	int d;
	
	
	
	
	
	
	noecho();
	Grille sudoku;
	Candidats_case candidats;
	char pap;
	char test='o';
	int pas_a_pas;
	time_t deb,fin;
	time(&deb);
      
	char continuer='o';

	initscr();
	clear();
	start_color();

	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	
	Menu();
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(18, 0, "Vous avez choisi %s\n", choices[choice - 1]);
	clrtoeol();
	choix = choice;
	echo();
    while (continuer == 'o'){
	
        switch(choix){
            case 1: 
	      
                do{
			  SaisirGrillev3(sudoku);
                            /* On se rassure que la Grille est valide */
                            if(VerifierGrille(sudoku)){
                              printw("Grille Chargee avec succes !!!\n");
                              test='n';
                            }else{
                              printw("Il y'a eu erreur lors de la saisie de la Grille \n ");
                              printw("Reessayer !!!!!!!\n");
                              test='o';
			    }
			    
		}while ( test=='o');
		
                     test='o';
              
                printw("\nVoulez vous executer le mode pas a pas ? O/N ");
		refresh();
                pap=getch();
                pap=tolower(pap);
                pas_a_pas=(pap == 'o')?1:0;
		
		clear();
		
		regle_win = newwin(8, 15, 10, 0);
		keypad(regle_win, TRUE);
		
		PrintMenuRegle(regle_win, highlignt_menu, sudoku);
		while(VerifierGrille(sudoku))
		{
			d = wgetch(regle_win);
			 switch(d)
			{	
				case KEY_UP:
					if(highlignt_menu == 1)
						highlignt_menu = n_regles;
					else
						--highlignt_menu;
				break;
				case KEY_DOWN:
					if(highlignt_menu == n_regles)
						highlignt_menu = 1;
					else 
						++highlignt_menu;
				break;
				case 10:
					regle = highlignt_menu;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", d, d);
				refresh();
				break;
		    }
			clear();
			PrintMenuRegle(regle_win, highlignt_menu, sudoku);
			switch(regle)	
			{
				case 1:
					res_AppliquerRegle1et2(sudoku, candidats, pas_a_pas);
					printw("Cette Regle est epuiser pour ce tour ci\n");
					break;
				case 2:
					res_AppliquerRegle3(sudoku, candidats, pas_a_pas);
					printw("Cette Regle est epuiser pour ce tour ci\n");
					break;
				case 3:
					res_AppliquerRegle4(sudoku, candidats, pas_a_pas);
					printw("Cette Regle est epuiser pour ce tour ci\n");
					break;
			}
			if(regle == 5)
			    break;
		}	
		clrtoeol();
	
		refresh();
		clear();
				
                /*Resolution(sudoku,candidats,pas_a_pas);*/
                printw("\t\t\t   GRILLE RESOLUE \n");
                AfficherGrille(sudoku,-1,-1);
                printw("\nVoulez vous resoudre une autre Grille ? O/N ");
		refresh();
                continuer = getch();
                continuer=tolower(continuer);
		printw("\n");
          break;
          case 2:
                /* On affiche l'Aide */
                AfficherAide();
                printw("\nVoulez vous essayer une grille ? O/N ");
                continuer=getch();
                continuer=tolower(continuer);
		refresh();
          break;
          case 3:printw("Vous avez choisi de finir l'execution du programme \n");
                continuer='N';
          break;
          default:printw("S'il vous plait entrez un choix valide : ");
                continuer='o';
          break;
        }
    }

    time(&fin);
    /*if(pas_a_pas != 1) printw("\nVous avez mis %.f secs \n",difftime(fin,deb));*/
	getch();
	
	refresh();
	endwin();
	return 0;
}


