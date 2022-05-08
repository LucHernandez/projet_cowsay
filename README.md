<body bgcolor = "#0", style="color : #ffffff">

Dans l'optique de vous faire passer un moment plus agréable, tout est disponible sur github à l'adresse METTRE L'ADRESSE ICI.
(le compte rendu est dans le README et tout les codes commentés sont dispo).

# Compte rendu projet INF203
# Préliminaires
|Option|Usage|Exemple|
|---|---|---|
|-e|Permet de définir à quoi ressemblent les yeux de la vache|`cowsay -e 00 foo` affiche une vache avec "00" comme yeux qui dit "foo"|
|-f|Permet d'afficher une vache customizée à l'aide d'un fichier cowfile|`cowsay -f /usr/share/cowsay/cows/vader.cow foo` affiche une vache dark fadoc qui dit "foo"|
|-h|Affiche une pour connaître la syntaxe des arguments de cowsay||
|-l|Affiche la liste et la localisation des fichiers cowfile par défaut||
|-n|Désactive la justification du texte par mots||
|-T|Permet de définir à quoi ressemblent la langue de la vache|`cowsay -T "U " foo` affiche une vache qui tire la langue et qui dit "foo"|
|-W|Permet de préciser à combien de colones on veut justifier le texte|`cowsay -W 2 foo` affiche une vache qui dit foo (en verticale)|
|-bdgpstwy|Certaines modifications cosmétiques par défaut de la vache|`cowsay -d aled` affiche une vache morte qui dit "aled"|

# Bash
&emsp; J'utilise ./.cs.sh et ./.fin.sh pour me faciliter la tâche dans tout les scripts
### ./.cs.sh
```bash
if [ $# -eq 0 ]; then
    echo $0 : Au moins 1 argument attendu
    exit 1
fi
clear
cowsay $*
sleep 1
```
### ./.fin.sh
```bash
clear
cowsay -T U "fin"
```
## cow_kindergarten
&emsp; Pour ce script, on fait simplement une boucle qui va de 1 à 10 en affichant la vache à chaque fois.
```bash
#!/bin/bash

for num in {1..10}
do
    ./.cs.sh $num
done

./.fin.sh
```

## cow_primaryschool
&emsp; Ici, je décide d'uiliser une boucle for comme en C, je préfère cette façon de faire et je la trouve plus efficace.
```bash
# Vérification des arguments
if [ $# -ne 1 ]
then
    echo $0 " : Nombre d'arguments incorrects, 1 attendu," $# "donnés"
    exit 1
fi

# Programme principal
for ((i=1; i<=$1; i++)); do
    ./.cs.sh $i
done

./.fin.sh
```

## cow_highschool
&emsp; Rien à dire, j'uilise expr mais rien de neuf
```bash
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
```

## cow_college
&emsp; Toujours rien à dire.
```bash
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
```

## cow_university
&emsp; Ici j'utilise une fonction parce que c'est quand même **VACHE**ment plus pratique. On va de deux en deux parce que ça va deux fois plus vite et du coup je préfère.
```bash
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
```

## smart_cow
&emsp; Ici j'ai décidé d'utiliser [] pour effectuer le calcul donné par l'uilisateur car c'est une fonctionnalité de bash et je trouve ça dommage de ne pas l'utiliser.
```bash
# Vérification du nombre d arguments
if [ $# -ne 1 ]; then
    echo $0 ": Nombre d'argument incorrect, 1 attendu $# reçus"
    exit 1
fi

cowsay -e $[$1] $1
```

## crazy_cow
&emsp; Je me suis vraiment trouvé face au mur quand il s'est agit de chercher une bonne idée pour la crazy_cow. Du coup j'ai décidé de refaire un classique. J'ai refait le jeu de la vie de Conway en bash.
&emsp; Pour être sûr qu'elle soit crazy mais prévisible, j'ai mis 69 ligne de vérification des arguments et de messages d'erreurs pour l'utilisateur. J'ai aussi créé mon propre format de fichier pour que tout soit bien contrôlé.  

&emsp; Le principe, c'est que tout se passe dans /tmp/conway. Chaque état du jeu de la vie est stocké dans un fichier et l'utilisateur peut retracer tout les états qui ont suivis sa configuration initiale.  

