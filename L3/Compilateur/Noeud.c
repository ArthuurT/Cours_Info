#include "Outil.h"
#include "Noeud.h"
#include "Forme.h"
#include "Deque.h"
int bNoeudAmorceR;//ie le module a effectivement été amorcé
int bNoeudOuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un arbre est actuellement alloué
int nNoeudVoiR;
#define knNoeudLiM kE7
#define knNoeudMaX (knNoeudLiM-1)
const int kbLitteraliseR=kF;
typedef struct{
	int nog;int nod;int typ;int val;int aqqu;int dequ;int eta;int fwa;
} tNoeuD;
tNoeuD aNoeuD[knNoeudLiM];
int nArtereMarqueR;
#define kuPlaceLiM 100
int noPlacE[kuPlaceLiM];

int iNoeuD;//pointeur courant sur le premier noeud de la liste libre
char *sOperateuR=".+*-/";//déclasse pas
#define knPisteMaX kE2
long zNoeudArboreR;
int nNoeudDerouteR;
int bNoeudVerifieR;
int nNoeudVerifieR;
int nNoeudCouvrirTouT;
int qArtereDebouteR[4];
int nNoeudEnumereR[4];
#define kuComposanteLiM 8
#define kuComposanteMaX kuComposanteLiM-1
int nNoeudEnumererEnTouT[kuComposanteLiM],nNoeudEnumererEnTroP[kuComposanteLiM],nNoeudEnumererElementairE[kuComposanteLiM],nNoeudEnumererTotaL[kuComposanteLiM];
long zNoeudVisitehEnTouT;
int nPriS;//total courant des noeuds pris dans la liste libre et pas encore restitués.
const int kuSegmentAnnoncE = 3;
#define kuPiedLiM 10
int ipPiedEtendrE;
int noPiedListE[kuPiedLiM];
#define kuPileLiM 64
#define kuSegmentLiM 64
#define kuArcParSegmenT 3
int iSegmenT[kuSegmentLiM][1+kuArcParSegmenT];
int nSegmentMaX;

void ArtereDenombreR(int uDag,int noRacine);//dédié zArtereDenombreR
long zArtereDenombreR(int uDag,int noRacine);//dédié NoeudCouvrir
int nFeuilleEnTouT(int noRacine,int nEnquis);
void FeuillePisteR(int noRacine,int iFeuilleValeur,int nOccurrence,int nPiste[]);
int noFeuillePlacE(int noRacine,int iValeur,int *pnOccurrence);
void NoeudArboreR(int noRacine,int nTabulation,int bAfficher);//dédié NoeudArborer
int iNoeudEvalueR(int noRacine,int bUn);//dédié iNoeudEvaluer
void NoeudFormuleR(int noRacine);//dédié NoeudFormuler
int noNoeudLibrE();
void NoeudMarqueR(int noRacine,int cMarque);
void NoeudPaterneR(int noRacine,int noPere);//dédié NoeudPaterner() égalt non appelé
void NoeudRestitueR(int iNoeud);
void NoeudListeR(int noRacine,int bPreparer,int *pnSommetEnTout,int *pnArcEnTout);
int noNoeudSingletonneR(char* sTitre,int noRacine);//PADAPEL
void NoeudVerifieR(int noRacine,int bCompter);//appelé en bascule ds plusieurs routines ci-dessous
int iOperandeDroiT(int noProduitOuDivision);
void OptimumExhibeR(int noRacine,int iProfondeur,int iSente[]);
void PiedEtendrePartouT(int noRacine);
void PiedListeR(int noTronc);
void SegmentAfficheR();
int bSegmentBannI1(int iPoidsXY);
int bSegmentBannI2(int iPoidsXY,int iPoidsYZ);
int bSegmentBannI3(int iPoidsXY,int iPoidsZT);
int bSegmenConnU(int nPoids1,int nPoids2,int nPoids3,int nSegmentEnTout);
int bSegmentElemenT(int iValeur);
int bSegmentInterdiT(int uDag,int noTete,int noTronc,int noPied);
void SegmentInverseR();
int bSegmentPresenT(int iPoids[]);
int bSegmentPresenT1(int iPoids[]);
int bSegmentPresenT2(int iPoids[]);
void SegmentVoiR(char *sQuoi);

int noPilE[kuPileLiM];
int ipPilE;

int nArtereDebouteR(int uDag,int noRacine){
	//rend le nombre total de couvertures valides dans le dag ou sous-dag de racine noRacine.
	int noGauche,noDroit,bInterdit;
	int nDebouter=0;
	int nG,nD;
	Assert2("ArtereDebouteR",noRacine>0,bCroit(NoeudNombre,aNoeuD[noRacine].typ,NoeudSoustraction));
	zNoeudVisitehEnTouT++;
	if (uDag==10) SegmentVoiR("ArtereDebouteR");
 	if (1 || aNoeuD[noRacine].eta==0){//sinon,le dag sera déployé en arbre,lequel sera parcouru en tps exponentiel en pire cas. 
		aNoeuD[noRacine].eta=1;//d; >0 pr parcourir un dag et non pas un arbre.
		switch (aNoeuD[noRacine].typ) {
			case NoeudDivision:
			case NoeudProduit:	bInterdit=bSegmentInterdiT(uDag,noPilE[ipPilE-1],noPilE[ipPilE-0],noRacine);
								//if (bInterdit) d3(noRacine,aNoeuD[noRacine].nog,iOperandeDroiT(noRacine));
								noPilE[++ipPilE]=noRacine;
									if (!bInterdit){
										nG=nArtereDebouteR(uDag,noGauche=aNoeuD[noRacine].nog);
										nDebouter=nG;
									}else nDebouter=0;
								ipPilE--;
								break;
			case NoeudSoustraction:
			case NoeudAddition:	nG=nArtereDebouteR(uDag,noGauche=aNoeuD[noRacine].nog);
								nD=nArtereDebouteR(uDag,noDroit=aNoeuD[noRacine].nod);
								nDebouter=nG+nD;
								break;
			case NoeudNombre:	nDebouter=1;//ainsi le dequ d'un produit de deux NoeudNombre est non nul.
		}
  	}
	//tee("noRacine,nDebouter",noRacine,nDebouter);
	return(nDebouter);
}//nArtereDebouteR

long zArtereDebouteR(int uDag,int noRacine,int nPivot){
	//rend ds aNoeuD[noRacine].dequ le nombre total de couvertures valides dans le dag ou sous-dag de racine noRacine.
	int bAfficher,noNoeud,nPris;
	bAfficher=qArtereDebouteR[uDag]>0;
	bAfficher=kF;
	if (bAfficher) Titrer( sC2("zArtereDebouteR, dag n°",sEnt(uDag)) );
	zNoeudVisitehEnTouT=0;//d pr ArtereDebouteR
		for (nPris=nNoeudPris(),noNoeud=1;noNoeud<=nPris;zNoeudVisitehEnTouT++,noNoeud++)
			aNoeuD[noNoeud].eta=0;
		noPilE[1]=noPilE[2]=noPilE[3]=0;
		ipPilE=3;
		zNoeudVisitehEnTouT=0;
	SegmentInverseR();
		aNoeuD[noRacine].dequ=nArtereDebouteR(uDag,noRacine);
	SegmentInverseR();
	if (bAfficher) Titrer(sC6("zArtereDebouteR avec ",sPluriel(nPivot,"pivot"),", dag n°",sEnt(uDag),":   ",sPluriel(aNoeuD[noRacine].dequ,"chemin")));
	//printf("ArtereDebouteR FINI: aNoeuD[noRacine].aqqu=%d et aNoeuD[noRacine].dequ=%d.\n",aNoeuD[noRacine].aqqu,aNoeuD[noRacine].dequ);
	if (0){
		SegmentAfficheR();
			NoeudArborer("APRES zArtereDebouteR",noRacine);
		SegmentAfficheR();
	}
	return(zNoeudVisitehEnTouT);
}//zArtereDebouteR

void ArtereDenombreR(int uDag,int noRacine){
	//cf zArtereDenombreR
	int noGauche,noDroit;
	Assert2("ArtereDenombreR",noRacine>0,bCroit(NoeudNombre,aNoeuD[noRacine].typ,NoeudSoustraction));
	zNoeudVisitehEnTouT++;
 	if (aNoeuD[noRacine].eta==0){//sinon,le dag sera déployé en arbre,lequel sera parcouru en tps exponentiel en pire cas. 
		aNoeuD[noRacine].eta=1;//d; >0 pr parcourir un dag et non pas un arbre.
 		if (aNoeuD[noRacine].typ!=NoeudNombre){
			ArtereDenombreR(uDag,noGauche=aNoeuD[noRacine].nog);
			ArtereDenombreR(uDag,noDroit=aNoeuD[noRacine].nod);
			if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction)
				aNoeuD[noRacine].aqqu=aNoeuD[noGauche].aqqu+aNoeuD[noDroit].aqqu;
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision)
				aNoeuD[noRacine].aqqu=aNoeuD[noGauche].aqqu*aNoeuD[noDroit].aqqu;
		} else aNoeuD[noRacine].aqqu=1;//dc le aqqu d'un produit à 2 opérandes de type NoeudNombre sera non nul.
  	}
	//Assert2("ArtereDenombreR0",aNoeuD[noRacine].dequ<=aNoeuD[noRacine].aqqu,aNoeuD[noRacine].eta>=eVu);//C2 pr parcours de dag et non pas d'arbre.
}//ArtereDenombreR

long zArtereDenombreR(int uDag,int noRacine){
	//rend ds aNoeuD[noRacine].aqqu le nombre total de couvertures en excès dans le dag ou sous-dag de racine noRacine.
	//Titrer( sC2("zArtereDenombreR, dag n°",sEnt(uDag)) );
	zNoeudVisitehEnTouT=0;//d pr ArtereDenombreR et ArtereMarqueR
	ArtereDenombreR(uDag,noRacine);
	//t("zArtereDenombreR FINI");
	return(zNoeudVisitehEnTouT);
}//zArtereDenombreR

int nFeuilleEnTouT(int noRacine,int nEnquis){
	int nEnTout=0;
	if (aNoeuD[noRacine].typ!=NoeudNombre)
		nEnTout=nFeuilleEnTouT(aNoeuD[noRacine].nog,nEnquis)+nFeuilleEnTouT(aNoeuD[noRacine].nod,nEnquis);
	else nEnTout=(aNoeuD[noRacine].nog==nEnquis);
	return(nEnTout);
}//nFeuilleEnTouT

int bFeuillePisteR(int noRacine,int iFeuilleValeur,int nHauteur,int *pnOccurrence,int nPiste[]){
	//rend la piste qui mène à la nOccurrence-ième feuille de valeur iFeuilleValeur dans l'arbre virtuel 
	Assert1("bFeuillePisteR",noRacine>0);
	int bPister=kF;
	//te(" noFeuillePlacE noRacine",noRacine); tee("noRacine,noPere",noRacine,noPere);
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		if (!bPister){ 
			bPister=bFeuillePisteR(aNoeuD[noRacine].nog,iFeuilleValeur,nHauteur+1,pnOccurrence,nPiste);
		}if (!bPister) 
			bPister=bFeuillePisteR(aNoeuD[noRacine].nod,iFeuilleValeur,nHauteur+1,pnOccurrence,nPiste);
	}else if (aNoeuD[noRacine].nog==iFeuilleValeur){
		*pnOccurrence=*pnOccurrence-1;
		bPister=(*pnOccurrence==0);
		//if (bPister) t("SUCCESSSSSSSSSSSSSSS");
		if (bPister)
			nPiste[0]=nHauteur;//dc fait une fois et une seule
	}
	if (bPister)
		nPiste[nHauteur]=noRacine;//dc tous noeuds
	return(bPister);
}//bFeuillePisteR

