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
int marqEstTouche = 0;
int marqEstCree = 0;
int marqAGagne = 0;
pid_t pid_amiral ;

/*
 * Handlers
 */

void DeplacementTirReussi(int sig){
  printf("Deplacement + Tir réussi (%i)\n",getpid());
  signal(SIGPIPE,DeplacementTirReussi);
  Energie = Energie * 0.95;
}

void EstTouche(int sig){
  printf("Bateau ciblé (%i)\n",getpid());
  signal(SIGUSR1,EstTouche);
  if(Energie < BATEAU_SEUIL_BOUCLIER){
    marqEstTouche = 1;
    kill(pid_amiral,SIGUSR1);
    printf("Bateau coulé (%i)\n",getpid());
    exit(0);
  }
}

void EstCree(int sig){
  printf("Plus de place sur la mer\n");
  marqEstCree = 1;
}

void AGagne(int sig){
  printf("Le processus %i a gagné\n",getpid());
  marqAGagne = 1;
}


void killSansErreur(pid_t pid, int sig){
  int r;
  r = kill(pid,sig);
  if(r != 0){
    perror("Erreur kill");
    exit(-1);
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

  sleep(2); // SECURITE: On s'assure que l'amiral est bien en place sur la mer

  /* Capture des signaux */

  signal(SIGPIPE,DeplacementTirReussi);
  signal(SIGUSR1,EstTouche);
  signal(SIGTSTP,EstCree);
  signal(SIGILL,AGagne);

  /* Création du bateau */



  killSansErreur(pid_amiral,SIGCHLD);

  printf("Tentative création bateau\n");
  sleep(5);

  if(marqEstCree == 1) killSansErreur(getpid(),SIGKILL);
  else printf("Bateau créé\n");

    /* Attente */

    sleep(2);

  do{

    /* Déplacement du bateau + tir */
    killSansErreur(pid_amiral,SIGFPE);
    sleep(4);

    /* Ai-je gagné ? */

    killSansErreur(pid_amiral,SIGILL);
    sleep(4);

  }while(marqEstTouche == 0 && marqAGagne == 0);

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
