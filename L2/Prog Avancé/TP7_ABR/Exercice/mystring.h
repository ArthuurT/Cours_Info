#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <commun.h>

/*
 * DEFINITION OBJET "STRING"  
 */

typedef struct string_s 
{
  int length ;
  char * string ;
} string_t ;

/*
 * VARIABLES GLOBALES
 */

/*
 * Compteur d'objets string_t 
 */

extern unsigned long int string_cpt  ;

/*
 * Compteur de comparaisons 
 */
extern unsigned long int string_comp  ;

/*
 * MACROS
 */

#define string_comp_raz() string_comp = 0 

/* 
 * FONCTIONS
 */
/* Acces */
extern int string_taille_lire( const string_t * string ) ;
extern char * string_string_lire( const string_t * string ) ;
/* Creation */
extern string_t * string_creer(const char * chaine ) ;
/* Test existance */
extern booleen_t string_existe( const string_t * string ) ;
/* Destructions */
extern err_t string_detruire( string_t ** string ) ;
extern err_t string_detruire_cb( void * string ) ;
/* Effacements */
extern err_t string_effacer( string_t ** string ) ;
extern err_t string_effacer_cb( void * string )  ; 
/* Affichages */
extern void string_afficher( const string_t * string ) ;
extern void string_afficher_cb( const void * string ) ;
extern void string_printf( const string_t * string ) ;
extern void string_printf_cb( const void * string ) ;
/* Comparaisons */
extern int string_comparer( const string_t * const * str1 , const string_t * const * str2 ) ;
extern int string_comparer_cb( const void * str1 , const void * str2 ) ;
/* Referencements */
extern err_t string_referencer( string_t ** str_cible ,  string_t * str_source ) ;
extern err_t string_referencer_cb( void * str_cible ,  void * str_source ) ;
/* Copies */
extern err_t string_copier( string_t ** str_cible ,  string_t * str_source ) ; 
extern err_t string_copier_cb( void * str_cible ,  void * str_source ) ;

/*
 * Chargement d'une string a partir d'un fichier 
 * La string est creee
 * Retour :  0 : OK 
 *           ERR_SCANF : pb lecture string dans le fichier
 *           ERR_DEB_MEMOIRE : debordement memoire lors de la creation de la string
 */
extern err_t string_charger( string_t ** string , 
			     FILE * restrict fd ) ;
extern err_t string_charger_cb( void * string , 
				FILE * restrict fd ) ; 

extern err_t string_fscanf( string_t ** string , 
			    FILE * restrict fd ) ;
extern err_t string_fscanf_cb( void * string , 
			       FILE * restrict fd ) ;
/*
 * Sauvegarde d'une string dans un fichier 
 */

extern err_t string_sauver( string_t * string , 
			    FILE * restrict fd ) ;

extern err_t string_sauver_cb( void * string , 
			       FILE * restrict fd ) ; 

/*
 * Saisie d'une strig au clavier (entree standard)
 */

extern string_t * string_saisir( const char * message ) ;

#endif
