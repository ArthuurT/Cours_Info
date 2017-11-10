/*
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>


/*
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ;

int boolbateau;
int fd1;
int indice_bateau;
int indice_bateau_est_touche;
int indice_bateau_destruction;
int indice_bateau_cible;
int nb_bateaux;
int cpt_marq = 0;

booleen_t deplace;
booleen_t cible;
booleen_t touche;

coord_t coordcible;
coords_t * coordvoisins;

bateau_t * bateau;
bateau_t * bateau_cible;
bateau_t * bateau_destruction;
bateau_t * bateau_creation;
bateau_t * bateau_est_touche;
bateaux_t * liste_bateaux;

pid_t pid_cible;



/*
 * FONCTIONS LOCALES
 */


 case_t GenererMarque(){
     case_t car = 'A'+ cpt_marq;
     cpt_marq++;
     return car;
 }

 void Creation(int sig, siginfo_t * siginfo, void * contexte){

   bateau_creation = bateau_new(coords_new(), GenererMarque(), siginfo->si_pid);
   boolbateau = mer_bateau_initialiser(fd1,bateau_creation);
   if(boolbateau != CORRECT){
     printf("ERREUR: Pose du bateau\n");
     kill(siginfo->si_pid,SIGTSTP);
   }else{
     bateaux_bateau_add(liste_bateaux,bateau_creation);
     mer_nb_bateaux_lire(fd1,&nb_bateaux);
     mer_nb_bateaux_ecrire(fd1,nb_bateaux+1);
   }

   mer_afficher(fd1);
 }

 void Action(int sig, siginfo_t * siginfo, void * contexte){

  indice_bateau = bateaux_pid_seek(liste_bateaux,siginfo->si_pid);
  bateau = bateaux_bateau_get(liste_bateaux,indice_bateau);
  mer_bateau_cible_acquerir(fd1,bateau,&cible,&coordcible);
  if(cible != VRAI)
    printf("ERREUR: Tir raté\n");
  else{

    /* Recuperation du bateau ciblé */

    indice_bateau_cible = bateaux_coord_seek(liste_bateaux,coordcible);
    bateau_cible = bateaux_bateau_get(liste_bateaux,indice_bateau_cible);
    pid_cible = bateau_pid_get(bateau_cible);

    /* Indique au bateau_cible qu'il est ciblé */

    kill(pid_cible,SIGUSR1);
    sleep(2);
    mer_afficher(fd1);
    sleep(2);


    /* Phase de déplacement */

   mer_voisins_rechercher(fd1,bateau,&coordvoisins);
   mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);
   kill(siginfo->si_pid,SIGPIPE);
   mer_afficher(fd1);
  }
 }

void AiGagne(int sig, siginfo_t * siginfo, void * contexte){
   mer_nb_bateaux_lire(fd1,&nb_bateaux);
   if(nb_bateaux == 1){
     kill(siginfo->si_pid,SIGILL);
     mer_afficher(fd1);
   }
}

void ReponseOui (int sig, siginfo_t * siginfo, void * contexte){
  mer_bateau_couler(fd1,bateaux_bateau_get(liste_bateaux,bateaux_pid_seek(liste_bateaux,siginfo->si_pid)));
  bateaux_bateau_del(liste_bateaux,bateaux_pid_seek(liste_bateaux,siginfo->si_pid));
  mer_nb_bateaux_lire(fd1,&nb_bateaux);
  mer_nb_bateaux_ecrire(fd1,nb_bateaux-1);
  mer_afficher(fd1);
}

void sigactionSansErreur(int sig, struct sigaction * new, struct sigaction * old){
  int r;
  r = sigaction(sig,new,old);
  if(r != 0){
    perror("Erreur sigaction");
    exit(-1);
  }
}

/*
 * Programme Principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     int largeur_mer = 10;
     int longueur_mer = 10;

     /*----------*/

     /*
      * Capture des parametres
      */

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> \n",
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );

     /*
      * Affichage pid bateau amiral
      */

     printf(" PID bateau amiral = %d\n" , getpid() ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     printf("\n\n\t----- Debut du jeu -----\n\n");

     fd1 = open(fich_mer,O_RDWR);

     mer_initialiser(fich_mer,largeur_mer,longueur_mer);
     mer_afficher(fd1);


     liste_bateaux = bateaux_new();

     /* Capture du signal création */

     struct sigaction screation;
     screation.sa_sigaction = Creation;
     screation.sa_flags = SA_SIGINFO;
     sigemptyset(&screation.sa_mask);
     sigaddset(&screation.sa_mask,SIGFPE);
     sigaddset(&screation.sa_mask,SIGILL);
     sigactionSansErreur(SIGCHLD,&screation,NULL);


     /* Capture du signal action */

     struct sigaction saction;
     saction.sa_sigaction = Action;
     saction.sa_flags = SA_SIGINFO;
     sigemptyset(&saction.sa_mask);
     sigaddset(&saction.sa_mask,SIGCHLD);
     sigaddset(&saction.sa_mask,SIGILL);
     sigactionSansErreur(SIGFPE,&saction,NULL);


     /* Capture du signal AiGagne */

     struct sigaction sgagne;
     sgagne.sa_sigaction = AiGagne;
     sgagne.sa_flags = SA_SIGINFO;
     sigemptyset(&sgagne.sa_mask);
     sigaddset(&sgagne.sa_mask,SIGFPE);
     sigaddset(&sgagne.sa_mask,SIGCHLD);
     sigactionSansErreur(SIGILL,&sgagne,NULL);

     /* Capture du signal ReponseOui */

     struct sigaction soui;
     soui.sa_sigaction = ReponseOui;
     soui.sa_flags = SA_SIGINFO;
     sigemptyset(&soui.sa_mask);
     sigaddset(&soui.sa_mask,SIGFPE);
     sigaddset(&soui.sa_mask,SIGCHLD);
     sigaddset(&soui.sa_mask,SIGILL);
     sigactionSansErreur(SIGUSR1,&soui,NULL);


    while(1){

        pause();

    }


     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}
