//
//  factorielle.c
//  
//
//  Created by Claudine Piau-Toffolon on 19/10/2015.
//./
//

#include <stdio.h>
#include <stdlib.h>
long fact (short nb)
{
    short indice;
    long factorielle_nb =1;
    for (indice = nb; indice >0; indice --)
        factorielle_nb = factorielle_nb * indice;
    return factorielle_nb;
}


void testfact (int valeur){
	int resultat;
	if(valeur == 0){
		resultat = fact(valeur);
		if(resultat != 1){
			printf("Le test a raté\n");
		}
	}
	if(valeur == 1){
		resultat = fact(valeur);
		if(resultat != 1){
			printf("Le test a raté\n");
		}
	}
	if(valeur == 2){
		resultat = fact(valeur);
		if(resultat != 2){
			printf("Le test a raté\n");
		}
	}
	if(valeur == 3){
		resultat = fact(valeur);
		if(resultat != 6){
			printf("Le test a raté\n");
		}
	}
}

int main (int argc, char *argv[])
{
    short nb_lu;
    if (argc !=2)
        exit(1);
    nb_lu = (short)atoi(argv[1]);
	testfact(nb_lu);
	if(nb_lu > 0 && nb_lu < 26){
   		printf("factorielle de %2hd = %ld\n", nb_lu, fact(nb_lu));
    		return 0;
	}else printf("Erreur car valeur impossible\n");
}
