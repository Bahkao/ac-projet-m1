/*
 *Auhor  Christian Sauvage & Ndiaye Moustapha
 */

#ifndef libgraphe_H
#define libgraphe_H
#include "libliste.h"

typedef struct TypGraphe{

	    int nbrMaxSommets; /*Le nombre maximun de sommets du graphe*/
	    struct TypVoisins** listesAdjacences; /*Listes d'ajacence*/
	        
} TypGraphe;


int creerGraphe(TypGraphe*, int);
int supprimmerSommet(int);
int suppressionSommet ( TypGraphe*, int);
int insertionAreteOriente ( TypGraphe*, int, int, int);
int insertionAreteNonOriente ( TypGraphe*, int, int, int);
int suppressionArete ( TypGraphe*, int, int, char);

void deleteGraphe ( TypGraphe* );
void saveGraphe (TypGraphe* ,FILE *);

#endif
