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
int EstTouche = 0;
int EstCree = 0;

/*
 * Handlers
 */

void DeplacementTirReussi(int sig){
  printf("Deplacement + Tir réussi\n");
  signal(SIGINFO,DeplacementTirReussi);
  Energie = Energie * 0.95;
}

void EstTouche(int sig){
  printf("Bateau touché\n");
  if(Energie < BATEAU_SEUIL_BOUCLIER) EstTouche = 1;
}

void EstCree(int sig){
  printf("Bateau créer");
  EstCree = 1;
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

  sleep(2); // SECURITE: On s'assure que l'amiral est bien en place sur la mer

  /* Capture des signaux */

  signal(SIGINFO,DeplacementTirReussi);
  signal(SIGUSR2,EstTouche);
  signal(SIGTST,EstCree);

  /* Création du bateau */

  while(EstCree == 0){

    kill(pid_amiral,SIGCHLD);
    sleep(1);

  }

  do{

    /* Attente */

    sleep(2);

    /* Déplacement du bateau + tir */

    kill(pid_amiral,SIGFPE);

    /* Est touché ? */

    kill(pid_amiral,SIGUSR1);
    sleep(1);

  while(EstTouche == 0);

  kill(pid_amiral,SIGTERM); // Demande de destruction du bateau

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
