

function GetImages(fileName)
    local file = io.open(fileName, 'rb')

    if file == nil then
        error("Unable to read file\n");
        return nil
    end

    local nbdata = NB_VALEUR
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
