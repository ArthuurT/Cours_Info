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
		       err_t (*fonction_destruction)(void * e) )
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
err_t liste_trier( liste_t * liste , int (*comparer)( const void * , const void *) ,...)
{
  type_tri_t type_tri ; 
  va_list ap ;

  va_start( ap , comparer ) ; 
  type_tri = va_arg( ap , type_tri_t ) ;
  switch( type_tri )
    {
    case QUICK : 
      qsort( liste->liste , (size_t)liste->nb , sizeof(void *) , comparer ) ;
      break ;
    case MERGE : 
      mergesort( liste->liste , (size_t)liste->nb , sizeof(void *) , comparer ) ;
      break ; 
    case HEAP : 
      heapsort( liste->liste , (size_t)liste->nb , sizeof(void *) , comparer ) ; 
      break ; 
    default :
      /* 
       * Pas de parametre en surnombre ou type incorrect
       * par defaut on fait le qsort
       */
      qsort( liste->liste , (size_t)liste->nb , sizeof(void *) , comparer ) ;
      break ;
    }


  va_end(ap) ; 
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
			err_t (*fonction_chargement)(void * e, FILE *  desc ) )	/* Fonction de chargement d'un element */
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
  if( ((*liste) = liste_creer(nb , fonction_affectation , fonction_destruction ) ) == NULL )
    {
      fprintf( stderr , "liste_fd_charger: debordement memoire lors de la creation de la liste (%d elements demades)\n" , 
	       nb );
      return(ERR_DEB_MEMOIRE) ; 
    }

  /* Chargement des elements */
  for( i=0 ; i<nb ; i++ )
    {
      if( (noerr = (*fonction_chargement)( &((*liste)->liste[i]) , 
					   fd ) ) ) 
	return(noerr);
    }

  return(OK) ;
}

extern 
err_t liste_charger( liste_t ** liste  ,						/* listeleau d'elements a charger */
		     char *  nom_fichier ,					/* Nom du fichier de chargement */
		     err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/* fonction d'affecation d'un element */ 
		     err_t (*fonction_destruction)(void * e) ,			/* fonction de destructiuon d'un element */
		     err_t (*fonction_chargement)(void *  e, FILE *  desc ) )	/* Fonction de chargement d'un element */
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
			      fonction_chargement ) ) )
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

  /* Ecriture du nombre de liste */
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