&emsp; J'ai donc mis en place une fonction pour calculer l'état suivant et une fonction pour mettre en place le programme au début.  
Le principe du script est qu'il tourne tant qu'il n'est pas déjà passé par son état courant (ça arrive forcément).  
Le programme n'est pas très bien optimisé. Il est même très lent. C'est pourquoi je vous recommande de ne pas aller plus loin qu'une taille de 10*10 si vous tenez à passer un bon moment.
```bash
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
    for i in $(seq 1 $H); do
        for j in $(seq 1 $W); do
            echo -n .
            originalValue=$(cat $1 | head -n $i | tail -n -1 | head -c $j | tail -c -1)
            voisinCount=$(expr 0 - $originalValue)
            max 1 $(expr $i - 1)
            max1=$?
            min $H $(expr $i + 1)
            min1=$?
            for v in $(seq $max1 $min1); do
                max 1 $(expr $j - 1)
                max2=$?
                min $W $(expr $j + 1)
                min2=$?
                for h in $(seq $max2 $min2); do
                    voisinCount=$(expr $voisinCount + $(cat $1 | head -n $v | tail -n -1 | head -c $h | tail -c -1))
                done
            done
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
padejatrouve=0
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
```

# C
## Important
&emsp;Si vous lisez mon code dans vscode, j'ai rajouté de la documentation pour toutes les fonctions que j'ai fait dans les headers. Passez votre souris un petit moment dessus et vous aurez un résumé. J'ai fait comme cela pour m'éviter d'avoir à mettre des commentaires de partout dans mes fichiers sources.
## Ajout des fonctionnalités de newcow
&emsp; Dans cette situation, j'ai décidé de stocker les choses qui sont gérées par les options dans un type paramètres que je fais passer par adresse à chaques fois que je veux les utiliser. Pour ce qui est de vérifier les arguments, j'utilise strcmp qui fait bien son boulot et je m'adapte en fonction des arguments qui me sont donnés. J'ai fais **le choix** de ne pas renvoyer de message d'erreur quand l'option n'est pas définie. Au lieu de printf plusieurs fois, je concatène tout ensemble puis j'affiche le résultat final. Je me rend compte de la limite de cette méthode dans la partie suivante.
### main.c
```c
#include <string.h>
#include <stdio.h>
#include "newcow.h"

int main(int argc, char **argv) {
    cow_parameters param;
    init_cow_param(&param);
    for (unsigned char i = 1; i < argc; i++){
        if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0){
            i++;
            set_eyes(argv[i], &param);
        }
        else if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tongue") == 0) {
            i++;
            set_tongue(argv[i], &param);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            set_eyes("==", &param);
        }
        else if (strcmp(argv[i], "-d") == 0) {
            set_eyes("xx", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-g") == 0) {
            set_eyes("$$", &param);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            set_eyes("@@", &param);
        }
        else if (strcmp(argv[i], "-s") == 0) {
            set_eyes("**", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-t") == 0) {
            set_eyes("__", &param);
        }
        else if (strcmp(argv[i], "-w") == 0) {
            set_eyes("OO", &param);
        }
        else if (strcmp(argv[i], "-y") == 0) {
            set_eyes("..", &param);
        }
    }
    affiche_vache(&param);
    return 0;
}
```

### newcow.h
```c
#ifndef NEWCOW_H
#define NEWCOW_H

/**
 * @brief Paramètres contenant les infos de la vache à afficher
 * @param yeux Chaîne de caractères contenant les yeux de la vache
 * @param langue Chaîne de caractères contenant la langue de la vache
 * @param burger Chaîne de caractère contenant la composition de votre **magnifique burger personnalisé**
 */
typedef struct {
  char yeux[3];
  char langue[3];
} cow_parameters;

/**
 * @brief Fonction affichant une vache correspondant aux paramètres donnés
 * 
 * @param param
 */
void affiche_vache(cow_parameters *param);

// Section dédiée à la mise en place des paramètres de la vache
/**
 * @brief Initialise les paramètres pour avoir la vache par défaut
 * 
 * @param param 
 */
void init_cow_param(cow_parameters *param);

/**
 * @brief Function qu'on appelle pour paramétrer les différentes parties des paramètres
 * 
 * @param value La valeur du paramètre
 * @param length La longeur requise de la valeur à donner
 * @param default_value La valeur par défaut si la valeur n'est pas assez grande
 * @param destination Le paramètre visé par la fonction
 */
void set_param(char *value, int length, char *default_value, char *destination);

/**
 * @brief Applique un style d'yeux dans les paramètres
 * 
 * @param value Le style d'yeux à appliquer
 * @param param Les paramètres auxquels appliquer les yeux
 */
void set_eyes(char *value, cow_parameters *param);

/**
 * @brief Applique un style de langue dans les paramètres
 * 
 * @param value Le style à appliquer
 * @param param Les paramètres auxquels appliquer le style de langue
 */
void set_tongue(char *value, cow_parameters *param);

/**
 * @brief Applique les paramètres choisis à la string qu'on va afficher plus tard
 * 
 * @param param Les paramètres à appliquer à la vache
 * @param s La chaîne de caractères qui va contenir la vache
 */
void build_cow(cow_parameters *param, char *s);

#endif
```

