local IMAGE_PAR_BATCH = 10000 --nombre d'image que contien un fichier d'image
local TAILLE_IMAGE_X = 32     --nombre de pixel X de l'image
local TAILLE_IMAGE_Y = 32     --nombre de pixel Y de l'image
local COLOR_SIZE = 1          --nombre de byte nessessaire par couleur d'un pixel



function GetImages(fileName)
    local file = io.open(fileName, 'rb')

    if file == nil then
        error("Unable to read file\n");
        return nil
    end

    local nbdata = TAILLE_IMAGE_X * TAILLE_IMAGE_Y * COLOR_SIZE * 3
    local images = {}
    images["nbimage"] = IMAGE_PAR_BATCH


    for i = 1, IMAGE_PAR_BATCH do
        local image = {}
        image["classe"] = file:read(1)

        local ligne = MatriceCreateLigneNull(nbdata)

        for index = 1, nbdata do
            ligne[i] = file:read(1)
        end

        image["data"] = ligne
        images[i] = ligne
    end

    file:close()

    return images
end
