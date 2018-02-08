#include "Outil.h"
#include "Quad.h"
#include "Graphe.h"
#include "Flot.h"
#include "Matrice.h"
//#include "Nb.h"
int bQuadAmorceR;//ie le module a effectivement été amorcé
#define kuQuarteronMaX 8
quad qQuarteroN[1+kuQuarteronMaX];

quad qQuadQuarteroN(int nCouleur);
void QuadQuarteronner();
void QuadripoleR(int uPivot,graf *pgG,int bBipartitionner,graf **ppgH);
void LongrineR(int iLongrine,int sA,int sB,int sC,int sD,graf *pgG);
void PermanentExpliciteR(iMatrice *pmA,int uColonne,int *pnPiste);
void VeqteurCopieR(quad qVecteurA[],int nIndexMin,int nIndexMax,quad qVecteurB[]);
int bVeqteurNuL(quad qVecteur[],int nIndexMin,int nIndexMax);
void VeqteurVoiR(char *sNom,quad qQuelVecteur[],int nIndexMin,int nIndexMax);
void VeqteurRazeR(quad qVecteur[],int nIndexMin,int nIndexMax);

quad qVV[1+1][1+52][1+52][1+52];

//	GrapheSymetriser(pgG); se débrouiller sans symétrisation afin de ne pas toucher au graphe fourni en DONNée
//a2=0 avec 1 a par croix

void tqqq(char *sMessage,quad qA,quad qB,quad qC){
	if (0)
		printf("%s: %s et %s donne %s .\n",sMessage,sQuad(qA),sQuad(qB),sQuad(qC));
}//tqqq

int bDeterminantCaracteriseR(graf *pgG,int bMatriceAfficher){
	const int bVoir=kF;
	int uC,uL,bDeterminantNul,nPiste,bCaracteriser;
	iMatrice *pmA;
	qMatrice *pmqA;
	GrapheVoir(pgG,"bDeterminantCaracteriseR");
	MatriceAllouer1(&pmA,pgG->nSommetEnTout);
		MatriceDepuisGraphe(pgG,!k1Incidence,&pmA);
		if (1 || bMatriceAfficher) MatriceVoir("bDeterminantCaracteriseR:pmA",pmA);
		iBof=yMatriceDeterminant(pmA);
		for (uC=1;uC<=pmA->nLigne;uC++)
			pmA->Mat[0][uC]=0;
		//tee("pmA->nLigne,pmA->nColonne",pmA->nLigne,pmA->nColonne);
		nPiste=0;
		PermanentExpliciteR(pmA,1,&nPiste);
		if (bVoir) printf("Déterminant standard de la matrice d'incidence: %s.\n",sPar3(iBof));
			pmqA=malloc(sizeof(qMatrice));
			pmqA->nLigne=pmqA->nColonne=pmA->nLigne;
			//QuadQuarteronner(&qA,&qB,&qC,&qD);
			for (uL=1;uL<=pmA->nLigne;uL++)
				for (uC=1;uC<=pmA->nLigne;uC++)
					//pmqA->Mat[uL][uC]=qQuadQuarteroN(pmA->Mat[uL][uC]);
					pmqA->Mat[uL][uC]=qQuad(pmA->Mat[uL][uC]);
			if (bVoir) QuadMatriceVoir("pmqA",pmqA);
		Assert1("bDeterminantCaracteriseR",!bQuadMatriceVide(pmqA));
		bDeterminantNul=bQuadDeterminer(pmqA);
	free(pmA);
	bCaracteriser=!bDeterminantNul;
	return(bCaracteriser);
}//bDeterminantCaracteriseR

quad qKnapsacQ(qMatrice *pmqA){//O(N3)
	//rend la valeur du knapsack (les valeurs successives sont calculées dans la matrice pKnapsack;résultat au bout de la diag principale).
	const int bVoir=kV; 
	int uLg,uHead,uP;
	quad qKnapsack,qSommeProduit,qTerme;
	qMatrice *pmqKnapsack;
	if (0) QuadMatriceVoir("Matrice complémentée (head de clow x longueur de clow) des sommes de produits reçue par qKnapsacQ",pmqA);
	QuadMatriceAllouer2(&pmqKnapsack,pmqA->nLigne,pmqA->nColonne);
		pmqKnapsack->nSecante=pmqA->nSecante;
		for (uLg=1;uLg<=pmqA->nColonne;uLg++)
			pmqKnapsack->Mat[1][uLg]=pmqA->Mat[1][uLg];
		for (uHead=2;uHead<=pmqA->nLigne;uHead++)//O(N2) //******* BUG ALGORITHMICA (2010) 56:35-50 p41:"for i,j from 1 to n we compute" vs from 2.
			for (uLg=1;uLg<=pmqA->nColonne;uLg++){//O(N2)
				//Table[i,j]=∑ sur 0<p<j de (Table[i-1,p]xA[i,j-p])+Table[i-1,j]
				for (qSommeProduit=qQuad(0),uP=1;uP<uLg;uP++){//O(N)
					qTerme=pmqA->Mat[uHead][uLg-uP];
					qSommeProduit=qQuadAdd(qSommeProduit,qQuadMul(pmqKnapsack->Mat[uHead-1][uP],qTerme));
				}
				qTerme=pmqKnapsack->Mat[uHead-1][uLg];
				pmqKnapsack->Mat[uHead][uLg]=qQuadAdd(qSommeProduit,qTerme);
			}
		//N'afficher que les colonnes paires car les colonnes impaires sont vides.
			//pmqKnapsack->nSecante=-2; 
		if (bVoir) QuadMatriceVoir("Matrice pKnapsack (head x longueur totale) des sommes de produits de SÉQUENCES de clows",pmqKnapsack);
		qKnapsack=pmqKnapsack->Mat[pmqA->nLigne][pmqA->nColonne];
	free(pmqKnapsack);
	return(qKnapsack);
}//qKnapsacQ

