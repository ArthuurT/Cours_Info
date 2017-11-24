#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

#include <msg_messages.h>

int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;
     int erreur;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Emetteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     /* Programme Principal */

     int cle_file;
     long compteur = 0;
     const char car = 'x';
     double temps_t1;
     double temps_t2;
     struct timeval date_envoi;
     message_t requete;
     reponse_t reponse;
     size_t lg = sizeof(corps_reponse_t);

     requete.type = MSG_TYPE_RECEPTEUR;
     requete.corps.pid = getpid();
     msg_remplir(&requete,car);

     cle_file = msgget(CLE_BAL,0666);
     printf("cle = %i\n",cle_file);
     gettimeofday(&date_envoi,NULL);
     temps_t1 = date_envoi.tv_sec + (date_envoi.tv_usec/1000000.0);

     /* Envoi des MESSAGES_NB messages à la suite */

     while(compteur < MESSAGES_NB){
       if(msgsnd(cle_file,&requete,sizeof(corps_t),0) == -1)
       printf("%s\n",strerror(errno));
       compteur++;
     }

     /* Reception du message contenant la date d'arrivé du dernier message */

     msgrcv(cle_file,&reponse,lg,getpid(),0);
     temps_t2 = reponse.corps.date_reception.tv_sec + (reponse.corps.date_reception.tv_usec/1000000.0);

     printf("Temps d'envoi: %.6lf\n",temps_t2 - temps_t1);
     exit(0);
}
