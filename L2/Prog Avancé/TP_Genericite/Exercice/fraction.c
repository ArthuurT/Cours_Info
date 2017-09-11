#include <stdlib.h>
#include <string.h>
#include <fraction.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int fraction_cpt = 0 ;

/*
 * FONCTIONS
 */

/*
 * Test d'existance
 */

extern
booleen_t fraction_existe( fraction_t * const fraction )
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

/*
 * Affichage
 */
extern
void fraction_afficher( fraction_t * const fraction )
{

  printf( "{" ) ;
  if(  fraction_existe(fraction) )
    {
      printf( "%d/%d" , fraction->numerateur , fraction->denominateur ) ;
    }
  printf( "}" ) ;
}

extern void fraction_afficher_cb(void * const fraction){
  fraction_afficher(fraction);
}

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
 * Affectation d'une fraction par reference
 */

extern
err_t fraction_referencer( fraction_t ** frac_cible ,  fraction_t * frac_source )
{
  (*frac_cible) = frac_source ;
  return(OK) ;
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
					frac_source->denominateur ) ) )
    return(ERR_DEB_MEMOIRE) ;

  return(OK) ;
}

extern int fraction_comparer_cb(const void * c1, const void * c2){
  return fraction_comparer(*(const fraction_t **)c1,*(const fraction_t **)c2);
}

extern err_t fraction_copier_cb(void * ind_cible, void * ind_source){
  fraction_copier(ind_cible,ind_source);
  return(OK);
}

extern err_t fraction_referencer_cb(void * ind_cible, void * ind_source){
  fraction_referencer(ind_cible,ind_source);
  return(OK);
}

extern err_t fraction_effacer_cb(void * liste){
  fraction_effacer(liste);
  return(OK);
}

extern err_t fraction_detruire_cb(void * liste){
  fraction_detruire(liste);
  return(OK);
}
