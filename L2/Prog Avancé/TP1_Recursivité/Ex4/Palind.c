#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define N 50


void DelSpace(char chaine1[], char chaine2[]){
  int i = 0;
  int j = 0;
  while(chaine1[i] != '\0'){
    if(chaine1[i] != ' '){
      chaine2[j] = chaine1[i]; i++; j++;
    }else i++;
  }
}



int Palind(char chaine[], int i, int j){
  if(i <= j){
    if(chaine[i] != chaine[j]) return 0;
    else return Palind(chaine,i+1,j-1);
  }
  return 1;
}


int main(){
  char chaine1[100];
  char chaine2[100];
  int i = 0;

  printf("\n **** PALINDROME ****\n\n");
  printf("Veuillez saisir un mot ou une phrase: ");
  fgets(chaine1,100,stdin);


  DelSpace(chaine1, chaine2);
  int lgr_chaine = strlen(chaine2) - 2;


  printf("\n **** RESULTAT **** \n\n");
  if(Palind(chaine2,i,lgr_chaine) == 0) printf("La chaine de caractère n'est pas un palindrome\n\n");
  else printf("La chaine de caractère est un palindrome\n\n");

}
