#include "matrice.h"
#include "image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NB_PAR_GENERATION 100
#define NB_EVOLUTION 30

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

    ImagesDestroy(&bank_images);
    
    free(filename);

}


