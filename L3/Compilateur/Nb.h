#define kuNbMax 7 //OK avec 7
#define kuNbLim (1+kuNbMax)
typedef struct{
	int sign;
	int digit[kuNbLim];
}nb;
#define knLigneLiMMM 128
typedef struct{
	int nColonne;
	int nLigne;
	int nSecante;
	nb Mat[knLigneLiMMM][knLigneLiMMM];
}nbMatrice;

char *sNb(nb nbA);
long yNb(nb nbA);
char *sNb0(nb nbA,int nEntier);
void NbAdd(nb nbA,nb nbB,nb *pnbS);
void NbAffecter(int iEntier,nb *pnbA);
void NbAMORCER();
void NbDeterminer(nbMatrice *pmQ,int bVoir,nb *pnbDeterminant);
void NbDupliquer(nb nbA,nb *pnbCopie);
int bNbEgal(nb nbA,nb nbB);
void NbFib(int nFibMax,nb *pnbFib);
void NbINITIALISER();
void NbMatriceAllouer(nbMatrice **pqmA);
void NbMatriceAllouer1(nbMatrice **pqmA,int nLigneEnTout);
void NbMatriceAllouer2(nbMatrice **pqmA,int nLigneEnTout,int nColonneEnTout);
void NbMul(nb nbA,nb nbB,nb *pnbP);
int bNbNul(nb nbA);
void NbSub(nb nbA,nb nbB,nb *pnbS);
void NbTESTER(int iTest);
void NbVoir(char *sMessage,nb nbA);
