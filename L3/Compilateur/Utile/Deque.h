void DequeAllouer(int nCardinalMax);//O(nCardinalMax);envoyer 0 pour restituer la deque
void DequeAMORCER();
int nDequeCardinal();//O(1)
int bDequeContient(int sSommeT);//O(1)
void DequeDefiler();//O(1) l'élément défilé est perdu
int sDequeDefiler();//O(1) rend l'élément défilé
void DequeDepiler();//O(1) l'élément dépilé est perdu
int sDequeDepiler();//O(1) rend l'élément dépilé
void DequeEmpiler(int sSommeT);//O(1) empile si pas déjà là
int bDequeEmpiler(int sSommeT);//O(1) empile si pas déjà là et dit si l'empilement a réussi
void DequeEnfiler(int sSommeT);//O(1)
int bDequeEnfiler(int sSommeT);//O(1) enfile si pas déjà là et dit si l'enfilement a réussi
void DequeINITIALISER();
void DequePileCopier(int nPile[]);
int sDequeQueue();//O(1)
int nDequeQuota();//O(1) effectif max de la deque
void DequeRazer(int nCardinalMax);//O(nCardinalMax)
int sDequeSommet();//O(1)
int sDequeSuivant(int sCourant);//O(1)
void DequeTESTER(int iTest);
int sDequeTete();//O(1)
int bDequeVide();//O(1)
void DequeVoir(char *sMessage);//O(nCardMaX)
void DequeVoirFile(char *sMessage);//O(taille courante de la deque)
void DequeVoirPile(char *sMessage);//O(taille courante de la deque)
