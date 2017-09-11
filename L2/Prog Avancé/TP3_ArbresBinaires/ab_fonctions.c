#include <ab_fonctions.h>

/*
 * Affichage des ancetres d'un noeud
 */

extern
void ab_ancetres_afficher( const ab_t * arbre , 
			   noeud_t * noeud ,
			   void (*afficher)(const void *) )
{
		noeud_t * res;
 		res = ab_pere_rechercher(arbre, noeud);
 		if(noeud_existe(res)){
 			afficher(res->etiquette);
			printf("\n");
 			ab_ancetres_afficher(arbre,res,afficher);
 	}
}