void FeuillePisteR(int noRacine,int iFeuilleValeur,int nOccurrence,int nPiste[]){
	//rend la piste qui mène à la nOccurrence-ième feuille de valeur iFeuilleValeur dans l'arbre virtuel 
	Assert1("FeuillePisteR1",noRacine>0);
	int nOccurrenceCopie=nOccurrence;
	//VecteurRazer(nPiste,1,50);
	teee("FeuillePisteR:noRacine,iFeuilleValeur,nOccurrence",noRacine,iFeuilleValeur,nOccurrence);
	VecteurRazer(nPiste,1,knPisteMaX);
	int bPister=bFeuillePisteR(noRacine,iFeuilleValeur,1,&nOccurrenceCopie,nPiste);
	Assert2("FeuillePisteR2",bPister,nOccurrenceCopie==0);
	//VecteurVoir("nPiste",nPiste,1,nPiste[0]);
}//FeuillePisteR

int noFeuillePlacE(int noRacine,int iValeur,int *pnOccurrence){
	//tee("bFeuilleCarnulablE noRacine,iValeur",noRacine,iValeur);
	Assert1("noFeuillePlacE",noRacine>0);
	int nPlace=0;
	//te(" noFeuillePlacE noRacine",noRacine); tee("noRacine,noPere",noRacine,noPere);
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		if (nPlace==0 && *pnOccurrence>0) 
			nPlace=noFeuillePlacE(aNoeuD[noRacine].nog,iValeur,pnOccurrence);
		if (nPlace==0 && *pnOccurrence>0) 
			nPlace=noFeuillePlacE(aNoeuD[noRacine].nod,iValeur,pnOccurrence);
	}else if (aNoeuD[noRacine].nog==iValeur){
			//Titrer("Euraka");
			*pnOccurrence=(*pnOccurrence)-1;
			if (*pnOccurrence==0){
				//Titrer("GOTIT");
				nPlace=noRacine;
			}
		}
	return(nPlace);
}//noFeuillePlacE

void NoeudAffiche(char* sQuoi,int noNoeud){
	if (noNoeud!=0){
		if (aNoeuD[noNoeud].typ!=NoeudNombre){
			printf(" %3d%s=(%3d %c %3d)",noNoeud,sQuoi,aNoeuD[noNoeud].nog,sOperateuR[aNoeuD[noNoeud].typ],aNoeuD[noNoeud].nod);
		}else if (aNoeuD[noNoeud].nog!=0)
			if (kbLitteraliseR)
				printf("%s",sFormeFeuille(aNoeuD[noNoeud].nog));
			else printf(" %3d%s=%11d",noNoeud,sQuoi,aNoeuD[noNoeud].nog);
		else printf(" %3d%s={%3d %c %3d}",noNoeud,sQuoi,aNoeuD[noNoeud].nog,sOperateuR[aNoeuD[noNoeud].typ],aNoeuD[noNoeud].nod);
	}else printf(" %3d%s=%11s",noNoeud,sQuoi," Z  E  R  O");
	Ligne();
}//NoeudAffiche

char *sNoeudAffiche(char* sQuoi,int noNoeud){
	char *sAffiche;
	if (noNoeud!=0){
		if (aNoeuD[noNoeud].typ!=NoeudNombre){
			sAffiche=sC8(" ",sEntier(noNoeud,3),sQuoi,"=(",sEntier(aNoeuD[noNoeud].nog,3),sC(sOperateuR[aNoeuD[noNoeud].typ]),sEntier(aNoeuD[noNoeud].nod,3),")");
		}else if (aNoeuD[noNoeud].nog!=0)
			if (kbLitteraliseR)
				sAffiche=sFormeFeuille(aNoeuD[noNoeud].nog);
			else sAffiche=sC4(" ",sEntier(noNoeud,3),sQuoi,sEntier(aNoeuD[noNoeud].nog,3));
	}
	return(sAffiche);
}//sNoeudAffiche

int noNoeudAjouter(int noGauche,int noType,int noDroit){
	//teee("noType,noGauche,noDroit",noType,noGauche,noDroit);
	Assert3("noNoeudAjouter",bCroit(NoeudNombre,noType,NoeudDivision),bInteger(noGauche),bInteger(noDroit));
	int noAjouter=noNoeudLibrE();
	aNoeuD[noAjouter].typ=noType;
	aNoeuD[noAjouter].nog=noGauche;//c'est aussi la valeur d'une feuille
	aNoeuD[noAjouter].nod=noDroit;//c'est aussi la valeur d'une feuille
	aNoeuD[noAjouter].aqqu=0;
	aNoeuD[noAjouter].dequ=0;
	aNoeuD[noAjouter].fwa=0;
	aNoeuD[noAjouter].val=-1;//z; toute cellule libérée a un .val>=0
	//te("noAjouter",noAjouter);
	//NoeudVoir("noAjouter",noAjouter);
	Assert2("noNoeudAjouter9",noAjouter>0,bCroit(NoeudNombre,aNoeuD[noAjouter].typ,NoeudDivision));
	return(noAjouter);
}//noNoeudAjouter

void NoeudAMORCER(){
	//amorce le présent module une fois pour toutes
	Assert3("NoeudAMORCER",!bNoeudAmorceR,bFrontiere8(sizeof(tNoeuD)),kuSegmentAnnoncE>1);//car eta utilise déjà les valeurs 0 et 1.
	bNoeudAmorceR=kV;
	//printf("NoeudAMORCER:sizeof(eNoeuD):%lu\n",sizeof(tNoeuD));
	NoeudINITIALISER();
	//tb("bNoeudAmorceR",bNoeudAmorceR);
}//NoeudAMORCER

void NoeudArboreR(int noRacine,int nTabulation,int bAfficher){
	const int kbEtat=kF;//pr afficher .eta du noeud
	const int kuNoeudNumero=4*0;//encombrement du numéro du noeud —— ou 4*0 si absent
	const int kbNoeudOccurrence=kF;//pr afficher le nombre d'occurrences de ce noeud
	const int kbEffectifs=kF;//pr afficher les effectifs large et strict
	const int kuOperateur=1;// "*" ou "+" valeur min:1
	const int knBlancSeparateur=3;//0 au minimum
	const int kbNoeudInterneEncombrement=kuOperateur+kuNoeudNumero+4*kbNoeudOccurrence+2*kbEffectifs+2*kbEtat*kbEffectifs;
	const int kuEspacement=knBlancSeparateur+kbNoeudInterneEncombrement;
	int nEffectif;
	zNoeudArboreR++;
	if (!bAfficher)
		aNoeuD[abs(noRacine)].fwa++;
	if (0 || zNoeudArboreR%kE8==0)
		teee("noRacine,zNoeudArboreR,nTabulation",noRacine,zNoeudArboreR,nTabulation);
	Assert2("NoeudArboreR",noRacine!=0,bCroit(NoeudNombre,aNoeuD[abs(noRacine)].typ,NoeudDivision));
	if (aNoeuD[abs(noRacine)].typ>NoeudNombre){
		if (bAfficher){
			printf("%c%s",sOperateuR[aNoeuD[abs(noRacine)].typ],sE(kuOperateur-1));
			if (kbEffectifs) {
				//printf("%2d%2d",aNoeuD[abs(noRacine)].aqqu%100,aNoeuD[abs(noRacine)].dequ%100);
				nEffectif=aNoeuD[abs(noRacine)].dequ%100;
				printf("%2d",nEffectif);
				if (kbEtat) printf(":%1d",aNoeuD[abs(noRacine)].eta);
				printf("%c",(nEffectif>0)?'@':' ');
			}
			if (kuNoeudNumero>0) printf("%s",sEntier(noRacine,kuNoeudNumero));
			if (kbNoeudOccurrence)//(%2d)"=knCaractereEnSus caractères en supposant #occurrences<100
				printf("%s",(aNoeuD[abs(noRacine)].fwa>1)? sP(sEntier(aNoeuD[abs(noRacine)].fwa,2)): sE(4));
			if (knBlancSeparateur>0)//ce test gagne un peu de tps au moment d'afficher les arborescences géantes
				printf("%s",sE(knBlancSeparateur));
		}
		NoeudArboreR(aNoeuD[abs(noRacine)].nog,nTabulation+1,bAfficher);
		if (kV || aNoeuD[aNoeuD[abs(noRacine)].nod].typ!=NoeudNombre || bSegmentElemenT(aNoeuD[aNoeuD[abs(noRacine)].nod].nog) ){
			if (bAfficher) printf("\n%s",sE(nTabulation*kuEspacement));
			NoeudArboreR(aNoeuD[abs(noRacine)].nod,nTabulation+1,bAfficher);
		}
	}else if (bAfficher){ 
		if (kbLitteraliseR)
			printf("%s",sFormeFeuille(aNoeuD[abs(noRacine)].nog));
		else if (1 || bSegmentElemenT(aNoeuD[abs(noRacine)].nog) )
			//printf("%4d %d",noRacine,aNoeuD[abs(noRacine)].nog);
			printf("%d",aNoeuD[abs(noRacine)].nog);
		else printf("…");
	}
}//NoeudArboreR
//                                                            ***
//012345678901234567890123456789012345678901234567890123456789
void NoeudArborer(char* sTitre,int noRacine){
	//affiche tous les noeuds de l'arbre de racine noRacine
	int nFwaMax,noNoeud,nPris,nTabulation;
	//Appel0("NoeudArborer");
		if ( !bNoeudNul(abs(noRacine)) ){
			for (nPris=nNoeudPris(),noNoeud=1;noNoeud<=nPris;noNoeud++)
				aNoeuD[noNoeud].fwa=0;
			if (nChaineLg(sTitre)>0) printf("%s:\n",sTitre);
				zNoeudArboreR=0;
				NoeudArboreR(noRacine,nTabulation=1,!k1Afficher);//comptabilise les occurrences des numéros de noeuds ds le champ fwa.
				zNoeudArboreR=0;
				NoeudArboreR(abs(noRacine),nTabulation=1,k1Afficher);//affiche l'arborescence verticalement
			printf("\n");
			if(0){
				for (noNoeud=1;noNoeud<=nPris;noNoeud++)
					printf("%s***\n",sE(aNoeuD[noNoeud].fwa));
				for (nFwaMax=0,noNoeud=1;noNoeud<=nPris;noNoeud++)
					nFwaMax=iSup(nFwaMax,aNoeuD[noNoeud].fwa);
				te("nFwaMax",nFwaMax);
			}
		}
	//Appel1("NoeudArborer");
}//NoeudArborer

int nNoeudChemiN(int noRacine){
	//rend le nombre de chemins distincts depuis noRacine jsq une feuille distale
	int nChemin=0,nDroit,nGauche;
	zNoeudVisitehEnTouT++;
	if (aNoeuD[noRacine].eta==0){
		aNoeuD[noRacine].eta=1;
		if (aNoeuD[noRacine].typ>NoeudNombre){
			nGauche=nNoeudChemiN(aNoeuD[noRacine].nog);
			nDroit=nNoeudChemiN(aNoeuD[noRacine].nod);
			if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction)
				nChemin=nGauche+nDroit;
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision)
				nChemin=nGauche*nDroit;
		} else nChemin=aNoeuD[noRacine].nog!=0;//ie non nul
		aNoeuD[noRacine].aqqu=nChemin;
	} else nChemin=aNoeuD[noRacine].aqqu;
	return(nChemin);
}//nNoeudChemin

int nNoeudChemin(int noRacine){
	//rend le nombre de chemins distincts depuis noRacine jsq une feuille distale
	int nChemin;
	long zComplexiteh=1;
	Assert1("nNoeudChemin",noRacine>0);
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		NoeudVerifieR(noRacine,kV);
			nChemin=nNoeudChemiN(noRacine);
		NoeudVerifieR(noRacine,kF);
		zComplexiteh=zNoeudVisitehEnTouT;
	}
	ld(zComplexiteh);
	return(nChemin);
}//nNoeudChemin

