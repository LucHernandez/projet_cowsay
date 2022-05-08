#!/bin/bash

if [ $# -lt 1 ]; then
    echo $0 : "Au moins 1 argument attendu ("$#" donnés). ./crazy_cow.sh -h pour l'aide"
    exit 1
fi

if [ $1 == "-h" ]; then
    echo "Le fichier crazy_cow est un fichier qui simule le jeu de la vie à partir d'un fichier .conway représentant une configuration initiale, d'une hauteur d'affichage telle que hauteur_fichier < hauteur affichage <= 30, et d'une largeur d'affichage telle que largeur_fichier < largeur_affichage <= 40"
    echo "La ligne commande type pour appeler crazy_cow.sh est : ./crazy_cow.sh mon_fichier.conway hauteur_affichage longueur_affichage"
    echo "Pour savoir comment bien construire un fichier .conway, taper la commande ./crazy_cow.sh -c"
    echo "Le programme s'arrête dès qu'il détecte un comportement en boucle"
    exit 0
fi

if [ $1 == "-tmpclean" ]; then
    rm -R /tmp/conway
    exit 0;
fi

if [ $1 == "-c" ]; then
    echo "Les fichiers .conway sont constitués de uniquement des 0 et des 1, les 1 représentant les cellules en vie et les 0 les cellules mortes."
    echo "Ils doivent avoir au moins 1 ligne et 1 colone et toujours le même nombre de valeurs par lignes"
    echo "Vous trouverez ci-dessous un exemple type de fichier .conway :
010
001
111"
exit 0
fi

if [ $# -ne 3 ]; then
    echo $0 : "3 arguments attendus ("$#" donnés). ./crazy_cow.sh -h pour l'aide"
    exit 1
fi

if [ ! -f $1 ]; then
    echo $0 : "L'argument donné n'est pas un fichier. ./crazy_cow.sh -h pour l'aide"
    exit 1
fi

if ! [ $3 -eq $3 -a $2 -eq $2 ] 2> /dev/null
then
    echo $0 : "La hauteur et la largeur doivent être des entiers. ./crazy_cow.sh -h pour l'aide"
    exit 1
fi

case $1 in
    *.conway);;
    *) echo $0 : "l'argument donné n'est pas un fichier .conway. ./crazy_cow.sh -h pour l'aide"; exit 1;;
esac

sourceH=$(cat $1 | wc -l)
sourceW=$(expr $(head -n 1 $1 | wc -m) - 1)

if [ $sourceH -ge $2 -o $sourceW -ge $3 ]; then
    echo $0 : "La hauteur et la largeur d'affichage doivent être strictement supérieurs à la hauteur et la largeur du fichier .conway. ./crazy_cow.sh -h pour l'aide"
    exit 1
fi
if [ $2 -gt 30 -o $3 -gt 40 ]; then
    echo $0 : "La hauteur (respectivement la largeur) d'affichage doit être inférieure à 30 (respectivement 40). ./crazy_cow.sh -h pour l'aide"
    exit 1
fi

for ((i=1; i<=sourceH; i++)); do
    if [ $(expr $(sed $i"q;d" $1 | wc -m) - 1) -ne $sourceW ]; then
        echo $0 : "Nombre de colones par lignes inconsistant dans le fichier" $1
        exit 1
    fi
done

# Declaration de la fonction constep qui simule une étape du jeu de la vie de conway entre deux fichiers, représentant respectivement le début et la fin

function max() {
    if [ $1 -gt $2 ]; then
	    return $1
    else
	    return $2
    fi    
}

function min() {
    if [ $1 -lt $2 ]; then
	    return $1
    else
	    return $2
    fi
}

