# Vérification du nombre d arguments
if [ $# -ne 1 ]; then
    echo $0 ": Nombre d'argument incorrect, 1 attendu $# reçus"
    exit 1
fi

cowsay -e $[$1] $1