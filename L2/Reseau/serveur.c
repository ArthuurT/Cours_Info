#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

#define SUCESS 0
#define ERROR 1

#define END_LINE 0x0
#define SERVER_PORT 1500
#define MAX_MSG 100

int main (int argc, char * argv[]){

	int sd, newSd, cliLen;
	struct sockaddr_in cliAddr, servAddr;
	char line[MAX_MSG];


	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0){
		perror("cannot open socket");
		return ERROR;
