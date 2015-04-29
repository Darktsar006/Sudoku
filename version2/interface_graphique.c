/************************************************
 * Module: interface_graphique.c	*
 * Ce modulue Impemente les fonctions et proce-	*
 * dure liées a l'affichage d'une grille depuis	*
 * 
 * Auteur: TRAORE Oumar	*
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/

#include <interface_graphique.h>


/* Affichage du Menu principal */

void interface_Menu()
{
    printw("\t\t\t  +-----+-----+-----+-----+\n");
    printw("\t\t\t   Projet  Sudoku   \n");
    printw("\t\t\t   Fait par TRAORE  \n");
    printw("\t\t     	  +-----+-----+-----+-----+\n");
}


void interface_AfficherSimple(Matrice grille)
{
    int i,j;
   
    printw("\t\t+-----------+-----------+-----------+\n");
    printw("\t\t|           |           |           |\n");

    for(i=0;i<LIGNES_MAX;i++)
    {
        printw("\t\t");
        for(j=0;j<COLONNES_MAX;j++)
        {
            if(j%3 == 0)
            {
                printw("| ");
            }
            else
            {
                printw("  ");
            }
            printw("%d ",grille[i][j]);
        }
        printw("|\n");
        if(((i+1)% 3) == 0)
        {
            printw("\t\t|           |           |           |\n");
            printw("\t\t+-----------+-----------+-----------+\n");
            if (i != 8) printf("\t\t|           |           |           |\n");
        }
    }
    /*printw("\n\n @coopyright TRAORE \n\n");*/
    refresh();
}

/* Procedure d'affichage d'une grille */

void interface_AfficherMatrice(Matrice grille,int lig,int col)
{
    int i,j;
    clear();
    interface_Menu();
    printw("\t\t+-----------+-----------+-----------+\n");
    printw("\t\t|           |           |           |\n");

    for(i=0;i<LIGNES_MAX;i++)
    {
        printw("\t\t");
        for(j=0;j<COLONNES_MAX;j++)
        {
            if(j%3 == 0)
            {
                printw("| ");
            }
            else
            {
                printw("  ");
            }
            if((i==lig)&&(j==col))
            {
                printw("\b[%d]",grille[i][j]);
            }else
            {
                printw("%d ",grille[i][j]);
            }
        }
        printw("|\n");
        if(((i+1)% 3) == 0)
        {
            printw("\t\t|           |           |           |\n");
            printw("\t\t+-----------+-----------+-----------+\n");
            if (i != 8) printf("\t\t|           |           |           |\n");
        }
    }
    /*printw("\n\n @coopyright TRAORE  \n\n");*/
    refresh();
}

/* Procedure qui recopie le contenue de la grille solution dans une fichier */

void interface_AfficherMatriceDansFichier(Matrice grille)
{

    FILE *fichier_grille=fopen("Solution.txt","a+");
    int i,j;
    printw("La Solution de la Matrice se trouvera dans le fichier Matrice.txt \n");
    fprintf(fichier_grille,"\n*** SOLUTION GRILLE ***\n");
    for(i=0;i<LIGNES_MAX;i++)
    {
        for(j=0;j<COLONNES_MAX;j++)
        {
            fprintf(fichier_grille,"%d ",grille[i][j]);
        }
        fprintf(fichier_grille,"\n");
    }
}


/* Procedure permettant de lire Saisie d'une grille via un fichier */

void interface_SaisirMatrice(Matrice grille)
{
  int i,j;
  char nomFichier[20];
  printw("Entrez le nom du fichier dans lequel\n");
  printw("il faut aller chercher la grille: ");
  printw(" de Sudoku a resoudre: ");
  getstr(nomFichier);
  printw("%s",nomFichier);

  FILE *fichier_grille=fopen(nomFichier,"r");
  if(fichier_grille == NULL)
  {
    perror("Erreur lors  de la lecture !!!! (ERREUR ) \n");
  }
  else
  {
    for(i=0;i<LIGNES_MAX;i++)
    {
      for(j=0;j<COLONNES_MAX;j++)
      {
        fscanf(fichier_grille,"%d",&(grille[i][j]));
      }
    }
  }
}

/* Affiche l'aide contenue dans Aide.txt */

void interface_AffichageAide()
{
    clear();
    interface_Menu();
    FILE *fichier_aide=fopen("Aide.txt","r");
    char ligne_fichier[LON_LIG_FICH_MAX]="";

    if(fichier_aide!=NULL)
    {
        while((fgets(ligne_fichier, LON_LIG_FICH_MAX, fichier_aide)) != NULL)
        {
            printw("%s",ligne_fichier);
        }
	/* On ferme le fichier d'aide */

	fclose(fichier_aide);
    }
}
