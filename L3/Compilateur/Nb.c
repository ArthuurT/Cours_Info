#include "Outil.h"
#include "Nb.h"
int bNbAmorceR;//vrai ssi le présent module a été amorcé
//ci-dessous kxBaseMaX ne doit pas dépasser kuIntegerMaX, eg 2**31-1. Pour NbTESTER, travailler en base 10 avec avec kxBaseMaX=9.
#define kxBaseMaX (kE9-1) //ainsi, chaque superdigit occupe exactement 3 paquets de 3 décits,cf sPar3()
//#define kxBaseMaX (kE9-1) //ainsi, chaque superdigit occupe exactement 3 paquets de 3 décits,cf sPar3()
//#define kxBaseMaX 9
long kxBaseLiM=1+(long) kxBaseMaX;

char *sNb1(nb nbA,int nPoids,int nEntier);
int tNbCompareR(nb nbA,nb nbB);
void NbComplementeR(nb *pnbA);
void NbDecrementeR(nb *pnbA);
void NbTesterFiB(int nFibMax);
void NbIncrementeR(nb *pnbA);
void NbKnapsacK(nbMatrice *pmA,int bVoir,nb *pnbResultat);//O(N3)
void NbMatriceAllouer(nbMatrice **ppmnbA);
void NbMatriceAllouer1(nbMatrice **ppmnbA,int nLigneEnTout);
void NbMatriceAllouer2(nbMatrice **pmnbA,int nLigneEnTout,int nColonneEnTout);
void NbMatriceDupliqueR(nbMatrice *pmnbA,nbMatrice *pmnbB);
void NbMatriceFoisseR(int iFois,nbMatrice *pmnbA);
void NbMatriceVoiR(char *sMessage,nbMatrice *pmnbA);
void NbMatriceZeroteR(nbMatrice *pmnbA,int uHauteur,nbMatrice *pmnbAh);
void NbOpposeR(nb *pnbA);
void NbSkewClosurE(nbMatrice *pmnbA,int uParcoursLgMax,nbMatrice **ppmnbAchapo);//O(N4)
void NbVecteurCopieR(nb ynbVecteurA[],int nIndexMin,int nIndexMax,nb ynbVecteurB[]);
void NbVecteurRazeR(nb ynbVecteur[],int nIndexMin,int nIndexMax);

char *sNb(nb nbA){
	//convertit en chaîne,dont signe ssi non nul
	char *sNb;
	int nPoids,nPoidsFort,bNul;
	sNb=(bNbNul(nbA))? "": (nbA.sign>=0)? "+" : "-";
	for (bNul=kV, nPoidsFort=kuNbMax, nPoids=kuNbMax-1;nPoids>=0 && bNul;nPoids--){
		nPoidsFort--;
		bNul=nbA.digit[nPoids]==0;
	}
	sNb=sC2(sNb,sPar3(nbA.digit[nPoidsFort]));
	for (nPoids=nPoidsFort-1;nPoids>=0;nPoids--)
		sNb=sC2b(sNb,sPar3(nbA.digit[nPoids]));
	t(sG(sNb));
	return(sNb);
}//sNb

long yNb(nb nbA){
	//convertit en longint ds [-kxLongintMax..+kxLongintMax],dc hors kyLongintMin
	long yN;
	int nPoids;
	const int bVoir=kF;
	if (bVoir) NbVoir("yNb:nbA",nbA);
	for (yN=0,nPoids=kuNbMax-1;nPoids>=0;nPoids--){
		yN=kxBaseLiM*yN+nbA.digit[nPoids];
		Assert1("yNb",yN<=kxLongintMax);
		if (bVoir) d(yN);
	}
	yN=yN*nbA.sign;//défini pr toute donnée ds 0..kxLongintMax puisque |kyLongintMin|<|kxLongintMax|
	if (bVoir) te("yN",yN);
	return(yN);
}//yNb

char *sNb0(nb nbA,int nEntier){
	//convertit en chaîne,dont signe ssi non nul et place le nombre à droite ds nEntier caractères
	char *sNb0=sChaine0(sNb(nbA),nEntier);
	return(sNb0);
}//sNb0

char *sNb1(nb nbA,int nPoids,int uEmpan){
	char *sNb1=(nPoids==kuNbMax)? (nbA.sign>=0)? sC('+') : sC('-') : sC('.');
	//char *sNb1=(nbA.sign>=0)? sC('+') : sC('-');
	sNb1=sC2(sNb1,sEntier(nbA.digit[nPoids],uEmpan) );
	return(sNb1);
}//sNb1

void NbAdd(nb nbA,nb nbB,nb *pnbS){
	int nPoids,bRetenue,tCompare,iSigne;
	long zSomme;
	const int bVoir =kF;
	if (bVoir) NbVoir("NbAdd: nbA",nbA);
	if (bVoir) NbVoir("NbAdd: nbB",nbB);
	pnbS->sign=nbA.sign;//d
	if (nbA.sign==nbB.sign){
		for (bRetenue=0,nPoids=0;nPoids<=kuNbMax;nPoids++){
			zSomme=(long) nbA.digit[nPoids]+(long) nbB.digit[nPoids]+(long) bRetenue;
			bRetenue=zSomme>kxBaseMaX;
			if (bRetenue)
				zSomme=zSomme-kxBaseLiM;
			if (bVoir) d(bRetenue);
			Assert1("NbAdd",bCroit(0,zSomme,kxBaseMaX) );
			pnbS->digit[nPoids]=zSomme;
		}
		//Assert1("NbAdd",bRetenue==0);
	}else {
		nbB.sign=-nbB.sign;
			tCompare=tNbCompareR(nbA,nbB);
		nbB.sign=-nbB.sign;
		if (bVoir) d(tCompare);
		if (tCompare>0){// A > -B
			iSigne=nbA.sign;
			nbA.sign=nbB.sign=+1;
			NbSub(nbA,nbB,pnbS);
			pnbS->sign=iSigne;
		}
		if (tCompare<0){// A < -B
			iSigne=nbB.sign;
			nbA.sign=nbB.sign=+1;
			NbSub(nbB,nbA,pnbS);
			pnbS->sign=iSigne;
		}
		if (tCompare==0){// A = -B
			NbAffecter(0,pnbS);
		}
	}
	if (bVoir) NbVoir("NbAdd: pnbS",*pnbS);
}//NbAdd

