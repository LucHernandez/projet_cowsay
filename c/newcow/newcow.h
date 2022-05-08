#ifndef NEWCOW_H
#define NEWCOW_H

#define TAILLE_MAX_FICHIER 4000

#include "tamacowshi.h"

/**
 * @brief Paramètres contenant les infos de la vache à afficher
 * @param text Chaîne de caractères contenant le texte que la vache doit dire
 * @param burger Chaîne de caractère contenant la composition de votre **magnifique burger personnalisé**
 * @param yeux Chaîne de caractères contenant les yeux de la vache
 * @param langue Chaîne de caractères contenant la langue de la vache
 * @param queueY La position Y de la queue. Ce paramètre est requis pour les situations où d'autres paramètres décalent la vache
 * @param finY La position Y du curseur une fois l'animation terminée
 * @param fichier Le fichier à faire lire à la vache
 * @param limitanim Le nombre de fois qu'on étend la taille de la queue
 * @param firsttime Permet de déterminer si c'est la permière fois qu'on dessine la vache où si on est dans le cas d'une animation. Utile pour ne pas trop décaler sa position Y
 * @param tamacowshi Pointeur vers le potentiel tamagoshi
 */
typedef struct {
  char text[TAILLE_MAX_FICHIER];
  char burger[8];
  char yeux[3];
  char langue[3];
  int queueY;
  unsigned int finY;
  FILE *fichier;
  tamacowshi *tamacow;
  char limitanim;
  char firsttime;
  char tamacowshi_enabled;
} cow_parameters;

/**
 * @brief Fonction affichant une vache correspondant aux paramètres donnés
 * @param param
 */
void affiche_vache(cow_parameters *param);

// Section dédiée à la mise en place des paramètres de la vache
/**
 * @brief Initialise les paramètres pour avoir la vache par défaut
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
 * @brief Met en place le fichier à lire par la vache
 * 
 * @param nom_fichier Le nom du fichier à lire
 * @param param Les paramètres où sera stocké le pointeur vers le fichier
 * @return int 0 si tout s'est bien passé
 */
int set_catfile(char *nom_fichier, cow_parameters *param);
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
 * @brief Donne le pointeur vers le fichier à lire aux paramèrtes
 * @param nom_fichier nom du fichier vers le quel pointer
 * @param paramètres stockant le pointeur vers le fichier
 * @return int 0 si tout s'est bien passé
 */
int set_catfile(char *nom_fichier, cow_parameters *param);

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
 * @param param Contient la chaîne de caractères contenant votre **magnifique burger personnalisé**
 * @param top Décide de si on parle de la partie haute ou basse de votre **magnifique burger personnalisé**
 */
void apply_borgor(char *s, cow_parameters *param, char top);

/**
 * @brief Dans le case où on veut faire animer la vache, permet de mettre à jour la queue
 * @param i La longueur de la queue
 * @param param les paramètres qu'on utilise
 */
void update_queue(unsigned char i, cow_parameters *param);

/**
 * @brief Affiche le texte du fichier contenu dans les paramètres, de la façon donnée dans l'énoncé
 * @param param Structure contenant le pointeur vers le fichier donné.
 */
void update_text(cow_parameters *param);

/**
 * @brief fclose le fichier de param si il existe
 * @param param Les paramètres contenant le potentiel fichier
 */
void close_param(cow_parameters *param);

#endif