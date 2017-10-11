void FlotAfficher(graf *pgG,int bTout,char *sMessage);//si non bTout,censure les arcs dont le flot est nul
void FlotAMORCER();
void FlotCapaciter(graf *pgG,int sOrigine,int sDestination,int nCapacitehMaximale);//attribue une capacité
int bFlotCompatible(graf *pgG,int sSource,int sTrappe,int bAfficher);
void FlotCouter1(graf *pgG,int sOrigine,int sDestination,int nCout);//attribue un coût (champ nCout)
void FlotCouter2(graf *pgG,int sOrigine,int sDestination,int nCout);//attribue un coût (champ nPrix)
void FlotINITIALISER();
int nFlotMaxCalculer(graf *pgG,int sSource,int sTrappe,int nFlotRequis,int bAfficher);
void FlotOptimiser(graf *pgG,int nSommetInitial,int sSource,int sTrappe,int bAfficher);
void FlotTESTER(int iTest);