void NbAffecter(int iEntier,nb *pnbA){
	int nPoids;
	long zEntier;
	//te("NbAffecter",iEntier);
	pnbA->sign=(iEntier>=0)? +1: -1;
	zEntier=labs( (long) iEntier);
	for (nPoids=0;nPoids<=kuNbMax;nPoids++){
		//te("zEntier%kxBaseLiM",zEntier%kxBaseLiM);
		pnbA->digit[nPoids]=zEntier%kxBaseLiM;
		zEntier=zEntier/kxBaseLiM;
	}
}//NbAffecter

void NbAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bNbAmorceR=kV;
	Assert2("NbAMORCER",kxBaseLiM<=1+(long) kuIntegerMax,bPuissanceDe2(kuNbLim));
}//NbAMORCER

int tNbCompareR(nb nbA,nb nbB){
	//rend +1 si nbA>nbB, -1 si nbA<nbB et 0 sinon.
	int tComparer,nPoids;
	if (nbA.sign==nbB.sign){
		for (tComparer=0,nPoids=kuNbMax;nPoids>=0 && tComparer==0;nPoids--)
			if (nbA.digit[nPoids]!=nbB.digit[nPoids])
				tComparer=(nbA.digit[nPoids]>nbB.digit[nPoids])? +1: -1;
	}else tComparer=nbA.sign;
	return(tComparer);
}//tNbCompareR

void NbComplementeR(nb *pnbA){
	//complément à 2: sur 2 digits,le complément de 49 est 51
	int nSomme,nPoids,bRetenue;
	const int bVoir=kF;
	if (bVoir) NbVoir("complément AVANT",*pnbA);
	if (!bNbNul(*pnbA) ){
		//complémenter à 1
			for (nPoids=0;nPoids<=kuNbMax;nPoids++)
				pnbA->digit[nPoids]=kxBaseMaX-pnbA->digit[nPoids];
			if (bVoir) NbVoir("complément à 1",*pnbA);
			if (bVoir) d2(pnbA->digit[1],pnbA->digit[0]);
		//incrémenter
			for (bRetenue=1,nPoids=0;nPoids<=kuNbMax;nPoids++){
				nSomme=pnbA->digit[nPoids]+bRetenue;
				if (bVoir) teee("AVANT pnbA->digit[nPoids],bRetenue,nSomme",pnbA->digit[nPoids],bRetenue,nSomme);
				bRetenue=nSomme>=kxBaseLiM;
				if (bRetenue)
					nSomme-=kxBaseLiM;
				if (bVoir) teee("APRÉS pnbA->digit[nPoids],bRetenue,nSomme",pnbA->digit[nPoids],bRetenue,nSomme);
				Assert1("NbComplementeR",bCroit(0,nSomme,kxBaseMaX) );
				pnbA->digit[nPoids]=nSomme;
			}
	}
	if (bVoir) NbVoir("complément APRES",*pnbA);
}//NbComplementeR

void NbDecrementeR(nb *pnbA){
	nb nbDecrement;
	NbAffecter(1,&nbDecrement);
	//NbVoir("nbDecrement",nbDecrement);
	NbSub(*pnbA,nbDecrement,pnbA);
}//NbDecrementeR

