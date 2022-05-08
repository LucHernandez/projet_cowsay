#ifndef MAIN_H
#define MAIN_H
#include "newcow.h"

/**
 * @brief Gère toute la partie animation de la vache
 * @param limite L'ajout à la taille de la queue pour l'animation
 * @param param Les paramètres de la vache
 * @return 0 Si l'animtaion est terminée
 */
char animation(int limite, cow_parameters *param);

/**
 * @brief stocke tout les paramètres donnés en arguments de la commande dans les paramètres de la vache
 * @param argc Le nombre d'arguments (./newcow inclus)
 * @param argv Un tableau des valeurs de tout les arguments
 * @param param Les paramètres de la vache
 * @return 0 Si tout s'est bien passé
 */
char read_parameters(int argc, char **argv, cow_parameters *param);

/**
 * @brief Fonction principale du programme
 * @param argc Le nombre d'arguments (./newcow inclus)
 * @param argv Un tableau des valeurs de tout les arguments
 * @return 0 si tout s'est bien passé
 */
int main(int argc, char **argv);

#endif