### newcow.c
```c
#include <stdio.h>
#include <string.h>
#include "newcow.h"

void affiche_vache(cow_parameters *param){
  char outputstr[123] = ""; // 123 étant la taille de la vache
  build_cow(param, outputstr);
  printf("%s", outputstr);
}

inline void init_cow_param(cow_parameters *param) {
  strcpy(param->yeux, "oo\0");
  strcpy(param->langue, "  \0");
  set_borgor("c", param);
}

void set_param(char *value, int length, char *default_value, char *destination) {
  unsigned char value_length = strlen(value);
  char truev[length];
  strcpy(truev, default_value);

  if (value_length <= length) {
    length = value_length;
  }
  for(;length > 0; length--) {
    truev[length-1] = value[length-1];
  }

  strcpy(destination, truev);
}

inline void set_eyes(char *value, cow_parameters *param) {
  set_param(value, 2, "oo", param->yeux);
}

inline void set_tongue(char *value, cow_parameters *param) {
  set_param(value, 2, "  ", param->langue);
}

void build_cow(cow_parameters *param, char *s) {
  strcat(s, "        \\   ^__^\n         \\  (");
  strcat(s, param->yeux); // Ajout des yeux
  strcat(s, ")\\_______\n            (__)\\       )\\/\\\n             ");
  strcat(s, param->langue); // Ajout de la langue
  strcat(s, " ||----w |\n                ||     ||\n");
}
```

## Burger ?
&emsp; Suite à un repas à Burger King, j'ai eu l'idée de rajouter cette option à newcow.
L'idée c'est qu'on donne une chaine de caractères correspondant à la composition d'un burger et on rajoute ces éléments en fonction.  
C'est ici que j'ai vu que si on choisissait de mettre 35000 pains dans le burger, on risquait de devoir allouer beaucoup de mémoire pour notre chaine de caractères. J'ai donc mis une limite au nombre d'ingrédients et ai alloué une quantité suffisante de mémoire à ma chaine de caractères.  
Il y a juste le fait que le pain soit dans le bon sens avant et après la vache qui est notable, le reste est plutôt basique.
### main.c
```c
#include <string.h>
#include <stdio.h>
#include "newcow.h"

int main(int argc, char **argv) {
    cow_parameters param;
    init_cow_param(&param);
    for (unsigned char i = 1; i < argc; i++){
        if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0){
            i++;
            set_eyes(argv[i], &param);
        }
        else if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tongue") == 0) {
            i++;
            set_tongue(argv[i], &param);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            set_eyes("==", &param);
        }
        else if (strcmp(argv[i], "-d") == 0) {
            set_eyes("xx", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-g") == 0) {
            set_eyes("$$", &param);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            set_eyes("@@", &param);
        }
        else if (strcmp(argv[i], "-s") == 0) {
            set_eyes("**", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-t") == 0) {
            set_eyes("__", &param);
        }
        else if (strcmp(argv[i], "-w") == 0) {
            set_eyes("OO", &param);
        }
        else if (strcmp(argv[i], "-y") == 0) {
            set_eyes("..", &param);
        }
        else if (strcmp(argv[i], "--borgor") == 0) {
            i++;
            char valide = set_borgor(argv[i], &param);
            if (valide == 1) {
                printf("Les seuls valeurs autorisées pour le paramètre borgor sont:\n: p (pour le pain)\n: s (pour la salade)\n: c (pour la vache, 1 seul autorisé)\n: t (pour la tomate)\nSi vous n'entrez pas des arguments valides, le programme ne s'exécutera pas.\n");
                return 1;
            }
            else if (valide == 2) {
                printf("Le nombre d'ingrédients de votre borgor doit être d'au maximum 7 (vache incluse), il s'agirait de ne pas avoir les yeux plus grand que votre écran...\n");
                return 1;
            }
            
        }
    }
    affiche_vache(&param);
    return 0;
}
```

