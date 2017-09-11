//
//  Pascal.c
//  
//
//  Created by Claudine Piau-Toffolon on 19/10/2015.
//
//
#include <stdio.h>
#include <stdlib.h>

long fact (short nb)
{
    short indice;
    long factorielle_nb = 1;
    	for(indice = nb ; indice > 0; indice--)
        	factorielle_nb = factorielle_nb * indice;
		
	return factorielle_nb;
}	

int calculer_une_case (int c, int l)
{
    return (fact(c) / (fact(l) * fact(c - l)));
}

int main(int argc, char *argv[])
{
    int nb_lignes, i, j;
    
    if(argc != 2)
        exit(1);
    
    nb_lignes = atoi(argv[1]);
    
    i = 0;
    while(i <= nb_lignes){  // pour chaque ligne
        j = 0;
        while(j <= i){   // pour chaque colonne de la ligne
            printf("%2d ", calculer_une_case(i,j));
            j++;
        }
        printf("\n"); // retour a la ligne avant de traiter la ligne suivante
        i++;
    }
    
    return 0;
}