void SkewQlosurE(qMatrice *pmqA,int uParcoursLgMax,qMatrice **ppmqAchapo){//O(N4)
	//rend dans ppmqAchapo[uH][uL] la somme des produits des poids de ts les parcours fermés de longueur uL qui commencent en uH.
	//pmqAhach est la matrice égale à A pour i>h et j>h, et nulle sinon.
	//iLigne/iColonne est la h-ième ligne/colonne de la matrice A avec les h 1ères entrées nulles.
	//const int kbBooleher=kF;//vrai ssi les opérateurs booléens ET et OU remplacent les opérateurs produit et somme (resp.) 
	int uC,uD,uH,uL,uK,nEcretage,uN=pmqA->nLigne;
	quad qAccu[1+uN],qColonne[1+uN],qLigne[1+uN],qProduit;
	te("SkewQlosurE0: uParcoursLgMax",uParcoursLgMax);
	qMatrice *pmqAhach;
	//Appel0(sC2b("SkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
		Assert3("SkewQlosurE01",pmqA->nLigne==pmqA->nColonne,pmqA->nLigne==(*ppmqAchapo)->nLigne,pmqA->nColonne>=(*ppmqAchapo)->nColonne);
		QuadMatriceAllouer1(&pmqAhach,uN);
			if (0) QuadMatriceVoir("SkewQlosurE ppmqAchapo initial",*ppmqAchapo);
			//calculer Achapeau[h,k]=ah.(Ah**k-2).ah
				for (nEcretage=0,uH=1;uH<=uN;uH++){//O(N4)
					if (0) Titrer(sEnt(uH));
					QuadMatriceZeroter(pmqA,uH,pmqAhach);//all rows and columns not greater than uH zeroed
					if (0) QuadMatriceVoir(sC2("pmqAhach pour sommet",sEnt(uH)),pmqAhach);
					//qLigne:=ligne pmqA[uH] 
						for (uC=1;uC<=uN;uC++)
							qLigne[uC]=(uC<=uH)? qQuad(0): pmqA->Mat[uH][uC];//hth row of A with the first h entries zeroed
					if (0 && !bVeqteurNuL(qLigne,1,uN)) VeqteurVoiR(sC2("qLigne   pour sommet",sEnt(uH)),qLigne,1,uN);
					//qColonne:=colonne pmqA[uH] 
						for (uL=1;uL<=uN;uL++)
							qColonne[uL]=(uL<=uH)? qQuad(0): pmqA->Mat[uL][uH];//hth column of A with the first h entries zeroed
					if (0 && !bVeqteurNuL(qColonne,1,uN)) VeqteurVoiR(sC2("qColonne pour sommet",sEnt(uH)),qColonne,1,uN);
					VeqteurCopieR(qLigne,1,uN,qAccu);
					for (uK=2;uK<=uParcoursLgMax;uK++){//O(N3)
						if (0) VeqteurVoiR(sC2("qAccu pour uK=",sEntier(uK,2)),qAccu,1,uN);
						//ppmqAchapo->Mat[uH][uK]:=produit scalaire iProduitLigne[]*iColonne[]
							for ( (*ppmqAchapo)->Mat[uH][uK]=qQuad(0), uD=1;uD<=uN;uD++){
								qProduit=qQuadMul(qAccu[uD],qColonne[uD]);
								//QuadVoir(sC2("qProduit pour uD=",sEntier(uD,2)),qProduit);
								(*ppmqAchapo)->Mat[uH][uK]=qQuadAdd((*ppmqAchapo)->Mat[uH][uK],qProduit);
							}
						//qLigne:=produit du vecteur ligne ah par la puissance pmqAhach
							VeqteurCopieR(qAccu,1,uN,qLigne);
							VeqteurRazeR(qAccu,1,uN);
							for (uC=1;uC<=uN;uC++)//O(N2)
								for (uD=1;uD<=uN;uD++)
									qAccu[uC]=qQuadAdd(qAccu[uC],qQuadMul(qLigne[uD],pmqAhach->Mat[uD][uC]));
					}//for uK
					for (uD=1;uD<=uN;uD++)
						(*ppmqAchapo)->Mat[uH][1]=pmqA->Mat[uH][uH];
				}//uH
			Assert1("SkewClosurE0 nEcretage",nEcretage==0);
		free(pmqAhach);
		//censurer les parcours de longueur supérieure à uParcoursLgMax
			//(*ppmqAchapo)->nColonne=10;
		//t("[uH][uL]=somme de produits, 1 par parcours fermé de lgr uL d'extrémité uH tel qu'aucun sommet <=uH n'est traversé");
		if (0) QuadMatriceVoir("SkewQlosurE1 ppmqAchapo final",*ppmqAchapo);
	//Appel1(sC2b("SkewClosurE0",sP(sC2b("parcours",sEnt(uParcoursLgMax)))));
}//SkewQlosurE

int iDeterminantQalculeR(iMatrice *pmE,int nDim){//O(S4) ici; Faisable: O(S3.5) exact car sans division et O(S3) avec multiplicO matrice optimale
	//rend le déterminant calculé par la méthode de Urbanska est nul
	int bVoir=kF;
	int uC,uL,iQalculer;
	int bColonnesImpairesVides=(nDim>0);
	quad qKalculer;
	qMatrice *pmqA,*pmqAchappo;
	QuadVoir("qQuad(2)",qQuad(2));
	QuadVoir("qQuad(3)",qQuad(3));
	int uParcoursLgMax=(nDim>100)? nDim*6: pmE->nLigne;
	Appel0(sC2b("iDeterminantQalculeR",sP(sC2b("dimension",sEnt(nDim)))));
		QuadMatriceAllouer1(&pmqA,pmE->nLigne);
			//convertir pmE en pmqA
				for (uL=1;uL<=pmE->nLigne;uL++)
					for (uC=1;uC<=pmE->nColonne;uC++)
						pmqA->Mat[uL][uC]=qQuad(pmE->Mat[uL][uC]);//seul point de traduction hors qQuad(0)
				//if (bColonnesImpairesVides) pmA->nSecante=-2;
			if (bVoir) QuadMatriceVoir("Calcul du déterminant Urbanska sur la matrice ci-dessous",pmqA);
			Assert2("iDeterminantQalculeR2",pmqA->nLigne==pmqA->nColonne,bCroit(1,pmqA->nLigne,kE2));
			QuadMatriceAllouer2(&pmqAchappo,pmqA->nLigne,uParcoursLgMax);
			//Assert1("iDeterminantQalculeR",uParcoursLgMax==pmA->nLigne);
			if (nDim>0) pmqAchappo->nSecante=-2;
			SkewQlosurE(pmqA,pmqA->nLigne,&pmqAchappo);//O(N4)
			if (bColonnesImpairesVides) pmqAchappo->nSecante=-2;
			//rendre (-1)**N * KnapsacK(- pmoAchappo)
				if (nDim>0){//ds pmqAchappo, annuler les colonnes de lgr hors 2 et nDim*6
					for (uL=1;uL<=pmqAchappo->nLigne;uL++)
						for (uC=1;uC<=pmqAchappo->nColonne;uC++)
							if (uC!=2)
								pmqAchappo->Mat[uL][uC]=qQuad(0);
					//pmoAchappo->Mat[1][nDim*6]=1;
				}
				//if (nDim==0)
					for (uL=1;uL<=pmqAchappo->nLigne;uL++)
						for (uC=1;uC<=pmqAchappo->nColonne;uC++)
							pmqAchappo->Mat[uL][uC]=qQuadNeg(pmqAchappo->Mat[uL][uC]);
				/*if (0 && kbUnier)
					for (uL=1;uL<=pmoAchappo->nLigne;uL++)
						for (uC=1;uC<=pmoAchappo->nColonne;uC++)
							pmoAchappo->Mat[uL][uC]=(pmoAchappo->Mat[uL][uC]!=0);*/
			QuadMatriceVoir("Achappo[H,L]=SOMME des POIDS de TOUS les CLOWS de HEAD H et de LONGUEUR L",pmqAchappo);
				qKalculer=qKnapsacQ(pmqAchappo);//O(N3)
				if (bImpair(pmqA->nLigne))
					qKalculer=qQuadNeg(qKalculer);
			//iBof=iKnaP(pmAchappo);
		free(pmqA);
		printf("Déterminant Urbanska: (%s,%s,%s,%s) .\n",sNb(qKalculer.q11),sNb(qKalculer.q12),sNb(qKalculer.q21),sNb(qKalculer.q22) );
		iQalculer=0;
	Appel1(sC2b("iDeterminantQalculeR",sP(sC2b("dimension",sEnt(nDim)))));
	return(iQalculer);
}//iDeterminantQalculeR