void NbDeterminer(nbMatrice *pmnbQ,int bVoir,nb *pnbDeterminant){//O(S3.5) exact car sans division
	//rend dans pnbDeterminant le déterminant de pmnbQ ——méthode de Urbanska
	//int bColonnesImpairesVides;
	nb ynbKalculer;
	//int nSommetTraversehParMotif=5;
	//int nArcTraversehPourAtteindreEtageSuivant=1;//et circulairement
	int uParcoursLgMax=pmnbQ->nLigne;
	if (bVoir) Titrer("NbDeterminer");
	//te("uParcoursLgMax",uParcoursLgMax);
	nbMatrice *pmnbQchappo;
	//Appel0(sC2b("NbDeterminer",sP(sC2b("dimension",sEnt(nDim)))));
		if (bVoir) NbMatriceVoiR("Calcul du déterminant Urbanska sur la matrice ci-dessous",pmnbQ);
		Assert2("NbDeterminer2",pmnbQ->nLigne==pmnbQ->nColonne,bCroit(1,pmnbQ->nLigne,kE2));
		NbMatriceAllouer2(&pmnbQchappo,pmnbQ->nLigne,uParcoursLgMax);
		//Assert1("yFormeKalculeR",uParcoursLgMax==pmnbQ->nLigne);
			//tee("NbSkewClosurE0:pmnbQchappo->nLigne,pmnbQchappo->nColonne",pmnbQchappo->nLigne,pmnbQchappo->nColonne);
		//pmnbQchappo->nSecante=(bColonnesImpairesVides)? -2:0;
		/*	pmnbQchappo->nSecante=-2;
		else pmnbQchappo->nSecante=0;*/
		NbSkewClosurE(pmnbQ,uParcoursLgMax,&pmnbQchappo);//O(N4)
		//tb("bColonnesImpairesVides",bColonnesImpairesVides);
		/*if (bColonnesImpairesVides)
			pmnbQchappo->nSecante=-2;
		else*/ pmnbQchappo->nSecante=0;
		//tee("bColonnesImpairesVides,pmnbQchappo->nSecante",bColonnesImpairesVides,pmnbQchappo->nSecante);
		if (bVoir) NbMatriceVoiR("Matrice pmnbQchappo (head x longueur) des sommes des produits des CLOWs avant cplémtO",pmnbQchappo);
		//rendre (-1)**N * KnapsacK(- pmnbQchappo)
			NbMatriceFoisseR(-1,pmnbQchappo);
			//NbMatriceVoiR("pmnbQchappo après négation",pmnbQchappo);
		//tee("bColonnesImpairesVides,pmnbQchappo->nSecante",bColonnesImpairesVides,pmnbQchappo->nSecante);
			pmnbQchappo->nLigne=pmnbQ->nLigne;
			pmnbQchappo->nColonne=pmnbQ->nLigne;
			//tee("yKnapsacK:pmnbQchappo->nLigne,pmnbQchappo->nColonne",pmnbQchappo->nLigne,pmnbQchappo->nColonne);
			NbKnapsacK(pmnbQchappo,bVoir,&ynbKalculer);//O(N3)
			if ( bImpair(pmnbQ->nLigne) )
				NbOpposeR(&ynbKalculer);//multiplie par -1
			*pnbDeterminant=ynbKalculer;
			if (bVoir) printf("DETERMINANT: %s.\n",sNb(*pnbDeterminant));
		//iBof=iKnaP(pmnbQchappo);
	//Appel1(sC2b("NbDeterminer",sP(sC2b("dimension",sEnt(nDim)))));
}//NbDeterminer

void NbDupliquer(nb nbA,nb *pnbCopie){
	int nPoids;
	for (nPoids=0;nPoids<=kuNbMax;nPoids++)
		pnbCopie->digit[nPoids]=nbA.digit[nPoids];
	pnbCopie->sign=nbA.sign;
}//NbDupliquer

int bNbEgal(nb nbA,nb nbB){
	int bEgal,nPoids;
	for (bEgal=nbA.sign==nbB.sign,nPoids=0;nPoids<=kuNbMax;nPoids++)
		bEgal=bEgal && nbA.digit[nPoids]==nbB.digit[nPoids];
	return(bEgal);
}//bNbEgal

void NbFib(int nFibMax,nb *pnbFib){
	int uF;
	nb nbFmoins1,nbFmoins2;
	Assert3("NbFib",kxBaseMaX==kE9-1,kuNbMax==7,bCroit(0,nFibMax,300));
	if (nFibMax>5){
		NbAffecter(1,&nbFmoins1);
		NbAffecter(1,pnbFib);
		for (uF=3;uF<=nFibMax;uF++){
			NbDupliquer(nbFmoins1,&nbFmoins2);
			NbDupliquer(*pnbFib,&nbFmoins1);
			NbAdd(nbFmoins2,nbFmoins1,pnbFib);
		}
	}else NbAffecter(zFib(nFibMax),pnbFib);
}//NbFib

void NbIncrementeR(nb *pnbA){
	nb nbIncrement;
	NbAffecter(1,&nbIncrement);
	NbAdd(nbIncrement,*pnbA,pnbA);
}//NbIncrementeR

void NbINITIALISER(){//O(?)
	//relance le présent module
	Assert1("NbINITIALISER",bNbAmorceR);
}//NbINITIALISER

void NbKnapsacK(nbMatrice *pmA,int bVoir,nb *pnbResultat){//O(N3)
	//rend la valeur du knapsack (les valeurs successives sont calculées dans la matrice pKnapsack;résultat au bout de la diag principale).
	int uLg,uHead,uP;
	nb ynbTerme,znbSommeProduit,nbProduit;
	nbMatrice *pnbKnapsack;
	pmA->nSecante=0;
	//tee("yKnapsacK:bColonnesImpairesVides,pmAchappo->nSecante",bColonnesImpairesVides,pmA->nSecante);
	//if (bVoir) NbMatriceVoiR("Matrice complémentée (head de clow x longueur de clow) des sommes de produits reçue par yKnapsacK",pmA);
	NbMatriceAllouer2(&pnbKnapsack,pmA->nLigne,pmA->nColonne);
		pnbKnapsack->nSecante=0;
		for (uLg=1;uLg<=pmA->nColonne;uLg++)
			pnbKnapsack->Mat[1][uLg]=pmA->Mat[1][uLg];
		for (uHead=2;uHead<=pmA->nLigne;uHead++)//O(N2) //******* BUG ALGORITHMICA (2010) 56:35-50 p41:"for i,j from 1 to n we compute" vs from 2.
			for (uLg=1+0;uLg<=pmA->nColonne;uLg+=1+0){//O(N2)
				//Table[i,j]=∑ sur 0<p<j de (Table[i-1,p]xA[i,j-p])+Table[i-1,j]
				NbAffecter(0,&znbSommeProduit);
				for (uP=1+0;uP<uLg;uP+=1+0){//O(N)
					ynbTerme=pmA->Mat[uHead][uLg-uP];
					NbMul(pnbKnapsack->Mat[uHead-1][uP],ynbTerme,&nbProduit);
					NbAdd(znbSommeProduit,nbProduit,&znbSommeProduit);
				}
				ynbTerme=pnbKnapsack->Mat[uHead-1][uLg];
				NbAdd(znbSommeProduit,ynbTerme,&pnbKnapsack->Mat[uHead][uLg]);
			}
		if (bVoir)
			NbMatriceVoiR("Matrice pnbKnapsack (head x longueur totale) des sommes de produits de SÉQUENCES de clows",pnbKnapsack);
		*pnbResultat=pnbKnapsack->Mat[pmA->nLigne][pmA->nColonne];
	free(pnbKnapsack);
}//NbKnapsacK

