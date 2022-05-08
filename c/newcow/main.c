#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "newcow.h" // La gestion de newcow
#include "tamacowshi.h" // Ce qui concerne le tamacowshi
#include "outils.h" // Toutes les commandes générales qui ne sont pas utilisées à des fins précis
#include "main.h" // C'est quand même mieux de voir main dès le début

int main(int argc, char **argv) {
    cow_parameters param;
    init_cow_param(&param);

    if (read_parameters(argc, argv, &param) != 0) return 1;

    update();
    if (argc == 1) {
        printf("SYNOPSIS : [--tamacoshi] [-e eye_string] [-T tongue_string] [-bdgpstwy] [--borgor burger_string] [--anim anim_length] [--file [filename]]\n");
        param.queueY++;
        param.finY++;
    }
    affiche_vache(&param);

    while (animation(param.limitanim, &param) != 0); // <=> anime tant qu'il y a quelque chose à animer
    
    if (param.fichier != NULL) param.finY++;
    gotoxy(0, param.finY+6);

    close_param(&param);
    return 0;
}

char animation(int limite, cow_parameters *param) {
    char tourne = 0; // Valeur déterminant si l'animation continue ou non
    if (param->fichier != NULL && !feof(param->fichier)){
        update_text(param);
        tourne++;
    }

    static char i = 0;
    update_queue(i, param);
    if (i < limite) {
        i++;
        tourne++;
    }
    
    fflush(stdout);
    usleep(100000);
    return tourne;
}

char read_parameters(int argc, char **argv, cow_parameters *param) {
    for (unsigned char i = 1; i < argc; i++) {
        
        // Ci-joint un usage abusif de strcmp. Il y a surement moyen de chercher l'index de argv[i] dans un liste prédéfinie et de faire un switch
        // Je verrai
        if (argc == 2 && strcmp(argv[i], "--tamacowshi") == 0) { // Permet d'empêcher le cas fatidique où l'utilisateur veut mélanger le tamacowshi et les autres fonctionnalités de newcow
            param->tamacowshi_enabled = 1;
            new_tamacowshi(param->tamacow);
        }
        else if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0) {
            i++;
            set_eyes(argv[i], param);
        }
        else if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--tongue") == 0) {
            i++;
            set_tongue(argv[i], param);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            set_eyes("==", param);
        }
        else if (strcmp(argv[i], "-d") == 0) {
            set_eyes("xx", param);
            set_tongue("U", param);
        }
        else if (strcmp(argv[i], "-g") == 0) {
            set_eyes("$$", param);
        }
        else if (strcmp(argv[i], "-p") == 0) {
            set_eyes("@@", param);
        }
        else if (strcmp(argv[i], "-s") == 0) {
            set_eyes("**", param);
            set_tongue("U", param);
        }
        else if (strcmp(argv[i], "-t") == 0) {
            set_eyes("__", param);
        }
        else if (strcmp(argv[i], "-w") == 0) {
            set_eyes("OO", param);
        }
        else if (strcmp(argv[i], "-y") == 0) {
            set_eyes("..", param);
        }
        else if (strcmp(argv[i], "--borgor") == 0) {
            if (i == argc - 1) return 1; // Vérifie que je peux faire le ++i d'après (bonjour la segmentation fault)
            char valide = set_borgor(argv[++i], param); // C'est beau ce ++i, j'aime bien
            if (valide == 1) {
                printf("Les seuls valeurs autorisées pour le paramètre borgor sont:\n: p (pour le pain)\n: s (pour la salade)\n: c (pour la vache, 1 seul autorisé)\n: t (pour la tomate)\nSi vous n'entrez pas des arguments valides, le programme ne s'exécutera pas.\n");
                return 1;
            }
            else if (valide == 2) {
                printf("Le nombre d'ingrédients de votre borgor doit être d'au maximum 7 et au minimum 1 (vache incluse), il s'agirait de ne pas avoir les yeux plus grand que votre écran...\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "--anim") == 0) {
            if (i == argc - 1) return 1;
            if (set_limitanim(argv[++i], param) != 0) {
                printf("Vous êtes censé mettre un entier entre 1 et 9 (inclus) comme argument du paramètre \n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "--cat") == 0) {
            if (i == argc - 1) return 1;
            if (set_catfile(argv[++i], param) != 0) return 1;
            param->finY+=2;
            param->queueY+=2;
        }
        else if (strcmp(argv[i], "-h") == 0 && argc == 2) {
            printf("SYNOPSIS : [-h] [--tamacoshi] [-e eye_string] [-T tongue_string] [-bdgpstwy] [--borgor burger_string] [--anim anim_length] [--cat ["", filename]]\n");
            return 1;
        }
        else {
            printf("%s : argument invalide\nSYNOPSIS : [--tamacoshi] [-e eye_string] [-T tongue_string] [-bdgpstwy] [--borgor burger_string] [--anim anim_length] [--cat ["", filename]]", argv[i]);
            return 1;
        }
    }
    return 0;
}