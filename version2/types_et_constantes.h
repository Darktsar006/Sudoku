/************************************************
 * Module types_et_constantes.h			*
 * Ce modulue defini les constantes de base	*
 * du programme. les types Grille, Region,	*
 * etc...					*
 * Auteur: TRAORE Oumar				*
 * date de creation:				*
 * date de dernier modification:22/04/2012		*
 * But: Rajout des constantes lies a		*
 * l'interface graphique			*/

#define LIGNES_MAX 9
#define COLONNES_MAX 9
#define LON_LIG_FICH_MAX 1000

/* Type Matrice : Tableau a 2 Dimensions */
typedef int Matrice[LIGNES_MAX][COLONNES_MAX];

/* Tableau des 9 entiers */
typedef int T_Tab[9];

/* Region du Sudoku */
typedef int T_Region[3][3];

/* Structure qui a chaque case, associe un tableau de candidats */
typedef T_Tab Candidats_case[81];

#define WIDTH 30
#define HEIGHT 10 
#define REGLE_WIDTH 30
#define REGLE_HEIGHT 10 

int startx = 0;
int starty = 0;

char *choices[] = {"Solveur SUDOKU ", "Aide / Instructions", "Quitter le programme", };

char *regles[] = { "Regle 1 et 2", "Regle 3", "Regle4", "Undo", "Exit", };

char *regle[] = {"Regle 1", "Regle 2", "Regle 3", "Regle 4", };
		  
int n_choices = sizeof(choices) / sizeof(char *);

int n_regles = sizeof(regles) / sizeof(char *);
