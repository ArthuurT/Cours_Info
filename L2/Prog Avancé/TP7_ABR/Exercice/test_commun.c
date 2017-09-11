#include <commun.h>

int
main( int argc , char * argv[] ) 
{
  char nomprog[MAX_STRING] ; 

  strcpy(nomprog , argv[0] ) ; 

  printf( "-----Debut %s ----\n" , nomprog ) ; 

  printf( "Test reponse Oui/Non\n")  ;
  booleen_t rep = VRAI ; 
  while( rep ) 
    {
      rep = OuiNon_saisir("Voulez vous recommencer ?") ;
    }

  printf( " ----- Fin %s -----\n" , nomprog ) ; 

  return(0) ; 
}
