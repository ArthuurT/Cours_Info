#ifndef _INDIVIDU_H_
#define _INDIVIDU_H_

/*
 * DEFINITION OBJET "INDIVIDU"  
 */

#include <commun.h>

typedef struct individu_s 
{
  char * nom ;
  char * prenom ;
} individu_t ;


/*
 * VARIABLES GLOBALES
 */

/*
 * Compteur d'objets individu_t 
 */

extern unsigned long int individu_cpt  ;

/*
 * Compteur de comparaisons 
 */
extern unsigned long int individu_comp  ;

/*
 * MACROS
 */

#define individu_comp_raz() individu_comp = 0 



/* 
 * FONCTIONS
 */

extern individu_t * individu_creer(const char * prenom , const char * nom ) ;

extern booleen_t individu_existe( const individu_t * individu ) ;

/* Destruction */
extern err_t individu_detruire( individu_t ** individu ) ;
extern err_t individu_detruire_cb( void * individu ) ;

/* Effacement reference */
extern err_t individu_effacer( individu_t ** individu ) ;
extern err_t individu_effacer_cb( void * individu )  ; 

/* Affichage */
extern void individu_afficher( const individu_t * individu ) ;
extern void individu_afficher_cb( const void * individu )  ;

/* Comparaison */
extern int individu_comparer( const individu_t * const * ind1 , const individu_t * const * ind2 ) ;
extern int individu_comparer_cb( const void * ind1 , const void * ind2 ) ;

/* Refencement */
extern err_t individu_referencer( individu_t ** ind_cible ,  individu_t * ind_source ) ;
extern err_t individu_referencer_cb( void * ind_cible ,  void * ind_source ) ;

/* Copie */
extern err_t individu_copier( individu_t ** ind_cible ,  individu_t * ind_source ) ; 
extern err_t individu_copier_cb( void * ind_cible ,  void * ind_source ) ;

/*
 * Chargement d'un individu a partir d'un fichier 
 * L'individu est cree
 * Retour :  0 : OK 
 *           ERR_SCANF : pb lecture individu dans le fichier
 *           ERR_DEB_MEMOIRE : debordement memoire lors de la creation de l'individu
 */
extern err_t individu_charger( individu_t ** individu  , 
			       FILE * restrict fd) ;

extern err_t individu_charger_cb( void * individu  , 
				  FILE * restrict fd ) ;

/*
 * Sauvegarde d'un individu dans un fichier 
 */

extern err_t individu_sauver( individu_t * individu  , 
			      FILE * restrict fd ) ;

extern err_t individu_sauver_cb( void * individu , 
				 FILE * restrict fd ) ;



#endif
