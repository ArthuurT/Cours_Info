#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE * fic;
	int nb_carac = 0;
	int nb_mots = 1;
	int nb_lignes = 1;
	char nom[20];
	char caractere;
	printf("Saisir le nom du fichier: ");
	scanf("%s",nom);
	fic = fopen(nom,"r");

	while(fic == 0){
		printf("nom de fichier inconnu, veuillez réessayer: ");
		scanf("%s",nom);
		fic = fopen(nom,"r");
	}
	fscanf(fic,"%c",&caractere);
	while(!feof(fic)){
		if(caractere == ' ' || caractere == '\n'){
			nb_mots++;
		}
		if(caractere == '\n'){
			nb_lignes++;
		}
		if(caractere != '\n'){
			nb_carac++;
	
		}
		fscanf(fic,"%c",&caractere);
	}
	printf(" le fichier contient %i caractères, %i mots et %i lignes \n",nb_carac,nb_mots,nb_lignes);
	fclose(fic);
}
		

	
