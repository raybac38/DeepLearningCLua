#include "image.h"
#include <stdio.h>
#include <stdlib.h>

#define NB_IMAGE_PAR_BATCH 10000
#define NB_VALEUR 3072

Images *ImageLecture(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("ERROR cannot read pictures\n");
        exit(EXIT_FAILURE);
    }

    Images *images = malloc(sizeof(Images));
    images->taille = NB_IMAGE_PAR_BATCH;
    images->image = malloc(sizeof(Image) * NB_IMAGE_PAR_BATCH);

    unsigned char valeur = 0;

    for (unsigned index_image = 0; index_image < NB_IMAGE_PAR_BATCH; index_image++)
    {
        Image *img = &(images->image[index_image]);
        img->input = InputInit(NB_VALEUR);
        if (0 == fread(&valeur, sizeof(char), 1, f))
        {
            printf("ERROR cannot read pictures classe \n");
            exit(EXIT_FAILURE);
        }
        else
        {
            img->class = (char)valeur;
        }
        for (unsigned index_data = 0; index_data < NB_VALEUR; index_data++)
        {
            double *valeurs = img->input->valeurs;

            if (0 == fread(&valeur, sizeof(char), 1, f))
            {
                printf("ERROR cannot read pictrue classe \n");
                exit(EXIT_FAILURE);
            }
            else
            {
                valeurs[index_data] = (double)(valeur / 255);
            }
        }
    }
    fclose(f);
    return images;
}

void ImagesDestroy(Images **images)
{
    Images *imgs = *images;

    unsigned taille = imgs->taille;

    for (unsigned index_image = 0; index_image < taille; index_image++)
    {
        Image *img = &imgs->image[index_image];
        InputDestroy(&img->input);
    }
    free(imgs->image);
    free(imgs);
    images = NULL;
}
