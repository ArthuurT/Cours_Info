#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int humain_joue(int score);
int ordinateur_joue(int score);


int humain_joue(int score){
  int i;
  int res;
  int min_res = 10;
  if(score == 20) return -1;
  else if(score > 20) return 1;

  else{

    for(i = 1; i < 4; i++){
      res = ordinateur_joue(score + i);
      if(res <= min_res){
        res = min_res;
      }
    }
    return min_res;
  }
}



int ordinateur_joue(int score){
  int i;
  int res;
  int max_res = -10;
  if(score == 20) return 1;
  else if(score > 20) return -1;

  else{

    for(i = 1; i < 4; i++){
      res = humain_joue(score + i);
      if(res >= max_res){
        res = max_res;
      }
    }
    return max_res;
  }
}

int min_max(int score){
  int i;
  int max_value = -10;
  int max_i;
  int res;

  if(score >= 17) return (20 - score);

  for(i = 1; i < 4; i++){
    res = humain_joue(score + i);
    if(res > max_value){
      max_value = res;
      max_i = i;
    }
  }
  return max_i;
}


int DeuxJoueur(){

  int i, jeu_arret;
  int total = 0;
  int score_A = 0;
  int score_B = 0;

  for(i = 0; total < 20; i++){
    printf("Tour N°%i : \n",i+1);

    /* Joueur A */

    do{
      printf("A joue: ");
      scanf("%i",&score_A);
    }while(score_A > 3);

    total = total + score_A;
    printf("\033[1A");
    printf("\t\t\t Total : %i\n",total);

    if(total == 20){
      printf("Le joueur A à gagné\n\n");
      jeu_arret = 1;
      return 1;
    }

    /* Joueur B */

    do{
      printf("B joue: ");
      scanf("%i",&score_B);
    }while(score_B > 3);

    total = total + score_B;
    printf("\033[1A");
    printf("\t\t\t Total : %i\n\n",total);

    if(total == 20){
      printf("Le joueur B à gagné\n\n");
      jeu_arret = 1;
      return 1;
    }
  }
  printf("Pas de gagnant\n");
  return 0;
}

int UnJoueur(){
  int i, jeu_arret;
  int total = 0;
  int score_A = 0;
  int score_B = 0;
  srand(time(NULL));

  for(i = 0; total < 20 ; i++){
    printf("Tour N°%i : \n",i+1);

    /* Joueur A */

    do{
      printf("A joue: ");
      scanf("%i",&score_A);
    }while(score_A > 3);

    total = total + score_A;
    printf("\033[1A");
    printf("\t\t\t Total : %i\n",total);

    if(total == 20){
      printf("Le joueur A à gagné\n\n");
      return 1;
    }

    /* Joueur B (IA) */

    /* score_B = rand()%(4-1)+1; */
    score_B = min_max(total);
    total = total + score_B;
    printf("B joue: %i \t\t Total : %i\n\n",score_B,total);


    if(total == 20){
      printf("Le joueur B à gagné\n\n");
      return 1;
    }
  }
  return 0;
}


int main(){

  int choix;
  srand(time(NULL));

  printf("\n****** LA COURSE A 20 ******\n\n");
  printf("Règle 1 : Le premier qui arrive à exactement 20 à gagner\n");
  printf("Règle 2 : A chaque tour, jouez 1, 2 ou 3\n\n");

  printf("Choisissez le nombre de joueur: \n");
  printf("1 : Un joueur\n");
  printf("2 : Deux Joueurs\n");
  printf("Votre choix: ");
  scanf("%i",&choix);
  printf("\n");

  switch (choix) {
    case 1 : UnJoueur(); break;
    case 2 : DeuxJoueur(); break;
    default : printf("Erreur: Choix indisponible"); break;
  }

}
