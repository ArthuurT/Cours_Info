/* TP 4 serie statistique */

#include<stdio.h>
#include<stdlib.h>
#include "liste.h"

#define TRUE 1
#define FALSE 0

void afficher()
{
  t_doublet a;
  int i;
  en_tete();
  while(!hors_liste()){
    valeur_elt(&a);
    for(i = 0; i < a.nb_occ; i++){
      printf("%i ",a.valeur);
    }
    suivant();
  }
}

void ajout()
{
  t_doublet entier;
  t_doublet a;
  int est_present = 0;
  printf("Saisir la valeur à ajouter: ");
  scanf("%i",&(entier.valeur));
  en_tete();
  valeur_elt(&a);
  while(!hors_liste() && a.valeur <= entier.valeur){
    if(entier.valeur == a.valeur){
      (a.nb_occ)++;
      modif_elt(a);
    }
    valeur_elt(&a);
    suivant();

  }

  if(hors_liste()){
    en_queue();
    entier.nb_occ=1;
    ajout_droit(entier);
  }else{
    entier.nb_occ=1;
    ajout_gauche(entier);
  }
}

void moyenne()
{
  t_doublet a;
  int nb_valeur;
  int total = 0;
  float res = 0;
  en_tete();
  while(!hors_liste()){
    valeur_elt(&a);
    total = total + (a.valeur)*(a.nb_occ);
    nb_valeur = nb_valeur + a.nb_occ;
    suivant();
  }
  res = total / nb_valeur;
  printf("moyenne = %.2f\n",res);
}

void rang_n()
{
  t_doublet a;
  int n;
  int compteur = 0;

  printf("Saisir un rang: ");
  scanf("%i",&n);
  en_tete();
  while(!hors_liste() && compteur < n){
    valeur_elt(&a);
    compteur = compteur + a.nb_occ;
    if(compteur >= n){
      printf("La valeur de rang n est: %i\n",a.valeur);
    }
    else suivant();
  }
  if(hors_liste()){
    printf("Le rang indiqué n'existe pas\n");
  }

}



void vider()
{
  en_queue();
  while(!hors_liste() && !liste_vide()){
    oter_elt();
  }
}

/*	Programme principal */
int main(void)
{
  	int choix;

/* Initialisation de la liste */
	init_liste();

/* Affichage du menu et saisie du choix */
	do
	{	printf("\nMenu :\n");
		printf(" 1 - Ajouter une valeur\n");
		printf(" 2 - Calculer la moyenne\n");
		printf(" 3 - Valeur de rang n\n");
		printf(" 4 - Vider la liste\n");
		printf(" 5 - Quitter\n");
		printf("Votre choix : ");
		scanf("%d",&choix);

/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1: ajout();		afficher(); break;
			case 2: moyenne();	afficher(); break;
			case 3: rang_n();	afficher(); break;
			case 4: vider();		afficher(); break;
			case 5: break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
		}
	}
	while(choix!=5);
	printf("Au revoir !\n");
	return EXIT_SUCCESS;
}
