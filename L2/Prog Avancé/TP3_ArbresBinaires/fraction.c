#include <fraction.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int fraction_cpt = 0 ; 

/* 
 * FONCTIONS
 */

extern 
booleen_t fraction_existe( const fraction_t * fraction )
{
  if( fraction == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

/*
 * Destruction 
 */
extern
err_t fraction_detruire( fraction_t ** fraction ) 
{

  /* Liberation attributs */
  /* Liberation memoire de l'objet */
  free( (*fraction) ) ;
  /* Pour eviter les pointeurs fous */
  (*fraction) = NULL ; 

  fraction_cpt-- ; 

  return(OK) ; 
}

extern
err_t fraction_detruire_cb( void * fraction ) 
{
  return(fraction_detruire( fraction ))  ;
}

/*
 * Effacement 
 */ 
extern
err_t fraction_effacer( fraction_t ** fraction ) 
{
  /* 
   * l'Objet n'est pas detruit 
   * Sa reference est effacee 
   */
  
  (*fraction) = NULL ; 

  fraction_cpt-- ; 

  return(OK) ; 
}

extern 
err_t fraction_effacer_cb( void * fraction ) 
{
  return(fraction_effacer( fraction ) ) ; 
}


/* 
 * Affichage 
 */

extern
void fraction_afficher( const fraction_t * fraction ) 
{

  printf( "{" ) ; 
  if(  fraction_existe(fraction) ) 
    {
      printf( "%d/%d" , fraction->numerateur , fraction->denominateur ) ;
    }
  printf( "}" ) ; 
}

extern
void fraction_afficher_cb( const void * fraction )
{
  return(fraction_afficher((fraction_t*)fraction)) ;
}

/*
 * Creation 
 */

extern 
fraction_t * fraction_creer( const int numerateur , const int denominateur ) 
{
  fraction_t * fraction = NULL ; 

  /* Creation place memoire objet fraction */
  if( ( fraction = malloc(sizeof(fraction_t)) ) == NULL )
    {
      fprintf( stderr , "fraction_creer: debordement memoire lors de la creation d'un objet de type fraction_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(fraction_t) ) ;
      return((fraction_t *)NULL);
    }

  /* Affectation attributs specifiques */
  fraction->numerateur = numerateur; 
  fraction->denominateur = denominateur ;
  
  fraction_cpt++ ; 

  return( fraction ) ;
}

/* 
 * Comparaison 
 */
extern
int fraction_comparer( const fraction_t * const f1 , const fraction_t * const f2 ) 
{
  float r1 = (float) f1->numerateur / f1->denominateur  ; 
  float r2 = (float) f2->numerateur / f2->denominateur  ; 
  if( r1 == r2 ) return(0) ; 
  if( r1 > r2 )  return(1) ; 
  return(-1) ;   
}

/* 
 * Fonction d'encapsulation (ou de callback) 
 * de comparaison de 2 fractions
 * destinee a etre utilisee par qsort 
 */
extern
int fraction_comparer_cb( const void * f1 , const void * f2 ) 
{
  /* 
   * Le pointeur generique doit representer l'adresse d'un element 
   * ici un element = pointeur sur une fraction
   * donc void * --> fraction_t ** 
   */
  const fraction_t * const * f1_cb = f1 ; 
  const fraction_t * const * f2_cb = f2 ; 
  return( fraction_comparer( *f1_cb , *f2_cb ) ) ;
}

/*
 * Affectation d'une fraction par reference 
 */

extern
err_t fraction_referencer( fraction_t ** frac_cible ,  fraction_t * frac_source )
{
  (*frac_cible) = frac_source ; 
  return(OK) ; 
}


extern
err_t fraction_referencer_cb( void * frac_cible ,  void * frac_source )
{
 
  return( fraction_referencer( frac_cible , frac_source ) ) ; 
}


/*
 * Affectation d'une fraction par copie 
 */

extern
err_t fraction_copier( fraction_t ** frac_cible ,  fraction_t * frac_source )
{
  err_t noerr = OK ; 

  if( fraction_existe( (*frac_cible) ) )
    {
      if( ( noerr = fraction_detruire( frac_cible ) ) )
	return(noerr) ;
    }

  if( ! fraction_existe( frac_source ) )
    return(OK) ; 

  if( ( (*frac_cible) = fraction_creer( frac_source->numerateur , 
					frac_source->denominateur ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ; 

  return(OK) ; 
}


extern
err_t fraction_copier_cb( void * frac_cible ,  void * frac_source )
{
  return( fraction_copier( frac_cible , frac_source ) ) ; 
}

/*
 * Chargement d'une fraction a partir d'un fichier 
 * La fraction est creee
 */

extern
err_t fraction_charger( fraction_t ** fraction ,
			FILE * restrict fd )
{
  int numerateur ; 
  int denominateur ;
  err_t noerr = OK ; 

  if( fraction_existe( (*fraction) ) )
    {
      if( ( noerr = fraction_detruire( fraction ) ) )
	return(noerr) ;
    }

  if( fscanf( fd , "%d %d" , &numerateur , &denominateur ) != 2 ) 
    return(ERR_SCANF) ;

  if( ( (*fraction) = fraction_creer( numerateur , 
				      denominateur ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ;  

  return(OK) ; 
}

extern
err_t fraction_charger_cb( void * fraction ,
			   FILE * restrict fd )
{
  return(fraction_charger( fraction , fd ) ) ;
}

/*
 * Sauvegarde d'une fraction dans un fichier 
 */

extern
err_t fraction_sauver( fraction_t * fraction  , 
		       FILE * restrict fd )
{
  if( ! fraction_existe( fraction ) )
    return(OK) ;

  fprintf( fd , "%d %d" , fraction->numerateur , fraction->denominateur ) ;
  
  return(OK) ; 
}

extern
err_t fraction_sauver_cb( void * fraction , 
			  FILE * restrict fd )
{
  return( fraction_sauver( fraction  , fd ) ) ; 
}
