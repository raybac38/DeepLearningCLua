#include "matrice.h"
#include "classement.h"
#include "image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NB_PAR_GENERATION 100
#define NB_GENERATION 30
const unsigned COUCHE_NEURONAL = 10;
const unsigned TAILLE_IMAGE_X = 32;
const unsigned TAILLE_IMAGE_Y = 32;

const char * FICHIER_IMAGE = "/media/raybac38/HDD/cifar-10-binary/cifar-10-batches-bin/data_batch_1.bin";


int main()
{
   
    printf("Lancement du deep learning\n");
    printf("Lecture des images\n");

    char * filename = malloc(sizeof(char) * 200);
    memcpy(filename, FICHIER_IMAGE, 199);
    filename[199] = '\0';

    Images * bank_images = ImageLecture(filename);

    printf("fichier d'image lu\n");

    for (unsigned index_generation = 0; index_generation < NB_GENERATION; index_generation++)
    {
        
    }

    ImagesDestroy(&bank_images);
    
    free(filename);

}




void RandomGeneration(Classement * classement)
{

    unsigned nb_valeur = TAILLE_IMAGE_X * TAILLE_IMAGE_Y;
    for (unsigned index_individu = 0; index_individu < NB_PAR_GENERATION; index_individu++)
    {
        
        Network * network = NetworkInitRandom(COUCHE_NEURONAL, nb_valeur);
        unsigned network_score = 0;




        ClassementUpdate(classement, &network, network_score);
    }
    
}


unsigned NetworkEvaluate(Images * bank_images, Network * network)
{
    unsigned score = 0;
    unsigned nombre_image = bank_images->taille;


    for (unsigned index_image = 0; index_image < nombre_image; index_image++)
    {
        Image * img = &(bank_images->image[index_image]);

        Input * data = InputMemcopy(img->input);
        char class = img->class;
        unsigned couche = network->couche;
        
        for (unsigned index_couche = 0; index_couche < couche; index_couche++)
        {
            MatrixExecute(&data, network->neurone[index_couche]);
        }
        if(class == InputDetermineClasse(data))
        {
            score++;
        }
        InputDestroy(&data);
    }
    return score;
}