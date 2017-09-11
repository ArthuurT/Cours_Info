#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define tmax 50


typedef struct element{char caract; struct element*suivant;} t_element;
t_element*pile;

void init_pile(){
	pile = NULL;
}

void empiler(int c){
	t_element*nouv;				//création d'un nouveau pointeur
	nouv = malloc(sizeof(t_element));	//qui point sur un nouvel élement dynamique
	nouv->caract = c;			//cet élément prend la valeur c
	nouv->suivant = pile;			//et pointe sur le sommet de la pile
	pile = nouv;				//donc le sommet de la pile change
}

void depiler(int*c){
	t_element*inter;			//création d'un pointeur intermediaire
	if(pile != NULL){
		*c = pile->caract;		//on recupère la valeur du sommet
		inter = pile;			//inter pointe sur le sommet de la pile
		pile = inter->suivant;		//pile pointe sur l'élement suivant
		free(inter);			//on supprime le sommet, qui devient l'élement suivant.
	}
		
}

void sommetpile(int*c){
	if(pile!=NULL){
		*c = pile->caract;
	}
		
}
