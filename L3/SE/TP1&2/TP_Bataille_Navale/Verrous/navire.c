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
 *  Programme principal
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char fich_mer[128] ;
  case_t marque = MER_CASE_LIBRE ;
  char nomprog[128] ;
  float energie = 0.0 ;

  /* variables utilisation verrou */

  int fd1;
  char VerrouPosition[128];
  char VerrouBouclier[128];
  struct flock verrouBouclier;
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

  fd1 = open(fich_mer, O_RDONLY);

  sprintf(VerrouPosition,"VerrouPosition_%s",fich_mer);

  verrouPosition.l_type = F_WRLCK;
  verrouPosition.l_whence = 0;
  verrouPosition.l_start = 0;
  verrouPosition.l_len = 10;

  fcntl(fd1,F_SETLKW,verrouPosition);

  printf("Pose du verrou Position --> SUCCESS\n");

  /* Pose du bateau sur la mer */

  if(mer_bateau_initialiser(fd1,bateau_new(coords_new(), marque, getpid())) == 0){
    printf("Pose du bateau sur la mer --> SUCCESS\n");
  }else{
    printf("Pose du bateau sur la mer --> FAILURE\n");
    exit(1);
  }

  /* Destruction du verrou après que le bateau soit posé */

  verrouPosition.l_type = F_UNLCK;

  fcntl(fd1,F_SETLKW,verrouPosition);

  close(fd1);



    /**********
    *  PARTIE *
    **********/

  printf("\n\n****** DEBUT DE PARTIE ******\n\n");


  /* Creation d'un verrou sur un bateau (bouclier/energie) */

    sprintf(VerrouBouclier,"VerrouBouclier_%s",fich_mer);

    fd1 = open(fich_mer, O_RDONLY);

    verrouBouclier.l_type = F_WRLCK;
    verrouBouclier.l_whence = 0;
    verrouBouclier.l_start = 0;
    verrouBouclier.l_len = 10;

    fcntl(fd1,F_SETLKW,verrouBouclier);
    close(fd1);

    printf("Pose du verrou Bouclier --> SUCCESS");



/************************************/



  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
	  nomprog , marque , getpid() );

  exit(0);
}
