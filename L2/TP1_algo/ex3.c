#include <stdlib.h>
#include <stdio.h>

int main(){

	FILE * fic;
	FILE * fic_pos;
	FILE * fic_neg;
	float val_max, val_min;
	float nombre, nb_positif, nb_negatif;
	fic = fopen("releves.txt","r");
	fic_pos = fopen("positif.txt","w");
	fic_neg = fopen("negatif.txt","w");
	fscanf(fic,"%f",&nombre);
	val_max  = nombre;
	val_min = nombre;
	while(!feof(fic)){
		if(nombre > 0){
			fprintf(fic_pos,"%f ",nombre);
		}
		if(nombre < 0){
			fprintf(fic_neg,"%f ",nombre);
		}
		if(val_max < nombre){
			val_max = nombre;
		}
		if(val_min > nombre){
			val_min = nombre;
		}
		fscanf(fic,"%f",&nombre);
	}
	printf("\n la valeur maximale du fichier est %f et la minimale est %f \n\n",val_max,val_min);
	fclose(fic);
	fclose(fic_pos);
	fclose(fic_neg);
}
			
	