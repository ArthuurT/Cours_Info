#include <getopt.h>

#include <individu.h>
#include <liste.h>

#define FICH_TEST "Fichiers/test_liste_individus.fich"

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

  individus = malloc( sizeof(individu_t *) * N )  ; 

  char prenom[128] ;
  char nom[128] ; 
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ; 
    }

  /* 
   * Creation d'une liste d'individus par reference
   * (les objets n'appartiennent pas a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d individus par reference\n" , N ) ;

  liste = liste_creer(N , individu_referencer_cb , individu_effacer_cb ) ;  
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


  /* 
   * Creation d'une liste d'individus par copie
   * (les objets appartiennent a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d individus par copie\n" , N ) ;

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
  
  /*
   * Test Sauvegarde
   */
  
  if( verbose ) printf( "Test Sauvegarde individus\n" ) ;
  if( ( noerr = liste_sauver(  liste ,
			       FICH_TEST ,
			       individu_sauver_cb,
			       '\n' ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  if( verbose ) printf( "Test destruction liste des individus\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  /* 
   * Destruction des variables de travail 
   */
  for( i=0 ; i<N ; i++ ) 
    {
      individu_detruire( &(individus[i]) )  ; 
    }
  free( individus ) ;
  
  /*
   * Test Restauration
   */
  
  if( verbose ) printf( "Test Restauration individus\n" ) ;
  if( ( noerr = liste_charger(  &liste ,
				FICH_TEST ,				
				individu_copier_cb , 
				individu_detruire_cb , 
				individu_charger_cb) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  liste_afficher( liste , individu_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test destruction liste des individus\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  /* ------------ */

  if( verbose ) printf( "\nFin du programme de test sur la liste d'individus\n" ) ; 
  
  if( verbose ) printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