### newcow.h
```c
#ifndef NEWCOW_H
#define NEWCOW_H

/**
 * @brief Paramètres contenant les infos de la vache à afficher
 * @param yeux Chaîne de caractères contenant les yeux de la vache
 * @param langue Chaîne de caractères contenant la langue de la vache
 * @param burger Chaîne de caractère contenant la composition de votre **magnifique burger personnalisé**
 */
typedef struct {
  char yeux[3];
  char langue[3];
  char burger[8];
} cow_parameters;

/**
 * @brief Fonction affichant une vache correspondant aux paramètres donnés
 * 
 * @param param
 */
void affiche_vache(cow_parameters *param);

// Section dédiée à la mise en place des paramètres de la vache
/**
 * @brief Initialise les paramètres pour avoir la vache par défaut
 * 
 * @param param 
 */
void init_cow_param(cow_parameters *param);

/**
 * @brief Function qu'on appelle pour paramétrer les différentes parties des paramètres
 * 
 * @param value La valeur du paramètre
 * @param length La longeur requise de la valeur à donner
 * @param default_value La valeur par défaut si la valeur n'est pas assez grande
 * @param destination Le paramètre visé par la fonction
 */
void set_param(char *value, int length, char *default_value, char *destination);

/**
 * @brief Applique un style d'yeux dans les paramètres
 * 
 * @param value Le style d'yeux à appliquer
 * @param param Les paramètres auxquels appliquer les yeux
 */
void set_eyes(char *value, cow_parameters *param);

/**
 * @brief Applique un style de langue dans les paramètres
 * 
 * @param value Le style à appliquer
 * @param param Les paramètres auxquels appliquer le style de langue
 */
void set_tongue(char *value, cow_parameters *param);

/**
 * @brief Vérifie que la string donnée en argument de l'option borgor est correcte et la passe aux paramètres
 * 
 * @param couches Les paramètres de l'option
 * @param param Les paramètres auxquels passer l'option
 * @return 0 si tout s'est bien passé
 */
int set_borgor(char *couches, cow_parameters *param);

/**
 * @brief Applique les paramètres choisis à la string qu'on va afficher plus tard
 * 
 * @param param Les paramètres à appliquer à la vache
 * @param s La chaîne de caractères qui va contenir la vache
 */
void build_cow(cow_parameters *param, char *s);

/**
 * @brief Permet d'afficher la vache dans un **magnifique burger personnalisé**. A retrouver dès maintenant dans vos burger-king les plus proches
 * 
 * @param s La chaîne de caractère que vous afficherez à la fin
 * @param param Contient chaîne de caractères contenant votre **magnifique burger personnalisé**
 * @param top Décide de si on parle de la partie haute ou basse de votre **magnifique burger personnalisé**
 */
void apply_borgor(char *s, cow_parameters *param, char top);

#endif
```

### newcow.c
```c
#include <stdio.h>
#include <string.h>
#include "newcow.h"

void affiche_vache(cow_parameters *param){
  char outputstr[123+474] = ""; // 123 étant la taille de la vache "normale" et les 474 étant là pour le cas où on met plein de pain autour de la vache
  build_cow(param, outputstr);
  printf("%s", outputstr);
}

inline void init_cow_param(cow_parameters *param) {
  strcpy(param->yeux, "oo\0");
  strcpy(param->langue, "  \0");
  set_borgor("c", param);
}

void set_param(char *value, int length, char *default_value, char *destination) {
  unsigned char value_length = strlen(value);
  char truev[length];
  strcpy(truev, default_value);

  if (value_length <= length) {
    length = value_length;
  }
  for(;length > 0; length--) {
    truev[length-1] = value[length-1];
  }

  strcpy(destination, truev);
}

inline void set_eyes(char *value, cow_parameters *param) {
  set_param(value, 2, "oo", param->yeux);
}

inline void set_tongue(char *value, cow_parameters *param) {
  set_param(value, 2, "  ", param->langue);
}

int set_borgor(char *couches, cow_parameters *param) {
  int length = strlen(couches);

  if (length > 7) {
    return 2;
  }

  unsigned char c_counter = 0;

  for (int i = 0; i < length; i++) {
    char v = couches[i];
    if (v != 'p' && v != 't' && v != 's' && v != 'c') return 1;
    else if (v == 'c') {
      if (c_counter == 0) c_counter++;
      else return 1;
    }
  }
  if (c_counter != 1) return 1;
  strcpy(param->burger, couches);
  if (length > 1) {
    set_eyes("xx", param);
    set_tongue("U", param);
  }
  return 0;
}

void build_cow(cow_parameters *param, char *s) {
  apply_borgor(s, param, 0);
  strcat(s, "        \\   ^__^\n         \\  (");
  strcat(s, param->yeux); // Ajout des yeux
  strcat(s, ")\\_______\n            (__)\\       )\\/\\\n             ");
  strcat(s, param->langue); // Ajout de la langue
  strcat(s, " ||----w |\n                ||     ||\n");
  apply_borgor(s, param, 1);
}

void apply_borgor(char *s, cow_parameters *param, char top) {

  char limite = 'c';
  unsigned char debut = 0;
  if (top == 1) {
    for (;param->burger[debut] != 'c'; debut++);
    debut++;
    limite = '\0';
  }

  // Exemple type de la longueur de la vache pour la construction des ingrédients: "                ||     ||"

 /* Ok donc là c'est le moment où je réalise qu'il faut que je définisse ma string de base d'une taille énorme parce que quelqu'un peut potentiellement
 plein de pain dans son burger et déborder de la mémoire que j'ai alloué, ça va être horrible, j'aurai dû y penser plus tôt :/ */

 while (param->burger[debut] != limite) {
   switch(param->burger[debut]) {
    case 'p':
      if (top == 0) strcat(s, "   -------------------   \n /   .     .     .     \\ \n| .     .     .     .   |\n");
      else strcat(s, "| .     .     .     .   |\n \\   .     .     .     / \n   -------------------   \n");
      break;
    case 's':
      strcat(s, " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
      break;
    case 't':
      strcat(s, "ooooooooooTOMATEooooooooo\n");
      break;
    default: // Normalement on ne rencontre pas cette situation
      break;
   }
   debut++;
 }
}
```

