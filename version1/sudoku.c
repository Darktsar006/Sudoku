#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>


#define LIGNES_MAX 9
#define COLONNES_MAX 9
#define LON_LIG_FICH_MAX 1000

/* Type Grille : Tableau a 2 Dimensions */
typedef int Grille[LIGNES_MAX][COLONNES_MAX];

/* Tableau des 9 entiers */
typedef int T_Tab[9];

/* Region du Sudoku */
typedef int T_Region[3][3];

/* Structure qui a chaque case, associe un tableau de candidats */
typedef T_Tab Candidats_case[81];

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


/* Procedure d'initialisation du tableau des candidats */

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

/* Fonction renvoyant la region d'une case donnee */

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

/* Fonction booleenne de verification d'une grille */

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
  
    j=0;
    i=0;
    while(i<LIGNES_MAX && j<COLONNES_MAX)
    {
      res=(res)&&(VerifierRegion(grille,i,j));
      i+=3;
      j+=3;
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
  /*if(fichier_grille == NULL)
  {
    printf("Erreur lors  de la lecture !!!! (ERREUR %d) \n",errno);
  }*/
  /*else
  {*/
    for(i=0;i<LIGNES_MAX;i++)
    {
      for(j=0;j<COLONNES_MAX;j++)
      {
        fscanf(fichier_grille,"%d",&(grille[i][j]));
      }
    }
  /*}*/
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

            if(pas_a_pas == 1)
            {
                grille[lig][col]=cand[num_case][0];
                AfficherGrille(grille,lig,col);
                printf("Appuyez sur une touche pour continuer\n");
                getchar();
            }
            else
            {
                grille[lig][col]=cand[num_case][0];
            }
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

int NbRepetitionLigne(int nbre,Candidats_case cand,int ligne)
{
    int num_case=ligne*9; /* on rajoute pas la colonne pour se mettre o debut */
    int i;
    int res=0;

    for(i=num_case;i<COLONNES_MAX+num_case;i++)
    {
        if(EstDansTab(nbre,cand[i])) res++;
    }
    return res;
}

/* Fonction retournant le nombre d'occurence de nbre dans les candidats d'une colonne */

int NbRepetitionColonne(int nbre,Candidats_case cand,int colonne)
{
    int num_case=colonne;
    int i;
    int res=0;

    for(i=num_case;i<81;i+=9)
    {
        if(EstDansTab(nbre,cand[i])) res++;
    }
    return res;
}

/* Fonction retournant le nombre d'occurence de nbre dans les candidats d'une region */

int NbRepetitionRegion(int nbre,Candidats_case cand,int reg)
{
    int lig=3*(reg/3);
    int col=3*(reg%3);
    int num_case=lig*9+col;

    int i,j;
    int res=0;

    for(i=num_case;i<num_case+18+1;i=i+9) /* le 18+1 c'est pour parcourir 3 ligne apres ce qui est le nombre de ligne maximum pour une region */
    {
        for(j=0;j<3;j++)
        {
            if(EstDansTab(nbre,cand[i+j])) res++;
        }
    }
    return res;
}

/* Fonction retournant le candidat unique d'une ligne */

int CandidatUniqueLigne(Candidats_case cand,int ligne)
{
    T_Tab rep={0};
    int i;

    for(i=1;i<=9;i++)
    {
        if((NbRepetitionLigne(i,cand,ligne)==1)) rep[i-1]=i;
    }
    Trier(rep);
    if(NombreDeCazNonVides(rep)==1)
    {
        return rep[0];
    }
    else
    {
        return 0;
    }
}

/* Fonction retournant le candidat unique sur une colonne */

int CandidatUniqueColonne(Candidats_case cand,int colonne)
{
    T_Tab rep={0};
    int i;

    for(i=1;i<=9;i++)
    {
        if((NbRepetitionColonne(i,cand,colonne)==1)) rep[i-1]=i;
    }
    Trier(rep);
    if(NombreDeCazNonVides(rep)==1)
    {
        return rep[0];
    }
    else
    {
        return 0;
    }
}

/* Fonction retournant le candidat unique dans une region */

int CandidatUniqueRegion(Candidats_case cand,int reg)
{
    T_Tab rep={0};
    int i;

    for(i=1;i<=9;i++)
    {
        if((NbRepetitionRegion(i,cand,reg)==1)) rep[i-1]=i;
    }
    Trier(rep);
    if(NombreDeCazNonVides(rep)==1)
    {
        return rep[0];
    }
    else
    {
        return 0;
    }
}

/* Regle 3: Candidats Uniques */

void Regle3(Grille grille, Candidats_case cand,int pas_a_pas)
{
    int ligne,colonne,reg,num_case;
    int unique; /* variable qui serra tester si elle est differente de 0 */
    int i,j,k,num,cpt,pos;

    /* Pour chaque ligne, on met le candidat unique a la case dont les candidats contiennent le candidat unique */

    for(ligne=0;ligne<LIGNES_MAX;ligne++)
    {
        /* Le numero de la case au debut de la ligne en question */

        num_case=9*ligne; /* d'ou le retrait de la colonne dans la formule num_case = 9*ligne+colonne */

        /* On trouve le candidat unique sur la ligne */

        unique=CandidatUniqueLigne(cand,ligne);

        /* Si il est different de zero i.e il existe */

        if(unique != 0)
        {
            for(i=0;i<9;i++)
            {
                /*Si le candidat unique sur la ligne est dans les candidats d'une case de la ligne, on le met a la case correspondante */

                if(EstDansTab(unique, cand[num_case+i])) /* plus i pour se deplacer en colonne a partir d'une ligne et donc atteindre le numero des case suivantes */
                {
                    grille[ligne][i]=unique;
                    /*if(pas_a_pas == 1)
                    {
                        AfficherGrille(grille,ligne,i);
                        printf("Appuyez une touche pour continuer\n");
                        getchar();
                    }*/

                    /* On reduit les candidats de la case a zero puisqu'elle est devoilee */

                    for(j=0;j<9;j++) cand[num_case+i][j]=0;

                    /* On enleve le candidat unique parmi les candidats de la colonne correspondant a sa case */

                    for(num=i;num<81;num+=9)
                    {
                        for(cpt=0;cpt<9;cpt++)
                        {
                            if(cand[num][cpt]== unique)
                            {
                                cand[num][cpt]=0;
                                Trier(cand[num]);
                            }
                        }
                    }

                    /* On enleve le candidat unique parmi les candidats de la region correspondant a sa case */

                    reg=Region(ligne,i);
                    pos=27*(reg/3)+3*(reg%3);

                    for(num=pos;num<pos+19;num+=9)
                    {
                        for(cpt=0;cpt<3;cpt++)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num+cpt][j] == unique)
                                {
                                    cand[num+cpt][j]=0;
                                    Trier(cand[num+cpt]);
                                }
                            }
                        }
                    }
        /* REMARQUE : On a pas besoin de supprimer le candidat unique parmi les candidats de sa ligne parcequ'on sait deja qu'il est unique sur la ligne */
                }
            }
        }
    }

    /* Pour chaque colonne, on met le candidat unique a la case dont les candidats contiennent le candidat unique */

    for(colonne=0;colonne<COLONNES_MAX;colonne++)
    {
        /* Le numero de la case au debut de la colonne en question */

        num_case=colonne;

        /* On trouve le candidat unique sur la colonne */

        unique=CandidatUniqueColonne(cand, colonne);

        /* Si le candidat unique est different de zero i.e il existe */

        if(unique != 0 )
        {
            for(i=0;i<9;i++)
            {
                /* Si le candidat unique appartient a la liste des candidats d'une case, on met le candidat unique a la case correspondante */

                if(EstDansTab(unique, cand[num_case+(9*i)]))
                {
                    grille[i][colonne]=unique;
                    if(pas_a_pas == 1)
                    {
                        AfficherGrille(grille,i,colonne);
                        printf("Appuyez une touche pour continuer\n");
                        getchar();
                    }

                    /* On reduit les candidats de la case a zero */

                    for(j=0;j<9;j++) cand[num_case+(9*i)][j]=0;

                    /* On supprime le candidat unique parmi les candidats des autres cases de la ligne correspondante */

                    for(num=i*9;num<9*i+9;num++)
                    {
                        for(cpt=0;cpt<9;cpt++)
                        {
                            if(cand[num][cpt] == unique) cand[num][cpt]=0;Trier(cand[num]);
                        }
                    }

                    /* On supprime le candidat unique parmi les candidats des autres cases de la region correspondante */

                    reg=Region(i,colonne);
                    pos=27*(reg/3)+3*(reg%3);

                    for(num=pos;num<pos+19;num+=9)
                    {
                        for(cpt=0;cpt<3;cpt++)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num+cpt][j] == unique)
                                {
                                    cand[num+cpt][j]=0;Trier(cand[num+cpt]);
                                }
                            }
                        }
                    }

                    /* REMARQUE : On a pas besoin de supprimer le candidat unique parmi les candidats de sa colonne parcequ'on sait deja qu'il est unique sur la colonne */

                }
            }
        }
    }

    /* Pour chaque region, on met le candidat unique a la case dont les candidats contiennent le candidat unique */

    for(reg=0;reg<9;reg++)
    {
        /* Le numero de la case en haut a gauche de la region en question */

        num_case=(27*(reg/3))+(3*(reg%3));

        /* On trouve le candidat unique dans la region */

        unique=CandidatUniqueRegion(cand, reg);

        /* S'il est different de zero i.e il existe */

        if(unique != 0)
        {
            for(i=0;i<3;i++)
            {
                for(j=0;j<3;j++)
                {

                    /* Si le candidat unique sur la region appartient a la liste des candidats d'une case; on le met a la case correspondante */

                    if(EstDansTab(unique, cand[(num_case+9*i+j)]))
                    {
                            ligne=(num_case+9*i+j)/9;
                            colonne=(num_case+9*i+j)%9;

                            grille[ligne][colonne]=unique;
                            if(pas_a_pas == 1)
                            {
                                AfficherGrille(grille,ligne,colonne);
                                printf("Appuyez une touche pour continuer\n");
                                getchar();
                            }

                            /* On reduit les candidats de la case a zero puisqu'elle est devoilee */

                            for(k=0;k<9;k++) cand[(num_case+9*i+j)][k]=0;

                            /* On supprime le candidat unique de la region parmi les candidats de la ligne */

                            for(num=ligne*9;num<9*ligne+9;num++)
                            {
                                for(cpt=0;cpt<9;cpt++)
                                {
                                    if(cand[num][cpt] == unique)
                                    {
                                        cand[num][cpt]=0;
                                        Trier(cand[num]);
                                    }
                                }
                            }

                            /* On supprime le candidat unique de la region parmi les candidats et de la colonne correspondant */

                            for(num=colonne;num<81;num+=9)
                            {
                                for(cpt=0;cpt<9;cpt++)
                                {
                                    if(cand[num][cpt]== unique)
                                    {
                                        cand[num][cpt]=0;
                                        Trier(cand[num]);
                                    }
                                }
                            }

                            /*REMARQUE : On a pas besoin de supprimer le candidat unique parmi les candidats de sa region parcequ'on sait deja qu'il est unique sur la region */
                    }
                }
            }
        }
    }
}


