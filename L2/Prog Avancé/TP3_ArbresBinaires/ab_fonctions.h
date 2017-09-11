#include <ab.h>

/*
 * Affichage des ancetres d'un noeud
 */

extern
void ab_ancetres_afficher( const ab_t * arbre , 
			   noeud_t * noeud ,
			   void (*afficher)(const void *) ) ;
