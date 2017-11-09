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

/*
 * Handlers
 */

void DeplacementTirReussi(int sig){
  printf("Deplacement + Tir réussi\n");
  signal(SIGPIPE,DeplacementTirReussi);
  Energie = Energie * 0.95;
}

void EstTouche(int sig){
  printf("Bateau touché\n");
  signal(SIGUSR2,EstTouche);
  if(Energie < BATEAU_SEUIL_BOUCLIER) marqEstTouche = 1;
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
  signal(SIGUSR2,EstTouche);
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
    printf("Signal deplacement %i\n",getpid());
    sleep(4);

    /* Est touché ? */

    killSansErreur(pid_amiral,SIGUSR1);
    printf("Signal touche %i\n",getpid());
    sleep(4);

    /* Ai-je gagné ? */

    killSansErreur(pid_amiral,SIGILL);
    printf("Signal gagne %i\n",getpid());
    sleep(4);

  }while(marqEstTouche == 0 && marqAGagne == 0);

    if(marqEstTouche == 0)killSansErreur(pid_amiral,SIGBUS); // Demande de destruction du bateau
    else printf("Bateau (%i) a gagné !!",getpid());

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