function constep() {
    echo "pro-tip:    ./crasy_cow.sh -tmpclean pour nettoyer le dossier tmp des fichiers temporaires utilisés par crazy_cow"
    echo "pro-tip V2: Les points qu'on peut voir ci-dessous représentent l'avancement du scan de l'étape précdente"
    H=$(expr $(cat $1 | wc -l) + 1)
    W=$(expr $(head -n 1 $1 | wc -m) - 1)
    # On parcours toutes les cases du fichier
    for i in $(seq 1 $H); do
        for j in $(seq 1 $W); do
            echo -n .
            originalValue=$(cat $1 | head -n $i | tail -n -1 | head -c $j | tail -c -1)
            voisinCount=$(expr 0 - $originalValue)
            max 1 $(expr $i - 1)
            max1=$?
            min $H $(expr $i + 1)
            min1=$?
            # On compte le nombre de cases actives (1) autour de la case qu'on analyse pour déterminer son état suivant
            for v in $(seq $max1 $min1); do
                max 1 $(expr $j - 1)
                max2=$?
                min $W $(expr $j + 1)
                min2=$?
                for h in $(seq $max2 $min2); do
                    voisinCount=$(expr $voisinCount + $(cat $1 | head -n $v | tail -n -1 | head -c $h | tail -c -1))
                done
            done
            # On calcule l'état suivant de la case
            if [ $voisinCount -eq 3 ]; then
                echo -n 1 >> $2
            elif [ $voisinCount -eq 2 ]; then
                echo -n $originalValue >> $2
            else
                echo -n 0 >> $2
            fi
        done
        if [ $i -ne $H ]; then 
            echo >> $2
            echo 
        fi
    done
}

# Permet de mettre en place un fichier au format demandé par l'utilisateur qui sera le point de départ de la séquence
function setup() {
    sourceH=$(expr $(cat $1 | wc -l) + 1)
    sourceW=$(expr $(head -n 1 $1 | wc -m) - 1)
    H=$2
    W=$3

    # On calcule le nombre de lignes et de colonnes qu'on met autour
    vOffset1=$(expr $(expr $H - $sourceH) / 2)
    vOffset2=$(expr $H - $sourceH - $vOffset1)
    hOffset1=$(expr $(expr $W - $sourceW) / 2)
    hOffset2=$(expr $W - $sourceW - $hOffset1)


    # On créé l'état initial de notre jeu de la vie
    touch /tmp/conway/0.conway

    # On commence par ajouter les lignes vides au dessus
    for i in $(seq 1 $vOffset1); do
        for j in $(seq 1 $W); do
            echo -n 0 >> /tmp/conway/0.conway
        done
        echo >> /tmp/conway/0.conway
    done

    # Puis on fait de même avec les colones vides à gauche et à droite
    for i in $(seq 1 $sourceH); do
        for j in $(seq 1 $hOffset1); do
            echo -n 0 >> /tmp/conway/0.conway
        done
        echo -n $(cat a.conway | head -n $i | tail -n -1) >> /tmp/conway/0.conway # Ici on glisse le fichier passé en argument dedans
        for j in $(seq 1 $hOffset2); do
            echo -n 0 >> /tmp/conway/0.conway
        done
        echo >> /tmp/conway/0.conway
    done
    
    # Enfin, on ajoute les lignes vides en dessous
    for i in $(seq 1 $vOffset2); do
        for j in $(seq 1 $W); do
            echo -n 0 >> /tmp/conway/0.conway
        done
        if [ $i -ne $vOffset2 ]; then
            echo >> /tmp/conway/0.conway
        fi
    done
}

# On commence par réinitialiser le dossier dédié au script dans /tmp
if [ -d /tmp/conway ]; then
    rm -R /tmp/conway
fi
mkdir /tmp/conway

# Puis on créé un fichier initial correspondant à la configuration donnée
setup $1 $2 $3

# On lance ensuite la boucle qui va calculer les etapes unes à unes jusqu'à ce qu'il ne reste plus rien ou que le fichier boucle
clear
cowsay -W $(expr $3 + 1) $(cat /tmp/conway/0.conway)
constep /tmp/conway/0.conway /tmp/conway/1.conway
clear
cowsay -W $(expr $3 + 1) $(cat /tmp/conway/1.conway)
fich_num=2
padejatrouve=0 # J'espere que le nom est assez explicite
while [ $padejatrouve -eq 0 ]; do
    constep /tmp/conway/$(expr $fich_num - 1).conway /tmp/conway/$fich_num.conway
    clear
    cowsay -W $(expr $3 + 1) $(cat /tmp/conway/$fich_num.conway)
    for fichnum in $(seq 0 $(expr $fich_num - 1)); do
        difference=$(diff "/tmp/conway/$fich_num.conway" "/tmp/conway/$fichnum.conway")
        cmp -s /tmp/conway/$fich_num.conway /tmp/conway/$fichnum.conway
        if [ $? -eq 0 ]; then
            padejatrouve=$(expr $padejatrouve + 1)
        fi
    done
    fich_num=$(expr $fich_num + 1)
done