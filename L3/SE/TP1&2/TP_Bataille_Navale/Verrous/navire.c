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

  printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ",
	  nomprog , marque , getpid() );

  /* Création d'un bateau */





  /* Creation verrou sur mer pour pose du bateau */

  sprintf(VerrouPosition,"VerrouPosition_%s",fich_mer);

  fd1 = open(fich_mer, O_RDONLY, 0666);

  verrouPosition.l_type = F_WRLCK;
  verrouPosition.l_whence = 0;
  verrouPosition.l_start = 0;
  verrouPosition.l_len = 10;

  fcntl(fd1,F_SETLKW,verrouPosition);
  close(fd1);

  printf("Pose du verrou Position réussi");

  /* Pose du bateau sur la mer */

  mer_bateau_initialiser();

  /* Destruction du verrou après que le bateau soit posé */

  verrou.l_type = F_UNLCK;

  fcntl(fd1,F_SETLKW,verrou);

  /* Creation d'un verrou sur un bateau (bouclier/energie) */

  if(energie > BATEAU_MAX_ENERGIE){

    sprintf(VerrouBouclier,"VerrouBouclier_%s",fich_mer);

    fd1 = open(fich_mer, O_RDONLY, 0666);

    verrouBouclier.l_type = F_WRLCK;
    verrouBouclier.l_whence = 0;
    verrouBouclier.l_start = 0;
    verrouBouclier.l_len = 10;

    if(fcntl(fd1,F_SETLK,verrouBouclier) == -1) printf("Pose du verrou Bouclier impossible");
    close(fd1);

    printf("Pose du verrou Bouclier réussi");

  }

  printf("Pose du verrou Bouclier impossible -> energie non suffisante");







  printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ",
	  nomprog , marque , getpid() );

  exit(0);
}
