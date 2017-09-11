#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pile.h"

int convertir(char c){
	return c - '0';
}

void traiter_vcar(char vcar){
	int a, b, c, d;
	if(isdigit(vcar)){
		d = convertir(vcar);
		empiler(d);
	}else{
		depiler(&a);
		depiler(&b);
		if(vcar == '+'){
			c = a + b;
		}else if(vcar == '-'){
			c = b - a;
		}else if(vcar == '*'){
			c = (a)*(b);
		}else if(vcar == '/'){
			c = b / a;
		}empiler(c);
	}
}

int main(){
	int i, a;
	init_pile();
	char ope;
	printf("Saisir l'opération postfixe caractère par caractère: ");
	scanf("%c",&ope);
	for(i = 0; ope != '\n'; i++){
		traiter_vcar(ope);
		scanf("%c",&ope);
	}
	sommetpile(&a);
	printf("resultat de l'opération: %i\n",a);
}








