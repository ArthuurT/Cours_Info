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
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;
     char nom_tube[128] = "tube";
     char message[MESSAGES_TAILLE+1];
     double temps_t2;
     double temps_t1;
     struct timeval date_envoi;
     struct timeval date_reception;
     const char car = 'x';
     int fd_tube;
     int compteur = 0;

     /*----------*/

     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }

     if((fd_tube = open(nom_tube,O_WRONLY,0)) == -1){
       perror("Erreur : ouverture du tube nommé en écriture impossible");
       exit(-3);
     }

     printf("Ouverture du tube nommé en écriture réussi\n");

     pipe_remplir(message,car);
     gettimeofday(&date_envoi,NULL);
     temps_t1 = date_envoi.tv_sec + (date_envoi.tv_usec/1000000.0);

     printf("Envoi des messages ...\n\n");
     while(compteur < MESSAGES_NB){
       write(fd_tube,message,sizeof(MESSAGES_TAILLE+1));
       compteur++;
     }

     close(fd_tube);

     if((fd_tube = open(nom_tube,O_RDONLY,0)) == -1){
       perror("Erreur : ouverture du tube nommé en lecture impossible");
       exit(-2);
     }

     printf("Ouverture du tube nommé en lecture réussi\n");
     printf("Attente d'un message ...\n\n");

     read(fd_tube,&date_reception,sizeof(struct timeval));
     temps_t2 = date_reception.tv_sec + (date_reception.tv_usec/1000000.0);

     printf("Temps d'envoi: %.6lf\n",temps_t2 - temps_t1);
     printf("Fin de l'emetteur\n");

     close(fd_tube);
     exit(0);

}
