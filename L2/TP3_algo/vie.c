#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define N 8

int nb_voisins(int x, int y, int mat[N][N]){
	int compteur = 0;
	if(mat[x][y+1]==1){
		compteur++;
	}
	if(mat[x][y-1]==1){
		compteur++;
	}
	if(mat[x+1][y]==1){
		compteur++;
	}
	if(mat[x-1][y]==1){
		compteur++;
	}
	if(mat[x+1][y+1]==1){
		compteur++;
	}
	if(mat[x-1][y-1]==1){
		compteur++;
	}
	if(mat[x+1][y-1]==1){
		compteur++;
	}
	if(mat[x-1][y+1]==1){
		compteur++;
	}
	return compteur;
}

void init_mat_fic(int mat_1[N][N], int mat_2[N][N]){
	int x,y;
	int a,i,j;
	FILE * fic;
	char nom[20];
	printf("Saisir le nom du fichier: ");
	scanf("%s",nom);
	fic = fopen(nom,"r");
	fscanf(fic,"%i%i",&x,&y);
	while(!feof(fic)){
		mat_1[x][y] = 1;
		fscanf(fic,"%i%i",&x,&y);
	}
	mat_1[x][y] = 1;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a = nb_voisins(i,j,mat_1);
			mat_2[i][j] = a;
			
		}
	}
	fclose(fic);	
}


void init_mat_voisins(int mat_1[N][N], int mat_2[N][N]){
	int a;
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			a = nb_voisins(i,j,mat_1);
			mat_2[i][j] = a;
			
		}
	}	
}

void init_nextgen(int mat_1[N][N], int mat_2[N][N]){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(mat_1[i][j] == 1 && (mat_2[i][j] != 2 && mat_2[i][j] != 3)){
				mat_1[i][j] = 0;
			}
			else if(mat_1[i][j] == 1 && mat_2[i][j] == 3){
				mat_1[i][j] = 1;
			}
		}
	}
}

void afficher_mat(int mat[N][N]){
	int i,j;
	char a;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(mat[i][j]==1){
				a='X';
			}
			else a = 'O';
			printf("%c ",a);
		}
		printf("\n");
	}
}

int main(){


	int nb_generation;
	int mat_automate[N][N]={0};
	int mat_voisins[N][N];
	int i,j;
	printf("Saisir le nombre de génération: ");
	scanf("%i",&nb_generation);
	init_mat_fic(mat_automate,mat_voisins);
	init_nextgen(mat_automate,mat_voisins);
	system("clear");
	afficher_mat(mat_automate);
	sleep(1);
	for(i=0;i<nb_generation-1;i++){
		system("clear");
		init_mat_voisins(mat_automate,mat_voisins);
		init_nextgen(mat_automate,mat_voisins);
		afficher_mat(mat_automate);
		sleep(1);
	}
	
	/*for(i=0;i<N;i++){
	printf("\n");
		for(j=0;j<N;j++){
			printf("%i ",mat_voisins[i][j]);
		}
	}*/
	

	
}
















