#include <stdio.h>
#include <stdlib.h>
#define N 20

int main(){
	int tab[N];
	int valeur = 0;
	int i = 0;
	int k;
	int j,a;
	while(valeur != -1){
		printf("Saisir un entier ou -1 pour terminer: ");
		scanf("%i",&valeur);
		if(valeur != -1){
			tab[i] = valeur;
			j = i;
			while(tab[j]<tab[j-1] && j>0){
				a = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = a;
				j--;
			}
			printf("Tableau trié: ");
			for(k=0;k<=i;k++){
				printf("%i ",tab[k]);
			}
			printf("\n");
		}
		i++;
	}
	printf("Merci et au revoir\n");
}