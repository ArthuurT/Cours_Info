#include "Outil.h"
#include "Abe.h"
#include "Deque.h"
//ABE=Arbre Binaire Etagé "essentiellement complet". Ses éléments sont des paires d'entiers (sSommet,iPoidS). 
//Pour extraire des sommets de poids minimal (maximal), ouvrir d'abord l'ABE via AbeAllouer(nSommetEnTout,iPoidsInfini) avec iPoidsInfini>0 (<0).
//sert à implémenter une variante plus efficace de l'algo de Prim pr calculer les arbres couvrants de poids optimal.
int bAbeAmorceR;//ie le module a effectivement été amorcé
int bAbeOuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un abe est actuellement alloué
int nAbeVoiR;

#define kuSommetEnTout 512
#define kuCoupleLiM (2*kuSommetEnTout)
#define kuCoupleMaX kuCoupleLiM-1
#define kbFilE kV //ie une file d'attente sera utilisée pour ne propager que les points chauds vers le sommet de l'ABE.
#define kbFileVoiR kF
#define kuEtageLiM 10
int nCOUT;
int uEtageEnTouT;
int bMinimiseR;
int ikPoidsInfinI;
int iPoidS[kuCoupleLiM];//poids de la paire pondérée courante.
int sSommeT[kuCoupleLiM];//sommet de la paire pondérée courante.
int nSommetMaX;
int nSommetMaximaL;
int nSommetOffseT;

void AbeAllouer(int nSommetEnTout,int iPoidsInfini){//O(S)
	//si nSommetEnTout>0, alloue un abe qui permet de gérer nSommetEnTout paires pondérées et mémorise iPoidsInfinI. Sinon, écrase l'abe. 
	int uPuissanceDe2,sX;
	Assert1("AbeAllouer1",bAbeAmorceR);
	FlipFlop("AbeAllouer2",nSommetEnTout>0,&bAbeOuverT);//contraint l'appelant à allouer un abe avant de l'utiliser et à le restituer avant de pouvoir en allouer un autre. 
	nSommetMaX=0;
	if (nSommetEnTout>0){
		nCOUT=0;//vu nouvelle allocation
		bMinimiseR=iPoidsInfini>0;
		ikPoidsInfinI=iPoidsInfini;
		for (uEtageEnTouT=1,uPuissanceDe2=1;uPuissanceDe2<=kuCoupleMaX && uPuissanceDe2<nSommetEnTout;uPuissanceDe2=2*uPuissanceDe2)
			uEtageEnTouT++;
		nCOUT+=uEtageEnTouT;
		nSommetMaX=uPuissanceDe2+nSommetEnTout;
		nSommetOffseT=uPuissanceDe2-1;
		nSommetMaximaL=nSommetOffseT+uPuissanceDe2;
		//teeee("nSommetEnTout,nSommetMaX,uEtageEnTouT,nSommetOffseT",nSommetEnTout,nSommetMaX,uEtageEnTouT,nSommetOffseT);
		Assert3("AbeAllouer3",nSommetMaX<kuCoupleLiM,uEtageEnTouT<kuEtageLiM,iPoidsInfini!=0);
		VecteurRazer(sSommeT,1,nSommetMaximaL);
		nCOUT+=nSommetMaximaL;
		VecteurValuer(iPoidS,1,nSommetMaximaL,ikPoidsInfinI);//O(S)
		nCOUT+=nSommetMaximaL;
		for (sX=1;sX<=1+nSommetMaximaL/2;sX++)
			sSommeT[nSommetMaximaL/2+sX]=sX;
		nCOUT+=1+nSommetMaximaL/2;
		if (kbFilE) DequeAllouer(nSommetMaximaL);//O(nSommetMaximaL)
		if (kbFilE) nCOUT+=nSommetMaximaL;
		//AbeVoir("après allocation");
	}else if (kbFilE) DequeAllouer(0);//O(1)
}//AbeAllouer

void AbeAMORCER(){
	//amorce le présent module une fois pour toutes
	bAbeAmorceR=kV;
	bAbeOuverT=kF;
	ikPoidsInfinI=0;
}//AbeAMORCER

int bAbeContient(int sSommet){
	Assert3("bAbeContient",bAbeAmorceR,bAbeOuverT,nCOUT>0);//COUT>0 dû au moins à l'initialisation d'un abe.
	int nIndex=nSommetOffseT+sSommet;
	int bContient=iPoidS[nIndex]!=ikPoidsInfinI;
	return(bContient);
}//bAbeContient

