TP 2 - D�veloppement d'une stucture de donn�es de manipulation de graphes

R�alis� par SAUVAGE Christophe et NDIAYE Moustafa


----- DESCRIPTION DES FICHIERS SOURCES DU PROGRAMME -----

libliste.c : Contient des fonctions permettant de cr�er et g�rer des listes
doublement cha�n�es avec sentinelle.

libliste.h : Contient la d�finition de TypVoisins et les prototypes des
fonctions de libliste.c.

libgraphe.c : Contient les fonctions permettant de cr�er et g�rer un graphe
� partir d'un tableau de listes doublement cha�n�es avec sentinelle.

libgraphe.h : Contient la d�finition de TypGraphe et les prototypes des
fonctions de libgraphe.c.

erreurs.h : D�finit des constantes permettant � certaines fonctions du programme
de renvoyer des codes d'erreur.

menu.c : Contient des fonctions permettant l'affichage des menus et
l'interaction des diff�rentes fonctionnalit�s du programme avec l'utilisateur.

menu.h : Contient uniquement le prototype de la fonction permettant l'affichage
du menu qui sera appel�e par la fonction main.

main.c : Contient la fonction main qui fait appel uniquement � la fonction
d'affichage du menu � l'utilisateur.


----- COMPILATION ET EXECUTION DU PROGRAMME -----

Se placer � la racine du projet, en ligne de commande, puis taper : 

make
./BIN/main