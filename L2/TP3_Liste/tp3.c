#include<stdio.h>
#include<stdlib.h>
#include "liste.h"

/* Fonctions de manipulation de la liste */

void afficher(void)
/* Affiche les valeurs de la liste */
{
	int elem;

	if(liste_vide())
		printf("La liste est vide\n");
	else
	{
		printf("\nLa liste contient: ");
		en_tete();
		while(!hors_liste())
		{
			valeur_elt(&elem);
			printf("%i ",elem);
			suivant();
		}
		printf("\n");
	}
}

void inserer(void)
/* Insere un élément dans la liste */
{
	int a, b;
	int ajout = 0;
	printf("Saisir un entier pour le remplacer: ");
	scanf("%i",&a);
	en_queue();
	while(!hors_liste() && ajout == 0){
		valeur_elt(&b);
		if(b<=a){
			ajout_droit(a);
			ajout=1;
		}else precedent();
	}
	if(ajout==0){
		en_tete();
		ajout_gauche(a);
	}
}

void inserer_remplacer(void)
/* Insere un élément dans la liste */
{
	int a, b;
	int ajout = 0;
	printf("Saisir un entier pour le remplacer: ");
	scanf("%i",&a);
	en_queue();
	while(!hors_liste() && ajout == 0){
		valeur_elt(&b);
		if(b<=a){
			ajout_droit(a);
			ajout=1;
		}else precedent();
	}
	if(ajout==0){
		en_tete();
		ajout_gauche(a);
	}
}

void supprimer(void)
/* Supprime toutes les occurrences d'un entier lu au clavier */
{
	int a,b;
	int marque = 0;
	printf("Saisir un entier: ");
	scanf("%i",&a);
	en_queue();
	while(!hors_liste()){
		valeur_elt(&b);
		if(b==a){
			oter_elt();
			marque = 1;
		}else precedent();
	}
	if(marque == 0)
		printf("Cette valeur n'est pas comprise dans la liste");
}

void afficher_multiples(void)
/* Affiche tous les multiples d'une valeur lue au clavier */
{	
	int a,b;
	printf("Saisir un entier: ");
	scanf("%i",&a);
	en_queue();
	printf("Les multiples de %i qui sont dans la liste sont: ",a);
	while(!hors_liste()){
		valeur_elt(&b);
		if((b%a)==0){
			printf("%i ",b);
		}
	precedent();
	}
	
}

void vider_liste(void)
/* Supprime tous les éléments de la liste */
{
	en_queue();
	while(!hors_liste()){
		oter_elt();
	}
}

void remplacer(){
	int b, n1, n2;
	printf("Saisir la valeur du nombre à changer: ");
	scanf("%i",&n1);
	en_queue();
	while(!hors_liste()){
		valeur_elt(&b);
		if(b == n1){
			oter_elt();
			inserer_remplacer();
		}
	precedent();
	}
}


/*	Programme principal */
int main(void)
{	int choix;

/* Initialisation de la liste d'entiers */
	init_liste();

	do
/* Affichage du menu et saisie du choix */
	{	printf("\nMenu :\n");
		printf(" 1 - Inserer une valeur\n");
		printf(" 2 - Supprimer une valeur\n");
		printf(" 3 - Afficher les multiples\n");
		printf(" 4 - Vider la liste\n");
		printf(" 5 - Remplacer un nombre par un autre\n");
		printf(" 6 - Trier liste\n");
		printf(" 7 - Quitter\n");
		printf("Votre choix : ");
		scanf("%d",&choix);

/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1: inserer();  afficher(); break;
			case 2: supprimer(); afficher(); break;
			case 3: afficher_multiples(); afficher(); break;
			case 4: vider_liste(); afficher(); break;
			case 5: remplacer(); afficher(); break;
			case 6: 
			case 7: break;
			default: printf("Erreur: votre choix doit ê5tre compris entre 1 et 5\n");
		}
	}
	while(choix!=7);

	printf("Au revoir !\n");
	return EXIT_SUCCESS;
}