void NbMatriceAllouer(nbMatrice **ppmnbA){
	*ppmnbA=malloc(sizeof(nbMatrice));
}//NbMatriceAllouer

void NbMatriceAllouer1(nbMatrice **ppmnbA,int nLigneEnTout){
	Assert1("NbMatriceAllouer1",nLigneEnTout>=0);
	NbMatriceAllouer(ppmnbA);
	(*ppmnbA)->nLigne=nLigneEnTout;
	(*ppmnbA)->nColonne=nLigneEnTout;
	(*ppmnbA)->nSecante=0;
}//NbMatriceAllouer1

void NbMatriceAllouer2(nbMatrice **pmnbA,int nLigneEnTout,int nColonneEnTout){
	Assert2("NbMatriceAllouer2",nLigneEnTout>=0,nColonneEnTout>=0);
	NbMatriceAllouer(pmnbA);
	(*pmnbA)->nLigne=nLigneEnTout;
	(*pmnbA)->nColonne=nColonneEnTout;
	(*pmnbA)->nSecante=0;
}//NbMatriceAllouer2

void NbMatriceDupliqueR(nbMatrice *pmnbA,nbMatrice *pmnbB){
	//si bDontPermutation,duplique aussi les permutations
	int nL,nC;
	int bHorsPermutation=0;
	int nLigneMax=pmnbA->nLigne;
	for (nL=bHorsPermutation;nL<=nLigneMax;nL++)
		for (nC=bHorsPermutation;nC<=nLigneMax;nC++)
			pmnbB->Mat[nL][nC]=pmnbA->Mat[nL][nC];
}//NbMatriceDupliqueR

void NbMatriceFoisseR(int iFois,nbMatrice *pmnbA){
	int uL,uC;
	nb nbFois;
	NbAffecter(iFois,&nbFois);
	for (uL=1;uL<=pmnbA->nLigne;uL++)
		for (uC=1;uC<=pmnbA->nColonne;uC++)
			NbMul(pmnbA->Mat[uL][uC],nbFois,&pmnbA->Mat[uL][uC]);
}//NbMatriceFoisseR

void NbMatriceVoiR(char *sMessage,nbMatrice *pmnbA){
	int uC,uL,uEmpan,uPas,nPoids;
	//const int uLargeur=15;
 	Assert2("NbMatriceVoiR",bNbAmorceR,sMessage!=0);
	//Appel0("NbMatriceVoiR");
	printf("%s (%dx%d):\n",sMessage,pmnbA->nLigne,pmnbA->nColonne);
	uPas=(pmnbA->nSecante==-2)? 2: 1;
	//uEmpan soit le sup des encombrements des valeurs numériques (entiers),signe compris,borné par le nombre de décits sans signe de xkSeuil.
		//pmnbA->Mat[5][5].q21=kE7;
		for (uEmpan=1,uL=uPas;uL<=pmnbA->nLigne;uL+=uPas)
			for (uC=uPas;uC<=pmnbA->nColonne;uC+=uPas)
				for (nPoids=kuNbMax;nPoids>=0;nPoids--)
					uEmpan=iMax(uEmpan,nChaineLg(sEnt(pmnbA->Mat[uL][uC].digit[nPoids])));
		uEmpan=1+iSup(4,uEmpan);
		d(uEmpan);
	//te("NbMatriceVoiR:uEmpan",uEmpan);
	//pmnbA soit affiché
		for (printf("  "),uC=uPas;uC<=pmnbA->nColonne;uC+=uPas)//afficher les numéros de colonne
			printf(" %s%2d",sFois(uEmpan-1,'.'),uC);
		Ligne();
		for (uL=1;uL<=pmnbA->nLigne;uL++){//afficher les tuples verticalt cause ascenseur horizontal inexistant
			for (printf("%2d ",uL),nPoids=kuNbMax;nPoids>=0;nPoids--){
				for (uC=uPas;uC<=pmnbA->nColonne || !bLigne();uC+=uPas)
					for (uC=uPas;uC<=pmnbA->nColonne;uC+=uPas)
						printf("%s ",sNb1(pmnbA->Mat[uL][uC],nPoids,uEmpan));
				if (nPoids>0) printf("   ");else Ligne();
			}
		}
	if (pmnbA->nSecante==-2){//vérifier que les éléments impairs sont tous nuls
		for (uL=1;uL<=pmnbA->nLigne;uL++)
			for (uC=1;uC<=pmnbA->nColonne;uC+=2)
				Assert1("NbMatriceVoiR colonne impaire nulle",bNbNul(pmnbA->Mat[uL][uC]));
	}
	//Appel1("NbMatriceVoiR");
}//NbMatriceVoiR

