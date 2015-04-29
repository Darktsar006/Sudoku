/************************************************
 * Module: id_case.c				*
 * Ce modulue defini les des traitement particu-*
 * lier sur la Matrice, trouver la ligne, la co-*
 * lonne, decomposer la ligne etc...		*
 * Auteur: TRAORE Oumar				*
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/


#include <id_case.h>


/* Fonction qui verfie si une valeur est dans un tableau [9] */

int id_RechercheValeur(int value, int tableau[],int n)
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

/* Procedure qui met les 0 d'un tableau à droite */ 

void id_Trier(T_Tab t)
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

/* Procedure d'initialisation du tableau des candidats */

void id_InitialiserCandidats(T_Tab candidats)
{
    int i;

    for(i=0;i<9;i++) candidats[i]=i+1;
}

/* Procedure d'initialisation d'une grille pour mettre toutes les grilles a zero (0) */

void id_InitialiserMatrice(Matrice grille)
{
    int i,j;

    for(i=0;i<LIGNES_MAX;i++)
    {
        for(j=0;j<COLONNES_MAX;j++)
        {
            grille[i][j]=0;
        }
    }
}

/* Procedure permettant de copier une liste de candidats A dans une liste de candidats B */

void CopierCandidats(Candidats_case candEntree,Candidats_case candSortie)
{
  int i,j;

  for(i=0;i<81;i++)
  {
    for(j=0;j<9;j++)
    {
      candSortie[i][j]=candEntree[i][j];
    }
  }
}

/* Procedure permettant de copier une grille A dans une grille B */

void id_CopierMatrice(Matrice entree,Matrice dupliquee)
{
    int i,j;

    for(i=0;i<LIGNES_MAX;i++)
    {
        for(j=0;j<COLONNES_MAX;j++)
        {
            dupliquee[i][j]=entree[i][j];
        }
    }
}

/* Procedure permettant de copier une liste de candidats A dans une liste de candidats B */

void id_CopierCandidats(Candidats_case candEntree,Candidats_case candSortie)
{
  int i,j;

  for(i=0;i<81;i++)
  {
    for(j=0;j<9;j++)
    {
      candSortie[i][j]=candEntree[i][j];
    }
  }
}

/* Fonction renvoyant la region d'une case donnee */

int id_Region(int ligne, int colonne)
{
    return (3*(ligne/3))+(colonne/3);
}


/* Fonction retournant le numero de la ligne d'une case */

int id_Ligne_of_case(int num_case)
{
    return (num_case)/9;
}

/* Fonction retournant le numero de la colonne d'une case */

int id_Colonne_of_case(int num_case)
{
    return (num_case)%9;
}

/* Retourne le contenu d'une case de la Matrice a partir de son numero */

int id_ValeurCase(Matrice grille,int num_case)
{
  int ligne=id_Ligne_of_case(num_case);
  int colonne=id_Colonne_of_case(num_case);

  return grille[ligne][colonne];
}

/* Decompose dans t_Colonne la j=colonne eme colonne de la grille */

void id_DecomposerEnLigne(Matrice grille, T_Tab t_ligne, int ligne)
{
    int j;

    for(j=0;j<COLONNES_MAX;j++) t_ligne[j] = grille[ligne][j];
}

/* Decompose dans t_Ligne la j=Ligne eme colonne de la grille */

void id_DecomposerEnColonne(Matrice grille, T_Tab t_colonne, int colonne)
{
    int i;

    for(i=0;i<LIGNES_MAX;i++) t_colonne[i]=grille[i][colonne];
}

/* Decompose dans t_region la region correspondant a la case lig col */

void id_DecomposerEnRegion(Matrice grille,T_id_Region t_region, int lig,int col)
{
    int region=id_Region(lig,col);

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

void id_AfficherTab(Candidats_case cand)
{
    int i,j;
    for(i=0;i<81;i++)
    {
        printw("Lig %d Col %d Candidats: ",id_Ligne_of_case(i),id_Colonne_of_case(i));
        for(j=0;j<9;j++)
        {
          if(cand[i][j] != 0 )
          {
            printw("%d ",cand[i][j]);
          }
        }
        printw("\n");
    }
}
