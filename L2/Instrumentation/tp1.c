#include <stdio.h>
#include <string.h>
#include <math.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>


void init(int *V,int *debut,int *N){ //demande a l'utilisateur les condition initiales pour le codage

  printf("veuillez saisir vos condition initiales\n V = ");
  scanf("%i",V);
  while(*V != 1 && *V != -1){
    printf("veuillez ressaisir V soit -1 ou 1\n V = ");
    scanf("%i",V);
  }
  printf(" N = ");
  scanf("%i",N);
  while(*N < 2 || *N > 4){
    printf("veuillez ressaisir N, il doit etre compris entre 2 et 4\n N = ");
    scanf("%i",N);
  }
  printf(" debut = ");
  scanf("%i",debut);
  while(*debut != 1 && *debut != -1){
    printf("veuillez ressaisir debut soit -1 ou 1\n debut = ");
    scanf("%i",debut);
  }

}

int reset(int *V,const int v_base){ //remet la valeur de v comme celle de l'initialisation

  if(*V != 0){
    *V = v_base;
  }else printf("veuiller dabord initialiser les condition de base");

}

void HDBN(int table_Data[],int table_P[],int table_N[], int *V, int debut,int n){ //fonction qui code le message

  int i;
  int compt_n = 0;   // varuiable qui compte le nombre de 0 consecutif pour le cas ou il y a plus de n+1 0
  int element;       // variable qui garde le signe du dernier pulse

  for (i = 0; i < 23; i++){

    if(table_Data[i] == 1){         //cas case = 1

      if(i == 0){   // cas de la premiere case
        if(debut == 1){
          table_P[i] = 1;
          table_N[i] = 0;
          element = 1;
        }else{
          table_P[i] = 0;
          table_N[i] = 1;
          element = -1;
        }
      }else {      // cas pas premiere case
        if(element == 1){
          table_P[i] = 0;
          table_N[i] = 1;
          element = -1;
        }else {
          table_P[i] = 1;
          table_N[i] = 0;
          element = 1;
        }
      }
      compt_n = 0;
    }else if(table_Data[i] == 0){  // cas case =0
      compt_n++;
      table_P[i] = 0;
      table_N[i] = 0;

      if(compt_n == n+1){  // cas ou il y a n+1 0
        if(*V == 1){
          table_P[i] = 0;
          table_N[i] = 1;
          if(element == 1){
            table_P[i-n] = 0;
            table_N[i-n] = 1;
            element = -element;
          }
        }else {
          table_P[i] = 1;
          table_N[i] = 0;
          if(element == -1){
            table_P[i-n] = 1;
            table_N[i-n] = 0;
            element = -element;
          }
        }
        *V = -*V;        // change la valeur du viol
        compt_n = 0;     // remet le compteur de zero a 0
      }
    }

  }

}

int Affichage (int table_P[],int table_N[],int table_signal[]){  // affiche les différent tableau de solution
  int i;
  printf("P = ");
  for (i = 0; i < 23; i++) {
    printf("  %i",table_P[i]);
  }
  printf("\n");
  printf("N = ");
  for (i = 0; i < 23; i++) {
    printf("  %i",table_N[i]);
  }

  printf("\n\n");
  printf("signal coder = ");
  for (i = 0; i < 23; i++) {
    printf("  %i",table_signal[i]);
  }
  printf("\n\n");

}

void creation_signal(int table_P[],int table_N[],int table_signal[]){  // crée le tableau du signal coder
  int i;
  for(i = 0; i < 23; i++){
    table_signal[i] = table_P[i] - (1 * table_N[i]);
  }
}
void DecodeHGBN(int table_signal[], int table_Data_decoder[], int *V, int debut, int n){
  /*int i;
  for(i = 0; i < 23; i++){
      if(table_signal[i] )
  }*/


}

int main() {

  int table_Data [23] = {1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0};
  int table_P [23] = {0};
  int table_N [23] = {0};
  int table_signal [23] = {0};
  int table_Data_decoder [23] = {0};

  int v = 0;
  int n = 0;
  int debut = 0;
  int choix;

  do
  {	/* Affichage du menu */
    printf("\nMenu :\n");
    printf(" 1 - Initialiser les conditions de base\n");
    printf(" 2 - Coder un message\n");
    printf(" 3 - creation du signal coder\n");
    printf(" 4 - afficher le message coder\n");
    printf(" 5 - Decoder un message\n");
    printf(" 6 - Reset les conditions de base\n");
    printf(" 7 - Quitter\n");
    printf("Votre choix : ");
    scanf("%i",&choix);

    /* Traitement du choix de l'utilisateur */
    switch(choix)
    {	case 1 : init(&v, &debut, &n); const int v_base = v; break;
      case 2:  HDBN(table_Data, table_P, table_N, &v, debut, n);
      case 3:  creation_signal(table_P,table_N, table_signal); break;
      case 4:  Affichage(table_P,table_N,table_signal); break;
      case 5:  DecodeHGBN(table_signal, table_Data_decoder, &v, debut, n); break;
      case 6:  reset(&v,v_base); break;
      case 7:  break;
      default: printf("Erreur: votre choix doit etre compris entre 1 et 7\n");
    }
  }
  while(choix!=7);

  printf("En revoir !! \n");


}