int nAbeCout(){
	//retourne le coût de gestion de l'abe depuis la dernière allocation
	Assert3("nAbeCout",bAbeAmorceR,bAbeOuverT,nCOUT>0);//COUT>0 dû au moins à l'initialisation d'un abe.
	return(nCOUT);
}//nAbeCout

int eAbeExtraire(){
	//retourne l'élément de plus petit poids
	int eExtraire,nIndex;
	Assert2("eAbeExtraire",bAbeAmorceR,bAbeOuverT);
	eExtraire=sSommeT[1];
	nIndex=nSommetOffseT+eExtraire;
	iPoidS[nIndex]=ikPoidsInfinI;//alourdit au maximum le sommet extrait
	if (kbFilE){
		nIndex=bPair(nIndex)? nIndex+1: nIndex-1;
		DequeEnfiler(nIndex);//O(1)
		if (kbFileVoiR) te("renfile",nIndex);
	}
	nCOUT++;
	Assert1("eAbeExtraire2",bCroit(1,eExtraire,nSommetMaX));
	return(eExtraire);
}//eAbeExtraire

void AbeINITIALISER(){//O(?)
	//initialise au besoin certains paramètres des structure de données de l'abe.
	Assert1("AbeINITIALISER",bAbeAmorceR);
	//compléter le code au beaoin
}//AbeINITIALISER

void AbeModifier(int sSommet,int iPoidsCourant){//O(1)
	//affecte iPoidsCourant à la paire (sSommet,iPoidS) mémorisée au rez-de-chaussée de l'abe.
	Assert3("AbeModifier",bAbeAmorceR,bAbeOuverT,bCroit(1,sSommet,nSommetMaX));
	int nIndex=nSommetOffseT+sSommet;
	//tee("sSommet,iPoidSCourant",sSommet,iPoidSCourant);
	iPoidS[nIndex]=iPoidsCourant;
	if (kbFilE) DequeEnfiler(nIndex);//O(1)
	if (kbFileVoiR) te("enfile",nIndex);
	nCOUT++;
}//AbeModifier

void AbePropager(){//O(S)
	//propage de bas en haut les paires (sSommet,iPoidS) de poids minimal.
	int nCout=0,iFilsDePoidsMin,iFils,iPere;
	Assert2("AbePropager",bAbeAmorceR,bAbeOuverT);
	if (!kbFilE)
		for (iFils=nSommetMaximaL;iFils>1;iFils-=2){
			iPere=iFils/2;
			if (iPere>0){
				if (bMinimiseR)
					iFilsDePoidsMin=iFils-(iPoidS[iFils-1]<=iPoidS[iFils]);
				else iFilsDePoidsMin=iFils-(iPoidS[iFils-1]>=iPoidS[iFils]);
				iPoidS[iPere]=iPoidS[iFilsDePoidsMin];
				sSommeT[iPere]=sSommeT[iFilsDePoidsMin];
				nCout++;
			} else Assert1("AbePropager1",0);
		}
	else while (!bDequeVide()){
		iFils=sDequeDefiler();
		if (kbFileVoiR) teee( "défile,sommet,pere",iFils,iFils-nSommetMaximaL/2,iFils/2);
		iPere=iFils/2;
		if (iPere>0){//remonter les plus petits poids en recopiant la paire d'index iFilsDePoidsMin dans la paire d'index iPere.
			if (bMinimiseR)
				iFilsDePoidsMin=2*iPere+(iPoidS[2*iPere+1]<iPoidS[2*iPere]);
			else iFilsDePoidsMin=2*iPere+(iPoidS[2*iPere+1]>iPoidS[2*iPere]);
			iPoidS[iPere]=iPoidS[iFilsDePoidsMin];
			sSommeT[iPere]=sSommeT[iFilsDePoidsMin];
			nCout++;
			//te("iPere",iPere);
			DequeEnfiler(iPere);
			if (kbFileVoiR) te("    réenfile",iPere);
		}
	}//else while
	Assert1("AbePropager2",nCout<=nSommetMaX);
	nCOUT+=nCout;
	//AbeVoir("après AbePropager");
}//AbePropager

