#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <commun.h>

/*
 * DEFINITION OBJET "INDIVIDU"
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
extern booleen_t fraction_existe( fraction_t * const fraction ) ;
/* Destructions */
extern err_t fraction_detruire( fraction_t ** fraction ) ;
/* Effacements */
extern err_t fraction_effacer( fraction_t ** fraction ) ;
/* Affichages */
extern void fraction_afficher( fraction_t * const fraction ) ;
extern void fraction_afficher_cb(void * const fraction);
/* Comparaisons */
extern int fraction_comparer( const fraction_t * const f1 , const fraction_t * const f2 ) ;
extern int fraction_comparer_cb(const void * c1, const void * c2);
/* Referencements */
extern err_t fraction_referencer( fraction_t ** frac_cible ,  fraction_t * frac_source ) ;
/* Copies */
extern err_t fraction_copier( fraction_t ** frac_cible ,  fraction_t * frac_source ) ;
/* Encapsulation */
extern err_t fraction_copier_cb(void * ind_cible, void * ind_source);
extern err_t fraction_referencer_cb(void * ind_cible, void * ind_source);
extern err_t fraction_effacer_cb(void * liste);
extern err_t fraction_detruire_cb(void * liste);
#endif