void LongrineR(int iLongrine,int sA,int sB,int sC,int sD,graf *pgG){
	//remplit le quadripole (sA,sB,sC,sD) avec la longrine de numéro abs(iLongrine),(en, interne,iChemin pour afficher les parcours)
	const int kuCoinNb=4;
	int uLongrineSommat;//4, 6, 8 ou 12
	const int kbVoir=kF;
	graf *pgH;
	int uC,nCouleur,nSommat;
	quad qProduit;
	int aK,sU,sV,sX,sY;
	int sCoin[1+4]={-1,sA,sB,sC,sD};
	char *sLongrine;
	int iChemin=0;
	char *sChemin41="ACBD";//suppose uLongrineSommat=4; rend (18,-9,-18,9)
	char *sChemin42="BDAC";//suppose uLongrineSommat=4; rend (30,-10,-30,10)
	char *sChemin61="AECBFD";//suppose uLongrineSommat=6; rend (18,-9,-18,9)
	char *sChemin62="BFDAEC";//suppose uLongrineSommat=6; rend (30,-10,-30,10)      
	char *sChemin81="AEBFHDGC";//suppose uLongrineSommat=8; rend (810,-270,-810,270) et,si papillons inversés,  (486,-243,-486,243)
	char *sChemin82="BFAEGCHD";//suppose uLongrineSommat=8; rend (720,-360,-720,360) et,si papillons inversés, (1200,-400,-1200,400)
	char *sChemin;
	Assert5("LongrineR0",bGrapheSommet(pgG,sA),bGrapheSommet(pgG,sB),bGrapheSommet(pgG,sC),bGrapheSommet(pgG,sD),bDistinct4(sA,sB,sC,sD) );
	//te("iLongrine",iLongrine);
	//sLongrine:=la longrine choisie; ci-dessous,les couleurs de 5 À 8 affecteront qA à qD, non nuls, qui vérifient (qA*qC)*qB=(qB*qD)*qA=0.
		//1 ou 2 papillons sans sommets intermédiaires
			char ksLongrine4[]="AC8BD7CB5DA6";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			char ksLongrhin8[]="AE1BF1CH0DG0EB0EG0FA0FH0GC1HD1";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			char ksLongrine8[]="AE8BF7CH5DG6EB5EG1FA6FH1GC8HD7";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			char kcLongryne8[]="AE1BF1CH3DG3EB2EG1FA2FH1GC1HD1";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			//char ksLongrine8[]="AE8BF7CH6DG5EB5EG1FA6FH1GC7HD8";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
		//1 ou 2 papillons avec sommets intermédiaires
			char ksLongrine6[]="AE1BF1CB5DA6EC8FD7";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			char ksLongrine12[]="AE8BG1CK5DI6EF1FB5FI1GH7HA6HK1KL1LD7IJ8JC1";//NB les coins du quadripôle doivent être les sommets A,B,C et D.
			char ksLongrine16[]="AE0BH0CN0DK0EF1FG0GB0GK0HI1IJ0JA0JN0KL0LM1MC0NO0OP1PD0";
		switch (abs(iLongrine)) {
			case  41: sLongrine=ksLongrine4;break;
			case  42: sLongrine=ksLongrine4;break;
			case  61: sLongrine=ksLongrine6;break;
			//case  8: sLongrine=ksLongrine8;break;
			case  80: sLongrine=ksLongrhin8;break;
			case  81: sLongrine=ksLongrine8;break;
			case  82: sLongrine=kcLongryne8;break;
			case  12: sLongrine=ksLongrine12;break;
			case  16: sLongrine=ksLongrine16;break;
			default: Assert1("LongrineRdefault",0);
		}
	GrapheGenerer(sLongrine,&pgH);
		uLongrineSommat=pgH->nSommetEnTout;
		//te("uLongrineSommat",uLongrineSommat);
		if (kbVoir) GrapheVoir(pgH,"pgH");
		nSommat=pgG->nSommetEnTout;//avant li+2
		Assert1("LongrineR3",uLongrineSommat>=0);
		GrapheSommer(pgG,+uLongrineSommat-kuCoinNb);//indolore si nul
		if (kbVoir) te("pgG->nSommetEnTout après empilt",pgG->nSommetEnTout);
		if (kbVoir) GrapheVoir(pgG,"pgG");
		for (sU=1;sU<=pgH->nSommetEnTout;sU++)
			for (aK=pgH->aHed[sU];aK<pgH->aHed[sU+1];aK++){
				sV=pgH->sSuk[aK];
				nCouleur=pgH->coulh[aK];
				if (abs(iLongrine)==82 && bDans2(nCouleur,2,3))
					nCouleur=-nCouleur;
				sX=(sU<=kuCoinNb)? sCoin[sU]: nSommat-kuCoinNb+sU;
				sY=(sV<=kuCoinNb)? sCoin[sV]: nSommat-kuCoinNb+sV;
				//teeee("sU,sV,sX,sY",sU,sV,sX,sY);
				Assert3("LongrineR6",bGrapheSommet(pgG,sX),bGrapheSommet(pgG,sY),sX!=sY);
				//teee("sX,sY,nCouleur",sX,sY,nCouleur);
				GrapheArquer1(pgG,sX,sY,nCouleur);
			}
		if (0){//refermer la longrine sur elle-même
			GrapheArquer1(pgG,sCoin[3],sCoin[1],1);
			GrapheArquer1(pgG,sCoin[4],sCoin[2],1);
		}
		if (0) GrapheVoir1(pgG,k1Couleur,"pgG longriné");
		if (iChemin!=0){//calculer la valeur du sChemin de rang iChemin
			//te("nChaineLg(sChemin)",nChaineLg(sChemin4));
			switch (iChemin) {
				case 41: Assert1("LongrineR01",uLongrineSommat==4);sChemin=sChemin41;break;
				case 42: Assert1("LongrineR01",uLongrineSommat==4);sChemin=sChemin42;break;
				case 61: Assert1("LongrineR02",uLongrineSommat==6);sChemin=sChemin61;break;
				case 62: Assert1("LongrineR03",uLongrineSommat==6);sChemin=sChemin62;break;
				case 81: Assert1("LongrineR02",uLongrineSommat==8);sChemin=sChemin81;break;
				case 82: Assert1("LongrineR03",uLongrineSommat==8);sChemin=sChemin82;break;
				default: Assert1("LongrineRdefoolt",0);
			}
			for (qProduit=qQuad(1),uC=1;uC<nChaineLg(sChemin);uC++){
				sU=sChemin[uC-1]-'@';
				sV=sChemin[uC]-'@';
				sX=(sU<=kuCoinNb)? sCoin[sU]: nSommat-kuCoinNb+sU;
				sY=(sV<=kuCoinNb)? sCoin[sV]: nSommat-kuCoinNb+sV;
				teeee("sU,sV,sX,sY",sU,sV,sX,sY);
				aK=nGrapheArc(pgG,sX,sY);
				nCouleur=pgH->coulh[aK];
				te("nCouleur",nCouleur);
				//qProduit=qQuadMul(qProduit,qQuadQuarteroN(nCouleur));
				qProduit=qQuadMul(qProduit,qQuad(nCouleur));
				QuadVoir("qProduit",qProduit);
			}
			printf("Valeur du chemin %s: %s.\n",sG(sChemin),sQuad(qProduit));
		}
	free(pgH);
}//LongrineR

