#include "network.h"
#include <stdlib.h>

typedef struct classement
{
    Network * premier;
    unsigned score_premier;
    Network * second;
    unsigned score_second;
    Network * troiseme;
    unsigned score_troiseme;
}Classement;

Classement * ClassementInit()
{
    Classement * classement = malloc(sizeof(Classement));
    classement->premier = NULL;
    classement->score_premier = 0;
    classement->second = NULL;
    classement->score_second = 0;
    classement->troiseme = NULL;
    classement->score_troiseme = 0;
    return classement;
}

/* Met a jour le classement, met le pointeur quandidat a NULL apres*/
void ClassementUpdate(Classement * classement, Network ** quandidat, unsigned score)
{
    Network * pointeur = NULL;

    if(classement->score_premier < score)
    {
        pointeur = classement->premier;
        classement->score_premier = score;
        classement->premier = *quandidat;
    }
    else if(classement->score_second < score)
    {
        pointeur = classement->second;
        classement->score_second = score;
        classement->second = *quandidat;
    }
    else if(classement->score_troiseme < score)
    {
        pointeur = classement->troiseme;
        classement->score_troiseme = score;
        classement->troiseme = *quandidat;
    }else
    {
        pointeur = *quandidat;
    }


    NetworkDestroy(&pointeur);
    *quandidat = NULL;
}