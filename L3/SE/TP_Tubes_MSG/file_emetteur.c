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

int pid_receveur;
int marq_LU = LU;

void handLU(int sig, siginfo_t * info, void * undef){
  pid_receveur = info->si_pid;
  marq_LU = LU;
}

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128];
     char nom_fichier[128] = "fichiertransfert.txt";
     char car = 'x';
     int fd;
     struct flock verrou_message;
     int compteur = 0;
     struct premier_message messagePID;
     char messageNORMAL[MESSAGES_TAILLE+1];
     struct sigaction signalREC;

     strcpy( nomprog , tab_arg[0] );
     if(nb_arg != 1 ){
        fprintf( stdout , "%s - Emetteur dans la communication par fichier\n\n" , nomprog ) ;
      	fprintf( stdout , "Usage : %s \n" , nomprog ) ;
      	exit(1) ;
      }


       fd = open(nom_fichier,O_CREAT | O_WRONLY);

       verrou_message.l_type = F_WRLCK;
       verrou_message.l_whence = SEEK_SET;
       verrou_message.l_start = 0;
       verrou_message.l_len = 0;

       signalREC.sa_sigaction = handLU;
       signalREC.sa_flags = SA_SIGINFO;
       sigemptyset(&signalREC.sa_mask);
       sigaction(SIGUSR1,&signalREC,NULL);


       messagePID.pid = getpid();
       file_remplir(messagePID.message,car);
       file_remplir(messageNORMAL,car);


       while(compteur < MESSAGES_NB){
         lseek(fd,0,SEEK_SET);

         while(marq_LU != LU);

         marq_LU = NON_LU;

         if(compteur == 0){
           fcntl(fd,F_SETLKW,verrou_message);
           write(fd,&messagePID,sizeof(premier_message_t));
           fcntl(fd,F_UNLCK,verrou_message);
         }else{
           write(fd,&messageNORMAL,sizeof(MESSAGES_TAILLE+1));
           kill(pid_receveur,SIGUSR2);
         }

         //printf("message envoyé n°%i\n",compteur+1);
         compteur++;
       }


       close(fd);
       exit(0);
}
