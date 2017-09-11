#include <math.h>

#include <abr_fonctions.h>
#include <liste.h>
#include <individu.h>

#define FICH_TEST "Fichiers/test_abr_individus.fich"

int
main(int argc , char * argv[] )
{
  err_t noerr = OK ;
  char nomprog[512] ;

  individu_t ** individus = NULL  ;
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

  printf( "\n\nDebut du programme de test sur un abr_t avec %d individus\n"  , (int)N ) ;

  /*
   * Creation variables de travail
   */

  srandom(getpid()) ;

  individus = malloc( sizeof(individu_t *) * N )  ;

  char prenom[128] ;
  char nom[128] ;
  individus[0] = NULL ;
  for( i=0 ; i<N ; i++ )
    {
      sprintf( nom , "nom_%03d" , (int)i ) ;
      sprintf( prenom , "prenom_%03d" , (int)i) ;
      individus[i] = individu_creer( prenom , nom ) ;
    }

  liste = liste_creer( N ,
		       individu_referencer_cb ,
		       individu_effacer_cb ,
		       individu_comparer_cb ) ;

  for( i=0 ; i<N ; i++ )
    {
      if( ( noerr = liste_elem_ecrire( liste , individus[i] , i ) ) )
	return(noerr) ;
    }

  /* ----- */

  printf( "Test Creation d'un abr_t \n" ) ;
  if( ( noerr = abr_dicho_creer( &arbre ,
				 individu_referencer_cb ,
				 individu_effacer_cb ,
				 individu_comparer_cb ,
				 liste ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }
    
  printf( "Test affichage arbre\n" ) ;
  abr_afficher( arbre , individu_afficher_cb , PREFIXE ) ;
  printf( "\n");

  printf( "Test sauvegarde arbre abr_t\n" ) ;
  if( ( noerr = abr_sauver( arbre , FICH_TEST , individu_sauver_cb ) ) )
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
  if( ( noerr = abr_charger( &arbre  ,
			     FICH_TEST ,
			     individu_copier_cb ,
			     individu_detruire_cb ,
			     individu_comparer_cb ,
			     individu_charger_cb ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ;
    }

  printf( "Affichage arbre charge\n" ) ;
  abr_afficher( arbre , individu_afficher_cb , PREFIXE ) ;
  printf( "\n");

  printf( "Test destructions elements \n" ) ;
  int ind_supp = 0 ;
  for( i=0 ; i<N ; i++ )
    {
      ind_supp = random()%(int)N ;
      printf("Destruction de ") ;
      individu_afficher(individus[ind_supp]) ;
      printf("\n") ;
      if( abr_supprimer( arbre , individus[ind_supp] ) )
	printf(" --> Noeud trouve\n" ) ;
      else
	printf(" --> Noeud pas trouve\n" ) ;

      abr_afficher(arbre , individu_afficher_cb , PREFIXE ) ;
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
      individu_detruire( &individus[i] ) ;
    }

  printf( "Fin du programme de test sur les objets de type arbre abr_t\n" ) ;

  return(0) ;
}
