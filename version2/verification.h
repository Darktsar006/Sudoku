#ifndef verification
#define verification

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h"
#include "Regle1.h"
#include types_et_constantes.h"



bool verifier_Coordonnees(int ligne,int colonne);
bool verifier_Region(Matrice grille,int ligne,int colonne);
bool verifier_Ligne(Matrice grille, int ligne);
bool verifier_Colonne(Matrice grille, int colonne);
bool verifier_Matrice(Matrice grille);
bool verifier_EstDansTAB(int valeur,T_Tab tableau);
bool verifier_EstDansReg(int valeur, T_id_Region reg);
bool verifier_EstDansMatrice(int valeur,Matrice grille);
bool verifier_MatricesEgales(Matrice grille1,Matrice grille2);
bool verifier_TableauxEgaux(T_Tab tab1,T_Tab tab2);

#endif