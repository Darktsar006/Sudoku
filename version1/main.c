#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Affichage_et_Saisie.h"
#include "Init_et_Verif.h"
#include "Resolution.h"
#include "Regles1_et_2.h"
#include "Regle3.h"
#include "Regle4.h"
#include "Resolution.h"

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
                            /*On se rassure que la Grille est valide */
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
                //On affiche l'Aide
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
