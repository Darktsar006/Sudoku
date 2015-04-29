#ifndef Regle4
#define Regle4

#include <stdio.h>
#include <stdlib.h>
#include "Regle1.h"
#include "verification.h"
#include types_et_constantes.h"



void reg4_CandJumeauxLigne(Candidats_case cand,int reg);
void reg4_CandJumeauxColonne(Candidats_case cand,int reg);
void Regle4(Matrice grille,Candidats_case cand);


#endif