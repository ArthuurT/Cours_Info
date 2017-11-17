#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


/* Constantes */

#define TAILLE_COMMANDE 20
#define TAILLE_MAX 256

/* Fonctions */

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

void afficher_tab(float * tab, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("M[%i] = %f\n",i,tab[i]);
  }
}

/* Programme principal */

int main(int argc, char * argv[]){


	/* Variables */

	int i, j, k;
	int nb_repet, nb_processus;
	float moyenne;
	int tube[2];
  int tube_err[2];
	float tempsPs;
	int cr, cr1;

	char commande[TAILLE_COMMANDE];
  char err_retour[TAILLE_MAX];

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
  pipe(tube_err);


	/* Création de nb_processus fils */

	for(i = 0; i < nb_processus; i++){
		switch(fork()){

			case -1:		perror("Erreur fork n°1");
							    exit(1);

			case 0:			close(tube[0]);

							    gettimeofday(&t1,NULL);

    							/* Creation de nb_repet processus petit-fils */

    							for(j = 0; j < nb_repet; j++){
    								switch(fork()){

    								  case -1: perror("Erreur fork n°2");
    													 exit(1);

    									case 0:	 dup2(fd_devnull,1);
    													 close(fd_devnull);
    													 execlp(commande,commande,NULL);
                               exit(3);

								   }
							    }

                  /* On attend que tous les petit-fils se termine */

                     while(wait(&cr1) != -1){

                      if(cr1 != 0){

                        if(WIFSIGNALED(cr1)){                                     // Cas 1 : interrompu par un signal
                          char erreur2[TAILLE_MAX];
                          sprintf(erreur2,"Processus arrêté: Signal n°%i",WTERMSIG(cr1));
                          write(tube_err[1],erreur2,TAILLE_MAX);
                          exit(2);
                        }

                        if(WIFEXITED(cr1)){                                       // Cas 2 : sortie avec exit
                          char erreur1[TAILLE_MAX];

                          if((WEXITSTATUS(cr1)) == 3)
                            sprintf(erreur1,"Commande %s innexistante, veuillez réessayer",commande);

                          else{
                            sprintf(erreur1,"Erreur: code sortie %i",WEXITSTATUS(cr1));
                          }

                          write(tube_err[1],erreur1,TAILLE_MAX);
                          exit(3);


                        }
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

    							tempsPs = (res.tv_sec + res.tv_usec) / nb_repet;

                  /* On ecrit dans le tube le temps moyen qu'a pris le fils à effectuer la commande */

    							write(tube[1],&tempsPs,sizeof(float));
                  exit(0);

	 }
  }


  /*  Dès que tous les processus fils se termine, on lit dans le tube */

      while(wait(&cr) != -1){


        if(cr != 0){
            read(tube_err[0],err_retour,TAILLE_MAX);
            printf("%s",err_retour);
            exit(1);
        }

      }

    for(i = 0; i < nb_processus; i++)
      read(tube[0],&M[i],sizeof(float));


  /* Calcul + Affichage */

  printf("Avant le tri: \n");
  afficher_tab(M,nb_processus);
	qsort(M,nb_processus,sizeof(float),floatcomp);
  printf("\n");
  printf("Apres le tri: \n");
  afficher_tab(M,nb_processus);

	moyenne = tempsMoyen(M,nb_processus);

	printf("\n\nEn moyenne la commande '%s' met %f microsecondes à s'executer\n\n",commande,moyenne);


}
