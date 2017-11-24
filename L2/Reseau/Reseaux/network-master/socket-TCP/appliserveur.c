#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#include "common.h"

typedef struct file_req_s {  /* definition of the type file request */
   char name[20];
   char REQ; /* REQ_UPLOAD, REQ_OK or REQ_KO */
} file_req_t ;


int main (int argc, char * argv[])
{	 
	if(argc > 1){
		fprintf(stdout, "erreur, le programme \"%s\" , ne prends pas d'arguments", argv[0]);
		return ERROR;	
	}
	int sd, newSd, n; 
	socklen_t cliLen ;
	
	/* data concerning the file */
	file_req_t file_req1;	
	char choice; 
	char rep_file[64];
	FILE * fic = NULL;

	struct sockaddr_in cliAddr, servAddr ;
	char line[MAX_MSG] ;
	
	/*create socket*/
	sd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sd < 0)
	{
		perror("Impossible d'ouvrir le socket !") ;
		return ERROR ;
	}
	
	/* to avoid the error of bind : address already taken*/
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
		perror("Impossible d'ouvrir le socket !") ;
		return ERROR ;
	}
	
	listen(sd, 5) ;
	
	while(1)
	{
		printf("%s : en attente des donnees sur le port TCP %u\n", argv[0], SERVER_PORT) ;
		cliLen = sizeof(cliAddr) ;
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen) ;
		printf("cliaddr.sin_family : %d\n", cliAddr.sin_family);
		printf("cliaddr.sin_addr.s_addr : %s\n", inet_ntoa(cliAddr.sin_addr));
		printf("cliaddr.sin_port : %d\n", cliAddr.sin_port);
		if(newSd < 0)
		{
			perror("Impossible d'accepter la connexion !") ;
			return ERROR ;
		}
		
		/*init line*/
		memset(line, 0x0, MAX_MSG) ;
		
		/* reception of a file request */
 		n = recv(newSd, &file_req1, sizeof(file_req1), 0);
		printf("demande de transfert recue \n nom du fichier : %s\n", file_req1.name);
		
		if(file_req1.REQ == REQ_UPLOAD){
			file_req1.REQ = REQ_OK;
			n = send(newSd, &file_req1, sizeof(file_req_t), 0);		 
		} 

		if(file_req1.REQ == REQ_OK){ /* if the server accpet the file , reception of the file */
			printf("DEBUT : reception du fichier %s \n", file_req1.name);
			/* create a new file which will be a copy of the sent file */	
			sprintf( rep_file, "tmp local/%s", file_req1.name); /* to open in the repertory tmp local */
			
			if((fic = fopen(rep_file, "w")) == NULL){
				perror("erreur : ouverture du fichier");
				return ERROR;		
			}

			/* reception of the file line by line */
			memset(line, 0x0, MAX_MSG); /* init buffer */
			fprintf(fic ,"test ");
			
			while((n = recv( newSd, line, MAX_MSG, 0)) > 0){
				
				if( fprintf(fic, "%s", line) < 0){  /* write the line on the file */
					perror("erreur : ecriture du fichier");
					return ERROR;	
				}				
				memset(line, 0x0, MAX_MSG);
			}
			printf("FIN : fichier recu %s\n", file_req1.name);
			if(n == 0){
				perror("Connexion fermee par le client\n");
				return ERROR;		
			}
			if(n < 0){
				perror("Impossible de recevoir les donees\n");
				return ERROR;		
			}
			
		}
		else printf("Transfert depuis : %s abandonne\n", inet_ntoa(cliAddr.sin_addr));
	}/*while(1)*/
	close(sd);
	close(newSd);
	fclose(fic);
}


