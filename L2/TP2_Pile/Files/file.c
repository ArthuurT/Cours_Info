#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct element{int nombre; struct element*suivant;} t_element;

t_element*tete;
t_element*queue;

void init_file(){
	tete = NULL;
	queue = NULL;
}

int file_vide(void){
	return(tete == NULL);
}

void ajouter(int v){
	t_element*nouv;
	nouv = malloc(sizeof(t_element));
	nouv->nombre=v;
	nouv->suivant=NULL;
	if(file_vide())tete=nouv;
	else queue->suivant=nouv;
	queue=nouv;
}

void retirer(int*v){
	t_element*premier;
	if(!file_vide()){
		premier=tete;
		*v=premier->nombre;
		tete=premier->suivant;
		free(premier);
	}
}

void queue_file(int*v){
	if(queue != NULL){
		*v = queue->nombre;
	}
		
}
