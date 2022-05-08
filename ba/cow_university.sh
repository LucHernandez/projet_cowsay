# Vérification du nombre d'arguments
if [ $# -ne 1 ]; then
    echo $0 " : Nombre d'argument incorrect, 1 attendu" $# "reçus"
    exit 1
fi

# Vérification de la validité de l'argument
if [ $1 -lt 0 ]; then
    echo $0 " : Argument invalide, l'entier est censé être >= 0 pour des raisons évidentes"
    exit 1
elif [ $1 -lt 2 ]; then
    exit 0
fi


function is_prime { # int -> bool. 0 si l'entier est premier, 1 sinon.

    # On gère le cas ou on vérifie 2 car il nous permet de parcourir les entiers 2 fois plus vite
    if [ $[$1%2] -eq 0 ]; then
        return 1
    fi

    # Algo principal
    div=3
    while [ $(expr $div \* $div) -le $1 ]; do # On met div au carré plutôt que de faire une racine carrée
        if [ $[$1%$div] -eq 0 ]; then
            return 1
        fi
        div=$(expr $div + 2)
    done
    return 0
}


# Programme principal

# On traite le cas de 2 pour les mêmes raisons que ci-dessus
i=2

./.cs.sh $i

# On parcours les entiers de 3 à notre limite

i=3

for ((i=3; i<=$1; i+=2)); do
    is_prime $i
    if [ $? -eq 0 ]; then
        ./.cs.sh $i
    fi
done

./.fin.sh