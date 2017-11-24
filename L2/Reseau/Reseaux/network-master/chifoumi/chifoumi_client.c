/* OUKACHE Ayas */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h> /* inet_ntoa(), */
#include <arpa/inet.h> /* gethostbyname(), */
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> /* strlen() */


#include "common_game.h"

typedef struct game_req_s {  /* definition of the type game request */
   int num_play; /* number of the current play */

   int cli_choice; /* pierre(1), feuille(2), ciseau(3) */

   int state_parti; /* SER_WIN, CLI_WIN, EQUALITY */

} game_req_t ;

void init_game(game_req_t * play_req){
	play_req->num_play = 1;
	play_req->cli_choice = 0;
	play_req->state_parti = UNKNOWN ;
}

extern int read_sizef(char * filename); /* return the size of a file (in octet)*/

int main(int argc, char ** argv){
	int sd, rc;

	struct sockaddr_in localAddr, servAddr;
	struct hostent *h;

	/* data linked with the game */
	game_req_t play_req;
	int choice;
	char line[MAX_MSG];

	if(argc<2){
		printf("usage: %s <server>\n",argv[0]);
		exit(1);
	}
	/* recuperation des infos de la machine donné en argument */
	h = gethostbyname(argv[1]);

	if(h == NULL){
		printf("%s: unknow host '%s'\n",argv[0],argv[1]);
		exit(1);
	}

	servAddr.sin_family = h->h_addrtype;
	memcpy((char*) &servAddr.sin_addr.s_addr, h->h_addr_list[0],h->h_length);
	servAddr.sin_port = htons(SERVER_PORT);

	/* create socket */
	sd = socket(AF_INET, SOCK_STREAM,0);
	if(sd<0){
		perror("cannot open socket");
		exit(1);
	}

	/* bind any port number */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);

	rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
	if(rc<0){
		printf("%s: cannot bind port TCP %u\n",argv[0],SERVER_PORT);
		perror("error");
		exit(1);
	}

	/* connect to server */
	rc = connect(sd,(struct sockaddr *) &servAddr, sizeof(servAddr));
	if(rc<0){
		perror("error");
		exit(1);
	}

	/* initialisation de la structure du jeu */
	init_game(&play_req);

	/* compteur de parti */
	int cpt = 1 ;
	while(cpt<=3){
		/* choix du client */
		printf("MANCHE n°%d : Tapez votre choix --> PIERRE: 0, FEUILLE: 1, CISEAU: 2 \n", cpt);
    printf("Choix: ");
		scanf("%d", &choice);
		while((choice<0)&&(choice>3)){
			printf("error : tap a number between 1 and 3\n");
			scanf("%d", &choice);
		}
		play_req.cli_choice = choice;
		play_req.num_play = cpt;

		/* envoi et receetpion de l'etat du jeu comprenant le choix du client et celui du serveur en reception */
		rc = send(sd, &play_req, sizeof(play_req), 0);
		memset(line, 0x0, MAX_MSG);
		rc = recv(sd, line, MAX_MSG, 0);
		printf("%s\n", line);

		memset(line, 0x0, MAX_MSG);
		if(cpt==3){
			rc = recv(sd, line, MAX_MSG, 0);
			printf("%s\n", line);
			memset(line, 0x0, MAX_MSG);
		}
		cpt++;
	}

	close(sd);
	return 0;
}