void PermanentAfficheR(iMatrice *pmA,int nPiste){
	int uC,nDim,sX,sY,mPlace,bFin,nCycle,nCouleur;
	quad qAccu,qCarreh;
	nDim=pmA->nColonne;
	int nListe[1+nDim];
	for (uC=1;uC<=nDim;uC++)
		nListe[uC]=pmA->Mat[0][uC];
	//VecteurVoir1("nListe",nListe,1,nDim);
	printf("Piste %d: ",nPiste);
		for (nCycle=0,sY=1;sY<=nDim;sY++){
			//te("sY",sY);
			if ( bVecteurContient1(sY,nDim,nListe) ){
				if (nCycle>0)
					printf("         ");
				nCycle++;
				//printf("(");
					for (qAccu=qQuad(1),sX=sY,uC=1;uC<=nDim;uC++){
						mPlace=mVecteurContient(sX,nListe,1,nDim);
						bFin=mPlace<0;
						//QuadVoir("qAccu0",qAccu);
						if (!bFin){
							//printf("%s ",sCouple(nListe[mPlace],mPlace));
							if (sX!=sY){
								nCouleur=pmA->Mat[nListe[mPlace]][mPlace];
								//teee("sX,sY,nCouleur",nListe[mPlace],mPlace,nCouleur);
								qAccu=qQuadMul(qAccu,qQuad(nCouleur));
							}
							sX=mPlace;
							nListe[mPlace]=0;
						}
					}
					QuadVoir("qAccu1",qAccu);
				//printf(").");
				
			}
		}
	//if (nCycle==1) printf(" ***** .");
	//printf("%s.\n",sPluriel(nCycle,"cycle"));
	//printf("\n");
	if (0){
		qCarreh=qQuadMul(qAccu,qAccu);
		QuadVoir("qAccu carré",qCarreh);
		qCarreh=qQuadMul(qCarreh,qCarreh);
		QuadVoir("qAccu carré du carré",qCarreh);
	}
}//PermanentAfficheR

void PermanentExpliciteR(iMatrice *pmA,int uColonne,int *pnPiste){
	int uC,uL,bVierge;
	//Appel0("PermanentExpliciteR");
		for (uL=1;uL<=pmA->nLigne;uL++)
			if (pmA->Mat[uL][uColonne]!=0){
				for (bVierge=kV,uC=1;uC<uColonne;uC++)
					bVierge=bVierge && pmA->Mat[0][uC]!=uL;
				if (bVierge){
					pmA->Mat[0][uColonne]=uL;
					if (uColonne==pmA->nColonne){
						(*pnPiste)++;
						PermanentAfficheR(pmA,*pnPiste);
					}else PermanentExpliciteR(pmA,uColonne+1,pnPiste);
				}
			}
	//Appel1("PermanentExpliciteR");
}//PermanentExpliciteR

quad qQuad(long yEntier){
	//si yEntier hors -1..1,rend la matrice (+e -ee et +1 -e) où "e" est yEntier; sinon,rend la matrice nulle ou ±identité.
	int nMode=0;
	quad qQuad;
	quad qQuadBis;
	//te("qQuad yEntier",yEntier);
	if (abs(yEntier)>1){
		if (nMode==1){//matrice de carré nul
					NbAffecter(+yEntier,&qQuad.q11);			NbAffecter(-1,&qQuad.q12);
					NbAffecter(+yEntier*yEntier,&qQuad.q21);	NbAffecter(-yEntier,&qQuad.q22);
		}else if (nMode==2){//matrice de carré nul
					NbAffecter(+yEntier,&qQuad.q11);			NbAffecter(-yEntier*yEntier,&qQuad.q12);
					NbAffecter(+1,&qQuad.q21);					NbAffecter(-yEntier,&qQuad.q22);
		}else if (nMode==3){//matrice de carré nul
					//te("yEntier",yEntier);
					if (yEntier==-2){
						NbAffecter(+1,&qQuad.q11);				NbAffecter(+1,&qQuad.q12);
						NbAffecter(-1,&qQuad.q21);				NbAffecter(-1,&qQuad.q22);
					}else if (yEntier==-3){
						NbAffecter(-2,&qQuad.q11);				NbAffecter(-4,&qQuad.q12);
						NbAffecter(+1,&qQuad.q21);				NbAffecter(+2,&qQuad.q22);
					}else{//multiple de l'identité
						NbAffecter(+yEntier,&qQuad.q11);		NbAffecter(0,&qQuad.q12);
						NbAffecter(0,&qQuad.q21);				NbAffecter(+yEntier,&qQuad.q22);
					}
		}else {//produit de matrices appariées nul
			if (yEntier>0){
					NbAffecter(+yEntier,&qQuad.q11);		NbAffecter(+yEntier*yEntier,&qQuad.q12);
					NbAffecter(+1,&qQuad.q21);				NbAffecter(+yEntier,&qQuad.q22);
			}else{
					NbAffecter(-yEntier,&qQuad.q11);		NbAffecter(-yEntier,&qQuad.q12);
					NbAffecter(-1,&qQuad.q21);				NbAffecter(-1,&qQuad.q22);
			}
		}
		if (nMode>0){//vérifier que le carré est nul
			qQuadBis=qQuadMul(qQuad,qQuad);
			if (yEntier<0)
				Assert1("qQuad99",bQuadNul(qQuadBis));
		}
	} else{
			NbAffecter(+yEntier,&qQuad.q11);		NbAffecter(0,&qQuad.q12);
			NbAffecter(0,&qQuad.q21);				NbAffecter(+yEntier,&qQuad.q22);
	}
	return(qQuad);
}//qQuad

char *sQuad(quad qQuoi){
	char *sQuad=sP(sC4v(sNb(qQuoi.q11),sNb(qQuoi.q12),sNb(qQuoi.q21),sNb(qQuoi.q22)));
	return(sQuad);
}//sQuad

char *sQuad0(quad qQuoi){
	const int kuLg=16;
	char *sQuad=sP(sC4v(sNb0(qQuoi.q11,kuLg),sNb0(qQuoi.q12,kuLg),sNb0(qQuoi.q21,kuLg),sNb0(qQuoi.q22,kuLg)));
	return(sQuad);
}//sQuad0

void Quad2Long(quad qA,long *py11,long *py12,long *py21,long *py22){
	*py11=yNb(qA.q11);*py12=yNb(qA.q12);*py21=yNb(qA.q21);*py22=yNb(qA.q22);
}//Quad2Long

void Quad2Int(quad qA,int *pi11,int *pi12,int *pi21,int *pi22){
	quad qB=qA;
	*pi11=yNb(qB.q11);*pi12=yNb(qA.q12);*pi21=yNb(qA.q21);*pi22=yNb(qA.q22);
}//Quad2Int

quad qQuad4(long y11,long y12,long y21,long y22){
	quad qQuad4;
	NbAffecter(y11,&qQuad4.q11);
	NbAffecter(y12,&qQuad4.q12);
	NbAffecter(y21,&qQuad4.q21);
	NbAffecter(y22,&qQuad4.q22);
	return(qQuad4);
}//qQuad4

quad qQuadAdd(quad qA,quad qB){
	quad qAdd;
	NbAdd(qA.q11,qB.q11,&qAdd.q11);
	NbAdd(qA.q12,qB.q12,&qAdd.q12);
	NbAdd(qA.q21,qB.q21,&qAdd.q21);
	NbAdd(qA.q22,qB.q22,&qAdd.q22);
	return(qAdd);
}//qQuadAdd

void QuadAMORCER(){
	//amorce le présent module une fois pour toutes
	bQuadAmorceR=kV;
	//QuadQuarteronner();
}//QuadAMORCER

void QuadCompatibleR(graf *pgG){
	int bCompatible,aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMin[aK]=pgG->coulh[aK];
		pgG->nCapaMax[aK]=1;
		pgG->nCout[aK]=0;
	}
	bCompatible=bFlotCompatible(pgG,0,0,k1Afficher);
}//QuadCompatibleR

