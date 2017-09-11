#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Definition du type booleen */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;

/* Definition du type erreur */
typedef int err_t ; 

/* Constantes */

#define TAILLE 32
#define MAX_STRING 256 

/* Erreurs */
#define OK 0

#define ERR_DEB_MEMOIRE -100 
#define ERR_SCANF -101 
#define ERR_NOM_FICHIER -102
#define ERR_ELEM_UNK -103

#define ERR_LISTE_IND_ELEM  -200 
#define ERR_LISTE_VIDE  -201
#define ERR_LISTE_ELEM  -202

#define ERR_ARBRE_NOEUD  -300 




/*
 ************
 * Fonctions 
 ************
 */

/* 
 * Affichage messages d'erreur
 */
extern void err_print( const err_t noerr ) ;

/* 
 * Saisie reponse de type Oui/Non 
 * retour VRAI si reponse positive
 *        FAUX sinon 
 * Reponses possibles dans l'intervalle [OoNnYy] 
 */

extern booleen_t OuiNon_saisir() ;

#endif

