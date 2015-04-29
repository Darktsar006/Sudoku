#ifndef REGLES_1_ET_2
#define REGLES_1_ET_2

#include "Types_et_Constantes.h"
#include "Affichage_et_Saisie.h"
#include "Init_et_Verif.h"
#include <stdio.h>
#include <stdbool.h>

void DecomposerEnLigne(Grille grille, T_Tab t_ligne, int ligne);
void DecomposerEnColonne(Grille grille, T_Tab t_colonne, int colonne);
int ValeurCase(Grille grille,int num_case);
void DecomposerEnRegion(Grille grille,T_Region t_region, int lig,int col);
int ResearchValue(int value, int tableau[],int n);
int Ligne_of_case(int num_case);
int Colonne_of_case(int num_case);
void AfficherTab(Candidats_case cand);
void Trier(T_Tab t);
int NombreDeCazNonVides(T_Tab t);
void AppliquerRegle1et2(Grille grille,Candidats_case cand,int pas_a_pas);
void Regle1(Grille grille, Candidats_case cand);
void Regle2(Grille grille, Candidats_case cand, int pas_a_pas);

#endif