long yQuadDeterminant(quad qA){
	long yDeterminant=qA.q11.digit[0]*qA.q22.digit[0]-qA.q21.digit[0]*qA.q11.digit[0];
	return(yDeterminant);
}//yQuadDeterminant

int bQuadDeterminer(qMatrice *pmA){//O(S4) calcul exact par quad
	//vrai ssi le déterminant par la méthode de Mahajan et Vinay est nul
	int bVoir=kF;
	quad qAvant,qApres,qDelta,qMatVU,qMatVW,qProduit,qPoleNegatif,qPolePositif,qUn,qZero;
	int bDeterminantNul,nEtage,bCp,bPositif,sH,sX,sV,sW,bCposantPariteh,uSommat,nE;
tee("bQuadDeterminer: pmA->nLigne,2*zPuissance(1+pmA->nLigne,3)",pmA->nLigne,2*zPuissance(1+pmA->nLigne,3));//297 754 quads
	//quad qV[1+1][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
	//Appel0("bQuadDeterminer");
		uSommat=pmA->nLigne;
		//MatriceVoir(sC2b("bQuadDeterminer1 sur",sPluriel(uSommat,"sommet")),pmA);
		Assert1("bQuadDeterminer2",pmA->nLigne==pmA->nColonne);
		//bPositif=bMatricePositive(pmA);
		//tb("Matrice positive ou nulle",bPositif);
		//bPositif=kF;
		bPositif=kV;
		qZero=qQuad(0);
		qUn=qQuad(1);
		//razer toute la structure; O(S3)
			for (bCposantPariteh=0;bCposantPariteh<=1;bCposantPariteh++)
				for (sH=1;sH<=uSommat;sH++)
					for (sX=1;sX<=uSommat;sX++)
						for (nEtage=0;nEtage<=uSommat;nEtage++)
							qVV[bCposantPariteh][sH][sX][nEtage]=qZero;
		qPolePositif=qPoleNegatif=qZero;//VITAL
		//Initialiser à 1 l'étage 0 pour bCposantPariteh=uSommat%2
			bCposantPariteh=uSommat%2;
			for (sH=1;sH<=uSommat;sH++)
				qVV[bCposantPariteh][sH][sH][nEtage=0]=qUn;
			Assert1("bQuadDeterminer3",bQuadNul(qPolePositif) || bQuadNul(qPoleNegatif));
		//traiter les arêtes qui sortent de chaque étage; O(S4)
			for (nEtage=0;nEtage<=uSommat-2;nEtage++){
				if (bVoir) te("nEtage",nEtage);
				for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
					for (sV=sH;sV<=uSommat;sV++)//pour tout sommet sV de rang supérieur ou égal à sH 
						for (bCposantPariteh=0;bCposantPariteh<=1;bCposantPariteh++)
							for (sW =sH+1;sW<=uSommat;sW++){//pour tout sommet sW de rang supérieur à sH
								qMatVW=pmA->Mat[sV][sW];//sW > sH
								qProduit=qQuadMul(qVV[bCposantPariteh][sH][sV][nEtage],qMatVW);
if (!bQuadNul(qProduit))
tqqq("Composaqnte 0 qMatVU,qVV[bCposantPariteh][sH][sV][nEtage],PRODUIT",qVV[bCposantPariteh][sH][sV][nEtage],qMatVW,qProduit);
								if (bPositif) Assert1("bQuadDeterminer12",bQuadModeste(qProduit));
								qAvant=qVV[bCposantPariteh][sH][sW][nEtage+1];
								qApres=qQuadAdd(qAvant,qProduit);
if (!bQuadNul(qApres))
tqqq("Composaqnte 0 qAvant,qProduit,qApres",qAvant,qProduit,qApres);
								//QuadVoir("qAvant",qAvant); QuadVoir("qProduit",qProduit); QuadVoir("qApres",qApres);
								if (bPositif) Assert1("bQuadDeterminer13",bQuadModeste(qApres));
								qVV[bCposantPariteh][sH][sW][nEtage+1]=qApres;

								qMatVU=pmA->Mat[sV][sH];//sV >= sH
								qProduit=qQuadMul(qVV[bCposantPariteh][sH][sV][nEtage],qMatVU);
if (!bQuadNul(qProduit))
tqqq("qComposaqnte 1 MatVU,qVV[bCposantPariteh][sH][sV][nEtage],PRODUIT",qVV[bCposantPariteh][sH][sV][nEtage],qMatVU,qProduit);
								if (bPositif) Assert1("bQuadDeterminer14",bQuadModeste(qProduit));
								qAvant=qVV[1-bCposantPariteh][sW][sW][nEtage+1];
								qApres=qQuadAdd(qAvant,qProduit);
								if (bPositif) Assert1("bQuadDeterminer15",bQuadModeste(qApres));
if (!bQuadNul(qApres))
tqqq("Composaqnte 1 qAvant,qProduit,qApres",qAvant,qProduit,qApres);
								qVV[1-bCposantPariteh][sW][sW][nEtage+1]=qApres;
							}
			}
		//traiter le dernier étage; O(S2)
			for (sH=1;sH<=uSommat;sH++)// sH est le sommet de plus petit rang d'un parcours fermé;cf sClowHead
				for (sV=sH;sV<=uSommat;sV++){//pour tout sommet sV de rang supérieur ou égal à sH
					qProduit=qQuadMul(qVV[1][sH][sV][uSommat-1],pmA->Mat[sV][sH]);
if (0 && !bQuadNul(qProduit))
	t(sCouple(sH,sV));
if (0 && !bQuadNul(qProduit))
tqqq("++++++qPolePositif,qMatVU,AJOUT PRODUIT",qVV[1][sH][sV][uSommat-1],pmA->Mat[sV][sH],qProduit);
					if (bPositif) Assert1("bQuadDeterminer21",bQuadModeste(qProduit));
					qPolePositif=qQuadAdd(qPolePositif,qProduit);//accumulation définie vu assertion bQuadDeterminer3
					if (bPositif) Assert1("bQuadDeterminer22",bQuadModeste(qPolePositif));
					qProduit=qQuadMul(qVV[0][sH][sV][uSommat-1],pmA->Mat[sV][sH]);
if (0 && !bQuadNul(qProduit))
	tt("++++++++++++++++++++++++qPoleNegatif:sH,sV",sCouple(sH,sV));
if (!bQuadNul(qProduit))
tqqq("++++++++++++++++++++++++qPoleNegatif,qMatVH,AJOUT PRODUIT",qVV[0][sH][sV][uSommat-1],pmA->Mat[sV][sH],qProduit);
					if (bPositif) Assert1("bQuadDeterminer23",bQuadModeste(qProduit));
					qPoleNegatif=qQuadAdd(qPoleNegatif,qProduit);//accumulation définie vu assertion bQuadDeterminer3
					if (bPositif) Assert1("bQuadDeterminer24",bQuadModeste(qPoleNegatif));
				}
		if (0){//afficher qVV[1+1][1+pmA->nLigne][1+pmA->nLigne][1+pmA->nLigne];
			t("[Composante,ClowHead,Currentvertex,edges seen so far=layer]");
			for (nE=0,bCp=0;bCp<=1;bCp++)
				for (sW=1;sW<=uSommat;sW++){//étage sW
					for (sH=1;sH<=uSommat;sH++)
						for (sV=1;sV<=uSommat;sV++)
							if (!bQuadNul(qVV[bCp][sH][sV][sW]))
								printf("%5d [%2d,%2d,%2d,%2d] = %s.\n",++nE,bCp,sH,sV,sW,sQuad0(qVV[bCp][sH][sV][sW]));
					Ligne();
				}
		}
		QuadVoir("qPolePositif",qPolePositif);
		QuadVoir("qPoleNegatif",qPoleNegatif);
		qDelta=qQuadSub(qPolePositif,qPoleNegatif);
		if (bPositif) Assert1("bQuadDeterminer35",bQuadModeste(qDelta));
		QuadVoir("qDelta vaut:",qDelta);
		//te("kxLongintMax",kxLongintMax);
		bDeterminantNul=bQuadEgal(qPolePositif,qPoleNegatif);
		bDeterminantNul=bQuadNul(qPolePositif) && bQuadNul(qPoleNegatif);
		//tb("bDeterminantNul Mahajan quad nul",bDeterminantNul);
	//Appel1("bQuadDeterminer");
	return(bDeterminantNul);
	//kxLongintMax= 9 223 372 036 854 775 807. 9*10**18
}//bQuadDeterminer

