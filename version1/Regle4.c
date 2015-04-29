#include "Regle4.h"

/* Procedure Permettant de reduire les candidats par les considerations inter-region */

void CandJumeauxLigne(Candidats_case cand,int reg)
{
    /* Les coordonnes en haut a gauche de la region reg */

    int lig=3*(reg/3);
    int col=3*(reg%3);

    /*Le numero de case correspondant a la case decrite precedemment */

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

    Trier(rep); /*On trie le tableau contenant les jumeaux et triples

    /*Pour toutes les cases non vides du tableau rep */

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
