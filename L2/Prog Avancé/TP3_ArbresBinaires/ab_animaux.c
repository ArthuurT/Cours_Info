#include <ab_animaux.h>

/*
 * Affichage
 */


static
void ab_animaux_afficher_bis( const noeud_t * noeud ,
			  void (*fonction_affichage)(const void *),int profondeur, int indicateur)
{
  int i;
  for(i = 0; i < profondeur; i++) printf("|-----");
	if(indicateur == 0) printf("[ ]");
	else if (indicateur == 1) printf("[OUI] ");
	else if (indicateur == 2) printf("[NON] ");
	fonction_affichage(noeud->etiquette);
  printf("\n");
  if(noeud_existe(noeud->gauche)) ab_animaux_afficher_bis(noeud->gauche, fonction_affichage, profondeur + 1, 1);
  if(noeud_existe(noeud->droit)) ab_animaux_afficher_bis(noeud->droit, fonction_affichage, profondeur + 1, 2);
}

extern void ab_animaux_afficher( const ab_t * arbre, void (*fonction_affichage)(const void *),int profondeur){
	ab_animaux_afficher_bis(arbre->racine,fonction_affichage,profondeur,0);
}
/*
 * Reconnaissance
 */

static void ab_animaux_reconnaitre_bis(ab_t * a, noeud_t * noeud, noeud_t * racine, err_t (*fonction_affectation)(void * , void *), void (*fonction_affichage)(const void *)){

	noeud_t * nomN, * questionN;
	string_t * temp;
	char reponse[5];
	char nom[50];
	char question[50];

	if(noeud != NULL){


		/* Question + réponse du joueur */

		fonction_affichage(noeud->etiquette);
		printf("\nRéponse: ");
		scanf("%s",reponse);


		/* Choix de la branche */

			/* CAS "OUI" */

			if((strcmp(reponse,"oui") == 0) || (strcmp(reponse,"Oui") == 0) || (strcmp(reponse,"OUI") == 0)){

				if(noeud_feuille(noeud)) printf("Bravo, animal trouvé!\n");
				else if(noeud->gauche == NULL){

					printf("Je donne ma langue au chat. \nQuelle est la réponse ?: ");
					scanf("%s",nom);

					a->taille++;
					temp = string_creer(nom);
					nomN = noeud_creer(a->taille,temp,NULL,NULL,fonction_affectation);
					string_detruire(&temp);
					noeud->gauche = nomN;



				}
				else ab_animaux_reconnaitre_bis(a,noeud->gauche,noeud,fonction_affectation,fonction_affichage);
			}

			/* CAS "NON" */

			else if((strcmp(reponse,"non") == 0) || (strcmp(reponse,"Non") == 0) || (strcmp(reponse,"NON") == 0)){

				if(noeud_feuille(noeud)){

					printf("Je donne ma langue au chat. \nQuelle est la réponse ?: ");
/*!!*/		scanf(" %[^\n]s", nom);
					printf("Donnez une question dont la réponse est oui pour '%s' et non pour '",nom);
					fonction_affichage(noeud->etiquette);
					printf("': ");
					scanf(" %[^\n]s", question);

					a->taille++;
					temp = string_creer(nom);
					nomN = noeud_creer(a->taille,temp,NULL,NULL,fonction_affectation);
					string_detruire(&temp);

					a->taille++;
					temp = string_creer(question);
					questionN = noeud_creer(a->taille,temp,nomN,noeud,fonction_affectation);
					string_detruire(&temp);

					racine->gauche = questionN;


				}else if(noeud->droit == NULL){

					printf("Je donne ma langue au chat. \nQuelle est la réponse ?: ");
					scanf(" %[^\n]s", nom);


					a->taille++;
					temp = string_creer(nom);
					nomN = noeud_creer(a->taille,temp,NULL,NULL,fonction_affectation);
					string_detruire(&temp);
					noeud->droit = nomN;

				}else{
					ab_animaux_reconnaitre_bis(a,noeud->droit,noeud,fonction_affectation,fonction_affichage);
				}

			/* CAS "Autre réponse" */

			}else{
					printf("Réponse incorrect (Oui / Non)\n");
					ab_animaux_reconnaitre_bis(a,noeud,noeud,fonction_affectation,fonction_affichage);
			}
	}
}

extern
void ab_animaux_reconnaitre( ab_t * arbre ,
			     err_t (*fonction_affectation)(void * , void *) ,
			     void (*fonction_affichage)(const void *))
{

ab_animaux_reconnaitre_bis(arbre,arbre->racine,arbre->racine,fonction_affectation,fonction_affichage);

}
