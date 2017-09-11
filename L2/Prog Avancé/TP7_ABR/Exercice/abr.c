  #include <abr.h>

extern
noeud_t * abr_racine_lire( const abr_t * arbre )
{
  return (arbre->racine);
}

extern
err_t abr_racine_ecrire( abr_t * arbre ,
			noeud_t * racine )
{
  arbre->racine = racine;
  return(OK) ;
}

extern
int abr_taille_lire( const abr_t * arbre )
{
  return (arbre->taille);
}

extern
err_t abr_taille_incrementer( abr_t * arbre )
{
  (arbre->taille)++;
  return(OK);
}

extern
err_t abr_taille_decrementer( abr_t * arbre )
{
  (arbre->taille)--;
  return(OK);
}


/*
 * Tests
 */

extern
booleen_t abr_existe( const abr_t * arbre )
{
  if( arbre == NULL )
    return(FAUX) ;
  else
    return(VRAI) ;
}

extern
booleen_t abr_vide( const abr_t * arbre )
{
    if(arbre->racine == NULL) return (VRAI);
  	else return(FAUX) ;
}

/*
 * Creation
 */

extern
abr_t * abr_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
		   err_t (*fonction_destruction)( void * e) ,			/*!< Fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) )		/*!< Fonction de comparaison de 2 elements */
{
  abr_t * arbre = NULL ;

  arbre = malloc(sizeof(ab_t));
  arbre->taille = 0;
  arbre->racine = NULL;
  arbre->affecter = fonction_affectation;
  arbre->detruire = fonction_destruction;
  arbre->comparer = fonction_comparaison;

  return(arbre) ;
}


/*
 * Destruction
 */


extern
err_t abr_detruire( abr_t ** arbre )
{
  (*arbre)->detruire((*arbre)->racine);
  free(*arbre);
  (*arbre) = NULL;

  return(OK) ;
}

/*
 * Affichage
 */

 extern void ab_afficher_prefixe( const noeud_t * noeud , void (*fonction_affichage)(const void *), int profondeur){
   int i;
   for(i = 0; i < profondeur*profondeur; i++) printf(" ");
   printf("|");
   for(i = 0; i < profondeur*profondeur; i++) printf("-");
   fonction_affichage(noeud->etiquette);
   printf("\n");
   if(noeud_existe(noeud->gauche)) ab_afficher_prefixe(noeud->gauche, fonction_affichage, profondeur + 1);
   if(noeud_existe(noeud->droit)) ab_afficher_prefixe(noeud->droit, fonction_affichage, profondeur + 1);
 }




 static void ab_afficher_infixe( const noeud_t * noeud , void (*fonction_affichage)(const void *), int profondeur){
   int i;
   if(noeud_existe(noeud->gauche)) ab_afficher_infixe(noeud->gauche, fonction_affichage, profondeur + 1);
   for(i = 0; i < profondeur*profondeur; i++) printf(" ");
   printf("|");
   for(i = 0; i < profondeur*profondeur; i++) printf("-");
   fonction_affichage(noeud->etiquette);
   printf("\n");
   if(noeud_existe(noeud->droit)) ab_afficher_infixe(noeud->droit, fonction_affichage, profondeur + 1);
 }



 static void ab_afficher_postfixe( const noeud_t * noeud , void (*fonction_affichage)(const void *), int profondeur){
 	int i;
 	if(noeud_existe(noeud->gauche)) ab_afficher_postfixe(noeud->gauche, fonction_affichage, profondeur + 1);
 	if(noeud_existe(noeud->droit)) ab_afficher_postfixe(noeud->droit, fonction_affichage, profondeur + 1);
 	for(i = 0; i < profondeur*profondeur; i++) printf(" ");
   	printf("|");
   	for(i = 0; i < profondeur; i++) printf("-");
   	fonction_affichage(noeud->etiquette);
   	printf("\n");

 }


 extern void abr_afficher( const abr_t * arbre , void (*fonction_affichage)(const void *), ab_parcours_t type){
   if(arbre != NULL){
    if(type == PREFIXE ){
      ab_afficher_prefixe(arbre->racine,fonction_affichage,0);
    }
    else if(type == INFIXE) ab_afficher_infixe(arbre->racine,fonction_affichage,0);
    else if(type == POSTFIXE) ab_afficher_postfixe(arbre->racine,fonction_affichage,0);
  }
 }