void QuadDupliquer(quad qA,quad *pqCopie){
	pqCopie->q11=qA.q11;
	pqCopie->q12=qA.q12;
	pqCopie->q21=qA.q21;
	pqCopie->q22=qA.q22;
}//QuadDupliquer

int bQuadEgal(quad qA,quad qB){
	int bEgal;
	bEgal=bNbEgal(qA.q11,qB.q11) && bNbEgal(qA.q12,qB.q12) && bNbEgal(qA.q21,qB.q21) && bNbEgal(qA.q22,qB.q22);
	return(bEgal);
}//bQuadEgal

int bQuadIdentiteh(quad qA){
	int bIdentiteh;
	bIdentiteh=(qA.q11.digit[0]==1 && qA.q12.digit[0]==0 && qA.q21.digit[0]==0 && qA.q22.digit[0]==1);
	return(bIdentiteh);
}//bQuadIdentiteh

void QuadINITIALISER(){//O(?)
	//relance le présent module
	Assert1("QuadINITIALISER",bQuadAmorceR);
}//QuadINITIALISER

int bQuadInversible(quad qA){
	int bInversible;
	bInversible=yQuadDeterminant(qA)!=0;
	return(bInversible);
}//bQuadInversible

void QuadMatriceAllouer(qMatrice **ppmqA){
	const int knLigneMax = kE2;
	*ppmqA=malloc(sizeof(qMatrice));
	(*ppmqA)->nLigne=knLigneMax;
	(*ppmqA)->nColonne=knLigneMax;
}//QuadMatriceAllouer

void QuadMatriceAllouer1(qMatrice **ppmqCarreh,int nDimension){
	Assert1("QuadMatriceAllouer1",nDimension>=0);
	QuadMatriceAllouer(ppmqCarreh);
	(*ppmqCarreh)->nLigne=(*ppmqCarreh)->nColonne=nDimension;
}//QuadMatriceAllouer1

void QuadMatriceAllouer2(qMatrice **ppmqA,int nLigneEnTout,int nColonneEnTout){
	Assert2("QuadMatriceAllouer2",nLigneEnTout>=0,nColonneEnTout>=0);
	QuadMatriceAllouer(ppmqA);
	(*ppmqA)->nLigne=nLigneEnTout;
	(*ppmqA)->nColonne=nColonneEnTout;
}//QuadMatriceAllouer2

int bQuadMatriceVide(qMatrice *pmqA){
	int uL,uC,bMatriceVide;
	for (bMatriceVide=kV,uL=1;uL<=pmqA->nLigne;uL++)
		for (uC=1;uC<=pmqA->nColonne;uC++)
			bMatriceVide=bMatriceVide && bQuadNul(pmqA->Mat[uL][uC]);
	return(bMatriceVide);
}//bQuadMatriceVide

void QuadMatriceVoir(char *sMessage,qMatrice *pmqA){
	int uC,uL,uEmpan,uPas;
	//const int uLargeur=15;
 	Assert2("MatriceVOir",bQuadAmorceR,sMessage!=0);
	//Appel0("QuadMatriceVoir");
	printf("%s (%dx%d):\n",sMessage,pmqA->nLigne,pmqA->nColonne);
	uPas=(pmqA->nSecante==-2)? 2: 1;
	//uEmpan soit le sup des encombrements des valeurs numériques (entiers),signe compris,borné par le nombre de décits sans signe de xkSeuil.
		//pmqA->Mat[5][5].q21=kE7;
		for (uEmpan=1,uL=uPas;uL<=pmqA->nLigne;uL+=uPas)
			for (uC=uPas;uC<=pmqA->nColonne;uC+=uPas){
				uEmpan=iMax(uEmpan,nChaineLg(sNb(pmqA->Mat[uL][uC].q11)));
				uEmpan=iMax(uEmpan,nChaineLg(sNb(pmqA->Mat[uL][uC].q12)));
				uEmpan=iMax(uEmpan,nChaineLg(sNb(pmqA->Mat[uL][uC].q21)));
				uEmpan=iMax(uEmpan,nChaineLg(sNb(pmqA->Mat[uL][uC].q22)));
			}
		uEmpan=1+iSup(2,uEmpan);
	//te("QuadMatriceVoir:uEmpan",uEmpan);
	//pmqA soit affiché
		for (printf("  "),uC=uPas;uC<=pmqA->nColonne;uC+=uPas)//afficher les numéros de colonne
			printf(" %s%2d",sFois(uEmpan-2,'.'),uC);
		Ligne();
		for (uL=1;uL<=pmqA->nLigne;uL++){//afficher les quadruplets verticalt cause ascenseur horizontal inexistant
			for (printf("%2d ",uL),uC=uPas;uC<=pmqA->nColonne || !bLigne();uC+=uPas)
				printf("%s ",sNb0(pmqA->Mat[uL][uC].q11,uEmpan));
			for (printf("   "),uC=uPas;uC<=pmqA->nColonne || !bLigne();uC+=uPas)
				printf("%s ",sNb0(pmqA->Mat[uL][uC].q12,uEmpan));
			for (printf("   "),uC=uPas;uC<=pmqA->nColonne || !bLigne();uC+=uPas)
				printf("%s ",sNb0(pmqA->Mat[uL][uC].q21,uEmpan));
			for (printf("   "),uC=uPas;uC<=pmqA->nColonne || !bLigne();uC+=uPas)
				printf("%s ",sNb0(pmqA->Mat[uL][uC].q22,uEmpan));
			Ligne();
		}
	if (pmqA->nSecante==-2){//vérifier que les éléments impairs sont tous nuls
		for (uL=1;uL<=pmqA->nLigne;uL++)
			for (uC=1;uC<=pmqA->nColonne;uC+=2)
				Assert4("MatriceVoir colonne impaire nulle",bNbNul(pmqA->Mat[uL][uC].q11),bNbNul(pmqA->Mat[uL][uC].q12),bNbNul(pmqA->Mat[uL][uC].q21),bNbNul(pmqA->Mat[uL][uC].q22));
	}
	//Appel1("QuadMatriceVoir");
}//QuadMatriceVoir

