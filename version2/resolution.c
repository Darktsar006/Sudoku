/************************************************
 * Module: resolution.c				*
 * Ce modulue Resoud le Sudoku en Appliquant	*
 * l'une des 4 regles.
 * Auteur: TRAORE Oumar	*
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/


#include "resolution.h"


/* On applique les regles 1 et 2 pour resoudre la grille */

void res_AppliquerRegle1et2(Grille grille,Candidats_case cand,int pas_a_pas)
{
    int i;
    
    /* On initialise tout les candidats de chaque case */

    for(i=0;i<81;i++) InitialiserCandidats(cand[i]); /* on a donc cand[9]={1,2,3,4,5,6,7,8,9} */
    Grille backup;

    /* On applique les regles 1 et 2 jusqu'a ce qu'elles arretent de modifier la grille en entree*/
    do{
        CopierGrille(grille,backup); /* On copie la grille dans backup */
        Regle1(grille,cand);
        Regle2(grille,cand,pas_a_pas);
    }while(!(GrillesEgales(grille,backup)));
    /* Remarque: A chaque traitement on affecte la grille modifier (par les regles 1 et 2) et on la met dans backup
        et si on constate qu'on a copier les même grille ce qui veux dire qu'on peut plus modifier la grille avec ces 2 regles */
}

/* On applique la regle 3 pour resoudre la grille */

void res_AppliquerRegle3(Grille grille,Candidats_case cand,int pas_a_pas)
{
    res_AppliquerRegle1et2(grille,cand,pas_a_pas); /* on devoile certaines cases à l'aide de la regle 1 et 2 */
    Grille backup;
    /*On applique la regle 3 tant qu'il y'a une case qui contient
    Zero ou que les regles ne modifient plus la grille en entree*/
    do{
        CopierGrille(grille,backup);
        Regle3(grille,cand,pas_a_pas);

    }while((!(GrillesEgales(grille,backup))));
}

/* Application de la regle 4 */

void res_AppliquerRegle4(Grille grille, Candidats_case cand,int pas_a_pas)
{
    /* On applique d'abord la regle 3 */

    res_AppliquerRegle3(grille,cand,pas_a_pas); /* on devoile certaines cases à l'aide de la regle 1, 2 et 3 */

    Grille backup;

    /* On applique la regle 1 : On reduit les Candidats
       On applique la regle 4 : Consideration Inter-Region puis
       On applique la regle 2 : Candidat Seul
       Jusqu'a ce que l'application des regles ne changent plus la grille
       en entree */

    do
    {
        CopierGrille(grille, backup);
        Regle1(grille,cand);
        Regle4(grille,cand);
        Regle2(grille,cand,pas_a_pas);

    }while((!(GrillesEgales(grille,backup))));
}

/* Procedure permettant de resoudre une grille par la force brute */

void Resolution( Grille G,Candidats_case cand,int pas_a_pas)
{
  /* On devoile d'abord la plus part des cases avec les regles 1, 2, 3 et 4 */
  
  res_AppliquerRegle4(G,cand,pas_a_pas);
  
  /* Ensuite on refet un autre traite sur les cases non devoiler pour reapliquer les regles 1, 2, 2 et 4 */
  
	int i, j,k;
	i=0;
	/* Pour toutes les lignes */
	while( i<9 ){
		j = 0;
		/* Pour toutes les colonnes */
		while( j<9 ){
		  
			/* On ne modifie pas les bases */
			
			if(id_ValeurCase(G,9*i+j) == 0)
			{
				/* Tant que la valeurs et inferieur a 9 et */
				/* ne respecte pas toutes les contraintes */
				k=0;
				do
				{
					G[i][j] = cand[9*i+j][k];
					k++;

				}while( k < reg2_NombreDeCaseNonVides(cand[9*i+j]) && !VerifierGrille(G));

				/* Si on ne peut valider la case */
				if( G[i][j] == 0 )
				{
					/* On la vide */
					/* G[i][j] = 0; */

					/* On se replace sur un element modifiable */
					
					do{
						/* On recule d'une colonne */
						j--;
						/* On recule d'une ligne */
						if( j == -1 ){
							j = 8;
							i--;
							/* Aucune Solution */
							if( i == -1 ) i++;
						}

					}while(id_ValeurCase(G,9*i+j)!=0);
				}
				else
				{
				  res_AppliquerRegle4(G,cand,pas_a_pas);
				  j++;
				}

			}else j++;
		}
		i++;
	}
}


