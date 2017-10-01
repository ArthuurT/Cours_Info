#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define N 20

void squeeze(char c,char * s){

  int i, j;

  for(i = 0; s[i] != '\0'; i++){
      if(s[i] == c){
          for(j = i; s[j] != '\0'; j++){
              s[j] = s[j+1];
          }
      }
  }
}

int main(){

  char word[N];
  char letter;

  printf("Choose a word: ");
  scanf("%s",word);

  printf("Choose a letter: ");
  scanf(" %c",&letter);

  squeeze(letter,word);

  printf("Result: %s \n",word);

}
