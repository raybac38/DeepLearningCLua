
print("- - - Initialisation de la scéance de DeepLearning - - - \n");


IMAGE_PAR_BATCH = 10000 --nombre d'image que contien un fichier d'image
TAILLE_IMAGE_X = 32     --nombre de pixel X de l'image
TAILLE_IMAGE_Y = 32     --nombre de pixel Y de l'image
COLOR_SIZE = 1          --nombre de byte nessessaire par couleur d'un pixel

NB_VALEUR = TAILLE_IMAGE_X * TAILLE_IMAGE_Y * COLOR_SIZE * 3

local NOMBRE_COUCHE = 5
local NOMBRE_GENERATION = 200
local NOMBRE_EVOLUTION = 30

FILE_NAME = "/media/raybac38/HDD/cifar-10-binary/cifar-10-batches-bin"


local function evaluation_generation_mutant(images)

    local premier = nil
    local score_premier = 0
    local second = nil
    local score_second = 0
    local troisieme = nil
    local score_troisieme = 0


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

        if score > score_premier then
            score_premier = score
            premier = individu
        elseif score > score_second then
            score_second = score
            second = individu
        elseif score > score_troisieme then
            score_troisieme = score
            troisieme = individu
        end
    end
    return premier, second, troisieme
end

local function evaluation_premiere_generation(images)

    local premier = nil
    local score_premier = 0
    local second = nil
    local score_second = 0
    local troisieme = nil
    local score_troisieme = 0


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

        if score > score_premier then
            score_premier = score
            premier = individu
        elseif score > score_second then
            score_second = score
            second = individu
        elseif score > score_troisieme then
            score_troisieme = score
            troisieme = individu
        end
    end
    return premier, second, troisieme
end


function Main()
    
    local images = GetImages(FILE_NAME)

    local premier_neurone = {}
    local second_neurone = {}
    local troisieme_neurone = {}

    evaluation_premiere_generation(images)

    for generation = 1, NOMBRE_GENERATION do
        
    end








end