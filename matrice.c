#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include <time.h>

SquareMatrix *SquareMatrixInit(unsigned taille)
{
    SquareMatrix *sqm = (SquareMatrix *)malloc(sizeof(SquareMatrix));
    sqm->taille = taille;

    sqm->valeurs = malloc(sizeof(double *) * taille);

    for (unsigned index = 0; index < taille; index++)
    {
        sqm->valeurs[index] = malloc(sizeof(double) * taille);
    }

    return sqm;
}

Input *InputInit(unsigned taille)
{
    
    Input *input = malloc(sizeof(Input));
    input->taille = taille;
    input->valeurs = malloc(sizeof(double) * taille);
    return input;
}

SquareMatrix *SquareMatrixInitRandome(unsigned taille)
{
    srand((unsigned)time(NULL));
    SquareMatrix *sqm = (SquareMatrix *)malloc(sizeof(SquareMatrix));
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

SquareMatrix *SquareMatrixMutate(SquareMatrix *sqm_ref, double mutation_power)
{
    unsigned taille = sqm_ref->taille;
    SquareMatrix *sqm = SquareMatrixInit(taille);

    double valeur = 0;

    for (size_t indexI = 0; indexI < taille; indexI++)
    {
        for (size_t indexJ = 0; indexJ < taille; indexJ++)
        {
            valeur = sqm_ref->valeurs[indexI][indexJ] + mutation_power * (double)((rand() - (RAND_MAX / 2)) / RAND_MAX);
            if (valeur > 1)
            {
                valeur = 1;
            }
            else if (valeur < 0)
            {
                valeur = 0;
            }
            sqm->valeurs[indexI][indexJ] = valeur;
        }
    }
    return sqm;
}

void SquareMatrixDestroy(SquareMatrix **sqm)
{
    SquareMatrix *pointeur = *sqm;
    unsigned taille = (*sqm)->taille;

    for (unsigned indexI = 0; indexI < taille; indexI++)
    {
        free(pointeur->valeurs[indexI]);
    }
    free(pointeur->valeurs);
    free(pointeur);
    *sqm = NULL;
}
void InputDestroy(Input **input)
{
    Input *pointeur = *input;
    free(pointeur->valeurs);
    free(pointeur);
    input = NULL;
}

Input *InputMemcopy(Input *input)
{
    unsigned taille = input->taille;
    
    Input *newInput = InputInit(taille);

    for (unsigned index_valeur = 0; index_valeur < taille; index_valeur++)
    {
        newInput->valeurs[index_valeur] = input->valeurs[index_valeur];
    }

    return newInput;
}

/* Vielle version, marche mais boite lol*/
void MatrixExecute(Input **input_pointeur, SquareMatrix *sqm)
{
    Input *input = *input_pointeur;
    unsigned taille = input->taille;
    double *double_array_input = input->valeurs;

    double inv_taille = 1 / taille;

    Input *output = InputInit(taille);

    double *double_array_output = output->valeurs;

    for (unsigned index_colone = 0; index_colone < taille; index_colone++)
    {
        double *colone = sqm->valeurs[index_colone];

        double valeur = 0;
        for (unsigned index_ligne = 0; index_ligne < taille; index_ligne++)
        {
            valeur += double_array_input[index_ligne] * colone[index_ligne];
        }
        valeur *= inv_taille;

        double_array_output[index_colone] = valeur;
    }

    InputDestroy(input_pointeur);
    *input_pointeur = output;
}

/*Nouvelle version en espérant plus de performance*/
void MatrixExecuteNew(Input *input, SquareMatrix *sqm)
{
    unsigned taille = sqm->taille;
    
    double * double_array = malloc(sizeof(double) * taille);

    double inv_taille = 1 / taille;
    //Initialisation des pointeurs

    double * ptrInput = input->valeurs;
    double * ptrOutput = double_array;
    double ** ptrColone = sqm->valeurs;
    double * ptrLigne = *ptrColone;

    for (unsigned index_colone = 0; index_colone < taille; index_colone++)
    {
        for (unsigned index_ligne = 0; index_ligne < taille; index_ligne++)
        {
            *ptrOutput = (*ptrLigne++) * *ptrInput;
        }
        ptrInput++;
        ptrColone++;
        (*ptrOutput++) *= inv_taille;
        ptrLigne = ptrColone[index_colone];
    }

    free(input->valeurs);
    input->valeurs = double_array;
}


char InputDetermineClasse(Input *input)
{
    double maximum = 0;
    char index_max = 0;

    double *array_double = input->valeurs;

    for (unsigned index = 0; index < 10; index++)
    {
        double valeur = array_double[index];

        if (valeur > maximum)
        {
            maximum = valeur;
            index_max = index;
        }
    }

    return index_max;
}