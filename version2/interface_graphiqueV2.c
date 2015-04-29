/************************************************
 * Module: interface-graphiqueV2.c		*
 * Ce modulue Resoud le Sudoku en Appliquant	*
 * l'une des 4 regles.
 * Auteur: TRAORE Oumar         *
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/

/* Procedure permettant d'afficher le menu principal */

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

/* Procedure permettant d'afficher le choix des regles */

void PrintMenuRegle(WINDOW *regle_win, int highlignt_menu, Grille grille)
{
	Menu();
	AfficherSimple(grille);
	refresh();
	int x, y, i;	

	x = 2;
	y = 2;
	box(regle_win, 0, 0);
	for(i = 0; i < n_regles; ++i)
	{	if(highlignt_menu == i + 1) /* High light the present regle */
		{	wattron(regle_win, A_REVERSE); 
			mvwprintw(regle_win, y, x, "%s", regles[i]);
			wattroff(regle_win, A_REVERSE);
		}
		else
			mvwprintw(regle_win, y, x, "%s", regles[i]);
		++y;
	}
	wrefresh(regle_win);
}



