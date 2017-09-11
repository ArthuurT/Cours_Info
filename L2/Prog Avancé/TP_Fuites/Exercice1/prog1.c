#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10000
#define TAILLE 500

typedef struct S_s
{
  int * tab_int[TAILLE] ;
  char tab_char[TAILLE] ;
} S_t ;

S_t  tab[N];
int inter;            /* création d'une variable globale intermediaire */

char f3()
{
  char c = 'a' + (rand() % ('z'+1)) ;
  return( c ) ;
}


void f2(int * i)
{
  *i = rand() ;           /* modification par pointeur du contenu de la variable pointé par i */
}


void f1(S_t tab[N])      /* pointeur sur la structure S_t */
{
  int i , j ;
  for( i=0 ; i<N ; i++ )
    {
      for( j=0 ; j<TAILLE ; j++ )
	{
    f2(&inter);                         /* Operation sur les champs de la structure */
	  tab[i].tab_int[j] = &inter;
	  tab[i].tab_char[j] = f3();
	}
    }
}



int main()
{

  printf("Debut du programme\n");

  srand(getpid());

  printf("Appel de f1\n");
  f1(tab) ;                       //Appel du tableau initialisé en global
  printf( "Retour de f1\n") ;

  printf("Fin normale du programme\n");
  return(0);
}
