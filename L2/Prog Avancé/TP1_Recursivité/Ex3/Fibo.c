#include <stdlib.h>
#include <stdio.h>
#define N 30


int Fibo(int n){
  if (n == 0) return 0;
  else if (n == 1) return 1;
  else return Fibo(n-1) + Fibo(n-2);
}

int Fibo1(int n, int t[]){
  int i;
  t[0] = 0;
  t[1] = 1;

  for(i = 2; i <= n; i++){
    t[i] = t[i-1] + t[i-2];
    printf("Fibo(%i) = %i\n",i,t[i]);
  }
  return t[n];
}

int main(){

  int nb;
  int t[N];

  printf("\n **** SUITE DE FIBONNACI ****\n\n");
  printf("Veuillez saisir un entier strictement positif: ");
  scanf("%i",&nb);

  while(nb < 0){
    printf("Valeur saisie incorrect, réessayer:");
    scanf("%i",&nb);
  }

  printf("\n **** RESULTAT **** \n\n");
  printf("Resultat Final: Fibo(%i) = %i\n\n",nb,Fibo1(nb,t));

}
