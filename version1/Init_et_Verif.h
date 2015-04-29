#ifndef INIT_ET_VERIF
#define INIT_ET_VERIF

#include <stdbool.h>
#include "Types_et_Constantes.h"
#include "Regles1_et_2.h"

void InitialiserGrille(Grille grille);
void InitialiserCandidats(T_Tab candidats);
bool VerifierRegion(Grille grille,int ligne,int colonne);
bool VerifierLigne(Grille grille,int ligne);
bool VerifierColonne(Grille grille, int colonne);
bool VerifierGrille(Grille grille);
bool VerifierCoordonnees(int ligne,int colonne);
bool EstDansTab(int valeur,T_Tab tableau);
bool EstDansReg(int valeur, T_Region reg);
bool EstDansGrille(int valeur,Grille grille);
int Region(int ligne, int colonne);
void CopierGrille(Grille entree,Grille dupliquee);
void CopierCandidats(Candidats_case candEntree,Candidats_case candSortie);
bool GrillesEgales(Grille grille1,Grille grille2);

#endif