void NoeudConfliteR(int noRacine,int nOccurrence[20]){
	if (aNoeuD[noRacine].typ>NoeudNombre){
		NoeudConfliteR(aNoeuD[noRacine].nog,nOccurrence);
		NoeudConfliteR(aNoeuD[noRacine].nod,nOccurrence);
	}else {nOccurrence[aNoeuD[noRacine].nog-1]++;
		//te("aNoeuD[noRacine].nog",aNoeuD[noRacine].nog);
		}
}//NoeudConfliteR

void NoeudConfliter(int noRacine,int nOccurrence[20]){
	VecteurRazer(nOccurrence,1,19);
	NoeudConfliteR(noRacine,nOccurrence);//affiche l'arborescence verticalement
	//VecteurVoir("nOccurrence dans NoeudConfliter",nOccurrence,1,19);
	//comparer les feuilles 2 à 2 et dénoncer les conflits éventuels
}//NoeudConfliter

int nNoeudCouplagE(int uMode,int nozAieul,int nozGrandPere,int nozPere,int noRacine,int nHauteur){
	//rend le nombre de couplages parfaits dans le dag de racine noRacine,ie de pariations valides.
	int mCouple=-1,noGauche,noDroit,uAieul,uGrandPere,uPere,uRacine,bBanni;
 	//Assert1("nNoeudCouplagE0",nHauteur==1 && nozPere==0 || nHauteur>1 && aNoeuD[nozPere].typ==NoeudProduit);
	if (aNoeuD[noRacine].typ>NoeudNombre){
		noGauche=aNoeuD[noRacine].nog;
		noDroit=aNoeuD[noRacine].nod;
		if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision) {
			mCouple=nNoeudCouplagE(uMode,nozGrandPere,nozPere,noRacine,noGauche,nHauteur+1);
			if (nozPere){//=> nHauteur>1 => nozPere ≠ 0 ET aNoeuD[nozPere].typ==NoeudProduit
				uRacine=abs(iOperandeDroiT(noRacine));
				uPere=abs(iOperandeDroiT(nozPere));
				if (nozGrandPere) uGrandPere=abs(iOperandeDroiT(nozGrandPere));else uGrandPere=0;
				if (nozAieul) uAieul=abs(iOperandeDroiT(nozAieul));else uAieul=0;
				bBanni=bSegmentBannI1(uRacine);//invalide tous les arcs interdits
				if (bImpair(nHauteur))//invalider les séquences de couplages impropres,ie telles que deux couplages ont un sommet commun
					bBanni=bBanni || (uMode>1) && bSegmentBannI2(uPere,uRacine);
				else bBanni=bBanni || ( uPere!=uRacine);//ce n'est pas un collier
				bBanni=bBanni || nozGrandPere && nozAieul && (uMode>2) && bSegmentBannI3(uAieul,uRacine);
				if (bBanni)
					mCouple=0;
			}
		} else mCouple=nNoeudCouplagE(uMode,nozAieul,nozGrandPere,nozPere,noGauche,nHauteur)+nNoeudCouplagE(uMode,nozAieul,nozGrandPere,nozPere,noDroit,nHauteur);// vu typ==NoeudAddition
	} else mCouple=1;
 	Assert1("nNoeudCouplagE1",mCouple>=0);
	return(mCouple);
}//nNoeudCouplagE

int nNoeudCouplage(int noRacine,int bDroite){
	//rend le nombre de couplages présents dans le dag de racine noRacine
	int nozAieul,nozGrandPere,nozPere,nCouplage;
	char *ksCouplage="séquences de paires,couplages parfaits,couplages parfaits contraints";
	const int kuMode=3;
	nCouplage=nNoeudCouplagE(kuMode,nozAieul=0,nozGrandPere=0,nozPere=0,noRacine,1);
	printf("Nombre total de %s: %d.\n",sItem(ksCouplage,kuMode),nCouplage);
	return(nCouplage);
}//nNoeudCouplage

void NoeudCouvrir(int uDag,int noRacine,int nPivot,int *pnPlus,int *pnMoins,long *pzComplexiteh){
	//rend nbre total couvertures dénombrées (*pnPlus) et décomptées (*pnMoins) ds le dag de racine noRacine. Accroît pzComplexiteh.
	#define kuComplexitehMax 2
	const int kbVoir=kF;
	int nChemin,noNoeud;
	int nPris=nNoeudPris();
	long zComplexiteh[1+kuComplexitehMax];
	char *sTitre=sC2("Dag n°",sEnt(uDag));
	//Appel0(sC2("NoeudCouvrir, dag n°",sEnt(uDag)));
		*pnPlus=*pnMoins=0;
		VekteurRazer(zComplexiteh,1,kuComplexitehMax);
		if (aNoeuD[noRacine].typ>NoeudNombre){
			if (kbVoir)printf("%s:\n",sTitre);
			for (noNoeud=1;noNoeud<=nPris;noNoeud++){
				aNoeuD[noNoeud].dequ=0;
				aNoeuD[noNoeud].aqqu=0;
				aNoeuD[noNoeud].eta=0;
				aNoeuD[noNoeud].fwa=0;//superflu
			}
			//NoeudArborer(sTitre,noRacine);
			//(aqqu,dequ):=nombre total de couvertures (dénombrées,décomptées) pr tout noeud pertinent,notamment en noRacine
				zComplexiteh[1]=zArtereDenombreR(uDag,noRacine);//rend dans aNoeuD[noRacine].aqqu le .
				d(aNoeuD[noRacine].aqqu);
				//NoeudArborer(sTitre,noRacine);
				zComplexiteh[2]=zArtereDebouteR(uDag,noRacine,nPivot);
	if (kbVoir)
printf("Noeuds pris() vs complexités: %s vs [%s, %s, %s].\n",sPar3(nPris),sPar3(zComplexiteh[1]),sPar3(zComplexiteh[2]),sPar3(zComplexiteh[3]));
			*pnMoins=aNoeuD[noRacine].dequ;//total couvertures valides
			*pnPlus=0;//total couvertures
			nChemin=*pnPlus-*pnMoins;
			//d2(*pnPlus,*pnMoins);
		} else nChemin=aNoeuD[noRacine].nog!=0;//dc non nul si réduit à 1 NoeudNombre.
		if (kbVoir) printf("Nombre de connexité %d: nPlus=%d,nMoins:%d,nChemin=%d.\n",uDag,*pnPlus,*pnMoins,nChemin);
		*pzComplexiteh+=yVekteurSomme(zComplexiteh,1,kuComplexitehMax);
		//d3(*pnMoins,*pnPlus,abs(nChemin));
		//ld(zComplexiteh[2]);
	//Appel1(sC2("NoeudCouvrir, dag n°",sEnt(uDag)));
}//NoeudCouvrir

void NoeudCouvrirTouT(int noRacine){//séquences 345,manque 456
	//rend le nombre total de couvertures strictes (ie sans ncSegment) dans le dag ou sous-dag de racine noRacine.
	int noGauche,noDroit;
	enum eEtat {eRaz,eVu,eAlpha,eBeta,eGamma};
	Assert2("NoeudCouvrirTouT",noRacine>0,bCroit(NoeudNombre,aNoeuD[noRacine].typ,NoeudSoustraction));
 	if (aNoeuD[noRacine].eta==eRaz){//sinon,le dag sera déployé en arbre,lequel sera parcouru en tps exponentiel en pire cas. 
		zNoeudVisitehEnTouT++;
		//d2(noRacine,aNoeuD[noRacine].fwa);
		aNoeuD[noRacine].eta=eVu;//d; >0 pr parcourir un dag et non pas un arbre.
 		if (aNoeuD[noRacine].typ!=NoeudNombre){
			NoeudCouvrirTouT(noGauche=aNoeuD[noRacine].nog);
			NoeudCouvrirTouT(noDroit=aNoeuD[noRacine].nod);
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
				aNoeuD[noRacine].aqqu=aNoeuD[noGauche].aqqu;//d
				//aNoeuD[noRacine].dequ=aNoeuD[noGauche].dequ;//d
				Assert1("NoeudCouvrirTouT 123",aNoeuD[noDroit].typ==NoeudNombre);//dc .nog mémorise le poids de l'arc.
				switch (aNoeuD[noDroit].nog) {
					case 3:			aNoeuD[noRacine].eta=eAlpha;
									nNoeudCouvrirTouT=aNoeuD[noRacine].aqqu;
									Assert1("NoeudCouvrirTouT case 3",nNoeudCouvrirTouT>0);
									break;
					case 4:			aNoeuD[noRacine].eta=(aNoeuD[noGauche].eta==eAlpha)? eBeta: eVu;
									//d(noRacine);
									//if (aNoeuD[noRacine].eta==eBeta) Assert1("NoeudCouvrirTouT case 4",nNoeudCouvrirTouT>0);
									break;
					case 5:			aNoeuD[noRacine].eta=(aNoeuD[noGauche].eta==eBeta)? eGamma: eVu;
									if (aNoeuD[noGauche].eta==eBeta) aNoeuD[noRacine].dequ=nNoeudCouvrirTouT;
									nNoeudCouvrirTouT=0;
									break;
					default:		break;
				}//switch
			}
			else if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction){
				//aNoeuD[noRacine].dequ=aNoeuD[noGauche].dequ+aNoeuD[noDroit].dequ;
				aNoeuD[noRacine].aqqu=aNoeuD[noGauche].aqqu+aNoeuD[noDroit].aqqu;
				//Assert2("NoeudCouvrirTouT 4",aNoeuD[noGauche].eta<=3,aNoeuD[noDroit].eta<=3);//? enquête
				aNoeuD[noRacine].eta=iSup(aNoeuD[noGauche].eta,aNoeuD[noDroit].eta);
				if (aNoeuD[noRacine].eta==eGamma)
					aNoeuD[noRacine].eta=eVu;
			}
		} else aNoeuD[noRacine].aqqu=1;
  	}
	//Assert2("NoeudCouvrirTouT0",aNoeuD[noRacine].dequ<=aNoeuD[noRacine].aqqu,aNoeuD[noRacine].eta>=eVu);//C2 pr parcours de dag et non pas d'arbre.
}//NoeudCouvrirTouT

void NoeudDagueR(int bUniquer,int noRacine,int *pnoPlexe){
	//factorise feuilles identQ en 2 tps. Appel 1:noPlacE[val feuille]:=adrS feuille.
	//Appel 2:factorise les feuilles de mm noPlacE. Total feuilles distinctes ds noPlacE[0]
	int uClef;
	Assert1("NoeudDagueR",noRacine>0);
	int noDroit,noGauche,noPlexe;
	noPlexe=noRacine;
	//tee("NoeudDagueR",aNoeuD[noRacine].nog,nPlaceEnTout=noPlacE[0]);
	if (aNoeuD[noRacine].typ==NoeudNombre){
		uClef=aNoeuD[noRacine].nog;
		//te("uClef",uClef);
	}
	if (aNoeuD[noRacine].typ>NoeudNombre){
		NoeudDagueR(bUniquer,aNoeuD[noRacine].nog,&noGauche);
		NoeudDagueR(bUniquer,aNoeuD[noRacine].nod,&noDroit);
		if (!bUniquer){
			noPlexe=noNoeudLibrE();
			aNoeuD[noPlexe].nog=noGauche;
			aNoeuD[noPlexe].nod=noDroit;
			aNoeuD[noPlexe].typ=aNoeuD[noRacine].typ;
		}
	}else if (bUniquer){
		if (noPlacE[uClef]==0){
			noPlacE[uClef]=noRacine;//stocke ds noPlacE le nom du premier noeud qui mémorise la valeur
			noPlacE[0]++;
		}
	}else if (noPlacE[uClef]>0)
		noPlexe=noPlacE[uClef];
		else Assert1("NoeudDagueR8",0);
	*pnoPlexe=noPlexe;
}//NoeudDagueR

