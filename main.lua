

print("- - - Initialisation de la scéance de DeepLearning - - - \n");

require("image")
require("matrice")
require("neurone")

IMAGE_PAR_BATCH = 10000 --nombre d'image que contien un fichier d'image
TAILLE_IMAGE_X = 32     --nombre de pixel X de l'image
TAILLE_IMAGE_Y = 32     --nombre de pixel Y de l'image
COLOR_SIZE = 1          --nombre de byte nessessaire par couleur d'un pixel

NB_VALEUR = TAILLE_IMAGE_X * TAILLE_IMAGE_Y * COLOR_SIZE * 3

local NOMBRE_COUCHE = 5
local NOMBRE_GENERATION = 200
local NOMBRE_EVOLUTION = 30

FILE_NAME = "/media/raybac38/HDD/cifar-10-binary/cifar-10-batches-bin/data_batch_1.bin"

local classement = {
    premier_neurone = nil,
    score_premier = 0,
    second_neurone = nil,
    score_second = 0,
    troisieme_neurone = nil,
    score_troisieme = 0,
}

local function evaluation_generation_mutant(images)

    for numero_individu = 1, NOMBRE_EVOLUTION do
        local individu = {}
        individu = CreateNeurone(NOMBRE_COUCHE, TAILLE_IMAGE_X)
        local score = 0;
        for index_image = 1, IMAGE_PAR_BATCH do
            local class = ExecuteNeurone(individu, images[index_image])

            if class == images[index_image].class
            then
                score = score + 1
            end
        end

        if score > classement.score_premier then
            classement.score_premier = score
            classement.premier_neurone = individu
        elseif score > classement.score_second then
            classement.score_second = score
            classement.second_neurone = individu
        elseif score > classement.score_troisieme then
            classement.score_troisieme = score
            classement.troisieme_neurone = individu
        end
    end
end

local function evaluation_premiere_generation(images)
    for numero_individu = 1, NOMBRE_EVOLUTION do
        local individu = {}
        individu = CreateNeurone(NOMBRE_COUCHE, NB_VALEUR)
        local score = 0;
        for index_image = 1, IMAGE_PAR_BATCH do
            local class = ExecuteNeurone(individu, images[index_image])

            if class == images[index_image].class
            then
                score = score + 1
            end
            print(index_image / IMAGE_PAR_BATCH)

        end

        if score > classement.score_premier then
            classement.score_premier = score
            classement.premier_neurone = individu
        elseif score > classement.score_second then
            classement.score_second = score
            classement.second_neurone = individu
        elseif score > classement.score_troisieme then
            classement.score_troisieme = score
            classement.troisieme_neurone = individu
        end

        print(numero_individu / NOMBRE_EVOLUTION)
    end
    return classement
end


function Main()

    print("- - - Lecture de l'image - - -\n")
    local images = GetImages(FILE_NAME)
    print("- - - Image lu - - -\n")

    local premier_neurone = {}
    local score_premier = 0
    local second_neurone = {}
    local score_second = 0
    local troisieme_neurone = {}
    local score_troisieme = 0

    evaluation_premiere_generation(images)


    print(classement.score_premier)
    print(classement.score_second)
    print(classement.score_troisieme)
end

Main()