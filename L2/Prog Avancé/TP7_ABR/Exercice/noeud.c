#include <noeud.h>

/* Etiquette */

extern
void * noeud_etiquette_lire( const noeud_t * noeud )
{
  	if(noeud != NULL) return (noeud->etiquette);
  	return NULL;
}

extern
err_t noeud_etiquette_ecrire( noeud_t * noeud ,
			      void * etiquette ,
			      err_t (*affecter)( void * e1 , void * e2 ) )
{
	if(noeud != NULL) return affecter(&(noeud->etiquette),etiquette);
	return ERR_ARBRE_NOEUD;
}

/* Sous arbre gauche */

extern
noeud_t * noeud_sag_lire( const noeud_t * noeud )
{
	if(noeud != NULL) return (noeud->gauche);
  	return(NULL) ;
}

extern
err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche )
{
	if(noeud != NULL) noeud->gauche = sous_arbre_gauche;
  	return(OK);
}

/* Sous arbre droit */

extern
noeud_t * noeud_sad_lire( const noeud_t * noeud )
{
	if(noeud != NULL) return (noeud->droit);
  	return(NULL);
}

extern
err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit )
{
  	if(noeud != NULL) noeud->droit = sous_arbre_droit;
  	return(OK);
}

/*
 * Existance ?
 */

booleen_t
noeud_existe( const noeud_t * noeud )
{
  	if(noeud == NULL) return(FAUX);
  	else return(VRAI);
}

/*
 * Feuille ?
 */
extern
booleen_t noeud_feuille( const noeud_t * noeud )
{
	if(noeud->gauche == NULL && noeud->droit == NULL) return (VRAI);
    return(FAUX);
}

/*
 * Parents ?
 */

extern
booleen_t noeud_est_pere( const noeud_t * noeud_pere ,
			  const noeud_t * noeud_fils )
{
	if(noeud_pere != NULL){
		if(noeud_pere->gauche == noeud_fils || noeud_pere->droit == noeud_fils) return (VRAI);
	}
 	return(FAUX) ;
}

/*
 * Creation
 */

extern
noeud_t * noeud_creer( void * etiquette ,
		       noeud_t * sous_arbre_gauche ,
		       noeud_t * sous_arbre_droit ,
		       err_t (*affecter)( void * e1 , void * e2 ) )
{
  	noeud_t * noeud = NULL;
  	noeud = malloc(sizeof(noeud_t));

  	noeud->etiquette = NULL;
  	noeud_etiquette_ecrire(noeud,etiquette,affecter);

  	noeud->gauche = sous_arbre_gauche;
  	noeud->droit = sous_arbre_droit;

  	return(noeud);
}

/*
 * Destruction d'un noeud
 */

extern
err_t noeud_detruire( noeud_t ** noeud ,
		      err_t (*detruire)( void * e) )
{
  	if(noeud_existe(*noeud)){
    	detruire(&(*noeud)->etiquette);
    	free(*noeud);
    	(*noeud) = NULL;
  	}
  	return(OK);
}

/*
 * Affichage
 */

extern
void noeud_afficher( const noeud_t * noeud ,
		     void (*afficher)(const void *) )
{
  	afficher(noeud->etiquette);
  	if(noeud_existe(noeud->gauche)) noeud_afficher(noeud->gauche, afficher);
  	if(noeud_existe(noeud->droit)) noeud_afficher(noeud->droit, afficher);
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

  if( ( noerr = sauver( noeud->etiquette , fd ) ) )
   return(noerr) ;

 return(OK) ;
}

/*
 * Recherches d'un noeud dans un arbre
 */

extern
booleen_t noeud_rechercher( const noeud_t ** result ,			 /* Resultat: @ du noeud trouve */
			    const noeud_t * racine  ,	         /* Racine de l'arbre de recherche */
			    const void * etiquette  ,		 /* Valeur a rechercher dans l'arbre */
			    int (*comparer)(const void * n1 , const void * n2) ) /* Fonction de comparaison des etiquettes */
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