int noNoeudDaguer(int noRacine){
	//rend la nouvelle racine d'un DAG qui décrit avec des feuilles uniques l'arbre ou dag de racine noRacine
	const int kbUniquer=kV; 
	int noDaguer=noRacine;
	Assert1("noNoeudDaguer",noRacine>0);
	//Appel0("noNoeudDaguer");
		VecteurRazer(noPlacE,1,kuPlaceLiM-1);
		noPlacE[0]=0;//a
		NoeudDagueR( kbUniquer,noRacine,&noDaguer);
		VecteurVoir("noPlacE",noPlacE,1,15);
		//Titrer("cépassé");NoeudLister("AVANT noNoeudDaguer",noDaguer);
		NoeudDagueR(!kbUniquer,noRacine,&noDaguer);
		//Titrer("céfini");NoeudLister("APRES noNoeudDaguer",noDaguer);
	//Appel1("noNoeudDaguer");
	return(noDaguer);
}//noNoeudDaguer

void NoeudDerouteR(int iSoliton){
	//accumule dans chaque feuille distale atteignable depuis noRacine le nombre de routes contenant 2 iSoliton Ou plus. PAS FINI.
	int nUn,nPlus,nCardinal,uF,noRacine;
	zNoeudVisitehEnTouT++;
	while (nCardinal=nDequeCardinal(),nCardinal>0){
		printf("Niveau %2d ",++nNoeudDerouteR);
		for (uF=1;uF<=nCardinal || !bLigne("");uF++){
			noRacine=sDequeDefiler();
			printf("%8d",noRacine);
			nUn=aNoeuD[noRacine].aqqu;
			nPlus=aNoeuD[noRacine].aqqu;
			if (1 || aNoeuD[noRacine].eta==0){
				aNoeuD[noRacine].eta=1;
				if (aNoeuD[noRacine].typ==NoeudAddition)
					PiedEtendrePartouT(noRacine);
				if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision)
					if (aNoeuD[aNoeuD[noRacine].nog].typ==NoeudAddition)
						PiedEtendrePartouT(aNoeuD[noRacine].nog);
					else DequeEnfiler(aNoeuD[noRacine].nog);
			};
		}//for uF
	}
}//NoeudDerouteR

void NoeudDerouter(int noRacine,int iSoliton){
	//accumule dans chaque feuille distale atteignable depuis noRacine le nombre de routes contenant 2 iSoliton Ou plus. PAS FINI.
	int noNoeud;
	//Appel0("NoeudDerouter");
		//d(noRacine);
		zNoeudVisitehEnTouT++;
		for (nNoeudVerifieR=nNoeudPris(),noNoeud=1;noNoeud<=nNoeudVerifieR;zNoeudVisitehEnTouT++,noNoeud++)
			aNoeuD[noNoeud].eta=aNoeuD[noNoeud].aqqu=aNoeuD[noNoeud].dequ=0;
		DequeAllouer(noRacine);
			PiedEtendrePartouT(noRacine);
			//d(nDequeCardinal());
			nNoeudDerouteR=0;
			NoeudDerouteR(iSoliton);
		DequeAllouer(0);
	//Appel1("NoeudDerouter");
}//NoeudDerouter

void NoeudDescendrE(int noRacine,int noDescendance[]){
	//accumule dans noDescendance les successeurs de noRacine de type NoeudProduit ou NoeudNombre en sautant les noeuds de type NoeudAddition.
	d2(noRacine,noDescendance[0]);
	if (aNoeuD[noRacine].typ==NoeudAddition){
		NoeudDescendrE(aNoeuD[noRacine].nog,noDescendance);
		NoeudDescendrE(aNoeuD[noRacine].nod,noDescendance);
	}
	if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
		Assert1("NoeudDescendrE0",noDescendance[0]<100);
		noDescendance[++noDescendance[0]]= noRacine;
		NoeudDescendrE(aNoeuD[noRacine].nog,noDescendance);
	}
	if (aNoeuD[noRacine].typ==NoeudNombre){
		Assert1("NoeudDescendrE1",noDescendance[0]<100);
		noDescendance[++noDescendance[0]]= - noRacine;
	}
}//NoeudDescendrE

void NoeudEnumereR(int bAfficher,int uDagNumero,int noRacine,int uHauteur,int iPoidsMin,int iPoidsMax,int iPoids[]){
	//cf NoeudEnumerer;iPoids[] est la pile courante de cardinal iPoids[0].
	int uH,bElementaire,uProfondeur,bSegment;
	uProfondeur=iPoids[0];
	int nCopie[1+uProfondeur];
	zNoeudVisitehEnTouT++;
	if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
		iPoids[uHauteur]=iOperandeDroiT(noRacine);
		NoeudEnumereR(bAfficher,uDagNumero,aNoeuD[noRacine].nog,uHauteur+1,iPoidsMin,iPoidsMax,iPoids);
	}
	if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction){
		NoeudEnumereR(bAfficher,uDagNumero,aNoeuD[noRacine].nog,uHauteur,iPoidsMin,iPoidsMax,iPoids);
		NoeudEnumereR(bAfficher,uDagNumero,aNoeuD[noRacine].nod,uHauteur,iPoidsMin,iPoidsMax,iPoids);
	}
	if (aNoeuD[noRacine].typ==NoeudNombre){
		iPoids[uHauteur]=aNoeuD[noRacine].nog;
		Assert1("NoeudEnumereR hauteur",uHauteur==uProfondeur);
		//d(uHauteur);
		if (uHauteur==uProfondeur){
			//VecteurVoir("iPoids",iPoids,1,nProfondeur);
			bSegment=kF;
			//bSegment=bSegmentPresenT(iPoids);
			nNoeudEnumererEnTroP[uDagNumero]+=bSegment;
			nNoeudEnumererEnTouT[uDagNumero]++;
			if (nNoeudEnumererEnTouT[uDagNumero]%kE5==0)
				printf("nNoeudEnumererEnTouT: %s.\n",sPar3(nNoeudEnumererEnTouT[uDagNumero]));
			if (!bSegment){//pas de segment interdit
				VecteurCopier(iPoids,1,uProfondeur,nCopie);
				VecteurTrier(nCopie,1,uProfondeur);
				bElementaire=!bVecteurDoublon(nCopie,1,uProfondeur);
bElementaire=kV;
				nNoeudEnumererElementairE[uDagNumero]+=bElementaire;
			}
			if (1 && !bSegment && bElementaire){
				printf("%sC[%d,%4d]=",sTab(1),uDagNumero,nNoeudEnumererEnTouT[uDagNumero]);
					for (uH=1;uH<=uHauteur || !bLigne(".\n");uH++)
						printf(" %2d",iPoids[uHauteur-uH+1]);
				//printf("    %s.\n",(bSegment)? "            REFUSÉE": "acceptée");
			}
		}
		iPoids[uHauteur]=0;
	}
}//NoeudEnumereR

void NoeudEnumererAvecDequE(int bAfficher,int uDagNumero,int noRacine,int iPoidsMin,int iPoidsMax,int uProfondeur){
	//variante de NoeudEnumerer qui ne descend dans le dag que les chemins élémentaires sans REPETITION d'éléments
	int bEmpiler,uH,bSegment,iP;
	int nOffset=1-iPoidsMin;
	Assert1("NoeudEnumererAvecDequE",nOffset+iPoidsMin==1);
	int iPoids[1+uProfondeur];
	//DequeVoirPile("PILE: ");
	zNoeudVisitehEnTouT++;
	if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
		bEmpiler=bDequeEmpiler(nOffset+iOperandeDroiT(noRacine));
		if (bEmpiler){
			NoeudEnumererAvecDequE(bAfficher,uDagNumero,aNoeuD[noRacine].nog,iPoidsMin,iPoidsMax,uProfondeur);
			DequeDepiler();
		}
	}
	else if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction){
		NoeudEnumererAvecDequE(bAfficher,uDagNumero,aNoeuD[noRacine].nog,iPoidsMin,iPoidsMax,uProfondeur);
		NoeudEnumererAvecDequE(bAfficher,uDagNumero,aNoeuD[noRacine].nod,iPoidsMin,iPoidsMax,uProfondeur);
	}
	else if (aNoeuD[noRacine].typ==NoeudNombre){
		bEmpiler=bDequeEmpiler(nOffset+aNoeuD[noRacine].nog);
		//d(uHauteur);
		if (bEmpiler){
			//DequeVoirPile("PILE TERMINALE: ");
			//d(uProfondeur);
			bSegment=kF;
			DequePileCopier(iPoids);//dont cardinal en nPile[0] 
			for (iP=1;iP<=uProfondeur;iP++)
				iPoids[iP]-=nOffset;
			iPoids[0]=uProfondeur;
			if (0){//bSegment:=couverture refusée cause présence de segment interdit
				bSegment=bSegmentPresenT1(iPoids);
				bSegment=bSegment || bSegmentPresenT2(iPoids);
				//printf("    %s.\n",(bSegment)? "            REFUSÉE": "acceptée");
			}
			nNoeudEnumererEnTroP[uDagNumero]+=bSegment;
			nNoeudEnumererElementairE[uDagNumero]+=1-bSegment;
			nNoeudEnumererEnTouT[uDagNumero]++;
			if (nNoeudEnumererEnTouT[uDagNumero]%kE5==0){
				printf("nNoeudEnumererEnTouT: %s.\n",sPar3(nNoeudEnumererEnTouT[uDagNumero]));
			}
			iPoids[0]=uProfondeur;
			if (1 || !bSegment){
				//d2(uProfondeur,nOffset);
				nNoeudEnumererTotaL[uDagNumero]++;
				printf("%sC[%d,%4d]=",sTab(1),uDagNumero,nNoeudEnumererTotaL[uDagNumero]);
					for (uH=1;uH<=uProfondeur || !bLigne(".\n");uH++)
						printf("%3d",iPoids[uH]);
			}
			DequeDepiler();
		}
	}
}//NoeudEnumererAvecDequE

