#ifndef REGLE3
#define REGLE3

#include "Types_et_Constantes.h"
#include "Init_et_Verif.h"
#include "Regles1_et_2.h"

int NbRepetitionLigne(int nbre,Candidats_case cand,int ligne);
int NbRepetitionColonne(int nbre,Candidats_case cand,int colonne);
int NbRepetitionRegion(int nbre,Candidats_case cand,int reg);
int CandidatUniqueLigne(Candidats_case cand,int ligne);
int CandidatUniqueColonne(Candidats_case cand,int colonne);
int CandidatUniqueRegion(Candidats_case cand,int reg);
void Regle3(Grille grille, Candidats_case cand,int pas_a_pas);
void AppliquerRegle3(Grille grille, Candidats_case cand,int pas_a_pas);

#endif // REGLE3
