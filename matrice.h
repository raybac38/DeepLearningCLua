typedef struct input
{
    unsigned taille;
    double* valeurs;
}Input;

typedef struct matrice
{
    unsigned taille;
    double **valeurs;

}SquareMatrix;


SquareMatrix * SquareMatrixInit(unsigned taille);

Input * InputInit(unsigned taille);

void SquareMatrixDestroy(SquareMatrix ** sqm);
void InputDestroy(Input ** input);

SquareMatrix * SquareMatrixInitRandome(unsigned taille);

SquareMatrix * SquareMatrixMutate(SquareMatrix * sqm_ref, double mutation_power);