## Animation :(
&emsp; On constate que `update()` sert à effacer l'écran tandis que `gotoxy(unsigned char x, unsigned char y)` permet d'aller à l'abscisse y et l'ordonnée x, ce qui ne me semble pas cohérent. Je me permet donc d'inverser les x et les y dans la fonction pour que le curseur se déplace bel et bien aux coodronées (x, y).  

Pour l'animation, j'ai décidé de partir sur quelque chose de plus classique. J'ai décidé de rajouter un paramètre qui permet de faire se rallonger la queue x fois (x étant compris entre 1 et 9). C'est plutôt simple, mais j'ai tout de même du rechercher la fonction fflush car tout s'affichait une fois que le programme était terminé, ce qui n'est pour le coup pas très pratique quand on essaie d'animer.
### main.c
```c
#include <string.h>
#include <stdio.h>
#include "newcow.h"
#include "escape_sequences.h"


int main(int argc, char **argv) {
    cow_parameters param;
    init_cow_param(&param);
    for (unsigned char i = 1; i < argc; i++){
        if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0){
            i++;
            set_eyes(argv[i], &param);
        }
        else if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tongue") == 0) {
            i++;
            set_tongue(argv[i], &param);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            set_eyes("==", &param);
        }
        else if (strcmp(argv[i], "-d") == 0) {
            set_eyes("xx", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-g") == 0) {
            set_eyes("$$", &param);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            set_eyes("@@", &param);
        }
        else if (strcmp(argv[i], "-s") == 0) {
            set_eyes("**", &param);
            set_tongue("U", &param);
        }
        else if (strcmp(argv[i], "-t") == 0) {
            set_eyes("__", &param);
        }
        else if (strcmp(argv[i], "-w") == 0) {
            set_eyes("OO", &param);
        }
        else if (strcmp(argv[i], "-y") == 0) {
            set_eyes("..", &param);
        }
        else if (strcmp(argv[i], "--borgor") == 0) {
            i++;
            char valide = set_borgor(argv[i], &param);
            if (valide == 1) {
                printf("Les seuls valeurs autorisées pour le paramètre borgor sont:\n: p (pour le pain)\n: s (pour la salade)\n: c (pour la vache, 1 seul autorisé)\n: t (pour la tomate)\nSi vous n'entrez pas des arguments valides, le programme ne s'exécutera pas.\n");
                return 1;
            }
            else if (valide == 2) {
                printf("Le nombre d'ingrédients de votre borgor doit être d'au maximum 7 (vache incluse), il s'agirait de ne pas avoir les yeux plus grand que votre écran...\n");
                return 1;
            }
            
        }
        else if (strcmp(argv[i], "--anim") == 0) {
            i++;
            if (set_limitanim(argv[i], &param) != 0) {
                printf("Vous êtes censé mettre un entier entre 1 et 9 (inclus) comme argument\n");
                return 1;
            }
        }
    }
    update();
    
    affiche_vache(&param);

    for (unsigned char i = 0; i < param.limitanim; i++) {
        update_queue(i, &param);
    }

    return 0;
}
```