void NbMatriceZeroteR(nbMatrice *pmnbA,int uHauteur,nbMatrice *pmnbAh){
	//all rows and columns not greater than uHauteur zeroed
	int uC,uL;
	Assert1("NbMatriceZeroteR",bCroit(1,uHauteur,pmnbA->nLigne));
	NbMatriceDupliqueR(pmnbA,pmnbAh);
	for (uL=1;uL<=uHauteur;uL++)
		for (uC=1;uC<=pmnbA->nLigne;uC++)
			NbAffecter(0,&pmnbAh->Mat[uL][uC]);
	for (uL=1;uL<=pmnbA->nLigne;uL++)
		for (uC=1;uC<=uHauteur;uC++)
			NbAffecter(0,&pmnbAh->Mat[uL][uC]);
}//NbMatriceZeroteR

void NbMul(nb nbA,nb nbB,nb *pnbP){
	int bDebordement,nPasse,nPoids,bRetenue,nRetenue;
	int nProduit;
	long zProduit,zSomme;
	nb nbProduit;
	int nOp[1+2*kuNbLim];
	//NbVoir("NbMul:nbA",nbA);
	//NbVoir("NbMul:nbB",nbB);
	NbAffecter(0,&nbProduit);
	VecteurRazer(nOp,0,2*kuNbMax+1);
	//VecteurVoir("nOp",nOp,0,2*kuNbMax+1);
	for (bDebordement=kF,nPasse=0;nPasse<=kuNbMax;nPasse++){
		//nbProduit soit le produit du digit courant de nbB par le vecteur nbA
			for (nbProduit.sign=1,nRetenue=0,nPoids=0;nPoids<=kuNbMax;nPoids++){
				zProduit=(long) nbA.digit[nPasse]*(long) nbB.digit[nPoids]+(long) nRetenue;
				nRetenue=zProduit/kxBaseLiM;
				zProduit=zProduit%kxBaseLiM;
				nProduit=zProduit;
				nbProduit.digit[nPoids]=nProduit;
				//VecteurVoir(sC2("nOp",sEnt(nPoids)),nOp,0,2*kuNbMax+1);
			}
		bDebordement= bDebordement || nRetenue!=0;
		//tb("bDebordement0",bDebordement);
		//zOp accumule nbProduit
			//VecteurVoir("nOpAVANT",nOp,0,2*kuNbMax+1);
			for (bRetenue=0,nPoids=0;nPoids<=kuNbMax;nPoids++){
				zSomme=(long) nOp[nPasse+nPoids] + (long) nbProduit.digit[nPoids]+(long) bRetenue;
				//te("zSomme",zSomme);
				bRetenue=zSomme>kxBaseMaX;
				zSomme=zSomme%kxBaseLiM;
				Assert1("NbMul",bCroit(0,zSomme,kxBaseMaX) );
				nOp[nPasse+nPoids]=zSomme;
				//tee("nPasse+nPoids,zOp[nPasse+nPoids]",nPasse+nPoids,nOp[nPasse+nPoids]);
				//VecteurVoir(sC2("nOp",sEnt(nPoids)),nOp,0,2*kuNbMax+1);
			}
			//VecteurVoir("nOp",nOp,0,2*kuNbMax+1);
			for (nPoids=0;nPoids<=kuNbMax;nPoids++)
				bDebordement = bDebordement || (nPasse+nPoids>kuNbMax && nOp[nPasse+nPoids]!=0);
		//tb("bDebordement1",bDebordement);
		Assert1("NbMul DEBORDEMENT",!bDebordement);
	}
	//pnbP soit la copie des kuNbLim poids faibles de nOp, avec pour signe le produit des signes des opérandes nbA et nbB
		for (nPoids=0;nPoids<=kuNbMax;nPoids++)
			pnbP->digit[nPoids]=nOp[nPoids];
		pnbP->sign=(nbA.sign==nbB.sign)? +1: -1;
	if (bNbNul(*pnbP))
		pnbP->sign=+1;
	//NbVoir("NbMul:pnbP",*pnbP);
}//NbMul

int bNbNul(nb nbA){
	int bNul,nPoids;
	for (bNul=kV,nPoids=0;nPoids<=kuNbMax && bNul;nPoids++)
		bNul=nbA.digit[nPoids]==0;
	return(bNul);
}//bNbNul

void NbOpposeR(nb *pnbA){
	//multiplie par -1
	nb nbMoins1;
	NbAffecter(-1,&nbMoins1);
	NbMul(*pnbA,nbMoins1,pnbA);
}//NbOpposeR

