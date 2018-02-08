# define DagNombre 0
# define DagAddition 1
# define DagProduit 2
# define DagSoustraction 3
# define DagDivision 4
void DagAffiche(char* sQuoi,int noDag);
char *sDagAffiche(char* sQuoi,int noDag);
int noDagAjouter(int noGauche,int noType,int noDroit);
void DagArborer(char* sTitre,int noRacine,int nPeriode);
void DagAMORCER();
int nDagChemin(int noRacine);
void DagConfliter(int noRacine,int nOccurrence[20]);
int nDagCouplage(int noRacine,int bDroite);
void DagCouvrir(int uDag,int noRacine,int nPivot,int *pnPlus,int *pnMoins,long *pzComplexiteh);
int noDagDaguer(int noRacine);
long zDagEnumerer(int uDagNumero,int bAfficher,int nProfondeur,int noRacine,int bElementaire,int iPoidsMin,int iPoidsMax,int *pnCheminValide,int *pnCheminInvalide);
long yDagEvaluer(int noRacine,int bUn);//si bUn, considère que les feuilles non nulles valent 1
int noDagFeuiller(int iFeuilleValeur);
void DagFormuler(char* sTitre,int noRacine);
void DagINITIALISER();
void DagInvalideAfficher();
void DagInvalideArc(int iArc1,int iArc2,int *pnSegmentEnTout);
void DagInvalider(int sX,int sY,int sZ,int sT,int iPoidsXY,int iPoidsYZ,int iPoidsZT,int *pnSegmentEnTout);
void DagLister(char* sTitre,int noRacine);
int bDagNul(int noRacine);
int nDagOptimum(int uDagNumero,int noRacine,int nProfondeur,int iSente[]);
void DagPaterniter(int noRacine);//attribue une paternité à chaque noeud. Pere(racine)=nil.
int nDagPris();
void DagRecuperer(int noRacine[]);
void DagRestituer(int iDag,int bDontDescendance);
int nDagRoute(int noRacine);
int bDagSimple(int noRacine);
void DagSimplifier(int nComposante,int noRacine,int iElementNeutre,int bDontDoublon);
int nDagSomme(int noRacine);
void DagTESTER(int iTest);
void DagVoir(char *sMessage,int noRacine);
void DagVoirTout(char *sMessage);
