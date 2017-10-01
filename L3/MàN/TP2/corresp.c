#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ENTREES 500

typedef struct{

  char *mot;
  int lignes[50];
  int nbLignes;

}Entree;

typedef struct{

  Entree entrees[MAX_ENTREES];
  int nbEntrees;

}Table;


void initTable(Table *t){

  int i, j;

  t->nbEntrees = 0;
  for(i = 0; i < MAX_ENTREES; i++){
    t->entrees[i].nbLignes = 0;
    t->entrees[i].mot = NULL;
    for(j = 0; j < 50; j++){
      t->entrees[i].lignes[j] = 0;
    }
  }

}

void initEntree(Entree * t, char * mot, int numLigne){

  int i;
  t->mot = malloc(sizeof(char)*strlen(mot));

  strcpy(t->mot,mot);

  for(i = 0; i < 50; i++){
    t->lignes[i] = 0;
  }

  t->lignes[0] = numLigne;
  (t->nbLignes)++;

}

int ajouterLigne(Entree * t, int numLigne){

  int i;

  for(i = 0; i < 50; i++){
    if(t->lignes[i] == 0){
      t->lignes[i] = numLigne;
      (t->nbLignes)++;
      return 1;
    }
  }
  return 0;
}

int rechercheEntree(Table * t, char * mot){

  int i;

  for(i = 0; i < t->nbEntrees; i++){
    if(strcmp(t->entrees[i].mot,mot) == 0){
      return i;
    }
  }
  return -1;
}

void traiterMot(Table * t, char * mot, int numLigne){

  int indice = rechercheEntree(t,mot);

  if(indice == -1){
    initEntree(&(t->entrees[t->nbEntrees]),mot,numLigne);
    (t->nbEntrees)++;
  }else{
    ajouterLigne(&(t->entrees[indice]),numLigne);
  }
}

void afficherTable(Table * t){

  int i, j;

  printf("Nb entree : %i\n",t->nbEntrees);

  for(i = 0; i < t->nbEntrees; i++){
    printf("Mot -> %s      Lignes -> ",t->entrees[i].mot);
    for(j = 0; j < t->entrees[i].nbLignes; j++){
      printf("%i ",t->entrees[i].lignes[j]);
    }
    printf("\n");
  }
}

void tableDetruire(Table * t){

  int i;
  for(i = 0; t->entrees[i].mot != NULL; i++){
    free(t->entrees[i].mot);
  }


}

int main() {

  Table maTable;
  char c;
  char mot[80];
  int imot=0;
  int numLigne=0;

  initTable(&maTable);

  while((c=getchar())!=EOF){
    if(isalpha(c)) mot[imot++]=c;
    else{
      mot[imot]='\0';
      if(imot>0) traiterMot(&maTable,mot,numLigne);
      imot=0;
    }
    if(c=='\n') numLigne++;
  }

/*  traiterMot(&maTable,"bonjour",2);
  traiterMot(&maTable,"salut",4);
  traiterMot(&maTable,"bonjour",3);
  traiterMot(&maTable,"yop",3); */

  afficherTable(&maTable);
  tableDetruire(&maTable);
  return 0;

}