void NbSkewClosurE(nbMatrice *pmnbA,int uParcoursLgMax,nbMatrice **ppmnbAchapo){//O(N4)
	//rend dans ppmnbQAchapo[uH][uL] la somme des produits des poids de ts les parcours fermés de longueur uL qui commencent en uH.
	//pmnbAhach est la matrice égale à A pour i>h et j>h, et nulle sinon.
	//ynbLigne/yColonne est la h-ième ligne/colonne de la matrice A avec les h 1ères entrées nulles.
	//const int kbBooleher=kF;//vrai ssi les opérateurs booléens ET et OU remplacent les opérateurs produit et somme (resp.) 
	int uC,uD,uH,uL,uK,uN=pmnbA->nLigne;
	nb ynbAccu[1+uN],ynbColonne[1+uN],ynbLigne[1+uN],nbProduit,znbEcretage;
	//te("NbSkewClosurE0: uParcoursLgMax",uParcoursLgMax);
	nbMatrice *pmnbAhach;
	//Appel0(sC2b("NbSkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
		Assert3("NbSkewClosurE01",pmnbA->nLigne==pmnbA->nColonne,pmnbA->nLigne==(*ppmnbAchapo)->nLigne,pmnbA->nColonne>=(*ppmnbAchapo)->nColonne);
		NbMatriceAllouer1(&pmnbAhach,uN);
			//NbMatriceVoiR("MatriceZeroter ppmnbQAchapo initial",*ppmnbAchapo);
			//calculer Achapeau[h,k]=ah.(Ah**k-2).ah
				//te("1:uN",uN);
				NbAffecter(0,&znbEcretage);
				for (uH=1;uH<=uN;uH++){//O(N4)
					if (0) Titrer(sEnt(uH));
					NbMatriceZeroteR(pmnbA,uH,pmnbAhach);//all rows and columns not greater than uH zeroed
					if (0) NbMatriceVoiR(sC2("pmnbAhach",sEnt(uH)),pmnbAhach);
					//ynbLigne:=ligne pmnbA[uH] 
						for (uC=1;uC<=uN;uC++)
							if (uC<=uH)
								NbAffecter(0,&ynbLigne[uC]);
							else NbDupliquer(pmnbA->Mat[uH][uC],&ynbLigne[uC]);//hth row of A with the first h entries zeroed
					//if (0 && !bVekteurNul(ynbLigne,1,uN)) VekteurVoir(sC2("ynbLigne",sEnt(uH)),ynbLigne,1,uN);
					//yColonne:=colonne pmnbA[uH] 
						for (uL=1;uL<=uN;uL++)
							if (uL<=uH)
								NbAffecter(0,&ynbColonne[uL]);
							else NbDupliquer(pmnbA->Mat[uL][uH],&ynbColonne[uL]);//hth column of A with the first h entries zeroed
					//if (0 && !bVekteurNul(yColonne,1,uN)) VekteurVoir(sC2("yColonne @@@@@@@@@@@@@@@",sEnt(uH)),yColonne,1,uN);
					NbVecteurCopieR(ynbLigne,1,uN,ynbAccu);
					for (uK=2;uK<=uParcoursLgMax;uK++){//O(N3)
						//if (0) VekteurVoir(sC2("yAccu pour uK=",sEntier(uK,2)),ynbAccu,1,uN);
						//ppmnbQAchapo->Mat[uH][uK]:=produit scalaire iProduitLigne[]*yColonne[]
							NbAffecter(0,&(*ppmnbAchapo)->Mat[uH][uK]);
							for (  uD=1;uD<=uN;uD++){
								NbMul(ynbAccu[uD],ynbColonne[uD],&nbProduit);
								NbAdd((*ppmnbAchapo)->Mat[uH][uK],nbProduit,&(*ppmnbAchapo)->Mat[uH][uK]);
							}
						//ynbLigne:=produit du vecteur ligne ah par la puissance pmnbAhach
							NbVecteurCopieR(ynbAccu,1,uN,ynbLigne);
							NbVecteurRazeR(ynbAccu,1,uN);
							for (uC=1;uC<=uN;uC++)//O(N2)
								for (uD=1;uD<=uN;uD++){
									NbMul(ynbLigne[uD],pmnbAhach->Mat[uD][uC],&nbProduit);
									NbAdd(ynbAccu[uC],nbProduit,&ynbAccu[uC]);
								}
						//zEcretage+=nVekteurEcreter(yAccu,1,uN,kiLongintMin,kxParcoursMaximal);
					}//for uK
					for (uD=1;uD<=uN;uD++)
						(*ppmnbAchapo)->Mat[uH][1]=pmnbA->Mat[uH][uH];
				}//uH
			//Assert1("NbSkewClosurE zEcretage",zEcretage==0);
		free(pmnbAhach);
		//censurer les parcours de longueur supérieure à uParcoursLgMax
			//(*ppmnbAchapo)->nColonne=10;
		//t("[uH][uL]=somme de produits, 1 par parcours fermé de lgr uL d'extrémité uH tel qu'aucun sommet <=uH n'est traversé");
		//NbMatriceVoiR("NbSkewClosurE0 ppmnbAchapo final",*ppmnbAchapo);
	//Appel1(sC2b("SkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
}//NbSkewClosurE

void NbSub(nb nbA,nb nbB,nb *pnbS){
	const int kbVoir=kF;
	int tCompare,nPoids,bRetenue;
	long zSomme;
	nb nbC;
	//Appel0("NbSub");
		pnbS->sign=nbA.sign;//d
		if (kbVoir) NbVoir("nbSub:nbA",nbA);
		if (kbVoir) NbVoir("nbSub:nbB",nbB);
		if ( bNbNul(nbA) ){
			t("bNbNul(nbA)");
			NbDupliquer(nbB,pnbS);
			pnbS->sign=-pnbS->sign;
			if (kbVoir) NbVoir("nbSub:pnbS",*pnbS);
		}else if ( bNbNul(nbB) )
			NbDupliquer(nbA,pnbS);
		else if (nbA.sign==nbB.sign){
			NbDupliquer(nbB,&nbC);
			NbComplementeR(&nbC);
			if (kbVoir) NbVoir("nbSub:nbC",nbC);
			for (bRetenue=0,nPoids=0;nPoids<=kuNbMax;nPoids++){
				zSomme=(long) nbA.digit[nPoids]+(long) nbC.digit[nPoids]+(long) bRetenue;
				bRetenue=zSomme>kxBaseMaX;
				if (bRetenue)
					zSomme=zSomme-kxBaseLiM;
				Assert1("NbSub",bCroit(0,zSomme,kxBaseMaX) );
				pnbS->digit[nPoids]=zSomme;
			}
		if (kbVoir) NbVoir("nbSub:pnbS",*pnbS);
			if (!bRetenue){
				NbComplementeR(pnbS);
			}
			tCompare=tNbCompareR(nbA,nbB);
			if (tCompare>0)
				pnbS->sign=+nbA.sign;
			if (tCompare<0)
				pnbS->sign=-nbA.sign;
			if (tCompare==0)
				pnbS->sign=+1;
			//Assert1("NbSub",bRetenue==0);
		} else {
			if (kbVoir) t("OPPOSER");
			NbDupliquer(nbB,&nbC);
			nbC.sign=-nbC.sign;
			if (kbVoir) NbVoir("nbC",nbC);
			NbAdd(nbA,nbC,pnbS);
		}
		if ( bNbNul(*pnbS) )
			pnbS->sign=+1;
		if (kbVoir) NbVoir("nbA - nbB",*pnbS);
	//Appel1("NbSub");
}//NbSub

