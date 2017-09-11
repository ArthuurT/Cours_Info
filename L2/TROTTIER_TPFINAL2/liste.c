/* TP 4 - Mise en oeuvre d'une liste de doublets */

#include<stdio.h>
#include<stdlib.h>
#include "liste.h"


/* Definition du type d'un element de liste */
typedef struct element {t_doublet valeur; struct element* pred; struct element* succ;} t_element;

/* Declaration des listes (drapeau et element courant) */
t_element* drapeau;
t_element* ec;


/* Primitives de manipulation des listes */

void init_liste(){

		drapeau = malloc(sizeof(t_element));
		drapeau->pred = drapeau;
		drapeau->succ = drapeau;
		ec = drapeau;
}


int liste_vide(){

		return drapeau->pred==drapeau;
}


int hors_liste(){

		return ec==drapeau;
}


void en_tete(){

		if (!liste_vide())
			ec = drapeau->succ;
}


void en_queue(){

		if (!liste_vide())
			ec = drapeau->pred;
}


void precedent(){

		if (!hors_liste())
			ec = ec->pred;
}


void suivant(){

		if (!hors_liste())
			ec = ec->succ;
}


void valeur_elt(t_doublet* d){

		if (!hors_liste())
			*d = ec->valeur;
}


void modif_elt(t_doublet d){

		if (!hors_liste())
			ec->valeur = d;
}


void oter_elt(){

	t_element * tmp;

	if (!hors_liste()){
		(ec->succ)->pred = ec->pred;
		(ec->pred)->succ = ec->succ;
		tmp = ec;
		ec = ec->pred;
		free(tmp);
	}
}

void ajout_droit(t_doublet d){

	t_element* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(t_element));
		nouv->valeur = d;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		ec = nouv;
	}
}


void ajout_gauche(t_doublet d){

	t_element* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(t_element));
		nouv->valeur = d;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		ec = nouv;
	}
}
