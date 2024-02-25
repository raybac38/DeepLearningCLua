#include "network.h"
#include <stdlib.h>
#include <stdio.h>

Network * NetworkInitRandom(unsigned couche, unsigned nb_valeur)
{

    Network * network = malloc(sizeof(Network));
    network->neurone = malloc(sizeof(SquareMatrix *) * couche);
    network->couche = couche;

    for (unsigned index = 0; index < couche; index++)
    {
        network->neurone[index] = SquareMatrixInitRandome(nb_valeur);
    }
    return network;
    
}

Network * NetworkInit(unsigned couche, unsigned nb_valeur)
{

    Network * network = malloc(sizeof(Network));
    network->neurone = malloc(sizeof(SquareMatrix *) * couche);

    network->couche = couche;

    for (unsigned index = 0; index < couche; index++)
    {
        network->neurone[index] = SquareMatrixInit(nb_valeur);
    }
    return network;
    
}




Network * NetworkMutate(Network * network_ref, double mutation_power)
{
    unsigned couche = network_ref->couche;
    Network * network = malloc(sizeof(Network));
    network->neurone = malloc(sizeof(SquareMatrix *) * couche);
    network->couche = couche;
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

void NetworkSave(Network * network, char * filename)
{
    unsigned couche = network->couche;
    unsigned taille = network->neurone[0]->taille;

    FILE * f = fopen(filename, "wb");

    fwrite(&couche, sizeof(unsigned), 1, f);
    fwrite(&taille, sizeof(unsigned), 1, f);

    for (unsigned index_couche = 0; index_couche < couche; index_couche++)
    {
        SquareMatrix * current_couche = network->neurone[index_couche];

        for (unsigned index_colone = 0; index_colone < taille; index_colone++)
        {
            double * array_double = current_couche->valeurs[index_colone];

            for (unsigned index_ligne = 0; index_ligne < taille; index_ligne++)
            {
                fwrite(&array_double[index_ligne], sizeof(double), 1, f);
            }
            
        }
        
    }

    NetworkDestroy(&network);
    fclose(f);
}

Network * NetworkLoad(char * filename)
{
    unsigned couche;
    unsigned taille;

    FILE * f = fopen(filename, "rb");

    if(f == NULL)
    {
        printf("Unable to open file \n");
        exit(EXIT_FAILURE);
    }

    if(fread(&couche, sizeof(unsigned), 1, f) == 0)
    {
        printf("ERREUR lecture nombre de couche \n");
        exit(EXIT_FAILURE);
    }

    if(fread(&taille, sizeof(unsigned), 1, f) == 0)
    {
        printf("ERREUR lecture taille matrice\n");
        exit(EXIT_FAILURE);
    }
    Network * network = NetworkInit(couche, taille);

    for (unsigned index_couche = 0; index_couche < couche; index_couche++)
    {
        SquareMatrix * current_couche = network->neurone[index_couche];

        for (unsigned index_colone = 0; index_colone < taille; index_colone++)
        {
            double * array_double = current_couche->valeurs[index_colone];

            for (unsigned index_ligne = 0; index_ligne < taille; index_ligne++)
            {
                if(fread(&array_double[index_ligne], sizeof(double), 1, f) == 0)
                {
                    printf("ERREUR Lecture de donnee\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    fclose(f);
    return network;
}

