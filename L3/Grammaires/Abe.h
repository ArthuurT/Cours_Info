//ABE=Arbre Binaire Etagé "essentiellement complet". Ses éléments sont des paires d'entiers (sSommet,iPoidS).
//Pour extraire des sommets de poids minimal (maximal), ouvrir d'abord l'ABE via AbeAllouer(nSommetEnTout,iPoidsInfini) avec iPoidsInfini>0 (<0).
void AbeAllouer(int bAllouer,int ukPoidsInfini);//O(S) iPoidsInfini>0 pour extraire le minimum, <0 pour extraire le maximum.
void AbeAMORCER();
int bAbeContient(int sSommet);//O(1); vrai ssi sSommet n'a pas encore été extrait
int nAbeCout();//O(1)
int eAbeExtraire();//O(1)
void AbeINITIALISER();
void AbeModifier(int sSommet,int iPoidsCourant);//O(1)
void AbePropager();//O(S)
void AbeTESTER(int iTest);
void AbeVoir(char *sQuoi);
