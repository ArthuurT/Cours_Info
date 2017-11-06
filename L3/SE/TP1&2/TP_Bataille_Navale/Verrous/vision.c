#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>


struct stat infomer;
time_t datemodif;

void PoseVerrouEnTete(int fd1, int mode){

  struct flock verrouEnTete;


    verrouEnTete.l_type = mode;
    verrouEnTete.l_whence = SEEK_SET;
    verrouEnTete.l_start = 0;
    verrouEnTete.l_len = MER_TAILLE_ENTETE;

    fcntl(fd1,F_SETLKW,verrouEnTete);

  if(mode == 0 || mode == 1) printf("\nPose du verrou EnTete --> SUCCESS\n");
  else printf("Desactivation du verrou EnTete --> SUCCESS");

}

/*--------------------*
 * Main demon
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;
     int largeur_mer = 10;
     int longueur_mer = 10;
     int moment = 0;

     /*----------*/

     if( nb_arg != 2 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer>\n",
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );

     int fd1 = open(fich_mer,O_RDONLY);
     mer_initialiser(fich_mer,largeur_mer,longueur_mer);


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );

     stat(fich_mer,&infomer);
     datemodif = infomer.st_ctime;
     mer_afficher(fd1);

     while(1){

      stat(fich_mer,&infomer);

      if(datemodif != infomer.st_ctime){

        if(moment == 0){
          printf("\n\nPOSE DES BATEAUX, VEUILLEZ PATIENTER !\n\n");
          sleep(TEMPS_ATTENTE*2);
          moment++;
        }

        PoseVerrouEnTete(fd1,F_RDLCK);
        mer_afficher(fd1);
        PoseVerrouEnTete(fd1,F_UNLCK);
        datemodif = infomer.st_ctime;
      }
     }

     mer_initialiser(fich_mer,largeur_mer,longueur_mer);

     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
