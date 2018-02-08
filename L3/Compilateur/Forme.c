#include "Outil.h"
#include "Forme.h"
#include "Graphe.h"
#include "Deque.h"
#include "Matrice.h"
#include "Flot.h"
#include "Dag.h"
#include "Quad.h"
#define k1AlterneR kV
#define kuLettreLiM 64
#define kuSommandeLiM 512
#define kuSommandeMaX (kuSommandeLiM-1)
#define kuTermeLiM kuLettreLiM
#define kuTermeMaX (kuTermeLiM-1)
#define kuLigneLiM 56 //168 sommets pour nCoteh=4
#define kuLigneMaX (kuLigneLiM-1)
#define kuColonneMaX (kuLigneLiM-1)
#define kuFormeLiM kE4
#define kuFormeMaX (kuFormeLiM-1)
long zChemineR;
int nCheminDeclineR;
int bCommutatiF;
int nCouvertureEstimeR;//dédié iCouvertureEstimeR()
const int k1DenominateuR=kV;
int bFormeAmorceR;
graf *pgGrapH;
enum eCouleurTypE CouleurType;
char *sCouleurNoM=CouleurNom;
enum eFormE{f0,fCarreH,fCouplE,fDemiX,fDemyX,fDuO,fLobiX,fSimplE,fComplexE,fIndividueL,fMuteX,fThetA,fThetB,fScissioN,f1};
char *sFORME= "fCarreH,fCouplE,fDemiX,fDemyX,fDuO,fLobiX,fSimplE,fComplexE,fIndividueL,fMuteX,fThetA,fThetB,fScissioN,fOmegA";
const int kuLosangeLargeurVautTroiS=3;
int nCouvertureBanniR;//dédié CouvertureBanniR()
char *sgrNoM=GrapheNom;
enum grTypE GrapheType;
// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grOmega}
typedef struct {int num[kuSommandeLiM][kuTermeLiM];int den[kuSommandeLiM][kuTermeLiM];} f;//rapport de produits kuSommandeLiM][kuTermeLiM] 
typedef struct{
	int nColonne;
	int nLigne;
	f fForme[kuLigneLiM][kuLigneLiM];
}fMathricE;
typedef struct{
	int nColonne;
	int nLigne;
	int iForme[kuLigneLiM][kuLigneLiM];
}iMathricE;
enum eMathricE {maAlphA,maAntisymetriquE,maBipartiAntisyM,maGeneralE,maGeneralE0,maSymetriquE,maTriangleInferieuR,maTriangleSuperieuR,maOmegA};
int nSignatureKalculeR;
long zAppelExponentieL;
char cCaracterE(int uRang);
char cCaractereSuivanT(char cCar);
void CouvertureBanniR(iMatrice *pmA);
int iCouvertureDecompterBieN(iMatrice *pmA,char *sContexte,int muNeutre,int nPivot,int bAfficher,long *pzComplexiteh);//O(S4)
int iCouvertureDecompterBiS(iMatrice *pmA,char *sContexte,int muNeutre,int nPivot,int bAfficher,long *pzComplexiteh);//O(S4)
long yCouvertureDecompterTeR(iMatrice *pmA,int nSommetDeBase,int iNeutre,int bOptimum,int nPeriode,int bAfficher,int *pnCouverture,long* pyDeterminant,long *pzComplexiteh);//O(S5)
long zCouvertureEnTouT(int nSommet,int bElementaire);
int iCouvertureEstimeR(int nCas,int bAfficher,int nCaractereParLibelleh,int nCaractereParResultat);
void CouvertureLongrinerUnQuadripolE(int sA,int sB,int sC,int sD,graf *pgG);
void CouvertureTESTER();
void DeterminantCalculeR(int nSommet,enum eMathricE maMode);
void DeterminantConfronteR(iMatrice *pmE);
void DeterminantExpliciter();
void DeterminantKalculeR(fMathricE *pmA,int bVoir);
int iFormeCalculeR(iMatrice *pmA);//O(S4) noV est integer
ri riFormeCalculeR(riMatrice *pmA);//O(S4) noV est complexe
long yFormeCalculeR(iMatrice *pmA);//O(S4) noV est longint
long yFormeKalculeR(iMatrice *pmA,int nDim,int bVoir);//O(S3.5) exact car sans division
void DeterminantQalculeR(fMathricE *pmA,int bVoir);//O(exponentiel)
char *sFormE(f fForme,int bDenominateurSinonNumerateur);
void FormeAjouteR(f fA,f fB,f *pfC);
void FormeArrangeR(int nDim,iMatrice **ppmE);
void FormeLosangeR(int *pnLigne,int *pnColonne,fMathricE **ppmA);
void FormeCaseR(int nMotif,int uLigne,int uColonne,fMathricE **ppmA);
void FormeCopieR(f fAccu,f *pfAccu);
void FormeCreeR(char *sProduit,f *pfCible);
void FormeDedoublonneR(f *pfF);
void FormeDiviseR(f fA,f fB,f *pfC);
void FormeFoisseR(int iFois,f *pfC);
void FormeInverseR(f *pfA);
void FormeLongrineR(graf *pgG,int coUn,int coBeaucoup,graf **ppgH);
void FormeLongrineR2(int uPivot,graf *pgG,int bBipartitionner,int bPoleBannir,graf **ppgH);
void FormeMatriceR(iMatrice *pmSource,nbMatrice *pmnbCible);
void FormeMultiplieR(f fA,f fB,f *pfC);
void FormeMutualiseR(f fA,f fB,f *pfA,f *pfB);
int bFormeNullE(f fForme);
void FormePoseR(int nCar,int nDiagonale,fMathricE *pmA);
int iFormeQalculeR(iMatrice *pmA);
void FormeRazeR(f *pfCible);
void FormeSimplifieR(f *pfF);
int bFormeTrianguleR(fMathricE *pmA,int bCommutatif);
void FormeTrieR(f *pfForme);
void FormeVoiR(char *sQuoi,f fForme);
void GrafMatriceR(graf *pgG,iMatrice **ppmE);
long yKnapsacK(iMatrice *pmA,int bColonnesImpairesVides,int bVoir);
int iKnapsacQ(qMatrice *pmqA,int bColonnesImpairesVides);
int nLettraT(f fForme,int uTerme,int bNumerateurSinonDenominateur);
void LettreR(int uLigne,int uColonne,char cCaractere,fMathricE *pmA);
void LimiteCalculeR();
void MathriceAffecteR(fMathricE **ppmA);
void MathriceAlloueR(int nLigneMax,int nColonneMax,fMathricE **ppmA);
void MathriceDedoublonneR(fMathricE *pmA);
void MathriceEvalueR(int nCoteh);
void MathriceRempliR(fMathricE *pmA,enum eMathricE maMode);
void MathriceVoiR(char *sMessage,fMathricE *pmA);
void MattriceVoiR(char *sMessage,iMathricE *piA);
void MotifSuivanT(int *pnMotif);
void NullissimeR();
void PermanentCalculeR(int nSommet,enum eMathricE maMode);
void PermanentKalculeR(fMathricE *pmA,int bVoir);//O(exponentiel)
void PoleBanniR(int uPivotEnTout,int nSommat,int nOffset,int szEntree[],int szSortie[]);
int noPolyAdD(int bPoly,int noA,int noB);
int noPolyAfF(int bPoly,int noElement);
int noPolyDiV(int bPoly,int noA,int noB);
int noPolyMuL(int bPoly,int noA,int noB);
int noPolySuB(int bPoly,int noA,int noB);
int nProduitEnTouT(iMatrice *pmA);
void QuadripoleLongrineR(int nQuadripole,int nQuad,int bSymetriser,graf *pgG);
void QuadTesteR(int iTest);
char *sRapporT(f Forme);
void SignatureCalculeR(int nSommet);//O(exponentiel)
void SignatureKalculeR(fMathricE *pmA,int bAlterner,f *pfAccu);//O(exponentiel)
int bSignaturePairE(fMathricE *pmA,char *sCouplage);
quad qSignatureQalculeR(qMatrice *pmqA,int bAlterner);
void SkewClosurE1(iMatrice *pmA,iMatrice **ppmK);
void SkewClosurE0(iMatrice *pmA,int uParcoursLgMax,iMatrice **ppmAchapo);//O(N4)
void SkewQlosurE(qMatrice *pmqA,int uParcoursLgMax,qMatrice **ppmqAchapo);//O(N4)
void SkewClosurE2(iMatrice *pmA,int uParcoursLgMax,iMatrice **ppmAchapo);//O(N4)
void SegmentBanniR(graf *pgG);
void SystemeComposeR(iMatrice *pmA,iMatrice *pmAB);
void SystemeExpanseR(iMatrice *pmQuadFoisQuad,iMatrice *pmCoefficient);
void TermeVoiR(char *sQuoi,f fVoir,int uTerme);

void DeterminantQuatreExhibeR(){
	float A=2,B=2,C=4,D=6,E=5,F=12,G=8,H=8,I=16,J=5,K=7,L=8,M=9,N=4,O=6,P=2,X,Y,DE,DI,DM;
	float D0,D14,D13,D24,D23;
	Appel0("DeterminantQuatreExhibeR");
		X=3;Y=-5;
		F=X*J+Y*N;
		G=X*K+Y*O;
		H=X*L+Y*P;
		D13=F*(K*P-O*L)-J*(G*P-O*H)+N*(G*L-K*H);
		f(D13);
		X=13;Y=-7;
		A=X*C+Y*D;
		I=X*K+Y*L;
		M=X*O+Y*P;
		D24=A*(K*P-O*L)-I*(C*P-O*D)+M*(C*L-K*D);
		f(D24);
		DE=B*(K*P-O*L)-J*(C*P-O*D)+N*(C*L-K*D);
		DI=B*(G*P-O*H)-F*(C*P-O*D)+N*(C*H-G*D);
		DM=B*(G*L-K*H)-F*(C*L-K*D)+J*(C*H-G*D);
		E=( A*D13 +I*DI -M*DM )/DE;
		D0= A*D13 -E*DE +I*DI -M*DM;
		D14= E*(K*P-O*L) -I*(G*P-O*H) +M*(G*L-K*H);
		D23=DE;
		f3(D13,D24,D0);
		printf(" %8.2f%8.2f%8.2f%8.2f\n %8.2f%8.2f%8.2f%8.2f\n %8.2f%8.2f%8.2f%8.2f\n %8.2f%8.2f%8.2f%8.2f\n",  A,B,C,D,   E,F,G,H,  I,J,K,L,     M,N,O,P  );
		f2(D14,D23);
	Appel1("DeterminantQuatreExhibeR");
}//DeterminantQuatreExhibeR

void DeterminantSelecteurCalculeR(int nBrancheEnTout){
	//calculer le déterminant de deux sélecteurs (nBrancheEnTout-1)XnBrancheEnTout reliés circulairt 
	int iDeterminant;
	int nSommetParSelecteur=2*nBrancheEnTout-1;
	int nSommet=2*nSommetParSelecteur;
	int nOffset,sX,sY;
	graf *pgG;
	iMatrice *pmA;
	d3(nBrancheEnTout,nSommetParSelecteur,nSommet);
	GrapheCreer(-nSommet,&pgG);
	//fabriquer K(n-1,n) amont avec n=nBrancheEnTout via nBrancheEnTout*(nBrancheEnTout-1) arêtes
		for (nOffset=0,sX=1;sX<nBrancheEnTout;sX++)
			for (sY=nBrancheEnTout;sY<=nSommetParSelecteur;sY++){
				GrapheArquer(pgG,nOffset+sX,nOffset+sY);//d2(sX,sY);
			}
		//GrapheVoir(pgG,"DeterminantSelecteurCalculeR");
	//fabriquer K(n-1,n) aval avec n=nBrancheEnTout via nBrancheEnTout*(nBrancheEnTout-1) arêtes
		for (nOffset=nSommetParSelecteur,sX=1;sX<nBrancheEnTout;sX++)
			for (sY=nBrancheEnTout;sY<=nSommetParSelecteur;sY++){
				GrapheArquer(pgG,nOffset+sX,nOffset+sY);//d2(nOffset+sX,nOffset+sY);
			}
		//GrapheVoir(pgG,"DeterminantSelecteurCalculeR");
	//relier K(n-1,n) amont à K(n-1,n) aval via nSommetParSelecteur arêtes
		for (sX=1;sX<nBrancheEnTout;sX++){
			GrapheArquer(pgG,sX,nOffset+sX);//d2(sX,nOffset+sX);
		}
		for (sX=1;sX<=nBrancheEnTout;sX++){
			GrapheArquer(pgG,nBrancheEnTout-1+sX,nOffset+nBrancheEnTout-1+sX);//d2(nBrancheEnTout-1+sX,nOffset+nBrancheEnTout-1+sX);
		}
	GrapheVoir(pgG,"DeterminantSelecteurCalculeR");
	Assert1("DeterminantSelecteurCalculeR1",pgG->nArcEnTout==2*nBrancheEnTout*(nBrancheEnTout-1)+nSommetParSelecteur);
	//pmA:=matrice symétrique du graphe
		MatriceAllouer1(&pmA,pgG->nSommetEnTout);
			MatriceDepuisGraphe(pgG,kV,&pmA);
			MatriceSymetriser(&pmA);
			MatriceVoir("pmA",pmA);
	//iDeterminant:=déterminant de pmA par Mahajan
		iDeterminant=iFormeCalculeR(pmA);
	free(pmA);
	d(iDeterminant);//n=2:-1,3:-25,-121,-361,-841,-1 681, cf 1**2,5**2,11**2,19**2,29**2,41**2: -(n**2-n-1)**2.
	Assert1("DeterminantSelecteurCalculeR1",iDeterminant==-nCarreh(nCarreh(nBrancheEnTout)-nBrancheEnTout-1));
}//DeterminantSelecteurCalculeR

void AreteR(int sSource,int sCible,int iPoidsDirect,int iPoidsInverse,iMatrice *pmE){
	pmE->Mat[sSource][sCible]=iPoidsDirect;
	pmE->Mat[sCible][sSource]=iPoidsInverse;
}//AreteR

void AreteR2(int sSource2,int sCible2,int iPoidsDirect,int iPoidsInverse,iMatrice *pmE){
	//génère l'arête ( (1+sSource2)/2,(1+sCible2)/2 )
	int sSource=(1+sSource2)/2;
	int sCible=(1+sCible2)/2;
	pmE->Mat[sSource][sCible]=iPoidsDirect;
	pmE->Mat[sCible][sSource]=iPoidsInverse;
}//AreteR2

void ArqueR(int sSource,int sCible,int iPoidsDirect,iMatrice *pmE){
	pmE->Mat[sSource][sCible]=iPoidsDirect;
}//ArqueR

void ArqueR2(int sSource2,int sCible2,int iPoidsDirect,iMatrice *pmE){
	int sSource=(1+sSource2)/2;
	int sCible=(1+sCible2)/2;
	pmE->Mat[sSource][sCible]=iPoidsDirect;
}//ArqueR2

void BanniR(int sX,int sY,int sZ,int sT){
	//d4(sX,sY,sZ,sT);
	EntierEmpiler4(sX,sY,sZ,sT);
}//BanniR

char cCaracterE(int uRang){
	char cCaractere;
	//if (uRang>26) te("uRang",uRang);
	cCaractere=(uRang<=26)?'A'+uRang-1:'A'+uRang-1;
	//if (uRang>26) tc("cCaractere",cCaractere);
	Assert1("cCaracterE",isprint(cCaractere)); 
	return(cCaractere); 
}//cCaracterE

char cCaractereSuivanT(char cCar){
	char cCaractere;
	//tc("cCar",cCar);
	cCaractere=(cCar=='Z')? 'a': cCar+1;
	//tc("cCaractere",cCaractere);
	Assert1("cCaractereSuivanT",isprint(cCaractere)); 
	return(cCaractere); 
}//cCaractereSuivanT

void CheminDeclineR(int sPile[]){
	int uS;
	nCheminDeclineR++;
	//Titrer(sC2("chemin n°",sEnt(nCheminDeclineR)));
	//VecteurVoir0(sC2("sPile n°",sEnt(nCheminDeclineR)),sPile);
	printf("CHEMIN n°%s: ",sEnt(nCheminDeclineR));
	for (uS=1;uS<=sPile[0];uS++)
		printf(" %2d",sPile[uS]);
	printf(" (%s).\n",sPluriel(sPile[0],"élément"));
}//CheminDeclineR

int iCheminSignE(int sPile[],int nColonne[]){
	//convertit (sPile,nColonne) en iMatrice imA à valeur dans {0,1} et rend le déterminant de imA, lequel est non nul et égal à son signe;
	//appel:ChemineR()
	iMatrice imA;
	int iDeterminant,iSigne;
	int uC,uL;
	imA.nLigne=imA.nColonne=imA.nSecante=sPile[0];
	//imA soit razé
		for (uL=1;uL<imA.nLigne;uL++)
			for (uC=1;uC<=imA.nColonne;uC++)
				imA.Mat[uL][uC]=0;
	//copier (sPile,nColonne) ds imA sachant que le sommet sPile[uL] est ligne uL et colonne nColonne[sPile[uL]]).
		for (uL=1;uL<=sPile[0];uL++)
			imA.Mat[uL][nColonne[sPile[uL]]]=1;
	//MatriceVoir(sC2("matrice n°",sEnt(nCheminDeclineR)),&imA);
	iDeterminant=yMatriceDeterminant(&imA);//O(S3)
	//printf("Déterminant de la matrice imA:%d.\n",iDeterminant);
	Assert1("iCheminSignE",abs(iDeterminant)==1);
	iSigne=iDeterminant;
	printf("Signe du déterminant: %s.\n",sSigne(iSigne));
	return(iSigne);
}//iCheminSignE

void ChemineR(graf *pgG,int nNiveauEnTout,int sX,int sTrappe,int sPile[],int nColonne[]){
	//liste TOUS les plus longs chemins (profondeur d'abord) qui vont de sSource à sTrappe par des colonnes distinctes.
	int aK,sY,iSigne;
	zChemineR++;
	if (sX==sTrappe && sPile[0]==nNiveauEnTout){
		CheminDeclineR(sPile);
		iSigne=iCheminSignE(sPile,nColonne);
		Assert1("ChemineR1",iSigne>0);//pr informer;indolore en fait
	}
	for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
		sY=pgG->sSuk[aK];
		if (!bDequeContient(nColonne[sY])){
			//teee("sY,nColonne[sY],nDequeCardinal",sY,nColonne[sY],nDequeCardinal());
			pgG->sPer[sY]=sX;
			DequeEmpiler(nColonne[sY]);
			sPile[++sPile[0]]=sY;
			ChemineR(pgG,nNiveauEnTout,sY,sTrappe,sPile,nColonne);
			nBof=sDequeDepiler();
			sPile[0]--;
		}
	}
}//ChemineR

void CliqueGenereR(int nSommet,int bBoucler,int ukHuit,int nTest,graf *pgG){
	//génère une clique à nSommet sommets 
	int nArc,bArquer,uC,uL,nOffset,nSommat,uEntresol;
	int uQuad0,uQuad1,sX,sY,nCouleur;
	nOffset=pgG->nSommetEnTout;
	for (uL=1;uL<=nSommet;uL++)
		for (uC=1;uC<=nSommet;uC++){
			nSommat=pgG->nSommetEnTout;
			GrapheSommer(pgG,+ukHuit);
			//relier les kuHuit sommets en Grand X
//enum eCouleuR {coAlphA,coJaunE,coRougE,coBleU,coVerT,coOrangE,coNoiR,coOmegA};
				if (uL==1 && uC==1 || !bBoucler)
					GrapheArquer1(pgG,nSommat+1,nSommat+2,(bBoucler)? coRouge: coJaune);
				else GrapheAreter2(pgG,nSommat+1,nSommat+2,coRouge,coBleu);
				if (bBoucler) GrapheAreter2(pgG,nSommat+3,nSommat+4,coBleu,coRouge);
				else GrapheArquer1(pgG,nSommat+3,nSommat+4,coBleu);
				if (bBoucler) GrapheAreter2(pgG,nSommat+5,nSommat+6,coRouge,coBleu);
				else GrapheArquer1(pgG,nSommat+5,nSommat+6,coRouge);
				if (bBoucler) GrapheAreter2(pgG,nSommat+7,nSommat+8,coBleu,coRouge);
				else GrapheArquer1(pgG,nSommat+7,nSommat+8,coJaune);
				GrapheArquer1(pgG,nSommat+2,nSommat+4,(bBoucler)? coJaune: coRouge);
				GrapheArquer1(pgG,nSommat+4,nSommat+5,coJaune);
				GrapheArquer1(pgG,nSommat+5,nSommat+7,(bBoucler)? coJaune: coBleu);
		}
	//relier les étages entre eux
		//te("nOffset",nOffset);
		for (nArc=0,uEntresol=1,nCouleur=coVert;uEntresol<nSommet;uEntresol++)
			for (uQuad0=1;uQuad0<=nSommet;uQuad0++){
				sX=nOffset+(uEntresol-1)*(ukHuit*nSommet)+ukHuit*(uQuad0-1)+ukHuit;
				nCouleur++;
				for (uQuad1=1;uQuad1<=nSommet;uQuad1++)
					if (uQuad0!=uQuad1){//connecter ces deux quadripoles de ukHuit à 1
						sY=nOffset+(uEntresol-0)*(ukHuit*nSommet)+ukHuit*(uQuad1-1)+1;
						bArquer= 0 && (uQuad0+1==uQuad1);
						//te("uEntresol",uEntresol);
						if ( nTest%10==0 || !(uEntresol==1 && uQuad0==1 && uQuad1==2) ){
							//prendre impérativt une couleur >1 pour couper le lien entre étages
							//teee("uEntresol,nQuad0,nQuad1",uEntresol,uQuad0,uQuad1);
							GrapheArquer1(pgG,sX,sY,nCouleur);//coVerT et suivants
							nArc++;
						}
					}
			}
	te("arcs entre étages:",nArc);
}//CliqueGenereR

void CouvertureCreerAuparavanT(int nSommet,int bDipoleExclu,graf **ppgG){
	//alloue et rend un graphe complet *ppgG déroulé,bipartitionné et flanqué de 2 sélecteurs amont et aval par colonne. 
	const int kbUnNoeudEnSus=kV;
	int bBiparti,bInformer=kF;
	int uC,nOffset,uB,uEtage,nSelecteur,sPole0,sPole1,nSommetParSelecteur;
	int aK,sZ;
	if (bInformer) Appel0("CouvertureCreerAuparavanT");
		Assert1("CouvertureCreerAuparavanT",nSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,nSommet);
			GrapheCliquer(*ppgG,nSommet);
			GrapheDerouler(*ppgG);
			GrapheBipartitionner(*ppgG);//génère les dipôles
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti pour",sPluriel(nSommet,"sommet")));
			for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->coulh[aK]=coRouge;
		//générer nSelecteur=nSommet*(nSommet-1) pôles amont et autant de pôles aval
			nOffset=2*nSommet*nSommet;
			nSommetParSelecteur=nSommet-1;
			if (bInformer) d(nSommetParSelecteur);
			nSelecteur=2*nSommet;//nb total de sélecteurs,ie les nSommet en amont plus les nSommet en aval
			if (bInformer) tee("nSommet,nOffset",nSommet,nOffset);
			GrapheSommer(*ppgG,+nSelecteur*nSommetParSelecteur);
			if (bInformer) te("Sommets dédiés dipôles",(*ppgG)->nSommetEnTout-nSelecteur*nSommetParSelecteur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée bipartie étoilée non encore connectée");
		//connecter les pôles aux dipôles
			for (uC=1;uC<=nSommet;uC++){//itère sur les colonnes
				sPole0=nOffset+(uC-1)*2*nSommetParSelecteur;//prépôle amont
				sPole1=sPole0+nSommetParSelecteur;//prépôle aval
				for (uB=1;uB<=nSommetParSelecteur;uB++){//itère sur les branches du sélecteur colonne
					for (sZ=2*(uC-1)+1,uEtage=1;uEtage<=nSommet;uEtage++,sZ+=2*nSommet){//itère sur les nSommet étages
						if (bInformer) d5(uC,uB,uEtage,sPole0+uB,sZ+0);
						GrapheArquer1(*ppgG,sPole0+uB,sZ+0,coJaune);
						if (bInformer) d5(uC,uB,uEtage,sZ+1,sPole1+uB);
						GrapheArquer1(*ppgG,sZ+1,sPole1+uB,coJaune);
					}
				}
				if (bInformer) Ligne();
			}
		//connecter chaque pôle sud à chaque pôle nord respectif
			for (uC=1;uC<=nSommet;uC++){//itère sur les colonnes
				sPole0=nOffset+2*nSommetParSelecteur*(uC-1)+1;
				sPole1=sPole0+nSommetParSelecteur;//pôle aval
				for (uB=1;uB<=nSommetParSelecteur;uB++){//itère sur les branches du sélecteur colonne
					if (bInformer) d4(uC,uB,sPole1+uB-1,sPole0+uB-1);
					GrapheArquer1(*ppgG,sPole1+uB-1,sPole0+uB-1,coBleu);
				}
			}
		//fermer le circuit source-trappe APRES
			if (bInformer) tee("fermeture nSommet0,nOffset+1",nOffset,1);
			if (kbUnNoeudEnSus){
				GrapheSommer(*ppgG,1);
				//d2(nOffset,(*ppgG)->nSommetEnTout);
				GrapheArquer1(*ppgG,nOffset,(*ppgG)->nSommetEnTout,coVert);
				GrapheArquer1(*ppgG,(*ppgG)->nSommetEnTout,1,coVert);
			}else GrapheArquer1(*ppgG,nOffset,1,coVert);
		if (bDipoleExclu){//retirer les nSommet*nSommet dipôles
			for (sZ=1;sZ<nOffset;sZ+=2)
				GrapheDesarquer(*ppgG,sZ,sZ+1);
		}
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerAuparavanT 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		Assert1("CouvertureCreerAuparavanT 2",kbUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerAuparavanT");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerAuparavanT

void CouvertureCreerDuO(int uSommet,int bSymetriser,int nArcManquant,graf **ppgG){
	//alloue et rend un graphe complet *ppgG déroulé,NON bipartitionné avec uSommet-1 dipôles saturateurs par colonne. 
	int bUnNoeudEnSus=!bSymetriser;
	int bBiparti,bInformer=kF;
	int uC,nOffset,uEtage,nSaturateurEnTout,sPole0,nSommetParSaturateur;
	int aK,sX,sY;
	//d2(bDipoleExclu,bUnNoeudEnSus);
	if (bInformer) Appel0("CouvertureCreerDuO");
		Assert1("CouvertureCreerDuO",uSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,uSommet);
			GrapheCliquer(*ppgG,uSommet);
			if (nArcManquant>0){//tuer assez d'arcs pour qu'il n'y ait plus de couvertures élémentaires
				if (bInformer) GrapheVoir(*ppgG,"ppgG AVANT GrapheDesarquer");
				if (uSommet==2 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==3 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==4 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (bInformer) GrapheVoir(*ppgG,"ppgG APRES GrapheDesarquer");
			}
			GrapheDerouler(*ppgG);
			//GrapheBipartitionner(*ppgG);//génère les dipôles
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé non biparti pour",sPluriel(uSommet,"sommet")));
			for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->coulh[aK]=coRouge;
		//générer nSaturateurEnTout=uSommet*(uSommet-1) saturateurs
			nOffset=1*uSommet*uSommet;
			nSaturateurEnTout=uSommet*(uSommet-1);//nb total de monopôles saturateurs
			nSommetParSaturateur=1;
			GrapheSommer(*ppgG,+nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) tee("uSommet,nOffset",uSommet,nOffset);
			if (bInformer) te("Sommets dédiés monopôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée non bipartie saturée non encore connectée");
		//connecter les saturateurs aux dipôles ainsi que le saturateur aval au saturateur amont associé
			sPole0=nOffset+1;
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				for (sX=1*(uC-1)+1,uEtage=1;uEtage<uSommet;uEtage++,sX+=1*uSommet){//itère sur les uSommet étages
					sY=sX+1*uSommet;
					if (bInformer) d5(uC,uEtage,sPole0,sX,sY);
					GrapheArquer1(*ppgG,sPole0,sX,coJaune);GrapheArquer1(*ppgG,sPole0,sY,coJaune);
					GrapheArquer1(*ppgG,sX,sPole0,coJaune);GrapheArquer1(*ppgG,sY,sPole0,coJaune);
					sPole0++;
				}
				if (bInformer) Ligne();
			}
		//fermer le circuit source-trappe APRES
			if (bUnNoeudEnSus){
				GrapheSommer(*ppgG,1);
				GrapheArquer1(*ppgG,nOffset,(*ppgG)->nSommetEnTout,coVert);
				GrapheArquer1(*ppgG,(*ppgG)->nSommetEnTout,1,coVert);
			}else GrapheArquer1(*ppgG,nOffset,1,coVert);
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerDuO 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		//Assert1("CouvertureCreerDuO 2",bUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerDuO");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerDuO

void CouvertureCreerDuoPaiR(int uSommet,int bSymetriser,int nArcManquant,graf **ppgG){
	//alloue et rend un graphe complet *ppgG déroulé,NON bipartitionné avec uSommet-1 dipôles saturateurs par colonne. 
	int uC,nOffset,uEtage,nSaturateurEnTout,sPole0,nSommetParSaturateur;
	int aK,sX,sY,bInformer=kF;
	int bUnNoeudEnSus=bImpair(uSommet);
	//d2(bDipoleExclu,bUnNoeudEnSus);
	if (bInformer) Appel0("CouvertureCreerDuoPaiR");
		Assert1("CouvertureCreerDuoPaiR",uSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,uSommet);
			GrapheCliquer(*ppgG,uSommet);
			if (nArcManquant>0){//tuer assez d'arcs pour qu'il n'y ait plus de couvertures élémentaires
				if (bInformer) GrapheVoir(*ppgG,"ppgG AVANT GrapheDesarquer");
				if (uSommet==2 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==3 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==4 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (bInformer) GrapheVoir(*ppgG,"ppgG APRES GrapheDesarquer");
			}
			GrapheDerouler(*ppgG);
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé non biparti pour",sPluriel(uSommet,"sommet")));
		//colorer les arcs selon la parité des étages
			Assert1("CouvertureCreerDuoPaiR 12345",uSommet*uSommet==(*ppgG)->nSommetEnTout);
			for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
				for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
					uEtage=1+(sX-1)/uSommet;
					(*ppgG)->coulh[aK]=(bImpair(uEtage) )? coBleu: coViolet;
				}
		//générer nSaturateurEnTout=uSommet*(uSommet-1) saturateurs
			nOffset=1*uSommet*uSommet;
			nSaturateurEnTout=uSommet*(uSommet-1);//nb total de monopôles saturateurs
			nSommetParSaturateur=1;
			GrapheSommer(*ppgG,+nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) tee("uSommet,nOffset",uSommet,nOffset);
			if (bInformer) te("Sommets dédiés monopôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée non bipartie saturée non encore connectée");
		//connecter les saturateurs aux dipôles en mode symétrique
			sPole0=nOffset+1;
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				for (sX=1*(uC-1)+1,uEtage=1;uEtage<uSommet;uEtage++,sX+=1*uSommet){//itère sur les uSommet étages
					sY=sX+1*uSommet;
					if (bInformer) d5(uC,uEtage,sPole0,sX,sY);
					GrapheArquer2(*ppgG,sPole0,sX,coRouge,coJaune);
					GrapheArquer2(*ppgG,sPole0,sY,coRouge,coJaune);
					sPole0++;
				}
				if (bInformer) Ligne();
			}
		//fermer le circuit source-trappe APRES
			if (bUnNoeudEnSus){
				GrapheSommer(*ppgG,1);
				GrapheArquer1(*ppgG,nOffset,(*ppgG)->nSommetEnTout,coBleu);
				GrapheArquer1(*ppgG,(*ppgG)->nSommetEnTout,1,coOrange);//négatif
			}else GrapheArquer1(*ppgG,nOffset,1,coOrange);//négatif
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert2("CouvertureCreerDuoPaiR 1",(*ppgG)->nSommetEnTout<knLigneLiM,bPair((*ppgG)->nSommetEnTout));
	if (bInformer) Appel1("CouvertureCreerDuoPaiR");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerDuoPaiR

void CouvertureCreerCarreH(int uSommet,int bSymetriser,int nArcManquant,graf **ppgG){
	//alloue et rend un graphe complet *ppgG déroulé,bipartitionné avec uSommet-1 dipôles saturateurs par colonne. 
	int bUnNoeudEnSus=1 && !bSymetriser;
	int bDipoleExclu=bSymetriser;
	int bBiparti,bInformer=kV;
	int uC,nOffset,uEtage,nSaturateurEnTout,sP,sPole0,sPole1,nSommetParSaturateur;
	int aK,sX,sY;
	//d2(bDipoleExclu,bUnNoeudEnSus);
	if (bInformer) Appel0("CouvertureCreerCarreH");
		Assert1("CouvertureCreerCarreH",uSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,uSommet);
			GrapheCliquer(*ppgG,uSommet);
			if (nArcManquant>0){//tuer assez d'arcs pour qu'il n'y ait plus de couvertures élémentaires
				if (bInformer) GrapheVoir(*ppgG,"ppgG AVANT GrapheDesarquer");
				if (uSommet==2 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==3 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==4 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (bInformer) GrapheVoir(*ppgG,"ppgG APRES GrapheDesarquer");
			}
			GrapheDerouler(*ppgG);//$
			GrapheBipartitionner(*ppgG);//génère les dipôles
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti pour",sPluriel(uSommet,"sommet")));
			for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->coulh[aK]=coRouge;
		//générer nSaturateurEnTout=uSommet*(uSommet-1) saturateurs
			nOffset=2*uSommet*uSommet;
			nSaturateurEnTout=uSommet*(uSommet-1);//nb total de dipôles saturateurs
			nSommetParSaturateur=2*(uSommet-1);
			//nSommetParSaturateur=2;
			d(nSommetParSaturateur);
			GrapheSommer(*ppgG,+nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) tee("uSommet,nOffset",uSommet,nOffset);
			if (bInformer) te("Sommets dédiés dipôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée bipartie saturée non encore connectée");
		//connecter les saturateurs aux dipôles ainsi que le saturateur aval au saturateur amont associé
			sPole0=nOffset+1;
			d(bDipoleExclu);
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				for (sX=2*(uC-1)+1,uEtage=1;uEtage<uSommet;uEtage++,sX+=2*uSommet){//itère sur les uSommet étages
					sY=sX+2*uSommet;
					sPole1=sPole0+nSommetParSaturateur-1;//saturateur aval
					if (bInformer) d5(uC,uEtage,sPole0,sX+0,sY+0);
					GrapheArquer1(*ppgG,sPole0,sX+0,coJaune);GrapheArquer1(*ppgG,sPole0,sY+0,coJaune);
					if (bInformer) d5(uC,uEtage,sX+1,sY+1,sPole1);
					GrapheArquer1(*ppgG,sX+1,sPole1,coJaune);GrapheArquer1(*ppgG,sY+1,sPole1,coJaune);
					//lier les pôles csécutifs
						for (sP=sPole0;sP<sPole1;sP++){
							GrapheArquer1(*ppgG,sP+1,sP,coBleu);
							d2(sP+1,sP);
						}
					sPole0=sPole1+1;//saturateur amont suivant
				}
				if (bInformer) Ligne();
			}
		//fermer le circuit source-trappe APRES
			if (bInformer) tee("fermeture nSommet0,nOffset+1",nOffset,1);
			if (bUnNoeudEnSus){
				GrapheSommer(*ppgG,1);
				//d2(nOffset,(*ppgG)->nSommetEnTout);
				GrapheArquer1(*ppgG,nOffset,(*ppgG)->nSommetEnTout,coVert);
				GrapheArquer1(*ppgG,(*ppgG)->nSommetEnTout,1,coVert);
			}else GrapheArquer1(*ppgG,nOffset,1,coVert);
		if (bDipoleExclu){//retirer les uSommet*uSommet dipôles
			for (sX=1;sX<nOffset;sX+=2)
				GrapheDesarquer(*ppgG,sX,sX+1);
		}
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerCarreH 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		Assert1("CouvertureCreerCarreH 2",bUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerCarreH");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerCarreH

void CouvertureCreerKarreH(int uSommet,int bDipoleExclu,graf **ppgG){
	//idem CouvertureCreerCarreH mais les plus petits heads hors sommet 1 sont les dipôles saturateurs. 
	int bBiparti,bInformer=kF;
	int uC,nOffset,uEtage,nSaturateurEnTout,sPole0,sPole1,nSommetMax,nSommetParSaturateur;
	int aK,sX,sY;
	if (bInformer) Appel0("CouvertureCreerKarreH");
		Assert1("CouvertureCreerKarreH",uSommet>0);
		nSommetMax=2*uSommet*uSommet+2+2*uSommet*(uSommet-1);
		GrapheCreer0(ppgG,uSommet);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCliquer(*ppgG,uSommet);
			GrapheDerouler(*ppgG);
			GrapheBipartitionner(*ppgG);//génère les dipôles
//GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti pour",sPluriel(uSommet,"sommet")));
			for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->coulh[aK]=coRouge;
			nSaturateurEnTout=uSommet*(uSommet-1);//nb total de dipôles saturateurs
			nSommetParSaturateur=2;
			//GrapheSommer(*ppgG,+nSaturateurEnTout*nSommetParSaturateur);
			GrapheTranslater(*ppgG,nSaturateurEnTout+2);//1 head par saturateur et 2 sommets sur la boucle majeure.
//GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti translaté pour",sPluriel(uSommet,"sommet")));
		//générer nSaturateurEnTout=uSommet*(uSommet-1) saturateurs
			GrapheSommer(*ppgG,nSommetMax-(*ppgG)->nSommetEnTout);
			nOffset=2+uSommet*(uSommet-1);
			if (bInformer) tee("uSommet,nOffset",uSommet,nOffset);
			if (bInformer) te("Sommets dédiés dipôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée bipartie saturée non encore connectée");
		//connecter les saturateurs aux dipôles ainsi que le saturateur aval au saturateur amont associé
			sPole1=2+1;//saturateur aval
			sPole0=sPole1+nSaturateurEnTout+2*uSommet*uSommet;//saturateur amont
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				for (sX=nOffset+2*(uC-1)+1,uEtage=1;uEtage<uSommet;uEtage++,sX+=2*uSommet){//itère sur les uSommet étages
					sY=sX+2*uSommet;
					if (bInformer) d5(uC,uEtage,sPole0,sX+0,sY+0);
					GrapheArquer1(*ppgG,sPole0,sX+0,coJaune);GrapheArquer1(*ppgG,sPole0,sY+0,coJaune);
					if (bInformer) d5(uC,uEtage,sX+1,sY+1,sPole1);
					GrapheArquer1(*ppgG,sX+1,sPole1,coJaune);GrapheArquer1(*ppgG,sY+1,sPole1,coJaune);
					if (!bDipoleExclu)
						GrapheArquer1(*ppgG,sPole1,sPole0,coBleu);//lier les pôles est inutile si pas de dipôle
					sPole0++;sPole1++;
				}
				if (bInformer) Ligne();
			}
		//fermer la boucle majeure APRES
			if (bInformer) tee("fermeture nSommet0,nOffset+1",nOffset,1);
			sX=1;
			//d2(sY+1,sX);
			GrapheArquer1(*ppgG,sY+1,1,coVert);
			GrapheArquer1(*ppgG,1,2,coVert);
			//d(nOffset+1);
			GrapheArquer1(*ppgG,2,nOffset+1,coVert);
		if (bDipoleExclu){//retirer les uSommet*uSommet dipôles
			for (sX=nOffset+1;sX<=sY;sX+=2){
				//d2(sX,sX+1);
				GrapheDesarquer(*ppgG,sX,sX+1);
			}
		}
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerKarreH 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		//Assert1("CouvertureCreerKarreH 2",bUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerKarreH");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerKarreH

void CouvertureCreerPentA(int uSommet,graf **ppgG){
	//monopôles,saturateurs n-1/n et n-2/n. 
	int bInformer=kF;
	int uC,bStrict,nOffset,uEtage,nSaturateurEnTout,sPole,nSommetMax,nSommetParSaturateur,nSommetDeBoucleMajeure;
	int sX,sY;
	if (bInformer) Appel0("CouvertureCreerPentA");
		Assert1("CouvertureCreerPentA",uSommet>0);
		nSommetDeBoucleMajeure=2;
		nSaturateurEnTout=(uSommet-1)+(uSommet-2)*(uSommet-2)+(uSommet-1);//nb total de dipôles saturateurs
		nSommetMax=nSommetDeBoucleMajeure+(uSommet*uSommet)+nSaturateurEnTout;
		GrapheCreer0(ppgG,uSommet);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet demeure un monopôle
			GrapheCliquer(*ppgG,uSommet);
			GrapheDerouler(*ppgG);
if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé pour",sPluriel(uSommet,"sommet")));
			if (bInformer) d(nSaturateurEnTout);
			nSommetParSaturateur=1;
			nOffset=nSommetDeBoucleMajeure+nSaturateurEnTout;//1 head par saturateur + 2 sommets sur boucle majeure.
			GrapheTranslater(*ppgG,nOffset);
//GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti translaté pour",sPluriel(uSommet,"sommet")));
		//générer tous les saturateurs
			GrapheSommer(*ppgG,nSommetMax-(*ppgG)->nSommetEnTout);
			if (bInformer) d2(uSommet,nOffset);
			if (bInformer) te("Sommets dédiés monopôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout*nSommetParSaturateur);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée saturée non encore connectée");
		//connecter les saturateurs aux monopôles
			sPole=nSommetDeBoucleMajeure+1;//saturateur aval
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				bStrict=bCroitStrict(1,uC,uSommet);//afin d'itérer sur les uSommet-bStrict étages
				for (sX=nOffset+(uC-1)+1,uEtage=1;uEtage+bStrict<uSommet;uEtage++,sX+=uSommet){
					sY=sX+uSommet*(1+bStrict);
					if (bInformer) d5(uC,uEtage,sPole,sX,sY);
					GrapheArquer1(*ppgG,sPole,sX,coJaune);
					GrapheArquer1(*ppgG,sPole,sY,coJaune);
					sPole++;
				}
				if (bInformer) Ligne();
			}
		//fermer la boucle majeure APRES
			sX=1;
			if (bInformer) d4(sY,sX,sX+1,nOffset+1);
			GrapheArquer1(*ppgG,sY,sX,coVert);
			GrapheArquer1(*ppgG,sX,sX+1,coVert);
			GrapheArquer1(*ppgG,sX+1,nOffset+1,coVert);
		//détruire le premier lien monopôle-saturateur
			if (bInformer) d2(nSommetDeBoucleMajeure+1,nOffset+1);
			GrapheDesarquer(*ppgG,nSommetDeBoucleMajeure+1,nOffset+1);
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe de monopôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerPentA 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		//Assert1("CouvertureCreerPentA 2",bUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerPentA");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerPentA

void CouvertureCreerTrianglE(int uSommet,int bDipoleExclu,graf **ppgG){
	//alloue et rend un graphe complet *ppgG déroulé,non bipartié avec uSommet-1 saturateurs par colonne. 
	const int kbUnNoeudEnSus=kV;
	int bBiparti,bInformer=kV;
	int uC,nOffset,uEtage,nSaturateurEnTout,sPole;
	int aK,sX,sY;
	if (bInformer) Appel0("CouvertureCreerTrianglE");
		Assert1("CouvertureCreerTrianglE",uSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,uSommet);
			GrapheCliquer(*ppgG,uSommet);
			GrapheDerouler(*ppgG);
			GrapheBipartitionner(*ppgG);//génère les dipôles
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti pour",sPluriel(uSommet,"sommet")));
			for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
				(*ppgG)->coulh[aK]=coRouge;
		//générer nSaturateurEnTout=uSommet*(uSommet-1) saturateurs
			nOffset=2*uSommet*uSommet;
			nSaturateurEnTout=uSommet*(uSommet-1);//nb total de dipôles saturateurs
			GrapheSommer(*ppgG,+nSaturateurEnTout);
			if (bInformer) tee("uSommet,nOffset",uSommet,nOffset);
			if (bInformer) te("Sommets dédiés dipôles",(*ppgG)->nSommetEnTout-nSaturateurEnTout);
			if (bInformer) GrapheVoir(*ppgG,"Clique étagée bipartie saturée non encore connectée");
		//connecter les saturateurs aux dipôles ainsi que le saturateur aval au saturateur amont associé
			sPole=nOffset+1;
			for (uC=1;uC<=uSommet;uC++){//itère sur les colonnes
				for (sX=2*(uC-1)+1,uEtage=1;uEtage<uSommet;uEtage++,sX+=2*uSommet){//itère sur les uSommet étages
					sY=sX+2*uSommet;
					if (bInformer) d5(sX+1,sY+1,sPole,sX+0,sY+0);
					GrapheArquer1(*ppgG,sPole,sX+0,coJaune);GrapheArquer1(*ppgG,sPole,sY+0,coJaune);
					GrapheArquer1(*ppgG,sX+1,sPole,coJaune);GrapheArquer1(*ppgG,sY+1,sPole,coJaune);
					sPole++;//saturateur amont
				}
				if (bInformer) Ligne();
			}
		//fermer le circuit source-trappe APRES
			if (bInformer) tee("fermeture nSommet0,nOffset+1",nOffset,1);
			if (kbUnNoeudEnSus){
				GrapheSommer(*ppgG,1);
				//d2(nOffset,(*ppgG)->nSommetEnTout);
				GrapheArquer1(*ppgG,nOffset,(*ppgG)->nSommetEnTout,coVert);
				GrapheArquer1(*ppgG,(*ppgG)->nSommetEnTout,1,coVert);
			}else GrapheArquer1(*ppgG,nOffset,1,coVert);
		if (bDipoleExclu){//retirer les uSommet*uSommet dipôles
			for (sX=1;sX<nOffset;sX+=2)
				GrapheDesarquer(*ppgG,sX,sX+1);
		}
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerTrianglE 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		Assert1("CouvertureCreerTrianglE 2",kbUnNoeudEnSus || bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerTrianglE");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerTrianglE

void GrapheDeroulerToriquE(graf *pgG){
	//transforme pgG=(S,A) de façon à obtenir un graphe torique à S*S sommets:à chaque arc (sX,sY) de pgG,on associe S arcs (sXi,sYj) avec 1≤i<S et j=i+1. 
	const int kbDerouler=kF;
	int nEtage,aK,aL,sX,sY,sZ,sP,sQ;
	int nSommat=pgG->nSommetEnTout;
	int nArcat=pgG->nArcEnTout;
	int uSommetEnTout=2*nSommat*nSommat;//sera biparti
	int uArcEnTout=nArcat*nSommat;
	int aHed0[1+nSommat+1];
	int sSuk0[1+nArcat];
	int aHed1[1+2*uSommetEnTout+1];
	if (kbDerouler) Appel0("GrapheDeroulerToriquE");
		Assert2("GrapheDeroulerToriquE1",nSommat>0,bGrapheSimple(pgG));
		if (kbDerouler) d3(nSommat,uSommetEnTout,uArcEnTout);
		Assert2("GrapheDeroulerToriquE2",uSommetEnTout<kuGrapheSommetLim,uArcEnTout<kuGrapheArcLim);
		//affecter pgG->sSuk[]: chague arc relie un sommet source de l'étage uEtage à un sommet cible de l'étage uEtage+1 (uEtage=1 ssi 1er étage):
			VecteurCopier(pgG->aHed,1,nSommat+1,aHed0);
			VecteurCopier(pgG->sSuk,1,nArcat,sSuk0);
			VecteurRazer(aHed1,0,uSommetEnTout+1);
			if (kbDerouler) VecteurVoir("aHed1",aHed1,1,uSommetEnTout+1);
			if (kbDerouler) VecteurVoir("aHed0",aHed0,1,nSommat+1);
			if (kbDerouler) VecteurVoir("sSuk0",sSuk0,1,nArcat);
			for (aL=0,sX=0,sP=1;sP<=nSommat;sP++)
				for (nEtage=0;nEtage<nSommat;nEtage++){
					for (sX++,aK=aHed0[sP];aK<aHed0[sP+1];aK++){
						sQ=sSuk0[aK];
						sY=1+(sQ-1)*nSommat+nEtage%(nSommat-1);
						if (nEtage+1<nSommat)
							sZ=sQ+uSommetEnTout/2+(nEtage*nSommat)+nSommat;
						else sZ=sQ+uSommetEnTout/2;
						if (kbDerouler) d3(sX,sY,sZ);
						pgG->sSuk[++aL]=sZ;
						pgG->coulh[aL]=aK;
					}
					aHed1[sX]=aHed0[sP+1]-aHed0[sP];//dc effectif et non pas cumul
				}
			Assert1("GrapheDeroulerToriquE98",aL==uArcEnTout);
			if (kbDerouler) VecteurVoir("pgG->sSuk APRES",pgG->sSuk,1,uArcEnTout);//dont élément final en sus
		//affecter pgG->aHed[]
			if (kbDerouler) VecteurVoir1("aHed1 INIT",aHed1,0,uSommetEnTout+1);
			for (sX=1;sX<=uSommetEnTout+1;sX++)
				aHed1[sX]+=aHed1[sX-1];
			if (kbDerouler) VecteurVoir1("aHed1 CUMUL",aHed1,0,uSommetEnTout+1);
			for (sX=1;sX<=uSommetEnTout;sX++)
				pgG->aHed[sX+1]=1+aHed1[sX];
		//affecter pgG->nArcEnTout et pgG->nSommetEnTout
			pgG->nArcEnTout=uArcEnTout;
			pgG->nSommetEnTout=uSommetEnTout;
		if (kbDerouler) VecteurVoir1("pgG->aHed APRES",pgG->aHed,0,pgG->nSommetEnTout+1);
		if (kbDerouler) VecteurVoir("pgG->sSuk APRES",pgG->sSuk,1,pgG->nArcEnTout+1);//dont élément final en sus
		Assert1("GrapheDeroulerToriquE3",bGrapheSimple(pgG));
	if (kbDerouler) Appel1("GrapheDeroulerToriquE");
}//GrapheDeroulerToriquE

void CouvertureCreerUltimE(int uSommet,int bSymetriser,int nArcManquant,graf **ppgG,int *pnPeriode){
	//alloue et rend un graphe complet *ppgG déroulé,bipartitionné et torique. 
	int bDipoleExclu=bSymetriser;
	int bBiparti,bInformer=kF,bTorique=kV;
	int sX;
	//d(bDipoleExclu);
	if (bInformer) Appel0("CouvertureCreerUltimE");
		Assert1("CouvertureCreerUltimE",uSommet>0);
		//*ppgG, orienté, décrive une clique déroulée où chaque sommet est remplacé par un dipôle
			GrapheCreer0(ppgG,uSommet);
			GrapheCliquer(*ppgG,uSommet);
			if (nArcManquant>0){//tuer assez d'arcs pour qu'il n'y ait plus de couvertures élémentaires
				if (bInformer) GrapheVoir(*ppgG,"ppgG AVANT GrapheDesarquer");
				if (uSommet==2 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==3 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (uSommet==4 && nArcManquant>0) GrapheDesarquer(*ppgG, 1, 2);
				if (bInformer) GrapheVoir(*ppgG,"ppgG APRES GrapheDesarquer");
			}
			*pnPeriode=(*ppgG)->nArcEnTout;
			GrapheDeroulerToriquE(*ppgG);//$
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé torique pour",sPluriel(uSommet,"sommet")));
			if (!bTorique)
				GrapheBipartitionner(*ppgG);//génère les dipôles
			if (bInformer) GrapheVoir(*ppgG,sC2b("Graphe déroulé biparti pour",sPluriel(uSommet,"sommet")));
		Assert1("CouvertureCreerUltimE56",bDipoleExclu);
		if (!bTorique && bDipoleExclu){//retirer les uSommet*uSommet dipôles
			for (sX=1;sX<2*uSommet*uSommet;sX+=2)
				GrapheDesarquer(*ppgG,sX,sX+1);
		}
		if (bInformer) GrapheVoir(*ppgG,"***********Graphe dipôlé avec dipôles dûment connectés aux sélecteurs");
		Assert1("CouvertureCreerUltimE 1",(*ppgG)->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(*ppgG);
		Assert1("CouvertureCreerUltimE 2",bBiparti);//graphe non biparti si kbUnNoeudEnSus sur cycle majeur
	if (bInformer) Appel1("CouvertureCreerUltimE");
	//GrapheVoir(*ppgG,"***********Graphe terminé");
}//CouvertureCreerUltimE

int nMatriceNumeroteR(iMatrice *pmE,int bSelonCouleur,int bSymetrique,int nPeriode){
	int uC,nCouleur,uL,aK,nNumeroter,aKmin=0;
	if (nPeriode>0){
		for (nNumeroter=0,uL=1;uL<=pmE->nLigne;uL++)
			for (uC=1;uC<uL;uC++){
				pmE->Mat[uL][uC]= - pmE->Mat[uC][uL];
				nNumeroter=iSup(nNumeroter,pmE->Mat[uC][uL]);
			}
	}else if (bSelonCouleur){//coRouge et coOrange et coViolet < 0
		printf("négativer les couleurs %d,%d et %d\n",coRouge,coOrange,coViolet);
		for (aK=aKmin,nNumeroter=0,uL=1;uL<=pmE->nLigne;uL++)
				for (uC=uL+1;uC<=pmE->nColonne;uC++){
					nCouleur=pmE->Mat[uL][uC];
					if (nCouleur>0)
						pmE->Mat[uL][uC]=ySignePres(nCouleur==coViolet,++aK);
					nNumeroter=iSup(nNumeroter,aK);
				}
		for (uL=1;uL<=pmE->nLigne;uL++)
				for (uC=1;uC<uL;uC++){
					nCouleur=pmE->Mat[uL][uC];
					if (nCouleur==coRouge)
						pmE->Mat[uL][uC]=-pmE->Mat[uC][uL];
					if (nCouleur==coOrange){
						pmE->Mat[uL][uC]=-(++aK);
						nNumeroter=iSup(nNumeroter,aK);
					}
				}
	}else for (aK=aKmin,nNumeroter=0,uL=1;uL<=pmE->nLigne;uL++)
		for (uC=1;uC<=pmE->nColonne;uC++){
			if ( (!bSymetrique || uL<uC) && pmE->Mat[uL][uC]){
				pmE->Mat[uL][uC]=++aK;
				if (bSymetrique)
					pmE->Mat[uC][uL]=-pmE->Mat[uL][uC];
				nNumeroter=iSup(nNumeroter,aK);
			}
		}
	//MatriceVoir("nMatriceNumeroteR",pmE);
	//d(nNumeroter);
	return(nNumeroter);
}//nMatriceNumeroteR

void CouvertureCompteR(int bGeneral,int nGraphType,int nArcManquant,int *pnCouverture,long *pyDeterminant){
	//teste iCouvertureDecompterBieN sur le graphe de type abs(iGraphType)
	//int nDim;
	const int bDuoPair=kF;
	const int bInformer=kV;
	const int bUltime=kF;
	int nArcMax,iNeutre,uSommet,bSymetriser;
	long yDeterminant,zKomplexiteh;
	graf *pgG;
	iMatrice *pmE;
	nbMatrice *pmnbE;
	int nPeriode;
	nb nbResultat;
	//d2(bGeneral,iGraphType);
	Assert1("CouvertureCompteR0",bBool(bGeneral) );
	uSommet=abs(nGraphType);//d
	char *sContexte=malloc(100);//sinon,à cause du volume d'affichage ci-dessous,sContexte serait libéré prématurément. 
		if(bGeneral) 
			strcpy(sContexte,sC4b("pour le graphe étagé",(nArcManquant>0)?"incomplet":"complet", "à",sPluriel(uSommet,"sommet")));//car transmis à des routines qui affichent bcp et libèrent sQuoi prématurément.
		else strcpy(sContexte,sItem(sgrNoM,1+nGraphType));//car transmis à des routines qui affichent bcp et libèrent sQuoi prématurément.
		if (bInformer) Titrer(sC2b("CouvertureCompteR",sContexte));
		//générer soit un petit graphe de test soit un graphe déroulé
			bSymetriser=!bGeneral;
d(bGeneral);
			if(!bGeneral){
				GrapheCreer1(&pgG,nGraphType,k1Creer);//dont couleurs;DESUET
				uSommet=pgG->nSommetEnTout;
			}
			//else CouvertureCreerKarreH(uSommet,bSansDipole=bSymetriser,&pgG);
			//}else CouvertureCreerPentA(uSommet,&pgG);
			nPeriode=0;
			if (1) CouvertureCreerDuO(uSommet,kV,nArcManquant=0,&pgG);
			if (bDuoPair) CouvertureCreerDuoPaiR(uSommet,bSymetriser=kF,nArcManquant=0,&pgG);
			if (0) CouvertureCreerCarreH(uSommet,bSymetriser=kF,nArcManquant=0,&pgG);
			if (bUltime) CouvertureCreerUltimE(uSommet,bSymetriser=kV,nArcManquant=0,&pgG,&nPeriode);

			GrapheVoir(pgG,"Graphe généré");
//d(iGraphType);
			if (bSymetriser)
				GrapheSymetriser(pgG);
		//générer la matrice associée au graphe et attribuer à chaque arc un numéro qui l'identifie
//bSymetriser=kF;
			MatriceAllouer1(&pmE,pgG->nSommetEnTout);
				MatriceDepuisGraphe(pgG,! (bDuoPair || bUltime),&pmE);
					//MatriceVoir(sC2b("Matrice dpi graf",sContexte),pmE);
					nArcMax=nMatriceNumeroteR(pmE,bDuoPair,bSymetriser,nPeriode);
					iNeutre=1+nArcMax;
					//d2(nPeriode,iNeutre);// $
					if (nArcManquant>1000){//tuer assez d'arcs pour qu'il n'y ait plus de couvertures élémentaires
						d(nArcManquant);
						if (uSommet==2 && nArcManquant>0) pmE->Mat[ 2][ 7]=0;
						
						if (uSommet==3 && nArcManquant>0) pmE->Mat[ 2][ 9]=0;
						if (uSommet==3 && nArcManquant>1) pmE->Mat[02][11]=0;
						
						if (uSommet==4 && nArcManquant>0) pmE->Mat[02][11]=0;
						if (uSommet==4 && nArcManquant>1) pmE->Mat[02][13]=0;
						if (uSommet==4 && nArcManquant>2) pmE->Mat[02][15]=0;
						
						if (uSommet==5 && nArcManquant>0) pmE->Mat[02][13]=0;
						if (uSommet==5 && nArcManquant>1) pmE->Mat[02][15]=0;
						if (uSommet==5 && nArcManquant>2) pmE->Mat[02][17]=0;
						if (uSommet==5 && nArcManquant>3) pmE->Mat[02][19]=0;
					}
				MatriceVoir(sC2b("Matrice",sContexte),pmE);
				//bannir les segments éventuels
					if(!bGeneral){
						//SegmentBanniR(pgG);//AVANT de modifier une qcq couleur
						//CouvertureBanniR(pmE);
					}
				if (0){//vérifier le déterminant par Urbanska
					//MatriceVoir(sC2b("Matrice pour Urbanska",sContexte),pmE);
					*pyDeterminant=yFormeKalculeR(pmE,0,!k1Voir);//Urbanska simple
					//d(*pyDeterminant);
					//if (bInformer)
						printf("Le déterminant BRUT vaut %s.%s(Urbanska longint).\n",sPar3(*pyDeterminant),sTab(4));
					//ld2(kyLongintMin,kxLongintMax);
				}
				if(1){
					//d2(uSommet,nPeriode);
					yDeterminant=yCouvertureDecompterTeR(pmE,uSommet,iNeutre,k1Optimum,nPeriode,!k1Afficher,pnCouverture,pyDeterminant,&zKomplexiteh);
					if (bInformer) printf("L'optimum est %s.%s(via yCouvertureDecompterTeR).\n",sPar3(yDeterminant),sTab(4));
				}
				if (1)//standardiser pr le calcul à venir du déterminant indépendamment des numéros des arcs
					MatriceUnifier(pmE);
				else MatriceUniter(pmE);
				MatriceSymetriser(&pmE);
				//HasardInit(kV);//VITAL pr comparer d'un appel à l'autre
				//MatriceHasarder(pmE,-6);
				//MatriceHasarder(pmE,-1);//[1..|iEmpan|];uniqt les éléments non nuls si iEmpan<0
				if (1){//vérifier le déterminant par Urbanska
					MatriceVoir(sC2b("Matrice symétrisée pour Urbanska",sContexte),pmE);
					*pyDeterminant=yFormeKalculeR(pmE,0,!k1Voir);//Urbanska simple
					//d(*pyDeterminant);
					//if (bInformer)
						printf("Le déterminant unifié vaut %s.%s(Urbanska longint).\n",sPar3(*pyDeterminant),sTab(4));
					//ld2(kyLongintMin,kxLongintMax);
				}
				if (0){//calculer le déterminant de la matrice
					//MatriceVoir(sC2b("Matrice",sContexte),pmE);
					*pyDeterminant=yFormeCalculeR(pmE);
					if (bInformer) printf("Le déterminant vaut %s.%s(Mahajan  longint).\n",sPar3(*pyDeterminant),sTab(4));
					//iDeterminant=iFormeCalculeR(pmE);
					//printf("Le déterminant vaut %s.%s(Mahajan integer...).\n",sPar3(iDeterminant),sTab(4));
				}
				if (0){//vérifier le déterminant par Gauss
					//MatriceVoir(sC2b("Matrice pour Gauss",sContexte),pmE);
					yDeterminant=yMatriceDeterminant(pmE);
					//if (bInformer)
						printf("Le déterminant vaut %s.%s(Gauss    longint).\n",sPar3(yDeterminant),sTab(4));
					//ld2(kyLongintMin,kxLongintMax);
				}
				if(0){//calculer le déterminant à l'aide du module Nb
					NbMatriceAllouer(&pmnbE);
						FormeMatriceR(pmE,pmnbE);
						NbDeterminer(pmnbE,!k1Voir,&nbResultat);
						if (bInformer) printf("Le déterminant vaut %s.%s(NbDeterminer).\n",sNb(nbResultat),sTab(4));
					free(pmnbE);
				}
			free(pmE);
		GrapheCreer0(&pgG,kF);
	free(sContexte);
	if (bInformer) Ligne();
}//CouvertureCompteR

void CouvertureCompterTouT(){
	int nCouverture[20],nArcManquant,uSommet=4;
	long yDeterminant[20];
	Appel0("CouvertureCompterTouT");Ligne();
		if(0)
			d(zCouvertureEnTouT(uSommet,k1Elementaire));//nb total de couvertures avec répétitions ds la dernière CC
		if(0){// $
			printf("%ssommets   coupures   couvertures       évaluation du déterminant\n",sTab(2));
			for (uSommet=5;uSommet<=5;uSommet++)
				for (nArcManquant=0;nArcManquant<=1+(uSommet>3)-2*(uSommet==5);nArcManquant++){
					CouvertureCompteR(k1General,uSommet,nArcManquant,&nCouverture[uSommet],&yDeterminant[uSommet]);
					printf("%s%4d%10d%15s%35s\n",sTab(2),uSommet,nArcManquant,sPar3(nCouverture[uSommet]),sPar3(yDeterminant[uSommet]));
				}
		}else CouvertureCompteR(k1General,uSommet,nArcManquant=0,&nCouverture[uSommet],&yDeterminant[uSommet]);
	Appel1("CouvertureCompterTouT");Ligne();
}//CouvertureCompterTouT

int iCouvertureDecompteR(iMatrice *pmA,int muNeutre,int nPivot,int bVoir,long *pzComplexiteh){//O(S4) calcul compilé ——exact car sans division
	//dénombre les couvertures du graphe simple pondéré défini par la matrice d'adjacence *pmA (Mahajan et Vinay,1997). 
	int noAvant,noApres,noMatYH,noMatYZ,noOperande,noProduit,noUn,noZero;
	int iDelta,nEtage,sH,sX,sY,sZ,nComposante,nComposanteEnTout,uSommat;
	int iDeltaPlus,iDeltaMoins,nInclus,nExclu,iPoidsMin,iPoidsMax;
	long zComplexiteh,xComplexitehMax;
	int noPole[2];
	int nCouverture0[2],nCouverture1[2],nCouverture2[2];
	char *sSymbole="==+-";
	int noV[2][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	float fRapport;
	int bPoly=kV;
	//Appel0("iCouvertureDecompteR");
		uSommat=pmA->nLigne;
		if (bVoir) printf("Le tableau noV nécessite %s éléments pour la matrice de dimension %s.\n",sPar3(2*uSommat*uSommat*uSommat),sPar3(uSommat));
		xComplexitehMax=2*zPuissance(pmA->nLigne,4);//facteur 2 vu la boucle sur nComposante
		Assert3("iCouvertureDecompteR2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne,xComplexitehMax>0);
		noZero=noPolyAfF(bPoly,0);noUn=noPolyAfF(bPoly,1);
		zComplexiteh=0;
		//noV et noPole soient razés; O(S3)
			for (nComposante=0;nComposante<2;nComposante++)
				for (noPole[nComposante]=noZero/*VITAL*/,sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;zComplexiteh++,nEtage++)
							noV[nComposante][sH][sX][nEtage]=noZero;
		if (bVoir) tee("uSommat",uSommat,uSommat*uSommat*uSommat);
		if (bVoir) te("zComplexiteh",zComplexiteh);
		if (bVoir) printf("Complexité courante %s. Ratio complexité/S4%.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*xComplexitehMax));
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de noV
			for (sH=1;sH<=uSommat;zComplexiteh++,sH++)
				noV[nComposante=uSommat%2][sH][sH][nEtage=0]=noUn;
		if (bVoir) printf("Complexité courante %s. Ratio complexité/S4%.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*xComplexitehMax));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (bVoir) {Titrer(sC2b("ETAGE",sEnt(nEtage))); tee("nEtage,uSommat",nEtage,uSommat);}
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (nComposante=0;nComposante<2;nComposante++)
							for (sZ =sH+1;sZ<=uSommat;zComplexiteh++,sZ++){
								noOperande=noV[nComposante][sH][sY][nEtage];
								noMatYZ=(pmA->Mat[sY][sZ]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sZ]);
								noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYZ);
								noAvant=noV[nComposante][sH][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[nComposante][sH][sZ][nEtage+1]=noApres;
								noMatYH=(pmA->Mat[sY][sH]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sH]);
								noOperande=noV[nComposante][sH][sY][nEtage];
								noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
								noAvant=noV[(1+nComposante)%2][sZ][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[(1+nComposante)%2][sZ][sZ][nEtage+1]=noApres;
							}//for sZ
			}
		nComposanteEnTout=2;
		if (bVoir) Titrer("COMPOSANTES");
		if (bVoir) d(nComposanteEnTout);
		//traiter le dernier étage; O(S2)
			if (0) Titrer("dernier etage");
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					noMatYH=noPolyAfF(bPoly,pmA->Mat[sY][sH]);
					for (nComposante=0;nComposante<2;nComposante++){
						noOperande=noV[nComposante][sH][sY][uSommat-1];
						noProduit=noPolyMuL(bPoly,noOperande,noMatYH);
						noAvant=noPole[nComposante];
						noApres=noPolyAdD(bPoly,noAvant,noProduit);
						noPole[nComposante]=noApres;
					}
				}
		//te("zComplexiteh Mahajan",zComplexiteh);
		fRapport=zComplexiteh/(1.0*xComplexitehMax);
		if (bVoir) printf("Complexité TOTALE Mahajan vs S4: %s / %s = %.2f.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),fRapport);
		if (bVoir) printf("Noeud pris pour Mahajan: %s.\n",sPar3(nDagPris()));
		//simplifier les DAGs en éliminant les feuilles de valeur 0 ou 1 qui sont superflues
			for (nComposante=0;nComposante<nComposanteEnTout;nComposante++)
				DagSimplifier(nComposante,noPole[nComposante],muNeutre,kF);
		//compter les couvertures dénombrées décrites dans les DAGs, les stocker dans nCouverture0[] et afficher la somme algébrique
			if (0){
				for (nComposante=0;nComposante<nComposanteEnTout;nComposante++){
					nCouverture0[nComposante]=nDagChemin(noPole[nComposante]);
					printf("Couvertures dénombrées à %s: %d.\n",sPluriel(1+nComposante,"composante"),nCouverture0[nComposante]);
				}
				printf("%sSomme alternée des couvertures dénombrée: ",sTab(2));
				for (iDelta=0,nComposante=0;nComposante<nComposanteEnTout;nComposante++){
					printf("%d%c",nCouverture0[nComposante],sSymbole[2*(nComposante+1<nComposanteEnTout)+bPair(nComposante)]);
					iDelta+=iSignePres(bImpair(nComposante),nCouverture0[nComposante]);
				}
				printf("%d.\n",iDelta);
			}
			//VecteurVoir("iEvaluer[]",iEvaluer,0,2-1);
		//inventorier les couvertures décrites dans les DAGs, les stocker dans nCouverture1[] et nCouverture2 et afficher la somme alternée.
			for (zComplexiteh=0,nComposante=0;nComposante<iInf(10,nComposanteEnTout);nComposante++){
				DagCouvrir(1+nComposante,noPole[nComposante],nPivot,&nCouverture1[nComposante],&nCouverture2[nComposante],&zComplexiteh);
				if (bVoir) printf("%sCouvertures décomptées à %s: %d.\n",sTab(2),sPluriel(1+nComposante,"composante"),nCouverture1[nComposante]);
			}
			fRapport=zComplexiteh/(1.0*xComplexitehMax);
			//printf("zComplexiteh TOTALE vs 2S4: %ld/%ld=%.2f.\n",zComplexiteh,xComplexitehMax,fRapport);
			if(0){
				printf("Somme alternée théorique: ");
				MatriceMarner(pmA,&iPoidsMin,&iPoidsMax);
				for (iDeltaPlus=iDeltaMoins=0,nComposante=0;nComposante<iInf(10,nComposanteEnTout);nComposante++){
					zDagEnumerer(nComposante,k1Afficher,pmA->nLigne,noPole[nComposante],!k1Tout,iPoidsMin,iPoidsMax,&nInclus,&nExclu);
					tee("Inclus et Exclus théoriques",nInclus,nExclu);
					iDeltaPlus+=iSignePres(bImpair(nComposante),nInclus);
					iDeltaMoins+=iSignePres(bImpair(nComposante),nExclu);
				}
				teee("iDeltaPlus,iDeltaMoins,iDeltaPlus-iDeltaMoins",iDeltaPlus,iDeltaMoins,iDeltaPlus-iDeltaMoins);
			}
			printf("%s Somme alternée des couvertures dénombrées: ",sTab(2));
			for (iDelta=0,nComposante=0;nComposante<nComposanteEnTout || !bLigne1(sEnt(iDelta));nComposante++){
				printf("%d%c",nCouverture1[nComposante],sSymbole[2*(nComposante+1<nComposanteEnTout)+bPair(nComposante)]);
				iDelta+=iSignePres(bImpair(nComposante),nCouverture1[nComposante]);
			}
			printf("%s Somme alternée des couvertures décomptées: ",sTab(2));
			for (iDelta=0,nComposante=0;nComposante<nComposanteEnTout || !bLigne1(sEnt(iDelta));nComposante++){
				printf("%d%c",nCouverture2[nComposante],sSymbole[2*(nComposante+1<nComposanteEnTout)+bPair(nComposante)]);
				iDelta+=iSignePres(bImpair(nComposante),nCouverture2[nComposante]);
			}
			printf("%s Somme alternée complète: ",sTab(2));
			for (iDelta=0,nComposante=0;nComposante<nComposanteEnTout || !bLigne1(sEnt(iDelta));nComposante++){
				printf("(%d-%d)%c",nCouverture1[nComposante],nCouverture2[nComposante],sSymbole[2*(nComposante+1<nComposanteEnTout)+bPair(nComposante)]);
				iDelta+=iSignePres(bImpair(nComposante),nCouverture1[nComposante]-nCouverture2[nComposante]);
			}
		//te("iDelta FINAL",iDelta);
	//Appel1("iCouvertureDecompteR");
	return(iDelta);
}//iCouvertureDecompteR

void CouvertureDecompterBieN(char *sQuoi,int nGraphType){
	//teste iCouvertureDecompterBieN sur le graphe de type nGraphType
	int iDeterminant,aK,uL,uC,nPivot;
	long yDeterminant,zKomplexiteh;
	int muNeutre=1;
	graf *pgG;
	iMatrice *pmE;
	//Titrer(sC3b("test depuis CouvertureDecompterBieN sur",sItem(sgrNoM,1+nGraphType),sQuoi));
	GrapheCreer1(&pgG,nGraphType,k1Creer);//dont couleurs
		GrapheSymetriser(pgG);
		GrapheVoir0(pgG,sC2b("Graphe",sItem(sgrNoM,1+nGraphType)),grCouleur);
		MatriceAllouer1(&pmE,pgG->nSommetEnTout);
			MatriceDepuisGraphe(pgG,!k1Incidence,&pmE);
				for (aK=1,uL=1;uL<=pmE->nLigne;uL++)
					for (uC=1;uC<=pmE->nColonne;uC++)
						if (uL<uC && pmE->Mat[uL][uC]){
							pmE->Mat[uL][uC]=++aK;
							pmE->Mat[uC][uL]=-pmE->Mat[uL][uC];
						}
				MatriceVoir(sC2b(sItem(sgrNoM,1+nGraphType),"symétrique"),pmE);
				iDeterminant=yMatriceDeterminant(pmE);
				printf("Le déterminant vaut %s.%s(Gauss...).\n",sPar3(iDeterminant),sTab(4));
				if(0){
					yDeterminant=yFormeKalculeR(pmE,0,!k1Voir);//Urbanska simple
					printf("Le déterminant vaut %s.%s(via Urbanska).\n",sPar3(yDeterminant),sTab(4));
					iDeterminant=iFormeCalculeR(pmE);
					printf("Le déterminant vaut %s.%s(via Mahajan et yDagEvaluer).\n",sPar3(iDeterminant),sTab(4));
					iDeterminant=iCouvertureDecompteR(pmE,muNeutre,nPivot=0,!k1Voir,&zKomplexiteh);
					printf("Le nb de couvertures vaut %s.%s(via iCouvertureDecompteR).\n",sPar3(iDeterminant),sTab(4));
					iDeterminant=iCouvertureDecompterBiS(pmE,sItem(sgrNoM,1+nGraphType),muNeutre,nPivot=0,k1Afficher,&zKomplexiteh);
					printf("Le déterminant vaut %s.%s(via Mahajan et noV dimension 2).\n",sPar3(iDeterminant),sTab(4));
					iDeterminant=iCouvertureDecompterBieN(pmE,sItem(sgrNoM,1+nGraphType),muNeutre,nPivot=0,k1Afficher,&zKomplexiteh);
					printf("Le déterminant vaut %s.%s(via iCouvertureDecompterBieN).\n",sPar3(iDeterminant),sTab(4));
				}
			SegmentBanniR(pgG);//AVANT de modifier une qcq couleur
			CouvertureBanniR(pmE);
			iDeterminant=iCouvertureDecompterBiS(pmE,sItem(sgrNoM,1+nGraphType),muNeutre,nPivot=0,!k1Afficher,&zKomplexiteh);
			printf("Le déterminant vaut %s.%s(via iCouvertureDecompterBiS).\n",sPar3(iDeterminant),sTab(4));
		free(pmE);
	GrapheCreer0(&pgG,kF);
}//CouvertureDecompterBieN

int iCouvertureDecompterBieN(iMatrice *pmA,char *sContexte,int muNeutre,int nPivot,int bAfficher,long *pzComplexiteh){//O(S4) calcul compilé ——exact car sans division
	//idem iCouvertureDecompteR mais le tableau local noV mémorise 2 étages et non pas pmA->nLigne étages.
	const int kbModeEco=kF; 
	const int kbStatuer=kF; 
	int bPrefinish;
	int noAvant,noApres,noMatYH,noMatYZ,noNoeudMax,noOperande,noProduit,noUn,noZero,uEtageEnTout;
	int iDelta0,iDelta1,cEtage,nEtage,sH,sX,sY,sZ,cComposante,uSommat;
	int iDeltaPlus,iDeltaMoins,nValide[2],nInvalide[2];
	long zComplexiteh,xComplexitehMax;
	int nCouverture1[2],nCouverture2[2],noPole[2];
	char *sSymbole="==+-";
	int noV[2][1+pmA->nLigne][1+pmA->nLigne][uEtageEnTout=2];
	int noMat[1+pmA->nLigne][1+pmA->nLigne];
	float fRapport;
	int iPoidsMin,iPoidsMax;
	int bPoly=kV;
	//Appel0("iCouvertureDecompterBieN");
		uSommat=pmA->nLigne;
		xComplexitehMax=2*zPuissance(pmA->nLigne,4);//facteur 2 vu la boucle sur cEtage
		Assert3("iCouvertureDecompterBiS2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne,xComplexitehMax>0);
		if (kbStatuer && bAfficher) printf("Le tableau noV contient %s éléments.\n",sPar3(2*(1+uSommat)*(1+uSommat)*2));
		noZero=noPolyAfF(bPoly,0);noUn=noPolyAfF(bPoly,1);
		if (kbModeEco){//Initialiser noMat[][]
			for (sX=1;sX<=uSommat;sX++)
				for (sY=1;sY<=uSommat;sY++)
					noMat[sX][sY]=0;
			for (sX=1;sX<=uSommat;sX++)
				for (sY=1;sY<=uSommat;sY++)
					noMat[sX][sY]=(pmA->Mat[sX][sY]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sX][sY]);
		}
		zComplexiteh=0;
		noPole[0]=noPole[1]=noZero;/*VITAL*/
		//noV[étage 0] soit razé; O(S2)
			for (cComposante=0;cComposante<2;cComposante++)
				for (sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++,zComplexiteh++)
						noV[cComposante][sH][sX][0]=noZero;
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de noV
			for (sH=1;sH<=uSommat;sH++,zComplexiteh++)
				noV[cComposante=0][sH][sH][0]=noUn;
		if (kbStatuer && bAfficher) printf("Complexité initialisation/complexité pire cas: %s / %s = %.4f.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),zComplexiteh/(1.0*xComplexitehMax));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (noNoeudMax=0,nEtage=0;nEtage<=iInf(4,uSommat-2);nEtage++){
				bPrefinish=nEtage==2;
				if (1) {Titrer(sC2b("ETAGE",sEnt(nEtage))); d3(nEtage,uSommat,2-bPrefinish);}
				d(noNoeudMax);
				cEtage=nEtage%2;
				//noV[étage suivant modulo 2] soit razé; O(S2)
					if (1 || !bPrefinish)
						for (cComposante=0;cComposante<2;cComposante++)
							for (sH=1;sH<=uSommat;sH++)
								for (sX=1;sX<=uSommat;sX++,zComplexiteh++)
									noV[cComposante][sH][sX][1-cEtage]=noZero;
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (cComposante=0;cComposante<2;cComposante++)
							for (sZ =sH+1;sZ<=uSommat;sZ++,zComplexiteh++){
								noOperande=noV[cComposante][sH][sY][cEtage];
								noNoeudMax=iSup(noNoeudMax,noOperande);

								if (kbModeEco) noMatYZ=noMat[sY][sZ];
								else noMatYZ=(pmA->Mat[sY][sZ]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sZ]);
								noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYZ);
								noAvant=noV[cComposante][sH][sZ][1-cEtage];
								if (kbModeEco){
									if (noAvant==noZero) noApres=noProduit;
									else if (noProduit==noZero) noApres=noAvant;
									else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								}else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[cComposante][sH][sZ][1-cEtage]=noApres;
								noNoeudMax=iSup(noNoeudMax,iSup(noProduit,noApres));

								Assert1("iCouvertureDecompterBieN 007",noOperande==noV[cComposante][sH][sY][cEtage]);
								if (kbModeEco) noMatYH=noMat[sY][sH];
								else noMatYH=(pmA->Mat[sY][sH]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sH]);
								noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
								if (bPrefinish){
									//t("préfinish");
									noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyDiV(bPoly,noOperande,noMatYH);
								}else noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);

								noAvant=noV[1-cComposante][sZ][sZ][1-cEtage];
								if (kbModeEco){
									if (noAvant==noZero) noApres=noProduit;
									else if (noProduit==noZero) noApres=noAvant;
									else noApres=noPolySuB(bPoly,noAvant,noProduit);
								}else noApres=noPolySuB(bPoly,noAvant,noProduit);
								noV[1-cComposante][sZ][sZ][1-cEtage]=noApres;
								noNoeudMax=iSup(noNoeudMax,iSup(noProduit,noApres));
							}//for sZ
			}
if (kbStatuer) printf("Noeuds consommés hors dernier étage: %s.\n",sPar3(nDagPris()));
		//traiter le dernier étage; O(S2)
			if (0) Titrer("dernier etage");
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					if (kbModeEco) noMatYH=noMat[sY][sH];
					else noMatYH=noPolyAfF(bPoly,pmA->Mat[sY][sH]);
					for (cComposante=0;cComposante<2;cComposante++){
						Assert1("iCouvertureDecompterBieN 412",bCroit(0,(uSommat-1)%2,1) );
						noOperande=noV[cComposante][sH][sY][(uSommat-1)%2];
						noProduit=(noMatYH==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
						noAvant=noPole[cComposante];
						if (kbModeEco){
							if (noAvant==noZero) noApres=noProduit;
							else if (noProduit==noZero) noApres=noAvant;
							else noApres=noPolyAdD(bPoly,noAvant,noProduit);
						}else noApres=noPolyAdD(bPoly,noAvant,noProduit);
						noPole[cComposante]=noApres;
					}
				}
cComposante=1;
if (0 && bPoly && bAfficher) DagArborer(sC4("Composante n°",sEnt(cComposante)," AVANT SIMPLIFICATION pour ",sContexte),noPole[cComposante],0);
		//te("zComplexiteh Mahajan",zComplexiteh);
		fRapport=zComplexiteh/(1.0*xComplexitehMax);
		if (kbStatuer) printf("Complexité TOTALE Mahajan /complexité pire cas: %s / %s = %.2f.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),fRapport);
		if (kbStatuer) printf("Noeud consommés en tout: %s.\n",sPar3(nDagPris()));
		if (kbStatuer) Titrer("COMPOSANTES");
		//simplifier les DAGs en éliminant les feuilles de valeur 0 ou 1 qui sont superflues.
if (0 && bAfficher) DagInvalideAfficher();
//t("DagSimplifier");
		if(bPoly)
			for (cComposante=0;cComposante<2;cComposante++){
				DagSimplifier(cComposante,noPole[cComposante],muNeutre,kF);//NB: DagSimplifier ne modifie pas la valeur de nDagPris().
				if (cComposante<=1 && bAfficher)
					DagArborer(sC4("Composante n°",sEnt(cComposante)," APRÈS SIMPLIFICATION pour ",sContexte),noPole[cComposante],0);
			}
		//inventorier les couvertures décrites dans les DAGs, les stocker dans nCouverture1[] et nCouverture2[], et afficher la somme alternée.
			VecteurRazer(nCouverture1,0,1);
			VecteurRazer(nCouverture2,0,1);
			if (0 && bPoly){
				//t("DagCouvrir0");
				for (zComplexiteh=0,cComposante=0;cComposante<2;cComposante++)
					DagCouvrir(1+cComposante,noPole[cComposante],nPivot,&nCouverture1[cComposante],&nCouverture2[cComposante],&zComplexiteh);
				//t("DagCouvrir1");
				for (iDelta1=0,cComposante=0;cComposante<2;cComposante++)
					iDelta1+=iSignePres(bImpair(cComposante),nCouverture2[cComposante]);
				Titrer(sC4("iCouvertureDecompterBieN avec ",sPluriel(nPivot,"pivot"),":   ",sPluriel(abs(iDelta1),"chemin")));
			}
			fRapport=zComplexiteh/(1.0*xComplexitehMax);
			if (kbStatuer) printf("zComplexiteh TOTALE vs 2S4: %ld/%ld=%.2f.\n",zComplexiteh,xComplexitehMax,fRapport);
			if (1) {
				if (0 && bAfficher) printf("ÉNUMÉRATION EXHAUSTIVE DES SOLUTIONS ATTENDUES pour %s en cours...\n",sContexte);
					MatriceMarner(pmA,&iPoidsMin,&iPoidsMax);
					for (iDeltaPlus=iDeltaMoins=0,cComposante=0;cComposante<2;cComposante++)
						zDagEnumerer(1+cComposante,k1Afficher,pmA->nLigne,noPole[cComposante],!k1Tout,iPoidsMin,iPoidsMax,&nValide[cComposante],&nInvalide[cComposante]);
				if (0 && bAfficher) printf("ÉNUMÉRATION EXHAUSTIVE DES SOLUTIONS ATTENDUES pour %s terminée.\n",sContexte);
				if (0 && bAfficher) printf("COUVERTURES ATTENDUES:  ");
					if (0 && bAfficher) for (printf("n° Dag    Acceptées    Refusées    Total\n"),cComposante=0;cComposante<2;cComposante++)
						printf("%s%8d  %10s %12s %10s\n",sTab(5),1+cComposante,sPar3(nValide[cComposante]),sPar3(nInvalide[cComposante]),sPar3(nValide[cComposante]+nInvalide[cComposante]));
					if (0 && bAfficher) for (printf("COUVERTURES ACCEPTÉES ATTENDUES: "),iDelta0=0,cComposante=0;cComposante<2 || (printf("%d.\n",iDelta0),0);cComposante++){
						printf("%s%c",sPar3(nValide[cComposante]),sSymbole[2*(cComposante+1<2)+bPair(cComposante)]);
						iDelta0+=iSignePres(bImpair(cComposante),nValide[cComposante]);
					}
			}
			if (0 && bAfficher){
				printf("COUVERTURES CALCULÉES: ");
				for (printf("Dag       Acceptées    Refusées      Total\n"),cComposante=0;cComposante<2;cComposante++)
printf("%s%s %s %s %s\n",sTab(5),sEntier1(1+cComposante,10),sEntier1(nCouverture1[cComposante],12),sEntier1(nCouverture2[cComposante],12),sEntier1(nCouverture1[cComposante]+nCouverture2[cComposante],12));
				for (printf("COUVERTURES ACCEPTÉES CALCULÉES: "),cComposante=0;cComposante<2 || (printf("%d.\n",iDelta1),0);cComposante++)
					printf("%d%c",nCouverture2[cComposante],sSymbole[2*(cComposante+1<2)+bPair(cComposante)]);
				Titrer2(sC2b("Les deux calculs de couverture",sDire(iDelta0==iDelta1,"sont équivalents")),(iDelta0==iDelta1)?'*': '@');
			}
			//Assert1("iCouvertureDecompterBieN Conclusion",iDelta0==iDelta1);
	//Appel1("iCouvertureDecompterBieN");
	iDelta1=yDagEvaluer(noPole[1],0)-yDagEvaluer(noPole[0],0);
	return(iDelta1);
}//iCouvertureDecompterBieN

int iCouvertureDecompterBiS(iMatrice *pmA,char *sContexte,int muNeutre,int nPivot,int bAfficher,long *pzComplexiteh){//O(S4) calcul compilé ——exact car sans division
	//iCouvertureDecompteR optimsé en espace: le tableau local noV mémorise 2 étages et non pas pmA->nLigne étages.
	const int kbDroite=kV;
	const int kbModeEco=kV; 
	const int kbStatuer=kV; 
	int noAvant,noApres,noMatYH,noMatYZ,noOperande,noProduit,noUn,noZero,uEtageEnTout,bUn;
	int iDelta0,iDelta1=999999999,cEtage,nEtage,sH,sX,sY,sZ,cComposante,uSommat;
	int iDeltaPlus,iDeltaMoins,nValide[2],nInvalide[2];
	long zComplexiteh,xComplexitehMax;
	int nCouverture1[2],nCouverture2[2],noPole[2];
	char *sSymbole="==+-";
	int noV[2][1+pmA->nLigne][1+pmA->nLigne][uEtageEnTout=2];
	int noMat[1+pmA->nLigne][1+pmA->nLigne];
	float fRapport;
	int iPoidsMin,iPoidsMax;
	int bPoly=kV;
	//Appel0("iCouvertureDecompterBiS");
		uSommat=pmA->nLigne;
		xComplexitehMax=2*zPuissance(pmA->nLigne,4);//facteur 2 vu la boucle sur cEtage
		Assert3("iCouvertureDecompterBiS2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne,xComplexitehMax>0);
		if (kbStatuer) printf("Le tableau noV contient %s éléments.\n",sPar3(2*(1+uSommat)*(1+uSommat)*2));
		noZero=noPolyAfF(bPoly,0);noUn=noPolyAfF(bPoly,1);
		if (kbModeEco){//Initialiser noMat[][]
			for (sX=1;sX<=uSommat;sX++)
				for (sY=1;sY<=uSommat;sY++)
					noMat[sX][sY]=0;
			for (sX=1;sX<=uSommat;sX++)
				for (sY=1;sY<=uSommat;sY++)
					noMat[sX][sY]=(pmA->Mat[sX][sY])? noPolyAfF(bPoly,pmA->Mat[sX][sY]): noZero;
		}
		zComplexiteh=0;
		noPole[0]=noPole[1]=noZero;/*VITAL*/
		//noV[étage 0] soit razé; O(S2)
			for (cComposante=0;cComposante<2;cComposante++)
				for (sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++,zComplexiteh++)
						noV[cComposante][sH][sX][0]=noZero;
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de noV
			for (sH=1;sH<=uSommat;sH++,zComplexiteh++)
				noV[cComposante=0][sH][sH][0]=noUn;
		if (kbStatuer) printf("Complexité initialisation/complexité pire cas: %s / %s = %.4f.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),zComplexiteh/(1.0*xComplexitehMax));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (0) {Titrer(sC2b("ETAGE",sEnt(nEtage))); tee("nEtage,uSommat",nEtage,uSommat);}
				cEtage=nEtage%2;
				//noV[étage suivant modulo 2] soit razé; O(S2)
					for (cComposante=0;cComposante<2;cComposante++)
						for (sH=1;sH<=uSommat;sH++)
							for (sX=1;sX<=uSommat;sX++,zComplexiteh++)
								noV[cComposante][sH][sX][1-cEtage]=noZero;
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (cComposante=0;cComposante<2;cComposante++)
							for (sZ =sH+1;sZ<=uSommat;sZ++,zComplexiteh++){
								noOperande=noV[cComposante][sH][sY][cEtage];
								if (kbModeEco) noMatYZ=noMat[sY][sZ];
								else noMatYZ=(pmA->Mat[sY][sZ]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sZ]);
								if (kbDroite) noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYZ);
								else noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noMatYZ,noOperande);
								noAvant=noV[cComposante][sH][sZ][1-cEtage];
								if (kbModeEco){
									if (noAvant==noZero) noApres=noProduit;
									else if (noProduit==noZero) noApres=noAvant;
									else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								}else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[cComposante][sH][sZ][1-cEtage]=noApres;
								if (kbModeEco) noMatYH=noMat[sY][sH];
								else noMatYH=(pmA->Mat[sY][sH])? noPolyAfF(bPoly,pmA->Mat[sY][sH]): noZero;
								noOperande=noV[cComposante][sH][sY][cEtage];
								if (kbDroite) noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
								else noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noMatYH,noOperande);
								noAvant=noV[1-cComposante][sZ][sZ][1-cEtage];
								if (kbModeEco){
									if (noAvant==noZero) noApres=noProduit;
									else if (noProduit==noZero) noApres=noAvant;
									else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								}else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[1-cComposante][sZ][sZ][1-cEtage]=noApres;
							}//for sZ
			}
if (kbStatuer) printf("Noeuds consommés hors dernier étage: %s.\n",sPar3(nDagPris()));
		//traiter le dernier étage; O(S2)
			if (0) Titrer("dernier etage");
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					if (kbModeEco) noMatYH=noMat[sY][sH];
					else noMatYH=noPolyAfF(bPoly,pmA->Mat[sY][sH]);
					for (cComposante=0;cComposante<2;cComposante++){
						Assert1("iCouvertureDecompterBiS 412",bCroit(0,(uSommat-1)%2,1) );
						noOperande=noV[cComposante][sH][sY][(uSommat-1)%2];
						if (kbDroite) noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
						else noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noMatYH,noOperande);
						noAvant=noPole[cComposante];
						noApres=(noProduit==noZero)? noAvant: noPolyAdD(bPoly,noAvant,noProduit);
						noPole[cComposante]=noApres;
					}
				}
		//te("zComplexiteh Mahajan",zComplexiteh);
		fRapport=zComplexiteh/(1.0*xComplexitehMax);
		if (kbStatuer) printf("Complexité TOTALE Mahajan /complexité pire cas: %s / %s = %.2f.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),fRapport);
		if (kbStatuer) printf("Noeud consommés en tout: %s.\n",sPar3(nDagPris()));
		if (kbStatuer) Titrer("COMPOSANTES");
		//simplifier les DAGs en éliminant les feuilles de valeur 0 ou 1 qui sont superflues.
DagInvalideAfficher();
tt("DagSimplifier",sG(sContexte));
			for (cComposante=0;cComposante<2;cComposante++){
				//DagArborer(sC4("Composante n°",sEnt(cComposante)," AVANT SIMPLIFICATION pour ",sContexte),noPole[cComposante]);
				DagSimplifier(cComposante,noPole[cComposante],muNeutre,kF);//NB: DagSimplifier ne modifie pas la valeur de nDagPris().
				if (1 && cComposante==1)
					DagArborer(sC4("Composante n°",sEnt(cComposante)," APRÈS SIMPLIFICATION pour ",sContexte),noPole[cComposante],0);
			}
	t("simplification terminée");
	//nBof=nNoeudCouplage(noPole[cComposante=1],k1Droit);
		//inventorier les couvertures décrites dans les DAGs, les stocker dans nCouverture1[] et nCouverture2[], et afficher la somme alternée.
			VecteurRazer(nCouverture1,0,1);
			VecteurRazer(nCouverture2,0,1);
			if (0){
				//t("DagCouvrir0");
				for (zComplexiteh=0,cComposante=0;cComposante<2;cComposante++)
					DagCouvrir(1+cComposante,noPole[cComposante],nPivot,&nCouverture1[cComposante],&nCouverture2[cComposante],&zComplexiteh);
				//t("DagCouvrir1");
				for (iDelta1=0,cComposante=0;cComposante<2;cComposante++)
					iDelta1+=iSignePres(bImpair(cComposante),nCouverture2[cComposante]);
				Titrer(sC4("iCouvertureDecompterBiS avec ",sPluriel(nPivot,"pivot"),":   ",sPluriel(abs(iDelta1),"chemin")));
			}
			fRapport=zComplexiteh/(1.0*xComplexitehMax);
			if (kbStatuer) printf("zComplexiteh TOTALE vs 2S4: %ld/%ld=%.2f.\n",zComplexiteh,xComplexitehMax,fRapport);
			if (0) {
				if (bAfficher) printf("ÉNUMÉRATION EXHAUSTIVE DES SOLUTIONS ATTENDUES %s en cours...\n",sContexte);
					MatriceMarner(pmA,&iPoidsMin,&iPoidsMax);
					for (iDeltaPlus=iDeltaMoins=0,cComposante=0;cComposante<2;cComposante++)
						zDagEnumerer(1+cComposante,k1Afficher,pmA->nLigne,noPole[cComposante],!k1Tout,iPoidsMin,iPoidsMax,&nValide[cComposante],&nInvalide[cComposante]);
				if (bAfficher) printf("ÉNUMÉRATION EXHAUSTIVE DES SOLUTIONS ATTENDUES %s terminée.\n",sContexte);
				if (bAfficher) printf("COUVERTURES ATTENDUES:  ");
					if (bAfficher) for (printf("n° Dag    Acceptées    Refusées    Total\n"),cComposante=0;cComposante<2;cComposante++)
						printf("%s%8d  %10s %12s %10s\n",sTab(5),1+cComposante,sPar3(nValide[cComposante]),sPar3(nInvalide[cComposante]),sPar3(nValide[cComposante]+nInvalide[cComposante]));
					if (bAfficher) for (printf("COUVERTURES ACCEPTÉES ATTENDUES: "),iDelta0=0,cComposante=0;cComposante<2 || (printf("%d.\n",iDelta0),0);cComposante++){
						printf("%s%c",sPar3(nValide[cComposante]),sSymbole[2*(cComposante+1<2)+bPair(cComposante)]);
						iDelta0+=iSignePres(bImpair(cComposante),nValide[cComposante]);
					}
			}
			if (0 && bAfficher){
				printf("COUVERTURES CALCULÉES: ");
				for (printf("Dag       Acceptées    Refusées      Total\n"),cComposante=0;cComposante<2;cComposante++)
printf("%s%s %s %s %s\n",sTab(5),sEntier1(1+cComposante,10),sEntier1(nCouverture1[cComposante],12),sEntier1(nCouverture2[cComposante],12),sEntier1(nCouverture1[cComposante]+nCouverture2[cComposante],12));
				for (printf("COUVERTURES ACCEPTÉES CALCULÉES: "),cComposante=0;cComposante<2 || (printf("%d.\n",iDelta1),0);cComposante++)
					printf("%d%c",nCouverture2[cComposante],sSymbole[2*(cComposante+1<2)+bPair(cComposante)]);
				Titrer2(sC2b("Les deux calculs de couverture",sDire(iDelta0==iDelta1,"sont équivalents")),(iDelta0==iDelta1)?'*': '@');
			}
			//Assert1("iCouvertureDecompterBiS Conclusion",iDelta0==iDelta1);
	//Appel1("iCouvertureDecompterBiS");
	bUn=1;
	iDelta1=yDagEvaluer(noPole[0],bUn)-yDagEvaluer(noPole[1],bUn);
	d(iDelta1);
	return(abs(iDelta1));
}//iCouvertureDecompterBiS

/*
	Chaque couverture a 7 CC commençant respectivt par 1,3,4,5,6,7 et 8. 
	Détecter la redondance  3  44 *21* 22   4  45 *21* 23 est facile vu localité.
	Détecter la redondance  -26-   -26- est difficile-.
C[7,1]=   1   2  *9* 11 -26- 30  40  41   3  43  *9* 10   4  45  21  23   5  47  13  14   6  49 -26- 28   7  51  17  18   8  53  31  33 ECHEC (doublets:2,distmin:8) .
C[7,4]=   1   2   9  11 -26- 30  40  41   3  44  21  22   4  46  36  37   5  47  13  14   6  49 -26- 28   7  51  17  18   8  53  31  33 ECHEC (doublets:1,distmin:18) .
C[7,2]=   1   2   9  11 -26- 30  40  41   3  44 *21* 22   4  45 *21* 23   5  47  13  14   6  49 -26- 28   7  51  17  18   8  53  31  33 ECHEC (doublets:2,distmin:4) .

C[7,3]=   1   2  *9* 11 -26- 30  40  41   3  43  *9* 10   4  46  36  37   5  47  13  14   6  49 -26- 28   7  51  17  18   8  53  31  33 ECHEC (doublets:2,distmin:8) .
*/
//	int noV[16][58][58][58];
long yCouvertureDecompterTeR(iMatrice *pmA,int nSommetDeBase,int iNeutre,int bOptimum,int nPeriode,int bAfficher,int *pnCouverture,long* pyDeterminant,long *pzComplexiteh){//O(S5)
	//variante lente de iCouvertureDecompteR où le tableau local noV contient 2 étages et 1+nSommetDeBase*(nSommetDeBase-1) composantes. 
	const int kbDroite=kF;
	const int kdEtageEnTout=2;
	const int kbInformer=kF;
	const int kbSenteExhiber=kV;
	int noMatYH,noMatYZ,noOperande,bPerte,noProduit,noUn,noZero,nOptimum=0;
	int nSenteLg=1+2*nSommetDeBase;
	int nComposante,nComposante0,uComposante,nComposanteApres,nDuree,cEtage,sEtage,nEtage,nExclu,nInclus,iPoidsMin,iPoidsMax,uSommat,sH,sX,sY,sZ;
	long zComplexiteh=0,xComplexitehMax,yDelta,yDeltaImpair;
	int uComposanteEnTout=1+nSommetDeBase*(nSommetDeBase-0);
	//int uComposanteEnTout=pmA->nLigne/2;//valeur maximale obtenue avec une couverture de cycles de longueur 2
	//d2(1+uComposanteEnTout,1+pmA->nLigne);
	long yValeur[2+uComposanteEnTout];
	long zEnumerer[2+uComposanteEnTout];
	int iSente[1+1+2*nSommetDeBase];
	int noPole[2+uComposanteEnTout];
	int noMat[1+pmA->nLigne][1+pmA->nLigne];
	int noTam[1+pmA->nLigne][1+pmA->nLigne];
	int noV[1+uComposanteEnTout][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	float fRapport;
	int bPoly=kV;
	//Appel0("yCouvertureDecompterTeR");
		uSommat=pmA->nLigne;
		if (kbInformer) d(nSommetDeBase);
		xComplexitehMax=uComposanteEnTout*zPuissance(uSommat,4);
		if (0 || kbInformer) d3(uSommat,uComposanteEnTout,xComplexitehMax);
		Assert4("yCouvertureDecompterTeR 2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne,xComplexitehMax>0,bBool(bOptimum));
		Assert1("yCouvertureDecompterTeR donnée impropre",!bMatriceContient(pmA,iNeutre));//iNeutre est l'élément neutre de la multiplication
		if (kbInformer) printf("Le tableau noV mémorise %s éléments pour la matrice de dimension %s.\n",sPar3(uComposanteEnTout*uSommat*uSommat*kdEtageEnTout),sPar3(uSommat));
		nDuree=nChrono(kV);
			noZero=noPolyAfF(bPoly,0);noUn=noPolyAfF(bPoly,iNeutre);//O(2)
			if (kbInformer) d3(noZero,noUn,iNeutre);
			VecteurRazer(noPole,1,uComposanteEnTout+1);
			VecteurInitialiser(noPole,1,uComposanteEnTout,noZero);//O(uComposanteEnTout);VITAL
			//VecteurVoir1("noPole initialisé",noPole,1,uComposanteEnTout+1);
			noPole[0]=uComposanteEnTout;
			if (kbInformer) printf("Complexité courante %s. Ratio de complexité = %.2f.\n",sPar3(zComplexiteh),zComplexiteh/(1.0*xComplexitehMax));
			//noMat[][] soit initialisé ——hors bOptimum,noMat est utilisé,ce qui réduit le nombre de noeuds consommés,cf nDagPris().
				for (sX=1;sX<=uSommat;sX++)
					for (sY=1;sY<=uSommat;sY++)//coût total pour noMat si les aK sont distincts: noZero + noUn+ nombre d'aK.
						noMat[sX][sY]=(pmA->Mat[sX][sY])? noPolyAfF(bPoly,pmA->Mat[sX][sY]): noZero;
			//noTam[][] soit initialisé ——hors bOptimum,noMat est utilisé,ce qui réduit le nombre de noeuds consommés,cf nDagPris().
				for (sX=1;sX<=uSommat;sX++)
					for (sY=1;sY<=uSommat;sY++)//coût total pour noMat si les aK sont distincts: noZero + noUn+ nombre d'aK.
						noTam[sX][sY]=(pmA->Mat[sX][sY])? noPolyAfF(bPoly,- pmA->Mat[sX][sY]): noZero;
			//noV[étage soit razé; O(uComposanteEnTout*S2)
				for (nComposante=0;nComposante<=uComposanteEnTout;nComposante++)
					for (sH=1;sH<=uSommat;sH++)
						for (sX=1;sX<=uSommat;sX++,zComplexiteh++)
							for (nEtage=0;nEtage<=uSommat-1;nEtage++)//O(uComposanteEnTout*S4)
								noV[nComposante][sH][sX][nEtage]=noZero;
			//noV[]:=noUn pour tous les heads ——caractérisés par (sH,sH)—— du seul étage 0 de noV
				for (nEtage=0,sH=1;sH<=uSommat;sH++)
					noV[nComposante=0][sH][sH][nEtage]=noUn;
//d(nDagPris());//2+nb éléments non nuls de la matrice
			//calculer les dags 
				for (nComposante=0;nComposante<uComposanteEnTout;nComposante++)
					for (nEtage=0;nEtage<=uSommat-2;nEtage++){//O(uComposanteEnTout*S4)
						if (kbInformer)  Titrer(sC4b("ETAGE",sEnt(nEtage),"pour le graphe étagé à",sPluriel(nSommetDeBase,"sommet")));
						sEtage=nEtage;//étage source (dédié lecture de l'opérande)
						cEtage=nEtage+1;//étage cible (en écriture seule)
						for (sH=1;sH<=uSommat;sH++)//O(uComposanteEnTout*S3); sH: sommet de + petit rang d'un parcours fermé;cf sClowHead
							for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
								noOperande=noV[nComposante][sH][sY][sEtage];
								for (sZ=sH+1;sZ<=uSommat;sZ++,zComplexiteh++){//affecter l'étage cible cEtage
									Assert1("yCouvertureDecompterTeR 278",noOperande>0);
									//noMatYZ = (nComposante+1==uComposanteEnTout)? noTam[sY][sZ]: noMat[sY][sZ];
									noMatYZ = noMat[sY][sZ];
									noProduit=(abs(noMatYZ)==noZero || abs(noOperande)==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYZ);
									if (noProduit!=noZero){
										noV[nComposante][sH][sZ][cEtage]=noPolyAdD(bPoly,noV[nComposante][sH][sZ][cEtage],noProduit);
									}
									if (1+nComposante<uComposanteEnTout){
										noMatYH=noMat[sY][sH];
										if (kbDroite)
											noProduit=(noMatYH==noZero || abs(noOperande)==noZero)? noZero: noPolyDiV(bPoly,noMatYH,abs(noOperande));
										else noProduit=(noMatYH==noZero || abs(noOperande)==noZero)? noZero: noPolyDiV(bPoly,abs(noOperande),noMatYH);
										if (noProduit!=noZero)
											if (nComposante<uComposanteEnTout-2)
												noV[1+nComposante][sZ][sZ][cEtage]= noPolyAdD(bPoly,noV[1+nComposante][sZ][sZ][cEtage],noProduit);
					else noV[1+nComposante][sZ][sZ][cEtage]= noPolySuB(bPoly,noV[1+nComposante][sZ][sZ][cEtage],noProduit);
									}
								}//for sZ
							}//for (sY
					}//for nEtage
//printf("Noeuds pris/Noeuds max= %s / %s = %.3f.\n",sPar3(nDagPris()),sPar3(xComplexitehMax),nDagPris()/(1.0*xComplexitehMax));
				//traiter le dernier étage; O(uComposanteEnTout*S2)
					if (kbInformer) Titrer("dernier étage");
					for (nEtage=uSommat-1,nComposante=0;nComposante<uComposanteEnTout;nComposante++)
						for (sH=1;sH<=uSommat;sH++)// sH: sommet de + petit rang d'un parcours fermé;cf sClowHead
							for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
								//noMatYH = (nComposante+1==uComposanteEnTout)? noTam[sY][sH]: noMat[sY][sH];
								noMatYH = noMat[sY][sH];
								noOperande=noV[nComposante][sH][sY][nEtage];
								noProduit=(noMatYH==noZero || abs(noOperande)==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
								if (noProduit!=noZero)
									noPole[1+nComposante]=noPolyAdD(bPoly,noPole[1+nComposante],noProduit);
							}//for (sY
		nDuree=nChrono(kF);
		if (kbInformer) printf("Temps pour exécuter le noyau de yCouvertureDecompterTeR: %s.\n",sPluriel(nDuree,"unité"));
		if (kbInformer) d(nDagPris());
		//te("zComplexiteh Mahajan",zComplexiteh);
		fRapport=zComplexiteh/(1.0*xComplexitehMax);
if (kbInformer) printf("Ratio de complexité et coût en noeuds: %s / %s = %.2f pour %s.\n",sPar3(zComplexiteh),sPar3(xComplexitehMax),fRapport,sPluriel(nDagPris(),"noeud"));
		if (kbInformer) d(uComposanteEnTout);
		if (kbInformer)  VecteurVoir1("noPole AVANT",noPole,1,1+uComposanteEnTout);
		//if (nSommetDeBase<=-2) for (uComposante=1;uComposante<=uComposanteEnTout;uComposante++)
		//	DagArborer(sC2("Composante n°",sEnt(uComposante)),noPole[uComposante]);
		if (kbInformer) d(nDagPris());
		//DagRecuperer(noPole);
		//simplifier les DAGs en éliminant les feuilles de valeur noZero ou noUn superflues et réduire par là uComposanteEnTout

		//DagArborer(sC2("Composante n°",sEnt(uComposanteEnTout)),noPole[uComposanteEnTout]);

			if (1 && bPoly){
				//printf("uComposanteEnTout AVANT SIMPLIFICATION: %d.\n",uComposanteEnTout);
		//VecteurVoir1("noPole avant écourter",noPole,1,1+uComposanteEnTout);
					for (uComposante=1;uComposante<=uComposanteEnTout;uComposante++)
						DagSimplifier(uComposante,noPole[uComposante],iNeutre,kF);// $
		//d2(uComposanteEnTout,uComposanteEnTout);
		VecteurVoir1("noPole APRES DagSimplifier",noPole,1,1+uComposanteEnTout);
					for (nComposanteApres=0,uComposante=uComposanteEnTout;uComposante && !nComposanteApres;uComposante--)
						if ( !bDagNul(noPole[uComposante]) )
							nComposanteApres=uComposante;//mémorise rang1 dernière composante utile puis écourte itération
					if (kbInformer) printf("Nombre de composantes AVANT vs APRES simplification: %d vs %d.\n",uComposanteEnTout,nComposanteApres);
					uComposanteEnTout=nComposanteApres;
			}


		if (0) for (uComposante=uComposanteEnTout;uComposante<=uComposanteEnTout;uComposante++)
			DagArborer(sC2("Composante n°",sEnt(uComposante)),noPole[uComposante],nPeriode);

			if (1){//printf("évaluation");
				for (uComposante=1;uComposante<=uComposanteEnTout;uComposante++)
					yValeur[uComposante]=yDagEvaluer(noPole[uComposante],k1Un);
				for (yDelta=0,uComposante=1;uComposante<=uComposanteEnTout;uComposante++)
					yDelta+=ySignePres(bPair(uComposante),yValeur[uComposante]);// $
				//Assert1("yCouvertureDecompterTeR0269",yDelta>=0);
				for (yDeltaImpair=0,uComposante=1;uComposante<=uComposanteEnTout;uComposante+=2)
					yDeltaImpair+=yValeur[uComposante];
				zBof=yDeltaImpair%27;
				yBof=yDeltaImpair%256;
				//d4(yDelta,yDeltaImpair,zBof,yBof);
			}
		bPerte=uComposanteEnTout<noPole[0];
		noPole[0]=uComposanteEnTout;
		//DagRecuperer(noPole);
//		d(nDagPris());
		if (kbInformer) VecteurVoir1("noPole APRES",noPole,1,1+uComposanteEnTout);
 		if (1){
			d(uComposanteEnTout);
			//DagArborer(sC2("Composante n°",sEnt(uComposanteEnTout)),noPole[uComposanteEnTout],nPeriode);
			//DagArborer(sC2("Composante n°",sEnt(1)),noPole[1],nPeriode);
			if (kbInformer) VecteurVoir0("noPole",noPole);
		}
		//if (bPerte) Titrer(sC2b("PERTE pour le graphe étagé à ",sPluriel(nSommetDeBase,"sommet")));
		nOptimum=0;
		bOptimum=1;
		if(0 && bOptimum && uComposanteEnTout>0){
			if (1){//énumérer les couvertures de la dernère composante ——ATTENTION: O(exponentiel)
				MatriceMarner(pmA,&iPoidsMin,&iPoidsMax);//d(uComposanteEnTout);printf("Couvertures énumérées par composante:\n");
				//*pnCouverture=zDagEnumerer(uComposanteEnTout,k1Afficher,pmA->nLigne,noPole[uComposanteEnTout],k1Elementaire,iPoidsMin,iPoidsMax,&nInclus,&nExclu);
//d(*pnCouverture);
			}
			//DagArborer(sC2("Composante n°",sEnt(uComposanteEnTout-1)),noPole[uComposanteEnTout],nPeriode);
			//MatriceMarner(pmA,&iPoidsMin,&iPoidsMax);//d(uComposanteEnTout);printf("Couvertures énumérées par composante:\n");
			nComposante0=(kF)? 1: uComposanteEnTout;// $
m6;
			for (uComposante=nComposante0;uComposante<=uComposanteEnTout;uComposante++)
				zEnumerer[uComposante]=zDagEnumerer(uComposante,!k1Afficher,pmA->nLigne,noPole[uComposante],!k1Elementaire,iPoidsMin,iPoidsMax,&nInclus,&nExclu);
m7;
			if (nComposante0<uComposanteEnTout)
				VekteurVoir1("zEnumerer",zEnumerer,nComposante0,uComposanteEnTout);
			iSente[0]=(kbSenteExhiber)? nSenteLg: 0;
			//nOptimum=nDagOptimum(uComposanteEnTout-1,noPole[uComposanteEnTout],pmA->nLigne-nSenteLg,iSente);
			//VecteurVoir0("iSente",iSente);
		} else if (uComposanteEnTout>0)
			nOptimum=!bDagNul(noPole[uComposanteEnTout]);
		//yDelta=( uComposanteEnTout>0 && !bDagNul(noPole[uComposanteEnTout]) )? nOptimum: 0;
//d(nRac(yDelta));
	//Appel1("yCouvertureDecompterTeR");
	return(yDelta);
}//yCouvertureDecompterTeR

/*
Composante n°3:
+  *  *  *  *  /  *  *  *  /  *  *  *  1
                                       2
                                    9
                                 11
                              18
                           4
                        6
                     17
                  15
               7
            8
         14
      13
   *  *  *  *  +  /  *  *  *  /  *  *  *  1
                                          2
                                       9
                                    11
                                 18
                              4
                           6
                        17
                     15
                  /  *  *  *  /  *  *  *  1
                                          2
                                       9
                                    11
                                 18
                              7
                           8
                        14
                     13
               9
            10
         17
      16


+  *  *  *  *  /  15
                  *  *  *  /  18
                              *  *  *  1
                                       2
                                    9
                                 11
                           4
                        6
                     17
               7
            8
         14
      13
   *  *  *  *  +  /  15
                     *  *  *  /  18
                                 *  *  *  1
                                          2
                                       9
                                    11
                              4
                           6
                        17
                  /  13
                     *  *  *  /  18
                                 *  *  *  1
                                          2
                                       9
                                    11
                              7
                           8
                        14
               9
            10
         17
      16


*/
void CouvertureFormeR(int uPivot,graf *pgG,graf **ppgH){
	//remplace tout sommet de pgG par une longrine
	const int kuCouleurForte=1;
	const int bVoir=kF;
	int nQuadripole,aK,sX,sY,uP,nQ;
	int nSommat=pgG->nSommetEnTout;
	int nSommetApres=uPivot+4*pgG->nArcEnTout;//avant symétrisation
	int szPred[1+nSommat];
	GrapheSymetriser(pgG);
	if (bVoir) GrapheVoir(pgG,sC2b("pgG symétrisé pour",sPluriel(uPivot,"pivot")));
		if (bVoir) te("nSommetApres",nSommetApres);
		GrapheCreer(-nSommetApres,ppgH);
		VecteurRazer(szPred,1,nSommat);//szPred[sX] mémorise les extrémités des circuits du futur graphe
		//connecter (liens externes) les quadripôles
			for (nQuadripole=0,sX=1;sX<=nSommat;sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					if (sX<sY){
						if (bVoir) printf("         Arc rencontré: %s.\n",sCouple(sX,sY));
						if (szPred[sX]==0){
							for (uP=1;uP<=uPivot;uP++)
								GrapheArquer1(*ppgH,uP,uPivot+4*nQuadripole+1,kuCouleurForte);
						} else GrapheArquer1(*ppgH,szPred[sX],uPivot+4*nQuadripole+1,kuCouleurForte);
						szPred[sX]=uPivot+4*nQuadripole+3;
						
						if (szPred[sY]==0){
							for (uP=1;uP<=uPivot;uP++)
								GrapheArquer1(*ppgH,uP,uPivot+4*nQuadripole+2,kuCouleurForte);
						}else GrapheArquer1(*ppgH,szPred[sY],uPivot+4*nQuadripole+2,kuCouleurForte);
						szPred[sY]=uPivot+4*nQuadripole+4;
						nQuadripole++;
					}
				}
			if (bVoir) printf("Nombre total de quadripoles générés: %d.\n",nQuadripole);
			for (sX=1;sX<=nSommat;sX++)
				for (uP=1;uP<=uPivot;uP++)
					GrapheArquer1(*ppgH,szPred[sX],uP,kuCouleurForte);
	if (0) 
		for (aK=1;aK<=(*ppgH)->nArcEnTout;aK++)
			if ( (*ppgH)->coulh[aK]==kuCouleurForte )
				(*ppgH)->coulh[aK]=aK;
	if (bVoir) GrapheVoir(*ppgH,"ppgH creux,ie sans longrine");
		//remplacer chaque quadripôle par une longrine
			for (nQ=0;nQ<nQuadripole;nQ++)
				CouvertureLongrinerUnQuadripolE(uPivot+4*nQ+1,uPivot+4*nQ+2,uPivot+4*nQ+3,uPivot+4*nQ+4,*ppgH);
	if (bVoir) GrapheVoir(*ppgH,"ppgH FINAL longriné");
}//CouvertureFormeR

void CouvertureLongrinerUnQuadripolE(int sA,int sB,int sC,int sD,graf *pgG){
	//remplace le quadripole (sA,sB,sC,sD) de pgG par la longrine ksLongrine (conserve les sommets du quadripôle).
	const int kuCoinNb=4;
	const int kbVoir=kF;
	graf *pgH;
	int nCouleur,nSommat;
	int aK,sU,sV,sX,sY;
	int sCoin[1+4]={-1,sA,sB,sC,sD};
	char ksLongrine[]="AE2BF2CH3DG5EB8EG9FA7FH9GC6HD4";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
	Assert5("CouvertureLongrineR0",bGrapheSommet(pgG,sA),bGrapheSommet(pgG,sB),bGrapheSommet(pgG,sC),bGrapheSommet(pgG,sD),bDistinct4(sA,sB,sC,sD) );
	//te("iLongrine",iLongrine);
	GrapheGenerer(ksLongrine,&pgH);
		//te("uLongrineSommat",uLongrineSommat);
		if (kbVoir) GrapheVoir(pgH,"pgH");
		nSommat=pgG->nSommetEnTout;//avant li+2
		GrapheSommer(pgG,pgH->nSommetEnTout-kuCoinNb);//empile la quantité de sommets fournie en paramètre.
		if (kbVoir) te("pgG->nSommetEnTout après empilt",pgG->nSommetEnTout);
		if (kbVoir) GrapheVoir(pgG,"pgG");
		for (sU=1;sU<=pgH->nSommetEnTout;sU++)
			for (aK=pgH->aHed[sU];aK<pgH->aHed[sU+1];aK++){
				sV=pgH->sSuk[aK];
				nCouleur=pgH->coulh[aK];
				sX=(sU<=kuCoinNb)? sCoin[sU]: nSommat-kuCoinNb+sU;
				sY=(sV<=kuCoinNb)? sCoin[sV]: nSommat-kuCoinNb+sV;
				//teeee("sU,sV,sX,sY",sU,sV,sX,sY);
				Assert3("CouvertureLongrineR6",bGrapheSommet(pgG,sX),bGrapheSommet(pgG,sY),sX!=sY);
				//teee("sX,sY,nCouleur",sX,sY,nCouleur);
				GrapheArquer1(pgG,sX,sY,nCouleur);
			}
		if (0) GrapheVoir1(pgG,k1Couleur,"pgG longriné");
	free(pgH);
}//CouvertureLongrinerUnQuadripolE

void CouvertureBanniR(iMatrice *pmA){
	//transmet au module noeud la liste de tous les segments bannis
	int uB,iK,iL,iM,sX,sY,sZ,sT,bValide;
	int nQuadruplet=nEntierEnTout()/4;//nEntierEnTout() rend la taille de la pile gérée par Outil.c.
	//Appel0("CouvertureBanniR");
		//d(nQuadruplet);
		for (uB=1;uB<=nQuadruplet;uB++){
			EntierDepiler4(&sT,&sZ,&sY,&sX);//oui, ordre inverse puisque pile
			d4(sX,sY,sZ,sT);
			iK=pmA->Mat[sX][sY];
			iL=(sZ!=0)? pmA->Mat[sY][sZ]: 0;
			iM=(sZ!=0 && sT!=0)? pmA->Mat[sZ][sT]: 0;
			bValide=iK!=1 && iL!=1 && iM!=1;
			if (!bValide) printf("Le segment défini par les sommets %d,%d,%d et %d est invalide.\n",sX,sY,sZ,sT);
			DagInvalider(sX,sY,sZ,sT,iK,iL,iM,&nCouvertureBanniR);
		}
	//Appel1("CouvertureBanniR");
}//CouvertureBanniR

long zCouvertureEnTouT(int nSommet,int bElementaire){
	//nb total de couvertures avec répétitions ds la dernière CC
	long xCnp,zCouverture,xPuissance,zChemin;
		if (bElementaire){
			xPuissance=zPuissance(zFact(nSommet-1),nSommet);//boucles
			zChemin=zFact(nSommet-2);
			zCouverture=zChemin*xPuissance;
		}else{
			xPuissance=zPuissance(nSommet-1,nSommet*(nSommet-1));
			xCnp=zCnp(nSommet*nSommet-1,nSommet*(nSommet-1));
			zCouverture=xCnp*xPuissance;
		}
	return(zCouverture);
}//zCouvertureEnTouT

int iCouvertureEstimeR(int nGraphe,int bAfficher,int nCaractereParLibelleh,int nCaractereParResultat){
	//estime toutes les couvertures de graphe obtenues en faisant varier le nombre de pivots.
	int iDeterminant,bPoleBannir,uPivot,nPivotMin=1,nPivotMax;
	int muNeutre=1;
	char *sContexte;
	long zComplexiteh;
	graf *pgG,*pgH;
	iMatrice *pmA;
	//Appel0("iCouvertureEstimeR");
		nCouvertureEstimeR++;
		DagINITIALISER();
		Assert1("iCouvertureEstimeR0",nDagPris()==0);
		// NB NoeudTESTER(1) demande l'affichage de l'arbre du dag n°1 et NoeudTESTER(-3) demande l'énumération des chemins des dags 1 et 2.
		//NoeudTESTER(+1);
		//NoeudTESTER(-1);
	//d(nGraphe);
		//nPivotMax:=nb maximal de pivots
			GrapheCreer1(&pgG,nGraphe,k1Creer);
				nPivotMax=pgG->nSommetEnTout;
			GrapheCreer0(&pgG,!k1Creer);
			//d(nPivotMax);
		//if (1) printf("%40s",sItem(sNom,1+nGraphe));
		if (1) printf("%s",sChaine0(sC3("Solutions pour ",sItem(sgrNoM,1+nGraphe),":"),nCaractereParLibelleh));
nPivotMax=2;
nPivotMin=2;
		for (uPivot=nPivotMin;uPivot<=nPivotMax || !bLigne("\n");uPivot++){
			GrapheCreer1(&pgG,nGraphe,k1Creer);
				//nPivotMax=pgG->nSommetEnTout;
				if (1 && bAfficher)
					GrapheVoir(pgG,sC5b("iCouvertureEstimeR: graphe",sItem(sgrNoM,1+nGraphe),"avec",sPluriel(uPivot,"pivot"),"ci-dessous"));
				FormeLongrineR2(uPivot,pgG,k1Biparti,bPoleBannir=kV,&pgH);
					MatriceAllouer1(&pmA,pgH->nSommetEnTout);
						MatriceDepuisGraphe(pgH,!k1Incidence,&pmA);
						if (1 && bAfficher) MatriceVoir("pmA",pmA);
						CouvertureBanniR(pmA);
						//DagInvalideAfficher();
						sContexte=sC3b(sItem(sgrNoM,1+nGraphe),"avec",sPluriel(uPivot,"pivot"));
						iDeterminant=iCouvertureDecompterBiS(pmA,sContexte,muNeutre,uPivot,0 && bAfficher,&zComplexiteh);//non optimisé
						//d(iDeterminant);
						//printf("%s",sEntier(iDeterminant,nCaractereParResultat));
					free(pmA);
				free(pgH);
			GrapheCreer0(&pgG,!k1Creer);
		}
	//Appel1("iCouvertureEstimeR");
	return(iDeterminant);
}//iCouvertureEstimeR
/*  CouvertureEstimerTouT: tâche en cours...

    Nombre de pivots:        1 pivot    2 pivots   3 pivots   4 pivots  
  Solutions pour grP2:           2x        2x               
  Solutions pour grP3:           1x        6x         6x
  Solutions pour grC3:           0x        6x         6x
  Solutions pour grP4:           0x        6x        24x        24x
  Solutions pour grL4:         0x        4x        24x        24x
  Solutions pour grS3:           1x        6x        24x        24x
  Solutions pour grC4:           0x        4x        24x        24x
  Solutions pour grC4b:          0x        2x        24x        24x
  Solutions pour grK4:           0x        0x        24x        24x
*/
void CouvertureEstimerTouT(){
	//estime toutes les couvertures de graphes listées ds ce code.
	int bAfficher=kV,nGraphe,nPivotMax;
	int iEstime,uPivot;
	graf *pgG;
	const int knLongueur=21;
	const int knCaractereParLibelleh=21;
	int nType[1+8]={grAlpha,grP2,grP3,grC3,grC4,grC4b,grL4,grK4,grOmega};
	Appel0("CouvertureEstimerTouT");
		nCouvertureEstimeR=0;
		//iEstime=iCouvertureEstimeR(grP3,bAfficher);

		if (bAfficher){
			//afficher sur la première ligne du tableau la gamme croissante des pivots utiles dans le pire cas
				//nPivotMax:=nb maximal de pivots
					for (nPivotMax=0,nGraphe=1+grAlpha;nGraphe<grOmega;nGraphe++){
							GrapheCreer1(&pgG,nGraphe,k1Creer);
								nPivotMax=iSup(nPivotMax,pgG->nSommetEnTout);
							GrapheCreer0(&pgG,!k1Creer);
					}
				for (printf("%s",sChaine0("Nombre de pivots:",knCaractereParLibelleh)),uPivot=1;uPivot<=nPivotMax || !bLigne("\n");uPivot++)
					printf("%s%s",sE(10),sChaine2(sPluriel(uPivot,"pivot"),knLongueur-10));
		}
		//estimer le nombre de solutions pour tous les graphes de l'itération et pour tous les pivots utiles au graphe considéré
			if (1) for (nGraphe=nType[1];nType[1];nGraphe++)
				iEstime=iCouvertureEstimeR(nGraphe,1 && bAfficher,knCaractereParLibelleh,knLongueur);
	Appel1("CouvertureEstimerTouT");
}//CouvertureEstimerTouT

/*
Programme en cours...
    CouvertureEstimerTouT: tâche en cours...
    Nombre de pivots:            1 pivot             2 pivots             3 pivots             4 pivots  
 Solutions pour grP2:Le dag n°1 n'a aucune couverture élémentaire.
    C[2, 3]= 17 18 14 11  9  3 19 21 13 10  7  2
    C[2, 5]= 20 21 15 11  9  3 16 18 12 10  7  2
Le dag n°2 a 2 couvertures élémentaires.
iDeterminant=-4.
                   -4
 Solutions pour grP3:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,19]= 30 32 25 20  9 21 19  7 16  6 24 15 13  3 33 36 23 14 11  2
    C[2,65]= 34 36 26 20  9 21 19  7 16  6 24 15 13  3 29 32 22 14 11  2
    C[2,252]= 18  7 31 32 27 21  8 20 17  6 33 36 23 14  5 15 13  3 10  2
    C[2,290]= 18  7 35 36 28 21  8 20 17  6 29 32 22 14  5 15 13  3 10  2
    C[2,330]= 31 32 27 21 19  7 12  3 34 36 26 20 17  6 24 15  4 14 11  2
    C[2,381]= 35 36 28 21 19  7 12  3 30 32 25 20 17  6 24 15  4 14 11  2
Le dag n°2 a 6 couvertures élémentaires.
iDeterminant=-8.
                   -8
 Solutions pour grC3:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,213]= 42 44 37 30 13 31 29 11 26 10 33 19 17  3 45 48 35 24  9 25 23  7 20  6 32 18 15  2
    C[2,734]= 46 48 38 30 13 31 29 11 26 10 33 19 17  3 41 44 34 24  9 25 23  7 20  6 32 18 15  2
    C[2,2855]= 22  7 43 44 39 31 29 11 36 25  8 24 21  6 16  3 46 48 38 30 27 10 33 19  4 18 15  2
    C[2,3273]= 22  7 47 48 40 31 29 11 36 25  8 24 21  6 16  3 42 44 37 30 27 10 33 19  4 18 15  2
    C[2,3722]= 43 44 39 31 12 30 27 10 28 11 36 25 23  7 45 48 35 24 21  6 32 18  5 19 17  3 14  2
    C[2,4256]= 47 48 40 31 12 30 27 10 28 11 36 25 23  7 41 44 34 24 21  6 32 18  5 19 17  3 14  2
Le dag n°2 a 6 couvertures élémentaires.
iDeterminant=8.
                    8
Solutions pour grL4Le dag n°1 n'a aucune couverture élémentaire.
    C[2,114395]= 26  7 56 58 50 40 17 41 39 15 36 14 49 35 33 11 46 29  8 28 25  6 20  3 60 63 48 34 31 10 43 23  4 22 19  2
    C[2,135337]= 26  7 61 63 51 40 17 41 39 15 36 14 49 35 33 11 46 29  8 28 25  6 20  3 55 58 47 34 31 10 43 23  4 22 19  2
    C[2,156230]= 56 58 50 40 17 41 39 15 36 14 49 35 12 34 31 10 32 11 46 29 27  7 59 63 45 28 25  6 42 22  5 23 21  3 18  2
    C[2,177076]= 61 63 51 40 17 41 39 15 36 14 49 35 12 34 31 10 32 11 46 29 27  7 54 58 44 28 25  6 42 22  5 23 21  3 18  2
Le dag n°2 a 4 couvertures élémentaires.
iDeterminant=68.
                   68
 Solutions pour grS3:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,985]= 43 46 33 19 17  3 47 51 39 30 13 31 29 11 26 10 35 24  9 25 23  7 20  6 32 18 15  2
    C[2,3422]= 48 51 34 19 17  3 42 46 38 30 13 31 29 11 26 10 35 24  9 25 23  7 20  6 32 18 15  2
    C[2,13659]= 44 46 36 25 23  7 47 51 39 30 13 31 29 11 26 10 35 24 21  6 32 18  5 19 17  3 14  2
    C[2,15506]= 49 51 37 25 23  7 42 46 38 30 13 31 29 11 26 10 35 24 21  6 32 18  5 19 17  3 14  2
    C[2,28964]= 45 46 40 31 29 11 47 51 39 30 27 10 35 24  9 25 23  7 20  6 32 18  5 19 17  3 14  2
    C[2,31469]= 50 51 41 31 29 11 42 46 38 30 27 10 35 24  9 25 23  7 20  6 32 18  5 19 17  3 14  2
Le dag n°2 a 6 couvertures élémentaires.
iDeterminant=12.
                   12
 Solutions pour grC4:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,101059]= 26  7 56 58 52 41 16 40 37 14 38 15 46 29  8 28 25  6 20  3 60 63 48 34 13 35 33 11 30 10 43 23  4 22 19  2
    C[2,119289]= 26  7 61 63 53 41 16 40 37 14 38 15 46 29  8 28 25  6 20  3 55 58 47 34 13 35 33 11 30 10 43 23  4 22 19  2
    C[2,245570]= 32 11 57 58 50 40 17 41 39 15 36 14 49 35 12 34 31 10 59 63 45 28  9 29 27  7 24  6 42 22  5 23 21  3 18  2
    C[2,261235]= 32 11 62 63 51 40 17 41 39 15 36 14 49 35 12 34 31 10 54 58 44 28  9 29 27  7 24  6 42 22  5 23 21  3 18  2
Le dag n°2 a 4 couvertures élémentaires.
iDeterminant=-24.
                  -24
Solutions pour grC4b:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,1340571]= 30  7 68 70 64 51 20 50 47 18 48 19 61 45 43 15 56 33  8 32 29  6 24  3 72 75 60 44 41 14 57 38 13 39 37 11 34 10 53 27  4 26 23  2
    C[2,1591449]= 30  7 73 75 65 51 20 50 47 18 48 19 61 45 43 15 56 33  8 32 29  6 24  3 67 70 59 44 41 14 57 38 13 39 37 11 34 10 53 27  4 26 23  2
Le dag n°2 a 2 couvertures élémentaires.
iDeterminant=248.

 Solutions pour grP4:Le dag n°1 n'a aucune couverture élémentaire.
    C[2,   8838]= 22  7 44 46 38 30 13 31 29 11 26 10 37 25  8 24 21  6 47 51 33 18  5 19 17  3 14  2
    C[2,  10250]= 22  7 49 51 39 30 13 31 29 11 26 10 37 25  8 24 21  6 42 46 32 18  5 19 17  3 14  2
    C[2,  11574]= 44 46 38 30 13 31 29 11 26 10 37 25 23  7 16  3 48 51 36 24 21  6 34 19  4 18 15  2
    C[2,  13189]= 49 51 39 30 13 31 29 11 26 10 37 25 23  7 16  3 43 46 35 24 21  6 34 19  4 18 15  2
    C[2,  20983]= 28 11 45 46 40 31 12 30 27 10 16  3 48 51 36 24  9 25 23  7 20  6 34 19  4 18 15  2
    C[2,  22439]= 28 11 50 51 41 31 12 30 27 10 16  3 43 46 35 24  9 25 23  7 20  6 34 19  4 18 15  2
Le dag n°2 a 6 couvertures élémentaires.
iDeterminant=-16.
                  -16
*/
void CouvertureTESTER(){
	//décompte les couvertures de graphe.
	int muNeutre=1;
	int aK,nCas,sX,sY;
	char ks0quoi[]="1 papillon unique à 4 sommets";
	char ks0point[]="AC2BD2CB3DA3";
	char ks1quoi[]="1 arc (x,y)=EBFA//CHDG. k=1: paire I-J relié à x et à y";
	char ks1point[]="AE4BF4CH3CI9DG3DI9EB8EG9FA7FH9GC2HD2IJ5JA9JB9";
	char ks2quoi[]="2 arcs (x,y) et (y,z). (x,y)=ABEF//CDGH et (y,z)=IJMN//KLOP. k=1: paire Q-R";
	char ks2point[]="AE4BF4CH3CQ9DG3DI9EB8EG9FA7FH9GC2HD2IM4JN4KP3KQ9LO3LQ9MJ8MO9NI7NP9OK2PL2QR9RA9RB9RJ9";
	char ks3quoi[]="TRIANGLE (x,y),(x,z) et (y,z). (x,y)=ABEF//CDGH, (x,z)=IJMN//KLOP et (y,z)=QRUV//STWX. k=1: paire Y-Z";
	char ks3point[]="AE4BF4CH3CI9DG3DQ9EB8EG9FA7FH9GC2HD2IM4JN4KP3KY9LO3LR9MJ8MO9NI7NP9OK2PL2QU4RV4SX3SY9TW3TY9UR8UW9VQ7VX9WS2XT2YZ9ZA9ZB9ZJ9";
	char ks4quoi[]="TRIANGLE (x,y),(x,z) et (y,z). (x,y)=ABEF//CDGH, (x,z)=IJMN//KLOP et (y,z)=QRUV//STWX. k=2: paires Y-Z et a-b";
	char ks4point[]="AE4BF4CH3CI9DG3DQ9EB8EG9FA7FH9GC2HD2IM4JN4KP3KY9Ka9LO3LR9MJ8MO9NI7NP9OK2PL2QU4RV4SX3SY9Sa9TW3TY9Ta9UR8UW9VQ7VX9WS2XT2YZ9ZA9ZB9ZJ9ab9bA9bB9bJ9";
	int bDepuisGraphe,nDimension;
	long zComplexiteh,yDeterminant;
	graf *pgG;
	iMatrice *pmA;
/*
pgG (17 sommets et 27 arcs):
          1		   2		3		  4		   5		6		7		8		   9		0
    0  (-1,-1)  ( 1, 5)  ( 2, 6)  ( 3, 8)  ( 3,17)  ( 4, 7)  ( 4, 9)  ( 5, 2)  ( 5, 7)  ( 6, 1)  
	1  ( 6, 8)  ( 7, 3)  ( 8, 4)  ( 9,13)  (10,14)  (11,16)  (11,17)  (12,15)  (12,17)  (13,10)
	2  (13,15)  (14, 9)  (14,16)  (15,11)  (16,12)  (17, 1)  (17, 2)  (17,10).
*/

/*
ks4point pgG (26 sommets et 45 arcs):
          1		   2		3		  4		   5		6		7		8		   9		0
    0  (-1,-1)  ( 1, 5)  ( 2, 6)  ( 3, 8)  ( 3,9)   ( 4, 7)  ( 4,17)  ( 5, 2)  ( 5, 7)  ( 6, 1)  
	1  ( 6, 8)  ( 7, 3)  ( 8, 4)  ( 9,13)  (10,14)  (11,16)  (11,25)  (11,26)  (12,15)  (12,18)
	2  (13,10)  (13,15)  (14, 9)  (14,16)  (15,11)  (16,12)  (17,21)  (18,22)  (19,24)  (19,25).
	3  (19,26)  (20,23)  (20,25)  (20,26)  (21,18)  (21,23)  (22,17)  (22,24)  (23,19)  (24,20).
	4  (25, 1)  (25, 2)  (25,10)  (26, 1)  (26, 2)  (26,10).
*/
	//Appel0("CouvertureTESTER");
		bDepuisGraphe=kV;
		nCas=403;//centaines= numéro du graphe; le modulo 100 est le niveau de bannisst demandé
		nCouvertureBanniR=0;
		EntierDepilerTout();//vide la pile de Outil.c
		if (bDepuisGraphe){
			//BanniR(-1,-2,-1,-2);//qqsoit nCas
			switch (nCas/100){
				case 0:	GrapheGenerer(ks0point,&pgG);if (1) t(ks0quoi);//nCas valides = 000 et 001
						break;// 1 solution
				case 1:	GrapheGenerer(ks1point,&pgG);if (1) t(ks1quoi);//nCas valides = 100, 101 et 102
						BanniR( 3, 9,10, 1); BanniR( 4, 9,10, 2);
						break;// 2 solutions 
				case 2:	GrapheGenerer(ks2point,&pgG);if (1) t(ks2quoi);
						BanniR(11,17,18, 2);//nCas valides = 200, 201
						break;// 2 solutions 
				case 3:	GrapheGenerer(ks3point,&pgG);if (1) t(ks3quoi);//nCas valides = 300 à 307
						BanniR(11,25,26, 2); BanniR(11,25,26,10);
						BanniR(19,25,26, 1); BanniR(19,25,26,10);
						BanniR(20,25,26, 1); BanniR(20,25,26, 2);
						break;// pas de solution
				case 4:	GrapheGenerer(ks4point,&pgG);if (1) t(ks4quoi);//nCas valides = 400 à 413
						BanniR(11,25,26, 2); BanniR(11,25,26,10); BanniR(11,27,28, 2); BanniR(11,27,28,10);
						BanniR(19,25,26, 1); BanniR(19,25,26,10); BanniR(11,27,28, 1); BanniR(11,27,28,10);
						BanniR(20,25,26, 1); BanniR(20,25,26, 2); BanniR(11,27,28, 1); BanniR(11,27,28, 2);
						break;// 3 solutions
				default: Assert1("CouvertureTESTER",0);
			}
			GrapheVoir0(pgG,"pgG",grCouleur);
		}
		nDimension=(bDepuisGraphe)?pgG->nSommetEnTout: 4;
		MatriceAllouer1(&pmA,nDimension);
			if (bDepuisGraphe){
				MatriceDepuisGraphe(pgG,!k1Incidence,&pmA);
				if (1) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=1;sY<=pgG->nSommetEnTout;sY++)
						if (bCroit(2,pmA->Mat[sX][sY],3))
							pmA->Mat[sX][sY]=-(pmA->Mat[sX][sY]-1);
				if (1) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=1;sY<=pgG->nSommetEnTout;sY++)
						if (pmA->Mat[sX][sY]>0){
							aK=nGrapheArc(pgG,sX,sY);
							//d3(sX,sY,aK);
							pmA->Mat[sX][sY]=1+aK;
						}
				if (1) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=1;sY<=pgG->nSommetEnTout;sY++){
						if (pmA->Mat[sX][sY]==1) teee("sX,sY,pmA->Mat[sX][sY]",sX,sY,pmA->Mat[sX][sY]);
						Assert1("CouvertureTESTER421",pmA->Mat[sX][sY]!=1);//car pour iCouvertureDecompterBiS , 5*1 est 5.
					}
			}else MatriceCanoniser(maTout,&pmA);
			if (1) MatriceVoir("CouvertureTESTER:pmA",pmA);
			if (0){
				//Mahajan
					yDeterminant=iFormeCalculeR(pmA);
					printf("Pseudo-déterminant par la méthode de Mahajan: %s.\n",sPar3(yDeterminant));
					zComplexiteh=2*zPuissance(nDimension,4);
				//Gauss
					yDeterminant=yMatriceDeterminant(pmA);
					printf("Déterminant classique par la méthode de Gauss: %s.\n",sPar3(yDeterminant));
			} else {
				CouvertureBanniR(pmA);
				//DagInvalideAfficher();
				yDeterminant=iCouvertureDecompterBiS(pmA,0,k1Afficher,muNeutre,0,&zComplexiteh);//non optimisé
			}
	//Appel1("CouvertureTESTER");
}//CouvertureTESTER

int iKouvertureEstimeR(int nGraphe,int bAfficher,int nCaractereParLibelleh,int nCaractereParResultat){
	//estime toutes les couvertures de graphe obtenues en faisant varier le nombre de pivots.
	int iDeterminant=97,nL,nC,nArcat,nSommat,nOffset;
	graf *pgG,*pgH;
	iMatrice *pmA;
	int aK,aL,sX,sY;
	//int iPoids[1+12]={ 1,      2, 2, 2, 2,        2, 2, 2, 2,      1      ,10,10, 1000};

	//int iPoids[1+12]={ 1,       2, 1, 2, 1,         2, 1, 2, 1,      1,    10, 10, 100};
	//int iPoids[1+12]={ 1,       2,-1,-1, 2,         1, 1, 1, 1,      1,    10, 10, 100};
	//int iPoids[1+12]={ 1,       2,-1,-1, 2,         2,-1,-1, 2,      1,    10, 10, 100};
	//int iPoids[1+12]={ 1,       2, 1, 1, 2,         1,-1, 1,-1,      1,    10, 10, 100};
	
	//int iPoids[1+12]={ 1,       1, 1, 1, 1,         1, 1, 1, 1,      1,       2,  2, 1000};
	//int iPoids[1+12]={ 1,       2, 1, 1, 2,         1,-1, 1,-1,      1,     5,  5, 1000};
	//int iPoids[1+12]={ 1,       3, 4, 5, 2,         5,-2, 4,-3,      1,     1,  1, 1000};

	//int iPoids[1+12]={ 1,       3, 4, 6, 2,         4, 3,-6,-2,      1,     10,  10, 1000};

	//int iPoids[1+12]={ 1,       3, 4, 6, 2,         4, 3,-6,-2,      1,     1,  1, 1};
	int iPoids[1+12]={ 1,       5, 5, 5, 5,         5, 5,-5,-5,      1,     1,  1, 1};
	//char kcLongrine8[]="AE1BF2CH8DG7EB4EG9FA3FH0GC5HD6";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
	int uL,uC;
	Appel0("iKouvertureEstimeR");
		nCouvertureEstimeR++;
		DagINITIALISER();
/*MatriceAllouer1(&pmA,6);
//MatriceCanoniser(maTout,&pmA);
MatriceFibonaccier(pmA->nLigne,&pmA);
DeterminantExpliciter(0,pmA);
free(pmA);
*/
		Assert1("iKouvertureEstimeR0",nDagPris()==0);
		if (0) printf("%s",sChaine0(sC3("Solutions pour ",sItem(sgrNoM,1+nGraphe),":"),nCaractereParLibelleh));
			GrapheCreer1(&pgG,nGraphe,k1Creer);
				if (1 && bAfficher) GrapheVoir(pgG,sC3b("iKouvertureEstimeR: graphe",sItem(sgrNoM,1+nGraphe),"ci-dessous"));
				nArcat=pgG->nArcEnTout;
				nSommat=pgG->nSommetEnTout;
				FormeLongrineR(pgG,10,12,&pgH);//altère pgG,eg pgG->nArcEnTout.
				//d(pgH->nSommetEnTout);
				if (0 && bAfficher) GrapheVoir0(pgH,sC2b("pgH associé à",sItem(sgrNoM,1+nGraphe)),grCouleur);
			GrapheCreer0(&pgG,!k1Creer);
			if (1){
					GrapheSymetriser(pgH);
					if (1 && bAfficher) GrapheVoir0(pgH,sC2b("pgH SYMÉTRISÉ associé à",sItem(sgrNoM,1+nGraphe)),grCouleur);
					int nPlace[1+pgH->nSommetEnTout];
					//nPlace:=correspondance entre sommet courant sX et un n° de ligne (>0) ou de colonne (<0) dans la future matrice pmA
						//d(pgH->nSommetEnTout);
						VecteurRazer(nPlace,1,pgH->nSommetEnTout);
						//VecteurVoir("nPlace0",nPlace,1,pgH->nSommetEnTout);
						nOffset=4*nArcat;
						//d2(nArcat,nOffset);
						for (nL=nC=0,aK=1;aK<=nArcat;aK++){//n° de ligne: >0 ou de colonne: <0
							//d3(aK,nL,nC);
							aL=(aK-1)*4;
							nPlace[aL+1]=+nL+1;nPlace[aL+2]=+nL+2;nPlace[aL+nOffset+3]=+nL+3;nPlace[aL+nOffset+4]=+nL+4;
							nPlace[aL+nOffset+1]=-nC-1;nPlace[aL+nOffset+2]=-nC-2;nPlace[aL+3]=-nC-3;nPlace[aL+4]=-nC-4;
							nL+=4;nC+=4;
						}
						//VecteurVoir1("nPlace1",nPlace,1,pgH->nSommetEnTout);
						for (aK=2*nSommat-1;aK>0;aK-=2){
							nPlace[pgH->nSommetEnTout-aK]=-(++nL);
							nPlace[pgH->nSommetEnTout-aK+1]=+nL;
						}
						VecteurVoir1("nPlace2",nPlace,1,pgH->nSommetEnTout);
					MatriceAllouer1(&pmA,pgH->nSommetEnTout/2);
						//pmA:=matrice associée à pgH
							//d(pgH->nSommetEnTout);
							for (sX=1;sX<=pgH->nSommetEnTout;sX++)
								if (nPlace[sX]>0)
									for (uL=nPlace[sX],aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){
										//Assert1("iKouvertureEstimeR95",bCroit(coJaune,pgH->coulh[aK],coBleu));
										sY=pgH->sSuk[aK]; uC= -nPlace[sY]; 
										//d5(sX,sY,uL,uC,iPoids[pgH->coulh[aK]]);
										pmA->Mat[uL][uC]= iPoids[pgH->coulh[aK]];
									}
							//reporter ds pmA (pr affichage) la correspondance numéro de sommet -> index de matrice
								for (sX=1;sX<=pgH->nSommetEnTout;sX++)
									if (nPlace[sX]<0)
										pmA->Mat[0][abs(nPlace[sX])]=sX;
									else pmA->Mat[abs(nPlace[sX])][0]=sX;
						if (1 || bAfficher) MatriceVoir("pmA*********",pmA);
						DeterminantConfronteR(pmA);
						DeterminantExpliciter(0,pmA);
					free(pmA);
			}
	Appel1("iKouvertureEstimeR");
	return(iDeterminant);
}//iKouvertureEstimeR

void KouvertureEstimerTouT(){
	//estime toutes les couvertures de graphes listées ds ce code.
	int bAfficher=kV,nGraphe,nPivotMax;
	int iEstime,uPivot;
	graf *pgG;
	const int knLongueur=21;
	const int knCaractereParLibelleh=21;
	int nType[1+8]={grAlpha,grP2,grP3,grC3,grC4,grC4b,grL4,grK4,grOmega};
	Appel0("CouvertureEstimerTouT");
		nCouvertureEstimeR=0;
		//iEstime=iKouvertureEstimeR(grP3,bAfficher);

		if (bAfficher){
			//afficher sur la première ligne du tableau la gamme croissante des pivots utiles dans le pire cas
				//nPivotMax:=nb maximal de pivots
					for (nPivotMax=0,nGraphe=1+grAlpha;nGraphe<grOmega;nGraphe++){
							GrapheCreer1(&pgG,nGraphe,k1Creer);
								nPivotMax=iSup(nPivotMax,pgG->nSommetEnTout);
							GrapheCreer0(&pgG,!k1Creer);
					}
				for (printf("%s",sChaine0("Nombre de pivots:",knCaractereParLibelleh)),uPivot=1;uPivot<=nPivotMax || !bLigne("\n");uPivot++)
					printf("%s%s",sE(10),sChaine2(sPluriel(uPivot,"pivot"),knLongueur-10));
		}
		//estimer le nombre de solutions pour tous les graphes de l'itération et pour tous les pivots utiles au graphe considéré
			if (1) for (nGraphe=nType[1];nType[1];nGraphe++)
				iEstime=iKouvertureEstimeR(nGraphe,1 && bAfficher,knCaractereParLibelleh,knLongueur);
	Appel1("KouvertureEstimerTouT");
}//KouvertureEstimerTouT

void DagChemineR(graf *pgG,int nNiveauEnTout,int sSource,int sTrappe,int nColonne[]){
	//liste tous les plus longs chemins (profondeur d'abord) qui vont de sSource à sTrappe par des colonnes distinctes.
	int sPile[1+pgG->nSommetEnTout];
	DequeAllouer(nNiveauEnTout);
		sPile[0]=0;
		sPile[++sPile[0]]=sSource;
		DequeEmpiler(nColonne[sSource]);
		zChemineR=nCheminDeclineR=0;
		ChemineR(pgG,nNiveauEnTout,sSource,sTrappe,sPile,nColonne);
	DequeAllouer(0);
	printf("Complexité en nombre d'empilements: %s.\n",sPar3(zChemineR));
	printf("nNiveauEnTout au cube: %s.\n",sPar3(zPuissance(nNiveauEnTout,3)));
	printf("Ratio cplexT/nNivo: %4.2f.\n",(zChemineR*1.0/zPuissance(nNiveauEnTout,3)));
}//DagChemineR

void DeterminantCalculeR(int nSommet,enum eMathricE maMode){
	fMathricE *pmA;
	MathriceAlloueR(nSommet,nSommet,&pmA);
	MathriceRempliR(pmA,maMode);
	MathriceVoiR("pmA",pmA);
	DeterminantKalculeR(pmA,k1Voir);
}//DeterminantCalculeR

void DeterminantConfronteR(iMatrice *pmE){
	int bGaussNul,bMahajanNul,bUrbanskaNul;
	long yDeterminant[3];
	#define kuVinh 20
	//Gauss
		yDeterminant[0]=yMatriceDeterminant(pmE);
		//te("yDeterminant Gauss",yDeterminant[0]);
		bGaussNul=yDeterminant[0]==0;
		//printf("Le déterminant hors quad de Gauss %s nul.\n",sEst(bGaussNul));
	//Mahajan
		yDeterminant[1]=iFormeCalculeR(pmE);
		bMahajanNul=yDeterminant[1]==0;
		//printf("Le déterminant hors quad de Mahajan %s nul.\n",sEst(bMahajanNul));
	//Urbanska
		yDeterminant[2]=yFormeKalculeR(pmE,0,!k1Voir);
		//te("yDeterminant Urbanska",yDeterminant[2]);
		bUrbanskaNul=yDeterminant[2]==0;
		//printf("Le déterminant hors quad de Urbanska %s nul.\n",sEst(bUrbanskaNul));
	Titrer("COMPARATIF CALCULS DE DETERMINANT");
	printf("Algorithme:      %s%s%s\n", sChaine0("G A U S S",kuVinh),sChaine0("M A H A J A N",kuVinh),sChaine0("U R B A N S K A",kuVinh));
	printf("Déterminant:    %s%s%s\n",sEnt3(yDeterminant[0],kuVinh),sEnt3(yDeterminant[1],kuVinh),sEnt3(yDeterminant[2],kuVinh));
	//Assert1("DeterminantConfronteR",bEgal3(yDeterminant[0],yDeterminant[1],yDeterminant[2]));
	printf("Déterminant nul:%20d%20d%20d\n",bGaussNul,bMahajanNul,bUrbanskaNul);
}//DeterminantConfronteR

void DeterminantExpliciteR(iMatrice *pmA,int bEnVrai,int bAfficher,int muSigneAvant,int ukPileMax,int iPile[],long yProduit[]){
	//explicite laborieust le calcul du déterminant de pmA,ie récursivt et par sommation alternée de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot,muSigne,ipPile;
	long yProd;
	iMatrice *pmB;
	//Appel0("DeterminantExpliciteR");
	//te("pmA->nLigne",pmA->nLigne);
	Assert2("DeterminantExpliciteR0",pmA->nLigne,pmA->nLigne==pmA->nColonne);
	if (pmA->nLigne>1){
		//MatriceVoir("Matrice Reçue",pmA);
		MatriceAllouer1(&pmB,pmA->nLigne-1);
			for (muSigne=muSigneAvant,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
				if (pmA->Mat[uPivot][1]){
					Assert1("DeterminantExpliciteR",iPile[0]<=ukPileMax);
					iPile[++iPile[0]]=pmA->Mat[uPivot][1];
						//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
							for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
								if (uL!=uPivot)
									for (nL++,nC=1,uC=2;uC<=pmA->nLigne;uC++){
										Assert2("DeterminantExpliciteR2",bCroit(1,nL,pmB->nLigne),bCroit(1,nC,pmB->nColonne));
										pmB->Mat[nL][nC++]=pmA->Mat[uL][uC];
									}
						//MatriceVoir(sC2b("Matrice B après pivot ligne",sEnt(uPivot)),pmB);
						DeterminantExpliciteR(pmB,bEnVrai,bAfficher,muSigne,ukPileMax,iPile,yProduit);//Récursion laborieuse
					iPile[0]--;
				};
				muSigne=-muSigne;
			}
		free(pmB);
		//te("ySignature",ySignature);
	} else if (pmA->Mat[1][1]) {
		//d(muSigneAvant);
		//VecteurVoir("iPile",iPile,1,iPile[0]);
		//d(pmA->Mat[1][1]);
		yProduit[0]++;
		iPile[++iPile[0]]=pmA->Mat[1][1];//le seul terme de la matrice locale reçue en paramètre
			for (yProd=muSigneAvant,ipPile=1;ipPile<=iPile[0];ipPile++)
				yProd*=iPile[ipPile];
			//d2(yProduit[0],yProd);
			if (!bEnVrai)
				yProduit[yProduit[0]]=yProd;
			if (bAfficher && yProduit[yProduit[0]]!=0){
				for (printf("%9ld: (",yProduit[0]),ipPile=1;ipPile<=iPile[0];ipPile++)
					printf("%5d%s",iPile[ipPile],(bCroitStrict(0,ipPile,iPile[0]))? "*":"");
				printf(")*(%c1)=%20s.\n",(muSigneAvant>0)?'+':'-',sEnt3(yProd,25));
			}
		iPile[0]--;
	}
	//Appel1("DeterminantExpliciteR");
}//DeterminantExpliciteR

void DeterminantExpliciter(int nGraphe,iMatrice* pmA){
	//explicite laborieust le calcul du déterminant de pmA,ie récursivt et par sommation alternée de cofacteurs;déroute si hors domaine.
	int bAfficher,nLongrine,nResidu;
	#define kuPileMax kE3
	long yDeterminant,yProduit[1+kuPileMax];
	//int iA=6,iB=4,iC=8,iD=3;
	int iA=10,iB=10,iC=10,iD=10,iE=1000;
	//pmA soit généré
		//int nGraphe=grP2;//iKouvertureEstimeR
		switch(nGraphe){
		 case grP2:
			nLongrine=1;
			MatriceAllouer1(&pmA,6);
			//si aucun zéro sur la diagonale
				/*pmA->Mat[1][2]=pmA->Mat[1][3]=pmA->Mat[1][4]=pmA->Mat[2][1]=pmA->Mat[2][3]=pmA->Mat[2][4]=1;
				pmA->Mat[3][4]=pmA->Mat[3][5]=pmA->Mat[3][6]=pmA->Mat[4][3]=pmA->Mat[4][5]=pmA->Mat[4][6]=1;
				pmA->Mat[5][2]=pmA->Mat[5][6]=pmA->Mat[6][1]=pmA->Mat[6][5]=1;
				pmA->Mat[1][3]=iC;pmA->Mat[2][3]=iB;pmA->Mat[1][4]=iA;pmA->Mat[2][4]=iD;//papillon 1
				pmA->Mat[3][5]=iC;pmA->Mat[4][5]=iB;pmA->Mat[3][6]=iA;pmA->Mat[4][6]=iD;//papillon 2
				pmA->Mat[5][2]=pmA->Mat[6][1]=100;//attaches*/
			//si zéros éventuels sur la diagonale
			pmA->Mat[1][3]=pmA->Mat[1][4]=pmA->Mat[1][5]=pmA->Mat[2][3]=pmA->Mat[2][4]=pmA->Mat[2][6]=1;
			pmA->Mat[3][1]=pmA->Mat[3][2]=pmA->Mat[3][3]=pmA->Mat[4][1]=pmA->Mat[4][2]=pmA->Mat[4][4]=1;
			pmA->Mat[5][1]=pmA->Mat[5][5]=pmA->Mat[6][2]=pmA->Mat[6][6]=1;
			pmA->Mat[1][3]=iA;pmA->Mat[2][4]=iB;pmA->Mat[1][4]=iC;pmA->Mat[2][3]=iD;//papillon 1
			pmA->Mat[3][1]=iA;pmA->Mat[4][2]=iB;pmA->Mat[3][2]=iC;pmA->Mat[4][1]=iD;//papillon 2
			pmA->Mat[5][5]=pmA->Mat[6][6]=iE;//attaches
			break;
		case grP3:
			nLongrine=2;
			MatriceAllouer1(&pmA,11);
			//si zéros éventuels sur la diagonale
			pmA->Mat[1][1]=pmA->Mat[1][2]=pmA->Mat[1][9]=pmA->Mat[2][1]=pmA->Mat[2][2]=pmA->Mat[2][10]=1;
			pmA->Mat[3][1]=pmA->Mat[3][3]=pmA->Mat[3][4]=pmA->Mat[4][2]=pmA->Mat[4][3]=pmA->Mat[4][4]=1;
			pmA->Mat[5][5]=pmA->Mat[5][6]=pmA->Mat[6][5]=pmA->Mat[6][6]=pmA->Mat[6][11]=1;
			pmA->Mat[7][5]=pmA->Mat[7][7]=pmA->Mat[7][8]=pmA->Mat[8][6]=pmA->Mat[8][7]=pmA->Mat[8][8]=1;
			pmA->Mat[9][3]=pmA->Mat[9][9]=pmA->Mat[10][7]=pmA->Mat[10][10]=pmA->Mat[11][8]=pmA->Mat[11][11]=1;
			pmA->Mat[1][1]=iA;pmA->Mat[2][2]=iB;pmA->Mat[2][1]=iC;pmA->Mat[1][2]=iD;//papillon 1
			pmA->Mat[5][5]=iA;pmA->Mat[6][6]=iB;pmA->Mat[6][5]=iC;pmA->Mat[5][6]=iD;//papillon 2
			pmA->Mat[9][9]=pmA->Mat[10][10]=pmA->Mat[11][11]=iE;//attaches
			pmA->Mat[5][4]=2;
			break;
			//default:Assert1("DeterminantExpliciter default",0);
		}//switch
		//MatriceCanoniser(maTout,&pmA);
		//MatriceFibonaccier(6,&pmA);
		if (nGraphe) MatriceVoir("pmA*********",pmA);
	int iPile[1+pmA->nLigne];
	//yProduit[] reçoive les produits élémentaires;yProduit[0] soit le nombre de produits
		VecteurRazer(iPile,0,pmA->nLigne);
		yProduit[0]=0;
		bAfficher=k1Afficher;
		if (bAfficher) Titrer("Produits élémentaires");
		DeterminantExpliciteR(pmA,!k1EnVrai,bAfficher,1,kuPileMax,iPile,yProduit);
		//d(yProduit[0]);
	//zéroter les couples de produits qui se neutralisent en s'opposant
		nResidu=yProduit[0];
		for (int uL=1;uL<=yProduit[0];uL++)
			for (int uC=uL+1;uC<=yProduit[0];uC++)
				if (yProduit[uL]!=0 && yProduit[uL]+yProduit[uC]==0){
					yProduit[uL]=yProduit[uC]=0;
					nResidu-=2;
				}
	//afficher les seuls produits non nuls
		VecteurRazer(iPile,0,pmA->nLigne);
		//VekteurVoir("yProduit",yProduit,1,yProduit[0]);
		//d(nResidu);
		Titrer(sC2b("Produits restants une fois appliqué A-A=0",sP(sPluriel(nResidu,"produit"))));
		yProduit[0]=0;
		DeterminantExpliciteR(pmA,k1EnVrai,k1Afficher,1,kuPileMax,iPile,yProduit);
	//yDeterminant soit le déterminant résultant
		yDeterminant=yVekteurSomme(yProduit,1,yProduit[0]);
		ld(yDeterminant);
}//DeterminantExpliciter

void DeterminantKalculeR(fMathricE *pmA,int bVoir){//O(exponentiel)
	f fKalcul;
	FormeCreeR("0",&fKalcul);
	nSignatureKalculeR=0;
	SignatureKalculeR(pmA,k1AlterneR,&fKalcul);
	FormeVoiR("Déterminant",fKalcul);
	FormeTrieR(&fKalcul);
	if (bVoir){
		FormeVoiR("Déterminant",fKalcul);
		te("Nombre de termes",fKalcul.num[0][0]);
	}
}//DeterminantKalculeR

void DeterminantNonNulVerifieR(){
	//vérifie qu'il existe bien 5 matrices non nulles A,B,C,D,E qui vérifient AD=0,BC=0,AC≠0,BD≠0 ainsi que DBEC=CBED.
	//A=(1,a,b,ab), B=(1,c,d,cd), C=(cu,cv,-u,-v), D=(am,an,-m,-n).
	int A,C,D,M,N,U,V;
	int iDeterminant;
	iMatrice *pmE;
	Appel0("DeterminantNonNulVerifieR");
		A=2;C=3;D=1;N=1;U=1;V=2;
		M=(U+D*V)-N*D;//non obligatoire, mais ce faisant les coeff de pmE sont tous sous la forme X-Y plutôt que (u+dv)X-(m+nd)Y.
		Assert2("DeterminantNonNulVerifieR",M+N*D!=0,M+N*D==U+D*V);//dc on peut diviser (u+dv)X et (m+nd)Y par u+dv alias m+nd.
		MatriceAllouer1(&pmE,4);
			//le déterminant de E est donné par la matrice pmE suivante:
				pmE->Mat[1][1]= A*C*U-A*M*C;pmE->Mat[1][2]=-A*U*+C*M;pmE->Mat[1][3]=A*C*C*U+A*C*D*M;pmE->Mat[1][4]=-A*C*U+C*D*M;
				pmE->Mat[2][1]=-C*U+A*D*M  ;pmE->Mat[2][2]= U-D*M   ;pmE->Mat[2][3]= -C*C*U+A*C*M  ;pmE->Mat[2][4]=   C*U-C*M;
				pmE->Mat[3][1]= A*C*V-A*N*C;pmE->Mat[3][2]=-A*V*+C*N;pmE->Mat[3][3]=A*C*C*V+A*C*D*N;pmE->Mat[3][4]=-A*C*V+C*D*N;
				pmE->Mat[4][1]=-C*V+A*D*N  ;pmE->Mat[4][2]= V-D*N   ;pmE->Mat[4][3]= -C*C*V+A*C*N  ;pmE->Mat[4][4]=   C*V-C*N;
				MatriceVoir("pmE",pmE);
			iDeterminant=yMatriceDeterminant(pmE);//si iDeterminant est non nul, alors DBEC=CBED est possible.
			te("iDeterminant",iDeterminant);//affiche 1296.
		free(pmE);
	Appel1("DeterminantNonNulVerifieR");
}//DeterminantNonNulVerifieR

void DeterminantQalculeR(fMathricE *pmA,int bVoir){//O(exponentiel)
	//transformer la matrice en matrice d'entiers puis calculer le permanent
	const int kbRetraitVoir=kF;
	int nColonne[1+pmA->nColonne];
	int nArcRetireh,bBascule,nFois,uL,uC,nSommande,nSommet,uT;
	int sSource,sTrappe,sX,sY;
	f fForme;
	graf *pgG;
	iMathricE imA,imB;
	imA.nLigne=pmA->nLigne;
	imA.nColonne=pmA->nColonne;
	imB.nLigne=pmA->nLigne;
	imB.nColonne=pmA->nColonne;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++){
			imA.iForme[uL][uC]=0;
			imB.iForme[uL][uC]=0;
			fForme=pmA->fForme[uL][uC];
			//tee("uL,uC",uL,uC);
			nSommande=fForme.num[0][0];
			Assert1("DeterminantQalculeR",nSommande<=1);
			for (uT=1;uT<=kuTermeMaX;uT++){
				nFois=fForme.num[1][uT];
				if (nFois>0)
					imA.iForme[uL][uC]=(uT<32)? uT:-(uT-32);
			}
		}
	//MathriceVoiR("DeterminantQalculeR,pmA",pmA);
	//transformer la matrice en graphe
		//nSommet soit le nombre total de sommets distincts
			for (nSommet=0,uL=1;uL<=imA.nLigne;uL++)
				for (uC=1;uC<=imA.nColonne;uC++)
					if (imA.iForme[uL][uC]!=0)
						nSommet++;
		GrapheCreer(-nSommet,&pgG);//aucun arc
			//imB contienne des cases ayant des numéros distincts ds 1..nSommet
				for (nSommet=0,uL=1;uL<=imA.nLigne;uL++)
					for (uC=1;uC<=imA.nColonne;uC++)
						if (imA.iForme[uL][uC]!=0){
							nSommet++;
							imB.iForme[uL][uC]=nSommet;
							nColonne[nSommet]=uC;
						}
				Assert1("DeterminantQalculeR4",nSommet==pgG->nSommetEnTout);
				//MattriceVoiR("imA numérotééééééééééééé",&imA);
				//MattriceVoiR("imB numéroté",&imB);
			//générer TOUS les arcs du Dag
				for (uL=1;uL<imB.nLigne;uL++)
					for (uC=1;uC<=imB.nColonne;uC++)
						if (imA.iForme[uL][uC]!=0){
							for (uT=1;uT<=imA.nColonne;uT++)
								if (imB.iForme[uL+1][uT]!=0){
									//printf("arc (%d,%d)\n",imA.iForme[uL][uC],imA.iForme[uL+1][uT]);
									GrapheArquer(pgG,imB.iForme[uL][uC],imB.iForme[uL+1][uT]);
								}
						}
				//GrapheVoir(pgG,"DeterminantQalculeR0");
			//retirer les arcs interdits
				for (nArcRetireh=0,bBascule=kV,uL=2;uL<imB.nLigne;uL++)
					for (uC=2;uC<=imB.nColonne;uC++)
						if (imA.iForme[uL][uC]<0){//chaque losange a deux sommets en minuscule dans imA. Seul le premier est exploité pour…
							if (bBascule){//…retirer les deux arcs interdits;grâce à bBascule, le second sommet concerné est ignoré.
									sX=imB.iForme[uL-1][uC-1];sY=imB.iForme[uL][uC-2];
									if (kbRetraitVoir) printf("Arc retiré: %s.\n",sCouple(sX,sY));
									nArcRetireh+=bGrapheDesarquer(pgG,sX,sY);
									sX=imB.iForme[uL][uC];sY=imB.iForme[uL+1][uC-1];
									if (kbRetraitVoir) printf("Arc retiré: %s.\n",sCouple(sX,sY));
									nArcRetireh+=bGrapheDesarquer(pgG,sX,sY);
								}
							bBascule=!bBascule;
						}
				//GrapheVoir(pgG,"DeterminantQalculeR1");
		printf("Le graphe secondaire a %s et %s (après retrait de %s).\n",sPluriel(nSommet,"sommet"),sPluriel(pgG->nArcEnTout,"arc"),sPluriel(nArcRetireh,"arc"));
		//énumérer tous les plus longs chemins (profondeur d'abord)
			DagChemineR(pgG,pmA->nLigne,sSource=2,sTrappe=nSommet,nColonne);
	GrapheCreer(0,&pgG);
}//DeterminantQalculeR

char *sFormE(f fForme,int bDenominateurSinonNumerateur){
	//rend la forme littérale classée selon la valeur de chaque coeff non nul: coeff 1, coeff < 1 et coeff > 1.
	int zdPasse;
	Assert1("sFormE",bFormeAmorceR);
	int bNul,iPoids,uP,nPoids,uL,nLettrat,nTermat,uT,nC;
	char cCar;
	char *sForme=malloc(kuFormeLiM);
	char *sPoids=malloc(kuFormeLiM);
		for (nC=0;nC<=kuFormeMaX;nC++)
			sForme[nC]='\0';
		for (nC=0;nC<=kuFormeMaX;nC++)
			sPoids[nC]='\0';
		nTermat=(bDenominateurSinonNumerateur)? fForme.den[0][0]:fForme.num[0][0];
		//tee("bDenominateurSinonNumerateur,nTermat",bDenominateurSinonNumerateur,nTermat);
		for (nC=0,zdPasse=0;zdPasse<=2;zdPasse++){
			//te("zdPasse",zdPasse);
			for (uT=1;uT<=nTermat;uT++){
				nLettrat=nLettraT(fForme,uT,bDenominateurSinonNumerateur);
				//tee("uT,nLettrat",uT,nLettrat);
				iPoids=(bDenominateurSinonNumerateur)? fForme.den[uT][0]: fForme.num[uT][0];//poids dudit sommande
				bNul=nLettrat==0;
				//Assert1("sFormE poids",iPoids!=0 || bNul);
				//tb("bNul",bNul);
				if (!bNul){//le terme courant a un coeff non nul;le prendre en 3 fois, selon zdPasse: coeff =1, coeff < 1 et coeff > 1.
					if ( (iPoids<0 && zdPasse==0) || (iPoids>0 && zdPasse==1) || (iPoids==0 && zdPasse==2) ){ //|| (iPoids==1 && zdPasse==2)
						nPoids=abs(iPoids);
						sForme[nC++]=(iPoids<0)? '-': '+';
						if (nPoids!=1){
							sprintf(sPoids,"%d",nPoids);
							for (uP=0;uP<nChaineLg(sPoids);uP++)
								sForme[nC++]=sPoids[uP];
						}
						/*if (uS==1){
							if (iPoids!=0 && iPoids !=1)
								if (iPoids!=-1){
									sprintf(sPoids,"%d",iPoids);
									for (uP=0;uP<nChaineLg(sPoids);uP++)
										sForme[nC++]=sPoids[uP];
								}else sForme[nC++]='-';
						} else {
							nPoids=zAbs(iPoids);
							if (nPoids!=0)
								sForme[nC++]=(iPoids<0)? '-': '+';
							if (nPoids!=1){
								sprintf(sPoids,"%d",nPoids);
								for (uP=0;uP<nChaineLg(sPoids);uP++)
									sForme[nC++]=sPoids[uP];
							}
						}*/
						for (uL=1;uL<=nLettrat;uL++){
							cCar=(bDenominateurSinonNumerateur)? fForme.den[uT][uL]: fForme.num[uT][uL];
							sForme[nC++]=cCar;
							//if (nFois>1)//rendre A2 plutôt que A*A
							//	sForme[nC++]='0'+nFois;
						}//if ((zdPasse==0) == (iPoids>=0))
					}
				};//if (!bNul)
			}//for uT
		}//for zdPasse
		if (nTermat==0)
			sprintf(sForme,"%c",(bDenominateurSinonNumerateur)?'1':'0');
		else if (nC==0)
			sprintf(sForme,"%c",(bDenominateurSinonNumerateur)?'1':'1');//5 inverse
	free(sPoids);
	Assert1("sFormE9 Taille allouée insuffisante",sForme[kuFormeMaX]=='\0');//ie la chaîne allouée est de taille suffisante
	return(sForme);
}//sFormE
	
void FormeAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bFormeAmorceR=kV;
	Assert4("FormeAMORCER1",bFrontiere8(kuLettreLiM),bFrontiere8(kuLigneLiM),bFrontiere8(kuSommandeLiM),bFrontiere8(kuFormeLiM));
	pgGrapH=NULL;
	Assert1("FormeAMORCER2",bFrontiere8(sizeof(fMathricE)));
}//FormeAMORCER

void FormeAjouteR(f fA,f fB,f *pfC){
	//ajoute des rapports en les cumulant
	Assert1("FormeAjouteR11",bFormeAmorceR);
	const int kbVoir=kF;
	int uA,uB,uCible,uL;
	int nSommandeA=fA.num[0][0];
	int nSommandeB=fB.num[0][0];
	if (!(nSommandeA+nSommandeB<kuSommandeLiM))
		tee("nSommandeA,nSommandeB",nSommandeA,nSommandeB);
	Assert1("FormeAjouteR2",nSommandeA+nSommandeB<kuSommandeLiM);
	//ajouter deux formes, c'est juxtaposer les formes
	if (kbVoir) FormeVoiR("FormeAjouteR gauche:fA",fA);
	if (kbVoir) FormeVoiR("FormeAjouteR droit:fB",fB);
	//if (kbVoir) te("FormeAjouteR avant:nSommandeA+nSommandeB",nSommandeA+nSommandeB);
	FormeRazeR(pfC);
	for (uA=1;uA<=nSommandeA;uA++){
		uCible=uA;
		for (uL=0;uL<=kuTermeMaX;uL++)
			(*pfC).num[uCible][uL]=fA.num[uA][uL];
		for (uL=0;uL<=kuTermeMaX;uL++)
			(*pfC).den[uCible][uL]=fA.den[uA][uL];
	}
	for (uB=1;uB<=nSommandeB;uB++){
		uCible=nSommandeA+uB;
		for (uL=0;uL<=kuTermeMaX;uL++)
			(*pfC).num[uCible][uL]=fB.num[uB][uL];
		for (uL=0;uL<=kuTermeMaX;uL++)
			(*pfC).den[uCible][uL]=fB.den[uB][uL];
	}
	(*pfC).num[0][0]=fA.num[0][0]+fB.num[0][0];
	(*pfC).den[0][0]=fA.den[0][0];
	if (kbVoir) FormeVoiR("FormeAjouteR gauche+droit *****************",*pfC);
	if (kbVoir) te("FormeAjouteR6:nSommandeA+nSommandeB",nSommandeA+nSommandeB);
	FormeSimplifieR(pfC);
	//if (kbVoir) FormeVoiR("fA+fB simplifiée",*pfC);
}//FormeAjouteR

void FormeArrangeR(int nDim,iMatrice **ppmE){
	int nCardinal,uC,uL,uQ,nQuadripole,sX;
	iMatrice *pmA,*pmB;
	int nSommat=(*ppmE)->nLigne;
	//Appel0("FormeArrangeR");
		//te("nSommat",nSommat);
		MatriceAllouer1(&pmA,nSommat);
		MatriceAllouer1(&pmB,nSommat);
		nQuadripole=nDim*nDim;
		//te("nQuadripole",nQuadripole);
		//pmA soit la copie de ppmE AVEC sa permutation courante
			MatriceDupliquer(*ppmE,pmA);
			if(0){//signaler les lignes qui ne contiennent qu'un item
				for (uL=1;uL<=pmA->nLigne;uL++){
					for (nCardinal=0,uC=1;uC<=pmA->nColonne;uC++)
						nCardinal+=pmA->Mat[uL][uC]!=0;
					if (nCardinal==1)
						for (uC=1;uC<=pmA->nColonne;uC++)
							pmA->Mat[uL][uC]= -abs(pmA->Mat[uL][uC]);
				}
			}
		//MatriceVoir("pmA AVANT FormeArrangeR",pmA);
		//Dans pmA, placer les sélections à droite ou en bas
			//te("nSommat",nSommat);
			MatriceDecaler(k1Ligne,nDim,1,pmA->nLigne,&pmA);
		//MatriceVoir("pmA après déplact sélections en LIGNE",pmA);
			MatriceDecaler(!k1Ligne,nDim,1,pmA->nColonne,&pmA);
		//MatriceVoir("pmA après déplact sélections en COLONNE",pmA);
		//Dans pmA, retirer l'arc central de chaque losange
			for (uQ=1,sX=2;uQ<=nQuadripole;sX+=4,uQ++){
				//printf("pmA->Mat[%d][%d]=%d\n",sX,sX+1,pmA->Mat[sX][sX+1]);
				pmA->Mat[sX][sX+1]=0;
			}
		//MatriceVoir("pmA après retirer l'arc central",pmA);
		//Reordonner chaque quadripole 
			for (uQ=1,sX=0;uQ<=nQuadripole;sX+=4,uQ++)
				MatriceEchangerSingleton(k1Ligne,sX+2,sX+3,!k1Voir,&pmA);
			for (uQ=1,sX=0;uQ<=nQuadripole;sX+=4,uQ++)
				MatriceEchangerSingleton(!k1Ligne,sX+2,sX+3,!k1Voir,&pmA);
		//MatriceVoir("pmA APRES Réordonner chaque quadripole",pmA);
		//Tasser les quadripoles en haut à gauche 
			for (uQ=1,uL=1;uQ<=nQuadripole;uL+=3,uQ++){
				MatriceDecaler(k1Ligne,1,uL,pmA->nLigne,&pmA);
				//MatriceVoir(sC2("pmA APRES Tassement n°",sEnt(uQ)),pmA);
			}
			//MatriceVoir(sC2("pmA APRES Tassement n°",sEnt(uQ)),pmA);
			if (1) for (uQ=2,uL=4;uQ<=nQuadripole;uL+=3,uQ++){
				MatriceDecaler(!k1Ligne,1,uL,pmA->nColonne,&pmA);
				//MatriceVoir(sC2("pmA APRES TASSEMENT n°",sEnt(uQ)),pmA);
			}
		//MatriceVoir("pmA APRES Tassement quadripole",pmA);
		MatriceDupliquer(pmA,*ppmE);
	//Appel1("FormeArrangeR");
}//FormeArrangeR

void FormeBordeR(int nCoteh,int *pnLigne,int *pnColonne,int *pnMotif,fMathricE **ppmA){
	//motif vertical allant un peu à droite
	int nC;
	int nMotif=*pnMotif;
	for (nC=0;nC<nCoteh;nC++)
		FormeCaseR(nMotif,*pnLigne+3*nC,*pnColonne+nC,ppmA);
	*pnColonne=*pnColonne+nCoteh;
	MotifSuivanT(pnMotif);
}//FormeBordeR

int iFormeCalculeR(iMatrice *pmA){//O(S4)
	//rend le déterminant calculé par la méthode de Mahajan et Vinay;utilise yDagEvaluer
	int muNeutre=1;
	int noAvant,noApres,noMatYH,noMatYZ,noOperande,noPoleNegatif,noPolePositif,noProduit,noUn,noZero;
	int iDelta,nEtage,bUn,sH,sX,sY,sZ,cComposante,uSommat,iPositif,iNegatif;
	long zComplexiteh;
	int noPole[2];
	int noV[2][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	int bPoly=kF;
	//Appel0("iFormeCalculeR Mahajan");
		uSommat=pmA->nLigne;
		Assert2("iFormeCalculeR 2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne);
		noZero=noPolyAfF(bPoly,0);
		noUn=noPolyAfF(bPoly,muNeutre);
		//d2(noZero,noUn);
		//noV et noPole soient razés; O(S3)
			for (zComplexiteh=0,cComposante=0;cComposante<=1;cComposante++)
				for (noPole[cComposante]=noZero/*VITAL*/,sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;zComplexiteh++,nEtage++)
							noV[cComposante][sH][sX][nEtage]=noZero;
		if (0){
			tee("uSommat",uSommat,uSommat*uSommat*uSommat);
			te("zComplexiteh",zComplexiteh);
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		}
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de noV
			for (sH=1;sH<=uSommat;zComplexiteh++,sH++)
				noV[cComposante=uSommat%2][sH][sH][nEtage=0]=noUn;
		if (0)
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (0) {Titrer(sC2b("ETAGE",sEnt(nEtage))); tee("nEtage,uSommat",nEtage,uSommat);}
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (cComposante=0;cComposante<=1;cComposante++)
							for (sZ =sH+1;sZ<=uSommat;zComplexiteh++,sZ++){
								noOperande=noV[cComposante][sH][sY][nEtage];
								noMatYZ=(pmA->Mat[sY][sZ]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sZ]);
								noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYZ);
								noAvant=noV[cComposante][sH][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								noV[cComposante][sH][sZ][nEtage+1]=noApres;
								noMatYH=(pmA->Mat[sY][sH]==0)? noZero: noPolyAfF(bPoly,pmA->Mat[sY][sH]);
								noOperande=noV[cComposante][sH][sY][nEtage];
								noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noPolyMuL(bPoly,noOperande,noMatYH);
								noAvant=noV[1-cComposante][sZ][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noPolyAdD(bPoly,noAvant,noProduit);
								if (!bPoly || bDagSimple(noApres))
									noV[1-cComposante][sZ][sZ][nEtage+1]=noApres;
							}
			}
		if (0) printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		if (0) Titrer("dernier etage");
		//traiter le dernier étage; O(S2)
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					noMatYH=noPolyAfF(bPoly,pmA->Mat[sY][sH]);
					for (cComposante=0;cComposante<=1;cComposante++){
						noOperande=noV[cComposante][sH][sY][uSommat-1];
						noProduit=noPolyMuL(bPoly,noOperande,noMatYH);
						noAvant=noPole[cComposante];
						noApres=noPolyAdD(bPoly,noAvant,noProduit);//accumulation définie vu assertion iFormeCalculeR3
						if (!bPoly || bDagSimple(noApres))
							noPole[cComposante]=noApres;
					}
				}
		iPositif=noPolePositif=noPole[1];//oui,1 et non pas 0.
		iNegatif=noPoleNegatif=noPole[0];
//d2(iPositif,iNegatif);
		if (0 && bPoly){//afficher la structure; O(S3)
			Assert1("iFormeCalculeR 47",noPoleNegatif>0);
			DagFormuler("noPoleNegatif",noPoleNegatif);
			//aficher noV[][][][]
				printf("    Composante 0       Composante 1\n");
				for (nEtage=0;nEtage<=uSommat-1;nEtage++)
					for (sX=1;sX<=uSommat;sX++)
						for (sY=1;sY<=uSommat;sY++){
							printf("    noV[%d,%d,%d,%d]=%d,",0,sX,sY,nEtage,noV[0][sX][sY][nEtage]);
							printf("    noV[%d,%d,%d,%d]=%d.\n",1,sX,sY,nEtage,noV[1][sX][sY][nEtage]);
						}
			d2(noPoleNegatif,noPolePositif);
			DagVoirTout("DagVoirTout noPoleNegatif");
		}
		if (1 && bPoly){
			//printf("Noeud pris AVANT simplification:%s.\n",sPar3(nDagPris()));
			DagSimplifier(-1,noPoleNegatif,muNeutre,kV);
			//printf("Noeud pris APRES simplification:%s.\n",sPar3(nDagPris()));//donc invariant
			if (0) DagFormuler("noPoleNegatif APRES simplification ultime",noPoleNegatif);
			if (0) DagArborer("noPoleNegatif APRES simplification ultime",noPoleNegatif,0);
			DagSimplifier(-2,noPolePositif,muNeutre,kV);
			if (0) DagFormuler("noPolePositif APRES simplification ultime",noPolePositif);
			if (1) DagArborer("noPolePositif APRES simplification ultime",noPolePositif,0);
		}
		bUn=0;//si kV,considère que chaque feuille non nulle vaut 1
		//ld(yDagEvaluer(noPoleNegatif,bUn));
		//ld(yDagEvaluer(noPolePositif,bUn));
		iNegatif=(bPoly)? yDagEvaluer(noPoleNegatif,bUn): noPoleNegatif;
		iPositif=(bPoly)? yDagEvaluer(noPolePositif,bUn): noPolePositif;
		//d2(iPositif,iNegatif);
		iDelta=iPositif-iNegatif;
	//Appel1("iFormeCalculeR Mahajan");
	return(iDelta);
}//iFormeCalculeR

ri riFormeCalculeR(riMatrice *pmA){//O(S4)
	//rend le déterminant (Mahajan et Vinay 1997).
	int nEtage,sH,sX,sY,sZ,cComposante,uSommat;
	long zComplexiteh;
	ri noAvant,noApres,noMatYH,noMatYZ,noOperande,noProduit,noUn,noZero,riDelta,noPole[2];
	ri noV[2][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	Appel0("riFormeCalculeR Mahajan");
		//d2(1+pmA->nLigne,2*(1+pmA->nLigne)*(1+pmA->nLigne)*(1+pmA->nLigne));
		noZero.r=0;noZero.i=0;
		noUn.r=1;noUn.i=0;
		riDelta=noPole[0]=noPole[1]=noZero;
		uSommat=pmA->nLigne;
		Assert2("riFormeCalculeR Mahajan 2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne);
		zComplexiteh=0;
		//noV et noPole soient razés; O(S3)
			for (cComposante=0;cComposante<=1;cComposante++)
				for (noPole[cComposante]=noZero/*VITAL*/,sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;nEtage++)
							noV[cComposante][sH][sX][nEtage]=noZero;
		if (0){
			tee("uSommat",uSommat,uSommat*uSommat*uSommat);
			te("zComplexiteh",zComplexiteh);
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		}
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de noV
			cComposante=uSommat%2;
			nEtage=0;
			for (sH=1;sH<=uSommat;zComplexiteh++,sH++)
				noV[cComposante][sH][sH][nEtage]=noUn;
		if (0)
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (0) {Titrer(sC2b("ETAGE",sEnt(nEtage))); tee("nEtage,uSommat",nEtage,uSommat);}
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (cComposante=0;cComposante<=1;cComposante++)
							for (sZ =sH+1;sZ<=uSommat;zComplexiteh++,sZ++){
								noOperande=noV[cComposante][sH][sY][nEtage];
								noMatYZ=(briNul(pmA->Mat[sY][sZ]))? noZero: pmA->Mat[sY][sZ];
								noProduit=(briNul(noMatYZ) || briNul(noOperande))? noZero: riMul(noOperande,noMatYZ);
								noAvant=noV[cComposante][sH][sZ][nEtage+1];
								if (briNul(noAvant)) noApres=noProduit;
								else if (briNul(noProduit)) noApres=noAvant;
								else noApres=riAdd(noAvant,noProduit);
								noV[cComposante][sH][sZ][nEtage+1]=noApres;
								noMatYH=(briNul(pmA->Mat[sY][sH]))? noZero: pmA->Mat[sY][sH];
								noOperande=noV[cComposante][sH][sY][nEtage];
								noProduit=(briNul(noMatYH) || briNul(noOperande))? noZero: riMul(noOperande,noMatYH);
								noAvant=noV[1-cComposante][sZ][sZ][nEtage+1];
								if (briNul(noAvant)) noApres=noProduit;
								else if (briNul(noProduit)) noApres=noAvant;
								else noApres=riAdd(noAvant,noProduit);
								//if (!bPoly || bDagSimple(noApres))
									noV[1-cComposante][sZ][sZ][nEtage+1]=noApres;
							}
			}
		if (0) printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		if (0) Titrer("dernier etage");
		//traiter le dernier étage; O(S2)
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					noMatYH=pmA->Mat[sY][sH];
					for (cComposante=0;cComposante<=1;cComposante++){
						noOperande=noV[cComposante][sH][sY][uSommat-1];
						noProduit=riMul(noOperande,noMatYH);
						noAvant=noPole[cComposante];
						noApres=riAdd(noAvant,noProduit);//accumulation définie vu assertion yFormeCalculeR3
						noPole[cComposante]=noApres;
					}
				}
		riDelta=riSub(noPole[1],noPole[0]);
		ttt("noPole[1] et noPole[0]",sK(noPole[1]),sK(noPole[0]));
		printf("riDelta=%s.\n",sK3(riDelta));
		//d2(riDelta,kxLongintMax);
		//teee("noPole[1],noPole[0],riDelta APRES",noPole[0],noPole[1],riDelta);
	Appel1("riFormeCalculeR Mahajan");
	return(riDelta);
}//riFormeCalculeR

long yFormeCalculeR(iMatrice *pmA){//O(S4)
	//rend le déterminant (Mahajan et Vinay 1997).
	int nEtage,sH,sX,sY,sZ,cComposante,uSommat;
	long noAvant,noApres,noMatYH,noMatYZ,noOperande,noProduit,noUn,noZero,zComplexiteh,yDelta,noPole[2];
	long ynoV[2][92][92][92];

	d2(1+pmA->nLigne,2*(1+pmA->nLigne)*(1+pmA->nLigne)*(1+pmA->nLigne));
	//long ynoV[2][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];

	//Appel0("yFormeCalculeR Mahajan");
		yDelta=noPole[0]=noPole[1]=0;
		uSommat=pmA->nLigne;
		Assert2("yFormeCalculeR 2",pmA->nLigne>0,pmA->nLigne==pmA->nColonne);
		noZero=0;noUn=1;
		zComplexiteh=0;
		//ynoV et noPole soient razés; O(S3)
			for (cComposante=0;cComposante<=1;cComposante++)
				for (noPole[cComposante]=noZero/*VITAL*/,sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;nEtage++)
							ynoV[cComposante][sH][sX][nEtage]=noZero;
		if (0){
			tee("uSommat",uSommat,uSommat*uSommat*uSommat);
			te("zComplexiteh",zComplexiteh);
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		}
		//Initialiser à noUn l'étage 0 pour les composantes sH identiques de ynoV
			cComposante=uSommat%2;
			nEtage=0;
			for (sH=1;sH<=uSommat;zComplexiteh++,sH++)
				ynoV[cComposante][sH][sH][nEtage]=noUn;
		if (0)
			printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (0) {Titrer(sC2b("ETAGE",sEnt(nEtage))); tee("nEtage,uSommat",nEtage,uSommat);}
				for (sH=1;sH<=iInf(uSommat,nEtage+1);sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
						for (cComposante=0;cComposante<=1;cComposante++)
							for (sZ =sH+1;sZ<=uSommat;zComplexiteh++,sZ++){
								noOperande=ynoV[cComposante][sH][sY][nEtage];
								noMatYZ=(pmA->Mat[sY][sZ]==0)? noZero: pmA->Mat[sY][sZ];
								noProduit=(noMatYZ==noZero || noOperande==noZero)? noZero: noOperande*noMatYZ;
								noAvant=ynoV[cComposante][sH][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noAvant+noProduit;
								ynoV[cComposante][sH][sZ][nEtage+1]=noApres;
								noMatYH=(pmA->Mat[sY][sH]==0)? noZero: pmA->Mat[sY][sH];
								noOperande=ynoV[cComposante][sH][sY][nEtage];
								noProduit=(noMatYH==noZero || noOperande==noZero)? noZero: noOperande*noMatYH;
								noAvant=ynoV[1-cComposante][sZ][sZ][nEtage+1];
								if (noAvant==noZero) noApres=noProduit;
								else if (noProduit==noZero) noApres=noAvant;
								else noApres=noAvant+noProduit;
								//if (!bPoly || bDagSimple(noApres))
									ynoV[1-cComposante][sZ][sZ][nEtage+1]=noApres;
							}
			}
		if (0) printf("**************Complexité %s. Ratio complexité/S3%8.2f\n",sPar3(zComplexiteh),zComplexiteh/(1.0*zPuissance(uSommat,3)));
		if (0) Titrer("dernier etage");
		//traiter le dernier étage; O(S2)
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
					noMatYH=pmA->Mat[sY][sH];
					for (cComposante=0;cComposante<=1;cComposante++){
						noOperande=ynoV[cComposante][sH][sY][uSommat-1];
						noProduit=noOperande*noMatYH;
						noAvant=noPole[cComposante];
						noApres=noAvant+noProduit;//accumulation définie vu assertion yFormeCalculeR3
						noPole[cComposante]=noApres;
					}
				}
		yDelta=noPole[1]-noPole[0];
		d2(noPole[1],noPole[0]);
		d2(yDelta,kxLongintMax);
	//Appel1("yFormeCalculeR Mahajan");
	return(yDelta);
}//yFormeCalculeR

void FormeCaseR(int nMotif,int uLigne,int uColonne,fMathricE **ppmA){
	char cAlphabet[1+52+1]="@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char cMotif;
	//teee("uLigne,uColonne,nMotif",uLigne,uColonne,nMotif);
	cMotif=cAlphabet[nMotif];
	tc("cMotif à créér",cMotif);
	FormeCreeR(sC(cMotif),&((*ppmA)->fForme[uLigne][uColonne]));
}//FormeCaseR

void FormeCopieR(f fAccu,f *pfAccu){
	int nT,nL;
	//	FormeRazeR(pfAccu);
	for (nT=0;nT<=fAccu.num[0][0];nT++)
		for (nL=0;nL<=kuTermeMaX;nL++)
			(*pfAccu).num[nT][nL]=fAccu.num[nT][nL];
	for (nT=0;nT<=fAccu.den[0][0];nT++)
		for (nL=0;nL<=kuTermeMaX;nL++)
			(*pfAccu).den[nT][nL]=fAccu.den[nT][nL];
}//FormeCopieR

void FormeCreeR(char *sProduit,f *pfCible){
	//crée une forme réduite à un produit unique et non pas à une somme de plusieurs produits.
	Assert1("FormeCreeR1",bFormeAmorceR);
	int uC,nL,bNegatif=0,nValeur=0,bQqch;
	int bSigne;
	char cCar;
	int nProduitLg=nChaineLg(sProduit);
	FormeRazeR(pfCible);
	for (uC=1;uC<=kuTermeMaX;uC++)
		(*pfCible).num[1][uC]=0;
	//nValeur soit le terme constant éventuel
		nValeur=0;
		bNegatif=sProduit[0]=='-';
		//te("bNegatif",bNegatif);	
		bSigne=(sProduit[0]=='-' || sProduit[0]=='+');
		nL=bSigne;
		//te("nL",nL);	
		while (bChiffre(sProduit[nL])){
			nValeur=nValeur*10+sProduit[nL++]-'0';
			//nL++;
		}
		if (bSigne && (nValeur==0))
			nValeur=1;
		//te("nValeur finale",nValeur);	
	for (bQqch=0,uC=nL+1;uC<=nProduitLg;uC++){
		cCar=sProduit[uC-1];
		//tc("cCar",cCar);
		Assert1("FormeCreeR2",bMajuscule(cCar) || bMinuscule(cCar));
		(*pfCible).num[1][uC]=cCar;//empile les caractères
		bQqch=uC;
	}
	(*pfCible).num[1][0]=1;//poids du terme
	(*pfCible).num[0][0]=1;//nombre total de termes
	(*pfCible).den[1][0]=1;//poids du terme
	(*pfCible).den[0][0]=1;//nombre total de termes
	//tee("Sommande et Constante finals",pfCible->num[0][0],pfCible->num[1][0]);	
	//FormeVoiR("FormeCreeR final",*pfCible);
}//FormeCreeR
	
void FormeDedoublonneR(f *pfF){
	Assert1("FormeDedoublonneR",bFormeAmorceR);
	int bDoublon,nL,nLettre,uS,uT;
	const int kbVoir=kV;
	const int kbDoublon=kV;
	int nPris,nTerme;
	char cCar;
	Assert1("FormeDedoublonneR",bFormeAmorceR);
	//if (kbVoir) FormeVoiR("AVANT FormeSimplifieR",*pfF);
	nTerme=(*pfF).num[0][0];
	if (kbDoublon){//A2=0 pour A B C.
		for (uS=1;uS<=nTerme;uS++){
			nLettre=nLettraT(*pfF,uS,!k1DenominateuR);
			for (uT=1;uT<nLettre;uT++){
				bDoublon=(*pfF).num[uS][uT]==(*pfF).num[uS][uT+1];
				cCar=cCaracterE(uT);
				if (bDoublon){//supprimer ce terme car c'est un doublon
					if (kbVoir) printf("DOUBLON %c \n",cCar);
					for (nL=0;nL<=kuTermeMaX;nL++)
						(*pfF).num[uS][nL]=0;
				}//if (bDoublon)
			}
		}
	nTerme=(*pfF).num[0][0];
		//supprimer les termes d'occurrence nulle en tassant les termes vers les indices faibles.
			for (nPris=0,uT=1;uT<=nTerme;uT++)
				if ((*pfF).num[uT][0]!=0)
					for (nPris++,nL=0;nL<=kuTermeMaX;nL++)
						(*pfF).num[nPris][nL]=(*pfF).num[uT][nL];
			(*pfF).num[0][0]=nPris;
		}
}//FormeDedoublonneR

void FormeDenonceR(iMatrice *pmA,int noZero){
	//dénonce les appariements d'arêtes non productifs.
	int uC,uL,bConflit;
	int aArc[1+8];
	int nOccurrence[1+pgGrapH->nArcEnTout];
	Appel0("FormeDenonceR");
		GrapheVoir(pgGrapH,"pgGrapH");
		aArc[1]=nGrapheArc(pgGrapH,4,6); aArc[2]=nGrapheArc(pgGrapH,6,4);
		aArc[3]=nGrapheArc(pgGrapH,5,6); aArc[4]=nGrapheArc(pgGrapH,6,5);
		aArc[5]=nGrapheArc(pgGrapH,7,8); aArc[6]=nGrapheArc(pgGrapH,8,7);
		aArc[7]=nGrapheArc(pgGrapH,7,9); aArc[8]=nGrapheArc(pgGrapH,9,7);
		VecteurVoir0("aArc",aArc);
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nLigne;uC++)
				if (pmA->Mat[uL][uC]>0 && pmA->Mat[uL][uC]!=noZero){
					DagConfliter(pmA->Mat[uL][uC],nOccurrence);
					bConflit=kF;
					bConflit=bConflit || (nOccurrence[aArc[1]]>0 || nOccurrence[aArc[2]]>0) && (nOccurrence[aArc[5]]>0 || nOccurrence[aArc[6]]>0) ; 
					bConflit=bConflit || (nOccurrence[aArc[3]]>0 || nOccurrence[aArc[4]]>0) && (nOccurrence[aArc[7]]>0 || nOccurrence[aArc[8]]>0) ;
					if (bConflit){
						VecteurVoir1("nOccurrence[]",nOccurrence,1,19);
						tee("CONFLIT",uL,uC);
						DagArborer(sC2("pmA->Mat",sCrochet(uL,uC)),pmA->Mat[uL][uC],0);
					}
				}
	Appel1("FormeDenonceR");
}//FormeDenonceR

void FormeDiffuseR(int nCoteh,int *pnLigne,int *pnColonne,int *pnMotif,fMathricE **ppmA){
	//motif horizontal allant un peu en bas
	int nC,nColonne,nLigne;
	int nMotif=*pnMotif;
	nColonne=*pnColonne;
	nLigne=*pnLigne;
	for (nC=0;nC<nCoteh;nC++){
		tee("nLigne+nCoteh-nC-1,nColonne-3*nC-1",nLigne+nCoteh-nC-1,nColonne-3*nC-1);
		FormeCaseR(nMotif,nLigne+nCoteh+nC,nColonne+3*nC,ppmA);
	}
	*pnLigne=*pnLigne+nCoteh;
	MotifSuivanT(pnMotif);
}//FormeDiffuseR

void FormeDiviseR(f fA,f fB,f *pfC){
	//divise fA par fB formellement
	Assert1("FormeDiviseR initial",bFormeAmorceR);
	const int kbVoir=kF;
	if (kbVoir) FormeVoiR("fA",fA);
	if (kbVoir) FormeVoiR("fB",fB);
	FormeInverseR(&fB);
	if (kbVoir) FormeVoiR("fB inversé",fB);
	FormeMultiplieR(fA,fB,pfC);
	FormeSimplifieR(pfC);
	if (kbVoir) FormeVoiR("FormeDiviseR final",*pfC);
}//FormeDiviseR

void FormeEntreEtageR(int nCoteh,int *pnLigne,int *pnColonne,int *pnMotif,fMathricE **ppmA){
	//matérialise tous les arcs qui relient deux étages consécutifs
	//appel depuis MathriceEvalueR
	int nC,nL;
	for (nL=0;nL<nCoteh;nL++)
		for (nC=0;nC<nCoteh;nC++)
			if (nL!=nC){
				tee("FormeEntreEtageR *pnLigne-nCoteh+nL,*pnColonne+nC",*pnLigne-nCoteh+nL,*pnColonne+nC);
				FormeCaseR(*pnMotif,*pnLigne-nCoteh+nL,*pnColonne+nC,ppmA);
			}
	MotifSuivanT(pnMotif);
}//FormeEntreEtageR

char *sFormeFeuille(int noFeuille){
	//rend le caractère majuscule de rang noFeuille: 1 donne A, 2 donne B, etc, prolongé par 0 donne @.
	int aK;
	char *sFeuille;
	//Appel0("sFormeFeuille");
		if (1 && pgGrapH!=NULL){
			aK=noFeuille-1;
			sFeuille=sGrapheArc(pgGrapH,aK);//rend un couple (sX,sY)
		}else if (noFeuille==0)
			sFeuille=sC('0');
		else sFeuille=sC('@'+noFeuille);
	//Appel1("sFormeFeuille");
	return(sFeuille);
}//sFormeFeuille

void FormeFoisseR(int iFois,f *pfC){
	Assert1("FormeFoisseR",bFormeAmorceR);
	int uA;
	int nSommande=(*pfC).num[0][0];
	for (uA=1;uA<=nSommande;uA++)
		(*pfC).num[uA][0]*=iFois;
}//FormeFoisseR

void FormeGrapheR(iMatrice *pmA,int noZero){
	//affiche les éléments de pmA. Chaque élément est une union de parcours fermés affichée sous forme arborescente.
	int uC,uL;
	Appel0("FormeGrapheR");
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nLigne;uC++)
				if (pmA->Mat[uL][uC]>0 && pmA->Mat[uL][uC]!=noZero)
					DagArborer(sC2("pmA->Mat",sCrochet(uL,uC)),pmA->Mat[uL][uC],0);
	Appel1("FormeGrapheR");
}//FormeGrapheR

void FormeINITIALISER(){
	//relance le présent module
	Assert1("FormeINITIALISER",bFormeAmorceR);
}//FormeINITIALISER

void FormeInverseR(f *pfA){
	//échange numérateur et dénominateur
	Assert1("FormeInverseR",bFormeAmorceR);
	const int kbVoir=kF;
	int uS,nL;
	if (kbVoir) FormeVoiR("FormeInverseR0",*pfA);
	for (uS=0;uS<=kuSommandeMaX;uS++){
		for (nL=0;nL<=kuTermeMaX;nL++)
			EntierEchanger(&(pfA->num[uS][nL]),&(pfA->den[uS][nL]));
	}
	//pfA->num[0][0]=pfA->den[0][0];
	if (kbVoir) FormeVoiR("FormeInverseR1",*pfA);
}//FormeInverseR

long yFormeKalculeR(iMatrice *pmA,int nDim,int bVoir){//O(S3.5) exact car sans division
	//vrai ssi le déterminant par la méthode de Urbanska est nul
	int bOptimiser35=kF;
	int bGrapheConserver=kF;
	int bColonnesImpairesVides;
	int uC,uL;
	long yKalculer;
	int nSommetTraversehParMotif=5;
	int nArcTraversehPourAtteindreEtageSuivant=1;//et circulairement
	int uParcoursLgMax=(nDim>1)? nDim*(nSommetTraversehParMotif+nArcTraversehPourAtteindreEtageSuivant): pmA->nLigne;
	if (bVoir) Titrer("yFormeKalculeR");
	//te("uParcoursLgMax",uParcoursLgMax);
	iMatrice *pmAchappo;
	//Appel0(sC2b("yFormeKalculeR",sP(sC2b("dimension",sEnt(nDim)))));
		bColonnesImpairesVides=(nDim>0);
		bColonnesImpairesVides=kF;
		if (bVoir) tb("bColonnesImpairesVides",bColonnesImpairesVides);
		//if (bColonnesImpairesVides) pmA->nSecante=-2;
		//if (bVoir) MatriceVoir("Calcul du déterminant Urbanska sur la matrice ci-dessous",pmA);
		Assert2("yFormeKalculeR2",pmA->nLigne==pmA->nColonne,bCroit(1,pmA->nLigne,kE2));
		MatriceAllouer2(&pmAchappo,pmA->nLigne,uParcoursLgMax);
		//Assert1("yFormeKalculeR",uParcoursLgMax==pmA->nLigne);
			//tee("SkewClosurE0:pmAchappo->nLigne,pmAchappo->nColonne",pmAchappo->nLigne,pmAchappo->nColonne);
		if (bColonnesImpairesVides)
			pmAchappo->nSecante=-2;
		else pmAchappo->nSecante=0;

		if (bOptimiser35)
			SkewClosurE1(pmA,&pmAchappo);//O(N3.5)
		else if (!bGrapheConserver)
			SkewClosurE0(pmA,uParcoursLgMax,&pmAchappo);//O(N4)
		else SkewClosurE2(pmA,uParcoursLgMax,&pmAchappo);
		//tb("bColonnesImpairesVides",bColonnesImpairesVides);
		if (bColonnesImpairesVides)
			pmAchappo->nSecante=-2;
		else pmAchappo->nSecante=0;
		//tee("bColonnesImpairesVides,pmAchappo->nSecante",bColonnesImpairesVides,pmAchappo->nSecante);
		if (bVoir) MatriceVoir("Matrice pmAchappo (head x longueur) des sommes des produits des CLOWs avant cplémtO",pmAchappo);
			if (0 && nDim>1){//ds pmAchappo, annuler les colonnes de lgr hors 2 et nDim*6
				Titrer("Censure des cycles trop longs");
				for (uL=1;uL<=2*nDim;uL++)
					for (uC=3;uC<=pmAchappo->nColonne;uC++)
						pmAchappo->Mat[uL][uC]=0;
				//pmAchappo->Mat[1][nDim*6]=1;
				MatriceUnifier(pmAchappo);
			}
		//rendre (-1)**N * KnapsacK(- pmAchappo)
			//if (nDim==0)
				MatriceFoisser(-1,&pmAchappo);
		//MatriceVoir("pmAchappo après censure",pmAchappo);
		//tee("bColonnesImpairesVides,pmAchappo->nSecante",bColonnesImpairesVides,pmAchappo->nSecante);
			pmAchappo->nLigne=pmA->nLigne;
			pmAchappo->nColonne=pmA->nLigne;
			//tee("yKnapsacK:pmAchappo->nLigne,pmAchappo->nColonne",pmAchappo->nLigne,pmAchappo->nColonne);
			yKalculer=yKnapsacK(pmAchappo,1 && bColonnesImpairesVides,bVoir);//O(N3)
			//corriger en prenant le modulo 
			if (0){
				t("Correction modulo");
				if (yKalculer<0){
					yKalculer= - ( (-yKalculer)%15);
				}else yKalculer=yKalculer%15;
			}
			yKalculer=ySignePres(bImpair(pmA->nLigne),yKalculer);
			if (bVoir) te("DETERMINANT",yKalculer);
		//iBof=iKnaP(pmAchappo);
		//printf("Déterminant Urbanska: %ld.\n",yKalculer);
	//Appel1(sC2b("yFormeKalculeR",sP(sC2b("dimension",sEnt(nDim)))));
	return(yKalculer);
}//yFormeKalculeR

void FormeLongrineR(graf *pgG,int coUn,int coBeaucoup,graf **ppgH){
	//génère ds ppgH un carrousel de uPivotEnTout doublets de pivots liés à des longrines, lesquelles sont les images des sommets de pgG.
	int uPivotEnTout=pgG->nSommetEnTout;
	const int bVoir=kF;
	int nOffset;
	int nPoleEnTout=2*pgG->nSommetEnTout;
	int nArcat;
	int nQuadripole,aK,sX,sY,uP,nQ;
	int nSommat=pgG->nSommetEnTout;
	int nSommetApres;//dédié ppgH
	int szSortie[1+nSommat];
	int szEntree[1+nSommat];
	Assert1("FormeLongrineR",uPivotEnTout>0);
	//d3(pgG->nArcEnTout,uPivotEnTout,nPoleEnTout);
	nArcat=pgG->nArcEnTout;
	nSommetApres=nPoleEnTout+8*nArcat;//8 sommets par longrine.
	GrapheSymetriser(pgG);//AVANT li+1; ainsi,pgG ne peut plus avoir quelques arcs opposés qui compliquent le calcul faute de symétrisation complète.
//d3(pgG->nArcEnTout,nPoleEnTout,nSommetApres);
	if (bVoir) GrapheVoir(pgG,sC2b("pgG symétrisé pour",sPluriel(uPivotEnTout,"pivot")));
		if (bVoir) te("nSommetApres",nSommetApres);
		GrapheCreer(-nSommetApres,ppgH);//réserve 8 sommets par longrine puis 2 sommets par pivot: 1 pôle nord P et 1 pôle sud P+1.
		VecteurRazer(szEntree,1,nSommat);//szEntree[sX] mémorise à terme les origines des circuits du futur graphe
		VecteurRazer(szSortie,1,nSommat);//szSortie[sX] mémorise à terme les extrémités des circuits du futur graphe
		//relier (liens externes) les quadripôles aux autres quadripôles ainsi qu'aux pivots
			nCouvertureBanniR=0;
			EntierDepilerTout();//vide la pile de Outil.c
			//connecter les pivots amont aux entrées (hautes) des quadripoles et relier les quadripoles entre eux le cas échéant (il y a une arête ds pgG)
				nOffset=4*pgG->nArcEnTout;//les pôles ont des numéros situés après le pack de 4*pgG->nArcEnTout sommets dédiés longrines 
				if (bVoir) d2(nSommat,nOffset);
				for (nQuadripole=0,sX=1;sX<=nSommat;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						if (sX<sY){
							if (bVoir) printf("         Arc rencontré: %s.\n",sCouple(sX,sY));
							if (szSortie[sX]==0){
								szEntree[sX]=4*nQuadripole+1;
								//d2(nOffset+2*sX-1,4*nQuadripole+1);
								GrapheArquer1(*ppgH,nOffset+2*sX-1,4*nQuadripole+1,coUn);
							} else GrapheArquer1(*ppgH,szSortie[sX],4*nQuadripole+1,coUn);
							szSortie[sX]=4*nQuadripole+3;
							
							if (szSortie[sY]==0){
								szEntree[sY]=4*nQuadripole+2;
								//d2(nOffset+2*sY-1,4*nQuadripole+2);
								GrapheArquer1(*ppgH,nOffset+2*sY-1,4*nQuadripole+2,coUn);
							}else GrapheArquer1(*ppgH,szSortie[sY],4*nQuadripole+2,coUn);
							szSortie[sY]=4*nQuadripole+4;
							nQuadripole++;
						}
					}
				if (bVoir) printf("Nombre total de quadripoles générés: %d.\n",nQuadripole);
			//VecteurVoir("szEntree",szEntree,1,nSommat);
			//VecteurVoir("szSortie",szSortie,1,nSommat);
			//connecter les sorties (basses) des quadripoles aux pivots aval
				for (sX=1;sX<=nSommat;sX++){
					//d3(szSortie[sX],nOffset+2*sX-0,coUn);
					GrapheArquer1(*ppgH,szSortie[sX],nOffset+2*sX-0,coUn);
				}
		//relier le pôle nord de chaque pivot à son pôle sud
			for (uP=1;uP<=uPivotEnTout;uP++){
				//d3(nOffset+2*uP-1, nOffset+2*uP-0,coBeaucoup);
				GrapheArquer1(*ppgH,nOffset+2*uP-1, nOffset+2*uP-0,coBeaucoup);
			}
	if (bVoir) GrapheVoir0(*ppgH,"ppgH creux",grCouleur);
		//former le carrousel,ie le circuit qui passe par chaque doublet de pôles nord et sud
			//for (uP=1;uP<=uPivotEnTout;uP++)
				//GrapheArquer1(*ppgH,nOffset+2*uP-0, nOffset+2*((uP+1<=uPivotEnTout)? uP+1:1)-1,coUn);
	if (bVoir) GrapheVoir0(*ppgH,"ppgH creux",grCouleur);
		//expliciter les quadripôles en les remplaçant par des longrines: les coins des quadripôles deviennent ceux des longrines.
			for (nQ=0;nQ<nQuadripole;nQ++)//NB li+1,la routine ajoute 10 arcs par longrine ––les sommets ont déjà été alloués en créant ppgH.
				QuadripoleLongrineR(nQuadripole,nQ,k1Symetriser,*ppgH);
	if (bVoir) GrapheVoir0(*ppgH,"ppgH FINAL longriné",grCouleur);
	Assert1("FormeLongrineR8",bGrapheBiparti(*ppgH));
}//FormeLongrineR

void FormeLongrineR2(int uPivotEnTout,graf *pgG,int bBipartitionner,int bPoleBannir,graf **ppgH){
	//génère ds ppgH uPivotEnTout pivots (dédoublés si bBipartitionner) liés à des longrines, lesquelles sont les images des sommets de pgG.
	const int kbPoidsDistinct2a2=kV;
	const int bVoir=kF;
	int uArcPoids,nOffset;
	int nPoleEnTout=uPivotEnTout*(1+bBipartitionner);
	int nQuadripole,aK,sX,sY,uP,nQ;
	int nSommat=pgG->nSommetEnTout;
	int nSommetApres;//dédié ppgH
	int szSortie[1+nSommat];
	int szEntree[1+nSommat];
	Assert2("FormeLongrineR2",uPivotEnTout>0,bBool(bBipartitionner));
	GrapheSymetriser(pgG);//AVANT li+1; ainsi,pgG ne peut plus avoir quelques arcs opposés qui compliquent le calcul faute de symétrisation complète.
	nSommetApres=nPoleEnTout+(4*pgG->nArcEnTout);//soit 8 sommets par arête, alias 8 sommets par longrine.
//d3(pgG->nArcEnTout,nPoleEnTout,nSommetApres);
	if (bVoir) GrapheVoir(pgG,sC2b("pgG symétrisé pour",sPluriel(uPivotEnTout,"pivot")));
		if (bVoir) te("nSommetApres",nSommetApres);
		GrapheCreer(-nSommetApres,ppgH);//réserve 8 sommets par longrine puis 2 sommets par pivot: 1 pôle nord P et 1 pôle sud P+1.
		VecteurRazer(szEntree,1,nSommat);//szEntree[sX] mémorise à terme les origines des circuits du futur graphe
		VecteurRazer(szSortie,1,nSommat);//szSortie[sX] mémorise à terme les extrémités des circuits du futur graphe
		//relier (liens externes) les quadripôles aux autres quadripôles ainsi qu'aux pivots
			nCouvertureBanniR=0;
			EntierDepilerTout();//vide la pile de Outil.c
			//connecter les pivots amont aux entrées (hautes) des quadripoles et relier les quadripoles entre eux le cas échéant (il y a une arête ds pgG)
				nOffset=(4*pgG->nArcEnTout);//les pôles ont des numéros situés après le pack de 4*pgG->nArcEnTout sommets dédiés longrines 
				if (bVoir) d(nOffset);
				for (nQuadripole=0,sX=1;sX<=nSommat;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						if (sX<sY){
							if (bVoir) printf("         Arc rencontré: %s.\n",sCouple(sX,sY));
							if (szSortie[sX]==0){
								szEntree[sX]=4*nQuadripole+1;
								for (uP=1;uP<=uPivotEnTout;uP++)
									GrapheArquer(*ppgH,nOffset+2*uP-1,4*nQuadripole+1);
							} else GrapheArquer(*ppgH,szSortie[sX],4*nQuadripole+1);
							szSortie[sX]=4*nQuadripole+3;
							
							if (szSortie[sY]==0){
								szEntree[sY]=4*nQuadripole+2;
								for (uP=1;uP<=uPivotEnTout;uP++)
									GrapheArquer(*ppgH,nOffset+2*uP-1,4*nQuadripole+2);
							}else GrapheArquer(*ppgH,szSortie[sY],4*nQuadripole+2);
							szSortie[sY]=4*nQuadripole+4;
							nQuadripole++;
						}
					}
				if (bVoir) printf("Nombre total de quadripoles générés: %d.\n",nQuadripole);
			//connecter les sorties (basses) des quadripoles aux pivots aval (distincts des pivots amont ssi bBipartitionner)
				for (sX=1;sX<=nSommat;sX++)
					for (uP=1;uP<=uPivotEnTout;uP++)
						GrapheArquer(*ppgH,szSortie[sX],(bBipartitionner)? nOffset+2*uP-0: nOffset+2*uP-1);
		if (bBipartitionner) //relier le pôle sud de chaque pivot à son pôle nord
			for (uP=1;uP<=uPivotEnTout;uP++)
				GrapheArquer(*ppgH,nOffset+2*uP-0, nOffset+2*uP-1);
		if (bBipartitionner && bPoleBannir)
			PoleBanniR(uPivotEnTout,nSommat,nOffset,szEntree,szSortie);//bannit les segments non symétriques qui passent par les pôles
	if (bVoir) GrapheVoir(*ppgH,"ppgH creux");
		//expliciter (liens internes) les quadripôles en les remplaçant par des longrines de sorte que les coins des quadripôles deviennent ceux des longrines.
			for (nQ=0;nQ<nQuadripole;nQ++)//NB li+1,la routine ajoute 10 arcs par longrine ––tous les sommets des longrines ont déjà été alloués en créant ppgH.
				QuadripoleLongrineR(nQuadripole,nQ,!k1Symetriser,*ppgH);
	//renuméroter les couleurs des arcs externes aux longrines de sorte que leurs couleurs soient distinctes 2 à 2 et diffèrent de 0 et 1,éléments neutres de + et *.
		if (kbPoidsDistinct2a2){
			for (uArcPoids=1,aK=1;aK<=(*ppgH)->nArcEnTout;aK++)
				if ((*ppgH)->coulh[aK]<0)
					(*ppgH)->coulh[aK]=-(++uArcPoids);
			for (aK=1;aK<=(*ppgH)->nArcEnTout;aK++)
				if ((*ppgH)->coulh[aK]>=0)
					(*ppgH)->coulh[aK]=++uArcPoids;
			if (1)//poids positifs égalt pour les arcs internes aux longrines
				for (aK=1;aK<=(*ppgH)->nArcEnTout;aK++)
					if ((*ppgH)->coulh[aK]<0)
						(*ppgH)->coulh[aK]=nAbs((*ppgH)->coulh[aK]);
		}
	if (bVoir) GrapheVoir0(*ppgH,"ppgH FINAL longriné",grCouleur);//ttes les couleurs des arcs internes (externes) aux longrines sont négatives (positives et distinctes).
	Assert1("FormeLongrineR21",!bBipartitionner || bGrapheBiparti(*ppgH));
}//FormeLongrineR2

void FormeMutualiseR(f fA,f fB,f *pfA,f *pfB){
	//réduit au même dénominateur pfA et pfB
	Assert1("FormeMutualiseR",bFormeAmorceR);
	const int kbVoir=kF;
	int uA,uB,nCible,uL,nLettreA,nLettreB;
	int nSommandeA,nSommandeB;
	if (kbVoir) FormeVoiR("FormeMutualiseR gauche",fA);
		//	Assert1("FormeMutualiseR03",fA.num[1][0]!=0);
	if (kbVoir) FormeVoiR("FormeMutualiseR droite",fB);
		//	Assert1("FormeMutualiseR04",fB.num[1][0]!=0);
	FormeRazeR(pfA);
	FormeRazeR(pfB);
	//multiplier le numérateur de fA par le dénominateur de fB
		for (nCible=0,uA=1;nSommandeA=fA.num[0][0],nSommandeB=fB.den[0][0],uA<=nSommandeA;uA++){
			nLettreA=nLettraT(fA,uA,!k1DenominateuR);
			Assert2("FormeMutualiseR78",nLettreA>0,fA.num[uA][0]!=0);
			for (uB=1;uB<=nSommandeB;uB++){//fabriquer 1 produit
				nCible++;
				nLettreB=nLettraT(fB,uB,k1DenominateuR);
				Assert2("FormeMutualiseR54",nLettreB>0,fB.den[uB][0]!=0);
				for (uL=1;uL<=nLettreA;uL++)
					pfA->num[nCible][uL]=fA.num[uA][uL];
				for (uL=1;uL<=nLettreB;uL++)
					pfA->num[nCible][nLettreA+uL]=fB.den[uB][uL];
				pfA->num[nCible][0]=fA.num[uA][0]*fB.den[uB][0];//produit des poids, 1 par produit
			}
		}
		//teee("nSommandeA,nSommandeB,nCible",nSommandeA,nSommandeB,nCible);
		pfA->num[0][0]=nCible;
	//multiplier le numérateur de fB par le dénominateur de fA
		for (nCible=0,uB=1;nSommandeB=fB.num[0][0],nSommandeA=fA.den[0][0],uB<=nSommandeB;uB++){
			nLettreB=nLettraT(fB,uB,!k1DenominateuR);
			for (uA=1;uA<=nSommandeA;uA++){//fabriquer le terme produit
				nCible++;
				nLettreA=nLettraT(fA,uA,k1DenominateuR);
				for (uL=1;uL<=nLettreB;uL++)
					pfB->num[nCible][uL]=fB.num[uB][uL];
				for (uL=1;uL<=nLettreA;uL++)
					pfB->num[nCible][nLettreB+uL]=fA.den[uA][uL];
				pfB->num[nCible][0]=fB.num[uB][0]*fA.den[uA][0];//produit des poids, 1 par produit
			}
		}
		//teee("nSommandeA,nSommandeB,nCible",nSommandeA,nSommandeB,nCible);
		pfB->num[0][0]=nCible;
	//multiplier tous les dénominateurs entre eux
		for (nCible=0,uB=1;nSommandeB=fB.den[0][0],nSommandeA=fA.den[0][0],uB<=nSommandeB;uB++){
			nLettreB=nLettraT(fB,uB,k1DenominateuR);
			for (uA=1;uA<=nSommandeA;uA++){//fabriquer le terme produit
				nCible++;
				nLettreA=nLettraT(fA,uA,k1DenominateuR);
				for (uL=1;uL<=nLettreB;uL++)
					pfA->den[nCible][uL]=pfB->den[nCible][uL]=fB.den[uB][uL];
				for (uL=1;uL<=nLettreA;uL++)
					pfA->den[nCible][nLettreB+uL]=pfB->den[nCible][nLettreB+uL]=fA.den[uA][uL];
			}
			pfA->den[nCible][0]=pfB->den[nCible][0]=fA.den[uA][0]*fB.den[uB][0];//produit des poids
			if (pfA->den[nCible][0]==0)
				pfA->den[nCible][0]=1;
			if (pfB->den[nCible][0]==0)
				pfB->den[nCible][0]=1;
			Assert2("FormeMutualiseR3",pfA->den[nCible][0]!=0,pfB->den[nCible][0]!=0);
		}
		pfA->den[0][0]=pfB->den[0][0]=nSommandeA*nSommandeB;
	//teeeee("pfA->num[0][0]",pfA->num[0][0],nLettraT(*pfA,1,!k1DenominateuR),nLettraT(*pfA,2,!k1DenominateuR),nLettraT(*pfA,3,!k1DenominateuR),nLettraT(*pfA,4,!k1DenominateuR));
	if (kbVoir) FormeVoiR("fA réduite",*pfA);
	if (kbVoir) FormeVoiR("fB réduite",*pfB);
}//FormeMutualiseR

int iKnaP(iMatrice *pmA){
	//calculer la somme alternée de tous les produits de pmA de longueur totale pmA->nLigne 
	int nG,nGmax,uP,iProduit,nReste,muSigne,nSomme,nTerme;
	int iKnap=0;
	int uNmax=pmA->nLigne;
	int uNlim=uNmax+1;
	int T[1+6];
	Assert1("iKnaP",uNmax<=6);
	MatriceVoir("iKnaP pmA complémentéééééééééééééééééééééé",pmA);
	nGmax=zPuissance(uNmax,uNlim);
	te("nGmax",nGmax);
	for (iKnap=0,nG=0;nG<nGmax;nG++){
		//te("nG",nG);
		for (nReste=nG,uP=1;uP<=uNlim;uP++){
			T[uP]=nReste%uNlim;
			nReste=nReste/uNlim;
		}
		for (nSomme=0,uP=1;uP<=uNmax;uP++)
			nSomme+=T[uP];
		//te("nSomme",nSomme);
		if (nSomme==uNmax){
			for (nSomme=0,uP=1;uP<=uNmax ;uP++)
				printf(" %d",T[uP]);
			printf(".\n");
			for (nTerme=0,uP=1;uP<=uNmax ;uP++)
				nTerme+=T[uP]>0;
			muSigne=(bPair(nTerme))? 1: -1;
			for (iProduit=1,uP=1;uP<=uNmax;uP++)
				if (T[uP]>0)
					iProduit*=pmA->Mat[uP][T[uP]];
			tee("muSigne,iProduit",muSigne,iProduit);
			iKnap+=muSigne*iProduit;
		}
	}//nG
	te("iKnap",iKnap);
	return(iKnap);
}//iKnaP

long yKnapsacK(iMatrice *pmA,int bColonnesImpairesVides,int bVoir){//O(N3)
	//rend la valeur du knapsack (les valeurs successives sont calculées dans la matrice pKnapsack;résultat au bout de la diag principale).
	int uLg,uHead,uP;
	long yKnapsacK,yTerme,zSommeProduit;
	iMatrice *pKnapsack;
	pmA->nSecante=-2*bColonnesImpairesVides;
	//tee("yKnapsacK:bColonnesImpairesVides,pmAchappo->nSecante",bColonnesImpairesVides,pmA->nSecante);
	//if (bVoir) MatriceVoir("Matrice complémentée (head de clow x longueur de clow) des sommes de produits reçue par yKnapsacK",pmA);
	MatriceAllouer2(&pKnapsack,pmA->nLigne,pmA->nColonne);
		pKnapsack->nSecante=-2*bColonnesImpairesVides;
		for (uLg=1;uLg<=pmA->nColonne;uLg++)
			pKnapsack->Mat[1][uLg]=pmA->Mat[1][uLg];
		for (uHead=2;uHead<=pmA->nLigne;uHead++)//O(N2) //******* BUG ALGORITHMICA (2010) 56:35-50 p41:"for i,j from 1 to n we compute" vs from 2.
			for (uLg=1+bColonnesImpairesVides;uLg<=pmA->nColonne;uLg+=1+bColonnesImpairesVides){//O(N2)
				//Table[i,j]=∑ sur 0<p<j de (Table[i-1,p]xA[i,j-p])+Table[i-1,j]
				for (zSommeProduit=0,uP=1+bColonnesImpairesVides;uP<uLg;uP+=1+bColonnesImpairesVides){//O(N)
					yTerme=pmA->Mat[uHead][uLg-uP];
					zSommeProduit+=pKnapsack->Mat[uHead-1][uP]*yTerme;
				}
				yTerme=pKnapsack->Mat[uHead-1][uLg];
				pKnapsack->Mat[uHead][uLg]=zSommeProduit + yTerme;
			}
		//if (bColonnesImpairesVides) MatriceUnifier(pKnapsack);
		if (bVoir)
			MatriceVoir("Matrice pKnapsack (head x longueur totale) des sommes de produits de SÉQUENCES de clows",pKnapsack);
		yKnapsacK=pKnapsack->Mat[pmA->nLigne][pmA->nColonne];
	free(pKnapsack);
	return(yKnapsacK);
}//yKnapsacK

void PileVoiR(char *sMessage,int sPile[]){
	int uP;
	printf("%s: ",sMessage);
	for (uP=1;uP<=sPile[0];uP++)
		printf("%2d,",sPile[uP]);
	printf(" (%s).\n",sPluriel(sPile[0],"élément"));
}//PileVoiR

void PoleBanniR(int uPivotEnTout,int nSommat,int nOffset,int szEntree[],int szSortie[]){
	//bannit les segments non symétriques qui passent par les pôles;dédié FormeLongrineR2()
	int uAmont,uAval,uP;
	//VecteurVoir("szEntree",szEntree,1,nSommat);
	//VecteurVoir("szSortie",szSortie,1,nSommat);
	//d2(uPivotEnTout,nSommat);
	for (uP=1;uP<=uPivotEnTout;uP++)
		for (uAmont=1;uAmont<=nSommat;uAmont++)
			for (uAval=1;uAval<=nSommat;uAval++)
				if (uAmont!=uAval){
					//d3(uP,uAmont,uAval);
					//d4(szSortie[uAval],nOffset+2*uP-0,nOffset+2*uP-1,szEntree[uAmont]);
					BanniR(szSortie[uAval],nOffset+2*uP-0,nOffset+2*uP-1,szEntree[uAmont]);
				}
}//PoleBanniR

void QuadripoleLongrineR(int nQuadripole,int nQuad,int bSymetriser,graf *pgG){
	//remplit le quadripole n°nQuad avec la longrine orientée kcLongrine8 à 8 sommets et 10 arcs
	const int kuCoinNb=4;
	const int kbVoir=kF;
	//const int kbBannir =kV;
	graf *pgH;
	int nOffset=4*nQuadripole;
	int sA=4*nQuad+1,sB=sA+1,sC=sB+1,sD=sC+1;
	int iCouleur,nSommat;
	int aK,sU,sV,sX,sY;
	int sCoin[1+4]={-1,sA,sB,sC,sD};
	int sPapillon[1+4]={-1,sA,sB,sC,sD};
	if (kbVoir) d5(sA,sB,sC,sD,nOffset);
	Assert5("QuadripoleLongrineR0",bGrapheSommet(pgG,sA),bGrapheSommet(pgG,sB),bGrapheSommet(pgG,sC),bGrapheSommet(pgG,sD),bDistinct4(sA,sB,sC,sD) );
	//char kcLongrine8[]="AE1BF1CH2DG2EB2EG7FA2FH8GC1HD1";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
	char kcLongrine8[]="AE1BF2CH8DG7EB4EG9FA3FH0GC5HD6";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
	//char kcLongrine8[]="AC1BD1CB3CE1DA3DF1EG1FH1GF3HE3";//NB coins: A,B,G et H.
	GrapheGenerer(kcLongrine8,&pgH);
		if (kbVoir) GrapheVoir(pgH,"Graphe kcLongrine8");
		nSommat=pgG->nSommetEnTout;//avant li+2
		if (kbVoir) te("pgG->nSommetEnTout après empilt",pgG->nSommetEnTout);
		if (kbVoir) GrapheVoir(pgG,"pgG");
		//créer dans pgG autant d'arcs (sX,sY) qu'il y a d'arcs (sU,sV) dans pgH qui décrit kcLongrine8,
			for (sU=1;sU<=pgH->nSommetEnTout;sU++)
				for (aK=pgH->aHed[sU];aK<pgH->aHed[sU+1];aK++){
					sV=pgH->sSuk[aK];
					//printf("Arc de kcLongrine8: %s.\n",sCouple(sU,sV));
					sX=(sU<=kuCoinNb)? sCoin[sU]: sCoin[sU-kuCoinNb]+nOffset;//ie si (sU>kuCoinNb),sU interne à kcLongrine8; enlever 4 donne tjrs un coin et un seul dc… 
					sY=(sV<=kuCoinNb)? sCoin[sV]: sCoin[sV-kuCoinNb]+nOffset;//…sCoin[sU-4] cvertit ce coin pgH en coin pgG,et +nOffset cvertit ce sommet en sommet interne pgH.
					//teeee("sU,sV,sX,sY",sU,sV,sX,sY);
					Assert3("QuadripoleLongrineR6",bGrapheSommet(pgG,sX),bGrapheSommet(pgG,sY),sX!=sY);
					iCouleur= pgH->coulh[aK];
					if (!bSymetriser){
						//teee("sX,sY,nCouleur",sX,sY,iCouleur);
						//d3(sX,sY,iCouleur);
						GrapheArquer1(pgG,sX,sY,-iCouleur);
					}else GrapheAreter1(pgG,sX,sY,iCouleur);
					if (sU>=7)
						sPapillon[sU-6]=sX;//ainsi sPapillon décrit le papillon aval de la longrine courante 
				}
			/*if (kbBannir && bSymetriser){//le papillon est banni à l'aide de deux segments; les extrémités de chacun d'eux sont les diagonales du papillon
				//d4(sPapillon[1],sPapillon[2],sPapillon[3],sPapillon[4]);
				BanniR(sPapillon[3],sPapillon[2],sPapillon[4],sPapillon[1]);
				BanniR(sPapillon[4],sPapillon[1],sPapillon[3],sPapillon[2]);
			}*/
		if (kbVoir) GrapheVoir0(pgG,"pgG *********longriné",grCouleur);
	free(pgH);
}//QuadripoleLongrineR

void QuadripoleMinimalTESTER1(iMatrice *pmE){
	enum eLettre {Z,U,A,B,C,D,E,F,G};
	int uC,uL;
	quad qSignature;
	qMatrice *pmqA;
	//Appel0("QuadripoleMinimalTESTER1");
		pmE->nLigne=pmE->nColonne=5;
		ArqueR(1,2,A,pmE);
		ArqueR(2,3,B,pmE);
		ArqueR(3,4,C,pmE);
		ArqueR(4,5,D,pmE);
		ArqueR(5,1,E,pmE);
		ArqueR(3,1,F,pmE);
		ArqueR(3,2,G,pmE);
		MatriceVoir("pmE",pmE);
t("hhhhhhhh");
		if (1){
			DeterminantConfronteR(pmE);
			MatriceTransposer(pmE);
			MatriceVoir("pmE transposé",pmE);
			DeterminantConfronteR(pmE);
			//MatriceTransposer(pmE);
		}
t("iiiiiiiii");
		yBof=iFormeCalculeR(pmE);//Mahajan noeud
t("jjjjjjjjj");
		
		if (0){
			pmqA=malloc(sizeof(qMatrice));
			pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
			for (uL=1;uL<=pmE->nLigne;uL++)
				for (uC=1;uC<=pmE->nLigne;uC++)
					pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
			QuadMatriceVoir("pmqA",pmqA);
			//bBof=bQuadDeterminer(pmqA);//Mahajan quad
			printf("******DÉTERMINANT par iFormeCalculeR: %ld.\n",yBof);
			//iBof=iFormeQalculeR(pmE,0);//Urbanska quad
		}
		if (0){//transposer
			for (uL=1;uL<=pmE->nLigne;uL++)
				for (uC=1;uC<=pmE->nLigne;uC++)
					pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uC][uL]);
			zAppelExponentieL=0;
			qSignature=qSignatureQalculeR(pmqA,k1Alterner);
			printf("************************** SIGNATURE: %s.\n",sQuad(qSignature));
		}
	//Appel1("QuadripoleMinimalTESTER1");
}//QuadripoleMinimalTESTER1

void GrafMatriceR(graf *pgG,iMatrice **ppmE){
	//déroule pgG dans la matrice
	int bMode=1;
	enum eLettre {Z,U,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,V,W,X,Y};//NB oui,Z et U en tête,et ds cet ordre.
	int nBas,nHaut,nEtage,nMotif,nMotifEnTout,uPoleNord,dX,dY,nSommet;
	nSommet=pgG->nSommetEnTout;
	int ukMotifCard=(bMode)? 8:10;
	nMotifEnTout=pgG->nSommetEnTout*pgG->nSommetEnTout;
	MatriceAllouer1(ppmE,(ukMotifCard*nMotifEnTout+2*nSommet)/2);
	//générer les motifs et les relier aux sélecteurs
		for (uPoleNord=1,dX=0,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			if (bMode) AreteR(dX+1,dX+2,A,-A,*ppmE);else AreteR2(dX+1,dX+5,A,-A,*ppmE); 
			if (bMode) AreteR(dX+1,dX+4,B,-B,*ppmE);else AreteR2(dX+3,dX+5,B,-B,*ppmE); 
			if (bMode) AreteR(dX+2,dX+3,C,-C,*ppmE);else AreteR2(dX+1,dX+9,C,-C,*ppmE);
			//if (bMode) nBof++;else AreteR2(dX+8,dX+8,D,-D,*ppmE);
			//tee("8*nMotifEnTout+uPoleNord,dX+7",8*nMotifEnTout+uPoleNord,dX+7);
			//te("8*nMotifEnTout+uPoleNord",8*nMotifEnTout+uPoleNord);
			if (bMode) AreteR(dX+3,(ukMotifCard*nMotifEnTout+uPoleNord+1)/2,U,-U,*ppmE);
			else AreteR2(dX+3,ukMotifCard*nMotifEnTout+uPoleNord,U,-U,*ppmE);
			if (bMode) dX+=ukMotifCard/2;else dX+=ukMotifCard;
			uPoleNord=uModulo1(uPoleNord+2,2*nSommet);
		}//GrafMatriceR2
	//connecter les étages successifs
		for (nEtage=0;nEtage<nSommet-1;nEtage++)
			for (nHaut=0;nHaut<nSommet;nHaut++)
				for (nBas=0;nBas<nSommet;nBas++)
					if ( nHaut!=nBas && bGrapheArc(pgG,nHaut+1,nBas+1) ){
						if (bMode) 
							{dX=8+ukMotifCard*(nEtage*nSommet+nHaut);
							dY=ukMotifCard+ukMotifCard*( (nEtage+1)*nSommet+nBas);
							AreteR2(dX,dY,G,-G,*ppmE);}
						else {dX=8+ukMotifCard*(nEtage*nSommet+nHaut);
							dY=ukMotifCard+ukMotifCard*( (nEtage+1)*nSommet+nBas);
							AreteR2(dX,dY,G,-G,*ppmE);
						}
						//tee("dX,dY",dX,dY);
					}
	//relier la trappe à la source
		if (bMode) 
			{dX=8;dY=8+ukMotifCard*(nMotifEnTout-1);AreteR2(dX,dY,E,-E,*ppmE);}
		else {dX=10;dY=8+ukMotifCard*(nMotifEnTout-1);AreteR2(dX,dY,E,-E,*ppmE);}
		//tee("        dX,dY",dX,dY);
		//if (bMode) AreteR2(dX,dY,E,-E,*ppmE);
	//MatriceVoir("GrafMatriceR",*ppmE);
}//GrafMatriceR

void GrafiqueR(int fMode,int nMotifEnTout,int nPoleEnTout,iMatrice *pmE){
	enum eLettre {Z,U,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,V,W,X,Y};//NB oui,Z,et U en tête et ds cet ordre.
	int nMotif,uPoleNord,uPoleSud,dX;
	int cA,cB;
	if (fMode==fCarreH){
			AreteR(1,2,A,-A,pmE); AreteR(2,3,B,-B,pmE); AreteR(3,4,C,-C,pmE); AreteR(1,4,D,-D,pmE); 
		}
	if (fMode==fComplexE)
		for (uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+2,dX+4,A,pmE); ArqueR(dX+4,dX+5,U,pmE); ArqueR(dX+5,dX+7,B,pmE);
			AreteR(dX+1,dX+2,U,U,pmE); AreteR(dX+3,dX+4,B,U,pmE); AreteR(dX+5,dX+6,A,U,pmE); AreteR(dX+7,dX+8,U,U,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+3,U,A,pmE);AreteR(dX+6,uPoleSud,U,B,pmE);
			dX+=8;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fCouplE)
		for (uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+2,dX+4,A,pmE); ArqueR(dX+4,dX+5,U,pmE); ArqueR(dX+5,dX+7,B,pmE);
			AreteR(dX+1,dX+2,U,U,pmE); AreteR(dX+3,dX+4,B,U,pmE); AreteR(dX+5,dX+6,A,U,pmE); AreteR(dX+7,dX+8,U,U,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+3,U,U,pmE);AreteR(dX+6,uPoleSud,U,U,pmE);
			dX+=8;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fDemiX)
		for (uPoleNord=1,dX=1,nMotif=0;nMotif<1;nMotif++){//raster scan
			AreteR(dX+2,dX+3,A,-A,pmE); AreteR(dX+3,dX+5,B,-B,pmE); AreteR(dX+4,dX+5,C,-C,pmE);
			AreteR(dX+6,dX+7,D,-D,pmE); AreteR(dX+6,dX+8,E,-E,pmE); AreteR(dX+8,dX+9,F,-F,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+4,U,-U,pmE);AreteR(dX+7,uPoleSud,U,-U,pmE);
			AreteR(dX+2,dX+9,G,-G,pmE);
		}
	if (fMode==fDemyX)
		for (uPoleNord=1,dX=1,nMotif=0;nMotif<1;nMotif++){//raster scan
			AreteR(dX+2,dX+3,A,-A,pmE); AreteR(dX+3,dX+5,B,-B,pmE); AreteR(dX+4,dX+5,C,-C,pmE);
			AreteR(dX+6,dX+7,D,-D,pmE); AreteR(dX+6,dX+8,E,-E,pmE); AreteR(dX+8,dX+9,F,-F,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+4,U,-U,pmE);AreteR(dX+7,uPoleSud,U,-U,pmE);
			AreteR(dX+2,dX+9,G,-G,pmE);
		}
	if (fMode==fDuO)
		for (uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			AreteR2(dX+1,dX+3,A,A,pmE); AreteR2(dX+3,dX+5,B,B,pmE); AreteR2(dX+5,dX+7,C,C,pmE);
			AreteR2(uPoleNord,dX+7,U,U,pmE);
			dX+=8;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fIndividueL )
		for (cA=A,cB=B,uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+2,dX+4,cA,pmE); ArqueR(dX+4,dX+5,U,pmE); ArqueR(dX+5,dX+7,cB,pmE);
			AreteR(dX+1,dX+2,U,U,pmE); AreteR(dX+3,dX+4,cB,U,pmE); AreteR(dX+5,dX+6,cA,U,pmE); AreteR(dX+7,dX+8,U,U,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+3,U,U,pmE);AreteR(dX+6,uPoleSud,U,U,pmE);
			dX+=8;
			cA+=2;cB+=2;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fLobiX)
		for (dX=0,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+1,dX+3,A,pmE);ArqueR(dX+2,dX+3,B,pmE);ArqueR(dX+3,dX+4,H,pmE);ArqueR(dX+4,dX+5,D,pmE);ArqueR(dX+4,dX+6,E,pmE);
			AreteR(dX+6,dX+1,F,-F,pmE); AreteR(dX+5,dX+2,G,-G,pmE);
			dX+=6;
		}
	if (fMode==fMuteX)
		for (uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+1,dX+3,B,pmE); ArqueR(dX+2,dX+4,B,pmE); ArqueR(dX+3,dX+6,B,pmE);
			ArqueR(dX+4,dX+6,B,pmE); ArqueR(dX+5,dX+1,B,pmE); ArqueR(dX+5,dX+2,B,pmE);
			uPoleSud=uPoleNord+1;
			//te("uPoleNord",uPoleNord);
			ArqueR(uPoleNord,dX+2,A,pmE);ArqueR(dX+3,uPoleSud,A,pmE);
			dX+=6;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fScissioN)
		for (cA=A,cB=B,uPoleNord=1,dX=0,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			AreteR(dX+1,dX+3,U,A,pmE); AreteR(dX+1,dX+4,U,B,pmE); AreteR(dX+2,dX+5,-A,U,pmE); AreteR(dX+2,dX+6,-B,U,pmE);
			AreteR(dX+3,dX+7,U,U,pmE); AreteR(dX+6,dX+8,U,U,pmE);
			uPoleSud=uPoleNord+1;
			AreteR(8*nMotifEnTout+uPoleNord,dX+4,U,U,pmE);AreteR(dX+5,8*nMotifEnTout+uPoleSud,U,U,pmE);
			dX+=8;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fSimplE)
		for (uPoleNord=1,dX=nPoleEnTout,nMotif=0;nMotif<nMotifEnTout;nMotif++){//raster scan
			ArqueR(dX+2,dX+4,U,pmE); ArqueR(dX+4,dX+5,U,pmE); ArqueR(dX+5,dX+7,U,pmE);
			AreteR(dX+1,dX+2,U,U,pmE); AreteR(dX+3,dX+4,U,U,pmE); AreteR(dX+5,dX+6,U,U,pmE); AreteR(dX+7,dX+8,U,U,pmE); 
			uPoleSud=uPoleNord+1;
			AreteR(uPoleNord,dX+3,U,U,pmE);AreteR(dX+6,uPoleSud,U,U,pmE);
			dX+=8;
			uPoleNord=uModulo1(uPoleNord+2,nPoleEnTout);
		}
	if (fMode==fThetA){
		AreteR(1,2,B,-B,pmE); AreteR(2,3,D,-D,pmE); AreteR(3,4,U,-U,pmE); AreteR(4,5,D,-D,pmE); AreteR(5,6,B,-B,pmE);
		AreteR(1,6,U,-U,pmE); AreteR(3,6,U,-U,pmE); 
		}
	if (fMode==fThetB){//fThetA modifié par échange des poids des arêtes (4,5) et (5,6)
		AreteR(1,2,B,-B,pmE); AreteR(2,3,D,-D,pmE); AreteR(3,4,U,-U,pmE); AreteR(4,5,B,-B,pmE); AreteR(5,6,D,-D,pmE);
		AreteR(1,6,U,-U,pmE); AreteR(3,6,U,-U,pmE); 
		}
}//GrafiqueR

void GrafixeR(int fMotif,int nSommet,int nInterdit,iMatrice *pmE){
	//S=nSommet. Rend matrice à S2 motifs fMotif;relie étages succesF via S(S-1)/2 arcs. Si nInterdit>0,omet arcs de rg1 nInterdit.
	enum eLettre {Z,U,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,V,W,X,Y};//NB oui,Z,et U en tête et ds cet ordre.
	int nBas,nHaut,nEtage,dX,dY;
	int uDiviseur=(fMotif==fDuO)?2: 1;
	int nMotifEnTout=nSommet*nSommet;
	int nPoleEnTout=2*nSommet;
	int nSommetParMotif=(fMotif==fMuteX)? 6: 8;
	pmE->nLigne=pmE->nColonne=(nPoleEnTout+nSommetParMotif*nMotifEnTout)/uDiviseur;
	//tee("nSommetParMotif,nSommet",nSommetParMotif,nSommet);
	GrafiqueR(fMotif,nMotifEnTout,nPoleEnTout,pmE);
	//MatriceVoir("APRES GrafiqueR",pmE);
	//relier les étages successifs
		for (nEtage=0;nEtage<nSommet-1;nEtage++)
			for (nHaut=0;nHaut<nSommet;nHaut++)
				if (nHaut+1!=nInterdit)
					for (nBas=0;nBas<nSommet;nBas++){
						if (nHaut!=nBas){
							if (fMotif==fDuO){
								dX=1+nPoleEnTout/2+4*(nEtage*nSommet+nHaut);dY=1+nPoleEnTout/2+4*(nEtage*nSommet+nSommet+nBas);
								//tee("dX,dY",dX,dY);
								ArqueR(dX,dY,G,pmE);
							}
							else if (fMotif==fMuteX) {
								dX=nPoleEnTout+nSommetParMotif*(nEtage*nSommet+nHaut);
								dY=nPoleEnTout+nSommetParMotif*(nEtage*nSommet+nSommet+nBas);
								//tee("dX+4,dY+1",dX+4,dY+1);
								ArqueR(dX+4,dY+1,U,pmE);
							}
							else {
								dX=nPoleEnTout+nSommetParMotif*(nEtage*nSommet+nHaut);
								dY=nPoleEnTout+nSommetParMotif*(nEtage*nSommet+nSommet+nBas);
								ArqueR(dX+nSommetParMotif,dY+1,U,pmE);
							}
							//pmE->Mat[dX+8][dY+1]= -4;//provisoire,facilite le débogage
						}
					}
	//relier la trappe à la source
		if (fMotif==fMuteX){
			dX=nPoleEnTout+1;dY=pmE->nLigne-2;
			//tee("dXsource,dYtapp",dX,dY);
			//ArqueR(dY,dX,C,pmE);}
		}else if (fMotif!=fDuO){
			if (fMotif!=fScissioN){
				dX=nPoleEnTout+1;dY=pmE->nLigne;ArqueR(dY,dX,U,pmE);}
			else {dX=7;dY=nSommetParMotif*nMotifEnTout;AreteR(dX,dY,U,U,pmE);}
			//retirer de l'arête liée à la source l'arc qui atteint la source  
				if (fMotif!=fScissioN)
					pmE->Mat[nPoleEnTout+2][nPoleEnTout+1]=0;
		}else {
			dX=1+nPoleEnTout/2;dY=pmE->nLigne-(8/2)+1;ArqueR(dY,dX,D,pmE);//tee("dX,dY",dX,dY);
		}
	//MatriceVoir("pmE avant unification",pmE);
	if (fMotif==fSimplE)
		MatriceUnifier(pmE);
	//MatriceVoir(sC2b(sItem(sFORME,fMotif),"graphixé"),pmE);
}//GrafixeR

void GraphixeR(int nGraphixe,iMatrice *pmE){
	//crée le graphixe à 10 sommets demandé
	int nDim,nMotifEnTout,bParfait,bOptimal,nPoleEnTout;
	enum eLettre {Z,U,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,V,W,X,Y};//NB oui,Z,et U en tête et ds cet ordre.
	pmE->nLigne=pmE->nColonne=10;
	//te("nGraphixe",nGraphixe);
	switch(nGraphixe){
		case 0:	//débogage: tous les arcs ont des littéraux distincts
				ArqueR(4,6,U,pmE); ArqueR(6,7,U,pmE); ArqueR(7,9,U,pmE);
				AreteR(3,4,F,U,pmE); AreteR(5,6,H,U,pmE); AreteR(7,8,J,U,pmE); AreteR(9,10,L,U,pmE); 
				AreteR(1,5,N,U,pmE); AreteR(8,2,P,U,pmE);
				ArqueR(10,3,T,pmE);//source trappe
				MatriceVoir("pmE",pmE);
				break;
		case 1:	//débogage: tous les arcs ont des littéraux distincts
				ArqueR(4,6,A,pmE); ArqueR(6,7,C,pmE); ArqueR(7,9,E,pmE);
				AreteR(3,4,F,G,pmE); AreteR(5,6,H,I,pmE); AreteR(7,8,J,K,pmE); AreteR(9,10,L,M,pmE); 
				AreteR(1,5,N,O,pmE); AreteR(8,2,P,Q,pmE);
				ArqueR(10,3,T,pmE);//source trappe
				MatriceVoir("pmE",pmE);
				break;
		case 2:	//les arcs triviaux sont étiquetés U
				ArqueR(4,6,U,pmE); ArqueR(6,7,U,pmE); ArqueR(7,9,U,pmE);
				AreteR(3,4,F,U,pmE); AreteR(5,6,G,U,pmE); AreteR(7,8,H,U,pmE); AreteR(9,10,I,U,pmE); 
				AreteR(1,5,J,U,pmE); AreteR(8,2,K,U,pmE);
				ArqueR(10,3,T,pmE);//source trappe
				MatriceVoir("pmE",pmE);
				break;
		case 3:	//les arcs hors axe et retour sont étiquetés A et B;arc retour étiqueté T
				ArqueR(4,6,A,pmE); ArqueR(6,7,U,pmE); ArqueR(7,9,B,pmE);
				AreteR(3,4,U,U,pmE); AreteR(5,6,B,U,pmE); AreteR(7,8,A,U,pmE); AreteR(9,10,U,U,pmE); 
				AreteR(1,5,U,A,pmE); AreteR(8,2,U,B,pmE);
				ArqueR(10,3,U,pmE);//source trappe
				MatriceVoir("pmE graphixée",pmE);
				//DeterminantConfronteR(pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;
		case 4:	//les arcs hors axe et retour sont étiquetés A et B;arc retour étiqueté T
				GrafixeR(fComplexE,2,0,pmE);
				DeterminantConfronteR(pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;
		case 5:	//les arcs hors axe et retour sont étiquetés A et B;arc retour étiqueté T
				nDim=2;
				GrafixeR(fCouplE,nDim,0,pmE);
				//DeterminantConfronteR(pmE);
				//yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				//iBof=iFormeQalculeR(pmE,0);//Urbanska quad
				break;
		case 6:	//les arcs hors axe et retour sont étiquetés A et B;arc retour étiqueté T
				nDim=2;
				GrafixeR(fIndividueL,nDim,0,pmE);
				//DeterminantConfronteR(pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				//iBof=iFormeQalculeR(pmE,0);//Urbanska quad
				break;
		case 7:	//les arcs hors axe et retour sont étiquetés A et B;arc retour étiqueté T
				nDim=2;
				GrafixeR(fScissioN,nDim,0,pmE);
				//DeterminantConfronteR(pmE);
				yBof=yFormeKalculeR(pmE,1,k1Voir);//Urbanska simple
				break;
		case 8:	//Cycle lg 6 + diagonale = forme Theta
				pmE->nLigne=pmE->nColonne=6;
				GrafiqueR(fThetB,6,0,pmE);
				//GrafiqueR(fThetA,6,0,pmE);
				MatriceVoir("fThetB graphixé",pmE);
				yBof=nProduitEnTouT(pmE);
				//yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		case 9:	//recherche de couplage parfait
				nDim=3;
				GrafixeR(fDuO,nDim,0,pmE);
				MatriceCoupler(pmE,&bParfait,&bOptimal);
				printf("Il %s couplage parfait.\n",sUn("existe",bParfait));
				break;
		case 10:	//généralise le cas 3 à une matrice 2x2 DE POIDS UNITAIRE
				nDim=2;
				GrafixeR(fSimplE,nDim,0,pmE);
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		case 11://Carreh d'arêtes
				nDim=0;
				pmE->nLigne=pmE->nColonne=4;
				GrafiqueR(fCarreH,4,0,pmE);
				MatriceVoir("fCarreH graphixé",pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		case 12://Demi X d'arêtes
				nDim=1;
				pmE->nLigne=pmE->nColonne=10;
				GrafiqueR(fDemiX,1,2,pmE);
				MatriceVoir("fDemiX graphixé",pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		case 13://Demy X d'arêtes
				nDim=1;
				pmE->nLigne=pmE->nColonne=10;
				GrafiqueR(fDemyX,1,2,pmE);
				MatriceVoir("fDemyX graphixé",pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		case 14://fLobiX X d'arêtes
				nDim=1;
				nMotifEnTout=2;
				pmE->nLigne=pmE->nColonne=6*nMotifEnTout;
				GrafiqueR(fLobiX,nMotifEnTout,2,pmE);
				MatriceVoir("fLobiX graphixé",pmE);
				yBof=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
				break;//Mahajan:iPositif,iNegatif,iDelta APRES:1952366592, 2091302912, -138936320.
		default://mutex d'arcs
				nDim=nGraphixe-100;
				nMotifEnTout=nDim;
				nPoleEnTout=2*nDim;
				pmE->nLigne=pmE->nColonne=nPoleEnTout+6*nMotifEnTout;
				GrafixeR(fMuteX,nDim,0,pmE);
				//MatriceVoir("mutex graphixé final",pmE);
				break;
	}
}//GraphixeR

void FormeLosangeR(int *pnLigne,int *pnColonne,fMathricE **ppmA){
	//génère en losange A , A B, et B,resp.lignes i, i+1 et i+2.
	int uL,uC;
	Appel0("FormeLosangeR");
		uL=*pnLigne+0;uC=*pnColonne+1;tee("uL,uC",uL,uC);FormeCaseR(1,uL,uC,ppmA);
		uL=*pnLigne+1;uC=*pnColonne+0;FormeCaseR(1,uL,uC,ppmA);
		uL=*pnLigne+1;uC=*pnColonne+2;FormeCaseR(2,uL,uC,ppmA);
		uL=*pnLigne+2;uC=*pnColonne+1;FormeCaseR(2,uL,uC,ppmA);
		*pnLigne=*pnLigne+kuLosangeLargeurVautTroiS;
		*pnColonne=*pnColonne+kuLosangeLargeurVautTroiS;
	Appel1("FormeLosangeR");
}//FormeLosangeR

void FormeMargeR(int nCoteh,int uDalleMax,int *pnLigne,int *pnColonne,int *pnMotif,fMathricE **ppmA){
	//ajoute à gauche et en bas les connexions aux sélecteurs haut et bas
	int uC,uL,nColonne,nLigne;
	//te("pnLigne",*pnLigne);
	//ajout à gauche de nCoteh motifs;chaque motif est un "antislash" vertical matérialisé par nCoteh points
		for (nLigne=0,uL=1;uL<=nCoteh;uL++){
			for (uC=1;nLigne+=kuLosangeLargeurVautTroiS,uC<=nCoteh;uC++)
				FormeCaseR(*pnMotif,nLigne,uC,ppmA);
			nLigne+=nCoteh-kuLosangeLargeurVautTroiS;
		}
		MotifSuivanT(pnMotif);
	//ajout en bas de nCoteh motifs;chaque motif est un "antislash" horizontal matérialisé par nCoteh points
		//passer le 1er antislash vertical tracé ci-dessus et le second antislash fait par MotifBorder dans MotifPlacer ,d'où "2*nCoteh": 
		for (nColonne=2*nCoteh,uC=1;uC<=nCoteh;uC++){
			for (uL=1;uL<=nCoteh;nColonne+=kuLosangeLargeurVautTroiS,uL++)
				FormeCaseR(*pnMotif,*pnLigne+uL-1,uC+nColonne,ppmA);
			nColonne+=nCoteh-1;
		}
		MotifSuivanT(pnMotif);
}//FormeMargeR

void FormeMatriceR(iMatrice *pmSource,nbMatrice *pmnbCible){
	int uC,uL;
	pmnbCible->nLigne=pmSource->nLigne;
	pmnbCible->nColonne=pmSource->nColonne;
	for (uL=1;uL<=pmSource->nLigne;uL++)
		for (uC=1;uC<=pmSource->nColonne;uC++)
			NbAffecter(pmSource->Mat[uL][uC],&pmnbCible->Mat[uL][uC]);
}//FormeMatriceR

void FormeMultiplieR(f fA,f fB,f *pfC){
	//multiplie deux formes mutualisées, ie chacune a un dénominateur unique, commun à tous ses sommandes 
	Assert1("FormeMultiplieR",bFormeAmorceR);
	const int kbVoir=kF;
	int uA,uB,nCible,uL;
	int nLettreA,nLettreB;
	int nTermeA=fA.num[0][0];
	int nTermeB=fB.num[0][0];
	Assert1("FormeMultiplieR",nTermeA*nTermeB<kuSommandeLiM);
	if (kbVoir) FormeVoiR("FormeMultiplieR:fA",fA);
	if (kbVoir) FormeVoiR("FormeMultiplieR:fB",fB);
	FormeRazeR(pfC);
	//te("fB.den[0][0]",fB.den[0][0]);
	//multiplier deux formes, c'est multiplier deux à deux les numérateurs des termes de fA et fB …
		for (nTermeA=fA.num[0][0],nTermeB=fB.num[0][0],nCible=0,uA=1;uA<=nTermeA;uA++)
			for (uB=1;uB<=nTermeB;uB++){
				nCible++;
				nLettreA=nLettraT(fA,uA,!k1DenominateuR);
				for (uL=1;uL<=nLettreA;uL++)
					(*pfC).num[nCible][uL]=fA.num[uA][uL];
				nLettreB=nLettraT(fB,uB,!k1DenominateuR);
				for (uL=1;uL<=nLettreB;uL++)
					(*pfC).num[nCible][nLettreA+uL]=fB.num[uB][uL];
				(*pfC).num[nCible][0]=fA.num[uA][0]*fB.num[uB][0];//produit des poids
			}
		(*pfC).num[0][0]=nCible;
	//…puis mutualiser le produit des dénominateurs de fA et fB
		for (nTermeA=fA.den[0][0],nTermeB=fB.den[0][0],nCible=0,uA=1;uA<=nTermeA;uA++)
			for (uB=1;uB<=nTermeB;uB++){
				nLettreA=nLettraT(fA,uA,k1DenominateuR);
				nLettreB=nLettraT(fB,uB,k1DenominateuR);
				nCible++;
				for (uL=1;uL<=nLettreA;uL++)
					(*pfC).den[nCible][uL]=fA.den[uA][uL];
				for (uL=1;uL<=nLettreB;uL++)
					(*pfC).den[nCible][nLettreA+uL]=fB.den[uB][uL];
				(*pfC).den[nCible][0]=fA.den[uA][0]*fB.den[uB][0];//produit des poids
			}
		(*pfC).den[0][0]=nCible;

		/*for (uD=1;uD<=fB.den[0][0];uD++)
			for (uL=0;uL<=nLettraT(fB,uD,k1DenominateuR);uL++)
				(*pfC).den[uD][uL]=fB.den[uD][uL];
		(*pfC).den[0][0]=fB.den[0][0];*/
	if (kbVoir) FormeVoiR("FormeMultiplieR:pfC",*pfC);
	//FormeVoiR("FormeMultiplieR0:pfC",*pfC);
	FormeSimplifieR(pfC);
	//FormeVoiR("FormeMultiplieR1:pfC",*pfC);
}//FormeMultiplieR

int bFormeNullE(f fForme){
	const int kbVoir= kF;
	int nLettrat,bNulle,uT,bZeroPartout,nTermat;
	//te("nSommande avant",fForme.num[1][0]);
	if (kbVoir) FormeVoiR("forme nulle?",fForme);
	bZeroPartout=1;
	nTermat=fForme.num[1][0];
	//te("nSommande",nSommande);
	for (uT=1;uT<=nTermat;uT++){
		//te("uS",uS);
		nLettrat=nLettraT(fForme,uT,!k1DenominateuR);
		if (nLettrat!=0)
			bZeroPartout=0;
	}
	Assert1("bFormeNullE",bZeroPartout==0 || bZeroPartout==1);
	bNulle=bZeroPartout;
	if (0 && !bNulle){
		Titrer("forme non nulle");
		FormeVoiR("forme non nulle",fForme);
	}
	if (kbVoir) te("bNulle",bNulle);
	Assert1("bFormeNullE",bZeroPartout==bNulle);
	return(bNulle);
}//bFormeNullE

void FormePoseR(int nCar,int nDiagonale,fMathricE *pmA){
	const int uMinusculeOffset=26;
	FormeCaseR(nCar,nDiagonale-1,nDiagonale+0,&pmA);//(1,2)
	FormeCaseR(nCar,nDiagonale-0,nDiagonale-1,&pmA);//(2,1)
	FormeCaseR(nCar+uMinusculeOffset,nDiagonale-0,nDiagonale+1,&pmA);//(2,3)
	FormeCaseR(nCar+uMinusculeOffset,nDiagonale+1,nDiagonale+0,&pmA);//(3,2)
}//FormePoseR

void FormeRazeR(f *pfCible){
	Assert1("FormeRazeR",bFormeAmorceR);
	int nS,nT;
	for (nS=0;nS<kuSommandeLiM;nS++)
		for (nT=0;nT<kuTermeLiM;nT++)
			(*pfCible).num[nS][nT]=0;
	for (nS=0;nS<kuSommandeLiM;nS++){
		for (nT=0;nT<kuTermeLiM;nT++)
			(*pfCible).den[nS][nT]=0;
		(*pfCible).den[nS][0]=1;
	}
}//FormeRazeR

void FormeSimplifieR(f *pfF){
	Assert1("FormeSimplifieR",bFormeAmorceR);
	int uA,uB,nL,nLettreA,nLettreB,uS,uT,bTuer,nFois;
	const int kbVoir=kF;
	const int kbSimplifier=kV;
	int bPareil,nPris,nTerme;
	char cCar;
	Assert1("FormeSimplifieR",bFormeAmorceR);
	//if (kbVoir) FormeVoiR("AVANT FormeSimplifieR",*pfF);
	nTerme=(*pfF).num[0][0];
	if (0){//A2=0 pour A B C.
		//te("nSommande",nSommande);
			for (uS=1;uS<=nTerme;uS++)
				for (uT=1;uT<=kuTermeMaX;uT++){
					nFois=(*pfF).num[uS][uT];
					if (nFois>1){//supprimer ce terme car c'est un doublon
						cCar=cCaracterE(uT);
						switch (cCar) {
							case 'A':	bTuer=kV;break;
							case 'B':	bTuer=kV;break;
							case 'C':	bTuer=kV;break;
							case 'G':	bTuer=kV;break;
							case 'H':	bTuer=kV;break;
							case 'I':	bTuer=kV;break;
							case 'M':	bTuer=kV;break;
							case 'N':	bTuer=kV;break;
							case 'O':	bTuer=kV;break;
							case 'a':	bTuer=kV;break;
							case 'b':	bTuer=kV;break;
							case 'c':	bTuer=kV;break;
							case 'g':	bTuer=kV;break;
							case 'h':	bTuer=kV;break;
							case 'i':	bTuer=kV;break;
							case 'm':	bTuer=kV;break;
							case 'n':	bTuer=kV;break;
							case 'o':	bTuer=kV;break;
							default: bTuer=kF;
						}
						if (bTuer){
							printf("SUPPRESSION de %s****",sFormE(*pfF,!k1DenominateuR));
							(*pfF).num[uS][0]=0;
							uT=kuTermeMaX;
						}
					}
				}
		}
	nTerme=(*pfF).num[0][0];
	if (kbSimplifier){
		//accumuler les termes identiques.
		if (1){
			for (uA=nTerme;uA>1;uA--){
				nLettreA=nLettraT(*pfF,uA,!k1DenominateuR);
				for (uB=1;uB<uA;uB++){
					nLettreB=nLettraT(*pfF,uB,!k1DenominateuR);
					//tee("nLettreA==nLettreB",nLettreA,nLettreB);
					if (nLettreA==nLettreB && nLettreA>0){
						if (bCommutatiF)
							bPareil=bVecteurSemblable(&(*pfF).num[uA][0],&(*pfF).num[uB][0],1,nLettreA);
						else bPareil=bVecteurEgal(&(*pfF).num[uA][0],&(*pfF).num[uB][0],1,nLettreA);
						if (bPareil){
							//if (kbVoir) t(sChoix(bCommutatiF,"céSemblable","céIdentique"));
							if (kbVoir) TermeVoiR("Alter",*pfF,uA);
							if (kbVoir && bCommutatiF) TermeVoiR("Ego",*pfF,uB);
							(*pfF).num[uB][0]=(*pfF).num[uA][0]+(*pfF).num[uB][0];//additionne les poids
							for (nL=0;nL<=kuTermeMaX;nL++)
								(*pfF).num[uA][nL]=0;
						}
					}
				}
			}
		}
		if (kbSimplifier){
		//supprimer les termes d'occurrence nulle en tassant les termes vers les indices faibles.
			for (nPris=0,uA=1;uA<=nTerme;uA++)
				if ((*pfF).num[uA][0]!=0)
					for (nPris++,nL=0;nL<=kuTermeMaX;nL++)
						(*pfF).num[nPris][nL]=(*pfF).num[uA][nL];
			(*pfF).num[0][0]=nPris;
		}
	}
	//if (kbVoir) FormeVoiR("APRES FormeSimplifieR",*pfF);
}//FormeSimplifieR

void FormeTESTER(int iTest){
	//teste le présent module
	char *sForme;
	int muNeutre=1;
	char cCar;
	int nDim,aK,uC,uL,nSommet,bParfait,bOptimal,uPivot;
	long yDeterminant;
	fMathricE *pmA;
	qMatrice *pmqA;
	iMatrice *pmE;
	graf *pgG;
	graf *pgH;
	f fA,fB,fC,fD,fE,fF,fG,fH,fV;
	int kbPoleBannir;
	//iTest=67;
	//iTest=70;
	//iTest=80;
	//iTest=6;
	iTest=100;
	if (iTest<0) Appel0(sC2("FormeTESTER,test n°",sEnt(iTest)));
		Assert1("FormeTESTER",bFormeAmorceR);
		switch (iTest) {
			case 200:	DeterminantQuatreExhibeR();
						break;
			case  0:	FormeCreeR(sC('A'),&fA);FormeVoiR("A",fA);
						FormeCreeR(sC('B'),&fB);FormeVoiR("B",fB);
						FormeCreeR(sC('C'),&fC);FormeVoiR("C",fC);
						FormeCreeR(sC('D'),&fD);FormeVoiR("D",fD);
						FormeAjouteR(fA,fB,&fE);FormeVoiR("A+B",fE);
						FormeAjouteR(fC,fD,&fF);FormeVoiR("C+D",fF);
						FormeDiviseR(fE,fF,&fG);FormeVoiR("A+B/C+D",fG);
						break;
			case  1:	FormeCreeR("ABCD",&fA);FormeVoiR("ABCD",fA);
						FormeCreeR("-2ABKZ",&fB);FormeVoiR("-2ABKZ",fB);
						FormeCreeR("ABBA",&fC);FormeVoiR("ABBA",fC);
						FormeCreeR("ABCDABCE",&fD);FormeVoiR("ABCDABCE",fD);
						FormeMultiplieR(fA,fB,&fE);FormeVoiR("ABCD*(-2ABKZ)",fE);
						FormeAjouteR(fA,fB,&fF);FormeVoiR("ABCD+(-2ABKZ)",fF);
						FormeCreeR("ABCD",&fG);FormeVoiR("ABCD",fG);
						FormeFoisseR(-1,&fG);FormeVoiR("-1*ABCD",fG);
						FormeAjouteR(fA,fG,&fH);FormeVoiR("ABCD+(-ABCD)",fH);
						FormeCreeR(sC('a'),&fA);
						tc("sC('a')",'a');
						FormeVoiR("fA",fA);
						break;
			case  2:	FormeCreeR("B",&fB);//FormeVoiR("B",fB);
						FormeCreeR("D",&fD);//FormeVoiR("D",fD);
						FormeMultiplieR(fB,fD,&fE);
						FormeVoiR("B*D",fE);
						printf("******%s*****.\n",sFormE(fE,!k1DenominateuR));
						FormeCreeR("-2ABKZ",&fB);FormeVoiR("-2ABKZ",fB);
						printf("******%s*****.\n",sFormE(fB,!k1DenominateuR));
						break;
			case  3:	FormeCreeR("0",&fV);
						printf("******%s*****.\n",sFormE(fV,!k1DenominateuR));
						FormeVoiR("fV",fV);
						break;
			case  4:	FormeCreeR("A",&fA);FormeVoiR("A",fA);
						FormeFoisseR(-1,&fA);FormeVoiR("-A",fA);
						break;
			case  5:	FormeCreeR("A",&fA);FormeVoiR("A",fA);
						FormeCreeR("FH",&fB);FormeVoiR("FH",fB);
						FormeCreeR("EI",&fC);FormeVoiR("EI",fC);
						FormeAjouteR(fB,fC,&fD);FormeVoiR("FH+EI",fD);
						FormeMultiplieR(fD,fA,&fE);FormeVoiR("(FH+EI)A",fE);
						FormeMultiplieR(fA,fD,&fE);FormeVoiR("A(FH+EI)",fE);
						break;
			case  6:	DeterminantExpliciter(grP3,pmE);
						//DeterminantCalculeR(3,maSymetriquE);//maAntisymetriquE
						//PermanentCalculeR(2,maSymetriquE);//maAntisymetriquE
						//FormeCreeR(sC2("-",'a'),&fA);
						//SignatureCalculeR(4);
						break;
			case  7:	MathriceAlloueR(4,4,&pmA);
						MathriceRempliR(pmA,maBipartiAntisyM);
						MathriceVoiR("pmA maBipartiAntisyM pour le déterminant",pmA);
						DeterminantKalculeR(pmA,k1Voir);
						break;
			case  8:	MathriceAlloueR(4,4,&pmA);
						//MathriceRempliR(pmA,maAntisymetriquE);
						MathriceRempliR(pmA,maTriangleInferieuR);
						MathriceVoiR("pmA maAntisymetriquE pour la signature de permutation",pmA);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						//DeterminantKalculeR(pmA,k1Voir);
						//tb("AF",bSignaturePairE(pmA,"AF"));
						//tb("BE",bSignaturePairE(pmA,"BE"));
						//tb("CD",bSignaturePairE(pmA,"CD"));
						break;
			case  9:	sForme="ABKZ@TY";//déclenche une assertion
						break;
			case 10:	nSommet=3;
						if (nSommet>1){
							//te("case 10,nSommet",nSommet);
							GrapheCreer0(&pgG,kV);
								//GrapheVoir(pgG,"pgG AVANT GrapheCliquer");
								GrapheCliquer(pgG,nSommet);
								if (nSommet>=20)
									bBof=bGrapheDesareter(pgG,1,2);
								if (nSommet>=30)
									bBof=bGrapheDesarquer(pgG,2,3);
								if (nSommet>=40)
									bBof=bGrapheDesarquer(pgG,2,4);
								if (nSommet>=5)
									bBof=bGrapheDesarquer(pgG,4,2);
								if (nSommet>=5)
									bBof=bGrapheDesarquer(pgG,3,2);
								GrapheVoir(pgG,"Graphe pgG à matricer");
								GrafMatriceR(pgG,&pmE);
							GrapheCreer0(&pgG,kF);
								//MatriceUnifier(pmE);
								//MatricePositiver(pmE);
								//DeterminantConfronteR(pmE);
							//MatriceVoir("Matrice pmE associée à pgG",pmE);
							if (1){//GrafMatriceR2
								MatricePositiver(pmE);
								MatriceCoupler(pmE,&bParfait,&bOptimal);
								printf("Il %s solution.\n",sUne("existe",bParfait && bOptimal));
							} else te("déterminant",yMatriceDeterminant(pmE));
						} else printf("Le problème n'est pas défini car le graphe généré a %d sommet.\n", nSommet);
						break;
			case 11:	MathriceEvalueR(4);//génère la matrice de dimension 39/68 associée à un graphe de 3/4 sommets
						break;
			case 12:	MathriceAlloueR(6,6,&pmA);
						FormeCreeR(sC('A'),&pmA->fForme[2][1]);
						FormeCreeR(sC('B'),&pmA->fForme[4][1]);
						FormeCreeR(sC('C'),&pmA->fForme[1][2]);
						FormeCreeR(sC('D'),&pmA->fForme[3][2]);
						FormeCreeR(sC('E'),&pmA->fForme[2][3]);
						FormeCreeR(sC('F'),&pmA->fForme[5][4]);
						FormeCreeR(sC('G'),&pmA->fForme[4][5]);
						FormeCreeR(sC('H'),&pmA->fForme[6][5]);
						FormeCreeR(sC('I'),&pmA->fForme[3][6]);
						FormeCreeR(sC('J'),&pmA->fForme[5][6]);
						//MathriceVoiR("pmA maBipartiAntisyM pour le déterminant",pmA);
						//DeterminantKalculeR(pmA,k1Voir);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 13:	nDim=3;
						MathriceAlloueR(nDim,nDim,&pmA);
						MathriceAffecteR(&pmA);
						//MathriceVoiR("pmA maBipartiAntisyM pour le déterminant",pmA);
						//DeterminantKalculeR(pmA,k1Voir);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 14:	nDim=6;
						MathriceAlloueR(nDim,nDim,&pmA);
						FormeCreeR(sC('A'),&pmA->fForme[1][2]);FormeCreeR(sC('A'),&pmA->fForme[2][1]);
						FormeCreeR(sC('B'),&pmA->fForme[2][3]);FormeCreeR(sC('B'),&pmA->fForme[3][2]);
						FormeCreeR(sC('C'),&pmA->fForme[4][5]);FormeCreeR(sC('C'),&pmA->fForme[5][4]);
						FormeCreeR(sC('D'),&pmA->fForme[5][6]);FormeCreeR(sC('D'),&pmA->fForme[6][5]);
						FormeCreeR(sC('E'),&pmA->fForme[1][4]);
						FormeCreeR(sC('F'),&pmA->fForme[3][6]);
						FormeCreeR(sC('G'),&pmA->fForme[4][1]);
						FormeCreeR(sC('H'),&pmA->fForme[6][3]);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 15:	nDim=6;
						MathriceAlloueR(nDim,nDim,&pmA);
						FormePoseR(1,2,pmA);
						FormePoseR(2,5,pmA);
						MathriceVoiR("après FormePoseR",pmA);
						FormeCreeR(sC('E'),&pmA->fForme[1][4]);
						FormeCreeR(sC('F'),&pmA->fForme[3][6]);
						FormeCreeR(sC('G'),&pmA->fForme[4][1]);
						FormeCreeR(sC('H'),&pmA->fForme[6][3]);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 16:	nDim=18;
						MathriceAlloueR(nDim,nDim,&pmA);
						FormePoseR(1,2,pmA);FormePoseR(2,5,pmA);FormePoseR(3,8,pmA);
						FormePoseR(4,11,pmA);FormePoseR(5,14,pmA);FormePoseR(6,17,pmA);
						MathriceVoiR("après FormePoseR",pmA);
						FormeCreeR(sC('E'),&pmA->fForme[3][9]);
						FormeCreeR(sC('F'),&pmA->fForme[3][6]);
						FormeCreeR(sC('G'),&pmA->fForme[4][1]);
						FormeCreeR(sC('H'),&pmA->fForme[6][3]);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 17:	MathriceAlloueR(4,4,&pmA);
						MathriceRempliR(pmA,maTriangleInferieuR);
						MathriceVoiR("pmA maTriangleInferieuR",pmA);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						free(pmA);
						MathriceAlloueR(4,4,&pmA);
						MathriceRempliR(pmA,maTriangleSuperieuR);
						MathriceVoiR("pmA maTriangleSuperieuR",pmA);
						bBof=bFormeTrianguleR(pmA,k1Commutatif);
						break;
			case 20:	//applique iFormeCalculeR à une matrice canonique,ie pmE->Mat[uL][uC]=10*uL+uC
						MatriceAllouer1(&pmE,4);
						MatriceCanoniser(maTout,&pmE);
						MatriceVoir("pmE",pmE);
						bBof=iFormeCalculeR(pmE);
						break;
			case 21:	//applique iFormeCalculeR à une matrice triangulaire inférieure losangée
						MatriceAllouer1(&pmE,6);
						//char *sItem="12,23,34,45,56";
						MatriceCanoniser(maInferieur,&pmE);
						MatriceLosanger(0,700,&pmE);
						for (uL=1;uL<=pmE->nLigne;uL++)
							for (uC=1;uC<=pmE->nLigne;uC++)
								if (pmE->Mat[uL][uC]>100)
									pmE->Mat[uL][uC]+=kE6;
						MatriceVoir("pmE",pmE);
						bBof=iFormeCalculeR(pmE);
						break;
			case 22:	//applique iFormeCalculeR à une matrice à carrés nuls
						MathriceAlloueR(4,4,&pmA);
						MathriceRempliR(pmA,maGeneralE0);
						LettreR(1,2,'M',pmA);LettreR(2,3,'M',pmA);
						LettreR(1,4,'N',pmA);LettreR(4,3,'N',pmA);
						LettreR(2,1,'D',pmA);LettreR(3,4,'D',pmA);
						MathriceVoiR("Déterminant maGeneralE0",pmA);
						MatriceAllouer1(&pmE,pmA->nLigne);
						for (uL=1;uL<=pmE->nLigne;uL++)
							for (uC=1;uC<=pmE->nLigne;uC++)
							if (uL!=uC){
								sForme=sFormE(pmA->fForme[uL][uC],!k1DenominateuR);
								cCar=sForme[1];
								Assert1("FormeTESTER Caractere invalide ds matrice",cCar>'A');//0=@ et 1=A sont les éléments neutres
								pmE->Mat[uL][uC]=cCar-'@';
								if (pmE->Mat[uL][uC]>12)
									pmE->Mat[uL][uC]=kE6+pmE->Mat[uL][uC];
							}
						bBof=iFormeCalculeR(pmE);
						break;
			case 30:
					Titrer("Mahajan sur K24");
					MatriceAllouer1(&pmE,6);//raze
						pmE->Mat[1][3]=pmE->Mat[1][4]=pmE->Mat[1][5]=pmE->Mat[1][6]=1;
						pmE->Mat[2][3]=pmE->Mat[2][4]=pmE->Mat[2][5]=pmE->Mat[2][6]=1;
						MatriceAntisymetriser(&pmE);
						bBof=iFormeCalculeR(pmE);
					break;
			case 31:
					Titrer("Urbanska sur K24");
					MatriceAllouer1(&pmE,6);//raze
						pmE->Mat[1][3]=pmE->Mat[1][4]=pmE->Mat[1][5]=pmE->Mat[1][6]=1;
						pmE->Mat[2][3]=pmE->Mat[2][4]=pmE->Mat[2][5]=pmE->Mat[2][6]=1;
						MatriceAntisymetriser(&pmE);
						yDeterminant=yFormeKalculeR(pmE,0,k1Voir);
					break;
			case 32:
					Titrer("Urbanska sur Cycle");
					MatriceAllouer1(&pmE,4);//raze
						MatriceCircuiter(1,&pmE);
						yDeterminant=yFormeKalculeR(pmE,0,k1Voir);
					break;
			case 33:
					Titrer("Urbanska sur Cycle et cyclets");
					MatriceAllouer1(&pmE,6);//raze
						MatriceCircuiter(1,&pmE);
						pmE->Mat[3][2]=pmE->Mat[5][4]=pmE->Mat[1][6]=1;
						yDeterminant=yFormeKalculeR(pmE,0,k1Voir);
					break;
			case 34:
					Titrer("Urbanska0 sur QUADRIPOLE");
					MatriceAllouer(&pmE);//raze
						nDim=2;
						MatriceQuadripoler(nDim*10+0,k1Boucler,&pmE);
						//MatriceVoir("QUADRIPOLE pmE",pmE);
						yDeterminant=yFormeKalculeR(pmE,nDim,k1Voir);
					break;
			case 35:
					Titrer("Urbanska0 sur QUADRIPOLE");
					MatriceAllouer(&pmE);//raze
						nDim=2;
						MatriceQuadripoler(nDim*10+2,k1Boucler,&pmE);
						//MatriceVoir("QUADRIPOLE pmE",pmE);
							pmqA=malloc(sizeof(qMatrice));
							pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
							for (uL=1;uL<=pmE->nLigne;uL++)
								for (uC=1;uC<=pmE->nLigne;uC++)
									pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
						bBof=bQuadDeterminer(pmqA);
					break;
			case 37://déterminant "Fibonacci" F(pmE->nLigne-1). F(0)=0,F(1)=1,F(2)=1,F(3)=2,F(4)=3,F(5)=5,F(6)=8,F(7)=13,F(8)=21,F(9)=34,F(10)=55.
					Titrer("Urbanska sur matrice de Fibonacci");
					MatriceAllouer1(&pmE,8);//raze
					MatriceBander(-1,&pmE);MatriceFoisser(-1,&pmE);
					MatriceBander(0,&pmE);pmE->Mat[1][1]=0;
					MatriceBander(+1,&pmE);
					//MatriceVoir(sC2("F",sP(sEnt(pmE->nLigne-1))),pmE);
					yDeterminant=yFormeKalculeR(pmE,nDim=0,k1Voir);
					Assert1("FormeTESTER35",yDeterminant==zFib(pmE->nLigne-1));
					printf("Le déterminant de la matrice de Fibonacci de dimension %d vaut F(%d-1),ie %ld.\n",pmE->nLigne,pmE->nLigne,yDeterminant);
					break;
			case 50:
					Titrer("(n(1+lgn)...");
						LimiteCalculeR();
					break;
			case 51:
					Titrer("Determinant nullissime...");
						NullissimeR();
					break;
			case 60:
					Titrer("test de FormeLongrineR2 sur un graphe à 2 sommets, 1 arc et 1 pivot");
					GrapheCreer1(&pgG,grP2,k1Creer);
						GrapheVoir(pgG,"Graphe pgG à matricer");
						FormeLongrineR2(uPivot=1,pgG,k1Biparti,kbPoleBannir=kV,&pgH);
						MatriceAllouer1(&pmE,pgH->nSommetEnTout);
							MatriceDepuisGraphe(pgH,!k1Incidence,&pmE);
							MatriceVoir("Matrice de longrines",pmE);
						free(pmE);
					GrapheCreer0(&pgG,kF);
					break;
			case 61:
					Titrer("test de FormeLongrineR2 sur grC3 et 2 pivots");
					GrapheCreer1(&pgG,grC3,k1Creer);
						GrapheVoir(pgG,"Graphe pgG (grC3 et 2 pivots) à matricer");
						FormeLongrineR2(uPivot=2,pgG,k1Biparti,kbPoleBannir=kV,&pgH);
						MatriceAllouer1(&pmE,pgH->nSommetEnTout);
							MatriceDepuisGraphe(pgH,!k1Incidence,&pmE);
							MatriceVoir("Matrice de longrines",pmE);
						free(pmE);
					GrapheCreer0(&pgG,kF);
					break;
			case 65:
					CouvertureCompteR(!k1General,gr2Aile,0,&nBof,&yBof);
					break;
			case 67:
					CouvertureCompteR(!k1General,grD4,0,&nBof,&yBof);
					break;
			case 68:
					CouvertureCompteR(!k1General,gr2Diam,0,&nBof,&yBof);
					break;
			case 70:
					CouvertureCompterTouT();
					break;
			case 72:
					CouvertureCompteR(!k1General,grXY,0,&nBof,&yBof);
					break;
			case 73:
					CouvertureDecompterBieN("symétrique",grP6);
					break;
			case 74:
					CouvertureDecompterBieN("symétrique",grX);
					break;
			case 76:
					CouvertureDecompterBieN("symétrique",grXX);
					break;
			case 80:
					CouvertureCompterTouT();
					break;
			case 97:
					Titrer("test de DagArborer sur grP8 symétrique");
					GrapheCreer1(&pgG,grP8,k1Creer);
						//échanger les sommets 2 et 3, expressément.
							GrapheDesarquer(pgG,1,2);GrapheDesarquer(pgG,2,3);GrapheDesarquer(pgG,3,4);
							GrapheArquer(pgG,1,3);   GrapheArquer(pgG,3,2);   GrapheArquer(pgG,2,4);
						GrapheSymetriser(pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->coulh[aK]=1+aK;
						GrapheVoir(pgG,"Graphe pgG à matricer");
						MatriceAllouer1(&pmE,pgG->nSommetEnTout);
							MatriceDepuisGraphe(pgG,!k1Incidence,&pmE);
							MatriceVoir("grP8 symétrique",pmE);
		//char *sContexte=sC2b(sItem(sgrNoM,1+nGraphe),sChoix0(nPivot>0,sC2b("avec",sPluriel(nPivot,"pivot"))));
							iBof=iCouvertureDecompterBiS(pmE,0,muNeutre,0,k1Afficher,&zBof);
						free(pmE);
					GrapheCreer0(&pgG,kF);
					break;
			case 98:
					//Titrer("test CouvertureTESTER");
					CouvertureTESTER();
					break;
			case 99:
					//Titrer("test CouvertureEprouveR");
					//iCouvertureEstimeR(200);
					CouvertureEstimerTouT();
					break;
			case 100:
					//Titrer("test CouvertureEprouveR");
					iKouvertureEstimeR(grP2,kV,30,30);//$ grP2 grP3 grC3
					//CouvertureEstimerTouT();
					break;
			case 500:	DeterminantSelecteurCalculeR(7);//-1,-25,-121,-361,-841
						break;
			default:QuadTesteR(iTest);
		}
	if (iTest<0) Appel1(sC2("FormeTESTER,test n°",sEnt(iTest)));
}//FormeTESTER

int bFormeTrianguleR(fMathricE *pmA,int bCommutatif){
	//rend vrai ssi le déterminant de la matrice ppmT est non nul;calcul exact sur les entiers par élimination gaussienne
	const int kbAlterner=kV;
	const int kbGausser=kF;
	int uL,uC,uD,bDerouter,uP,nPivot,nEtape,bTrianguler,nPermutation,bNul;
	f fIndex,fValeur,fPivot,fProduit,fDivision,fB,fAD,fD,fDmut,fDivmut,fFois,fSomme;
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	//MathriceVoiR("pmA originale",pmA);
	bCommutatiF=bCommutatif;
	printf("La triangulation %s en mode commutatif.\n",sEst(bCommutatiF));
	bNul=bFormeNullE(pmA->fForme[1][1]);
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=pmA->nLigne && nPivot>=uD-1;uD++){
			//MathriceVoiR(sC2("pmA n°",sEnt(uD)),pmA);
				bNul=bFormeNullE(pmA->fForme[uD][uD]);//tb("bNul111111",bNul);
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uP=uD;uP<=pmA->nColonne;nEtape++,uP++){
					fIndex=pmA->fForme[uD][uP];
					if (nPivot==0 && !bFormeNullE(pmA->fForme[uD][uP]))
						nPivot=uP;
				}
			//tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<pmA->nLigne; 
			//tb("nPivot>=uD",nPivot>=uD);
			if (nPivot!=0){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (nPermutation++,uL=1;uL<=pmA->nLigne;nEtape++,uL++){
						fValeur=pmA->fForme[uL][nPivot];
						pmA->fForme[uL][nPivot]=pmA->fForme[uL][uD];
						pmA->fForme[uL][uD]=fValeur;
					}
				}
				MathriceVoiR(sC2("pmA recolonné n°",sEnt(uD)),pmA);
				fPivot=pmA->fForme[uD][uD];
				//FormeVoiR("fPivot",fPivot);
				bNul=bFormeNullE(pmA->fForme[uD][uD]);//tb("bNul22222",bNul);
				Assert1("bFormeTrianguleR01",!bNul);
				//tee("uD,ivPivot",uD,ivPivot);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux (leur ppcm suffit)
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						fPivot=pmA->fForme[uD][uD];//a
						for (uL=uD+1;uL<=pmA->nLigne;uL++){
							fFois=pmA->fForme[uL][uD];//c si matrice ligne 1=ab,ligne2=cd.
							bNul=bFormeNullE(pmA->fForme[uL][uD]);
							//FormeVoiR(sC2("pmA->fForme",sCouple(uL,uD)),pmA->fForme[uL][uD]);
							//tb("bNul333",bNul);
							if (!bNul){
								for (uC=uD;uC<=pmA->nColonne;uC++){//fabriquer d-bc/a ou (ad-bc)/a selon kbGauss
									fB=pmA->fForme[uD][uC];//b ligne 1
									fD=pmA->fForme[uL][uC];//d ligne 2
									if (0 && bImpair(uD))
										FormeMultiplieR(fFois,fB,&fProduit);//bc
									else FormeMultiplieR(fB,fFois,&fProduit);//bc
									if (kbAlterner)
										FormeFoisseR(-1,&fProduit);//-bc
									if (kbGausser){
										FormeVoiR("fNumerateur",fProduit);FormeVoiR("fDenominateur",fPivot);
										FormeDiviseR(fProduit,fPivot,&fDivision);// -(bc)/a
										FormeVoiR("fDivision",fDivision);
										FormeMutualiseR(fD,fDivision,&fDmut,&fDivmut);
										FormeVoiR("fDmut",fDmut);FormeVoiR("fDivmut",fDivmut);
										FormeAjouteR(fDmut,fDivmut,&fSomme);//d-(bc)/a
										FormeVoiR("fSomme",fSomme);
									}else{
										FormeMultiplieR(fPivot,fD,&fAD);//ad
										//FormeVoiR("fAD",fAD);
										FormeAjouteR(fAD,fProduit,&fSomme);//ad-bc
										//FormeVoiR("fSomme",fSomme);
									}
									FormeCopieR(fSomme,&(pmA->fForme[uL][uC]));
								}
							}
						}//for (uL
						//MathriceVoiR("pmA pivoté",pmA);
						//MathriceDedoublonneR(pmA);
				//MathriceVoiR(sC4b("pmA après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),pmA);
			}else printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//t("céfini de trianguler");
	//bTrianguler=déterminant non nul,ie aucun élément de la diagonale principale n'est le polynome nul
		FormeCreeR("1",&fValeur);
		for (bTrianguler=kV,uD=1;uD<=pmA->nLigne;uD++){
			bNul=bFormeNullE(pmA->fForme[uD][uD]);
			FormeVoiR("Produit diagonal",fValeur);
			FormeMultiplieR(fValeur,pmA->fForme[uD][uD],&fValeur);
			if (bNul)
				bTrianguler=kF;
		}
		//FormeVoiR("Produit diagonal final",fValeur);
		if (0 && bTrianguler)
			FormeCopieR(pmA->fForme[pmA->nLigne][pmA->nLigne],&fValeur);
		FormeVoiR(sC2b("Produit diagonal",sP(sPluriel(fValeur.num[0][0],"terme"))),fValeur);
	//MathriceVoiR(sC2b("ppmT triangulé",sChoix0(!bTrianguler && bDerouter,"(déroutement dû au pivot nul)")),pmA);
	//te("bTrianguler APRES",bTrianguler);
	return(bTrianguler);
}//bFormeTrianguleR

void FormeTrieR(f *pfForme){
	//trie les termes de pfForme par poids (termes positifs ou nuls d'abord), puis par ordre alphabétique croissant.
	f fFormeAvant;
	int uS,nT,uT,nPremier;
	int iPoids,nSommande;
	int nIndex[kuSommandeLiM];
	int iOrdre[kuSommandeLiM];
	FormeCopieR(*pfForme,&fFormeAvant);
	Assert1("FormeTrieR",bFormeAmorceR);
	if (1){
		nSommande=fFormeAvant.num[0][0];
		//iOrdre[uS] soit la valeur du sommande selon le poids du sommande et selon l'ordre alphabétique du premier terme non nul
			for (uS=1;uS<=nSommande;uS++)
				iOrdre[uS]=0;
			for (uS=1;uS<=nSommande;uS++){
				iPoids=fFormeAvant.num[uS][0];
				for (nPremier=0,uT=1;uT<=kuTermeMaX && (nPremier==0);uT++)
					if (fFormeAvant.num[uS][uT]!=0)
						nPremier=uT;
				iOrdre[uS]=nPremier;
				if (iPoids>=0)
					iOrdre[uS]+=kuTermeLiM;
			}
			//te("nSommande",nSommande);
			//Assert1("FormeTrieR1",nSommande>0);
		if (0)
			if (nSommande>0)
				VecteurVoir("iOrdre",iOrdre,1,nSommande);
			else t("Le vecteur iOrdre est vide");
		if (nSommande>0){
			VecteurTrier2(iOrdre,1,nSommande,nIndex);
			//accumuler les termes dans l'ordre défini par nIndex.
				for (uS=1;uS<=nSommande;uS++)
					for (nT=0;nT<=kuTermeMaX;nT++)
						(*pfForme).num[uS][nT]=fFormeAvant.num[nIndex[uS]][nT];
		}//printf("FormeTrieR: %s.\n",sFormE(*pfForme));
	}
}//FormeTrieR
	
void FormeVoiR(char *sQuoi,f fForme){
	Assert1("FormeVoiR",bFormeAmorceR);
	printf("%s: %s.\n",sQuoi,sRapporT(fForme));
}//FormeVoiR
	
int nLettraT(f fForme,int uTerme,int bDenominateurSinonNumerateur){
	int nLettrat,uL;
	for (nLettrat=0,uL=1;uL<kuLettreLiM;uL++)
		if (!bDenominateurSinonNumerateur && fForme.num[uTerme][uL]!=0 || bDenominateurSinonNumerateur && fForme.den[uTerme][uL]!=0)
			nLettrat++;
	return(nLettrat);
}//nLettraT

void LettreR(int uLigne,int uColonne,char cCaractere,fMathricE *pmA){
	FormeCreeR(sC(cCaractere),&pmA->fForme[uLigne][uColonne]);
}//LettreR

void LimiteCalculeR(){
	//calcule la limite de (1+lg(1+lg(1+lg...N
	float rP;
	int uX,uN;
	for (uX=1;uX<=kE2;uX+=1){
		rP=uX;
		for (uN=1;uN<=uX;uN++)
			rP=1+log2(rP);
		printf("%d:%.2f ",uX,rP);
	}
	Ligne();//la limite est 2.00;passe par un maximum de 2.24 pr uX=3 et uX=4 et retombe à 2 pour uX=17,cf détail ci-dessous
	//1:1.00 2:2.00 3:2.24 4:2.24 5:2.20 6:2.15 7:2.11 8:2.08 9:2.06 10:2.04 11:2.03 12:2.02 13:2.02 14:2.01 15:2.01 16:2.01 17:2.00 18:2.00 19:2.00
}//LimiteCalculeR

void MathriceAffecteR(fMathricE **ppmA){
	int uL,uC;
	char cCar='A';
	for (uL=1;uL<=(*ppmA)->nLigne;uL++)
		for (uC=1;uC<=(*ppmA)->nColonne;uC++)
			FormeCreeR(sC(cCar++),&(*ppmA)->fForme[uL][uC]);
}//MathriceAffecteR

void MathriceAlloueR(int nLigneMax,int nColonneMax,fMathricE **ppmA){
	Assert2("MathriceAlloueR",bCroit(1,nLigneMax,kuLigneMaX),bCroit(1,nColonneMax,kuColonneMaX));
	int nSize=sizeof(fMathricE);
	if (0) te("nSize",nSize);
	int uL,uC;
	//Appel0("MathriceAlloueR");
		*ppmA=malloc(sizeof(fMathricE));
		(*ppmA)->nLigne=nLigneMax;
		(*ppmA)->nColonne=nColonneMax;
		for (uL=1;uL<=nLigneMax;uL++)
			for (uC=1;uC<=nColonneMax;uC++)
				FormeRazeR(&(*ppmA)->fForme[uL][uC]);
	//Appel1("MathriceAlloueR");
}//MathriceAlloueR

void MathriceDedoublonneR(fMathricE *pmA){
	int uL,uC;
	//Appel0("MathriceDedoublonneR");
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC++)
				FormeDedoublonneR(&pmA->fForme[uL][uC]);
	//Appel1("MathriceDedoublonneR");
}//MathriceDedoublonneR

void MathriceEvalueR(int nCoteh){
	int uC,nColonne,nColonneMax,uL,nLigne,nLigneMax;
	fMathricE *pmA;
	const int kuCroixPassante=8;
	int nMotif,uPaveh,uPavehMax,nSommet;
	uPavehMax=nCoteh;
	Appel0("MathriceEvalueR");
		//générer la matrice formelle
			nSommet=kuCroixPassante*nCoteh*nCoteh;
			nSommet+=2*nCoteh;//ajoute 2 sommets par colonne: 1 pour le sélecteur amont et 1 pour le sélecteur aval
			nLigneMax=nSommet/2;//Edmonds
			nColonneMax=nLigneMax;
			printf("Le graphe original a %s et la matrice qui le décrit est de dimension %d.\n",sPluriel(nCoteh,"sommet"),nLigneMax);
			MathriceAlloueR(nLigneMax,nColonneMax,&pmA);
			for (nLigne=nColonne=1,uPaveh=1,nMotif=1;uPaveh<=uPavehMax;uPaveh++)
				for (uC=1;uC<=nCoteh;uC++)
					FormeLosangeR(&nLigne,&nColonne,&pmA);
			for (nLigne=1,uPaveh=1,nMotif+=2;uPaveh<=uPavehMax;uPaveh++){
				FormeBordeR(nCoteh,&nLigne,&nColonne,&nMotif,&pmA);
				nLigne+=3*3;
			}
			for (nColonne=1,nLigne-=3,uPaveh=1;uPaveh<=uPavehMax;uPaveh++){
				tee("nLigne,nColonne",nLigne,nColonne);
				FormeDiffuseR(nCoteh,&nLigne,&nColonne,&nMotif,&pmA);
				nColonne+=3*3;
			}
			nLigne=3*3*3;
			nColonne=1;
			for (uPaveh=1;uPaveh<=uPavehMax;uPaveh++){
				if (uPaveh<uPavehMax)
					FormeEntreEtageR(nCoteh,&nLigne,&nColonne,&nMotif,&pmA);
			}
			//ajouter une rétroaction trappe source
				for (uL=1;uL<=nCoteh;uL++)
					FormeCaseR(nMotif,nLigne-uL,nCoteh+1,&pmA);
			MotifSuivanT(&nMotif);
			//FormeMargeR(nCoteh,nLigneMax,&nLigne,&nColonne,&nMotif,&pmA);
			//teee("nLigne,nColonne,nMotif",nLigne,nColonne,nMotif);
			MathriceVoiR("MathriceEvalueR",pmA);
		//DeterminantQalculeR(pmA,k1Voir);
	Appel1("MathriceEvalueR");
}//MathriceEvalueR

void MathriceRempliR(fMathricE *pmA,enum eMathricE maMode){
	int uL,uC;
	char cCar;
	switch (maMode){
		case maAntisymetriquE:	for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=uL+1;uC<=pmA->nColonne;uC++){
										FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
										FormeCreeR(sC2("-",sC(cCar)),&pmA->fForme[uC][uL]);
										cCar=cCaractereSuivanT(cCar);
									}
								break;
		case maBipartiAntisyM:	for (cCar='A',uL=1;uL<=pmA->nLigne/2;uL++)
									for (uC=pmA->nColonne/2+1;uC<=pmA->nColonne;uC++)
										if (uL+pmA->nLigne/2!=uC){
											FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
											FormeCreeR(sC2("-",sC(cCar)),&pmA->fForme[uC][uL]);
											cCar=cCaractereSuivanT(cCar);
										}
								break;
		case maGeneralE:		for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=1;uC<=pmA->nColonne;uC++){
										FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
										cCar=cCaractereSuivanT(cCar);
									}
								break;
		case maGeneralE0:		for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=1;uC<=pmA->nColonne;uC++)
										if (uL!=uC){
											FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
											cCar=cCaractereSuivanT(cCar);
										}
								break;
		case maSymetriquE:		for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=uL+1;uC<=pmA->nColonne;uC++){
										FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
										FormeCreeR(sC(cCar),&pmA->fForme[uC][uL]);
										cCar=cCaractereSuivanT(cCar);
									}
								break;
		case maTriangleInferieuR:for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=1;uC<=uL;uC++){
										//tee("inférieure uL,uC",uL,uC);
										FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
										cCar=cCaractereSuivanT(cCar);
									}
								break;
		case maTriangleSuperieuR:for (cCar='A',uL=1;uL<=pmA->nLigne;uL++)
									for (uC=uL;uC<=pmA->nColonne;uC++){
										//tee("supérieure uL,uC",uL,uC);
										FormeCreeR(sC(cCar),&pmA->fForme[uL][uC]);
										cCar=cCaractereSuivanT(cCar);
									}
								break;
		default: Assert1("MathriceRempliR",kF);
	}
}//MathriceRempliR

void MathriceVoiR(char *sMessage,fMathricE *pmA){
	//affiche la matrice pmA en laissant un blanc en marge gauche
	int uL,uC,nLargeur=2;
	const int kbZeroter=kF;
	char *sRapport=malloc(4*kE3);
	char *sForme=malloc(4*kE3);
		printf("%s:\n",sMessage);
		for (uL=1;uL<=pmA->nLigne;uL++){
			for (uC=1;uC<=pmA->nLigne;uC++)
				if (kF || kbZeroter || !bChaineEgale(sFormE(pmA->fForme[uL][uC],!k1DenominateuR),"0")){
					sRapport=sRapporT(pmA->fForme[uL][uC]);
					if (nChaineLg(sRapport)<=nLargeur)
						printf("%s ",sChaine0(sRapport,nLargeur));
					else printf("%s ",sChaine0(sCrochet(uL,uC),nLargeur));
				}else printf("%s. ",sE(nLargeur-1));
			printf("\n");
		}
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nLigne;uC++)
				if (kbZeroter || !bChaineEgale(sFormE(pmA->fForme[uL][uC],!k1DenominateuR),"0")){
					sRapport=sRapporT(pmA->fForme[uL][uC]);
					if (nChaineLg(sRapport)>nLargeur)
						printf("%s%s: %s.\n",sTab(2),sCrochet(uL,uC),sRapport);
				}
	free(sForme);
}//MathriceVoiR

void MattriceVoiR(char *sMessage,iMathricE *piA){
	//affiche la matrice pmA en laissant un blanc en marge gauche
	const int kuChiffreNb=3;
	int uL,uC;
	const int kbZeroter=kF;
		printf("%s:\n",sMessage);
		for (uL=1;uL<=piA->nLigne;uL++){
			for (uC=1;uC<=piA->nLigne;uC++)
				//printf("%s%2s",sCouple(uL,uC),sFormE(pmA->fForme[uL][uC]));
				if (kbZeroter || piA->iForme[uL][uC]!=0)
					printf("%s",sEntier(piA->iForme[uL][uC],kuChiffreNb));
				else printf("%s ",sE(kuChiffreNb-1));
			printf("\n");
		}
}//MattriceVoiR

void MotifSuivanT(int *pnMotif){
	int nMotif=*pnMotif;
	nMotif=uModulo1(nMotif+1,26);
	*pnMotif=nMotif;
}//MotifSuivanT

void NullisseR(int iElement,int uL,int uC,iMatrice *pmQ){
	int uD,nOffset;
	quad qR=qQuad(iElement);
	teee("uL,uC,iElement",uL,uC,iElement);
	for (nOffset=0,uD=1;uD<=2;uD++){
		pmQ->Mat[8*(uL-1)+2*(uD-1)+1][nOffset+8*(uC-1)+1]=yNb(qR.q11);
		pmQ->Mat[8*(uL-1)+2*(uD-1)+1][nOffset+8*(uC-1)+3]=yNb(qR.q12);
		pmQ->Mat[8*(uL-1)+2*(uD-1)+2][nOffset+8*(uC-1)+1]=yNb(qR.q21);
		pmQ->Mat[8*(uL-1)+2*(uD-1)+2][nOffset+8*(uC-1)+3]=yNb(qR.q22);
		nOffset+=1;
	}
}//NullisseR

void MatriceDedamieR(iMatrice *pmCible){
	int nL,nC,nX,nY,uPas=pmCible->nLigne/4;
	iMatrice *pmCopie;
	MatriceAllouer1(&pmCopie,pmCible->nLigne);
		MatriceDupliquer(pmCible,pmCopie);
		//MatriceVoir("pmCopie",pmCopie);
		MatriceRazer(&pmCible);
		te("uPas",uPas);
		for (nX=-uPas,nL=0;nL<2*uPas;nL++){
			if (nL%uPas==0)
				nX+=uPas;
			for (nY=-uPas,nC=0;nC<2*uPas;nC++){
				if ( nC%uPas==0 )
					nY+=uPas;
				pmCible->Mat[nL+1][nC+1]=pmCopie->Mat[nL+1+nX][nC+1+nY];
			}
		}
		for (nL=0;nL<2*uPas;nL++)
			for (nC=0;nC<2*uPas;nC++)
				pmCible->Mat[nL+1+2*uPas][nC+1+2*uPas]=pmCible->Mat[nL+1][nC+1];
		//MatriceVoir("pmCible",pmCible);
	free(pmCopie);
}//MatriceDedamieR

void MatriceDedamyeR(iMatrice *pmCible){
	int nL,nC,nX,nY,uPas=1;
	iMatrice *pmCopie;
	MatriceAllouer1(&pmCopie,pmCible->nLigne);
		MatriceDupliquer(pmCible,pmCopie);
		//MatriceVoir("pmCopie",pmCopie);
		MatriceRazer(&pmCible);
		te("uPas",uPas);
		for (nX=-uPas,nL=0;nL<4*uPas;nL++){
			if (nL%uPas==0)
				nX+=uPas;
			for (nY=-uPas,nC=0;nC<4*uPas;nC++){
				if ( nC%uPas==0 )
					nY+=uPas;
				pmCible->Mat[nL+1][nC+1]=pmCopie->Mat[nL+1+nX][nC+1+nY];
			}
		}
		if (1) for (nL=0;nL<4*uPas;nL++)
			for (nC=0;nC<4*uPas;nC++)
				pmCible->Mat[nL+1+4*uPas][nC+1+4*uPas]=pmCible->Mat[nL+1][nC+1];
		//MatriceVoir("pmCible",pmCible);
	free(pmCopie);
}//MatriceDedamyeR

void MatriceDemeleR(iMatrice *pmCible){
	//ramène d'abord les lignes impaires
	int uL,uC;
	iMatrice *pmCopie;
	MatriceAllouer1(&pmCopie,pmCible->nLigne);
		MatriceDupliquer(pmCible,pmCopie);
		//MatriceVoir("pmCopie",pmCopie);
		MatriceRazer(&pmCible);
		for (uL=1;uL<=pmCible->nLigne/2;uL++)
			for (uC=1;uC<=pmCible->nLigne;uC++)
				pmCible->Mat[uL][uC]=pmCopie->Mat[2*(uL-1)+1][uC];
		for (uL=2;uL<=pmCible->nLigne;uL+=2)
			for (uC=1;uC<=pmCible->nLigne;uC++)
				pmCible->Mat[pmCible->nLigne/2+uL/2][uC]=pmCopie->Mat[uL][uC];
		MatriceVoir("Demêlée",pmCible);
	free(pmCopie);
}//MatriceDemeleR

void NullissimeR(){
	iMatrice *pmA,*pmAB,*pmE;
	long yDeterminant;
	Appel0("NullissimeR");
	//QuadVoir("qQuad(+2)",qQuad(+2));QuadVoir("qQuad(-2)",qQuad(-2));
	Assert1("NullissimeR44",bQuadNul(qQuadMul(qQuad(+2),qQuad(-2))));
	Assert1("NullissimeR55",bQuadNul(qQuadMul(qQuad(+3),qQuad(-3))));
	//pmA:=matrice de A à déterminant nul
		MatriceAllouer1(&pmA,2);
		pmA->Mat[1][1]=+2;pmA->Mat[2][2]=-pmA->Mat[1][1];
		pmA->Mat[2][1]=+3;pmA->Mat[1][2]=-pmA->Mat[2][1];
		MatriceVoir("Matrice A de numéros de quads",pmA);
	//pmE:=matrice quinconcée de AxB
		MatriceAllouer1(&pmE,2*pmA->nLigne);
		SystemeComposeR(pmA,pmE);
		MatriceVoir("Système d'équations, chaque élément étant un numéro de quad",pmE);
	//pmAB:=matrice quinconcée quadée de AxB
		MatriceAllouer1(&pmAB,4*pmE->nLigne);
			SystemeExpanseR(pmE,pmAB);
			MatriceVoir("Système d'équations, chaque élément étant un coefficient de quad",pmAB);
			yDeterminant=yMatriceDeterminant(pmAB);
			ld(yDeterminant);
			if (0){
				MatriceDedamieR(pmAB);
				yDeterminant=yMatriceDeterminant(pmAB);
				ld(yDeterminant);
				pmAB->nLigne=pmAB->nColonne=pmAB->nLigne/2;
				MatriceVoir("Quart de Matrice finale pmAB",pmAB);
				yDeterminant=yMatriceDeterminant(pmAB);
				ld(yDeterminant);
				MatriceDemeleR(pmAB);
				yDeterminant=yMatriceDeterminant(pmAB);
				ld(yDeterminant);
				MatriceDedamyeR(pmAB);
				MatriceVoir("Quart de quart de  Matrice finale pmAB",pmAB);
				yDeterminant=yMatriceDeterminant(pmAB);
				ld(yDeterminant);
				pmAB->nLigne=pmAB->nColonne=pmAB->nLigne/2;
				MatriceVoir("Quart de quart de  Matrice finale pmAB",pmAB);
				yDeterminant=yMatriceDeterminant(pmAB);
				ld(yDeterminant);
			}
		free(pmAB);
	Appel1("NullissimeR");
}//NullissimeR

void PermanentCalculeR(int nSommet,enum eMathricE maMode){
	fMathricE *pmA;
	MathriceAlloueR(nSommet,nSommet,&pmA);
	MathriceRempliR(pmA,maMode);
	//MathriceRempliR(pmA,maAntisymetriquE);
	MathriceVoiR("pmA",pmA);
	PermanentKalculeR(pmA,k1Voir);
}//PermanentCalculeR

void PermanentKalculeR(fMathricE *pmA,int bVoir){//O(exponentiel)
	f fKalcul;
	nSignatureKalculeR=0;
	SignatureKalculeR(pmA,!k1AlterneR,&fKalcul);
	FormeTrieR(&fKalcul);
	if (bVoir){
		FormeVoiR("Permanent",fKalcul);
		te("Nombre de termes",fKalcul.num[0][0]);
	}
}//PermanentKalculeR

int noPolyAdD(int bPoly,int noA,int noB){
	int nAdd=noA+noB;
	if (bPoly)
		nAdd=noDagAjouter(noA,DagAddition,noB);
	return(nAdd);
}//noPolyAdD

int noPolyAfF(int bPoly,int noElement){
	int nAff=noElement;
	if (bPoly)
		nAff=noDagAjouter(noElement,DagNombre,noElement);
	return(nAff);
}//noPolyAfF

int noPolyDiV(int bPoly,int noA,int noB){
	int nDiv=noA*noB;
	if (bPoly)
		nDiv=noDagAjouter(noA,DagDivision,noB);
	return(nDiv);
}//noPolyDiV

int noPolyMuL(int bPoly,int noA,int noB){
	long nMul=noA*noB;
	if (bPoly)
		nMul=noDagAjouter(noA,DagProduit,noB);
	return(nMul);
}//noPolyMuL

int noPolySuB(int bPoly,int noA,int noB){
	int nSub=noA-noB;
	if (bPoly)
		nSub=noDagAjouter(noA,DagSoustraction,noB);
	return(nSub);
}//noPolySuB

int nProduitEnTouT(iMatrice *pmA){
	//dénombre les produits non nuls d'éléments purs ou non situés sur des lignes et colonnes distinctes (au sens du déterminant)
	const int bTout=kF;
	int nCas,bCompatible,nConfig,nConfigLim,bPur;
	int bCouplage,bDistinct,nValide,iProduit,bHomogene,nGene;
	int uL,uC;
	int nSommat=pmA->nLigne;
	int iPris[1+nSommat];
	int nColonne[1+nSommat];
	//te("nSommat",nSommat);
	//prendre 1 élément non nul dans chaque colonne et chaque ligne distincte Ajouter si produit non nul
	//énumérer les combinaisons distinctes et compter ds nValide les séquences non nulles
		nConfigLim=zPuissance(nSommat,nSommat);
		printf("Configurations: %d**%d=%s.\n",nSommat,nSommat,sPar3(nConfigLim));
		for (nValide=0,nConfig=0;nConfig<nConfigLim;nConfig++){
			//tee("nConfig,nValide",nConfig,nValide);
			VecteurRazer(nColonne,1,nSommat);
			for (nCas=nConfig,uC=1;uC<=nSommat;uC++){
				uL=1+nCas%nSommat;
				//tee("uL,uC",uL,uC);
				Assert2("nProduitEnTouT",bCroit(1,uL,nSommat),bCroit(1,uC,nSommat));
				iPris[nSommat+1-uC]=pmA->Mat[uL][nSommat+1-uC];
				nColonne[uL]=(nColonne[uL]==0) ? uC: -uC;
				nCas=nCas/nSommat;
			}
			for (bDistinct=1,uC=1;uC<=nSommat;uC++)
				bDistinct=bDistinct && (nColonne[uC]>0);
			if (bDistinct){
				for (iProduit=1,uL=1;uL<=nSommat;uL++)
					iProduit*=iPris[uL];
				bCompatible=iProduit!=0;
				nValide+=bCompatible;
				if (bCompatible){//tous les termes de iPris[] sont non nuls vu bCompatible
					//bHomogene:=les termes du produit courant qui excèdent 1 en valeur absolue ont des valeurs absolues identiques.
						for (bHomogene=kV,nGene=0,uL=1;uL<=nSommat;uL++)
							if (abs(iPris[uL])>1)
								if (nGene==0)
									nGene=abs(iPris[uL]);
								else bHomogene=bHomogene && abs(iPris[uL])==nGene; 
						//teee("bHomogene,iProduit,iProduit%15",bHomogene,iProduit,iProduit%15);
						if (bCompatible)
							Assert1("nProduitEnTouT44",bHomogene==(iProduit%15!=0));
					bPur=bCompatible && bHomogene;
					if (bTout || bPur)
						VecteurVoir(sC3( (bPur)? sChaineEtale1("PRODUIT DE TERMES DE VALEUR ABSOLUE EGALE") :"produit non nul"," n°",sEnt(nValide)),iPris,1,nSommat);
					if (bPur){
					//bCouplage:= le transposé de chaque élément pris est également pris
						for (printf("Éléments du produit:"),uC=1;uC<=nSommat || !bLigne();uC++)
							printf(" %s%c",sCouple(uC,nColonne[nSommat+1-uC]),(uC<nSommat)?',':'.');
						for (bCouplage=kV,uL=1;uL<=nSommat;uL++){
							uC=nSommat+1-nColonne[uL];
							bCouplage=bCouplage && iPris[uC]== - iPris[nSommat+1-nColonne[uC]];//et non nuls vu bCompatible
							//teeee("uL,uC,nColonne[nSommat+1-uC0],bCouplage",uL,uC,nColonne[nSommat+1-uL],bCouplage);
						}
						//tb("bCouplage",bCouplage);
						//Assert1("nProduitEnTouT7",bCouplage);
					}
				}
			}
		}
	return(nValide);
}//nProduitEnTouT

void QuadripoleMinimalTESTER2(iMatrice *pmE){
	int uC,uL;
	quad qSignature;
	qMatrice *pmqA;
	//Appel0("QuadripoleMinimalTESTER");
		MatriceAllouer(&pmE);//raze
		MatriceVoirLitteral(kF);
		//GrafixeR(3,pmE);
		GraphixeR(13,pmE);
		if (0){
			MatriceVoir("pmE graphixée",pmE);
			//MatriceTransposer(pmE);
			DeterminantConfronteR(pmE);
			if (0){
				//DeterminantConfronteR(pmE);
				//MatriceTransposer(pmE);
				pmqA=malloc(sizeof(qMatrice));
				pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
				for (uL=1;uL<=pmE->nLigne;uL++)
					for (uC=1;uC<=pmE->nLigne;uC++)
						pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
				//QuadMatriceVoir("pmqA",pmqA);
			}
		}
		//yBof=iFormeCalculeR(pmE);//Mahajan noeud
		
		//bBof=bQuadDeterminer(pmqA);//Mahajan quad
		//yBof=yFormeKalculeR(pmE,nSommet,k1Voir);//Urbanska simple
		//iBof=iFormeQalculeR(pmE,0);//Urbanska quad
		//zAppelExponentieL=0;
		//qSignature=qSignatureQalculeR(pmqA,k1Alterner);
		//printf("************************** SIGNATURE: %s.\n",sQuad(qSignature));
		if (0){//transposer
			for (uL=1;uL<=pmE->nLigne;uL++)
				for (uC=1;uC<=pmE->nLigne;uC++)
					pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uC][uL]);
			zAppelExponentieL=0;
			qSignature=qSignatureQalculeR(pmqA,k1Alterner);
			printf("************************** SIGNATURE: %s.\n",sQuad(qSignature));
		}
	//Appel1("QuadripoleMinimalTESTER");
}//QuadripoleMinimalTESTER2

void QuadripoleMinimalTESTER3(iMatrice *pmE){
	//mutex
	graf *pgG;
	int nDim,aK,nPoleEnTout;
	int sSource,sTrappe;
	Appel0("QuadripoleMinimalTESTER3");
		MatriceAllouer(&pmE);//raze
		MatriceVoirLitteral(kF);
		nDim=3;
		GraphixeR(100+nDim,pmE);
		//MatriceVoir("pmE graphixée",pmE);
		GrapheCreer(-pmE->nLigne,&pgG);
		if (0) MatriceVoir("mutex graphixé final",pmE);
		MatriceGrapher(pmE,pgG);
		//attribuer un coût unitaire aux seul arcs du graphe original
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				pgG->nCout[aK]=(pgG->coulh[aK]==1);
			VecteurValuer(pgG->nCout,1,pgG->nArcEnTout,1);
		if (0) GrapheVoir(pgG,"apres MatriceGrapher");
		nPoleEnTout=2*nDim;
		sSource=nPoleEnTout+1;//entrée du premier hème
		sTrappe=pgG->nSommetEnTout-2;//sortie du dernier hème
		//te("sDestination",sDestination);
		//tee("sSource,sTrappe",sSource,sTrappe);
		if (0) GrapheVoir(pgG,"avant FlotOptimiser");
		FlotOptimiser(pgG,nDim,sSource,sTrappe,k1Afficher);
	Appel1("QuadripoleMinimalTESTER3");
}//QuadripoleMinimalTESTER3

void QuadTesteR(int iTest){
	//teste le présent module
	int nDim,uC,uL,uF;
	long yDeterminant;
	iMatrice *pmE;
	riMatrice *pmK;
	qMatrice *pmqA;
	quad qSignature;
	int nQuadTest;
	ri riDeterminant;
	iTest=50;
	Appel0(sC2("QuadTesteR,test n°",sEnt(iTest)));
		Assert1("QuadTesteR",bFormeAmorceR);
		switch (iTest) {
			case 50:
					Titrer("Matrice minimale de complexes");
					MatRIceAllouer1(&pmK,2);//raze
					pmK->Mat[1][1].r=3;pmK->Mat[1][1].i=1;pmK->Mat[1][2].r=3;
					pmK->Mat[2][1].r=3;pmK->Mat[2][2].r=3;pmK->Mat[2][2].i=-1;
					MatRIceVoir("pmK",pmK);
					riDeterminant=riFormeCalculeR(pmK);//$
					printf("Le déterminant de la matrice vaut %s.\n",sK(riDeterminant));
				break;
			case 60:
					Titrer("Matrice minimale de quads");
					MatriceAllouer1(&pmE,2);//raze
					pmE->Mat[1][1]=2;pmE->Mat[1][2]=3;
					pmE->Mat[2][1]=3;pmE->Mat[2][2]=2;
					yDeterminant=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
					printf("Le déterminant de la matrice vaut %ld.\n",yDeterminant);
				break;
			case 61://Urbanska00
					Titrer("Matrice minimale de quads");
					MatriceAllouer1(&pmE,3);
					pmE->Mat[1][1]=0;pmE->Mat[1][2]=2;pmE->Mat[1][3]=3;
					pmE->Mat[2][1]=4;pmE->Mat[2][2]=0;pmE->Mat[2][3]=2;
					pmE->Mat[3][1]=5;pmE->Mat[3][2]=0;pmE->Mat[3][3]=0;
					yDeterminant=yFormeKalculeR(pmE,nDim,k1Voir);//Urbanska simple
					printf("Le déterminant de la matrice vaut %ld.\n",yDeterminant);
				break;
			case 62:
					Titrer("Urbanska0 sur QUADRIPOLE");
					MatriceAllouer(&pmE);//raze
						nDim=2;
						MatriceQuadripoler(nDim*10+0,k1Boucler,&pmE);
						MatriceVoir("QUADRIPOLE pmE",pmE);
						//yDeterminant=iFormeQalculeR(pmE,nDim);
					break;
			case 80://déterminant "Fibonacci" F(pmE->nLigne-1). F(0)=0,F(1)=1,F(2)=1,F(3)=2,F(4)=3,F(5)=5,F(6)=8,F(7)=13,F(8)=21,F(9)=34,F(10)=55.
					Titrer("Quads sur matrice de Fibonacci");
					for (uF=1;uF<=15;uF++){
						MatriceAllouer1(&pmE,uF);//F(13)=144
							MatriceBander(-1,&pmE);MatriceFoisser(-1,&pmE);
							MatriceBander(0,&pmE);pmE->Mat[1][1]=0;
							MatriceBander(+1,&pmE);
							//MatriceVoir("matrice de Fibonacci",pmE);
							DeterminantConfronteR(pmE);
						free(pmE);
					}
					if (0){
						pmqA=malloc(sizeof(qMatrice));
						pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
						for (uL=1;uL<=pmE->nLigne;uL++)
							for (uC=1;uC<=pmE->nLigne;uC++)
								pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
								//pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]*zPuissance(10,uC-1));
						MatriceVoir("pmE",pmE);
						printf("***************** Déterminant attendu:%ld.\n",zFib(pmE->nLigne-1));
						QuadMatriceVoir("pmqA",pmqA);
						qSignature=qSignatureQalculeR(pmqA,k1Alterner);//déterminant:F(pmE->nLigne-1),donc F(3-1)=1 et F(4-1)=2
						QuadVoir("qSignature",qSignature);
					}
					break;
			case 81:
					//Titrer("Urbanska0 sur QUADRIPOLE");
					MatriceAllouer(&pmE);//raze
						nDim=2;
						MatriceQuadripoler(nDim*10+0,k1Boucler,&pmE);
						MatriceVoir("QUADRIPOLE pmE",pmE);
						pmqA=malloc(sizeof(qMatrice));
						pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
						for (uL=1;uL<=pmE->nLigne;uL++)
							for (uC=1;uC<=pmE->nLigne;uC++)
								pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
						//QuadMatriceVoir("pmqA",pmqA);
						qSignature=qSignatureQalculeR(pmqA,k1Alterner);
						QuadVoir("qSignature",qSignature);
					break;
			case 90:
					Titrer("test sur QUADRIPOLE réorganisé");
					MatriceAllouer(&pmE);//raze
						nDim=3;
						nQuadTest=nDim*10+1;
						MatriceQuadripoler(nQuadTest,!k1Boucler,&pmE);
						FormeArrangeR(nDim,&pmE);
						MatriceVoir("AVANT MatriceDepermuter",pmE);
							MatriceDepermuter(pmE);
						//MatriceVoir("APReS MatriceDepermuter",pmE);
						DeterminantConfronteR(pmE);
						if (1){
							pmqA=malloc(sizeof(qMatrice));
							pmqA->nLigne=pmqA->nColonne=pmE->nLigne;
							for (uL=1;uL<=pmE->nLigne;uL++)
								for (uC=1;uC<=pmE->nLigne;uC++)
									pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);
							//QuadMatriceVoir("pmqA",pmqA);
							zAppelExponentieL=0;
							qSignature=qSignatureQalculeR(pmqA,!k1Alterner);
							printf("Quad test n°%d: qSignature=%s.\n",nQuadTest,sQuad(qSignature));
							bBof=bQuadDeterminer(pmqA);//Mahajan quad
						}
						//iBof=iFormeQalculeR(pmE,0);//Urbanska quad
						//tee("kxLongintMax,kyLongintMin",kxLongintMax,kyLongintMin);
					break;
			case 91:
					Titrer("test sur QUADRIPOLE minimal");
					MatriceAllouer(&pmE);//raze
						QuadripoleMinimalTESTER1(pmE);
					break;
			case 92:
					Titrer("test sur QUADRIPOLE minimal");
						QuadripoleMinimalTESTER2(pmE);
					break;
			case 95:
					Titrer("test sur QUADRIPOLE minimal");
						QuadripoleMinimalTESTER3(pmE);
					break;
			case 100:
					DeterminantNonNulVerifieR();
					break;
			default:break;
		}
	Appel1(sC2("QuadTesteR,test n°",sEnt(iTest)));
}//QuadTesteR

char *sRapporT(f Forme){
	char *sRapport=malloc(kuFormeLiM);
	int bEgale=bChaineEgale(sFormE(Forme,k1DenominateuR),"1");
	//bEgale=kF;
	if ( !bEgale )
		sRapport=sC3(sFormE(Forme,!k1DenominateuR),"/",sFormE(Forme,k1DenominateuR));
	else sRapport=sFormE(Forme,!k1DenominateuR);
	return(sRapport);
}//sRapporT

void SegmentBanniR(graf *pgG){//O(S3)
	//bannit tous les segments impropres de pgG; les segments bannis autour du pivot ont des branches de même couleur.
	const int kuPivotCouleur=1;
	int aK,aL,aM,nTour,sX,sY,sZ,sT;
	Assert1("SegmentBanniR0",bGrapheSymetrique(pgG));
	int uSommat=pgG->nSommetEnTout;
		if (1)//segment de longueur 1 interdit
			for (sX=1;sX<=uSommat;sX++)//O(S2)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//O(S)
					if (pgG->coulh[aK]==kuPivotCouleur)
						BanniR(sX,sY=pgG->sSuk[aK],0, 0);
		if (1)//segment de longueur 2 interdit
			for (sX=1;sX<=uSommat;sX++)//O(S3)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//O(S2)
					for (sY=pgG->sSuk[aK],aL=pgG->aHed[sY];aL<pgG->aHed[sY+1];aL++)//O(S)
						if ( bDistinct3(sX,sY,sZ=pgG->sSuk[aL]) && sX<sZ )
							BanniR(sX,sY,sZ, 0);
		if (1)//segment de longueur 3 interdit
			for (sY=1;sY<=uSommat;sY++)//O(S2)
				for (aK=pgG->aHed[sY];aK<pgG->aHed[sY+1];aK++)//O(S)
					if (pgG->coulh[aK]==kuPivotCouleur){
						for (sZ=pgG->sSuk[aK],nTour=0,aL=pgG->aHed[sY];aL<pgG->aHed[sY+1];aL++)//O(1)
							for (sX=pgG->sSuk[aL],aM=pgG->aHed[sZ];aM<pgG->aHed[sZ+1];nTour++,aM++)
								if (sT=pgG->sSuk[aM],pgG->coulh[aL]==pgG->coulh[aM] && bDistinct4(sX,sY,sZ, sT))
									BanniR(sX,sY,sZ, sT);
						Assert1(sC2b("SegmentBanniR1: nTour=",sPar3(nTour)),nTour<10);
					}//if
}//SegmentBanniR

void SignatureCalculeR(int nSommet){
	fMathricE *pmA;
	MathriceAlloueR(nSommet,nSommet,&pmA);
	MathriceRempliR(pmA,maAntisymetriquE);
	MathriceVoiR("pmA maAntisymetriquE pour le déterminant",pmA);
	MathriceRempliR(pmA,maSymetriquE);
	MathriceVoiR("pmA maSymetriquE pour le permanent",pmA);
	MathriceRempliR(pmA,maAntisymetriquE);
	DeterminantKalculeR(pmA,k1Voir);
	MathriceRempliR(pmA,maSymetriquE);
	PermanentKalculeR(pmA,k1Voir);
}//SignatureCalculeR

void SignatureKalculeR(fMathricE *pmA,int bAlterner,f *pfAccu){//O(exponentiel)
	int bVoir=kF;
	int uL,uPivot,bPivotNul,muSigne;
	int nL,nC,uC;
	fMathricE *pmB;
	nSignatureKalculeR++;
	if (nSignatureKalculeR%kE2==0)
		te("nSignatureKalculeR",nSignatureKalculeR);
	f fForme,fProduit,fAccu,fOperande;
	//tee("pmA->nLigne,bAlterner",pmA->nLigne,bAlterner);
	if (pmA->nLigne>1){
		//if (kbVoir) MathriceVoiR("SignatureKalculeR1",pmA);
		FormeCreeR("0",&fAccu);
		for (muSigne=1,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
			bPivotNul=bFormeNullE(pmA->fForme[uPivot][1]);
			Assert1("SignatureKalculeR7",bBool(bPivotNul));
			//tee("uPivot,bPivotNul",uPivot,bPivotNul);
			if (bPivotNul==0){
				//Titrer("pivot non nul");
				if (bVoir) FormeVoiR("Pivot non nul",pmA->fForme[uPivot][1]);
				MathriceAlloueR(pmA->nLigne-1,pmA->nColonne-1,&pmB);
				//pmB soit le cofacteur associé,ie la copie de pmA amputée de la colonne 1 et de la ligne uPivot
					for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
						if (uL!=uPivot)
							for (nL++,nC=0,uC=2;nC++,uC<=pmA->nLigne;uC++)
								pmB->fForme[nL][nC]=pmA->fForme[uL][uC];
					//MathriceVoiR("SignatureKalculeR2",pmB);
				bVoir=(pmB->nLigne==2);
				if (bVoir) MathriceVoiR("pmB",pmB);
				//if (bVoir) FormeVoiR("Multiplicande1",fForme);
				SignatureKalculeR(pmB,bAlterner,&fForme);
				if (bVoir) FormeVoiR("Signature",fForme);
				//if (bVoir) FormeVoiR("Multiplicande2",pmA->fForme[uPivot][1]);
				FormeCopieR(pmA->fForme[uPivot][1],&fOperande);
				//if (bVoir) FormeVoiR("fOperande AVANT",fOperande);
				if (muSigne<0)
					FormeFoisseR(-1,&fOperande);
				//if (bVoir) FormeVoiR("fOperande APRES",fOperande);
				FormeMultiplieR(fForme,fOperande,&fProduit);
				FormeVoiR("Produit",fProduit);
				FormeVoiR("fAccu AVANT",fAccu);
				FormeAjouteR(fProduit,fAccu,&fAccu);
				FormeVoiR("fAccu APRES",fAccu);
			}
			if (bAlterner)
				muSigne=-muSigne;
		}
		FormeCopieR(fAccu,pfAccu);
		//if (kbVoir) FormeVoiR("pfAccu FINAL then",*pfAccu);
	} else {*pfAccu=pmA->fForme[1][1];
		//if (kbVoir) FormeVoiR("pfAccu FINAL else",*pfAccu);
	}
	//if (kbVoir) FormeVoiR("pfAccu final",*pfAccu);
}//SignatureKalculeR

int bSignaturePairE(fMathricE *pmA,char *sCouplage){
	int nCar,nC,nL,uC,uL,ipP,uP;
	char cCar;
	int nInversion;
	int bSucces;
	int bPaire=kF;
	int nPermutation[1+pmA->nLigne];
	//Appel0("bSignaturePairE");
		for (ipP=0,nCar=0;nCar<nChaineLg(sCouplage);nCar++){
			cCar=sCouplage[nCar];
			//tc("cCar",cCar);
			//empiler la permutation induite par cCar dans pmA
				for (nL=0,nC=0,uL=1;uL<=pmA->nLigne;uL++)
					for (uC=1;uC<=pmA->nColonne;uC++){
						if (bSucces=bChaineEgale(sFormE(pmA->fForme[uL][uC],!k1DenominateuR),sC(cCar)),bSucces){
							nPermutation[++ipP]=uL;
							nPermutation[++ipP]=uC;
							//tt("sFormE(pmA->fForme[uL][uC]",sFormE(pmA->fForme[uL][uC]));
							//tb("bSucces",bSucces);
						}
					}
		}
		//te("ipP",ipP);
		VecteurVoir("nPermutation",nPermutation,1,ipP);
		//bPaire:=permutation paire
			for (nInversion=0,uP=1;uP<=ipP;uP++)
				if (uP>nPermutation[uP])
					nInversion++;
			te("nInversion",nInversion);
			bPaire=bPair(nInversion);
	//Appel1("bSignaturePairE");
	return(bPaire);
}//bSignaturePairE

quad qSignatureQalculeR(qMatrice *pmqA,int bAlterner){
	//rend la signature "laborieuse" de pmA,ie calculée par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	const int bVoir=kF;
	int uC,uL,nL,nC,uPivot;
	quad qSignature,qProduit,qSigne,qSousSignature,qOperande;
	qMatrice *pmqB;
	//Appel0("qSignatureCalculeR");
		Assert2("qSignatureQalculeR56",pmqA->nLigne==pmqA->nColonne,bBool(bAlterner));
	zAppelExponentieL++;
	if (zAppelExponentieL % kE5==0 && zAppelExponentieL>=kE6)
		printf("zAppelExponentieL=%s.\n",sPar3(zAppelExponentieL));
	//te("pmqA->nLigne",pmqA->nLigne);
	if (pmqA->nLigne>1){
		//if (bVoir) QuadMatriceVoir("Matrice Reçue",pmqA);
		for (qSignature=qQuad(0),qSigne=qQuad(1),uPivot=1;uPivot<=pmqA->nLigne;uPivot++){
			//te("uPivot",uPivot);
			if (!bQuadNul(pmqA->Mat[uPivot][1])){
				pmqB=malloc(sizeof(qMatrice));
					//pmqB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
						for (nL=0,uL=1;uL<=pmqA->nLigne;uL++)
							if (uL!=uPivot)
								for (nL++,nC=0,uC=2;nC++,uC<=pmqA->nColonne;uC++)
									pmqB->Mat[nL][nC]=pmqA->Mat[uL][uC];
						pmqB->nLigne=pmqB->nColonne=pmqA->nLigne-1;
					//if (bVoir) QuadMatriceVoir("sous-Matrice B",pmqB);
					qSousSignature=qSignatureQalculeR(pmqB,bAlterner);
				free(pmqB);
				//if (bVoir) QuadVoir("qSousSignature",qSousSignature);
				//if (bVoir) QuadVoir("qSigne",qSigne);
				//if (bVoir) QuadVoir("pmqA->Mat[uPivot][1]",pmqA->Mat[uPivot][1]);
				qOperande=qQuadMul(qSigne,pmqA->Mat[uPivot][1]);
				qProduit=qQuadMul(qOperande,qSousSignature);//oui,qSousSignature est opérande droit
				if (bVoir && !bQuadNul(qOperande) && !bQuadNul(qSousSignature)) printf("%s=%sx%s.\n",sQuad(qProduit),sQuad(qOperande),sQuad(qSousSignature));
				qSignature=qQuadAdd(qSignature,qProduit);
				if (bVoir && !bQuadNul(qSignature) && !bQuadNul(qProduit)) QuadVoir("qSignature",qSignature);
			}
			if (bAlterner)
				qSigne=qQuadNeg(qSigne);
		}//for uPivot
		//QuadVoir("qSignature",qSignature);
	} else qSignature=pmqA->Mat[1][1];
	//Appel1("qSignatureCalculeR");
	if (bVoir && !bQuadNul(qSignature)) QuadVoir("qSignature renvoyée",qSignature);
	return(qSignature);
}//qSignatureQalculeR

void SkewClosurE0(iMatrice *pmA,int uParcoursLgMax,iMatrice **ppmAchapo){//O(N4)
	//rend dans ppmqAchapo[uH][uL] la somme des produits des poids de ts les parcours fermés de longueur uL qui commencent en uH.
	//pmAhach est la matrice égale à A pour i>h et j>h, et nulle sinon.
	//yLigne/yColonne est la h-ième ligne/colonne de la matrice A avec les h 1ères entrées nulles.
	//const int kbBooleher=kF;//vrai ssi les opérateurs booléens ET et OU remplacent les opérateurs produit et somme (resp.) 
	int uC,uD,uH,uL,uK,uN=pmA->nLigne;
	long yAccu[1+uN],yColonne[1+uN],yLigne[1+uN],zEcretage;
	//te("SkewClosurE0: uParcoursLgMax",uParcoursLgMax);
	iMatrice *pmAhach;
	//Appel0(sC2b("SkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
		Assert3("SkewClosurE01",pmA->nLigne==pmA->nColonne,pmA->nLigne==(*ppmAchapo)->nLigne,pmA->nColonne>=(*ppmAchapo)->nColonne);
		MatriceAllouer1(&pmAhach,uN);
			//MatriceVoir("MatriceZeroter ppmqAchapo initial",*ppmAchapo);
			//calculer Achapeau[h,k]=ah.(Ah**k-2).ah
				//te("1:uN",uN);
				for (zEcretage=0,uH=1;uH<=uN;uH++){//O(N4)
					if (0) Titrer(sEnt(uH));
					MatriceZeroter(pmA,uH,pmAhach);//all rows and columns not greater than uH zeroed
					if (0) MatriceVoir(sC2("pmAhach",sEnt(uH)),pmAhach);
					//yLigne:=ligne pmA[uH] 
						for (uC=1;uC<=uN;uC++)
							yLigne[uC]=(uC<=uH)? 0: pmA->Mat[uH][uC];//hth row of A with the first h entries zeroed
					if (0 && !bVekteurNul(yLigne,1,uN)) VekteurVoir(sC2("yLigne",sEnt(uH)),yLigne,1,uN);
					//yColonne:=colonne pmA[uH] 
						for (uL=1;uL<=uN;uL++)
							yColonne[uL]=(uL<=uH)? 0: pmA->Mat[uL][uH];//hth column of A with the first h entries zeroed
					if (0 && !bVekteurNul(yColonne,1,uN)) VekteurVoir(sC2("yColonne @@@@@@@@@@@@@@@",sEnt(uH)),yColonne,1,uN);
					VekteurCopier(yLigne,1,uN,yAccu);
					for (uK=2;uK<=uParcoursLgMax;uK++){//O(N3)
						if (0) VekteurVoir(sC2("yAccu pour uK=",sEntier(uK,2)),yAccu,1,uN);
						//ppmqAchapo->Mat[uH][uK]:=produit scalaire iProduitLigne[]*yColonne[]
							for ( (*ppmAchapo)->Mat[uH][uK]=0, uD=1;uD<=uN;uD++)
								(*ppmAchapo)->Mat[uH][uK]+=yAccu[uD]*yColonne[uD];
						//yLigne:=produit du vecteur ligne ah par la puissance pmAhach
							VekteurCopier(yAccu,1,uN,yLigne);
							VekteurRazer(yAccu,1,uN);
							for (uC=1;uC<=uN;uC++)//O(N2)
								for (uD=1;uD<=uN;uD++)
									yAccu[uC]+=yLigne[uD]*pmAhach->Mat[uD][uC];
						//zEcretage+=nVekteurEcreter(yAccu,1,uN,kiLongintMin,kxParcoursMaximal);
					}//for uK
					for (uD=1;uD<=uN;uD++)
						(*ppmAchapo)->Mat[uH][1]=pmA->Mat[uH][uH];
				}//uH
			Assert1("SkewClosurE0 zEcretage",zEcretage==0);
		free(pmAhach);
		//censurer les parcours de longueur supérieure à uParcoursLgMax
			//(*ppmAchapo)->nColonne=10;
		//t("[uH][uL]=somme de produits, 1 par parcours fermé de lgr uL d'extrémité uH tel qu'aucun sommet <=uH n'est traversé");
		//MatriceVoir("SkewClosurE0 ppmAchapo final",*ppmAchapo);
	//Appel1(sC2b("SkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
}//SkewClosurE0

void SkewClosurE1(iMatrice *pmA,iMatrice **ppmK){
	//rend dans ppmK[uH][uL] la somme des poids de ts les parcours fermés de longueur uL qui commencent en uH.
	//Ah est la matrice égale à A pour i>h et j>h, et nulle sinon.
	//ah est la h-ième ligne de la matrice A avec les h 1ères entrées nulles.
	#define kuSkewClosure2 2
	int uN=pmA->nLigne;
	int uH,uL,nR,nK,nQ;
	int nGamma=ceil(sqrt(uN));//plafond de racine(N)
	int nEta=ceil(uN/(1.0*nGamma));//plafond de N/gamma
	iMatrice *pmAh,*pmP;
	iMatrice *pV[kuSkewClosure2+1+nGamma];//tableau de vecteurs colonne
	iMatrice *pW[kuSkewClosure2+1+nGamma];//tableau de vecteurs ligne
	iMatrice *pmZ[1+uN];//tableau de matrices
	//allouer les espaces
		MatriceAllouer(&pmAh);
		MatriceAllouer(&pmP);
		for (uH=1;uH<=uN;uH++)
			MatriceAllouer(&pV[uH]);
		for (uH=1;uH<=uN;uH++)
			MatriceAllouer(&pW[uH]);
		for (uH=1;uH<=uN;uH++)
			MatriceAllouer(&pmZ[uH]);
	//calculer la SkewClosurE
		for (uH=uN-1;uH>0;uH--){
			//pV[ku2-1] soit initialisé
				for (uL=1;uL<=pmA->nLigne;uL++)
					pV[kuSkewClosure2-1]->Mat[uL][uH]=(uL=uH);
			//V[r]h=Ah*V[r-1]h
				for (nR=0;nR<=nGamma;nR++){;
					MatriceZeroter(pmA,uH,pmAh);
					MatriceFoisColonne(pmAh,pV[kuSkewClosure2+nR-1],uH,&pV[kuSkewClosure2+nR]);
				}
			//pW[ku2-1] soit initialisé
				for (uL=1;uL<=pmA->nLigne;uL++)
					pW[kuSkewClosure2-1]->Mat[uL][uH]=(uL=uH);
			//W[r]h=W[r-1]h*Ah-1;
				for (nR=0;nR<=nGamma;nR++){
					MatriceZeroter(pmA,uH-1,pmAh);
					MatriceFoisColonne(pmAh,pW[kuSkewClosure2+nR-1],uH,&pW[kuSkewClosure2+nR]);
				}
			//Zh=Zh+1 + ∑ V[k-1]h+1 * W[gamma-k-1]h+1 de 0 à gamma
				MatriceDupliquer(pmZ[uH+1],pmZ[uH]);
				for (nK=0;nK<=nGamma;nK++){
					MatriceCartesier(pV[kuSkewClosure2+nK-1],pW[kuSkewClosure2+nGamma-nK-1],uH+1,&pmP);//produit vecteur ligne par vecteur colonne
					MatriceAdditionner(pmZ[uH],pmP,&pmZ[uH]);
				}
			//Zh=Zh+1 + S
			for (nQ=1;nQ<=nEta;nQ++){
				//U[q]h=U[q-1]h.Zh;
			}
			for (nR=0;nR<=nGamma;nR++){
				for (nQ=0;nQ<=nEta;nQ++);
					//Achapeau[h,q.gamma+r+2]=U[q]h.V[r]h
			}
		}//uH
	//restituer les espaces
		free(pmAh);
		free(pmP);
		for (uH=1;uH<=uN;uH++)
			free(pV[uH]);
		for (uH=1;uH<=uN;uH++)
			free(pW[uH]);
		for (uH=1;uH<=uN;uH++)
			free(pmZ[uH]);
}//SkewClosurE1

void SkewClosurE2(iMatrice *pmA,int uParcoursLgMax,iMatrice **ppmAchapo){//O(N4)
	//rend dans ppmqAchapo[uH][uL] la somme des produits des poids de ts les parcours fermés de longueur uL qui commencent en uH.
	//pmAhach est la matrice égale à A pour i>h et j>h, et nulle sinon.
	//yLigne/yColonne est la h-ième ligne/colonne de la matrice A avec les h 1ères entrées nulles.
	//const int kbBooleher=kF;//vrai ssi les opérateurs booléens ET et OU remplacent les opérateurs produit et somme (resp.) 
	int uC,uD,uH,uL,uK,uN=pmA->nLigne;
	int muNeutre=1;
	int anK;
	long zEcretage;
	int noProduit,noAccu[1+uN],noColonne[1+uN],noAvant,noLigne[1+uN],noRacine,noZero;
	int bPoly=kF;
	//te("SkewClosurE0: uParcoursLgMax",uParcoursLgMax);
	iMatrice *pmAhach;
	Appel0(sC2b("SkewClosurE2",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
		Assert3("SkewClosurE21",pmA->nLigne==pmA->nColonne,pmA->nLigne==(*ppmAchapo)->nLigne,pmA->nColonne>=(*ppmAchapo)->nColonne);
		GrapheCreer(-pmA->nLigne,&pgGrapH);
		//MatriceVoir("pmA",pmA);
		//GrapheVoir(pgGrapH,"pgA AVANT");
		MatriceGrapher(pmA,pgGrapH);
		//GrapheVoir(pgGrapH,"pgA APRES");
		MatriceAllouer1(&pmAhach,uN);
			//MatriceVoir("MatriceZeroter ppmqAchapo initial",*ppmAchapo);
			//calculer Achapeau[h,k]=ah.(Ah**k-2).ah
				//te("1:uN",uN);
				noZero=noPolyAfF(bPoly,0);
				//te("noZero",noZero);
				for (zEcretage=0,uH=1;uH<=uN;uH++){//O(N4)
					if (0) Titrer(sEnt(uH));
					MatriceZeroter(pmA,uH,pmAhach);//all rows and columns not greater than uH zeroed
					if (0) MatriceVoir(sC2("pmAhach",sEnt(uH)),pmAhach);
					//noLigne:=ligne pmA[uH] 
						for (uC=1;uC<=uN;uC++){
							anK=(pmA->Mat[uH][uC]!=0)? 1+nGrapheArc(pgGrapH,uH,uC): noZero;
							noLigne[uC]=(uC<=uH || pmA->Mat[uH][uC]==0)? noZero: noPolyAfF(bPoly,anK);//hth row of A with the first h entries zeroed
							//teee("uH,uC,noLigne[uC]",uH,uC,noLigne[uC]);
						}
					if (0 && !bVecteurNul(noLigne,1,uN)) VecteurVoir(sC2("noLigne",sEnt(uH)),noLigne,1,uN);
					//noColonne:=colonne pmA[uH] 
						for (uL=1;uL<=uN;uL++){
							anK=(pmA->Mat[uL][uH]!=0)? 1+nGrapheArc(pgGrapH,uL,uH) :noZero;
							noColonne[uL]=(uL<=uH || pmA->Mat[uL][uH]==0)? noZero: noPolyAfF(bPoly,anK);//hth column of A with the first h entries zeroed
							//teee("uL,uH,noColonne[uL]",uL,uH,noColonne[uL]);
						}
					if (0 && !bVecteurNul(noColonne,1,uN)) VecteurVoir(sC2("noColonne @@@@@@@@",sEnt(uH)),noColonne,1,uN);
					VecteurCopier(noLigne,1,uN,noAccu);
					for (uK=2;uK<=uParcoursLgMax;uK++){//O(N3)
						if (0) VecteurVoir(sC2("noAccu pour uK=",sEntier(uK,2)),noAccu,1,uN);
						//ppmqAchapo->Mat[uH][uK]:=produit scalaire iProduitLigne[]*yColonne[]
							for ( (*ppmAchapo)->Mat[uH][uK]=noZero, uD=1;uD<=uN;uD++){
								if (noAccu[uD]!=noZero && noColonne[uD]!=noZero)
									noProduit=noPolyMuL(bPoly,noAccu[uD],noColonne[uD]);
								else noProduit=noZero;
								noAvant=(*ppmAchapo)->Mat[uH][uK];
								if (noAvant!=noZero || noProduit!=noZero)
									(*ppmAchapo)->Mat[uH][uK]=noPolyAdD(bPoly,noAvant,noProduit);
								else (*ppmAchapo)->Mat[uH][uK]=noZero;
							}
						//noLigne:=produit du vecteur ligne ah par la puissance pmAhach
							VecteurCopier(noAccu,1,uN,noLigne);
							VecteurValuer(noAccu,1,uN,noZero);
							for (uC=1;uC<=uN;uC++)//O(N2)
								for (uD=1;uD<=uN;uD++){
									anK=(pmAhach->Mat[uD][uC]!=0)? 1+nGrapheArc(pgGrapH,uD,uC): noZero;
									if (noLigne[uD]!=noZero && pmAhach->Mat[uD][uC]!=0)
										noProduit=noPolyMuL(bPoly,noLigne[uD],noPolyAfF(bPoly,anK));
									else noProduit=noZero;
									if (noAccu[uC]!=noZero || noProduit!=noZero)
										noAccu[uC]=noPolyAdD(bPoly,noAccu[uC],noProduit);
									else noAccu[uC]=noZero;
								}
					}//for uK
					for (uD=1;uD<=uN;uD++){
						anK=(pmA->Mat[uH][uH]!=0)? 1+nGrapheArc(pgGrapH,uH,uH): noZero;
						(*ppmAchapo)->Mat[uH][1]=(pmA->Mat[uH][uH]==0)? noZero: noPolyAfF(bPoly,anK);
					}
				}//uH
			Assert1("SkewClosurE2 zEcretage",zEcretage==0);
			
			MatriceVoir("(*ppmAchapo)->Mat",*ppmAchapo);
			//DagArborer("(*ppmAchapo)->Mat[1][1] NON simplifié",(*ppmAchapo)->Mat[1][1]);
			//DagArborer("(*ppmAchapo)->Mat[2][2]",(*ppmAchapo)->Mat[1][2]);
			if (0)//simplifier les arborescences
				for (uL=1;uL<=uN;uL++)
					for (uC=1;uC<=uN;uC++){
						noRacine=(*ppmAchapo)->Mat[uL][uC];
						if (noRacine!=0)
							DagSimplifier(-3,noRacine,muNeutre,!k1Doublon);
						else tee("Racine nulle",uL,uC);//se produit qd uParcoursLgMax diminue délibérément le nbre de colonnes
					}
			//DagSimplifier(-4,(*ppmAchapo)->Mat[4][2],muNeutre,!k1Doublon);
			//DagArborer("(*ppmAchapo)->Mat[4][2] simplifié",(*ppmAchapo)->Mat[4][2]);
			//DagArborer("(*ppmAchapo)->Mat[2][2] simplifié",(*ppmAchapo)->Mat[2][2]);
			//FormeDenonceR(*ppmAchapo,noZero);
			FormeGrapheR(*ppmAchapo,noZero);

		free(pmAhach);
		//censurer les parcours de longueur supérieure à uParcoursLgMax
			//(*ppmAchapo)->nColonne=10;
		//t("[uH][uL]=somme de produits, 1 par parcours fermé de lgr uL d'extrémité uH tel qu'aucun sommet <=uH n'est traversé");
		//MatriceVoir("SkewClosurE2 0 ppmAchapo final",*ppmAchapo);
		free(pgGrapH);
		pgGrapH=NULL;
	Appel1(sC2b("SkewClosurE2",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
}//SkewClosurE2

void SystemeComposeR(iMatrice *pmA,iMatrice *pmAB){
	//rend le système d'équations obtenu en multipliant pmA par une matrice de variables pmB fictive de même dimension que pmA,carrée.
	int uI,uJ,uK,uLigne,uVariable;
	Assert1("SystemeComposeR",pmA->nLigne==pmA->nColonne);
	for (uLigne=1,uI=1;uI<=pmA->nLigne;uI++)
		for (uJ=1;uJ<=pmA->nColonne;uJ++,uLigne++)
			for (uK=1;uK<=pmA->nColonne;uK++){
				uVariable=(pmA->nLigne)*(uK-1)+uJ;//attribue à l'élément (uK,uJ) de pmB un rang1.
				pmAB->Mat[uLigne][uVariable]=pmA->Mat[uI][uK];
			}
}//SystemeComposeR

void SystemeExpanseR(iMatrice *pmQuadFoisQuad,iMatrice *pmCoefficient){
	//expanse le système pmQuadFoisQuad en rplaçant chaq élémt quadxquad par 1 pavé à 4x4 éléments contenant son développement.
	int nC,nD,nL;
	quad qR;
	for (nL=0;nL<pmQuadFoisQuad->nLigne;nL++)
		for (nC=0;nC<pmQuadFoisQuad->nColonne;nC++)
			for (qR=qQuad(pmQuadFoisQuad->Mat[1+nL][1+nC]),nD=0;nD<2;nD++){//remplir le pavé de topleft 4*nL+1,4*nC+1.
				pmCoefficient->Mat[4*nL+nD+1][4*nC+nD+1]=yNb(qR.q11);
				pmCoefficient->Mat[4*nL+nD+1][4*nC+nD+3]=yNb(qR.q12);
				pmCoefficient->Mat[4*nL+nD+3][4*nC+nD+1]=yNb(qR.q21);
				pmCoefficient->Mat[4*nL+nD+3][4*nC+nD+3]=yNb(qR.q22);
			}//le produit de 2 quads, donc de deux matrices 2x2 donne bien 4 sommes de 2 termes, soit 8 coefficients sur 4 lignes.
}//SystemeExpanseR

void TermeVoiR(char *sQuoi,f fVoir,int uTerme){
	char *sForme=malloc(kuFormeLiM);
	int nC,uL;
	char cCar;
	int nLettrat=nLettraT(fVoir,uTerme,!k1DenominateuR);
	for (nC=0;nC<=kuFormeMaX;nC++)
		sForme[nC]='\0';
	for (nC=0,uL=1;uL<=nLettrat;uL++){
		cCar= fVoir.num[uTerme][uL];
		sForme[nC++]=cCar;
	}
	printf("%s:%s\n",sQuoi,sForme);
}//TermeVoiR

