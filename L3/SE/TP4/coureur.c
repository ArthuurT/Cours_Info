#include "messages.h"
#include <unistd.h>
#include <time.h>
#include <sys/msg.h>
#include <signal.h>

#define CLE_BAL 11

void hand(int sig){

  int cle_file;
  requete_t requete;
  ack_t reponse;
  size_t lg = sizeof(err_t);

  requete.type = PC_COURSE;
  requete.corps.dossard = getpid();
  requete.corps.etat = ABANDON;

  cle_file = msgget(CLE_BAL,0666);

  msgsnd(CLE_BAL,&requete,sizeof(corps_requete_t),0);
  msgrcv(CLE_BAL,&reponse,lg,getpid(),0);
  
  exit(0);

}


int main(int argc, char * agrv[]){

  int cle_file;
  requete_t requete;
  reponse_t reponse;
  size_t lg = sizeof(corps_reponse_t);
  struct sigaction s_err;

  s_err.sa_handler = hand;
  sigemptyset(&s_err.sa_mask);
  sigaction(SIGINT,&s_err,NULL);

  requete.type = PC_COURSE;
  requete.corps.dossard = getpid();
  requete.corps.etat = EN_COURSE;

  cle_file = msgget(CLE_BAL,0666);

  while(reponse.corps.etat != EN_COURSE && reponse.corps.etat != DECANILLE){

    messages_afficher_requete(&requete);
    msgsnd(CLE_BAL,&requete,sizeof(corps_requete_t),0);

    msgrcv(CLE_BAL,&reponse,lg,getpid(),0);
    messages_afficher_reponse(&reponse);

    messages_afficher_etat(reponse.corps.etat);
    messages_afficher_parcours(&reponse);

    messages_attendre_tour();
  }

  messages_afficher_etat(reponse.corps.etat);

}
