#ifndef _AVL_H_
#define _AVL_H_
/*
 * Definition Arbre Binaire
 */

#include <abr.h>

/*
 * Constantes
 */



/* 
 * Type Arbre Binaire Equilibre 
 */

typedef abr_t avl_t ; 

/*
 * Fonctions 
 */
extern noeud_t * avl_racine_lire( const avl_t * arbre )  ; 
extern err_t avl_racine_ecrire( avl_t * arbre , noeud_t * racine )  ;

extern int avl_taille_lire( const avl_t * arbre )     ;
extern err_t avl_taille_incrementer( avl_t * arbre )  ;
extern err_t avl_taille_decrementer( avl_t * arbre )  ;

/* Test */
extern booleen_t avl_existe( const avl_t * arbre ) ; 
extern booleen_t avl_vide( const avl_t * arbre ) ;

/*
 * Creation 
 */

extern avl_t * avl_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	      /*!< Fonction d'affectation d'un element */
			  err_t (*fonction_destruction)( void * e)   ,			      /*!< Fonction de destruction d'un element */
			  int (*fonction_comparaison) ( const void * e1 , const void * e2) ) ;  /*!< Fonction de comparaison de 2 elements */

/*
 * Destruction 
 */

extern err_t avl_detruire( avl_t ** arbre )  ;


/*
 * Affichage 
 */

extern void avl_afficher( const avl_t * arbre , 
			  void (*fonction_affichage)(const void *) ,
			  const ab_parcours_t parcours ) ;
/*
 * Insertion d'une valeur dans un AVL
 */

extern err_t avl_inserer( avl_t * arbre  ,
			  void * etiquette ) ;

/*
 * Suppression d'une valeur dans un AVL
 */

extern booleen_t avl_supprimer( avl_t * arbre ,
			    void * etiquette ) ;

/*
 * Chargement d'un arbre a partir d'un fichier 
 */

extern  err_t avl_charger( avl_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
			   char *  nom_fichier ,					    /* Nom du fichier de chargement */
			   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */ 
			   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
			   int (*fonction_compaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
			   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) ;	    /* Fonction de chargement d'un element */

/*
 * Sauvegarde d'un arbre dans un fichier 
 */

extern  err_t avl_sauver( const avl_t * arbre  ,					/* AVL  a charger */
			 char *  nom_fichier ,						/* Nom du fichier de chargement */
			 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) ;	/* Fonction de sauvegarde d'un element */

/*
 * Recherche du pere d'un noeud dans un arbre 
 */

extern noeud_t * avl_pere_rechercher( const avl_t * arbre , 
				      const noeud_t * noeud_fils ) ;

/*
 * Recherche d'un element dans un arbre 
 */

extern booleen_t avl_rechercher( noeud_t ** result , 
				 const avl_t * arbre , 
				 const void * etiquette ) ;

#endif
