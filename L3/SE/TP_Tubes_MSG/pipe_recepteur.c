#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
//#ifdef _LINUX_
#include <string.h>
//#else
//#include <strings.h>
//#endif
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;
     char nom_tube[128] = "tube";
     char message[MESSAGES_TAILLE+1];
     struct timeval date_envoi;
     int fd_tube;
     int compteur = 0;

     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	     fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
	     fprintf( stderr , "usage : %s \n" , nomprog );
	     exit(-1);
     }


     if( nb_arg != 1 )
     {
	     fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	     fprintf( stderr , "usage : %s \n" , nomprog );
	     exit(-1);
     }

     mknod(nom_tube, S_IFIFO | 0666, 0);

     if((fd_tube = open(nom_tube,O_RDONLY,0)) == -1){
       perror("Erreur : ouverture du tube nommé en lecture impossible");
     }

     printf("Ouverture du tube nommé en lecture réussi\n");
     printf("Attente des messages ...\n\n");

     while(compteur < MESSAGES_NB){
       read(fd_tube,message,sizeof(MESSAGES_TAILLE+1));

       if(compteur == MESSAGES_NB - 1){
         close(fd_tube);
         if((fd_tube = open(nom_tube,O_WRONLY,0)) == -1){
           perror("Erreur : ouverture du tube nommé en écriture impossible");
         }
         printf("Ouverture du tube nommé en écriture réussi\n");
         printf("Ecriture d'un message ...\n\n");
         gettimeofday(&date_envoi,NULL);
         write(fd_tube,&date_envoi,sizeof(struct timeval));
         close(fd_tube);
       }
       compteur++;

     }

     printf("Fin du recepteur\n");
     exit(0);

}
