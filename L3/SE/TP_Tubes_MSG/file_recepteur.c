#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

//#ifdef _LINUX_
#include <string.h>
//#else
//#include <strings.h>
//#endif

#include <file_messages.h>

#define BIG_TAILLE 3000
char big_buffer[BIG_TAILLE] ;
int marq_LU = LU;

void handLU(int sig){
  marq_LU = LU;
}

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128];
     char nom_fichier[128] = "fichiertransfert.txt";
     int fd;
     struct flock verrou_message;
     struct premier_message messagePID;
     struct sigaction signalLU;
     char messageNORMAL[MESSAGES_TAILLE+1];
     int compteur = 0;

     struct timeval t1;
     struct timeval t2;
     double temps_debut;
     double temps_fin;

     strcpy( nomprog , tab_arg[0] );
     if( nb_arg != 1 ){
	        fprintf( stdout , "%s - Recepteur dans la communication par fichier\n\n" , nomprog ) ;
	        fprintf( stderr , "Usage : %s \n" , nomprog ) ;
	        exit(1) ;
      }

      fd = open(nom_fichier,O_RDWR);

      verrou_message.l_type = F_RDLCK;
      verrou_message.l_whence = SEEK_SET;
      verrou_message.l_start = 0;
      verrou_message.l_len = 0;

      signalLU.sa_handler = handLU;
      sigemptyset(&signalLU.sa_mask);
      sigaction(SIGUSR2,&signalLU,NULL);


      while(compteur < MESSAGES_NB){

        while(marq_LU != LU);

        marq_LU = NON_LU;

        if(compteur == 0){
          fcntl(fd,F_SETLKW,verrou_message);
          read(fd,&messagePID,sizeof(premier_message_t));
          gettimeofday(&t1,NULL);
        }else{
          read(fd,&messageNORMAL,sizeof(MESSAGES_TAILLE+1));
        }

        read(fd,big_buffer,BIG_TAILLE);
        lseek(fd,0,SEEK_SET);
        write(fd,big_buffer,BIG_TAILLE);

        //printf("message lu n°%i\n",compteur+1);

        if(compteur == 0)fcntl(fd,F_UNLCK,verrou_message);

        if(compteur < MESSAGES_NB - 1){
          kill(messagePID.pid,SIGUSR1);
        }else{
          gettimeofday(&t2,NULL);
        }
        compteur++;
      }

      temps_debut = t1.tv_sec + (t1.tv_usec/1000000.0);
      temps_fin = t2.tv_sec + (t2.tv_usec/1000000.0);

      printf("Temps d'envoi: %.6lf\n",temps_fin - temps_debut);

      close(fd);
      exit(0);
}
