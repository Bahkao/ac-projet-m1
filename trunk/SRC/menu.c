#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "menu.h"
#include "libgraphe.h"
#include "libliste.h"


TypGraphe* graphe;


void menu_principale (){
	char chaine[3], chemin[ 512 ];
	int tmp,choix;
	
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
			graphe = creerGraphe(tmp);
			break;
		case 2 : 
			printf( "Entrer le nom du fichier\n" );
				scanf("%s",chemin);
				printf("%s",chemin);
                graphe = lecture(chemin);
                sous_menu();
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
	FILE *fichier;
	char chemin[ 256 ];
	char chaine[256];
	char cheminSauvegarde[80] = "../ac-projet-m1/lecture/";
	
	int numSommet;
	
	int areteOrientee;
	int sommetDepart;
	int sommetArrive;
	int poidsArete;
	
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
		affichage ( graphe );
		break;
	case 2 :
		printf("Insérer un sommet\n");
        printf("Saisir le numéro du sommet : ");
		scanf("%s",chaine);
		numSommet = atoi(chaine);
		insertionSommet(graphe,numSommet);
		break;
	case 3 :
		printf("Insérer une arête \n");
        printf( "Est-ce une arête orientée ? \n 1-Oui 0-Non\n" );
		scanf("%s",chaine);
		areteOrientee = atoi(chaine);
		printf("Saisissez le sommet de départ : ");
		scanf("%s",chaine);
		sommetDepart = atoi(chaine);
		printf("Saisissez le sommet d'arrivée : ");
		scanf("%s",chaine);
		sommetArrive = atoi(chaine);
		printf("Saisissez le poids de l'arête : ");
		scanf("%s",chaine);
		poidsArete = atoi(chaine);
		if (areteOrientee == 1)
			insertionAreteOriente(graphe,sommetDepart,sommetArrive,poidsArete);
		else
			insertionAreteNonOriente(graphe,sommetDepart,sommetArrive,poidsArete);
		break;
	case 4 :
		printf("Supprimer un sommet\n");
        printf("Entrer le sommet à supprimer : ");
		scanf("%s",chaine);
		numSommet = atoi(chaine);
		suppressionSommet(graphe,numSommet);
        break;
	case 5 :
		printf("Supprimer une arête\n");
		printf( "Est-ce une arête orientée ? \n 1-Oui 0-Non\n" );
		scanf("%s",chaine);
		areteOrientee = atoi(chaine);
        printf("Insérer le sommet de départ : ");
		scanf("%s",chaine);
		sommetDepart = atoi(chaine);
		printf("Insérer le sommet d'arrivée : ");
		scanf("%s",chaine);
		sommetArrive = atoi(chaine);
		if (areteOrientee == 1)
			suppressionArete(graphe,sommetDepart,sommetArrive,'o');
		else
			suppressionArete(graphe,sommetDepart,sommetArrive,'n');
        break;
	case 6 :
		printf("Sauvegarder le graphe\n");
        if(graphe != NULL) {
			printf("saisir le nom de fichier: \n");
            scanf("%s",chemin);
			strcat(cheminSauvegarde,chemin);
            fichier = fopen( cheminSauvegarde, "w" );
            sauvegarde(graphe,fichier);
            fclose( fichier );
		}
        else {
			printf( "Pas de graphe en cours\n" );
        }
        break;
           
	case 8 :
		deleteGraphe(graphe);
		exit(0);
		break;
	
	}
	sous_menu();
}