void NbTesteR(int iA,char cOperateur,int iB){
	nb nbA,nbB,nbC;
	int iC;
	NbAffecter(iA,&nbA);
	NbVoir(" nbA",nbA);
	NbAffecter(iB,&nbB);
	switch(cOperateur){
		case '+':	NbAdd(nbA,nbB,&nbC);NbVoir("+nbB",nbB);NbVoir("=nbC",nbC);iC=yNb(nbC);
					Assert1(sC6("NbTesteR:",sEnt(iA),"+",sEnt(iB),"=",sEnt(iC)),iA+iB==iC);
					break;
		case '-':	NbSub(nbA,nbB,&nbC);NbVoir("-nbB",nbB);NbVoir("=nbC",nbC);iC=yNb(nbC);
					Assert1(sC6("NbTesteR:",sEnt(iA),"-",sEnt(iB),"=",sEnt(iC)),iA-iB==iC);
					break;
		case '*':	NbMul(nbA,nbB,&nbC);NbVoir("*nbB",nbB);NbVoir("=nbC",nbC);iC=yNb(nbC);
					Assert1(sC6("NbTesteR:",sEnt(iA),"*",sEnt(iB),"=",sEnt(iC)),iA*iB==iC);
					break;
		default:	Assert1("NbTesteR default",0);
	}
	Ligne();
}//NbTesteR

void NbTESTER(int iTest){
	//teste le présent module.
	nb nbA,nbB,nbC;
	int uP,uG,uD;
	iTest=50;
	Appel0(sC2("NbTESTER,test n°",sEnt(iTest)));
		if (iTest!=50)
			Assert1("NbTESTER",kxBaseMaX==9);
		switch (iTest) {
			case  0:	Titrer("ÉGALITÉ");
						for (uG=-20;uG<=20;uG++)
							for (uD=-20;uD<=20;uD++){
								NbAffecter(uG,&nbA);NbVoir("nbA",nbA);
								NbAffecter(uD,&nbB);NbVoir("nbB",nbB);
								Assert1("NbTESTER case 0",(uG==uD)==(yNb(nbA)==yNb(nbB)));
							}
						break;
			case  5:	Titrer("Affectation");
						for (uP=-20;uP<=20;uP++){
							NbAffecter(uP,&nbC);NbVoir("nbC",nbC);
							Assert1("NbTESTER case 5",uP==yNb(nbC));
						}
						break;
			case  8:	Titrer("Incrémentation et décrémentation");
						NbAffecter(0,&nbB);NbVoir("nbB",nbB);
						for (uP=1;uP<=20;uP++){
							NbIncrementeR(&nbB);NbVoir("nbB",nbB);
							Assert1("NbTESTER case 8",uP==yNb(nbB));
						}
						for (uP=1;uP<=40;uP++){
							NbDecrementeR(&nbB);NbVoir("nbB",nbB);
							Assert1("NbTESTER case 8",20-uP==yNb(nbB));
						}
						for (uP=1;uP<=40;uP++){
							NbIncrementeR(&nbB);NbVoir("nbB",nbB);
							Assert1("NbTESTER case 8",20-40+uP==yNb(nbB));
						}
						break;
			case 10:	Titrer("Complémentation");
						for (uG=-10;uG<=+10;uG++){
							NbAffecter(uG,&nbA);d(uG);NbVoir("nbA",nbA);
							NbComplementeR(&nbA);NbVoir("nbA cplémnté",nbA);
							d2(uG,yNb(nbA));
							Assert1("NbTESTER case 10",(uG+yNb(nbA))%10==0);
						}
						break;
			case 20:	Titrer("Additions");
						for (uG=-20;uG<=20;uG++)
							for (uD=-20;uD<=20;uD++)
								NbTesteR(uG,'+',uD);
						break;
			case 30:	Titrer("Soustractions");
						for (uG=-20;uG<=20;uG++)
							for (uD=-20;uD<=20;uD++)
								NbTesteR(uG,'-',uD);
						break;
			case 40:	Titrer("Produits");
						for (uG=-20;uG<=20;uG++)
							for (uD=-20;uD<=20;uD++)
								NbTesteR(uG,'*',uD);
						for (uG=-20;uG<=20;uG++){
							NbAffecter(uG,&nbA);NbVoir("nbA",nbA);
							NbMul(nbA,nbA,&nbA);NbVoir("nbA**2",nbA);
							Assert1("NbTESTER case 40",uG*uG==yNb(nbA));
						}
						break;
			case 50:	//test des grands nombres avec kxBaseMaX=kE9-1 et kuNbMax=7
						Assert2("NbTESTER case 50",kxBaseMaX==kE9-1,kuNbMax==7);
						NbTesterFiB(uP=300);//uP=300
						break;
			default:	Assert1("NbTESTER",0);
		}
	Appel1(sC2("NbTESTER,test n°",sEnt(iTest)));
}//NbTESTER	

