/* OUKACHE Ayas */
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#include "common_game.h"

typedef struct game_req_s {  /* definition of the type game request */
   int num_play; /* number of the current play */

   int cli_choice; /* pierre(1), feuille(2), ciseau(3) */
   int state_parti; /* SERVER, CLIENT, EQUALITY, UNKNOWN */

} game_req_t ;


int main (int argc, char * argv[])
{
	if(argc > 1){
		fprintf(stdout, "erreur, le programme \"%s\" ne prends pas d'arguments", argv[0]);
		return ERROR;
	}
	int sd, newSd, n;
	socklen_t cliLen ;

	/* data concerning the game */
	game_req_t play_req;
	int server_choice; /* P(ierre) 0, F(euille) 1, ou C(iseau) 2 */

	/* number of win parties */
	int win_client = 0;
	int win_serveur = 0;

	/* data concerning the print of the result */
	char * player[4] = {"inconnu", "client", "serveur", "aucun des deux"};
	char * jeu[3] = {"pierre", "feuille", "ciseau" };

	struct sockaddr_in cliAddr, servAddr ;
	char line[MAX_MSG] ;

	/*create socket*/
	sd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sd < 0)
	{
		perror("Cannot open socket !") ;
		return ERROR ;
	}

	/* to avoid the error of bind : address already taken */
	int optval = 1;
 	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1) {
    		perror("setsockopt");
    		exit(EXIT_FAILURE);
  	}

	/*bind server port*/
	servAddr.sin_family = AF_INET ;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
	servAddr.sin_port = htons(SERVER_PORT) ;

	if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
	{
		perror("Cannot open socket !") ;
		return ERROR ;
	}

	/* listen of the socket */
	listen(sd, 5) ;

	while(1)
	{
		printf("%s : waiting for data on port TCP %u\n", argv[0], SERVER_PORT) ;
		cliLen = sizeof(cliAddr) ;
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen) ; /* the server is wainting for a connection */

		/* when he got a connection , we print the information about the client connected */
		printf("cliaddr.sin_family : %d\n", cliAddr.sin_family);
		printf("cliaddr.sin_addr.s_addr : %s\n", inet_ntoa(cliAddr.sin_addr));
		printf("cliaddr.sin_port : %d\n", cliAddr.sin_port);

		if(newSd < 0)
		{
			perror("Cannot accept connection !") ;
			return ERROR ;
		}

		/*init line*/
		memset(line, 0x0, MAX_MSG) ;

		/* reception of a play request */
		int cpt = 1; /* compteur de parti */
		while(cpt <=3){

			if((n = recv(newSd, &play_req, sizeof(game_req_t), 0)) > 0){
				server_choice = rand()%3 ; /* choix du serveur */

				/* pour eviter d'analyser tout les cas on suppose que client gagne*/
				win_client++;
				play_req.state_parti = CLIENT;

				if(play_req.cli_choice == server_choice){ /* sinon si client et serveur ont choisi le meme element */
					win_client--;
					play_req.state_parti = EQUALITY;
				}

				if((play_req.cli_choice == P)&&(server_choice==F)){ /* si client choisi Pierre et serveur Feuille */
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;
				}

				if((play_req.cli_choice == F)&&(server_choice == C)){ /* si client choisi Feuille et serveur Ciseau */
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;
				}
				if((play_req.cli_choice == C)&&(server_choice == P)){ /* si client choisi Ciseau et serveur Pierre */
					win_client--;
					win_serveur++;
					play_req.state_parti = SERVER;
				}

				memset(line, 0x0, MAX_MSG); /* init buffer */
				sprintf(line, "MANCHE n°%d : %s \"%s\" VS  %s \"%s\" --> Resultat %s gagne\n", play_req.num_play, player[CLIENT], jeu[play_req.cli_choice], player[SERVER], jeu[server_choice], player[play_req.state_parti]);
				n = send(newSd, line, MAX_MSG, 0); /* envoi du resultat */

				memset(line, 0x0, MAX_MSG); /* init buffer */

				/* si on arrive a la fin d'une partie (en 3 manches )*/
				if(cpt==3){
					if(win_client > win_serveur){
						play_req.state_parti = CLIENT;
					}
					if(win_serveur > win_client){
						play_req.state_parti = SERVER;
					}
					else if(win_serveur == win_client) play_req.state_parti = EQUALITY;

					sprintf(line, "%s est le vainqueur\n", player[play_req.state_parti]);
					n = send(newSd, line, MAX_MSG, 0);
				}

			}

			if(n == 0){
				perror("Connection closed by the Client\n");
				return ERROR;
			}

			if(n < 0){
				perror("Cannot receive data\n");
				return ERROR;
			}
			cpt++;
		}
	}/*while(1)*/
	close(sd);
	close(newSd);
}
