#include "matrice.h"

typedef struct network
{
    unsigned couche;
    SquareMatrix ** neurone;

}Network;

Network * NetworkInitRandom(unsigned couche, unsigned nb_valeur);

Network * NetworkMutate(Network * network_ref, float mutation_power);

void NetworkDestroy(Network ** network);

void NetworkSave(Network * network, char * filename);

Network * NetworkLoad(char * filename);

