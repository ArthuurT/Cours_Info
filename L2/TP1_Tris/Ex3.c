#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(){
	char T[N][20]={0};
	char mot[20]={0};
	int P[N]={0};
	char Tbis[N][20]={0};
	int i=0;
	int j;
	int nb_valeurs = 0;

	while(strcmp(mot,"##") != 0){
		printf("Entrer un mot: ");
		scanf("%s",mot);
		if(strcmp(mot,"##") != 0){
			strcpy(T[i],mot);
			i++;
			nb_valeurs++;
		}
	}
	
	for(i = 0; i < nb_valeurs; i++){
		P[i] = 0;
		for(j = 0; j < nb_valeurs; j++){
			if(strcmp(T[j],T[i]) < 0 || (strcmp(T[j],T[i]) == 0 && j<i)){
				P[i]++;
			}
		}
	}

	for(i = 0; i < nb_valeurs; i++){
		strcpy(Tbis[P[i]],T[i]);
	}
	
	printf("Tableau des positions: \n");
	for(i = 0; i < nb_valeurs; i++){
		printf("\nmot:%s position:%i\n ",T[i],P[i]);
	}
	
	printf("\n");
	printf("Mots triés: \n");
	for(i = 0; i < nb_valeurs; i++){
		printf("\n%s\n",Tbis[i]);
	
	}

	
}