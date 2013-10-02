#ifndef LIBLISTE_H
#define LIBLISTE_H

#include <stdbool.h>

typedef struct _TypVoisins {
	int voisin;
	int poidsVoisin;
	struct _TypVoisins* voisinSuivant;
	struct _TypVoisins* voisinPrecedent;
} TypVoisins;

TypVoisins* creerListe ();

void ajouterVoisin (TypVoisins**,int,int);

void supprimerVoisin (TypVoisins**,int);

int numeroVoisin (TypVoisins**);

int poidsVoisin (TypVoisins**);

TypVoisins* voisinSuivant (TypVoisins**);

TypVoisins* voisinPrecedent (TypVoisins**);

int tailleListe (TypVoisins**);

bool voisinExiste (TypVoisins**,int);

char* toString (TypVoisins**);

#endif