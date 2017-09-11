#include <fraction.h>

#define FICH_TEST "Fichiers/test_fraction.fich"

int
main() 
{
  err_t noerr = OK; 
  fraction_t * fraction = NULL ; 
  fraction_t * fraction_2 = NULL ; 

  printf( "Debut du programme des test sur les objets de type fraction_t\n" ) ; 

  printf( "Test d'existance sur un fraction_t inexistant\n" ) ;
  ( fraction_existe(fraction) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf( "Test creation fraction_t\n" ) ;
  fraction = fraction_creer( 5 , 7 ) ;

  printf( "Test affichage fraction\n" ) ;
  fraction_afficher( fraction ) ; 
  printf( "\n");

  printf( "Test d'existance sur un fraction_t existant\n" ) ;
  ( fraction_existe(fraction) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test comparaison fraction_t\n" ) ;
  fraction_2 = fraction_creer( 1 , 3 ) ;  
  int cmp = fraction_comparer( (const fraction_t **)&fraction , (const fraction_t **)&fraction_2 ) ;
  fraction_afficher( fraction ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  fraction_afficher(fraction_2 ) ; 
  printf("\n");

  cmp = fraction_comparer( (const fraction_t **)&fraction_2 , (const fraction_t **)&fraction ) ;
  fraction_afficher( fraction_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  fraction_afficher(fraction ) ; 
  printf("\n");

  cmp = fraction_comparer( (const fraction_t **)&fraction_2 , (const fraction_t **)&fraction_2 ) ;
  fraction_afficher( fraction_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  fraction_afficher(fraction_2 ) ; 
  printf("\n");

  printf( "\nTest destruction fraction\n" ) ;
 
  if( ( noerr = fraction_detruire( &fraction_2 ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }



  FILE * fd = NULL ; 
  
  printf( "Test sauvegarde fraction\n" ) ; 
  if( (fd = fopen( FICH_TEST , "w" ) ) == NULL )
    { 
      char mess[256] ;
      sprintf( mess , "Pb ouverture ecriture fichier \"%s\"" , FICH_TEST ) ;
      perror(mess ) ;
      return(-1) ; 
    }
  if( ( noerr = fraction_sauver( fraction , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  fclose(fd) ;

  printf( "Test destruction fraction\n" ) ;
  if( ( noerr = fraction_detruire( &fraction ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  printf( "Test chargement fraction\n" ) ; 
  if( (fd = fopen( FICH_TEST , "r" ) ) == NULL )
    { 
      char mess[256] ; 
      sprintf("Pb ouverture lecture fichier \"%s\"" , FICH_TEST ) ;
      perror(mess) ;
      return(-1) ; 
    }
  if( ( noerr = fraction_charger( &fraction , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  
  fraction_afficher( fraction ) ; 
  printf("\n") ;
  fclose(fd) ; 

  if( ( noerr = fraction_detruire( &fraction ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  printf( "Fin du programme des test sur les objets de type fraction_t\n" ) ; 
  
  printf( "Nombre de fraction_t  = %lu\n" , fraction_cpt ) ;

  return(0) ; 
}