void QuadMatriceZeroter(qMatrice *pmqA,int uHauteur,qMatrice *pmqAh){
	//all rows and columns not greater than uHauteur zeroed
	int uC,uL;
	Assert1("QuadMatriceZeroter",bCroit(1,uHauteur,pmqA->nLigne));
	//pmqAh:=pmqA
		for (uL=1;uL<=pmqA->nLigne;uL++)
			for (uC=1;uC<=pmqA->nColonne;uC++)
				pmqAh->Mat[uL][uC]=pmqA->Mat[uL][uC];
	for (uL=1;uL<=uHauteur;uL++)
		for (uC=1;uC<=pmqA->nColonne;uC++)
			pmqAh->Mat[uL][uC]=qQuad(0);
	for (uL=1;uL<=pmqA->nLigne;uL++)
		for (uC=1;uC<=uHauteur;uC++)
			pmqAh->Mat[uL][uC]=qQuad(0);
}//QuadMatriceZeroter

int bQuadModeste(quad qQuoi){
	//qQuoi a des éléments pas trop grand en valeur absolue
	//long kzGeant=kxLongintMax-1;
	int bModeste;
	//=labs(qQuoi.q11)<kzGeant && labs(qQuoi.q12)<kzGeant && labs(qQuoi.q21)<kzGeant && labs(qQuoi.q22)<kzGeant;
	bModeste=kV;
	return(bModeste);
}//bQuadModeste

quad qQuadMul(quad qA,quad qB){
	quad qMul;
	nb nbDroit,nbGauche;
	NbMul(qA.q11,qB.q11,&nbGauche);		NbMul(qA.q12,qB.q21,&nbDroit);		NbAdd(nbGauche,nbDroit,&qMul.q11);
	NbMul(qA.q11,qB.q12,&nbGauche);		NbMul(qA.q12,qB.q22,&nbDroit);		NbAdd(nbGauche,nbDroit,&qMul.q12);
	NbMul(qA.q21,qB.q11,&nbGauche);		NbMul(qA.q22,qB.q21,&nbDroit);		NbAdd(nbGauche,nbDroit,&qMul.q21);
	NbMul(qA.q21,qB.q12,&nbGauche);		NbMul(qA.q22,qB.q22,&nbDroit);		NbAdd(nbGauche,nbDroit,&qMul.q22);
/*
	qMul.q11=qA.q11*qB.q11+qA.q12*qB.q21;
	qMul.q12=qA.q11*qB.q12+qA.q12*qB.q22;
	qMul.q21=qA.q21*qB.q11+qA.q22*qB.q21;
	qMul.q22=qA.q21*qB.q12+qA.q22*qB.q22;
*/

	return(qMul);
}//qQuadMul

quad qQuadMul3(quad qA,quad qB,quad qC){
	//multiplie par associativité à gauche
	quad qMul3;
	qMul3=qQuadMul(qQuadMul(qA,qB),qC);
	return(qMul3);
}//qQuadMul3

quad qQuadNeg(quad qA){
	quad qNeg;
	NbDupliquer(qA.q11,&qNeg.q11);	qNeg.q11.sign= - qNeg.q11.sign;
	NbDupliquer(qA.q12,&qNeg.q12);	qNeg.q12.sign= - qNeg.q12.sign;
	NbDupliquer(qA.q21,&qNeg.q21);	qNeg.q21.sign= - qNeg.q21.sign;
	NbDupliquer(qA.q22,&qNeg.q22);	qNeg.q22.sign= - qNeg.q22.sign;
/*
	qNeg.q11=-qA.q11;
	qNeg.q12=-qA.q12;
	qNeg.q21=-qA.q21;
	qNeg.q22=-qA.q22;
*/
	return(qNeg);
}//qQuadNeg

int bQuadNul(quad qA){
	int bNul;
	bNul=bNbNul(qA.q11) && bNbNul(qA.q12) && bNbNul(qA.q21) && bNbNul(qA.q22);
	return(bNul);
}//bQuadNul

quad qQuadQuarteroN(int nCouleur){
	quad qQuarteron;
	Assert1("qQuadQuarteroN",bCroit(0,nCouleur,kuQuarteronMaX) );
	qQuarteron=qQuarteroN[nCouleur];
	return(qQuarteron);
}//qQuadQuarteroN

void QuadQuarteronner(){
	//rend qA,qB,qC,qD non nulles tels que (qA*qC)*qB=(qB*qD)*qA=0.
	int nQ,iA,iB,iC,  iU,iX,iZ,  iAlpha,iBeta,iGamma,  iUprim,iXprim,iZprim;
	quad qA,qB,qC,qD;
	iA=1;
	iB=1;
	iC=2;

	iAlpha=1;
	iBeta=1;
	iGamma=3;

	iU=1;
	iX=2;
	iZ=1;

	iUprim=1;
	iXprim=2;
	iZprim=3;
	
	qA=qQuad4(iAlpha*iAlpha,iAlpha*iBeta,iAlpha*iGamma,iBeta*iGamma);
	qB=qQuad4(iA*iA,iA*iB,iA*iC,iB*iC);
	Assert2("QuadQuarteR1",!bQuadInversible(qA),!bQuadInversible(qB));//dc il existe des quads A' et B' tels que A.A'=0 et B.B'=0.
	qC=qQuad4(iA*iC*iX,iBeta*iU-iA*iA*iX,iA*iC*iZ,-iAlpha*iU-iA*iA*iZ);
	Assert4("QuadQuarteR2",!bNbNul(qC.q11),!bNbNul(qC.q12),!bNbNul(qC.q21),!bNbNul(qC.q22));//ne s'impose pas
	qD=qQuad4(iAlpha*iGamma*iXprim,iB*iUprim-iAlpha*iAlpha*iXprim,iAlpha*iGamma*iZprim,-iA*iUprim-iAlpha*iAlpha*iZprim);
	Assert4("QuadQuarteR3",!bNbNul(qD.q11),!bNbNul(qD.q12),!bNbNul(qD.q21),!bNbNul(qD.q22));//ne s'impose pas
	Assert4("QuadQuarteR4",!bQuadNul(qA),!bQuadNul(qB),!bQuadNul(qC),!bQuadNul(qD) );//dc multiplicOs non triviales
	Assert2("QuadQuarteR5",bQuadNul(qQuadMul3(qA,qC,qB)),bQuadNul(qQuadMul3(qB,qD,qA)));
	//on vérifie que ( (1,1,3,3) * (4,-1,2,-2) ) * (1,1,2,2) = (0,0,0,0) et ( (1,1,2,2) * (6,-1,9,-4) ) * (1,1,3,3) = (0,0,0,0).
	for (nQ=0;nQ<=kuQuarteronMaX;nQ++)
		qQuarteroN[nQ]=qQuad(nQ);
	qQuarteroN[5]=qA;
	qQuarteroN[6]=qB;
	qQuarteroN[7]=qC;
	qQuarteroN[8]=qD;
	if (0) for (nQ=0;nQ<=kuQuarteronMaX;nQ++)
		QuadVoir(sC2("   Quarteron n°",sEnt(nQ)),qQuarteroN[nQ]);
	Assert1("QuadQuarteronner45",bQuadIdentiteh(qQuarteroN[1]) );
}//QuadQuarteronner

