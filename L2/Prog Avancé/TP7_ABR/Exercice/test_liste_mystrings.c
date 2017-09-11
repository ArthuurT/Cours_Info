#include <getopt.h>

#include <mystring.h>
#include <liste.h>

#define FICH_TEST  "Fichiers/test_liste_mystrings.fich"

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <nombre d'element dans les listes>\n" , nomprog ) ; 
  printf( "options:\n" ) ; 
  printf( "\t--verbose : trace des principales actions\n" ) ; 
  printf( "\t--help    : affiche cette aide\n" ) ; 
}

static struct option longopts[] =
{
  {"verbose", no_argument, NULL, (int)'v'},
  {"help", no_argument, NULL, (int)'h'},
  {0, 0, 0, 0}
};

int
main( int argc , char * argv[] ) 
{
  err_t noerr = OK; 

  string_t ** strings = NULL  ; 

  liste_t * liste = NULL ; 
  int i = 0 ; 

  int opt ; 
  char nomprog[512] ;
  booleen_t  verbose = FAUX ;

  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vht:", longopts, NULL)) != -1 )
    {
      switch(opt)
	{
	case 'v' :  /* --verbose */
	  verbose = VRAI ;
	  break ; 

	case 'h': /* --help */
	  usage(nomprog) ;
	  exit(0);
	  break;

	case '?':
	  usage(nomprog) ;
	  exit(0);
	  break;

	default:
	  usage(nomprog) ;
	  exit(0);
	  break;
	}
    }
  argc -= optind ;
  argv += optind ;

  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */ 

  /* Arguments */
  if( argc != 1 )
    {
      printf( "Nombre d'argument incorrect %d (1 attendu)\n" , argc ) ;
      usage(nomprog) ;  
      exit(-1);
    }
  int N = atoi(argv[0]) ;


  /* ---------- */
  
  /* 
   * Creation des variables de travail 
   */

  if( verbose ) printf( "\nCreation des variables de travail\n" ) ;

  char string[128] ;
  strings = malloc( sizeof(string_t *) * N )  ; 
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( string , "string_%d" , N-i ) ; 
      strings[i] = string_creer( string ) ; 
    }


  /* 
   * Creation d'une liste de strings par reference
   * (les objets n'appartiennent pas a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d strings par reference\n" , N ) ;

  liste = liste_creer(N , string_referencer_cb , string_effacer_cb , string_comparer_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }
     
  printf( "Affichage liste des strings AVANT tri \n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des strings\n" );
  string_comp_raz() ; 
  liste_trier( liste ) ;
  if( verbose ) printf( "Nb comparaisons = %lu\n" , string_comp );

  printf( "Affichage liste des strings APRES tri\n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  if( verbose ) printf( "Test destruction liste des strings\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }


  /* 
   * Creation d'une liste des strings par copie
   * (les objets appartiennent a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d strings par copie\n" , N ) ;

  liste = liste_creer(N , string_copier_cb , string_detruire_cb , string_comparer_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }
     
  printf( "Affichage liste des strings AVANT tri \n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des strings\n" );
  string_comp_raz() ;
  liste_trier( liste ) ;
  if( verbose ) printf( "Nb comparaisons = %lu\n" , string_comp );

  printf( "Affichage liste des strings APRES tri\n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  /*
   * Test Sauvegarde
   */
  
  if( verbose ) printf( "Test Sauvegarde strings\n" ) ;
  if( ( noerr = liste_sauver(  liste ,
			       FICH_TEST ,
			       string_sauver_cb,
			       '\n' ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  
  /*
   * Test Restauration
   */
  
  if( verbose ) printf( "Test Restauration strings\n" ) ;
  if( ( noerr = liste_charger(  &liste ,
				FICH_TEST ,				
				string_copier_cb , 
				string_detruire_cb , 
				string_comparer_cb ,
				string_charger_cb , 
				verbose ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");
  
  /*
   * Test Suppressions d'elements 
   */
  
  printf("\nTest Suppressions d'elements dans une liste triee\n\n"); 
  int ind_supp = -1 ; 
   for( i=0 ; i<N ; i++ ) 
     {
      ind_supp = random()%N ;
      printf("Destruction de "); string_afficher( strings[ind_supp] ) ; printf("\n") ; 
      if( liste_supprimer( liste , strings[ind_supp] ) )
	printf("---> element trouve\n") ; 
      else
	printf("---> element non trouve\n") ; 
      liste_afficher( liste , string_afficher_cb , ' ' ) ; printf( "\n\n");
    }
  
  if( verbose ) printf( "Test destruction liste des strings\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }

  /* ------------ */

  /* 
   * Destruction des variables de travail 
   */
  for( i=0 ; i<N ; i++ ) 
    {
      string_detruire( &(strings[i]) )  ; 
    }
  free( strings ) ;

  if( verbose ) printf( "\nFin du programme de test sur la liste de strings\n" ) ; 
  
  if( verbose ) printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
