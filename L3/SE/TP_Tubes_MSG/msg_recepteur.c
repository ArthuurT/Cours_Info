#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     int cle_file;
     int compteur = 0;
     struct timeval date_reception;
     message_t reception;
     reponse_t requete;
     size_t lg = sizeof(corps_reponse_t);

     cle_file = msgget(CLE_BAL, IPC_CREAT | 0666);

     /* Recuperation des MESSAGES_NB messages */

     while(compteur < MESSAGES_NB){
       msgrcv(cle_file,&reception,sizeof(corps_t),MSG_TYPE_RECEPTEUR,0);

       /* Si on lit le dernier message, alors on envoi la date courante */

       if(compteur == MESSAGES_NB - 1){
         gettimeofday(&date_reception,NULL);
         requete.type = reception.corps.pid;
         requete.corps.date_reception = date_reception;
         msgsnd(cle_file,&requete,lg,0);
       }
       compteur++;

     }

     exit(0);
}
