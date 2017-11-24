FLAGS = -Wall -Wextra

all: serveur client

serveur: chifoumi_serveur.o
	gcc -o serveur chifoumi_serveur.o

chifoumi_serveur.o: chifoumi_serveur.c common_game.h
	gcc -o chifoumi_serveur.o -c chifoumi_serveur.c ${FLAGS}

client: chifoumi_client.o
	gcc -o client chifoumi_client.o

chifoumi_client.o: chifoumi_client.c common_game.h
	gcc -o chifoumi_client.o -c chifoumi_client.c ${FLAGS}

clean:
	rm client
	rm serveur
