#ifndef TYPES_ET_CONSTANTES
#define TYPES_ET_CONSTANTES

#define LIGNES_MAX 9
#define COLONNES_MAX 9
#define LON_LIG_FICH_MAX 1000

//Type Grille : Tableau a 2 Dimensions
typedef int Grille[LIGNES_MAX][COLONNES_MAX];

//Tableau des 9 entiers
typedef int T_Tab[9];

//Region du Sudoku
typedef int T_Region[3][3];

//Structure qui a chaque case, associe un tableau de candidats
typedef T_Tab Candidats_case[81];

#endif