void NoeudEnumerer(int uDagNumero,int nProfondeur,int noRacine,int bElementaire,int iPoidsMin,int iPoidsMax,int *pnCheminValide,int *pnCheminInvalide){
	//rend ds pnCheminEnTout/pnCheminEnTrop le nombre de chemins depuis noRacine acceptés/refusés;si kbAfficher,affiche ces chemins et statue.
	int bAfficher,uArc,nElementaire,nTps;
	int iPoids[1+nProfondeur];
	Assert2("NoeudEnumerer",bCroit(1,uDagNumero,kuComposanteMaX),iPoidsMin<iPoidsMax);
	bAfficher=nNoeudEnumereR[uDagNumero]>0;
	bAfficher=kV;
	//Appel0(sC4b("NoeudEnumerer, composante",sEnt(uDagNumero),"profondeur",sEnt(nProfondeur)));
		//VecteurVoir("nNoeudEnumereR",nNoeudEnumereR,1,2);
		//d2(uDagNumero,bAfficher);
//NoeudArborer(sC2b("NoeudEnumerer,dag",sEnt(uDagNumero)),noRacine);
		Titrer(sC6b("NoeudEnumerer, composante",sEnt(uDagNumero),"profondeur",sEnt(nProfondeur),"sur",(!bElementaire)? "parcours non élémentaire": "parcours élémentaire"));
		*pnCheminValide=*pnCheminInvalide=0;
		if (aNoeuD[noRacine].typ>NoeudNombre){
			VecteurRazer(iPoids,1,nProfondeur);
			iPoids[0]=nProfondeur;
			if (0)
				for (printf("\n%sNuméro de l'arc: ",sTab(3)),uArc=1;uArc<=nProfondeur || !bLigne("");uArc++)
					printf(" %2d",uArc);
			VecteurRazer(nNoeudEnumererEnTouT,0,kuComposanteMaX);
			VecteurRazer(nNoeudEnumererEnTroP,0,kuComposanteMaX);
			VecteurRazer(nNoeudEnumererElementairE,0,kuComposanteMaX);
			VecteurRazer(nNoeudEnumererTotaL,0,kuComposanteMaX);
			//d3(iPoidsMin,iPoidsMax,nProfondeur);
			DequeAllouer(iPoidsMax-iPoidsMin+1);
				nTps=nChrono(kV);
					zNoeudVisitehEnTouT=0;
					if (bElementaire)//énumérer tous les chemins élémentaires
						NoeudEnumererAvecDequE(bAfficher,uDagNumero,noRacine,iPoidsMin,iPoidsMax,nProfondeur);
					else NoeudEnumereR(bAfficher,uDagNumero,noRacine,1,iPoidsMin,iPoidsMax,iPoids);//chemins avec ou sans répétition d'arcs
				nTps=nChrono(kF);
			DequeAllouer(0);
			*pnCheminInvalide=nNoeudEnumererEnTroP[uDagNumero];
			*pnCheminValide=nNoeudEnumererEnTouT[uDagNumero]-nNoeudEnumererEnTroP[uDagNumero];
			nElementaire=nNoeudEnumererElementairE[uDagNumero];
			//tee("*pnCheminInvalide,*pnCheminValide",*pnCheminInvalide,*pnCheminValide);
			if (0 && nElementaire>0){
				printf("Le dag n°%d %s %s.\n",uDagNumero,(nElementaire)?"a":"n'a",sPluriel0(nElementaire,"couverture$ élémentaire$",k1Feminin));
				ld3(nTps,zNoeudVisitehEnTouT,zPuissance(nProfondeur,4));
			}
		}
	//Appel1(sC4b("NoeudEnumerer, composante",sEnt(uDagNumero),"profondeur",sEnt(nProfondeur)));
}//NoeudEnumerer

int iNoeudEvalueR(int noRacine,int bUn){
	Assert1("iNoeudEvalueR",noRacine>0);
	int iEvaluer=0,iGauche,iDroit;
	if (aNoeuD[noRacine].eta==0){
		aNoeuD[noRacine].eta==1;
		if (aNoeuD[noRacine].typ>NoeudNombre){
			iGauche=iNoeudEvalueR(aNoeuD[noRacine].nog,bUn);
			iDroit=iNoeudEvalueR(aNoeuD[noRacine].nod,bUn);
			if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction)
				iEvaluer=iGauche+iDroit;
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision)
				iEvaluer=iGauche*iDroit;
		}else iEvaluer=(bUn)? iInf(1,abs(aNoeuD[noRacine].nog)) : aNoeuD[noRacine].nog;
		aNoeuD[noRacine].aqqu=iEvaluer;
	}else iEvaluer=aNoeuD[noRacine].aqqu;
	return(iEvaluer);
}//iNoeudEvalueR

int iNoeudEvaluer(int noRacine,int bUn){
	//évalue le dag;attribue la valeur 1 à toutes feuille non nulle ssi bUn est vrai.
	Assert1("NoeudEvaluer",noRacine>0);
	int iEvaluer=0;
	//Appel0("iNoeudEvaluer");
		//te("iNoeudEvaluer:noRacine",noRacine);
		NoeudVerifieR(noRacine,kV);
			iEvaluer=iNoeudEvalueR(noRacine,bUn);
		NoeudVerifieR(noRacine,kF);
		//d(iEvaluer);
	//Appel1("iNoeudEvaluer");
	return(iEvaluer);
}//iNoeudEvaluer

int noNoeudFeuiller(int iFeuilleValeur){
	Assert1("noNoeudFeuiller",0);
	int noFeuiller=noNoeudLibrE();
	aNoeuD[noFeuiller].typ=NoeudNombre;
	aNoeuD[noFeuiller].nog=aNoeuD[noFeuiller].nod=iFeuilleValeur;
	aNoeuD[noFeuiller].aqqu=aNoeuD[noFeuiller].fwa=0;
	NoeudVoir("noFeuiller",noFeuiller);
	return(noFeuiller);
}//noNoeudFeuiller

void NoeudFormuleR(int noRacine){
	//affiche la formule parenthèsée
	Assert1("NoeudFormuleR",noRacine>0);
	if (noRacine!=0){
		if (aNoeuD[noRacine].typ!=NoeudNombre){
			printf("(");
				NoeudFormuleR(aNoeuD[noRacine].nog);
				printf("%c",sOperateuR[aNoeuD[noRacine].typ]);
				NoeudFormuleR(aNoeuD[noRacine].nod);
			printf(")");
		}else if (kbLitteraliseR)
			printf("%s",sFormeFeuille(aNoeuD[noRacine].nog));
		else printf("%d",aNoeuD[noRacine].nog);
	}
}//NoeudFormuleR

void NoeudFormuler(char* sTitre,int noRacine){
	//affiche la formule parenthèsée
	printf("%s depuis NoeudFormuler():\n",sTitre);
		Assert1("NoeudFormuler",noRacine>0);
		NoeudFormuleR(noRacine);
	printf(".\n");
}//NoeudFormuler

void NoeudINITIALISER(){
	int uN;
	Assert1("NoeudINITIALISER",bNoeudAmorceR);
	//créer une liste chainée de noeuds libres
		for (uN=1;uN<=knNoeudMaX;uN++){
			if (uN%kE7==0)
				printf("Cellules à initialiser depuis NoeudINITIALISER: %9s.\n",sPar3(knNoeudMaX-uN+1));
			aNoeuD[uN].typ=-1;
			aNoeuD[uN].nog=0;
			aNoeuD[uN].nod=0;
			aNoeuD[uN].val=uN+1;
			aNoeuD[uN].fwa=0;
		}
		aNoeuD[knNoeudMaX].val=0;
	iNoeuD=1;
	nPriS=0;
	VecteurRazer(qArtereDebouteR,1,2);
	VecteurRazer(nNoeudEnumereR,1,2);
}//NoeudINITIALISER

void NoeudInvalideAfficher(){
	SegmentAfficheR();
}//NoeudInvalideAfficher

void NoeudInvalideArc(int iArc1,int iArc2,int *pnSegmentEnTout){
	//si pas déjà ajouté, incrémente *pnSegmentEnTout et ajoute le nouveau segment à l'index *pnSegmentEnTout.
	int bRangValide=bCroit(0,*pnSegmentEnTout,kuSegmentLiM-1);
	if (!bRangValide) d2(*pnSegmentEnTout,kuSegmentLiM);
	Assert1("NoeudInvalider",bRangValide);// $
	if ( !bSegmenConnU(iArc1,iArc2,0,*pnSegmentEnTout) ){
		nSegmentMaX=*pnSegmentEnTout+1;
		iSegmenT[nSegmentMaX][1]=iArc1;//progression en sens DIRECT utile pour le code interne
		iSegmenT[nSegmentMaX][2]=iArc2;
		iSegmenT[nSegmentMaX][3]=0;
		*pnSegmentEnTout=nSegmentMaX;
		if (1)
			printf("Segment invalide n°%3d de poids (%3d,%3d).\n",nSegmentMaX,iArc1,iArc2);
	}
}//NoeudInvalideArc

void NoeudInvalider(int sX,int sY,int sZ,int sT,int iPoidsXY,int iPoidsYZ,int iPoidsZT,int *pnSegmentEnTout){
	//si pas déjà ajouté, incrémente *pnSegmentEnTout et ajoute le nouveau segment à l'index *pnSegmentEnTout.
	int nPoidsXY=nAbs(iPoidsXY);
	int nPoidsYZ=nAbs(iPoidsYZ);
	int nPoidsZT=nAbs(iPoidsZT);
	int bRangValide=bCroit(0,*pnSegmentEnTout,kuSegmentLiM-1);
	if (!bRangValide) d2(*pnSegmentEnTout,kuSegmentLiM);
	Assert1("NoeudInvalider",bRangValide);// $
	if ( !bSegmenConnU(nPoidsXY,nPoidsYZ,nPoidsZT,*pnSegmentEnTout) ){
		nSegmentMaX=*pnSegmentEnTout+1;
		iSegmenT[nSegmentMaX][1]=nPoidsXY;//progression en sens DIRECT utile pour le code interne
		iSegmenT[nSegmentMaX][2]=nPoidsYZ;
		iSegmenT[nSegmentMaX][3]=nPoidsZT;
		*pnSegmentEnTout=nSegmentMaX;
		if (1)
			printf("Segment invalide n°%3d de sommets %3d,%3d,%3d,%3d et de poids (%3d,%3d,%3d).\n",nSegmentMaX,sX,sY,sZ,sT,nPoidsXY,nPoidsYZ,nPoidsZT);
	}
}//NoeudInvalider

int noNoeudLibrE(){
	int noLibre=iNoeuD;
	iNoeuD=aNoeuD[noLibre].val;
	Assert1("noNoeudLibrE",bCroit(0,iNoeuD,knNoeudMaX));
	//if (nPriS%kE6==0) tee("nPriS,noLibre",nPriS,noLibre);
	nPriS++;
	Assert1("noNoeudLibrE",noLibre>0);
	return(noLibre);
}//noNoeudLibrE

void NoeudListeR(int noRacine,int bPreparer,int *pnSommetEnTout,int *pnArcEnTout){
	Assert1("NoeudListeR",noRacine>0);
	int nArcDroit,nArcGauche,nSommetDroit,nSommetGauche;
	int nFois;
	if (bPreparer)
		aNoeuD[noRacine].fwa++;
	nFois=aNoeuD[noRacine].fwa;
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		NoeudListeR(aNoeuD[noRacine].nog,bPreparer,&nSommetGauche,&nArcGauche);
		if (!bPreparer)
			printf("%d:%c %d %8d%s(%d)\n",noRacine,sOperateuR[aNoeuD[noRacine].typ],aNoeuD[noRacine].nog,aNoeuD[noRacine].nod,sFois(nFois,'*'),nFois);
		NoeudListeR(aNoeuD[noRacine].nod,bPreparer,&nSommetDroit,&nArcDroit);
	}else if (!bPreparer)
		printf("%d:%8d                  %s(%d)\n",noRacine,aNoeuD[noRacine].nog,sFois(nFois,'*'),nFois);
	*pnSommetEnTout=(aNoeuD[noRacine].typ!=NoeudNombre)? 1+nSommetGauche+nSommetDroit: 1;
	*pnArcEnTout=(aNoeuD[noRacine].typ!=NoeudNombre)? 2+nArcGauche+nArcDroit: 0;
}//nNoeudListeR

void NoeudLister(char* sTitre,int noRacine){
	//affiche chaque noeud (dont total pointeurs afférents entre parenthèses) puis affiche le nombre total de sommets et d'arcs visités.
	const int k1Preparer=kV;
	int nArcEnTout,nSommetEnTout;
	Assert1("NoeudLister1",noRacine>0);
	Titrer(sTitre);
	te("noRacine",noRacine);
	for (int uN=1;uN<=knNoeudMaX;uN++)
		aNoeuD[uN].fwa=0;
	NoeudListeR(noRacine,k1Preparer,&nSommetEnTout,&nArcEnTout);
	tee("nSommetEnTout0,nArcEnTout0",nSommetEnTout,nArcEnTout);
	NoeudListeR(noRacine,!k1Preparer,&nSommetEnTout,&nArcEnTout);
	tee("nSommetEnTout1,nArcEnTout1",nSommetEnTout,nArcEnTout);
	Assert1("NoeudLister2",nSommetEnTout==1+nArcEnTout);//c'est bien une arborescence virtuelle qui est affichée.
}//NoeudLister

