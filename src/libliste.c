/*
********************************************************************************************************************
*
* Programme : libliste.c
*
* Auteurs : Christophe SAUVAGE et Mustafa Ndiaye
*
* Résumé : Bibliothèque permettant de créer et gérer des listes circulaire doublement chaînées
*          avec sentinelle.
*
* Date : 02/10/2013
********************************************************************************************************************
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "libliste.h"

/*
* DECLARER LES INCLUDE DANS .h OU PAS ???
*/

/*
* VERIFIER QUE LES POINTEURS NE SONT PAS NULL ETC...
*/


/* La fonction peut également s'utiliser en dehors du fichier ??? quel utilité du .h alors ???*/
TypVoisins* creerTypVoisins (int voisin, int poidsVoisin,TypVoisins** voisinSuivant, TypVoisins** voisinPrecedent) {
	TypVoisins* res;
	res = malloc(sizeof(TypVoisins));
	res->voisin = voisin;
	res->poidsVoisin = poidsVoisin;
	res->voisinSuivant = *voisinSuivant;
	res->voisinPrecedent = *voisinPrecedent;
	return res;
}

/*Créer une liste avec une sentinelle ayant pour numéro et poids -1*/
TypVoisins* creerListe () {
	TypVoisins* res;
	res = creerTypVoisins(-1,-1,&res,&res);
	res->voisinSuivant = res;
	res->voisinPrecedent = res;
	return res;
}

/* ajoute un voisin à fin de la liste*/
void ajouterVoisin (TypVoisins** liste, int nouveauVoisin, int poidsNouveauVoisin) {
	TypVoisins* vS = *liste;
	TypVoisins* vP = vS->voisinPrecedent;
	TypVoisins* vC = creerTypVoisins(nouveauVoisin,poidsNouveauVoisin,&vS,&vP);
	vP->voisinSuivant = vC;
	vS->voisinPrecedent = vC;
}

void supprimerVoisin (TypVoisins** liste, int voisinASupprimer) {
	if (voisinASupprimer != -1)
	{
		TypVoisins *vC, *vP, *vS;
		bool trouve;
		
		vC = voisinSuivant(liste);
		trouve = false;
		while (!trouve && vC != *liste) {
			if (numeroVoisin(&vC) == voisinASupprimer)
				trouve = true;
			else
				vC = voisinSuivant(&vC);
		}
		
		if (trouve) {
			vP = voisinPrecedent(&vC);
			vS = voisinSuivant(&vC);
			vP->voisinSuivant = vS;
			vS->voisinPrecedent = vP;
			free(vC);
		}
	}
}

int numeroVoisin (TypVoisins** voisin) {
	return (*voisin)->voisin;
}

int poidsVoisin (TypVoisins** voisin) {
	return (*voisin)->poidsVoisin;
}

TypVoisins* voisinSuivant (TypVoisins** voisin) {
	return (*voisin)->voisinSuivant;
}

TypVoisins* voisinPrecedent (TypVoisins** voisin) {
	return (*voisin)->voisinPrecedent;
}

/* La sentinelle ne compte pas dans la taille de la liste*/
int tailleListe (TypVoisins** liste) {
	TypVoisins* voisinCourant = voisinSuivant(liste);
	int res = 0;
	while (voisinCourant != *liste) {
		res++;
		voisinCourant = voisinSuivant(&voisinCourant);
	}
	return res;
}

/* Renvoie true si le numéro du voisin demandé est présent dans la liste*/
bool voisinExiste (TypVoisins** liste, int voisin) {
	TypVoisins* voisinCourant = voisinSuivant(liste);
	bool trouve = false;
	while (!trouve && voisinCourant != *liste) {
		if (numeroVoisin(&voisinCourant) == voisin)
			trouve = true;
		voisinCourant = voisinSuivant(&voisinCourant);
	}
	return trouve;
}

/* Renvoie la représentation de la liste passée en paramètre sous la forme :
 (2/3), (4,6)  avec une liste comportant 2 voisins numérotés 2 et 4 et ayant pour poids 3 et 6
 fonctionne mais modifier ou pas ? (faire un malloc ? un realloc à la fin ?)*/
char* toString (TypVoisins** liste) {
	char *res, *tmp;
	TypVoisins* vC;
	res = malloc(256);
	tmp = malloc(256);
	
	vC = voisinSuivant(liste);
	sprintf(res,"(%d,%d)",numeroVoisin(&vC),poidsVoisin(&vC));
	
	vC = voisinSuivant(&vC);
	
	while (vC != *liste) {
		sprintf(tmp,", (%d,%d)",numeroVoisin(&vC),poidsVoisin(&vC));
		strcat(res,tmp);
		vC = voisinSuivant(&vC);
	}
	return res;
}
