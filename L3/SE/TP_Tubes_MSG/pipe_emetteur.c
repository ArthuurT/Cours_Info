#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
#include <sys/time.h>
//#ifdef _LINUX_
#include <string.h>
//#else
//#include <strings.h>
//#endif
//#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;
     char nomtube[128] = "tube";
     int fd_tube;

     /*----------*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }

     if(mknod(nom_tube, S_IFIFO | 0666, 0)){
       perror("Erreur: création du tube nommé impossible");
       exit(-3);
     }

     printf("Création du tube réussi\n");





}
