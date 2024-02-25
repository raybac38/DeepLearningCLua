#ifndef IMAGE_H
#define IMAGE_H



#include "matrice.h"

typedef struct image
{
    char class;
    Input * input;

}Image;



typedef struct images
{
    Image * image;
    unsigned taille;

}Images;

Images * ImageLecture(char *filename);

void ImagesDestroy(Images ** images);

#endif