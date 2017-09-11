#ifndef _AB_H_
#define _AB_H_
/*
 * Definition Arbre Binaire
 */

#include <noeud.h>

/*
 * Constantes
 */

typedef enum ab_parcours_s {PREFIXE , INFIXE, POSTFIXE } ab_parcours_t ;

/* 
 * Type Arbre Binaire 
 */

typedef struct ab_s
{
  #include <ab_attributs.h>
} ab_t ;

#endif
