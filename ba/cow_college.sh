# Vérification du nombre arguments
if [ $# -ne 1 ]; then
    echo $0 " : Nombre d'argument incorrect, 1 attendu" $# "reçus"
    exit 1
fi

# Vérification de la validité de l'argument
if [ $1 -lt 0 ]; then
    echo $0 " : Argument invalide, l'entier est censé être >= 0 pour des raisons évidentes"
    exit 2
fi


# Programme principal
# a et b sont les deux valeurs qu'on ajoute ensemble pour trouver la suite de fibonacci
a=1
b=1

while [ $a -le $1 ]; do
    ./.cs.sh $a
    a=$(expr $a + $b)
    t=$b; b=$a; a=$t # a et b s'inversent à la fin pour toujours garder b > a et afficher la bonne partie de la suite à chaque fois
done

./.fin.sh