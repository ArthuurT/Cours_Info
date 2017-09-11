#ifndef _ABR_H_
#define _ABR_H_
/*
 * Definition Arbre Binaire
 */

#include <ab.h>


/*
 * Type Arbre Binaire
 */

typedef struct abr_s
{
  #include <abr_attributs.h>
} abr_t ;

/*
 * Fonctions
 */
extern noeud_t * abr_racine_lire( const abr_t * arbre )  ;
extern err_t abr_racine_ecrire( abr_t * arbre , noeud_t * racine )  ;

extern int abr_taille_lire( const abr_t * arbre )     ;
extern err_t abr_taille_incrementer( abr_t * arbre )  ;
extern err_t abr_taille_decrementer( abr_t * arbre )  ;

/* Test */
extern booleen_t abr_existe( const abr_t * arbre ) ;
extern booleen_t abr_vide( const abr_t * arbre ) ;

/*
 * Creation
 */

extern abr_t * abr_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	      /*!< Fonction d'affectation d'un element */
			  err_t (*fonction_destruction)( void * e)   ,			      /*!< Fonction de destruction d'un element */
			  int (*fonction_comparaison) ( const void * e1 , const void * e2) ) ;  /*!< Fonction de comparaison de 2 elements */

/*
 * Destruction
 */

extern err_t abr_detruire( abr_t ** arbre )  ;


/*
 * Affichage
 */

extern void abr_afficher( const abr_t * arbre , void (*fonction_affichage)(const void *), ab_parcours_t type);
/*
 * Insertion d'une valeur dans un ABR
 */

extern err_t abr_inserer( abr_t * arbre  ,
			  void * etiquette ) ;

/*
 * Suppression d'une valeur dans un ABR
 */

extern booleen_t abr_supprimer( abr_t * arbre ,
			    void * etiquette ) ;

/*
 * Chargement d'un arbre a partir d'un fichier
 */

extern  err_t abr_charger( abr_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
			   char *  nom_fichier ,					    /* Nom du fichier de chargement */
			   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */
			   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
			   int (*fonction_compaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
			   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) ;	    /* Fonction de chargement d'un element */

/*
 * Sauvegarde d'un arbre dans un fichier
 */

extern  err_t abr_sauver( const abr_t * arbre  ,					/* ABR  a charger */
			 char *  nom_fichier ,						/* Nom du fichier de chargement */
			 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) ;	/* Fonction de sauvegarde d'un element */

/*
 * Recherche du pere d'un noeud dans un arbre
 */

extern noeud_t * abr_pere_rechercher( const abr_t * arbre ,
				      const noeud_t * noeud_fils ) ;

/*
 * Recherche d'un element dans un arbre
 */

extern booleen_t abr_rechercher( noeud_t ** result ,
				 const abr_t * arbre ,
				 const void * etiquette ) ;

#endif