void AbeTESTER(int iTest){
	//teste le présent module
	Assert1("AbeTESTER",bAbeAmorceR);
	Appel0(sC2("AbeTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 0://compléter le code
				break;
			case 1://compléter le code
				break;
			default:
				Assert1("AbeTESTER",0);
				break;
		}
	Appel1(sC2("AbeTESTER,test n°",sEnt(iTest)));
}//AbeTESTER	

void AbeVoir(char *sQuoi){//O(S)
	Assert3("AbeVoir",bAbeAmorceR,bAbeOuverT,sQuoi!=0);
	int uEtage,uEtageMax,uIndex,uPuissanceDe2;
	int lgmPoids,lgmSommet,lgmCouple;//lgm=longueur maximale en nombre de caractères
	int ncEncombrement[kuEtageLiM],ncMargeGauche[kuEtageLiM],ncPas[kuEtageLiM];//nc=nombre de caractères
	//Appel0("AbeVoir");
	nAbeVoiR++;
	printf("Abe n°%d %s:\n",nAbeVoiR,sQuoi);
		//lgmSommet:=encombrement maximal en nombre de caractères requis pour spécifier un sommet quelconque de [1..nSommetMaX]:
			lgmSommet=nChaineLg(sEnt(nSommetMaX));//puisque le sommet de rang max est nSommetMaX
		//lgmPoids:=encombrement maximal en nombre de caractères du poids attaché à un sommet  quelconque de [1..nSommetMaX]:
			for (lgmPoids=0,uIndex=1;uIndex<=nSommetMaX;uIndex++)
				lgmPoids=iSup(lgmPoids,nChaineLg(sEnt(iPoidS[uIndex])));
		//lgmCouple:=encombrt maximal en nbre de caractères du couple (sommet,poids) attaché à un sommet qcq de [1..nSommetMaX]:
			lgmCouple=1+lgmSommet+1+lgmPoids+1;//1 ppur parenthèse et 1 pour virgule
		//teee("lgmCouple,lgmSommet,lgmPoids",lgmCouple,lgmSommet,lgmPoids);
		//ncEncombrement[]:=encombrement en nombre de caractères de chaque étage de l'abe:
			for (ncEncombrement[uEtageEnTouT]=nSommetMaximaL*lgmCouple,uEtage=uEtageEnTouT-1;uEtage>0;uEtage--)
				ncEncombrement[uEtage]=ncEncombrement[uEtage+1]/2;
			//VecteurVoir("ncEncombrement",ncEncombrement,1,uEtageEnTouT);
		//ncPas[]:=espacement en nombre de caractères entre les couples affichés à chaque étage:
			VecteurRazer(ncPas,1,kuEtageLiM-1);
			for (ncPas[uEtageEnTouT]=1,uEtage=uEtageEnTouT-1;uEtage>0;uEtage--)
				ncPas[uEtage]=ncPas[uEtage+1]*2;
			//VecteurVoir("ncPas",ncPas,1,uEtageEnTouT);
		//ncMargeGauche[]:=marge gauche en nombre de caractères ménagée avant l'affichage du premier couple de l'étage courant:
			VecteurRazer(ncMargeGauche,1,kuEtageLiM-1);
			for (ncMargeGauche[uEtageEnTouT-1]=lgmCouple/2,uPuissanceDe2=1,uEtage=uEtageEnTouT-2;uEtage>0;uEtage--){
				ncMargeGauche[uEtage]=ncMargeGauche[uEtage+1]+uPuissanceDe2*lgmCouple;
				uPuissanceDe2=2*uPuissanceDe2;
			}
			//VecteurVoir("ncMargeGauche",ncMargeGauche,1,uEtageEnTouT);
		uEtageMax=nLog2(iSup(2,nSommetMaX-1));
		//te("uEtageMax",uEtageMax);
		for (uPuissanceDe2=1,uEtage=0,uIndex=1;uIndex<=nSommetMaX;uIndex++){
			if (uIndex==uPuissanceDe2){
				//te("uEtage courant",uEtage);
				uPuissanceDe2=2*uPuissanceDe2;
				if (uPuissanceDe2>2 && uEtage<uEtageMax)
					Ligne();
				uEtage++;
				printf("%s",sE(ncMargeGauche[uEtage]));
			}
			if (uEtage<=uEtageMax){
				printf("(%s,%s)",sEntier(sSommeT[uIndex],lgmSommet),sEntier(iPoidS[uIndex],lgmPoids));
				if ((ncPas[uEtage]-1)*lgmCouple>0)
					printf("%s",sE((ncPas[uEtage]-1)*lgmCouple));
			}
		}
	printf(".\n");
	//Appel1("AbeVoir");
}//AbeVoir

