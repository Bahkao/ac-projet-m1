TP 2 - Développement d'une stucture de données de manipulation de graphes

Réalisé par SAUVAGE Christophe et NDIAYE Moustafa


----- DESCRIPTION DES FICHIERS SOURCES DU PROGRAMME -----

libliste.c : Contient des fonctions permettant de créer et gérer des listes
doublement chaînées avec sentinelle.

libliste.h : Contient la définition de TypVoisins et les prototypes des
fonctions de libliste.c.

libgraphe.c : Contient les fonctions permettant de créer et gérer un graphe
à partir d'un tableau de listes doublement chaînées avec sentinelle.

libgraphe.h : Contient la définition de TypGraphe et les prototypes des
fonctions de libgraphe.c.

erreurs.h : Définit des constantes permettant à certaines fonctions du programme
de renvoyer des codes d'erreur.

menu.c : Contient des fonctions permettant l'affichage des menus et
l'interaction des différentes fonctionnalités du programme avec l'utilisateur.

menu.h : Contient uniquement le prototype de la fonction permettant l'affichage
du menu qui sera appelée par la fonction main.

main.c : Contient la fonction main qui fait appel uniquement à la fonction
d'affichage du menu à l'utilisateur.


----- COMPILATION ET EXECUTION DU PROGRAMME -----

Se placer à la racine du projet, en ligne de commande, puis taper : 

make
./BIN/main