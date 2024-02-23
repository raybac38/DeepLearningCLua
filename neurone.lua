--[[Fonction : CreateNeurone
    Description : Permet de crée un neurone de manière aléatoire]]
function CreateNeurone(nombre_couche, taille_matrice)
    local neurone = {}
    neurone["profondeur"] = nombre_couche;

    for layer = 1, nombre_couche do
        neurone[layer] = MatriceCreateRandom(taille_matrice, taille_matrice)
    end
    return neurone
end


-- Fonction determine_classe
-- Cette fonction prend en entrée un tableau d'entrée (input) contenant les scores pour chaque classe et détermine la classe la plus probable.
-- Elle parcourt chaque élément du tableau et compare sa valeur à la valeur maximale actuelle.
-- Si la valeur de l'élément est supérieure à la valeur maximale actuelle, elle met à jour la valeur maximale et enregistre l'indice de la classe correspondante.
-- À la fin de la boucle, si aucune valeur maximale n'a été trouvée (valeur == 0), elle retourne -1 pour indiquer qu'aucune classe n'a été déterminée.
-- Sinon, elle retourne l'indice de la classe la plus probable.

local function determine_classe(input)
    local class = 0
    local valeur = 0

    for i = 1, 10, 1 do
        if input[i] > valeur then
            valeur = input[valeur]
            class = i
        end
    end
    
    if valeur == 0 then
        class = -1
    end

    return class
end

-- Fonction ExecuteNeurone
-- Cette fonction prend en entrée un neurone et un input, et effectue la propagation avant à travers le réseau de neurones représenté par le neurone donné.
-- Elle parcourt chaque couche du réseau en appliquant la fonction d'activation et les poids associés à chaque neurone.
-- À la fin du processus de propagation avant, elle détermine la classe la plus probable en utilisant la fonction determine_classe et retourne cette classe.

function ExecuteNeurone(neurone, input)
    for i = 1, neurone.profondeur do
        input = MatriceOperation(input, neurone[i])
    end
    -- retourne la classe la plus probable (regarder ligne 1 a 10 )
    return determine_classe(input)
end
