#include <stdlib.h>
#include <stdio.h>

int fun(int a, int i){
  if(a < 10) return i;
  else fun((a/10),i+1);
}



int main(){

  int nb;

  printf("\n **** LONGUEUR D'UN NOMBRE ****\n\n");
  printf("Veuillez saisir un entier strictement positif: ");
  scanf("%i",&nb);

  while(nb < 0){
    printf("Valeur saisie incorrect, réessayer:");
    scanf("%i",&nb);
  }

  printf("\n **** RESULTAT **** \n\n");
  printf("Resultat Final: Ce nombre possède %i chiffres\n\n",fun(nb,1));

}
