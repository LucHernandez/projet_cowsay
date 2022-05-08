#ifndef TAMACOWSHI_H
#define TAMACOWSHI_H

/**
 * @brief structure contenant les informations sur la tamacowshi
 * @param fitness La santé de la vache
 * @param stock Le stock de nourriture
 */
typedef struct {
    char fitness;
    char stock;
} tamacowshi;

/**
 * @brief Initialise le tamacowshi en début de partie
 * @param tama la struct contenant les infos du tamacowshi
 */
void new_tamacowshi(tamacowshi *tama);

/**
 * @brief Dit si la quantité de nourriture demandée est valide
 * @param lunchfood Quantité de nourriture demandée
 * @param tama Structure contenant les informations concernant la vache
 * @return lunchfood valide ou non
 */
char lunchfood_valide(char lunchfood, tamacowshi *tama);
/**
 * @brief Met à jour le stock en fonction de l'entrée de l'utilisateur ainsi que d'une variable aléatoire
 * @param lunchfood La quantité de nourriture extraite du stock pour la donner à la vache
 * @param tama La structure contenant les informations concernant la vache
 */
void stock_update(char lunchfood, tamacowshi *tama);

/**
 * @brief Met à jour la santé de la vache en fonction de l'entrée de l'utilisateur ainsi que d'une variable aléatoire
 * @param lunchfood La quantité de nourriture donnée à la vache
 * @param tama La structure contenant les informations concernant la vache
 */
void fitness_update(char lunchfood, tamacowshi *tama);

/**
 * @brief Lance une étape du tamacowshi
 * @param tama La structure contenant les information du tamacowshi
 * @return La fitness du tamacowshi après l'étape
 */
char tamacowshi_step(tamacowshi *tama);

#endif