/************************************************
 * Module: verification.c			*
 * Ce modulue Impemente les fonctions et proce-	*
 * dure liées a la verification de la grille	*
 * Auteur: TRAORE Oumar	*
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/


#include "verification.h"


/* Fonction booleenne verifiant les coordonnes Pour voir si une case est bien dans la grille */

bool verifier_Coordonnees(int ligne,int colonne)
{
  bool resultat=true;

  return (resultat) && (ligne >= 1) && (ligne <= 9) && (colonne >= 1) && (colonne <= 9);
}


/* Fonction verifiant si une region ne contient pas des cases devoilees de valeurs egales */

bool verifier_Region(Matrice grille,int ligne,int colonne)
{
    int region=id_Region(ligne,colonne);

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

bool verifier_Ligne(Matrice grille, int ligne)
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

bool verifier_Colonne(Matrice grille, int colonne)
{
    int i;
    bool res=true;

    for(i=0;i<LIGNES_MAX-1;i++)
    {
        res=(res)&&((grille[i][colonne] == 0)|| (grille[i][colonne] != grille[i+1][colonne]));
    }
    return res;
}

/* Fonction booleenne de verification d'une grille */

bool verifier_Matrice(Matrice grille)
{
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

    for(i=0;i<LIGNES_MAX;i++) res=(res)&&(verifier_Ligne(grille,i));

    /* On verifie toutes les colonnes */

    for(j=0;j<COLONNES_MAX;j++) res=(res)&&(verifier_Colonne(grille,j));

    /* On verifie toutes les regions */
  
    j=0;
    i=0;
    while(i<LIGNES_MAX && j<COLONNES_MAX)
    {
      res=(res)&&(verifier_Region(grille,i,j));
      i+=3;
      j+=3;
    }

    return res;
}

/* Fonction booleene verifiant qu'une valeur est dans un tableau */

bool verifier_EstDansTAB(int valeur,T_Tab tableau)
{
    if(id_RechercheValeur(valeur,tableau,9)==9)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Fonction booleene verifiant qu'une valeur est dans une region */

bool verifier_EstDansReg(int valeur, T_id_Region reg)
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

bool verifier_EstDansMatrice(int valeur,Matrice grille)
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

bool verifier_MatricesEgales(Matrice grille1,Matrice grille2)
{
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

bool verifier_TableauxEgaux(T_Tab tab1,T_Tab tab2)
{
    id_Trier(tab1);
    id_Trier(tab2);

    int i;
    bool res=true;;

    for(i=0;i<LIGNES_MAX;i++)
    {
        res=(res)&&(tab1[i]==tab2[i]);
    }

    return res;
}