void NbTesterFiB(int nFibMax){
	const int bVoir=kF;
	int bEgal,uF,uM,uN;
	long zF;
	nb nbF,nbFmoins1,nbFmoins2,nbFmMoins1Fn,nbFmFnPlus1,nbFmFnPlusn,nbFn,nbFm,nbFnPlus1,nbSomme;
	if (1){
		Titrer("additions"),
		NbAffecter(1,&nbFmoins1);
		NbAffecter(1,&nbF);
		NbVoir("F(  1)",nbFmoins1);
		NbVoir("F(  2)",nbF);
		for (uF=3;uF<=nFibMax;uF++){
			NbDupliquer(nbFmoins1,&nbFmoins2);
			NbDupliquer(nbF,&nbFmoins1);
			NbAdd(nbFmoins2,nbFmoins1,&nbF);
			NbVoir(sC2("F",sP(sEntier(uF,3))),nbF);
			if (uF<=92)//F(92)= 7 540 113 804 746 346 429 ≤ 9 223 372 036 854 775 807 alias kxLongintMax
				Assert1("NbTesterFiB1",yNb(nbF)==yNb(nbFmoins1)+yNb(nbFmoins2));
		}
	}
	if (1)
		for (Titrer("soustractions"),uF=nFibMax;uF>=-20;uF--){
			NbSub(nbF,nbFmoins1,&nbFmoins2);
			NbVoir(sC2("F",sP(sEntier(uF,3))),nbF);
			if (uF<=92)//F(92)= 7 540 113 804 746 346 429 ≤ 9 223 372 036 854 775 807 alias kxLongintMax
				Assert1("NbTesterFiB2",yNb(nbF)==yNb(nbFmoins1)+yNb(nbFmoins2));
			NbDupliquer(nbFmoins1,&nbF);
			NbDupliquer(nbFmoins2,&nbFmoins1);
		}
	if (1) //70 est la limite max de l'opérande de zFib
		for (Titrer("zFib vs nbFib"),uF=1;uF<=70;uF++){
			NbFib(uF,&nbF);
			zF=zFib(uF);
			te("zF",zF);
			NbVoir(sC2("F",sP(sEntier(uF,3))),nbF);
			if (uF<=92)//F(92)= 7 540 113 804 746 346 429 ≤ 9 223 372 036 854 775 807 alias kxLongintMax
				Assert1("NbTesterFiB3",yNb(nbF)==zF);
		}
	//multiplications et comparaisons via F(m+n)=Fm-1Fn+FmFn+1
	if (1)
		for (Titrer("multiplications et comparaisons"),uM=1;uM<=100;uM++)
			for (uN=1;uN<=100;uN++){
				NbFib(uM-1,&nbFmoins1);
				if (bVoir) NbVoir(sC3("F(",sEnt(uM-1),")"),nbFmoins1);
				NbFib(uN,&nbFn);
				NbMul(nbFmoins1,nbFn,&nbFmMoins1Fn);
				if (bVoir) NbVoir(sC5("GAUCHE: F(",sEnt(uM-1),")*F(",sEnt(uN),")"),nbFmMoins1Fn);
				NbFib(uM,&nbFm);
				NbFib(uN+1,&nbFnPlus1);
				NbMul(nbFm,nbFnPlus1,&nbFmFnPlus1);
				if (bVoir) NbVoir(sC5("DROITE: F(",sEnt(uM),")*F(",sEnt(uN+1),")"),nbFmFnPlus1);
				NbAdd(nbFmMoins1Fn,nbFmFnPlus1,&nbSomme);
				if (bVoir) NbVoir("nbSomme:     ",nbSomme);
				NbFib(uM+uN,&nbFmFnPlusn);
				if (bVoir) NbVoir("nbFmFnPlusn: ",nbFmFnPlusn);
				bEgal=bNbEgal(nbSomme,nbFmFnPlusn);
				printf("%s est %s.\n",sC9("F(",sEnt(uM-1),")*F(",sEnt(uN),") = F(",sEnt(uM),")*F(",sEnt(uN+1),")"),sBool(bEgal));
				Assert1("NbTesterFiB",bEgal);
				if (uM+uN<=70)//70 est la limite max de l'opérande de zFib
					Assert1("NbTesterFiB4",yNb(nbFmFnPlusn)==zFib(uM-1)*zFib(uN)+zFib(uM)*zFib(uN+1));
			}
		}//NbTesterFiB

void NbVecteurCopieR(nb ynbVecteurA[],int nIndexMin,int nIndexMax,nb ynbVecteurB[]){
	//yVecteurB[nIndexMin..nIndexMax] := yVecteurA[nIndexMin..nIndexMax] 
	int nK;
	Assert1("NbVecteurCopieR",bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		ynbVecteurB[nK]=ynbVecteurA[nK];
}//NbVecteurCopieR

void NbVecteurRazeR(nb ynbVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert1("NbVecteurRazeR",bCroit(0,nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			NbAffecter(0,&ynbVecteur[nE]);
}//NbVecteurRazeR

void NbVoir(char *sMessage,nb nbA){
	int uDigitMax=1;
	if (kxBaseMaX>9)
		uDigitMax=kuNbMax*(nLog10(kxBaseMaX)+3);
	if (kxBaseMaX>9)
		uDigitMax=24;
	printf("     %s:",sMessage);
		/*printf("%c",(nbA.sign>=0)? '+' :'-');
		for (nPoids=kuNbMax;nPoids>=0;nPoids--)
			printf(" %s",sEntier(nbA.digit[nPoids],uDigitMax));*/
		printf(" %s",sNb0(nbA,1+uDigitMax) );
	printf(".\n");
}//NbVoir	

