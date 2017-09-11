#include <ab_animaux.h>

int
main( int argc  , char * argv[] ) 
{
  err_t noerr = OK; 
  ab_t * arbre = NULL ; 
  char nomprog[MAX_STRING] ;
  booleen_t continuer = VRAI ;
  char nom_fichier_sauvegarde[MAX_STRING] ; 
  char nom_fichier_animaux[MAX_STRING] ; 
  booleen_t sauvegarde = FAUX ; 

  strcpy( nomprog , argv[0] ) ; 

  printf( "----- Debut %s ----- \n"  , nomprog ) ; 

  printf("Veuillez entrer le nom du fichier de classification des animaux :" ) ;
  fflush(stdout) ; 
  scanf("%s" , nom_fichier_animaux ) ;

  /*
   * Chargement avec copie/destruction obligatoirement 
   */
  if( ( noerr = ab_charger( &arbre  , nom_fichier_animaux , 			
			    string_copier_cb , string_detruire_cb , 
			    string_charger_cb ) ) )  
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      err_print(noerr) ;
      return(noerr) ; 
    }
  

  printf("Affichage\n\n") ; 
  ab_animaux_afficher( arbre , string_string_afficher_cb,0 ) ; 
  printf( "\n");

  printf("Reconnaissance\n\n") ; 

  continuer = VRAI ; 
  while( continuer )
    {
      ab_animaux_reconnaitre( arbre , string_copier_cb , string_string_afficher_cb ) ; 
      continuer = OuiNon_saisir("Voulez vous recommencer ? ") ;       
    }
  printf( "\n");

  printf("Affichage apres reconnaissance\n\n") ; 
  ab_animaux_afficher( arbre , string_string_afficher_cb,0 ) ; 
  printf( "\n");
  
  sauvegarde = OuiNon_saisir("Voulez vous sauvegarder le nouvel arbre ?") ; 
  if( sauvegarde ) 
    {
      /* Saisie nom ficher sauvegarde */
      printf("Veuillez alors entrer le nom du fichier de sauvegarde :" ) ;
      fflush(stdout) ; 
      scanf("%s" , nom_fichier_sauvegarde ) ;
      
      if( ( noerr = ab_sauver( arbre , 
			       nom_fichier_sauvegarde , 
			       string_sauver_cb ) ) )
	{
	  printf("Sortie erreur %d\n" , noerr ) ;
	  err_print(noerr) ; 
	  return(noerr) ; 
	}
    }
  
  printf( "----- Fin %s -----\n" , nomprog ) ; 

  return(0) ; 
}
