#ifndef _LISTE_SDD_H_
#define _LISTE_SDD_H_

#include <commun.h>
#include <objet.h>


#define LISTE_NULL NULL
#define LISTE_ID_NULL -1

typedef struct liste_s liste_t;

typedef struct liste_s
{
  void (*aff)(liste_t * const liste , const char separateur);                     /* Ptrs de fonction utile à liste */
  err_t (*det)(liste_t ** liste);
  int nb ;		/* Nombre d'objets dans la liste  */
  objet_t ** liste ;	/* liste  des objets */
} liste_t ;

#endif
