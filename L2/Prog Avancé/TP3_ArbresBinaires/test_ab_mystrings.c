#include <math.h>

#include <ab.h>
#include <mystring.h>

#define FICH_TEST "Fichiers/test_ab_strings.fich"

int
main(int argc , char * argv[] )
{
  err_t noerr = OK;
  char nomprog[512] ;

  string_t ** strings = NULL  ;
  noeud_t ** noeuds = NULL ;
  ab_t * arbre = NULL ;

  float exp_n = 0 ;
  float N = 0 ;

  int i ;

  strcpy( nomprog , argv[0] ) ;

  if( argc != 3 )
    {
      printf( "usage: %s 2<n> <parcours>\n" , nomprog ) ;
      printf( "\t n: puissance de 2; n^2 - 1  representera le nombre d'elements de l'arbre\n" ) ;
      printf( "\t <parcours>: type de parcours dans l'affichage de l'arbre\n" ) ;
      printf( "\t            INF  --> Infixe \n" ) ;
      printf( "\t            POST --> Postfixe \n" ) ;
      printf( "\t            PRE  --> Prefixe \n" ) ;
      exit(1) ;
    }

  exp_n = atof(argv[1]) ;
  N = powf( 2 , exp_n ) - 1 ;

  ab_parcours_t parcours = UNK  ;
  if( ! strcmp( argv[2] , "INF"  ) ) parcours = INFIXE ;
  if( ! strcmp( argv[2] , "POST" ) ) parcours = POSTFIXE ;
  if( ! strcmp( argv[2] , "PRE"  ) ) parcours = PREFIXE ;
  if( parcours == UNK )
    {
      printf( "Parametre <parcours> incorrect (%s)\n" , argv[2] ) ;
      printf( "\t <parcours>: type de parcours dans l'affichage de l'arbre\n" ) ;
      printf( "\t            INF  --> Infixe \n" ) ;
      printf( "\t            POST --> Postfixe \n" ) ;
      printf( "\t            PRE  --> Prefixe \n" ) ;
      exit(1) ;
    }

  printf( "Debut du programme de test sur les objets de type arbre ab_t avec %d elements\n"  , (int)N ) ;

  /*
   * Creation variables de travail
   */

  strings = malloc( sizeof(string_t *) * N+1 )  ;

  char string[128] ;
  strings[0] = NULL ;
  for( i = 0; i < N; i++ )
    {
      sprintf( string , "string_%d" , (int)(N-i) ) ;
      strings[i] = string_creer( string ) ;
    }

  noeuds = malloc( sizeof(noeud_t *) * N+1 ) ;
  noeuds[0] = NULL ;
  for( i = 0; i < N; i++ )
    {
      noeuds[i]= noeud_creer( i , strings[i] , NULL , NULL , string_referencer_cb ) ;
    }

  for( i = 0; i < N; i++ )
    {

    if( 2*i+1 < N ) noeud_sag_ecrire( noeuds[i] , noeuds[2*i+1] ) ;
	  if(2*i+2 < N) noeud_sad_ecrire( noeuds[i] , noeuds[(2*i)+2] ) ;

    }

  /* ----- */

 printf( "Test d'existance sur un ab_t inexistant\n" ) ;
 ( ab_existe(arbre) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

 printf( "Test Creation d'un ab_t \n" ) ;
 if( ( arbre = ab_creer( string_referencer_cb , string_effacer_cb ) ) == NULL )
   {
     printf("Debordement memoire\n") ;
     return(ERR_DEB_MEMOIRE) ;
   }
 printf( "Rattachement arbre a sa racine\n" ) ;
 if( N > 0 )
   {
     if( ( noerr = ab_racine_ecrire( arbre , noeuds[0] ) ) )
       {
	 printf("Sortie avec code erreur = %d\n" , noerr ) ;
	 return(noerr) ;
       }
   }

  printf( "Test affichage arbre\n" ) ;
  ab_afficher( arbre , string_afficher_cb, parcours ) ;
  printf( "\n");

  printf( "Test d'existance sur un arbre ab_t existant\n" ) ;
  ( ab_existe(arbre) ? printf("-->OK\n") : printf ("-->KO\n") )  ;

  printf( "Test sauvegarde arbre ab_t\n" ) ;
  if( ( noerr = ab_sauver( arbre , FICH_TEST , string_sauver_cb ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

  printf( "Test destruction arbre\n" ) ;
  if( ( noerr = ab_detruire( &arbre ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

 printf( "Test chargement arbre\n" ) ;
 if( ( noerr = ab_charger( &arbre  , FICH_TEST ,
			   string_copier_cb , string_detruire_cb ,
			   string_charger_cb ) ) )
   {
     printf("Sortie avec code erreur = %d\n" , noerr ) ;
     err_print(noerr) ;
     return(noerr) ;
   }

  printf( "Affichage arbre charge\n" ) ;
  ab_afficher( arbre , string_afficher_cb , parcours) ;
  printf( "\n");

  /*
   * Destructions variables de travail
   */

  for( i=0 ; i<N ; i++ )
    {
      string_detruire( &strings[i] ) ;
    }

  printf( "Fin du programme de test sur les objets de type arbre ab_t\n" ) ;

  return(0) ;
}
