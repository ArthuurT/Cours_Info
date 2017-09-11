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
 * VARIABLE LOCALE
 * declaration du compteur d'objets individu_t comme variable externe
 * pour compter les references sur ces objets
 */

extern unsigned long int individu_cpt  ;

/*
 * FONCTIONS
 */

extern individu_t * individu_creer(char * const prenom , char * const nom ) ;

extern booleen_t individu_existe( individu_t * const individu ) ;

extern err_t individu_detruire( individu_t ** individu ) ;
extern err_t individu_effacer( individu_t ** individu ) ;

extern void individu_afficher( individu_t * const individu ) ;
extern void individu_afficher_cb(void * const individu);

extern int individu_comparer( const individu_t * const ind1 , const individu_t * const ind2 ) ;
extern int individu_comparer_cb(const void * i1, const void * i2);

extern err_t individu_referencer( individu_t ** ind_cible ,  individu_t * ind_source ) ;
extern err_t individu_copier( individu_t ** ind_cible ,  individu_t * ind_source ) ;

extern err_t individu_copier_cb(void * ind_cible, void * ind_source);
extern err_t individu_referencer_cb(void * ind_cible, void * ind_source);

extern err_t individu_effacer_cb(void * liste);
extern err_t individu_detruire_cb(void * liste);

#endif
