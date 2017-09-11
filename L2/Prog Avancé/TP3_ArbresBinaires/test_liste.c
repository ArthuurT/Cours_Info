#include <getopt.h>

#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste.h>

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

  individu_t ** individus = NULL  ; 
  fraction_t ** fractions = NULL  ;
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
  if( N == 0 )
    {
      printf( "Argument %s incorrect (entier > 0 attendu)\n" , argv[0] ) ;
      usage(nomprog) ;  
      exit(-1);
    }


  if( verbose )  printf( "Debut du programme de test sur des listes de %d objets homogenes\n" , N ) ; 

  /* ---------- */

  individus = malloc( sizeof(individu_t *) * N )  ; 
  fractions = malloc( sizeof(fraction_t *) * N )  ;
  strings = malloc( sizeof(string_t *) * N )   ; 

  if( verbose ) printf( "\nCreations des variables de travail\n" ) ;
  
  if( verbose ) printf( "\tindividus..." ) ; fflush(stdout) ;
  char prenom[128] ;
  char nom[128] ; 
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ; 
    }
  if( verbose ) printf("OK\n"); 

  if( verbose ) printf( "\tfractions..." ) ; fflush(stdout) ;
  for( i=0 ; i<N ; i++ ) 
    {
      fractions[i] = fraction_creer( N-i , N-i+1 ) ; 
    }
  if( verbose ) printf("OK\n");

 if( verbose ) printf( "\tstrings..." ) ; fflush(stdout) ;
  char string[128] ;
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( string , "string_%d" , N-i ) ; 
      strings[i] = string_creer( string ) ; 
    }
  if( verbose ) printf("OK\n");
  /* ---------- */

  if( verbose ) printf( "\nTest creation d'une liste de %d individus \n" , N ) ;
  /*   liste = liste_creer(N , individu_referencer_cb , individu_effacer_cb ) ;  */
  liste = liste_creer(N , individu_copier_cb , individu_detruire_cb ) ; 
  for( i=0 ; i<N ; i++ )  
    {
      liste_elem_ecrire( liste , individus[i] , i ) ;
    }
  printf( "Affichage liste d'individus AVANT tri \n" ) ;
  liste_afficher( liste , individu_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des individus\n" );
  if( type_tri == UNK ) 
    liste_trier( liste , individu_comparer_cb ) ;
  else
    liste_trier( liste , individu_comparer_cb , type_tri ) ;

  printf( "Affichage liste d'individus APRES tri\n" ) ;
  liste_afficher( liste , individu_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  if( verbose ) printf( "Test destruction liste d'individus\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  /* ---------- */

  if( verbose ) printf( "\nTest creation d'une liste de %d fractions \n" , N ) ;

  /*   liste = liste_creer(N , fraction_referencer_cb , fraction_effacer_cb ) ;   */
  liste = liste_creer(N , fraction_copier_cb , fraction_detruire_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , fractions[i] , i ) ;
    }

  printf( "Affichage liste de fractions AVANT tri\n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des fractions\n" );
  if( type_tri == UNK ) 
    liste_trier( liste , fraction_comparer_cb ) ;
  else
    liste_trier( liste , fraction_comparer_cb , type_tri ) ;

  printf( "Affichage liste des fractions APRES tri\n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  if( verbose ) printf( "Test destruction liste de fractions\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  /* ---------- */

  if( verbose ) printf( "\nTest creation d'une liste de %d strings \n" , N ) ;
 
  /*   liste = liste_creer(N , string_referencer_cb , string_effacer_cb ) ;   */
  liste = liste_creer(N , string_copier_cb , string_detruire_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }

  printf( "Affichage liste de strings AVANT tri\n" ) ;
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
  
  if( verbose ) printf( "Test destruction liste de strings\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      exit(-1) ; 
    }

  /* ---------- */

  if( verbose ) printf( "\nDestructions des variables de travail\n" ) ;

  if( verbose ) printf( "individus..." ) ; fflush(stdout) ; 
  for( i=0 ; i<N ; i++ ) 
    {
      if( ( noerr = individu_detruire( &individus[i] ) ) )
	{ 
	  printf("Sortie avec code erreur = %d\n" , noerr ) ;
	  exit(-1) ; 
	}
    }
  free( individus ) ;
  if(verbose ) printf("OK\n"); 


  if( verbose ) printf( "fractions..." ) ; fflush(stdout) ; 
  for( i=0 ; i<N ; i++ ) 
    {
      if( ( noerr = fraction_detruire( &fractions[i] ) ) )
	{ 
	  printf("Sortie avec code erreur = %d\n" , noerr ) ;
	  exit(-1) ; 
	}
    }
  free( fractions ) ;
  if(verbose ) printf("OK\n"); 

  
  if( verbose ) printf( "strings..." ) ; fflush(stdout) ; 
  for( i=0 ; i<N ; i++ ) 
    {
      if( ( noerr =string_detruire( &strings[i] ) ) )
	{ 
	  printf("Sortie avec code erreur = %d\n" , noerr ) ;
	  exit(-1) ; 
	}
    }
  free( strings ) ; 
  if(verbose ) printf("OK\n"); 

  
  /* ---------- */
  

  if( verbose ) printf( "\nFin du programme de test sur la liste d'objets homogenes\n" ) ; 
  
  if( verbose ) printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
