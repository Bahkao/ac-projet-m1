#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "libgraphe.h"
#include "libliste.h"



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


int suppressionSommet ( TypGraphe* graphe, int sommet ) {

 return 0;
  
}


int insertionAreteOriente ( TypGraphe* graphe, int de, int vers, int poids ) {
	return 0;
}

int insertionAreteNonOriente ( TypGraphe* graphe, int de, int vers, int poids ) {
return 0;
}


int suppressionArete ( TypGraphe* graphe, int de, int vers, char orientation ) {
return 0;
}

void deleteGraphe ( TypGraphe* graphe ) {

}
void saveGraphe (TypGraphe* graphe,FILE *fichier){  
    	
 }
