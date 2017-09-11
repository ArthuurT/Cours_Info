#include <stdio.h>
#include <mystring.h>

#define FICH_TEST "Fichiers/test_mystring.fich"

int
main() 
{
  err_t noerr = OK; 
  string_t * string = NULL ; 
  string_t * string_2 = NULL ; 

  printf( "Debut du programme des test sur les objets de type string_t\n" ) ; 

  printf( "Test d'existance sur un string_t inexistant\n" ) ;
  ( string_existe(string) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf( "Test creation string_t\n" ) ;
  string = string_creer( "azertyuiop qsdfghjklm wxcvbn" ) ;

  printf( "Test affichage string\n" ) ;
  string_afficher( string ) ; 
  printf( "\n");

  printf( "Test d'existance sur un string_t existant\n" ) ;
  ( string_existe(string) ? printf("-->OK\n") : printf ("-->KO\n") )  ;
  

  printf( "Test comparaison string_t\n" ) ;
  string_2 = string_creer( "azertyuiopAAA" ) ;  
  int cmp = string_comparer( (const string_t **)&string , (const string_t **)&string_2 ) ;
  string_afficher( string ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  string_afficher(string_2 ) ; 
  printf("\n");
  
  cmp = string_comparer( (const string_t **)&string_2 , (const string_t **)&string ) ;
  string_afficher( string_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  string_afficher(string ) ; 
  printf("\n");

  cmp = string_comparer( (const string_t **)&string_2 , (const string_t **)&string_2 ) ;
  string_afficher( string_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  string_afficher(string_2 ) ; 
  printf("\n");

  printf( "Test destruction string\n" ) ;
  if( ( noerr = string_detruire( &string_2 ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  FILE * fd = NULL ; 
  
  printf( "Test sauvegarde string\n" ) ; 
  if( (fd = fopen( FICH_TEST , "w" ) ) == NULL )
    { 
      char mess[256] ; 
      sprintf( mess , "Pb ouverture ecriture fichier \"%s\"" , FICH_TEST ) ; 
      perror(mess) ;
      return(-1) ; 
    }
  if( ( noerr = string_sauver( string , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  fclose(fd) ;

  printf( "Test destruction string\n" ) ;
  if( ( noerr = string_detruire( &string ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  printf( "Test chargement string\n" ) ; 
  if( (fd = fopen( FICH_TEST , "r" ) ) == NULL )
    { 
      char mess[256] ;
      sprintf( mess , "Pb ouverture lecture fichier \"%s\"" , FICH_TEST ) ;
      perror(mess);
      return(-1) ; 
    }
  if( ( noerr = string_charger( &string , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  
  string_afficher( string ) ; 
  printf("\n") ;
  fclose(fd) ; 

  if( ( noerr = string_detruire( &string ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  printf( "Test saisie de strings\n" ) ; 
  string = string_saisir("Veuillez saisir une string 1" ) ; 
  string_afficher(string) ; 
  printf("\n") ; 

  string = string_saisir("Veuillez saisir une string 2" ) ; 
  string_afficher(string) ; 
  printf("\n") ; 

  printf( "Fin du programme des test sur les objets de type string_t\n" ) ; 
  
  printf( "Nombre de string_t  = %lu\n" , string_cpt ) ;

  return(0) ; 
}