/* On applique la regle 3 pour resoudre la grille */

void AppliquerRegle3(Grille grille,Candidats_case cand,int pas_a_pas)
{
    AppliquerRegle1et2(grille,cand,pas_a_pas); /* on devoile certaines cases à l'aide de la regle 1 et 2 */
    Grille backup;
    /*On applique la regle 3 tant qu'il y'a une case qui contient
    Zero ou que les regles ne modifient plus la grille en entree*/
    do{
        CopierGrille(grille,backup);
        Regle3(grille,cand,pas_a_pas);

    }while((!(GrillesEgales(grille,backup))));
}

/* Procedure Permettant de reduire les candidats par les considerations inter-region */

void CandJumeauxLigne(Candidats_case cand,int reg)
{
    /* Les coordonnes en haut a gauche de la region reg */

    int lig=3*(reg/3);
    int col=3*(reg%3);

    /* Le numero de case correspondant a la case decrite precedemment */

    int num_case=9*lig+col;

    T_Tab rep={0};
    int i,j,num;

    /* On regarde pour chaque candidat de [1;9] son nombre de repetition;
    Si celui-ci est egal a 2 ou 3 i.e c'est un candidat soit jumeau ou triple;
    on le met dans le tableau rep */

    for(i=1;i<=9;i++)
    {
        if(((NbRepetitionRegion(i,cand,reg))==2)||((NbRepetitionRegion(i,cand,reg))==3))
        {
            rep[i-1]=i;
        }
    }

    Trier(rep); /* On trie le tableau contenant les jumeaux et triples */

    /* Pour toutes les cases non vides du tableau rep */

    for(i=0;i<(NombreDeCazNonVides(rep));i++)
    {

        /* Si le nombre de repetion d'une valeur du tableau est egal a 2 i.e il a un jumeau parmi */

        if((NbRepetitionRegion(rep[i],cand,reg))==2)
        {

            /* On se rassure qu'il soient(son jumeau et lui) candidats a deux cases sur la meme ligne
                avant de les supprimer parmi les candidats des autres cases de la ligne; on a 3 configurations
                possible XX? ?XX X?X */

        if(((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+1])))||
        ((EstDansTab(rep[i],cand[num_case+1]))&&(EstDansTab(rep[i],cand[num_case+2])))||
        ((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+2]))))
        {

            /* On supprime rep[i](le jumeau) parmi les candidats de la ligne */

            for(num=9*lig;num<(9*lig)+9;num++)
            {

                /* On se rassure de ne pas supprimer les jumeaux parmi les candidats de leur region */

                if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                {
                    for(j=0;j<9;j++)
                    {
                        if(cand[num][j] == rep[i])
                        {
                            cand[num][j]=0;
                            Trier(cand[num]);
                        }
                    }
                }
            }
        }
        else
            if(((EstDansTab(rep[i],cand[num_case+9]))&&(EstDansTab(rep[i],cand[num_case+10])))||
            ((EstDansTab(rep[i],cand[num_case+10]))&&(EstDansTab(rep[i],cand[num_case+11])))||
            ((EstDansTab(rep[i],cand[num_case+9]))&&(EstDansTab(rep[i],cand[num_case+11]))))
            {
                for(num=lig*9+9;num<9*lig+18;num++)
                {
                    if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                    {
                        for(j=0;j<9;j++)
                        {
                            if(cand[num][j]==rep[i])
                            {
                                cand[num][j]=0;
                                Trier(cand[num]);
                            }
                        }
                    }
                }
            }
            else
            if(((EstDansTab(rep[i],cand[num_case+18])&&(EstDansTab(rep[i],cand[num_case+19]))))||
            ((EstDansTab(rep[i],cand[num_case+19])&&(EstDansTab(rep[i],cand[num_case+20]))))||
            ((EstDansTab(rep[i],cand[num_case+18])&&(EstDansTab(rep[i],cand[num_case+20])))))
            {
                for(num=lig*9+18;num<9*lig+27;num++)
                {
                    if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                    {
                        for(j=0;j<9;j++)
                        {
                            if(cand[num][j]==rep[i])
                            {
                                cand[num][j]=0;
                                Trier(cand[num]);
                            }
                        }
                    }
                }
            }
            }
            else
            if((NbRepetitionRegion(rep[i],cand,reg))==3)
            {
                if((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+1]))&&(EstDansTab(rep[i],cand[num_case+2])))
                {
                    for(num=9*lig;num<(9*lig)+9;num++)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j] == rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }
                else
                if((EstDansTab(rep[i],cand[num_case+9]))&&(EstDansTab(rep[i],cand[num_case+10]))&&(EstDansTab(rep[i],cand[num_case+11])))
                {
                    for(num=lig*9+9;num<9*lig+18;num++)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j]==rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }else
                if((EstDansTab(rep[i],cand[num_case+18]))&&(EstDansTab(rep[i],cand[num_case+19]))&&(EstDansTab(rep[i],cand[num_case+20])))
                {
                    for(num=lig*9+18;num<9*lig+27;num++)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j]==rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }
            }
    }
}

