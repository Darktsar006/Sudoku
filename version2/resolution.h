#ifndef resolution
#define resolution

#include <stdio.h>
#include <stdlib.h>
#include "Regle1.h"
#include "Regle2.h"
#include "Regle3.h"
#include "Regle4.h"
#include "verification.h"
#include types_et_constantes.h"



void res_AppliquerRegle1et2(Grille grille,Candidats_case cand,int pas_a_pas);
void res_AppliquerRegle3(Grille grille,Candidats_case cand,int pas_a_pas);
void res_AppliquerRegle4(Grille grille, Candidats_case cand,int pas_a_pas);
void Resolution( Grille G,Candidats_case cand,int pas_a_pas);


#endif