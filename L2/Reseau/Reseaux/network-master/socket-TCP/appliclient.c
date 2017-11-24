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

typedef struct file_req_s {  /* definition of the type file request */
   char name[20];
   char REQ; /* REQ_UPLOAD, REQ_OK or REQ_KO */
} file_req_t ;


extern int read_sizef(char * filename); /* return the size of a file (in octet)*/

int main(int argc, char ** argv){
	int sd, rc;
	struct sockaddr_in localAddr, servAddr;
	struct hostent *h;
	
	//struct time_val time_send; /* A REVOIR */
	//struct time_val time_recv; 

	/* data linked with the file */
	file_req_t file_req1;
	FILE * fic = NULL;	
	char file_line[MAX_MSG];
	int cpt_line = 0; /* to print the number of line sent */	

	if(argc<3){
		printf("usage: %s <server> <file>\n",argv[0]);
		exit (1);
	}
	
	h = gethostbyname(argv[1]);
	
	if(h == NULL){
		printf("%s: serveur inconnu '%s'\n",argv[0],argv[1]);
		exit(1);
	}
	
	servAddr.sin_family = h->h_addrtype;
	memcpy((char*) &servAddr.sin_addr.s_addr, h->h_addr_list[0],h->h_length);
	servAddr.sin_port = htons(SERVER_PORT);
	
	/* create socket */
	sd = socket(AF_INET, SOCK_STREAM,0);
	if(sd<0){
		perror("Impossible d'ouvrir le socket");
		exit(1);
	}
	
	/* bind any port number */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);
	
	rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
	if(rc<0){
		printf("%s: impossible de lier port TCP %u\n",argv[0],SERVER_PORT);
		perror("erreur");
		exit(1);
	}
	
	/* connect to server */
	rc = connect(sd,(struct sockaddr *) &servAddr, sizeof(servAddr)); 
	if(rc<0){
		perror("erreur");
		exit(1);
	}
	
	/* initialisation of the file request */
	strcpy(file_req1.name, argv[2]);
	file_req1.REQ = REQ_UPLOAD; /* request concerning the send of the file */

 	/* send of the file request */
	struct timeb time_beg; /* initialisation of the time */
	struct timeb time_end;
	ftime(&time_beg);

	rc = send(sd, &file_req1, sizeof(file_req_t), 0);
	printf(" envoie de la demande a %s\n", argv[1]);

	/* reception of the file request to comfirm */
	rc = recv(sd, &file_req1, sizeof(file_req_t), 0);
	ftime(&time_end);
	fprintf(stdout, "la reception de la reponse a la requete a pris %lu secondes et %d ms\n", (time_end.time - time_beg.time), (time_end.millitm - time_beg.millitm));
	
	(file_req1.REQ == REQ_OK)? printf("reception de comfirmation :\n") : perror("le serveur a arrete le transfert");

	if(file_req1.REQ == REQ_OK){
		/* open the file given in argument */
		if((fic = fopen(file_req1.name, "r")) == NULL){
			perror("erreur : ouverture fichier");
			exit(-1);	 
		}
		
		/* send of the file line by line */
		while(fgets(file_line, MAX_MSG, fic) != NULL){
			rc = send(sd, file_line, MAX_MSG, 0);
			cpt_line++;
			printf("envoie ligne n°%d : %s", cpt_line, file_line);	
		}
		fclose(fic); /* close the file */
	}
	
	
	close(sd);
	return 0;
}

/* return the size of a file (in octet)*/
extern int read_sizef(char * filename){
	int size;
	FILE * fic = NULL;
	
	if((fic = fopen(filename, "r")) == NULL){
		perror("erreur : ouverture fichier");
		exit(-1);	
	}
	fseek(fic, 0, SEEK_END);
	size = ftell(fic);
	fseek(fic, 0, SEEK_SET);
	fclose(fic);
	return size;
}