void NoeudMarqueR(int noRacine,int cMarque){
	//marque (eta:=1) TOUTES les cellules accessibles depuis noRacine
	zNoeudVisitehEnTouT++;
	if (aNoeuD[noRacine].eta==1-cMarque){
		aNoeuD[noRacine].eta=cMarque;
		if (aNoeuD[noRacine].typ>NoeudNombre){
			NoeudMarqueR(aNoeuD[noRacine].nog,cMarque);
			NoeudMarqueR(aNoeuD[noRacine].nod,cMarque);
		};
	}
}//NoeudMarqueR

int bNoeudNul(int noRacine){
	Assert1("bNoeudNul",noRacine);
	int bNul=aNoeuD[noRacine].typ==NoeudNombre && aNoeuD[noRacine].nog==0 && aNoeuD[noRacine].nod==0;
	return(bNul);
}//bNoeudNul

void NoeudOptimuM(int noRacine,int iProfondeur){
	const int kbArbreSinonDag= kF;
	int bSomme=0,bProduit=0;
	Assert2("NoeudOptimuM0",noRacine>0,aNoeuD[noRacine].val<0); //toute cellule libérée a un .val>=0
	//d(noRacine);
	int nRaccourci=0,noGauche,noDroit;
	zNoeudVisitehEnTouT++;//OUI,ici
 	if (aNoeuD[noRacine].eta==0){//sinon,le dag sera déployé en arbre,lequel sera parcouru en tps exponentiel en pire cas. 
		aNoeuD[noRacine].eta=1;//d; >0 pr parcourir un dag et non pas un arbre.
		if (aNoeuD[noRacine].typ!=NoeudNombre){
			bSomme=(aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction);
			bProduit=(aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision);
			noGauche=aNoeuD[noRacine].nog;
			noDroit=aNoeuD[noRacine].nod;
			Assert3("NoeudOptimuM1",noGauche!=0,noDroit!=0,bSomme || bProduit);
			if (kbArbreSinonDag || aNoeuD[noGauche].eta==0) NoeudOptimuM(noGauche,iProfondeur-bProduit);
			if (kbArbreSinonDag || aNoeuD[noDroit].eta==0) NoeudOptimuM(noDroit,iProfondeur);// ou iProfondeur-bProduit
			nRaccourci=(bSomme)? iInf(aNoeuD[noGauche].aqqu,aNoeuD[noDroit].aqqu): aNoeuD[noGauche].aqqu+aNoeuD[noDroit].aqqu*(iProfondeur<=0);
			aNoeuD[noRacine].dequ=aNoeuD[noGauche].aqqu<aNoeuD[noDroit].aqqu;
			//d5(noRacine,iProfondeur,bSomme,bProduit,nRaccourci);
		}else nRaccourci=aNoeuD[noRacine].nod;
	} else t("appelé pour des prunes");
	aNoeuD[noRacine].aqqu=nRaccourci;
}//NoeudOptimuM

int nNoeudOptimum(int uDagNumero,int noRacine,int nProfondeur,int iSente[]){
	//rend le poids d'une sente de poids minimal ds le dag issu de noRacine; si iSente[0]>0, décrit ds iSente[] la sente à iSente[0] éléments.  
	long zComplexiteh;
	int nSenteLg;
	//Appel0("nNoeudOptimum");
		//d3(uDagNumero,noRacine,nProfondeur);
		Assert1("nNoeudOptimum",noRacine>0);
		if (nProfondeur>0 && aNoeuD[noRacine].typ!=NoeudNombre){
			NoeudVerifieR(noRacine,kV);
				NoeudOptimuM(noRacine,nProfondeur);
				//ld(zNoeudVisitehEnTouT);
			NoeudVerifieR(noRacine,kF);
			nSenteLg=iSente[0];//nb d'éléments de la sente
			if (nSenteLg){
				NoeudVerifieR(noRacine,kV);
					OptimumExhibeR(noRacine,nProfondeur,iSente);//élabore iSente mais altère iSente[0]
				NoeudVerifieR(noRacine,kF);
				//ld(zNoeudVisitehEnTouT);//lg totale = ∑ opérateurs * et +,lesquels "augmentent" la longueur du chemin d'accès.
				iSente[0]=nSenteLg;
				//VecteurVoir("iSente",iSente,1,iSente[0]);
			}
			zComplexiteh=zNoeudVisitehEnTouT;
		} else iSente[0]=0;//ie pas de sente
		//printf("Complexité de nNoeudOptimum pour la composante %d: %s.\n",uDagNumero,sPar3(zComplexiteh));
	//Appel1("nNoeudOptimum");
	return(aNoeuD[noRacine].aqqu);
}//nNoeudOptimum

int nNoeudPariatioN(int nozPere,int noRacine,int nHauteur){
	//rend le nombre de pariations, ie de séquences de paires d'arcs opposés, présentes dans le dag de racine noRacine.
	int mPariation=-1,noGauche,noDroit;
 	Assert1("nNoeudPariatioN0",nHauteur==1 && nozPere==0 || nHauteur>1 && (aNoeuD[nozPere].typ==NoeudProduit || aNoeuD[nozPere].typ==NoeudDivision));
	if (aNoeuD[noRacine].typ>NoeudNombre){
		noGauche=aNoeuD[noRacine].nog;
		noDroit=aNoeuD[noRacine].nod;
		if (aNoeuD[noRacine].typ==NoeudAddition)
			mPariation=nNoeudPariatioN(nozPere,noGauche,nHauteur)+nNoeudPariatioN(nozPere,noDroit,nHauteur);
		if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision) {
			mPariation=nNoeudPariatioN(noRacine,noGauche,nHauteur+1);
			if (bPair(nHauteur)){//=> nHauteur>1 => nozPere ≠ 0
				if ( iOperandeDroiT(nozPere)!= - iOperandeDroiT(noRacine) )
					mPariation=0;
			}
		};
	} else mPariation=1;
 	Assert1("nNoeudPariatioN1",mPariation>=0);
	return(mPariation);
}//nNoeudPariatioN

void NoeudPaterniteR(int noFils,int noPere){
	Assert1("NoeudPaterniteR",0);
	aNoeuD[noFils].aqqu=noPere;
	//if (noFils==113) tee("NoeudPaterniteR noFils,noPere",noFils,noPere);
	if (aNoeuD[noFils].typ!=NoeudNombre){
		NoeudPaterniteR(aNoeuD[noFils].nog,noFils);
		NoeudPaterniteR(aNoeuD[noFils].nod,noFils);
	}
}//NoeudPaterniteR

void NoeudPaterniter(int noRacine){//PADAPEL
	//attribue une paternité à chaque noeud du Dag.
	Assert1("NoeudPaterniter",0);
	//Appel0("NoeudPaterniter");
		NoeudPaterniteR(noRacine,noRacine);
	//Appel1("NoeudPaterniter");
}//NoeudPaterniter

int nNoeudPris(){
	//d2(nPriS,knNoeudMaX);
	return(nPriS);
}//nNoeudPris

void NoeudRecuperer(int noRacine[]){
	//ramasse les cellules inaccessibles depuis une collection de noRacine[0] racines dans un réseau de cellules réputé sans cycle.
	int noNoeud,nNoeudLibereh,nPris,uR;
	if (noRacine[0]>0){
		nPris=nNoeudPris();
		//marquer les cellules accessibles
			for (zNoeudVisitehEnTouT=0,noNoeud=1;noNoeud<=nPris;zNoeudVisitehEnTouT++,noNoeud++)
				aNoeuD[noNoeud].eta=0;
			for (uR=1;uR<=noRacine[0];uR++)
				if (aNoeuD[noRacine[uR]].eta==0) 
					NoeudMarqueR(noRacine[uR],1);
		//restituer les cellules non marquées
			for (zNoeudVisitehEnTouT=0,noNoeud=1;noNoeud<=nPris;zNoeudVisitehEnTouT++,noNoeud++)
				if (aNoeuD[noNoeud].eta==0)
					NoeudRestituer(noNoeud,kF);
		//démarquer les cellules marquées pour laisser les lieux...
			for (zNoeudVisitehEnTouT=0,uR=1;uR<=noRacine[0];uR++)
				if (aNoeuD[noRacine[uR]].eta==1) 
					NoeudMarqueR(noRacine[uR],0);
		nNoeudLibereh=nPris-nNoeudPris();
		d(nNoeudLibereh);
	}
}//NoeudRecuperer

void NoeudRestitueR(int iNoeud){
	if (aNoeuD[iNoeud].typ>=0){
		aNoeuD[iNoeud].typ=-1;
		aNoeuD[iNoeud].val=iNoeuD;
		nPriS--;
		iNoeuD=iNoeud;
	}
}//NoeudRestitueR

void NoeudRestituer(int iNoeud,int bDontDescendance){
	Assert1("NoeudRestituer",bCroitStrict(0,iNoeud,knNoeudLiM));
	if (bDontDescendance)
		if (aNoeuD[iNoeud].typ>0){
			NoeudRestituer(aNoeuD[iNoeud].nog,bDontDescendance);
			NoeudRestituer(aNoeuD[iNoeud].nod,bDontDescendance);
		};
	NoeudRestitueR(iNoeud);
}//NoeudRestituer

int nNoeudRoutE(int noRacine){
	//rend le nombre de chemins distincts depuis noRacine jsq une feuille distale
	int nRoute=0,nDroit,nGauche;
	zNoeudVisitehEnTouT++;
	if (aNoeuD[noRacine].eta==0){
		aNoeuD[noRacine].eta=1;
		if (aNoeuD[noRacine].typ>NoeudNombre){
			nGauche=nNoeudRoutE(aNoeuD[noRacine].nog);
			nDroit=nNoeudRoutE(aNoeuD[noRacine].nod);
			if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction)
				nRoute=nGauche+nDroit;
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision)
				nRoute=nGauche*nDroit;
		} else nRoute=aNoeuD[noRacine].nog!=0;//ie non nul
		aNoeuD[noRacine].aqqu=nRoute;
	} else nRoute=aNoeuD[noRacine].aqqu;
	return(nRoute);
}//nNoeudRoutE

int nNoeudRoute(int noRacine){
	//rend le nombre de chemins distincts sans doublon depuis noRacine jsq une feuille distale
	int nRoute;
	long zComplexiteh=1;
	Assert1("nNoeudRoute",noRacine>0);
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		NoeudVerifieR(noRacine,kV);
			//nRoute=nNoeudRoutE(noRacine);
			NoeudDerouter(noRacine,15);
		NoeudVerifieR(noRacine,kF);
		zComplexiteh=zNoeudVisitehEnTouT;
	}
	ld(zComplexiteh);
	return(nRoute);
}//nNoeudRoute

void NoeudSimplE(int noRacine){
	int uClef,bSimple;
	bSimple=kV;
	//te("noRacine",noRacine);
	if (aNoeuD[noRacine].typ==NoeudNombre){
		uClef=aNoeuD[noRacine].nog;
		//te("uClef",uClef);
		noPlacE[uClef]++;
		//bSimple=noPlacE[uClef]<=1;
	} else {
		//te("aNoeuD[noRacine].nog",aNoeuD[noRacine].nog);
		NoeudSimplE(aNoeuD[noRacine].nog);
		//te("aNoeuD[noRacine].nod",aNoeuD[noRacine].nod);
		NoeudSimplE(aNoeuD[noRacine].nod);
	}
	//return(bSimple);
}//NoeudSimplE

