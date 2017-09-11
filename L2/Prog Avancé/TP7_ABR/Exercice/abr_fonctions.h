#include <abr.h>
#include <liste.h>

/*
 * Affichage des ancetres d'un noeud
 */

extern
void abr_ancetres_afficher( const abr_t * arbre , 
			    noeud_t * noeud ,
			    void (*afficher)(const void *) ) ;
/* 
 * Creation d'un arbre binaire de travail par dichotomie 
 * a partir d'un tableau d'elements generiques
 */

extern
err_t abr_dicho_creer( abr_t ** arbre , 
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	
		       err_t (*fonction_destruction)( void * e) ,			
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste ) ;
