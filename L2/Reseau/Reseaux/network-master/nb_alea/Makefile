all: serveur client

serveur: appliserveur.o
	gcc -o serveur appliserveur.o

appliserveur.o: appliserveur.c
	gcc -o appliserveur.o -c appliserveur.c

client: appliclient.o
	gcc -o client appliclient.o

appliclient.o: appliclient.c
	gcc -o appliclient.o -c appliclient.c

clean:
	rm client
	rm serveur
