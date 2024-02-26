#include "matrice.h"
#include "classement.h"
#include "image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NB_PAR_GENERATION 10
#define NB_GENERATION 2
const unsigned COUCHE_NEURONAL = 2;
const unsigned TAILLE_IMAGE_X = 32;
const unsigned TAILLE_IMAGE_Y = 32;

const char * FICHIER_IMAGE = "/media/raybac38/HDD/cifar-10-binary/cifar-10-batches-bin/data_batch_1.bin";

void RandomGeneration(Classement * classement, Images * bank_images);
void MutateGeneration(Classement * classement, Images * bank_images);
unsigned NetworkEvaluate(Images * bank_images, Network * network);



int main()
{
   
    printf("Lancement du deep learning\n");
    printf("Lecture des images\n");

    char * filename = malloc(sizeof(char) * 200);
    memcpy(filename, FICHIER_IMAGE, 199);
    filename[199] = '\0';

    Images * bank_images = ImageLecture(filename);

    printf("fichier d'image lu\n");

    Classement * classement = ClassementInit();

    

    RandomGeneration(classement, bank_images);


    for (unsigned index_generation = 0; index_generation < NB_GENERATION; index_generation++)
    {
        MutateGeneration(classement, bank_images);
    }

    printf("Score du pemier ; %d\n", classement->score_premier);

    char fileoutname[] = "premier\0";
    NetworkSave(classement->premier, fileoutname);

    ImagesDestroy(&bank_images);
    
    free(filename);

}

void MutateGeneration(Classement * classement, Images * bank_images)
{

    for (unsigned index_individu = 0; index_individu < NB_PAR_GENERATION; index_individu++)
    {
        
        Network * network = NetworkMutate(classement->premier, 0.001);

        unsigned network_score = NetworkEvaluate(bank_images, network);

        ClassementUpdate(classement, &network, network_score);
    }
    
}


void RandomGeneration(Classement * classement, Images * bank_images)
{
    printf("Début de Génération randome\n");
    unsigned nb_valeur = TAILLE_IMAGE_X * TAILLE_IMAGE_Y * 3;
    
    for (unsigned index_individu = 0; index_individu < NB_PAR_GENERATION; index_individu++)
    {
        printf("individu numero : %d\n", index_individu);
        Network * network = NetworkInitRandom(COUCHE_NEURONAL, nb_valeur);
        printf("Initialisation de l'individu \n");
        unsigned network_score = NetworkEvaluate(bank_images, network);
        printf("Evaluation de l'individu \n");
        ClassementUpdate(classement, &network, network_score);
        printf("%d\n", index_individu / NB_PAR_GENERATION);
    }
    printf("Fin de Génération randome\n");
}


unsigned NetworkEvaluate(Images * bank_images, Network * network)
{
    unsigned score = 0;
    unsigned nombre_image = bank_images->taille;


    for (unsigned index_image = 0; index_image < nombre_image; index_image++)
    {
        Image * img = &(bank_images->image[index_image]);
            printf("%d\n", index_image);

        Input * data = InputMemcopy(img->input);

        char class = img->class;
        unsigned couche = network->couche;
        
        for (unsigned index_couche = 0; index_couche < couche; index_couche++)
        {
            MatrixExecuteNew(data, network->neurone[index_couche]);
        }
        if(class == InputDetermineClasse(data))
        {
            score++;
        }
        InputDestroy(&data);
    }
    return score;
}