#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SUCCESS 0
#define ERROR 1

#define END_LINE 0x0
#define SERVER_PORT 1500
#define MAX_MSG 100

int read_line();
int main( int argc, char * argv[]){
	int sd, newSd, cliLen;
	struct sockaddr_in cliAddr, servAddr;
	char line[MAX_MSG];

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0){
		perror("cannot open socket");
		return ERROR;
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERVER_PORT);

	if(bind(sd, (struct sockaddr *) &cliAddr, sizeof(servAddr)) < 0){
		perror("cannot bind port");
		return ERROR;
	}

	listen(sd,5);

	while(1){
		printf("%s: waiting for data onport TCP %u\n",argv[0],SERVER_PORT);

		cliLen = sizeof(cliAddr);
		newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
		if(newSd < 0){
			perror("cannot accept connection");
			return ERROR;
		}

		memset(line, 0x0, MAX_MSG);
		while(read_line(newSd,line) != ERROR){
			printf("%s: received from %s:TCP%d : %s\n",argv[0],inet_ntoa(cliAddr.sin_addr),ntohs(cliAddr.sin_port),line);
			memset(line, 0x0,MAX_MSG);
		}
	}
}
	int read_line(int newSd, char *line_to_return){
		static int rcv_ptr=0;
		static char rcv_msg[MAX_MSG];
		static int n;
		int offset;

		offset = 0;

		while(1){
			if(rcv_ptr == 0){
				memset(rcv_msg, 0x0, MAX_MSG);
				n = recv(newSd, rcv_msg, MAX_MSG, 0);
				if(n < 0){
					perror("cannot receive data");
					return ERROR;
				}
				else if(n == 0){
					printf("connection closed by client\n");
					close(newSd);
					return ERROR;
				}
			}

			while(*(rcv_msg + rcv_ptr) != END_LINE && rcv_ptr < n){
				memcpy(line_to_return + offset, rcv_msg + rcv_ptr, 1);
				offset++;
				rcv_ptr++;
			}

			if(rcv_ptr == n -1 ){
				*(line_to_return + offset) = END_LINE;
				rcv_ptr = 0;
				return ++offset;
			}

			if(rcv_ptr < n - 1){
				*(line_to_return + offset) = END_LINE;
				rcv_ptr++;
				return ++offset;
			}
			if(rcv_ptr == n){
				rcv_ptr = 0;
			}
		}
	}


