#ifndef _AB_H_
#define _AB_H_
/*
 * Definition Arbre Binaire
 */

#include <noeud.h>

/*
 * Type de parcours
 */

typedef enum ab_parcours_s { UNK , INFIXE , POSTFIXE , PREFIXE } ab_parcours_t ;

/*
 * Type Arbre Binaire
 */

typedef struct ab_s
{
  int taille ;
  noeud_t * racine ;
  err_t (*affecter)( void * e1 , void * e2 ) ;	/*!< Fonction d'affectation d'un element */
  err_t (*detruire)( void * e) ;		/*!< Fonction de destruction d'un element */
} ab_t ;

/*
 * Fonctions
 */
extern noeud_t * ab_racine_lire( const ab_t * arbre )  ;
extern err_t ab_racine_ecrire( ab_t * arbre , noeud_t * racine )  ;

extern int ab_taille_lire( const ab_t * arbre )  ;
extern err_t ab_taille_incrementer( ab_t * arbre )  ;

/* Test */
extern booleen_t ab_existe( const ab_t * arbre ) ;
extern booleen_t ab_vide( const ab_t * arbre ) ;

/*
 * Creation
 */

extern ab_t * ab_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
			err_t (*fonction_destruction)( void * e)  ) ;			/*!< Fonction de destruction d'un element */


/*
 * Destruction
 */

extern err_t ab_detruire( ab_t ** arbre )  ;


/*
 * Affichage d'un arbre selon un type de parcour donne
 * Les types de parcours sont : infixe, postfixe et symetrique
 */
extern void ab_afficher_prefixe( const noeud_t * noeud , void (*fonction_affichage)(const void *), int profondeur);

extern void ab_afficher( const ab_t * arbre ,
			 void (*fonction_affichage)(const void *), ab_parcours_t type);

/*
 * Chargement d'un arbre a partir d'un fichier
 */

extern  err_t ab_charger( ab_t ** arbre  ,						/* Arbre Binaire d'elements a charger */
			  char *  nom_fichier ,						/* Nom du fichier de chargement */
			  err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/* fonction d'affectation d'un element */
			  err_t (*fonction_destruction)(void * e) ,			/* fonction de destruction d'un element */
			  err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) ;	/* Fonction de chargement d'un element */

/*
 * Sauvegarde d'un arbre dans un fichier
 */

extern  err_t ab_sauver( const ab_t * arbre  ,						/* Arbre Binaire d'elements a charger */
			 char *  nom_fichier ,						/* Nom du fichier de chargement */
			 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) ;	/* Fonction de sauvegarde d'un element */

/*
 * Recherche du pere d'un noeud dans un arbre
 */

extern noeud_t * ab_pere_rechercher_bis( noeud_t * racine, const noeud_t * noeud_fils);

extern noeud_t * ab_pere_rechercher( const ab_t * arbre ,
				     const noeud_t * noeud_fils ) ;

#endif