/*
 * Insertion d'une valeur dans un ABR
 */

extern
err_t abr_inserer( abr_t * arbre  ,
		   void * etiquette )
{
  if(arbre == NULL) return ERR_ARBRE_NOEUD;

  noeud_t * noeud = noeud_creer(etiquette,NULL,NULL,arbre->affecter);
	noeud_inserer(noeud,&(arbre->racine),arbre->comparer,arbre->affecter);

  return (OK);
}

/*
 * Suppression d'une valeur dans un ABR
 */

static noeud_t * cherche_max( noeud_t * racine ){

	if( (noeud_sad_lire(racine)) == NULL) return racine;
	else return cherche_max(racine->droit);
}


static booleen_t abr_supprimer_bis(noeud_t ** noeud, void * etiquette, int (*comparer)(const void * e1, const void * e2), err_t (*supprimer)(void * e),err_t(*affecter)(void * e1, void * e2)){

 		noeud_t * res_noeud = NULL;
 		void * res_eti = NULL;

 		if((*noeud) != NULL){

 			/* Recherche de l'arbre */

			if((comparer(etiquette,(*noeud)->etiquette)) > 0) abr_supprimer_bis(&(*noeud)->droit,etiquette,comparer,supprimer,affecter);

			else if((comparer(etiquette,(*noeud)->etiquette)) < 0) abr_supprimer_bis(&(*noeud)->gauche,etiquette,comparer,supprimer,affecter);

			else{

				/* 0 fils */

				if((*noeud)->droit == NULL && (*noeud)->gauche == NULL) noeud_detruire(noeud,supprimer);

				/* 1 fils */

				else if((*noeud)-> droit == NULL && (*noeud)->gauche != NULL){
					affecter((*noeud)->etiquette,(*noeud)->gauche->etiquette);
					noeud_detruire(&(*noeud)->gauche,supprimer);

				}else if((*noeud)-> droit != NULL && (*noeud)->gauche == NULL){
					affecter((*noeud)->etiquette,(*noeud)->droit->etiquette);
					noeud_detruire(&(*noeud)->droit,supprimer);

				/* 2 fils */

				}else{
					res_noeud = cherche_max((*noeud)); 											/* On récupère le noeud max du sad */
					affecter(res_eti,res_noeud->etiquette);										/* On copie son étiquette */
					abr_supprimer_bis(noeud,res_noeud->etiquette,comparer,supprimer,affecter);			/* On supprime le noeud max */
					affecter((*noeud)->etiquette,res_eti) ;										/* On copie la valeur de l'étiquette du noeud max à la racine */
				}
				return (VRAI);
			}
		}
 		return (FAUX);
 }


extern booleen_t abr_supprimer( abr_t * arbre ,
			 void * etiquette )
{
  return abr_supprimer_bis(&arbre->racine,etiquette,arbre->comparer,arbre->detruire,arbre->affecter);
}

/*
 * Chargement d'un arbre a partir d'un fichier
 */

