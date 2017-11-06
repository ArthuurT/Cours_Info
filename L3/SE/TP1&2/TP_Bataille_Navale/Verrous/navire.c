#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>
#include <bateau.h>
#include <mer.h>

/*
 *  Fonctions verrous
 */


void PoseVerrouBateau(int fd1, bateau_t * bateau, int mode){

  int taille_bateau;
  off_t offset;
  int i;
  struct flock verrouBouclier;

  taille_bateau = coords_nb_get(bateau->corps);

  for(i = 0; i < taille_bateau; i++){      /* Pour chaque cellule du bateau */

    offset = coord_position_get(coords_coord_get(bateau->corps,i));
    lseek(fd1,offset,SEEK_SET);

    verrouBouclier.l_type = mode;
    verrouBouclier.l_whence = SEEK_CUR;
    verrouBouclier.l_start = 0;
    verrouBouclier.l_len = MER_TAILLE_CASE;

    fcntl(fd1,F_SETLKW,verrouBouclier);

  }

  if(mode == 0 || mode == 1) printf("\nPose du verrou Bouclier --> SUCCESS\n");
  else printf("Desactivation du verrou Bouclier --> SUCCESS");

}

void PoseVerrouEnTete(int fd1, int mode){

  struct flock verrouEnTete;


    verrouEnTete.l_type = mode;
    verrouEnTete.l_whence = SEEK_SET;
    verrouEnTete.l_start = 0;
    verrouEnTete.l_len = MER_TAILLE_ENTETE;

    fcntl(fd1,F_SETLKW,verrouEnTete);

  if(mode == 0 || mode == 1) printf("\nPose du verrou EnTete --> SUCCESS\n");
  else printf("Desactivation du verrou EnTete --> SUCCESS");

}

void PoseVerrouMer(int fd1, int mode){

  struct flock verrouMer;
  int rowmer;
  int colmer;
  off_t taillemer;

  mer_dim_lire(fd1,&rowmer,&colmer);

  mer_lc2pos(fd1,rowmer,colmer,&taillemer);

  verrouMer.l_type = mode;
  verrouMer.l_whence = SEEK_SET;
  verrouMer.l_start = 0;
  verrouMer.l_len = 0;

  fcntl(fd1,F_SETLKW,verrouMer);

  if(mode == 0 || mode == 1) printf("\nPose du verrou Mer --> SUCCESS\n");
  else printf("Desactivation du verrou Mer --> SUCCESS");

}

void PoseVerrouDeplacement(int fd, bateau_t * bateau, int mode, coords_t * coordvoisins){

  struct flock verrouDeplacement;
  int i;
  off_t offset;

  printf("\nListe des voisins:\n");
  mer_voisins_afficher(fd,coordvoisins);
  printf("\n");

  for(i = 0; i < coords_nb_get(coordvoisins); i++){

    offset = coord_position_get(coords_coord_get(coordvoisins,i));
    lseek(fd,offset,SEEK_SET);

    verrouDeplacement.l_type = mode;
    verrouDeplacement.l_whence = SEEK_CUR;
    verrouDeplacement.l_start = 0;
    verrouDeplacement.l_len = MER_TAILLE_CASE;

    fcntl(fd,F_SETLKW,verrouDeplacement);

  }

  if(mode == 0 || mode == 1) printf("\nPose du verrou Deplacement --> SUCCESS\n");
  else printf("Desactivation du verrou Deplacement --> SUCCESS");

}