void QuadripoleR(int uPivot,graf *pgG,int bBipartitionner,graf **ppgH){
	//génère dans ppgH un graphe dans lequel tout sommet de pgG est remplacé par un quadripole contenant une longrine
	const int kuCouleurForte=1-bBipartitionner;
	const int bVoir=kF;
	int iLongrine,nQuadripole,aK,sX,sY,uP,nQ;
	int nSommat=pgG->nSommetEnTout;
	int nSommetApres=uPivot*(1+bBipartitionner)+4*pgG->nArcEnTout;//avant symétrisation
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
					GrapheArquer1(*ppgH,szPred[sX],(bBipartitionner)? nSommetApres-uP+1: uP,kuCouleurForte);
	if (!bBipartitionner) 
		for (aK=1;aK<=(*ppgH)->nArcEnTout;aK++)
			if ( (*ppgH)->coulh[aK]==kuCouleurForte )
				(*ppgH)->coulh[aK]=aK;
	if (bVoir) GrapheVoir(*ppgH,"ppgH creux");
		//remplir (liens internes) les quadripôles
			for (iLongrine=(bBipartitionner)? 16: 82,nQ=0;nQ<nQuadripole;nQ++)
				LongrineR(iLongrine,uPivot+4*nQ+1,uPivot+4*nQ+2,uPivot+4*nQ+3,uPivot+4*nQ+4,*ppgH);
	if (bVoir) GrapheVoir(*ppgH,"ppgH FINAL longriné");
}//QuadripoleR

quad qQuadSub(quad qA,quad qB){
	quad qSub;
	qSub=qQuadAdd(qA,qQuadNeg(qB));
	return(qSub);
}//qQuadSub

void QuadTESTER(int iTest){
	//teste le présent module
	int iLongrine;
	quad qA,qB,qC,qD,qR;
	graf *pgG,*pgH;
	int aK,sX,sY,uP,bSucces;
	Appel0(sC2("QuadTESTER,test n°",sEnt(iTest)));
		iTest=5;
		switch (iTest) {
			case 0:
					for (uP=1;uP<=2;uP++){
						GrapheCreer(-2,&pgG);
							GrapheArquer(pgG,1,2);
							if (uP>0) GrapheVoir(pgG,"pgG");
							QuadripoleR(uP,pgG,k1Biparti,&pgH);
								//bSucces=bDeterminantCaracteriseR(pgH,uP>0);
								QuadCompatibleR(pgH);
								//printf("%s avec %s.\n",sChoix(bSucces,"Succès","Échec"),sPluriel(uP,"pivot"));
							free(pgH);
						free(pgG);
					}
					break;
			case 1:
					Titrer("Multiplications inter quads");
					qA=qQuarteroN[5];qB=qQuarteroN[6];qC=qQuarteroN[7];qD=qQuarteroN[8];
					qR=qQuadMul3(qA,qC,qB);//QuadVoir("qR0",qR);
					printf("( %s * %s ) * %s = %s.\n",sQuad(qA),sQuad(qC),sQuad(qB),sQuad(qR));
					qR=qQuadMul3(qB,qD,qA);//QuadVoir("qR1",qR);
					printf("( %s * %s ) * %s = %s.\n",sQuad(qB),sQuad(qD),sQuad(qA),sQuad(qR));
					break;
			case 2: GrapheCreer(-4,&pgG);
					//GrapheVoir1(pgG,k1Couleur,"pgG avant LongrineR");
					LongrineR(iLongrine=41,1,2,3,4,pgG);
					GrapheVoir1(pgG,k1Couleur,"pgG après LongrineR");
					if (0) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
							sY=pgG->sSuk[aK];
							pgG->coulh[aK]=-3;
					}
					//GrapheVoir(pgG,"pgG");
					bSucces=bDeterminantCaracteriseR(pgG,k1Voir);
					break;
			case 3:
					t("TRIANGLE");//OK
					for (uP=1;uP<=3;uP++){
						GrapheCreer(-3,&pgG);
						GrapheArquer(pgG,1,2);
						GrapheArquer(pgG,2,3);
						GrapheArquer(pgG,1,3);
							if (uP>0) GrapheVoir(pgG,"pgG");
							QuadripoleR(uP,pgG,!k1Biparti,&pgH);
								bSucces=bDeterminantCaracteriseR(pgH,uP>0);
								printf("%s avec %s.\n",sChoix(bSucces,"Succès","Échec"),sPluriel(uP,"pivot"));
							free(pgH);
						free(pgG);
					}
					break;
			case 4:
					t("TRIANGLE ET MANCHE");//OK
					for (uP=1;uP<=4;uP++){
						GrapheCreer(-4,&pgG);//triangle avec manche
							GrapheArquer(pgG,1,2);
							GrapheArquer(pgG,1,3);
							GrapheArquer(pgG,2,3);
							GrapheArquer(pgG,1,4);
							if (uP>0) GrapheVoir(pgG,"pgG");
							QuadripoleR(uP,pgG,!k1Biparti,&pgH);
								bSucces=bDeterminantCaracteriseR(pgH,uP==1);
								printf("%s avec %s.\n",sChoix(bSucces,"Succès","Échec"),sPluriel(uP,"pivot"));
							free(pgH);
						free(pgG);
					}
					break;
			case 5:
					t("CLIQUE K4");//KO
					for (uP=2;uP<=2;uP++){
						GrapheCreer(-4,&pgG);
							GrapheArquer(pgG,1,2);
							GrapheArquer(pgG,1,3);
							GrapheArquer(pgG,1,4);
							GrapheArquer(pgG,2,3);
							GrapheArquer(pgG,2,4);
							GrapheArquer(pgG,3,4);
							if (uP>0) GrapheVoir(pgG,"pgG");
							QuadripoleR(uP,pgG,!k1Biparti,&pgH);
								bSucces=bDeterminantCaracteriseR(pgH,uP==1);
								printf("%s avec %s.\n",sChoix(bSucces,"Succès","Échec"),sPluriel(uP,"pivot"));
							free(pgH);
						free(pgG);
					}
					break;
		default:
			Assert1("QuadTESTER",0);
			break;
	}
	Appel1(sC2("QuadTESTER,test n°",sEnt(iTest)));
}//QuadTESTER	

void QuadVoir(char *sMessage,quad qVoir){
	printf("%s (%s,%s,%s,%s).\n",sMessage,sNb(qVoir.q11),sNb(qVoir.q12),sNb(qVoir.q21),sNb(qVoir.q22));
}//QuadVoir

void VeqteurCopieR(quad qVecteurA[],int nIndexMin,int nIndexMax,quad qVecteurB[]){
	//qVecteurB[nIndexMin..nIndexMax] := qVecteurA[nIndexMin..nIndexMax] 
	int nK;
	Assert3("VecteurCopier",qVecteurA!=0,qVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		qVecteurB[nK]=qVecteurA[nK];
}//VeqteurCopieR

int bVeqteurNuL(quad qVecteur[],int nIndexMin,int nIndexMax){
	//iVecteur[nIndexMin..nIndexMax] est nul partout 
	int uE;
	int bNul;
	Assert1("bVeqteurNuL",bCroit(0,nIndexMin,nIndexMax));
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (!bNbNul(qVecteur[uE].q11) || !bNbNul(qVecteur[uE].q12) || !bNbNul(qVecteur[uE].q21) || !bNbNul(qVecteur[uE].q22) )
			 bNul=kF;
	return(bNul);
}//bVeqteurNuL

void VeqteurVoiR(char *sNom,quad qQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Assert3("VeqteurVoiR",sNom!=0,qQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	printf("%s: ",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("(%s %s %s %s)%c ",sNb(qQuelVecteur[nE].q11),sNb(qQuelVecteur[nE].q12),sNb(qQuelVecteur[nE].q21),sNb(qQuelVecteur[nE].q22),(nE<nIndexMax)?',':'.');
	printf("\n");
}//VeqteurVoiR

void VeqteurRazeR(quad qVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VeqteurRazeR",qVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			qVecteur[nE]=qQuad(0);
}//VeqteurRazeR