void CandJumeauxColonne(Candidats_case cand,int reg)
{
    int lig=3*(reg/3);
    int col=3*(reg%3);
    int num,num_case=9*lig+col;

    T_Tab rep={0};
    int i,j;


    for(i=1;i<=9;i++)
    {
        if(((NbRepetitionRegion(i,cand,reg))==2)||((NbRepetitionRegion(i,cand,reg))==3))
        {
            rep[i-1]=i;
        }
    }

    Trier(rep);

    for(i=0;i<(NombreDeCazNonVides(rep));i++)
    {
        if((NbRepetitionRegion(rep[i],cand,reg))==2)
        {
            if(((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+9])))||
            ((EstDansTab(rep[i],cand[num_case+9])&&(EstDansTab(rep[i],cand[num_case+18]))))||
            ((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+18]))))
            {
                for(num=col;num<81;num+=9)
                {
                    if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                    {
                        for(j=0;j<9;j++)
                        {
                            if(cand[num][j] == rep[i])
                            {
                                cand[num][j]=0;
                                Trier(cand[num]);
                            }
                        }
                    }
                }
            }
            else
            if(((EstDansTab(rep[i],cand[num_case+1]))&&(EstDansTab(rep[i],cand[num_case+10])))||
            ((EstDansTab(rep[i],cand[num_case+10]))&&(EstDansTab(rep[i],cand[num_case+19])))||
            ((EstDansTab(rep[i],cand[num_case+1]))&&(EstDansTab(rep[i],cand[num_case+19]))))
            {
                for(num=col+1;num<81;num+=9)
                {
                    if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                    {
                        for(j=0;j<9;j++)
                        {
                            if(cand[num][j] == rep[i])
                            {
                                cand[num][j]=0;
                                Trier(cand[num]);
                            }
                        }
                    }
                }
            }
            else
            if((((EstDansTab(rep[i],cand[num_case+2]))&&(EstDansTab(rep[i],cand[num_case+11]))))||
            ((EstDansTab(rep[i],cand[num_case+11]))&&(EstDansTab(rep[i],cand[num_case+20])))||
            ((EstDansTab(rep[i],cand[num_case+2]))&&(EstDansTab(rep[i],cand[num_case+20]))))
            {
                for(num=col+2;num<81;num+=9)
                {
                    if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                    {
                        for(j=0;j<9;j++)
                        {
                            if(cand[num][j] == rep[i])
                            {
                                cand[num][j]=0;
                                Trier(cand[num]);
                            }
                        }
                    }
                }
            }
            }else
            if((NbRepetitionRegion(rep[i],cand,reg))==3)
            {
                if((EstDansTab(rep[i],cand[num_case]))&&(EstDansTab(rep[i],cand[num_case+9]))&&(EstDansTab(rep[i],cand[num_case+18])))
                {
                    for(num=col;num<81;num+=9)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j] == rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }
                else
                if ((EstDansTab(rep[i],cand[num_case+1]))&&(EstDansTab(rep[i],cand[num_case+10]))&&(EstDansTab(rep[i],cand[num_case+19])))
                {
                    for(num=col+1;num<81;num+=9)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j] == rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }
                else
                if ((EstDansTab(rep[i],cand[num_case+2]))&&(EstDansTab(rep[i],cand[num_case+11]))&&(EstDansTab(rep[i],cand[num_case+20])))
                {
                    for(num=col+2;num<81;num+=9)
                    {
                        if((Region(Ligne_of_case(num),Colonne_of_case(num))) != reg)
                        {
                            for(j=0;j<9;j++)
                            {
                                if(cand[num][j] == rep[i])
                                {
                                    cand[num][j]=0;
                                    Trier(cand[num]);
                                }
                            }
                        }
                    }
                }
            }
    }
}

