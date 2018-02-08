#include "Nb.h"
typedef struct{nb q11;nb q12;nb q21;nb q22;}quad;
#define knLigneLiMM 128
typedef struct{
	int nColonne;
	int nLigne;
	int nSecante;
	quad Mat[knLigneLiMM][knLigneLiMM];
}qMatrice;

quad qQuad(long iEntier);//convertit iEntier en quad selon le mode standard
char *sQuad(quad qQuoi);
char *sQuad0(quad qQuoi);//idem sQuad mais sur 8 caractères exactt par élément du quad
void Quad2Int(quad qA,int *pi11,int *pi12,int *pi21,int *pi22);
void Quad2Long(quad qA,long *py11,long *py12,long *py21,long *py22);
quad qQuad4(long y11,long y12,long y21,long y22);
quad qQuadAdd(quad qA,quad qB);
void QuadAMORCER();
long yQuadDeterminant(quad qA);
int bQuadDeterminer(qMatrice *pmA);
void QuadDupliquer(quad qA,quad *pqCopie);
int bQuadEgal(quad qA,quad qB);
int bQuadIdentiteh(quad qA);
void QuadINITIALISER();
int bQuadInversible(quad qA);
void QuadMatriceAllouer(qMatrice **ppmqA);
void QuadMatriceAllouer1(qMatrice **ppmqA,int nDimension);
void QuadMatriceAllouer2(qMatrice **ppmqA,int nLigneEnTout,int nColonneEnTout);
int bQuadMatriceVide(qMatrice *pmqA);
void QuadMatriceVoir(char *sMessage,qMatrice *pmqA);//matrice de quad
void QuadMatriceZeroter(qMatrice *pmqA,int uHauteur,qMatrice *pmqAh);
int bQuadModeste(quad qQuoi);//qQuoi a des éléments pas trop grand en valeur absolue
quad qQuadMul(quad qA,quad qB);
quad qQuadMul3(quad qA,quad qB,quad qC);
quad qQuadNeg(quad qA);
int bQuadNul(quad qA);
quad qQuadSub(quad qA,quad qB);
void QuadTESTER(int iTest);
void QuadVoir(char *sMessage,quad qVoir);