/*
 * Insertion d'un noeud dans un ABR (aux feuilles)
 * Le noeud doit etre cree avec son etiquette
 */

extern
err_t noeud_inserer( noeud_t * noeud ,			          /* @ du noeud a inserer */
		     noeud_t ** racine  ,	                  /* Racine de l'arbre de recherche */
		     int (*comparer)(const void * n1 , const void * n2) ,     /* Fonction de comparaison des etiquettes */
		     err_t (*affecter)( void * e1 , void * e2 ) ) /* Fonction d'affectation des etiquettes */
{

int cmp = 0;

if(noeud == NULL) return ERR_ARBRE_NOEUD;

	/* Si le noeud n'est pas vide -> on cherche */

	if(*racine != NULL){

    /* !!!!!!!!!! BUS ERROR !!!!!!!!! */

    cmp = comparer(&(noeud->etiquette),&((*racine)->etiquette));

    /* !!!!!!!!!! BUS ERROR !!!!!!!!! */

    if(cmp > 0) return noeud_inserer(noeud,&((*racine)->droit),comparer,affecter); /* on cherche à droite */
    else if(cmp < 0) return noeud_inserer(noeud,&((*racine)->gauche),comparer,affecter); /* on cherche à gauche */
    else return ERR_ARBRE_NOEUD; /* déja présent */

	}

  /* si le noeud est vide -> on insère */

    (*racine) = noeud;

  	return(OK);
}


/*
 * Suppression d'un noeud dans un ABR
 * Renvoie VRAI si le noeud existait dans l'arbre
 *         FAUX sinon
 */


static noeud_t * cherche_max( noeud_t * racine ){

	if( (noeud_sad_lire(racine)) == NULL) return racine;
	else return cherche_max(racine->droit);
}

extern
booleen_t noeud_supprimer( void * etiquette ,			 /* valeur a supprimer de l'arbre */
			   noeud_t ** racine  ,	                  /* Racine de l'arbre de recherche */
			   err_t (*affecter)( void * e1 , void * e2 ) , /* Fonction d'affectation des etiquettes */
			   err_t (*detruire)( void * e ) , /* Fonction de destruction des etiquettes */
			   int (*comparer)(const void * n1 , const void * n2) )
{
	void * res_eti = NULL;
	noeud_t * res_noeud = NULL;

 		if((*racine) != NULL){

 			/* Recherche du noeud dans l'arbre */

			if((comparer(etiquette,(*racine)->etiquette)) > 0) noeud_supprimer(etiquette,&(*racine)->droit,affecter,detruire,comparer);

			else if((comparer(etiquette,(*racine)->etiquette)) < 0) noeud_supprimer(etiquette,&(*racine)->gauche,affecter,detruire,comparer);

			/* Si trouvé ... */

			else{

				/* 0 fils */

				if((*racine)->droit == NULL && (*racine)->gauche == NULL) noeud_detruire(racine,detruire);

				/* 1 fils */

				else if((*racine)-> droit == NULL && (*racine)->gauche != NULL){
					affecter((*racine)->etiquette,(*racine)->gauche->etiquette);
					noeud_detruire(&(*racine)->gauche,detruire);

				}else if((*racine)-> droit != NULL && (*racine)->gauche == NULL){
					affecter((*racine)->etiquette,(*racine)->droit->etiquette);
					noeud_detruire(&(*racine)->droit,detruire);

				/* 2 fils */

				}else{
					res_noeud = cherche_max((*racine)); 										/* On récupère le noeud max du sad */
					affecter(res_eti,res_noeud->etiquette);										/* On copie son étiquette */
					noeud_supprimer(res_noeud->etiquette,racine,affecter,detruire,comparer);		/* On supprime le noeud max */
					affecter((*racine)->etiquette,res_eti);										/* On copie la valeur de l'étiquette du noeud max à la racine */
				}
				return (VRAI);
			}
		}
 		return (FAUX);
}
