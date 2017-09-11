#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <commun.h>

/*
 * DEFINITION OBJET "FRACTION"  
 */

typedef struct fraction_s 
{
  int numerateur ;
  int denominateur ;
} fraction_t ;

/*
 * VARIABLE LOCALE
 * declaration du compteur d'objets fraction_t comme variable externe
 * pour compter les references sur ces objets 
 */

extern unsigned long int fraction_cpt  ;

/* 
 * FONCTIONS
 */

/* Creation */
extern fraction_t * fraction_creer(const int numerateur , const int denominateur ) ;
/* Test existance */
extern booleen_t fraction_existe( const fraction_t * fraction ) ;
/* Destructions */
extern err_t fraction_detruire( fraction_t ** fraction ) ;
extern err_t fraction_detruire_cb( void * fraction ) ;
/* Effacements */
extern err_t fraction_effacer( fraction_t ** fraction ) ;
extern err_t fraction_effacer_cb( void * fraction )  ; 
/* Affichages */
extern void fraction_afficher( const fraction_t * fraction ) ;
extern void fraction_afficher_cb( const void * fraction ) ;
/* Comparaisons */
extern int fraction_comparer( const fraction_t * const f1 , const fraction_t * const f2 ) ;
extern int fraction_comparer_cb( const void * f1 , const void * f2 )  ;
/* Referencements */
extern err_t fraction_referencer( fraction_t ** frac_cible ,  fraction_t * frac_source ) ;
extern err_t fraction_referencer_cb( void * frac_cible ,  void * frac_source ) ;
/* Copies */
extern err_t fraction_copier( fraction_t ** frac_cible ,  fraction_t * frac_source ) ; 
extern err_t fraction_copier_cb( void * frac_cible ,  void * frac_source ) ;
/*
 * Chargement d'une fraction a partir d'un fichier 
 * La fraction est creee
 * Retour :  0 : OK 
 *           ERR_SCANF : pb lecture fraction dans le fichier
 *           ERR_DEB_MEMOIRE : debordement memoire lors de la creation de la fraction
 */
extern err_t fraction_charger( fraction_t ** fraction , 
			       FILE * restrict fd ) ;

extern err_t fraction_charger_cb( void * fraction ,
				  FILE * restrict fd ) ;

/*
 * Sauvegarde d'une fraction dans un fichier 
 */
extern err_t fraction_sauver( fraction_t * fraction  , 
			      FILE * restrict fd) ;

extern err_t fraction_sauver_cb( void * fraction , 
				 FILE * restrict fd ) ;
#endif
