#ifndef REGLE4
#define REGLE4

#include "Types_et_Constantes.h"
#include "Regles1_et_2.h"
#include "Regle3.h"

void CandJumeauxLigne(Candidats_case cand, int reg);
void CandJumeauxColonne(Candidats_case cand,int reg);
void Regle4(Grille grille,Candidats_case cand);
void AppliquerRegle4(Grille grille, Candidats_case cand,int pas_a_pas);

#endif // REGLE4
