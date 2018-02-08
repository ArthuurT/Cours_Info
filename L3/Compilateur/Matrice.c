#include "Outil.h"
#include "Graphe.h"
#include "Couplage.h"
#include "Matrice.h"
#include "Quad.h"
#define k1BitsDistincts 2
//#define knLigneLiM 18
#define kbExacT kV
#define k1LignE kV
#define knLigneMaX (knLigneLiM-1)
#define knNomLiM 160
#define knPolyLiM (knLigneMaX*knLigneMaX)
#define knPolyMaX (knPolyLiM-1)
#define knTermeLiM kE3
#define knTermeMaX (knTermeLiM-1)
//#define knColonneLiM knLigneMaX*knLigneMaX+1
#define knColonneLiM knLigneLiM
#define knColonneMaX (knColonneLiM-1)
#define FloaT "%10.5f"
#define knPremierMaX kE3
//enum eCouleuR {coAlphA,coJaune,coRouge,coBleu,coVert,coOrange,coNoir,coOmegA};
//char *sCouleuR[coOmegA-coAlphA+1]={"coAlphA ","coJaune","coRouge ","coBleu  ","coVert  ","coOrange","coNoir","coOmegA "};
enum eCoulheurTypE CouleurType;
char *sCoulheurNoM=CouleurNom;
//oMatrice soit la structure qui décrit la matrice d'objets;le type de l'objet est spécifié par un paramètre de type eTypE: 
	enum eMatriceType {matAlpha,matEntier,matRationnel,matReel,matComplexe,matRect,matOmega};
	typedef union{long ent;double reel;q rat;ri cplx;quad mm;}objet;
	typedef struct{
		int nColonne;
		int nLigne;
		int nSecante;
		enum eMatriceType typ;
		objet Mat[knLigneLiM][knLigneLiM];//pas knColonneMaX,dédié nDuoCompteR()
	}oMatrice;
typedef struct{
	int nColonne;
	int nLigne;
	double Mat[knLigneLiM][knLigneLiM];//pas knColonneMaX,dédié nDuoCompteR()
}dMatricE;
typedef struct{
	int nColonne;
	int nLigne;
	q Mat[knLigneLiM][knLigneLiM];//pas knColonneMaX,dédié nDuoCompteR()
}qMatricE;
typedef struct{
	int nColonne;
	int nLigne;
	long Mat[knLigneLiM][knLigneLiM];//pas knColonneMaX,dédié nDuoCompteR()
}yMatricE;
typedef struct{
	int nColonne;
	int nLigne;
	int nPoly;
	int nTerme;
	int Map[knLigneLiM][knLigneLiM];
	int Pol[knPolyLiM][knTermeLiM];
	int Poi[knPolyLiM][knTermeLiM];
	int Exp[knPolyLiM][knTermeLiM];
}iMatrycE;
typedef struct{
	int Vect[knTermeLiM];
} iVecteuR;

enum eDuoUtiliseR {duDenombreR,duMinimiseR,duPireCaS};
int bLitteraliseR=kF;
enum eTriUtiliseR {tuSimplE};
int bMatriceAmorceR;
int bMatriceOuvertE;
int abPremieR[1+knPremierMaX];
int bVoiR;

void ApparieR(graf *pgG,int coCouleur,int sAlter,int sEgo,int *pnBaton,int *pnPaire);
void AreteDelimiteR(iMatrice *pmAreteIndex,int nArete,int *pnSource,int *pnCible);
void ComplexitehAfficheR(long zBarre);
void ComplexitehAfficheR2(long zCase);
void ComplexitehCalculeR(float fTempsMoyen);
void ComplexitehPreciseR(int nDimension,long zBarre);
void DecomposE(int nDecomposota);
void DecomposeR(int nDecomposota);
objet oDeterminantCalculeR(oMatrice *pmoA);
long yDeterminantCalculeR(iMatrice *pmA,int bExact);
long yDeterminantKalculeR(iMatrice *pmA);//O(S4) exact car sans division
int bDeterminantNonNuL(iMatrice *pmA,int *pnAppelPolynomial);
int bDeterminantNOnNuL(oMatrice *pmoA,int *pnAppelPolynomial);
void DeterminantFormuleR(iMatrice *pmA,iMatrice *pmAreteIndex,int bAlterner,graf *pgG);
int bDetermynantNonNul(iMatrycE *pmA,int *pnAppelPolynomial);
int bDiagonaleNullE(iMatrice *pmA);
void DiviseurS(int nDivisota,int uPile[]);
int nDuoCompteR(int bVoir,iMatrice *pmA,int *pnDuo,int *pnCopie,int *pnRecopie);
void DuoDecompteR(long zDecompteMaximal);
void DuoDenombreR();
int nDuoEstimeR(iMatrice *pmA,int uFois);
void DuoMaximiseR();
void DuoMinimiseR();
void DuoUtiliseR(int nCas);
int mExposantCalculeR(int uLigneDuCofacteurCourant,int bLignePrise[]);
void GrapheArcBouteR(graf *pgG,int nMorceau);
void GrapheConcocteR(iMatrice* pmA,int nSommetDuGrapheOriginal);
void GrapheEtireR(graf *pgG,int nTest);
void GrapheMatriceR(graf *pgG,int bSimple,int nBaton,int nCarreh,iMatrice **ppmMatriceDuGraphe);
int bGrapheQuadripoleR(graf *pgG,int bBoucler,int nTest,iMatrice **ppmA);
void ListeVoiR(int uListe[]);
void MatriceAffecteR(iMatrice* pmA,int bVoir);
void MatriceAlloueR0(iMatrice **ppmA,int nLigne,int nColonne,int nSecante);
void MatriceAlloueR2(yMatricE **ppmA);
void MatriceAllouher(oMatrice **ppmoA,enum eMatriceType maType);
void MatriceAllouheR(dMatricE **ppmA);
int bMatriceAntiSymetriquE(iMatrice *pmA);
void MatriceApparieR(graf *pgG,int bSimple,iMatrice *pmA);
void MatriceCarrehNuL(int nValeur);
void MatriceCarreR(iMatrice **ppmA);
void MatriceConfigureR(long zConfigurationVoulue,iMatrice **ppmC);
void MatriceConstitueR(long zConfigurationVoulue,iMatrice **ppmC);
void MatriceCulminer(int uCulminant,iMatrice **ppmC);
int nMatriceCulmineR(iMatrice *pmC);
long zMatriceCulminerAuMieuX(int uCulminant,iMatrice *pmC);
void MatriceDedoubleR(iMatrice *pmA);
void MatriceDupliqueR2(iMatrice *pmA,iMatrice **ppmB);
void MatriceEchafaudeR(int nSommet,int kbSimple);
int nMatriceEffectifNonNuL(iMatrice *pmA);
int nMatRIceEffectifNonNuL(riMatrice *pmK);
void MatriceIdentiteR(riMatrice **ppmC);
void MatriceIntervaller(iMatrice **ppmC);
void MatriceIntervaller2(int nLigneEnTout,int nColonneEnTout, iMatrice **ppmC);
int nMatriceModulE(iMatrice *pmA);
void MatriceModuleR(int uModulo,iMatrice **ppmC);
long zMatriceMultiplieR(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
void MatriceNettoyeR(iMatrice *pmA);
int bMatriceNullE(iMatrice *pmA);
void MatriceQuintesseR(int nSommet);
void MatriceRazOueR(oMatrice **ppmoA);
void MatRIceRazeR(riMatrice **ppmA);
void MatriceRazer2(yMatricE **ppmA);
void MatriceRazheR(dMatricE **ppmA);
void MatriceRedresseR(iMatrice *pmA);
int bMatriceRehausseR(int uDiagonale,int bVoir,iMatrice **ppmT);
int bMatriceRemonteR(int uDiagonale,int bVoir,iMatrice **ppmT);
int nMatriceRempliE(iMatrice *pmA);
void MatriceRempliR(iMatrice **ppmC);
float fMatriceRempliR(int bDoublonPossible,int uEffectif,iMatrice **ppmA);
int bMatriceSainE(char *sMessage,iMatrice *pmA);
int bMatriceSingulariseR(iMatrice **ppmT,int *pnNom,int *pnEtape);
int bMatriceSingulierE(yMatricE **ppmT,int *pnEtape);
void MatriceSomme3InitialiseR(int nLigneEnTout,int nColonneEnTout,int bOperandeGauche,iMatrice **ppmC);
void MatriceSommer1(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
void MatriceSommer2(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
void MatriceSommer3(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC);
int bMatriceSymetriquE(iMatrice *pmC);
void MatriceTourTourer(iMatrice *pmA);
int bMatriceTrianguleR(yMatricE **ppmT,int *pnEtape);
double dMatriceTrianguleR(dMatricE **ppmT,int bVoir,int *pnEtape);
objet oMatriceTrianguleR(oMatrice **ppmoT,int *pnEtape);
void MatriceTrieR(iMatrice *pmA);
void MatriceTrierTouT(iMatrice *pmA);
void MatriceTU(iMatrice *pmA);
int bMatriceTU(iMatrice *pmA);
int bMatriceVidE(iMatrice *pmA);
void MatriceVOir(char *sMessage,oMatrice *pmoA);
void MatriceVoirReeL(char *sMessage,dMatricE *pmA);//matrice de réels
void MatriceVoyR(char *sMessage,yMatricE *pmA);//matrice de longint
void MatriceVoirSouS(int bSous,char *sMessage,iMatrice *pmA);
void MatriqeAlloueR(qMatricE **ppmA);
void MatriqeRazeR(qMatricE **ppmA);
void MatriqeVoiR(char *sMessage,qMatricE *pmA);
void MatryceAffecteR(int nLigne,iMatrice **ppmA);
void MatryceAlloueR(iMatrycE **ppmA);
void MatryceRazeR(iMatrycE **ppmA);
int bMatryceTrianguleR(iMatrycE **ppmT,int *pnEtape);
void MatryceVoiR(char *sMessage,iMatrycE *pmA);
void ModuloParFibonnaccI();
objet oObjetAdD(objet oA,objet oB,enum eMatriceType tip);
objet oObjetMuL(objet oA,objet oB,enum eMatriceType tip);
int bObjetNuL(objet Ob,enum eMatriceType tip);
objet oObjetOpP(objet oA,enum eMatriceType tip);
void ObjetRazeR(objet *poCible,enum eMatriceType tip);
objet oObjetSuB(objet oA,objet oB,enum eMatriceType tip);
void ObjetUnariseR(objet *poCible,enum eMatriceType tip);
void ObjetVoiR(char *sQuoi,objet oQuoi,enum eMatriceType tip);
void PpcmOptimalExhibeR();
int bPermutatioN(int nPermutation[]);
int bPermutationSolidairE(iMatrice *pmA);
void PolynomeAjouteR(int iCoefficient,int nExposant,int ivCible,iMatrycE **ppmT);
void PolynomeAnnuleR(int ivCible,iMatrycE **ppmT);
void PolynomeFoisseR(int ivOperande,int iFois,int ivFois,iMatrycE **ppmT);
void PolynomeMultiplieR(int ivGauche,int ivDroit,int ivProduit,iMatrycE **ppmT);
void PolynomeSommeR(int ivGauche,int ivDroit,int ivSomme,iMatrycE **ppmT);
int nPolynomeTermE(int ivTerme,iMatrycE **ppmT);
void PolynomeVoiR(char *sMessage,int ivQuoi,iMatrycE **ppmT);
void PremierTabuleR();
void PremierVoiR();
objet oSignatureCalculeR(oMatrice *pmoA,int bAlterner,int *pnAppelExponentiel);
q qSignatureCalculeR(qMatricE *pmA,int bAlterner,int *pnAppelExponentiel);
ri riSignatureCalculeR(riMatrice *pmA,int bAlterner,int *pnAppelExponentiel);
long ySignatureCalculeR(iMatrice *pmA,int bAlterner,int *pnAppelExponentiel);
void SignatureCertifieR(graf *pgG,int bSiguliere);
long ySygnatureCalculeR(yMatricE *pmA,int bAlterner,int *pnAppelExponentiel);
long ySignatureKalculeR(iMatrice *pmA,int bAlterner,int *pnAppelExponentiel);
int bSygnaturePairE(int nPermutation[]);
void SygnaturePredirE();
void TriEffectueR();
void TriUtiliseR(int nCas);

void ColoreR(graf *pgG,int sSommet,int coCouleur){
	pgG->sPer[sSommet]=coCouleur;
}//ColoreR

void ApparieR(graf *pgG,int coCouleur,int sAlter,int sEgo,int *pnBaton,int *pnPaire){
	//apparie sAlter et sEgo,au signe près si coCouleur==coJaune,et leur attribue la coCouleur.
	int bBaton=(coCouleur==coJaune);
	//NB sAlter et sEgo ne pas,en général,liés par un arc
	pgG->aArcTo[sAlter]=iSignePres(bBaton,sEgo);
	pgG->aArcTo[sEgo]=iSignePres(bBaton,sAlter);
	(*pnPaire)++;
	(*pnBaton)+=bBaton;
	//printf("sAlter,sEgo,couleur (%d,%d,%s)\n",sAlter,sEgo,sCouleuR[coCouleur]);
	pgG->sPer[sAlter]=pgG->sPer[sEgo]=coCouleur;
}//ApparieR

void AreteDelimiteR(iMatrice *pmAreteIndex,int nArete,int *pnSource,int *pnCible){
	int uL,uC;
	int bEureka=kV;
	for (bEureka=kF,uL=1;uL<=pmAreteIndex->nLigne &&!bEureka;uL++)
		for (uC=1;uC<=pmAreteIndex->nColonne &&!bEureka;uC++)
			if (nArete==pmAreteIndex->Mat[uL][uC]){
				*pnSource=uL;
				*pnCible=uC;
				bEureka=kV;
			}
	Assert1("AreteDelimiteR",bEureka);
}//AreteDelimiteR

void ComplexitehAfficheR(long zBarre){
	float fExposant;
	if (0)
		te("zBarre",zBarre);
	fExposant=rLog(zBarre*knLigneMaX)/rLog(knLigneMaX);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité:N**%3.4f au pire.\n",fExposant);
}//ComplexitehAfficheR

void ComplexitehAfficheR2(long zCase){
	float fExposant;
	if (0)
		te("zBarre",zCase);
	fExposant=rLog(zCase)/rLog(knLigneMaX);// car N**X = zCase => X=log(zCase)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité:N**%3.4f au pire.\n",fExposant);
}//ComplexitehAfficheR2

void ComplexitehCalculeR(float fTempsMoyen){
	float fExposant;
	fExposant=rLog(fTempsMoyen*knLigneMaX)/rLog(knLigneMaX);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité moyenne:N**%3.4f.\n",fExposant);
}//ComplexitehCalculeR

void ComplexitehPreciseR(int nDimension,long zBarre){
	float fExposant;
	if (0)
		te("zBarre",zBarre);
	fExposant=rLog(zBarre*nDimension)/rLog(nDimension);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité:N**%3.4f au pire.\n",fExposant);
}//ComplexitehPreciseR

void DecomposE(int nDecomposota){
	int uN,nReste;
	//printf("nDecomposota=%d\n",nDecomposota);
	for (nReste=1,uN=2;(uN<=nDecomposota) &&(nReste!=0);uN++){
		nReste=nDecomposota%uN;
		if (nReste==0){
			printf("%d",uN);
			if (uN<nDecomposota)
				printf(".",uN);
			DecomposE(nDecomposota/uN);
		}
	}
}//DecomposE

void DecomposeR(int nDecomposota){
	Assert1("DecomposeR",bCroit(1,nDecomposota,1e3));
	printf("%d=",nDecomposota);
		if (nDecomposota>1)
			DecomposE(nDecomposota);
		else printf("%d",nDecomposota);
	printf(".\n");
}//DecomposeR

objet oDeterminantCalculeR(oMatrice *pmoA){
	int nAppelExponentiel;
	objet oDeterminer;
	//tt("Entier max",sPar3(kuIntegerMax));
	if (0)
		oDeterminer=oSignatureCalculeR(pmoA,k1Alterner,&nAppelExponentiel);
	else oDeterminer.mm=qQuad(bDeterminantNOnNuL(pmoA,&nAppelExponentiel));
	Assert1("oDeterminantCalculeR",nAppelExponentiel>0);
	ObjetVoiR("oDeterminantCalculeR",oDeterminer,pmoA->typ);
	//tri("Déterminant de oSignatureCalculeR",riDeterminer);
	return(oDeterminer);
}//oDeterminantCalculeR

ri riDeterminantCalculeR(riMatrice *pmA){
	ri riDeterminer;
	int nAppelExponentiel;
	//tt("Entier max",sPar3(kuIntegerMax));
	riDeterminer=riSignatureCalculeR(pmA,k1Alterner,&nAppelExponentiel);
	Assert1("riDeterminantCalculeR",nAppelExponentiel>0);
	tri("Déterminant de riSignatureCalculeR",riDeterminer);
	return(riDeterminer);
}//riDeterminantCalculeR

long yDeterminantCalculeR(iMatrice *pmA,int bExact){
	long yDeterminer,bNonNul;
	int nAppelExponentiel,nAppelPolynomial;
	//t(sC2("Entier max:",sPar3(kuIntegerMax)));
	yDeterminer=ySignatureCalculeR(pmA,k1Alterner,&nAppelExponentiel);
	Assert1("yDeterminantCalculeR0",nAppelExponentiel>0);
	if (!bExact){
		//tb("kbVite",kbVite);
		bNonNul=bDeterminantNonNuL(pmA,&nAppelPolynomial);
		printf("nAppelExponentiel/nAppelPolynomial = %s/%s =%5.2f.\n",sPar3(nAppelExponentiel),sPar3(nAppelPolynomial),(nAppelExponentiel*1.0)/nAppelPolynomial);
		if ((yDeterminer!=0)!=bNonNul)
			printf("Déterminant exact vs bNonNul %ld vs %ld.\n",yDeterminer,bNonNul);
		Assert1("yDeterminantCalculeR1",(yDeterminer!=0)==bNonNul);
	}
	te("Déterminant de yDeterminantCalculeR",yDeterminer);
	return(yDeterminer);
}//yDeterminantCalculeR

long yDeterminantKalculeR(iMatrice *pmA){//O(S4) exact car sans division
	//calcule le déterminant par la méthode de Mahajan et Vinay
	const int kbCensurer=kF;
	int bVoir=kV;
	long yAvant,yApres,yDeterminant,yProduit,yPoleNegatif,yPolePositif;
	int bCensurer2,bCensurer3,nEtage,sH,sX,sY,sZ,bCposantPariteh,uSommat;
	long V[1+1][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	//Appel0("yDeterminantKalculeR");
		uSommat=pmA->nLigne;
		MatriceVoir(sC2b("yDeterminantKalculeR sur",sPluriel(uSommat,"sommet")),pmA);
		Assert2("yDeterminantKalculeR2",pmA->nLigne==pmA->nColonne,bCroit(1,pmA->nLigne,6));
		//razer toute la structure; O(S3)
			for (bCposantPariteh=0;bCposantPariteh<=1;bCposantPariteh++)
				for (sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;nEtage++)
							V[bCposantPariteh][sH][sX][nEtage]=0;
		yPolePositif=yPoleNegatif=0;
		bVoir=kF;
		//Initialiser l'étage 0 à 1 pour bCposantPariteh=uSommat%2
			for (sH=1;sH<=uSommat;sH++){
				V[bCposantPariteh=uSommat%2][sH][sH][nEtage=0]=1;
				if (bVoir) printf("V[%d][%d][%d][%d]+=1.\n",bCposantPariteh,sH,sH,nEtage);
			}
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				bVoir=kV;
				if (bVoir) te("nEtage",nEtage);
				//pour (sH,sY) appartenant à {1,n} tel que sH≤sY et bCposantPariteh appartenant à {0,1} 
					for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
						for (sY=sH;sY<=uSommat;sY++)//pour tout sommet sY de rang supérieur ou égal à sH 
							for (bCposantPariteh=0;bCposantPariteh<=1;bCposantPariteh++)
								for (sZ =sH+1;sZ<=uSommat;sZ++){
									yAvant=V[0+bCposantPariteh][sH][sZ][nEtage+1];
									yApres=yAvant+V[bCposantPariteh][sH][sY][nEtage]*pmA->Mat[sY][sZ];
									bCensurer2=kbCensurer && (abs(pmA->Mat[sY][sZ])==13 || abs(pmA->Mat[sY][sZ])==17);
									bCensurer3=kbCensurer && (abs(pmA->Mat[sY][sZ])==93 || abs(pmA->Mat[sY][sZ])==97);
									bVoir=(bCensurer2 || bCensurer3);// {yApres=yAvant;t("***********Censure haute");}
									V[0+bCposantPariteh][sH][sZ][nEtage+1]=yApres;
									bVoir=kV;
if (bVoir && yAvant!=yApres){
printf("V[%d][%d][%d][%d]+=V[%d][%d][%d][%d]*pmA->Mat[%d][%d]:",0+bCposantPariteh,sH,sZ,nEtage+1,bCposantPariteh,sH,sY,nEtage,sY,sZ);
printf(" %ld=%ld+%ld*%ld.\n",yApres,yAvant,V[bCposantPariteh][sH][sY][nEtage],pmA->Mat[sY][sZ]);
}
									
									yAvant=V[1-bCposantPariteh][sZ][sZ][nEtage+1];
									yApres=yAvant+V[bCposantPariteh][sH][sY][nEtage]*pmA->Mat[sY][sH];
									bCensurer2=kbCensurer && (abs(pmA->Mat[sY][sH])==13 || abs(pmA->Mat[sY][sH])==17);
									bCensurer3=kbCensurer && (abs(pmA->Mat[sY][sH])==93 || abs(pmA->Mat[sY][sH])==97);
									bVoir=(bCensurer2 || bCensurer3);// {yApres=yAvant;t("************Censure basse");}
									V[1-bCposantPariteh][sZ][sZ][nEtage+1]=yApres;
									bVoir=kV;
if (bVoir && yAvant!=yApres){
printf("V[%d][%d][%d][%d]+=V[%d][%d][%d][%d]*pmA->Mat[%d][%d]:                ",1-bCposantPariteh,sZ,sZ,nEtage+1,bCposantPariteh,sH,sY,nEtage,sY,sH);
printf(" %ld=%ld+%ld*%ld.\n",yApres,yAvant,V[bCposantPariteh][sH][sY][nEtage],pmA->Mat[sY][sH]);
}
								}
			}
		if (0){//StructureAfficheR("AVANT process",uSommat);
			Titrer("APRES process");
			for (bCposantPariteh=0;bCposantPariteh<=1;bCposantPariteh++){
				for (nEtage=0;nEtage<=uSommat;nEtage++)
					for (printf("nEtage %1d:",nEtage),sH=1;sH<=uSommat || (printf(".\n"),kF);sH++)
						for (printf(" ("),sX=sH;sX<=uSommat || (printf(")"),kF);sX++)
							printf("%8ld",V[bCposantPariteh][sH][sX][nEtage]);
				if (bCposantPariteh==0) Ligne();
			}
		}
		bVoir=kF;
		//traiter le dernier étage; O(S2)
			//pour (sH,sY) appartenant à {1,n} tel que sH≤sY et bCposantPariteh appartenant à {0,1} 
				for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sY=sH;sY<=uSommat;sY++){//pour tout sommet sY de rang supérieur ou égal à sH
						yProduit=V[1][sH][sY][uSommat-1]*pmA->Mat[sY][sH];
						if (bVoir && yProduit!=0)
							printf("V[1][%d][%d][%d]*pmA->Mat[%d][%d]:%ld * %ld = %ld.\n",sH,sY,uSommat-1,sY,sH,V[1][sH][sY][uSommat-1],pmA->Mat[sY][sH],yProduit);
						yPolePositif+=V[1][sH][sY][uSommat-1]*pmA->Mat[sY][sH];
						yProduit=V[0][sH][sY][uSommat-1]*pmA->Mat[sY][sH];
						if (bVoir && yProduit!=0)
							printf("V[0][%d][%d][%d]*pmA->Mat[%d][%d]:                      %ld * %ld = %ld.\n",sH,sY,uSommat-1,sY,sH,V[0][sH][sY][uSommat-1],pmA->Mat[sY][sH],yProduit);
						yPoleNegatif+=V[0][sH][sY][uSommat-1]*pmA->Mat[sY][sH];
					}
		yDeterminant=(yPolePositif-yPoleNegatif);
		bVoir=kV;
		if (bVoir)
			printf("yPolePositif=%20s.\nyPoleNegatif=%20s.\nyDeterminant=%20s.\n",sPar3(yPolePositif),sPar3(yPoleNegatif),sPar3(yDeterminant));
	//Appel1("yDeterminantKalculeR");
	return(yDeterminant);
}//yDeterminantKalculeR

void DeterminantFormuleR(iMatrice *pmA,iMatrice *pmAreteIndex,int bAlterner,graf *pgG){
	//liste les couvertures maximales des sommets de pgG par les arêtes de pgG en les énumérant puis en les regroupant par occurrences
	#define knFormuleMax 299
	#define kbCouvertureAfficher kF
	int bCouplageParfait=kF;
	int uC,uL,nCarreh,mSigne,bNul,nCouverture,ipF,nX,uRg,uMin,bLa,nPlace,nSource,nCible,mExposant,nSource0,nCible0;
	int ipFormule;
	int nFormule[knFormuleMax][knColonneLiM];
	int nColonne[knColonneLiM];
	int bLignePrise[knLigneLiM];
	long zAccu,zFormule,zFormuleEnTout;
	//Appel0("DeterminantFormuleR");
	Assert1("DeterminantFormuleR1",bCroitStrict(0,pmA->nLigne,knLigneLiM));
	for (uL=1;uL<=knFormuleMax;uL++)
		for (uC=0;uC<=pmA->nColonne;uC++)//le nombre d'occurrences de la formule est stocké à l'indice 0
			nFormule[uL][uC]=0;
	//te("pmA->nLigne",pmA->nLigne);
	//te("nArete",pgG->nArcEnTout);
	//MatriceVoir("Matrice sommet-sommet des numéros d'arêtes",pmAreteIndex);
	zFormuleEnTout=zPuissance(pmA->nLigne,pmA->nLigne);
	if (kbCouvertureAfficher)
		printf("Dans les %d**%d=%ld configurations étudiées,figurent les couvertures de sommets suivantes:\n",pmA->nLigne,pmA->nLigne,zFormuleEnTout);
	for (nCouverture=0,ipFormule=0,zFormule=1;zFormule<=zFormuleEnTout;zFormule++){
		//razer bLignePrise[]
			for (uL=1;uL<=pmA->nLigne;uL++)
				bLignePrise[uL]=kF;
			bLignePrise[0]=pmA->nLigne;
		zAccu=zFormule;
		for (bNul=0,mSigne=1,uC=1;uC<=pmA->nColonne && !bNul;uC++){
			uL=1+zAccu%pmA->nLigne;
			if (bLignePrise[uL]==kF){
				if (pmA->Mat[uL][uC]!=0){//ce terme non nul est situé sur une nouvelle ligne et une nouvelle colonne
					nColonne[uC]=uL;//permettra de retrouver le terme pmA->Mat[uL][uC] au moment d'afficher le polynome en cours de calcul
					mExposant=mExposantCalculeR(uL,bLignePrise);
					if (kF) teee("uC,uL et mExposant",uC,uL,mExposant);
					if (bAlterner)
						mSigne=mSigne*(mExposant*pmA->Mat[uL][uC]);
				} else bNul=kV;
				bLignePrise[uL]=kV;//ie la ligne uL a été consommée car un élément et un seul est pris sur chaque ligne
			}else bNul=kV;
			zAccu=zAccu/pmA->nLigne;
		}
		if (!bNul){
			//te("mSigne",mSigne);
			if (kF){//afficher le vecteur courant non trié sous forme polynomiale
				for (printf("   "),uC=1;uC<=pmA->nColonne || bPrint(".");uC++)
					printf(" X%d%d",nColonne[uC],uC);
			}
			//transformer nColonne[] en tableau de numéros d'arêtes
				for (uC=1;uC<=pmA->nColonne;uC++)
					if (nColonne[uC]!=0){
						uL=nColonne[uC];
						nColonne[uC]=pmAreteIndex->Mat[uL][uC];
					}
				//VecteurVoir("arêtes non triées",&nColonne[0],1,pmA->nColonne);
			//croissanter nColonne[]
				for (uL=1;uL<=pmA->nColonne;uL++){
					uRg=uL;
					uMin=nColonne[uL];
					for (uC=uL+1;uC<=pmA->nColonne;uC++)
						if (uMin>nColonne[uC]){
							uMin=nColonne[uC];
							uRg=uC;
						}
					if (uRg>uL){//échanger nColonne[uL] et nColonne[uRg]
						nX=nColonne[uL];
						nColonne[uL]=nColonne[uRg];
						nColonne[uRg]=nX;
					}
				}
				//VecteurVoir("arêtes triées",&nColonne[0],1,pmA->nColonne);
			//afficher le vecteur courant sous forme polynomiale
				nCouverture++;
				if (kbCouvertureAfficher){
					for (printf("   "),uC=1;uC<=pmA->nColonne || bPrint(sC2p(" (couverture n°",sEnt(nCouverture)));uC++){
						AreteDelimiteR(pmAreteIndex,nColonne[uC],&nSource,&nCible);
						printf(" X%d%d",nSource,nCible);
					}
					
				}
				/*for (uC=1;uC<=pmA->nColonne || bPrint(".");uC++)
					if (nColonne[uC]!=0)
						printf(" X%d%d",uC,nColonne[uC]);
				*/
			//ajouter algébriquement le vecteur dans nFormule[][]
				for (nPlace=0,ipF=1;ipF<=ipFormule;ipF++){
					for (bLa=kV,uC=1;uC<=pmA->nColonne;uC++)
						if (nFormule[ipF][uC]!=nColonne[uC])
							bLa=kF;
					if (bLa)
						nPlace=ipF;//ie formule rencontrée en nFormule[nPlace][] 
				}
				Assert1("DeterminantFormuleR2",ipFormule<knFormuleMax);
				if (nPlace==0)
					for (ipFormule++,nPlace=ipFormule,uC=1;uC<=pmA->nColonne;uC++)
						nFormule[ipFormule][uC]=nColonne[uC];
				nFormule[nPlace][0]+=mSigne;
		}
	}
	if (nCouverture>1)
		printf("Couvertures distinctes parmi les %d trouvées, et occurrences%s:\n",nCouverture,sChoix0(bAlterner," avec le signe du polynome"));
	for (nCouverture=0,bCouplageParfait=kF,ipF=1;ipF<=ipFormule;ipF++){
		if (nFormule[ipF][0]){
			nCouverture++;
			for (printf("   "),nSource0=0,nCible0=0,nCarreh=0,uC=1;uC<=pmA->nColonne;uC++){
				AreteDelimiteR(pmAreteIndex,nFormule[ipF][uC],&nSource,&nCible);
				if (nSource0==nSource && nCible0==nCible){
					printf(" **2",nSource,nCible);
					nCarreh++;
				}else printf(" X%d%d",nSource,nCible);
				nSource0=nSource;nCible0=nCible;
			}
			printf(" (couverture n°%d obtenue %d fois)",nCouverture,nFormule[ipF][0]);
			if (2*nCarreh==pmA->nLigne){
				bCouplageParfait=kV;
				printf(" ——complète:%s",sPluriel(nCarreh,"carré"));
			}
			/*for (uC=1;uC<=pmA->nColonne;uC++)
				printf("%2d",nFormule[ipF][uC]);
			printf(" alias");*/
			printf(".\n");
		}
	}
	//printf("%s.\n",sC3b("Le couplage",sEst(bCouplageParfait),"parfait"));
	//printf("Le couplage %s parfait.\n",sEst(bCouplageParfait));
	//Appel1("DeterminantFormuleR");
}//DeterminantFormuleR

int bDeterminantNonNuL(iMatrice *pmA,int *pnAppelPolynomial){
	int uC,uL,bNonNul;
	yMatricE *pmB;
	MatriceAlloueR2(&pmB);
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC++)
				pmB->Mat[uL][uC]=pmA->Mat[uL][uC];
		pmB->nLigne=pmA->nLigne;
		pmB->nColonne=pmA->nColonne;
		bNonNul=bMatriceTrianguleR(&pmB,pnAppelPolynomial);
		Assert1("bDeterminantNonNuL",(pmB->nLigne<=2) || (*pnAppelPolynomial<zPuissance(pmB->nLigne,3)));
		//te("pnEtape",*pnEtape);
	free(pmB);
	if (bVoiR)
		tb("bDeterminantNonNuL",bNonNul);
	return(bNonNul);
}//bDeterminantNonNuL

int bDeterminantNOnNuL(oMatrice *pmoA,int *pnAppelPolynomial){
	int uC,uL,bNonNul;
	oMatrice *pmoB;
	objet oNonNul;
	Appel0("bDeterminantNOnNuL");
	MatriceAllouher(&pmoB,pmoA->typ);
		pmoB->nLigne=pmoA->nLigne;
		pmoB->nColonne=pmoA->nColonne;
		for (uL=1;uL<=pmoB->nLigne;uL++)
			for (uC=1;uC<=pmoB->nColonne;uC++)
				pmoB->Mat[uL][uC]=pmoA->Mat[uL][uC];
		oNonNul=oMatriceTrianguleR(&pmoB,pnAppelPolynomial);
		bNonNul=!bNbNul(oNonNul.mm.q11);
		Assert1("bDeterminantNOnNuL",(pmoB->nLigne<=2) || (*pnAppelPolynomial<zPuissance(pmoB->nLigne,3)));
		//te("pnEtape",*pnEtape);
	free(pmoB);
	if (bVoiR)
		tb("bDeterminantNOnNuL",bNonNul);
	Appel1("bDeterminantNOnNuL");
	return(bNonNul);
}//bDeterminantNOnNuL

int bDetermynantNonNul(iMatrycE *pmA,int *pnAppelPolynomial){
	int uC,uL,bNonNul;
	iMatrycE *pmB;
	Appel0("bDetermynantNonNul");
	MatryceAlloueR(&pmB);
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC++)
				pmB->Map[uL][uC]=pmA->Map[uL][uC];
		pmB->nLigne=pmA->nLigne;
		pmB->nColonne=pmA->nColonne;
		pmB->nTerme=pmA->nTerme;
		MatryceVoiR("pmB AVANT",pmB);
		bNonNul=bMatryceTrianguleR(&pmB,pnAppelPolynomial);
		Assert1("bDetermynantNonNul",(pmB->nLigne<=2) || (*pnAppelPolynomial<zPuissance(pmB->nLigne,3)));
		//te("pnEtape",*pnEtape);
	free(pmB);
	tb("bDetermynantNonNul",bNonNul);
	Appel1("bDetermynantNonNul");
	return(bNonNul);
}//bDetermynantNonNul

int bDiagonaleNullE(iMatrice *pmA){
	//diagonale principale nulle
	int uL;
	int bNulle;
	Appel0("bDiagonaleNullE");
		MatriceVoir("bDiagonaleNullE",pmA);
		for (bNulle=kV,uL=1;uL<=pmA->nLigne;uL++)
			bNulle=bNulle && (pmA->Mat[uL][uL]==0);
		Assert1("bDiagonaleNullE",bBool(bNulle));
	Appel1("bDiagonaleNullE");
	return(bNulle);
}//bDiagonaleNullE

void DiviseurS(int nDivisota,int uPile[]){
	//empile ds uPile[] les diviseurs stricts de nDivisota,ie ]1,nDivisota[,en ordre croissant,avec le plus petit diviseur en fond de pile (index 1). 
	int upIndex,uN,nReste;
	Assert1("DiviseurS",bCroit(1,nDivisota,1e3));
	for (upIndex=0,uN=2;uN<nDivisota;uN++){
		nReste=nDivisota%uN;
		if (nReste==0){
			uPile[++upIndex]=uN;
		}
	}
	uPile[0]=upIndex;
}//DiviseurS

int nDuoCompteR(int bVoir,iMatrice *pmA,int *pnDuo,int *pnCopie,int *pnRecopie){
	//rend le nombre minimum de duos de 1 distincts ds *pmA. Deux duos identiques situés sur deux lignes distinctes ne comptent que pour 1.
	int uC,uD,uL,nCmax,nDmax,nDuoMajeur,nEtape,nSingleton;
	int nColon;
	int nDecompter,nDecompter0;
	int nDuau;
	int bDuo=kF;
	int nDuo[knColonneLiM][knColonneLiM];
	int nMatrice[knLigneLiM][knColonneLiM];
	int nPasse;
	int bVide;
	//nMatrice[][]:=(*ppmA)->Mat[][]
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				nMatrice[uL][uC]=0;
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knLigneMaX;uC++)
				nMatrice[uL][uC]=-pmA->Mat[uL][uC];//dc négatif
	//nDuo[][]=0
		for (uL=1;uL<=knColonneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				nDuo[uL][uC]=0;
	//nDuo[uL][0]=nbre de 1 ds nMatrice[uL][]
		for (uL=1;uL<=knLigneMaX;uL++)
			for (nDuo[uL][0]=0,uC=1;uC<=knLigneMaX;uC++)
				if (nMatrice[uL][uC]==1)
					nDuo[uL][0]++;
	nPasse=0;
	nEtape=0;
	nDecompter=0;
	do{
		nEtape++;
		nDecompter0=nDecompter;
		do{
			nPasse++;
			if (0)
				MatriceVoir(sC2("Passe n°",sEnt(nPasse)),pmA);
			if (0){
				for (uL=1;uL<=knLigneMaX;uL++)
					for (uC=1;uC<=knColonneMaX || bPrint("");uC++)
						printf(" %2d",nMatrice[uL][uC]);
			}
			//nDuo[uC][uD]=k ssi k lignes contiennent un duo de valeurs nEtape,avec un nEtape en colonne uC et un autre en colonne uD
				for (uC=1;uC<=knColonneMaX;uC++)
					for (uD=1;uD<=knColonneMaX;uD++)
						nDuo[uC][uD]=0;
				nDuau=0;//a
				for (uL=1;uL<=knLigneMaX;uL++)
					for (uC=1;uC<=knColonneMaX;uC++)
						if (abs(nMatrice[uL][uC])==nEtape)
							for (uD=uC+1;uD<=knColonneMaX;uD++)
								if (abs(nMatrice[uL][uD])==nEtape){
									(nDuo[uC][uD])++;
									nDuau++;
								}
			if (bVoir && (nPasse>=1))
				te("Nb de duos vus",nDuau);
			//nCmax,nDmax mémorise les numéros de colonnes qui ciblent le (un) duo majeur, ie rencontré sur le plus grand nombre de lignes
				nCmax=0;
				nDmax=0;
				nDuoMajeur=0;//d
				for (uC=1;uC<=knColonneMaX;uC++)
					for (uD=1;uD<=knColonneMaX;uD++)
						if (nDuoMajeur<nDuo[uC][uD]){
							nDuoMajeur=nDuo[uC][uD];
							nCmax=uC;
							nDmax=uD;
						}
				bDuo=(nDuoMajeur>0);
				if (bDuo){
					//nColon:=rg première colonne entièrt vide de nMatrice
						for (nColon=0,uC=1;uC<=knColonneMaX && nColon==0;uC++){
							bVide=kV;
							for (uL=1;uL<=knLigneMaX;uL++)
								bVide=bVide && nMatrice[uL][uC]==0;
							if (bVide)
								nColon=uC;
						}
					Assert1("nDuoCompteR",bCroit(1,nColon,knColonneMaX));//si assertion fausse,augmenter knColonneMaX.
					if (0)
						teee("nCmax,nDmax et nColon (ie nouvelle colonne attribuée)",nCmax,nDmax,nColon);
					for (uL=1;uL<=knLigneMaX;uL++)
						if (abs(nMatrice[uL][nCmax])==nEtape && abs(nMatrice[uL][nDmax])==nEtape){
							nMatrice[uL][nCmax]=0;//le premier terme du duo disparaît
							nMatrice[uL][nDmax]=0;//le second terme du duo disparaît
							nMatrice[uL][nColon]=abs(nEtape)+1;//un futur opérande est créé
						}
					nDecompter++;
				}
		}while(bDuo);
		//nMatrice[uL][uC]=nValeur+1 si nMatrice[uL][uC] est non nul;dc ts les opérandes non nuls ont la même valeur,au signe près,conservé
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				if (abs(nMatrice[uL][uC])==nEtape)
					nMatrice[uL][uC]=iSignePres(nMatrice[uL][uC]<0,nEtape+1);
	} while(nDecompter0<nDecompter);
	if (bVoir)
		MatriceVoir(sC2("Passe n°",sEnt(nPasse)),pmA);
	//*pnRecopie:=somme sur chaque colonne des bits isolés de résultats de duos, moins 1
		for (*pnRecopie=0,uC=1;uC<=knColonneMaX;uC++){
			nSingleton=0;
			for (uL=1;uL<=knLigneMaX;uL++)
				if (nMatrice[uL][uC]>nEtape)//>0, donc addition de 2 opérandes qui constituent un duo
					nSingleton++;
			if (nSingleton>1)
				(*pnRecopie)+=nSingleton-1;
		}
	//*pnCopie:=somme sur chaque colonne des bits isolés d'opérandes jamais évalués
		for (*pnCopie=0,uC=1;uC<=knColonneMaX;uC++){
			nSingleton=0;
			for (uL=1;uL<=knLigneMaX;uL++)
				if (nMatrice[uL][uC]<-nEtape)//opérande jamais évalué
					nSingleton++;
			(*pnCopie)+=nSingleton;
		}
	/*//nSingleton:=nb de sommes par ligne
		nSingleton=0;
		for (uL=1;uL<=knLigneMaX;uL++){
			nSingleton+=(nDuo[uL][0]+1)/2;
			te("uL",(nDuo[uL][0]+1)/2);
		}*/
	*pnDuo=nDecompter;
	return(*pnDuo+*pnCopie+*pnRecopie);
}//nDuoCompteR

void DuoDecompteR(long zDecompteMaximal){
	//décompte aléatoirt le nombre max de duos ds une matrice de densité 0.5 ds le coté est un multiple de 4; affiche la complexité pire cas
	iMatrice *pmA;
	int nBit,nCompte;
	int aLigne[knLigneLiM];
	int nC,nCompteMax,nDuo,nCopie,nRecopie,nPlace;
	long zFois;
	MatriceAllouer(&pmA);
	for (nCompteMax=0,zFois=zDecompteMaximal;zFois>0;zFois--){
		//aLigne[]:=knLigneMaX/2 bits placés aléatoirt,0 ailleurs
			for (nC=1;nC<=knLigneMaX;nC++)
				aLigne[nC]=0;
			for (nC=knLigneMaX;nC>knLigneMaX/2;nC--){
				nPlace=uHasard(nC);
				for (nBit=knLigneMaX;nBit>0;nBit--){
					if (aLigne[nBit]==0){
						nPlace--;
						if (nPlace==0){
							aLigne[nBit]=1;
							nBit=0;
						}
					}
				}
			}
		//VecteurVoir("aLigne",aLigne,1,knLigneMaX);
		if (zFois%kE3==0){
			te("zFois",zFois);
			ComplexitehAfficheR(nCompteMax);
		}
		//remplir pmA conformément à aLigne[] et compter les duos
			MatriceRazer(&pmA);
			for (nBit=0,nC=1;nC<=knLigneMaX;nC++)
				if (aLigne[nC]==1){
					nBit++;
					MatriceCircuiter(nC,&pmA);
				}
			Assert1("DuoDecompteR",nBit<knLigneMaX);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			if (nCompteMax<nCompte || zFois==0){
				nCompteMax=nCompte;
				MatriceVoir("DuoDecompteR",pmA);
				if (1)
					teee("Duos,copies et recopies",nDuo,nCopie,nRecopie);
				ComplexitehAfficheR(nCompte);
			}
	}
	// N=100: Duos,copies et recopies:2134,    0,    0. Complexité:N**2.6646 au pire.
}//DuoDecompteR

void DuoDenombreR(){
	//compte le nombre max de duos ds une matrice biaisée de densité 0.5 ou moins de coté 4N ; affiche complexité pire cas et moyenne
	iMatrice *pmA;
	int nBit,nCompte;
	int nC,nCompteMax,nDuo,nCopie,nRecopie;
	long zComptage,zCompte,zReste,zVect,zVect0,zVect1,zVectMax;
	MatriceAllouer(&pmA);
	zVect1=zPuissance(2,knLigneMaX)-1;
	zVect0=(knLigneMaX>24)? 0:0;
	t(sC2("zVect1=",sPar3(zVect1)));
	for (zCompte=zComptage=nCompteMax=0,zVectMax=0,zVect=zVect1;zVect>=zVect0;zVect--){
		zReste=(zVect==zVect0)? zVectMax: zVect;
		for (nBit=0,nC=0;nC<=knLigneMaX;nC++){
			if (zReste%2==1)
				nBit++;
			zReste=zReste/2;
		}
		if (nBit<=knLigneMaX/2){
			MatriceRazer(&pmA);
			zReste=(zVect==zVect0)? zVectMax: zVect;
			if (zReste%kE3==0){
				te("zReste",zReste);
				ComplexitehAfficheR(nCompteMax);
			}
			for (nC=0;nC<=knLigneMaX;nC++){
				if (zReste%2==1)
					MatriceCircuiter(nC,&pmA);
				zReste=zReste/2;
			};
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			if (zVect>0){
				//te("nCompte",nCompte);
				zCompte+=nCompte;
				zComptage++;
			}
			if (nCompteMax<nCompte || zVect==zVect0){
				nCompteMax=nCompte;
				zVectMax=zVect;
				MatriceVoir("DuoDenombreR",pmA);
				if (1)
					teee("Duos,copies et recopies",nDuo,nCopie,nRecopie);
				ComplexitehAfficheR(nCompte);
				//zVect=zVect0;// *****************
				//t("Dhhhhhhhhhhh");
			}
		}
	}
	te("zComptage",zComptage);
	te("zCompte",zCompte);
	tr("zCompte moyen",(zCompte*1.0)/zComptage);
	ComplexitehCalculeR((zCompte*1.0)/zComptage);  //moyenne: N=4:2.00   N=8:2.26   N=12:2.40   N=16:2.47
/*
    1    0    0    0
    0    1    0    0
    0    0    1    0
    0    0    0    1
Complexité pr N=4:N**2.00 au pire.Duos,copies et recopies:  0,    4,    0.
    0    0    1    0    1    0    1    1
    1    0    0    1    0    1    0    1
    1    1    0    0    1    0    1    0
    0    1    1    0    0    1    0    1
    1    0    1    1    0    0    1    0
    0    1    0    1    1    0    0    1
    1    0    1    0    1    1    0    0
    0    1    0    1    0    1    1    0
Complexité pr N=8:N**2.44 au pire.Duos,copies et recopies:  20,    0,    0.
    0    0    1    0    0    0    1    0    1    1    1    1
    1    0    0    1    0    0    0    1    0    1    1    1
    1    1    0    0    1    0    0    0    1    0    1    1
    1    1    1    0    0    1    0    0    0    1    0    1
    1    1    1    1    0    0    1    0    0    0    1    0
    0    1    1    1    1    0    0    1    0    0    0    1
    1    0    1    1    1    1    0    0    1    0    0    0
    0    1    0    1    1    1    1    0    0    1    0    0
    0    0    1    0    1    1    1    1    0    0    1    0
    0    0    0    1    0    1    1    1    1    0    0    1
    1    0    0    0    1    0    1    1    1    1    0    0
    0    1    0    0    0    1    0    1    1    1    1    0
Complexité pr N=12:N**2.53 au pire.Duos,copies et recopies:  45,    0,    0.
    0    0    0    0    1    0    1    0    1    1    0    0    1    1    1    1
    1    0    0    0    0    1    0    1    0    1    1    0    0    1    1    1
    1    1    0    0    0    0    1    0    1    0    1    1    0    0    1    1
    1    1    1    0    0    0    0    1    0    1    0    1    1    0    0    1
    1    1    1    1    0    0    0    0    1    0    1    0    1    1    0    0
    0    1    1    1    1    0    0    0    0    1    0    1    0    1    1    0
    0    0    1    1    1    1    0    0    0    0    1    0    1    0    1    1
    1    0    0    1    1    1    1    0    0    0    0    1    0    1    0    1
    1    1    0    0    1    1    1    1    0    0    0    0    1    0    1    0
    0    1    1    0    0    1    1    1    1    0    0    0    0    1    0    1
    1    0    1    1    0    0    1    1    1    1    0    0    0    0    1    0
    0    1    0    1    1    0    0    1    1    1    1    0    0    0    0    1
    1    0    1    0    1    1    0    0    1    1    1    1    0    0    0    0
    0    1    0    1    0    1    1    0    0    1    1    1    1    0    0    0
    0    0    1    0    1    0    1    1    0    0    1    1    1    1    0    0
    0    0    0    1    0    1    0    1    1    0    0    1    1    1    1    0
Complexité pr N=16:N**2.58 au pire.Duos,copies et recopies:  81,    0,    0.
    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1
    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1
    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1
    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1
    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1
    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0
    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1
    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0
    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0
    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1
    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1
    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1
    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0
    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0
    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0
    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0
    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0
    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0
    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1
    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0
Complexité pr N=20:N**2.60 au pire.Duos,copies et recopies: 121,    0,    0.
    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1
    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1
    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1
    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1
    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0
    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1
    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1
    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0
    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0
    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1
    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0
    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0
    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1
    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0
    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0
    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0
    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1
    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1
    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1
    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0
    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0
    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0
    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1
    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0
Complexité pr N=24:N**2.62 au pire.Duos,copies et recopies: 172,    0,    0.
*/
}//DuoDenombreR 

int nDuoEstimeR(iMatrice *pmA,int uFois){
	//rend une estiMation statistique de la complexité en pire cas du nombre de duos à sommer pour multiplier deux Matrices 
	int uBitat;
	int nAccumulationMax;
	int k1Doublons=k1BitsDistincts;
	float fDensiteh;
	float fDensitehMax;
	int nCompte,nDuo;
	int uF;
	int nCopie;
	int nRecopie;
	nAccumulationMax=0;
	printf("Mesures sur %s aléatoirement (dimensions:%dx%d).\n",sPluriel(uFois,"Matrice$ de bits remplie$"),pmA->nLigne,pmA->nLigne);
	//estimer kuFois fois et en déduire zDuoMax ds le pire cas
		for (fDensitehMax=0.0,uF=1;uF<=uFois;uF++){
			MatriceRazer(&pmA);
			uBitat=knLigneMaX*knLigneMaX;
			fDensiteh=fMatriceRempliR(k1Doublons,uBitat,&pmA);//pose uBitat bits distincts ou non selon k1Doublons
			if (fDensiteh>10)
				tr("Densité max courante",fDensiteh);
			if (fDensiteh>=0.0)
				MatriceVoir(sC3("Matrice n°",sEnt(uF),":"),pmA);
			fDensitehMax=rSup(fDensitehMax,fDensiteh);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//à chaq duo de la multipliante A correspond ds la multipliée B 1 somMation de lignes.
			if (1)
				teee("Duos,copies et recopies",nDuo,nCopie,nRecopie);
			if (0)
				MatriceVoir("Matrice originale:",pmA);
			if (nCompte>nAccumulationMax)
				printf("Matrice %d/%d: %s.\n",uFois-uF+1,uFois,sPluriel(nCompte,"accumulation$ en tout"));
			nAccumulationMax=iMax(nAccumulationMax,nCompte);
		}
	//tr("Complexité au pire",2+nDecompteMax/pow(knLigneMaX,2));
	printf("Dans le pire cas, accumulations/somMations de lignes avec algo naïf: %d/%d.\n",nAccumulationMax,(knLigneMaX-1)*knLigneMaX);
	//nDecompteMax=knLigneMaX*knLigneMaX;
	return(nAccumulationMax);
}//nDuoEstimeR

void DuoMaximiseR(){
	//sélectionne le pire cas et affiche la matrice multipliante pr la multiplication par duos ainsi que la complexité algorithmique ds ce pire cas.
	iMatrice *pmA;
	long zCas,zCasInitial,zCasMax,zCasPire;
	int uBitat,nCompte,nComptePire,nCopie,nDuo,nDuoPire,bCasPire,uPeriode,nRecopie,bVoir;
	uBitat=knLigneMaX*(knLigneMaX-1);//la matrice contient uBitat bits
	zCasMax=2*zPuissance(2,uBitat)-1;//soit zCasMax configuration binaires à envisager
	uPeriode=zPuissance(10,iMin(knLigneMaX,6));
	printf("DuoMaximiseR: %s configurations à examiner (knLigneMaX=%d,uPeriode=%d).\n",sPar3(zCasMax),knLigneMaX,uPeriode);
	MatriceAllouer(&pmA);
	zCasInitial=257924799;
	zCasInitial=zCasMax;
	for (nComptePire=0,nDuoPire=0,zCas=zCasInitial;zCas>=0;zCas--){
		MatriceConstitueR(zCas,&pmA);
		//MatriceVoir(sC3("Matrice ",sEnt(zCas),":"),pmA);
		nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
		bCasPire=(nCompte>nComptePire || ((nCompte==nComptePire) && nDuo>nDuoPire));//à compte égal, retenir le cas du pire nombre de duos (discutable)
		if (bCasPire){
			zCasPire=zCas;
			nDuoPire=nDuo;
			nComptePire=nCompte;
		}
		bVoir=bCasPire || (zCas>0 && zCas%uPeriode==0) || zCas==zCasMax;
		//bVoir=kF;
		if (bVoir){
			MatriceConstitueR(zCasPire,&pmA);
			MatriceVoir("Matrice de poids maximal:",pmA);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			printf("nCompte (nDuo+nCopie+nRecopie)/zCasPire/Reste: %d (%d+%d+%d) %9ld %9ld\n",nComptePire,nDuo,nCopie,nRecopie,zCasPire,zCas);
			ComplexitehAfficheR(nCompte);
		}
	}
/*Matrice de poids maximal:
    0    1    1    1    1    0
    1    0    1    1    1    0
    1    1    0    1    0    1
    1    1    1    0    0    1
    0    1    1    1    0    1
    1    1    1    1    1    1
nCompte (nDuo+nCopie+nRecopie)/zCasPire/Reste: 15 (15+0+0) 2146164207 2146483647
Complexité:N**2.51 au pire.
    MatriceTester,test n°6: tâche terminée.
Programme terminé.*/
}//DuoMaximiseR

void DuoMinimiseR(){
	//dans C=AxB, minimise le nombre de paires de vecteurs lignes de B à additionner en mutualisant les sommes ayant les mêmes opérandes
	iMatrice *pmA;
	int nBarre;
	int kuFois=1;//nb total d'estiMations
	t("Minimiser les sommes de vecteurs lignes de B ds C=AxB en factorisant les sommes ayant mêmes opérandes");
	t("Le nbre de duos de 1 distincts ds la multipliante A donne le nbre de lignes à sommer ds la multipliée B");
	MatriceAllouer(&pmA);
	nBarre=nDuoEstimeR(pmA,kuFois);
	ComplexitehAfficheR(nBarre);
}//DuoMinimiseR

void DuoUtiliseR(int nCas){
		switch (nCas) {
			case duMinimiseR:
				DuoMinimiseR();
				break;
			case duDenombreR:
				DuoDenombreR();//décompte exhaustif
				//DuoDecompteR(kE6);//décompte statistique
				break;
			case duPireCaS:
				DuoMaximiseR();
				break;
			default:
				break;
	}
}//DuoUtiliseR

int mExposantCalculeR(int uLigneDuCofacteurCourant,int bLignePrise[]){
	//rend le signe de (-1)**k ds la contribution du cofacteur (aij) courant;le nombre de termes du tableau bLignePrise[] est bLignePrise[0].
	int mExposant,nLignat,uL;
	Assert2("mExposantCalculeR",bCroit(1,uLigneDuCofacteurCourant,bLignePrise[0]),bLignePrise[uLigneDuCofacteurCourant]==kF);
	//tt calcul de cofacteur est une somme alternée;le signe du terme courant change à chaque ligne encore présente ds le cofacteur courant
	nLignat=bLignePrise[0];
	if (kF){
		for (uL=1;uL<=nLignat || bPrint(" *** ");uL++)
			printf(" %d",bLignePrise[uL]);
	}
	for (mExposant=-1,uL=1;uL<=uLigneDuCofacteurCourant;uL++)
		if (bLignePrise[uL]==0)//cette ligne fait partie du cofacteur car elle n'a pas encore été consommée
			mExposant=-mExposant;
	//si ttes les lignes sont prises sauf (évidt,vu Assert2) uLigneDuCofacteurCourant, l'exposant est cplémenté 1 fois,dc mExposant final=1.
	return(mExposant);
}//mExposantCalculeR

int nFibonacciDeterminanT(int nCoteh){
	//rend le déterminant de la matrice carrée "Fibonacci" de coté nCoteh;ce déterminant est un nombre de la suite de Fibonacci.
	int nDeterminant=0;
	iMatrice *pmA;
	MatriceFibonaccier(nCoteh,&pmA);
		//MatriceVoir("nFibonacciDeterminanT",pmA);
		printf("Fib(%d): ",nCoteh-1);//oui,F(1)=F(2)=1 et F(10)=55.
		nDeterminant=yDeterminantCalculeR(pmA,kV);
	free(pmA);
	return(nDeterminant);
}//nFibonacciDeterminanT

void GrapheArcBouteR(graf *pgG,int nArcMineur){
	//décompose chaque arc majeur de pgG en nArcMineur arcs mineurs (empile les nouveaux sommets)
	int nSommet,nSommet0=pgG->nSommetEnTout;
	int nSommetEnSus,nArcMajeur;
	int uArc,aK,aL,sX,sY;
	//te("nArcMineur",nArcMineur);
	Assert1("GrapheArcBouteR1",nArcMineur>1);
	te("nSommet0",nSommet0);
	//nArcMajeur:=nb total d'arcs majeurs
		for (nArcMajeur=0,sX=1;sX<=nSommet0;sX++)
			if ( bPair(sX) ) 
				nArcMajeur++;
		te("nArcMajeur",nArcMajeur);
	nSommetEnSus=(nArcMineur-1)*nArcMajeur;
		te("nSommetEnSus",nSommetEnSus);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé arc-bouté AVANT");
	//empiler les nouveaux sommets
		t("empiler les nouveaux sommets");
		Assert1("GrapheArcBouteR2",nSommet0+nSommetEnSus+1<kuGrapheSommetLim);
		for (sX=nSommet0+1;sX<=nSommet0+nSommetEnSus;sX++)
			pgG->aHed[sX+1]=pgG->aHed[sX]+1;
		pgG->nSommetEnTout+=nSommetEnSus;
	te("nSommet0 APRES empiler les nouveaux sommets",nSommet0);
	//ajouter les nouveaux arcs
		for (nSommet=nSommet0,sX=1;sX<=nSommet0;sX++)
			if ( bPair(sX) ) 
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];//printf("%s\n",sCouple(sX,sY));
					pgG->sSuk[aK]=++nSommet;//remplace sY
					for (uArc=2;uArc<=nArcMineur;uArc++){
						aL=pgG->aHed[nSommet];
						if (uArc<nArcMineur)
							nSommet++;
						pgG->sSuk[aL]=(uArc<nArcMineur)? nSommet:sY;//cible le sommet suivant, et finalt sY.
					}
				}
		pgG->nArcEnTout+=nSommetEnSus;
	Assert1("GrapheArcBouteR3",bGrapheSimple(pgG));
	if (0) GrapheVoir(pgG,"Graphe cliqué étagé arc-bouté APRES");
}//GrapheArcBouteR

void GrapheChemineR(graf *pgG,int uColonneSource,int sL,int sC,int uLigneCible,int uPoidsCentral){
	int knCapaciteMinimaleNulle=0,kuCapaciteMaximaleUnitaire=1,kuPoidsUnitaire=1;
	//printf("uColonneSource,uLigneCible,sL,sC: %s %3d,%3d,%3d,%3d.\n",sTab(uColonneSource),uColonneSource,uLigneCible,sL,sC);
	if (uPoidsCentral==kuPoidsUnitaire)
		printf("uColonneSource,uLigneCible: %s %3d,%3d.\n",sTab(uColonneSource),uColonneSource,uLigneCible);
	GrapheArquer3(pgG,uColonneSource,sL,knCapaciteMinimaleNulle,kuCapaciteMaximaleUnitaire,kuPoidsUnitaire);
	GrapheArquer3(pgG,sL,sC,knCapaciteMinimaleNulle,kuCapaciteMaximaleUnitaire,uPoidsCentral);
	GrapheArquer3(pgG,sC,uLigneCible,knCapaciteMinimaleNulle,kuCapaciteMaximaleUnitaire,kuPoidsUnitaire);
}//GrapheChemineR

void GrapheConcocteR(iMatrice* pmA,int nSommetDuGrapheOriginal){
	//Génère le graphe contracté associé à pmA 
	int bArete,cPasse,bSommet,bStandard;
	int kuPoidsDouble=2,kuPoidsUnitaire=1;
	int sL,uL,sC,uC,uCoinMax,sX;
	int nSommet,nSommet1,nSommet2,nSommetInterfacable;
	graf *pgG;
	Appel0("GrapheConcocteR");
		nSommetInterfacable=pmA->nLigne/2+pmA->nColonne/2;
		te("nSommetInterfacable",nSommetInterfacable);
		pgG=(graf *) malloc(sizeof(graf));
			for (cPasse=0;cPasse<=1;cPasse++){
				if (cPasse>0){//pgG soit initialt un graphe à nSommet sommets (calculés lorsque cPasse=0) et ne contenant aucun arc:
					te("nSommet requis",nSommet);
					Assert1("GrapheContracteR1",nSommet<kuGrapheSommetLim);
					pgG->nSommetEnTout=nSommet;
					VecteurInitialiser(pgG->aHed,1,pgG->nSommetEnTout+1,1);
					pgG->nArcEnTout=0;
				}
				nSommet=nSommetInterfacable;
				//Connecter les arêtes
					for (uL=1;uL<=pmA->nLigne/2;uL++)
						for (uC=1;uC<=pmA->nColonne/2;uC++){
							bArete=pmA->Mat[2*uL-1][2*uC-1]==2 && pmA->Mat[2*uL-0][2*uC-0]==2;
							if (bArete){//générer les deux sommets qui délimitent l'arête et construire un chemin qui la traverse:
								sL=++nSommet;sC=++nSommet;
								if (cPasse>0)
									GrapheChemineR(pgG,uC,sL,sC,uL,kuPoidsDouble);
							}
						}//for uC
					nSommet1=nSommet;
				tee("nSommet1,Delta1/2",nSommet1,(nSommet1-nSommetInterfacable)/2);
				//Connecter les sommets
					uCoinMax=nSommetDuGrapheOriginal*nSommetDuGrapheOriginal;
					for (uC=1;uC<=pmA->nColonne/2;uC++)
						for (uL=1;uL<=pmA->nLigne/2;uL++){
							bSommet=pmA->Mat[2*uL-1][2*uC]==1;
							if (bSommet){//générer deux sommets (sL,sC) et construire un chemin qui les traverse:
								sL=++nSommet;sC=++nSommet;
								bStandard=kF || (uL>1);
								if (cPasse>0)
									GrapheChemineR(pgG,(bStandard)? uC: uCoinMax,sL,sC,(bStandard)? uC: uCoinMax,kuPoidsUnitaire);
							}
						}//for uL
					nSommet2=nSommet;
				tee("nSommet2,Delta2/2",nSommet2,(nSommet2-nSommet1)/2);
			}//for cPasse
		GrapheVoir(pgG,"Graphe contracté avant symétrisation");
		//GrapheSymetriser(pgG);
		if (0){
			//négativer pgG->aHed[sX] lorsque sX n'est pas connectable à une source ou une trappe ——pour CouplageOptimiser
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX]=iSignePres(nSommetInterfacable<sX,pgG->aHed[sX]);
			//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout);
			//CouplageOptimiser(pgG,k1Poids,k1Maximum);
			//VecteurVoir("pgG->aDeh",pgG->sPer[],1,pgG->nSommetEnTout);
			//négativer les éléments de pmA qui ont été choisis ——pgG->sPer[] contient une copie du couplage résultant 
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]>0){
						//uL=sOrigine[sX];uC=sOrigine[pgG->sPer[sX]];
						//aK=sOrigine[sX];
						/*tee("uL,uC",uL,uC);
						if (sX<pgG->sPer[sX]){
							aK=nGrapheArc(*pgSource,uL,uC);*/
						//tee("uL,uC",uL,uC);
						//te("aK",aK);
							//pgSource->sSuk[aK]=-abs(pgSource->sSuk[aK]);
							//pgSource->coulh[aK]=0;
						}
			//GrapheVoir1(pgSource,kV,"Graphe contracté dans lequel chaque ARC pris est décoloré");
		}
		free(pgG);
	Appel1("GrapheConcocteR");
}//GrapheConcocteR

void GrapheEtireR(graf *pgG,int nTest){
	//crée un graphe complet pgG (ou quasi-complet,selon nTest),déroulé,bipartitionné et relié sur chaque colonne à 2 sélecteurs amont et aval. 
	int bEtirer=kF;
	int bBaton,nBaton,nCas;
	int uB,uE,nPaire,sX,sY,sYamont,sYaval,sZ;
	int uBrancheParEtoile,bDesarquer,nEtoile,nSommetParEtoile,nSommet,nSommet0,nSommet1;
	int aK,aL;
	Appel0("GrapheEtireR");
	nSommet=nTest/10;
	Assert1("GrapheEtireR0",nSommet>1);
	nCas=nTest%10;
	if (bEtirer) te("nSommet",nSommet);
	GrapheCliquer(pgG,nSommet);
	if (nSommet==3){//succes cas 0 OK
		if (nCas==1) bDesarquer=bGrapheDesarquer(pgG,2,3);//échec,OK
		if (nCas==2) bDesarquer=bGrapheDesarquer(pgG,3,2);//succès OK
	}
	if (nSommet==4){//succes cas 0 OK
		if (nCas==1) bDesarquer=bGrapheDesarquer(pgG,2,3);//succès 1-3-2-4
		if (nCas==2) bDesarquer=bGrapheDesarquer(pgG,3,2);//succès 1-2-3-4
		if (nCas==3) bDesarquer=bGrapheDesarquer(pgG,2,4) && bGrapheDesarquer(pgG,2,3);//échec OK
	}
	GrapheVoir(pgG,sC4("Graphe cliqué à ",sPluriel(nSommet,"sommet"),",restriction n°",sEnt(nCas)));
	GrapheDerouler(pgG);
	if (0) GrapheVoir(pgG,"Graphe cliqué étagé");
	GrapheBipartitionner(pgG);
	if (0) GrapheVoir(pgG,"Graphe cliqué étagé biparti");
	nSommet0=pgG->nSommetEnTout;
	//te("nSommet0",nSommet0);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé biparti arqué");
	GrapheArcBouteR(pgG,5);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé biparti arc-bouté");
	//fermer le circuit source-trappe
		GrapheArquer(pgG,1,nSommet0);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé biparti arc-bouté fermé");
	nEtoile=2*nSommet;
	if (bEtirer) te("nEtoile",nEtoile);
	uBrancheParEtoile=nSommet;
	nSommetParEtoile=1+uBrancheParEtoile;
	if (bEtirer) te("uBrancheParEtoile",uBrancheParEtoile);
	nSommet1=pgG->nSommetEnTout;
	GrapheEtoiler(pgG,nEtoile,uBrancheParEtoile);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé biparti étoilé non connecté");
	//connecter les étoiles au reste du graphe
		if (bEtirer) te("nSommet1",nSommet1);
		for (uE=1;uE<=nEtoile/2;uE++){
			sYamont=nSommet1+2*(uE-1)*nSommetParEtoile+1;//centre étoile amont
			sYaval=sYamont+nSommetParEtoile;//centre étoile aval
			if (bEtirer) printf("Centres des étoiles amont et aval:%d,%d.\n",sYamont,sYaval);
			for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				if (bEtirer) printf("(sX,pointe amont):       (%2d,%2d)\n",sX,sYamont);
				if (bEtirer) printf("(sX,pointe aval):       (%2d,%2d)\n",sX+1,sYaval);
				GrapheArquer(pgG,sX,sYamont);
				GrapheArquer(pgG,sX+1,sYaval);
				sX+=2*nSommet;
			}
		}
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé biparti arc-bouté étoilé connecté");
	//pgG->aDeh[]:=appariements des sommets
		VecteurRazer(pgG->aArcTo,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->coulh,1,pgG->nArcEnTout);
bEtirer=kF;
		//appariements hors arc-boutement
			for (nBaton=0,nPaire=0,uE=1;uE<=nEtoile/2;uE++){
				sYamont=nSommet1+2*(uE-1)*nSommetParEtoile+1;
				sYaval=sYamont+nSommetParEtoile;
				ApparieR(pgG,coBleu,sYamont,sYaval,&nBaton,&nPaire);
				if (bEtirer) printf("Couple %s\n",sCouple(sYamont,sYaval));
				if (bEtirer) te("étoile0",sYamont);
				for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
					if (bEtirer) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
					if (bEtirer) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
					aK=nGrapheArc(pgG,sX,sYamont);
					aL=nGrapheArc(pgG,sX+1,sYaval);
					bBaton=bImpair(sX) && bCroit(1,sX,2*nSommet0*nSommet0);
					Assert1("GrapheEtireR98",bBaton);
					ApparieR(pgG,coJaune,sX,sX+1,&nBaton,&nPaire);
					if (bEtirer) printf("Couple %s\n",sCouple(sX,sX+1));
					ApparieR(pgG,coRouge,sYamont,sYaval,&nBaton,&nPaire);
					if (bEtirer) printf("Coupleeee %s\n",sCouple(sYamont,sYaval));
					sX+=2*nSommet;
				}
			}
		//VecteurVoir("pgG->coulh",pgG->coulh,1,pgG->nArcEnTout);
		//appariements des sommets de l'arc-boutement
			if (bEtirer) t("*******************appariements des sommets de l'arc-boutement");
bEtirer=kF;
			if (bEtirer) tee("nSommet0,nSommet1",nSommet0,nSommet1);
			for (sX=2;sX<=nSommet0;sX+=2)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					if ( bCroitStrict(nSommet0,sY,nSommet1) ){
						//if (bEtirer) printf("Kouple %s\n",sCouple(sX,sY));
						sZ=pgG->sSuk[pgG->aHed[sY+1]];
						ApparieR(pgG,coNoir,sY,sY+1,&nBaton,&nPaire);
						if (bEtirer) printf("Couple %s\n",sCouple(sY,sY+1));
					}
				}
bEtirer=kF;
	if (0) teeee("nEtoile,uBrancheParEtoile+1,nBaton,nPaire",nEtoile,uBrancheParEtoile+1,nBaton,nPaire);
	Assert1("GrapheEtireR",sYaval=pgG->nSommetEnTout);
	//te("nSommet0",nSommet0);
	Appel1("GrapheEtireR");
	Assert1("GrapheEtireR9",bGrapheBiparti(pgG));
}//GrapheEtireR

void GrapheEtriller(graf *pgG,int uPartition){//O(A)
	//X devient X' et X"=X+1,contrairt à GrapheBipartitionne(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;
	int aK;
	int kbScruter=kF;
	int nSommet;
	int Index[kuGrapheArcLim];
	int uP,sX,sY;
	//Assert4("GrapheEtriller1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),uPartition>1);
	if (kbScruter) Appel0("GrapheEtriller");
		//if (kbScruter) GrapheVoir(pgG,"AVANT");
		nSommet=pgG->nSommetEnTout;
		nArc=pgG->nArcEnTout;
			for (aK=1;aK<=nArc+(uPartition-1)*nSommet;aK++)
				Index[aK]=aK;
		//ménager entre les listes de sommets successeurs dédiés à chaque sommet source uPartition-1 arcs par nouveau sommet,en terminant par un nouvel arc en pgG->sSuk[1]. 
			if (kbScruter) VecteurVoir("aHed1",pgG->aHed,1,nSommet+1);
			if (kbScruter) VecteurVoir("index",Index,1,nArc+(uPartition-1)*nSommet);
			if (kbScruter) VecteurVoir("sSuk1",&pgG->sSuk[0],1,nArc+(uPartition-1)*nSommet);
			if (kbScruter) te("nSommet",nSommet);
			for (sX=nSommet;sX>0;sX--){
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					//tee("aK,sY",aK,sY);
					pgG->sSuk[aK+(uPartition-1)*(sX-1)+uPartition-1]=+(uPartition*sY-uPartition+1);//ds chaq plexe,recopie des cibles,décalées de (uPartition-1) cases. 
				}
				//if (kbScruter) tee("aK,sX",aK,sX);
				//pgG->sSuk[aK+sX]=uPartition*sX;//nouvel arc,notamment en pgG->sSuk[1] puisque aK=0 quand sX=1.
			}
			if (kbScruter) VecteurVoir("aHed3",pgG->aHed,1,nSommet+1);
			if (kbScruter) VecteurVoir("index",Index,1,nArc+(uPartition-1)*nSommet);
			if (kbScruter) VecteurVoir("sSuk3",pgG->sSuk,1,nArc+(uPartition-1)*nSommet);
		//interclasser les sommets originaux de sorte que X'=X+1 pour tout X
			//te("2*nSommet+2",2*nSommet+2);
			Assert1("GrapheEtriller3",uPartition*nSommet+2<kuGrapheSommetLim);//pr li+3;sinon,ajouter un "if"
			for (sX=nSommet+1;sX>=0;sX--)
				pgG->aHed[uPartition*sX]=+abs( pgG->aHed[sX]+(uPartition-1)*sX );
			for (sX=nSommet+1;sX>=0;sX--)
				for (uP=1;uP<uPartition;uP++)
					pgG->aHed[uPartition*sX-uP]=abs(pgG->aHed[uPartition*sX-uP+1])-1;
			if (kbScruter) VecteurVoir("aHed5",pgG->aHed,1,uPartition*nSommet+1);
			if (kbScruter) VecteurVoir("index",Index,1,nArc+(uPartition-1)*nSommet);
			if (kbScruter) VecteurVoir("sSuk5",pgG->sSuk,1,nArc+(uPartition-1)*nSommet);
		//remplacer les 0 de sSuk par le sommet suivant
			for (sX=nSommet*uPartition;sX>0;sX--)
				if ((sX % uPartition)!=0){
					Assert1("GrapheEtriller2",pgG->aHed[sX+1]-pgG->aHed[sX]==1);
					aK=pgG->aHed[sX];
					pgG->sSuk[aK]=sX+1;
					//pgG->sSuk[aK]=0;
				}
			if (kbScruter) VecteurVoir("aHed7",pgG->aHed,1,uPartition*nSommet+1);
			if (kbScruter) VecteurVoir("index",Index,1,nArc+(uPartition-1)*nSommet);
			if (kbScruter) VecteurVoir("sSuk7",pgG->sSuk,1,nArc+(uPartition-1)*nSommet);
		pgG->nSommetEnTout=nSommet*uPartition;
		pgG->nArcEnTout=nArc+(uPartition-1)*nSommet;
		if (kbScruter) GrapheVoir(pgG,"APRES");
		if (0 && kbScruter)
			GrapheSymetriser(pgG);
		//Assert4("GrapheEtriller9",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),!kbScruter || bGrapheBiparti(pgG));
	if (kbScruter) Appel1("GrapheEtriller");
}//GrapheEtriller

void GrapheExtirpeR(graf *pgG,int nTest){
	//crée un graphe complet pgG (ou quasi-complet,selon nTest),déroulé,quadripartitionné et relié sur chaque colonne à 2 sélecteurs amont et aval. 
	int bExtirper=kF;
	int bBaton,nBaton,nCas;
	int uB,uE,nPaire,sX,sY,sYamont,sYaval;
	int uBrancheParEtoile,bDesarquer,nEtoile,nSommetParEtoile,nSommet,nSommet0;
	int aK,aL;
	if (bExtirper) Appel0("GrapheExtirpeR");
	nSommet=nTest/10;
	nEtoile=2*nSommet;
	uBrancheParEtoile=nSommet;
	nSommetParEtoile=1+uBrancheParEtoile;
	//teee("nSommet,nEtoile,uBrancheParEtoile",nSommet,nEtoile,uBrancheParEtoile);
	Assert1("GrapheExtirpeR0",nSommet>1);
	nCas=nTest%10;
	GrapheCliquer(pgG,nSommet);
	if (nSommet==3){//succes cas 0 OK
		if (nCas==1) bDesarquer=bGrapheDesarquer(pgG,2,3);//échec,OK
		if (nCas==2) bDesarquer=bGrapheDesarquer(pgG,3,2);//succès OK
	}
	if (nSommet==4){//succes cas 0 OK
		if (nCas==1) bDesarquer=bGrapheDesarquer(pgG,2,3);//succès 1-3-2-4
		if (nCas==2) bDesarquer=bGrapheDesarquer(pgG,3,2);//succès 1-2-3-4
		if (nCas==3) bDesarquer=bGrapheDesarquer(pgG,2,4) && bGrapheDesarquer(pgG,2,3);//échec OK
	}
	if (1) GrapheVoir(pgG,sC4("Graphe cliqué à ",sPluriel(nSommet,"sommet"),",restriction n°",sEnt(nCas)));
	GrapheDerouler(pgG);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé");
	GrapheEtriller(pgG,3);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé triparti");
	GrapheBipartitionner(pgG);
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé hexaparti");
	nSommet0=pgG->nSommetEnTout;
	//te("nSommet0",nSommet0);
	GrapheArquer(pgG,1,nSommet0);
	if (0) GrapheVoir(pgG,"Graphe cliqué étagé hexaparti arqué");
	GrapheEtoiler(pgG,nEtoile,uBrancheParEtoile);
	if (0) GrapheVoir(pgG,"Graphe cliqué étagé hexaparti étoilé non connecté");
	//connecter les étoiles au reste du graphe
		if (bExtirper) te("nSommet0",nSommet0);
		for (uE=1,sX=3;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;//centre étoile amont
			sYaval=sYamont+nSommetParEtoile;//centre étoile aval
			if (bExtirper) printf("Centres des étoiles amont et aval:%d,%d.\n",sYamont,sYaval);
			for (uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				//te("sX",sX);
				if (bExtirper) printf("(sX,pointe amont):       (%2d,%2d)\n",sX,sYamont);
				if (bExtirper) printf("(sX,pointe aval):       (%2d,%2d)\n",sX+1,sYaval);
				GrapheArquer(pgG,sX,sYamont);
				GrapheArquer(pgG,sX+1,sYaval);
				sX+=6;
			}
		}
	if (1) GrapheVoir(pgG,"Graphe cliqué étagé quadriparti étoilé connecté");
bExtirper=kF;
	VecteurRazer(pgG->aDeh,1,pgG->nSommetEnTout);
	//pgG->aDeh[]:=appariements des sommets vers les étoiles
		for (nBaton=0,nPaire=0,uE=1,sX=3;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;
			sYaval=sYamont+nSommetParEtoile;
			ApparieR(pgG,coBleu,sYamont,sYaval,&nBaton,&nPaire);
			if (bExtirper) printf("Couple extrême10 %s\n",sCouple(sYamont,sYaval));
			//if (bExtirper) te("étoile0",sYamont);
			for (uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				//if (bExtirper) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
				//if (bExtirper) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
				aK=nGrapheArc(pgG,sX,sYamont);
				aL=nGrapheArc(pgG,sX+1,sYaval);
				bBaton=(sX%6==3) && (sX<=6*nSommet0*nSommet0);
				Assert1("GrapheExtirpeR98",bBaton);
				ApparieR(pgG,coJaune,sX,sX+1,&nBaton,&nPaire);
				if (bExtirper) printf("    Couplq11 %s baton:%s\n",sCouple(sX,sX+1),sBool(bBaton));
				ApparieR(pgG,coRouge,sYamont,sYaval,&nBaton,&nPaire);
				if (bExtirper) printf("    Couplq12 %s\n",sCouple(sYamont,sYaval));
				sX+=6;
			}
		}
//bExtirper=kF;
//Titrer("APRES");
	//pgG->aDeh[]:=appariements des sommets hors étoiles
		for (uE=1,sX=3;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;
			sYaval=sYamont+nSommetParEtoile;
			//ApparieR(pgG,coBleu,sYamont,sYaval,&nBaton,&nPaire);
			if (bExtirper) printf("Couple extrême20 %s\n",sCouple(sYamont,sYaval));
			//if (bExtirper) te("étoile0",sYamont);
			for (uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				//if (bExtirper) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
				//if (bExtirper) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
				aK=nGrapheArc(pgG,sX,sYamont);
				aL=nGrapheArc(pgG,sX+1,sYaval);
				ApparieR(pgG,coOrange,sX-2,sX+3,&nBaton,&nPaire);
				if (bExtirper) printf("    Couplq21 %s\n",sCouple(sX-2,sX+3));
				ApparieR(pgG,coVert,sX-1,sX+2,&nBaton,&nPaire);
				if (bExtirper) printf("    Couplq22 %s\n",sCouple(sX-1,sX+2));
				sX+=6;
			}
		}
bExtirper=kF;
	if (0) teeee("nEtoile,uBrancheParEtoile+1,nBaton,nPaire",nEtoile,uBrancheParEtoile+1,nBaton,nPaire);
	//tee("pgG->nSommetEnTout,nPaire",pgG->nSommetEnTout,nPaire);
	Assert1("GrapheExtirpeR",2*nPaire==pgG->nSommetEnTout);
	//te("nSommet0",nSommet0);
	if (0){//retirer les bâtons dus au bipartitionnement
		for (sX=nSommet0-1;sX>=1;sX--)
			for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--)
				if (sY=pgG->sSuk[aK],sY==sX+1){
					//tee("suppression arc",sX,sY);
					bDesarquer=bGrapheDesarquer(pgG,sX,sY);
					Assert1("GrapheExtirpeR9",bDesarquer);
				}
	}
	Assert1("GrapheExtirpeR9",bGrapheBiparti(pgG));
	if (bExtirper) Appel1("GrapheExtirpeR");
}//GrapheExtirpeR

void GrapheMatriceR(graf *pgG,int bSimple,int nBaton,int nCarreh,iMatrice **ppmMatriceDuGraphe){
	int nB,bBaton,aK,uL,nLien,bPaire,nValeur,sX,sY;
	const int kbAntisymetrique=kF;
	//te("(*ppmMatriceDuGraphe)->nLigne",(*ppmMatriceDuGraphe)->nLigne);
	//VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
	for (nLien=0,nB=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			bPaire=pgG->aArcTo[sX]!=0 && (abs(pgG->aArcTo[sY])==sX) && (abs(pgG->aArcTo[sX])==sY);
			//nValeur:=couleur de l'arc si (sX,sY) est un arc apparié et, sinon, une couleur qui indique l'appartenance au carré 
				nValeur=(bCroit(1,sX,nCarreh) && bCroit(1,sY,nCarreh))? 8 : 9;//appartenance au carré
				if (!bSimple)
					nValeur=(pgG->sPer[sX]==coOrange && pgG->sPer[sY]==coOrange)?8: 9;
				if (bPaire)
					nValeur=pgG->sPer[sX];
			if (nValeur>0)
				nLien++;
			//supprimer les bâtons
				bBaton=bPaire && pgG->aArcTo[sX]<0 && pgG->aArcTo[sY]<0;
				if (bBaton)
					(nB++,nValeur=0);
			(*ppmMatriceDuGraphe)->Mat[sX][sY]=+nValeur;
			if (nBaton!=0)
				(*ppmMatriceDuGraphe)->Mat[sY][sX]=iSignePres(kbAntisymetrique,nValeur);
		}
	teeee("dans GrapheMatriceR,nB et nCarreh et nBaton,nLien",nB,nCarreh,nBaton,nLien);
	Assert2("GrapheMatriceR1",nB==nBaton,nLien==pgG->nArcEnTout);
	for (uL=1;uL<=(*ppmMatriceDuGraphe)->nLigne;uL++)
		(*ppmMatriceDuGraphe)->Mat[uL][0]=(*ppmMatriceDuGraphe)->Mat[0][uL]=uL;
	(*ppmMatriceDuGraphe)->Mat[0][0]=(*ppmMatriceDuGraphe)->nLigne;
}//GrapheMatriceR

void QuadripoleGenererEtageConnecteR(int nSommet,int bBoucler,int ukHuit,int nTest,graf *pgG){
	int nArc,bArquer,uC,uL,nOffset,nSommat,uEntresol;
	int uQuad0,uQuad1,sX,sY,nCouleur;
	nOffset=pgG->nSommetEnTout;
	for (uL=1;uL<=nSommet;uL++)
		for (uC=1;uC<=nSommet;uC++){
			nSommat=pgG->nSommetEnTout;
			GrapheSommer(pgG,+ukHuit);
			//relier les kuHuit sommets en Grand X
//enum eCouleuR {coAlphA,coJaune,coRouge,coBleu,coVert,coOrange,coNoir,coOmegA};
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
							GrapheArquer1(pgG,sX,sY,nCouleur);//coVert et suivants
							nArc++;
						}
					}
			}
	te("arcs entre étages:",nArc);
}//QuadripoleGenererEtageConnecteR

int bGrapheQuadripoleR(graf *pgG,int bBoucler,int nTest,iMatrice **ppmA){
	//crée un graphe complet pgG (ou quasi-complet,selon nTest),déroulé,bipartitionné et relié sur chaque colonne à 2 sélecteurs amont et aval. 
	const int kuHuit=8;//nbre de sommets dans le quadripole
	const int kuSommetParSelecteur=1;
	int bBiparti,bInformer=kF;
	int uC,nCas,uE,nSelecteur,nSommet,sYamont,sYaval,sZ;
	if (bInformer) Appel0("bGrapheQuadripoleR");
		nSommet=nTest/10;
		Assert1("GrapheQuadripoleR0",nSommet>0);
		nCas=nTest%10;
		nSelecteur=2*nSommet;
		if (bInformer) tee("nSommet,nSelecteur",nSommet,nSelecteur);
		//générer les 2*nSommet pôles amont et aval
			GrapheSommer(pgG,+nSelecteur);
		//générer les quadripoles
			QuadripoleGenererEtageConnecteR(nSommet,bBoucler,kuHuit,nTest,pgG);//relie aussi les étages entre eux
			if (0) GrapheVoir(pgG,sC4("Graphe quadripolé de dimension ",sEnt(nSommet),",restriction n°",sEnt(nCas)));
			if (bInformer) te("Sommets dédiés quadripôles",pgG->nSommetEnTout-nSelecteur);
			if (bInformer) GrapheVoir(pgG,"Graphe cliqué étagé biparti étoilé non connecté");
		//connecter les sélecteurs au reste du graphe
			for (uC=1;uC<=nSommet;uC++){//itère sur les colonnes
				sYamont=2*(uC-1)*kuSommetParSelecteur+1;//pôle amont
				sYaval=sYamont+kuSommetParSelecteur;//pôle aval
				if (bInformer) printf("Pôles nord et sud:%d,%d.\n",sYamont,sYaval);
				for (sZ=nSelecteur+kuHuit*(uC-1),uE=1;uE<=nSommet;uE++){//itère sur les étages
					if (bInformer) printf("(sX,pôle nord):      (%2d,%2d)\n",sZ+3,sYamont);
					if (bInformer) printf("(sX,pôle sud):       (%2d,%2d)\n",sZ+6,sYaval);
					if (bBoucler) GrapheAreter2(pgG,sZ+3,sYamont,coRouge,coBleu);//{coAlphA,coJaune,coRouge,coBleu,coVert,coOrange,coNoir,coOmegA}
					else GrapheArquer1(pgG,sZ+3,sYamont,coJaune);
					if (bBoucler) GrapheAreter2(pgG,sZ+6,sYaval,coRouge,coBleu);
					else GrapheArquer1(pgG,sZ+6,sYaval,coJaune);
					sZ+=kuHuit*nSommet;//ajoute un étage
				}
			}
		//fermer le circuit source-trappe APRES
			if (bInformer) tee("fermeture nSommet0,nSelecteur+1",pgG->nSommetEnTout,nSelecteur+1);
			GrapheArquer1(pgG,pgG->nSommetEnTout,nSelecteur+1,coVert);//coNoir à voir
		if (bInformer) GrapheVoir(pgG,"***********Graphe quadripolé avec sélecteurs");
		Assert1("GrapheQuadripoleR1",pgG->nSommetEnTout<knLigneLiM);
		bBiparti=bGrapheBiparti(pgG);
	if (bInformer) Appel1("bGrapheQuadripoleR");
	return(bBiparti);
}//bGrapheQuadripoleR

void ListeVoiR(int uListe[]){
	//affiche les uListe[0] éléments de uListe[]
	int uE,nEffectif;
	nEffectif=uListe[0];
	if (nEffectif>0){
		for (printf("Liste (%s):",sPluriel(uListe[0],"élément")),uE=1;uE<=nEffectif;uE++){
			printf("%d",uListe[uE]);
			if (uE<nEffectif)
				printf(",");
		}
	}
	else printf("Liste vide");
	printf(".\n");
}//ListeVoiR

void MatriceAdditionner(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	int uC,uL;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			(*ppmC)->Mat[uL][uC]=pmA->Mat[uL][uC]+pmB->Mat[uL][uC];
}//MatriceAdditionner

void MatriceAffecteR(iMatrice* pmA,int bVoir){
	//affecte pmA avec des 0,1 et 2 —matrice destinée au problème des tours ou des tours-tours
	#define knLigneMax 8
	char *sMatrice[1+knLigneMax];
	const int knPas=5;//nombre total de caractères disponibles pour spécifier l'état suivant ds la i-ième ligne de texte sAEF[ligne i]
	int uL,uC;
	if (bVoir) Appel0("MatriceAffecteR");
		for (uL=1;uL<=knLigneMax;uL++)
			sMatrice[uL]=malloc(knPas*(1+knLigneMax));//pas de free plus bas, mais cette routine n'est appelée qu'une fois
	    //classes:    $  0..9  AZaz  .    ;  operH blc autre
		sMatrice[ 1]="    0    0    2    0    2    0    2    0";
		sMatrice[ 2]="    0    0    0    2    0    2    0    2";
		sMatrice[ 3]="    2    0    0    0    0    0    0    1";
		sMatrice[ 4]="    0    2    0    0    1    0    1    0";
		sMatrice[ 5]="    2    0    0    1    0    1    0    0";
		sMatrice[ 6]="    0    2    0    0    1    0    1    0";
		sMatrice[ 7]="    2    0    0    1    0    1    0    1";
		sMatrice[ 8]="    0    2    1    0    0    0    1    0";
		for (uL=1;uL<=pmA->nLigne;uL++){
			for (uC=1;uC<=pmA->nColonne;uC++){
				sscanf(sMatrice[uL]+knPas*(uC-1),"%ld\n",&(pmA->Mat[uL][uC]));
				//if (pmA->Mat[uL][uC]==1) pmA->Mat[uL][uC]=0;
				if (bVoir)
					printf("[%2d,%2d]=%2ld ",uL,uC,pmA->Mat[uL][uC]);
			}
			if (bVoir)
				printf("\n");
		}
		if (bVoir) MatriceVoir("MatriceAffecteR finale",pmA);
	if (bVoir) Appel1("MatriceAffecteR");
}//MatriceAffecteR

void MatriceAllouher(oMatrice **ppmoA,enum eMatriceType maType){
	Appel0("MatriceAllouher");
	ppmoA=malloc(sizeof(oMatrice));
	(*ppmoA)->nLigne=knLigneMaX;
	(*ppmoA)->nColonne=knColonneMaX;
	(*ppmoA)->nSecante=0;
	(*ppmoA)->typ=maType;
	Appel1("MatriceAllouher");
	//MatriceRazer(ppmA);
}//MatriceAllouher

void MatriceAllouher1(oMatrice **ppmoA,enum eMatriceType maType,int nDimension){
	Appel0("MatriceAllouher1");
		te("nDimension",nDimension);
		ppmoA=(oMatrice **) malloc(sizeof(oMatrice));
		te("malloc fini",(*ppmoA)->nLigne);
		(*ppmoA)->nLigne=nDimension;
		(*ppmoA)->nColonne=nDimension;
		(*ppmoA)->nSecante=0;
	Appel1("MatriceAllouher1");
}//MatriceAllouher1

void MatriceAllouher2(oMatrice **ppmoA,enum eMatriceType maType,int nLigneEnTout,int nColonneEnTout){
	MatriceAllouher(ppmoA,maType);
	(*ppmoA)->nLigne=nLigneEnTout;
	(*ppmoA)->nColonne=nColonneEnTout;
}//MatriceAllouher2

void MatriceAllouer(iMatrice **ppmA){
	*ppmA=malloc(sizeof(iMatrice));
	(*ppmA)->nLigne=knLigneMaX;
	(*ppmA)->nColonne=knColonneMaX;
	(*ppmA)->nSecante=0;
	MatriceRazer(ppmA);
}//MatriceAllouer

void MatriceAlloueR0(iMatrice **ppmA,int nLigne,int nColonne,int nSecante){
	Assert3("MatriceAlloueR0",bCroit(0,nLigne,knLigneMaX),bCroit(0,nColonne,knColonneMaX),nSecante<=iMin(nLigne,nColonne));
	*ppmA=malloc(sizeof(iMatrice));
	(*ppmA)->nLigne=nLigne;
	(*ppmA)->nColonne=nColonne;
	(*ppmA)->nSecante=nSecante;
	MatriceRazer(ppmA);
}//MatriceAlloueR0

void MatriceAllouer1(iMatrice **ppmCarreh,int nDimension){
	Assert1("MatriceAllouer1",nDimension>=0);
	MatriceAllouer(ppmCarreh);
	(*ppmCarreh)->nLigne=(*ppmCarreh)->nColonne=nDimension;
}//MatriceAllouer1

void MatriceAllouer2(iMatrice **ppmA,int nLigneEnTout,int nColonneEnTout){
	Assert2("MatriceAllouer2",nLigneEnTout>=0,nColonneEnTout>=0);
	MatriceAllouer(ppmA);
	(*ppmA)->nLigne=nLigneEnTout;
	(*ppmA)->nColonne=nColonneEnTout;
}//MatriceAllouer2

void MatriceAlloueR2(yMatricE **ppmA){
	*ppmA=malloc(sizeof(yMatricE));
	(*ppmA)->nLigne=knLigneMaX;
	(*ppmA)->nColonne=knColonneMaX;
	MatriceRazer2(ppmA);
}//MatriceAlloueR2

void MatRIceAllouer(riMatrice **ppmK){
	*ppmK=malloc(sizeof(riMatrice));
	(*ppmK)->nLigne=knLigneMaX;
	(*ppmK)->nColonne=knColonneMaX;
	MatRIceRazeR(ppmK);
}//MatRIceAllouer

void MatRIceAllouer1(riMatrice **ppmKarreh,int nDimension){
	Assert1("MatRIceAllouer1",nDimension>=0);
	MatRIceAllouer(ppmKarreh);
	(*ppmKarreh)->nLigne=(*ppmKarreh)->nColonne=nDimension;
}//MatRIceAllouer1

void MatRIceAllouer2(riMatrice **ppmK,int nLigneEnTout,int nColonneEnTout){
	Assert2("MatRIceAllouer2",nLigneEnTout>=0,nColonneEnTout>=0);
	MatRIceAllouer(ppmK);
	(*ppmK)->nLigne=nLigneEnTout;
	(*ppmK)->nColonne=nColonneEnTout;
}//MatRIceAllouer2

void MatriceAllouheR(dMatricE **ppmA){
	*ppmA=malloc(sizeof(dMatricE));
	(*ppmA)->nLigne=knLigneMaX;
	(*ppmA)->nColonne=knColonneMaX;
	MatriceRazheR(ppmA);
}//MatriceAllouheR

void MatriceAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bMatriceAmorceR=kV;
	bMatriceOuvertE=kF;
	PremierTabuleR();
}//MatriceAMORCER

int bMatriceAntiSymetriquE(iMatrice *pmA){
	//pmA->Mat[uL][uC]==-pmA->Mat[uC][uL] (donc diagonale principale nulle)
	int uL,uC;
	int bAntiSymetrique;
	Appel0("bMatriceAntiSymetriquE");
		MatriceVoir("bMatriceAntiSymetriquE",pmA);
		for (bAntiSymetrique=bDiagonaleNullE(pmA),tb("bAntiSymetrique",bAntiSymetrique),uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<uL;uC++){
				tee("uL,uC",uL,uC);
				tee("pmA->Mat[uL][uC]+pmA->Mat[uC][uL]",pmA->Mat[uL][uC],pmA->Mat[uC][uL]);
				bAntiSymetrique=bAntiSymetrique && (pmA->Mat[uL][uC]+pmA->Mat[uC][uL]==0);
				if (pmA->Mat[uL][uC]+pmA->Mat[uC][uL]!=0)
					teeee("pas antisym",uL,uC,pmA->Mat[uL][uC],pmA->Mat[uC][uL]);
				tb("bAntiSymetrique",bAntiSymetrique);
			}
		Assert1("bMatriceAntiSymetriquE",bBool(bAntiSymetrique));
	Appel1("bMatriceAntiSymetriquE");
	return(bAntiSymetrique);
}//bMatriceAntiSymetriquE

void MatriceAntisymetriser(iMatrice **ppmC){
	int uC,uL;
	for (uL=1;uL<=(*ppmC)->nLigne;uL++){
		(*ppmC)->Mat[uL][uL]=0;
		for (uC=1;uC<uL;uC++)
			(*ppmC)->Mat[uL][uC]=-(*ppmC)->Mat[uC][uL];
	}
}//MatriceAntisymetriser

void MatRIceAntisymetriser(riMatrice **ppmK){
	int uC,uL;
	for (uL=1;uL<=(*ppmK)->nLigne;uL++){
		(*ppmK)->Mat[uL][uL]=riAff(0,0);
		for (uC=1;uC<uL;uC++)
			(*ppmK)->Mat[uL][uC]=riAff(-(*ppmK)->Mat[uC][uL].r,-(*ppmK)->Mat[uC][uL].i);
	}
}//MatRIceAntisymetriser

void MatriceApparieR(graf *pgG,int bSimple,iMatrice *pmA){
	//apparie tous les sommets X et Y de la matrice qui vérifient pgG->aDeh[sX]=sY (et pgG->aDeh[sY]=sX par construction de pgG->aDeh[]).
	const int bApparier=kV;
	int uL,uC,tEchanger,coC;
	int ipP,nCoc;
	int sPred,sSuc,sX,sY;
	int nPermutation[knLigneLiM];
	iMatrice *pmB;
	Assert3("MatriceApparieR1",bPair(pgG->nSommetEnTout),bPair(pmA->nLigne),pmA->nLigne==pmA->nColonne);
	//VecteurVoir("pgG->aDeh",pgG->aDeh,1,pgG->nSommetEnTout);
	pgG->aArcTo[0]=pgG->nSommetEnTout;
	GrapheInverser(pgG);
	//Assert1("MatriceApparieR2",bPermutatioN(pgG->aDeh));
	//nPermutation[]=pile des paires de sommets appariés, et effectif en 0.
		VecteurRazer(nPermutation,1,pgG->nSommetEnTout);
		for (ipP=0,coC=coAlpha+1;coC<coOmega;coC++)
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (pgG->sPer[sX]==coC){
					sY=abs(pgG->aArcTo[sX]);
					Assert2("MatriceApparieR3",sY>0,abs(pgG->aArcTo[sY])==sX);
					if (sX<sY){
						if (kF && coC==coNoir){
							//sPred=sGraphePredecesseur(pgG,sX);
							sPred=pgG->sKus[pgG->aDeh[sX]];
							sSuc=pgG->sSuk[pgG->aHed[sY]];
							teeee("sX,sY,sPred,sSuc",sX,sY,sPred,sSuc);
							nPermutation[++ipP]=sPred;
							nPermutation[++ipP]=sSuc;
							nPermutation[++ipP]=sX;
							nPermutation[++ipP]=sY;
						}else {
							nPermutation[++ipP]=sX;
							nPermutation[++ipP]=sY;
						}
						//printf("dans MatriceApparieR: Paire,sX,sY et couleur %2d,%2d,%2d %s %s\n",ipP/2,sX,sY,sTab(coC),sCouleuR[coC]);
					}
				}
		te("ipP",ipP);
		if (bApparier)
			for (coC=coC=coAlpha+1;coC<coOmega;coC++){
				for (nCoc=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					nCoc+=(pgG->sPer[sX]==coC);
				if (nCoc>0)
					for (printf("%s: ",sItem(sCoulheurNoM,coC)),sX=1;sX<=pgG->nSommetEnTout || bPrint(".");sX++)
						if (pgG->sPer[sX]==coC)
							printf("%2d%s",sX,(--nCoc>0)? ",": "");
			}
		nPermutation[0]=ipP;
	//te("nPermutation[0]",nPermutation[0]);
	if (1){
		VecteurVoir("nPermutation",nPermutation,1,pgG->nSommetEnTout);
		for (uL=1;uL<=pmA->nLigne;uL++)
			pmA->Mat[uL][0]=pmA->Mat[0][uL]=nPermutation[uL];
		if(0) VecteurVoir("nPermutation",nPermutation,1,nPermutation[0]);
		Assert1("MatriceApparieR5",bPermutatioN(nPermutation));
		MatriceAlloueR0(&pmB,pmA->nLigne,pmA->nLigne,pmA->nLigne);
		//pmB:=pmA
			for (uL=1;uL<=pmA->nLigne;uL++)
				for (uC=1;uC<=pmA->nColonne;uC++)
					pmB->Mat[uL][uC]=pmA->Mat[uL][uC];
			//MatriceVoir("Matrice pmB copie de pmA",pmB);
		//pmA soit razé
			for (uL=1;uL<=pmA->nLigne;uL++)
				for (uC=1;uC<=pmA->nColonne;uC++)
					pmA->Mat[uL][uC]=0;
		//pmA soit la copie de pmB permutée en lignes et colonnes selon nPermutation[]
			for (uL=1;uL<=pmA->nLigne;uL++){
				for (uC=1;uC<=pmA->nColonne;uC++)
					pmA->Mat[uL][uC]=pmB->Mat[nPermutation[uL]][nPermutation[uC]];
			}
			/*for (uL=1;uL<=pmA->nLigne;uL++){
				for (uC=1;uC<=pmA->nColonne;uC++)
					pmA->Mat[uL][uC]=pmB->Mat[nPermutation[uL]][uC];
			}*/
			if (0) MatriceVoir("Matrice pmA permutée",pmA);
	}
	//pmA->nSecante=pmA->nLigne;
	//MatriceVoir("Matrice appariée non redressée associée à pgG",pmA);
	if (0){//échanger au besoin les paires de colonnes consécutives afin que les 1 des carrés 2x2 soient en diagonale principale
		for (uC=1;uC<pmA->nColonne;uC+=2){
			for (tEchanger=0,uL=1;uL<pmA->nLigne && tEchanger==0;uL+=2){
				if (abs(pmA->Mat[uL][uC+1])==1 && abs(pmA->Mat[uL+1][uC])==1)
					tEchanger=+1;
				if (abs(pmA->Mat[uL][uC])==1 && abs(pmA->Mat[uL+1][uC+1])==1)
					tEchanger=-1;
			}
			Assert1("MatriceApparieR7",sY>0);
			if (tEchanger>0){
				//tee("échanger les colonnes",uC,uC+1);
				for (uL=1;uL<pmA->nLigne;uL++)
					EntyerEchanger(&pmA->Mat[uL][uC],&pmA->Mat[uL][uC+1]);
				EntierEchanger(&nPermutation[uC],&nPermutation[uC+1]);
			}
		}
		for (uC=1;uC<=pmA->nLigne;uC++)
			pmA->Mat[0][uC]=nPermutation[uC];
	}
	Assert1("MatriceApparieR9",bPermutatioN(nPermutation));
	//NB à ce point,les permutations en lignes et en colonnes diffèrent en général (vu li-1).
}//MatriceApparieR

void MatriceBander(int iBande,iMatrice **ppmC){
	//ajoute une diagonale de 1 sur la bande iBande (=0:diagonale principale,+1:diag suivante,-1:précédente
	int uC,uL;
	Assert1("MatriceBander",bCroit(-(*ppmC)->nLigne,iBande,+(*ppmC)->nLigne));
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			if (uC-uL==iBande)
				(*ppmC)->Mat[uL][uC]=1;
		}
}//MatriceBander

void MatriceCanoniser(int maOu,iMatrice **ppmC){
	int uL,uC;
	for (uL=1;uL<=(*ppmC)->nLigne;uL++)
		for (uC=1;uC<=(*ppmC)->nLigne;uC++)
			if (maOu==maTout || uL>uC && maOu==maInferieur || uL<uC && maOu==maSuperieur)
				(*ppmC)->Mat[uL][uC]=10*uL+uC;
}//MatriceCanoniser

void MatriceFibonaccier(int nCoteh,iMatrice **ppmC){
	//rend une matrice carrée de coté nCoteh dont le déterminant est un nombre de la suite de Fibonacci.
	MatriceAllouer1(ppmC,nCoteh);
		MatriceBander(-1,ppmC);
		MatriceFoisser(-1,ppmC);
		MatriceBander(0,ppmC);
		MatriceBander(+1,ppmC);
		(*ppmC)->Mat[1][1]=0;
}//MatriceFibonaccier

void MatriceCarrehNuL(int nValeur){
	//Génère une matrice carrée dont le carré et nul,calcule ce carré et affiche la matrice originale et son carré.
	iMatrice *pmA;
	MatriceAllouer1(&pmA,2);
		pmA->Mat[1][1]=+nValeur;
		pmA->Mat[2][1]=-nValeur;
		MatriceVoir("pmA",pmA);
		MatriceCarreR(&pmA);
		MatriceVoir("Carré de pmA",pmA);
		Assert1("MatriceCarrehNuL",bMatriceNullE(pmA));
	free(pmA);
}//MatriceCarrehNuL

void MatriceCarreR(iMatrice **ppmA){
	//Génère une matrice carrée dont le carré est nul,calcule ce carré et affiche la matrice originale et son carré.
	int uI,uJ,uK;
	iMatrice *pmC;
	Assert1("MatriceCarreR",(*ppmA)->nLigne==(*ppmA)->nColonne);
	MatriceAllouer1(&pmC,(*ppmA)->nLigne);
		//MatriceVoir("ppmA",*ppmA);
		for (uI=1;uI<=pmC->nLigne;uI++)
			for (uJ=1;uJ<=pmC->nLigne;uJ++)
				for (uK=1;uK<=pmC->nLigne;uK++)
					pmC->Mat[uI][uJ]=(*ppmA)->Mat[uI][uK]*(*ppmA)->Mat[uK][uJ];
		//MatriceVoir("pmC",pmC);
		MatriceDupliquer(pmC,*ppmA);
		//MatriceVoir("ppmA",*ppmA);
	free(pmC);
}//MatriceCarrehNuL

void MatriceCartesier(iMatrice *pmA,iMatrice *pmB,int uH,iMatrice **ppmC){
	//multiplie le uH-ième vecteur colonne de pmA par le uH-ième vecteur ligne de pmB
	int uC,uL;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nLigne;uC++)
			(*ppmC)->Mat[uL][uC]=pmA->Mat[uL][uH]*pmB->Mat[uH][uC];
}//MatriceCartesier

void MatriceCircuiter(int iBande,iMatrice **ppmC){
	//ajoute circulairt une diagonale de 1 sur la bande iBande (=0:diagonale principale,+1:diag suivante,-1:précédente
	int uC,uL;
	Assert1("MatriceCircuiter",bCroit(-(*ppmC)->nLigne,iBande,+(*ppmC)->nLigne));
	for (uL=1;uL<=(*ppmC)->nLigne;uL++)
		for (uC=1;uC<=(*ppmC)->nColonne;uC++){
			if (uL+iBande==uC || uL-(*ppmC)->nLigne+iBande==uC)
				(*ppmC)->Mat[uL][uC]=1;
		}
}//MatriceCircuiter

void MatriceConfigureR(long zConfigurationVoulue,iMatrice **ppmC){
	long zConfiguration;
	int uBit,uL,uC;
	zConfiguration=zConfigurationVoulue;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			uBit=zConfiguration%2;
			(*ppmC)->Mat[uL][uC]=uBit;
			zConfiguration=zConfiguration/2;
		}
}//MatriceConfigureR

void MatriceConstitueR(long zConfigurationVoulue,iMatrice **ppmC){
	//configure la matrice hors diagonale principale selon zConfigurationVoulue;la diagonale est à 0 sauf le dernier terme
	long zConfiguration;
	int uBit,uL,uC;
	zConfiguration=zConfigurationVoulue;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			if (uL!=uC || uL==knLigneMaX){
				uBit=zConfiguration%2;
				(*ppmC)->Mat[uL][uC]=uBit;
				zConfiguration=zConfiguration/2;
			};
		}
}//MatriceConstitueR

int bMatriceContient(iMatrice *pmA,int iValeur){
	int uC,bContient,uL;
	for (bContient=kF,uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			bContient=bContient || (iValeur==pmA->Mat[uL][uC]);
	return(bContient);
}//bMatriceContient

void MatriceConvertir(iMatrice *pmLu,oMatrice *pmoEcrit){
	//convertit la matrice pmLu en matrice d'objets de type pmoEcrit->typ
	int uL,uC,iValeur;
	objet Ob;
	for (uL=1;uL<=pmLu->nLigne;uL++)
		for (uC=1;uC<=pmLu->nColonne;uC++){
			iValeur=pmLu->Mat[uL][uC];
			Ob=pmoEcrit->Mat[uL][uC];
			switch (pmoEcrit->typ){
				case matEntier:Ob.ent=iValeur;break;
				case matRationnel:Ob.rat.num=iValeur;Ob.rat.den=0;break;
				case matComplexe:Ob.cplx=riAff(iValeur,0);break;
				case matReel:Ob.reel=iValeur;break;
				case matRect:NbAffecter(iValeur,&Ob.mm.q11);NbAffecter(0,&Ob.mm.q12);NbAffecter(0,&Ob.mm.q21);NbAffecter(0,&Ob.mm.q22);break;
			}
		};
}//MatriceConvertir

void MatriceCoupler(iMatrice *pmA,int *pbParfait,int *pbOptimal){
	//rend le nombre maximal de couplages dans la matrice sommet sommet pmA associée à un graphe (ie un élément représente un arc).
	//cf algo Hongrois, Pb affectations, et carrés latins,Pb des tours.
	const int knCapaciteMinimaleNulle=0;
	const int kuCapaciteMaximale=1;
	const int kuPoidsPrioritaire=2;
	const int kuPoidsStandard=kE3;
	const int kuPoidsMaximal=kE1;
	int nArc,sL,uL,sC,uC;
	int nNegativeh,bParfait,cPasse,nPoids,nArcPrioritaire,nPoidsMin,nPris,nSommet,nSommetInterfacable,bSuffisant,sX;
	graf *pgG;
	int sColonne[1+pmA->nColonne];
	int sLigne[1+pmA->nLigne];
	int uMatriceIndex[kuGrapheArcLim];//excessif
	//Appel0("MatriceCoupler");
		if (!k1Voir)
			MatriceVoir("MatriceCoupler INITIALE",pmA);
		Assert1("MatriceCoupler78",bMatricePositive(pmA));
		//sLigne[uL],sColonne[uC]:= un sommet qui identifie la ligne uL, la colonne uC:
			for (uL=1;uL<=pmA->nLigne;uL++)
				sLigne[uL]=uL;
			for (uC=1;uC<=pmA->nColonne;uC++)
				sColonne[uC]=pmA->nLigne+uC;
			//VecteurVoir1("sColonne",sColonne,1,pmA->nColonne);
		nSommetInterfacable=pmA->nLigne+pmA->nColonne;
		GrapheCreer0(&pgG,kV);
//te("nSommetInterfacable ds MatriceCoupler",nSommetInterfacable);
			for (nArcPrioritaire=0,cPasse=0;cPasse<=1;cPasse++){
				if (cPasse==1){//nSommet,calculé à cPasse==0,est le nombre total de sommets de pgG
					bSuffisant=(nSommet+10<kuGrapheSommetLim);
					printf("MatriceCoupler: Construction d'un graphe de flots à 2A+2S=%s...\n",sPluriel(nSommet,"sommet"));
					Assert1("MatriceCoupler TROP DE SOMMETS",bSuffisant);
					//pgG (déjà créé) contienne nSommet sommets et aucun arc: 
						pgG->nSommetEnTout=nSommet;
						for (sX=1;sX<=pgG->nSommetEnTout+1;sX++)
							pgG->aHed[sX]=1;
						pgG->nArcEnTout=0;
				}
				for (nArc=0,nSommet=nSommetInterfacable,uL=1;uL<=pmA->nLigne;uL++)
					for (uC=1;uC<=pmA->nColonne;uC++)
						if (pmA->Mat[uL][uC]>0){
							nArc++;
							sL=++nSommet;
							sC=++nSommet;
							if (0 && cPasse==1)
								teeee("sLigne[uL],sL,sC,sColonne[uC]",sLigne[uL],sL,sC,sColonne[uC]);
							uMatriceIndex[sL]=uL;
							uMatriceIndex[sC]=uC;
							if (cPasse==1){
								Assert2("bMatriceCoupler1",sLigne[uL]<=pgG->nSommetEnTout,sL<=pgG->nSommetEnTout);
								GrapheArquer3(pgG,sLigne[uL],sL,knCapaciteMinimaleNulle,kuCapaciteMaximale,kuPoidsStandard);
								Assert2("bMatriceCoupler2",sL<=pgG->nSommetEnTout,sC<=pgG->nSommetEnTout);
								nPoids=kuPoidsStandard;
								if (pmA->Mat[uL][uC]==kuPoidsPrioritaire){
									//teeee("*******************POIDS LOURD uL,uC,sL,sC",uL,uC,sL,sC);
									nPoids=kuPoidsMaximal;
									nArcPrioritaire++;
								}
								GrapheArquer3(pgG,sL,sC,knCapaciteMinimaleNulle,kuCapaciteMaximale,nPoids);
								Assert2("bMatriceCoupler3",sC<=pgG->nSommetEnTout,sColonne[uC]<=pgG->nSommetEnTout);
								GrapheArquer3(pgG,sC,sColonne[uC],knCapaciteMinimaleNulle,kuCapaciteMaximale,kuPoidsStandard);
							}
						}
				//te("nArc ds MatriceCoupler",nArc);
			}//cPasse
			te("nArcPrioritaire",nArcPrioritaire);
			if (0)
				GrapheVoir0(pgG,"Réseau de transport hors source et trappe",grCout);
			GrapheSymetriser(pgG);
			//négativer pgG->aHed[sX] lorsque sX n'est pas connectable à une source ou une trappe ——pour CouplageOptimiser
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX]=iSignePres(nSommetInterfacable<sX,pgG->aHed[sX]);
			//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout);
//t("5");
			bParfait=bCouplageParfait(pgG);//qui appellera en interne bCouplagePonderehOptimiseR car pgG est biparti.
//t("6");
			//VecteurVoir("pgG->aDeh",pgG->sPer[],1,pgG->nSommetEnTout);
			//négativer les élémts de pmA qui figurent ds le couplG. Ils contiennent une copie du couplage résultant ds pgG->sPer[].
				Assert1("MatriceCoupler32",bMatricePositive(pmA));
				for (nNegativeh=0,nPoidsMin=0,nPris=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->sPer[sX]>0){
						uL=uMatriceIndex[sX];uC=uMatriceIndex[pgG->sPer[sX]];
						if (pmA->Mat[uL][uC]!=0){
							if (0 && uL<uC)
								printf("MatriceCoupler:Sommet n°%2d %s\n",++nPris,sCouple(uL,uC));
							if (pmA->Mat[uL][uC]==kuPoidsPrioritaire)
								nPoidsMin++;
							if (sX<pgG->sPer[sX]){
								pmA->Mat[uL][uC]=-pmA->Mat[uL][uC];
								nNegativeh++;
							}
						}
					}
				//tee("pmA->nLigne,nNegativeh",pmA->nLigne,nNegativeh);
				Assert1("MatriceCoupler48",nNegativeh==pmA->nLigne);
			//tb("nPoidsMin",nPoidsMin);
			//for (uL=1;uL<=pmA->nLigne;uL++) VecteurVoir("pmA[uL]",pmA->Mat[uL],1,pmA->nLigne);
//t("7");
			if (k1Voir)
				MatriceVoir("MatriceCoupler FINALE",pmA);
		GrapheCreer0(&pgG,kF);
	//Appel1("MatriceCoupler");
	*pbParfait=bParfait;
	te("nPoidsMin",nPoidsMin);
	*pbOptimal=(nPoidsMin==2*3);
	tee("MatriceCoupler:*pbParfait,*pbOptimal",*pbParfait,*pbOptimal);
}//MatriceCoupler

void MatriceCulminer(int uCulminant,iMatrice **ppmC){
	//Mat[uL][uC]=uCulminant-Mat[uL][uC]
	int uC,nEffectif,uL;
	nEffectif=(*ppmC)->nLigne;
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++)
			(*ppmC)->Mat[uL][uC]=uCulminant-(*ppmC)->Mat[uL][uC];
}//MatriceCulminer

void MatriceCulminerAuMieuX(iMatrice *pmC){
	//recherche le culminant qui produit le plus petit le ppcm des éléments horc diagonale de ppmC
	int uC,nEffectif,uL;
	int uCulminant,uCulminantMin,nMaximum;
	long zDiviseurMin,zDiviseur;
	nEffectif=pmC->nLigne;
	for (nMaximum=0,uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++)
			nMaximum=iMax(nMaximum,pmC->Mat[uL][uC]);
	//te("Plus grand élément de la Matrice",nMaximum);
	zDiviseurMin=kxLongintMax;
	for (uCulminant=nMaximum+1;uCulminant<=5000;uCulminant++){
		//te("uCulminant",uCulminant);
		zDiviseur=zMatriceCulminerAuMieuX(uCulminant,pmC);
		if (zDiviseur<0)
			t("zDiviseur<0");
		if (zDiviseurMin>zDiviseur){
			zDiviseurMin=zDiviseur;
			uCulminantMin=uCulminant;
			tee("Culminant optimal et ppcm associé",uCulminantMin,zDiviseurMin);
		}
	}
}//MatriceCulminerAuMieuX

long zMatriceCulminerAuMieuX(int uCulminant,iMatrice *pmC){
	//rend le ppcm des éléments situés en haut et à droite de la diagonale principale, ou kxLongintMax si hors longint
	int uC,nEffectif,uL,bQuitter;
	long zChallenger,xPpcm;
	nEffectif=pmC->nLigne;
	//te("uCulminant",uCulminant);
	for (bQuitter=kF,xPpcm=1,uL=1;(uL<=nEffectif) && (!bQuitter);uL++)
		for (uC=uL+1,1;(uC<=nEffectif) && (!bQuitter);uC++){
			zChallenger=uCulminant-pmC->Mat[uL][uC];
			//tee("xPpcm et zChallenger",xPpcm,zChallenger);
			xPpcm=zPpcm(xPpcm,zChallenger);
			if (xPpcm<=0)
				bQuitter=kV;
		}
	//te("nPpcm",zPpcm);
	if (bQuitter)
		xPpcm=kxLongintMax;
	else te("Culminant à ppcm calculable",uCulminant);
	return(xPpcm);
}//zMatriceCulminerAuMieuX

void MatriceDecaler(int bLigne,int nDecalageVersLeHautSiPositifEtVersLeBasSinon,int nIndexMin,int nIndexMax,iMatrice **ppmA){
	int uC,uL,nDecalage=nDecalageVersLeHautSiPositifEtVersLeBasSinon,uCmin,uCmax,uLmin,uLmax,nC0,nL0;
	iMatrice *pmCopie;
	int nBorneSup=(bLigne)? (*ppmA)->nLigne: (*ppmA)->nColonne;
	Assert2("MatriceDecaler",nDecalage>=0,bCroit4(1,nIndexMin,nIndexMax,nBorneSup));//A FAIRE POUR nDecalage NÉGATIF
	if (nDecalage!=0){
		MatriceAllouer(&pmCopie);
			MatriceDupliquer(*ppmA,pmCopie);
			if (bLigne){
				//décaler vers le haut
					uLmin=iSup(1,nIndexMin);
					uLmax=iInf((*ppmA)->nLigne,nIndexMax)-nDecalage;
					//tee("uLmin,uLmax",uLmin,uLmax);
					for (uL=uLmin;uL<=uLmax;uL++)
						for (uC=0;uC<=(*ppmA)->nColonne;uC++)
							(*ppmA)->Mat[uL][uC]=(*ppmA)->Mat[uL+nDecalage][uC];
				//recopier plus bas l'ancienne partie haute
					uLmin=uL;//te("uL",uL);
					uLmax=(*ppmA)->nLigne;
					//tee("uLmin,uLmax",uLmin,uLmax);
					for (nL0=nIndexMin,uL=uLmin;uL<=uLmax;nL0++,uL++)
						for (uC=0;uC<=(*ppmA)->nColonne;uC++)
							(*ppmA)->Mat[uL][uC]=pmCopie->Mat[nL0][uC];
			} else {
				//décaler vers la gauche
					uCmin=iSup(1,nIndexMin);
					uCmax=iInf((*ppmA)->nColonne,nIndexMax)-nDecalage;
					//tee("uCmin,uCmax",uCmin,uCmax);
					for (uC=uCmin;uC<=uCmax;uC++)
						for (uL=0;uL<=(*ppmA)->nLigne;uL++)
							(*ppmA)->Mat[uL][uC]=(*ppmA)->Mat[uL][uC+nDecalage];
				//recopier à droite toute l'ancienne partie gauche
					uCmin=uC;//te("uC",uC);
					uCmax=(*ppmA)->nColonne;
					//tee("uCmin,uCmax",uCmin,uCmax);
					for (nC0=nIndexMin,uC=uCmin;uC<=uCmax;nC0++,uC++)
						for (uL=0;uL<=(*ppmA)->nLigne;uL++)
							(*ppmA)->Mat[uL][uC]=pmCopie->Mat[uL][nC0];
			}
		free(pmCopie);
	}
}//MatriceDecaler

void MatriceDedoubleR(iMatrice *pmA){
	int uC,uL;
	iMatrice *pmB,*pmC;
	MatriceAlloueR0(&pmB,pmA->nLigne/2,pmA->nColonne/2,pmA->nColonne/2);
		MatriceAlloueR0(&pmC,pmA->nLigne/2,pmA->nColonne/2,pmA->nColonne/2);
			//pmB:=recto de pmA
				for (uL=1;uL<=pmB->nLigne;uL++)
					for (uC=1;uC<=pmB->nColonne;uC++){
						if (pmA->Mat[2*uL-1][2*uC-1]==2)
							pmB->Mat[uL][uC]=2;
						if (pmA->Mat[2*uL-1][2*uC+0]==1)
							pmB->Mat[uL][uC]=1;
					}
			//pmC:=verso de pmA
				for (uL=1;uL<=pmC->nLigne;uL++)
					for (uC=1;uC<=pmC->nColonne;uC++){
						if (pmA->Mat[2*uL+0][2*uC+0]==2)
							pmC->Mat[uL][uC]=2;
						if (pmA->Mat[2*uL+0][2*uC-1]==1)
							pmC->Mat[uL][uC]=1;
					}
		MatriceVoir("pmB",pmB);
		MatriceVoir("pmC",pmC);
}//MatriceDedoubleR

void MatriceDepermuter(iMatrice *pmA){
	int uC,uL;
	for (uL=1;uL<=pmA->nLigne;uL++)
		pmA->Mat[uL][0]=0;
	for (uC=1;uC<=pmA->nColonne;uC++)
		pmA->Mat[0][uC]=0;
	pmA->Mat[0][0]=0;
	//MatriceVoir("pmA dépermuté",pmA);
}//MatriceDepermuter

void MatriceDepuisGraphe(graf *pgG,int bIncidenceSinonCouleur,iMatrice **ppmMatriceDuGraphe){
	//si bIncidenceSinonCouleur est vrai,ppmMatriceDuGraphe[sX,sY]=1 ssi (sX,sY) est arc de pgG;sinon,affecte la couleur de l'arc.
	int aK,uL,sX,sY;
	//te("(*ppmMatriceDuGraphe)->nLigne",(*ppmMatriceDuGraphe)->nLigne);
	//VecteurVoir1("pgG->coulh,pgG->coulh,1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			(*ppmMatriceDuGraphe)->Mat[sX][sY]= (bIncidenceSinonCouleur)? 1: pgG->coulh[aK];
		}
	for (uL=1;uL<=(*ppmMatriceDuGraphe)->nLigne;uL++)
		(*ppmMatriceDuGraphe)->Mat[uL][0]=(*ppmMatriceDuGraphe)->Mat[0][uL]=uL;
	(*ppmMatriceDuGraphe)->Mat[0][0]=(*ppmMatriceDuGraphe)->nLigne;
}//MatriceDepuisGraphe

void MatRIceDepuisGraphe(graf *pgG,int bIncidenceSinonCouleur,riMatrice **ppmMatriceDuGraphe){
	//si bIncidenceSinonCouleur est vrai,ppmMatriceDuGraphe[sX,sY]=1 ssi (sX,sY) est arc de pgG;sinon,affecte la couleur de l'arc.
	int aK,uL,sX,sY;
	//te("(*ppmMatriceDuGraphe)->nLigne",(*ppmMatriceDuGraphe)->nLigne);
	//VecteurVoir1("pgG->coulh,pgG->coulh,1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			(*ppmMatriceDuGraphe)->Mat[sX][sY].r= (bIncidenceSinonCouleur)? 1: pgG->coulh[aK];
		}
	for (uL=1;uL<=(*ppmMatriceDuGraphe)->nLigne;uL++)
		(*ppmMatriceDuGraphe)->Mat[uL][0].r=(*ppmMatriceDuGraphe)->Mat[0][uL].r=uL;
	(*ppmMatriceDuGraphe)->Mat[0][0].r=(*ppmMatriceDuGraphe)->nLigne;
}//MatRIceDepuisGraphe

void MatriceEchafaudeR(int nSommet,int kbSimple){
	int uBaton,uCarreh,iDeterminant,iDeterminant0,iDeterminant1,nNom,nEtape,muSigne,nSommetPourEtoile,nTest;
	long yDeterminant;
	graf *pgG;
	iMatrice *pmA;
	Appel0("MatriceEchafaudeR");
		Assert1("MatriceEchafaudeR0",nSommet<=5);
		GrapheCreer0(&pgG,kV);
			if (kbSimple)
				GrapheEtireR(pgG,nTest=nSommet*10);
			else GrapheExtirpeR(pgG,nTest=nSommet*10);
			nSommet=nTest/10;
			if (0) GrapheVoir1(pgG,k1Couleur,"Graphe étiré à matricer");
			if (1) GrapheVoir(pgG,"Graphe étiré à matricer");
			if (0) te("nSommet",nSommet);
			if (pgG->nSommetEnTout>=knLigneLiM)
				tee("pgG->nSommetEnTout vs knLigneLiM",pgG->nSommetEnTout,knLigneLiM);
			Assert2("MatriceEchafaudeR2",pgG->nSommetEnTout<knLigneLiM,bGrapheBiparti(pgG));
			MatriceAlloueR0(&pmA,pgG->nSommetEnTout,pgG->nSommetEnTout,0);
				uBaton=nSommet*nSommet;
				nSommetPourEtoile=2*nSommet*(nSommet+1);
				//te("nSommetPourEtoile",nSommetPourEtoile);
				uCarreh=pgG->nSommetEnTout-nSommetPourEtoile;//nb total de sommets hors étoiles
			//teee("uBaton,uCarreh,kbSimple",uBaton,uCarreh,kbSimple);
				GrapheMatriceR(pgG,kbSimple,uBaton,uCarreh,&pmA);
				pmA->nSecante=pgG->nSommetEnTout;
				if (1) MatriceVoir("Matrice brute associée à pgG",pmA);
				if (0) iDeterminant0=yMatriceDeterminant(pmA);
				if (0) te("Déterminant obtenu par yMatriceDeterminant",iDeterminant0);
				if (1) MatriceApparieR(pgG,kbSimple,pmA);//apparie selon pgG->aDeh[]
				//pmA->nSecante=2*nSommet*nSommet;
				MatriceVoir("Matrice appariée associée à pgG",pmA);
				if (0) MatriceNettoyeR(pmA);
				pmA->nSecante=pmA->nLigne;
				if (0) MatriceVoir("Matrice appariée nettoyée associée à pgG",pmA);
				//GrapheConcocteR(pmA,nSommet);
				if (0) MatriceDedoubleR(pmA);


				if (0){ te("Déterminant 2 obtenu par yMatriceDeterminant",yMatriceDeterminant(pmA));
					iDeterminant1=yMatriceDeterminant(pmA);
					if (0) te("Déterminant 3 obtenu par yMatriceDeterminant",iDeterminant1);
					muSigne=(iDeterminant1==iDeterminant1)?1:-1;
				}
				pmA->nSecante=pgG->nSommetEnTout-uCarreh;
				//Assert1("MatriceEchafaudeR4",bMatriceAntiSymetriquE(pmA));
				//MatriceVoir("Matrice appariée finale",pmA);
				if (0){
					yDeterminant=muSigne*ySignatureCalculeR(pmA,k1Alterner,&nEtape);
					printf("Déterminant LABORIEUX par ySignatureCalculeR: %ld.\n",yDeterminant);
						if (yDeterminant<0)
							t("DÉTERMINANT NÉGATIF @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
				}
				if (0){
					iDeterminant=yMatriceDeterminant(pmA);te("Déterminant 4 obtenu par yMatriceDeterminant",iDeterminant);
				}
				if (0)
					bBof=muSigne*bMatriceSingulariseR(&pmA,&nNom,&nEtape);
			free(pmA);
		GrapheCreer0(&pgG,kF);
	Appel1("MatriceEchafaudeR");
}//MatriceEchafaudeR

int bMatriceEchangerPaire(int bLigne,int uA,int uB,int bVoir,iMatrice **ppmC){
	//échange réellement soit les lignes uA..uA+1 et uB..uB+1, soit les colonnes uA..uA+1 et uB..uB+1, de ppmC;actualise le vecteur de permutations
	int uL,uC;
	int bEchangerPaire=kF;
	int nModule0,nModule1;
	//Appel0("bMatriceEchangerPaire");
	Assert4("MatriceEchangerPairE1",bCroit(1,uA,(*ppmC)->nLigne),bCroit(1,uB,(*ppmC)->nLigne),uA!=uB,(*ppmC)->nLigne==(*ppmC)->nColonne);
	nModule0=nMatriceModulE(*ppmC);
	if (bVoir) MatriceVoir(sC2("AVANT bMatriceEchangerPaire n°",sEnt(uA)),*ppmC);
	//Assert1("MatriceEchangerPairE2",bLigne);
	if (bLigne){//échanger deux doublets de lignes
		if (kF) printf("Echange des doublets de lignes %d-%d et %d-%d.\n",uA,uA+1,uB,uB+1);
		//Assert2("MatriceEchangerPairE2",bImpair(uA),bImpair(uB));
		for (uC=1;uC<=(*ppmC)->nColonne;uC++)
			EntyerEchanger(&(*ppmC)->Mat[uA][uC],&(*ppmC)->Mat[uB][uC]);
		EntyerEchanger(&(*ppmC)->Mat[uA+0][0],&(*ppmC)->Mat[uB+0][0]);
		for (uC=1;uC<=(*ppmC)->nColonne;uC++)
			EntyerEchanger(&(*ppmC)->Mat[uA+1][uC],&(*ppmC)->Mat[uB+1][uC]);
		EntyerEchanger(&(*ppmC)->Mat[uA+1][0],&(*ppmC)->Mat[uB+1][0]);
	}else {//échanger deux doublets de colonnes
		if (kF) printf("Echange des doublets de colonnes %d-%d et %d-%d.\n",uA,uA+1,uB,uB+1);
		//Assert2("MatriceEchangerPairE3",bImpair(uA),bImpair(uB));
Assert1("bMatriceEchangerPaireA",!bVekteurContient(0,(*ppmC)->nLigne,(*ppmC)->Mat[0]));
		for (uL=1;uL<=(*ppmC)->nLigne;uL++)
			EntyerEchanger(&(*ppmC)->Mat[uL][uA],&(*ppmC)->Mat[uL][uB]);
		EntyerEchanger(&(*ppmC)->Mat[0][uA+0],&(*ppmC)->Mat[0][uB+0]);
		for (uL=1;uL<=(*ppmC)->nLigne;uL++)
			EntyerEchanger(&(*ppmC)->Mat[uL][uA+1],&(*ppmC)->Mat[uL][uB+1]);
		EntyerEchanger(&(*ppmC)->Mat[0][uA+1],&(*ppmC)->Mat[0][uB+1]);
Assert1("bMatriceEchangerPaireB",!bVekteurContient(0,(*ppmC)->nLigne,(*ppmC)->Mat[0]));
	}
	if (bVoir) MatriceVoir(sC2("APRES bMatriceEchangerPaire n°",sEnt(uA)),*ppmC);
	//Assert1("bMatriceEchangerPaire5",bEchangerPaire);
	nModule1=nMatriceModulE(*ppmC);
	Assert1("bMatriceEchangerPaire541",nModule0==nModule1);
	//Appel1("bMatriceEchangerPaire");
	bEchangerPaire=bImpair(uA) && bImpair(uB);
	return(bEchangerPaire);
}//bMatriceEchangerPaire

void MatriceEchangerSingleton(int bLigne,int uA,int uB,int bVoir,iMatrice **ppmC){
	//échange réellement soit les lignes uA et uB soit les colonnes uA et uB, de ppmC;actualise le vecteur de permutations
	int uL,uC;
	Assert4("MatriceEchangerSingleton1",bCroit(1,uA,(*ppmC)->nLigne),bCroit(1,uB,(*ppmC)->nLigne),uA!=uB,(*ppmC)->nLigne==(*ppmC)->nColonne);
	if (bVoir) MatriceVoir(sC2("AVANT MatriceEchangerSingleton n°",sEnt(uA)),*ppmC);
	//Assert1("MatriceEchangerPairE2",bLigne);
	if (bLigne){//échanger deux lignes
		if (kF) printf("Echange des lignes %d et %d.\n",uA,uB);
		//Assert2("MatriceEchangerSingleton2",bImpair(uA),bImpair(uB));
		for (uC=1;uC<=(*ppmC)->nColonne;uC++)
			EntyerEchanger(&(*ppmC)->Mat[uA][uC],&(*ppmC)->Mat[uB][uC]);
		EntyerEchanger(&(*ppmC)->Mat[uA+0][0],&(*ppmC)->Mat[uB+0][0]);
	}else {//échanger deux colonnes
		if (kF) printf("Echange des colonnes %d et %d.\n",uA,uB);
		//Assert2("MatriceEchangerSingleton3",bImpair(uA),bImpair(uB));
		for (uL=1;uL<=(*ppmC)->nLigne;uL++)
			EntyerEchanger(&(*ppmC)->Mat[uL][uA],&(*ppmC)->Mat[uL][uB]);
		EntyerEchanger(&(*ppmC)->Mat[0][uA+0],&(*ppmC)->Mat[0][uB+0]);
	}
	if (bVoir) MatriceVoir(sC2("APRES MatriceEchangerSingleton n°",sEnt(uA)),*ppmC);
}//MatriceEchangerSingleton

long yMatriceDeterminant(iMatrice *pmA){
	dMatricE *pmT;
	int nEtape,uL,uC;
	double dDeterminant;
	long yDeterminant;
	MatriceAllouheR(&pmT);
		pmT->nLigne=pmA->nLigne;		
		pmT->nColonne=pmA->nColonne;
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC++)
				pmT->Mat[uL][uC]=1.0*pmA->Mat[uL][uC];
		dDeterminant=dMatriceTrianguleR(&pmT,!k1Voir,&nEtape);
		//tr("Déterminant obtenu par dMatriceTrianguleR",dDeterminant);
	free(pmT);
	//tr("dDeterminant brut",dDeterminant);
	//printf("Déterminant DOUBLE  de dMatriceTrianguleR: %lf.\n",dDeterminant);
	yDeterminant=yArrondi(dDeterminant);
	//printf("Déterminant LONGINT de dMatriceTrianguleR: %ld.\n",yDeterminant);

	//yBof=ySignatureCalculeR(pmA,!k1Alterner,&nBof);tr("ySignatureCalculeR brut",yBof);
	return(yDeterminant);
}//yMatriceDeterminant

int nMatriceSignature(graf *pgG,int emMode){
	//évalue la signature associée au graphe pgG;si emMode=maFormuler0 ou maFormuler1,évalue aussi les polynomes associés.
	const int kuAreteValeur=1;
	const int kbMatriceAfficher=kF;
	const int kbPremier=kV;
	iMatrice *pmA;
	iMatrice *pmAreteIndex;
	int bkAlterner=kF;
	int nAppelExponentiel;
	int bComplementer;
	long ySignature;
	int iSignature;
	int bFormuler;
	int cPasse;
	int uL,uC,nP;
	int bSinguliere;
	int aK,sX,sY;
	//enum eMatrice {maAlpha,maFormuler0,maFormuler1,maPremier0,maPremier1,maOmega};
	Assert1("nMatriceSignature1",bCroitStrict(maAlpha,emMode,maOmega));
	bFormuler=(emMode==maFormuler0 || emMode==maFormuler1);
	if (bFormuler && kbMatriceAfficher)
		GrapheVoir(pgG,"Graphe à signer");
	bVoiR=kF;
	for (cPasse=0;cPasse<=bFormuler;cPasse++){//1 passe, ou 2 si bFormuler
		MatriceAllouer1(&pmA,pgG->nSommetEnTout);
			MatriceAllouer1(&pmAreteIndex,pgG->nSommetEnTout);
				//remplir la matrice pmA[] avec ±1 si l'arc aK de pgG existe et mémoriser aK ds pmAreteIndex[]
					//MatriceVoir("nMatriceSignature",pmA)
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
							sY=pgG->sSuk[aK];
							pmA->Mat[sX][sY]=+kuAreteValeur;
							pmA->Mat[sY][sX]=iSignePres(bkAlterner,kuAreteValeur);
							pmAreteIndex->Mat[sX][sY]=aK;
							pmAreteIndex->Mat[sY][sX]=aK;
						}
				if (bkAlterner && kbPremier)//remplacer chaque ±1 mémorisé dans pmA->Mat par un nbre premier particulier flanqué du signe déjà attribué.
					if (bCroit(maPremier0,emMode,maPremier1) || (cPasse==0))
						for (nP=0,uL=1;uL<=pmA->nLigne;uL++)
							for (uC=1;uC<=pmA->nColonne;uC++)
								if (abs(pmA->Mat[uL][uC])==1){
									pmA->Mat[uL][uC]=iSignePres(uC<uL,nPremier(++nP));
									pmA->Mat[uC][uL]=iSignePres(bkAlterner,pmA->Mat[uL][uC]);//**************
								}
				bComplementer=(cPasse==1) && (emMode==maFormuler1) && bkAlterner;
				if (kF && bComplementer){
					for (uL=1;uL<=pmA->nLigne && bComplementer;uL++)
						for (uC=1;uC<=pmA->nColonne && bComplementer;uC++)
							if (pmA->Mat[uL][uC]!=0){
								pmA->Mat[uL][uC]=-pmA->Mat[uL][uC];
								pmA->Mat[uC][uL]=-pmA->Mat[uC][uL];
								pmAreteIndex->Mat[uL][uC]=-pmAreteIndex->Mat[uL][uC];
								pmAreteIndex->Mat[uC][uL]=-pmAreteIndex->Mat[uC][uL];
								bComplementer=kF;
							}
				}
				if (kbMatriceAfficher && bFormuler)
					MatriceVoir("Matrice antisymétrique sommet-sommet associée au graphe",pmA);
				if (cPasse==0){
					//MatriceVoir(sC2b("Matrice",sChoix((emMode!=maFormuler1 || !bkAlterner),"associée","retouchée")),pmA);
					ySignature=ySignatureCalculeR(pmA,bkAlterner,&nAppelExponentiel);
					//te("Signature",ySignature);
					bSinguliere=(ySignature==0);
					//DeterminantFormuleR(pmA,pmAreteIndex,bkAlterner,pgG);
				}else if (bFormuler){
					SignatureCertifieR(pgG,bSinguliere);
					//else DeterminantFormuleR(pmA,pmAreteIndex,bkAlterner,pgG);
				}
			free(pmAreteIndex);
		free(pmA);
	}
	//te("Signature",ySignature);
	iSignature=ySignature;
	return(iSignature);
}//nMatriceSignature

int bMatriceSingulierh(graf *pgG,int emMode){
	//évalue le déterminant associé au graphe pgG;si emMode=maFormuler0 ou maFormuler1,évalue aussi les polynomes associés.
	#define kuAreteValeur 1
	riMatrice *pmA;
	ri riDeterminer;
	int bFormuler;
	int bSinguliere;
	int aK,sX,sY;
	//enum eMatrice {maAlpha,maFormuler0,maFormuler1,maPremier0,maPremier1,maOmega};
	Assert1("bMatriceSingulierh1",bCroitStrict(maAlpha,emMode,maOmega));
	bFormuler=(emMode==maFormuler0 || emMode==maFormuler1);
	if (1)
		GrapheVoir(pgG,"Graphe fourni à bMatriceSingulierh");
	bVoiR=kF;
	MatRIceAllouer(&pmA);
		pmA->nLigne=pgG->nSommetEnTout;
		pmA->nColonne=pgG->nSommetEnTout;
		MatRIceRazeR(&pmA);
		//remplir la matrice pmA[] avec 1±i si l'arc aK de pgG existe
			//MatRIceVoir("bMatriceSingulierh",pmA);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					pmA->Mat[sX][sY]=riAff(+kuAreteValeur,+0);
					pmA->Mat[sY][sX]=riAff(-kuAreteValeur,-0);
				}
		MatRIceVoir("Matrice antisymétrique sommet-sommet associée au graphe",pmA);
		riDeterminer=riDeterminantCalculeR(pmA);
		tri("Déterminant singulier",riDeterminer);
		bSinguliere=briNul(riDeterminer);
	free(pmA);
	return(bSinguliere);
}//bMatriceSingulierh

void MatriceDupliquer(iMatrice *pmA,iMatrice *pmB){
	//si bDontPermutation,duplique aussi les permutations
	int nL,nC;
	int bHorsPermutation=0;
	for (nL=bHorsPermutation;nL<=knLigneMaX;nL++)
		for (nC=bHorsPermutation;nC<=knLigneMaX;nC++)
			pmB->Mat[nL][nC]=pmA->Mat[nL][nC];
}//MatriceDupliquer

void MatriceDupliqueR2(iMatrice *pmA,iMatrice **ppmB){
	int uL,uC;
	(*ppmB)->nLigne=pmA->nLigne;
	(*ppmB)->nColonne=pmA->nColonne;
	(*ppmB)->nSecante=pmA->nSecante;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			(*ppmB)->Mat[uL][uC]=pmA->Mat[uL][uC];
}//MatriceDupliqueR2

int nMatriceEffectifNonNuL(iMatrice *pmA){
	int uC,uL,nEffectifNonNul;
	for (nEffectifNonNul=0,uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			nEffectifNonNul+=pmA->Mat[uL][uC]!=0;
	return(nEffectifNonNul);
}//nMatriceEffectifNonNuL

int nMatRIceEffectifNonNuL(riMatrice *pmK){
	int uC,uL,nEffectifNonNul;
	for (nEffectifNonNul=0,uL=1;uL<=pmK->nLigne;uL++)
		for (uC=1;uC<=pmK->nColonne;uC++)
			nEffectifNonNul+= !briNul(pmK->Mat[uL][uC]);
	return(nEffectifNonNul);
}//nMatRIceEffectifNonNuL

void MatriceFoisColonne(iMatrice *pmA,iMatrice *pmB,int uColonneDansB,iMatrice **ppmC){
	int uL,uK;
		for (uL=1;uL<=pmA->nLigne;uL++)
			for ( (*ppmC)->Mat[uL][uColonneDansB]=0,uK=1;uK<=pmA->nLigne;uK++)
				(*ppmC)->Mat[uL][uColonneDansB]+=pmA->Mat[uL][uK]*pmB->Mat[uK][uColonneDansB];
}//MatriceFoisColonne

void MatriceFoisser(int iFois,iMatrice **ppmC){
	//multiplie tous les termes de la Matrice par iFois
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			(*ppmC)->Mat[uL][uC]*=iFois;
}//MatriceFoisser

void MatriceGrapher(iMatrice *pmA,graf *pgA){
	//rend le graphe pgA qui a pmA pour matrice;la couleur de chaque arc est la valeur absolue de l'élément matriciel non nul
	int uC,uL;
	//Appel0("MatriceGrapher");
		//te("pgA->nSommetEnTout",pgA->nSommetEnTout);
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC++)
				if (pmA->Mat[uL][uC]!=0){
					//tee("MatriceGrapher uL,uC",uL,uC);
					GrapheArquer1(pgA,uL,uC,abs(pmA->Mat[uL][uC]));
				}
	//Appel1("MatriceGrapher");
}//MatriceGrapher

void MatriceHasarder(iMatrice *pmC,int iEmpan){
	//remplit pmC de nombres aléatoires dans [1..|iEmpan|];uniqt les éléments non nuls si iEmpan<0
	int uC,uL;
	//MatriceRazer(&pmC);
	for (uL=1;uL<=pmC->nLigne;uL++)
		for (uC=1;uC<=pmC->nColonne;uC++)
			if (pmC->Mat[uL][uC]!=0)
				pmC->Mat[uL][uC]=uHasard(abs(iEmpan));
}//MatriceHasarder

void MatriceIdentiter(iMatrice **ppmC){
	int uD;
	MatriceRazer(ppmC);
	for (uD=1;uD<=knLigneMaX;uD++)
		(*ppmC)->Mat[uD][uD]=1;
}//MatriceIdentiter

void MatriceIdentiteR(riMatrice **ppmC){
	int uD;
	MatRIceRazeR(ppmC);
	for (uD=1;uD<=knLigneMaX;uD++)
		(*ppmC)->Mat[uD][uD].r=1;
}//MatriceIdentiteR

void MatriceINITIALISER(){//O(?)
	//relance le présent module
	Assert2("MatriceINITIALISER",bMatriceAmorceR,!bMatriceOuvertE);
}//MatriceINITIALISER

void MatriceIntervaller(iMatrice **ppmC){
	//rend une matrice intervalle,ie tte colonne contient une suite de 1 consécutifs et une seule
	int uC,uL,uL0,uL1;
	MatriceRazer(ppmC);
	for (uC=1;uC<=(*ppmC)->nColonne;uC++){
		uL0=uHasard((*ppmC)->nLigne-1);
		uL1=uL0+uHasard((*ppmC)->nLigne-uL0);
		Assert1("MatriceIntervaller",bCroit4(1,uL0,uL1,(*ppmC)->nLigne));
		for (uL=uL0;uL<=uL1;uL++)
			(*ppmC)->Mat[uL][uC]=1;
	}
}//MatriceIntervaller

void MatriceIntervaller2(int nLigneEnTout,int nColonneEnTout, iMatrice **ppmC){
	//rend une matrice intervalle,ie tte colonne contient une suite de 1 consécutifs et une seule
	(*ppmC)->nLigne=nLigneEnTout;
	(*ppmC)->nColonne=nColonneEnTout;
	MatriceIntervaller(ppmC);
}//MatriceIntervaller2

void MatriceLosanger(int nOffsetDepuisDiagonalePrincipale,int nMarqueInitiale,iMatrice **ppmC){
	//ajoute une diagonale de losange;diagonale principale si nOffsetDepuisDiagonalePrincipale=0,diagonale décalée de c colonnes si =c.
	int uD,uL,uC,nLigne,nMarque;
	Assert1("MatriceLosanger",(*ppmC)->nLigne==(*ppmC)->nColonne);
	nLigne=(*ppmC)->nLigne;
	for (nMarque=nMarqueInitiale,uD=2;uD<nLigne;uD+=3){
		uL=uD;
		uC=nOffsetDepuisDiagonalePrincipale+uD;
		(*ppmC)->Mat[uL-1][uC+0]=(*ppmC)->Mat[uL+0][uC-1]=nMarque++;
		(*ppmC)->Mat[uL+1][uC+0]=(*ppmC)->Mat[uL+0][uC+1]=nMarque++;
	}
}//MatriceLosanger

void MatriceMarner(iMatrice *pmA,int *piValeurMin,int *piValeurMax){
	int uL,uC,iValeurMin,iValeurMax;
	for (iValeurMax=kiIntegerMin,iValeurMin=kuIntegerMax,uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++){
			iValeurMax=iSup(iValeurMax,pmA->Mat[uL][uC]);
			iValeurMin=iInf(iValeurMin,pmA->Mat[uL][uC]);
		}
	*piValeurMax=iValeurMax;
	*piValeurMin=iValeurMin;
}//MatriceMarner

int nMatriceModulE(iMatrice *pmA){
	int uC,nEffectif,uL;
	int nModule;
	nEffectif=pmA->nLigne;
	for (nModule=0,uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++){
			nModule+=abs(pmA->Mat[uL][uC]);
		}
	return(nModule);
}//nMatriceModulE

void MatriceModuleR(int uModulo,iMatrice **ppmC){
	//(*ppmC)->Mat[uL][uC]%=uModulo
	int uC,nEffectif,uL;
	nEffectif=(*ppmC)->nLigne;
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++){
			(*ppmC)->Mat[uL][uC]%=uModulo;
		}
	(*ppmC)->nLigne=nEffectif;
}//MatriceModuleR

void MatriceMultiplier(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	//multiplication usuelle, en O(N**3)
	int uC,uK,uL;
	Assert5("MatriceMultiplier",pmA->nLigne==pmA->nColonne,pmB->nLigne==pmB->nColonne,(*ppmC)->nLigne==(*ppmC)->nColonne,pmA->nLigne==pmB->nLigne,pmA->nLigne==(*ppmC)->nLigne);
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			for ((*ppmC)->Mat[uL][uC]=0,uK=1;uK<=pmA->nColonne;uK++)
				(*ppmC)->Mat[uL][uC]+=pmA->Mat[uL][uK]*pmB->Mat[uK][uC];
}//MatriceMultiplier

long zMatriceMultiplieR(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	//multiplication usuelle, en O(N**3)
	long zCopie=0;
	MatriceMultiplier(pmA,pmB,ppmC);
	zCopie=knLigneMaX*knLigneMaX;
	return(zCopie);
}//zMatriceMultiplieR

void MatriceNettoyeR(iMatrice *pmA){
	//retire de pmA les 1 non appariables
	int uC,uL,tRetrait;
	int nSegment[1+pmA->nSecante];
	//te("pmA->nSecante",pmA->nSecante);
	do{
		tRetrait=0;
		//nSegment[uL]:=pmA->Mat[1..pmA->nSecante][..] non nul:
			VecteurRazer(nSegment,1,pmA->nSecante);
			for (uL=1;uL<=pmA->nSecante;uL++)
				for (uC=1;uC<=pmA->nSecante;uC++)
					if (pmA->Mat[uL][uC]!=0)
						nSegment[uL]=1;
		//retirer tout 1 de ligne uL qui n'a pas de segment correspondant non nul ligne uL±1
			for (uL=1;uL<=pmA->nSecante;uL++)
				if (bPair(uL) && nSegment[uL-1]==0 || bImpair(uL) && nSegment[uL+1]==0)
					for (uC=1;uC<=pmA->nSecante;uC++)
						if (pmA->Mat[uL][uC]!=0){
							pmA->Mat[uL][uC]=0;
							tRetrait=1;
						}
		//if (tRetrait>0) MatriceVoir("Nettoyage lignes",pmA);
		//nSegment[uL]:=pmA->Mat[..][1..pmA->nSecante] non nul:
			VecteurRazer(nSegment,1,pmA->nSecante);
			for (uC=1;uC<=pmA->nSecante;uC++)
				for (uL=1;uL<=pmA->nSecante;uL++)
					if (pmA->Mat[uL][uC]!=0)
						nSegment[uC]=1;
		//retirer tout 1 de colonne uC qui n'a pas de segment correspondant non nul colonne uC±1
			for (uC=1;uC<=pmA->nSecante;uC++)
				if (bPair(uC) && nSegment[uC-1]==0 || bImpair(uC) && nSegment[uC+1]==0)
					for (uL=1;uL<=pmA->nSecante;uL++)
						if (pmA->Mat[uL][uC]!=0){
							pmA->Mat[uL][uC]=0;
							tRetrait=-1;
						}
		//if (tRetrait<0) MatriceVoir("Nettoyage colonnes",pmA);
	}while (tRetrait!=0);
}//MatriceNettoyeR

int bMatriceNullE(iMatrice *pmA){
	int uC,uL,bNulle=kV;
	for (bNulle=kV,uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nLigne;uC++)
			bNulle=bNulle && !pmA->Mat[uL][uC];
	return(bNulle);
}//bMatriceNullE

void MatriceProduirE(int uListe[],int bDirect,iMatrice **ppmC){
	//remplit ppmC avec ts les produits des diviseurs de uListe
	int uC,nEffectif,uL,nValeur;
	nEffectif=uListe[0];
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++){
			nValeur=(bDirect)? uListe[uL]*uListe[nEffectif+1-uC]: uListe[uC]*uListe[nEffectif+1-uL];
			(*ppmC)->Mat[uL][uC]+=nValeur;
		}
	(*ppmC)->nLigne=nEffectif;
}//MatriceProduirE

int bMatricePositive(iMatrice *pmA){
	int uC,uL,bPositive=kV;
	for (bPositive=kV,uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nLigne;uC++)
			bPositive=bPositive && pmA->Mat[uL][uC]>=0;
	return(bPositive);
}//bMatricePositive

void MatricePositiver(iMatrice *pmA){
	int uC,uL;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			pmA->Mat[uL][uC]=abs(pmA->Mat[uL][uC]);
}//MatricePositiver

void MatricePuissancer(iMatrice *pmA,int nPuissance,iMatrice **ppmC){//O(nPuissance*N3)
	//puissance usuelle,volontrairt séquentialisée
	Assert1("MatricePuissancer",nPuissance>=0);
	int uP;
	iMatrice *pmCopie;
	if (!bMatriceNullE(pmA) &&nPuissance>1) MatriceVoir(sC2("AVANT MatricePuissancer**",sEnt(nPuissance)),pmA);
	MatriceRazer(ppmC);
	MatriceBander(0,ppmC);
	MatriceAllouer1(&pmCopie,pmA->nLigne);
		//MatriceVoir("MatricePuissancer=matrice identité",*ppmC);
		if (nPuissance>0)
			MatriceDupliquer(pmA,*ppmC);
		for (uP=2;uP<=nPuissance;uP++){
			MatriceDupliquer(*ppmC,pmCopie);
			MatriceMultiplier(pmA,pmCopie,ppmC);
		}
	free(pmCopie);
	if (!bMatriceNullE(pmA) &&nPuissance>1) MatriceVoir(sC2("APRES MatricePuissancer**",sEnt(nPuissance)),*ppmC);
}//MatricePuissancer

void MatriceQuadripoler(int nTest,int bBoucler,iMatrice **ppmQ){
	const int bVoir=kF;
	graf *pgG;
	int bBiparti,uC,uL,nLmoins,nLplus,nSommet;
	int aK,sX,sY;
	int nRang[1+100];
	GrapheCreer0(&pgG,kV);
		bBiparti=bGrapheQuadripoleR(pgG,bBoucler,nTest,ppmQ);
GrapheVoir1(pgG,kV,"après Quadripole");
		if (bVoir) GrapheVoir1(pgG,kV,"après Quadripole");
		//ppmQ soit la matrice associée à pgG
			//bBiparti=kF;
			nSommet=pgG->nSommetEnTout/(1+bBiparti);
			MatriceAlloueR0(ppmQ,nSommet,nSommet,nSommet);
			//attribuer par défaut la permutation identité
				for (uL=1;uL<=nSommet;uL++)
					(*ppmQ)->Mat[uL][0]=(*ppmQ)->Mat[0][uL]=uL;
				(*ppmQ)->Mat[0][0]=nSommet;
			if (bBiparti){//la couleur 1 ou 2 du sommet sX a été stockée dans pgG->sPer[sX]
					//VecteurRazer(nRang,1,100);
					for (sX=1,nLmoins=0,nLplus=0;sX<=pgG->nSommetEnTout;sX++){
						if (pgG->sPer[sX]==1){
							nRang[sX]=-(++nLmoins);
							(*ppmQ)->Mat[nLmoins][0]=sX;
						}else {nRang[sX]=+(++nLplus);
							(*ppmQ)->Mat[0][nLplus]=sX;
						}
					}
				//VecteurVoir1("nRang",nRang,1,2*nSommet);
				//VekteurVoir1("(*ppmQ)->Mat[nLmoins]",(*ppmQ)->Mat[0],1,nSommet);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){
					uL=abs(nRang[sX]);
					//(*ppmQ)->Mat[uL][0]=sX;
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						uC=abs(nRang[sY]);
						//(*ppmQ)->Mat[0][uC]=sY;
						//teeee("sX,sY,uL,uC",sX,sY,uL,uC);
						Assert1("MatriceQuadripoler9",nRang[sX]>0 != nRang[sY]>0);
						if (nRang[sX]<0)
							(*ppmQ)->Mat[uL][uC]=pgG->coulh[aK];
						else (*ppmQ)->Mat[uC][uL]=pgG->coulh[aK];
					}
				}
			}else {
				for (sX=1;sX<=nSommet;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						(*ppmQ)->Mat[sX][sY=pgG->sSuk[aK]]=pgG->coulh[aK];
			}
			if (0) MatriceVoir("@@@@@@@@@@@@@@@@@@@@@@@Matrice brute associée à pgG quadripolé",*ppmQ);
		if (0)//négativer le triangle supérieur
			for (uL=1;uL<=(*ppmQ)->nLigne;uL++)
				for (uC=uL+1;uC<=(*ppmQ)->nColonne;uC++)
					(*ppmQ)->Mat[uL][uC]= -(*ppmQ)->Mat[uL][uC];
		if (0)//négativer le triangle inférieur
			for (uL=1;uL<=(*ppmQ)->nLigne;uL++)
				for (uC=1;uC<uL;uC++)
					(*ppmQ)->Mat[uL][uC]= -(*ppmQ)->Mat[uL][uC];
	GrapheCreer0(&pgG,kF);
}//MatriceQuadripoler

void MatriceQuintesseR(int nSommet){
	#define kbKalculer kV
	int nAppel,nBaton,uCarreh,nPaire,nNom,nEtape;
	graf *pgG;
	int sX,sY,sT,aK,vX,vY;
	iMatrice *pmA,*pmB,*pmC;
	int bPaire;
	int nPermutation[knLigneLiM];
	int ipPaire;
	int bFait[knLigneLiM];
	Appel0("MatriceQuintesseR");
		Assert1("MatriceQuintesseR0",nSommet<=4);
		GrapheCreer0(&pgG,kV);
			GrapheQuintesser(pgG,nSommet);
			GrapheVoir(pgG,"Graphe quiné");
			if (!(pgG->nSommetEnTout<knLigneLiM))
				tee("pgG->nSommetEnTout vs knLigneLiM",pgG->nSommetEnTout,knLigneLiM);
			Assert1("MatriceQuintesseR1",pgG->nSommetEnTout<knLigneLiM);
			MatriceAlloueR0(&pmA,pgG->nSommetEnTout,pgG->nSommetEnTout,0);
			uCarreh=4*nSommet*nSommet;//nb total de sommets hors étoiles
			te("uCarreh",uCarreh);
			for (nBaton=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					pmA->Mat[sX][sY=pgG->sSuk[aK]]=pmA->Mat[sY][sX]=(pgG->aDeh[sX]>0)? ((kbKalculer)?1:8):1;
					if (sX<=uCarreh && sY<=uCarreh)
						pmA->Mat[sX][sY]=pmA->Mat[sY][sX]=(kbKalculer)? 1:5;//arc interne,ie non connecté à une étoile
					//effacer les arcs "bâtons" qui matérialisent le dédoublement de chaque sommet du graphe original
						if ( (sX<uCarreh) && bImpair(sX) && (sX+1==sY) )
							(nBaton++,pmA->Mat[sX][sY]=pmA->Mat[sY][sX]=0);
				}
			te("nBaton",nBaton);
			Assert1("MatriceQuintesseR baton",2*nBaton==uCarreh);
			//MatriceVoir("MatriceQuintesseR pmA",pmA);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				bFait[sX]=kF;
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				nPermutation[sX]=sX;
			//VecteurVoir("Permutation",nPermutation,1,pgG->nSommetEnTout);
			for (ipPaire=0,nPaire=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
				//VecteurVoir("Permutation",nPermutation,1,pgG->nSommetEnTout);
				bPaire=(vY=pgG->aDeh[vX=nPermutation[sX]])>0;
				//if (vX<vY && bPaire){
				if (!bFait[vX] && !bFait[vY] && bPaire){
					nPaire++;
					for (sY=0,sT=sX+1;sT<=pgG->nSommetEnTout;sT++)
						if (vY==nPermutation[sT])
							sY=sT;
					Assert1("MatriceQuintesseR2",sY>0);
					//printf("Paire n°%d,sX=%d,sY=%d,P(X=%d,P(Y)=%d.\n",nPaire,sX,sY,nPermutation[sX],nPermutation[sY]);
					EntierEchanger(&nPermutation[++ipPaire],&nPermutation[sX]);
					EntierEchanger(&nPermutation[++ipPaire],&nPermutation[sY]);
					if (nPermutation[ipPaire-1]>nPermutation[ipPaire])
						EntierEchanger(&nPermutation[ipPaire-1],&nPermutation[ipPaire]);
					bFait[vX]=bFait[vY]=kV;
				}
			}
			Assert2("MatriceQuintesseR appariement",ipPaire==2*nPaire,ipPaire==pgG->nSommetEnTout);
			//transférer les solitons (numérotés "5") au bout de la diagonale principale
				for (sX=1;sX<=pgG->nSommetEnTout-uCarreh;sX++)
					nPermutation[sX]=nPermutation[uCarreh+sX];
				for (sX=1;sX<=uCarreh;sX++)
					nPermutation[pgG->nSommetEnTout-uCarreh+sX]=sX;
			nPermutation[0]=pgG->nSommetEnTout;
			//VecteurVoir("Permutation",nPermutation,1,pgG->nSommetEnTout);
			//tee("sécante,reste",ipPaire,pgG->nSommetEnTout-ipPaire);
			MatriceAlloueR0(&pmB,pgG->nSommetEnTout,pgG->nSommetEnTout,pgG->nSommetEnTout-uCarreh);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)
					pmB->Mat[sX][sY]=pmA->Mat[sX][nPermutation[sY]];
			//MatriceVoir("MatriceQuintesseR pmB",pmB);
			//pmB->Mat reçoive la copie de nPermutation[] en ligne 0 ET AUSSI en colonne 0
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pmB->Mat[sX][0]=nPermutation[sX];
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pmB->Mat[0][sX]=nPermutation[sX];
			MatriceAlloueR0(&pmC,pgG->nSommetEnTout,pgG->nSommetEnTout,pgG->nSommetEnTout-uCarreh);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)
					pmC->Mat[sX][sY]=pmB->Mat[nPermutation[sX]][sY];
			//pmC->Mat reçoive la copie de nPermutation[] en ligne 0 ET AUSSI en colonne 0
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pmC->Mat[sX][0]=nPermutation[sX];
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pmC->Mat[0][sX]=nPermutation[sX];
		GrapheCreer0(&pgG,kF);
			MatriceVoir("MatriceQuintesseR pmC",pmC);
			nAppel=0;
			//yBof=ySignatureKalculeR(pmC,!k1Alterner,&nAppel);
			//te("Signature à sécante nulle",yBof);
			bBof=bMatriceSingulariseR(&pmC,&nNom,&nEtape);
			printf("\nIl %s chemin.\n\n",sUn("y a",!bBof));

		free(pmA);free(pmB);free(pmC);
	Appel1("MatriceQuintesseR");
}//MatriceQuintesseR

void MatriceRazOueR(oMatrice **ppmoA){
//enum eMatriceType {maAlphA,matEntier,matRationnel,matReel,matComplexe,matRect,maOmegA};
//	typedef union{long ent;double reel;q rat;ri cplx;rect mm;}objet;
	int nC,nL;
	objet Ob;
	for (nL=0;nL<=knLigneMaX;nL++)
		for (nC=0;nC<=knColonneMaX;nC++)
			Ob=(*ppmoA)->Mat[nL][nC];
			switch ((*ppmoA)->typ){
				case matEntier:Ob.ent=0;break;
				case matRationnel:Ob.rat.num=0;Ob.rat.den=0;break;
				case matComplexe:Ob.cplx=riAff(0,0);break;
				case matReel:Ob.reel=0;break;
				case matRect:NbAffecter(0,&Ob.mm.q11);NbAffecter(0,&Ob.mm.q12);NbAffecter(0,&Ob.mm.q21);NbAffecter(0,&Ob.mm.q22);break;
			}
}//MatriceRazOueR

void MatriceRazer(iMatrice **ppmA){
	int nC,nL;
	for (nL=0;nL<=knLigneMaX;nL++)
		for (nC=0;nC<=knColonneMaX;nC++)
			(*ppmA)->Mat[nL][nC]=0;
}//MatriceRazer

void MatRIceRazeR(riMatrice **ppmA){
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knColonneMaX;uC++)
			(*ppmA)->Mat[uL][uC]=riAff(0,0);
}//MatRIceRazeR

void MatriceRazer2(yMatricE **ppmA){
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knColonneMaX;uC++)
			(*ppmA)->Mat[uL][uC]=0;
}//MatriceRazer2

void MatriceRazheR(dMatricE **ppmA){
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knColonneMaX;uC++)
			(*ppmA)->Mat[uL][uC]=0.0;
}//MatriceRazheR

int nMatriceRempliE(iMatrice *pmA){
	//rend le nombre de cases non vide ds pmA
	int uL,uC;
	int nRemplie=0;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			if (pmA->Mat[uL][uC]>0)
				nRemplie++;
	return(nRemplie);
}//nMatriceRempliE

void MatriceRempliR(iMatrice **ppmC){
	//remplit ppmC avec les (*ppmC)->nLigne)*(*ppmC)->nColonne premiers entiers depuis 1;
	int uC,uL,nValeur;
	for (nValeur=0,uL=1;uL<=(*ppmC)->nLigne;uL++)
		for (uC=1;uC<=(*ppmC)->nColonne;uC++)
			(*ppmC)->Mat[uL][uC]+=(++nValeur);
}//MatriceRempliR

float fMatriceRempliR(int bDoublonPossible,int uEffectif,iMatrice **ppmA){
	//remplit ppmA avec uEffectif 1 placés au hasard,certains au même endroit ssi bDoublonPossible;rend la densité de la Matrice
	int uF,uL,uC,nLibre,nOccurrence,nRemplie;
	float fRemplir;
	Assert1("fMatriceRempliR1",bCroit(1,uEffectif,knLigneMaX*knLigneMaX));
	if (!bDoublonPossible){
		nRemplie=nMatriceRempliE(*ppmA);
		nLibre=knLigneMaX*knLigneMaX-nRemplie;
		Assert1("fMatriceRempliR2",nLibre>=uEffectif);
		for (uF=1;uF<=uEffectif;uF++){
			nOccurrence=uHasard(knLigneMaX*knLigneMaX-nRemplie);
			//remplir la case non vide de rang nOccurrence
				for (uL=1;uL<=knLigneMaX;uL++)
					for (uC=1;uC<=knLigneMaX;uC++)
						if ( (*ppmA)->Mat[uL][uC]==0 ){
							if (--nOccurrence==0) 
								(*ppmA)->Mat[uL][uC]=1;
						}
				nRemplie++;
		}
	}
	else for (uF=1;uF<=uEffectif;uF++){
			uC=uHasard(knLigneMaX);
			uL=uHasard(knLigneMaX);
			(*ppmA)->Mat[uL][uC]=1;
		}
	nOccurrence=nMatriceRempliE(*ppmA);//nb d'éléments non nuls ds (*ppmA)->Mat 
	fRemplir=(nOccurrence*1.0)/(knLigneMaX*knLigneMaX);
	Assert1("fMatriceRempliR3",bCroissant(0.0,fRemplir,1.0));
	return(fRemplir);
}//fMatriceRempliR

int bMatriceSingulariser(graf *pgG){
	int nEtape,aK,uIndex,nNom,bSingulariser,sX,sY;
	iMatrice *pmA;
	GrapheVoir(pgG,"Graphe fourni en donnée");
	MatriceAllouer1(&pmA,pgG->nSommetEnTout);
	Assert2("bMatriceSingulariser",pmA->nLigne<knLigneLiM,pmA->nColonne<knColonneLiM);
	MatriceRazer(&pmA);
	//remplir la matrice pmA avec les seules caractéristiques du graphe pgG en attribuant à chaque variable un nom et un signe.
		for (nNom=0,uIndex=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX<sY){//variable de coefficient +1
					nNom++;
					Assert1("bMatryceSinguliere",nNom<knNomLiM);
					pmA->Mat[sX][sY]=nNom;
				}
			}
		for (uIndex=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX>sY){//variable de coefficient -1
					uIndex=pmA->Mat[sX][sY];
					pmA->Mat[sX][sY]=-pmA->Mat[sY][sX];
				}
			}
	MatriceVoir("Matrice antisymétrique sommet-sommet associée au graphe",pmA);
	bSingulariser=bMatriceSingulariseR(&pmA,&nNom,&nEtape);
	printf("\nIl %s chemin.\n\n",sUn("y a",!bSingulariser));
	return(bSingulariser);
}//bMatriceSingulariser

int nNomAdHoC(int uD,int uL,int uC,iMatrice *pmA,int *pnNom){
	//rend un nom qui caractérise l'expression: nmA*nmD-nmB*nmC; A et B sont sur la mm ligne de gauche à droite;C et D aussi,de gauche à droite.
	int nAdHoc=0;
	int nNom;
	int nmA,nmB,nmC,nmD;
	int umA,umB,umC,umD;
	nmA=pmA->Mat[uD][uD];umA=abs(nmA);	//	pmA->Mat[uD][uD]*pmA->Mat[uL][uC]-pmA->Mat[uD][uC]*pmA->Mat[uL][uD]
	nmB=pmA->Mat[uD][uC];umB=abs(nmB);
	nmC=pmA->Mat[uL][uD];umC=abs(nmC);
	nmD=pmA->Mat[uL][uC];umD=abs(nmD);
	Assert1("nNomAdHoC",nmA!=0);
	if (uC==uD){
		//t("pivotttt");
	}
	else {nNom=*pnNom;
		//teeeeee("ligne uL,A,D,B,C,AD-BC",uL,nmA,nmD,nmB,nmC,nmA*nmD-nmB*nmC);
		if (umA*umD!=0 || umB*umC!=0){
			nNom++;
			nAdHoc=nNom;
			*pnNom=nNom;
			//te("nAdHoccccccccc",nAdHoc);
		}
	}
	//teeee("                           uD,uL,uC,nAdHoc",uD,uL,uC,nAdHoc);
	//nLieu:=place du quadruplet (nmA,nmB,nmC,nmD) ds la table
	//si nLieu=0, attribuer un nouveau nom
	nAdHoc=nmA*nmD-nmB*nmC;
	return(nAdHoc);
}//nNomAdHoC

int bMatriceRehausseR(int uDiagonale,int bVoir,iMatrice **ppmT){
	//échanger autant que possible la ligne uDiagonale avec la ligne contenant le meilleur pivot.
	//const int kuInfini=kE9;
	int uC,uL,nLigneDuMeilleurPivot;
	//int nPivot;
	int bRehausser=kF;
	int bEchangerPaire;
	//int nSecante=(*ppmT)->nSecante;
	//nLigneDuMeilleurPivot:=ligne de même parité que uDiagonale contenant le meilleur pivot
		for (nLigneDuMeilleurPivot=0,uC=uDiagonale;uC<=(*ppmT)->nColonne && nLigneDuMeilleurPivot==0;uC+=2)
			for (uL=uDiagonale;uL<=(*ppmT)->nLigne;uL+=2)
				if ( nLigneDuMeilleurPivot==0 && ((*ppmT)->Mat[uL][uC]!=0) )
					nLigneDuMeilleurPivot=uL;
		bRehausser=(0<nLigneDuMeilleurPivot);
		if (bRehausser){ 
			if (bVoir) printf("Pivot primaire:%d (depuis diagonale=%d).\n",nLigneDuMeilleurPivot,uDiagonale);
			if (uDiagonale!=nLigneDuMeilleurPivot){
				Assert2("bMatriceRehausseR",bCroit(uDiagonale+1,nLigneDuMeilleurPivot,(*ppmT)->nLigne),nLigneDuMeilleurPivot%2==uDiagonale%2);
				//printf("Echange des doublets de lignes %d-%d et %d-%d.\n",uDiagonale,uDiagonale+1,nLigneDuMeilleurPivot,nLigneDuMeilleurPivot+1);
				bEchangerPaire=bMatriceEchangerPaire(k1LignE,uDiagonale,nLigneDuMeilleurPivot,!k1Voir,ppmT);
			}
		}
		//Assert1("bMatriceRehausseR0000",bRehausser);
	/*	} else if (bImpair(uDiagonale)){
			if (bVoir) Titrer("Echec pour trouver un pivot primaire");
			if (bVoir) tee("uDiagonale,nSecante",uDiagonale,nSecante);
			for (nLigneDuMeilleurPivot=0,uC=uDiagonale;uC<=(*ppmT)->nColonne && nLigneDuMeilleurPivot==0;uC++)
				for (uL=uDiagonale;uL<=(*ppmT)->nLigne;uL++)
					if ( nLigneDuMeilleurPivot==0 && (uL<=nSecante || uC<=nSecante) && ((*ppmT)->Mat[uL][uC]!=0) )
						nLigneDuMeilleurPivot=uL;
			if (nLigneDuMeilleurPivot>0){
				if (bVoir) printf("Pivot secondaire:%d (depuis diagonale=%d).\n",nLigneDuMeilleurPivot,uDiagonale);
				//printf("Echange des doublets de lignes %d-%d et %d-%d.\n",uDiagonale,uDiagonale+1,nLigneDuMeilleurPivot,nLigneDuMeilleurPivot+1);
				Assert1("MatriceRehausseR5",uDiagonale<nLigneDuMeilleurPivot);
				bRehausser=bMatriceEchangerPaire(k1LignE,uDiagonale,nLigneDuMeilleurPivot,bVoir,ppmT);
			}
			else if (bVoir) Titrer("Echec TOTAL pour trouver un pivot sécant");
		}
	}else {//RehausseR si possible la ligne contenant le plus petit pivot non nul
			for (nLigneDuMeilleurPivot=0,nPivot=kuInfini,uL=uDiagonale;uL<=(*ppmT)->nLigne;uL++)
				for (uC=uDiagonale;uC<=(*ppmT)->nColonne;uC++)
					if ( bCroitStrict(0,abs((*ppmT)->Mat[uL][uC]),nPivot) )
						(nLigneDuMeilleurPivot=uL,nPivot=abs((*ppmT)->Mat[uL][uC]));
			if (nLigneDuMeilleurPivot>0){
				if (nLigneDuMeilleurPivot>uDiagonale)
					if (bVoir) printf("Diagonale %d: Pivot tertiaire ligne %d ds bMatriceRehausseR.\n",uDiagonale,nLigneDuMeilleurPivot);
				Assert1("MatriceRehausseR6",nLigneDuMeilleurPivot>=uDiagonale);
				if (nLigneDuMeilleurPivot>uDiagonale)
					MatriceEchangerSingleton(k1LignE,uDiagonale,nLigneDuMeilleurPivot,!k1Voir,ppmT);
			}
			else if (bVoir) Titrer("Echec TOTAL pour trouver un pivot TERTIAIRE sécant");
	}*/
	return(bRehausser);
}//bMatriceRehausseR

int bMatriceRemonteR(int uDiagonale,int bVoir,iMatrice **ppmT){
	//échanger autant que possible la ligne uDiagonale avec la ligne ctenant le meilleur pivot, lequel est si possible interne à la sécante.
	const int kuInfini=kE9;
	int uC,uL,nLigneDuMeilleurPivot,nPivot;
	int nSecante=(*ppmT)->nSecante;
	int bRemonter=(uDiagonale<=nSecante);
	if (bRemonter){
		for (nLigneDuMeilleurPivot=0,uC=uDiagonale;uC<=nSecante && nLigneDuMeilleurPivot==0;uC++)
			for (uL=uDiagonale;uL<=nSecante;uL++)
				if ( nLigneDuMeilleurPivot==0 && ((*ppmT)->Mat[uL][uC]!=0) )
					nLigneDuMeilleurPivot=uL;
		if (0<nLigneDuMeilleurPivot){ 
			if (bVoir) printf("Pivot primaire:%d (depuis diagonale=%d).\n",nLigneDuMeilleurPivot,uDiagonale);
			if (uDiagonale!=nLigneDuMeilleurPivot){
				Assert1("bMatriceRemonteR",bCroit(uDiagonale+1,nLigneDuMeilleurPivot,nSecante));
				//printf("Echange des doublets de lignes %d-%d et %d-%d.\n",uDiagonale,uDiagonale+1,nLigneDuMeilleurPivot,nLigneDuMeilleurPivot+1);
				bRemonter=bMatriceEchangerPaire(k1LignE,uDiagonale,nLigneDuMeilleurPivot,!k1Voir,ppmT);
			}
		} else if (bImpair(uDiagonale)){
			if (bVoir) Titrer("Echec pour trouver un pivot primaire");
			if (bVoir) tee("uDiagonale,nSecante",uDiagonale,nSecante);
			for (nLigneDuMeilleurPivot=0,uC=uDiagonale;uC<=(*ppmT)->nColonne && nLigneDuMeilleurPivot==0;uC++)
				for (uL=uDiagonale;uL<=(*ppmT)->nLigne;uL++)
					if ( nLigneDuMeilleurPivot==0 && (uL<=nSecante || uC<=nSecante) && ((*ppmT)->Mat[uL][uC]!=0) )
						nLigneDuMeilleurPivot=uL;
			if (nLigneDuMeilleurPivot>0){
				if (bVoir) printf("Pivot secondaire:%d (depuis diagonale=%d).\n",nLigneDuMeilleurPivot,uDiagonale);
				//printf("Echange des doublets de lignes %d-%d et %d-%d.\n",uDiagonale,uDiagonale+1,nLigneDuMeilleurPivot,nLigneDuMeilleurPivot+1);
				Assert1("MatriceRemonteR5",uDiagonale<nLigneDuMeilleurPivot);
				bRemonter=bMatriceEchangerPaire(k1LignE,uDiagonale,nLigneDuMeilleurPivot,bVoir,ppmT);
			}
			else if (bVoir) Titrer("Echec TOTAL pour trouver un pivot sécant");
		}
	}else {//remonter si possible la ligne contenant le plus petit pivot non nul
			for (nLigneDuMeilleurPivot=0,nPivot=kuInfini,uL=uDiagonale;uL<=(*ppmT)->nLigne;uL++)
				for (uC=uDiagonale;uC<=(*ppmT)->nColonne;uC++)
					if ( bCroitStrict(0,abs((*ppmT)->Mat[uL][uC]),nPivot) )
						(nLigneDuMeilleurPivot=uL,nPivot=abs((*ppmT)->Mat[uL][uC]));
			if (nLigneDuMeilleurPivot>0){
				if (nLigneDuMeilleurPivot>uDiagonale)
					if (bVoir) printf("Diagonale %d: Pivot tertiaire ligne %d ds bMatriceRemonteR.\n",uDiagonale,nLigneDuMeilleurPivot);
				Assert1("MatriceRemonteR6",nLigneDuMeilleurPivot>=uDiagonale);
				if (nLigneDuMeilleurPivot>uDiagonale)
					MatriceEchangerSingleton(k1LignE,uDiagonale,nLigneDuMeilleurPivot,!k1Voir,ppmT);
			}
			else if (bVoir) Titrer("Echec TOTAL pour trouver un pivot TERTIAIRE sécant");
	}
	return(bRemonter);
}//bMatriceRemonteR

int bMatriceSainE(char *sMessage,iMatrice *pmA){
	int uC,uL,iValeur;
	int bSaine=kV;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nLigne;uC++){
			iValeur=pmA->Mat[uL][uC];
			bSaine=bSaine &&(iValeur!=-2147483648);
			/*if (!bSaine)
				t(sMessage);
			if (!bSaine)
				tee("uL,uC",uL,uC);
			Assert1("bMatriceSainE77777",iValeur!=-2147483648);*/
		}
	return(bSaine);
}//bMatriceSainE

void MatriceSimplifieR(int uDiagonale,iMatrice *pmA){
	//simplifie pmA[uDiagonale..][] en divisant les termes non nuls d'une ligne par le pgcd de leurs valeurs absolues.
	int uC,uL;
	long xPgcd,yValeur;
	for (uL=uDiagonale;uL<=pmA->nLigne;uL++){
		for (xPgcd=0,uC=uDiagonale;uC<=pmA->nColonne;uC++)
			if (yValeur=pmA->Mat[uL][uC],yValeur!=0)
				if (xPgcd==0)
					xPgcd=abs(yValeur);
				else xPgcd=zPgcd(xPgcd,abs(yValeur));
		if (bCroit(2,xPgcd,kuIntegerMax)){
			MatriceVoir("AVANT MatriceSimplifieR",pmA);
			for (printf("Division de la ligne %d par %ld.\n",uL,xPgcd),uC=uDiagonale;uC<=pmA->nColonne;uC++)
				if ( pmA->Mat[uL][uC]!=0)
					pmA->Mat[uL][uC]/=xPgcd;
			MatriceVoir("APRES MatriceSimplifieR",pmA);
		}
	}
}//MatriceSimplifieR

int bMatriceSingulariseR(iMatrice **ppmT,int *pnNom,int *pnEtape){
	//rend vrai ssi le déterminant de la matrice ppmT est nul;calcul exact par élimination gaussienne
	int uL,uC,uD,bDerouter,bSingulariser,iPivot,nPivot,nEtape,bSinguliere,nPermutation;
	int iFacteur[knLigneLiM];
	int iDD,iLC,iDC,iLD,uFois;
	long int xPpcm;
	int nImpropre;
	int iDeterminant;
	int bEchangerPaire;
	int bMiroir;
	int nSekante;
	int bRehausser;
	int iMultiplicande;
	int yzPivot,nNom,iValeur;
	int bVoir;
	nNom=*pnNom;
	//te("nNom",nNom);
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	//Titrer("bMatriceSingulariseR");
	Assert1("bMatriceSingulariseR1",bMatriceAntiSymetriquE(*ppmT));
nSekante=(*ppmT)->nSecante;
(*ppmT)->nSecante=0;
	MatriceVoir("ppmT original",*ppmT);
	bSingulariser=kV;
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		VecteurValuer(iFacteur,1,(*ppmT)->nLigne,1);
		if (0) VecteurVoir("iFacteur avant",iFacteur,1,(*ppmT)->nLigne);
		bMiroir=kF;
		for (nImpropre=0,bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=(*ppmT)->nLigne && nPivot>=uD-1 /*&& bSingulariser*/;uD++){
if (uD==nSekante-1)
	Titrer("nSekante rencontrée");
bVoir=bImpair(uD);
if (uD>=nSekante){//43
	bVoir=kV;
	(*ppmT)->nSecante=nSekante-1;
}
			if (bVoir) MatriceVoir(sC2b("ppmT courant au début de uD =",sEnt(uD)),*ppmT);
			//if (bVoir) MatriceVoir("ppmT courant",*ppmT);
			if (bVoir) tee("uD et Déterminant via yMatriceDeterminant",uD,yMatriceDeterminant(*ppmT));
			bRehausser=bMatriceRehausseR(uD,k1Voir,ppmT);
			if (!bRehausser && !bMiroir){
				Titrer("miroir en cours");
				for (uL=uD;uL<=(*ppmT)->nLigne;uL+=2)
					MatriceEchangerSingleton(!k1LignE,uL,uL+1,!k1Voir,ppmT);
				MatriceVoir("APRES MIROIR",*ppmT);
				bMiroir=kV;
				Titrer("miroir terminé");
				bRehausser=bMatriceRehausseR(uD,bVoir,ppmT);
			}
			Assert1("bMatriceSingulariseR464",bRehausser);

			//Assert1("bMatriceSingulariseR154",bPermutationSolidairE(*ppmT));
			//iPivot:=rg colonne du 1er terme non nul dans (*ppmT)->Mat[uD][uD..(*ppmT)->nColonne],au signe près
				iPivot=0;
				if (iPivot==0)
					for (uC=uD;uC<=(*ppmT)->nColonne;nEtape++,uC++){
						iValeur=(*ppmT)->Mat[uD][uC];
						if ( iPivot==0 && (iValeur!=0) && bPair(uD)==bPair(uC) )
							iPivot=uC;
					}
				if (iPivot==0 && uD>(*ppmT)->nSecante)
					for (uC=uD;uC<=(*ppmT)->nColonne;nEtape++,uC++){
						iValeur=(*ppmT)->Mat[uD][uC];
						if (iPivot==0 && iValeur!=0){
							iPivot=-uC;//négatif pr le repérer à l'affichage
							nImpropre++;
						}
					}
				Assert1("bMatriceSingulariseR7",bMatriceSainE("beta",*ppmT));
			if (iPivot<0)
				printf("Diagonale %d: Parité impropre n°%d et pivot %d.\n",uD,nImpropre,iPivot);
			if (bVoir) tee("uD et iPivot",uD,iPivot);
			//Assert1("bMatriceSingulariseR72",bSingulariser);
			nPivot=abs(iPivot);
			if (iPivot==0)
				tee("uD et iPivot nul",uD,iPivot);
			Assert1("Pivot nul",iPivot!=0);
			bDerouter=(nPivot==0) && uD<(*ppmT)->nLigne; 
			if (nPivot>=uD){
				bEchangerPaire=kV;
//if (bVoir) MatriceVoir("AVANT zérotage sous le pivot",*ppmT);
				if (uD!=nPivot){//échanger les colonnes nPivot et uD ainsi que,si bImpair(uD),les colonnes nPivot+1 et uD+1
					printf("Echange colonnes %d et %d",nPivot,uD);
					bEchangerPaire=(nPivot>0 && uD<(*ppmT)->nLigne && nPivot<(*ppmT)->nColonne);
					if (bEchangerPaire)
						printf("ainsi que les colonnes %d et %d",nPivot+1,uD+1);
					Ligne();
					if (bEchangerPaire)
						bEchangerPaire=bMatriceEchangerPaire(!k1LignE,uD,nPivot,bVoir,ppmT);
					else MatriceEchangerSingleton(!k1LignE,uD,nPivot,bVoir,ppmT);
					//if (kbMap) MatriceVoir("ppmT recolonné",*ppmT);
				}
				bSingulariser=bEchangerPaire;
				yzPivot=(*ppmT)->Mat[uD][uD];
				Assert1("bMatriceSingulariseR1",yzPivot!=0);
				//tee("uD,nmA",uD,nmA);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						iMultiplicande=0;
						for (iDD=yzPivot=(*ppmT)->Mat[uD][uD],uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							iLD=(*ppmT)->Mat[uL][uD];
							uFois=iMax(1,abs(iLD));
							xPpcm=zPpcm(abs(yzPivot),uFois);//donc xPpcm/iFois et xPpcm/yzPivot seront des divisions entières
							if (xPpcm>1 && bVoir)
								tee("uD et xPPcm",uD,xPpcm);
							if (iDD!=0)
								for (uC=(*ppmT)->nColonne;uC>=uD;nEtape++,uC--){
									iLC=(*ppmT)->Mat[uL][uC];
									iDC=(*ppmT)->Mat[uD][uC];
									//(*ppmT)->Mat[uL][uC]=iDD*iLC-iDC*iLD;
									if (iLD!=0){
										iMultiplicande=xPpcm/iLD;
										//Assert1("bMatriceSingulariseR44",abs(iMultiplicande)==1);bien exigeant!
										(*ppmT)->Mat[uL][uC]=-iLC*(xPpcm/iLD)+iDC*(xPpcm/yzPivot);
										iFacteur[uL]*=iMultiplicande;
									}
									if (!bMatriceSainE("zeta",*ppmT)){
										teeee("iDD,iLC,iDC,iLD",iDD,iLC,iDC,iLD);
										te("iDD*iLC",iDD*iLC);
									}
								}
						}
//if (bVoir) MatriceVoir("APRES zérotage sous le pivot",*ppmT);
					if (bVoiR) VecteurVoir("iFacteur",iFacteur,1,(*ppmT)->nLigne);
					//MatriceSimplifieR(uD,*ppmT);
				//if (kbMap) MatriceVoir(sC4b("ppmT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),*ppmT);//printf("******************\n");
			}else if (kV)
				printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	if (bSinguliere=kV,iDeterminant=0,bSingulariser){
		//iDeterminant/bSinguliere=déterminant/déterminant nul,ie au moins un polynome de la diagonale principale est nul
			for (bSinguliere=kF,iDeterminant=1,uD=1;uD<=(*ppmT)->nLigne;uD++){
				iDeterminant*=(*ppmT)->Mat[uD][uD];
				if ((*ppmT)->Mat[uD][uD]==0)
					bSinguliere=kV;
			}
		Assert1("bMatriceSingulariseR111117",bMatriceSainE("eta",*ppmT));
		//MatriceVoir(sC2b("ppmT triangulé then",sChoix0(bSinguliere && bDerouter,"(déroutement dû au pivot nul)")),*ppmT);
		*pnEtape=nEtape;
		if (0){
			for (uD=1;uD<=(*ppmT)->nLigne;uD++){
				iValeur=(*ppmT)->Mat[uD][uD];
				printf("Diag[%d]=%d %s.\n",uD,iValeur,(iValeur==0)?"************************************************":"");
				(*ppmT)->Mat[uL][nPivot+1]=(*ppmT)->Mat[uL][uD+1];
				(*ppmT)->Mat[uL][uD+1]=iValeur;
			}
		}
		//printf("Cette matrice %s singulière.\n",sEst(bSinguliere));
		Assert1("bMatriceSingulariseR233",bMatriceSainE("theta",*ppmT));
	}
	else ;//MatriceVoir(sC2b("ppmT triangulé else",sChoix0(bSinguliere && bDerouter,"(déroutement dû au pivot nul)")),*ppmT);
	if (!bSinguliere)
		Titrer("Succes, il y a une solution");
	else Titrer("Echec, pas de solution");
	//te("iDeterminant",iDeterminant);
	return(bSinguliere);
}//bMatriceSingulariseR

int bMatriceSingulierE(yMatricE **ppmT,int *pnEtape){
	//rend vrai ssi le déterminant de la matrice ppmT est nul;calcul exact sur les entiers par élimination gaussienne
	int uL,uC,uD,bDerouter,uP,nPivot,nEtape,bSinguliere,nPermutation;
	int iFois,uFois;
	long yzPivot,yValeur,xPgcd,xPgcd0,xPpcm,xElement,bSimplification;
	//xPgcd=zPgcd(316,4);
	//te("pgcd(316,4)",xPgcd);
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	MatriceVoyR("ppmT original",*ppmT);
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=(*ppmT)->nLigne && nPivot>=uD-1;uD++){
			//MatriceVoyR("ppmT courant",*ppmT);
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uP=1;uP<=(*ppmT)->nColonne;nEtape++,uP++){
					yValeur=(*ppmT)->Mat[uD][uP];
					if (nPivot==0 && (yValeur!=0))
						nPivot=uP;
				}
			//tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<(*ppmT)->nLigne; 
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (nPermutation++,uL=1;uL<=(*ppmT)->nLigne;nEtape++,uL++){
						yValeur=(*ppmT)->Mat[uL][nPivot];
						(*ppmT)->Mat[uL][nPivot]=(*ppmT)->Mat[uL][uD];
						(*ppmT)->Mat[uL][uD]=yValeur;
					}
					//MatriceVoyR("ppmT recolonné",*ppmT);
				}
				yzPivot=(*ppmT)->Mat[uD][uD];
				Assert1("bMatriceTrianguleR1",yzPivot!=0);
				//tee("uD,inPivot",uD,yzPivot);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux (leur ppcm suffit)
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						for (yzPivot=(*ppmT)->Mat[uD][uD],uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							iFois=(*ppmT)->Mat[uL][uD];
							uFois=iMax(1,abs((*ppmT)->Mat[uL][uD]));
							//te("iFois",iFois);
							xPpcm=zPpcm(abs(yzPivot),abs(uFois));//donc xPpcm/iFois et xPpcm/yzPivot seront des divisions entières
							for (uC=uD;uC<=(*ppmT)->nColonne;nEtape++,uC++){
								Assert1("bMatriceTrianguleR2",xPpcm % yzPivot==0);
								yValeur=(*ppmT)->Mat[uL][uC];
								if (iFois!=0)
									(*ppmT)->Mat[uL][uC]=-(*ppmT)->Mat[uL][uC]*(xPpcm/iFois)+(*ppmT)->Mat[uD][uC]*(xPpcm/yzPivot);
							}
						}
						//MatriceVoyR("ppmT pivoté",*ppmT);
					//simplifier si possible les lignes qui ont été traitées
						for (bSimplification=kF,uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							for (xPgcd=0,uC=1;uC<=(*ppmT)->nColonne;uC++)
								if ((*ppmT)->Mat[uL][uC]!=0){
									xElement=abs((*ppmT)->Mat[uL][uC]);
									xPgcd0=xPgcd;
									if (xPgcd==0)
										xPgcd=xElement;
									else xPgcd=zPgcd(xPgcd,xElement);
									//teeee("uL,xElement,xPgcd0,xPgcd",uL,xElement,xPgcd0,xPgcd);
								}
							if (xPgcd>1){
								//tee("uL,xPgcd",uL,xPgcd);
								for (uC=1;uC<=(*ppmT)->nColonne;uC++)
									if ((*ppmT)->Mat[uL][uC]!=0)
										(*ppmT)->Mat[uL][uC]/=xPgcd;
								bSimplification=kV;
							}
						}
						if (0 && bSimplification)
							MatriceVoyR("ppmT simplifié",*ppmT);
				MatriceVoyR(sC4b("ppmT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),*ppmT);//printf("******************\n");
			}else if (bVoiR)
				printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//bSinguliere=déterminant nul,ie au moins un terme de la diagonale principale est nul
		for (bSinguliere=kF,uD=1;uD<=(*ppmT)->nLigne;uD++)
			if ((*ppmT)->Mat[uD][uD]==0)
				bSinguliere=kV;
	MatriceVoyR(sC2b("ppmT triangulé",sChoix0(bSinguliere && bDerouter,"(déroutement dû au pivot nul)")),*ppmT);
	*pnEtape=nEtape;
	//te("bSinguliere APRES",bSinguliere);
	return(bSinguliere);
}//bMatriceSingulierE

void MatriceSomme3InitialiseR(int nLigneEnTout,int nColonneEnTout,int bOperandeGauche,iMatrice **ppmC){
	//[A a a; c 0 1]+ [1 0 b ; d d  B] =[A ab ; dc B]
	int uL;
	MatriceIntervaller2(nLigneEnTout,nColonneEnTout,ppmC);
	//MatriceRempliR(ppmC);facilite la mise au point de la présente routine
	if (bOperandeGauche){
		// ppmC a ses deux derniers vecteurs colonne identiques,sauf dernière ligne,laquelle a un 0 ds la pénultième colonne et un 1 ds la dernière.
			for (uL=1;uL<=(*ppmC)->nLigne-1;uL++)
				(*ppmC)->Mat[uL][(*ppmC)->nColonne-1]=(*ppmC)->Mat[uL][(*ppmC)->nColonne];
			(*ppmC)->Mat[(*ppmC)->nLigne][(*ppmC)->nColonne-1]=0;
			(*ppmC)->Mat[(*ppmC)->nLigne][(*ppmC)->nColonne]=1;
	} else {
		// ppmC a ses deux premiers vecteurs colonne identiques,sauf première ligne,laquelle a un 1 en colonne 1 et un 0 en colonne 2.
			for (uL=2;uL<=(*ppmC)->nLigne;uL++)
				(*ppmC)->Mat[uL][1]=(*ppmC)->Mat[uL][2];
			(*ppmC)->Mat[1][1]=1;
			(*ppmC)->Mat[1][2]=0;
	}
}//MatriceSomme3InitialiseR

void MatriceSommer1(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	//A+B=[A 0 ; 0 B]
	int uL,uC;
	MatriceRazer(ppmC);
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			(*ppmC)->Mat[uL][uC]=pmA->Mat[uL][uC];
	for (uL=1;uL<=pmB->nLigne;uL++)
		for (uC=1;uC<=pmB->nColonne;uC++)
			(*ppmC)->Mat[uL+pmA->nLigne][uC+pmA->nColonne]=pmB->Mat[uL][uC];
	(*ppmC)->nLigne=pmA->nLigne+pmB->nLigne;
	(*ppmC)->nColonne=pmA->nColonne+pmB->nColonne;
}//MatriceSommer1

void MatriceSommer2(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	//[A a]+ t[b B] =[A ab ; 0 B]
	int uL,uC;
	MatriceRazer(ppmC);
	// copier A ds C 
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne-1;uC++)
				(*ppmC)->Mat[uL][uC]=pmA->Mat[uL][uC];
	// copier B ds C 
		for (uL=2;uL<=pmB->nLigne;uL++)
			for (uC=1;uC<=pmB->nColonne;uC++)
				(*ppmC)->Mat[uL+pmA->nLigne-1][uC+pmA->nColonne-1]=pmB->Mat[uL][uC];
	// ajouter ab 
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmB->nColonne;uC++)
				(*ppmC)->Mat[uL][uC+pmA->nColonne-1]=pmA->Mat[uL][pmA->nColonne]*pmB->Mat[1][uC];
	(*ppmC)->nLigne=pmA->nLigne+pmB->nLigne-1;
	(*ppmC)->nColonne=pmA->nColonne+pmB->nColonne-1;
}//MatriceSommer2

void MatriceSommer3(iMatrice *pmA,iMatrice *pmB,iMatrice **ppmC){
	//[A a a ; c 0 1]+ [1 0 b ; d d  B] =[A ab ; dc B]
	const int kbMap=kV;
	int bIdentique;
	int uL,uC;
	//dénoncer les appels non valides
		Assert4("MatriceSommer30",pmA->nLigne>2,pmA->nColonne>2,pmB->nLigne>2,pmB->nColonne>2);
		// pmA a ses deux derniers vecteurs colonne identiques,sauf dernière ligne,laquelle a un 0 ds la pénultième colonne et un 1 ds la dernière.
			for (bIdentique=kV,uL=1;uL<=pmA->nLigne-1;uL++)
				bIdentique=bIdentique && pmA->Mat[uL][pmA->nColonne-1]==pmA->Mat[uL][pmA->nColonne];
			Assert3("MatriceSommer31",bIdentique,pmA->Mat[pmA->nLigne][pmA->nColonne-1]==0,pmA->Mat[pmA->nLigne][pmA->nColonne]==1);
		// pmB a ses deux premiers vecteurs colonne identiques,sauf première ligne,laquelle a un 1 en colonne 1 et un 0 en colonne 2.
			for (bIdentique=kV,uL=2;uL<=pmB->nLigne;uL++)
				bIdentique=bIdentique && pmB->Mat[uL][1]==pmB->Mat[uL][2];
			Assert3("MatriceSommer32",bIdentique,pmB->Mat[1][1]==1,pmB->Mat[1][2]==0);
	MatriceRazer(ppmC);
	// copier A ds C 
		for (uL=1;uL<=pmA->nLigne-1;uL++)
			for (uC=1;uC<=pmA->nColonne-2;uC++)
				(*ppmC)->Mat[uL][uC]=pmA->Mat[uL][uC];
	// copier B ds C 
		for (uL=2;uL<=pmB->nLigne;uL++)
			for (uC=3;uC<=pmB->nColonne;uC++)
				(*ppmC)->Mat[uL+pmA->nLigne-2][uC+pmA->nColonne-2-2]=pmB->Mat[uL][uC];
	// ajouter ab 
		for (uL=1;uL<=pmA->nLigne-1;uL++)
			for (uC=1;uC<=pmB->nColonne-2;uC++){
				(*ppmC)->Mat[uL][uC+pmA->nColonne-2]=pmA->Mat[uL][pmA->nColonne]*pmB->Mat[1][2+uC];
				if (kbMap)
					if ((*ppmC)->Mat[uL][uC+pmA->nColonne-2]==0)
						(*ppmC)->Mat[uL][uC+pmA->nColonne-2]=66;
					else (*ppmC)->Mat[uL][uC+pmA->nColonne-2]=77;
			}
	// ajouter dc 
		for (uL=2;uL<=pmB->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne-2;uC++){
				(*ppmC)->Mat[pmA->nLigne-1+uL-1][uC]=pmA->Mat[pmA->nLigne][uC]*pmB->Mat[uL][1];
				if (kbMap)
					if ((*ppmC)->Mat[pmA->nLigne-1+uL-1][uC]==0)
						(*ppmC)->Mat[pmA->nLigne-1+uL-1][uC]=66;
					else (*ppmC)->Mat[pmA->nLigne-1+uL-1][uC]=77;
			}
	(*ppmC)->nLigne=pmA->nLigne+pmB->nLigne-2;
	(*ppmC)->nColonne=pmA->nColonne+pmB->nColonne-4;
}//MatriceSommer3

int bMatriceSymetriquE(iMatrice *pmC){
	int uC,uL,bSymetrique;
	for (bSymetrique=kV,uL=1;uL<=pmC->nLigne;uL++){
		//bSymetrique=bSymetrique && pmC->Mat[uL][uL]==0;//restriction abusive
		for (uC=1;uC<uL;uC++)
			bSymetrique=bSymetrique && pmC->Mat[uL][uC]==pmC->Mat[uC][uL];
	}
	return(bSymetrique);
}//bMatriceSymetriquE

void MatriceSymetriser(iMatrice **ppmC){
	int uC,uL;
	for (uL=1;uL<=(*ppmC)->nLigne;uL++){
		(*ppmC)->Mat[uL][uL]=0;
		for (uC=1;uC<uL;uC++)
			(*ppmC)->Mat[uL][uC]=(*ppmC)->Mat[uC][uL];
	}
}//MatriceSymetriser

void MatRIceSymetriser(riMatrice **ppmK){
	int uC,uL;
	for (uL=1;uL<=(*ppmK)->nLigne;uL++){
		(*ppmK)->Mat[uL][uL]=riAff(0,0);
		for (uC=1;uC<uL;uC++)
			(*ppmK)->Mat[uL][uC]=(*ppmK)->Mat[uC][uL];
	}
}//MatRIceSymetriser

/*void MatriceSymetriser(iMatrice *pmA){
	//rend A * At
	iMatrice *pmB,*pmC;
	MatriceAllouer1(&pmB,pmA->nLigne);
		MatriceAllouer1(&pmC,pmA->nLigne);
			MatriceDupliquer(pmA,pmB);
			MatriceDupliquer(pmA,pmC);
			MatriceTransposer(pmC);
			MatriceMultiplier(pmB,pmC,&pmA);
		free(pmC);
	free(pmB);
	Assert1("MatriceSymetriser",bMatriceSymetriquE(pmA));
}//MatriceSymetriser
*/
void MatriceTESTER(int iTest){
	//teste le présent module
	int nAppel=0,bParfait,bOptimal;
	long zBarre,ySignature,yDeterminant;
	ri riDeterminant;
	int bSucces,nSommet;
	int uFois;
	float fDensiteh;
	iMatrice *pmA;
	iMatrice *pmB;
	iMatrice *pmC;
	iMatrice *pmE;
	riMatrice *pmK;
	oMatrice *pmoA;
	objet oDeterminant;
	graf *pgG;
	Appel0(sC2("MatriceTester,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:
				MatriceAllouer(&pmA);
				MatriceAllouer(&pmB);
				MatriceAllouer(&pmC);
					MatriceIdentiter(&pmA);
					MatriceFoisser(2,&pmA);
					MatriceIdentiter(&pmB);
					MatriceFoisser(3,&pmB);
					MatriceVoir("Matrice A",pmA);
					MatriceVoir("Matrice B",pmB);
					zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
					MatriceVoir("Matrice AxB",pmC);
				break;
			case 2:
				MatriceAllouer(&pmA);
				MatriceAllouer(&pmB);
				MatriceAllouer(&pmC);
					MatriceBander(1,&pmA);
					MatriceBander(-2,&pmB);
					MatriceVoir("Matrice A",pmA);
					MatriceVoir("Matrice B",pmB);
					zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
					MatriceVoir("Matrice AxB",pmC);
					//MatriceVoir("Matrice finale");
				//MatriceAllouer(0);
				break;
			case 3: DuoUtiliseR(duPireCaS);//enum eDuoUtiliseR {duDenombreR,duMinimiseR,duPireCaS,-};
				break;
			case 4:
				ModuloParFibonnaccI();
				break;
			case 5://multiplication standard
				MatriceAllouer(&pmA);
					MatriceAllouer(&pmB);
						MatriceAllouer(&pmC);
							fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmA);
							fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmB);
							MatriceVoir("Matrice A",pmA);
							MatriceVoir("Matrice B",pmB);
							zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
							MatriceVoir("Matrice AxB",pmC);
							te("zBarre",zBarre);
							ComplexitehAfficheR(zBarre);
				break;
			case 6: TriUtiliseR(tuSimplE);//enum eDuoUtiliseR {duDenombreR,duMinimiseR,duPireCaS,-};
				break;
			case 7:
				PpcmOptimalExhibeR();//Chaque produit hors diagonale d'un tenseur aurait 1 pour modulo et 1 multiplicO remplacerait N muliplicOs.
				break;
			case 8://décompostion en produit de nombres premiers
				//PremierVoiR();
				DecomposeR(60);
				DecomposeR(241);
				DecomposeR(904);
				DecomposeR(1);
				break;
			case 9://déterminant
				MatriceAllouer1(&pmA,3);
					MatriceIdentiter(&pmA);
					//MatriceFoisser(1,&pmA);
					//MatriceRempliR(&pmA);
					//pmA->nLigne=1;
					MatriceVoir("Matrice A",pmA);
					//zBarre=ySignatureCalculeR(pmA,k1Alterner,&nAppel);
					te("Déterminant",zBarre);
				break;
			case 10://unimodularité totale
				MatriceAllouer2(&pmA,3,4);
					pmA->Mat[1][1]=0;pmA->Mat[1][2]=1;pmA->Mat[1][3]=1;pmA->Mat[1][4]=0;//**** basculer pmA->Mat[1][4] basculera bMatriceTU()
					pmA->Mat[2][1]=0;pmA->Mat[2][2]=0;pmA->Mat[2][3]=1;pmA->Mat[2][4]=1;
					pmA->Mat[3][1]=0;pmA->Mat[3][2]=1;pmA->Mat[3][3]=0;pmA->Mat[3][4]=1;
					MatriceVoir("Matrice testée",pmA);
					bSucces=bMatriceTU(pmA);
					t(sC3b("La matrice ci-dessus",sEst(bSucces),"totalement unnimodulaire"));
				break;
			case 11://vérification de l'unimodularité des matrices d'intervalle
				MatriceAllouer(&pmA);
					for (uFois=1;uFois<80;uFois++){
						MatriceIntervaller2(3,4,&pmA);
						pmA->Mat[2][4]=0;//l'activation de cette instruction déclenche l'assertion qui suit lorsque uFois=55
						MatriceVoir(sC2("Matrice quasi-intervalle n°",sEnt(uFois)),pmA);
						bSucces=bMatriceTU(pmA);
						t(sC3b("La matrice ci-dessus",sEst(bSucces),"totalement unnimodulaire"));
						Assert1(sC3("Test n°",sEnt(uFois)," de totale unimodularité"),bSucces);
					}
				break;
			case 12://sommes de matrices TU
				MatriceAllouer(&pmA);
				MatriceAllouer(&pmB);
				MatriceAllouer(&pmC);
					/*MatriceIntervaller2(3,4,&pmA);
				pmA->Mat[pmA->nLigne][pmA->nColonne]=1;
					MatriceVoir("pmA",pmA);
					MatriceTU(pmA);
					MatriceIntervaller2(3,4,&pmB);
				pmB->Mat[1][1]=1;
				pmB->Mat[1][2]=0;
					MatriceVoir("pmB",pmB);
					MatriceTU(pmB);
					MatriceSommer1(pmA,pmB,&pmC);
					MatriceVoir("pmC1",pmC);
					MatriceSommer2(pmA,pmB,&pmC);
					MatriceVoir("pmC2",pmC);*/
					
					MatriceSomme3InitialiseR(10,8,kV,&pmA);
					MatriceVoir("pmA,opérande gauche compatible somme3",pmA);
					MatriceSomme3InitialiseR(9,10,kF,&pmB);
					MatriceVoir("pmB,opérande droit compatible somme3",pmB);
					MatriceSommer3(pmA,pmB,&pmC);
					MatriceVoir("pmC est la somme3 de pmA et pmB",pmC);
					//MatriceTU(pmC);
				break;
			case 13://déterminant complexe
				MatRIceAllouer(&pmK);
					pmK->nLigne=3;
					pmK->nColonne=3;
					MatRIceRazeR(&pmK);
					pmK->Mat[1][1]=riAff(+1,+1);
					pmK->Mat[2][3]=riAff(+1,+1);
					pmK->Mat[3][2]=riAff(+1,-1);
					MatRIceVoir("Matrice A",pmK);
					riDeterminant=riSignatureCalculeR(pmK,k1Alterner,&nAppel);
					tri("riDeterminant",riDeterminant);
				break;
			case 15:
				Titrer("Test terminant Mahajan vs Classique");
				MatriceAllouer(&pmE);
					MatryceAffecteR(6,&pmE);
					ySignature=ySignatureCalculeR(pmE,k1Alterner,&nAppel);//Récursion laborieuse
					//te("**********Déterminant Classique",ySignature);
					yDeterminant=yDeterminantKalculeR(pmE);
					//te("**********Déterminant Vinay",yDeterminant);
					tee("Vinay vs Classique",yDeterminant,ySignature);
					Assert1("Test Mahajan vs Classique",yDeterminant==ySignature);
				break;
			case 16:
				Titrer("Mahajan sur K24");
				MatriceAllouer1(&pmA,6);//raze
					pmA->Mat[1][3]=pmA->Mat[1][4]=pmA->Mat[1][5]=pmA->Mat[1][6]=1;
					pmA->Mat[2][3]=pmA->Mat[2][4]=pmA->Mat[2][5]=pmA->Mat[2][6]=1;
					MatriceAntisymetriser(&pmA);
					yDeterminant=yDeterminantKalculeR(pmA);
				break;
			case 18://affichage grande matrice
				MatriceAllouer1(&pmA,28);
					pmA->Mat[1][1]=1;
					pmA->Mat[1][1]=1;
					pmA->Mat[2][3]=1;
					pmA->Mat[2][3]=1;
					pmA->Mat[3][2]=1;
					pmA->Mat[3][2]=-1;
					MatriceVoir("Matrice A",pmA);
				break;
			case 19://affichage grande matrice
				MatriceAllouer1(&pmA,4);
					pmA->nSecante=4;
					MatriceBander(1,&pmA);MatriceBander(-1,&pmA);
					MatriceBander(3,&pmA);MatriceBander(-3,&pmA);
					MatriceHasarder(pmA,9);
					MatriceSymetriser(&pmA);
					MatriceVoir("Matrice A1",pmA);
					yBof=ySignatureKalculeR(pmA,!k1Alterner,&nAppel);
					te("Signature à sécante nulle",yBof);
					/*pmA->nSecante=4;
					MatriceVoir("Matrice A2",pmA);
					yBof=ySignatureKalculeR(pmA,!k1Alterner,&nAppel);
					te("Signature à sécante non nulle",yBof);*/
				break;
			case 20://signature
					SygnaturePredirE();
					break;
			case 22://MatriceEchafaudeR
					MatriceEchafaudeR(nSommet=2,k1Simple);
					break;
			case 23://MatriceEchafaudeR
					MatriceEchafaudeR(nSommet=3,k1Simple);
					break;
			case 24://MatriceEchafaudeR
					MatriceEchafaudeR(nSommet=4,!k1Simple);
					break;
			case 25://bGrapheQuadripoleR
				MatriceAllouer(&pmA);
					GrapheCreer0(&pgG,kV);
						bGrapheQuadripoleR(pgG,!k1Areter,nSommet=2*10+0,&pmA);
						MatriceVoir("Matrice du quadripole",pmA);
					GrapheCreer0(&pgG,kF);
					break;
			case 29://GrapheEtirer
				GrapheCreer0(&pgG,kV);
					GrapheEtireR(pgG,30);
					GrapheVoir(pgG,"Graphe étiré");
				GrapheCreer0(&pgG,kF);
			break;
			case 30://GrapheExtirpeR
				GrapheCreer0(&pgG,kV);
					GrapheExtirpeR(pgG,30);
					//GrapheVoir(pgG,"Graphe extirpé");
				GrapheCreer0(&pgG,kF);
				//MatriceEchafaudeR(nSommet=3);
			break;
			case 50://MatriceCoupler
				MatriceAllouer1(&pmA,4);
					MatriceBander(2,&pmA);
					MatriceSymetriser(&pmA);
					MatriceVoir("Matrice à tourer",pmA);
					MatriceCoupler(pmA,&bParfait,&bOptimal);
				break;
			case 51://MatriceTourTourer
				MatriceAllouer1(&pmA,6);
					MatriceAffecteR(pmA,!k1Voir);
					pmA->nLigne=pmA->nColonne=6;
					MatriceVoir("Matrice à tourer",pmA);
					MatriceTourTourer(pmA);
				break;
			case 52://MatriceTourTourer
				MatriceAllouer1(&pmA,8);
					MatriceAffecteR(pmA,!k1Voir);
					MatriceVoir("Matrice à tourer",pmA);
					MatriceTourTourer(pmA);
				break;
			case 60://F(0)=0,F(1)=1,F(2)=1,F(3)=2,F(4)=3,F(5)=5,F(6)=8,F(7)=13,F(8)=21,F(9)=34 et F(10)=55.
				for (uFois=1;uFois<=12;uFois++)
					nBof=nFibonacciDeterminanT(uFois);
				break;
			case 61:for (uFois=1;uFois<=5;uFois++)
						MatriceCarrehNuL(uFois);
			case 62://matrice d'objets
						MatriceAllouher(&pmoA,matEntier);
						MatriceRazOueR(&pmoA);
						pmoA->nColonne=pmoA->nLigne=2;
						pmoA->Mat[1][1].ent=2;pmoA->Mat[1][2].ent=3;pmoA->Mat[2][1].ent=4;pmoA->Mat[2][2].ent=5;
						MatriceVOir("matrice d'objets maEntier",pmoA);
						oDeterminant=oDeterminantCalculeR(pmoA);
						ObjetVoiR("oDeterminant",oDeterminant,matEntier);
						free(pmoA);
						MatriceAllouher(&pmoA,matRect);
						MatriceRazOueR(&pmoA);
						pmoA->nColonne=pmoA->nLigne=2;
NbAffecter(2,&pmoA->Mat[1][1].mm.q11);NbAffecter(0,&pmoA->Mat[1][1].mm.q12);NbAffecter(0,&pmoA->Mat[1][1].mm.q21);NbAffecter(2,&pmoA->Mat[1][1].mm.q22);
NbAffecter(3,&pmoA->Mat[1][1].mm.q11);NbAffecter(0,&pmoA->Mat[1][1].mm.q12);NbAffecter(0,&pmoA->Mat[1][1].mm.q21);NbAffecter(3,&pmoA->Mat[1][1].mm.q22);
NbAffecter(4,&pmoA->Mat[1][1].mm.q11);NbAffecter(0,&pmoA->Mat[1][1].mm.q12);NbAffecter(0,&pmoA->Mat[1][1].mm.q21);NbAffecter(4,&pmoA->Mat[1][1].mm.q22);
NbAffecter(5,&pmoA->Mat[1][1].mm.q11);NbAffecter(0,&pmoA->Mat[1][1].mm.q12);NbAffecter(0,&pmoA->Mat[1][1].mm.q21);NbAffecter(5,&pmoA->Mat[1][1].mm.q22);
						MatriceVOir("matrice d'objets matRect",pmoA);
						oDeterminant=oDeterminantCalculeR(pmoA);
						ObjetVoiR("oDeterminant",oDeterminant,matRect);
						free(pmoA);
			case 63://matrice de carrés nuls
			t("1");
						MatriceAllouher(&pmoA,matRect);
			t("2");
							MatriceRazOueR(&pmoA);
			t("3");
							pmoA->nColonne=pmoA->nLigne=6;
							pmoA->Mat[1][2].mm=pmoA->Mat[2][3].mm=qQuad(1);
							pmoA->Mat[2][1].mm=pmoA->Mat[3][2].mm=qQuad(2);
							pmoA->Mat[4][5].mm=pmoA->Mat[5][6].mm=qQuad(3);
							pmoA->Mat[5][4].mm=pmoA->Mat[6][5].mm=qQuad(4);
							pmoA->Mat[4][1].mm=qQuad(5);
							pmoA->Mat[3][6].mm=qQuad(6);
							//MatriceVhoir("matrice d'objets matRect",pmoA);
			t("4");
							oDeterminant=oDeterminantCalculeR(pmoA);
			t("5");
							ObjetVoiR("oDeterminant",oDeterminant,pmoA->typ);
						free(pmoA);
				break;
			default:
				break;
		}
	Appel1(sC2("MatriceTester,test n°",sEnt(iTest)));
}//MatriceTESTER

void MatriceTourTourer(iMatrice *pmA){
	//rend le nombre maximal de tours-tours qui peuvent être conservées dans la matrice de sorte qu'aucune tour ne soit en prise par une autre.
	const int knCapaciteMinimaleNulle=0;
	const int kuCapaciteMaximale=1;
	int cPasse;
	int bParfait,nPoids=1;
	int uL,uC,uK,sX;
	int sL,sC;
	graf *pgG;
	int sColonne[1+pmA->nColonne];
	int sLigne[1+pmA->nLigne];
	int uMatriceIndex0[kuGrapheArcLim];//excessif
	int uMatriceIndex1[kuGrapheArcLim];//excessif
	int nSommet,nSommetInterfacable;
	Assert2("MatriceTourTourer0",bPair(pmA->nLigne),bPair(pmA->nColonne));
	//sLigne[uL],sColonne[uC]:= un sommet qui identifie le doublet de lignes, de colonnes:
		for (uL=1;uL<=pmA->nLigne;uL++)
			sLigne[uL]=(uL+1)/2;
		for (uC=1;uC<=pmA->nColonne;uC++)
			sColonne[uC]=pmA->nLigne/2+(uC+1)/2;
	nSommetInterfacable=pmA->nLigne/2+pmA->nColonne/2;
	GrapheCreer0(&pgG,kV);
		for (cPasse=0;cPasse<=1;cPasse++){
			if (cPasse==1){//nSommet,calculé à cPasse==0,est le nombre total de sommets de pgG
				//te("nSommet",nSommet);
				pgG->nSommetEnTout=nSommet;
				for (sX=1;sX<=pgG->nSommetEnTout+1;sX++)
					pgG->aHed[sX]=1;
				pgG->nArcEnTout=0;
			}
			nPoids=2;
			for (nSommet=nSommetInterfacable,uL=1;uL<=pmA->nLigne;uL+=2)
				for (uC=1;uC<=pmA->nColonne;uC+=2)
					if (abs(pmA->Mat[uL][uC])==nPoids){
						Assert1("MatriceTourTourer1",abs(pmA->Mat[uL+1][uC+1])==abs(pmA->Mat[uL][uC]));
						sL=++nSommet;sC=++nSommet;
						//teeee("sLigne[uL],sL,sC,sColonne[uC]",sLigne[uL],sL,sC,sColonne[uC]);
						uMatriceIndex0[sL]=uL;uMatriceIndex0[sC]=uC;uMatriceIndex1[sL]=uL+1;uMatriceIndex1[sC]=uC+1;
						if (cPasse==1){
							//teeee("ARCAGE poids 2 sLigne[uL],sL,sC,sColonne[uK]",sLigne[uL],sL,sC,sColonne[uC+1]);
							GrapheArquer3(pgG,sLigne[uL],sL,knCapaciteMinimaleNulle,kuCapaciteMaximale,0);
							GrapheArquer3(pgG,sL,sC,knCapaciteMinimaleNulle,kuCapaciteMaximale,nPoids);
							GrapheArquer3(pgG,sC,sColonne[uC+1],knCapaciteMinimaleNulle,kuCapaciteMaximale,0);
						}
					}
			nPoids=1;
			for (uL=1;uL<=pmA->nLigne;uL+=2)
				for (uC=2;uC<=pmA->nColonne;uC+=2)
					if (abs(pmA->Mat[uL][uC])==nPoids)
						for (uK=1;uK<=pmA->nColonne;uK+=2)
							if (abs(pmA->Mat[uL+1][uK])==abs(pmA->Mat[uL][uC])){
								sL=++nSommet;sC=++nSommet;
								//if (cPasse==1) tee("hhhh uL,uC",uL,uC);
								//teeee("sLigne[uL],sL,sC,sColonne[uC]",sLigne[uL],sL,sC,sColonne[uC]);
								uMatriceIndex0[sL]=uL;uMatriceIndex0[sC]=uC;uMatriceIndex1[sL]=uL+1;uMatriceIndex1[sC]=uK;
								if (cPasse==1){
									//teeee("ARCAGE poids 1 sLigne[uL],sL,sC,sColonne[uK]",sLigne[uL],sL,sC,sColonne[uK]);
									GrapheArquer3(pgG,sLigne[uL],sL,knCapaciteMinimaleNulle,kuCapaciteMaximale,0);
									GrapheArquer3(pgG,sL,sC,knCapaciteMinimaleNulle,kuCapaciteMaximale,nPoids);
									GrapheArquer3(pgG,sC,sColonne[uK],knCapaciteMinimaleNulle,kuCapaciteMaximale,0);
								}
							}
		}//cPasse
		GrapheSymetriser(pgG);
		GrapheVoir4(pgG,"APRES symétrisation");
		//te("nSommetInterfacable",nSommetInterfacable);
		//négativer pgG->aHed[sX] lorsque sX n'est pas connectable à une source ou une trappe ——pour CouplageOptimiser
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=iSignePres(nSommetInterfacable<sX,pgG->aHed[sX]);
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout);
		bParfait=bCouplageOptimiser(pgG,k1Poids,k1Maximum);
		//VecteurVoir("pgG->aDeh",pgG->sPer[],1,pgG->nSommetEnTout);
		//négativer les éléments de pmA qui ont été choisis ——pgG->sPer[] contient une copie du couplage résultant 
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (pgG->sPer[sX]>0){
					uL=uMatriceIndex0[sX];uC=uMatriceIndex0[pgG->sPer[sX]];
					//tee("uL,uC",uL,uC);
					if (sX<pgG->sPer[sX])
						pmA->Mat[uL][uC]=-pmA->Mat[uL][uC];
					uL=uMatriceIndex1[sX];uK=uMatriceIndex1[pgG->sPer[sX]];
					//tee("uL,uC",uL,uK);
					if (sX<pgG->sPer[sX])
						pmA->Mat[uL][uK]=-pmA->Mat[uL][uK];
				}
		//for (uL=1;uL<=pmA->nLigne;uL++) VecteurVoir("pmA[uL]",pmA->Mat[uL],1,pmA->nLigne);
		MatriceVoir("MatriceTourTourer FINALE",pmA);
	GrapheCreer0(&pgG,kF);
}//MatriceTourTourer

int bMatriceTrianguleR(yMatricE **ppmT,int *pnEtape){
	//rend vrai ssi le déterminant de la matrice ppmT est non nul;calcul exact sur les entiers par la méthode de Gauss
	int uL,uC,uD,bDerouter,uP,nPivot,nEtape,bTrianguler,nPermutation;
	int iFois,uFois;
	long yzPivot,yValeur,xPgcd,xPgcd0,xPpcm,xElement,bSimplification;
	//xPgcd=zPgcd(316,4);
	//te("pgcd(316,4)",xPgcd);
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	//t("bMatriceTrianguleR");
	MatriceVoyR("ppmT original",*ppmT);
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=(*ppmT)->nLigne && nPivot>=uD-1;uD++){
			//MatriceVoyR("ppmT courant",*ppmT);
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uP=1;uP<=(*ppmT)->nColonne;nEtape++,uP++){
					yValeur=(*ppmT)->Mat[uD][uP];
					if (nPivot==0 && (yValeur!=0))
						nPivot=uP;
				}
			//tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<(*ppmT)->nLigne; 
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (nPermutation++,uL=1;uL<=(*ppmT)->nLigne;nEtape++,uL++){
						yValeur=(*ppmT)->Mat[uL][nPivot];
						(*ppmT)->Mat[uL][nPivot]=(*ppmT)->Mat[uL][uD];
						(*ppmT)->Mat[uL][uD]=yValeur;
					}
					//MatriceVoyR("ppmT recolonné",*ppmT);
				}
				yzPivot=(*ppmT)->Mat[uD][uD];
				Assert1("bMatriceTrianguleR1",yzPivot!=0);
				//tee("uD,inPivot",uD,yzPivot);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux (leur ppcm suffit)
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						for (yzPivot=(*ppmT)->Mat[uD][uD],uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							iFois=(*ppmT)->Mat[uL][uD];
							uFois=iMax(1,abs((*ppmT)->Mat[uL][uD]));
							//te("iFois",iFois);
							xPpcm=zPpcm(abs(yzPivot),abs(uFois));//donc xPpcm/iFois et xPpcm/yzPivot seront des divisions entières
							for (uC=uD;uC<=(*ppmT)->nColonne;nEtape++,uC++){
								Assert1("bMatriceTrianguleR2",xPpcm % yzPivot==0);
								yValeur=(*ppmT)->Mat[uL][uC];
								if (iFois!=0)
									(*ppmT)->Mat[uL][uC]=-(*ppmT)->Mat[uL][uC]*(xPpcm/iFois)+(*ppmT)->Mat[uD][uC]*(xPpcm/yzPivot);
							}
						}
						//MatriceVoyR("ppmT pivoté",*ppmT);
					//simplifier si possible les lignes qui ont été traitées
						for (bSimplification=kF,uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							for (xPgcd=0,uC=1;uC<=(*ppmT)->nColonne;uC++)
								if ((*ppmT)->Mat[uL][uC]!=0){
									xElement=abs((*ppmT)->Mat[uL][uC]);
									xPgcd0=xPgcd;
									if (xPgcd==0)
										xPgcd=xElement;
									else xPgcd=zPgcd(xPgcd,xElement);
									//teeee("uL,xElement,xPgcd0,xPgcd",uL,xElement,xPgcd0,xPgcd);
								}
							if (xPgcd>1){
								//tee("uL,xPgcd",uL,xPgcd);
								for (uC=1;uC<=(*ppmT)->nColonne;uC++)
									if ((*ppmT)->Mat[uL][uC]!=0)
										(*ppmT)->Mat[uL][uC]/=xPgcd;
								bSimplification=kV;
							}
						}
						if (0 && bSimplification)
							MatriceVoyR("ppmT simplifié",*ppmT);
				MatriceVoyR(sC4b("ppmT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),*ppmT);//printf("******************\n");
			}else if (bVoiR)
				printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//bTrianguler=déterminant non nul,ie aucun élément de la diagonale principale n'est nul
		for (bTrianguler=kV,uD=1;uD<=(*ppmT)->nLigne;uD++)
			if ((*ppmT)->Mat[uD][uD]==0)
				bTrianguler=kF;
	MatriceVoyR(sC2b("ppmT triangulé",sChoix0(!bTrianguler && bDerouter,"(déroutement dû au pivot nul)")),*ppmT);
	*pnEtape=nEtape;
	//te("bTrianguler APRES",bTrianguler);
	return(bTrianguler);
}//bMatriceTrianguleR

double dMatriceTrianguleR(dMatricE **ppmT,int bVoir,int *pnEtape){
	const int kbVise=kF;
	int uL,uLmax,nLignat,uC,uD,nPivot,nEtape,nRecolonnage;
	double dDeterminant,dFois,dnPivot,dValeur,dOptimum;
	nLignat=(*ppmT)->nLigne;
	nEtape=0;//mesure de la complexité algorithmique
	if (bVoir) MatriceVoirReeL("AVANT matrice triangulée",*ppmT);
	//transformer ppmT en matrice triangulaire supérieure;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (nRecolonnage=0,uD=1;uD<=(*ppmT)->nLigne;uD++){
			if (kbVise) MatriceVoirReeL("ppmT non recolonné",*ppmT);
			//uLmax:=ligne>=uD contenant le pivot maximal en valeur absolue
				for (dOptimum=0.0,uLmax=uD,uL=uD;uL<=(*ppmT)->nLigne;uL++)
					for (uC=1;uC<=(*ppmT)->nColonne;uC++)
						if ( dOptimum< abs((*ppmT)->Mat[uL][uC])){
							dOptimum=abs((*ppmT)->Mat[uL][uC]);
							uLmax=uL;
						}
			if (uD!=uLmax){//échanger les lignes uLmax et uD
				for (uC=1;uC<=(*ppmT)->nColonne;nEtape++,uC++){
					dValeur=(*ppmT)->Mat[uLmax][uC];
					(*ppmT)->Mat[uLmax][uC]=(*ppmT)->Mat[uD][uC];
					(*ppmT)->Mat[uD][uC]=dValeur;
				}
				nRecolonnage++;
			}
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uC=1;uC<=(*ppmT)->nColonne;uC++){
					dValeur=(*ppmT)->Mat[uD][uC];
					nEtape++;
					if (nPivot==0 && !bNul(dValeur))
						nPivot=uC;
				}
				//tee("uD,nPivot",uD,nPivot);
				//Assert1("dMatriceTrianguleR9",nPivot!=0);
			//dValeur=0.5;
			//tb("bNul(dValeur)",bNul(dValeur));
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (uL=1;uL<=(*ppmT)->nLigne;nEtape++,uL++){
						dValeur=(*ppmT)->Mat[uL][nPivot];
						(*ppmT)->Mat[uL][nPivot]=(*ppmT)->Mat[uL][uD];
						(*ppmT)->Mat[uL][uD]=dValeur;
					}
					//if two rows are interchanged in a determinant,then the sign of the determinant changes (p260).
					nRecolonnage++;
					if (kbVise) MatriceVoirReeL("ppmT recolonné",*ppmT);
				}
				dnPivot=(*ppmT)->Mat[uD][uD];
				Assert1("dMatriceTrianguleR2",!bNul(dnPivot));
				//tee("uD,inPivot",uD,inPivot);
				//retrancher du terme (*ppmT)->Mat[uL][uC] le terme ((*ppmT)->Mat[uD][uC]*iFois)/inPivot
					for (uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
						dFois=(*ppmT)->Mat[uL][uD];
						//tr("dFois",dFois);
						for (uC=(*ppmT)->nColonne;uC>=uD;uC--){
							//printf("dFois/dnPivot=%.3f/%.3f.\n",dFois,dnPivot);
							nEtape++;
							dValeur=(*ppmT)->Mat[uD][uC]*dFois;
							/*if (1){
								if (!bNul(dValeur%dnPivot))
									printf("(*ppmT)->Mat[%d][%d]*dFois/dnPivot=%f*%f/%d %s un nombre entier.\n",uD,uC,(*ppmT)->Mat[uD][uC],iFois,inPivot,sEst(iValeur%inPivot==0));
								Assert1("nMatriceTrianguleR5",iValeur%inPivot==0);
							}*/
							(*ppmT)->Mat[uL][uC]=(*ppmT)->Mat[uL][uC] - (*ppmT)->Mat[uD][uC]*dFois/dnPivot;
						}
					}
				if (kbVise) {MatriceVoirReeL("ppmT pivoté",*ppmT);printf("******************\n");}
			}
		}
	if (nPivot==0)//1 ligne au moins est nulle dc la matrice triangulaire supérieure nulle est une solution valide pr le calcul du déterminant.
		for (uL=1;uL<=(*ppmT)->nLigne;uL++)
			for (uC=1;uC<=(*ppmT)->nColonne;uC++)
				(*ppmT)->Mat[uL][uC]=0.0;
	*pnEtape=nEtape;
	if (bVoir) MatriceVoirReeL("APRES matrice triangulée",*ppmT);
	//dDeterminant:=produit des termes diagonaux
		for (dDeterminant=1.0,uD=1;uD<=(*ppmT)->nLigne;uD++)
			dDeterminant*=(*ppmT)->Mat[uD][uD];
		if (bImpair(nRecolonnage))
			dDeterminant=-dDeterminant;
	return(dDeterminant);
}//dMatriceTrianguleR

objet oMatriceTrianguleR(oMatrice **ppmoT,int *pnEtape){
	//rend le déterminant de la matrice ppmoT;calcul exact sur les entiers par la méthode de Gauss
	int uL,uC,uD,bDerouter,uP,nPivot,nEtape,bTrianguler,nPermutation;
	objet oAntiDiag,oDiag,oDessous,ozPivot,oTrianguler,oCible;
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	//t("oMatriceTrianguleR");
	Assert1("oMatriceTrianguleR",(*ppmoT)->typ==matRect);
	//MatriceVhoir("ppmoT original",*ppmoT);
	//transformer ppmoT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale principale de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=(*ppmoT)->nLigne && nPivot>=uD-1;uD++){
			MatriceVOir(sC2("ppmoT courant n°",sEnt(uD)),*ppmoT);
			//nPivot:=rg du 1er terme non nul sur la ligne courante uD
				for (nPivot=0,uP=1;uP<=(*ppmoT)->nColonne;nEtape++,uP++)
					if ( nPivot==0 && !bObjetNuL((*ppmoT)->Mat[uD][uP],(*ppmoT)->typ) )
						nPivot=uP;
			//tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<(*ppmoT)->nLigne; 
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes uD et nPivot
					//printf("échange des colonnes %d et %d:\n",uD,nPivot);
					for (nPermutation++,uL=1;uL<=(*ppmoT)->nLigne;nEtape++,uL++){
						oCible=(*ppmoT)->Mat[uL][nPivot];
						(*ppmoT)->Mat[uL][nPivot]=(*ppmoT)->Mat[uL][uD];
						(*ppmoT)->Mat[uL][uD]=oCible;
					}
					//MatriceVhoir(sC2b("ppmoT recolonné, colonnes",sCouple(uD,nPivot)),*ppmoT);
				}
				ozPivot=(*ppmoT)->Mat[uD][uD];
				Assert1("bMatriceTrianguleR1",!bObjetNuL(ozPivot,(*ppmoT)->typ));
				//ObjetVoiR(sC2("ozPivot sur diag n°",sEnt(uD)),ozPivot,(*ppmoT)->typ);
				//introduire des 0 en colonne uD en soustrayant la ligne uD du pivot de la ligne courante uL>uD
					for (uL=uD+1;uL<=(*ppmoT)->nLigne;uL++){
						oDessous=(*ppmoT)->Mat[uL][uD];//sauvegarde la valeur originale
						if (!bObjetNuL(oDessous,(*ppmoT)->typ)){
							//ObjetVoiR("oDessous",oDessous,(*ppmoT)->typ);
							for (uC=uD;uC<=(*ppmoT)->nColonne;nEtape++,uC++){
								oCible=(*ppmoT)->Mat[uL][uC];
								//ObjetVoiR("oCible",oCible,(*ppmoT)->typ);
								oDiag=oObjetMuL(ozPivot,oCible,(*ppmoT)->typ);
								//ObjetVoiR("oDiag",oDiag,(*ppmoT)->typ);
								oAntiDiag=oObjetMuL((*ppmoT)->Mat[uD][uC],oCible,(*ppmoT)->typ);
								//ObjetVoiR("oAntiDiag",oAntiDiag,(*ppmoT)->typ);
								(*ppmoT)->Mat[uL][uC]=oObjetSuB(oDiag,oAntiDiag,(*ppmoT)->typ);
							}
						}
					}
					//MatriceVhoir("ppmoT pivoté",*ppmoT);
				//MatriceVhoir(sC4b("ppmoT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),*ppmoT);//printf("******************\n");
			}else if (bVoiR)
				printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//bTrianguler=aucun élément de la diagonale principale n'est nul
		for (bTrianguler=kV,uD=1;uD<=(*ppmoT)->nLigne;uD++)
			if (bObjetNuL((*ppmoT)->Mat[uD][uD],(*ppmoT)->typ))
				bTrianguler=kF;
		//tb("bTrianguler",bTrianguler);
	MatriceVOir(sC2b("ppmoT triangulé",sChoix0(!bTrianguler && bDerouter,"(déroutement dû au pivot nul)")),*ppmoT);
	*pnEtape=nEtape;
	//tb("Zéro dans la diagonale",!bTrianguler);
	oTrianguler.mm=qQuad(bTrianguler);
	ObjetVoiR("oTrianguler",oTrianguler,(*ppmoT)->typ);
	return(oTrianguler);
}//oMatriceTrianguleR

void MatriceTrieR(iMatrice *pmA){
	int nBit;
	int uK,uL,uC;
	int uMeilleur;
	long zRang[knLigneLiM];
	iMatrice *pmB;
	MatriceAllouer(&pmB);
	//MatriceVoir("Avant MatriceDupliquer",pmA);
	MatriceDupliquer(pmA,pmB);
	//MatriceVoir("Apres MatriceDupliquer",pmB);
	//pmA reprend les lignes de pmA, mais triées par densité  décroissante
		//MatriceVoir("Avant MatriceTrieR",pmA);
		for (uL=1;uL<=knLigneMaX;uL++)
			for (zRang[uL]=0,uC=1;uC<=knLigneMaX;uC++)
				zRang[uL]=zRang[uL]*2+pmA->Mat[uL][uC];
		for (uK=1;uK<=knLigneMaX;uK++){
			for (uMeilleur=1,uL=1;uL<=knLigneMaX;uL++){
				if (zRang[uL]>zRang[uMeilleur])
					uMeilleur=uL;
			}
			Assert1("uMeilleur",bCroit(1,uMeilleur,knLigneMaX));
			for (uC=1;uC<=knLigneMaX;uC++){
				nBit=pmA->Mat[uMeilleur][uC];
				pmB->Mat[uK][uC]=nBit;
			}
			zRang[uMeilleur]=0;
		}
		MatriceDupliquer(pmB,pmA);
		//MatriceVoir("MatriceTrieR,tri lignes",pmA);
	//pmA reprend les colonnes de pmA, mais triées par densité  décroissante
		for (uC=1;uC<=knLigneMaX;uC++)
			for (zRang[uC]=0,uL=1;uL<=knLigneMaX;uL++)
				zRang[uC]=zRang[uC]*2+pmA->Mat[uL][uC];
		for (uK=1;uK<=knLigneMaX;uK++){
			for (uMeilleur=1,uC=1;uC<=knLigneMaX;uC++)
				if (zRang[uC]>zRang[uMeilleur])
					uMeilleur=uC;
			for (uL=1;uL<=knLigneMaX;uL++)
				pmB->Mat[uL][uK]=pmA->Mat[uL][uMeilleur];
			zRang[uMeilleur]=0;
		}
		MatriceDupliquer(pmB,pmA);
		//MatriceVoir("MatriceTrieR,tri colonnes",pmA);
	//MatriceVoir("Apres MatriceTrieR",pmB);
}//MatriceTrieR

void MatriceTrierTouT(iMatrice *pmA){
	int bEffacer,nCompteMax,nLigne,nColon;
	int nBaton,uL,uC,nTri=0;
	iMatrice *pmB;
	MatriceAllouer(&pmB);
	MatriceDupliquer(pmA,pmB);
	MatriceVoir("Avant MatriceTrierTouT",pmB);
	for (nBaton=0,uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			if (pmB->Mat[uL][uC]>0)
				nBaton++;
	nCompteMax=0;
	do{
		MatriceTrieR(pmB);
		nTri++;
		te("tri n°",nTri);
		//MatriceVoir(sC2p("Matrice triée après le tri n°",sEnt(nTri)),pmB);
		for (nLigne=0,uC=1;uC<=knLigneMaX;uC++)
			if (pmB->Mat[1][uC]>0)
				nLigne++;
		for (nColon=0,uL=1;uL<=knLigneMaX;uL++)
			if (pmB->Mat[uL][1]>0)
				nColon++;
		nCompteMax+=nLigne*nColon;
		for (uL=1;uL<=knLigneMaX;uL++){
			for (bEffacer=kV,uC=1;uC<=knLigneMaX && bEffacer;uC++)
				if (pmB->Mat[uL][uC]>0){
					pmB->Mat[uL][uC]=0;
					nBaton--;
				}
				else bEffacer=kF;
		}
		//if (bEffacage)
		//	MatriceVoir(sC2("MatriceTrierTouT, passe n°",sEnt(nPasse)),pmB);
	}while (nBaton>0);
	//nCompteMax=nTri*knLigneMaX;
	ComplexitehAfficheR2(nCompteMax);
}//MatriceTrierTouT

void MatriceTU(iMatrice *pmA){
	Appel0("MatriceTU");
		int bSucces=bMatriceTU(pmA);
		Assert1("MatriceTU",bSucces);
	Appel1("MatriceTU");
}//MatriceTU

int bMatriceTU(iMatrice *pmA){
	//pmA est totalement unimodulaire ssi toute sous-matrice carrée de pmA a un déterminant égal à -1,0 ou +1.
	int nAppel,uLigne,uColonne,nL,nC,uL,uC,bOK;
	int bTU;
	long yDeterminant;
	iMatrice *pmB;
	if (pmA->nLigne>pmA->nColonne)
		for (bTU=kV,uLigne=1;uLigne<=pmA->nLigne;uLigne++){
			MatriceAllouer(&pmB);
			//pmB soit la sous-matrice obtenue en copiant pmA amputé de la ligne uLigne
				for (nL=0,uL=1;uL<=pmA->nLigne;uL++){
					if (uL!=uLigne){
						nL++;
						for (uC=1;uC<=pmA->nColonne;uC++)
							pmB->Mat[nL][uC]=pmA->Mat[uL][uC];
					}
				}
				pmB->nLigne=pmA->nLigne-1;
				pmB->nColonne=pmA->nColonne;
			bOK=bMatriceTU(pmB);
			bTU=bTU && bOK;
	}
	else if (pmA->nLigne<pmA->nColonne){
		for (bTU=kV,uColonne=1;uColonne<=pmA->nColonne;uColonne++){
			MatriceAllouer(&pmB);
			//pmB soit la sous-matrice obtenue en copiant pmA amputé de la colonne uColonne
				for (nC=0,uC=1;uC<=pmA->nColonne;uC++){
					if (uC!=uColonne){
						nC++;
						for (uL=1;uL<=pmA->nLigne;uL++)
							pmB->Mat[uL][nC]=pmA->Mat[uL][uC];
					}
				}
				pmB->nLigne=pmA->nLigne;
				pmB->nColonne=pmA->nColonne-1;
			bOK=bMatriceTU(pmB);
			bTU=bTU && bOK;
		}
	}
	else {//matrice carrée
		yDeterminant=ySignatureCalculeR(pmA,k1Alterner,&nAppel);
		bTU=zAbs(yDeterminant)<=1;
		if (bTU && (pmA->nLigne>1)){
			MatriceAllouer(&pmB);
			for (uLigne=1;uLigne<=pmA->nLigne;uLigne++){
				for (uColonne=1;uColonne<=pmA->nLigne;uColonne++){
					//pmB soit la sous-matrice obtenue en copiant pmA amputé de la ligne uLigne et de la colonne uColonne 
						for (nL=0,uL=1;uL<=pmA->nLigne;uL++){
							if (uL!=uLigne){
								nL++;
								for (nC=0,uC=1;uC<=pmA->nLigne;uC++)
									if (uC!=uColonne){
										nC++;
										pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
									}
							}
						}
						pmB->nLigne=pmA->nLigne-1;
						pmB->nColonne=pmA->nColonne-1;
					bOK=bMatriceTU(pmB);
					bTU=bTU && bOK;
					}
				}
			};
		//if (pmA->nLigne==33){
			//MatriceVoir("Matrice Lue",pmA);
			//te("bTU",bTU);
		//}
	}
	return(bTU);
}//bMatriceTU

void MatriceUnifier(iMatrice *pmA){
	//remplace tout élément non nul par 1
	int uC,uL;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			pmA->Mat[uL][uC]=(pmA->Mat[uL][uC]!=0);
			//if (pmA->Mat[uL][uC]) pmA->Mat[uL][uC]=(pmA->Mat[uL][uC]>0)? +1: -1;
}//MatriceUnifier

void MatRIceUnifier(riMatrice *pmK){
	//remplace tout élément non nul par 1
	int uC,uL;
	for (uL=1;uL<=pmK->nLigne;uL++)
		for (uC=1;uC<=pmK->nColonne;uC++)
			pmK->Mat[uL][uC]=riAff(!briNul(pmK->Mat[uL][uC]),0);
			//if (pmA->Mat[uL][uC]) pmA->Mat[uL][uC]=(pmA->Mat[uL][uC]>0)? +1: -1;
}//MatRIceUnifier

void MatriceUniter(iMatrice *pmA){
	//remplace tout élément non nul par son signe
	int uC,uL,iValeur;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++){
			iValeur=pmA->Mat[uL][uC];
			pmA->Mat[uL][uC]=ySignePres(iValeur<0,iValeur!=0);
		}
	/*for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=uL+1;uC<=pmA->nColonne;uC++){
			if (pmA->Mat[uL][uC]!=0 && pmA->Mat[uC][uL]==0)
				pmA->Mat[uL][uC]=-pmA->Mat[uL][uC];
		}*/
}//MatriceUniter

int bMatriceVidE(iMatrice *pmA){
	int uC,uL;
	int bVide;
	for (bVide=kV,uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			bVide=bVide && pmA->Mat[uL][uC]==0;
	return(bVide);
}//bMatriceVidE

void MatriceVoir(char *sMessage,iMatrice *pmA){
	//affiche pmA[pmA->nSecante...][pmA->nSecante...],tout si pmA->nSecante=0;bordé si kbBorder par les n°s lignes et colonnes;gabarit automatQ.
	const int kbBorder=kV;
	const int kbInterligner= kF;
	int bBorder;
	#define kcDiagonale ' '
	#define kcSecante '/'
	int bBlancPointeh;
	int uC,nCoupe,uDecit,uEmpan,nIndexMax,uL,uLmax,uModulo,uPas,bPermutation,nSecante;
	long yValeur;
	int iValeur,bColonner;//ie afficher le numéro de chaque colonne en haut et en bas de la matrice
	int bLigner;//ie afficher le numéro de chaque ligne à gauche et à droite de la matrice
	char kcMarque;
	long xkSeuil=kxLongintMax-1;
	//te("kxLongintMax",kxLongintMax);//kxLongintMax:9223372036854775807
												//-8480660638351149532
	Assert3("MatriceVoir",bMatriceAmorceR,sMessage!=0,pmA->nColonne<kE4);//si >kE4,réécrire l'affichage des numéros de colonne.
	//Appel0("MatriceVoir");
	//teee("pmA->nLigne,pmA->nColonne,pmA->nSecante",pmA->nLigne,pmA->nColonne,pmA->nSecante);
	nSecante=pmA->nSecante;
	if (0 && nSecante<0){//vérifier que les éléments impairs sont tous nuls
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne;uC+=2)
				Assert1(sC2b("MatriceVoir colonne impaire nulle",sEnt(nSecante)),pmA->Mat[uL][uC]==0);
	}
	uPas=(nSecante<0)? 2: 1;
	nSecante=0;uPas=1;
	bColonner=bLigner=bBorder=(pmA->nColonne>=4)? kbBorder: uPas>1;
	//if (1) bColonner=bLigner=kV;
	if (nSecante<=0)
		nSecante=pmA->nLigne;
	nCoupe=abs(nSecante);
	uModulo=(pmA->nColonne<kE3)? 10:100;
	printf("%s (%d-%dx%d-%d; %s):\n",sMessage,nCoupe,pmA->nLigne,nCoupe,pmA->nColonne,sPluriel(nMatriceEffectifNonNuL(pmA),"élément$ non nul$"));
	//te("pmA->nSecante",pmA->nSecante);
	//bPermutation:=la matrice contient des permutations de colonnes ou de lignes
		nIndexMax=0;
		for (bPermutation=kF,uL=1;uL<=pmA->nLigne;uL++){
			bPermutation=bPermutation || pmA->Mat[uL][0]!=0;
			nIndexMax=iSup(nIndexMax,pmA->Mat[uL][0]);
		}
		for (uC=uPas;uC<=pmA->nColonne;uC+=uPas)
			bPermutation=bPermutation || pmA->Mat[0][uC]!=0;
		//te("bPermutation",bPermutation);
	//uEmpan soit le sup des encombrements des valeurs numériques (entiers),signe compris,borné par le nombre de décits sans signe de xkSeuil.
		for (uEmpan=1,uL=1;iInf(nCoupe,uL<=pmA->nLigne);uL++)
			for (uC=uPas;uC<=iInf(nCoupe,pmA->nColonne);uC+=uPas)
				uEmpan=iMax(uEmpan,nChaineLg(sEnt(pmA->Mat[uL][uC])));
		uEmpan=(bLitteraliseR)? 2: 0+iSup(1,iMin(uEmpan,nChaineLg(sEnt(xkSeuil))));
		uEmpan=iSup(2,uEmpan);
	if (!bPermutation)
		nIndexMax=pmA->nLigne;
	uDecit=nChaineLg(sEnt(nIndexMax));//nbre total de décits requis pour afficher un numéro de ligne dans le pire cas.
//d4(uEmpan,uDecit,nCoupe,bPermutation);
	//pmA soit affiché,encadré en haut et en bas par les numéros de colonne et à gauche et à droite par les numéros de ligne (permutées ou non)
		if (bColonner){//afficher sur 2 lignes les numéros de colonnes PERMUTÉES: numéro/10 en ligne 1 (1 ou 2 décits), numéro%10 en ligne 2 (1 décit si uModulo=10)
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmA->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier( ((bPermutation)? pmA->Mat[0][uC]: uC)/uModulo,uEmpan));//NB pmA->Mat[0][uC] décrit le vecteur de permutation des colonnes
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmA->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier( ((bPermutation)? pmA->Mat[0][uC]: uC)%uModulo,uEmpan));
		}
		//afficher chaque ligne: les numéros de lignes PERMUTÉES puis les éléments de la ligne courante puis les numéros de lignes NON PERMUTÉES
			for (uLmax=iInf(nCoupe,pmA->nLigne),uL=1;uL<=uLmax;uL++){//NB li+1,pmA->Mat[uL][0] décrit le vecteur de permutation des lignes
				for (!bLigner || printf("%s:",sEntier0( ((bPermutation)? pmA->Mat[uL][0]: uL),uDecit)),uC=uPas;uC<=iInf(nCoupe,pmA->nColonne) || !(!bLigner || printf(" :%s",sEntier0(uL,uDecit)),bLigne());uC+=uPas){
					//yValeur=(bPermutation)? pmA->Mat[pmA->Mat[uL][0]][pmA->Mat[0][uC]]: pmA->Mat[uL][uC];
					//tee("uL,uC",uL,uC);
						yValeur=pmA->Mat[uL][uC];
					if (labs(yValeur)>xkSeuil)//borner par xkSeuil,quitte à ignorer le signe
						yValeur=xkSeuil;
					iValeur=yValeur;
					if (bBorder && yValeur==0){
						//sauf diagonale, aucun 0 n'est affiché. Un blanc le remplace,sauf s'il est indexé par une ligne et une colonne impaires. 
							bBlancPointeh=((uL<=nSecante) || (uC<=nSecante)) && (uC>=1) || (uC>=1);//ie le blanc peut être remplacé par un point.
							kcMarque=(bBlancPointeh && bImpair(uL) && bImpair(uC))? '.': ' ';//kcMarque est un blanc ou un blanc pointé.
							if (uL==uC && pmA->nLigne==pmA->nColonne) kcMarque=':';//la marque '0',qui caractérise la diagonale principale,prévaut.
						printf("%s%c",sE(uEmpan-1),kcMarque);
					}else if (bLitteraliseR)
						printf(" %c",'@'+iValeur-1);
					else printf("%s",sEntier(yValeur,uEmpan));
				}
				if (kbInterligner && uL<uLmax) Ligne();
			}
		if (bColonner){//afficher les numéros de colonnes NON PERMUTÉES sur 2 lignes: numéro/10 en ligne 1 (1 ou 2 décits), numéro%10 en ligne 2 (1 décit si uModulo=10)
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmA->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier(uC/uModulo,uEmpan));
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmA->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier(uC%uModulo,uEmpan));
		}
	//Appel1("MatriceVoir");
}//MatriceVoir

void MatriceVOir(char *sMessage,oMatrice *pmoA){
	int uC,uL;
	objet Ob;
	ri rComplexe;
	Assert2("MatriceVOir",bMatriceAmorceR,sMessage!=0);
	printf("%s (%dx%d):\n",sMessage,pmoA->nLigne,pmoA->nColonne);
	//te("Type courant de la matrice à afficher",pmoA->typ);
	//pmoA soit affiché
		for (uL=1;uL<=pmoA->nLigne;uL++)
			for (uC=1;uC<=pmoA->nColonne || bPrint("");printf(" "),uC++){
				Ob=pmoA->Mat[uL][uC];
				rComplexe=Ob.cplx;
				switch (pmoA->typ){
					case matEntier:		printf("%s",sEnt(Ob.ent));break;
					case matRationnel:	printf("%s",sQ(Ob.rat));break;
					case matComplexe:	printf("%s",sK(Ob.cplx));break;
					case matReel:		printf("%lf",Ob.reel);break;
					case matRect:		printf("(%s,%s,%s,%s)   ",sNb0(Ob.mm.q11,3),sNb0(Ob.mm.q12,3),sNb0(Ob.mm.q21,3),sNb0(Ob.mm.q22,3) );break;
					default:			Assert1("MatriceVOirdefault",kF);
				}//switch
			}//for (uC
}//MatriceVOir

void MatRIceVoir(char *sMessage,riMatrice *pmK){
	//affiche pmK[pmK->nSecante...][pmK->nSecante...],tout si pmK->nSecante=0;bordé si kbBorder par les n°s lignes et colonnes;gabarit automatQ.
	const int kbBorder=kV;
	const int kbInterligner= kF;
	int bBorder;
	#define kcDiagonale ' '
	#define kcSecante '/'
	int bBlancPointeh;
	int uC,nCoupe,uDecit,uEmpan,uL,uLmax,uModulo,uPas,bPermutation,nSecante;
	ri riValeur;
	int iValeur,bColonner;//ie afficher le numéro de chaque colonne en haut et en bas de la matrice
	int bLigner;//ie afficher le numéro de chaque ligne à gauche et à droite de la matrice
	char kcMarque;
	long xkSeuil=kxLongintMax-1;
	//te("kxLongintMax",kxLongintMax);//kxLongintMax:9223372036854775807
												//-8480660638351149532
	Assert3("MatRIceVoir",bMatriceAmorceR,sMessage!=0,pmK->nColonne<kE4);//si >kE4,réécrire l'affichage des numéros de colonne.
	Appel0("MatRIceVoir");
	//teee("pmK->nLigne,pmK->nColonne,pmK->nSecante",pmK->nLigne,pmK->nColonne,pmK->nSecante);
	nSecante=0;
	if (0 && nSecante<0){//vérifier que les éléments impairs sont tous nuls
		for (uL=1;uL<=pmK->nLigne;uL++)
			for (uC=1;uC<=pmK->nColonne;uC+=2)
				Assert1(sC2b("MatriceVoir colonne impaire nulle",sEnt(nSecante)),briNul(pmK->Mat[uL][uC]));
	}
	uPas=(nSecante<0)? 2: 1;
	nSecante=0;uPas=1;
	bColonner=bLigner=bBorder=(pmK->nColonne>=8)? kbBorder: uPas>1;
	//if (1) bColonner=bLigner=kV;
	if (nSecante<=0)
		nSecante=pmK->nLigne;
	nCoupe=abs(nSecante);
	uModulo=(pmK->nColonne<kE3)? 10:100;
	printf("%s (%d-%dx%d-%d; %s):\n",sMessage,nCoupe,pmK->nLigne,nCoupe,pmK->nColonne,sPluriel(nMatRIceEffectifNonNuL(pmK),"élément$ non nul$"));
	//te("pmK->nSecante",pmK->nSecante);
	//bPermutation:=la matrice contient des permutations de colonnes ou de lignes
		for (bPermutation=kF,uL=1;uL<=pmK->nLigne;uL++)
			bPermutation=bPermutation || pmK->Mat[uL][0].r!=0;
		for (uC=uPas;uC<=pmK->nColonne;uC+=uPas)
			bPermutation=bPermutation || pmK->Mat[0][uC].r!=0;
		//te("bPermutation",bPermutation);
	//uEmpan soit le sup des encombrements des valeurs numériques (entiers),signe compris,borné par le nombre de décits sans signe de xkSeuil.
		for (uEmpan=1,uL=1;iInf(nCoupe,uL<=pmK->nLigne);uL++)
			for (uC=uPas;uC<=iInf(nCoupe,pmK->nColonne);uC+=uPas)
				uEmpan=iMax(uEmpan,nChaineLg(sK(pmK->Mat[uL][uC])));
		uEmpan=(bLitteraliseR)? 2: 0+iSup(1,iMin(uEmpan,nChaineLg(sEnt(xkSeuil))));
		uEmpan=iSup(2,uEmpan);
		uEmpan++;
	uDecit=nChaineLg(sEnt(pmK->nLigne));//nbre total de décits requis pour afficher un numéro de ligne dans le pire cas.
//teee("uEmpan,uDecit,nCoupe",uEmpan,uDecit,nCoupe);
	//pmK soit affiché,encadré en haut et en bas par les numéros de colonne et à gauche et à droite par les numéros de ligne (permutées ou non)
		if (bColonner){//afficher sur 2 lignes les numéros de colonnes PERMUTÉES: numéro/10 en ligne 1 (1 ou 2 décits), numéro%10 en ligne 2 (1 décit si uModulo=10)
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmK->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier( ((bPermutation)? pmK->Mat[0][uC].r: uC)/uModulo,uEmpan));//NB pmK->Mat[0][uC] décrit le vecteur de permutation des colonnes
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmK->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier( ((bPermutation)? pmK->Mat[0][uC].r: uC)%uModulo,uEmpan));
		}
		//afficher chaque ligne: les numéros de lignes PERMUTÉES puis les éléments de la ligne courante puis les numéros de lignes NON PERMUTÉES
			for (uLmax=iInf(nCoupe,pmK->nLigne),uL=1;uL<=uLmax;uL++){//NB li+1,pmK->Mat[uL][0] décrit le vecteur de permutation des lignes
				for (!bLigner || printf("%s:",sEntier0( ((bPermutation)? pmK->Mat[uL][0].r: uL),uDecit)),uC=uPas;uC<=iInf(nCoupe,pmK->nColonne) || !(!bLigner || printf(" :%s",sEntier0(uL,uDecit)),bLigne());uC+=uPas){
					//yValeur=(bPermutation)? pmK->Mat[pmK->Mat[uL][0]][pmK->Mat[0][uC]]: pmK->Mat[uL][uC];
					//tee("uL,uC",uL,uC);
						riValeur=pmK->Mat[uL][uC];
					if (labs(riValeur.r)>xkSeuil)//borner par xkSeuil,quitte à ignorer le signe
						riValeur.r=xkSeuil;
					if (labs(riValeur.i)>xkSeuil)//borner par xkSeuil,quitte à ignorer le signe
						riValeur.i=xkSeuil;
					iValeur=riValeur.r;
					if (bBorder && briNul(riValeur)){
						//sauf diagonale, aucun 0 n'est affiché. Un blanc le remplace,sauf s'il est indexé par une ligne et une colonne impaires. 
							bBlancPointeh=((uL<=nSecante) || (uC<=nSecante)) && (uC>=1) || (uC>=1);//ie le blanc peut être remplacé par un point.
							kcMarque=(bBlancPointeh && bImpair(uL) && bImpair(uC))? '.': ' ';//kcMarque est un blanc ou un blanc pointé.
							if (uL==uC && pmK->nLigne==pmK->nColonne) kcMarque=':';//la marque '0',qui caractérise la diagonale principale,prévaut.
						printf("%s%c",sE(uEmpan-1),kcMarque);
					}else if (bLitteraliseR)
						printf(" %c",'@'+iValeur-1);
					else printf("%s",sChaine0(sK(riValeur),uEmpan));
				}
				if (kbInterligner && uL<uLmax) Ligne();
			}
		if (bColonner){//afficher les numéros de colonnes NON PERMUTÉES sur 2 lignes: numéro/10 en ligne 1 (1 ou 2 décits), numéro%10 en ligne 2 (1 décit si uModulo=10)
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmK->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier(uC/uModulo,uEmpan));
			for (printf(" %s",sE(uDecit)),uC=uPas;uC<=iInf(nCoupe,pmK->nColonne) || !bLigne();uC+=uPas)
				printf("%s",sEntier(uC%uModulo,uEmpan));
		}
	Appel1("MatRIceVoir");
}//MatRIceVoir

void MatriceVoirLitteral(int bLitteral){
	bLitteraliseR=bLitteral;
}//MatriceVoirLitteral

void MatriceVoirReeL(char *sMessage,dMatricE *pmA){
	int uC,uL;
	Assert2("MatriceVoirReeL",bMatriceAmorceR,sMessage!=0);
	printf("%s:\n",sMessage);
	//eMat afficher 
		for (uL=1;uL<=pmA->nLigne;uL++){
			for (uC=1;uC<=pmA->nColonne|| bPrint("");uC++)
				if (fabs(pmA->Mat[uL][uC])>=0.1)
					printf("%5.2lf",pmA->Mat[uL][uC]);//ou %8.3f pr 8 caractères en tout et 3 décimales
				else printf("     ");
		}
}//MatriceVoirReeL

void MatriceVoirSouS(int bSous,char *sMessage,iMatrice *pmA){
	if (bSous)
		MatriceVoir(sMessage,pmA);
}//MatriceVoirSouS

void MatriceVoyR(char *sMessage,yMatricE *pmA){
	int uC,uL;
	Assert2("MatriceVoyR",bMatriceAmorceR,sMessage!=0);
	if (1){
		printf("%s:\n",sMessage);
		//eMat afficher 
			for (uL=1;uL<=pmA->nLigne;uL++)
				for (uC=1;uC<=pmA->nColonne|| bPrint("");uC++)
					printf(" %16ld",pmA->Mat[uL][uC]);
	}
}//MatriceVoyR

void MatriceZeroter(iMatrice *pmA,int uHauteur,iMatrice *pmAh){
	//all rows and columns not greater than uHauteur zeroed
	int uC,uL;
	Assert1("MatriceZeroter",bCroit(1,uHauteur,pmA->nLigne));
	MatriceDupliquer(pmA,pmAh);
	for (uL=1;uL<=uHauteur;uL++)
		for (uC=1;uC<=pmA->nLigne;uC++)
			pmAh->Mat[uL][uC]=0;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=uHauteur;uC++)
			pmAh->Mat[uL][uC]=0;
}//MatriceZeroter

void MatriceTransposer(iMatrice *pmA){
	int uC,uL;
	Assert1("MatriceTransposer",pmA->nLigne==pmA->nColonne);
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=uL+1;uC<=pmA->nLigne;uC++)
			EntyerEchanger(&pmA->Mat[uL][uC],&pmA->Mat[uC][uL]);
}//MatriceTransposer

void MatriqeAlloueR(qMatricE **ppmA){
	*ppmA=malloc(sizeof(qMatricE));
	(*ppmA)->nLigne=knLigneMaX;
	(*ppmA)->nColonne=knColonneMaX;
	MatriqeRazeR(ppmA);
}//MatriqeAlloueR

void MatriqeRazeR(qMatricE **ppmA){
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knColonneMaX;uC++){
			(*ppmA)->Mat[uL][uC].num=0;
			(*ppmA)->Mat[uL][uC].den=1;
		}
}//MatriqeRazeR

void MatriqeVoiR(char *sMessage,qMatricE *pmA){
	int uC,uL;
	Assert2("MatriqeVoiR",bMatriceAmorceR,sMessage!=0);
	printf("%s:\n",sMessage);
	//eMat afficher 
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne|| bPrint("");uC++)
				printf(" %8s",sQ(pmA->Mat[uL][uC]));
}//MatriqeVoiR


void MatryceAffecteR(int nLigne,iMatrice **ppmA){
	/*char *sLigne[1+6]={//grand X1
		"**1,**2,**3,**4,**5,**6",
		"  0,  1,  2,  3,  0,  0",
		"  1,  0,  0,  0, -3, -2",
		"  1,  0,  0,  0,  5,  0",
		"  1,  0,  0,  0,  0,  7",
		"  0,  1,  1,  0,  0,  0",
		"  0,  1,  0,  1,  0,  0",
	};*/
	char *sLigne[1+6]={//grand X2
		"**1,**2,**3,**4,**5,**6",
		"  1, 97,  1, 17,  1,  1",
		"-97,  1,  1,  1, 13, 93",
		"  1,  1,  1,  1,  1,  1",
		"-17,  1,  1,  1,  1,  1",
		"  1,-13,  1,  1,  1,  1",
		"  1,-93,  1,  1,  1,  1",
	};
	/*char *sLigne[1+4]={//cycle de 4 arêtes
		"**1,**2,**3,**4",
		"  0,  2,  0,  7",
		" -2,  0,  3,  0",
		"  0, -3,  0,  5",
		" -7,  0, -5,  0",
	};*/
	/*char *sLigne[1+4]={//matrice pleine qcq
		"*1,*2,*3,*4",
		"08, 2, 3,04",
		" 5,07, 7,08",
		"11,13,08,12",
		"13,14,15,07"
	};*/
	int uL,uC;
	(*ppmA)->nLigne=(*ppmA)->nColonne=nLigne;
	//te("nLigne",nLigne);
	for (uL=1;uL<=nLigne;uL++)
		for (uC=1;uC<=nLigne;uC++)
			sscanf(sItem(sLigne[uL],uC),"%ld",&(*ppmA)->Mat[uL][uC]);
}//MatryceAffecteR

void MatryceAlloueR(iMatrycE **ppmA){
	*ppmA=malloc(sizeof(iMatrycE));
	(*ppmA)->nLigne=knLigneMaX;
	(*ppmA)->nColonne=knColonneMaX;
	(*ppmA)->nPoly=knPolyMaX;
	(*ppmA)->nTerme=knTermeMaX;
	MatryceRazeR(ppmA);
}//MatryceAlloueR

void MatryceRazeR(iMatrycE **ppmA){
	int uL,uC,uP,nT;
	for (uL=1;uL<=(*ppmA)->nLigne;uL++)
		for (uC=1;uC<=(*ppmA)->nColonne;uC++)
			(*ppmA)->Map[uL][uC]=(uL-1)*(*ppmA)->nLigne+uC;
	for (uP=1;uP<=(*ppmA)->nPoly;uP++)
		for (nT=0;nT<=(*ppmA)->nTerme;nT++)
			(*ppmA)->Pol[uP][nT]=0;
	for (uP=1;uP<=(*ppmA)->nPoly;uP++)
		for (nT=0;nT<=(*ppmA)->nTerme;nT++)
			(*ppmA)->Poi[uP][nT]=0;
	for (uP=1;uP<=(*ppmA)->nPoly;uP++)
		for (nT=0;nT<=(*ppmA)->nTerme;nT++)
			(*ppmA)->Exp[uP][nT]=0;
}//MatryceRazeR

void MatriceRedresseR(iMatrice *pmA){
	int uL,uC;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=uL+1;uC<=pmA->nColonne;uC++)
			if (pmA->Mat[uL][uC]<0)
				EntyerEchanger(&(pmA->Mat[uL][uC]),&(pmA->Mat[uC][uL]));
}//MatriceRedresseR

int bMatryceSinguliere(graf *pgG){
	int nEtape;
	iMatrycE *pmA;
	#define kuAreteValeur 1
	#define kbMatriceAfficher kF
	int nExposant;
	int uIndex;
	int bSinguliere;
	int sX,sY,aK;
	//enum eMatrice {maAlpha,maPremier,eMatriceStandard,eMatriceTotale,maOmega};
	GrapheVoir(pgG,"Graphe fourni en donnée");
	MatryceAlloueR(&pmA);
	pmA->nLigne=pgG->nSommetEnTout;
	pmA->nColonne=pgG->nSommetEnTout;
	pmA->nPoly=pgG->nSommetEnTout*pgG->nSommetEnTout;
	nExposant=(pgG->nSommetEnTout*(pgG->nSommetEnTout-1))/2;
	pmA->nTerme=iMax(3,nExposant*nExposant);//empirique;iMax(3,…) pour MatryceVoiR()
	Assert4("bMatryceSinguliere",pmA->nLigne<knLigneLiM,pmA->nColonne<knColonneLiM,pmA->nPoly<knPolyLiM,pmA->nTerme<knTermeLiM);
	teee("nExposant,pmA->nPoly,pmA->nTerme",nExposant,pmA->nPoly,pmA->nTerme);
	MatryceRazeR(&pmA);
	//remplir la matrice pmA avec les seules caractéristiques du graphe pgG en attribuant à chaque variable une puissance de 2 et un signe.
		for (nExposant=0,uIndex=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX<sY){//variable de coefficient +1
					nExposant++;
					Assert1("bMatryceSinguliere",nExposant<knTermeLiM);
					uIndex=pmA->Map[sX][sY];
					//pmA->Pol[uIndex][nExposant]=1;
					pmA->Pol[uIndex][0]=1;
					pmA->Poi[uIndex][1]=1;
					pmA->Exp[uIndex][1]=nExposant;
				}
			}
		for (uIndex=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX>sY){//variable de coefficient -1
					uIndex=pmA->Map[sX][sY];
					/*for (nT=0;nT<pmA->nTerme;nT++)
						pmA->Pol[uIndex][nT]=-pmA->Pol[pmA->Map[sY][sX]][nT];*/
					pmA->Pol[uIndex][0]=1;
					pmA->Poi[uIndex][1]=-1;
					pmA->Exp[uIndex][1]=pmA->Exp[pmA->Map[sY][sX]][1];
				}
			}
	MatryceVoiR("Matrice antisymétrique sommet-sommet associée au graphe",pmA);
	bSinguliere=!bMatryceTrianguleR(&pmA,&nEtape);
	printf("Coût de la triangulation polynomiale: %s étapes pour %d sommets.\n",sPar3(nEtape),pgG->nSommetEnTout);
	printf("zPuissance(pgG->nSommetEnTout,6):%s.\n",sPar3(zPuissance(pgG->nSommetEnTout,7)));
	printf("zPuissance(pgG->nSommetEnTout,6):%s.\n",sPar3(zPuissance(pgG->nSommetEnTout,6)));
	return(bSinguliere);
}//bMatryceSinguliere

int bMatryceTrianguleR(iMatrycE **ppmT,int *pnEtape){
	//rend vrai ssi le déterminant de la matrice ppmT est non nul;calcul exact sur les entiers par élimination gaussienne
	int bNonNul,uIndex,uL,uC,uD,nT,bDerouter,uP,nPivot,nEtape,bTrianguler,nPermutation;
//	int iFois,uFois;
	int iValeur;
	int ivB,ivFois,ivC,ivPivot;
	int ivProduit1,ivProduit2,ivProduit3;
	int ivSomme;
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	MatryceVoiR("ppmT original",*ppmT);
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=(*ppmT)->nLigne && nPivot>=uD-1;uD++){
			MatryceVoiR("ppmT courant",*ppmT);
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uP=1;uP<=(*ppmT)->nColonne;nEtape++,uP++){
					uIndex=(*ppmT)->Map[uD][uP];
					/*for (nT=0;nT<(*ppmT)->nTerme;nT++){
						iValeur=(*ppmT)->Pol[uIndex][nT];
						if (nPivot==0 && (iValeur!=0))
							nPivot=uP;
					}*/
					iValeur=(*ppmT)->Pol[uIndex][0];
					if (nPivot==0 && (iValeur!=0))
						nPivot=uP;
				}
			tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<(*ppmT)->nLigne; 
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (nPermutation++,uL=1;uL<=(*ppmT)->nLigne;nEtape++,uL++){
						iValeur=(*ppmT)->Map[uL][nPivot];
						(*ppmT)->Map[uL][nPivot]=(*ppmT)->Map[uL][uD];
						(*ppmT)->Map[uL][uD]=iValeur;
					}
					MatryceVoiR("ppmT recolonné",*ppmT);
				}
				ivPivot=(*ppmT)->Map[uD][uD];
				Assert1("bMatriceTrianguleR1",ivPivot!=0);
				tee("uD,ivPivot",uD,ivPivot);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux (leur ppcm suffit)
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						ivPivot=(*ppmT)->Map[uD][uD];//a
						ivProduit1=(*ppmT)->nPoly+1;
						ivProduit2=(*ppmT)->nPoly+2;
						ivProduit3=(*ppmT)->nPoly+3;
						ivSomme=(*ppmT)->nPoly+4;
						for (uL=uD+1;uL<=(*ppmT)->nLigne;uL++){
							ivFois=(*ppmT)->Map[uL][uD];//d
							for (uC=uD;uC<=(*ppmT)->nColonne;uC++){//ajouter ac-bd
								ivB=(*ppmT)->Map[uD][uC];//b
								ivC=(*ppmT)->Map[uL][uC];//c
								//PolynomeVoiR("ivPivot",ivPivot,ppmT);
								//PolynomeVoiR("ivC",ivC,ppmT);
								PolynomeMultiplieR(ivPivot,ivC,ivProduit1,ppmT);//ac
								//PolynomeVoiR("ivProduit1",ivProduit1,ppmT);
								//PolynomeVoiR("ivB",ivB,ppmT);
								//PolynomeVoiR("ivFois",ivFois,ppmT);
								PolynomeMultiplieR(ivB,ivFois,ivProduit2,ppmT);//bd
								//PolynomeVoiR("ivProduit2",ivProduit2,ppmT);
								PolynomeFoisseR(ivProduit2,-1,ivProduit3,ppmT);//-bd
								//PolynomeVoiR("ivProduit3",ivProduit3,ppmT);
								ivSomme=(*ppmT)->Map[uL][uC];
								PolynomeSommeR(ivProduit1,ivProduit3,ivSomme,ppmT);//ac-bd
								//PolynomeVoiR("ivSomme",ivSomme,ppmT);
								nEtape+=(*ppmT)->nTerme*(*ppmT)->nTerme;//coût quadratique de PolynomeMultiplieR (on sait descendre à NlogN)
							}
						}
						//MatriceVoyR("ppmT pivoté",*ppmT);
				MatryceVoiR(sC4b("ppmT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),*ppmT);
			}else if (bVoiR)
				printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//bTrianguler=déterminant non nul,ie aucun élément de la diagonale principale n'est le polynome nul
		for (bTrianguler=kV,uD=1;uD<=(*ppmT)->nLigne;uD++){
			uIndex=(*ppmT)->Map[uD][uD];
			for (bNonNul=kV,nT=0;nT<(*ppmT)->nTerme;nT++){
				iValeur=(*ppmT)->Pol[uIndex][nT];
				if (iValeur!=0)
					bNonNul=kF;
			}
			bTrianguler=bTrianguler && !bNonNul;
			//tee("uIndex,bTrianguler",uIndex,bTrianguler);
		}
	MatryceVoiR(sC2b("ppmT triangulé",sChoix0(!bTrianguler && bDerouter,"(déroutement dû au pivot nul)")),*ppmT);
	*pnEtape=nEtape;
	//te("bTrianguler APRES",bTrianguler);
	return(bTrianguler);
}//bMatryceTrianguleR

void MatryceVoiR(char *sMessage,iMatrycE *pmA){
	#define bkAlgebrique kV
	int uC,uL,nT,uP,nOperande;
	te("pmA->nTerme",pmA->nTerme);
	Assert3("MatryceVoiR",bMatriceAmorceR,sMessage!=0,pmA->nTerme>2);
	printf("%s:\n",sMessage);
	//afficher seule la matrice des index de polynomes
		for (uL=1;uL<=pmA->nLigne;uL++)
			for (uC=1;uC<=pmA->nColonne|| bPrint("");uC++){
				uP=pmA->Map[uL][uC];
				printf("%3d",uP);
			}
	//afficher les polynomes index par index
		if (bkAlgebrique)//afficher sous forme algébrique 
			for (uP=1;uP<=pmA->nPoly;uP++){
				nOperande=pmA->Pol[uP][0];
				Assert1("MatryceVoiR enquete",nOperande<=1);
				if (nOperande>0){
					for (printf("Polynome n°%2d:",uP),nT=nOperande;nT>0 || bPrint("");--nT){
						Assert1("MatryceVoiR2",abs(pmA->Poi[uP][nT]!=0)<=1);
						if (pmA->Poi[uP][nT]!=0){
							if (abs(pmA->Poi[uP][nT])==1)
								printf(" %cX**%d",(pmA->Poi[uP][nT]>0)?'+':'-',pmA->Exp[uP][nT]);
							else printf(" %dX**%d",pmA->Poi[uP][nT],pmA->Exp[uP][nT]);
						}
					};
				}
			}
		else if (bkAlgebrique){//afficher sous forme algébrique 
			for (uP=1;uP<=pmA->nPoly;uP++){
				for (nOperande=0,nT=pmA->nTerme-1;nT>=0;--nT)
					if (pmA->Pol[uP][nT]!=0)
						nOperande++;
				Assert1("MatryceVoiR enquete",nOperande<=1);
				if (nOperande>0){
					for (printf("Polynome n°%2d:",uP),nT=pmA->nTerme-1;nT>=0|| bPrint("");--nT){
						Assert1("MatryceVoiR2",abs(pmA->Pol[uP][nT]!=0)<=1);
						if (pmA->Pol[uP][nT]!=0){
							printf(" %cX**%d",(pmA->Pol[uP][nT]>0)?'+':'-',nT);
							nOperande--;
						}
					};
				}
			}
		}else {//afficher sous forme tabulaire  
			for (printf("Poids exposant"),nT=pmA->nTerme-1;nT>=0 || bPrint("");--nT)
				printf("%3d",nT);
			for (uP=1;uP<=pmA->nPoly;uP++){
				for (printf("Polynome n°%2d:",uP),nT=pmA->nTerme-1;nT>=0 || bPrint("");--nT)
					printf("%3d",pmA->Pol[uP][nT]);
			}
		}
}//MatryceVoiR

void ModuloParFibonnaccI(){
	//utiliser la fonction de Fibonacci pour neutraliser les coef hors diagonale
	iMatrice *pmA;
	iMatrice *pmB;
	iMatrice *pmC;
	long zBarre;
	float fDensiteh;
	MatriceAllouer(&pmA);
		MatriceAllouer(&pmB);
			MatriceAllouer(&pmC);
				fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmA);
				fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmB);
				MatriceVoir("Matrice A",pmA);
				MatriceVoir("Matrice B",pmB);
				zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
				MatriceVoir("Matrice AxB",pmC);
				te("zBarre",zBarre);
				ComplexitehAfficheR(zBarre);
				/*for (nIndex=0;nIndex<=20;nIndex++)
					printf("F(%d)=%ld\n",nIndex,zFib(nIndex));
				te("F(10)\%F(10)",zFib(10)%zFib(10));
				te("F(20)\%F(10)",zFib(20)%zFib(10));
				te("F(30)\%F(10)",zFib(30)%zFib(10));
				te("F(40)\%F(10)",zFib(40)%zFib(10));*/
}//ModuloParFibonnaccI

objet oObjetAdD(objet oA,objet oB,enum eMatriceType tip){
	objet oAdd;
	switch (tip){
		case matEntier:		oAdd.ent=oA.ent+oB.ent;break;
		case matRationnel:	oAdd.rat=qAdd(oA.rat,oB.rat);break;
		case matComplexe:	oAdd.cplx=riAdd(oA.cplx,oB.cplx);break;
		case matReel:		oAdd.reel=oA.reel+oB.reel;break;
		case matRect:		NbAdd(oA.mm.q11,oB.mm.q11,&oAdd.mm.q11);
							NbAdd(oA.mm.q12,oB.mm.q12,&oAdd.mm.q12);
							NbAdd(oA.mm.q21,oB.mm.q21,&oAdd.mm.q21);
							NbAdd(oA.mm.q22,oB.mm.q22,&oAdd.mm.q22);
							break;
		default: Assert1("oObjetAdD Default",kF);
	}
	return(oAdd);
}//oObjetAdD

objet oObjetMuL(objet oA,objet oB,enum eMatriceType tip){
	objet oMul;
	nb nbDroit,nbGauche;
	switch (tip){
		case matEntier:		oMul.ent=oA.ent*oB.ent;break;
		case matRationnel:	oMul.rat=qMul(oA.rat,oB.rat);break;
		case matComplexe:	oMul.cplx=riMul(oA.cplx,oB.cplx);break;
		case matReel:		oMul.reel=oA.reel*oB.reel;break;
		case matRect:		NbMul(oA.mm.q11,oB.mm.q11,&nbGauche);		NbMul(oA.mm.q12,oB.mm.q21,&nbDroit);		NbAdd(nbGauche,nbDroit,&oMul.mm.q11);
							NbMul(oA.mm.q11,oB.mm.q12,&nbGauche);		NbMul(oA.mm.q12,oB.mm.q22,&nbDroit);		NbAdd(nbGauche,nbDroit,&oMul.mm.q12);
							NbMul(oA.mm.q21,oB.mm.q11,&nbGauche);		NbMul(oA.mm.q22,oB.mm.q21,&nbDroit);		NbAdd(nbGauche,nbDroit,&oMul.mm.q21);
							NbMul(oA.mm.q21,oB.mm.q12,&nbGauche);		NbMul(oA.mm.q22,oB.mm.q22,&nbDroit);		NbAdd(nbGauche,nbDroit,&oMul.mm.q22);
							break;
		default: Assert1("oObjetMuL Default",kF);
	}
	return(oMul);
}//oObjetMuL

int bObjetNuL(objet Ob,enum eMatriceType tip){
	int bNul=kF;
	//Ob=(*ppmoA)->Mat[nL][nC];
	switch (tip){
		case matEntier:	bNul=(Ob.ent==0);break;
		case matRationnel:	bNul=(Ob.rat.num==0);break;
		case matComplexe:	bNul=briNul(Ob.cplx);break;
		case matReel:		bNul=(Ob.reel==0);break;
		case matRect:		bNul=(bNbNul(Ob.mm.q11) && bNbNul(Ob.mm.q12) && bNbNul(Ob.mm.q21) && bNbNul(Ob.mm.q22) );break;
		default: Assert1("bObjetNuLDefault",kF);
	}
	return (bNul);
}//bObjetNuL

objet oObjetOpP(objet oA,enum eMatriceType tip){
	objet oOpP;
	switch (tip){
		case matEntier:		oOpP.ent=-oA.ent;break;
		case matRationnel:	oOpP.rat=qOpp(oA.rat);break;
		case matComplexe:	oOpP.cplx=riOpp(oA.cplx);break;
		case matReel:		oOpP.reel=-oA.reel;break;
		case matRect:		NbDupliquer(oA.mm.q11,&oOpP.mm.q11);	oOpP.mm.q11.sign= - oOpP.mm.q11.sign;
							NbDupliquer(oA.mm.q12,&oOpP.mm.q12);	oOpP.mm.q12.sign= - oOpP.mm.q12.sign;
							NbDupliquer(oA.mm.q21,&oOpP.mm.q21);	oOpP.mm.q21.sign= - oOpP.mm.q21.sign;
							NbDupliquer(oA.mm.q22,&oOpP.mm.q22);	oOpP.mm.q22.sign= - oOpP.mm.q22.sign;
							break;
		default: Assert1("oObjetOpP Default",kF);
	}
	return(oOpP);
}//oObjetOpP

void ObjetRazeR(objet *poCible,enum eMatriceType tip){
	objet oRaz;
	switch (tip){
		case matEntier:		oRaz.ent=0;break;
		case matRationnel:	oRaz.rat.num=0;oRaz.rat.den=1;break;
		case matComplexe:	oRaz.cplx=riAff(0,0);break;
		case matReel:		oRaz.reel=0;break;
		case matRect:		NbAffecter(0,&oRaz.mm.q11);NbAffecter(0,&oRaz.mm.q12);NbAffecter(0,&oRaz.mm.q21);NbAffecter(0,&oRaz.mm.q22);break;
		default: Assert1("bObjetNuLDefault",kF);
	}
	*poCible=oRaz;
}//ObjetRazeR

objet oObjetSuB(objet oA,objet oB,enum eMatriceType tip){
	objet oSub;
	oSub=oObjetAdD(oA,oObjetOpP(oB,tip),tip);
	return(oSub);
}//oObjetSuB

void ObjetUnariseR(objet *poCible,enum eMatriceType tip){
	objet oUn;
	switch (tip){
		case matEntier:oUn.ent=1;break;
		case matRationnel:oUn.rat.num=1;oUn.rat.den=1;break;
		case matComplexe:oUn.cplx=riAff(1,0);break;
		case matReel:oUn.reel=1;break;
		case matRect:NbAffecter(1,&oUn.mm.q11);NbAffecter(1,&oUn.mm.q12);NbAffecter(1,&oUn.mm.q21);NbAffecter(1,&oUn.mm.q22);break;
		default: Assert1("bObjetNuLDefault",kF);
	}
	*poCible=oUn;
}//ObjetUnariseR

void ObjetVoiR(char *sQuoi,objet oQuoi,enum eMatriceType tip){
	printf("%s: ",sQuoi);
	switch (tip){
		case matEntier:		printf("%s",sEnt(oQuoi.ent));break;
		case matRationnel:	printf("%s",sQ(oQuoi.rat));break;
		case matComplexe:	printf("%s",sK(oQuoi.cplx));break;
		case matReel:		printf("%lf",oQuoi.reel);break;
		case matRect:		printf("(%s,%s,%s,%s)",sNb(oQuoi.mm.q11),sNb(oQuoi.mm.q12),sNb(oQuoi.mm.q21),sNb(oQuoi.mm.q22));break;
		default: Assert1("ObjetVoiR Default",kF);
	}
	printf(".\n");
}//ObjetVoiR

void PolynomeAjouteR(int iCoefficient,int nExposant,int ivCible,iMatrycE **ppmT){
	int nPlace,nT,nTerme;
	nTerme=(*ppmT)->Pol[ivCible][0];
	Assert1("PolynomeAjouteR1",nTerme<=1);
	for (nPlace=0,nT=1;nT<=nTerme;nT++)
		if (abs((*ppmT)->Exp[ivCible][nT])==nExposant)
			nPlace=nT;
	if (nPlace==0){
		nTerme++;
		(*ppmT)->Pol[ivCible][0]=nTerme;
		nPlace=nTerme;
		Assert1("PolynomeAjouteR2",nTerme<=1);
	}
	(*ppmT)->Poi[ivCible][nPlace]+=iCoefficient;
	(*ppmT)->Exp[ivCible][nPlace]=nExposant;
}//PolynomeAjouteR

void PolynomeAnnuleR(int ivCible,iMatrycE **ppmT){
	int nT,nTerme;
	nTerme=(*ppmT)->Pol[ivCible][0];
	for (nT=0;nT<=nTerme;nT++)
		(*ppmT)->Pol[ivCible][nT]=0;
}//PolynomeAnnuleR

void PolynomeFoisseR(int ivOperande,int iFois,int ivFois,iMatrycE **ppmT){
	int nT,nTerme,uElement;
	uElement=(*ppmT)->nTerme;
	Assert1("PolynomeFoisseR",uElement>0);
	nTerme=(*ppmT)->Pol[ivOperande][0];
	Assert1("PolynomeFoisseR2",nTerme>=0);
	for (nT=1;nT<nTerme;nT++)
		(*ppmT)->Poi[ivFois][nT]=iFois * (*ppmT)->Poi[ivOperande][nT];
}//PolynomeFoisseR

void PolynomeMultiplieR(int ivGauche,int ivDroit,int ivProduit,iMatrycE **ppmT){
	int nD,nG,nExposant,iCoefficient,uElement;
	Assert3("PolynomeMultiplieR1",ivGauche>0,ivDroit>0,ivProduit>0);
	uElement=(*ppmT)->nTerme;
	/*for (nT=0;nT<uElement;nT++)
		(*ppmT)->Pol[ivProduit][nT]=0;
	for (nG=0;nG<uElement;nG++)
		if ((*ppmT)->Pol[ivGauche][nG]!=0){
			for (nD=0;nD<uElement;nD++)
				if ((*ppmT)->Pol[ivDroit][nD]!=0){
					if (nG+nD<uElement)
						(*ppmT)->Pol[ivProduit][nG+nD]+=(*ppmT)->Pol[ivGauche][nG]*(*ppmT)->Pol[ivDroit][nD];
					else {teeeeee("ivGauche,nG,ivDroit,nD",ivGauche,nG,ivDroit,nD,nG+nD,uElement);}
					Assert1("PolynomeMultiplieR2",nG+nD<uElement);
				}
		}*/
	PolynomeAnnuleR(ivProduit,ppmT);
	for (nG=1;nG<=(*ppmT)->Pol[ivGauche][0];nG++)
		for (nD=1;nD<=(*ppmT)->Pol[ivDroit][0];nD++){
			nExposant=(*ppmT)->Exp[ivGauche][nG]+(*ppmT)->Exp[ivDroit][nD];
			iCoefficient=(*ppmT)->Poi[ivGauche][nG]*(*ppmT)->Poi[ivDroit][nD];
			PolynomeAjouteR(iCoefficient,nExposant,ivProduit,ppmT);
		}
}//PolynomeMultiplieR

void PolynomeSommeR(int ivGauche,int ivDroit,int ivSomme,iMatrycE **ppmT){
	int uElement,nT,nTerme;
	uElement=(*ppmT)->nTerme;
	Assert1("PolynomeSommeR",uElement>0);
	PolynomeAnnuleR(ivSomme,ppmT);
	nTerme=(*ppmT)->Pol[ivGauche][0];
	for (nT=1;nT<=nTerme;nT++)
		PolynomeAjouteR((*ppmT)->Poi[ivGauche][nT],(*ppmT)->Exp[ivGauche][nT],ivSomme,ppmT);
	nTerme=(*ppmT)->Pol[ivDroit][0];
	for (nT=1;nT<=nTerme;nT++)
		PolynomeAjouteR((*ppmT)->Poi[ivDroit][nT],(*ppmT)->Exp[ivDroit][nT],ivSomme,ppmT);
}//PolynomeSommeR

int nPolynomeTermE(int ivTerme,iMatrycE **ppmT){
	//rend le nombre de termes non nuls du polynome ivTerme de ppmT
	int nTerme;
	nTerme=(*ppmT)->Pol[ivTerme][0];
	return(nTerme);
}//nPolynomeTermE

void PolynomeVoiR(char *sMessage,int ivQuoi,iMatrycE **ppmT){
	int uElement,nT;
	uElement=(*ppmT)->nTerme;
	Assert2("PolynomeVoiR",uElement>0,ivQuoi>0);
	for (printf("%s\n",sMessage),nT=uElement-1;nT>=0 || bPrint("");nT--)
		printf("%4d",(*ppmT)->Pol[ivQuoi][nT]);
}//PolynomeVoiR

void PpcmOptimalExhibeR(){
	//Exhibe un ppcm calculable tel que chaque produit hors diagonale d'un tenseur a pour modulo 1 (remplace N multiplicO par 1 seule)
	iMatrice *pmC;
	int uListe[20];
	t("Soit L la liste des diviseurs d'un nombre N donné");
	//DiviseurS(60,&uListe[0]);
	//DiviseurS(12,&uListe[0]);
	DiviseurS(2*3*5,&uListe[0]);//2,3,5,6,10,15
	ListeVoiR(uListe);
	t("Soit T la Matrice Tenseur, ie tous les produits de deux diviseurs de L");
	MatriceAllouer(&pmC);
	MatriceProduirE(uListe,1,&pmC);
	MatriceVoir("Matrice tenseur T",pmC);
	t("Soit S la Matrice selle (diagonale principale minimale) obtenue en ajoutant à T la transposée de T");
	MatriceProduirE(uListe,0,&pmC);
	MatriceVoir("Matrice selle S",pmC);
	t("Soit Co le culminant optimal tel que les éléments Eij=Co-Sij hors diagonale ont le plus petit ppcm de type longint");
	MatriceCulminerAuMieuX(pmC);
	t("Bilan:il semble impossible de trouver un tenseur à ppcm calculable lorsque la Matrice NxN vérifie N>6");
	//MatriceModuleR(120,&pmC);
	//MatriceVoir("Matrice modulo",pmC);
}//PpcmOptimalExhibeR

int bPermutatioN(int nPermutation[]){
	int uN,uNmax=nPermutation[0];
	int bPermutation;
	int nEntier[knLigneLiM];
	//vrai ssi nPermutation[] ne renferme que des entiers distincts compris entre 1 et nPermutation[0]
	for (uN=1;uN<=uNmax;uN++)
		nEntier[uN]=0;
	for (uN=1;uN<=uNmax;uN++)
		nEntier[nPermutation[uN]]++;
	for (bPermutation=kV,uN=1;uN<=uNmax;uN++)
		bPermutation=bPermutation && nEntier[uN]==1;
	if (!bPermutation)
		VecteurVoir("nEntier     ",nEntier,1,uNmax);
	return(bPermutation);
}//bPermutatioN

int bPermutationSolidairE(iMatrice *pmA){
	int bSolidaire=kV;
	int uP;
	for (uP=1;uP<pmA->nLigne;uP+=2)
		bSolidaire=bSolidaire && (pmA->Mat[uP][0]+1==pmA->Mat[uP+1][0]);
	for (uP=1;uP<pmA->nLigne;uP+=2)
		bSolidaire=bSolidaire && (pmA->Mat[0][uP]+1==pmA->Mat[0][uP+1]);
	return(bSolidaire);
}//bPermutationSolidairE

void PremierVoiR(){
	int uN,nPremier;
	for (printf("Nombre premiers:\n"),nPremier=abPremieR[0],uN=1;uN<=knPremierMaX || bPrint(".");uN++)
		if (abPremieR[uN]!=0){
			printf("%3d",uN);
			if (--nPremier>0)
				printf(",");
		}
}//PremierVoiR

void PremierTabuleR(){
	//abPremieR[X]:="X est un nombre premier",1≤X≤knPremierMaX;de plus,abPremieR[0]:=effectif de ces nombres premiers.
	int uDividende,nPremier,uN,uQuotient,nRac;
	Assert1("PremierTabuleR1",knPremierMaX>1);
	nRac=trunc(sqrt(knPremierMaX));//X premier <=>X non divisible par un nombre inférieur ou égal à nRac
	//te("nRac",nRac);
	for (uDividende=1;uDividende<=knPremierMaX;uDividende++)
		abPremieR[uDividende]=1;//d
	for (uDividende=1;uDividende<=knPremierMaX;uDividende++)
		for (uQuotient=2;uQuotient<=iMin(uDividende-1,nRac);uQuotient++)
			if (uDividende%uQuotient==0)
				abPremieR[uDividende]=0;
	//nPremier:=nbre total de nombres premiers
		for (nPremier=0,uN=1;uN<=knPremierMaX;uN++)
			if (abPremieR[uN]!=0)
				nPremier++;
	abPremieR[0]=nPremier;
	Assert1("PremierTabuleR2",nPremier>0);
}//PremierTabuleR

objet oSignatureCalculeR(oMatrice *pmoA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmoA,ie calculée par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot;
	objet oSignature,oProduit,oSigne,oSousSignature,oOperande;
	oMatrice *pmoB;
	//Appel0("qSignatureCalculeR");
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	MatriceAllouher(&pmoB,pmoA->typ);
	//te("pmA->nLigne",pmA->nLigne);
	if (pmoA->nLigne>1){
		//MatriceVOir("Matrice Reçue",pmoA);
		ObjetRazeR(&oSignature,pmoA->typ);
		ObjetUnariseR(&oSigne,pmoA->typ);
		//ObjetVoiR("oSignature",oSignature,pmoA->typ);
		//ObjetVoiR("oSigne",oSigne,pmoA->typ);
		for (uPivot=1;uPivot<=pmoA->nLigne;uPivot++){
			//te("uPivot",uPivot);
			if ( !bObjetNuL(pmoA->Mat[uPivot][1],pmoA->typ) ){
				//pmoB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
					for (nL=0,uL=1;uL<=pmoA->nLigne;uL++)
						if (uL!=uPivot)
							for (nL++,nC=0,uC=2;nC++,uC<=pmoA->nLigne;uC++)
								pmoB->Mat[nL][nC]=pmoA->Mat[uL][uC];
					pmoB->nLigne=pmoA->nLigne-1;
					pmoB->nColonne=pmoA->nColonne-1;
				//MatriceVOir("Matrice B",pmoB);
				oSousSignature=oSignatureCalculeR(pmoB,bAlterner,pnAppelExponentiel);
				oOperande=oObjetMuL(oSigne,pmoA->Mat[uPivot][1],pmoA->typ);
				//s'assurer que le produit qui suit ne va pas déborder 
					//Assert2("qSignatureCalculeR1",abs(pmA->Mat[uPivot][1].num)<=kuIntegerMax,abs(qSousSignature.num)<=kuIntegerMax);
				oProduit=oObjetMuL(oOperande,oSousSignature,pmoA->typ);
				if (pmoA->nLigne>=200){
					Titrer("PRODUIT");
					ObjetVoiR("oGauche",oOperande,pmoA->typ);
					ObjetVoiR("oDroit",oSousSignature,pmoA->typ);
					ObjetVoiR("oProduit",oProduit,pmoA->typ);
				}
				//s'assurer que la somme qui suit ne va pas déborder 
					//Assert2("qSignatureCalculeR2",abs(qSignature.num)<=kuIntegerMax,abs(qProduit.num)<=kuIntegerMax);//kxLongintMax/2 suffirait en fait!
				if (pmoA->nLigne==200){
					Titrer("SOMME");
					ObjetVoiR("oGauche",oSignature,pmoA->typ);
					ObjetVoiR("oDroit",oProduit,pmoA->typ);
				}
				oSignature=oObjetAdD(oSignature,oProduit,pmoA->typ);
				if (pmoA->nLigne>=200){
					ObjetVoiR("oSomme",oSignature,pmoA->typ);
				}
			}
			if (bAlterner)
				oSigne=oObjetOpP(oSigne,pmoA->typ);
		}
		//te("yDetermiiiiiiiiiiiiinant",ySignature);
		if (pmoA->nLigne<0){
			//MatriceVOir("Matrice déterminée",pmoA);
			//tq("qSignature",qSignature);
		}
	} else oSignature=pmoA->Mat[1][1];
	//Appel1("qSignatureCalculeR");
	
	return(oSignature);
}//oSignatureCalculeR

q qSignatureCalculeR(qMatricE *pmA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmA,ie calculée par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot;
	q qSignature,qProduit,qSigne,qSousSignature,qOperande;
	qMatricE *pmB;
	//Appel0("qSignatureCalculeR");
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	MatriqeAlloueR(&pmB);
	//te("pmA->nLigne",pmA->nLigne);
	if (pmA->nLigne>1){
		//MatriqeVoiR("Matrice Reçue",pmA);
		for (qSignature.num=0,qSignature.den=1,qSigne.num=1,qSigne.den=0,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
			//te("uPivot",uPivot);
			if (pmA->Mat[uPivot][1].num!=0){
				//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
					for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
						if (uL!=uPivot)
							for (nL++,nC=0,uC=2;nC++,uC<=pmA->nLigne;uC++)
								pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
					pmB->nLigne=pmA->nLigne-1;
					pmB->nColonne=pmA->nColonne-1;
				//MatriceVoir("Matrice B",pmB);
				qSousSignature=qSignatureCalculeR(pmB,bAlterner,pnAppelExponentiel);
				qOperande=qMul(qSigne,pmA->Mat[uPivot][1]);
				//s'assurer que le produit qui suit ne va pas déborder 
					Assert2("qSignatureCalculeR1",abs(pmA->Mat[uPivot][1].num)<=kuIntegerMax,abs(qSousSignature.num)<=kuIntegerMax);
				qProduit=qMul(qOperande,qSousSignature);
				//s'assurer que la somme qui suit ne va pas déborder 
					Assert2("qSignatureCalculeR2",abs(qSignature.num)<=kuIntegerMax,abs(qProduit.num)<=kuIntegerMax);//kxLongintMax/2 suffirait en fait!
				qSignature=qAdd(qSignature,qProduit);
			}
			if (bAlterner)
				qSigne.num=-qSigne.num;
		}
		//te("yDetermiiiiiiiiiiiiinant",ySignature);
		if (pmA->nLigne<0){
			MatriqeVoiR("Matrice déterminée",pmA);
			tq("qSignature",qSignature);
		}
	} else qSignature=pmA->Mat[1][1];
	//Appel1("qSignatureCalculeR");
	
	return(qSignature);
}//qSignatureCalculeR

ri riSignatureCalculeR(riMatrice *pmA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmA,ie calculée par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot;
	ri riSignature,riProduit,riSigne,riSousSignature,riOperande;
	riMatrice *pmB;
	//Appel0("riSignatureCalculeR");
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	MatRIceAllouer(&pmB);
	//te("pmA->nLigne",pmA->nLigne);
	if (pmA->nLigne>1){
		//MatriceVoir("Matrice Reçue",pmA);
		for (riSignature=riAff(0,0),riSigne=riAff(1,0),uPivot=1;uPivot<=pmA->nLigne;uPivot++){
			//te("uPivot",uPivot);
			if (pmA->Mat[uPivot][1].r!=0 || pmA->Mat[uPivot][1].i!=0){
				//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
					for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
						if (uL!=uPivot)
							for (nL++,nC=0,uC=2;nC++,uC<=pmA->nLigne;uC++)
								pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
					pmB->nLigne=pmA->nLigne-1;
					pmB->nColonne=pmA->nColonne-1;
				//MatriceVoir("Matrice B",pmB);
				riSousSignature=riSignatureCalculeR(pmB,bAlterner,pnAppelExponentiel);
				riOperande=riMul(riSigne,pmA->Mat[uPivot][1]);
				//s'assurer que le produit qui suit ne va pas déborder 
					Assert2("riSignatureCalculeR1",abs(pmA->Mat[uPivot][1].r)<=kuIntegerMax,abs(riSousSignature.r)<=kuIntegerMax);
				riProduit=riMul(riOperande,riSousSignature);
				//s'assurer que la somme qui suit ne va pas déborder 
					Assert2("riSignatureCalculeR2",abs(riSignature.r)<=kuIntegerMax,abs(riProduit.r)<=kuIntegerMax);//kxLongintMax/2 suffirait en fait!
				riSignature=riAdd(riSignature,riProduit);
			}
			if (bAlterner)
				riSigne.r=-riSigne.r;
		}
		//te("yDetermiiiiiiiiiiiiinant",ySignature);
		if (pmA->nLigne<0){
			MatRIceVoir("Matrice déterminée",pmA);
			tri("riSignature",riSignature);
		}
	} else riSignature=pmA->Mat[1][1];
	//Appel1("riSignatureCalculeR");
	
	return(riSignature);
}//riSignatureCalculeR

long ySignatureCalculeR(iMatrice *pmA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmA,ie récursive et par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot,muSigne;
	long yOperande,yProduit,ySignature,ySousSignature;
	iMatrice *pmB;
	//Appel0("ySignatureExactCalculeR");
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	//te("pmA->nLigne",pmA->nLigne);
	if (pmA->nLigne>1){
		//MatriceVoir("Matrice Reçue",pmA);
		MatriceAllouer(&pmB);
			for (ySignature=0,muSigne=1,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
				if (pmA->Mat[uPivot][1]!=0){
					//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
						for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
							if (uL!=uPivot)
								for (nL++,nC=0,uC=2;nC++,uC<=pmA->nLigne;uC++)
									pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
						pmB->nLigne=pmA->nLigne-1;
					//MatriceVoir("Matrice B",pmB);
					if (pmB->nLigne>300)
						te("uPivot",uPivot);
					ySousSignature=ySignatureCalculeR(pmB,bAlterner,pnAppelExponentiel);//Récursion laborieuse
					yOperande=muSigne*pmA->Mat[uPivot][1];
					//s'assurer que le produit qui suit ne va pas déborder 
						Assert2("ySignatureCalculeR1",abs(pmA->Mat[uPivot][1])<=kuIntegerMax,abs(ySousSignature)<=kuIntegerMax);
					yProduit=yOperande*ySousSignature;
					//s'assurer que la somme qui suit ne va pas déborder 
						Assert2("ySignatureCalculeR2",abs(ySignature)<=kuIntegerMax,abs(yProduit)<=kuIntegerMax);//oui,kxLongintMax/2 suffirait.
					ySignature+=yProduit;
				};
				if (bAlterner)
					muSigne=-muSigne;
			}
		free(pmB);
		//te("ySignature",ySignature);
	} else ySignature=pmA->Mat[1][1];
	//Appel1("ySignatureExactCalculeR");
	return(ySignature);
}//ySignatureCalculeR

void SignatureCertifieR(graf *pgG,int bSinguliere){//O(S3)
	//s'assure en O(S3) que le polynome associé à pgG est nul ssi bSinguliere est vrai.
	const int kbAlterner=kV;//obligatoire car sinon c'est un permanent qui serait calculé (en tps exponentiel).
	long ySignature,yValeur;
	yMatricE *pmA;//dc longint
	int nAppelExponentiel,bCertificat,aK,bPreuve,uEpreuve,uEpreuveMax,nP,sX,sY;
	Appel0("SignatureCertifieR");
		MatriceAlloueR2(&pmA);
			pmA->nLigne=pmA->nColonne=pgG->nSommetEnTout;
			uEpreuveMax=pgG->nSommetEnTout;
			te("uEpreuveMax",uEpreuveMax);
			//si le polynome est non nul,au moins une signature d'une épreuve ci-dessous est non nulle.
			//si le le polynome est nul,toutes les signatures des épreuves ci-dessous sont nulles.
			for (nAppelExponentiel=0,bPreuve=kF,uEpreuve=1;uEpreuve<=uEpreuveMax && !bPreuve;uEpreuve++){
				for (nP=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						if (sX<sY){
							yValeur=zPuissance(nPremier(++nP),uEpreuve);
							pmA->Mat[sX][sY]=+yValeur;
							pmA->Mat[sY][sX]=ySignePres(kbAlterner,yValeur);
						}
					}
				MatriceVoyR("Matrice antisymétrique SINGULIERE associée au graphe",pmA);
				printf("Nombre premier maximal de rang %s et élément maximal de valeur %s.\n",sEnt(nP),sPar3(yValeur));
				ySignature=ySygnatureCalculeR(pmA,kbAlterner,&nAppelExponentiel);//calcule le déterminant,vu kbAlterner.
				printf("uEpreuve %s,ySignature %s.\n",sEnt(uEpreuve),sPar3(ySignature));
				bCertificat=(bSinguliere==(ySignature==0));
				Assert1("SignatureCertifieR1",bCertificat);//SI se produit,pas de panique: POURSUIVRE AVEC LES CARRÉS DES PREMIERS,ETC
				if (!bSinguliere)
					bPreuve=(ySignature!=0);
			}
		free(pmA);
		Assert1("SignatureCertifieR2",bCertificat);//ANORMAL si le degré du polynome est bien borné par uEpreuveMax.
	Appel1("SignatureCertifieR");
}//SignatureCertifieR

long ySygnatureCalculeR(yMatricE *pmA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmA,ie récursive et par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot,muSigne;
	long yOperande,yProduit,ySignature,ySousSignature;
	yMatricE *pmB;
	//Appel0("ySignatureExactCalculeR");
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	//te("pmA->nLigne",pmA->nLigne);
	if (pmA->nLigne>1){
		//MatriceVoir("Matrice Reçue",pmA);
		MatriceAlloueR2(&pmB);
			for (ySignature=0,muSigne=1,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
				if (pmA->Mat[uPivot][1]!=0){
					//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 et de la ligne uPivot
						for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
							if (uL!=uPivot)
								for (nL++,nC=0,uC=2;nC++,uC<=pmA->nLigne;uC++)
									pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
						pmB->nLigne=pmA->nLigne-1;
					//MatriceVoir("Matrice B",pmB);
					if (pmB->nLigne>300)
						te("uPivot",uPivot);
					ySousSignature=ySygnatureCalculeR(pmB,bAlterner,pnAppelExponentiel);//Récursion laborieuse
					yOperande=muSigne*pmA->Mat[uPivot][1];
					//s'assurer que le produit qui suit ne va pas déborder 
						//Assert2("ySignatureCalculeR1",abs(pmA->Mat[uPivot][1])<=kxLongintMax,abs(ySousSignature)<=kxLongintMax);
					yProduit=yOperande*ySousSignature;
					//s'assurer que la somme qui suit ne va pas déborder 
						//Assert2("ySignatureCalculeR2",abs(ySignature)<=kxLongintMax,abs(yProduit)<=kxLongintMax);//oui,kxLongintMax/2 suffirait.
					ySignature+=yProduit;
				};
				if (bAlterner)
					muSigne=-muSigne;
			}
		free(pmB);
		//te("ySignature",ySignature);
	} else ySignature=pmA->Mat[1][1];
	//Appel1("ySignatureExactCalculeR");
	return(ySignature);
}//ySygnatureCalculeR

long ySignatureKalculeR(iMatrice *pmA,int bAlterner,int *pnAppelExponentiel){
	//rend la signature "laborieuse" de pmA,ie récursive et par sommation (alternée ssi bAlterner) de cofacteurs;déroute si calcul hors domaine.
	int uC,uL,nL,nC,uPivot,mSigne;
	int bDoublet;
	long yOperande,yProduit,ySignature,ySousSignature;
	iMatrice *pmB;
	//Appel0("ySignatureExactCalculeR");
	Assert1("ySignatureKalculeR0",pmA->nLigne%2==0 || pmA->nSecante==0);
	//MatriceVoir("Matrice pmA",pmA);
	*pnAppelExponentiel=*pnAppelExponentiel+1;
	MatriceAllouer(&pmB);
	//te("pmA->nLigne",pmA->nLigne);
	if (pmA->nLigne>1){
		//MatriceVoir("Matrice Reçue",pmA);
		Assert1("ySignatureCalculeR19",pmA->nSecante%2==0);
		for (ySignature=0,mSigne=1,uPivot=1;uPivot<=pmA->nLigne;uPivot++){
			bDoublet=(uPivot<pmA->nSecante);
			//bDoublet=kV;
			te("uPivot",uPivot);
			//pmB soit la copie carrée de la matrice carrée pmA amputée de la colonne 1 (et 2) et de la ligne uPivot (et uPivot+1),selon bDoublet
			if (bDoublet){
				MatriceVoir("Matrice A",pmA);
				for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
					if (uL!=uPivot && uL!=uPivot+bDoublet)
						for (nL++,nC=0,uC=2+bDoublet;nC++,uC<=pmA->nColonne;uC++)
							pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
				pmB->nLigne=pmA->nLigne-1-bDoublet;
				pmB->nColonne=pmA->nColonne-1-bDoublet;
				pmB->nSecante=pmA->nSecante-2*bDoublet;
				MatriceVoir("Matrice B",pmB);
			}else{
				for (nL=0,uL=1;uL<=pmA->nLigne;uL++)
					if (uL!=uPivot)
						for (nL++,nC=0,uC=2;nC++,uC<=pmA->nColonne;uC++)
							pmB->Mat[nL][nC]=pmA->Mat[uL][uC];
				pmB->nLigne=pmA->nLigne-1;
				pmB->nColonne=pmA->nColonne-1;
			}
			//MatriceVoir("Matrice B",pmB);
			ySousSignature=ySignatureCalculeR(pmB,bAlterner,pnAppelExponentiel);//Récursion laborieuse
			yOperande=mSigne*pmA->Mat[uPivot][1];
			//s'assurer que le produit qui suit ne va pas déborder 
				Assert2("ySignatureCalculeR1",labs(pmA->Mat[uPivot][1])<=kuIntegerMax,labs(ySousSignature)<=kuIntegerMax);
			yProduit=yOperande*ySousSignature;
			//s'assurer que la somme qui suit ne va pas déborder 
				Assert2("ySignatureKalculeR2",labs(ySignature)<=kuIntegerMax,labs(yProduit)<=kuIntegerMax);//oui,kxLongintMax/2 suffirait.
			ySignature+=yProduit;
			if (bAlterner)
				mSigne=-mSigne;
			if (bDoublet)
				uPivot++;
		}
		//te("ySignature",ySignature);
	} else ySignature=pmA->Mat[1][1];
	//Appel1("ySignatureExactCalculeR");
	return(ySignature);
}//ySignatureKalculeR

int bSygnaturePairE(int nPermutation[]){
	int uP,uI,uJ;
	int nInversion;
	int bPaire=kF;
	//Appel0("bSygnaturePairE");
		printf("Permutation (%d éléments):\n",nPermutation[0]);
			for (printf("%s",sTab(1)),uP=1;uP<=nPermutation[0] || bPrint(".");uP++)
				printf("%3d",uP);
			for (printf("%s",sTab(1)),uP=1;uP<=nPermutation[0] || bPrint(".");uP++)
				printf("%3d",nPermutation[uP]);
		//bPaire:=permutation paire
			for (nInversion=0,uI=1;uI<=nPermutation[0];uI++){
				for (uJ=uI+1;uJ<=nPermutation[0];uJ++)
					if (nPermutation[uI]>nPermutation[uJ])
						nInversion++;
			}
			te("Nombre total d'inversions",nInversion);
			bPaire=bPair(nInversion);
	//Appel1("bSygnaturePairE");
	return(bPaire);
}//bSygnaturePairE

void SommetApparieR(int nEtoile,iMatrice *pmA){
	int uL,uC;
	int ipP;
	int nEcart;
	int sX,sY;
	int nPermutation[knLigneLiM];
	for (ipP=0,uL=1;uL<=2;uL++){
		sX=(uL-1)*4+1+nEtoile;
		for (uC=1;uC<=2;uC++){
			sX++;
			sY=sX+2;
			//tee("sX,sY",sX,sY);
			nPermutation[++ipP]=sX;
			nPermutation[++ipP]=sY;
		}
	}
	nEcart=pmA->nLigne-(2+nEtoile);
	for (uL=1+1;uL<=1+nEtoile;uL++){
		//tee("uL,uL+nEcart",uL,uL+nEcart);
		nPermutation[++ipP]=uL;
		nPermutation[++ipP]=uL+nEcart;
	}
	//tee("1,pmA->nLigne",1,pmA->nLigne);
	nPermutation[++ipP]=1;
	nPermutation[++ipP]=pmA->nLigne;
	for (uL=1;uL<=pmA->nLigne;uL++)
		pmA->Mat[uL][0]=pmA->Mat[0][uL]=nPermutation[uL];
}//SommetApparieR

void SygnaturePredirE(){
	int nArcOrigine[]=    {0,   1, 1, 2, 2, 3,    3, 4, 5, 6, 6,    7, 7, 8, 9,10,    10,11,11};
	int nArcDestination[]={0,   4, 5, 4, 8, 5,    9, 6, 7, 9,12,    8,13,10,11,12,    14,13,14};
	int nPermutation0[1+18]={14,  5,4,9,2,1,12,8,7,3,14,13,6,11,10};
	int nPermutation1[1+18]={14,  4,8,5,1,3,9,13,2,6,12,14,10,7,11};
	int nAppariement[1+18];
	int nPermutation[1+18];
	graf *pgA;
	int aK,sX,sY,uL,uC;
	int nEtoile;
	int nSommet=14;
	int nArc=18;
	iMatrice *pmA;
	GrapheCreer2(&pgA,nSommet,nArc,&nArcOrigine[0],&nArcDestination[0]);
	GrapheVoir(pgA,"Graphe saisi");
	tb("bSygnaturePairE",bSygnaturePairE(nPermutation0));
	tb("bSygnaturePairE",bSygnaturePairE(nPermutation1));
	nSommet=pgA->nSommetEnTout;
	MatriceAlloueR0(&pmA,nSommet,nSommet,0);
	GrapheMatriceR(pgA,kV,4*nSommet*nSommet,4*nSommet*nSommet,&pmA);
	MatriceVoir("Matrice brute",pmA);
	SommetApparieR(nEtoile=2,pmA);
	for (uL=1;uL<=pmA->nLigne;uL++)
		nAppariement[uL]=pmA->Mat[0][uL];
	if (0) VecteurVoir("nAppariement",nAppariement,1,pmA->nLigne);
	for (uL=1;uL<=pmA->nLigne;uL++)
		nPermutation[uL]=0;
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			if (nAppariement[uC]==uL)
				nPermutation[uL]=uC;
	if (0) VecteurVoir("nPermutation",nPermutation,1,pmA->nLigne);
	for (uL=1;uL<=pmA->nLigne;uL++)
		for (uC=1;uC<=pmA->nColonne;uC++)
			pmA->Mat[uL][uC]=0;
	for (sX=1;sX<=pgA->nSommetEnTout;sX++)
		for (aK=pgA->aHed[sX];aK<pgA->aHed[sX+1];aK++){
			sY=pgA->sSuk[aK];
			pmA->Mat[nPermutation[sX]][nPermutation[sY]]=+1;
			pmA->Mat[nPermutation[sY]][nPermutation[sX]]=-1;
		}
	pmA->nSecante=pmA->nLigne;
	MatriceVoir("Matrice appariée",pmA);
}//SygnaturePredirE

void TriEffectueR(){
	//trie les lignes de la matrice A pour la multiplier ensuite plus rapidement par B; affiche la complexité équivalente
	iMatrice *pmA;
	iMatrice *pmB;
	iMatrice *pmC;
	long zN2;
	float fDensiteh;
	Appel0("TriEffectueR");
		MatriceAllouer(&pmA);
			MatriceAllouer(&pmB);
				MatriceAllouer(&pmC);
					fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmA);
					fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmB);
					//MatriceVoir("Matrice A",pmA);
					//MatriceVoir("Matrice B",pmB);
					zN2=zMatriceMultiplieR(pmA,pmB,&pmC);
					//MatriceVoir("Matrice AxB",pmC);
					//te("zN2",zN2);
					ComplexitehAfficheR(zN2);
					//MatriceVoir("Matrice A avant tri",pmA);
					MatriceTrierTouT(pmA);
					//MatriceVoir("Matrice A après tri",pmA);
	Appel1("TriEffectueR");
}//TriEffectueR

void TriUtiliseR(int nCas){
	switch (nCas) {
		case tuSimplE:
			TriEffectueR();
			break;
	default:
		break;
	}
}//TriUtiliseR
