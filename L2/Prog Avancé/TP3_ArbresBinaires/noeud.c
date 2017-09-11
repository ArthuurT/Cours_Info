#include <noeud.h>

/*
 * Existance ?
 */

booleen_t noeud_existe( const noeud_t * noeud ){
  if(noeud == NULL) return(FAUX) ;
  else return(VRAI);
}

/* Numero */

extern int noeud_numero_lire( const noeud_t * noeud ){
  return (noeud->numero);
}

extern err_t noeud_numero_ecrire( noeud_t * noeud , const int numero ){
  if(noeud_existe(noeud)) noeud->numero = numero;
  return(OK) ;
}

/* Etiquette */

extern void * noeud_etiquette_lire( const noeud_t * noeud ){
  return (noeud->etiquette);
}

extern err_t noeud_etiquette_ecrire( noeud_t * noeud , void * etiquette , err_t (*affecter)( void * e1 , void * e2 ) ){
  if(noeud != NULL) return affecter(&(noeud->etiquette), etiquette);

	return ERR_NOEUD_INEXISTANT;
}

/* Sous arbre gauche */

extern noeud_t * noeud_sag_lire( const noeud_t * noeud ){
  return (noeud->gauche);
}

extern err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche ){
  if(noeud_existe(noeud)) noeud->gauche = sous_arbre_gauche;
  return(OK) ;
}

/* Sous arbre droit */

extern noeud_t * noeud_sad_lire( const noeud_t * noeud ){
  return (noeud->droit);
}

extern err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit ){
  if(noeud_existe(noeud)) noeud->droit = sous_arbre_droit;
  return(OK) ;
}

/*
 * Feuille ?
 */

extern booleen_t noeud_feuille( const noeud_t * noeud ){
  if(noeud->gauche == NULL && noeud->droit == NULL) return (VRAI);
  else return(FAUX);
}

/*
 * Parents ?
 */

extern booleen_t noeud_est_pere( const noeud_t * noeud_pere , const noeud_t * noeud_fils ){
  if(noeud_fils == noeud_pere->gauche || noeud_fils == noeud_pere->droit) return(VRAI);
  else return(FAUX) ;
}

/*
 * Creation
 */

extern noeud_t * noeud_creer( const int numero , void * etiquette , noeud_t * sous_arbre_gauche , noeud_t * sous_arbre_droit , err_t (*affecter)( void * e1 , void * e2 ) ){
  noeud_t * noeud = NULL ;
  noeud = malloc(sizeof(noeud_t));
  noeud->etiquette = NULL;
  noeud->numero = numero;
  affecter(&(noeud->etiquette),etiquette);
  noeud->gauche = sous_arbre_gauche;
  noeud->droit = sous_arbre_droit;
  return(noeud) ;
}

/*
 * Destruction
 */

extern err_t noeud_detruire( noeud_t ** noeud , err_t (*detruire)( void * e) ){
  if(noeud_existe(*noeud)){
    detruire(&(*noeud)->etiquette);
    free(*noeud);
    (*noeud) = NULL;
  }
  return(OK) ;
}

/*
 * Affichage
 */

extern
void noeud_afficher( const noeud_t * noeud , void (*afficher)(const void *), int profondeur)
{
  int i;
  for(i = 0; i < profondeur; i++) printf("  ");
  afficher(noeud->etiquette);
  printf(",");
  if(noeud_existe(noeud->gauche)) noeud_afficher(noeud->gauche, afficher, profondeur + 1);
  if(noeud_existe(noeud->droit)) noeud_afficher(noeud->droit, afficher, profondeur + 1);
}

/*
 * Sauvegarde dans un fichier
 */

extern
err_t noeud_fd_sauver( noeud_t * noeud  ,	                  /* Noeud a sauvegarder */
		       FILE * fd , 		                  /* Descripteur fichier  */
		       err_t (*sauver)( void * e, FILE *  desc) ) /* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;

  if( ! noeud_existe( noeud ) )
    return(OK) ;

  fprintf( fd , "%d " , noeud->numero ) ;
  noeud_t * fils_gauche  = noeud_sag_lire( noeud ) ;
  noeud_t * fils_droit   = noeud_sad_lire( noeud ) ;

  if( noeud_existe( fils_gauche ) )
    fprintf( fd , "%d " ,  noeud_numero_lire(fils_gauche) ) ;
  else
    fprintf( fd , "-1 " ) ;

  if( noeud_existe( fils_droit ) )
    fprintf( fd , "%d " ,  noeud_numero_lire(fils_droit) ) ;
  else
    fprintf( fd , "-1 " ) ;

  if( ( noerr = sauver( noeud->etiquette , fd ) ) )
    return(noerr) ;

  return(OK) ;
}

/*
 * Recherches d'un noeud dans un arbre
 */


/* Sur le numero */

extern booleen_t noeud_numero_rechercher(noeud_t ** result, noeud_t * racine, const int numero){
	if(racine != NULL){

		if(racine->numero == numero){
			(*result) = racine;
			return (VRAI);
		}

		return noeud_numero_rechercher(result, racine->gauche, numero) || noeud_numero_rechercher(result, racine->droit, numero);
	}
	return (FAUX);
}


/* Sur l'etiquette */

extern booleen_t noeud_rechercher( noeud_t ** result ,			 /* Resultat: @ du noeud trouve */
			    noeud_t * racine  ,	         /* Racine de l'arbre de recherche */
			    void * etiquette     ,		 /* Valeur a rechercher dans l'arbre */
			    int (*comparer)(void * n1 , void * n2) ) /* Fonction de comparaison des etiquettes */
{
    if(noeud_existe(racine)){
        if(comparer(racine->etiquette,etiquette) == 0){
          return (VRAI);
          (*result) = racine;
        }
        else if((noeud_rechercher(result,racine->droit,etiquette,comparer))) return (VRAI);
        else return (noeud_rechercher(result,racine->gauche,etiquette,comparer));
    }
    return(FAUX) ;
}