/* Regle 4: Consideration Inter-Region */

void Regle4(Grille grille,Candidats_case cand)
{
    int reg;

    /* Pour chaque region, on supprime les candidats jumeaux ou triples
      des lignes ou colonnes des autres regions voisines */

    for(reg=0;reg<9;reg++)
    {
        CandJumeauxLigne(cand,reg);
        CandJumeauxColonne(cand,reg);
    }
}

/* Application de la regle 4 */

void AppliquerRegle4(Grille grille, Candidats_case cand,int pas_a_pas)
{
    /* On applique d'abord la regle 3 */

    AppliquerRegle3(grille,cand,pas_a_pas); /* on devoile certaines cases à l'aide de la regle 1, 2 et 3 */

    Grille backup;

    /* On applique la regle 1 : On reduit les Candidats
       On applique la regle 4 : Consideration Inter-Region puis
       On applique la regle 2 : Candidat Seul
       Jusqu'a ce que l'application des regles ne changent plus la grille
       en entree */

    do
    {
        CopierGrille(grille,backup);
        Regle1(grille,cand);
        Regle4(grille,cand);
        Regle2(grille,cand,pas_a_pas);

    }while((!(GrillesEgales(grille,backup))));
}

void Resolution( Grille G,Candidats_case cand,int pas_a_pas){
  AppliquerRegle4(G,cand,pas_a_pas);
	int i, j,k;

	i=0;
	/* Pour toutes les lignes */
	while( i<9 ){
		j = 0;
		/* Pour toutes les colonnes */
		while( j<9 ){
			/* On ne modifie pas les bases */
			if( ValeurCase(G,9*i+j) == 0){
				/* Tant que la valeurs et inferieur a 9 et */
				/* ne respecte pas toutes les contraintes */
				k=0;
				do
				{
					G[i][j] = cand[9*i+j][k];
					k++;

				}while( k < NombreDeCazNonVides(cand[9*i+j]) && !VerifierGrille(G));

				/* Si on ne peut valider la case */
				if( G[i][j] == 0 ){
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


int main(){
  Grille sudoku;
  Candidats_case candidats;
  char pap;
  int pas_a_pas;
    time_t deb,fin;
    time(&deb);
    int choix,mode;
    char continuer='o';
    while (continuer == 'o'){
        Menu();
        scanf("%d", &choix);

        switch(choix){
            case 1: printf("\t\tSUDOKU SOLVER\n");
                printf("Quel mode de saisie preferez vous ?\n");
                printf("1: Vous taper les 9 valeurs de chaque ligne \n");
                printf("2: Vous entrez les coordonnees des cases devoilees et leurs valeurs \n");
                printf("3: Vous mettez la grille dans un fichier du dossier courant \n");
                scanf("%d", &mode);
                char test='o';
                while ( test=='o'){
                  switch (mode){
                    case 1: SaisirGrillev1(sudoku);
                            /*On se rassure que la Grille est valide */
                            if(VerifierGrille(sudoku)){
                              printf("Grille Chargee avec succes!!!\n");
                              test='n';
                            }else{
                              printf("Il y'a eu erreur lors de la saisie de la Grille \n ");
                              printf("Reessayer !!!!!!!\n");
                              test='o';
                            }
                    break;
                    case 2: SaisirGrillev2(sudoku);
                            printf("Grille Chargee !!!\n");
                            test='n';
                    break;
                    case 3: SaisirGrillev3(sudoku);
                            /* On se rassure que la Grille est valide */
                            if(VerifierGrille(sudoku)){
                              printf("Grille Chargee avec succes !!!\n");
                              test='n';
                            }else{
                              printf("Il y'a eu erreur lors de la saisie de la Grille \n ");
                              printf("Reessayer !!!!!!!\n");
                              test='o';
                            }
                    break;
                    default: printf("Erreur de mode ");
                             printf("Entrez un mode correct 1, 2, ou 3 : ");
                             scanf("%d", &mode);
                             test='o';
                    break;
                }
              }
                printf("Voulez vous executer le mode pas a pas ? O/N ");
                scanf("\n %c", &pap);
                pap=tolower(pap);
                pas_a_pas=(pap == 'o')?1:0;
                Resolution(sudoku,candidats,pas_a_pas);
                printf("\t\t\t   GRILLE RESOLUE \n");
                AfficherGrille(sudoku,-1,-1);
                printf("Une autre Grille a resoudre ? O/N ");
                scanf("\n %c", &continuer);
                continuer=tolower(continuer);
          break;
          case 2:
                /* On affiche l'Aide */
                AfficherAide();
                printf("Voulez vous essayer une grille ? O/N ");
                scanf("\n %c", &continuer);
                continuer=tolower(continuer);
          break;
          case 3:printf("Vous avez choisi de finir l'execution du programme \n");
                continuer='N';
          break;
          default:printf("S'il vous plait entrez un choix valide : ");
                continuer='o';
          break;
        }
    }

    time(&fin);
    if(pas_a_pas != 1) printf("Vous avez mis %.f secs \n",difftime(fin,deb));
    return 0;
}
