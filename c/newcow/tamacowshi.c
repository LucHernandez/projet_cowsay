#include <stdio.h>

#include "tamacowshi.h"
#include "outils.h"

void new_tamacowshi(tamacowshi *tama) {
    tama->fitness = 5;
    tama->stock = 5;
}

char lunchfood_valide(char lunchfood, tamacowshi *tama) {
    return (lunchfood <= tama->stock && lunchfood >= 0);
}

void stock_update(char lunchfood, tamacowshi *tama) {
    char crop = rand_char(1, 3);
    char stock = tama->stock+crop-lunchfood;

    // On vérifie que stock reste dans son intervalle
    if (stock < 0) tama->stock = 0;
    else if (stock > 10) tama->stock = 10;
    else tama->stock = stock;
}

void fitness_update(char lunchfood, tamacowshi *tama) {
    char digestion = rand_char(-2, 0);
    char fit = tama->fitness+digestion+lunchfood;

    // On vérifie que fitness reste dans son intervalle
    if (fit < 0) tama->fitness = 0;
    else if (fit > 10) tama->fitness = 10;
    else tama->fitness = fit;
}

char tamacowshi_step(tamacowshi *tama) {
    int lunchfood = -1; // Initialisation du lunchfood invalide

    while (!lunchfood_valide(lunchfood, tama)) {
        printf("Stock : %d\nEntrez une quantité de nourriture à donner à votre vache : ", tama->stock);
        scanf("%d", &lunchfood);
        if (!lunchfood_valide(lunchfood, tama)) printf("%d : valeur invalide\n", lunchfood);
    }

    // Mise à jour des paramètres du tamacowshi
    stock_update(lunchfood, tama);
    fitness_update(lunchfood, tama);

    return tama->fitness;
}