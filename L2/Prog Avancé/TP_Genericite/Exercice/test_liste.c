#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste.h>


int
main(int argc, char * argv[])
{

  /* Partie options */

  int a;
  int choix = 0;
  int type_tri = 0;
  static struct option option_l[] = {
    {"verbose",no_argument, NULL, (int)'v'},
    {0,0,0,0}
  };

  if(argc > 1){

  a = getopt_long(argc,argv,"v",option_l,NULL);

  const int N = atoi(argv[1]);
  printf("\nN = %i\n",N);

  err_t noerr = OK;

  individu_t ** individus = NULL  ;
  fraction_t ** fractions = NULL  ;
  string_t ** strings = NULL  ;

  liste_t * liste = NULL ;
  int i = 0 ;

  individus = malloc( sizeof(individu_t *) * N )  ;
  fractions = malloc( sizeof(fraction_t *) * N )  ;
  strings = malloc( sizeof(string_t *) * N )   ;

  printf("Choisir une méthode de création: \n");
  printf("1: Par référencement\n");
  printf("2: Par copie\n");
  while(choix != 1 && choix != 2){
    printf("Votre choix: ");
    scanf("%i",&choix);
  }

    printf("\nChoisir une méthode de tri: \n");
    printf("1: Tri bulle\n");
    printf("2: Tri qsort\n");
    printf("Votre choix: ");
    scanf("%i",&type_tri);




  printf( "Debut du programme des test sur les listes de %d objets homogenes\n" , N ) ;

  if(a =='v')printf( "\nTest creation d'une liste de %d individus \n" , N ) ;
  char prenom[128] ;
  char nom[128] ;
  if(choix == 1) liste = liste_creer(N,individu_referencer_cb,individu_effacer_cb);
  else if(choix == 2) liste = liste_creer(N, individu_copier_cb, individu_detruire_cb);

  for( i=0 ; i<N ; i++ )
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ;
      liste_elem_ecrire( liste , individus[i] , i ) ;
    }

  if(a == 'v')printf( "Test affichage liste d'individus AVANT tri \n" ) ;
  liste_afficher( liste , individu_afficher_cb, '/') ;
  printf( "\n");

  if(a == 'v')printf( "Test Tri de la liste des individus\n" );
  liste_trier(liste,individu_comparer_cb,type_tri);

  if(a == 'v')printf( "Test affichage liste d'individus APRES tri\n" ) ;
  liste_afficher( liste ,individu_afficher_cb ,'/' ) ;
  printf( "\n");

  if(a == 'v')printf( "Test destruction liste d'individus\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }
    for(i = 0; i < N; i++){
      if(individus[i] != NULL){
        individu_detruire(&individus[i]);
      }
    }

  if(a == 'v')printf( "\nTest creation d'une liste de %d fractions \n" , N ) ;
  if(choix == 1) liste = liste_creer(N,fraction_referencer_cb,fraction_effacer_cb);
  else if(choix == 2) liste = liste_creer(N,fraction_copier_cb,fraction_detruire_cb);
  for( i=0 ; i<N ; i++ )
    {
      fractions[i] = fraction_creer( N-i , N-i+1 ) ;
      liste_elem_ecrire( liste , fractions[i] , i ) ;
    }

  if(a == 'v')printf( "Test affichage liste de fractions AVANT tri\n" ) ;
  liste_afficher( liste ,fraction_afficher_cb ,'/' ) ;
  printf( "\n");

  if(a == 'v')printf( "Test Tri de la liste des fractions\n" );
  liste_trier(liste,fraction_comparer_cb,type_tri);

  if(a == 'v')printf( "Test affichage liste des fractions APRES tri\n" ) ;
  liste_afficher( liste ,fraction_afficher_cb ,'/' ) ;
  printf( "\n");

  if(a == 'v')printf( "Test destruction liste de fractions\n" ) ;
  if( ( noerr = liste_detruire( &liste ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }
  for(i = 0; i < N; i++){
    if(fractions[i] != NULL){
      fraction_detruire(&fractions[i]);
    }
  }


  if(a == 'v')printf( "\nTest creation d'une liste de %d strings \n" , N ) ;
  char string[128] ;
  if(choix == 1) liste = liste_creer(N,string_referencer_cb,string_effacer_cb);
  else if(choix == 2) liste = liste_creer(N, string_copier_cb,string_detruire_cb);
  for( i=0 ; i<N ; i++ )
    {
      sprintf( string , "string_%d" , N-i ) ;
      strings[i] = string_creer( string ) ;
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }

  if(a == 'v')printf( "Test affichage liste de strings AVANT tri\n" ) ;
  liste_afficher( liste ,string_afficher_cb, '/' ) ;
  printf( "\n");

  if(a == 'v')printf( "Test Tri de la liste des strings\n" );
  liste_trier(liste, string_comparer_cb, type_tri) ;

  if(a == 'v')printf( "Test affichage liste des strings APRES tri\n" ) ;
  liste_afficher( liste ,string_afficher_cb, '/' ) ;
  printf( "\n");

  if(a == 'v')printf( "Test destruction liste de strings\n" ) ;
  if( ( noerr = liste_detruire( &liste  ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

  for(i = 0; i < N; i++){
    if(strings[i] != NULL){
      string_detruire(&strings[i]);
    }
  }

  free( individus ) ;
  free( fractions ) ;
  free( strings ) ;

  printf( "\nFin du programme des test sur la lste d'objets homogenes\n" ) ;

  printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

}else{
  printf("\nERREUR: le programme s'utilise de cette manière ./test_liste <nb_elem> <options>\n\n");
}

  return(0) ;
}
