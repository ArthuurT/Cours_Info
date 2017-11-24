#ifndef _MSG_MESSAGES_H_
#define _MSG_MESSAGES_H_

#include <messages.h>
#include <sys/time.h>

#define MSG_TYPE_RECEPTEUR 22
#define CLE_BAL 11

/* Structure message */

typedef struct corps
{
  int pid;
  char buffer[MESSAGES_TAILLE+1];
} corps_t ;

typedef struct message
{
  long     type ;
  corps_t corps ;
} message_t ;

typedef struct corps_reponse
{
  struct timeval date_reception;
} corps_reponse_t ;

typedef struct reponse
{
  long     type ;
  corps_reponse_t corps ;
} reponse_t ;


/*
 * Definition des fonctions
 */

/* Affichage d'un message */
extern
void msg_afficher( message_t * const message );

/* Remplissage d'un message */
extern
void msg_remplir( message_t * message , const char val ) ;

#endif
