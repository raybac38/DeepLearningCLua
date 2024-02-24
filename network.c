#include "network.h"
#include <stdlib.h>

Network * NetworkInitRandom(unsigned couche, unsigned nb_valeur)
{

    Network * network = malloc(sizeof(Network));
    network->neurone = malloc(sizeof(SquareMatrix) * couche);

    for (unsigned index = 0; index < couche; index++)
    {
        network->neurone[index] = SquareMatrixInitRandome(nb_valeur);
    }
    return network;
    
}





Network * NetworkMutate(Network * network_ref, double mutation_power)
{
    unsigned couche = network_ref->couche;
    Network * network = malloc(sizeof(Network));
    network->neurone = malloc(sizeof(SquareMatrix) * couche);
    for (unsigned index = 0; index < couche; index++)
    {
        network->neurone[index] = SquareMatrixMutate(network_ref->neurone[index], mutation_power);
    }
    return network;


}

void NetworkDestroy(Network ** network)
{
    Network * pointeur = *network;
    unsigned couche = pointeur->couche;
    for (unsigned index = 0; index < couche; index++)
    {
        SquareMatrix * sqm = pointeur->neurone[index];
        free(pointeur->neurone[index]);
        SquareMatrixDestroy(&sqm);
    }

    free(pointeur);
    *network = NULL;
    return;
}

