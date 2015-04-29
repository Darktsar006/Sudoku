#include "version2.h"


/* Implementation de la version 2 utilisation de la bibliothèque ncurses pour l'affichage */


void affichage_version2(Grille sudoku, Candidats_case_candidats cand)
{
    initscr(); /* Initialisation du mode ncurses */
    printw("Projet sudoku\n");
    printw("TRAORE\n");

    refresh(); /* Permet de mettre a jour l'affichage de la fenetre */

    endwin(); /* ferme le programme d'affichage */

}
