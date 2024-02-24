#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include <time.h>

SquareMatrix * SquareMatrixInit(unsigned taille)
{
    SquareMatrix * sqm = (SquareMatrix *)malloc(sizeof(SquareMatrix));
    sqm->taille = taille;

    sqm->valeurs = malloc(sizeof(double *) * taille);

    for (unsigned index = 0; index < taille; index++)
    {
        sqm->valeurs[index] = malloc(sizeof(double) * taille);
    }
    
    return sqm;
}

Input * InputInit(unsigned taille)
{
    Input * input = malloc(sizeof(Input));
    input->taille = taille;
    input->valeurs = malloc(sizeof(double) * taille);
    return input;
}

SquareMatrix * SquareMatrixInitRandome(unsigned taille)
{
    srand((unsigned) time(NULL));
    SquareMatrix * sqm = (SquareMatrix *)malloc(sizeof(SquareMatrix));
    sqm->taille = taille;

    sqm->valeurs = malloc(sizeof(double *) * taille);

    for (unsigned indexI = 0; indexI < taille; indexI++)
    {
        sqm->valeurs[indexI] = malloc(sizeof(double) * taille);

        for (unsigned indexJ = 0; indexJ < taille; indexJ++)
        {
            sqm->valeurs[indexI][indexJ] = (double)rand() / RAND_MAX;
        }
    }
    
    return sqm;
}


SquareMatrix * SquareMatrixMutate(SquareMatrix * sqm_ref, double mutation_power)
{
    unsigned taille = sqm_ref->taille;
    SquareMatrix * sqm = SquareMatrixInit(taille);

    double valeur = 0;

    for (size_t indexI = 0; indexI < taille; indexI++)
    {
        for (size_t indexJ = 0; indexJ < taille; indexJ++)
        {
            valeur = sqm_ref->valeurs[indexI][indexJ] + mutation_power * (double)( (rand() - (RAND_MAX / 2)) / RAND_MAX);
            if(valeur > 1)
            {
                valeur = 1;
            }
            else if(valeur < 0)
            {
                valeur = 0;
            }
            sqm->valeurs[indexI][indexJ] = valeur;
        }
    }
    return sqm;
}

void SquareMatrixDestroy(SquareMatrix ** sqm)
{
    SquareMatrix * pointeur = *sqm;
    unsigned taille = (*sqm)->taille;


    for (unsigned indexI = 0; indexI < taille; indexI++)
    {
        free(pointeur->valeurs[indexI]);
    }
    free(pointeur->valeurs);
    free(pointeur);
    *sqm = NULL;
}
void InputDestroy(Input ** input)
{
    Input * pointeur = *input;
    free(pointeur->valeurs);
    free(pointeur);
    input = NULL;
}