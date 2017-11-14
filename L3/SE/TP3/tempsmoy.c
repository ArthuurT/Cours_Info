#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TAILLE_COMMANDE 20

int floatcomp(const void* elem1, const void* elem2)
{
    if(*(const float*)elem1 < *(const float*)elem2)
        return -1;
    return *(const float*)elem1 > *(const float*)elem2;
}

float tempsMoyen(float * tab, int n){

	if(n % 2 == 1) return tab[n / 2];
	else return ((tab[n / 2] + tab[(n / 2)- 1]) / 2);
}


int main(int argc, char * argv[]){


	/* Variables */

	int i, j, k;
	int nb_repet, nb_processus;
	float moyenne;
	int tube[2];
	float tempsPs;
	int cr, cr1;

	char commande[TAILLE_COMMANDE];

	struct timeval t1, t2,res;


	if(argc != 4){
		printf("Utilisation : ./<nom_executable> <nb_repetitions> <commande> <nb_processus>");
		exit(0);
	}

	nb_repet = atoi(argv[1]);
	nb_processus = atoi(argv[3]);
	strcpy(commande,argv[2]);

	float M[nb_processus];					/*  Contient les les temps moyens d'executions de chaque processus Mi = Ti / K */
	int fd_devnull = open("/dev/null", O_RDWR);

  pipe(tube);

	/* Création de nb_processus fils */

	for(i = 0; i < nb_processus; i++){
		switch(fork()){

			case -1:		perror("Erreur fork n°1");
							    exit(1);

			case 0:			close(tube[0]);

							    gettimeofday(&t1,NULL);

    							/* Creation de nb_repet processus sous-fils */

    							for(j = 0; j < nb_repet; j++){
    								switch(fork()){

    								  case -1: perror("Erreur fork n°2");
    													 exit(1);

    									case 0:	dup2(fd_devnull,1);
    													close(fd_devnull);
    													execlp(commande,commande,NULL);
                              exit(3);

								   }
							    }

							    while(wait(&cr1) != -1){
                    if(cr1 > 768){
                      exit(2);
                    }
                    else if(cr1 != 0){
                      exit(cr1);
                    }
                  }

							    gettimeofday(&t2,NULL);

    							/*
    							 *	On soustrait t2 le temps final à t1 le temps initial -> on obtient T le temps d'execution.
    							 *	Il suffit de divisé le tous par le nombre de repetition pour obtenir le temps moyen.
    							 */


                  if (t2.tv_sec > t1.tv_sec)
                      timersub(&t2,&t1,&res);
                  else if (t2.tv_sec < t1.tv_sec)
                       timersub(&t1, &t2, &res);
                   else  // t2.tv_sec == t1.tv_sec
                   {
                       if (t2.tv_usec >= t1.tv_usec)
                           timersub(&t2, &t1, &res);
                       else
                           timersub(&t1, &t2, &res);
                   }

    							tempsPs = res.tv_sec + res.tv_usec / nb_repet;
                  tempsPs = tempsPs / 1000;
    							write(tube[1],&tempsPs,sizeof(float));
                  close(tube[1]);
                  exit(0);
	 }
 }

  for(i = 0; (i < nb_processus) && (wait(&cr) != -1); i++){
    printf("cr = %i\n",cr);
    if(cr != 0){
      printf("cr = %i\n",cr);
      if(cr == 512){
          printf("Erreur commande inexistante\n");
      }else if(cr > 128){
          printf("Erreur cr = %i\n", cr);
      }else{
          printf("Interrompu par le signal n° %i",cr);
      }
      exit(-1);
    }else{
      read(tube[0],&M[i],sizeof(float));
    }
  }

  printf("Avant le tri \n");
  for(i = 0; i < nb_processus; i++){
    printf("M[%i] = %f\n",i,M[i]);
  }

	qsort(M,nb_processus,sizeof(float),floatcomp);

  printf("\n");

  printf("Apres le tri \n");
  for(i = 0; i < nb_processus; i++){
    printf("M[%i] = %f\n",i,M[i]);
  }

	moyenne = tempsMoyen(M,nb_processus);

	printf("\n\nEn moyenne la commande '%s' met %f secondes à s'executer\n\n",commande,moyenne);


}