### newcow.h
```c
#ifndef NEWCOW_H
#define NEWCOW_H

/**
 * @brief Paramètres contenant les infos de la vache à afficher
 * @param yeux Chaîne de caractères contenant les yeux de la vache
 * @param langue Chaîne de caractères contenant la langue de la vache
 * @param burger Chaîne de caractère contenant la composition de votre **magnifique burger personnalisé**
 */
typedef struct {
  char yeux[3];
  char langue[3];
  char burger[8];
  int queueY;
  int limitanim;
} cow_parameters;

/**
 * @brief Fonction affichant une vache correspondant aux paramètres donnés
 * 
 * @param param
 */
void affiche_vache(cow_parameters *param);

// Section dédiée à la mise en place des paramètres de la vache
/**
 * @brief Initialise les paramètres pour avoir la vache par défaut
 * 
 * @param param 
 */
void init_cow_param(cow_parameters *param);

/**
 * @brief Function qu'on appelle pour paramétrer les différentes parties des paramètres
 * 
 * @param value La valeur du paramètre
 * @param length La longeur requise de la valeur à donner
 * @param default_value La valeur par défaut si la valeur n'est pas assez grande
 * @param destination Le paramètre visé par la fonction
 */
void set_param(char *value, int length, char *default_value, char *destination);

/**
 * @brief Applique un style d'yeux dans les paramètres
 * 
 * @param value Le style d'yeux à appliquer
 * @param param Les paramètres auxquels appliquer les yeux
 */
void set_eyes(char *value, cow_parameters *param);

/**
 * @brief Applique un style de langue dans les paramètres
 * 
 * @param value Le style à appliquer
 * @param param Les paramètres auxquels appliquer le style de langue
 */
void set_tongue(char *value, cow_parameters *param);

/**
 * @brief Vérifie que la string donnée en argument de l'option borgor est correcte et la passe aux paramètres
 * 
 * @param couches Les paramètres de l'option
 * @param param Les paramètres auxquels passer l'option
 * @return 0 si tout s'est bien passé
 */
int set_borgor(char *couches, cow_parameters *param);

/**
 * @brief Applique les paramètres choisis à la string qu'on va afficher plus tard
 * 
 * @param param Les paramètres à appliquer à la vache
 * @param s La chaîne de caractères qui va contenir la vache
 */

/**
 * @brief Permet de préciser si la queue est décalée à cause du burger
 * 
 * @param y 
 * @param param 
 */
void set_queueY(int y, cow_parameters *param);

/**
 * @brief Permet de décider si on veut animer la vache et si oui combien de fois
 * 
 */
int set_limitanim(char *val, cow_parameters *param);

/**
 * @brief Concatene tout les éléments de la vache dans s pour ensuite l'afficher
 * 
 * @param param 
 * @param s 
 */
void build_cow(cow_parameters *param, char *s);

/**
 * @brief Permet d'afficher la vache dans un **magnifique burger personnalisé**. A retrouver dès maintenant dans vos burger-king les plus proches
 * 
 * @param s La chaîne de caractère que vous afficherez à la fin
 * @param param Contient chaîne de caractères contenant votre **magnifique burger personnalisé**
 * @param top Décide de si on parle de la partie haute ou basse de votre **magnifique burger personnalisé**
 */
void apply_borgor(char *s, cow_parameters *param, char top);

void update_queue(int i, cow_parameters *param);

#endif
```

