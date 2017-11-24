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
#include <sys/timeb.h>

#include "common.h"

int main(int argc, char ** argv){
	int sd, rc;
	struct sockaddr_in localAddr, servAddr;
	struct hostent *h;
	struct timeb time_beg; /* initialisation of the time */
	struct timeb time_end;


	char line[MAX_MSG];
	int cpt_line = 0; /* to print the number of line sent */	

	if(argc<2){
		printf("usage: %s <server> \n",argv[0]);
		exit (1);
	}
	
	h = gethostbyname(argv[1]);
	
	if(h == NULL){
		printf("%s: hote inconnu '%s'\n",argv[0],argv[1]);
		exit(1);
	}
	
	servAddr.sin_family = h->h_addrtype;
	memcpy((char*) &servAddr.sin_addr.s_addr, h->h_addr_list[0],h->h_length);
	servAddr.sin_port = htons(SERVER_PORT);
	
	/* create socket */
	sd = socket(AF_INET, SOCK_STREAM,0);
	if(sd<0){
		perror("impossible d'ouvrir socket");
		exit(1);
	}
	
	/* bind any port number */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);
	
	rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
	if(rc<0){
		printf("%s: impossible de lier %u\n",argv[0],SERVER_PORT);
		perror("erreur");
		exit(1);
	}
	
	/* connect to server */
	rc = connect(sd,(struct sockaddr *) &servAddr, sizeof(servAddr)); 
	if(rc<0){
		perror("erreur");
		exit(1);
	}
	

	ftime(&time_beg);

	rc = send(sd, "OK", sizeof(char)*2, 0);
	printf(" envoie demande echo %s\n", argv[1]);
	
	/* reception of the OK to end echo timer */
	rc = recv(sd, line, sizeof(line) + 1, 0);
	ftime(&time_end);
	fprintf(stdout, "la reception de la reponse a la requete a pris %lu seconds et %d ms\n", (time_end.time - time_beg.time), (time_end.millitm - time_beg.millitm));
	
	close(sd);
	return 0;
}

