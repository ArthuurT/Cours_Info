#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define tmax 50

int pile[tmax];
int sommet;

void init_pile(){
	sommet = -1;
}

void empiler(int c){
	if(sommet < (tmax - 1)){
		sommet++;
		pile[sommet] = c;
	}
}

void depiler(int*c){
	if(sommet > -1){
		*c = pile[sommet];
		sommet--;
	}
}

void sommetpile(int*c){
	*c = pile[sommet];
}
 
	
	



