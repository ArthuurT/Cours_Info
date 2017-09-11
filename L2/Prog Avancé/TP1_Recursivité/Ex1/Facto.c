#include <stdlib.h>
#include <stdio.h>

int facto(int a, int res){
  printf("Resultat intermédiaire: !%i = %i\n",a,res);
  if(a == 0) return res;
  else return facto(a-1,a*res);
}


int main(){

  int nb;

  printf("\n **** CALCUL DE FACTORIELLE ****\n\n");
  printf("Veuillez saisir un entier strictement positif: ");
  scanf("%i",&nb);
  while(nb < 0 || nb > 25){
    printf("Valeur saisie incorrect, réessayer: ");
    scanf("%i",&nb);
  }

  printf("\n **** RESULTAT **** \n\n");
  printf("\nResultat Final: !%i = %i\n\n",nb,facto(nb,1));

}