int bNoeudSimple(int noRacine){
	//aucun doublon dans le dag
	int uClef;
	int bSimple=kV;
	Assert1("bNoeudSimple",noRacine>0);
	//Appel0("bNoeudSimple");
		if (0){
			VecteurRazer(noPlacE,1,15);
			noPlacE[0]=0;//a
			NoeudSimplE(noRacine);
			for (uClef=1;uClef<=15;uClef++)
				bSimple=bSimple && noPlacE[uClef]<=1;
			//if (!bSimple) Titrer("PAS SIMPLE");
		}
		bSimple=kV;
	//Appel1("bNoeudSimple");
	return(bSimple);
}//bNoeudSimple

void NoeudSimplifieR(int noRacine,int iElementNeutre,int bDontDoublon){
	const int kbArbreSinonDag= kF;
	Assert1("NoeudSimplifieR",noRacine>0);
	//d(noRacine);
	int mGauche,mDroit,noGauche,noDroit;
	zNoeudVisitehEnTouT++;//OUI,ici
 	if (aNoeuD[noRacine].eta==0){//sinon,le dag sera déployé en arbre,lequel sera parcouru en tps exponentiel en pire cas. 
		aNoeuD[noRacine].eta=1;//d; >0 pr parcourir un dag et non pas un arbre.
		if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction || aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
			noGauche=abs(aNoeuD[noRacine].nog);
			noDroit=abs(aNoeuD[noRacine].nod);
			Assert2("aNoeuD[noRacine].nog>0,nod>0",noGauche!=0,noDroit!=0);
			if (kbArbreSinonDag || aNoeuD[noGauche].eta==0) NoeudSimplifieR(noGauche,iElementNeutre,bDontDoublon);
			if (kbArbreSinonDag || aNoeuD[noDroit].eta==0) NoeudSimplifieR(noDroit,iElementNeutre,bDontDoublon);
			Assert2("NoeudSimplifieR 22",noGauche==abs(aNoeuD[noRacine].nog),noDroit==abs(aNoeuD[noRacine].nod));//ie pas d'altération
			if (aNoeuD[noGauche].typ==NoeudNombre) mGauche=aNoeuD[noGauche].nog; else mGauche=kiIntegerMin;
			if (aNoeuD[noDroit].typ==NoeudNombre)  mDroit=aNoeuD[noDroit].nod; else mDroit=kiIntegerMin;
			if (aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision){
				if (mDroit==0 || mGauche==0){
					aNoeuD[noRacine].nog=aNoeuD[noRacine].nod=0;aNoeuD[noRacine].typ=NoeudNombre;
				}else  if (mGauche==iElementNeutre)
					aNoeuD[noRacine]=aNoeuD[noDroit];
				else if (mDroit==iElementNeutre)
					aNoeuD[noRacine]=aNoeuD[noGauche];
				else if (0 && bDontDoublon && mDroit==mGauche && mGauche>1){
					printf("                       *********** %d*%d=0.\n",mDroit,mDroit);
					aNoeuD[noRacine].nog=aNoeuD[noRacine].nod=0;aNoeuD[noRacine].typ=NoeudNombre;
				}
			} else if (aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction){
				if (mGauche==0)
					aNoeuD[noRacine]=aNoeuD[noDroit];
				else if (mDroit==0)
					aNoeuD[noRacine]=aNoeuD[noGauche];
			}
		};
	}// else t("appelé pour des prunes");
}//NoeudSimplifieR

void NoeudSimplifier(int nComposante,int noRacine,int iElementNeutre,int bDontDoublon){
	long zComplexiteh=1;
	//Appel0("NoeudSimplifier");
		//d3(nComposante,noRacine,bDontDoublon);
		Assert1("NoeudSimplifier",abs(noRacine)>0);
		if (aNoeuD[abs(noRacine)].typ!=NoeudNombre){
			NoeudVerifieR(noRacine,kV);
				NoeudSimplifieR(abs(noRacine),iElementNeutre,!k1Doublon);
				//if (bDontDoublon) NoeudSimplifieR(noRacine,bDontDoublon);
			NoeudVerifieR(noRacine,kF);
			zComplexiteh=zNoeudVisitehEnTouT;
		}
		//printf("NoeudSimplifier pour la composante %d: complexité = %s.\n",nComposante,sPar3(zComplexiteh));
	//Appel1("NoeudSimplifier");
}//NoeudSimplifier

void NoeudSingletonneR(int noRacine,int *pnoPlexe){
	//dédouble les noeuds mis en commun
	Assert1("NoeudUniqueR",noRacine>0);
	int noPlexe,noDroit,noGauche;
	noPlexe=noNoeudLibrE();
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		NoeudSingletonneR(aNoeuD[noRacine].nog,&noGauche);
		NoeudSingletonneR(aNoeuD[noRacine].nod,&noDroit);
	}else noGauche=noDroit=aNoeuD[noRacine].nog;
	aNoeuD[noPlexe].nog=noGauche;
	aNoeuD[noPlexe].nod=noDroit;
	aNoeuD[noPlexe].typ=aNoeuD[noRacine].typ;
	*pnoPlexe=noPlexe;
}//NoeudSingletonneR

int noNoeudSingletonneR(char* sTitre,int noRacine){
	//rend la nouvelle racine d'un ARBRE identique au DAG de racine noRacine 
	int uN,noUniker;
	Assert1("noNoeudSingletonneR",noRacine>0);
	//Titrer(sC2b("noNoeudSingletonneR",sTitre));
	for (uN=1;uN<=knNoeudMaX;uN++)
		aNoeuD[uN].fwa=0;
	NoeudSingletonneR(noRacine,&noUniker);
	//NoeudLister("fin DE noNoeudSingletonneR",noUniker);
	return(noUniker);
}//noNoeudSingletonneR

int nNoeudSommE(int noRacine){
	int nGauche,nDroit,nSomme=0;
	int bAddition , bSoustraction , bProduit;
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		bAddition=bVrai(aNoeuD[noRacine].typ==NoeudAddition);
		bSoustraction=bVrai(aNoeuD[noRacine].typ==NoeudSoustraction);
		bProduit=bVrai(aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision);
		//teeee("aNoeuD[noRacine].typ,bAddition,bSoustraction,bProduit",aNoeuD[noRacine].typ,bAddition,bSoustraction,bProduit);
		Assert1("nNoeudSommE",bAddition || bSoustraction || bProduit);
		nGauche=nNoeudSommE(aNoeuD[noRacine].nog);
		nDroit=nNoeudSommE(aNoeuD[noRacine].nod);
		nSomme=nGauche+nDroit+bVrai(aNoeuD[noRacine].typ==NoeudAddition);//bVrai indispensB!
		if (nSomme>0)
			printf("nGauche+nDroit=nSomme:%d+%d=%d.\n",nGauche,nDroit,nSomme);
		if (nSomme==5593){
			tee("nGauche,nDroit",nGauche,nDroit);
			Titrer("5593");
		}
		if (nSomme==5466){
			tee("nGauche,nDroit",nGauche,nDroit);
			Titrer("5466");
		}
	}else nSomme=0;
	return(nSomme);
}//nNoeudSommE

int nNoeudSomme(int noRacine){
	Appel0("nNoeudSomme0");
		int nGauche,nDroit,nSomme=0;
		nGauche=nNoeudSommE(aNoeuD[noRacine].nog);
		nDroit=nNoeudSommE(aNoeuD[noRacine].nod);
		nSomme=nGauche+nDroit;
		//teee("nGauche,nDroit,nSomme",nGauche,nDroit,nSomme);
	Appel1("nNoeudSomme1");
	return(nSomme);
}//nNoeudSomme

