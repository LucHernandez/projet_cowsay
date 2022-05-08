#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "newcow.h"
#include "outils.h"
#include "tamacowshi.h"

void affiche_vache(cow_parameters *param){
  char outputstr[723] = "";         // 123 étant la taille de la vache "normale", les 565 étant là pour le cas où on met plein de pain autour de la vache
  if (!param->tamacowshi_enabled) { // On vérifie si on est dans un cas "simple" d'utilisation
    build_cow(param, outputstr);
    printf("%s", outputstr);
  }
  else {
    char fitness = 5;
    unsigned char durre_de_vie = 0;
    while (fitness % 10 != 0) {
      update();
      printf("%s", outputstr);
      durre_de_vie++;
      reset_str(outputstr);

      // On change les paramètres en fonction du fitness de la vache
      fitness = tamacowshi_step(param->tamacow);
      if (fitness % 10 == 0){
        set_eyes("xx", param);
        set_tongue("U", param);
      }
      else if (fitness <= 3) {
        set_eyes("@@", param);
      }
      else if (fitness <= 6) {}
      else {
        set_eyes("**", param);
        set_tongue("U", param);
      }
      build_cow(param, outputstr);
      printf("%s", outputstr);
    }

    update();
    printf("Votre vache est morte. Vous avez tenu %d tours.\n", durre_de_vie - 1);
  }
}

void init_cow_param(cow_parameters *param) {
  strcpy(param->yeux, "oo\0");
  strcpy(param->langue, "  \0");
  set_borgor("c", param);
  set_queueY(3, param); // 3 étant la position y de la queue quand on ne met pas la vache dans un burger
  param->limitanim = 0;
  param->fichier = NULL;
  param->firsttime = 1;
  param->tamacowshi_enabled = 0;
  param->tamacow = (tamacowshi*) malloc(sizeof(tamacowshi));
  param->finY = 0;
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

  if (length > 7 || length == 0) return 2; // Permet d'éviter les petits malins qui mettent 35000 tomates et qui boulversent le commerce espagnol

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
  if (length > 1 && !param->tamacowshi_enabled) {
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

int set_catfile(char *nom_fichier, cow_parameters *param) {
  FILE *fichier = fopen(nom_fichier, "r");
  if (fichier == NULL) param->fichier = stdin; // Si on donne n'importe quoi au fichier, il va utiliser stdin comme sortie et va fonctionner comme cat
  else param->fichier = fichier;
  for (int i=0; i<TAILLE_MAX_FICHIER; i++){
    param->text[i] = '\0';
  }
  param->queueY++;
  return 0;
}

void build_cow(cow_parameters *param, char *s) {
  apply_borgor(s, param, 0); // On ajoute la partie supérieure du burger
  if (strlen(param->burger) != 1) strcat(s, "\033[38;5;130m");
  strcat(s, "        \\   ^__^\n         \\  (");
  strcat(s, param->yeux); // Ajout des yeux
  strcat(s, ")\\_______\n            (__)\\       )\\/\\\n             ");
  strcat(s, param->langue); // Ajout de la langue
  strcat(s, " ||----w |\n                ||     ||\n");
  apply_borgor(s, param, 1); // On ajoute la partie inférieure du burger
  strcat(s, "\033[38;5;130m");
  if (strlen(param->burger) == 1) strcat(s, "\033[0m"); 
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
      param->finY += 3;
      if (top == 0) { // On différencie les pains au dessus et en dessous de la vache pour avoir un vrai aspect burger
        strcat(s, "\033[38;5;178m   -------------------   \n /   .     .     .     \\ \n| .     .     .     .   |\n");
        if (param->firsttime == 1) set_queueY(param->queueY + 3, param);
      }
      else strcat(s, "\033[38;5;178m| .     .     .     .   |\n \\   .     .     .     / \n   -------------------   \n");
      break;
    case 's':
      param->finY += 2;
      strcat(s, "\033[38;5;28m ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
      if (top == 0 && param->firsttime == 1) set_queueY(param->queueY + 2, param);
      break;
    case 't':
      param->finY += 1;
      strcat(s, "\033[38;5;196mooooooooooTOMATEooooooooo\n"); // Je ne suis pas graphiste
      if (top == 0 && param->firsttime == 1) set_queueY(param->queueY + 1, param);
      break;
    default: // On ne rencontre jamais cette situation mais je suppose que c'est good practice d'avoir un default
      break;
   }
   debut++;
 }
 param->firsttime = 0;
}

void update_queue(unsigned char i, cow_parameters *param) {
  i += 3; // 3 étant la longueur minimum de la queue
  gotoxy(26, param->queueY);
  while (i > 0) {
    if(i%2 == 0) printf("\\"); // J'ai bloqué beaucoup trop de temps sur le fait que \ n'était pas comptabilisé
    else printf("/");
    i--;
  }
}

void update_text(cow_parameters *param) {
  printf("\033[0m");
  static char tmp = '\0';
  static unsigned int i = 0;
  
  if (param->fichier == NULL) return; // On s'assure qu'on veut afficher quelque chose, ça n'arrivera jamais parce qu'on fait déjà le test avant mais ça paraît cohérent de le mettre là
  if (i >= TAILLE_MAX_FICHIER - 2){ // Aie Aie Aie, on dépasse la taille maximale du fichier, on va éviter la seg fault
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
    tmp = (char) fgetc(param->fichier);
    if (tmp != '\n') set_tongue(&tmp, param); // On évite de faire dire des retours à la ligne à la vache
  }

  update();
  unsigned char mc = max_char_par_ligne(param->text);

  // Affichage de la ligne du haut
  for (unsigned char tirets = 0; tirets <= mc; tirets++) printf("-");
  printf("\n");

  printf("%s\n", param->text); // Ici ça sera l'affichage du texte
  
  // Affichage de la ligne du bas
  for (unsigned char tirets = 0; tirets <= mc; tirets++) printf("-");
  printf("\n");

  affiche_vache(param);
}

void close_param(cow_parameters *param) {
  if (param->fichier != NULL) fclose(param->fichier);
  free(param->tamacow);
}
