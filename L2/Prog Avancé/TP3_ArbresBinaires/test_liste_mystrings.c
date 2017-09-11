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
  printf( "\t--tri=1   : tri avec qsort (par defaut) \n" ) ; 
  printf( "\t      2   : tri avec mergesort\n" ) ; 
  printf( "\t      3   : tri avec heapsort \n" ) ; 
}

static struct option longopts[] =
{
  {"verbose", no_argument, NULL, (int)'v'},
  {"help", no_argument, NULL, (int)'h'},
  {"tri", required_argument, NULL, (int)'t'},
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
  type_tri_t type_tri = UNK ; 

  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vht:", longopts, NULL)) != -1 )
    {
      switch(opt)
	{
	case 't':  /* --tri */
	  type_tri = atoi(optarg) ;
	  switch(type_tri) 
	    {
	    case QUICK : 
	      printf("\nTRI RAPIDE\n");
	      break ;
	    case MERGE : printf("\nTRI FUSION\n");
	      break ;
	    case HEAP : printf("\nTRI PAR TAS\n");
	      break ;
	    default : printf("\nTri inconnu [%d] \n", type_tri );
	      usage(nomprog);
	      exit(-1) ;
	    }
	  break;

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

  liste = liste_creer(N , string_referencer_cb , string_effacer_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }
     
  printf( "Affichage liste des strings AVANT tri \n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des strings\n" );
  if( type_tri == UNK ) 
    liste_trier( liste , string_comparer_cb ) ;
  else
    liste_trier( liste , string_comparer_cb , type_tri ) ;

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

  liste = liste_creer(N , string_copier_cb , string_detruire_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }
     
  printf( "Affichage liste des strings AVANT tri \n" ) ;
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des strings\n" );
  if( type_tri == UNK ) 
    liste_trier( liste , string_comparer_cb ) ;
  else
    liste_trier( liste , string_comparer_cb , type_tri ) ;

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
   * Destruction des variables de travail 
   */
  for( i=0 ; i<N ; i++ ) 
    {
      string_detruire( &(strings[i]) )  ; 
    }
  free( strings ) ;


  /*
   * Test Restauration
   */
  
  if( verbose ) printf( "Test Restauration strings\n" ) ;
  if( ( noerr = liste_charger(  &liste ,
				FICH_TEST ,				
				string_copier_cb , 
				string_detruire_cb , 
				string_charger_cb) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  liste_afficher( liste , string_afficher_cb , ' ' ) ; 
  printf( "\n");
  
  
  
  if( verbose ) printf( "Test destruction liste des strings\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }

  /* ------------ */

  if( verbose ) printf( "\nFin du programme de test sur la liste de strings\n" ) ; 
  
  if( verbose ) printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
