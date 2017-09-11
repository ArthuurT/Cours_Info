#include <individu.h>

#define FICH_TEST "Fichiers/test_individu.fich"

int
main() 
{
  err_t noerr = OK; 
  individu_t * individu = NULL ; 
  individu_t * individu_2 = NULL ; 

  printf( "Debut du programme des test sur les objets de type individu_t\n" ) ; 

  printf( "Test d'existance sur un individu_t inexistant\n" ) ;
  ( individu_existe(individu) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf( "Test creation individu_t\n" ) ;
  individu = individu_creer( "Roger" , "Waters" ) ;

  printf( "Test affichage individu\n" ) ;
  individu_afficher( individu ) ; 
  printf( "\n");

  printf( "Test d'existance sur un individu_t existant\n" ) ;
  ( individu_existe(individu) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test comparaison individu_t\n" ) ;
  individu_2 = individu_creer( "David" , "Gilmour" ) ;  
  int cmp = individu_comparer( (const individu_t **)&individu , (const individu_t **)&individu_2 ) ;
  individu_afficher( individu ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  individu_afficher(individu_2 ) ; 
  printf("\n");

  cmp = individu_comparer( (const individu_t **)&individu_2 , (const individu_t **)&individu ) ;
  individu_afficher( individu_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  individu_afficher(individu ) ; 
  printf("\n");

  cmp = individu_comparer( (const individu_t **)&individu_2 , (const individu_t **)&individu_2 ) ;
  individu_afficher( individu_2 ) ; 
  if( cmp < 0 ) printf( " < " ) ; 
  if( cmp == 0 ) printf( " == " ) ; 
  if( cmp > 0 ) printf( " > " ) ; 
  individu_afficher(individu_2 ) ; 
  printf("\n");

  if( ( noerr = individu_detruire( &individu_2 ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }  

  FILE * fd = NULL ; 
  
  printf( "Test sauvegarde individu\n" ) ; 
  if( (fd = fopen( FICH_TEST , "w" ) ) == NULL )
    { 
      char mess[256] ; 
      sprintf( mess , "Pb ouverture ecriture fichier \"%s\"" , FICH_TEST ) ;
      perror( mess ) ;
      return(-1) ; 
    }
  if( ( noerr = individu_sauver( individu , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  fclose(fd) ;

  printf( "Test destruction individu\n" ) ;
  if( ( noerr = individu_detruire( &individu ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  printf( "Test chargement individu\n" ) ; 
  if( (fd = fopen( FICH_TEST , "r" ) ) == NULL )
    { 
      char mess[256] ;
      sprintf( mess , "Pb ouverture lecture fichier \"%s\"" , FICH_TEST ) ;
      perror(mess) ; 
      return(-1) ; 
    }
  if( ( noerr = individu_charger( &individu , fd ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  
  individu_afficher( individu ) ; 
  printf("\n") ;
  fclose(fd) ; 

  if( ( noerr = individu_detruire( &individu ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
 
  printf( "Fin du programme des test sur les objets de type individu_t\n" ) ; 
  
  printf( "Nombre de individu_t  = %lu\n" , individu_cpt ) ;

  return(0) ; 
}
