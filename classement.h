#ifndef CLASSEMENT_H
#define CLASSEMENT_H

#include "network.h"

typedef struct classement
{
    Network * premier;
    unsigned score_premier;
    Network * second;
    unsigned score_second;
    Network * troiseme;
    unsigned score_troiseme;
}Classement;

Classement * ClassementInit();

void ClassementUpdate(Classement * classement, Network ** quandidat, unsigned score);


#endif