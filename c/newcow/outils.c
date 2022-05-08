#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "outils.h"

void update() { printf("\033[H\033[J"); }
void gotoxy(unsigned char x, unsigned char y) { printf("\033[%d;%dH", y, x); }
char rand_char(char bi, char bs) {
    static char seme = 0;
    if (!seme) {
        srandom(getpid());
        seme = 1;
    }

    return bi + (rand() % (bs-bi)); //bs-bi c'est l'écart entre les deux borne donc bi + bs - bi = bs donc tout va bien et ça marche
}


void reset_str(char *chaine) {
    for (unsigned int i = 0;i < 597; i++) {
        chaine[i] = '\0'; // Bon ça ne la vide pas réellement parce que c'est pas possible mais c'est ce que je veux faire donc je suis content
    }
}


/* Cette façon de faire la fonction pose problème avec les caractères tels que ç ou à car ils comptent comme deux caractères. Je n'ai pas pris le temps de
   chercher une façon de palier à ce problème... */
unsigned char max_char_par_ligne(char *chaine) {
    unsigned char max = 0;
    unsigned char nombre = 0;
    unsigned int i = 0;
    while (chaine[i] != '\0') {
        if (chaine[i] == '\n') {
            nombre = 0;
        }
        else {
            if (++nombre > max) max = nombre;
        }
        i++;
    }
    return max;
}