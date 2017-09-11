#include <stdlib.h>
#include <stdio.h>

void creer_fichier(){ //fonction qui créer un fichier au nom que souhaite l'utilisateur
	FILE * fic;	
	int entier;
	char nom[20];
	printf("Saisir le nom du fichier: ");
	scanf("%s",nom);
	fic = fopen(nom,"w");
	printf("rentrez une suite d'entier positifs: "); //et qui y rentre des entiers souhaités par l'utilisateur
	do{
		scanf("%i",&entier);
		if(entier>0){
			fprintf(fic,"%i ",entier);
		}
	}while(entier != -1);
	fclose(fic);
}

void afficher_fichier(){ //fonction qui affiche le contenu d'un fichier souhaité
	FILE * fic;
	int entier;
	char nom[20];
	printf("Saisir le nom du fichier: ");
	scanf("%s",nom);
	fic = fopen(nom,"r");
	while(fic == 0){
		printf("nom de fichier inconnu, veuillez réessayer: ");
		scanf("%s",nom);
		fic = fopen(nom,"r");
	}	
	fscanf(fic,"%i",&entier);
	while(!feof(fic)){
		printf("%i ",entier);
		fscanf(fic,"%i",&entier);
	}
	printf("\n");
	fclose(fic);
}


int main(){
	creer_fichier();
	afficher_fichier();
}