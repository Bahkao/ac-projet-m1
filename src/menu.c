#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "menu.h"
#include "libgraphe.h"
#include "libliste.h"



void menu_principale (){
	TypGraphe* graphe;
	char chaine[3];
	int tmp,choix,j;
	
	printf(  "##########################################\n" );
        printf(  "#             MENU PRINCIPALE            #\n" );
        printf(  "##########################################\n" );
	printf(  "#	1 : Creer un nouveau graphe       #\n");
	printf(  "#	2 : Charger le graphe             #\n");
	printf(  "#	3 : Quitter                       #\n");
	printf(  "##########################################\n" );
	printf(  "Faites un choix\n");
	scanf("%d",&choix);
	switch (choix){
		case 1 :
			printf("Taper le nombre maximum de sommets:  \n");
			scanf("%s",chaine);
			sscanf(chaine,"%d",&tmp);
			graphe = malloc(sizeof(TypGraphe));
			j = creerGraphe(graphe, tmp);
			break;
		case 2 : 
			exit(0);
			break;
	
	}
	sous_menu();
	
}

/****************************************************
 * Fonction   		:sous_menu
 *
 * Paramettre 		:rien
 *
 * Retour     		:rien
 * 
 * Description		: affichage du sous menu
 ****************************************************
 */
void sous_menu(){
	
	int choix;
	
	printf(  "##########################################\n" );
        printf(  "#                 SOUS MENU              #\n" );
        printf(  "##########################################\n" );
	printf(  "#	1 : Afficher le graphe            #\n");
	printf(  "#	2 : Inserer un sommet             #\n");
	printf(  "#	3 : Inserer une arête             #\n");
	printf(	 "#	4 : Supprimer un sommet           #\n");
	printf(	 "#	5 : Supprimer une arête           #\n");
	printf(	 "#	6 : Sauvegarder le graphe         #\n");
	printf(	 "#	7 : Charger le graphe             #\n");
	printf(  "#	8 : Quitter                       #\n");
	printf(  "##########################################\n" );
	printf(" Faites un choix:\n ");
	scanf("%d",&choix);
	switch (choix){
	case 1 :
		printf("Afficher le graphe\n ");
		
	case 2 :
		printf("Inserer un sommet\n");
		printf("Saisir le numéro du sommet\n");
		break;
	case 3 :
		printf("Inserer une arête \n");
		printf( "Es une arête orientée ? \n 1-Oui 0-Non\n" );
		break;
	case 4 :
		printf("Supprimer un sommet\n");
		printf("Entrer le sommet à supprimer\n");
		break;
	case 5 :
		printf("Supprimer une arête\n");
		printf("Inserer le sommet de départ : \n");
		break;
	case 6 :
		
		printf("Sauvegarder le graphe\n");
		break;
           
	case 8 :
		
		exit(0);
		break;
	
	}
	sous_menu();
}







