/*
******************************************************************************
*
* Programme : libliste.c
*
* Auteurs : Christophe SAUVAGE et Mustafa NDIAYE
*
* Résumé : Bibliothèque permettant de créer et gérer des graphes.
*
*          On considère que pour un graphe, listesAdjacences[0] désigne le
*          sommet 1, listesAdjacences[1] le sommet 2 etc...
*
* Date : 10/10/2013
*
******************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "libgraphe.h"
#include "libliste.h"
#include "erreurs.h"


/* on considère en fait que c'est dans le programme principal que l'on va tester si un graphe est déjà créé ou non
//
// Exemple de création d'un graphe dans le main :
// TypGraphe* graphe;
// graphe = creerGraphe(7);
//
// insertionSommet(graphe,2);
// ...*/
TypGraphe* creerGraphe(int nbrMaxSommets) {
	int i;
	TypGraphe* graphe;
	
	graphe = malloc(sizeof(TypGraphe));
	graphe->nbrMaxSommets = nbrMaxSommets;
	graphe->listesAdjacences = ( TypVoisins** ) malloc( nbrMaxSommets * sizeof( TypVoisins* ) );
		
	for ( i = 0; i < nbrMaxSommets; i++) {
		graphe->listesAdjacences[i] = NULL;
	} 

	return graphe;
}


int insertionSommet ( TypGraphe *graphe, int idSommet ) {
	
	if ( graphe->listesAdjacences == NULL ) {
		return GRAPHE_INEXISTANT;
	}
	
	if( (idSommet >= 0 ) && ( idSommet <= graphe->nbrMaxSommets ) ) {
		if ( graphe->listesAdjacences[idSommet-1] == NULL ) {
            graphe->listesAdjacences[idSommet-1] = creerListe();
			return 0;
        }
		else
			return SOMMET_EXISTANT;
	}
	else {
		return SOMMET_INVALIDE;
	}
}




int sommetExistant ( TypGraphe * graphe, int numSommet ) {

	if ( graphe->listesAdjacences == NULL ) {
		return GRAPHE_INEXISTANT;
	} 
	else {
		if ( numSommet > graphe->nbrMaxSommets ) {
			return SOMMET_INVALIDE;
		}
	}

	if ( graphe->listesAdjacences[ numSommet-1 ] != NULL ) {
		return 0;
	} else {
		return SOMMET_INEXISTANT;
	}

}


int areteExistante (TypGraphe *graphe, int depart, int arrivee) {
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,depart) == 0 && sommetExistant(graphe,arrivee) == 0) {
			if (voisinExiste(&(graphe->listesAdjacences[depart-1]),arrivee) == true)
				return 0;
			else
				return ARETE_INEXISTANTE;
		}
		else
			return SOMMET_INEXISTANT;
	}
}


int suppressionSommet ( TypGraphe* graphe, int sommet ) {
	int i;
  
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,sommet) == 0) {
			supprimerListe(&(graphe->listesAdjacences[sommet-1]));
			for (i = 0; i < graphe->nbrMaxSommets; i++) {
				if (graphe->listesAdjacences[i] != NULL)
					supprimerVoisin(&(graphe->listesAdjacences[i]),sommet);
			}
			return 0;
		}
		else
			return SOMMET_INEXISTANT;
	}
}


int insertionAreteOriente ( TypGraphe* graphe, int depart, int arrivee, int poids ) {
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,depart) == 0 && sommetExistant(graphe,arrivee) == 0) {
			ajouterVoisin(&(graphe->listesAdjacences[depart-1]),arrivee,poids);
			return 0;
		}
		else
			return SOMMET_INEXISTANT;
	}
}

int insertionAreteNonOriente ( TypGraphe* graphe, int depart, int arrivee, int poids ) {
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,depart) == 0 && sommetExistant(graphe,arrivee) == 0) {
			ajouterVoisin(&(graphe->listesAdjacences[depart-1]),arrivee,poids);
			ajouterVoisin(&(graphe->listesAdjacences[arrivee-1]),depart,poids);
			return 0;
		}
		else
			return SOMMET_INEXISTANT;
	}
}

/* orientation : 'o' (arête orientée) ou 'n' (non orientée) */
int suppressionArete ( TypGraphe* graphe, int depart, int arrivee, char orientation ) {
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,depart) == 0 && sommetExistant(graphe,arrivee) == 0) {
			if (orientation == 'o') {
				if (areteExistante(graphe,depart,arrivee) == 0) {
					supprimerVoisin(&(graphe->listesAdjacences[depart-1]),arrivee);
					return 0;
				}
				else
				return ARETE_INEXISTANTE;
			}
			else {
				if (areteExistante(graphe,depart,arrivee) == 0 && areteExistante(graphe,arrivee,depart) == 0) {
					supprimerVoisin(&(graphe->listesAdjacences[depart-1]),arrivee);
					supprimerVoisin(&(graphe->listesAdjacences[arrivee-1]),depart);
					return 0;
				}
				else
					return ARETE_INEXISTANTE;
			}
		}
		else
			return SOMMET_INEXISTANT;
	}
}


/*
 *******************************************************************************
 *	Fonction:	affichage
 *
 *	Paramettre :	TypGraphe * graphe      : est un pointeur sur TypGraphe
 *			
 *
 *	Retour:		rien
 *
 *	Description:	affichage d'un graphe
 ********************************************************************************
 */
void affichage ( TypGraphe* graphe ) {

	int i;
	graphe = malloc(sizeof(TypGraphe));
	printf ( "# nombre maximum de sommets\n" );
	printf ( "%d",graphe->nbrMaxSommets );
	printf ( "\n" );
	printf ( "# sommets : voisins\n" );
	
	for ( i=0; i< graphe->nbrMaxSommets; i++ ) {
	
		printf ( "%d : ", i+1 );
		if ( graphe->listesAdjacences[i] != NULL ) {
    
			toString ( graphe->listesAdjacences[ i ] );
		}
		else{
			printf( "\n" );
		}
		
	}
  
}


/* Supprime toute la mémoire allouée pour l'ensemble du graphe*/
void deleteGraphe ( TypGraphe* graphe ) {
	int i;
	
	/* Suppression de tous les sommets (donc de toutes les listes)*/
	for (i = 0; i < graphe->nbrMaxSommets; i++)
		suppressionSommet(graphe,i+1);
		
	/* Libération de la mémoire occupée par le tableau*/
	free(graphe->listesAdjacences);
	
	/*Libération de la mémoire occupée par le graphe*/
	free(graphe);
}

/*

void saveGraphe (TypGraphe* graphe,FILE *fichier){  
    	
 }
*/
