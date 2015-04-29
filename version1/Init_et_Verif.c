/* Toutes les FONCTIONS et PROCEDURES d'initialisation et de Verification */

#include "Init_et_Verif.h"

/* Procedure d'initialisation du tableau des candidats*/

void InitialiserCandidats(T_Tab candidats)
{
    int i;

    for(i=0;i<9;i++) candidats[i]=i+1;
}

/* Procedure d'initialisation d'une grille pour mettre toutes les grilles a zero (0) */

void InitialiserGrille(Grille grille)
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

/* Procedure permettant de copier une grille A dans une grille B */

void CopierGrille(Grille entree,Grille dupliquee)
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

/* Fonction booleenne verifiant les coordonnes Pour voir si une case est bien dans la grille */

bool VerifierCoordonnees(int ligne,int colonne)
{
  bool resultat=true;

  return (resultat) && (ligne >= 1) && (ligne <= 9) && (colonne >= 1) && (colonne <= 9);
}

/* Fonction renvoyant la region d'une case donnee*/

int Region(int ligne, int colonne)
{
    return (3*(ligne/3))+(colonne/3);
}

/* Fonction verifiant si une region ne contient pas des cases devoilees de valeurs egales */

bool VerifierRegion(Grille grille,int ligne,int colonne)
{
    int region=Region(ligne,colonne);

    /* Les coordonnees de la case situee en haut a droite de la region */

    int i=3*(region/3);
    int j=3*(region%3);
    int x,y;
    bool res=true;

    for(x=i;x<(i+3);x++)
    {
        for(y=j;y<(j+2);y++)
        {
            res=(res) && ((grille[x][y] == 0) || (grille[x][y] != grille[x][y+1]));
        }
    }
    return res;
}

/* Fonction verifiant si une ligne ne contient pas des cases devoilees de valeurs egales */

bool VerifierLigne(Grille grille, int ligne)
{
    int i;
    bool res=true;

    for(i=0;i<COLONNES_MAX-1;i++)
    {
        res=(res)&&((grille[ligne][i] == 0)||(grille[ligne][i] != grille[ligne][i+1]));
    }
    return res;
}

/* Fonction verifiant si une colonne ne contient pas des cases devoilees de valeurs egales */

bool VerifierColonne(Grille grille, int colonne)
{
    int i;
    bool res=true;

    for(i=0;i<LIGNES_MAX-1;i++)
    {
        res=(res)&&((grille[i][colonne] == 0)|| (grille[i][colonne] != grille[i+1][colonne]));
    }
    return res;
}

/*Fonction booleenne de verification d'une grille*/

bool VerifierGrille(Grille grille){
    int i,j;
    bool res=true;

    /* On verifie que les cases sont devoilees ou dans [1;9] */

    for(i=0;i<LIGNES_MAX;i++)
    {
        for(j=0;j<COLONNES_MAX;j++)
        {
            res=(res)&&(grille[i][j]>=0)&&(grille[i][j]<=9);
        }
    }

    /* On verifie toutes les lignes */

    for(i=0;i<LIGNES_MAX;i++) res=(res)&&(VerifierLigne(grille,i));

    /* On verifie toutes les colonnes */

    for(j=0;j<COLONNES_MAX;j++) res=(res)&&(VerifierColonne(grille,j));

    /* On verifie toutes les regions */

    for(i=0,j=0;i<LIGNES_MAX,j<COLONNES_MAX;i+=3,j+=3)
    {
      res=(res)&&(VerifierRegion(grille,i,j));
    }

    return res;
}

/* Fonction booleene verifiant qu'une valeur est dans un tableau */

bool EstDansTab(int valeur,T_Tab tableau)
{
    if(ResearchValue(valeur,tableau,9)==9)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Fonction booleene verifiant qu'une valeur est dans une region */

bool EstDansReg(int valeur, T_Region reg)
{
    int i,j;
    bool res=false;

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            res=(res)||(reg[i][j] == valeur);
        }
    }
    return res;
}

/* Fonction Verifiant qu'une valeur est dans une grille  */

bool EstDansGrille(int valeur,Grille grille)
{
  int i,j;
  bool res=false;

  for(i=0;i<LIGNES_MAX;i++)
  {
    for(j=0;j<COLONNES_MAX;j++)
    {
      res=(res)||(grille[i][j] == valeur);
    }
  }
  return res;
}

/* Fonction comparant deux grilles */

bool GrillesEgales(Grille grille1,Grille grille2){
    int i,j;
    bool res=true;

    for(i=0;i<LIGNES_MAX;i++)
    {
        for(j=0;j<COLONNES_MAX;j++)
        {
            res=(res)&&((grille1[i][j])==(grille2[i][j]));
        }
    }
    return res;
}

/* Fonction comparant deux tableaux de candidats */

bool TableauxEgaux(T_Tab tab1,T_Tab tab2)
{
    Trier(tab1);
    Trier(tab2);

    int i;
    bool res=true;;

    for(i=0;i<LIGNES_MAX;i++)
    {
        res=(res)&&(tab1[i]==tab2[i]);
    }

    return res;
}
