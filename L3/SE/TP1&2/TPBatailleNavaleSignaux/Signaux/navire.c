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
int boolbateau;

booleen_t deplace;
booleen_t cible;

coord_t coordcible;
coords_t * coordvoisins;

bateau_t * bateau;

/*
 * Handlers
 */

void Creation(int sig){

  bateau = bateau_new(coords_new(), marque, pid_bateau);
  boolbateau = mer_bateau_initialiser(fd1,bateau);
  if(boolbateau != CORRECT) printf("ERREUR: Pose du bateau\n");

}

void Tir(int sig){

  mer_bateau_cible_acquerir(fd1,bateau,&cible,&coordcible);
  if(cible == VRAI) mer_bateau_cible_tirer(fd1,coordcible);
  else printf("ERREUR: Tir raté\n");

}

void Deplacement(int sig){

  printf("SIGNAL DEPLACEMENT RECU\n")
  mer_voisins_rechercher(fd1,bateau,&coordvoisins);
  mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);
  if(deplace == VRAI) Energie = Energie * 0.95;
  else printf("ERREUR: Deplacement impossible\n");

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

  /* Création du bateau */

  sigaction screation
  screation.sa_handler = Creation;
  sigemptyset(&screation.sa_mask);
  sigaddset(&screation.sa_mask,SIGFPE);
  sigprocmask(SIG_BLOCK,&screation.sa_mask,NULL);
  sigaction(SIGCHLD,&screation,NULL);
  kill(pid_amiral,SIGCHLD);

  /* Attente */


  /* Déplacement du bateau */

  sigaction sdeplacement
  sdeplacement.sa_handler = Deplacement;
  sigaction(SIGFPE,&sdeplacement,NULL);
  kill(pid_amiral,SIGFPE);

  /* Attente */

  wait(2);

  /* Tir du bateau */

  sigaction stir
  stir.sa_handler = Tir;
  sigaction(SIGFPE,&stir,NULL);
  kill(pid_amiral,SIGFPE);

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}
