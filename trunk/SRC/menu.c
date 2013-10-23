/*
******************************************************************************
*
* Programme : menu.c
*
* Auteurs : Christophe SAUVAGE et Mustafa NDIAYE
*
* Résumé : Affichage et gestion du menu du programme
*
* Date : 23/10/2013
*
******************************************************************************
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "libgraphe.h"
#include "libliste.h"
#include "erreurs.h"


TypGraphe* graphe;


static void sous_menu();
static void sousMenuAfficherGraphe();
static void sousMenuInsererSommet();
static void sousMenuInsererArete();
static void sousMenuSupprimerSommet();
static void sousMenuSupprimerArete();
static void sousMenuSauvegarderGraphe();
static void sousMenuChargerGraphe();
static void sousMenuQuitter();
static void cleanBuffer(const char *chaine);
static void pause();


	/*
	* Fonction : menu_principale
	*
	* Description : Affiche le premier menu du programme
	*/
void menu_principale (){
	int nbSommets;     /* Nombre max de sommets que pourra contenir le graphe */
	int choix;         /* Choix de l'utilisateur dans le menu */
	char ligne[201];   /* Contient l'entrée au clavier de l'utilisateur */
	int compte;        /* Permet de vérifier le retour de sscanf */
	char chemin[201];  /* Chemin vers un fichier à charger */
	
	printf(  "##########################################\n" );
	printf(  "#             MENU PRINCIPAL             #\n" );
	printf(  "##########################################\n" );
	printf(  "#	1 : Créer un nouveau graphe      #\n");
	printf(  "#	2 : Charger le graphe            #\n");
	printf(  "#	3 : Quitter                      #\n");
	printf(  "##########################################\n" );
	
	do {
		printf("Faites un choix: ");
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&choix);
	} while (compte != 1 || choix < 1 || choix > 3);
	
	switch (choix){
		case 1 :
			do {
				printf("Tapez le nombre maximum de sommets (>= 1) : ");
				fgets(ligne,10,stdin);
				cleanBuffer(ligne);
				compte = sscanf(ligne,"%d",&nbSommets);
			} while (compte != 1 || nbSommets <= 0);
			graphe = creerGraphe(nbSommets);
			printf("\nGraphe créé avec succès !\n");
			sous_menu();
			break;
		case 2 : 
			printf("Saisissez le nom du fichier : ");
			fgets(ligne,200,stdin);
			sscanf(ligne,"%s",chemin);
			graphe = lecture(chemin);
			sous_menu();
			break;
		case 3 :
			exit(0);
			break;
	}
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
static void sous_menu(){
	int choix;      /* Choix de l'utilisateur dans le menu */
	char ligne[3];  /* Contient l'entrée au clavier de l'utilisateur */
	int compte;     /* Permet de vérifier le retour de sscanf */
	
	printf("\n\n\n");
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
	
	do {
		printf("Faites un choix: ");
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&choix);
	} while (compte != 1 || choix < 1 || choix > 8);
	
	switch (choix){
	case 1 :
		sousMenuAfficherGraphe();
		break;
	case 2 :
		sousMenuInsererSommet();
		break;
	case 3 :
		sousMenuInsererArete();
		break;
	case 4 :
		sousMenuSupprimerSommet();
        break;
	case 5 :
		sousMenuSupprimerArete();
        break;
	case 6 :
		sousMenuSauvegarderGraphe();
        break;
    case 7 :
		sousMenuChargerGraphe();
		break;
	case 8 :
		sousMenuQuitter();
		break;
	}
	sous_menu();
}


	/*
	* Fonction : sousMenuAfficherGraphe
	*
	* Description : Permet de demander l'affichage du graphe
	*/
static void sousMenuAfficherGraphe() {
	printf("\n===Afficher le graphe ===\n\n");
	affichage(graphe);
	pause();
}


	/*
	* Fonction : sousMenuInsererSommet
	*
	* Description : Permet de demander l'insertion d'un sommet dans le graphe
	*/
