#include <math.h>

#include <abr_fonctions.h>
#include <mystring.h>
#include <liste.h>

#define FICH_TEST "Fichiers/test_abr_strings.fich"

int
main(int argc , char * argv[] ) 
{
  err_t noerr = OK; 
  char nomprog[512] ;

  string_t ** strings = NULL  ; 
  abr_t * arbre = NULL ; 
  liste_t * liste = NULL ; 

  float exp_n = 0 ; 
  float N = 0 ; 

  int i ; 

  strcpy( nomprog , argv[0] ) ; 

  if( argc != 2 )
    {
      printf( "usage: %s 2<n>\n" , nomprog ) ; 
      printf( "\t n: puissance de 2; n^2 - 1  representera le nombre d'elements de l'arbre\n" ) ; 
      exit(1) ;
    }

  exp_n = atof(argv[1]) ;
  N = powf( 2 , exp_n ) - 1 ; 
 
  printf( "\n\nDebut du programme de test sur un abr_t avec %d strings\n"  , (int)N ) ; 

  /* 
   * Creation variables de travail 
   */

  strings = malloc( sizeof(string_t *) * N )  ; 

  char string[128] ;
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( string , "string_%d" , (int)(N-i) ) ; 
      strings[i] = string_creer( string ) ; 
    }

  liste = liste_creer( N ,  
		       string_referencer_cb ,
		       string_effacer_cb , 
		       string_comparer_cb ) ; 
  
  for( i=0 ; i<N ; i++ ) 
    {
      if( ( noerr = liste_elem_ecrire( liste , strings[i] , i ) ) )
	return(noerr) ; 
    }

  /* ----- */

  printf( "Test Creation d'un abr_t \n" ) ;
  if( ( noerr = abr_dicho_creer( &arbre ,
				 string_referencer_cb ,
				 string_effacer_cb , 
				 string_comparer_cb ,
				 liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  printf( "Test affichage arbre\n" ) ;
  abr_afficher( arbre , string_afficher_cb , PREFIXE ) ; 
  printf( "\n");

  printf( "Test d'existance sur un arbre abr_t existant\n" ) ;
  ( abr_existe(arbre) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test sauvegarde arbre abr_t\n" ) ; 
  if( ( noerr = abr_sauver( arbre , FICH_TEST , string_sauver_cb ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 

  printf( "Test destruction arbre\n" ) ;
  if( ( noerr = abr_detruire( &arbre ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
 printf( "Test chargement arbre\n" ) ;
 if( ( noerr = abr_charger( &arbre  , FICH_TEST , 			
			    string_copier_cb , 
			    string_detruire_cb , 
			    string_comparer_cb ,
			    string_charger_cb ) ) )  
   { 
     printf("Sortie avec code erreur = %d\n" , noerr ) ;
     err_print(noerr) ;
     return(noerr) ; 
   }

  printf( "Affichage arbre charge\n" ) ;
  abr_afficher( arbre , string_afficher_cb , PREFIXE ) ; 
  printf( "\n");

  printf( "Test destructions elements \n" ) ;
  int ind_supp = 0 ; 
  for( i=0 ; i<N ; i++ ) 
    {
      ind_supp = random()%(int)N ;
      printf("Destruction de ") ; 
      string_afficher(strings[ind_supp]) ; 
      printf("\n") ; 
      if( abr_supprimer( arbre , strings[ind_supp] ) )
	printf(" --> Noeud trouve\n" ) ; 
      else
	printf(" --> Noeud pas trouve\n" ) ; 

      abr_afficher(arbre , string_afficher_cb , PREFIXE ) ;
      printf("\n") ;
    }

  printf( "Test destruction arbre\n" ) ;
  if( ( noerr = abr_detruire( &arbre ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  /*
   * Destructions variables de travail 
   */
  
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie destruction liste avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  
  for( i=1 ; i<N ; i++ ) 
    {
      string_detruire( &strings[i] ) ; 
    }

  printf( "Fin du programme de test sur les objets de type arbre abr_t\n" ) ; 

  return(0) ; 
}
