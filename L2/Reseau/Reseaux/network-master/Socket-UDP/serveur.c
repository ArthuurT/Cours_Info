/* OUKACHE Ayas */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define MAX_MSG 100
#define SERVER_PORT 1500

#define ERROR 0	
/* pour une communication non connecté on utiliseras les primitives 
 * de sockets de la maniere suivantes (coté serveur) ...  
 * socket()
 * bind()
 * recvfrom()
 * close() */

void afficher_client(struct sockaddr_in client); /* printf information about the client */

int main(){
	
	int sd, n; 
	int valnum;
	socklen_t cliLen ;
	struct sockaddr_in cliAddr, servAddr ;
	char line[MAX_MSG];

	/*create socket*/
	sd = socket(AF_INET, SOCK_DGRAM, 0) ;
	if(sd < 0)
	{
		perror("Cannot open socket !") ;
		return ERROR ;
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

	cliLen = sizeof(cliAddr);
	printf("waiting for the data\n");
	memset(line, 0x0,MAX_MSG); /* init buffer */

 	/* waiting for the client data (string)*/
	n = recvfrom( sd, (void *)line, MAX_MSG, 0, (struct sockaddr *)&cliAddr, (socklen_t *)&cliLen);
 	  /* end of waiting */
 	if(n<=0){
		perror("receive data fail");
		exit(-1);
	}
	
	/* print the information of client */
	afficher_client(cliAddr);
	printf("reception : %s\n", line);
	memset(line, 0x0, MAX_MSG); /* init buffer */
	
	/* waiting for the client data (numerical) */
	n= recvfrom(sd, (void *)&valnum, sizeof(valnum), 0, (struct sockaddr *)&cliAddr, (socklen_t *)&cliLen);
	/* end of waiting */
	if(n<=0){
		perror("receive data fail");
		exit(-1);
	}
	printf("reception : %d\n", valnum);
	close(sd);
	
	return 0;
}

void afficher_client(struct sockaddr_in client){
	printf("adresse client : %s\n", inet_ntoa(client.sin_addr));
	printf("port client : %d\n", client.sin_port);
}
