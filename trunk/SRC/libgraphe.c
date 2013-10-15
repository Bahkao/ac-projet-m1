/*
******************************************************************************
*
* Programme : libliste.c
*
* Auteurs : Christophe SAUVAGE et Mustafa NDIAYE
*
* Résumé : Bibliothèque permettant de créer et gérer des listes circulaires
*          doublement chaînées avec sentinelle.
*
* Date : 06/10/2013
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

/*Fonction création */

int creerGraphe ( TypGraphe* graphe, int nbrMaxSommets ) {

	int i;
	
	if ( graphe->listesAdjacences != NULL ) {
		return 1;
	} else{
	
	graphe->nbrMaxSommets = nbrMaxSommets;
	graphe->listesAdjacences = ( TypVoisins** ) malloc( nbrMaxSommets * sizeof( TypVoisins* ) );
		
	
	for ( i = 0; i < nbrMaxSommets; i++) {
		graphe->listesAdjacences[i] = NULL;
	} 

	}

	return 1;

		
}



int insertionSommet ( TypGraphe *graphe, int idSommet ) {
	
	if ( graphe->listesAdjacences == NULL ) {
		return 1;
	}
	
	if( (idSommet >= 0 ) && ( idSommet <= graphe->nbrMaxSommets ) ) {
		
		if ( graphe->listesAdjacences[ idSommet-1 ] == NULL ) {
            		graphe->listesAdjacences[ idSommet-1 ] = creerListe();
        	}
        	return 1;
	}
	else{
		return 0;
	}
	
	
}




int sommetExistant ( TypGraphe * graphe, int numSommet ) {

	if ( graphe->listesAdjacences == NULL ) {
		return 0;
	} 
	else {
		if ( numSommet > graphe->nbrMaxSommets ) {
			return 0;
		}
	}

	if ( graphe->listesAdjacences[ numSommet-1 ] != NULL ) {
		return 1;
	} else {
		return 0;
	}

}


int areteExistante (TypGraphe *graphe, int depart, int arrivee) {
	if (graphe->listesAdjacences == NULL)
		return GRAPHE_INEXISTANT;
	else {
		if (sommetExistant(graphe,depart) == 0 && sommetExistant(graphe,arrivee) == 0) {
			if (voisinExiste(graphe->listesAdjacences[depart],arrivee) == true)
				return 0;
			else
				return SOMMET_INEXISTANT;
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
			supprimerListe(graphe->listesAdjacences[sommet]);
			for (i = 0; i <= graphe->nbrMaxSommets; i++) {
				if (graphe->listesAdjacences[i] != NULL)
					supprimerVoisin(graphe->listesAdjacences[i],sommet);
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
			ajouterVoisin(graphe->listesAdjacences[depart],arrivee,poids);
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
			ajouterVoisin(graphe->listesAdjacences[depart],arrivee,poids);
			ajouterVoisin(graphe->listesAdjacences[arrivee],depart,poids);
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
					supprimerVoisin(graphe->listesAdjacences[depart],arrivee);
					return 0;
				}
				else
				return ARETE_INEXISTANTE;
			}
			else {
				if (areteExistante(graphe,depart,arrivee) == 0 && areteExistante(graphe,arrivee,depart)) {
					supprimerVoisin(graphe->listesAdjacences[depart],arrivee);
					supprimerVoisin(graphe->listesAdjacences[arrivee],depart);
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


void deleteGraphe ( TypGraphe* graphe ) {

}
/*

void saveGraphe (TypGraphe* graphe,FILE *fichier){  
    	
 }
*/