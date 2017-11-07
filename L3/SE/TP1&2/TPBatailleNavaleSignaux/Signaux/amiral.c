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
int nb_bateaux;

booleen_t deplace;
booleen_t cible;
booleen_t touche;

coord_t coordcible;
coords_t * coordvoisins;

bateau_t * bateau;
bateau_t * bateau_destruction;
bateau_t * bateau_creation;
bateau_t * bateau_est_touche;
bateaux_t * liste_bateaux;

/*
 * FONCTIONS LOCALES
 */

 void Creation(int sig, siginfo_t * siginfo){

   bateau_creation = bateau_new(coords_new(), marque, siginfo.si_pid);
   boolbateau = mer_bateau_initialiser(fd1,bateau_creation);
   if(boolbateau != CORRECT) printf("ERREUR: Pose du bateau\n");
   else{
     bateaux_bateau_add(liste_bateaux,bateau_creation);
     mer_nb_bateaux_lire(fd1,&nb_bateaux);
     mer_nb_bateaux_ecrire(fd1,nb_bateaux+1);

     kill(siginfo.si_pid,SIGTST);
   }

 }

 void Action(int sig, siginfo_t * siginfo){

   indice_bateau = bateaux_pid_seek(liste_bateaux,siginfo.si_pid);
   bateau = bateaux_bateau_get(liste_bateaux,indice_bateau);

   mer_bateau_cible_acquerir(fd1,bateau,&cible,&coordcible);
   if(cible == VRAI) mer_bateau_cible_tirer(fd1,coordcible);
   else printf("ERREUR: Tir raté\n");

   mer_voisins_rechercher(fd1,bateau,&coordvoisins);
   mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);

   kill(siginfo.si_pid,SIGINFO);

 }

 void EstTouche(int sig, siginfo_t * siginfo){

   indice_bateau_est_touche = bateaux_pid_seek(liste_bateaux,siginfo.si_pid);
   bateau_est_touche = bateaux_bateau_get(liste_bateaux,indice_bateau_est_touche);

   mer_bateau_est_touche(fd1,bateau_est_touche,&touche);

   if(touche == VRAI) kill(signinfo.si_pid,SIGUSR2);

 }


 void Destruction(int sig, siginfo_t * siginfo){

   indice_bateau_destruction = bateaux_pid_seek(liste_bateaux,siginfo.si_pid);
   bateau_destruction = bateaux_bateau_get(liste_bateaux,indice_bateau_destruction);

   mer_bateau_couler(fd1,bateau_destruction);



 }


/*
 * Programme Principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;

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

     liste_bateaux = bateaux_new();

     /* Capture du signal création */

     sigaction screation;
     screation.sa_sigaction = Creation;
     screation.sa_flags = SA_SIGINFO;
     sigemptyset(&screation.sa_mask);

     sigaddset(&screation.sa_mask,SIGFPE);              // Pas d'action sur la mer lors de la création d'un bateau
     sigprocmask(SIG_BLOCK,&screation.sa_mask,NULL);

     sigaction(SIGCHLD,&screation,NULL);


     /* Capture du signal action */

     sigaction saction;
     saction.sa_handler = Action;
     saction.sa_flags = SA_SIGINFO;
     sigaction(SIGFPE,&saction,NULL);


     /* Capture du signal EstTouche */

     sigaction sesttouche;
     sesttouche.sa_handler = EstTouche;
     sesttouche.sa_flags = SA_SIGINFO;

     sigaddset(&sesttouche.sa_mask,SIGFPE);            // Pas d'action sur la mer lors de la vérification d'un bateau touché
     sigprocmask(SIG_BLOCK,&sesttouche.sa_mask,NULL);

     sigaction(SIGUSR1,&sesttouche,NULL);

     /* Capture du signal Destruction */

     sigaction sdestruction;
     sdestruction.sa_handler = Action;
     sdestruction.sa_flags = SA_SIGINFO;

     sigaddset(&sdestruction.sa_mask,SIGFPE);            // Pas d'action sur la mer lors de la destruction d'un bateau
     sigprocmask(SIG_BLOCK,&sdestruction.sa_mask,NULL);

     sigaction(SITERM,&destruction,NULL);


     while(1);


     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}
