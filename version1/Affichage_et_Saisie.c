#include "Affichage_et_Saisie.h"

/* Procedure d'affichage d'une grille */

void AfficherGrille(Grille grille,int lig,int col)
{
    int i,j;

    printf("\t\t+-----------+-----------+-----------+\n");
    printf("\t\t|           |           |           |\n");
    for(i=0;i<LIGNES_MAX;i++)
    {
        printf("\t\t");
        for(j=0;j<COLONNES_MAX;j++)
        {
            if(j%3 == 0)
            {
                printf("| ");
            }
            else
            {
                printf("  ");
            }
            if((i==lig)&&(j==col))
            {
                printf("\b[%d]",grille[i][j]);
            }else
            {
                printf("%d ",grille[i][j]);
            }
        }
        printf("|\n");
        if(((i+1)% 3) == 0)
        {
            printf("\t\t|           |           |           |\n");
            printf("\t\t+-----------+-----------+-----------+\n");
            if (i != 8) printf("\t\t|           |           |           |\n");
        }
    }
}

/* Procedure qui recopie le contenue de la grille solution dans une fichier */

void AfficherGrilleDansFichier(Grille grille){

    FILE *fichier_grille=fopen("Solution.txt","a+");
    int i,j;
    printf("La Solution de la Grille se trouvera dans le fichier Grille.txt \n");
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


/* Procedure de saisie d'une grille version 1 */

void SaisirGrillev1(Grille grille)
{
    int i,j;

    printf("Saisie d'une grille Version 1\n");
    for(i=0;i<LIGNES_MAX;i++)
    {
        printf("Entrez les 9 elements de la ligne %d \n",i+1);
        for(j=0;j<COLONNES_MAX;j++)
        {
            scanf("%d", &(grille[i][j]));
        }
    }
}

/* Procedure de saisie d'une grille version 2 */

void SaisirGrillev2(Grille grille)
{
  InitialiserGrille(grille);
  int lig,col;
  int valeur;

  printf("Saisie d'une grille Version 2 \n");
  printf("Pour terminer la saisie; tapez 0 0 0 ..............\n");
  do{
    printf("Coordonnees sous la forme lig col valCase (ils sont tous compris entre 1 et 9) ");
    scanf("%d", &lig);
    scanf("%d", &col);
    scanf("%d", &valeur);

    if((VerifierCoordonnees(lig,col))&&((valeur >0)&&(valeur <= 9)))
    {
      grille[lig-1][col-1]=valeur;
    }
    else
    {
        printf("Valeur non ajoutee Erreur dans la saisie \n");
    }
  }while((lig != 0 )&&(col != 0)&&(valeur != 0));
}

/* Procedure permettant de lire Saisie d'une grille via un fichier */

void SaisirGrillev3(Grille grille)
{
  int i,j;
  char nomFichier[20];
  printf("Entrez le nom du fichier dans lequel il faut aller chercher la grille");
  printf(" de Sudoku a resoudre \n");
  scanf("%s",nomFichier);
  FILE *fichier_grille=fopen(nomFichier,"r");
  if(fichier_grille == NULL)
  {
    printf("Erreur lors  de la lecture !!!! (ERREUR %d) \n",errno);
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

/* Affichage du Menu principal */

void Menu()
{
    printf("\t\t+-----+-----+-----+\n");
    printf("\t\t  Projet  Sudoku   \n");
    printf("\t\t   Darktsar Exe  \n");
    printf("\t\t+-----+-----+-----+\n");

    printf("1- Resolution de Grilles de SUDOKU \n");
    printf("2- Aide / Instructions \n");
    printf("3- Quitter le programme \n");
    printf("Votre choix : ");
}

/* Affiche l'aide contenue dans Aide.txt */

void AfficherAide()
{
    FILE *fichier_aide=fopen("Aide.txt","r");
    char ligne_fichier[LON_LIG_FICH_MAX]="";

    if(fichier_aide!=NULL)
    {
        while((fgets(ligne_fichier, LON_LIG_FICH_MAX, fichier_aide)) != NULL)
        {
            printf("%s",ligne_fichier);
        }
	/* On ferme le fichier d'aide */

	fclose(fichier_aide);
    }
}
