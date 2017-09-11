#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(){
	char mot[N];
	int taille;
	int i,j,imin;
	char a;
	int compteur;
	printf("Entrer un mot: ");
	scanf("%s",mot);
	taille = strlen(mot);

	for(i = 0; i < taille; i++){
		imin = i;
		for(j=i+1; j < taille; j++){
			if(mot[j] < mot[imin]){
				imin = j;
			}
		}
		a = mot[i];
		mot[i] = mot[imin];
		mot[imin] = a;
		printf("Mot trié: %s",mot);
		printf("\n");
	}
}