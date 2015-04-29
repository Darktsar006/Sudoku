#include "Regle4.h"

void Resolution( Grille G,Candidats_case cand,int pas_a_pas){
  AppliquerRegle4(G,cand,pas_a_pas);
	int i, j,k;

	i=0;
	//Pour toutes les lignes
	while( i<9 ){
		j = 0;
		//Pour toutes les colonnes
		while( j<9 ){
			//On ne modifie pas les bases
			if( ValeurCase(G,9*i+j) == 0){
				//Tant que la valeurs et inferieur a 9 et
				//ne respecte pas toutes les contraintes
				k=0;
				do
				{
					G[i][j] = cand[9*i+j][k];
					k++;

				}while( k < NombreDeCazNonVides(cand[9*i+j]) && !VerifierGrille(G));

				//Si on ne peut valider la case
				if( G[i][j] == 0 ){
					//On la vide
					//G[i][j] = 0;

					//On se replace sur un element modifiable
					do{
						//On recule d'une colonne
						j--;
						//On recule d'une ligne
						if( j == -1 ){
							j = 8;
							i--;
							//Aucune Solution
							if( i == -1 ) i++;
						}

					}while( ValeurCase(G,9*i+j)!=0);
				}else{
				  AppliquerRegle4(G,cand,pas_a_pas);
				  j++;
				}

			}else j++;
		}
		i++;
	}
}
