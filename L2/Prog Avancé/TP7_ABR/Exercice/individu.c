#include <individu.h>

/*
 * VARIABLES GLOCALES
 */

/* Compteur d'objets */
unsigned long int individu_cpt = 0 ; 

/* Compteur de comparaisons */
unsigned long int individu_comp = 0 ; 



/* 
 * FONCTIONS
 */

/*
 * Test existance 
 */
extern 
booleen_t individu_existe( const individu_t * individu )
{
  if( individu == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

/* 
 * Destruction  
 */
extern 
err_t individu_detruire( individu_t ** individu ) 
{

  /* 
   * l'Objet est detruit en profondeur 
   */
  /* Liberation attributs */
  free( (*individu)->nom ) ; 
  free( (*individu)->prenom ) ; 
  /* Liberation memoire de l'objet */
  free( (*individu) ) ;
  /* 
   * Sa reference est effacee 
   * Pour eviter les pointeurs fous 
   */
  (*individu) = NULL ; 

  individu_cpt-- ; 

  return(OK) ; 
}

extern 
err_t individu_detruire_cb( void * individu ) 
{
  return(individu_detruire( individu ) ) ; 
}

/*
 * Effacement 
 */

err_t individu_effacer( individu_t ** individu ) 
{
  /* 
   * l'Objet n'est pas detruit 
   */

  /* 
   * Sa reference est effacee 
   */
  
  (*individu) = NULL ; 

  individu_cpt-- ; 

  return(OK) ; 
}

extern 
err_t individu_effacer_cb( void * individu ) 
{
  return(individu_effacer( individu ) ) ; 
}

/*
 * Affichage 
 */

extern
void individu_afficher( const individu_t * individu ) 
{

  printf( "{" ) ; 
  if(  individu_existe(individu) ) 
    {
      printf( "%s %s" , individu->prenom , individu->nom ) ;
    }
  printf( "}" ) ; 
}

extern
void individu_afficher_cb( const void * individu ) 
{
  return(individu_afficher( individu ) ) ;
}

/*
 * Creation
 */
extern 
individu_t * individu_creer( const char * prenom , const char * nom ) 
{
  individu_t * individu = NULL ; 

  /* Creation place memoire objet individu */
  if( ( individu = malloc(sizeof(individu_t)) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation d'un objet de type individu_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(individu_t) ) ;
      return((individu_t *)NULL);
    }

  /* Affectation attributs specifiques */
  if( ( individu->nom = malloc( sizeof(char)*strlen(nom)+1) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation du nom d'un individu_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(char)*strlen(nom)+1 ) ;
      return((individu_t *)NULL);
    }

  if( ( individu->prenom = malloc( sizeof(char)*strlen(prenom)+1) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation du prenom d'un individu_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(char)*strlen(prenom)+1 ) ;
      return((individu_t *)NULL);
    }

  strcpy( individu->nom , nom ); 
  strcpy( individu->prenom , prenom ) ;
  
  individu_cpt++ ; 

  return( individu ) ;
}

/*
 * Comparaison 
 */

/* 
 * Comparaison de 2 pointeurs sur des individus 
 * 1 individu = individu_t * 
 * 1 pointeur sur 1 individu = individu_t ** 
 */
extern 
int individu_comparer( const individu_t * const * ind1 , const individu_t * const * ind2 ) 
{
  individu_comp++ ; 

  int cmp = strcmp( (*ind1)->nom , (*ind2)->nom )  ;
  if( cmp ) return(cmp); 
  return( strcmp( (*ind1)->prenom , (*ind2)->prenom ) ) ;
}

/* 
 * Fonction d'encapsulation (ou de callback) 
 * de comparauson de 2 individus 
 * destinee a etre utilisee par qsort 
 */
extern
int individu_comparer_cb( const void * ind1 , const void * ind2 )
{
  /* 
   * Le pointeur generique doit representer l'adresse d'un element 
   * ici un element = pointeur sur un individu 
   * donc void * --> individu_t ** 
   */
 
  return( individu_comparer( ind1 , ind2 ) ) ;
}

/*
 * Affectation d'un individu par reference 
 */

extern
err_t individu_referencer( individu_t ** ind_cible ,  individu_t * ind_source )
{
  (*ind_cible) = ind_source ; 
  return(OK) ; 
}


extern
err_t individu_referencer_cb( void * ind_cible ,  void * ind_source )
{
  return( individu_referencer( ind_cible , ind_source ) ) ; 
}


/*
 * Affectation d'un individu par copie 
 */

extern
err_t individu_copier( individu_t ** ind_cible ,  individu_t * ind_source )
{
  err_t noerr = OK ; 

  if( individu_existe( (*ind_cible) ) )
    {
      if( ( noerr = individu_detruire( ind_cible ) ) )
	return(noerr) ;
    }

  if( ! individu_existe( ind_source ) )
    return(OK) ; 

  if( ( (*ind_cible) = individu_creer( ind_source->nom , 
				       ind_source->prenom ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ; 

  return(OK) ; 
}

extern
err_t individu_copier_cb( void * ind_cible ,  void * ind_source )
{
  return( individu_copier( ind_cible , ind_source ) ) ; 
}

/*
 * Chargement d'un individu a partir d'un fichier 
 * L'individu est cree
 */

extern
err_t individu_charger( individu_t ** individu  , 
			FILE * restrict fd )
{
  char nom[MAX_STRING] ;
  char prenom[MAX_STRING] ;
  err_t noerr = OK ; 

  if( individu_existe( (*individu) ) )
    {
      if( ( noerr = individu_detruire( individu ) ) )
	return(noerr) ;
    }

  if( fscanf( fd , "%s %s" , nom ,  prenom ) != 2 ) 
    return(ERR_SCANF) ;

  if( ( (*individu) = individu_creer( nom , 
				      prenom ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ;  

  return(OK) ; 
}

extern
err_t individu_charger_cb( void * individu  , 
			   FILE * restrict fd )
{
  return(individu_charger( individu , fd ) ) ;
}


/*
 * Sauvegarde d'un individu dans un fichier 
 */

extern
err_t individu_sauver( individu_t * individu , 
		       FILE * restrict fd )
{
  if( ! individu_existe( individu ) )
    return(OK) ;

  fprintf( fd , "%s %s" , individu->nom , individu->prenom ) ;
  
  return(OK) ; 
}

extern
err_t individu_sauver_cb( void * individu , 
			  FILE * restrict fd )
{
  return(individu_sauver( individu , fd ) ) ; 
}
