#include <getopt.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include <mystring.h>
#include <abr_fonctions.h>
#include <liste.h>

static
void usage( char * nomprog ) 
{
  printf( "usage: %s [options] <nom du fichier dictionnaire> <nb recherches>\n" , nomprog ) ; 
  printf( "options:\n" ) ; 
  printf( "\t--verbose=1 trace des principales actions\n" ) ; 
  printf( "\t         =2 trace detaillee\n" ) ; 
  printf( "\t--help    : affiche cette aide\n" ) ; 
}

static struct option longopts[] =
{
  {"verbose", required_argument, NULL, (int)'v'},
  {"help", no_argument, NULL, (int)'h'},
  {0, 0, 0, 0}
};

int
main( int argc , char * argv[] ) 
{
  err_t noerr = OK; 
  struct timeval tp_avant ;
  struct timeval tp_apres ;
  unsigned long int temps = 0 ; 

  liste_t * liste_w = NULL ; 
  abr_t * arbre = NULL ; 

  int opt ; 
  char nomprog[MAX_STRING] ;
  int  verbose = 0 ;

  char nom_fichier_dico[MAX_STRING] ; 
  unsigned long int nb_operations = 0 ; 
  int i_operation = 0 ; 

  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "v:h", longopts, NULL)) != -1 )
    {
      switch(opt)
	{	
	case 'v' :  /* --verbose */
	  verbose = atoi(optarg) ;
	  switch(verbose)
	    {
	    case 1 : 
	      printf("(Trace generale)\n\n");
	      break ;
	    case 2 :
	      printf("(Trace detaillee)\n\n") ;
	      break ; 
	    default : 
	       printf("\nNiveau de trace incorrect\n") ;
	       usage(nomprog);
	       exit(-1) ;
	    }
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
  if( argc != 2 )
    {
      printf( "Nombre d'argument incorrect %d (2 attendu)\n" , argc ) ;
      usage(nomprog) ;  
      exit(-1);
    }

  strcpy( nom_fichier_dico , argv[0] ) ; 
  if( sscanf( argv[1] , "%lu" , &nb_operations ) != 1 )
    {
      printf( "Nombre de comparaisons incorrect %s\n" , argv[1] ) ;
      usage(nomprog) ;  
      exit(-1);
    }
  
  srandom(getpid()) ;

  /* ---------- */
  
  if( verbose ) printf( "\n--- Debut du programme %s ---\n" , nomprog ) ; 

  if( verbose ) printf( "Chargement des variables de travail\n" ) ;
  if( ( noerr = liste_charger(  &liste_w ,
				nom_fichier_dico ,				
				string_copier_cb , 
				string_detruire_cb , 
				string_comparer_cb ,
				string_fscanf_cb ,
				FAUX ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  
  if( verbose ) printf( "Chargement dichotomique du dictionnaire\n" ) ;
  gettimeofday(&tp_avant,NULL);
  string_comp_raz() ;

  if( ( noerr = abr_dicho_creer(  &arbre ,
				  string_copier_cb , 
				  string_detruire_cb , 
				  string_comparer_cb ,
				  liste_w ) ))
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }

  gettimeofday(&tp_apres,NULL);

  temps = (tp_apres.tv_sec*1000000+tp_apres.tv_usec) - (tp_avant.tv_sec*1000000+tp_avant.tv_usec) ;

  int nb = liste_nb_lire(liste_w) ;

  /* Statistiques */

  printf( "\n-------------------- Statistiques Chargement --------------------\n\n" ) ; 

  printf( "Taille dictionnaire = %d mots\n\n" , nb ); 
  
  printf( "Nb de comparaisons\n" );
  printf( "   - Total = %lu\n" , string_comp ); 
  printf( "   - Moyen = %.2lf\n\n" , (double)string_comp/nb ); 

  printf( "Temps de chargement = %lu microsecondes\n" , temps ) ;

  printf( "\n----------------------------------------------------------------\n\n" ) ; 

  if( verbose > 1 ) abr_afficher( arbre , string_printf_cb , PREFIXE ) ; 

  if( verbose ) printf( "Test de performance sur la recherche aleatoire d'elements\n" ) ;

  gettimeofday(&tp_avant,NULL);
  string_comp_raz() ; 
  
  int i = 0 ; 
  unsigned long int cpt_rech_pos = 0 ; 
  unsigned long int cpt_rech_neg = 0 ; 
  string_t * mot_inconnu = string_creer( "XXX" ) ;  
  noeud_t * result = NULL ; 
  for( i=0 ; i<nb_operations ; i++ ) 
    {
      if( random()%2 )
	{
	  /* Recherche positive */
	  i_operation = random()%nb ;
	  if( ! abr_rechercher( &result ,
				arbre ,
				liste_elem_lire(liste_w , i_operation ) ) ) 
	    {
	      printf("Erreur le mot %i n'a pas  ete trouve : " , i ) ;
	      string_printf_cb(liste_elem_lire(liste_w,i_operation)); 
	      printf("\n");
	      return(-1) ; 
	    }	
	  cpt_rech_pos++ ; 
	} 
      else
	{
	 /* Recherche negative */
	  if(  abr_rechercher( &result ,
			       arbre , 
			       mot_inconnu ) ) 
	    {
	      printf("Erreur le mot inconnu a ete trouve dans le dictionnaire\n" ) ;
	      return(-1) ; 
	    }	
	  cpt_rech_neg++ ; 
	}
    }

  gettimeofday(&tp_apres,NULL);

  temps = (tp_apres.tv_sec*1000000+tp_apres.tv_usec) - (tp_avant.tv_sec*1000000+tp_avant.tv_usec) ;

  /* Statistiques */

  printf( "\n-------------------- Statistiques Recherches --------------------\n\n" ) ; 

  printf( "Taille dictionnaire = %d mots\n\n" , nb ); 

  printf( "Nb de recherches demandees      = %7lu\n" , nb_operations ); 
  printf( "   - Nb de recherches positives = %7lu \n" , cpt_rech_pos ); 
  printf( "   - Nb de recherches negatives = %7lu \n\n" , cpt_rech_neg ); 
  
  printf( "Nb de comparaisons\n" );
  printf( "   - Total = %lu\n" , string_comp ); 
  printf( "   - Moyen = %.2lf\n\n" , (double)string_comp/nb_operations ); 

  printf( "Temps de recherche = %lu microsecondes\n" , temps ) ;

  printf( "\n----------------------------------------------------------------\n\n" ) ; 



  if( verbose ) printf( "Test de performances sur destructions elements \n" ) ;
  
  gettimeofday(&tp_avant,NULL);
  string_comp_raz() ;
  cpt_rech_pos = 0 ; 
  cpt_rech_neg = 0 ; 
  for( i=0 ; i<nb_operations ; i++ ) 
    {
      i_operation = random()%(int)nb ;
      if( abr_supprimer( arbre , liste_elem_lire(liste_w , i_operation ) ) )
	cpt_rech_pos++ ;
      else
	cpt_rech_neg++ ;
    }
  
  gettimeofday(&tp_apres,NULL);
  temps = (tp_apres.tv_sec*1000000+tp_apres.tv_usec) - (tp_avant.tv_sec*1000000+tp_avant.tv_usec) ;
  

  /* Statistiques */
  
  printf( "\n-------------------- Statistiques Suppressions --------------------\n\n" ) ; 
  
  printf( "Taille dictionnaire = %d mots\n\n" , nb ); 
  
  printf( "Nb de suppressions demandees      = %7lu\n" , nb_operations ); 
  printf( "   - Nb de suppressions positives = %7lu \n" , cpt_rech_pos ); 
  printf( "   - Nb de suppressions negatives = %7lu \n\n" , cpt_rech_neg ); 
  
  printf( "Nb de comparaisons\n" );
  printf( "   - Total = %lu\n" , string_comp ); 
  printf( "   - Moyen = %.2lf\n\n" , (double)string_comp/nb_operations ); 
  
  printf( "Temps de recherche = %lu microsecondes\n" , temps ) ;
  
  printf( "\n----------------------------------------------------------------\n\n" ) ; 


 if( verbose ) printf( "Destruction du dictionnaire\n" ) ;
 if( ( noerr = liste_detruire( &liste_w ) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }


 if( ( noerr = liste_detruire( &liste_w ) ) )
    { 
      printf("Sortie destruction liste avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }

  /* ------------ */

 if( verbose ) printf( "\n--- Fin du programme %s ---\n" , nomprog ) ; 

  return(0) ; 
}
