#ifndef Regle3
#define Regle3

#include <stdio.h>
#include <stdlib.h>
#include "Regle1.h"
#include "verification.h"
#include types_et_constantes.h"



int reg3_NbRepetitionLigne(int nbre,Candidats_case cand,int ligne);
int reg3_NbRepetitionColonne(int nbre,Candidats_case cand,int colonne);
int reg3_NbRepetitionRegion(int nbre,Candidats_case cand,int reg);
int reg3_CandidatUniqueLigne(Candidats_case cand,int ligne);
int reg3_CandidatUniqueColonne(Candidats_case cand,int colonne);
int reg3_CandidatUniqueRegion(Candidats_case cand,int reg);
void Regle3(Matrice grille, Candidats_case cand, int pas_a_pas);
