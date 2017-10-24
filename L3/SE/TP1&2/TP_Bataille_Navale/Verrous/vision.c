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

/*--------------------*
 * Main demon
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;
     char nomprog[256] ;

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


     printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );

     stat(fich_mer,&infomer);
     datemodif = infomer.st_ctime;
     mer_afficher(fd1);

     while(1){

      stat(fich_mer,&infomer);

      if(datemodif != infomer.st_ctime){
        mer_afficher(fd1);
        datemodif = infomer.st_ctime;
      }
     }



     printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

     exit(0);
}
