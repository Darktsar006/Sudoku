#ifndef interface_graphique
#define interface_graphique

#include <stdio.h>
#include <stdlib.h>


void interface_Menu();
void interface_AfficherSimple(Matrice grille);
void interface_AfficherMatrice(Matrice grille,int lig,int col);
void interface_AfficherMatriceDansFichier(Matrice grille);
void interface_SaisirMatrice(Matrice grille);
void interface_AffichageAide();

#endif