void NoeudTESTER(int iTest){
	//teste le présent module
	Assert1("NoeudTESTER",bNoeudAmorceR);
	Appel0(sC2("NoeudTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case-1: nNoeudEnumereR[1]=1;nNoeudEnumereR[2]=0;
					break;
			case-2: nNoeudEnumereR[1]=2;nNoeudEnumereR[2]=0;
					break;
			case-3: nNoeudEnumereR[1]=nNoeudEnumereR[2]=1;
					break;
			case 1: qArtereDebouteR[1]=1;qArtereDebouteR[2]=0;
					break;
			case 2: qArtereDebouteR[1]=2;qArtereDebouteR[2]=0;
					break;
			case 3: qArtereDebouteR[1]=qArtereDebouteR[2]=1;
					break;
			default:
				Assert1("NoeudTESTER",0);
				break;
		}
	Appel1(sC2("NoeudTESTER,test n°",sEnt(iTest)));
}//NoeudTESTER	

void NoeudVerifieR(int noRacine,int bCompter){
	//vérifie (routine parenthésante) que la routine parenthésée ne consomme pas de noeuds supplémentaires et que son coût est borné par O(N**k).
	FlipFlop("NoeudVerifieR",bCompter,&bNoeudVerifieR);
	nNoeudVerifieR=nNoeudPris();
	NoeudMarqueR(noRacine,0);
	//d3(bCompter,zNoeudVisitehEnTouT,nNoeudVerifieR);
	if (bCompter){
		zNoeudVisitehEnTouT=0;//d pr compter les appels à la routine parenthésée
	}else Assert1("NoeudVerifieR",zNoeudVisitehEnTouT< 2*nNoeudVerifieR);
}//NoeudVerifieR

void NoeudVoir(char *sMessage,int noRacine){
	//affiche uniquement 1 noeud: celui d'index noRacine;pour voir une arborescence,cf NoeudArborer
	Assert1("NoeudVoir",noRacine>0);
	printf("%s:",sMessage);
	printf("noeud %s ",(aNoeuD[noRacine].typ==NoeudNombre)? "externe":"interne");
	printf("n°%5d:(",noRacine);
			printf("%d,",aNoeuD[noRacine].nog);
			printf("%c,",sOperateuR[aNoeuD[noRacine].typ]);
			printf("%d",aNoeuD[noRacine].nod);
	printf(").\n");
}//NoeudVoir

void NoeudVoirTout(char *sMessage){
	int noNoeud,nPris;
	for (nPris=nNoeudPris(),noNoeud=1;noNoeud<=nPris;noNoeud++)
		NoeudVoir(sEnt(noNoeud),noNoeud);
}//NoeudVoirTout

int iOperandeDroiT(int noProduitOuDivision){
	Assert1("iOperandeDroiT0",aNoeuD[noProduitOuDivision].typ==NoeudProduit || aNoeuD[noProduitOuDivision].typ==NoeudDivision);
	int noFeuille=aNoeuD[noProduitOuDivision].nod;
	Assert2("iOperandeDroiT1",aNoeuD[noFeuille].typ==NoeudNombre,aNoeuD[noFeuille].nog==aNoeuD[noFeuille].nod);//l'opérande droit d'un produit est tjrs une feuille.
	int iOperande=aNoeuD[noFeuille].nog;
	return(iOperande);
}//iOperandeDroiT

void OptimumExhibeR(int noRacine,int iProfondeur,int iSente[]){
	int noGauche,noDroit;
	int bProduit,bSomme;
	Assert2("OptimumExhibeR 0",noRacine>0,iSente[0]>0);
	//d3(noRacine,iProfondeur,iSente[0]);
	zNoeudVisitehEnTouT++;//OUI,ici; kbArbreSinonDag et .eta superflus vu parcours descendant guidé par aNoeuD[noRacine].dequ si bSomme.
	//d(noRacine);
	if (aNoeuD[noRacine].typ!=NoeudNombre){
		bSomme=(aNoeuD[noRacine].typ==NoeudAddition || aNoeuD[noRacine].typ==NoeudSoustraction);
		bProduit=(aNoeuD[noRacine].typ==NoeudProduit || aNoeuD[noRacine].typ==NoeudDivision);
		noGauche=aNoeuD[noRacine].nog;
		noDroit=aNoeuD[noRacine].nod;
		Assert3("OptimumExhibeR 1",noGauche!=0,noDroit!=0,bSomme || bProduit);
		if (bProduit){
			if (iProfondeur<=0){
				iSente[iSente[0]--]=aNoeuD[noDroit].aqqu;
				if (aNoeuD[noGauche].typ==NoeudNombre)
					iSente[iSente[0]--]=aNoeuD[noGauche].aqqu;//dernier élément du segment
				 else OptimumExhibeR(noGauche,iProfondeur-1,iSente);
			} else OptimumExhibeR(noGauche,iProfondeur-1,iSente);
		} else OptimumExhibeR( (aNoeuD[noRacine].dequ)? noGauche: noDroit,iProfondeur,iSente);
	} else t("appelé pour des prunes");
}//OptimumExhibeR

void PiedEtendrE(int noRacine){
	//dédié PiedEtendrePartouT
	if (aNoeuD[noRacine].typ==NoeudAddition){
		PiedEtendrE(aNoeuD[noRacine].nog);
		PiedEtendrE(aNoeuD[noRacine].nod);
	}else{
		Assert3("PiedEtendrE",ipPiedEtendrE+1<kuPiedLiM,noRacine!=NoeudAddition,noRacine!=NoeudNombre);//?
		noPiedListE[++ipPiedEtendrE]=noRacine;
	}
}//PiedEtendrE;

void PiedEtendrePartouT(int noRacine){
	//enfile (largeur d'abord) tous les successeurs de noRacine qui sont de type NoeudProduit ou NoeudNombre. Saute les NoeudAddition.
	int ipListe;
	ipPiedEtendrE=0;
	PiedEtendrE(noRacine);
	noPiedListE[0]=ipPiedEtendrE;
	if (0)
		if (ipPiedEtendrE>0)
			VecteurVoir(sC2b("**************************noPiedListE pour le tronc",sEnt(noRacine)),noPiedListE,1,noPiedListE[0]);
		else printf("%s:Liste vide.\n",sC2b("**************************noPiedListE pour le tronc",sEnt(noRacine)));
	for (ipListe=1;ipListe<=noPiedListE[0];ipListe++)
		DequeEnfiler(noPiedListE[ipListe]);
}//PiedEtendrePartouT;

void PiedListeR(int noRacine){
	//empile tous les successeurs de noRacine qui sont de type NoeudProduit. Ils existent.
	int noDroit,noPied,ipListe;
	//Appel0(sC2b("PiedListeR pour le tronc",sEnt(noRacine)));
		noPiedListE[0]=ipListe=0;
		noPied=noRacine;//d
		if (aNoeuD[noPied].typ==NoeudAddition)
			while (aNoeuD[noPied].typ==NoeudAddition){
				noDroit=aNoeuD[noPied].nod;
				Assert2("PiedListeR",noDroit!=NoeudAddition,noDroit!=NoeudNombre);//?
				if ( aNoeuD[noDroit].typ==NoeudProduit || aNoeuD[noDroit].typ==NoeudDivision){
					Assert1("PiedListeR",ipListe+1<kuPiedLiM);
					noPiedListE[++ipListe]=noDroit;
				}
				noPied=aNoeuD[noPied].nog;
			}
		if (aNoeuD[noPied].typ==NoeudProduit || aNoeuD[noPied].typ==NoeudDivision)
			noPiedListE[++ipListe]=aNoeuD[noPied].nod;
		noPiedListE[0]=ipListe;
		if (ipListe>0)
			VecteurVoir(sC2b("**************************noPiedListE pour le tronc",sEnt(noRacine)),noPiedListE,1,noPiedListE[0]);
		else printf("%s:Liste vide.\n",sC2b("**************************noPiedListE pour le tronc",sEnt(noRacine)));
	//Appel1(sC2b("PiedListeR pour le tronc",sEnt(noRacine)));
}//PiedListeR

void SegmentAfficheR(){
	const int kuSegmentParLigne=10;
	int nS,uSegment;
	printf("SEGMENTS INVALIDES");
	if (nSegmentMaX>0){
		printf(" (%s en tout):\n",sPluriel(nSegmentMaX,"segment") );
		for (uSegment=1;uSegment<=nSegmentMaX;uSegment+=kuSegmentParLigne){
			printf("%2d à %2d:",uSegment,uSegment+kuSegmentParLigne-1);
			for (nS=0;nS<kuSegmentParLigne && uSegment+nS<=nSegmentMaX;nS++)
				printf(" (%3d,%3d,%3d)",iSegmenT[uSegment+nS][1],iSegmenT[uSegment+nS][2],iSegmenT[uSegment+nS][3]);
			printf("\n");
		}
	}else printf(": aucun.\n");
}//SegmentAfficheR

int bSegmentBannI1(int iPoidsXY){
	int bInvalide,uS;
	for (bInvalide=kF,uS=1;uS<=nSegmentMaX && !bInvalide;uS++)
		bInvalide=bInvalide || abs(iSegmenT[uS][1])==abs(iPoidsXY) && abs(iSegmenT[uS][2])==0 && iSegmenT[uS][3]==0;
	//if (bInvalide) Titrer("bSegmentBannI1");
	return(bInvalide);
}//bSegmentBannI1

int bSegmentBannI2(int iPoidsXY,int iPoidsYZ){
	int bInvalide,uS;
	//int nPoids1=iInf(abs(iPoidsXY),abs(iPoidsYZ));//ds iSegmenT[],les segments de la forme (A,B,0) vérifient A≤B. Grâce à iInf et…
	//int nPoids2=iSup(abs(iPoidsXY),abs(iPoidsYZ));//…iSup, cette routine rend vrai dès que (|iPoidsXY|,|iPoidsYZ|)= (A,B) ou (B,A).
	for (bInvalide=kF,uS=1;uS<=nSegmentMaX;uS++)//chercher
		bInvalide=bInvalide || iSegmenT[uS][1]==iPoidsXY && iSegmenT[uS][2]==iPoidsYZ && iSegmenT[uS][3]==0;
	//if (bInvalide) Titrer("bSegmentBannI2");
	//bInvalide=bSegmentBannI1(iPoidsXY) && bSegmentBannI1(iPoidsYZ);
	return(bInvalide);
}//bSegmentBannI2

int bSegmentBannI3(int iPoidsXY,int iPoidsZT){
	int bInvalide,uS;
	int nPoidsXY=abs(iPoidsXY);
	int nPoidsZT=abs(iPoidsZT);
	//d2(iPoidsXY,iPoidsZT);
	for (bInvalide=kF,uS=1;uS<=nSegmentMaX;uS++)
		bInvalide=bInvalide || iSegmenT[uS][1]==nPoidsXY && iSegmenT[uS][3]==nPoidsZT;
	//if (bInvalide) Titrer("bSegmentBannI3");
	return(bInvalide);
}//bSegmentBannI3

int bSegmenConnU(int nPoids1,int nPoids2,int nPoids3,int nSegmentEnTout){
	//vrai ssi le triplet (nPoids1,nPoids2,nPoids3) figure déjà dans la liste de segments interdits iSegmenT[1..nSegmentEnTout]
	int bSegment,uSegment;
	for (bSegment=kF,uSegment=1;uSegment<=nSegmentEnTout && !bSegment;uSegment++)
		bSegment=nPoids1==iSegmenT[uSegment][1] && nPoids2==iSegmenT[uSegment][2] && nPoids3==iSegmenT[uSegment][3];
	return(bSegment);
}//bSegmenConnU

int bSegmentElemenT(int iValeur){
	//iValeur est un élément d'un qcq segment; dédié NoeudArboreR
	int bElement,uSegment;
	for (bElement=kF,uSegment=1;uSegment<=nSegmentMaX && (!bElement);uSegment++)
		bElement=bElement || bDans3(iValeur,iSegmenT[uSegment][1],iSegmenT[uSegment][2],iSegmenT[uSegment][3]);
	return(bElement);
}//bSegmentElemenT

int bSegmentInterdiT(int uDag,int noTete,int noTronc,int noPied){
	//vrai ssi (noTete,noTronc,noPied) décrit un segment interdit.
	int bInterdit,uSegment,iTete,iTronc,iPied;
	//NB l'appelant peut envoyer des valeurs nulles en guise de noeud,d'où li+1
	bInterdit=aNoeuD[noTete].typ==NoeudProduit && aNoeuD[noTronc].typ==NoeudProduit && aNoeuD[noPied].typ==NoeudProduit;
	if (bInterdit){
		//if (noTete==1614) t("1");
		iTete=iOperandeDroiT(noTete);
		iTronc=iOperandeDroiT(noTronc);
		iPied=iOperandeDroiT(noPied);
		for (bInterdit=kF,uSegment=1;uSegment<=nSegmentMaX && (!bInterdit);uSegment++)
			bInterdit=iSegmenT[uSegment][1]==iTete && iSegmenT[uSegment][2]==iTronc && iSegmenT[uSegment][3]==iPied;
		if (0 && bInterdit) d3(iTete,iTronc,iPied);
		if (uDag==10)
			printf("Le segment %d,%d,%d est %s.\n",iTete,iTronc,iPied,(bInterdit)? "INTERDIT": "accepté");
	}
	return(bInterdit);
}//bSegmentInterdiT

void SegmentInverseR(){
	int uS;
	for (uS=1;uS<=nSegmentMaX;uS+=1)
		EntierEchanger( &iSegmenT[uS][1],&iSegmenT[uS][3] );
}//SegmentInverseR

int bSegmentPresenT(int iPoids[]){
	int uH,uI,uJ,uProfondeur=iPoids[0];
	int bSegment,uSegment;
	for (bSegment=kF,uSegment=1;uSegment<=nSegmentMaX && !bSegment;uSegment++)
		for (uH=1;uH<=uProfondeur && !bSegment;uH++){
			uI=uModulo1(uH+1,uProfondeur);
			uJ=uModulo1(uH+2,uProfondeur);
			bSegment=(iPoids[uH]==iSegmenT[uSegment][1]) && (iPoids[uI]==iSegmenT[uSegment][2]) && (iPoids[uJ]==iSegmenT[uSegment][3]);
		}
	return(bSegment);
}//bSegmentPresenT

int bSegmentPresenT1(int iPoids[]){
	int bSegment,uSegment;
	for (bSegment=kF,uSegment=1;uSegment<=nSegmentMaX && !bSegment;uSegment++)
		if (iSegmenT[uSegment][2]==0 && iSegmenT[uSegment][3]==0)
			bSegment=bVecteurContient(iSegmenT[uSegment][1],iPoids);
	return(bSegment);
}//bSegmentPresenT1

int bSegmentPresenT2(int iPoids[]){
	int bSegment,uSegment;
	for (bSegment=kF,uSegment=1;uSegment<=nSegmentMaX && !bSegment;uSegment++)
		if (iSegmenT[uSegment][2]!=0 && iSegmenT[uSegment][3]==0){
			bSegment=bVecteurContient(iSegmenT[uSegment][1],iPoids) && bVecteurContient(iSegmenT[uSegment][2],iPoids);
		}
	bSegment=kF;
	return(bSegment);
}//bSegmentPresenT2

void SegmentVoiR(char *sQuoi){
	//Liste tous les segments mémorisé dans noPilE[]
	int nIndex,noNoeud,iPoids;
	for (printf("%s:  0  0  0",sQuoi),nIndex=4;nIndex<=ipPilE || bPrint0(".\n") ;nIndex++){
		noNoeud=noPilE[nIndex];
		Assert1("SegmentVoiR",aNoeuD[noNoeud].typ==NoeudProduit || aNoeuD[noNoeud].typ==NoeudDivision);
		iPoids=iOperandeDroiT(noNoeud);
		printf(" %d",iPoids);
	}
}//SegmentVoiR
