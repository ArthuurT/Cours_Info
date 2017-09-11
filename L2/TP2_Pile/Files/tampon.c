#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "file.h"

int main(){

	int nombre,queue;
	init_file();
	int b;
	printf("Donner un nombre: ");
	scanf("%i",&nombre);
	while(nombre != -1){
		
		if(nombre != 0)	
			ajouter(nombre);
		else{
			while(!file_vide()){
				retirer(&b);
				printf("%i ",b);
			}
			printf("\n");
		}
		printf("Donner un nombre: ");
		scanf("%i",&nombre);
	}

}
