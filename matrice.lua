function MatriceCreateLigneNull(nbligne)
    local ligne = {}
    ligne["taille"] = nbligne;
    ligne["type"] = "Ligne"
    for i = 1, nbligne
    do
        ligne[i] = 0
    end
    return ligne
end

-- Crée une matrice null--
function MatriceCreateNull(nbligne, nbcolone)
    local matrice = {}
    matrice["taille"] = { nbcolone = nbcolone, nbligne = nbligne }
    matrice["type"] = "Matrice"
    for i = 1, nbligne
    do
        matrice[i] = {}
        for j = 1, nbcolone
        do
            matrice[i][j] = 0;
        end
    end
    return matrice
end

-- Crée une matrice randome --
function MatriceCreateRandom(nbligne, nbcolone)
    local matrice = {}
    matrice["taille"] = { nbcolone = nbcolone, nbligne = nbligne }
    matrice["type"] = "Matrice"
    for i = 1, nbligne
    do
        matrice[i] = {}
        for j = 1, nbcolone
        do
            matrice[i][j] = math.random();
        end
    end
    return matrice
end

--[[
    Fonction : Matrice Mutation
    Description : mute les valeurs de la matrice via un delta mutationpower
    Parametre :
        matrice : la matrice a muter
        mutationPower : le delta pour lequelles les valeurs seront possiblement décalé
    Retour : la matrice mutée
--]]

function MatriceMutation(matrice, mutationPower)
    local nbcolone = matrice.taille.nbcolone
    local nbligne = matrice.taille.nbligne

    for i = 1, nbligne
    do
        for j = 1, nbcolone
        do
            local valeur = math.random(-mutationPower, mutationPower) + matrice[i][j];
            if valeur > 1 then
                valeur = 1
            elseif valeur < 0 then
                valeur = 0
            end
            matrice[i][j] = valeur
        end
    end
    return matrice
end

function MatriceOperation(ligneInput, matrice)
    local nbligne = ligneInput.taille;
    local nbIteration = nbligne

    local max = 0

    local ligneOutput = MatriceCreateLigneNull(nbligne)
    for i = 1, nbligne do
        local valeur = 0

        for k = 1, nbIteration do
            valeur = valeur + (ligneInput[k] * matrice[k][i]);
        end

        if valeur > max then
            max = valeur
        end
        ligneOutput[i] = valeur
    end

    --Normalization des valeurs

    if max == 0 then
        return ligneOutput
    end

    for i = 1, nbligne do
        ligneOutput[i] = ligneOutput[i] / max
    end

    return ligneOutput
end