static void sousMenuInsererSommet() {
	char ligne[11];  /* Contient l'entrée au clavier de l'utilisateur */
	int numSommet;   /* Sommet à insérer */
	int compte;      /* Permet de vérifier le retour de sscanf */

	printf("\n===Insérer un sommet ===\n\n");
	
	do {
		printf("Saisissez le numéro du sommet : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&numSommet);
	} while (compte != 1);
	
	/* Insertion du sommet si possible et traitement d'une éventuelle erreur */
	switch(insertionSommet(graphe,numSommet)) {
		case SOMMET_EXISTANT :
			printf("Erreur : le sommet %d existe déjà dans le graphe\n",numSommet);
			pause();
			break;
		case SOMMET_INVALIDE :
			printf("Erreur : le sommet doit être compris entre 1 et %d\n",graphe->nbrMaxSommets);
			pause();
			break;
		case 0 :
			printf("Le sommet %d a bien été inséré dans le graphe.\n",numSommet);
			pause();
			break;
	}
}


	/*
	* Fonction : sousMenuInsererArete
	*
	* Description : Permet de demander l'insertion d'une arête dans le graphe
	*/
static void sousMenuInsererArete() {
	char areteOrientee; /* 'o' : arête orientée ; 'n' : arête non orientée */
	int sommetDepart;   /* Sommet de départ de l'arête */
	int sommetArrivee;  /* Sommet d'arrivée de l'arête */
	int poidsArete;     /* Poids de l'arête */
	char ligne[11];     /* Contient l'entrée au clavier de l'utilisateur */
	int compte;         /* Permet de vérifier le retour de sscanf */

	printf("\n=== Insérer une arête ===\n\n");
	
	do {
		printf( "Est-ce une arête orientée ? (o/n) " );
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%c",&areteOrientee);
	} while (compte != 1 || (areteOrientee != 'o' && areteOrientee != 'n'));
	
	do {
		printf("Saisissez le sommet de départ : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&sommetDepart);
	} while (compte != 1);
	
	do {
		printf("Saisissez le sommet d'arrivée : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&sommetArrivee);
	} while (compte != 1);
	
	do {
		printf("Saisissez le poids de l'arête : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&poidsArete);
	} while (compte != 1);
	
	if (areteOrientee == 'o') {
		switch (insertionAreteOriente(graphe,sommetDepart,sommetArrivee,poidsArete)) {
			case SOMMET_INEXISTANT :
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				pause();
				break;
			case ARETE_EXISTANTE :
				printf("Erreur : l'arête demandée existe déjà dans le graphe\n");
				pause();
				break;
			case 0 :
				printf("L'arête (%d,%d) a bien été insérée dans le graphe\n",sommetDepart,sommetArrivee);
				pause();
				break;
		}
	}
	else {
		switch (insertionAreteNonOriente(graphe,sommetDepart,sommetArrivee,poidsArete)) {
			case SOMMET_INEXISTANT :
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				pause();
				break;
			case ARETE_EXISTANTE :
				printf("Erreur : l'arête demandée existe déjà dans le graphe\n");
				pause();
				break;
			case 0 :
				printf("L'arête non orientée (%d,%d) a bien été insérée dans le graphe\n",sommetDepart,sommetArrivee);
				pause();
				break;
		}
	}
}


	/*
	* Fonction : sousMenuSupprimerSommet
	*
	* Description : Permet de demander la suppression d'un sommet du graphe
	*/
static void sousMenuSupprimerSommet() {
	int numSommet;   /* Sommet à supprimer */
	char ligne[11];  /* Contient l'entrée au clavier de l'utilisateur */
	int compte;      /* Permet de vérifier le retour de sscanf */

	printf("\n=== Supprimer un sommet ===\n\n");
	
	do {
		printf("Entrez le sommet à supprimer : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&numSommet);
	} while (compte != 1);
	
	switch (suppressionSommet(graphe,numSommet)) {
		case SOMMET_INEXISTANT :
			printf("Erreur : le sommet %d n'existe pas dans le graphe\n",numSommet);
			pause();
			break;
		case 0 :
			printf("Le sommet %d a bien été supprimé du graphe\n",numSommet);
			pause();
			break;
	}
}


	/*
	* Fonction : sousMenuSupprimerArete
	*
	* Description : Permet de demander la suppression d'une arête du graphe
	*/
static void sousMenuSupprimerArete() {
	char areteOrientee;  /* 'o' : arête orientée ; 'n' : arête non orientée */
	int sommetDepart;    /* Sommet de départ de l'arête */
	int sommetArrivee;   /* Sommet d'arrivée de l'arête */
	char ligne[11];      /* Contient l'entrée au clavier de l'utilisateur */
	int compte;          /* Permet de vérifier le retour de sscanf */

	printf("\n=== Supprimer une arête ===\n\n");
	
	do {
		printf( "Est-ce une arête orientée ? (o/n) " );
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%c",&areteOrientee);
	} while (compte != 1 || (areteOrientee != 'o' && areteOrientee != 'n'));
	
	do {
		printf("Saisissez le sommet de départ : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&sommetDepart);
	} while (compte != 1);
	
	do {
		printf("Saisissez le sommet d'arrivée : ");
		fgets(ligne,10,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%d",&sommetArrivee);
	} while (compte != 1);
	
	if (areteOrientee == 'o') {
		switch (suppressionArete(graphe,sommetDepart,sommetArrivee,'o')) {
			case SOMMET_INEXISTANT :
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				pause();
				break;
			case ARETE_INEXISTANTE :
				printf("Erreur : l'arête demandée n'existe pas dans le graphe\n");
				pause();
				break;
			case 0 :
				printf("L'arête (%d,%d) a bien été supprimée du graphe\n",sommetDepart,sommetArrivee);
				pause();
				break;
		}
	}
	else {
		switch (suppressionArete(graphe,sommetDepart,sommetArrivee,'n')) {
			case SOMMET_INEXISTANT :
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				pause();
				break;
			case ARETE_INEXISTANTE :
				printf("Erreur : l'arête demandée n'existe pas dans le graphe\n");
				pause();
				break;
			case 0 :
				printf("L'arête non orientée (%d,%d) a bien été supprimée du graphe\n",sommetDepart,sommetArrivee);
				pause();
				break;
		}
	}
}


	/*
	* Fonction : sousMenuSauvegarderGraphe
	*
	* Description : Permet de demander la sauvegarde du graphe dans un fichier
	*/
static void sousMenuSauvegarderGraphe() {
	char chemin[201];  /* Nom du fichier à créer */
	char ligne[201];   /* Contient l'entrée au clavier de l'utilisateur */
	char cheminSauvegarde[250] = "lecture/";  /* Où est sauvegardé le graphe */
	FILE* fichier;

	printf("\n=== Sauvegarder le graphe ===\n\n");

	printf("Saisissez le nom du fichier : ");
	fgets(ligne,200,stdin);
	sscanf(ligne,"%s",chemin);
	strcat(cheminSauvegarde,chemin);
	
	fichier = fopen(cheminSauvegarde,"w");
	if (fichier != NULL) {
		sauvegarde(graphe,fichier);
		if (fclose(fichier) != EOF) {
			printf("Le graphe a été sauvegardé avec succès.\n");
			pause();
		}
		else {
			printf("Erreur lors de la fermeture du fichier.\n");
			pause();
		}
	}
	else {
		printf("Erreur lors de l'ouverture du fichier.\n");
		pause();
	}
}


	/*
	* Fonction : sousMenuChargerGraphe
	*
	* Description : Permet de demander le chargement d'un graphe depuis un fichier
	*/
static void sousMenuChargerGraphe() {
	char chemin[201];  /* Nom du fichier à charger */
	char ligne[201];   /* Contient l'entrée au clavier de l'utilisateur */
	char continuer;    /* 'o' : continuer l'opération en cours, sinon 'n' */
	int compte;        /* Permet de vérifier le retour de sscanf */
	
	printf("\n=== Charger un graphe ===\n\n");
	
	printf("Attention, le graphe en cours sera supprimé\n");
	do {
		printf("Etes-vous sûr de vouloir charger un autre graphe ? (o/n) ");
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%c",&continuer);
	} while (compte != 1 || (continuer != 'o' && continuer != 'n'));
	
	if (continuer == 'o') {
		deleteGraphe(graphe);
		printf("Saisissez le nom du fichier : ");
		fgets(ligne,200,stdin);
		sscanf(ligne,"%s",chemin);
		graphe = lecture(chemin);
	}
}


	/*
	* Fonction : sousMenuQuitter
	*
	* Description : Permet de quitter le programme
	*/
static void sousMenuQuitter() {
	char ligne[3];   /* Contient l'entrée au clavier de l'utilisateur */
	char continuer;  /* 'o' : continuer l'opération en cours, sinon 'n' */
	int compte;      /* Permet de vérifier le retour de sscanf */

	printf("Attention, le graphe en cours sera supprimé\n");
	do {
		printf("Etes-vous sûr de vouloir quitter ? (o/n) ");
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%c",&continuer);
	} while (compte != 1 || (continuer != 'o' && continuer != 'n'));
	
	if (continuer == 'o') {
		deleteGraphe(graphe);
		exit(0);
	}
}


	/*
	* Fonction : cleanBuffer
	*
	* Paramètre : char* chaine, une chaine dans laquelle on vient d'écrire
	*
	* Description : Permet de supprimer le buffer du clavier après une entrée au
	*				clavier de l'utilisateur dans la console.
	*/
static void cleanBuffer (const char *chaine) {
    char *p;  /* Pointeur sur le "\n" de chaine s'il existe */
	int c;

	p = strchr(chaine,'\n');
    if (p) {
        p = NULL;
    }
    else {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}


	/*
	* Fonction : pause
	*
	* Description : Permet de mettre le programme en pause.
	*				Attend que l'utilisateur appuie sur Entrée.
	*/
static void pause() {
	int c;
	
	printf("\nAppuyez sur Entrer pour continuer\n");
	/* pour faire une pause puis vider le buffer */
	while ((c = getchar()) != '\n' && c != EOF);
}