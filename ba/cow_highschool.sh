#!/bin/bash

# Vérification des arguments
if [ $# -ne 1 ]; then
    echo $0 " : Nombre d'arguments incorrects, 1 attendu," $# "donnés"
    exit 1
fi

# Programme principal
for ((i=1; i<=$1; i++)); do
    ./.cs.sh $(expr $i \* $i)
done

./.fin.sh