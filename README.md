# cowsay
Projet d'INF203 en S2

# Présentation du Projet
&emsp; Le projet débute au premier jour du cours INF203 et s'achève lors de la dernière semaine de cours. Cette dernière fait date de rendu (dimanche soir minuit de la dernière semaine). On peut progresser sur le projet à son rythme, mais on nous recommande de prendre de l'avance par rapport au cours. La partie Bash devrait être achevée quand les cours de C débuteront.

## 1.1 Objectif du projet
&emsp; L'objectif du projet est d'explorer les possibilités de cowsay et du terminal. Au cours du projet, nous réaliserons les objectifs suivants:
1. **Préliminaires**. Découvrir la commande `cowsay`à travers son manuel et l'ensemble des options qu'elle contient.
2. **Bash**. Implémenter un script Bash qui fait réciter à la vache différentes suites logiques
3. **C**. Recoder `cowsay` en C, avec des nouvelles fonctionnalités.
4. **Automates**. En s'appuyany sur la théorie des automates, impléter un tamagoshi dans cowsay

# 1 Préliminaires
Dans cette première section, il nous est conseillé de découvrir l'éxecutable `cowsay`.  
Pour cela, on lit consciencieusement le manuel de cowsay à travers la commande `man cowsay`.  
&emsp; A l'aide du manuel, faire un tableau reportant l'ensemble des arguments et explicitant leurs usages en donnant quelques exemples d'exécution.

# 2 Bash
Dans cette section, l'objectif est de proposer un script shell consistant à faire dynamiquement lister par la vache les itérés d'une suite de nombres. Pour cela, on se servira de `clear` qui rafraichit l'écran et de `sleep`  qui créé une pause de t secondes.  
On produira successivement les scripts suivants:
1. `cow_kindergarten` dans lequel la vache prononce les chiffres de **1 à 10** avec une pause d'**une seconde** entre chaque chiffre. La vache tirera la langue à la fin de l'exercice.
2. `cow_primaryschool` où cette fois-ci la vache prononce les chiffres de **1 à *n*** où n est donné en argument du script
3. `cow_highschool` où la vache prononce les carrés des chiffres de **1 à *n***
4. `cow_college` qui prononce les nombres de la suite de Fibonacci inférieurs à *n*.
5. `cow_university` qui fait de même avec les nombre premiers inférieurs à *n*
6. `smart_cow` qui effectue le calcul donné par l'utilisateur et qui affiche le résultat dans ses yeux
7. `crazy_cow` qui permet de calculer toutes les étapes du jeu de la vie pour une configuration initiale donnée.

# 3 C
Dans cette seconde partie du projet, on recode la routine `cowsay`de sorte à lui apporter de nouvelles fonctionnalités.
## 1. affiche_vache
On commence par créer la fonction `affiche_vache` qui affiche simplement une vache sans la bulle de texte.  
Dans l'appel de la fonction `main`, on effectuera simplement l'appel à la fonction `affiche_vache`.

## 2. Paramètres de base
Il s'agit désormais d'ajouter des fonctionnalités à `newcow`. Pour cela, on modifie `newcow.c` de sorte à ce que `newcow` reçoive et filtre les arguments de `-e` (ou `--eyes`) et une chaîne de deux caractères qui modifie les yeux de la vache. On adapte ensuite la vache à d'autres paramètres du cowsay original.

## 3. Paramètre original
On implémente ensuite une nouvelle fonctionnalité à `newcow`.

## 4. Animation
On peut maintenant créer une "vache animée". Pour parvenir à cet objectif, on utilise les deux fonctions suivantes:
```c
void update() {
  printf("\033[H\033[J");
} // Efface l'écran, effet similaire à clear

void gotoxy(int x, int y) {
  printf("\033[%d;%dH", y, x);
} // Déplace le curseur du terminal à la coordonnée (x, y)
```
En utilisant ces deux commandes ainsi que la routine `sleep()` disponible dans `<unistd.h>`, on créé une vache animée de notre choix.

## 5. Lecture de fichier
Nous allons enfin créer une vache animée qui apprend à lire. Pour cela, on rédige un code qui prendre comme argument un fichier dans lequel sera écrit un ou plusieurs mots (on pourra ajouter un paramètres pour que le fichier pris en compte soit l'entrée standard `stdin`). L'objectif est de faire lire le fichier à la vache, caractères par caractères. Chaque caractères apparaitra alors successivement dans la gueule de la vache et sera "avalé" et ensuite placé à la suite des caractères affichés.

# 4 Automates
Dans cette dernière section, nous allons créer notre premier Tamagoshi-vache. Il s'agit de mettre en place un petit jeu vidéo dans lequel on doit nourrir notre vache afin qu'elle survive aussi longtemps que possible. Le score du joueur à la fin du jeu est précisément ce temps de survie. Le jeu se déroule ainsi:
- A chaque instant du jeu, la vache se trouve dans l'un des trois *états* suivants:
  - `liferocks` : en pleine forme
  - `lifesucks` : ne se sent pas bien
  - `byebyelife` : morte
- Chaque état est associé à un *niveau de santé* appelé `fitness` : 0 étant l'état mort de faim et 10 mort de suralimentation:
  - `liferocks` : `4 <= fitness <= 6`
  - `lifesucks` : `7 <= fitness <= 9`
  - `byebyelife` : `1 <= fitness <= 3`  
Au début du jeu, la vache est à `fitness = 5`
- Le joueur observe à tout moment l'*état* de la vache mais n'est jamais au courant de son *niveau de santé*.
- Le jouer a par aillers à sa disposition une réserve de nourriture qui évolue avec le temps et mesurable via la variable `stock`comprise entre 0 (réserve à sec) et 10 (réserve pleine). La réserve initiale est composée de `stock = 5` unités de nourriture. A chaque pas de temps du jeu, le joueur décide de nourrir la vache d'une quantité `lunchfood` de nourriture extraite de la réserve.
- Après que le joueur a choisi la valeur de `lunchfood`, une variable aléatoire `digestion` comprise entre 0 (digestion optimale) et -3 (digestion difficile) s'ajoute à `lunchfood` pour faire écoluer le niveau de santé `fitness` de la vache. Le niveau de santé devient donc `fitness + lunchfood + digestion`.
- De la même manière, après que le joueur a choisi la valeur de `lunchfood`, une variable aléatoire `crop` comprise entre -3 (la nourriture de la réserve devient avariée) et 3 (nouvelles récoltes) fait évoluer le niveau de al réserve. La variable `stock` devient donc `stock - lunchfood + crop`  

Dans un premier temps, afin de mettre le problème au clair, on peut dessiner un automate des trois états de santé de notre vache.
- Pour dessiner l'automate, on supposera que les variables `fitness`, `digestion` et `stock` sont figées et connues.
- L'unique action possible est celle de l'utilisateur qui choisit la valeur `lunchfood` dans son intervalle de validité. Les transitions dépendent alors de l'intervalle dans lequel `lunchfood` se trouve: cet intervalle dépend de `fitness`, `digestion` et `stock`.
- Les sorties possibles correspondent:
  1. A l'affichage visuel de la vache dans son nouvel *état*
  2. L'affichage visuel de la valeur `stock` mise à jour
  3. L'affichage du score final au moment de la conclusion du programme  

Il sera possible de modéliser les actions des 2 variables aléatoires `digestion`et `crop` comme les actions menées par 2 autres acteurs du jeu.
Ce graph d'automate sera utile pour valider notre code.  

&emsp; Nous mettrons alors en place un code tamagoshi_cow.c qui implémentera le jeu vidéo.
