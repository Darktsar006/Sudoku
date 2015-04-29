/************************************************
 * Module: Regle1.c				*
 * Ce modulue Renseigne les fonctions neces-	*
 * a l'implementation de la regle 1		*
 * Auteur: TRAORE Oumar         *
 * date de creation:				*
 * date de dernier modification:22/04/2012	*/


/* Regle 1 : On diminue les candidats */

void Regle1(Matrice grille,Candidats_case cand)
{
    int i;
    int num_case;
    T_id_Region reg;
    T_Tab t_ligne,t_colonne;

    for(num_case=0;num_case<81;num_case++)
    {

        /* Si la case n'est pas devoilee */

        if((id_ValeurCase(grille,num_case)) == 0) /* cette case n'est donc pas resolut */
        {

            /* On decompose la ligne de la case num_case dans t_ligne */

            id_DecomposerEnLigne(grille,t_ligne,id_Ligne_of_case(num_case));

            /*On decompose la colonne de la case num_case dans t_colonne */

            id_DecomposerEnColonne(grille,t_colonne,id_Colonne_of_case(num_case));

            /* On decompose la region de la case num_case dans reg */

            id_DecomposerEnRegion(grille,reg,id_Ligne_of_case(num_case), id_Colonne_of_case(num_case));
            for(i=0;i<9;i++)
            {
                /* On reduit le tableau des candidats en eliminant les valeurs qui sont sur sa ligne */

                if(verifier_EstDansTAB(cand[num_case][i], t_ligne)) cand[num_case][i]=0;
            }
            for(i=0;i<9;i++)
            {
                /*On reduit le tableau des candidats en eliminant les valeurs qui sont sur sa colonne */

                if(verifier_EstDansTAB(cand[num_case][i], t_colonne)) cand[num_case][i]=0;
            }
            for(i=0;i<9;i++)
            {
                /* On reduit le tableau des candidats en eliminant les valeurs qui sont dans sa region */

                if(verifier_EstDansReg(cand[num_case][i], reg)) cand[num_case][i]=0;
            }
        }
        else
        {
            /* La case est devoilee, tout ses candidats sont mis a zero */

            for(i=0;i<9;i++) cand[num_case][i]=0;
        }
    }
}