extern
err_t abr_charger( abr_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
		   char *  nom_fichier ,					    /* Nom du fichier de chargement */
		   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */
		   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
		   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) 	    /* Fonction de chargement d'un element */
{
  err_t noerr = OK ;
  FILE * fd = NULL ;
  void * etiquette = NULL ;

  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "abr_charger: ouverture en lecture du fichier %s impossible\n" ,
	       nom_fichier ) ;
      return(ERR_NOM_FICHIER) ;
    }

  /* Destruction de l'arbre si il existe deja */
  if( abr_existe( (*arbre) )  )
    {
      if( (noerr = abr_detruire( arbre ) ) )
	return(noerr) ;
    }

  /* Creation de l'arbre */
  if( ( (*arbre) = abr_creer( fonction_affectation ,
			      fonction_destruction ,
			      fonction_comparaison ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ;


  /* Lecture de la taille de l'arbre */
  int taille = 0 ;
  if( fscanf( fd , "%d\n" , &taille ) != 1 )
    {
      /* Pas d'element a charger */
      return(OK)  ;
    }

  /*
   * Chargement
   */
  while( ! feof(fd) )
    {
      /*
       * Lecture 1 ligne :  <etiquette>
       */

      if( (noerr = fonction_chargement( &etiquette , fd ) ) )
	{
	  if( feof(fd) )
	    continue ;
	  else
	    return(noerr) ;
	}

      /*
       * Insertion de la valeur dans l'arbre
       */

      if( ( noerr = abr_inserer( (*arbre) , etiquette ) ) )
	return(noerr ) ;

      if( ( noerr = fonction_destruction( &etiquette ) ) )
	return(noerr) ;

    }

  /* Fermeture */
  fclose(fd) ;

  return(OK) ;
}

/*
 * Sauvegarde d'un arbre dans un fichier
 */


static
err_t abr_sauver_bis( const noeud_t * racine ,
		     FILE * fd  ,						/* File descriptor du fichier de chargement */
		     err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;

  /*
   * Sauvegarde du noeud racine
   * Creation 1 ligne : <etiquette>
   */

  if( ! noeud_existe( racine ) )
    return(OK) ;

  if( (noerr = fonction_sauvegarde( noeud_etiquette_lire(racine) ,
				    fd ) ) )
    return(noerr) ;

  fprintf( fd , "\n" ) ;

  /*
   * Sauvegarde des noeuds dans les sous arbres gauche et droit
   */
  noeud_t * noeud_fg = noeud_sag_lire(racine) ;
  if( noeud_existe(noeud_fg) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fg ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ;
    }

  noeud_t * noeud_fd = noeud_sad_lire(racine) ;
  if( noeud_existe(noeud_fd) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fd ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ;
    }

  return(OK) ;
}

extern
err_t abr_sauver( const abr_t * arbre  ,						/* Arbre Binaire d'elements a charger */
		 char *  nom_fichier ,						/* Nom du fichier de chargement */
		 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;
  FILE * fd = NULL ;


  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "abr_sauver: ouverture en ecriture du fichier %s impossible\n" ,
	       nom_fichier ) ;
      return(ERR_NOM_FICHIER) ;
    }

  /* test si arbre vide */
  if( !abr_existe( arbre )  )
    return(OK);

  /*
   * Sauvegarde
   */

  /* Taille */
  fprintf( fd , "%d\n" , abr_taille_lire(arbre) ) ;

  /* Elements */

  if( ( noerr = abr_sauver_bis(  abr_racine_lire(arbre) , fd  ,fonction_sauvegarde ) ) )
    return(noerr) ;

  /* Fermeture */
  fclose(fd) ;

  return(OK) ;
}

/*
 * Recherche du pere d'un noeud dans un arbre
 */


static noeud_t * ab_pere_rechercher_bis( noeud_t * racine, const noeud_t * noeud_fils){
   	noeud_t * res;
   	if(racine == NULL) return NULL;
   	if(noeud_est_pere(racine,noeud_fils)) return racine;

   	if(racine->gauche != NULL){
   		if((res = ab_pere_rechercher_bis(racine->gauche,noeud_fils))) return res;
   	}
   	if(racine->droit != NULL){
   		return ab_pere_rechercher_bis(racine->droit,noeud_fils);
   	}else return NULL;
}

extern noeud_t * abr_pere_rechercher( const abr_t * arbre ,
			      const noeud_t * noeud_fils )
{
  return ab_pere_rechercher_bis(arbre->racine, noeud_fils);
}


/*
 * Recherche d'un element dans un arbre
 */


static booleen_t abr_rechercher_bis(noeud_t ** result,  noeud_t * noeud, const void * etiquette, int (*comparer) ( const void * e1 , const void * e2) ){
	if(noeud != NULL){
		if((comparer(etiquette,noeud->etiquette)) == 0){
			(*result) = noeud;
			return (VRAI);
		}
		else if((comparer(etiquette,noeud->etiquette)) > 0)
			return abr_rechercher_bis(result,noeud->droit,etiquette,comparer);
		else
			return abr_rechercher_bis(result,noeud->gauche,etiquette,comparer);
	}
	return (FAUX);
}





extern
booleen_t abr_rechercher(noeud_t ** result ,
			  const abr_t * arbre ,
			  const void * etiquette )
{
  (*result) = NULL ;
  return abr_rechercher_bis(result,arbre->racine,etiquette,arbre->comparer);
}
