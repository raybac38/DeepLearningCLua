
#ifndef MATRICE_H
#define MATRICE_H

typedef struct input
{
    unsigned taille;
    float* valeurs;
}Input;

typedef struct matrice
{
    unsigned taille;
    float **valeurs;

}SquareMatrix;


SquareMatrix * SquareMatrixInit(unsigned taille);

Input * InputInit(unsigned taille);

void SquareMatrixDestroy(SquareMatrix ** sqm);
void InputDestroy(Input ** input);

SquareMatrix * SquareMatrixInitRandome(unsigned taille);

SquareMatrix * SquareMatrixMutate(SquareMatrix * sqm_ref, float mutation_power);

Input * InputMemcopy(Input * input);

void MatrixExecute(Input ** input_pointeur, SquareMatrix * sqm);

char InputDetermineClasse(Input * input);
void MatrixExecuteNew(Input *input_pointeur, SquareMatrix *sqm);

#endif