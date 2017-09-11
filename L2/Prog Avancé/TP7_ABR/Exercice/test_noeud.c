#include <noeud.h>
#include <individu.h>

#define FICH_TEST "Fichiers/test_noeud.fich"

int
main() 
{
  err_t noerr = OK; 
  noeud_t * noeud = NULL ; 
  noeud_t * noeud_fg = NULL ; 
  noeud_t * noeud_fd = NULL ; 


  printf( "Debut du programme des test sur les objets de type noeud_t\n" ) ; 

  /* 
   * Creation variables de travail 
   */
  individu_t * individu_1 = individu_creer( "Roger" , "Waters" ) ;
  individu_t * individu_2 = individu_creer( "David" , "Gilmour" ) ;
  individu_t * individu_3 = individu_creer( "Pete"  , "Masson" ) ;

  printf( "Test d'existance sur un noeud_t inexistant\n" ) ;
  ( noeud_existe(noeud) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf( "Test creation noeud_t\n" ) ;
  noeud_fg = noeud_creer( individu_2 , NULL , NULL , individu_copier_cb ) ; 
  noeud_fd = noeud_creer( individu_3 , NULL , NULL , individu_copier_cb ) ; 
  noeud    = noeud_creer( individu_1 , noeud_fg , noeud_fd , individu_copier_cb ) ; 

  printf( "Test affichage noeud\n" ) ;
  noeud_afficher( noeud , individu_afficher_cb ) ; 
  printf( "\n");

  printf( "Test d'existance sur un noeud_t existant\n" ) ;
  ( noeud_existe(noeud) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test positif pere d'un noeud\n" ) ;
  ( noeud_est_pere(noeud , noeud_fg ) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test negatif pere d'un noeud\n" ) ;
 ( noeud_est_pere(noeud_fg , noeud ) ? printf("-->KO\n") : printf ("-->OK\n") )  ;
  
  FILE * fd = NULL ; 
  
  printf( "Test sauvegarde noeud\n" ) ; 
  if( (fd = fopen( FICH_TEST , "w" ) ) == NULL )
    { 
      perror("Pb ouverture ecriture fichier \"test_noeud.fich\"" ) ;
      return(-1) ; 
    }
  if( ( noerr = noeud_fd_sauver( noeud , fd , individu_sauver_cb ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    } 
  fclose(fd) ;

  printf( "Test destruction noeuds\n" ) ;
  if( ( noerr = noeud_detruire( &noeud , individu_detruire_cb ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  if( ( noerr = noeud_detruire( &noeud_fg , individu_detruire_cb ) ) )
   { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  if( ( noerr = noeud_detruire( &noeud_fd , individu_detruire_cb ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
 
  /*
   * Destruction varaibles de travail 
   */
  individu_detruire( &individu_1 ) ; 
  individu_detruire( &individu_2 ) ; 
  individu_detruire( &individu_3 ) ; 

  printf( "Fin du programme des test sur les objets de type noeud_t\n" ) ; 

  return(0) ; 
}
