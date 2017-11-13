#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TAILLE_COMMANDE 20

int compare (void const *a, void const *b)
{
   int const *pa = a;
   int const *pb = b;

   return *pa - *pb;
}

int tempsMoyen(float * tab, int n){

	if(n % 2 == 1) return tab[(n / 2) + 1];
	else return ((tab[n / 2] + tab[(n / 2)+ 1]) / 2);
}


int main(int argc, char * argv[]){


	/* Variables */

	int i, j, k;
	int nb_repet, nb_processus;
	float moyenne;
	int tube[2];
	float tempsPs;
	int pid_fils;
	int cr, cr1;

	char commande[TAILLE_COMMANDE];

	struct timeval t1, t2;


	if(argc != 4){
		printf("Utilisation : ./<nom_executable> <nb_repetitions> <commande> <nb_processus>");
		exit(0);
	}

	nb_repet = atoi(argv[1]);
	nb_processus = atoi(argv[3]);
	strcpy(commande,argv[2]);


	printf("nb_repet = %i\n",nb_repet);
	printf("nb_processus = %i\n",nb_processus);

	float M[nb_processus];					/*  Contient les les temps moyens d'executions de chaque processus Mi = Ti / K */
	int tab_pid[nb_processus];				/*  Contient les pid de chaque processus fils */
	int fd_devnull = open("/dev/null", O_RDWR);

	pipe(tube);

	/* Création de nb_processus fils */

	for(i = 0; i < nb_processus; i++){
		switch(tab_pid[i] = fork()){

			case -1:		perror("Erreur fork n°1");
							exit(1);

			case 0:			close(tube[1]);
							close(0);
							dup(tube[0]);
							close(tube[0]);

							gettimeofday(&t1,NULL);

							/* Creation de nb_repet processus sous-fils */

							for(j = 0; j < nb_repet; j++){
								switch(fork()){

									case -1: 		
													perror("Erreur fork n°2");
													exit(1);

									case 0:			dup2(fd_devnull,1);
													close(fd_devnull);
													execlp(commande,commande,NULL);

								}
							}

							while(wait(&cr1) != -1);

							gettimeofday(&t2,NULL);

							/*	
							 *	On soustrait t2 le temps final à t1 le temps initial -> on obtient T le temps d'execution.
							 *	Il suffit de divisé le tous par le nombre de repetition pour obtenir le temps moyen.
							 */

							tempsPs = ((t2.tv_sec + t2.tv_usec) - (t1.tv_sec + t1.tv_usec)) / nb_repet;
							exit(tempsPs);

			default:	close(tube[0]);
						printf("Programme père\n");	
		}
	}

	/* On récupère le temps moyen d'execution de chaque processus */

	while((pid_fils = wait(&cr)) != -1){
		for(k = 0; tab_pid[i] != pid_fils; k++);
		M[k] = tempsPs;
	}

	qsort(M,nb_processus,sizeof(float),compare);
	moyenne = tempsMoyen(M,nb_processus);

	printf("\n\n En moyenne la commande '%s' met %f secondes à s'executer\n\n",commande,moyenne);


}
