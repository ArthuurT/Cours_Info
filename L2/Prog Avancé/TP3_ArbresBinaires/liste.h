#ifndef _LISTE_H_
#define _LISTE_H_

#include <commun.h>

#define LISTE_NULL NULL
#define LISTE_ID_NULL -1

typedef enum type_tri_s { UNK , QUICK , MERGE , HEAP } type_tri_t ;

typedef struct liste_s
{
  int nb ;		/* Nombre d'objets dans la liste  */
  void ** liste ;	/* liste  des objets */
  /*! Fonctions invariables applicables sur tous les elements de la liste */
  err_t (*affecter)( void * e1 , void * e2 ) ; /*!< Fonction d'affectation d'un element */
  err_t (*detruire)( void * e) ; /*!< Fonction de destruction d'un element */
} liste_t ;

extern unsigned long int liste_cpt  ;

/*
 * FONCTIONS
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! Acces au nombre d'objets */
extern int liste_nb_lire( liste_t * const liste );

/*! Acces a un objets de la liste */
extern void * liste_elem_lire( liste_t * const liste , const int ind );

/*!
 * @}
 * \name Tests 
 * @{
 */

/*! Teste si la liste existe */
extern booleen_t liste_existe( liste_t * const liste) ; 

/*! Teste si la liste est vide (aucun &eacute;l&eacute;ment dedans) */
extern booleen_t liste_vide( liste_t * const liste) ; 

/*!
 * @}
 * \name Methodes d'affectations 
 * @{
 */

/*! Affectation d'un objet */
extern err_t liste_elem_ecrire( liste_t * liste, 
				void * const elem ,
				const int ind ) ;

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
 * Creation d'une liste 
 */
extern liste_t * liste_creer( const int nb , 
			      err_t (*fonction_affectation)( void * e1 , void * e2 ) ,
			      err_t (*fonction_destruction)(void * e) );

/*!
 * Destruction d'une liste 
 */

extern err_t liste_detruire( liste_t ** liste ) ; 


/*! 
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'une liste sur la sortie standard
 */

extern void liste_afficher( liste_t * const liste , 
			    void (*elem_afficher)(const void * ),
			    const char separateur );

/*!
 * @}
 */


/*!
 * tri d'une liste 
 */

extern err_t liste_trier( liste_t * liste , int (*comparer)( const void * , const void *) ,...) ;

/*!
 * \name Chargement d'une liste a partir d'un fichier 
 * @{
 */
extern 
err_t liste_fd_charger( liste_t ** liste  ,							/* liste d'elements a charger */
			FILE * fd ,							/* descripteur fichier de chargement */
			err_t (*fonction_affectation)( void * e1 , void * e2 ) ,   /* fonction d'affecation d'un element */ 
			err_t (*fonction_destruction)(void * e) ,                        /* fonction de destructiuon d'un element */
			err_t (*fonction_chargement)(void * e, FILE *  desc ) ) ;	/* Fonction de chargement d'un element */

extern 
err_t liste_charger( liste_t ** liste  ,						/* liste d'elements a charger */
		     char *  nom_fichier ,					/* Nom du fichier de chargement */
		     err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/* fonction d'affecation d'un element */ 
		     err_t (*fonction_destruction)(void * e) ,			/* fonction de destructiuon d'un element */
		     err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) ;	/* Fonction de chargement d'un element */
/*!
 * @}
 */

/*! 
 * \name Sauvegarde d'une liste dans un fichier 
 * @{
 */

extern 
err_t liste_fd_sauver(  liste_t * liste  ,		/* liste a sauvegarder */
			FILE *  fd , 		/* descripteur fichier  */
			err_t (*fonction_sauvegarde)( void * e, FILE *  desc) , /* Fonction de sauvegarde d'un element */
		        char separateur ) ; /* Separateur d'elements */


extern 
err_t liste_sauver(  liste_t * liste  ,							/* liste a sauvegarder */
		     char *  nom_fichier ,						/* Nom fichier sauvegarde */
		     err_t (*fonction_sauvegarde)( void * e, FILE *  desc) ,	/* Fonction de sauvegarde d'un element */
		     char separateur )	;
/*!
 * @}
 */

/*! @} */
#endif
