#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 100

char tab_conv[26][5]={".-","-...","-.-.","-..",".","..-.","-- .","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",
                      ".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


/* FONCTION QUI RETOURNE L'INDICE DE LA LETTRE QUI CORRESPOND AU BLOC EN MORSE */

int search_sequence(char * seq){

  int i;

  for(i = 0; i < 26; i++){
   if(strcmp(seq,tab_conv[i]) == 0) return i;
  }
  return -1;
}


/* FONCTION CODER */


char * code(char * source){

  int i,j;
  int size = strlen(source);
  char * n_word = malloc(N * sizeof(char));

  for(i = 0; i < size; i++){
    if(isalpha(source[i]) && islower(source[i])){
      source[i] = (char)toupper(source[i]);
    }
  }

  for(i = 0; i < size; i++){
    for(j = 0; j < 26; j++){
      if(source[i] == alphabet[j]){
        strcat(n_word,tab_conv[j]);
        strcat(n_word," ");
      }else if(source[i] == ' '){
        strcat(n_word,"---. ");
        break;
      }
    }
  }
  strcat(n_word,"---.");
  return n_word;
}


/* FONCTION DECODER */

char * uncode(char * source){

  int i;
  int j = 0;
  int size = strlen(source);
  int indice;
  char mem[5] = "";
  char * m_word = malloc(N * sizeof(char));
  char conc[2];

  conc[1] = '\0';


  for(i = 0; i < size; i++){

    if(source[i] != ' '){
      mem[j] = source[i];
      j++;
    }else{
      indice = search_sequence(mem);
      conc[0] = alphabet[indice];
      if(indice == -1){
        strcat(m_word," ");
      }else if(indice >= 0){
        strcat(m_word,conc);
      }
      j = 0;
      memset(mem,0,sizeof(mem));
    }
  }
  return m_word;
}

/* PROGRAMME PRINCIPAL */

int main(){

  char word[N];
  char * ptr_c = NULL;
  char * ptr_u = NULL;

  int choix = 1;


  printf("Choose a word: ");
  scanf("%80[^\n]",word);

  ptr_c = code(word);
  ptr_u = uncode(word);


  if(choix == 1)printf("%s -> %s\n",word,code(word));
  else if(choix == 2)printf("%s -> %s\n",word,uncode(word));
  else printf("ERROR");

  free(ptr_c);
  free(ptr_u);

}
