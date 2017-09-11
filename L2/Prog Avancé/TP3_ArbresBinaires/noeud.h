#ifndef _NOEUD_H_
#define _NOEUD_H_

#include <commun.h>

/*
 * Definition Arbre Binaire
 */

/* Type Noeud */

typedef struct noeud_s
{
  int numero ;
  void * etiquette ;
  struct noeud_s * gauche ;
  struct noeud_s * droit ;

} noeud_t ;

/*
 * Fonctions d'acc�s aux attributs
 */

/* -- numero du noeud */
extern int noeud_numero_lire( const noeud_t * noeud ) ;
extern err_t noeud_numero_ecrire( noeud_t * noeud , const int numero )  ;

/* -- Etiquette */
extern void * noeud_etiquette_lire( const noeud_t * noeud )  ;
extern err_t noeud_etiquette_ecrire( noeud_t * noeud ,
				     void * etiquette ,
				     err_t (*affecter)( void * e1 , void * e2 ) ) ;
/* -- Sous arbre gauche */
extern noeud_t * noeud_sag_lire( const noeud_t * noeud ) ;
extern err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche )   ;

/* -- Sous arbre droit */
extern noeud_t * noeud_sad_lire( const noeud_t * noeud ) ;
extern err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit ) ;

/*
 * Tests
 */

/* Existance ? */
extern booleen_t noeud_existe( const noeud_t * noeud ) ;

/* Feuille ?*/
extern booleen_t noeud_feuille( const noeud_t * noeud ) ;

/* Parents ? */
extern booleen_t noeud_est_pere( const noeud_t * noeud_pere ,
				 const noeud_t * noeud_fils )  ;
/*
 * Creation d'un noeud
 */

extern noeud_t * noeud_creer( const int numero ,
			      void * etiquette ,
			      noeud_t * sous_arbre_gauche ,
			      noeud_t * sous_arbre_droit ,
			      err_t (*affecter)( void * e1 , void * e2 ) ) ;

/*
 * Destruction d'un noeud
 */

extern err_t noeud_detruire( noeud_t ** noeud ,
			     err_t (*detruire)( void * e) ) ;

/*
 * Affichage d'un noeud
 */

extern void noeud_afficher( const noeud_t * noeud ,
			    void (*afficher)(const void *), int profondeur ) ;

/*
 * Sauvegarde d'un noeud dans un fichier
 */

extern err_t noeud_fd_sauver( noeud_t * noeud  ,	                  /* Noeud a sauvegarder */
			      FILE * fd , 		                  /* Descripteur fichier  */
			      err_t (*sauver)( void * e, FILE *  desc) ) ; /* Fonction de sauvegarde d'un element */




/*
 * Recherche d'un noeud dans un arbre
 * Retour :
 * - VRAI si recherche positive ; result --> @ du noeud trouve
 * - FAUX si recherche negative ; result --> NULL
 */

/* Sur le numero */

extern
booleen_t noeud_numero_rechercher( noeud_t ** result ,        /* Resultat: @ du noeud trouve */
				   noeud_t * racine ,  /* Racine de l'arbre de recherche */
				   const int numero       ) ;  /* Numero du noeud a rechercher dans l'arbre */

/* Sur l'etiquette */

extern
booleen_t noeud_rechercher( noeud_t ** result ,			 /* Resultat: @ du noeud trouve */
			    noeud_t * racine  ,	         /* Racine de l'arbre de recherche */
			    void * etiquette     ,		 /* Valeur a rechercher dans l'arbre */
			    int (*comparer)(void * n1 , void * n2) ) ; /* Fonction de comparaison des etiquettes */


#endif
