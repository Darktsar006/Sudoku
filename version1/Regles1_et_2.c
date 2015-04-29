/* Toutes les fonctions et procedure liees a la resolution ansi que les regles */

#include "Regles1_et_2.h"

/* Decompose t_ligne la i=ligne eme ligne de la grille */

void DecomposerEnLigne(Grille grille, T_Tab t_ligne, int ligne)
{
    int j;

    for(j=0;j<COLONNES_MAX;j++) t_ligne[j] = grille[ligne][j];
}

/* Decompose dans t_Colonne la j=colonne eme colonne de la grille */

void DecomposerEnColonne(Grille grille, T_Tab t_colonne, int colonne)
{
    int i;

    for(i=0;i<LIGNES_MAX;i++) t_colonne[i]=grille[i][colonne];
}

/* Decompose dans t_region la region correspondant a la case lig col */

void DecomposerEnRegion(Grille grille,T_Region t_region, int lig,int col)
{
    int region=Region(lig,col);

    /* Les coordonnees de la case situee en haut a droite de la region */

    int i=3*(region/3);
    int j=3*(region%3);
    int x,y;

    for(x=i;x<(i+3);x++){
        for(y=j;y<(j+3);y++){
            t_region[x-i][y-j]=grille[x][y];
        }
    }
}

/* Sous-Programme qui recherche une valeur v dans un tableau de n entiers
    Si v est dans tableau, elle renvoie l'indice i de la case
    Sinon elle renvoie n

    _________________________SPECIFICATION____________________________
*/

int ResearchValue(int value, int tableau[],int n)
{
    int i=0;

    while((value != tableau[i])&&(i<n))
    {
        i++;
    }
    if((i==n-1)&&(value!=tableau[n-1]))
    {
        return n;
    }
    else
    {
        return i;
    }
}

/* Fonction retournant le numero de la ligne d'une case */

int Ligne_of_case(int num_case)
{
    return (num_case)/9;
}

/* Fonction retournant le numero de la colonne d'une case */

int Colonne_of_case(int num_case)
{
    return (num_case)%9;
}

/* Retourne le contenu d'une case de la Grille a partir de son numero */

int ValeurCase(Grille grille,int num_case)
{
  int ligne=Ligne_of_case(num_case);
  int colonne=Colonne_of_case(num_case);

  return grille[ligne][colonne];
}

/* Fonction de teste pour voir si tout fonctionnne */

void AfficherTab(Candidats_case cand)
{
    int i,j;
    for(i=0;i<81;i++)
    {
        printf("Lig %d Col %d Candidats: ",Ligne_of_case(i),Colonne_of_case(i));
        for(j=0;j<9;j++)
        {
          if(cand[i][j] != 0 )
          {
            printf("%d ",cand[i][j]);
          }
        }
        printf("\n");
    }
}

/* Regle 1 : On diminue les candidats */

void Regle1(Grille grille,Candidats_case cand)
{
    int i;
    int num_case;
    T_Region reg;
    T_Tab t_ligne,t_colonne;

    for(num_case=0;num_case<81;num_case++)
    {

        /* Si la case n'est pas devoilee */

        if((ValeurCase(grille,num_case)) == 0) /* cette case n'est donc pas resolut */
        {

            /* On decompose la ligne de la case num_case dans t_ligne */

            DecomposerEnLigne(grille,t_ligne,Ligne_of_case(num_case));

            /*On decompose la colonne de la case num_case dans t_colonne */

            DecomposerEnColonne(grille,t_colonne,Colonne_of_case(num_case));

            /* On decompose la region de la case num_case dans reg */

            DecomposerEnRegion(grille,reg,Ligne_of_case(num_case), Colonne_of_case(num_case));
            for(i=0;i<9;i++)
            {
                /* On reduit le tableau des candidats en eliminant les valeurs qui sont sur sa ligne */

                if(EstDansTab(cand[num_case][i], t_ligne)) cand[num_case][i]=0;
            }
            for(i=0;i<9;i++)
            {
                /*On reduit le tableau des candidats en eliminant les valeurs qui sont sur sa colonne */

                if(EstDansTab(cand[num_case][i], t_colonne)) cand[num_case][i]=0;
            }
            for(i=0;i<9;i++)
            {
                /* On reduit le tableau des candidats en eliminant les valeurs qui sont dans sa region */

                if(EstDansReg(cand[num_case][i], reg)) cand[num_case][i]=0;
            }
        }
        else
        {
            /* La case est devoilee, tout ses candidats sont mis a zero */

            for(i=0;i<9;i++) cand[num_case][i]=0;
        }
    }
}

/* Fonction retournant le nombre de cases non vides d'un tableau ce qui sera utuliser pour la regle 2 */

int NombreDeCazNonVides(T_Tab t)
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

void Trier(T_Tab t)
{
  int i,j;
  int tmp;

  for(i=0;i<8;i++)
  {
      for(j=i+1;j<9;j++)
      {
          if(t[i]==0)
          {
              tmp=t[i];
              t[i]=t[j];
              t[j]=tmp;
          }
      }
  }
}

/* Regle 2 : Candidats Seuls */

void Regle2(Grille grille, Candidats_case cand,int pas_a_pas)
{
    int num_case,lig,col;

    for(num_case=0;num_case<81;num_case++)
    {

        /* On commence par trier les candidats pour mettre les cases non vide au debut */

        Trier(cand[num_case]);
        if(NombreDeCazNonVides(cand[num_case])==1) /* Si le nombre de candidat est egale a 1 on peut donc mettre ce candidat */
        {
            lig=Ligne_of_case(num_case);
            col=Colonne_of_case(num_case);


            /* Si on choisit l'affichage pas a pas, on affiche la grille apres chaque affectation */

            /*if(pas_a_pas == 1)
            {
                grille[lig][col]=cand[num_case][0];
                AfficherGrille(grille,lig,col);
                printf("Appuyez sur une touche pour continuer\n");
                getchar();
            }
            else
            {*/
                grille[lig][col]=cand[num_case][0];
            /*}*/
        }
    }
}

/* On applique les regles 1 et 2 pour resoudre la grille */

void AppliquerRegle1et2(Grille grille,Candidats_case cand,int pas_a_pas)
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
