/* Menu du TP 2 - Base de donnees sur des personnes*/
#include<stdio.h>
#include<string.h>
#define N 50

/* Definition du type date (jour, mois, annee) */
typedef struct { int jour, mois, an; } t_date;

/* Definition du type sexe avec la convention INSEE */
typedef enum { homme = 1, femme } t_sexe;

/* Definition du type personne (prenom, sexe, date de naissance) */
typedef struct { char prenom[20] ; t_sexe sexe ; t_date naissance ; } t_personne ;

/*Definition du type mois (numéro, nb_jour) */
typedef struct { int numero ; int nb_jour ;} t_mois;

	
void afficher_base(t_personne* amis, int nb_amis)
{
	int i;
	for(i=0; i < nb_amis; i++){
		printf("Prénom: %s // Date de naissance: %i/%i/%i // ",amis[i].prenom,amis[i].naissance.jour,amis[i].naissance.mois,amis[i].naissance.an);
		if(amis[i].sexe == 1){
			printf("Sexe: Homme \n");
		}else{
			printf("Sexe: Femme \n");
		}	
	}
}

void afficher_nombre_fh(t_personne* amis, int nb_amis)
{	
	int i;
	int nb_femme = 0;
	int nb_homme = 0;
	for(i=0; i < nb_amis; i++){
		if(amis[i].sexe == 1){
			nb_homme++;
		}else{
			nb_femme++;
		}	
	}
	printf("Il y a %i hommes et %i femmes dans la base",nb_homme,nb_femme);
}

void afficher_cadet(t_personne* amis, int nb_amis)
{
	int i = 0;
	t_personne jeune = amis[i];
	for(i = 1; i < nb_amis; i++){
		if(amis[i].naissance.an > jeune.naissance.an){
			jeune = amis[i];
		}else if(amis[i].naissance.an == jeune.naissance.an){
			if(amis[i].naissance.mois > jeune.naissance.mois){
				jeune = amis[i];
			}else if(amis[i].naissance.mois == jeune.naissance.mois){
				if(amis[i].naissance.jour > jeune.naissance.jour){
					jeune = amis[i];
				}
			}
		}
	}
	
	printf("Le cadet s'appelle %s",jeune.prenom);	
}

void afficher_anniv(t_personne* amis, int nb_amis)
{	
	int i,j;
	int vrai;
	char prenom_enter[20];
	printf("Veuillez entrer un prénom: ");
	scanf("%s", prenom_enter);
	for(i = 0; i < nb_amis; i++){
		vrai = 1;
		for(j = 0; prenom_enter[j] != '\0' && vrai == 1; j++){
			if(amis[i].prenom[j] == prenom_enter[j]){
				vrai = 1;
				}else{
				vrai = 0;
				}
		}
		if(vrai == 1){
			printf("Né(e) le %i/%i/%i \n", amis[i].naissance.jour,amis[i].naissance.mois,amis[i].naissance.an);
		}
	}
}	

void ajouter_personne(t_personne* amis, int* nb_amis, t_mois * mois)
{	
	t_personne prenom_enter;
	
	printf("Veuillez entrer un prénom: ");
	scanf("%s", prenom_enter.prenom);
	printf("Veuillez entrer le sexe (homme ou femme): ");
	scanf("%i", &(prenom_enter.sexe));
	printf("Veuillez enter l'année de naissance: ");
	scanf("%i", &(prenom_enter.naissance.an));
	printf("Veuillez enter le mois de naissance: ");
	scanf("%i", &(prenom_enter.naissance.mois));
	printf("Veuillez enter le jour de naissance: ");
	scanf("%i", &(prenom_enter.naissance.jour));
	if(prenom_enter.naissance.jour < mois[prenom_enter.naissance.mois].nb_jour && prenom_enter.naissance.jour > 0){
		amis[*nb_amis] = prenom_enter;
		(*nb_amis)++;
	}
	else{
		printf("Le jour entré est incorrect");
	}
}

/* Programme principal */
int main()
{	

	/* Declaration de la base de donnees, de taille maximale 50 et de taille utile nb_amis */
	t_personne amis[N]={{"Elodie",femme,{30,5,1996}}, {"Julien",homme,{8,11,1996}},{"Camille",femme,{2,6,1995}}, {"Adrien",homme,{20,11,1996}},{"Camille",homme,{12,5,1994}}, {"Lise",femme,{5,10,1995}}} ;
	t_mois mois[N]={{1,31}, {2,29}, {3,31}, {4,30}, {5,31}, {6,30}, {7,31}, {8,31}, {9,30}, {10,31}, {11,30}, {12,31}};
	int nb_amis = 6 ;

	int choix;	/* Choix de l'utilisateur */

	do
	{	/* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Afficher le contenu de la base\n");
		printf(" 2 - Afficher le nombre d'hommes et de femmes\n");
		printf(" 3 - Afficher le prenom de la personne la plus jeune\n");
		printf(" 4 - Afficher les anniversaires d'un prenom\n");
		printf(" 5 - Ajouter une personne\n");
		printf(" 6 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1 : afficher_base(amis,nb_amis); break;
			case 2:  afficher_nombre_fh(amis,nb_amis); break;
			case 3:  afficher_cadet(amis,nb_amis); break;
			case 4:  afficher_anniv(amis,nb_amis); break;
			case 5:  ajouter_personne(amis,&nb_amis,mois); break;
			case 6:  break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}
	}
	while(choix!=6);
	printf("Au revoir !\n");
	return 0;
}