### newcow.c
```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "newcow.h"
#include "escape_sequences.h"

void affiche_vache(cow_parameters *param){
  char outputstr[123+474] = ""; // 123 étant la taille de la vache "normale" et les 474 étant là pour le cas où on met plein de pain autour de la vache
  build_cow(param, outputstr);
  printf("%s", outputstr);
}

inline void init_cow_param(cow_parameters *param) {
  strcpy(param->yeux, "oo\0");
  strcpy(param->langue, "  \0");
  set_borgor("c", param);
  set_queueY(3, param);
  param->limitanim = 0;
}

void set_param(char *value, int length, char *default_value, char *destination) {
  unsigned char value_length = strlen(value);
  char truev[length];
  strcpy(truev, default_value);

  if (value_length <= length) {
    length = value_length;
  }
  for(;length > 0; length--) {
    truev[length-1] = value[length-1];
  }

  strcpy(destination, truev);
}

inline void set_eyes(char *value, cow_parameters *param) {
  set_param(value, 2, "oo", param->yeux);
}

inline void set_tongue(char *value, cow_parameters *param) {
  set_param(value, 2, "  ", param->langue);
}

int set_borgor(char *couches, cow_parameters *param) {
  int length = strlen(couches);

  if (length > 7) {
    return 2;
  }

  unsigned char c_counter = 0;

  for (int i = 0; i < length; i++) {
    char v = couches[i];
    if (v != 'p' && v != 't' && v != 's' && v != 'c') return 1;
    else if (v == 'c') {
      if (c_counter == 0) c_counter++;
      else return 1;
    }
  }
  if (c_counter != 1) return 1;
  strcpy(param->burger, couches);
  if (length > 1) {
    set_eyes("xx", param);
    set_tongue("U", param);
  }
  return 0;
}

void set_queueY(int y, cow_parameters *param) {
  param->queueY = y;
}

int set_limitanim(char *val, cow_parameters *param) {
  if (strlen(val) != 1) return 1;
  if (*val > '9' || *val < '1') return 2;
  param->limitanim = *val - '0';
  return 0;
}

void update_queue(int i, cow_parameters *param) {
  i += 3;
  gotoxy(26, param->queueY);
  while (i > 0) {
    if(i%2 == 0) printf("\\");
    else printf("/");
    i--;
  }
  fflush(stdout);
  sleep(1);
}

void build_cow(cow_parameters *param, char *s) {
  apply_borgor(s, param, 0);
  strcat(s, "        \\   ^__^\n         \\  (");
  strcat(s, param->yeux); // Ajout des yeux
  strcat(s, ")\\_______\n            (__)\\       )\\/\\\n             ");
  strcat(s, param->langue); // Ajout de la langue
  strcat(s, " ||----w |\n                ||     ||\n");
  apply_borgor(s, param, 1);
}

void apply_borgor(char *s, cow_parameters *param, char top) {

  char limite = 'c';
  unsigned char debut = 0;
  if (top == 1) {
    for (;param->burger[debut] != 'c'; debut++);
    debut++;
    limite = '\0';
  }

  // Exemple type de la longueur de la vache pour la construction des ingrédients: "                ||     ||"

 /* Ok donc là c'est le moment où je réalise qu'il faut que je définisse ma string de base d'une taille énorme parce que quelqu'un peut potentiellement
 plein de pain dans son burger et déborder de la mémoire que j'ai alloué, ça va être horrible, j'aurai dû y penser plus tôt :/ */

 while (param->burger[debut] != limite) {
   switch(param->burger[debut]) {
    case 'p':
      if (top == 0) {
        strcat(s, "   -------------------   \n /   .     .     .     \\ \n| .     .     .     .   |\n");
        set_queueY(param->queueY + 3, param);
      }
      else strcat(s, "| .     .     .     .   |\n \\   .     .     .     / \n   -------------------   \n");
      break;
    case 's':
      strcat(s, " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
      if (top == 0) set_queueY(param->queueY + 2, param);
      break;
    case 't':
      strcat(s, "ooooooooooTOMATEooooooooo\n");
      if (top == 0) set_queueY(param->queueY + 1, param);
      break;
    default: // Normalement on ne rencontre pas cette situation
      break;
   }
   debut++;
 }
}
```

## Remotivation
Après un long moment de vide, j'ai décidé de me remttre au projet et ai décidé de faire un léger changement. J'ai déplacé la lecture des arguments dans une fonction pour alléger mon fichier main.c. Rien d'impressionnant mais je trouve ça mieux.

## reading_cow
Etant donné que j'ai fait mon programme pour qu'il soit facilement modifiable afin d'ajouter des nouvelles fonctionnalitées, j'ai décidé de rajouter la fonctionnalité que vous nous proposez de créer directement dans newcow. Comme ça il n'y aura qu'un seul exécutable et il sera plus polyvalent que cowsay (il reste encore à savoir lire les cowfile mais je m'y atèlerais sûrement si j'ai le temps).  
Cependant, cette fois ci je ne ferai pas une concaténation mais afficherai plutôt d'abord le texte puis afficherai la vache. Je considère que les deux sont séparés.  
Etant donné que j'ai oublié de faire le compte rendu en même temps que je codais, je me suis retrouvé avec un projet terminé sans pouvoir donner mon code au moment t. J'ai donc décidé de vous donner les fonctions clés dans reading cow.  
J'ai déicdé de toujours réutiliser ma struct cow_parameters et de lui rajouter le composan  FILE *fichier` : le pointeur vers le fichier à lire.
Ainsi, il ne me restait plus qu'à l'initialiser sur un pointeur NULL puis à créer une fonction pour récupérer le bon fichier et une autre pou  le lire caractère par caractère:
### set_catfile
```c
int set_catfile(char *nom_fichier, cow_parameters *param) {
  FILE *fichier = fopen(nom_fichier, "r");
  if (fichier == NULL) return 1;
  param->fichier = fichier;
  for (int i=0; i<TAILLE_MAX_FICHIER; i++){ // Initialise le texte pour qu'il soit prêt à recevoir le fichier.
    param->text[i] = '\0';
  }
  param->queueY++;
  return 0; // renvoie 0 si le fichier à été trouvé
}
```

