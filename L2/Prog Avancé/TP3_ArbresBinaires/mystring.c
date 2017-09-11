#include <mystring.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int string_cpt = 0 ; 

/* 
 * FONCTIONS
 */

/*
 * Acces 
 */

extern
int string_taille_lire( const string_t * string )
{
  return(string->length) ;
}

extern
char * string_string_lire( const string_t * string )
{
  return(string->string) ;
}

/*
 * Test existance 
 */
extern 
booleen_t string_existe( const string_t * string )
{
  if( string == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

/*
 * Destruction 
 */
extern
err_t string_detruire( string_t ** string ) 
{

  /* Liberation attributs */
  free( (*string)->string ) ; 
  /* Liberation memoire de l'objet */
  free( (*string) ) ;
  /* Pour eviter les pointeurs fous */
  (*string) = NULL ; 

  string_cpt-- ; 

  return(OK) ; 
}

extern
err_t string_detruire_cb( void * string ) 
{
  return(string_detruire( string ) )  ;
}

/*
 * Effacement 
 */

err_t string_effacer( string_t ** string ) 
{
  /* 
   * l'Objet n'est pas detruit 
   */

  /* 
   * Sa reference est effacee 
   */
  
  (*string) = NULL ; 

  string_cpt-- ; 

  return(OK) ; 
}

extern 
err_t string_effacer_cb( void * string ) 
{
  return(string_effacer( string ) ) ; 
}

/*
 * Affichages
 */

/* -- Structure complete */

extern
void string_afficher( const string_t * string ) 
{

  printf( "{" ) ; 
  if(  string_existe(string) ) 
    {
      printf( "%s (%d car.)" , string->string , string->length ) ;
    }
  printf( "}" ) ; 
}

extern
void string_afficher_cb( const void * string ) 
{
  return(string_afficher( string ) ) ; 
}

/* -- Juste la chaine de caracteres */

extern
void string_string_afficher( const string_t * string ) 
{

  if(  string_existe(string) ) 
    {
      printf( "%s" , string->string ) ;
    }
}

extern
void string_string_afficher_cb( const void * string ) 
{
  return(string_string_afficher( string ) ) ; 
}

/*
 * Creation 
 */
extern 
string_t * string_creer( const char * chaine ) 
{
  string_t * string = NULL ; 

  /* Creation place memoire objet string */
  if( ( string = malloc(sizeof(string_t)) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(string_t) ) ;
      return((string_t *)NULL);
    }

  /* Affectation attributs specifiques */
  if( ( string->string = malloc(sizeof(char)*strlen(chaine)+1) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n", 
	       (unsigned long int)strlen(chaine)+1 ) ;
      return((string_t *)NULL);
    }
  strcpy( string->string , chaine ) ;
  string->length = strlen( chaine ) ; 

  string_cpt++ ; 

  return( string ) ;
}

/*
 * Comparaison
 */

extern
int string_comparer( const string_t * const str1 , const string_t * const str2 )
{
  return(strcmp( str1->string , str2->string) ) ;
}

/* 
 * Fonction d'encapsulation (ou de callback) 
 * de comparauson de 2 strings
 * destinee a etre utilisee par qsort 
 */
extern 
int string_comparer_cb( const void * str1 , const void * str2 ) 
{
  /* 
   * Le pointeur generique doit representer l'adresse d'un element 
   * ici un element = pointeur sur une string 
   * donc void * --> string_t ** 
   */
  const string_t * const * str1_cb = str1 ; 
  const string_t * const * str2_cb = str2 ; 
  return( string_comparer( *str1_cb , *str2_cb ) ) ;
}

/*
 * Affectation d'une string par reference 
 */

extern
err_t string_referencer( string_t ** str_cible ,  string_t * str_source )
{
  (*str_cible) = str_source ; 
  return(OK) ; 
}


extern
err_t string_referencer_cb( void * str_cible ,  void * str_source )
{
 
  return( string_referencer( str_cible , str_source ) ) ; 
}


/*
 * Affectation d'un string par copie 
 */

extern
err_t string_copier( string_t ** str_cible ,  string_t * str_source )
{
  err_t noerr = OK ; 

  if( string_existe( (*str_cible) ) )
    {
      if( ( noerr = string_detruire( str_cible ) ) )
	return(noerr) ;
    }

  if( ! string_existe( str_source ) )
    return(OK) ; 

  if( ( (*str_cible) = string_creer( str_source->string ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ; 

  return(OK) ; 
}

extern
err_t string_copier_cb( void * str_cible ,  void * str_source )
{
  return( string_copier( str_cible , str_source ) ) ; 
}

/*
 * Chargement d'une string a partir d'un fichier 
 * La string est creee
 */

extern
err_t string_charger( string_t ** string , 
		      FILE * restrict fd )
{
  char w_string[MAX_STRING] ;
  err_t noerr = OK ; 
  int length = 0 ; 

  if( string_existe( (*string) ) )
    {
      if( ( noerr = string_detruire( string ) ) )
	return(noerr) ;
    }
  
   if( fscanf( fd , "%d " , &length ) != 1 ) 
     {
       printf("string_charger: erreur lors de la lecture de la longueur de la string\n" ) ; 
       return(ERR_SCANF) ; 
     }

   /* rem: fegts lit un car de moins que la taille specifiee */
   if( fgets( w_string , length+1 , fd ) == NULL )
     {
       printf("string_charger: erreur lors de la lecture de la string\n" ) ; 
       return(ERR_SCANF) ; 
     }

  if( ( (*string) = string_creer( w_string ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ;  

  return(OK) ; 
}

extern
err_t string_charger_cb( void * string , 
			 FILE * restrict fd )
{
  return(string_charger( string , fd ) ) ; 
} 


/*
 * Sauvegarde d'une string dans un fichier 
 */

extern
err_t string_sauver( string_t * string , 
		     FILE * restrict fd )
{
  if( ! string_existe( string ) )
    return(OK) ;

  /* Ecriture taille string */
  fprintf( fd , "%d " , string->length ) ; 

  /* Ecriture corps de la string */
  if( fputs( string->string , fd ) == EOF )
    {
      printf("string_sauver: erreur lors de l'ecriture de \"%s\" \n" , string->string ) ; 
      return(ERR_SCANF) ; 
    }
  return(OK) ; 
}

extern
err_t string_sauver_cb( void * string , 
			FILE * restrict fd )
{
  return( string_sauver( string , fd ) ) ;
}


/*
 * Saisie d'une strig au clavier (entree standard)
 */

extern 
string_t * string_saisir( const char * message )
{
  char chaine[MAX_STRING] ; 
  printf("%s : " , message ) ; fflush(stdout); 
  
  fgets( chaine , MAX_STRING , stdin ) ;

  char * rc = strchr(chaine, '\n' );
  (*rc) = '\0' ;

  return( string_creer( chaine ) ) ;
}
