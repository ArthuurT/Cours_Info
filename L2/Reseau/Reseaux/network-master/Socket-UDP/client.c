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


#define SERVER_PORT 1500
#define MAX_MSG 100

#define ERROR 0
/* pour une communication non connecté on utiliseras les primitives 
 * de sockets de la maniere suivantes (coté client) ...  
 * gethostbyname()
 * socket()
 * bind()
 * sendto()
 * close() */
 
int main(int argc, char * argv[]){
	int sd, numval;
	ssize_t rc;
	
	struct sockaddr_in localAddr, servAddr;
	struct hostent *h;
	char line[MAX_MSG];

	if(argc<2){
		printf("usage: %s <server> \n",argv[0]);
		exit (1);
	}
	
	h = gethostbyname(argv[1]);

	if(h == NULL){
		printf("%s: unknow host '%s'\n",argv[0],argv[1]);
		exit(1);
	}
	/* initialisation of the socket adress of the server */
	servAddr.sin_family = h->h_addrtype;
	memcpy((char*) &servAddr.sin_addr.s_addr, h->h_addr_list[0],h->h_length);
	servAddr.sin_port = htons(SERVER_PORT);

	/* create socket */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){
		perror("cannot open socket\n");
		exit(1);		
	}
	
	/* bind the port */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);
	
	if(bind(sd, (struct sockaddr *)&localAddr, (socklen_t )sizeof(localAddr))<0){
		perror("cannot bind the port");
		return ERROR;
	}
	
	/* send of a line */
	printf("Quelle chaine voulez vous envoyer ?\n");
	scanf("%[^\n]s", line);
	rc = sendto(sd, line, MAX_MSG, 0, (struct sockaddr *)&servAddr, (socklen_t )sizeof(servAddr));
	if(rc<=0){
		perror("receive data fail");
		exit(-1);
	}
	
	/* send of a numeric value */
	printf("Quelle entier voulez vous envoyer ? :");
	scanf("%d", &numval);
	rc = sendto(sd, (void *)&numval, sizeof(numval), 0, (struct sockaddr *)&servAddr, (socklen_t )sizeof(servAddr));
	if(rc<=0){
		perror("receive data fail");
		exit(-1);
	}
	
	close(sd);
	return 0;
}
