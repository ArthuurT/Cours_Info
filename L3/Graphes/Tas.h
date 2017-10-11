void TasActualiser(int uElement,int nPoids);//O(lg(nEffectifMax))
void TasAllouer(int nEffectifMax);//O(nEffectifMax)
void TasAMORCER();
int bTasContient(int uElement);//O(1)
int nTasCout();//coût en nombre d'appels depuis la dernière allocation
int eTasExtraire();//O(1)
void TasINITIALISER();
void TasInsererValuer(int uElement,int nPoids);//O(lg(nEffectifMax))
void TasRazer();//O(nEffectifMax)
int eTasSommet();//O(1)
void TasTESTER(int iTest);
int bTasVide();//O(1)
void TasVoir(char *sMessage);//O(nEffectifMax)
