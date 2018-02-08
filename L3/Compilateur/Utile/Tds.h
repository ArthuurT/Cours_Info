int bTdsAllouer(int bAllouer,char* pcTds);
int bTdsAjouter(char cTdsNom,char *sIdentificateur);
int nTdsAjouter(char cTds,char *sIdentificateur);
int bTdsAjouterValuer(char cTdsNom,char *sIdentificateur,int iValeur);
void TdsAMORCER();
int bTdsContient(char cTdsNom,char *sIdentificateur,int *pnItem);
int nTdsCout();//coût en nombre d'appels depuis le dernier TdsINITIALISER
float fTdsDensiteh();
void TdsINITIALISER();//raze les TDS
int nTdsItem();//rend le nombres d'items mémorisés en TDS
int bTdsPresent(char cTdsNom,char *sIdentificateur,int *piValeur);
void TdsTESTER(int iTest);
void TdsValuer(char cTdsNom,int nItem,int iValeur);
void TdsVoir(char cTdsNom,char *sTitre);
