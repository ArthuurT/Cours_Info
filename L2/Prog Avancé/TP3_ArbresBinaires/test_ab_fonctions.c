#include <math.h>

#include <ab_fonctions.h>
#include <individu.h>

#define FICH_TEST "Fichiers/test_ab_individus.fich"

int
main(int argc , char * argv[] )
{
  err_t noerr = OK;
  char nomprog[512] ;

  individu_t ** individus = NULL  ;
  noeud_t ** noeuds = NULL ;
  ab_t * arbre = NULL ;

  float exp_n = 0 ;
  float N = 0 ;

  int i ;

  strcpy( nomprog , argv[0] ) ;

  if( argc != 2 )
    {
      printf( "Tests fonctions de ab_t\n" ) ;
      printf( "usage: %s 2<n>\n" , nomprog ) ;
      printf( "\t n: puissance de 2; n^2 - 1  representera le nombre d'elements de l'arbre\n" ) ;
      exit(1) ;
    }

  exp_n = atof(argv[1]) ;
  N = powf( 2 , exp_n ) - 1 ;

  printf( "Debut du programme de test sur les fonctions  de type arbre ab_t avec %d elements\n"  , (int)N ) ;

  /*
   * Creation variables de travail
   */

  individus = malloc( sizeof(individu_t *) * N+1 )  ;

  char prenom[128] ;
  char nom[128] ;
  individus[0] = NULL ;
  for( i=1 ; i<N+1 ; i++ )
    {
      sprintf( nom , "nom_%d" , (int)N-i ) ;
      sprintf( prenom , "prenom_%d" , (int)N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ;
    }

  noeuds = malloc( sizeof(noeud_t *) * N+1 ) ;
  noeuds[0] = NULL ;
  for( i=1 ; i<N+1 ; i++ )
    {
      noeuds[i]= noeud_creer( i , individus[i] , NULL , NULL , individu_referencer_cb ) ;
    }

  for( i=1 ; i<N+1 ; i++ )
    {
      if( 2*i <= N )
	{
	  noeud_sag_ecrire( noeuds[i] , noeuds[2*i] ) ;
	  noeud_sad_ecrire( noeuds[i] , noeuds[(2*i)+1] ) ;
	}
    }

  /* ----- */

 printf( "Creation d'un ab_t \n" ) ;
 if( ( arbre = ab_creer( individu_referencer_cb , individu_effacer_cb ) ) == NULL )
   {
     printf("Debordement memoire\n") ;
     return(ERR_DEB_MEMOIRE) ;
   }
 if( N > 0 )
   {
     if( ( noerr = ab_racine_ecrire( arbre , noeuds[1] ) ) )
       {
	 printf("Sortie avec code erreur = %d\n" , noerr ) ;
	 return(noerr) ;
       }
   }

  ab_afficher( arbre , individu_afficher_cb, PREFIXE ) ;
  printf( "\n");

  /* ------ */

  for( i=1 ; i<N+1 ; i++ )
    {
      printf("\n--------\nAffichage ancetres du noeud ") ;
      noeud_afficher( noeuds[i] ,
		      individu_afficher_cb, 0 ) ;
      printf("\n\n") ;
      ab_ancetres_afficher( arbre ,  noeuds[i] ,
			    individu_afficher_cb ) ;
    }

  printf("\n\n");

  /* ------ */

  if( ( noerr = ab_detruire( &arbre ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

  for( i=1 ; i<N+1 ; i++ )
    {
      individu_detruire( &individus[i] ) ;
    }

  printf( "Fin du programme de test sur les objets de type arbre ab_t\n" ) ;

  return(0) ;
}
