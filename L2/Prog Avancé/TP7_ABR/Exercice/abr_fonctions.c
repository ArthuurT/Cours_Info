#include <abr_fonctions.h>

/*
 * Affichage des ancetres d'un noeud
 */

extern
void abr_ancetres_afficher( const abr_t * arbre ,
			    noeud_t * noeud ,
			    void (*afficher)(const void *) )
{
  	noeud_t * res;
 		res = abr_pere_rechercher(arbre, noeud);
 		if(res != NULL){
 			afficher(res->etiquette);
			printf("\n");
 			abr_ancetres_afficher(arbre,res,afficher);
 		}
}

/*
 * Creation d'un arbre binaire de travail par dichotomie
 * a partir d'une liste d'elements generiques
 */

static err_t abr_dicho_creer_bis( abr_t ** arbre ,
		       liste_t * liste ,
					 int debut,
				 	 int fin)
{

	if(debut <= fin){

		int milieu = (debut + fin) / 2 ;
		void * elem = NULL;

		/* on ajoute l'élément du milieu de la liste dans l'ABR */

		elem = liste_elem_lire(liste,milieu);
		abr_inserer(*arbre,elem);

		/* Recursivité sag / sad */

		abr_dicho_creer_bis(arbre,liste,debut,milieu-1);
		abr_dicho_creer_bis(arbre,liste,milieu+1,fin);


	}

	return (OK);

}

extern
err_t abr_dicho_creer( abr_t ** arbre ,
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,
		       err_t (*fonction_destruction)( void * e) ,
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste)
{

	if(*arbre == NULL) *arbre = abr_creer(fonction_affectation,fonction_destruction,fonction_comparaison);
	abr_dicho_creer_bis(arbre,liste,0,((*liste).nb)-1);

  return(OK) ;
}
