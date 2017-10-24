#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>


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
    verrouBouclier.l_len = 1;

    fcntl(fd1,F_SETLKW,verrouBouclier);

  }

  if(mode == 0 || mode == 1) printf("\nPose du verrou Bouclier --> SUCCESS\n");
  else printf("Desactivation du verrou Bouclier --> SUCCESS");

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
    verrouDeplacement.l_len = 1;

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
  int rowmer;
  int colmer;
  off_t taillemer;
  bateau_t * bateau;
  booleen_t touche = FAUX;
  booleen_t deplace;
  booleen_t cible;
  int nb_tourjeu = 0;
  int cpt_bateau;
  coord_t coordcible;
  coords_t * coordvoisins;




  /* variables utilisation verrou */

  int fd1;
  struct flock verrouPosition;

  /* variables création bateau */


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


  /* Creation verrou sur mer pour pose du bateau */

  fd1 = open(fich_mer, O_RDWR);

  mer_dim_lire(fd1,&rowmer,&colmer);

  mer_lc2pos(fd1,rowmer,colmer,&taillemer);

  verrouPosition.l_type = F_WRLCK;
  verrouPosition.l_whence = SEEK_SET;
  verrouPosition.l_start = 0;
  verrouPosition.l_len = taillemer;

  fcntl(fd1,F_SETLKW,verrouPosition);

  printf("\nPose du verrou Position --> SUCCESS\n");

  /* Pose du bateau sur la mer */

  bateau = bateau_new(coords_new(), marque, getpid());

  mer_nb_bateaux_lire(fd1,&cpt_bateau);
  printf("CPT BATEAU : %i\n",cpt_bateau);
  cpt_bateau++;
  mer_nb_bateaux_ecrire(fd1,cpt_bateau);

  if(mer_bateau_initialiser(fd1,bateau) == 0){
    printf("\nPose du bateau sur la mer --> SUCCESS\n\n");
  }else{
    printf("\nPose du bateau sur la mer --> FAILURE\n\n");
    exit(1);
  }

  coords_printf(bateau->corps);

  /* Destruction du verrou après que le bateau soit posé */

  verrouPosition.l_type = F_UNLCK;
  fcntl(fd1,F_SETLKW,verrouPosition);


    /**********
    *  PARTIE *
    **********/

  printf("\n\n****** DEBUT DE PARTIE ******\n\n");


  /* Creation d'un verrou sur un bateau (bouclier/energie) */

  PoseVerrouBateau(fd1,bateau,1); // mode = 1 -> WRLCK

  /* BOUCLE DE JEU */

  do{

    printf("\n// Tour de jeu n°%i \\\\ \n",nb_tourjeu);

    /* Desactivation du verrou bouclier si energie < SEUIL  */

    if(energie < BATEAU_SEUIL_BOUCLIER){
      PoseVerrouBateau(fd1,bateau,2); //mode = 2 -> UNLCK
    }

    mer_bateau_est_touche(fd1,bateau,&touche);

    /* Bateau touché avec bouclier en place */

    if(touche == VRAI && energie >= BATEAU_SEUIL_BOUCLIER){

      printf("\nBateau touché -> Bouclier disponible -> Aucun dégats apparent\n");
      touche = FAUX;

    /* Bateau touché sans bouclier en place */

    }else if(touche == VRAI && energie < BATEAU_SEUIL_BOUCLIER){

      printf("\nBateau touché -> coulé\n");
      mer_bateau_couler(fd1,bateau);

      mer_nb_bateaux_lire(fd1,&cpt_bateau);
      cpt_bateau--;
      mer_nb_bateaux_ecrire(fd1,cpt_bateau);

      printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
    	  nomprog , marque , getpid() );
      exit(0);

    }else{
      printf("\nBateau non-touché\n");
    }


    /* Phase de tir */

    printf("\nDebut de la phase de tir\n");

    mer_bateau_cible_acquerir(fd1,bateau,&cible,&coordcible);

    if(cible == FAUX){
      printf("Pas de cible trouvé\n");
    }else{
      printf("Cible trouvé\n");

      mer_bateau_cible_tirer(fd1,coordcible);

      printf("Tir effectué\n");
    }

    printf("\nFin de la phase de tir\n");

    sleep(5);

    /* Phase de déplacement */

    printf("\nDebut de la phase de déplacement\n");

    mer_voisins_rechercher(fd1,bateau,&coordvoisins);
    PoseVerrouDeplacement(fd1,bateau,1,coordvoisins);
    mer_bateau_deplacer(fd1,bateau,coordvoisins,&deplace);
    PoseVerrouDeplacement(fd1,bateau,2,coordvoisins);

    if(deplace == VRAI){
      printf("\nDeplacement effectué\n");
      energie = energie * 0.95;
      printf("Energie restante : %f\n",energie);
    }

    printf("\nFin de la phase de déplacement\n");

    sleep(5);

    nb_tourjeu++;

    mer_nb_bateaux_lire(fd1,&cpt_bateau);

    printf("\nNombre de bateau restant sur la mer: %i\n",cpt_bateau);

  }while(cpt_bateau > 1);


  printf("\n\nPlus de bateau sur la mer\nNavire %c vainqueur\n\n",marque);

  printf("****** FIN DE PARTIE ******");

  mer_bateau_couler(fd1,bateau);
  mer_nb_bateaux_lire(fd1,&cpt_bateau);
  cpt_bateau--;
  mer_nb_bateaux_ecrire(fd1,cpt_bateau);

  close(fd1);
  exit(1);

}
