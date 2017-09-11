#include <commun.h>

extern 
void err_print( const err_t noerr ) 
{
  switch( noerr ) 
    {
    case OK : 
      printf("OK") ; 
      break ; 

    case ERR_DEB_MEMOIRE : 
      printf("Debordement memoire\n") ; 
      break ; 
    case ERR_SCANF : 
      printf( "Erreur de scanf: argument manquant dans un fichier\n") ; 
      break ; 
    case ERR_NOM_FICHIER : 
      printf( "Erreur: nom de fichier inconnu\n" );
      break ;
    case ERR_ELEM_UNK : 
      printf( "Element inconnu\n" );
      break ;

   case ERR_LISTE_IND_ELEM :
      printf("Erreur d'indice dans une liste\n") ; 
      break ;

    case ERR_ARBRE_NOEUD :
      printf("Erreur sur un noeud dans un arbre\n") ; 
      break ;

    default :
      printf( "Code d'erreur inconnu\n" );
      break ;
    }
}

/* 
 * Saisie reponse de type Oui/Non 
 * retour VRAI si reponse positive
 *        FAUX sinon 
 * Reponses possibles dans l'intervalle [OoNnYy] 
 */

extern
booleen_t OuiNon_saisir( char * message )
{
  char rep[2] ;

  printf( "%s  " , message ) ; 
  fflush(stdout) ; 
  scanf("%s" , rep ) ; 
  getchar() ;
  while( strchr( "ONonYy", rep[0] ) == NULL )
    {
      printf( "Reponse [ONonYy] : ") ; fflush(stdout) ; 
      scanf("%s" , rep ) ; 
      getchar();
    }

  if(  strchr( "OoYy", rep[0] ) != NULL )
    return(VRAI) ;
  else
    return(FAUX) ; 
}