### update_text
&emsp; Ici l'objectif est de traiter tout les cas de lecture du fichier. En effet, on pourrait penser qu'il suffit de lire un caractère, mais non. Par exemple, si on lit un '\n', il est important de décaler tout ce qui est affiché par position pour notre programme d'un, sinon tout sera décalé.
```c
void update_text(cow_parameters *param) {
  static char tmp = '\0';
  static unsigned int i = 0;
  
  if (param->fichier == NULL) return; // On s'assure qu'on veut afficher quelque chose, ça n'arrivera jamais parce qu'on fait déjà le test avant mais ça paraît cohérent de le mettre là
  if (i >= TAILLE_MAX_FICHIER - 1){
    fclose(param->fichier);
    param->fichier = NULL;
    return;
  }
  else {
    if (tmp == '\n') {
      param->queueY++;
      param->finY++;
    }
    if (tmp != '\0') {
      param->text[i++] = tmp;
    }
    tmp = (char) fgetc(param->fichier); // Ici j'utilise fgetc parce que ça existe et que scanf m'a joué des mauvais tours.
    if (tmp != '\n') set_tongue(&tmp, param);
  }
```

### Modification de animation
En soit, afficher du texte c'est une façon d'animer la vache. J'ai donc décidé d'implementer la lecture et l'affichage du texte par la cache dans animation() :
```c
char animation(int limite, cow_parameters *param) {
    char tourne = 0; // Permet de renvoyer si l'animation a changé quelque chose ou pas
    // Partie texte
    if (param->fichier != NULL && !feof(param->fichier)){
        update_text(param);
        tourne++;
    }

    // Partie queue
    static char i = 0;
    update_queue(i, param);
    if (i < limite) {
        i++;
        tourne++;
    }
    
    fflush(stdout);
    sleep(1); // A décomenter si vous voulez aller loin dans le fichier, c'eest un peu long 1 seconde
    return tourne;
}
```
Pour que l'animation tourne tant qu'elle a quelque chose à faire, on utilise donc la fonction main suivante :
```c
int main(int argc, char **argv) {
    cow_parameters param;
    init_cow_param(&param);

    if (read_parameters(argc, argv, &param) != 0) return 1;

    update();
    affiche_vache(&param);

    while (animation(param.limitanim, &param) != 0); // <=> anime tant qu'il y a quelque chose à animer
    
    if (param.fichier != NULL) param.finY++;
    gotoxy(0, param.finY+6);

    close_param(&param);
    return 0;
}
```

# Tamacowshi
J'ai fait le choix de changer les intervalles dans lesquels peuvent se trouver digestion et crops pour rééquilibrer le tamacowshi car il me semblait injouable (mon âme de "***__G4M3RZ__***" comme dit le sujet).  
Pour tout ce qui est de l'aléatoire, la fonction que le sujet nous a fourni ne voulait pas fonctionner correctement sur mon pc, j'ai donc décidé d'utiliser le pid pour seed l'aléatoire (je vous assure que j'essaie de faire les choses bien) au début et fait une fonction qui prend un minimum et un maximum et qui renvoit un entier entre les deux.  
Ensuite j'ai créé ma struct tamacowshi qui a comme valeur la fitness et le stock de notre tamacowshi (oui je suis fier de ce jeu de mot) ainsi que deux fonction permettant de mettre à jour ces deux variables en fonction de la lunchfood qu'on choisi de donner à notre vache. Je me suis ensuite rendu compte que j'avais des problèmes de mémoire (struct dans une struct, je suppose que ça n'a pas aimé) donc j'ai décidé d'allouer dynamiquement de la place à ma struct dans le tas pour pouvoir passer le pointeur dans la struct de cow_param (je pense bien évidemment à free à la fin, je ne suis pas un monstre). J'ai ensuite créé une fonction pour initialiser le tamacowshi ainsi que la fonction me permettant de faire jouer un tour au joueur.  
Pour des raisons de manque de comptétence, je n'ai pas implémenté la possibilité de jouer au tamagoshi tout en utilisant les autres fonctionnalités de newcow. Cependant, après réflexion, c'est peut être mieux comme ça; on ne va pas mélanger le tetris de emacs avec un éditeur de texte... Vous trouverez ci-joint le code final, je pense que ça ne sert à rien que je le mette en compte-rendu étant donné que c'est littéralement la même chose.  
Au final, j'ai fait un repo sur github qui a le code ainsi que le Makefile pour compiler le projet. Comme ça je n'ai pas besoin de vous mettre le projet en texte dans un pdf et vous l'avez en ligne, bien organisé.
