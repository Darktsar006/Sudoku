/************************************************
 * Module: Regle1.c				*
 * Ce modulue Renseigne les fonctions neces-	*
 * a l'implementation de la regle 2		*
 * Auteur: TRAORE Oumar         *
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/

#include <Regle2.h>


/* Fonction retournant le nombre de cases non vides d'un tableau ce qui sera utuliser pour la regle 2 */

int reg3_NombreDeCaseNonVides(T_Tab t)
{
  int i,nbcases=0;

  for(i=0;i<9;i++)
  {
      if(t[i]!=0)
      {
          nbcases++;
      }
  }
  return nbcases;
}

/* Fonction qui mets les cases non vides d'un tableau au debut */


/* Regle 2 : Candidats Seuls */

void Regle2(Matrice grille, Candidats_case cand, int pas_a_pas)
{
    int num_case,lig,col;

    for(num_case=0;num_case<81;num_case++)
    {

        /* On commence par trier les candidats pour mettre les cases non vide au debut */

        id_Trier(cand[num_case]);
        if(reg3_NombreDeCaseNonVides(cand[num_case])==1) /* Si le nombre de candidat est egale a 1 on peut donc mettre ce candidat */
        {
            lig=id_Ligne_of_case(num_case);
            col=id_Colonne_of_case(num_case);


            /* Si on choisit l'affichage pas a pas, on affiche la grille apres chaque affectation */

            if(pas_a_pas == 1)
            {
                grille[lig][col]=cand[num_case][0];
                interface_AfficherMatrice(grille,lig,col);
                printw("Appuyez sur une touche pour continuer\n");
                getch();
            }
            else
            {
                grille[lig][col]=cand[num_case][0];
            }
        }
    }
}
