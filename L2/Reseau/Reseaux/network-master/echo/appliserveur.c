#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#include "common.h"

int main (int argc, char * argv[])
{	
	if(argc > 1){
		fprintf(stdout, "erreur, le programme \"%s\" ,e prends pas d'arguments", argv[0]);
		return ERROR;	
	}
	int sd, newSd, n; 
	socklen_t cliLen ;
	
	/* data concerning the file */
	struct sockaddr_in cliAddr, servAddr ;
	char line[MAX_MSG] ;
	
	/*create socket*/
	sd = socket(AF_INET, SOCK_STREAM, 0) ;
	if(sd < 0)
	{
		perror("Impossible d'ouvrir socket !") ;
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
		perror("Impossible d'ouvrir socket !") ;
		return ERROR ;
	}
	
	listen(sd, 5) ;
	
	while(1)
	{
		printf("%s : en attende de donnees %u\n", argv[0], SERVER_PORT) ;
		cliLen = sizeof(cliAddr) ;
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen) ;
		printf("cliaddr.sin_family : %d\n", cliAddr.sin_family);
		printf("cliaddr.sin_addr.s_addr : %s\n", inet_ntoa(cliAddr.sin_addr));
		printf("cliaddr.sin_port : %d\n", cliAddr.sin_port);
		if(newSd < 0)
		{
			perror("Connexion refusee !") ;
			return ERROR ;
		}
		
		/*init line*/
		memset(line, 0x0, MAX_MSG) ;
		
 		n = recv(newSd, line, sizeof(line) + 1, 0);
			if(n == 0){
				perror("Connexion refusee par le client\n");
				return ERROR;		
			}
			if(n < 0){
				perror("Peut pas recevoir les donnes\n");
				return ERROR;		
			}
			if(strcmp(line,"OK") == 0){
				int i;
				int j = rand()%9999999+99999;
				for(i = 0; i < j; i++){}
				n = send(newSd, "OK", sizeof(char)*2 ,0);	
			}
		else printf("Transfert depuis : %s abandonne\n", inet_ntoa(cliAddr.sin_addr));
	}/*while(1)*/
	close(sd);
	close(newSd);
}


