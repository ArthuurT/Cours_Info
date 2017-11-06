/*
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int Energie ;
bateau_t * bateau;
booleen_t boolbateau;
booleen_t deplace;
coords_t * coordvoisins;

/*
 * Handlers
 */

void Creation(int sig){

  bateau = bateau_new(coords_new(), marque, getpid());
  boolbateau = mer_bateau_initialiser(fd1,bateau);

  if(boolbateau != CORRECT) printf("ERREUR: Pose du bateau -- %i",getpid());

}

void Tir(int sig){

}

void Deplacement(int sig){

  mer_voisins_rechercher(fd1,bateau,&coordvoisins);
  mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);
  if(deplace == VRAI){
    printf("\n[Bateau %c]:Deplacement effectué\n",marque);
    energie = energie * 0.95;
    printf("[Bateau %c]: Energie restante : %f\n",marque,energie);
  }
}






/*
 * Programme Principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;
  pid_t pid_amiral ;
  pid_t pid_bateau = getpid()  ;

  /*----------*/

  /*
   * Capture des parametres
   */

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n",
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , tab_arg[0] );
  sscanf( tab_arg[1] , "%d" , &pid_amiral ) ;

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  Energie = random()%BATEAU_MAX_ENERGIE ;

  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );






  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
