# define NoeudNombre 0
# define NoeudAddition 1
# define NoeudProduit 2
# define NoeudSoustraction 3
# define NoeudDivision 4
void NoeudAffiche(char* sQuoi,int noNoeud);
char *sNoeudAffiche(char* sQuoi,int noNoeud);
int nNoeudCouplage(int noRacine,int bDroite);
void NoeudFormuler(char* sTitre,int noRacine);
int noNoeudAjouter(int noGauche,int noType,int noDroit);
void NoeudArborer(char* sTitre,int noRacine);
void NoeudAMORCER();
int nNoeudChemin(int noRacine);
void NoeudConfliter(int noRacine,int nOccurrence[20]);
void NoeudCouvrir(int uDag,int noRacine,int nPivot,int *pnPlus,int *pnMoins,long *pzComplexiteh);
int noNoeudDaguer(int noRacine);
void NoeudEnumerer(int uDagNumero,int nProfondeur,int noRacine,int bElementaire,int iPoidsMin,int iPoidsMax,int *pnCheminValide,int *pnCheminInvalide);
int iNoeudEvaluer(int noRacine,int bUn);
int noNoeudFeuiller(int iFeuilleValeur);
void NoeudINITIALISER();
void NoeudInvalideAfficher();
void NoeudInvalideArc(int iArc1,int iArc2,int *pnSegmentEnTout);
void NoeudInvalider(int sX,int sY,int sZ,int sT,int iPoidsXY,int iPoidsYZ,int iPoidsZT,int *pnSegmentEnTout);
void NoeudLister(char* sTitre,int noRacine);
int bNoeudNul(int noRacine);
int nNoeudOptimum(int uDagNumero,int noRacine,int nProfondeur,int iSente[]);
void NoeudPaterniter(int noRacine);//attribue une paternité à chaque noeud. Pere(racine)=nil.
int nNoeudPris();
void NoeudRecuperer(int noRacine[]);
void NoeudRestituer(int iNoeud,int bDontDescendance);
int nNoeudRoute(int noRacine);
int bNoeudSimple(int noRacine);
void NoeudSimplifier(int nComposante,int noRacine,int iElementNeutre,int bDontDoublon);
int nNoeudSomme(int noRacine);
void NoeudTESTER(int iTest);
void NoeudVoir(char *sMessage,int noRacine);
void NoeudVoirTout(char *sMessage);
