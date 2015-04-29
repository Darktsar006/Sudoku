#ifndef id_case
#define id_case

#include <stdio.h>
#include <stdlib.h>
#include "types_et_constantes.h"
#include "verification.h"

int id_RechercheValeur(int value, int tableau[],int n);
void id_Trier(T_Tab t);
void id_InitialiserCandidats(T_Tab candidats);
void id_InitialiserMatrice(Matrice grille);
void CopierCandidats(Candidats_case candEntree,Candidats_case candSortie);
void id_CopierMatrice(Matrice entree,Matrice dupliquee);
void id_CopierCandidats(Candidats_case candEntree,Candidats_case candSortie);
int id_Region(int ligne, int colonne);
int id_Ligne_of_case(int num_case);
int id_Colonne_of_case(int num_case);
int id_ValeurCase(Matrice grille,int num_case);
void id_DecomposerEnLigne(Matrice grille, T_Tab t_ligne, int ligne);
void id_DecomposerEnColonne(Matrice grille, T_Tab t_colonne, int colonne);
void id_DecomposerEnRegion(Matrice grille,T_id_Region t_region, int lig,int col);
void id_AfficherTab(Candidats_case cand);


#endif