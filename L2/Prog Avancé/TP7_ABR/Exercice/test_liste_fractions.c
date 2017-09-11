#include <getopt.h>

#include <fraction.h>
#include <liste.h>


#define FICH_TEST "Fichiers/test_liste_fractions.fich"

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

  fraction_t ** fractions = NULL  ; 

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

  srandom(getpid()) ; 

  /* ---------- */
  
  /* 
   * Creation des variables de travail 
   */

  if( verbose ) printf( "\nCreation des variables de travail\n" ) ;

  fractions = malloc( sizeof(fraction_t *) * N )  ; 
  for( i=0 ; i<N ; i++ ) 
    {
      fractions[i] = fraction_creer( N-i , N-i+1 ) ; 
    }

  /* 
   * Creation d'une liste de fractions par reference
   * (les objets n'appartiennent pas a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d fractions par reference\n" , N ) ;

  liste = liste_creer(N , fraction_referencer_cb , fraction_effacer_cb , fraction_comparer_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , fractions[i] , i ) ;
    }
     
  printf( "Affichage liste des fractions AVANT tri \n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des fractions\n" );
  fraction_comp_raz() ; 
  liste_trier( liste ) ;
  if( verbose ) printf( "Nb comparaisons = %lu\n" , fraction_comp );

  printf( "Affichage liste des fractions APRES tri\n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  if( verbose ) printf( "Test destruction liste des fractions\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }


  /* 
   * Creation d'une liste des fractions par copie
   * (les objets appartiennent a la liste)
   */

  if( verbose ) printf( "\nTest creation d'une liste de %d fractions par copie\n" , N ) ;

  liste = liste_creer(N , fraction_copier_cb , fraction_detruire_cb , fraction_comparer_cb ) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      liste_elem_ecrire( liste , fractions[i] , i ) ;
    }
     
  printf( "Affichage liste des fractions AVANT tri \n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");

  if( verbose ) printf( "Test Tri de la liste des fractions\n" );
  fraction_comp_raz() ;
  liste_trier( liste ) ;
  if( verbose ) printf( "Nb comparaisons = %lu\n" , fraction_comp );

  printf( "Affichage liste des fractions APRES tri\n" ) ;
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  /*
   * Test Sauvegarde
   */
  
  if( verbose ) printf( "Test Sauvegarde fractions\n" ) ;
  if( ( noerr = liste_sauver(  liste ,
			       FICH_TEST ,
			       fraction_sauver_cb,
			       '\n' ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  if( verbose ) printf( "Test destruction liste des fractions\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  /*
   * Test Restauration
   */
  
  if( verbose ) printf( "Test Restauration fractions\n" ) ;
  if( ( noerr = liste_charger(  &liste ,
				FICH_TEST ,				
				fraction_copier_cb , 
				fraction_detruire_cb , 
				fraction_comparer_cb ,
				fraction_charger_cb ,
				verbose ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  liste_afficher( liste , fraction_afficher_cb , ' ' ) ; 
  printf( "\n");
 
  /*
   * Test Suppressions d'elements 
   */
  

  printf("\nTest Suppressions d'elements dans une liste triee\n\n"); 
  int ind_supp = -1 ; 
   for( i=0 ; i<N ; i++ ) 
    {
      ind_supp = random()%N ;
      printf("Destruction de "); fraction_afficher( fractions[ind_supp] ) ; printf("\n") ; 
      if( liste_supprimer( liste , fractions[ind_supp] ) )
	printf("---> element trouve\n") ; 
      else
	printf("---> element non trouve\n") ; 
      liste_afficher( liste , fraction_afficher_cb , ' ' ) ; printf( "\n\n");
    }


   if( verbose ) printf( "Test destruction liste des fractions\n" ) ;
   if( ( noerr = liste_detruire( &liste ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }

  /* ------------ */
   

   /* Destruction des variables de travail */
   for( i=0 ; i<N ; i++ ) 
    {
      fraction_detruire( &(fractions[i]) )  ; 
    }
  free( fractions ) ;


  if( verbose ) printf( "\nFin du programme de test sur la liste de fractions\n" ) ; 
  
  if( verbose ) printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
