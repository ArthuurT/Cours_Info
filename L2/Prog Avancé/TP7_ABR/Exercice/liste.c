#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liste.h>

#include <stdarg.h>

/*
 * VARIABLE LOCALE
 */

unsigned long int liste_cpt = 0 ; 

/*
 * Methodes d'acces 
 */

/* Nombre d'elements */

extern 
int liste_nb_lire( liste_t * const liste )
{
  return(liste->nb );
} 

/* -- Acces individuel a un element */

extern 
void * liste_elem_lire( liste_t * const liste  , const int ind )
{
  if( (ind < 0) || (ind > liste_nb_lire(liste)-1 ) )
    {
      fprintf( stderr , "liste_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , liste_nb_lire(liste)-1 );
      return(NULL);
    }

  return( liste->liste[ind] ) ;
}

/*
 * Tests 
 */

extern 
booleen_t liste_existe( liste_t * const liste )
{
  if( liste == NULL )
    {
      return(FAUX) ; 
    }
  else
    {
      return(VRAI) ; 
    }
}

extern 
booleen_t liste_vide( liste_t * const liste )
{
  if( liste->nb == 0 )
    {
      return(VRAI) ; 
    }
  else
    {
      return(FAUX) ; 
    }
}

/*
 * Methodes d'affectation 
 */


/* -- Acces individuel a un element */
extern 
err_t liste_elem_ecrire( liste_t * liste , 
			 void * const elem ,
			 const int ind ) 
{

  err_t noerr = OK ; 

#ifdef _DEBUG_
  if( (ind < 0) || (ind > liste_nb_lire(liste) ) )
    {
      fprintf( stderr , "liste_elem_ecrire: mauvais indice d'element [%d] (devrait etre dans [%d..%d]\n",
	       ind , 0 , liste_nb_lire(liste) );
      return(ERR_LISTE_IND_ELEM);
    }
#endif

  if( (noerr = liste->affecter( &(liste->liste[ind]) ,
				elem  )) )
    return(noerr);
  
  return(OK) ;
}


/*
 * Creation d'une liste 
 */
extern
liste_t * liste_creer( const int nb ,
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,
		       err_t (*fonction_destruction)(void * e) ,
		       int (*fonction_comparer)(const void * n1 , const void * n2) )
{
  liste_t * liste = NULL ;
  int i = 0 ; 
  
  if(( liste= malloc(sizeof(liste_t))) == NULL )
    {
      fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
      return((liste_t *)NULL);
    }

  liste->nb = nb ;
  liste->liste = (void**)NULL ;
  if( nb > 0 ) 
    {
      if( ( liste->liste = malloc( sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
	  free( liste ) ;
	  return((liste_t *)NULL);
	}
    }

  for( i=0 ; i<nb ; i++ ) 
    liste->liste[i] = NULL ; 
  
  liste->affecter = fonction_affectation ;
  liste->detruire = fonction_destruction ; 
  liste->comparer = fonction_comparer ;
  liste_cpt++ ; 

  return(liste);
}

/*
 * Destruction d'une liste 
 */

extern
err_t liste_detruire( liste_t ** liste )
{
  err_t cr = OK ;
  int nb ;
  int i ;
  void * elem ;

  if( ! liste_existe((*liste)) )
    return(OK) ;

  nb = liste_nb_lire((*liste));

  for(i=0 ; i<nb ; i++)
    {
      elem = liste_elem_lire( (*liste) , i ) ;
      if( elem == NULL )
	continue ;
      
      if( (cr = (*liste)->detruire(&elem) ) )
	return(cr) ;
    }
  free( (*liste)->liste ) ;
  free( (*liste) ) ;
  (*liste) = (liste_t *)NULL ;
  
  liste_cpt-- ; 
  return(OK) ;
}


/*
 * Affichage d'une liste sur la sortie standard
 */

extern 
void liste_afficher( liste_t * const liste ,
		     void (*elem_afficher)(const void *),
		     const char separateur )
{
  int i ;
  int nb ;
  void * elem = NULL ;

  if( ! liste_existe(liste) )
    {
      printf("(inexistante)" );
      return ;
    }
  
  if( liste_vide(liste) )
    {
      printf("(vide)" );
      return ;
    }
  
  nb = liste_nb_lire(liste) ; 
  for( i=0 ; i<nb ; i++ ) 
    {
      elem = liste_elem_lire( liste , i ) ;
      if( elem != NULL )
	{
	  elem_afficher( elem ) ;
	}
      else
	{
	  printf("null") ;
	}
      printf("%c" , separateur ) ;
    } 
  printf( "(%d elements)" , nb );
}

extern
err_t liste_trier( liste_t * liste )
{
  qsort( liste->liste , (size_t)liste->nb , sizeof(void *) , liste->comparer ) ;
  return(OK) ; 
}


/*
 * Chargement d'une liste a partir d'un fichier 
 */
extern 
err_t liste_fd_charger( liste_t ** liste  ,							/* listeleau d'elements a charger */
			FILE *  fd ,							/* descripteur fichier de chargement */
			err_t (*fonction_affectation)( void * e1 , void * e2 ) ,   /* fonction d'affecation d'un element */ 
			err_t (*fonction_destruction)(void * e) ,                        /* fonction de destructiuon d'un element */
			int (*fonction_comparaison)( const void * , const void *) , /* fonction de comparaison de 2 elements */
			err_t (*fonction_chargement)(void * e, FILE *  desc ) ,	/* Fonction de chargement d'un element */
			booleen_t verbose ) /* Trace du chargement */
{
  int i  ;
  err_t noerr ;
  int nb ;

  /* Destruction de la liste si elle existe deja */
  if( !liste_existe( (*liste) )  )
    {
      if( (noerr = liste_detruire( liste ) ) )
	return(noerr) ; 
    }

  if( feof(fd) )
    return(OK) ; 

  /* Lecture du nombre d'elements */
  if( fscanf( fd , "%d\n" , &nb ) != 1 )
    {
      /* Pas d'element a charger */
      return(OK)  ;
    }

  /* Creation de la liste */
  if( ((*liste) = liste_creer(nb , fonction_affectation , fonction_destruction , fonction_comparaison ) ) == NULL )
    {
      fprintf( stderr , "liste_fd_charger: debordement memoire lors de la creation de la liste (%d elements demades)\n" , 
	       nb );
      return(ERR_DEB_MEMOIRE) ; 
    }

  /* Chargement des elements */
  if( verbose ) printf("Nombre d'elements:      ");
  for( i=0 ; i<nb ; i++ )
    {
      if( verbose ) printf("\b\b\b\b\b\b%6d" , i+1 );
      if( (noerr = (*fonction_chargement)( &((*liste)->liste[i]) , 
					   fd ) ) ) 
	return(noerr);
    }
  if( verbose ) printf("\n");

  return(OK) ;
}

extern 
err_t liste_charger( liste_t ** liste  ,						/* listeleau d'elements a charger */
		     char *  nom_fichier ,					/* Nom du fichier de chargement */
		     err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/* fonction d'affecation d'un element */ 
		     err_t (*fonction_destruction)(void * e) ,			/* fonction de destruction d'un element */
		     int (*fonction_comparaison)( const void * , const void *) , /* fonction de comparaison de 2 elements */
		     err_t (*fonction_chargement)(void *  e, FILE *  desc ) ,	/* Fonction de chargement d'un element */
		     booleen_t verbose )
{
  err_t cr = OK ; 
  FILE * fd = NULL ; 

  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "liste_charger: ouverture en lecture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Chargement */
  if( (cr = liste_fd_charger( liste ,
			      fd ,	
			      fonction_affectation,
			      fonction_destruction,
			      fonction_comparaison,
			      fonction_chargement ,
			      verbose ) ) )
    return(cr) ; 

  /* Fermeture */
  fclose(fd) ; 

  return(cr) ; 
}

/*
 * Sauvegarde d'une liste dans un fichier 
 */
extern 
err_t liste_fd_sauver( liste_t * liste  ,		/* liste a sauvegarder */
		       FILE * fd , 		/* descripteur fichier  */
		       err_t (*fonction_sauvegarde)( void * e, FILE *  desc) , /* Fonction de sauvegarde d'un element */
		       char separateur ) /* Separateur d'elements */
{
  int l  ;
  err_t noerr ;
  int nb ;

  if( ! liste_existe(liste) )
    {      
      return(OK) ; 
    }

  /* Ecriture du nombre d'elements */
  nb= liste_nb_lire(liste) ; 
  fprintf( fd , "%d\n" , nb )  ; 
  
  /* Ecriture des liste */
  for( l=0 ; l<nb ; l++ )
    {
      if( (noerr = (*fonction_sauvegarde)( liste_elem_lire( liste , l ) ,
					   fd ) ) ) 
	return(noerr);
      fprintf( fd , "%c" , separateur ) ;
    }

  return(OK) ;
}
  
extern 
err_t liste_sauver(  liste_t * liste  ,							/* listeleau a sauvegarder */
		     char *  nom_fichier ,						/* Nom fichier sauvegarde */
		     err_t (*fonction_sauvegarde)( void * e, FILE *  desc) ,	/* Fonction de sauvegarde d'un element */
		     char separateur )						/* Separateur d'elements */
{
  err_t cr = OK ; 
  FILE * fd = NULL ; 

  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "liste_sauver: ouverture en ecriture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Sauvegarde */
  if( ( cr = liste_fd_sauver( liste  ,
			      fd ,
			      fonction_sauvegarde, 
			      separateur ) )  )
    return(cr) ; 
  
  /* Fermeture */
  fclose(fd) ; 

  return(cr) ; 
}


/*
 * Recherche d'un element dans une liste triee 
 * Retour 
 * - VRAI si trouve ; result == indice de l'element dans la liste 
 * - FAUX sinon     ; result == indice d'insertion de l'element
 */

extern 
booleen_t liste_rechercher( int * result ,  
			    liste_t * liste  ,	               /* Liste de recherche */
			    void * element  )	       /* Element a rechercher dans la liste */
{  
  /* Assertions */
  if( ! liste_existe(liste) )
    {
      return(FAUX) ;
    }
  
   if( liste_vide(liste) )
     {
       return(FAUX) ;
     }
   
   (*result) = -1 ; 

   int i = 0 ;
   int nb = liste_nb_lire(liste) ; 
   int cmp = -1 ; 
   void * elem = NULL ; 
   
   while( (i<nb) && (cmp < 0) ) 
     {
       elem = liste_elem_lire( liste , i ) ;
       cmp = liste->comparer( &elem , &element) ;
       if( cmp < 0 ) i++ ;
     } 
   
   (*result) = i ; 

   if( cmp == 0 ) 
     return(VRAI) ; 
   else
     return(FAUX) ; 
}

/*
 * Insertion d'un element dans une liste triee
 */

extern 
err_t liste_inserer( liste_t * liste , void * elem ) 
{
  err_t noerr = OK ; 
  int nb = 0 ; 
  int i = 0 ;
  int ind = -1 ; 

  /* Assertions */
  if( ! liste_existe( liste ) ) 
    {
      return(ERR_LISTE_VIDE) ;
    }

  /*
   * Recherche de la position d'insertion
   */

  if( liste_rechercher( &ind , 
			liste , 
			elem ) )
    {
      /* Element deja present dans la liste /*/
      return(ERR_LISTE_ELEM) ; 
    }

  /*
   * Insertion
   */

  /* Mise a jour de la taille du tableau */
  nb = liste_nb_lire(liste) + 1 ;

  liste->nb = nb ; 

  if( nb == 1 ) 
    {
      if( ( liste->liste = malloc( sizeof(void *) ) ) == NULL ) 
	{
	  fprintf( stderr , "liste_inserer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) ) ;
	  return(ERR_DEB_MEMOIRE) ; 
	} 
    }
  else
    {
      if( ( liste->liste = realloc( liste->liste , sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "liste_inserer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) * nb ) ;
	  return(ERR_DEB_MEMOIRE) ; 
	} 
    }
  /* Initialisation de la position ajoutee (en fin) */
  liste->liste[nb-1] = NULL ; 

  /* Decalage des pointeurs vers la fin a partir la position d'insertion*/
  for( i=nb-1 ; i>ind ; i-- ) 
    {
      liste->liste[i] = liste->liste[i-1] ;
    }

  /* Initialisation de la position d'insertion */
  liste->liste[ind] = NULL ; 

  /* Affectation du nouvel element a la position d'insertion */
  if( ( noerr = liste->affecter( &(liste->liste[ind]) , elem ) ) )
    return(noerr) ;
  
  return(OK) ; 
}


/*
 * Suppression d'un element dans la liste 
 */

extern
booleen_t liste_supprimer( liste_t * liste , 
			   void * const elem ) 
{
  int  nb = 0 ; 
  int i = 0 ;
  int ind = -1 ; 

  /* --- Assertions --- */
  if( ! liste_existe( liste ) ) 
    {
      fprintf( stderr , "liste_elem_supprimer: tentative d'extraction dans un listeleau inexistant\n");
      return(FAUX) ;
    }

  if( liste_vide( liste ) )
    return(FAUX) ; 
  
  /* ----------------- */


  /* 
   * Recherche de l'indice de l'element 
   */
  
  if( ! liste_rechercher( &ind ,
			  liste  ,
			  elem  ) )
    return(FAUX) ; 

  /* 
   * Destruction de l'element 
   */

  /* Initialisation de l'element extrait */
  nb = liste_nb_lire(liste) ;

  /* Decalage des pointeurs depuis la position d'extraction jusqu'a la fin */
  for( i=ind ; i<nb-1 ; i++ ) 
    {
      liste->liste[i] = liste->liste[i+1] ;
    }

 /* Mise a jour de la taille de la liste */
  nb-- ; 
  liste->nb = nb ; 
 
  if( nb == 0 ) 
    {
      free(liste->liste) ; 
      liste->liste = NULL ; 
    }
  else
    {
      if( ( liste->liste = realloc( liste->liste , sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "liste_supprimer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) * nb ) ;
	  return(FAUX) ; 
	} 
    }

  return(VRAI) ;
}
