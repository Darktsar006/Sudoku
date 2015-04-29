#ifndef AFFICHAGE_ET_SAISIE
#define AFFICHAGE_ET_SAISIE

#include <stdio.h>
#include <errno.h>
#include "Types_et_Constantes.h"
#include "Init_et_Verif.h"

/*Les prototypes des fonctions du .c correspondant*/
void AfficherGrille(Grille grille,int lig,int col);
void AfficherGrilleDansFichier(Grille grille);
void SaisirGrillev1(Grille grille);
void SaisirGrillev2(Grille grille);
void SaisirGrillev3(Grille grille);
void Menu();
void AfficherAide();

#endif