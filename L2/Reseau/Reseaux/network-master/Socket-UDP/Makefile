CC=gcc
FLAGS= -Wall -Wextra

client : client.c
	${CC} ${FLAGS} client.c -o client
serveur : serveur.c
	${CC} ${FLAGS} serveur.c -o serveur

all : client serveur

clean : 
	rm serveur client 
