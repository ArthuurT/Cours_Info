#include <stdio.h>
#include <stdlib.h>
#define N 3

void init_mat(char mat[N][N]){ //fonction qui initalise la matrice avec des points
  int i, j;
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
        mat[i][j]='.';
    }
  }
}

void afficher_grille(char mat[N][N], FILE * fic){ //fonction qui affiche la grille à l'écran et dans le fichier
  int i, j;
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
        printf("%c ",mat[i][j]);
        fprintf(fic,"%c ",mat[i][j]);
    }
    printf("\n");
    fprintf(fic,"\n");
  }
  fprintf(fic,"\n");
}

void update_grille(char mat[N][N], int x, int y, int joueur){ //fonction qui met à jour la grille en fonction des valeurs rentrés
  if(joueur == 1){
    mat[x][y]='O';
  }else mat[x][y]='X';
}

int verif_win(char mat[N][N]){    //fonction qui vérifie si un joueur à gagné
  int compteur = 0;
  int i, j;
  for (i = 0, j = 0; i < N; i++){
    if(mat[i][j] == mat[i][j+1] && mat[i][j] == mat[i][j+2] && mat[i][j] != '.'){
      compteur++;
    }
  }
  for (j = 0, i = 0; j < N; j++){
    if(mat[i][j] == mat[i+1][j] && mat[i][j] == mat[i+2][j] && mat[i][j] != '.'){
      compteur++;
    }
  }

  if(mat[0][0] == mat[1][1] && mat[0][0] == mat[2][2] && mat[0][0] != '.'){
    compteur++;
  }

  if(mat[0][2] == mat[1][1] && mat[0][2]== mat[2][0] && mat[0][2] != '.'){
    compteur++;
  }
  return compteur;
}

int verif_end(char mat[N][N]){ //fonction qui vérifie que la grille n'est pas remplie et donc qu'il n'y a pas encore de match nul
  int i, j;
  int compteur = 0;
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
        if(mat[i][j] == '.'){
          compteur++;
        }
    }
  }

  return compteur;

}



int main(){
  FILE * fic;
  char mat_jeu[N][N];
  int x, y;
  int winA = 0;
  int winB = 0;
  int compteur = 1;
  init_mat(mat_jeu);
  char nom[20];
  printf("Saisir le nom du fichier de sauvegarde: ");
  scanf("%s",nom);
  fic = fopen(nom,"w");
  printf("Le jeu Tic-Tac-Toe: \n\n");
  while(winA == 0 && winB == 0 && compteur > 0){
      printf("Joueur A, donnez les coordonnées que vous voulez jouer (ligne colonne): ");
      scanf("%i%i",&x,&y);
      update_grille(mat_jeu,x,y,1);
      winA = verif_win(mat_jeu);
      afficher_grille(mat_jeu,fic);
      if(winA > 0){
        printf("\n Le joueur A à gagné !!\n ");
      }else{
        compteur = verif_end(mat_jeu);
        if(compteur > 0){
          printf("Joueur B, donnez les coordonnées que vous voulez jouer (ligne colonne): ");
          scanf("%i%i",&x,&y);
          update_grille(mat_jeu,x,y,2);
          winB = verif_win(mat_jeu);
          afficher_grille(mat_jeu,fic);
          if(winB > 0){
            printf("\n Le joueur B à gagné !!\n ");
          }
        }
    }
    compteur = verif_end(mat_jeu);

  }
  if(compteur == 0){
    printf("\nMatch Nul !!\n");
  }

fclose(fic);

}