/*
 *  Programme principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;
  bateau_t * bateau;
  booleen_t touche = FAUX;
  booleen_t deplace;
  booleen_t cible;
  int nb_tourjeu = 0;
  int cpt_bateau;
  coord_t coordcible;
  coords_t * coordvoisins;
  int fd1;


  /*----------*/

  strcpy( nomprog , tab_arg[0] ) ;

  if( nb_arg != 4 )
    {
      fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n",
	       nomprog );
      exit(-1);
    }

  if( strlen(tab_arg[2]) !=1 )
    {
      fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
	       nomprog , tab_arg[2] );
      exit(-1) ;
    }


  strcpy( fich_mer , tab_arg[1] );
  marque = tab_arg[2][0] ;
  sscanf( tab_arg[3] , "%f" , &energie );

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)getpid());

  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n",
	  nomprog , marque , getpid() );


    /*****************
    *  INITALISATION *
    ******************/

  printf("\n\n****** INITALISATION ******\n\n");


  fd1 = open(fich_mer, O_RDWR);

  /* Pose du bateau sur la mer */

  PoseVerrouMer(fd1,F_WRLCK);
  bateau = bateau_new(coords_new(), marque, getpid());
  int boolbateau = mer_bateau_initialiser(fd1,bateau);
  PoseVerrouMer(fd1,F_UNLCK);

  sleep(TEMPS_ATTENTE);

  if(boolbateau == CORRECT){

    printf("\n[Bateau %c]: Pose du bateau sur la mer --> SUCCESS\n\n",marque);
    PoseVerrouEnTete(fd1,F_WRLCK);
    mer_nb_bateaux_lire(fd1,&cpt_bateau);
    cpt_bateau++;
    mer_nb_bateaux_ecrire(fd1,cpt_bateau);
    PoseVerrouEnTete(fd1,F_UNLCK);

  }else if(boolbateau == ERREUR){

    printf("\n[Bateau %c]:Pose du bateau sur la mer --> FAILURE\n\n",marque);
    exit(1);

  }

  //coords_printf(bateau->corps);

  /* Destruction du verrou après que le bateau soit posé */

  sleep(TEMPS_ATTENTE);


    /**********
    *  PARTIE *
    **********/


  /* Creation d'un verrou sur un bateau (bouclier/energie) */

  PoseVerrouBateau(fd1,bateau,F_WRLCK); // mode = 1 -> WRLCK

  /* BOUCLE DE JEU */

  do{

    printf("\n[Bateau %c]: // Tour de jeu n°%i \\\\ \n",marque,nb_tourjeu);

    /* Desactivation du verrou bouclier si energie < SEUIL  */

    if(energie < BATEAU_SEUIL_BOUCLIER){
      PoseVerrouBateau(fd1,bateau,F_UNLCK); //mode = 2 -> UNLCK
    }

    mer_bateau_est_touche(fd1,bateau,&touche);

    /* Bateau touché avec bouclier en place */

    if(touche == VRAI && energie >= BATEAU_SEUIL_BOUCLIER){

      printf("\n[Bateau %c]: Bateau touché -> Bouclier disponible -> Aucun dégats apparent\n",marque);
      touche = FAUX;

    /* Bateau touché sans bouclier en place */

    }else if(touche == VRAI && energie < BATEAU_SEUIL_BOUCLIER){

      printf("\n[Bateau %c]: Bateau touché -> coulé\n",marque);

      PoseVerrouEnTete(fd1,F_WRLCK);
      mer_nb_bateaux_lire(fd1,&cpt_bateau);
      cpt_bateau--;
      mer_nb_bateaux_ecrire(fd1,cpt_bateau);
      mer_bateau_couler(fd1,bateau);
      PoseVerrouEnTete(fd1,F_UNLCK);

      printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
    	  nomprog , marque , getpid() );
      exit(0);

    }else{
      printf("\n[Bateau %c]: Bateau non-touché\n",marque);
    }


    /* Phase de tir */

    printf("\n[Bateau %c]:Debut de la phase de tir\n",marque);

    mer_bateau_cible_acquerir(fd1,bateau,&cible,&coordcible);

    if(cible == FAUX){
      printf("[Bateau %c]:Pas de cible trouvé\n",marque);
    }else{
      printf("[Bateau %c]:Cible trouvé\n",marque);

      mer_bateau_cible_tirer(fd1,coordcible);

      printf("[Bateau %c]:Tir effectué\n",marque);
    }

    printf("\n[Bateau %c]:Fin de la phase de tir\n",marque);

    sleep(3);

    /* Phase de déplacement */

    printf("\n[Bateau %c]:Debut de la phase de déplacement\n",marque);

    mer_voisins_rechercher(fd1,bateau,&coordvoisins);
    PoseVerrouDeplacement(fd1,bateau,F_WRLCK,coordvoisins);
    mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);
    PoseVerrouDeplacement(fd1,bateau,F_UNLCK,coordvoisins);

    if(deplace == VRAI){
      printf("\n[Bateau %c]:Deplacement effectué\n",marque);
      energie = energie * 0.95;
      printf("[Bateau %c]: Energie restante : %f\n",marque,energie);
    }

    printf("\n[Bateau %c]:Fin de la phase de déplacement\n",marque);

    sleep(3);

    nb_tourjeu++;

    PoseVerrouEnTete(fd1,F_RDLCK);
    mer_nb_bateaux_lire(fd1,&cpt_bateau);
    PoseVerrouEnTete(fd1,F_UNLCK);

    printf("\n[Bateau %c]:Nombre de bateau restant sur la mer: %i\n",marque,cpt_bateau);

  }while(cpt_bateau > 1);


  printf("\n\nPlus de bateau sur la mer\nNavire %c vainqueur\n\n",marque);

  printf("****** FIN DE PARTIE ******\n");

  PoseVerrouEnTete(fd1,F_WRLCK);
  mer_nb_bateaux_lire(fd1,&cpt_bateau);
  cpt_bateau--;
  mer_bateau_couler(fd1,bateau);
  mer_nb_bateaux_ecrire(fd1,cpt_bateau);
  PoseVerrouEnTete(fd1,F_UNLCK);


  close(fd1);
  exit(1);

}
