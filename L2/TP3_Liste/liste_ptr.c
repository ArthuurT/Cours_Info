#include<stdlib.h>
#include<stdio.h>
typedef struct element {int valeur; struct element * pred; struct element * succ;}t_element;
t_element * drapeau;
t_element * ec;

void init_liste(void)
/* Initialise la liste � vide */
{	
	drapeau = malloc(sizeof(t_element));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}
int liste_vide(void)
/* Rend vrai si la liste est vide, faux sinon */
{	
	return (drapeau->succ == drapeau);
}

int hors_liste(void)
/* Rend vrai si l'elt courant est hors de la liste, faux sinon */
{	
	return (ec == drapeau);
}

void en_tete(void)
/* Positionne en tete de la liste */
{	
	if(!liste_vide())
		ec = drapeau->succ;
}

void en_queue(void)
/* Positionne en queue de la liste */
{	
	if(!liste_vide())
		ec = drapeau->pred;
}

void precedent(void)
/* Positionne sur l'elt precedent*/
{	
	if(!hors_liste()) 
		ec = ec->pred;
}

void suivant(void)
/* Positionne sur l'elt suivant*/
{	
	if(!hors_liste()) 
		ec = ec->succ;
}

void valeur_elt(int* v)
/* Renvoie dans e la veleur de l'elt courant */
{	
	if(!hors_liste()) 
		*v = ec->valeur;
}

void modif_elt(int v)
/* Affecte v � l'elt courant */
{	
	if(!hors_liste()) 
		ec->valeur = v;
}

void oter_elt(void)
/* Supprime l'elt courant et positionne sur le precedent */
{	
	t_element * old;

	if(!hors_liste())
	{	
		old = ec;
		(ec->pred)->succ = ec->succ;
		(ec->succ)->pred = ec->pred;
		ec=ec->pred;
		free(old);
		
	}
}

void ajout_droit(int v)
/* Ajoute v a droite de l'elt courant */
{	
	t_element * nouv;

	if(!hors_liste() || liste_vide())
	{
		nouv = malloc(sizeof(t_element));

		nouv->valeur = v;
		nouv->succ = ec->succ;
		nouv->pred = ec;
		
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		
		ec = nouv;
		
	}
		
}

void ajout_gauche(int v)
/* Ajoute v a gauche de l'elt courant */
{	
	t_element * nouv;

	if(!hors_liste() || liste_vide())
	{
		nouv = malloc(sizeof(t_element));

		nouv->valeur = v;
		nouv->pred = ec->pred;
		nouv->succ = ec;

		(ec->pred)->succ = nouv;
		ec->pred = nouv;
	
		ec = nouv;
		
	}
}
 
