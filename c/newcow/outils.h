#ifndef ESC_SEQUENCES_H
#define ESC_SEQUENCES_H

/**
 * @brief efface l'écran
 */
void update();

/** 
 * @brief Bouge le curseur à la position donnée
 * @param x
 * @param y
 */
void gotoxy(unsigned char x, unsigned char y);

/**
 * @brief Renvoie un char aléatoire c tel que BI <= c <= BS
 * @param bi Borne inférieure
 * @param bs Borne supérieure
 * @return c | BI <= c <= BS 
 */
char rand_char(char bi, char bs);

/**
 * @brief Vide la chaîne de caractères de retour pour pouvoir la reremplire après-coup
 * @param chaine la chaine de caractère à vider
 */
void reset_str(char* chaine);

/**
 * @brief Renvoie le nombre maximum de caractères par lignes d'une chaine de caractères
 * @param chaine La chaine a analyser
 * @return Le nombre maximum de caractères par lignes de chaine
 */
unsigned char max_char_par_ligne(char *chaine);

#endif