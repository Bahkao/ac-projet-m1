#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
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


void menu_principale (){
	int nbSommets;
	int choix;
	char ligne[201];
	int compte;
	char ligneNbSommets[11];
	char chemin[201];
	
	printf(  "##########################################\n" );
    printf(  "#             MENU PRINCIPAL             #\n" );
    printf(  "##########################################\n" );
	printf(  "#	1 : Créer un nouveau graphe       #\n");
	printf(  "#	2 : Charger le graphe             #\n");
	printf(  "#	3 : Quitter                       #\n");
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
				fgets(ligneNbSommets,10,stdin);
				cleanBuffer(ligneNbSommets);
				compte = sscanf(ligneNbSommets,"%d",&nbSommets);
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
	int choix;
	char ligne[3];
	int compte;
	
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


static void sousMenuAfficherGraphe() {
	printf("\n===Afficher le graphe ===\n\n");
	affichage(graphe);
	pause();
}

static void sousMenuInsererSommet() {
	char ligne[11];
	int numSommet;
	int compte;

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


static void sousMenuInsererArete() {
	char areteOrientee;
	int sommetDepart;
	int sommetArrivee;
	int poidsArete;
	char ligne[11];
	int compte;

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


static void sousMenuSupprimerSommet() {
	int numSommet;
	char ligne[11];
	int compte;

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


static void sousMenuSupprimerArete() {
	char areteOrientee;
	int sommetDepart;
	int sommetArrivee;
	char ligne[11];
	int compte;

	printf("\n=== Supprimer une arête ===\n\n");
	
	do {
		printf( "Est-ce une arête orientée ? (o/n) " );
		fgets(ligne,2,stdin);
		cleanBuffer(ligne);
		compte = sscanf(ligne,"%c",&areteOrientee);
	} while (compte != 1 || areteOrientee != 'o' || areteOrientee != 'n');
	
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


static void sousMenuSauvegarderGraphe() {
	char chemin[201];
	char ligne[201];
	char cheminSauvegarde[250] = "lecture/";
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


static void sousMenuChargerGraphe() {
	char chemin[201];
	char ligne[201];
	char continuer;
	int compte;
	
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


static void sousMenuQuitter() {
	char ligne[3];
	char continuer;
	int compte;

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


/* Vide le buffer du clavier si nécessaire */
static void cleanBuffer (const char *chaine) {
    char *p = strchr(chaine, '\n');
	int c;
 
    if (p) {
        p = NULL;
    }
    else {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}


static void pause() {
	int c;
	
	printf("\nAppuyez sur Entrer pour continuer\n");
	/* pour faire une pause puis vider le buffer */
	while ((c = getchar()) != '\n' && c != EOF);
}