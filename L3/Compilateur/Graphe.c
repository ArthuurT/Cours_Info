#include "Outil.h"
#include "Deque.h"
#include "Foret.h"
#include "Graphe.h"
#include "Matrice.h"
#include "Tas.h"
#include "Abe.h"
//structure de données du graphe courant G
#define kbCourtSinonLong 1
#define k1BipartiR kV
const int k1PerformanceCompareR=kV;
int bGrapheAmorceR;
int bGrapheCreeR;
int bGrapheBipartiR;
void CoutInverseR(graf *pgG);
void DijkstraAvecOuSansTasCompareR();
void ElectrifieR();
int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur);
void GrapheCheminerAuLargE (graf *pgG,int sSource,int sTrappe);
void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int nMesure,int gcMode);
int bGrapheCheminE(graf *pgG,int sSource,int sTrappe);
int nGrapheChemineR (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh);
int nGrapheCheminerAuLargE (graf *pgG,int sSource,int sTrappe);
int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh);//O(SlgS+A)
int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh);//O(S2)
void GrapheCompletCreerPondereR(int nSommet,graf **ppgG);
void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG);
void GraphePondererPareiL(graf *pgG);
void GrapheQuinconceR(graf *pgG,int bBipartir);
int bGrapheVidE(graf *pgG);
void GrapheCouvrirAvecKruskaL(graf *pgG,int bAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecKruskaL(graf *pgG,int bLogn,int bTas,int bAfficher);
int nGrapheCouvrirAvecP(graf *pgG);
void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer);
int nGrapheCouvrirAvecPriM(graf *pgG);
void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int nPoidsMax,graf **ppgG);
void GrapheSymetrizer(graf *pgG);
void GrapheViseR(graf *pgG,char *sMessage);

void DijkstraAvecOuSansTasCompareR(){
	//effectue kuMesureMax mesures sur les deux algorithmes de Dijkstra, ie versions sans tas et avec tas, et affiche les résultats des mesures.
	#define kuFacteur 10
	#define kuMesureMax 9
	graf *pgG;
	int bAfficher=k1Afficher;
	int nArc,bCheminer,uM,nSommet;
	const int ksSource=1;
	const int kuTab=4;
	int nComplexitehAvecTas[1+kuMesureMax];
	int nComplexitehSansTas[1+kuMesureMax];
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		GrapheCompletCreerPondereR(nSommet,&pgG);
			//GrapheVoir0(pgG,sC4b("Graphe à",sPluriel(nSommet,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
			bCheminer=bGrapheCheminerCourt(pgG,ksSource,ksSource+1,bAfficher,&nComplexitehSansTas[uM]);
			bCheminer=bGrapheCheminerCourtTaS(pgG,ksSource,ksSource+1,bAfficher,&nComplexitehAvecTas[uM]);
		GrapheCreer(0,&pgG);
	}
	Ligne();
	Titrer(" Tableau comparatif des algorithmes de Dijkstra \"sans tas\" vs \"avec tas\" pour les plus courts chemins ");
	Ligne();
	printf("%sGraphe complet  Temps total d'exécution T    Rapport des temps    T/pire temps théorique\n",sTab(kuTab));
	printf("%s   (S,A)          Sans tas   Avec tas        Sans tas/Avec tas     Sans tas   Avec tas  \n",sTab(kuTab));
	for (uM=1;uM<=kuMesureMax;uM++){
		nSommet=kuFacteur*uM;
		nArc=(nSommet*(nSommet-1))/2;
		printf("%s  %s%s",sTab(kuTab),sCouple(nSommet,nArc),sE(10-nChaineLg(sCouple(nSommet,nArc))));
		printf("       %5d     %5d",nComplexitehSansTas[uM],nComplexitehAvecTas[uM]);
		printf("                 %5.2f",nComplexitehSansTas[uM]/(nComplexitehAvecTas[uM]*1.0));
		printf("            %5.2f",nComplexitehSansTas[uM]/(nSommet*nSommet*1.0));
		printf("      %5.2f",nComplexitehAvecTas[uM]/(nArc+nSommet*rLog(nSommet)));
		Ligne();
	}
	Ligne();
}//DijkstraAvecOuSansTasCompareR

void ElectrifieR(){
	#define kuSmax 6
	const int kuFacteurMultiplicatif=kE4;
	const int kuPoidsMaxBidon=kE5;
	const int k1Prim=kV;
	int nAretePoids;
	int nCoteX[1+kuSmax]={-1,1,2,2,3,3,1};
	int nCoteY[1+kuSmax]={-1,1,2,3,3,4,4};
	graf *pgG;
	int aK,sX,sY;
	Appel0("ElectrifieR");
		GrapheSymetriqueCreerPondereR(k1Dense,kuSmax,kuPoidsMaxBidon,&pgG);//les poids affectés sont provisoires
		//poids(X,Y):=distance(X,Y) pr tout couple (X,Y) de sommets de pgG
			for (sX=1;sX<=kuSmax;sX++)
				for (sY=sX+1;sY<=kuSmax;sY++){
					nAretePoids=nRac( kuFacteurMultiplicatif*(nCarreh(nCoteX[sX]-nCoteX[sY])+nCarreh(nCoteY[sX]-nCoteY[sY])) );
					aK=nGrapheArc(pgG,sX,sY);
					pgG->nCout[aK]=nAretePoids;
					aK=nGrapheArc(pgG,sY,sX);
					pgG->nCout[aK]=nAretePoids;
				}
		GrapheVoir3(pgG,"graphe complet pondéré à \"électrifier\"");
		Assert1("ElectrifieR1",bGrapheSymetrique(pgG));//indispensable pour appeler GrapheCouvrirAvecPrimOuP
		GrapheCouvrirAvecPrimOuP(pgG,!k1Prim,k1Afficher,!k1PerformanceCompareR);
		GrapheCouvrirAvecKruskaL(pgG,k1Afficher,!k1PerformanceCompareR);
	Appel1("ElectrifieR");
}//ElectrifieR

int bGraphe(graf *pgG){//O(A)
	//vrai ssi les champs de gG décrivent effectivement un graphe quelconque ——pr les quatre champs nSommetEnTout,nArcEnTout,aHed et sSuk de gG.
	int bGraphe,aK,sX;
	Assert1("bGraphe",bGrapheAmorceR);
	bGraphe=(pgG->nSommetEnTout>=0) && (pgG->nArcEnTout>=0) && (pgG->aHed[1]==1);
	Assert1("bGraphe2",bGraphe);
	bGraphe=bGraphe && (pgG->aHed[pgG->nSommetEnTout+1]==pgG->nArcEnTout+1);
	Assert1("bGraphe3",bGraphe);
	if (bGraphe)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			bGraphe=bGraphe && pgG->aHed[sX]<=pgG->aHed[sX+1];
	Assert1("bGraphe4",bGraphe);
	if (bGraphe)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			bGraphe=bGraphe && bGrapheSommet(pgG,pgG->sSuk[aK]);
	Assert1("bGraphe5",bGraphe);
	return(bGraphe);//noter qu'un graphe qui vérifie bGraphe est un multigraphe;donc ce n'est pas nécessairement un graphe simple;
}//bGraphe

void GrapheAMORCER(){
	//amorce le présent module une fois pour toutes
	bGrapheAmorceR=kV;
	//tee("GrapheAMORCER:kuGrapheSommetLim,kuGrapheArcLim",kuGrapheSommetLim,kuGrapheArcLim);
	Assert2("GrapheAMORCER",bFrontiere8(kuGrapheSommetLim),bFrontiere8(kuGrapheArcLim));
}//GrapheAMORCER

int bGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//vrai ssi (sOrigine,sDestination) est un arc de gG
	int bArc;
	int aK;
	Assert3("bGrapheArc",bGraphe(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (bArc=kF,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			bArc=kV;//l'arc est effectivement présent dans gG
	return(bArc);
}//bGrapheArc

int nGrapheArc(graf *pgG,int sOrigine,int sDestination){//O(S)
	//si (sOrigine,sDestination) est un arc de gG,rend le numéro de cet arc (ce numéro est utilisé pour indexer sSuk[1..]);sinon,rend 0.
	int nArc;
	int aK;
	Assert3("nGrapheArc",bGraphe(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nArc=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nArc=aK;//l'arc est effectivement présent dans gG
	return(nArc);
}//nGrapheArc

char *sGrapheArc(graf *pgG,int aArcNumero){//O(S)
	//rend sous la forme d'un couple (sX,sY) les sommets sX et sY qui délimitent l'arc aArcNumero de pgG.
	char *sArc;
	int bEureka,sX;
	//Appel0("sGrapheArc");
		//tee("aArcNumero,pgG->nArcEnTout",aArcNumero,pgG->nArcEnTout);
		Assert2("sGrapheArc0",bGrapheSimple(pgG),bCroit(1,aArcNumero,pgG->nArcEnTout));
		for (bEureka=kF,sX=1;sX<=pgG->nSommetEnTout && !bEureka;sX++)
			if ( bCroit(pgG->aHed[sX],aArcNumero,pgG->aHed[sX+1]-1) ){
				sArc=sCouple(sX,pgG->sSuk[aArcNumero]);//l'arc est effectivement présent dans gG
				bEureka=kV;
			}
		Assert1("sGrapheArc1",bEureka);
		//sArc=sC2("Alpha","Beta");
	//Appel1("sGrapheArc");
	return(sArc);
}//sGrapheArc

void GrapheAreter(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter",sOrigine!=sDestination);
	GrapheArquer(pgG,sOrigine,sDestination);
	GrapheArquer(pgG,sDestination,sOrigine);
}//GrapheAreter

void GrapheAreter1(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter1",sOrigine!=sDestination);
	GrapheArquer1(pgG,sOrigine,sDestination,nCouleur);
	GrapheArquer1(pgG,sDestination,sOrigine,nCouleur);
}//GrapheAreter1

void GrapheAreter2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	Assert1("GrapheAreter1",sOrigine!=sDestination);
	GrapheArquer1(pgG,sOrigine,sDestination,nCouleurDirecte);
	GrapheArquer1(pgG,sDestination,sOrigine,nCouleurInverse);
}//GrapheAreter2

void GrapheArquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//tee("GrapheArquer",sOrigine,sDestination);
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (!bArquer){
		printf("Impossible d'ajouter l'arc(%d,%d) ——",sOrigine,sDestination);
		if (!bGrapheSommet(pgG,sOrigine)) printf("sommet origine inconnu.\n");
		if (!bGrapheSommet(pgG,sDestination)) printf("sommet destination inconnu.\n");
		if (bGrapheArc(pgG,sOrigine,sDestination)) printf("arc déjà présent.\n");
	}
	Assert1("GrapheArquer",bArquer);
}//GrapheArquer

void GrapheArquer1(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//teee("GrapheArquer10",sOrigine,sDestination,nCouleur);
	int bArquer1=bGrapheArqueR(pgG,sOrigine,sDestination,nCouleur);
	//teee("GrapheArquer11",sOrigine,sDestination,nCouleur);
	Assert1("GrapheArquer1",bArquer1);
}//GrapheArquer1

void GrapheArquer2(graf *pgG,int sOrigine,int sDestination,int nCouleurDirecte,int nCouleurInverse){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk. Déroute si échec.
	//teee("GrapheArquer10",sOrigine,sDestination,nCouleur);
	int bArquer1=bGrapheArqueR(pgG,sOrigine,sDestination,nCouleurDirecte);
	int bArquer2=bGrapheArqueR(pgG,sDestination,sOrigine,nCouleurInverse);
	Assert1("GrapheArquer2",bArquer1 && bArquer2);
}//GrapheArquer2

void GrapheArquer3(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCout){//O(A)
	//ajoute effectivt l'arc (sOrigine,sDestination) à pgG ——affecte les champs nArcEnTout,aHed,sSuk,nCapaMax,nCapaMin,nCout. Déroute si échec.
	int aK;
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	if (bArquer){
		aK=nGrapheArc(pgG,sOrigine,sDestination);
		Assert1("GrapheArquer30",aK>0);
		pgG->nCapaMin[aK]=nCapaMin;
		pgG->nCapaMax[aK]=nCapaMax;
		pgG->nCout[aK]=nCout;
	}
	Assert1("GrapheArquer31",bArquer);
}//GrapheArquer3

int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed, sSuk et coulh.
	int bArquer,aK,sX;
	Assert3("bGrapheArqueR0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	Assert1("bGrapheArqueR1",bGrapheSommet(pgG,sOrigine) );
	//te("sDestination",sDestination);
	Assert1("bGrapheArqueR2",bGrapheSommet(pgG,sDestination));
	if (bGrapheArc(pgG,sOrigine,sDestination)) d2(sOrigine,sDestination);
	Assert1("bGrapheArqueR3",!bGrapheArc(pgG,sOrigine,sDestination));//l'arc à créer existe déjà
	bArquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination) && (!bGrapheArc(pgG,sOrigine,sDestination));
	if (bArquer){
		//faire une place au nouvel arc en décalant les tableaux vers les index hauts
		for (aK=pgG->nArcEnTout;aK>=pgG->aHed[sOrigine+1];aK--){
			pgG->sSuk[aK+1]=pgG->sSuk[aK];
			pgG->coulh[aK+1]=pgG->coulh[aK];
			pgG->nCapaMin[aK+1]=pgG->nCapaMin[aK];
			pgG->nCapaMax[aK+1]=pgG->nCapaMax[aK];
			pgG->nCout[aK+1]=pgG->nCout[aK];
		}
		aK=pgG->aHed[sOrigine+1];
		pgG->sSuk[aK]=sDestination;
		pgG->coulh[aK]=nCouleur;
		for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX+1]++;
		pgG->nArcEnTout++;
	}
	Assert2("bGrapheArqueR9",bGraphe(pgG),bGrapheSimple(pgG));
	return(bArquer);
}//bGrapheArqueR

int bGrapheBiparti(graf *pgG){//O(A)
	//et rend la couleur du sommet sX dans pgG->sPer[sX]
	int bBiparti;
	int uC;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	graf *pgH;
	int aK,sX,sY,sZ;
	int nCouleur[kuGrapheSommetLim];
	int kbVoir=kF;
	if (kbVoir) Appel0("bGrapheBiparti");
		Assert3("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
		pgH=(graf *) malloc(sizeof(graf));
			//pgH soit la copie symétrisée de pgG (l'algo ci-dessous requiert un graphe symétrique).
				GrapheDupliquer(pgG,&pgH);
				GrapheSymetriser(pgH);
			//bBiparti:=pgH est bicolorable
				DequeAllouer(pgH->nSommetEnTout);//raze;O(pgH->nSommetEnTout)
					//décolorer tous les sommets de pgH
						for (sX=1;sX<=pgH->nSommetEnTout;sX++)
							nCouleur[sX]=cIncolore;
					for (bBiparti=kV,sZ=1;sZ<=pgH->nSommetEnTout;sZ++){
						if (nCouleur[sZ]==cIncolore){
							nCouleur[sZ]=cNoir;
							DequeEnfiler(sZ);
							if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgH->nSommetEnTout);
							while (nCardinal=nDequeCardinal(),nCardinal>0)
								for (uC=1;uC<=nCardinal;uC++){
									sX=sDequeDefiler();
									for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){
										sY=pgH->sSuk[aK];
										if (nCouleur[sY]==cIncolore){
											nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;
											DequeEnfiler(sY);
											if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgH->nSommetEnTout);
										} else if (nCouleur[sY]==nCouleur[sX])//cycle impair
											bBiparti=kF;
									}
								}//for
						}//if
					}//for
				DequeAllouer(0);
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->sPer[sX]=nCouleur[sX];
			//VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
		free(pgH);
	if (kbVoir) Appel1("bGrapheBiparti");
	return(bBiparti);
}//bGrapheBiparti

int bGrapheBipartiOuAfficherCycleImpair(graf *pgG){//O(A)
	int bBiparti;
	int sConflit0,sConflit1;
	int uC,aK;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int sX,sY,sZ;
	int nCoulh[kuGrapheSommetLim];
	int sPere[kuGrapheSommetLim];
	Assert4("bGrapheBiparti",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
		//razer nPere[]
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				sPere[sX]=0;
		//décolorer tous les sommets du graphe
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				nCoulh[sX]=cIncolore;
		//(sConflit0,sConflit1),sPere[]:=(sommet en conflit avec sConflit1,sommet 1 en conflit avec sConflit0), sPere[sY]=sX si sY a été coloré grâce à sX.
			for (sConflit0=0,sConflit1=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
				if (nCoulh[sZ]==cIncolore){
					nCoulh[sZ]=cNoir;
					sPere[sZ]=sZ;
					DequeEnfiler(sZ);
					while (nCardinal=nDequeCardinal(),nCardinal>0)
						for (uC=1;uC<=nCardinal;uC++){
							sX=sDequeDefiler();
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
								sY=pgG->sSuk[aK];
								if (nCoulh[sY]==cIncolore){
									nCoulh[sY]=(nCoulh[sX]==cNoir)? cRouge: cNoir;
									sPere[sY]=sX;
									DequeEnfiler(sY);
								} else if (nCoulh[sY]==nCoulh[sX]){//cycle impair
									sConflit1=sX;sConflit0=sY;}
							}
						}//for
				}//while
			}//for
		//bBiparti:=pgG est bicolorable,ie aucun sommet n'est en conflit de couleur avec un sommet adjacent.
			bBiparti=(sConflit0==0);
		if (!bBiparti){
			//tee("sConflit0,sConflit1",sConflit0,sConflit1);
			printf("Un cycle impair a été détecté:");
			//enfiler les sommets qui ont permis de colorer sConflit0
				sX=sConflit0;
				while(sX!=sPere[sX]){
					DequeEnfiler(sX);//n'enfile rien si déjà enfilé
					sX=sPere[sX];
				}
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDefiler());
	DequeAllouer(0);//fin du mode file;la Deque fonctionnant soit en mode pile soit en mode file,on ne peut mélanger les deux modes.
	DequeAllouer(pgG->nSommetEnTout);//début du mode pile
			//empiler les sommets qui ont permis de colorer sConflit1
				DequeEmpiler(sX=sConflit1);
				while(sX!=sPere[sX])
					DequeEmpiler(sX=sPere[sX]);
			//afficher ces sommets
				for (nCardinal=nDequeCardinal(),uC=1;uC<=nCardinal;uC++)
					printf(" %d",sDequeDepiler());
			printf(" %d.\n",sConflit0);//réaffiche sConflit0 afin de signifier qu'il s'agit bien d'un cycle, et non pas d'un chaîne.
		}
	DequeAllouer(0);
	return(bBiparti);
}//bGrapheBipartiOuAfficherCycleImpair

void GrapheBipartir(graf *pgG,int bBipartir){//O(A)
	//si bBipartir,négative dans pgG->aHed[] les sommets de l'ensemble X réputé biparti; sinon,dénégative pgG->aHed[].
	int bBiparti;
	int uC;
	int nCardinal;
	enum couleur {cIncolore,cNoir,cRouge};
	int aK,sX,sY,sZ;
	int nCouleur[kuGrapheSommetLim];
	int kbVoir=kF;
	if (kbVoir) Appel0("GrapheBipartir");
		FlipFlop("GrapheBipartir",bBipartir,&bGrapheBipartiR);
		if (bBipartir){
			Assert4("GrapheBipartir0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
			//bBiparti,nCouleur[]:=pgG est bicolorable,nCouleur[sX]:cRouge/cNoir si sX appartient à X/à Y.
				DequeAllouer(pgG->nSommetEnTout);//raze;O(pgG->nSommetEnTout)
					//décolorer tous les sommets de pgH
						for (sX=1;sX<=pgG->nSommetEnTout;sX++)
							nCouleur[sX]=cIncolore;
					for (bBiparti=kV,sZ=1;sZ<=pgG->nSommetEnTout;sZ++){
						if (nCouleur[sZ]==cIncolore){
							nCouleur[sZ]=cNoir;
							DequeEnfiler(sZ);
							if (kbVoir) VecteurVoir("nCouleur[] initial",&nCouleur[0],1,pgG->nSommetEnTout);
							while (nCardinal=nDequeCardinal(),nCardinal>0)
								for (uC=1;uC<=nCardinal;uC++){
									sX=sDequeDefiler();
									for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
										sY=pgG->sSuk[aK];
										if (nCouleur[sY]==cIncolore){
											nCouleur[sY]=(nCouleur[sX]==cNoir)? cRouge: cNoir;//cRouge,cNoir est la couleur des sommets de X/de Y.
											DequeEnfiler(sY);
											if (kbVoir) VecteurVoir("nCouleur[] général",&nCouleur[0],1,pgG->nSommetEnTout);
										} else if (nCouleur[sY]==nCouleur[sX])//cycle impair
											bBiparti=kF;
									}
								}//for
						}//if
					}//for
				DequeAllouer(0);
			Assert1("GrapheBipartir2",bBiparti);//pgG est réputé biparti
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//négative dans pgG->aHed[] les sommets de l'ensemble X colorés en cRouge
				pgG->aHed[sX]=iSignePres(nCouleur[sX]==cRouge,pgG->aHed[sX]);
			if (0){
				printf("Ensemble X obtenu:{");
					for (sX=1;sX<=pgG->nSommetEnTout;sX++)
						if (pgG->aHed[sX]<0)
							printf(" %d",sX);
				printf(" }.\n");
			}
	} else {for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=abs(pgG->aHed[sX]);
			Assert3("GrapheBipartir1",bGraphe(pgG),bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	}
	if (kbVoir) Appel1("bGrapheBiparti");
}//GrapheBipartir

void GrapheBipartitionne(graf *pgG){//O(A)
	//X devient X' et X"=X+nSommet,contrairt à GrapheBipartitionner(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;
	int aK;
	int nSommet;
	int kbVerifier=kF;
	int sX;
	Assert3("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbVerifier) GrapheVoir(pgG,"AVANT");
	nSommet=pgG->nSommetEnTout;
	nArc=pgG->nArcEnTout;
	//enfiler dans pgG->aHed[] nSommet nouveaux sommets X' devant les sommets X renommés nSommet+sX
		if (kbVerifier) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
		for (sX=nSommet;sX>=0;sX--)
			pgG->aHed[nSommet+sX+1]=nSommet+pgG->aHed[sX+1];//décale et donc translate les noms des sommets
		if (kbVerifier) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
		for (sX=nSommet;sX>0;sX--)
			pgG->aHed[sX]=sX;
		if (kbVerifier) VecteurVoir("aHed3",&pgG->aHed[0],1,2*nSommet+1);
	//enfiler dans pgG->sSuk[] un arc (X',X) pour chaque sommet X' créé
		if (kbVerifier) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc);
		for (aK=nArc;aK>0;aK--)
			pgG->sSuk[aK+nSommet]=pgG->sSuk[aK];//décale et pointe vers les sommets 1..nSommet,lesquels sont maintenant les nouveaux sommets
		for (aK=1;aK<=nSommet;aK++)
			pgG->sSuk[aK]=nSommet+aK;//les nouveaux sommets 1..nSommet pointent vers les anciens,ie ceux renommés nSommet+sX
		if (kbVerifier) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
	pgG->nSommetEnTout+=nSommet;
	pgG->nArcEnTout+=nSommet;
	if (kbVerifier) GrapheVoir(pgG,"APRES");
	/*if (0 && kbVerifier)
		GrapheSymetriser(pgG);*/
	Assert4("GrapheBipartitionne",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bGrapheBiparti(pgG));
}//GrapheBipartitionne

void GrapheBipartitionner(graf *pgG){//O(A)
	//X devient X' et X"=X+1,contrairt à GrapheBipartitionne(). Altère uniqt pgG->nSommetEnTout,pgG->nArcEnTout,aHed et sSuk.
	int nArc;//dit autrement,X est remplacé par l'arc (2*X-1,2*X).
	int aK;
	int kbScruter=kF;
	int nSommet;
	int sX,sY;
	Assert3("GrapheBipartitionner1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	if (kbScruter) Appel0("GrapheBipartitionner");
		if (kbScruter) GrapheVoir(pgG,"AVANT");
		nSommet=pgG->nSommetEnTout;
		nArc=pgG->nArcEnTout;
		//ménager entre les listes de sommets successeurs dédiés à chaque sommet source 1 arc par nouveau sommet,en terminant par un nouvel arc en pgG->sSuk[1]. 
			if (kbScruter) VecteurVoir("sSuk4",&pgG->sSuk[0],1,nArc+nSommet);
			for (sX=nSommet;sX>0;sX--){
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX]=2*sY-1;
				}
				if (kbScruter) tee("aK,sX",aK,sX);
				pgG->sSuk[aK+sX]=2*sX;//nouvel arc,notamment en pgG->sSuk[1] puisque aK=0 quand sX=1.
			}
			if (kbScruter) VecteurVoir("sSuk5",&pgG->sSuk[0],1,nArc+nSommet);
		//interclasser les sommets originaux de sorte que X'=X+1 pour tout X
			if (kbScruter) VecteurVoir("aHed1",&pgG->aHed[0],1,nSommet+1);
			//te("2*nSommet+2",2*nSommet+2);
			Assert1("GrapheBipartitionner3",2*nSommet+2<kuGrapheSommetLim);//pr li+3;sinon,ajouter un "if"
			for (sX=nSommet;sX>=0;sX--){
				pgG->aHed[2*sX+1]=pgG->aHed[sX+1]+sX;
				pgG->aHed[2*sX+2]=pgG->aHed[2*sX+1]+1;
			}
			if (kbScruter) VecteurVoir("aHed2",&pgG->aHed[0],1,2*nSommet+1);
			if (kbScruter) VecteurVoir("sSuk6",&pgG->sSuk[0],1,nArc+nSommet);
		pgG->nSommetEnTout+=nSommet;
		pgG->nArcEnTout+=nSommet;
		if (kbScruter) GrapheVoir(pgG,"APRES");
		if (0 && kbScruter)
			GrapheSymetriser(pgG);
		Assert4("GrapheBipartitionner9",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),!kbScruter || bGrapheBiparti(pgG));
	if (kbScruter) Appel1("GrapheBipartitionner");
}//GrapheBipartitionner

void GrapheCheminE(graf *pgG,int sSource,int sTrappe,int bCheminer,int nMesure,int gcMode){
	//affiche s'il existe le chemin qui relie sSource à sTrappe,sa grandeur (ie une longueur ou une largeur,selon gcMode) et sa valeur nMesure.
	int uS,sX;
	Assert2("GrapheCheminE",bBool(bCheminer),pgG->sPer[sSource]==sSource);
	if (bCheminer){
		//tee("sSource,sTrappe",sSource,sTrappe);
		printf("    Chemin le plus %s du sommet %d au sommet %d: (",sItem4(gcMode,"court","large","long","court en moyenne"),sSource,sTrappe);
		//afficher sommet par sommet le chemin qui relie sSource à sTrappe ——en partant de sSource:
			DequeAllouer(pgG->nSommetEnTout);
				//empiler les sommets car ils jalonnent le chemin à afficher dans le sens inverse du sens requis pour l'affichage
					sX=sTrappe;
					While(pgG->nSommetEnTout);
					while ( bWhile("GrapheCheminE",pgG->sPer[sX]!=sX) ){
						DequeEmpiler(sX);
						sX=pgG->sPer[sX];
					}
					DequeEmpiler(sX);
				//afficher les sommets en les dépilant: ils se présentent dans l'ordre requis pour l'affichage
					for (uS=nDequeCardinal();uS>0;uS--){
						sX=sDequeDepiler();
						printf("%d",sX);
						if (uS>1)
							printf(",");
					};
			DequeAllouer(0);
		printf(").\n");
		if (gcMode==grCheminLePlusLarge)
			printf("    Largeur de ce chemin: %d mètres.\n",nMesure);
		else printf("    Longueur de ce chemin: %d km.\n",nMesure);
	}
	else printf("    Il n'existe pas de chemin entre les sommets %d et %d.\n",sSource,sTrappe);
}//GrapheCheminE

int bGrapheCheminE(graf *pgG,int sSource,int sTrappe){
	//rend vrai ssi gG.sPer[] décrit un chemin qui relie sSource à sTrappe.
	int bChemine;
	int nSommet;
	int sX,sY;
	for (bChemine=kF,sX=sTrappe,nSommet=0;nSommet<=pgG->nSommetEnTout;nSommet++){
		bChemine=bChemine || (sX==sSource);
		sY=pgG->sPer[sX];//facilite le débogage
		sX=sY;
	}
	return(bChemine);
}//bGrapheCheminE

int nGrapheChemineR (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(S2)
	//rend la longueur du plus court chemin de sSource à sTrappe, (algo:Dijkstra sans tas)
	const int kbVoirPere=kF;
	const int kuInfini=1e5;
	int nD;//distance courante de sSource au sommet le plus proche de sSource
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int sProche;
	int uSommet;
	int sX;
	int sY;
	if (kbVoirPere) Appel0("nGrapheChemineR");
	*pnComplexiteh=0;
	//initialiser bFait[], nDist[] et pgG->sPer[].
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			bFait[sX]=0;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			nDist[sX]=kuInfini;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			pgG->sPer[sX]=0;
	nDist[sSource]=0;//distance entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		//sProche:=numéro du sommet le plus proche de sSource, ou 0 si aucun nouveau sommet ne peut être atteint depuis sSource)
			for (sProche=0,nD=kuInfini,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if (*pnComplexiteh++,!bFait[sX] && nD>nDist[sX])
					nD=nDist[sProche=sX];
		sX=sProche;
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX réduit la distance entre sSource et sY 
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; *pnComplexiteh++,aK++) {
				sY=pgG->sSuk[aK];
				nDistanceParX=nDist[sX]+pgG->nCout[aK];
				if ( nDist[sY]>nDistanceParX ) {//passer par sX est plus court 
					nDist[sY]=nDistanceParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus court qui relie sY à sSource.
				}
			}
			bFait[sX]=kV;
		}
	}//à chaque tour, calculer sProche coûte O(S). Chaque arc étant consulté 1 fois au plus dans "for aK",la complexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (kbVoirPere) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbVoirPere) Appel1("nGrapheChemineR");
	return(nDist[sTrappe]);
}//nGrapheChemineR

int bGrapheCheminerAuLargE(graf *pgG,int sSource,int sTrappe,int bAfficher){//O(S2)
	//calcule et affiche si bAfficher le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas)
	int bChemine=0,nLargeur;
	Assert1("bGrapheCheminerAuLargE",bBool(bAfficher));
	nLargeur=nGrapheCheminerAuLargE(pgG,sSource,sTrappe);
	bChemine=bGrapheCheminE(pgG,sSource,sTrappe);
	if (bAfficher)
		GrapheCheminE(pgG,sSource,sTrappe,bChemine,nLargeur,grCheminLePlusLarge);
	return(bChemine);
}//bGrapheCheminerAuLargE

int nGrapheCheminerAuLargE (graf *pgG,int sSource,int sTrappe){//O(S2)
	//calcule le plus large chemin de sSource à sTrappe, (algo:Dijkstra sans tas);le coût d'1 arc est la largeur de l'arc,eg la largeur minimale d'une route.
	#define kbCheminerAuLarge kF
	const int kuInfini=1e5;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int mLargeurMax;//capacité maximale des chemins qui relient sSource au sommet le plus proche de sSource
	int mLargeur[1+pgG->nSommetEnTout];
	int nLargeurParX;
	int sProche;
	int uSommet;
	int sX,sY;
	//t("GrapheCheminerAuLargE");
	if (kbCheminerAuLarge) Appel1("nGrapheCheminerAuLargE");
	//initialiser bFait[], nDist[] et pgG->sPer[].
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			bFait[sX]=0;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			mLargeur[sX]=-1;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			pgG->sPer[sX]=0;
	mLargeur[sSource]=kuInfini;//largeur entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		//sProche:=numéro du sommet situé sur la route la plus large qui mène à sSource, ou 0 si aucun nouveau sommet n'est trouvé)
			for (sProche=0,mLargeurMax=-1,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if (!bFait[sX] && mLargeurMax<mLargeur[sX])
					mLargeurMax=mLargeur[sProche=sX];
		//tee("sProche,mLargeurMax",sProche,mLargeurMax);
		sX=sProche;
		if (sX!=0) {//pour tout voisin sY de sX,rectifier nDist[sY] si passer par sX permet de cheminer de sSource à sY par un chemin plus large
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];
				Assert1("GrapheCheminerAuLargE",bCroit(0,pgG->nCout[aK],kuInfini-1));//largeur de l'arc
				nLargeurParX=yMin(mLargeur[sX],pgG->nCout[aK]);
				if ( mLargeur[sY]<nLargeurParX ) {//la route qui relie sSource à sY ne passe pas par sX; elle est moins large que celle qui relie sSource à sY en passant par sX.
					mLargeur[sY]=nLargeurParX;
					pgG->sPer[sY]=sX;//sX est situé sur le chemin le plus large qui relie sY à sSource.
					//teeee("sY,sX,mLargeur[sY],pgG->nCout[aK]",sY,sX,nLargeurParX,pgG->nCout[aK]);
				}
			}
			bFait[sX]=kV;
		}
	}//à chaque tour, calculer sProche coûte O(S). Chaque arc étant consulté 1 fois au plus dans "for aK",la complexité au pire vaut sup( O(S*S),O(A) ), dc O(S2)
	if (kbCheminerAuLarge) VecteurVoir("mLargeur",&mLargeur[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
	if (kbCheminerAuLarge) Appel1("nGrapheCheminerAuLargE");
	return(mLargeur[sTrappe]);
}//nGrapheCheminerAuLargE

int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh){//O(SlgS+A)
	//Algo plus court chemin, Dijkstra sans tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	Assert1("bGrapheCheminerCourt",bBool(bCheminAfficher));
	nCheminLg=nGrapheChemineR(pgG,sSource,sTrappe,pnComplexiteh);
	bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
	if (bCheminAfficher)
		GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,nCheminLg,grCheminLePlusCourt);
	return(bCheminerCourt);
}//bGrapheCheminerCourt

int bGrapheCheminerCourtTaS(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh){//O(S2)
	//Algo plus court chemin, Dijkstra AVEC tas;distances élémentR dans pgG->nCout[].
	int bCheminerCourt=0,nCheminLg;
	//Appel0("bGrapheCheminerCourtTaS");
		Assert1("bGrapheCheminerCourtTaS",bBool(bCheminAfficher));
		nCheminLg=nGrapheCheminerTaS(pgG,sSource,sTrappe,pnComplexiteh);
		bCheminerCourt=bGrapheCheminE(pgG,sSource,sTrappe);
		if (bCheminAfficher)
			GrapheCheminE(pgG,sSource,sTrappe,bCheminerCourt,nCheminLg,grCheminLePlusCourt);
	//Appel1("bGrapheCheminerCourtTaS");
	return(bCheminerCourt);
}//bGrapheCheminerCourtTaS

int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int bCheminAfficher,int *pnComplexiteh){//O(S2)
	//vrai ssi un plus long chemin de sSource à sTrappe est calculable ds pgG (distances élémentR dans pgG->nCout[]).
	int bCheminerLong=kV,nCheminLg,aK;
	GrapheInverser(pgG);
	bCheminerLong=!bGrapheCircuite(pgG);
	if (bCheminerLong){
		//négativer les coûts des arcs
			for (aK=1; aK<=pgG->nArcEnTout; aK++)
				pgG->nCout[aK] = - pgG->nCout[aK];
		nCheminLg=nGrapheChemineR(pgG,sSource,sTrappe,pnComplexiteh);
		//restaurer les coûts des arcs
			for (aK=1; aK<=pgG->nArcEnTout; aK++)
				pgG->nCout[aK] = - pgG->nCout[aK];
		bCheminerLong=bGrapheCheminE(pgG,sSource,sTrappe);
		if (bCheminAfficher)
			GrapheCheminE(pgG,sSource,sTrappe,bCheminerLong,nCheminLg,grCheminLePlusLong);
	}
	else if (bCheminAfficher)
		printf("Le chemin le plus long n'est pas calculable car le graphe contient un circuit.\n");
	return(bCheminerLong);
}//bGrapheCheminerLong

int nGrapheCheminerTaS (graf *pgG,int sSource,int sTrappe,int *pnComplexiteh){//O(AlgS)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo de plus court chemin exécuté: Dijkstra AVEC tas.
	const int kuInfini=9999;
	int nDist[1+pgG->nSommetEnTout];
	int nDistanceParX;//entier Naturel positif ou nul,donc préfixe "n".
	int bFait[1+pgG->nSommetEnTout];//b comme booléen
	int aK;//index d'Arc,donc préfixe "a".
	int sProche;//index de Sommet,donc préfixe "s".
	int uSommet;//entier naturel supérieur ou égal à Un,donc préfixe "u".
	int sX,sY;
	//bFait[], nDist[] et pgG->sPer[] soient initialisés.
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	*pnComplexiteh=3*pgG->nSommetEnTout;//coût initialisations
	TasAllouer(pgG->nSommetEnTout);
		//initialiser le tas (le coût total du module Tas, en terme de complexité algorithmique, sera ajouté en fin de routine grâce à nTasCout() 
			for (sX=1; sX<=pgG->nSommetEnTout; sX++)
				TasInsererValuer(sX,kuInfini);
			TasActualiser(sSource,0);
			//TasVoir("Tas après initialisation");
		nDist[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE() chargé de cheminer sur le plus court chemin grâce à sPer[]
		for (uSommet=1; uSommet<=pgG->nSommetEnTout; (*pnComplexiteh)++, uSommet++) {//O(AlgS)
			//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
				//TasVoir("Tas avant extraction");
				sProche=eTasExtraire();//O(lgS)
			sX=sProche;
			if (sX!=0) {
				for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; (*pnComplexiteh)++, aK++) {
					sY=pgG->sSuk[aK];//chaque arc (sX,sY) est examiné 1 fois (si accessible par un chemin depuis sSource)
					nDistanceParX=nDist[sX]+pgG->nCout[aK];
					if ( nDist[sY]>nDistanceParX ) {
						nDist[sY]=nDistanceParX;
						//d2(sY,nDistanceParX);
						TasActualiser(sY,nDistanceParX);//O(lgS) par arc (sX,sY)
						//TasVoir("Tas après TasActualiser");
						pgG->sPer[sY]=sX;
					}
				}
				bFait[sX]=kV;//ie l'opportunité de passer par sX pour atteindre au plus court un sommet de pgG depuis sSource a été exploitée.
			}
		}//chaque sProche est obtenu en O(lgS) et chaque arc est consulté 1 fois, soit une complexité au pire égale à sup( O(S*lS),O(AlgS) ), dc O(AlgS).
		//VecteurVoir("sPer",pgG->sPer,1,pgG->nSommetEnTout);
		(*pnComplexiteh)+=nTasCout();//coût total du tas entre 2 allocations, donc à ajouter juste avant TasAllouer(0) qui remet ce coût à 0.
	TasAllouer(0);
	return(nDist[sTrappe]);
}//nGrapheCheminerTaS

int bGrapheCircuite(graf *pgG){//O(A)
	//vrai ssi gG contient un circuit (algo de Marimont)
	int nCard;//n comme Naturel,dc 0 ou plus
	int bCircuite=kF;
	int uE;//E comme Elément;u comme Un ou plus
	int aK;//a comme Arc
	int nMarq[1+pgG->nSommetEnTout];
	int nMarque;
	int nPred[1+pgG->nSommetEnTout];
	int nSucc[1+pgG->nSommetEnTout];
	int sX,sY;//s comme Sommet
	//Appel0("bGrapheCircuite");
		Assert2("bGrapheCircuite1",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim));
		if (pgG->nSommetEnTout>1){//algo de MARIMONT
			//nSucc[sX],nPred[sX] et nMarq[sX] soit le nombre total de successeurs,de prédécesseurs ainsi que la marque du sommet courant sX
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
					nSucc[sX]=pgG->aHed[sX+1]-pgG->aHed[sX];
					nPred[sX]=pgG->aDeh[sX+1]-pgG->aDeh[sX];
					nMarq[sX]=0;//ie sX n'est pas marqué
					Assert2("bGrapheCircuite2",nSucc[sX]>=0,nPred[sX]>=0);
				}
			DequeAllouer(pgG->nSommetEnTout);//raze;O(nSommetEnTout)
				//enfiler les sommets sources (ie sans prédécesseurs) et trappes (ie sans successeurs) en les marquant avec nMarque égal à 1
					for (nMarque=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
						if ( !nPred[sX] || !nSucc[sX] ){
							nMarq[sX]=nMarque;
							DequeEnfiler(sX);//O(1)
						}
				While(pgG->nSommetEnTout);
				while (bWhile("bGrapheCircuite3",(nMarque++,nCard=nDequeCardinal())) ){//nDequeCardinal() est en O(1) et le while en O(A) ——justification en fin de while
					for (uE=1;uE<=nCard;uE++){//NB les appels à la deque ds ce for vont modifier nDequeCardinal() mais pas nCard évalué li-1 
						sX=sDequeDefiler();//O(1)/
						if (!nPred[sX])//si vrai,sX est une source;éliminer un arc (sX,sY),c'est retirer un prédécesseur de sY via "nPred[sY]--"
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//O(degré sortant de sX)
								if (!nMarq[sY=pgG->sSuk[aK]]){
									nPred[sY]--;
									Assert1("bGrapheCircuite4",nPred[sY]>=0);
									if (!nPred[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										DequeEnfiler(sY);//O(1)
									}
								}
							}
						else for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)//O(degré entrant de sX)
								if (!nMarq[sY=pgG->sKus[aK]]){
									nSucc[sY]--;
									Assert1("bGrapheCircuite5",nSucc[sY]>=0);
									if (!nSucc[sY]){ //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										nMarq[sY]=nMarque;
										DequeEnfiler(sY);//O(1)
									}
								}
					}//grâce à nMarq[],tt sommet est enfilé (et dc défilé) 1 fois Au plus, dc ses arcs examinés 1 fois Au plus,dc while est en O(A).
				}
			DequeAllouer(0);//O(1) Si vous ôtez cette ligne au vu du code de Deque,vous acceptez qu'une modification dudit code plante votre logiciel.
			for (bCircuite=0,sX=1; sX<=pgG->nSommetEnTout; sX++)//O(S);zéroter bCircuite ici initialise à l'évidence le bCircuite situé li+1 avant "||".
				bCircuite=bCircuite||!nMarq[sX];//quitter le for dès bCircuite vrai complique le code et n'améliore pas la borne O(A):mauvaise idée.
		}
	else bCircuite=kF;//redite,mais ainsi,li+1,bCircuite est l'évidence valué; chercher sa valeur initiale en déclarations est inutile,dc gain de temps.
	//Appel1("bGrapheCircuite");
	return(bCircuite);
}//bGrapheCircuite

void GrapheCircuiterAuMieux(graf *pgG){
	//calcule et affiche un circuit de longueur moyenne minimale (moyennée sur le nombre d'arcs) dans pgG,réputé fortement connexe.
	const int kbAff = kF;
	const int kuPoidsInfini=kE4;
	int aK,nK,nK0,uK,aL,nMin,nPoidsTotal,sX,sY,sY0,sZ;
	float rMin,rMax,rMoyenne;
	int nSommet=pgG->nSommetEnTout;
	int nPoids[1+nSommet][1+nSommet];
	int sPere[1+nSommet][1+nSommet];
	Assert1("GrapheCircuiterEnMoyennE",nGrapheComposanteFortementConnexe(pgG)==1);
	//les poids sont les couleurs du graphe
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->nPoids[aK]=pgG->coulh[aK];
	//nPoids[0][] soit initialisé
		GrapheInverser(pgG);//pr accéder en O(1) aux prédécesseurs
		for (sX=1;sX<=nSommet;sX++)
			nPoids[0][sX]=kuPoidsInfini;
		nPoids[0][1]=0;
		for (sY=1;sY<=nSommet;sY++)
			for (aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];
				if (sX==1)
					nPoids[0][sY]=pgG->nPoids[aK];
			}//for aL
	//nPoids[1..nSommet][] et sPere[1..nSommet][] soient affectés:
		for (uK=1;uK<=nSommet;uK++)
			for (sY=1;sY<=nSommet;sY++){
				for (nMin=kuPoidsInfini,aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
					sX=pgG->sKus[aL];
					aK=pgG->aInv[aL];
					nPoidsTotal=nPoids[uK-1][sX]+pgG->nPoids[aK];
					if (nPoidsTotal<nMin){
						nMin=nPoidsTotal;
						sZ=sX;//pour sPere li+4
					}
				}//for aL
				nPoids[uK][sY]=nMin;
				sPere[uK][sY]=sZ;
			}
		if (kbAff) for (nK=0;nK<=nSommet;nK++)
			VecteurVoir(sC3("nSommet[",sEnt(nK),"]"),nPoids[nK],1,nSommet);
		if (kbAff) for (uK=1;uK<=nSommet;uK++)
			VecteurVoir(sC3("sPere[",sEnt(uK),"]"),sPere[uK],1,nSommet);
	//sY0,nK0:=index caractéristiques du circuit optimal
		for (rMin=kuPoidsInfini,sX=1;sX<=nSommet;sX++){
			for (sY=0,rMax=0.0,nK=0;nK<nSommet;nK++){
				rMoyenne=((nPoids[nSommet][sX]-nPoids[nK][sX])*1.0)/(nSommet-nK);
				if (rMoyenne>rMax){
					sY=sX;
					uK=nK;
					rMax=rMoyenne;
				}
			}
			if (rMax<rMin){
				sY0=sY;
				nK0=uK;
				rMin=rMax;
			}
		}
	//tr("rMin",rMin);
	//teee("moyenne de 1 pour sY0,nPoidsTotal0,nArc0",sY0,nPoidsTotal0,nArc0);
	//afficher le circuit optimal de longueur moyenne minimale:
		printf("Circuit optimal: ( ");
			for (uK=nSommet-1,sX=sPere[uK][sY0];uK>=nK0;printf("%d ",sX),uK--)
				sX=sPere[uK][sX];
		printf("), de longueur moyenne minimale égale à %.2f.\n",rMin);
}//GrapheCircuiterAuMieux

void GrapheCliquer(graf *pgG,int uCliqueTaille){
	//empile dans pgG une clique à uCliqueTaille sommets.
	int sX,sY;
	const int kbVerif = kF;
	Assert1("GrapheCliquer",uCliqueTaille>0);
	int nSommet=pgG->nSommetEnTout;
	//te("nSommettttt",nSommet);
	for (sX=1;sX<=uCliqueTaille;sX++)
		pgG->aHed[nSommet+sX+1]=pgG->aHed[nSommet+sX];
	pgG->nSommetEnTout+=uCliqueTaille;
	if(kbVerif) te("gG->nSommetEnTout",pgG->nSommetEnTout);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	for (sX=nSommet+1;sX<=pgG->nSommetEnTout;sX++)
		for (sY=nSommet+1;sY<=pgG->nSommetEnTout;sY++)
			if (sX!=sY)
				GrapheArquer(pgG,sX,sY);
	if(kbVerif) VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	if(kbVerif) VecteurVoir("pgG->sSuk",pgG->sSuk,1,pgG->nArcEnTout);
}//GrapheCliquer

void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur){
	//colore l'arc (sOrigine,sDestination) avec la nCouleur
	int aK;
	Assert4("GrapheColorer0",bGrapheSommet(pgG,sOrigine), bGrapheSommet(pgG,sDestination), sOrigine!=sDestination, bCroit(0,nCouleur,knGrapheCouleurMax));
	for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++){
		if (pgG->sSuk[aK] == sDestination)
			pgG->coulh[aK]=nCouleur;
	}
}//GrapheColorer

void GrapheCompletCreerPondereR(int nSommet,graf **ppgG){
	int aK,sX,sY;
	//appel: DijkstraAvecOuSansTasCompareR()
	//Appel0("GrapheCompletCreerPondereR");
		GrapheCreer(-nSommet,ppgG);
		for (sX=1;sX<=nSommet;sX++)
			for (sY=1;sY<=nSommet;sY++)
				if (sX!=sY)
					GrapheArquer(*ppgG,sX,sY);
		//GrapheVoir(*ppgG,"Graphe complet créé");
		Assert1("GrapheCompletCreerPondereR1",bGrapheSimple(*ppgG));
		for (sX=1;sX<=nSommet;sX++)
			for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
				sY=(*ppgG)->sSuk[aK];
				(*ppgG)->nCout[aK]=kE4-sX-nSommet*sY;
			}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
		//si nSommet=6, faire que les plus courts chemins passent par les arcs (1,6),(6,5),(5,4),(4,3),(3,2) et (2,1)
			for (sX=1;sX<=nSommet;sX++)
				for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
					sY=(*ppgG)->sSuk[aK];
					if (sY==sX-1 || sX==1 && sY==nSommet)
						(*ppgG)->nCout[aK]=sX;
				}
		Assert1("GrapheCompletCreerPondereR4",bGrapheSimple(*ppgG));
	//Appel1("GrapheCompletCreerPondereR");
}//GrapheCompletCreerPondereR

int nGrapheComposanteConnexe(graf *pgG){//O(A)
	//rend le nombre de composantes connexes du graphe non orienté associé à pgG 
	int nCC[1+pgG->nSommetEnTout];//numéro de composante connexe
	int nCCcourante,nComposanteConnexe=0;
	graf *pgH;
	int aK,sX,sY,sZ,uS;
	Assert2("nGrapheComposanteConnexe",bGrapheAmorceR,bGrapheSimple(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		//pgH soit le graphe symétrique associé à pgH
			GrapheDupliquer(pgG,&pgH);//O(A)
			GrapheSymetriser(pgH);//O(A)
		VecteurRazer(nCC,1,pgG->nSommetEnTout);//O(S)
		DequeAllouer(pgG->nSommetEnTout);//O(1)
			for (nCCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//O(A)
				if (nCC[sZ]==0){//attribuer la composante connexe nCCcourante+1 à sZ et aux sommets atteints depuis sZ dans pgH symétrique 
					DequeEnfiler(sZ);//sZ n'est enfilé qu'une fois
					nCCcourante++;
					While(1+pgH->nSommetEnTout);
					while (bWhile("nGrapheComposanteConnexe",!bDequeVide())){
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							nCC[sX]=nCCcourante;
							for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//les successeurs de sY ne sont passés en revue qu'une fois
								sY=pgH->sSuk[aK];
								if (nCC[sY]==0)//sY n'est enfilé qu'une fois
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//if
		DequeAllouer(0);//O(1)
	free(pgH);
	nComposanteConnexe=nCCcourante;
	//te("nComposanteConnexe",nComposanteConnexe);
	return(nComposanteConnexe);
}//nGrapheComposanteConnexe

int nGrapheComposanteFortementConnexe(graf *pgFortementConnexe){//O(SA)
	//rend le nombre de composantes fortement connexes (CFC) de pgG et stocke dans pgG->sPer[] le numéro de CFC attribué à chacun des sommets. 
	int bAtteint[2][1+pgFortementConnexe->nSommetEnTout];
	int nCFC[1+pgFortementConnexe->nSommetEnTout];//numéro de composante fortement connexe attribué au sommet courant
	int nCFCcourante;
	int nComposanteFortementConnexe=0;
	graf *pgG=pgFortementConnexe;
	int aK,sX,sY,sZ,uS;
	int cPasse,bVoir = kF;
	Assert2("nGrapheComposanteFortementConnexe",bGrapheAmorceR,bGrapheSimple(pgG));
	GrapheInverser(pgG);//mm si déjà fait
	//GrapheViseR(pgG,"Graphe inversé");
	VecteurRazer(nCFC,1,pgG->nSommetEnTout);//O(S)
	DequeAllouer(1+pgG->nSommetEnTout);//O(1)
		for (nCFCcourante=0,sZ=1;sZ<=pgG->nSommetEnTout;sZ++)//S*sup(S,A),dc O(SA)
			if (nCFC[sZ]==0){//marquer parmi tous les sommets atteints depuis sZ dans pgG ceux qui mènent à sZ dans le graphe inversé de pgG
				//if (bVoir) te("sZ",sZ);
				VecteurRazer(bAtteint[0],1,pgG->nSommetEnTout);//O(S)
				VecteurRazer(bAtteint[1],1,pgG->nSommetEnTout);//O(S)
				for (cPasse=0;cPasse<=1;cPasse++){//cPasse=0: accès au graphe direct;cPasse=1: accès au graphe inversé (champs aDeh et sKus)
					DequeRazer(1+pgG->nSommetEnTout);
					DequeEnfiler(sZ);
					While(pgG->nSommetEnTout);
					while (bWhile("nGrapheComposanteFortementConnexe",!bDequeVide())){//O(A)
						for (uS=1;uS<=nDequeCardinal();uS++){
							sX=sDequeDefiler();
							bAtteint[cPasse][sX]=nCFCcourante+1;
							//if (bVoir) tee("cPasse,sX défilé",cPasse,sX);
							for (aK=(cPasse==0)? pgG->aHed[sX]: pgG->aDeh[sX];(cPasse==0)? aK<pgG->aHed[sX+1]: aK<pgG->aDeh[sX+1];aK++){
								sY=(cPasse==0)? pgG->sSuk[aK]: pgG->sKus[aK];
								if (!bAtteint[cPasse][sY])
									DequeEnfiler(sY);
							}
						}//for uS
					}//while
				}//for cPasse
			//if (bVoir) TableauVoir("bAtteint",bAtteint,0,1,1,pgG->nSommetEnTout);
			for (nCFCcourante++,sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (bAtteint[0][sX] && bAtteint[1][sX])
					nCFC[sX]=nCFCcourante;
		}
	DequeAllouer(0);//O(1)
	if (bVoir) VecteurVoir("Numéro de composante attribuée à chaque sommet",nCFC,1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->sPer[sX]=nCFC[sX];
	nComposanteFortementConnexe=nCFCcourante;
	if (bVoir) te("Nombre de composantes fortement connexes",nComposanteFortementConnexe);
	return(nComposanteFortementConnexe);
}//nGrapheComposanteFortementConnexe

int nGrapheCouleur(graf *pgG,int sOrigine,int sDestination){//O(S)
	//rend la couleur réputée non nulle de l'arc(sOrigine,sDestination), ou 0 si arc inexistant
	int aK;
	int nCouleur;
	Assert4("nGrapheCouleur",bGrapheAmorceR,bGrapheSimple(pgG),bGrapheSommet(pgG,sOrigine),bGrapheSommet(pgG,sDestination));
	for (nCouleur=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination)
			nCouleur=pgG->coulh[aK];
	return(nCouleur);
}//nGrapheCouleur

void GrapheCouvrir(graf *pgG){
	//rend dans pgG->sPer la description d'un acpm qui couvre pgG.
	GrapheCouvrirAvecKruskaL(pgG,!k1Afficher,!k1PerformanceCompareR);
}//GrapheCouvrir

void GrapheCouvrirAvecKruskaL(graf *pgG,int bAfficher,int bPerformanceComparer){
	//génère un graphe "intéressant" à nSommetEnTout sommets puis affiche l'acpm calculé selon bAlgoKruskalSinonAlgoPrim.
	const int kuModeMax=3;
	int nComplexiteh[1+kuModeMax],nLg[1+kuModeMax];
	int nLgMax,nMode;
	//const int k1Abe=kV;
	const int k1Logn=kV;
	const int k1Tas=kV;
	tb("bPerformanceComparer",bPerformanceComparer);
	//Appel0("GrapheCouvrirAvecKruskaL");
		//4 arbres couvrants sont calculés: d'abord 2 arbres de poids minimal sans tas, puis 2 arbres de poids minimal avec tas
			VecteurRazer(nComplexiteh,0,kuModeMax);
			if (bPerformanceComparer){//comparer les caractéristiques de l'algorithme optimisé avec des variantes non optimisées ou de poids quelconque.
				nComplexiteh[0]=nGrapheCouvrirAvecKruskaL(pgG,!k1Logn,!k1Tas,bAfficher);//arbre couvrant n°1,aucune optimisation
				nComplexiteh[1]=nGrapheCouvrirAvecKruskaL(pgG,k1Logn,!k1Tas,bAfficher);//arbre couvrant n°2,hauteur des anti-arbres optimisée
				nComplexiteh[2]=nGrapheCouvrirAvecKruskaL(pgG,!k1Logn,k1Tas,bAfficher);//arbre couvrant n°3;utilise un minimier
			}
			nComplexiteh[3]=nGrapheCouvrirAvecKruskaL(pgG,k1Logn,k1Tas,bAfficher);//arbre couvrant n°4;algo le plus efficace sur un graphe dense
			//VecteurVoir("nComplexiteh",nComplexiteh,0,kuModeMax);
			if (bPerformanceComparer){
				Titrer("Comparaison des algorithmes de calcul d'acpm par la méthode de Kruskal");
				printf("%sOption    Forêt optimisée    Tas (minimier)    Durée du calcul\n",sTab(1));
				for (nLgMax=0,nMode=0;nMode<=kuModeMax;nMode++)
					nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
				//VecteurVoir("nLg",nLg,0,kuModeMax);te("nLgMax",nLgMax);
				for (nMode=0;nMode<=kuModeMax;nMode++)
printf("%s  %d           %s                 %s          %s%s\n",sTab(1),nMode,sOui(nMode%2),sOui(nMode/2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
			}
	//Appel1("GrapheCouvrirAvecKruskaL");
}//GrapheCouvrirAvecKruskaL

int nGrapheCouvrirAvecKruskaL(graf *pgG,int bLogn,int bTas,int bAfficher){
	//calcule et affiche un arbre couvrant (résultat ds pgG->nVal[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Kruskal. Rend une mesure de sa complexité.
	int aArete,nAreteEnTout,nAreteTotalDansArbre;
	int nComplexiteh=0,aK;
	int nHauteur,nHauteurMax;
	int nPoids,nPoids0,nPoidsTotal,nVersus;
	int sX,sY,ccX,ccY;
	//Appel0("nGrapheCouvrirAvecKruskaL");
		ForetINITIALISER(pgG->nSommetEnTout,bLogn);
			//razer arbre couvrant: pgG->nVal[]=0 
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					pgG->nVal[aK]=0;
			if (bTas){
				TasINITIALISER();
				TasAllouer(pgG->nArcEnTout);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						TasInsererValuer(aK,pgG->nCout[aK]);
				//TasVoir("initialisation");
			} else {//tri non optimisé,eg tri par insertion.
				VecteurTrier(pgG->nCout,1,pgG->nArcEnTout);
				nComplexiteh=pgG->nArcEnTout*pgG->nArcEnTout;
				//te("nComplexiteh par insertion",nComplexiteh);
			}
			printf("Exécution de l'algorithme de Kruskal %s minimier et %s optimisation de la forêt:\n",sChoix(bTas,"avec","sans"),sChoix(bLogn,"avec","sans")); 
			nAreteEnTout=pgG->nArcEnTout;
			for (nPoids0=0,aK=1;aK<=nAreteEnTout;aK++){
				//aArete=aAreteSuivante():
				//tb("bTas",bTas);
					if (bTas){
						aArete=eTasExtraire();
						//TasVoir("");
					} else aArete=aK;
				nPoids=pgG->nCout[aArete];
				//te("poids courant",nPoids);
				Assert1("nGrapheCouvrirAvecKruskaL",!bTas || nPoids0<=nPoids);//vérifie que eTasExtraire() rend des arêtes successives de poids croissants
				nPoids0=nPoids;
				sX=pgG->nPhi[aArete];
				sY=pgG->sSuk[aArete];
				//teee("aArete,sX,sY",aArete,sX,sY);
				ccX=nForetComposante(sX);
				ccY=nForetComposante(sY);
				if (ccX!=ccY){
					//printf("    Arête (%d,%d) prise.\n",sX,sY);
					ForetFusionner(ccX,ccY);
					//ForetVoir("fusion");
					pgG->nVal[aArete]=1;//ajoute aArete à l'arbre couvrant
				}
			}
			if (bTas)
				nComplexiteh+=nTasCout();
			//te("nTasCout",nTasCout());
			if (bTas)
				TasAllouer(0);
			if (1 && bAfficher){//Afficher l'arbre couvrant et son poids total
				//nAreteTotalDansArbre:=nombre total d'arêtes de l'arbre couvrant
					for (nAreteTotalDansArbre=0,aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							nAreteTotalDansArbre+=1;
				printf("    Arbre couvrant résultant à %s spécifiées par des triplets (sommet,sommet:poids):",sPluriel(nAreteTotalDansArbre,"arête"));
					for (aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							printf(" (%d,%d:%d) ",pgG->nPhi[aK],pgG->sSuk[aK],pgG->nCout[aK]);
				printf("\n");
				//nPoidsTotal:=poids total des arêtes de l'arbre couvrant
					for (nPoidsTotal=0,aK=1;aK<=pgG->nArcEnTout;aK++)
						if (pgG->nVal[aK]>0)
							nPoidsTotal+=pgG->nCout[aK];
				printf("    Poids total de l'arbre couvrant obtenu%s: %d.\n",sChoix(bTas," (réputé minimal)",""),nPoidsTotal);
				nComplexiteh+=nForetComplexiteh(&nHauteur);
				nHauteurMax=mPoidsFort(pgG->nSommetEnTout);
				printf("    Hauteur maximale théorique de la forêt équilibrée: %s. Hauteur maximale obtenue: %s.\n",sPar3(nHauteurMax),sPar3(nHauteur));
				nVersus=2*nAreteEnTout*nHauteurMax;//2 appels à nForetComposante par arête
				printf("    Cumul itérations de nForetComposante() vs maximum théorique 2Alog2(S): %s vs %s.\n",sPar3(nComplexiteh),sPar3(nVersus));
			}
		ForetINITIALISER(0,bLogn);
		//te("Complexité",nComplexiteh);
	//Appel1("nGrapheCouvrirAvecKruskaL");
	return(nComplexiteh);
}//nGrapheCouvrirAvecKruskaL

void GrapheCouvrirAfficheR(char *sAlgorithme,graf *pgG){
	int nArete,nPoids,nPoidsTotal;
	int aK,sX,sY;
	nArete=pgG->nSommetEnTout-1;//car nGrapheComposanteConnexe(pgG)==1.
	printf("——— Résultat avec %s: un arbre couvrant de poids minimal à %s:\n     ",sAlgorithme,sPluriel(nArete,"arête"));
	//afficher les arêtes avec leurs poids respectifs ainsi que nPoidsTotal:
		for (nArete=0,nPoidsTotal=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (pgG->sPer[sY]==sX){//tout arc (X,Y) qui vérifie pgG->sPer[sY]==sX appartient à l'arbre couvrant
					nArete++;
					nPoids=pgG->nCout[aK];
					printf("(%d,%d:%d)%s",sX,sY,nPoids,(nArete+1<pgG->nSommetEnTout)?",":"");
					nPoidsTotal+=nPoids;
				}
			}
		printf(" ——poids total:%d.\n",nPoidsTotal);
}//GrapheCouvrirAfficheR

int nGrapheCouvrirAvecP(graf *pgG){//O(S2)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant l'algo P vu en TD. Rend une mesure de sa complexité.
	const int kuInfini=kE4-1;
	const int kbVoir=kF;
	int nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecP");
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecP2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) te("nCoutMax",nCoutMax);
			Assert1("nGrapheCouvrirAvecP3",nCoutMax<kuInfini);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		AbeAllouer(pgG->nSommetEnTout,kuInfini);//O(1)
			//Abe:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					AbeModifier(sX,nDist[sX]);//O(lgS)
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(S2)
				AbePropager();//O(S)
				if (kbVoir) AbeVoir("avant extraction");
				sX=eAbeExtraire();//O(1)
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//donc positive strictt.
				if (kF || kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						AbeModifier(sY,nDist[sY]);//O(1)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				//if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh=nAbeCout();//ajoute le coût total des opérations effectuées sur l'abe entre les deux AbeAllouer().
		AbeAllouer(0,kuInfini);//O(1)
	if (kbVoir) Appel1("nGrapheCouvrirAvecP");
	return(nComplexiteh);
}//nGrapheCouvrirAvecP

int nGrapheCouvrirAvecPriM(graf *pgG){//O(SlgS+AlgS)
	//calcule un arbre couvrant (résultat ds pgG->sPer[]) de poids minimal (donnée ds pgG->nCout[]) en utilisant Prim avec tas. Rend une mesure de sa complexité.
	const int kuInfini=kE3-1;
	const int kbVoir=kF;
	int nComplexiteh=0,nCoutMax,aK,sX,sY,uSommet;
	int nDist[1+pgG->nSommetEnTout];//nDist[sY] est la plus petite distance entre le sommet sY et l'arbre en cours de construction.
	if (kbVoir) Appel0("nGrapheCouvrirAvecPriM");
		//vérifier que kuInfini est bien une valeur supérieure à toute valeur du vecteur positif ou nul pgG->nCout[1..pgG->nSommetEnTout].
			for (nCoutMax=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nCoutMax=iSup(nCoutMax,pgG->nCout[aK]);
					Assert1("nGrapheCouvrirAvecPriM2",pgG->nCout[aK]>=0);
				}
			if (kbVoir) te("nCoutMax",nCoutMax);
			Assert1("nGrapheCouvrirAvecPriM3",nCoutMax<kuInfini);
		sX=1;//existe vu pgG->nSommetEnTout>1.
		//nDist[sY]:=kuInfini pour tout sommet sY autre que sX,et nDist[sX]=0.
			VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);//O(S)
			nComplexiteh+=pgG->nSommetEnTout;
			nDist[sX]=0;
			if (kbVoir) VecteurVoir1("nDist",nDist,1,pgG->nSommetEnTout);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);//O(S);superflu,mais facilite le débogage.
		nComplexiteh+=pgG->nSommetEnTout;
		pgG->sPer[sX]=-sX;//changera de signe après extraction du sommet considéré par eTasExtraire() (superflu,mais facilite le débogage).
		TasAllouer(pgG->nSommetEnTout);//O(1)
			//Tas:=tous les couples (sX,nDist[sX])
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					TasInsererValuer(sX,nDist[sX]);//O(lgS)
			for (uSommet=1;uSommet<=pgG->nSommetEnTout;uSommet++){//O(SlgS+AlgS)
				if (kbVoir) TasVoir("avant extraction");
				sX=eTasExtraire();//O(lgS)
				//te("sommet extrait",sX);
				pgG->sPer[sX]=abs(pgG->sPer[sX]);//change donc de signe et devient strictement positif.
				if (kbVoir) printf("Extraction du sommet n°%d.\n",sX);
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					sY=pgG->sSuk[aK];
					nComplexiteh+=1;
					if (nDist[sY]>pgG->nCout[aK] && pgG->sPer[sY]<=0){
						nDist[sY]=pgG->nCout[aK];
						//tee("actualise",sY,nDist[sY]);
						TasActualiser(sY,nDist[sY]);//O(lgS)
						pgG->sPer[sY]=-sX;//pgG->sPer[sX] changera de signe après extraction du sommet considéré par eTasExtraire().
					}
				}//for aK
				if (kbVoir) VecteurVoir1("pgG->sPer",pgG->sPer,1,pgG->nSommetEnTout);
			}//for uSommet
			nComplexiteh+=nTasCout();//ajoute le coût total des opérations effectuées sur le tas entre les deux TasAllouer().
		TasAllouer(0);
		if (kbVoir) te("Complexité",nComplexiteh);
	if (kbVoir) Appel1("nGrapheCouvrirAvecPriM");
	return(nComplexiteh);
}//nGrapheCouvrirAvecPriM

void GrapheCouvrirAvecPrimOuP(graf *pgG,int bPrim,int bAfficher,int bPerformanceComparer){
	//le code de cette routine est à compléter ——en ajoutant notamment du code pris dans GrapheCouvrirAvecKruskaL.
	const int kuModeMaxi=2;
	int nComplexiteh[kuModeMaxi],nComplexitehMax[kuModeMaxi],nMode,nLgMax,nLg[kuModeMaxi];
	Assert3("GrapheCouvrirAvecPrimOuP",bGrapheSymetrique(pgG),nGrapheComposanteConnexe(pgG)==1,pgG->nSommetEnTout>1);
	//nComplexiteh[0]=nComplexiteh[1]=0;
	if (bPrim || bPerformanceComparer){
		nComplexiteh[0]=nGrapheCouvrirAvecPriM(pgG);//O(SlgS+AlgS)
		if (bAfficher)
			GrapheCouvrirAfficheR("Prim",pgG);
	}
	if (!bPrim || bPerformanceComparer){
		nComplexiteh[1]=nGrapheCouvrirAvecP(pgG);//O(S2)
		if (bAfficher)
			GrapheCouvrirAfficheR("P",pgG);
	}
	if (bPerformanceComparer){
		//tee("nComplexiteh[0],nComplexiteh[1]",nComplexiteh[0],nComplexiteh[1]);
		Titrer("Comparaison des performances Prim vs P pour le calcul d'acpm");
		printf("%sOption    Prim (minimier)    P(abe)    Durée du calcul\n",sTab(1));
		for (nLgMax=0,nMode=0;nMode<kuModeMaxi;nMode++)
			nLgMax=iSup(nLgMax,nLg[nMode]=nChaineLg(sPar3(nComplexiteh[nMode])));
		//VecteurVoir("nLg",nLg,0,1);te("nLgMax",nLgMax);
		for (nMode=0;nMode<kuModeMaxi;nMode++)
			printf("%s  %d           %s             %s      %s%s\n",sTab(1),nMode,sOui(nMode%2==0),sOui(nMode%2),sE((15-nLgMax)/2+nLgMax-nLg[nMode]),sPar3(nComplexiteh[nMode]));
		nComplexitehMax[0]=pgG->nArcEnTout*nLog2(pgG->nSommetEnTout);
		nComplexitehMax[1]=pgG->nSommetEnTout*pgG->nSommetEnTout;
		printf("Gains sur le pire cas: SlgS/Prim=%s et S2/P=%s. Facteur de vitesse gagné sur Prim par le challenger P: %s.\n",
			sDiv(nComplexitehMax[0],nComplexiteh[0]),sDiv(nComplexitehMax[1],nComplexiteh[1]),sDiv(nComplexiteh[0],nComplexiteh[1]));
	}
}//GrapheCouvrirAvecPrimOuP

void GrapheCreer(int iSommet,graf **ppgG){
	//si iSommet!=0, alloue un espace pour pgG puis,seult si iSommet>0,ajoute des arcs via GrapheDecrire(); si iSommet est nul,libère l'espace.
	int sX;
	//FlipFlop("GrapheCreer",iSommet!=0,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer(0,…) avant une nouvelle allocation. 
	if (iSommet!=0){
		Assert1("GrapheCreer 1",abs(iSommet)<kuGrapheSommetLim);
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=abs(iSommet);
		(*ppgG)->nArcEnTout=0;
		if (iSommet>0){
			GrapheDecrire(*ppgG);//génère un graphe simple avec (*ppgG)->nSommetEnTout sommets et quelques arcs choisis.
		}else for (sX=1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=1;//génère donc un graphe simple avec (*ppgG)->nSommetEnTout sommets et aucun arc.
		Assert1("GrapheCreer 2",bGrapheSimple(*ppgG));
	}
	else free(*ppgG);
}//GrapheCreer

void GrapheCreer0(graf **ppgG,int bCreer){
	//crée un graphe vide, ie sans sommets ni arcs.
	//FlipFlop("GrapheCreer0",bCreer,&bGrapheCreeR);//ie tout graphe alloué doit être désalloué via GrapheCreer0(0,…) avant une nouvelle allocation. 
	if (bCreer){
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=0;
		(*ppgG)->nArcEnTout=0;
		(*ppgG)->aHed[1]=1;
	}else free(*ppgG);
}//GrapheCreer0

void GrapheCreer1(graf **ppgG,int nGraphe,int bCreer){
	//si bCreer,crée le graphe de numéro nGraphe; sinon,restitue le graphe alloué
	//NB Les graphes générés ne sont pas, en général, symétriques; Pour les symétriser,appeler GrapheSymetriser(pgG) après la création. 
	graf *pgG;
	enum grType GrapheType;
// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grXX,grOmega}
	int sX,sY;
	char ks2Aile[]="AC2BD3CE1DF1EG2FH2GF3HE3GA1HB1";//2 papillons à 4 sommets
	char ks2Diam[]="AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char ksFigure8aPage272[]="AB0AC0BC1BE0CD0DE1DG0EF0FG1FH0";//Gondran et Minoux Eyrolles 37 pour tester les couplages qcq
	//char ksX[]="AE2BE3EF4FC5FD6";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksX[]="AC2BD2CB2DA2";//NB les coins du quadripôle sont les sommets A,B,C et D.
	
	//char ksXX[]="AE2BF2CH3DG5EB8EG9FA7FH9GC6HD4";//NB les coins du quadripôle sont les sommets A,B,C et D.
	char ksXX[]="AC2BD2CB2CE3DA2DF3EG2FH2GF2HE2";//NB les coins du quadripôle NE SONT PAS les sommets A,B,C et D.
	char ksXY[]="AE5BF3EF2FG1GC2GH3HD5";//NB les coins du quadripôle sont les sommets A,B,C et D.
	GrapheCreer0(ppgG,bCreer);//oui,mm pr grXX,tant pis
	if (bCreer){
		pgG=*ppgG;
		switch (nGraphe) {
			case gr2Aile:
				GrapheGenerer(ks2Aile,ppgG);
			break;
			case gr2Diam:
				GrapheGenerer(ks2Diam,ppgG);
			break;
			case grC2:case grC3:case grC4:case grC5:case grC6:	//C comme Cycle: Cn est un cycle à n sommets
				GrapheSommer(pgG,nGraphe-grC2+2);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer(pgG,sX,(sX>=pgG->nSommetEnTout)? 1: sX+1);
			break;
			case grC4b:	//C4 + 1 arc (2,4)
				GrapheSommer(pgG,4);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer(pgG,sX,(sX>=pgG->nSommetEnTout)? 1: sX+1);
				GrapheArquer(pgG,2,4);
			break;
			case grD2:case grD3:case grD4:	//peigne à Dn dents
				GrapheSommer(pgG,2*(nGraphe-grD2+2));
				for (sX=1;sX<=pgG->nSommetEnTout/2-1;sX++)
					GrapheArquer(pgG,2*sX-1,2*sX+1);//base du peigne=sommets impairs
				for (sX=1;sX<=pgG->nSommetEnTout/2;sX++)
					GrapheArquer(pgG,2*sX-1,2*sX+0);//dents du peigne, de sommets impair à sommet suivant
			break;
			case grK2:case grK3:case grK4:case grK5:case grK6:	//K comme Kuratowski: Kn est une clique (un sous-graphe complet) à n sommets
				GrapheSommer(pgG,nGraphe-grK4+4);
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (sY=sX+1;sY<=pgG->nSommetEnTout;sY++)
						GrapheArquer(pgG,sX,sY);
			break;
			case grL4:	//C3 + 1 arc (3,4)
				GrapheSommer(pgG,4); GrapheArquer(pgG,1,2); GrapheArquer(pgG,2,3); GrapheArquer(pgG,3,1); GrapheArquer(pgG,3,4);
			break;
			case grP2:case grP3:case grP4:case grP5:case grP6:case grP7:case grP8://P comme Path: Pn est un chemin à n sommets
				GrapheSommer(pgG,nGraphe-grP2+2);
				for (sX=1;sX<pgG->nSommetEnTout;sX++)
					GrapheArquer(pgG,sX,sX+1);
				//GrapheVoir(pgG,"pgG après création");
			break;
			case grS2:case grS3:case grS4:case grS5:case grS6://S comme Star: Sn est une étoile à n extrémités (1 sommet central)
				GrapheSommer(pgG,nGraphe-grS2+3);
				for (sX=2;sX<=pgG->nSommetEnTout;sX++)
					GrapheArquer(pgG,1,sX);
			break;
			case grX: //X allongé,ie deux Y tête-bêche.
				GrapheGenerer(ksX,ppgG);
			break;
			case grXX: //20 écrit en chiffres romains ——deux X côte à côte confinés entre deux barres horizontales et verticales.
				GrapheGenerer(ksXX,ppgG);
			break;
			case grXY: //X allongé et prolongé.
				GrapheGenerer(ksXY,ppgG);
			break;
			case grOmega://Gondran et Minoux Eyrolles 37 pour tester les couplages qcq (contient notamment des triangles imbriqués)
				GrapheGenerer(ksFigure8aPage272,ppgG);
			break;
			default:Assert1("GrapheCreer1: numéro de graphe inconnu (cf GrapheType)",0);
		}//switch (nGraphe)
	};
}//GrapheCreer1

void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]){
	//crée un graphe simple à nSommet sommets et nArc arcs listés dans nArcOrigine[] et nArcDestination[];déroute en cas de problème.
	int sDestination;
	int aK;
	int sOrigine;
	Assert4("GrapheCreer20",nSommet>=0, nArc>=0, nArcOrigine!=NULL, nArcDestination!=NULL);
	GrapheCreer(-nSommet,ppgG);//crée un graphe à nSommet sommets et aucun arc
	//Ajouter tous les arcs aK spécifiés par nArcOrigine[aK] et nArcDestination[aK] et dérouter si un ajout est impossible:
		for (aK=1;aK<=nArc;aK++){
			sOrigine=nArcOrigine[aK];
			sDestination=nArcDestination[aK];
			//tee("création de l'arc",sOrigine,sDestination);
			GrapheArquer(*ppgG,sOrigine,sDestination);//actualise notamment pgG->nArcEnTout;déroute si l'arc ne peut être créé.
		}
	Assert1("GrapheCreer22",bGrapheSimple(*ppgG));
}//GrapheCreer2

void GrapheDecrire(graf *pgG){
	//rend un graphe simple "intéressant" à pgG->nSommetEnTout sommets, ie un graphe connexe obtenu en empilant quelques arcs choisis.
	int uArc,uArcMax,aK,sX,sY;
	int bSucc[1+pgG->nSommetEnTout];
	//Appel0("GrapheDecrire");
		Assert2("GrapheDecrire",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,kuGrapheSommetLim-1));
		//préparer d'abord un graphe à 1 sommet et aucun arc et faciliter le débogage en razant autant que possible aHed[] et sSuk[]
			pgG->aHed[0]=0;//zèle
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=0;
			pgG->aHed[1]=1;
			for (aK=1;sX<=pgG->nSommetEnTout;aK++)
				pgG->sSuk[aK]=0;
		//lier chaque sommet sX à plusieurs autres sommets, jusqu'à,si possible,sX autres sommets:
			for (pgG->nArcEnTout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)
					bSucc[sY]=kF;//ie sY n'est pas un successeur de sX 
				pgG->aHed[sX+1]=pgG->aHed[sX];
				sY=sX;
				uArcMax=3*sX;
				for (uArc=1;uArc<=uArcMax;uArc++){
					sY=uModulo1(sY+uArcMax,pgG->nSommetEnTout);//tente un sommet successeur sY
					if ( (sY!=sX) && !bSucc[sY] ){//le sommet successeur sY a du sens pour sX et c'est effectivement un nouveau successeur
						pgG->nArcEnTout++;
						pgG->sSuk[aK=pgG->nArcEnTout]=sY;
						pgG->nCapaMax[aK]=1;
						pgG->nCout[aK]=1;
						pgG->aHed[sX+1]++;
						bSucc[sY]=kV;
					}
				}
			}
		//GrapheInverser(pgG);//affecte en O(A) les tableaux aDeh[] et sKus[] qui décrivent le graphe inverse du graphe défini par aHed[] et aSuK[]
		Assert1("GrapheDecrire",bGrapheSimple(pgG));
	//Appel1("GrapheDecrire");
}//GrapheDecrire

void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination){//O(A)
	//rend les sommets qui délimitent l'arc de rang1 uArcIndex dans pgG;déroute si uArcIndex n'est pas l'index d'un arc de pgG.
	int aK,sX;
	Assert3("GrapheDelimiteR1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	Assert1("GrapheDelimiteR2",bCroit(1,uArcIndex,pgG->nArcEnTout));
		for (*psOrigine=0,*psDestination=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (aK==uArcIndex){
					*psOrigine=sX;
					*psDestination=pgG->sSuk[aK];
				}
		}
	Assert2("GrapheDelimiteR3",*psOrigine>0,*psDestination>0);
}//GrapheDelimiter

void GrapheDerouler(graf *pgG){
	//transforme pgG=(S,A) de façon à obtenir un dag à S*S sommets:à chaque arc (sX,sY) de pgG,on associe S-1 arcs (sXi,sYj) avec 1≤i<S et j=i+1. 
	#define kbDerouler kF
	int uEtage,aK,aKlim,sX;
	if (kbDerouler) Appel0("GrapheDerouler");
		Assert3("GrapheDerouler1",bGrapheAmorceR,pgG->nSommetEnTout>0,bGrapheSimple(pgG));
		Assert2("GrapheDerouler2",pgG->nSommetEnTout*pgG->nSommetEnTout<kuGrapheSommetLim,pgG->nArcEnTout*(pgG->nSommetEnTout-1)<kuGrapheArcLim);
		//affecter pgG->sSuk[]: chague arc relie un sommet source de l'étage uEtage à un sommet cible de l'étage uEtage+1 (uEtage=1 ssi 1er étage):
			for (uEtage=pgG->nSommetEnTout-1;uEtage>=1;uEtage--)
				for (aK=pgG->nArcEnTout;aK>=1;aK--)
					pgG->sSuk[aK+(uEtage-1)*pgG->nArcEnTout]=pgG->sSuk[aK]+uEtage*pgG->nSommetEnTout;
		//affecter pgG->aHed[] hors dernier étage: chague sommet source n'a pour successeurs que des sommets situés à l'étage suivant:
			for (uEtage=2;uEtage<=pgG->nSommetEnTout-1;uEtage++)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX+(uEtage-1)*pgG->nSommetEnTout]=pgG->aHed[sX+(uEtage-2)*pgG->nSommetEnTout]+pgG->nArcEnTout;
		//affecter pgG->aHed[] pour le dernier étage: les sommets du dernier étage n'ont aucun successeur
			aKlim=pgG->nArcEnTout*(pgG->nSommetEnTout-1)+1;
			if (kbDerouler) te("pgG->nSommetEnTout*pgG->nSommetEnTout",pgG->nSommetEnTout*pgG->nSommetEnTout);
			if (kbDerouler) te("aKlim",aKlim);
			if (kbDerouler) VecteurVoir("pgG->aHed AVANT",pgG->aHed,1,pgG->nSommetEnTout*pgG->nSommetEnTout+1);
			if (kbDerouler) VecteurVoir("pgG->sSuk AVANT",pgG->sSuk,1,aKlim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX--)
				pgG->aHed[(pgG->nSommetEnTout-1)*pgG->nSommetEnTout+sX]=aKlim;
			pgG->aHed[pgG->nSommetEnTout*pgG->nSommetEnTout+1]=aKlim;
		//affecter pgG->nArcEnTout et pgG->nSommetEnTout
			pgG->nArcEnTout=aKlim-1;
			pgG->nSommetEnTout=pgG->nSommetEnTout*pgG->nSommetEnTout;
		if (kbDerouler) VecteurVoir("pgG->aHed APRES",pgG->aHed,1,pgG->nSommetEnTout+1);
		if (kbDerouler) VecteurVoir("pgG->sSuk APRES",pgG->sSuk,1,aKlim);
		Assert2("GrapheDerouler3",bGrapheSimple(pgG),!bGrapheCircuite(pgG));
	if (kbDerouler) Appel1("GrapheDerouler");
}//GrapheDerouler

float fGrapheDensiteh(graf *pgSimple){
	//rend la densité du graphe simple pgSimple orienté ou non,ou -1 si non défni. S'il est non orienté,chaque arête est représentée par deux arcs opposés.
	//Dit autrement, le calcul de la densité du graphe ne dépend pas du mode orienté ou non orienté puisque pgSimple est de toute façon un graphe orienté.
	int nArcAuPlus;//nombre d'arcs d'un graphe simple complet
	Assert1("fGrapheDensiteh",bGrapheSimple(pgSimple));
	float fDensiteh=-1.0;//ie densité non définie
	nArcAuPlus=pgSimple->nSommetEnTout*(pgSimple->nSommetEnTout-1);//chaque sommet a pgSimple->nSommetEnTout-1 voisins et il y a Au plus deux arcs opposés entre 2 sommets quelconques.
	if (pgSimple->nSommetEnTout>1){
		fDensiteh=pgSimple->nArcEnTout*1.0/nArcAuPlus;
	}else if (pgSimple->nSommetEnTout==1)//tout arc ou arete formerait une boucle sur le sommet unique de pgSimple: absurde. dc pgSimple->nArcEnTout=0.
		fDensiteh=-1.0;//le nombre d'arcs, égal à 0, est à la fois maximal et minimal. Donc la densité n'est pas définie.
	else fDensiteh=-1.0;//aucun sommet et aucun arc;le nombre d'arcs, égal à 0, est encore à la fois maximal et minimal. Donc densité non définie.
	//tr("fDensiteh",fDensiteh);
	return(fDensiteh);
}//fGrapheDensiteh

int bGrapheDesareter(graf *pgG,int sExtremiteh0,int sExtremiteh1){//O(A)
	//retire de pgG l'arête (sExtremiteh0,sExtremiteh1) s'il existe;rend vrai ssi l'arête a pu être retirée ——donc elle existait à l'appel de la routine. 
	Assert2("bGrapheDesareter0",bGrapheAmorceR,bGraphe(pgG));
	int bDesareter=bGrapheSommet(pgG,sExtremiteh0) && bGrapheSommet(pgG,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh0,sExtremiteh1);
	bDesareter=bDesareter && bGrapheDesarquer(pgG,sExtremiteh1,sExtremiteh0);
	Assert2("bGrapheDesareter1",bGraphe(pgG),bBool(bDesareter));
	return(bDesareter);
}//bGrapheDesareter

void GrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//d2(sOrigine,sDestination);
	int bDesarquer=bGrapheDesarquer(pgG,sOrigine,sDestination);
	Assert1("GrapheDesarquer UN",bDesarquer);
}//GrapheDesarquer

int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//retire de pgG l'arc (sOrigine,sDestination) s'il existe;rend vrai ssi l'arc a pu être retiré ——donc il existait à l'appel de la routine. 
	int aK,aL,sX;
	Assert2("bGrapheDesarquer0",bGrapheAmorceR,bGraphe(pgG));
	int bDesarquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination);
	if (bDesarquer){
		//aL soit l'index de l'arc (sOrigine,sDestination) dans sSuk[], ou 0 si non défini.
			for (aL=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
				if (pgG->sSuk[aK]==sDestination)
					aL=aK;//unique vu Assert3(bGrapheDesarquer0,…,bGrapheSimple(pgG));
		bDesarquer=(aL>0);
	}
	if (bDesarquer){//l'arc (sOrigine,sDestination) existe bien dans pgG et son index dans sSuk[] est aL.
		//retirer l'arc de rang1 aL crée un trou en sSuk[aL]; le combler en tassant à gauche les éléments de sSuk situés au-delà de sSuk[aL]: 
			for (aK=aL;aK<pgG->nArcEnTout;aK++){
				pgG->sSuk[aK]=pgG->sSuk[aK+1];
				pgG->nCapaMin[aK]=pgG->nCapaMin[aK+1];
				pgG->nCapaMax[aK]=pgG->nCapaMax[aK+1];
				pgG->coulh[aK]=pgG->coulh[aK+1];
				pgG->nCout[aK]=pgG->nCout[aK+1];
				pgG->nPoids[aK]=pgG->nPoids[aK+1];
			}
			pgG->sSuk[pgG->nArcEnTout]=0;
		//décrémenter tous les éléments de aHed[] situés après pgG->aHed[sOrigine] pour pouvoir accéder aux éléments de sSuk[] qui ont été décalés:
			for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX+1]--;
		pgG->nArcEnTout--;
	}
	Assert2("bGrapheDesarquer1",bGraphe(pgG),bBool(bDesarquer));
	return(bDesarquer);
}//bGrapheDesarquer

void GrapheDesarquerTout(graf *pgG,int sAccroche){
	//retire de pgG tous les arcs éventuels incidents à sAccroche (ne fait rien si aucun arc de pgG n'a sAccroche pour origine ou destination).
	int bIncidence,nIncidence0,nIncidence1;
	int aK,sX,sY;
	Assert3("GrapheDesarquerTout1",bGrapheAmorceR,bGraphe(pgG),bGrapheSommet(pgG,sAccroche));
	//retirer ts les arcs éventuels qui ont pour origine sAccroche
		nIncidence0=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,aK=pgG->aHed[sAccroche];aK<pgG->aHed[sAccroche+1]; aK++){
				sY=pgG->sSuk[aK];
				bIncidence=bGrapheDesarquer(pgG,sAccroche,sY) || bIncidence;
			}
			nIncidence0++;
		} while (bWhile("GrapheDesarquerTout11",bIncidence));
	Assert3("GrapheDesarquerTout2",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//retirer ts les arcs éventuels qui ont pour destination sAccroche
		nIncidence1=0;
		While(pgG->nSommetEnTout);
		do {
			for (bIncidence=kF,sX=1; sX<=pgG->nSommetEnTout; sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1]; aK++){
					sY=pgG->sSuk[aK];
					if (sY==sAccroche){
						bIncidence=bGrapheDesarquer(pgG,sX,sAccroche) || bIncidence;
					}
				}//for aK
			nIncidence1++;
		} while (bWhile("GrapheDesarquerTout22",bIncidence));
	Assert2("GrapheDesarquerTout3",bGrapheAmorceR,bGraphe(pgG));
}//GrapheDesarquerTout

void GrapheDupliquer(graf *pgOriginal,graf **ppgCopie){
	int aK;
	int sX;
	Assert4("GrapheDupliquer0",bGrapheAmorceR,bGraphe(pgOriginal),bGrapheSimple(pgOriginal),ppgCopie!=NULL);
	(*ppgCopie)->nSommetEnTout=pgOriginal->nSommetEnTout;
	(*ppgCopie)->nArcEnTout=pgOriginal->nArcEnTout;
	for (sX=1;sX<=pgOriginal->nSommetEnTout+1;sX++){
		(*ppgCopie)->aHed[sX]=pgOriginal->aHed[sX];//dont aHed[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->aDeh[sX]=pgOriginal->aDeh[sX];//dont aDeh[pgOriginal->nSommetEnTout+1]
		(*ppgCopie)->sPer[sX]=pgOriginal->sPer[sX];
	}
	for (aK=1;aK<=pgOriginal->nArcEnTout;aK++){
		(*ppgCopie)->sSuk[aK]=pgOriginal->sSuk[aK];
		(*ppgCopie)->sKus[aK]=pgOriginal->sKus[aK];
		(*ppgCopie)->aInv[aK]=pgOriginal->aInv[aK];
		(*ppgCopie)->nCapaMax[aK]=pgOriginal->nCapaMax[aK];
		(*ppgCopie)->nCapaMin[aK]=pgOriginal->nCapaMin[aK];
		(*ppgCopie)->nCout[aK]=pgOriginal->nCout[aK];
		(*ppgCopie)->nPoids[aK]=pgOriginal->nPoids[aK];
		(*ppgCopie)->aArcTo[aK]=pgOriginal->aArcTo[aK];
		(*ppgCopie)->nVal[aK]=pgOriginal->nVal[aK];
		(*ppgCopie)->coulh[aK]=pgOriginal->coulh[aK];
	}
	Assert3("GrapheDupliquer1",bGrapheAmorceR,bGraphe(*ppgCopie),bGrapheSimple(*ppgCopie));
}//GrapheDupliquer

void GrapheEtoiler(graf *pgG,int uEtoile,int nBrancheParEtoile){
	//empile sur pgG uEtoile composantes connexes. Chacune est une étoile. Traite aussi le cas limite: une étoile avec 0 branche.
	int uB,uE;
	Assert2("GrapheEtoiler",uEtoile>0,nBrancheParEtoile>=0);
	int uSommetParEtoile=1+nBrancheParEtoile;
	int nSommet=pgG->nSommetEnTout;
	//te("pgG->nSommetEnTout+uEtoile*uSommetParEtoile",pgG->nSommetEnTout+uEtoile*uSommetParEtoile);
	Assert1("GrapheEtoiler aHed",pgG->nSommetEnTout+uEtoile*uSommetParEtoile<kuGrapheSommetLim);
	for (uE=1;uE<=uEtoile*uSommetParEtoile;uE++)
		pgG->aHed[nSommet+uE+1]=pgG->aHed[nSommet+uE];
	pgG->nSommetEnTout+=uEtoile*uSommetParEtoile;
	Assert1("GrapheEtoiler sSuk",pgG->nArcEnTout+uEtoile*uSommetParEtoile<kuGrapheArcLim);
	for (uE=1;uE<=uEtoile;uE++)
		for (uB=1;uB<=nBrancheParEtoile;uB++)
			GrapheArquer(pgG,nSommet+uSommetParEtoile*(uE-1)+1,nSommet+uSommetParEtoile*(uE-1)+1+uB);
}//GrapheEtoiler

int bGrapheEulerien(graf *pgG,int szSource,int szTrappe){
	//pgG admet un parcours eulérien (fermé/ouvert selon que szSource et szTrappe sont nuls/non nuls ——solidairement;sinon,appel non défini.
	int nDegreh[1+pgG->nSommetEnTout];
	int bEulerien;
	int aK,aL;
	int sX;
	Assert4("bGrapheEulerien1",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->aDeh[1]>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
	if (szSource!=0)
		Assert2("bGrapheEulerien2",bGrapheSommet(pgG,szSource),bGrapheSommet(pgG,szTrappe));
	//nDegreh[sX]:=degré du sommet sX pour tout sX
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			nDegreh[sX]=0;
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			//nDegreh[sX]+=degré sortant de sX,ie le nb de successeurs de sX
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					nDegreh[pgG->sSuk[aK]]++;
			//nDegreh[sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
				for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
					nDegreh[pgG->sKus[aL]]++;
		}
	for (bEulerien=kV,sX=1;sX<=pgG->nSommetEnTout;sX++)
		if ( (szSource==0) || (sX!=szSource && sX!=szTrappe) )
			bEulerien=bEulerien && bPair(nDegreh[sX]);
	return(bEulerien);
}//bGrapheEulerien

int bGrapheEulerier(graf *pgOrienteh,int szSource,int szTrappe){
	//rend dans pgOrienteh->nVal un parcours eulérien qui va de szSource à szTrappe ——donc fermé ssi szSource=szTrappe. rend faux ssi impossible;
	int bEulerier,nSommat,nGreffe=0,nMalloc=0,nPasse;
	int aNext[kuGrapheSommetLim];
	int aK,sX,sY;
	const int kbVoir=kF;
	typedef struct{
		int	 sVertex;
		void *pLien;
	}cellule,*pcellule;
	cellule *pcListe,*pcGreffe,*pcInsert,*pcSuivant,*pcPrecedent;
	graf *pgG=pgOrienteh;
	if (kbVoir) Appel0("bGrapheEulerier");
		Assert4("bGrapheEulerier1",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->aDeh[1]>0,(szSource==0)==(szTrappe==0));//"source existe" <=> "trappe existe"
		if (szSource!=0)
			Assert2("bGrapheEulerier2",bGrapheSommet(pgG,szSource),bGrapheSommet(pgOrienteh,szTrappe));
		bEulerier=bGrapheEulerien(pgG,szSource,szTrappe);
		if (bEulerier){
			//pcListe contienne une liste de cellules; chaque cellule mémorise le sommet courant rencontré lors de l'exploration du graphe.
				pcListe=malloc(sizeof(cellule));nMalloc++;pcListe->sVertex=szSource;pcListe->pLien=NULL;
			//pcInsert pointe dans pcListe la cellule courante après laquelle le prochain parcours sera inséré.
				pcInsert=pcListe;
			nSommat=1;//nombre courant d'occurrences de sommets qui jalonnent le parcours
			//aNext[sX] indexe un arc sortant non encore exploré d'origine sX; cet arc existe aussi longtemps que aNext[sX]<pgG->aHed[sX+1].
				VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
				nPasse=0;//nombre d'itérations dans la boucle principale ci-dessous
				While(pgG->nArcEnTout+pgG->nSommetEnTout);
				do{//si un sX dans pcInsert a des arcs non encore explorés,explorer ce sommet et greffer le parcours obtenu sur le parcours principal:
					sX=pcInsert->sVertex;
					//nPasse++;tee("nPasse,sX",nPasse,sX);
					if (aNext[sX]<pgG->aHed[sX+1]){//il reste des arcs sortants non encore explorés
						//partir du sommet sX et traverser un maximum d'arcs non encore explorés
							aK=aNext[sX];
							sY=sX;
							pcGreffe=NULL;
							nGreffe++;if (kbVoir) printf("greffe n°%d:",nGreffe);
							While(1+pgG->nArcEnTout);
							do {
								aNext[sY]=aNext[sY]+1;
								sY=pgG->sSuk[aK];
								if (kbVoir) printf(" %d",sY);
								pcSuivant=malloc(sizeof(cellule));nMalloc++;
								pcSuivant->sVertex=sY;
								if (pcGreffe==NULL)
									pcGreffe=pcSuivant;
								else pcPrecedent->pLien=pcSuivant;
								pcPrecedent=pcSuivant;
								nSommat++;
								aK=aNext[sY];
							}while( bWhile("bGrapheEulerier1",aK!=pgG->aHed[sY+1]) );
						if (kbVoir) printf(".\n");
						//greffer le parcours secondaire
							pcSuivant->pLien=pcInsert->pLien;//la cellule qui suit la dernière cellule du parcours secondaire pcSuivant est la cellule pcInsert->pLien.
							pcInsert->pLien=(pcellule) pcGreffe;//la première cellule de la liste secondaire
					}else pcInsert=pcInsert->pLien;
				}while ( bWhile("bGrapheEulerier2",pcInsert!=NULL) );
				Assert1("bGrapheEulerier3",nSommat==1+pgG->nArcEnTout);//les arcs de pgG ont bien été exploités TOUS et exactement une fois
			//pgG->nVal[]:=copie des 1+pgG->nArcEnTout sommets stockés dans la liste chaînée accessible depuis la cellule pcListe:
				pcInsert=pcListe;
				VecteurRazer(pgG->nVal,1,nSommat);
				for (aK=1;aK<=nSommat;aK++){
					pgG->nVal[aK]=pcInsert->sVertex;
					pcSuivant=pcInsert->pLien;
					free(pcInsert);nMalloc--;
					pcInsert=pcSuivant;
				}
				Assert1("bGrapheEulerier4",pcInsert==NULL);
			VecteurVoir("pgG->nVal",pgG->nVal,1,nSommat);
			//toute cellule allouée a été restituée
				if (nMalloc!=0)
					te("nMalloc",nMalloc);
				Assert1("bGrapheEulerier5",nMalloc==0);
		}
	if (kbVoir) Appel1("bGrapheEulerier");
	return(bEulerier);
}//bGrapheEulerier

void GrapheExplorer(graf *pgG,int bLargeurSinonProfondeur){//O(A)
	//explore pgG en largeur d'abord
	const int kbVoir=kF;
	int sX,sY;
	int bMarque[1+pgG->nSommetEnTout];
	int aNext[1+pgG->nSommetEnTout];
	if (kbVoir) Appel0(sC3b("GrapheExplorer en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
		Assert4("GrapheExplorer",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG),bBool(bLargeurSinonProfondeur));
		VecteurCopier(pgG->aHed,1,pgG->nSommetEnTout,aNext);
		VecteurRazer(bMarque,1,pgG->nSommetEnTout);
		bMarque[sX=1]=kV;if (kbVoir) d(sX);
		DequeAllouer(pgG->nSommetEnTout);
			if (bLargeurSinonProfondeur) DequeEnfiler(sX);else DequeEmpiler(sX);
			do{
				sX=sDequeSommet();
				if (aNext[sX]<pgG->aHed[sX+1]){
					sY=pgG->sSuk[aNext[sX]];
					if (!bMarque[sY]){
						bMarque[sY]=kV;if (kbVoir) d(sY);
						if (bLargeurSinonProfondeur) DequeEnfiler(sY);else DequeEmpiler(sY);
					}
					aNext[sX]++;//n'altère dc pas pgG->aHed
				}else sX=(bLargeurSinonProfondeur)? sDequeDefiler(): sDequeDepiler();
			}while (!bDequeVide());
		DequeAllouer(0);
	if (kbVoir) Appel1(sC3b("GrapheExplorer en mode",(bLargeurSinonProfondeur)?"largeur":"profondeur","d'abord"));
}//GrapheExplorer

void GrapheGenerer(char kcArc[],graf **ppgG){
	//Alloue et rend ppgG défini par les triplets d'arcs colorés (origine,destination,couleur),eg kcArc="AC1AD1AE1AF1BC2BD2BE2BF2".
	int uArc;
	int nArc0[kuGrapheArcLim];//NB sommet origine de l'arc
	int nArc1[kuGrapheArcLim];//NB sommet destination de l'arc
	int uArcEnTout;
	int nC;
	int uChaineLg;
	int nCouleur;
	int bCouleurNulle;
	int sDernier;
	int sDestination;
	int nDistinct[1+kuByteMax];
	int sOrigine;
	int sPremier;
	int uS;
	char cSommet;
	int nSommet;
	uChaineLg=nChaineLg(kcArc);
	Assert2("GrapheGenerer1", uChaineLg %3==0,uChaineLg<kuByteMax);//chaque triplet occupe 3 caractères, donc uChaineLg est un multiple de 3.
	//nSommet:=nb de sommets distincts cités ds kcArc censé être une suite de triplets (origine,destination,couleur) qui occupent 3 caractères.
		//nDistinct[sX]:=nombre de références au sommet sX,lequel est censé être une majuscule ou une minuscule
			for (uS=1;uS<=kuByteMax;uS++)
				nDistinct[uS]=0;
			for (nC=0;nC<uChaineLg;nC++)
				if (nC%3!=2){//nC est censé indexer un sommet, pas une couleur
					cSommet=kcArc[nC];
					Assert1("GrapheGenerer2",bCroit('a',cSommet,'z') || bCroit('A',cSommet,'Z') );
					nSommet=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
					Assert1("GrapheGenerer3",bCroit(1,nSommet,26+26) );
					nDistinct[nSommet]++;
				}
		//nDernier:=numéro du sommet de rang maximal; les sommets de kcArc[] sont réputés commencer à la lettre 'A' et être consécutifs
			for (sPremier=kuIntegerMax,sDernier=0,uS=1;uS<=kuByteMax;uS++)
				if (nDistinct[uS]>0){
					sPremier=iMin(sPremier,uS);
					sDernier=iMax(sDernier,uS);
				}
			Assert1("GrapheGenerer4", sPremier==1);
			for (uS=sPremier;uS<=sDernier;uS++)
				Assert1("GrapheGenerer5", nDistinct[uS]>0);//ts les noms de sommets cités couvrent un facteur gauche de [A-Za-z]
		nSommet=sDernier;
		//te("nSommet",nSommet);
	uArcEnTout=(uChaineLg)/3;
	Assert1("GrapheGenerer6", uArcEnTout>0);
	//nArc0[]:=sommets origine listés ds cArc[]
		for (nArc0[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			nArc0[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//nArc1[]:=sommets destination listés ds cArc[]
		for (nArc1[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-2];
			nArc1[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//ppgG soit le graphe à nSommet sommets et uArcEnTout arcs d'origine nArc0[] et de destination nArc1[]
		//tee("nSommet,uArcEnTout",nSommet,uArcEnTout);
		GrapheCreer2(ppgG,nSommet,uArcEnTout,nArc0,nArc1);
	//colorier chaque arc de ppgG avec la couleur spécifiée dans kcArc[] et calculer,pour info, bCouleurNulle:=toutes les couleurs sont nulles:
		for (bCouleurNulle=kF,nArc1[0]=0,uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			sOrigine=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			cSommet=kcArc[3*uArc-2];
			sDestination=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			nCouleur=kcArc[3*uArc-1]-'0';
			Assert1("GrapheGenerer7", bCroit(0,nCouleur,knGrapheCouleurMax));
			bCouleurNulle=bCouleurNulle || (nCouleur==0);
			//t(sC7("arc (",sEnt(sOrigine),",",sEnt(sDestination),",",sEnt(nCouleur),")"));
			GrapheColorer(*ppgG,sOrigine,sDestination,nCouleur);
		}
		//Assert1("bGrapheGenerer6",!bCouleurNulle);
}//bGrapheGenerer

void GrapheINITIALISER(){//O(?)
	//relance le présent module
	Assert1("GrapheINITIALISER",bGrapheAmorceR);
}//GrapheINITIALISER

void GrapheInverser(graf *pgG){//O(A)
	//affecte aDeh[],sKus[] qui décrivent le graphe inverse de pgG,et aInv[] qui donne l'index aK=pgG->aInv[aL] de l'arc inverse de l'arc d'index aL.
	const int kbDisert = kF;
	int aK,aL;
	int nPred[1+pgG->nSommetEnTout];
	int sX,sY,sZ;
	Assert1("GrapheInverser",bGrapheAmorceR);
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++){//O(A)
			sY=pgG->sSuk[aK];
			nPred[sY]++;
		}
		//VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
	//aDeh[sX]:=1+nombre total d'arcs qui auront pour extrémité les sommets 1 à sX (inclus)
		pgG->aDeh[0]=1;//technique
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			pgG->aDeh[sX]=pgG->aDeh[sX-1]+nPred[sX];
		pgG->aDeh[pgG->nSommetEnTout+1]=pgG->nArcEnTout+1;
		//VecteurVoir("aDeH0",pgG->aDeh,1,pgG->nSommetEnTout+1);
	//sKus[] et aInv[] soient affectés
		Assert1("GrapheInverser0",pgG->nArcEnTout>0);
		VecteurRazer(pgG->aInv,1,pgG->nArcEnTout);//O(A)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				Assert1("GrapheInverser1",sY>0);
				pgG->aDeh[sY]--;
				aL=pgG->aDeh[sY];
				Assert1("GrapheInverser2",aL>0);
				pgG->sKus[aL]=sX;
				pgG->aInv[aL]=aK;//dc aK est l'index de l'arc (sX,sY) dans sSuk[] et aL est l'index de (sY,sX) dans sKus[].
			}
	if (kbDisert) GrapheViseR(pgG,"Graphe Inversé");
	if (kbDisert) Titrer("vérifications");
	//vérifier pgG->aDeh et pgG->sKus
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				aL=pgG->aDeh[sY];
				sZ=pgG->sKus[aL]=sX;
				Assert1("GrapheInverser3",sX==sZ);
			}
	//vérifier pgG->aInv qui permet de passer du graphe inverse au graphe direct
		for (sY=1;sY<=pgG->nSommetEnTout;sY++)//O(A)
			for (aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
				sX=pgG->sKus[aL];
				aK=pgG->aInv[aL];
				sZ=pgG->sSuk[aK];
				Assert1("GrapheInverser4",sY==sZ);
			}
	if (kbDisert)//constater que pgG->aInv NE PERMET PAS (sauf exception) DE PASSER DU GRAPHE DIRECT AU GRAPHE INVERSE
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				aL=pgG->aInv[aK];
				sZ=pgG->sKus[aL];
				teee("sX,sY,sZ",sX,sY,sZ);
				tee("aK,aL",aK,aL);
				Assert1("GrapheInverser9",sX==sZ);//plante le plus souvent quelque part
			}
}//GrapheInverser

void GraphePolariser(graf *pgG,int *psSource,int *psTrappe){//O(A)
	//ajoute à pgG une source/une trappe unique reliée à ts les sommets sans prédécesseurs/sans successeurs,transformant ainsi pgG en dipôle.
	int bArquer;
	int aK;
	int nPred[kuGrapheSommetLim];
	int nSommet;
	int sX;
	Assert2("GraphePolariser0",bGrapheSimple(pgG),pgG->nSommetEnTout+3<kuGrapheSommetLim);
	nSommet=pgG->nSommetEnTout;
	*psSource=nSommet+1;
	*psTrappe=nSommet+2;
	pgG->nSommetEnTout+=2;//avant l'appel de bGrapheArqueR afin de valider les assertions au début du code de bGrapheArqueR()
	pgG->aHed[nSommet+2]=pgG->aHed[nSommet+1];
	pgG->aHed[nSommet+3]=pgG->aHed[nSommet+2];
	Assert1("GraphePolariser1",bGrapheSimple(pgG));
	bArquer=kV;
	//sSource soit reliée à tous les sommets sans prédécesseurs
		for (sX=1;sX<=nSommet;sX++)
			nPred[sX]=0;
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				nPred[pgG->sSuk[aK]]++;
		for (sX=1;sX<=nSommet;sX++)
			if (nPred[sX]==0)
				bArquer=bArquer && bGrapheArqueR(pgG,*psSource,sX,0);//confronte sSource à pgG->nSommetEnTout
	//sTrappe soit reliée à tous les sommets sans successeurs
		for (sX=1;sX<=nSommet;sX++)
			if (pgG->aHed[sX]==pgG->aHed[sX+1])
				bArquer=bArquer && bGrapheArqueR(pgG,sX,*psTrappe,0);//confronte sSource à pgG->nSommetEnTout
	Assert2("GraphePolariser2",bArquer,bGrapheSimple(pgG));
}//GraphePolariser

void GraphePondererPareiL(graf *pgG){//O(A)
	//pgG->nCout[(X,Y)]=pgG->nCout[(Y,X)]=Sup(pgG->nCout[(X,Y)],pgG->nCout[(Y,X)]).
	int aK,sX,sY;
	int nMatrice[1+pgG->nSommetEnTout][1+pgG->nSommetEnTout];//N.B. NE PAS L'INITIALISER CAR CELA COUTERAIT O(S2), PLUS CHER QUE O(A) si pgG non dense.
	Assert1("GraphePondererPareiL",bGrapheSymetrique(pgG));
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurRazer(nMatrice[sX],1,pgG->nSommetEnTout);
	if (0) for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		VecteurVoir("nMatrice[sX]",nMatrice[sX],1,pgG->nSommetEnTout);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			nMatrice[sY][sX]=nMatrice[sX][sY]=iSup(pgG->nCout[aK],nMatrice[sX][sY]);
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			pgG->nCout[aK]=nMatrice[sX][sY];
		}
	//VecteurVoir("gG->nCout[aK]",pgG->nCout,1,pgG->nArcEnTout);
}//GraphePondererPareiL

void GraphePonderer(graf *pgG,int sOrigine,int sDestination,int nArcCout){//O(A)
	//pgG->nCout["sOrigine,sDestination"]=nArcCout.
	Assert1("GraphePonderer",nArcCout>=0);
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	pgG->nCout[aK]=nArcCout;
}//GraphePonderer

void GraphePonderer0(graf *pgG,int nArcCout){//O(A)
	//initialise pgG->nCout[aK] avec nArcCout.
	Assert1("GraphePonderer0",nArcCout>=0);
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		pgG->nCout[aK]=nArcCout;
}//GraphePonderer0

void GraphePonderer2(graf *pgG,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMax et nCout de pgG avec des valeurs aléatoires dans [1..uCapaMax] et [1..uCoutMax], unitaires si uCapaMax ou uCoutMax=1.
	Assert2("GraphePonderer2",uCapaMax>0,uCoutMax>0);
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer2

void GraphePonderer3(graf *pgG,int uCapaMin,int uCapaMax,int uCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec des valeurs aléatoires dans [1..uCapaMax],etc, unitaires si uCapaMax,etc,=1.
	Assert3("GraphePonderer3",uCapaMin>0,uCapaMax>0,uCoutMax>0);
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMin[aK]=uHasard(uCapaMin);
		pgG->nCapaMax[aK]=uHasard(uCapaMax);//ds [1..uCapaMax]
		pgG->nCout[aK]=uHasard(uCoutMax);
	}
}//GraphePonderer3

void GraphePonderer5(graf *pgG,int sOrigine,int sDestination,int nCapaMin,int nCapaMax,int nCoutMax){//O(A)
	//initialise les champs nCapaMin, nCapaMax, et nCout avec les valeurs positives ou nulles spécifiées uCapaMin,uCapaMax et uCoutMax.
	Assert3("GraphePonderer50",nCapaMin>=0,nCapaMax>=0,nCoutMax>=0);
	//tee("sOrigine,sDestination",sOrigine,sDestination);
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("GraphePonderer51",aK>0);
	pgG->nCapaMin[aK]=nCapaMin;
	pgG->nCapaMax[aK]=nCapaMax;
	pgG->nCout[aK]=nCoutMax;
}//GraphePonderer5

void GraphePondererAleatoirement(graf *pgG,int uBorneMax){//O(A)
	//initialiser pgG avec des valeurs aléatoires dans [1..uBorneMax] les 3 champs nCapaMax[],nCout[] et nPoids[]
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapaMax[aK]=uHasard(uBorneMax);
		pgG->nCout[aK]=uHasard(uBorneMax);
		pgG->nPoids[aK]=uHasard(uBorneMax);
	}
}//GraphePondererAleatoirement

void GrapheQuinconceR(graf *pgG,int bBipartir){
	//déroule pgG en quinconce de façon à obtenir un dag puis,si bBipartir,dédouble chaq sommet en lui attribuant 2 numéros de sommets csécutifs.
	const int kbQuinconcer=kF;
	int bDesarquer;
	int nOffset;
	int bQuinconce;
	int uCoteh,nEtage,aK,sX,sY;
	if (kbQuinconcer) Appel0("GrapheQuinconceR");
	Assert1("GrapheQuinconceR1",bGrapheSimple(pgG));
	uCoteh=pgG->nSommetEnTout;//côté du graphe étagé à venir
	GrapheDerouler(pgG);
	Assert1("GrapheQuinconceR2",bGrapheSimple(pgG));
	//supprimer les arcs hors quinconce
		for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
			bQuinconce=(bPair(nEtage)==bPair(sX));
			if (sX==1)
				Assert1("bQuinconce",bQuinconce);
			for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
				if (!bQuinconce){
					sY=pgG->sSuk[aK];
					bDesarquer=bGrapheDesarquer(pgG,sX,sY);
					Assert1("GrapheQuinconceR",bDesarquer);
				}
			}
			if ((sX-1) % uCoteh==0)
				nEtage--;
		}
		if (kbQuinconcer) VecteurVoir("aHed4",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk4",&pgG->sSuk[0],1,pgG->nArcEnTout+pgG->nSommetEnTout/2);
		if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé");
	Assert1("GrapheQuinconceR3",bGrapheSimple(pgG));
	if (bBipartir){//réaffecter les sommets hors quinconce;le sommet 1 dédoublé devient 1 et 2;mais à l'étage suivant,le sommet n devient n-1 et n. 
		//insérer dans pgG->sSuk[] 1 arc par sommet hors quinconce ——de façon à ajouter 1 arc en pgG->sSuk[1] et en prendre acte dans pgG->aHed[]. 
			Assert1("GrapheQuinconceR4",pgG->nArcEnTout+pgG->nSommetEnTout<kuGrapheArcLim);
			for (sX=pgG->nSommetEnTout;sX>=1;sX-=2)
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX-1];aK--){
					sY=pgG->sSuk[aK];
					pgG->sSuk[aK+sX/2]=-sY;//décale les arcs et en profite pour les marquer négativement (exploité plus bas, et pour deboguer)
				}
			for (nOffset=0,nEtage=0,sX=1;sX<=pgG->nSommetEnTout+1;sX++){
				if (bQuinconce=(bPair(nEtage)==bPair(sX)))
					nOffset++;
				pgG->aHed[sX]+=nOffset;
				if ((sX-1) % uCoteh==0)
					nEtage++;
			}
			pgG->nArcEnTout+=nOffset;
			if (kbQuinconcer) VecteurVoir("aHed5",&pgG->aHed[0],1,pgG->nSommetEnTout);
			if (kbQuinconcer) VecteurVoir("sSuk5",&pgG->sSuk[0],1,pgG->nArcEnTout);
			if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé TRANSITOIRE");
		//actualiser la cible de chaque arc: l'arc origine d'un sommet dédoublé cible le sommet suivant;l'arc destination cible un sommet positif. 
			for (nEtage=uCoteh,sX=pgG->nSommetEnTout;sX>=1;sX--){
				bQuinconce=(bPair(nEtage)==bPair(sX));
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					sY=pgG->sSuk[aK];
					if (sY<0)//cet arc original doit cibler maintenant le sommet origine de chaque sommet bipartitionné
						pgG->sSuk[aK]=bPair(nEtage)? -sY : -sY-1;//cible le bon sommet positif.
					else pgG->sSuk[aK]=sX+1;//logique car le sommet 1 est devenu 1 et 2;à l'étage suivant, n est devenu n-1 et n
				}
				if ((sX-1) % uCoteh==0)
					nEtage--;
			}
		if (kbQuinconcer) VecteurVoir("aHed6",&pgG->aHed[0],1,pgG->nSommetEnTout);
		if (kbQuinconcer) VecteurVoir("sSuk6",&pgG->sSuk[0],1,pgG->nArcEnTout);
		if (kbQuinconcer) GrapheVoir(pgG,"Graphe biparti quinconcé FINAL");
	}//Le plus souvent,le graphe obtenu n'est pas connexe. 
	Assert2("GrapheQuinconceR2",bGrapheSimple(pgG),!bBipartir || bGrapheBiparti(pgG));//Si bBipartir,aucun sommet n'est isolé.
	if (kbQuinconcer) Appel1("GrapheQuinconceR");
}//GrapheQuinconceR

void GrapheQuintesser(graf *pgG,int nSommet){
	//génère un graphe déroulé bipari en quiconce puis l'étoile et connecte les étoiles amont et aval à chaque colonne;
	#define kbQuintesser kF
	int uB,uE,nPaire,sX,sYamont,sYaval;
	int bDesarquer;
	int aK,aL;
	int nSommet0;
	if (kbQuintesser) Appel0("GrapheQuintesser");
	if (kbQuintesser) te("nSommet",nSommet);
	GrapheCliquer(pgG,nSommet);
	if (0){
		if (nSommet==3)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,3,2);
		if (nSommet==4)
			bDesarquer=bGrapheDesarquer(pgG,2,3) && bGrapheDesarquer(pgG,2,4);
	}
	GrapheVoir(pgG,"Graphe cliqué");
	GrapheBipartitionner(pgG);
	GrapheVoir(pgG,"Graphe cliqué biparti");
	GrapheQuinconceR(pgG,k1BipartiR);
	//refermer le chemin diagonal pour obtenir un circuit
		GrapheArquer(pgG,1,pgG->nSommetEnTout);
	GrapheVoir(pgG,"Graphe cliqué biparti quinconcé et bipartitionné");
	nSommet0=pgG->nSommetEnTout;
	int nEtoile=4*nSommet;
	if (kbQuintesser) te("nEtoile",nEtoile);
	int uBrancheParEtoile=nSommet;
	int nSommetParEtoile=1+uBrancheParEtoile;
	if (kbQuintesser) te("uBrancheParEtoile",uBrancheParEtoile);
	GrapheEtoiler(pgG,nEtoile,uBrancheParEtoile);
	GrapheVoir(pgG,"Graphe cliqué biparti quinconcé bipartitionné et étoilé");
	if (kbQuintesser) te("nSommet0",nSommet0);
	//connecter les étoiles au reste du graphe
		for (uE=1;uE<=nEtoile/2;uE++){
			sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;//centre étoile amont
			sYaval=sYamont+nSommetParEtoile;//centre étoile aval
			if (kbQuintesser) printf("Centres des étoiles amont et aval:%d,%d.\n",sYamont,sYaval);
			for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
				if (kbQuintesser) printf("arc sX,Centre amont:       (%2d,%2d)\n",sX,sYamont);
				if (kbQuintesser) printf("arc sX,Centre aval:       (%2d,%2d)\n",sX+1,sYaval);
				GrapheArquer(pgG,sX,sYamont);
				GrapheArquer(pgG,sX+1,sYaval);
				sX+=4*nSommet;
			}
		}
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		pgG->aDeh[sX]=0;
	for (nPaire=0,uE=1;uE<=nEtoile/2;uE++){
		sYamont=nSommet0+2*(uE-1)*nSommetParEtoile+1;
		sYaval=sYamont+nSommetParEtoile;
		pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
		if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
		if (kbQuintesser) te("étoile0",sYamont);
		for (sX=2*(uE-1)+1,uB=1;sYamont++,sYaval++,uB<=uBrancheParEtoile;uB++){
			//if (kbQuintesser) printf("arc sX,sYamont:       (%2d,%2d)\n",sX,sYamont);
			//if (kbQuintesser) printf("arc sX,sYaval:       (%2d,%2d)\n",sX+1,sYaval);
			aK=nGrapheArc(pgG,sX,sYamont);
			aL=nGrapheArc(pgG,sX+1,sYaval);
			pgG->aDeh[sX]=sX+1;pgG->aDeh[sX+1]=sX;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sX,sX+1));
			pgG->aDeh[sYamont]=sYaval;pgG->aDeh[sYaval]=sYamont;nPaire++;
			if (kbQuintesser) printf("Couple %s\n",sCouple(sYamont,sYaval));
			sX+=4*nSommet;
		}
	}
	teee("nEtoile,uBrancheParEtoile+1,nPaire",nEtoile,uBrancheParEtoile+1,nPaire);
	Assert1("GrapheQuintesser",sYaval=pgG->nSommetEnTout);
	if (kbQuintesser) Appel1("GrapheQuintesser");
}//GrapheQuintesser

int bGrapheSimple(graf *pgG){
	//ni boucle,ni plus d'un arc d'un sommet origine à un sommet destination
	int aK,sX,sY;
	int bSimple;
	int nSucc[1+pgG->nSommetEnTout];
	Assert2("bGrapheSimple",bGrapheAmorceR,bGraphe(pgG));
	for (bSimple=kV,sX=1;sX<=pgG->nSommetEnTout;sX++){
		for (sY=1;sY<=pgG->nSommetEnTout;sY++)
			nSucc[sY]=0;
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if ( !bGrapheSommet(pgG,sY) || (sX==sY) || (++nSucc[sY]>1) )
				bSimple=kF;
		}
	}
	return(bSimple);
}//bGrapheSimple

void GrapheSommer(graf *pgG,int inEmpilerSinonDepiler){
	//si inEmpilerSinonDepiler>0,empile inEmpilerSinonDepiler sommets;si <0,élimine ts les arcs liés aux sommets et les dépile (n° pgG->nSommetEnTout) puis dépile ce sommet
	int uS;
	Assert2("GrapheSommer1",bGrapheAmorceR,bGrapheSimple(pgG));
	//te("inEmpilerSinonDepiler",inEmpilerSinonDepiler);
	if (inEmpilerSinonDepiler!=0)
		if (inEmpilerSinonDepiler>0) {
			Assert1("GrapheSommer2",pgG->nSommetEnTout+inEmpilerSinonDepiler<kuGrapheSommetLim);
			for (uS=1;uS<=inEmpilerSinonDepiler;uS++){
				pgG->aHed[pgG->nSommetEnTout+2]=pgG->aHed[pgG->nSommetEnTout+1];//crée les nouveaux sommets,sans arcs incidents.
				(pgG->nSommetEnTout)+=1;
			}//te("pgG->nSommetEnTout",pgG->nSommetEnTout);
		}
		else {
			Assert1("GrapheSommer3",pgG->nSommetEnTout>-inEmpilerSinonDepiler);
			for (uS=1;uS<=-inEmpilerSinonDepiler;uS++){
				GrapheDesarquerTout(pgG, pgG->nSommetEnTout);//dépile le dernier sommet
				pgG->aHed[pgG->nSommetEnTout+1]=0;
				(pgG->nSommetEnTout)--;
			}
		}
	Assert2("GrapheSommer4",bGraphe(pgG),bGrapheSimple(pgG));
}//GrapheSommer

int bGrapheSommet(graf *pgG,int sSommet){
	int bGrapheSommet=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bGrapheSommet);
}//bGrapheSommet

int bGrapheSymetrique(graf *pgG){//O(A)
	//à tout arc (X,Y) présent dans pgG correspond dans pgG un arc inverse (Y,X)
	graf *pgH;
	int bSymetrique;
	Assert2("bGrapheSymetrique",bGrapheAmorceR,bGraphe(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		//GrapheVoir(pgH,"pgH");
		GrapheSymetriser(pgH);//O(A)
		bSymetrique=(pgG->nArcEnTout==pgH->nArcEnTout);
	free(pgH);
	//Assert1("bGrapheSymetrique1",bSymetrique);
	return(bSymetrique);
}//bGrapheSymetrique

void GrapheSymetriqueCreerPondereR(int bDense,int nSommetEnTout,int uPoidsMax,graf **ppgG){
	//alloue et rend un graphe symétrique "intéressant" à nSommetEnTout sommets,pondéré aléatoirement de 1 à uPoidsMax ——champ (*ppgG)->nCout. 
	int aK,aL;
	int sX,sY;
	//Appel0("GrapheSymetriqueCreerPondereR");
		Assert2("GrapheSymetriqueCreerPondereR",uPoidsMax>0,bCroitStrict(0,nSommetEnTout,kuGrapheSommetLim));
		if (bDense)
			GrapheCompletCreerPondereR(nSommetEnTout,ppgG);
		else GrapheCreer(nSommetEnTout,ppgG);
			//GrapheVoir(pgG,"AVANT symétrisation");
			GrapheSymetriser(*ppgG);
			//GrapheVoir(pgG,"APRES symétrisation");
			if (0){
				t("Extrémités des arêtes");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sSuk[aK]);
				printf("\n");
				for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++)
					printf("%4d",(*ppgG)->sKus[aK]);
				printf("\n");
			}
			GrapheInverser(*ppgG);//pour Kruskal
			//initialiser les poids pgG->nCout[aK] et compléter la correspondance aK->sX,sY via pgG->nPhi[aK]=sX en plus de pgG->sSuk[aK]=sY
				for (sX=1;sX<=(*ppgG)->nSommetEnTout;sX++)
					for (aK=(*ppgG)->aHed[sX];aK<(*ppgG)->aHed[sX+1];aK++){
						sY=(*ppgG)->sSuk[aK];
						aL=(*ppgG)->aInv[aK];
						Assert1("GrapheSymetriqueCreerPondereR2",(*ppgG)->sSuk[aL]==sX); 
						(*ppgG)->nPhi[aK]=sX;
						Assert1("GrapheSymetriqueCreerPondereR3",(*ppgG)->sSuk[(*ppgG)->aInv[aK]]==(*ppgG)->nPhi[aK]);//donc nPhi est d'une certaine façon superflu
						(*ppgG)->nCout[aK]=uHasard(uPoidsMax);
						//teeee("arête et poids X Y",aK,pgG->nCout[aK],sX,sY);
					}
				GraphePondererPareiL(*ppgG);//O(A);le poids des arcs (X,Y) et (Y,X) est maintenant identique.
			//GrapheVoir0(*ppgG,"——— Donnée: un graphe non orienté");
				if (0) for (aK=1;aK<=(*ppgG)->nArcEnTout;aK++){
					te("aK",aK);
					Assert1("GrapheSymetriqueCreerPondereR8",(*ppgG)->nPhi[aK]>0);
				}
	//Appel1("GrapheSymetriqueCreerPondereR");
}//GrapheSymetriqueCreerPondereR

void GrapheSymetriser(graf *pgG){//O(A)
	//symétrise pgG en complétant les (X,Y) par les (Y,X) manquants. Reconduit pgG->coulh[] et pgG->nCout[] sur l'arc (Y,X) manquant.
	int aK,aL,aM;//aM est l'index de pile qui progresse sur pgG->sSuk[],cf pgG->sSuk[++aM]
	graf *pgH;
	int nCumul[1+pgG->nSommetEnTout];
	int bPred[1+pgG->nSommetEnTout];
	int bSucc[1+pgG->nSommetEnTout];
	int sX,sZ;
	Assert2("GrapheSymetriser",bGrapheAmorceR,bGraphe(pgG));
	pgH=(graf *) malloc(sizeof(graf));
		GrapheDupliquer(pgG,&pgH);//O(A)
		GrapheInverser(pgH);//O(A)
		//GrapheVoir1(pgG,k1Couleur,"pgG");GrapheVoir1(pgH,k1Couleur,"pgH");
		//pgG->sSuk[],pgG->coulh[],nCumul[]:= les arcs de pgG symétrisé, ses couleurs, le cumul des arcs empilés sommet par sommet.
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				bPred[sX]=bSucc[sX]=kF;
			for (aM=0,sX=1;sX<=pgH->nSommetEnTout;sX++){//O(A): les 3 aK et les 3 aL ci-dessous visitent 6 fois la totalité des arcs de pgH 
				//bSucc[] / bPred[]:=coche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kV;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kV;
					//VecteurVoir("nSucc",nSucc,1,pgG->nSommetEnTout);VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
				//empiler dans pgG les sommets de bSucc union bPred,ie tous ceux de pgH->sSuk[],plus ceux cochés dans bPred mais pas dans bSucc:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++){//au total,cet aK aura passé en revue 1 fois la totalité des arcs de pgH
						Assert1("GrapheSymetriser1",aM+1<kuGrapheArcLim);
						pgG->sSuk[++aM]=pgH->sSuk[aK];
						pgG->coulh[aM]=pgH->coulh[aK];
						pgG->nCout[aM]=pgH->nCout[aK];
					}
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++){//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						sZ=pgH->sKus[aL];
						if (bPred[sZ] && !bSucc[sZ]){//ajouter l'arc manquant aL:
							Assert1("GrapheSymetriser2",aM+1<kuGrapheArcLim);
							pgG->sSuk[++aM]=sZ;
							pgG->coulh[aM]=pgH->coulh[pgH->aInv[aL]];//la couleur de l'arc aL est par défaut celle de l'arc inverse de aL.
							pgG->nCout[aM]=pgH->nCout[pgH->aInv[aL]];
						}
					}
				nCumul[sX]=aM;
				//bSucc[] / bPred[]:=décoche des sommets successeurs de sX dans pgH / des sommets prédécesseurs de sX dans pgH:
					for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++)//au total,cet aK aura indexé 1 fois chacun des arcs de pgH.
						bSucc[pgH->sSuk[aK]]=kF;
					for (aL=pgH->aDeh[sX];aL<pgH->aDeh[sX+1];aL++)//au total,cet aL aura indexé 1 fois chacun des arcs de pgH.
						bPred[pgH->sKus[aL]]=kF;
			}
	free(pgH);
	//pgG->aHed[]:=nouveaux index fonctions de nCumul[]
		//pgG->aHed[1] vaut déjà 1.
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX+1]=nCumul[sX]+1;
	//pgG->nSommetEnTout est déjà correct: symétriser le graphe ne modifie pas le nombre de ses sommets.
	pgG->nArcEnTout=nCumul[pgG->nSommetEnTout];
	Assert1("GrapheSymetriser",bGrapheSimple(pgG));
	//GrapheVoir1(pgG,k1Couleur,"pgG symétrisé");
}//GrapheSymetriser

void GrapheTESTER(int iTest){
	const int k1Prim=kV;
	const int ksSource=1;
	int bkAfficher=1;
	int nArcOrigine[]=    {0,   1,2,3,3,2};
	int nArcDestination[]={0,   2,3,1,2,1};
	int nGraphe,nPoidsMax;
	char kcTriominoComplet[]="AB1BC1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 1 composante fortement connexe
	char kcTriominoIncomplet[]="AB1BG1CD1CF7DE1EF1FG1GH1HA9";//1 composante connexe et 5 composantes fortement connexes
	int bBiparti,bCheminer,bCircuit,nComplexiteh,bEulerien,aK;
	graf *pgG;
	int bSimple;
	int nSommet,uSommet;
	char *sgrNom=GrapheNom;
	enum grType GrapheType;
	// GrapheType {grAlpha,grL4,grC4b,grC2,grC3,grC4,grC5,grC6,grK2,grK3,grK4,grK5,grK6,grP2,grP3,grP4,grP5,grP6,grP7,grP8,grS2,grS3,grS4,grS5,grS6,grOmega}

	Appel0(sC2("GrapheTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=8,pgG) );
					bSimple=bGrapheSimple(pgG);
					printf( "Le graphe à %s %s simple.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bSimple) );
					GrapheCreer(0,&pgG);
					break;
			case 2: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=2,pgG) );
					GrapheSymetriser(pgG);
					GrapheVoir(pgG,"graphe eulérien non orienté");
					GrapheInverser(pgG);
					bEulerien=bGrapheEulerien(pgG,1,1);
					printf( "Le graphe à %s %s eulérien.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bEulerien) );
					bEulerien=bEulerien && bGrapheEulerier(pgG,1,1);
					GrapheCreer(0,&pgG);
					break;
			case 3: GrapheSymetriqueCreerPondereR(k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0(pgG,"——— Donnée: un graphe non orienté",grCout);
						GrapheCouvrirAvecPrimOuP(pgG,k1Prim,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 4: GrapheSymetriqueCreerPondereR(!k1Dense,50,nPoidsMax=9,&pgG);
						GrapheVoir0(pgG,"——— Donnée: un graphe non orienté",grCout);
						GrapheCouvrirAvecKruskaL(pgG,k1Afficher,k1PerformanceCompareR);
					GrapheCreer(0,&pgG);
					break;
			case 5: ElectrifieR();
					break;
			case 6: if (0) for (uSommet=1;uSommet<10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerCourt(pgG,ksSource,pgG->nSommetEnTout,bkAfficher,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=10;uSommet<=10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheArquer(pgG, 1, 4);
							bGrapheDesarquer(pgG, 4, 2);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerLong(pgG,ksSource,pgG->nSommetEnTout,bkAfficher,&nComplexiteh);
							if (!bkAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=3;uSommet<10;uSommet++){
						GrapheCreer(uSommet, &pgG);
							GrapheInverser(pgG);
							GrapheVoir2(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCircuit=bGrapheCircuite(pgG);
							t(sC3bp("Il",sUn("y a",bCircuit),"circuit"));
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(4,&pgG);
							GrapheDerouler(pgG);
							GrapheVoir(pgG,sC4b("Le graphe étagé a",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
						GrapheCreer(0,&pgG);
					}
					if (1){
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG);
							GraphePondererAleatoirement(pgG,5);
							GrapheVoir0(pgG,"Graphe de largeur",grCout);
							bCircuit=bGrapheCheminerAuLargE(pgG,1,6,kV);//***********
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(3,&pgG);
							GrapheSymetriser(pgG);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheSymetriser(pgG);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheSymetriser(pgG);
							bBiparti=bGrapheBipartiOuAfficherCycleImpair(pgG);
							GrapheVoir(pgG,sC3b("Le graphe ci-dessous",sEst(bBiparti),"biparti"));
						GrapheCreer(0,&pgG);
					}
					break;
					if (0){
						GrapheCreer(3,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
						GrapheCreer(4,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
						GrapheCreer(6,&pgG);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
						GrapheCreer(0,&pgG);
					}
					break;
			case 7:	{//GrapheQuinconceR & GrapheEtoiler
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir(pgG,"Graphe original");
							GrapheBipartitionner(pgG);
							GrapheVoir(pgG,"Graphe biparti résultant");
							GrapheQuinconceR(pgG,k1BipartiR);
							GrapheVoir(pgG,"Graphe biparti quinconcé et bipartitionné");
							GrapheEtoiler(pgG,2,3);
							GrapheVoir(pgG,"Graphe biparti quinconcé et bipartitionné et étoilé 2*3");
						GrapheCreer(0,&pgG);
					}
					break;
			case 8:	{//GrapheCliquer
						GrapheCreer2(&pgG,3,5,&nArcOrigine[0],&nArcDestination[0]);
							GrapheVoir(pgG,"Graphe original");
							GrapheCliquer(pgG,4);
							GrapheVoir(pgG,"Graphe original cliqué");
						GrapheCreer(0,&pgG);
					}
					break;
			case 11:{//GrapheQuintesser
						GrapheCreer0(&pgG,kV);
							GrapheQuintesser(pgG,nSommet=3);
							GrapheVoir(pgG,"Graphe quiné");
						GrapheCreer0(&pgG,kF);
					}
					break;
			case 13:	DijkstraAvecOuSansTasCompareR();
					break;
			case 15:	GrapheCreer(4,&pgG);
						GrapheColorer(pgG,1,2,1);
						GrapheColorer(pgG,2,4,2);
						GrapheColorer(pgG,3,2,3);
						GrapheColorer(pgG,3,1,4);
						GrapheColorer(pgG,3,4,5);
						GrapheVoir1(pgG,k1Couleur,"Graphe original");
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER90",!bBof);
						GrapheSymetriser(pgG);
						GrapheVoir1(pgG,k1Couleur,"Graphe symétrisé");
						bBof=bGrapheSymetrique(pgG);
						Assert1("GrapheTESTER91",bBof);
					GrapheCreer(0,&pgG);
					break;
			case 20:	GrapheGenerer(kcTriominoIncomplet,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 30:	GrapheGenerer(kcTriominoComplet,&pgG);
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							pgG->nCout[aK]=pgG->coulh[aK];
						GrapheCircuiterAuMieux(pgG);
						break;
			case 40:
					Titrer("test des types de graphe générées");
					for (nGraphe=grAlpha+1;nGraphe<grOmega;nGraphe++){
						//t(sItem(sgrNom,1+nGraphe));
						GrapheCreer1(&pgG,nGraphe,k1Creer);
							GrapheVoir(pgG,sItem(sgrNom,1+nGraphe));
						GrapheCreer0(&pgG,kF);
					}
					break;
			default:break;
		}
	Appel1(sC2("GrapheTESTER,test n°",sEnt(iTest)));
}//GrapheTESTER

void GrapheTranslater(graf *pgG,int uOffset){
	//renumérote tous les sommets de pgG: le sommet n°sX aura pour n°sX+uOffset.
	int aK,sX;
	Assert1("GrapheTranslater",uOffset>0);
	//d2(uOffset,pgG->nSommetEnTout);
	//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	GrapheSommer(pgG,uOffset);
	//d2(uOffset,pgG->nSommetEnTout);
	for (sX=pgG->nSommetEnTout+1;sX>uOffset;sX--)
		pgG->aHed[sX]=pgG->aHed[sX-uOffset];
	for (sX=uOffset;sX>0;sX--)
		pgG->aHed[sX]=1;
	//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout+1);
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		pgG->sSuk[aK]+=uOffset;
}//GrapheTranslater

void GrapheTrier(graf *pgG){
	//effectue un tri topologique
	const int kbVoir=kF;
	int nNiveau[1+pgG->nSommetEnTout];
	int nPred[1+pgG->nSommetEnTout];
	int uCardinal,uS,aK,sX,sY,nNivo=0;
	Assert1("GrapheTrier",bGrapheSimple(pgG));
	//nPred[sY]:=degré entrant du sommet sY
		VecteurRazer(nPred,1,pgG->nSommetEnTout);//O(S)
		for (aK=1;aK<=pgG->nArcEnTout;aK++)//O(A)
			nPred[sY=pgG->sSuk[aK]]++;
	DequeAllouer(pgG->nSommetEnTout);
		VecteurRazer(nNiveau,1,pgG->nSommetEnTout);//O(S)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			if (!nPred[sX]) DequeEnfiler(sX);
		if (kbVoir) VecteurVoir("nPred",nPred,1,pgG->nSommetEnTout);
		while (!bDequeVide())
			for (nNivo++,uCardinal=nDequeCardinal(),uS=1;uS<=uCardinal;uS++){
				sX=sDequeDefiler();
				nNiveau[sX]=nNivo;
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					nPred[sY=pgG->sSuk[aK]]--;
					Assert1("GrapheTrier8",nPred[sY]>=0);
					if (!nPred[sY])
						DequeEnfiler(sY);
				}
			}
		if (kbVoir) VecteurVoir("nNiveau",nNiveau,1,pgG->nSommetEnTout);
	DequeAllouer(0);
}//GrapheTrier

int bGrapheVidE(graf *pgG){
	int bVide;
	Assert2("bGrapheVidE0",bGrapheAmorceR,bGraphe(pgG));
	bVide=(pgG->nSommetEnTout==0);
	if (bVide)
		Assert1("bGrapheVidE1",pgG->nArcEnTout==0);//sinon,savoir pourquoi
	return(bVide);
}//bGrapheVidE

void GrapheViseR(graf *pgG,char *sMessage){
	//affiche la structure brute de pgG
	int aK,sX;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s et %s):\n",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	if (pgG->nArcEnTout>0){
		VecteurVoir2(" aHed",pgG->aHed,1,pgG->nSommetEnTout);
		VecteurVoir2(" aDeh",pgG->aDeh,1,pgG->nSommetEnTout);
		printf(" sSuk");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sSuk[aK]);
			//printf("\n");
		}
		printf("\n sKus");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sKus[aK]);
			//printf("\n");
		}
		printf("\n aInv");
		for (aK=1;aK<=pgG->nArcEnTout;aK++){
			printf("  (%d,%d)",aK,pgG->aInv[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheViseR

void GrapheVoir(graf *pgG,char *sMessage){
	//énumère les arcs de pgG sous la forme de couples (origine,destination)
	const int kuArcParLigne=10;
	const int kuIndentation=1;
	int aK,sX;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s, %s, densité %.3f):\n%s",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"),fGrapheDensiteh(pgG),sTab(kuIndentation));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				if (pgG->nSommetEnTout<kE2 && pgG->nArcEnTout<kE2)
					printf("  (%2d,%2d)",sX,pgG->sSuk[aK]);
				else printf("  (%3d,%3d)",sX,pgG->sSuk[aK]);
				if (aK % kuArcParLigne==0 && aK<pgG->nArcEnTout)
					printf("\n%s",(aK<pgG->nArcEnTout)? sTab(kuIndentation) : "");
			}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir

void GrapheVoir0(graf *pgG,char *sMessage,int nAttribut){
	//affiche les arcs de pgG sous forme de triplets (origine,destination,attributs) ——GrapheVoir0(pgG,grCout+grPhi) demande nCout et nPhi.
	int aK,sX,sY;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s à %s et %s spécifié par triplets (sommet,sommet",sMessage,sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel((pgG->nArcEnTout), "arc"));
		if (nAttribut & grCapaMax) printf(",≤capamax");
		if (nAttribut & grCapaMin) printf(",≥capamin");
		if (nAttribut & grCouleur) printf(",çouleur");
		if (nAttribut & grCout) printf(",©coût");
		if (nAttribut & grPoids) printf(",πpoids");
		if (nAttribut & grPhi) printf(",ƒphi");
	printf("):\n   ");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				printf("  (%d,%d",sX,sY);
				if (nAttribut & grCapaMax) printf("≤%d",pgG->nCapaMax[aK]);
				if (nAttribut & grCapaMin) printf("≥%d",pgG->nCapaMin[aK]);
				if (nAttribut & grCouleur) printf("ç%d",pgG->coulh[aK]);
				if (nAttribut & grCout) printf("©%d",pgG->nCout[aK]);
				if (nAttribut & grPoids) printf("π%d",pgG->nPoids[aK]);
				if (nAttribut & grPhi) printf("ƒ%d",pgG->nPhi[aK]);
				printf(")");
			}
			//printf("\n");
		}
	} else printf(" Aucune arête");
	printf(".\n");
}//GrapheVoir0

void GrapheVoir1(graf *pgG,int bDontCouleur,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination,couleur)
	const int kbLitteral=1;
	int aK,sX;
	char cOrigine,cDestination;
	char cCouleur[1+knGrapheCouleurMax+2]={'z','v','r','b','j','n','d','g','h','f','s'};//zéro,vert,rouge,bleu,jaune,f=facultatif
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s et %s):\n   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				if (kbLitteral){
					//printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
					cOrigine=(bCroit(1,sX,kuMinusculeOffset-1))? 'A'+sX-kuMajusculeOffset : 'a'+sX-kuMinusculeOffset;
					cDestination=(bCroit(1,pgG->sSuk[aK],kuMinusculeOffset-1))? 'A'+pgG->sSuk[aK]-kuMajusculeOffset : 'a'+pgG->sSuk[aK]-kuMinusculeOffset;
					if (bDontCouleur)
						printf(" (%c,%c,%c)",cOrigine,cDestination,cCouleur[pgG->coulh[aK]]);
					else printf(" (%c,%c)",cOrigine,cDestination);
				} else if (bDontCouleur)
					printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
				else printf(" (%c,%c)",cOrigine,cDestination);
			}
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir1

void GrapheVoir2(graf *pgG,char *sMessage){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination)
	int aK,sX;
	Assert2("GrapheVoir2",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s et %s):\n",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	printf(" direct:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sSuk[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(" inverse:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sKus[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir2

void GrapheVoir3(graf *pgG,char *sMessage){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination,cout) puis (origine,destination,nPoids)
	int aK,sX;
	Assert2("GrapheVoir3",bGrapheAmorceR,sMessage!=0);
	//GrapheVoir2(pgG,sMessage);
	printf("%s%c(%s et %s):",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	printf("\n -cout:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d:%d)",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	if (0){
		printf("\n -prix:");
		if (pgG->nArcEnTout>0){
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					printf("  (%d,%d:%d)",sX,pgG->sSuk[aK],pgG->nPoids[aK]);
				//printf("\n");
			}
		} else printf(" Aucun arc");
	}
	printf(".\n");
}//GrapheVoir3

void GrapheVoir4(graf *pgG,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination,capamin) puis (origine,destination,capamax) puis (origine,destination,cout)
	#define kbArc 1
	int aK,sX;
	Assert2("GrapheVoir4",bGrapheAmorceR,sMessage!=0);
	//GrapheVoir2(pgG,sMessage);
	printf("%s%c(%s et %s):   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	printf("\n -capa min:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (kbArc || sX<pgG->sSuk[aK])
					printf("  (%d,%d:%d)",sX,pgG->sSuk[aK],pgG->nCapaMin[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n -capa max:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (kbArc || sX<pgG->sSuk[aK])
					printf("  (%d,%d:%3d)",sX,pgG->sSuk[aK],pgG->nCapaMax[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n -cout arc:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (kbArc || sX<pgG->sSuk[aK])
					printf("  (%d,%d:%3d)",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir4

void GrapheVoirCadufouA(graf *pgG,char *sMessage,int nLargeur[],int nLongueur[],int nVitMax[],int nNature[]){
	//énumère les arcs de gG sous la forme de couples (origine,destination:nLargeur,nLongueur,nVitMax,nNature)
	int aK,sX;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s à %s et %s sous la forme (source,cible:largeur,longueur,vitesse,nature):\n",sMessage,sPluriel(pgG->nSommetEnTout,"sommet"),sPluriel(pgG->nArcEnTout,"arc"));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d:%d,%d,%d,%d)",sX,pgG->sSuk[aK],nLargeur[aK],nLongueur[aK],nVitMax[aK],nNature[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoirCadufouA

#define kuCoureurMaX 6
#define kuFacteurMultiplicatiF kE2
#define k1GrandeLargeuR (kV)
#define kuCamionGrandeLargeur 5
#define kuTransportMaX 4
enum eNature {naAlpha,naChemin1,naFleuve2,naRoute3,naOmega};
enum eTransport             {trAlpha,trCamion1,trPorsche2,trScooter3,trMarche4,trTracteur5,trBicyclette6,trAviron7,trNage8,trOmega};
char *sTransporT[1+trOmega]={"Alpha", "Camion","Porsche",  "Scooter", "Marche", "Tracteur", "Bicyclette", "Aviron", "Nage", "Omega"};
int nVitesseMaX[1+trOmega]= {      0,      100,      300,         60,        5,         30,           20,       10,      3,       0};

int nCourseChronO(graf gG,int sSource,int sTrappe){
	//rend le temps mis par le coureur pour aller du sommet sSource au sommet sTrappe
	int bChemine=kF;
	int nChrono=0;
	int aK,sX,sY=sTrappe;
	Assert2("nCourseChronOa",bGrapheSommet(&gG,sSource),bGrapheSommet(&gG,sTrappe));
	//nChrono soit le cumul des champs gG.nCout[aK] situés sur le chemin qui va de sSource à sTrappe mémorisé en sens inverse dans gG.sPer[] 
		While(gG.nSommetEnTout);
		while (bWhile("nCourseChronO",(bChemine=bChemine || (sY==sSource),sY!=(sX=gG.sPer[sY]))) ) {
			aK=nGrapheArc(&gG,sX,sY);
			//teee("sX,sY,gG.nCout[aK]",sX,sY,gG.nCout[aK]);
			Assert1("nCourseChronO",aK>0);//l'arc existe tjrs,sauf erreur de programmation,humaine,que l'assertion signalera au plus tôt. 
			nChrono+=gG.nCout[aK];
			sY=sX;
		}
	Assert1("nCourseChronOb",nChrono>0);
	return(nChrono);
}//nCourseChronO

int uVitesseMaximalE(int nNature,int uTransport[],int bGrandeLargeur){
	//rend la vitesse du moyen transport le plus rapide sur une voie de nature nNature;bGrandeLargeur étend la gamme des moyens de transport disponibles.
	int nMaximale,uT;
	Assert2("uVitesseMaximalE",bCroitStrict(naAlpha,nNature,naOmega),bBool(bGrandeLargeur));
	for (nMaximale=0,uT=1;uT<=kuTransportMaX;uT++)
		switch (nNature) {//le code ci-dessous peut être compacté. Mais est-ce plus clair?
			case naChemin1:
					if (bCroit(trScooter3,uTransport[uT],trBicyclette6))
						nMaximale=yMax(nMaximale,nVitesseMaX[uTransport[uT]]);
				break;
			case naFleuve2:
					if (bCroit(trAviron7,uTransport[uT],trNage8))
						nMaximale=yMax(nMaximale,nVitesseMaX[uTransport[uT]]);
				break;
			case naRoute3:
					if (bCroit(trPorsche2,uTransport[uT],trMarche4))
						nMaximale=yMax(nMaximale,nVitesseMaX[uTransport[uT]]);
				break;
			default: Assert1("uVitesseMaximalE",0);//pr localiser le bug
		}
	Assert1("uVitesseMaximalE",nMaximale>0);//puisque les moyens de transport sont viables, il en existe un qui a une vitesse non nulle.
	return(nMaximale);
}//uVitesseMaximalE

int nCourseEffectueR(int uCoureur,graf *pgG,int sSource,int sTrappe,int uTransport[],int nLargeur[],int nLongueur[],int nVitMax[],int nNature[],int bGrandeLargeur){
	int aK,nCheminLg,nChrono,nComplexiteh,uVitesseMax;
	Assert4("nCourseEffectueRa",bCroit(1,uCoureur,kuCoureurMaX),bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe),bBool(bGrandeLargeur));
	//pgG->nCout[aK]:=cout de l'arc perçu par chaque coureur compte-tenu de la nature de la voie et de ses moyens de transport.
		for (aK=1;aK<=pgG->nArcEnTout;aK++){
			uVitesseMax=iMin(nVitMax[aK],uVitesseMaximalE(nNature[aK],&uTransport[0],bGrandeLargeur && nLargeur[aK]>kuCamionGrandeLargeur));
			//te("uVitesseMax",uVitesseMax);
			pgG->nCout[aK]=(nLongueur[aK]*kuFacteurMultiplicatiF)/uVitesseMax;
		}//N.B. kuFacteurMultiplicatiF permet de diviser sans passer par les réels: comparer 2000/3=666 et 2.0/3.0=0.667
	//GrapheVoir0(pgG,"Graphe de la cadufoua");
	nCheminLg=nGrapheChemineR(pgG,sSource,sTrappe,&nComplexiteh);
	nChrono=(nCheminLg>0)? nCourseChronO(*pgG,sSource,sTrappe): 0;//nCourseChronO exploite pgG->sPer[aK] pour calculer la durée du parcours
	Assert1("nCourseEffectueRb",nChrono>=0);
	return(nChrono);
}//nCourseEffectueR

int nCourseEffectueR3(int uCoureur,graf *pgG,int sSource,int sX,int sY,int sZ,int sTrappe,int uTransport[],int nLargeur[],int nLongueur[],int nVitMax[],int nNature[]){
	//chronomètre la course qui va de sSource à sTrappe en passant d'abord par sX, puis par sY puis par sZ.
	int nChrono,uC;
	Assert3("nCourseEffectueR3a",bCroit(1,uCoureur,kuCoureurMaX),bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe));
	Assert6("nCourseEffectueR3b",bGrapheSommet(pgG,sX),bGrapheSommet(pgG,sY),bGrapheSommet(pgG,sZ),sX!=sY,sY!=sZ,sZ!=sX);
	for (nChrono=0,uC=1;uC<=kuCoureurMaX;uC++){
		nChrono+=nCourseEffectueR(uC,pgG,sSource,sX,&uTransport[0],nLargeur,nLongueur,nVitMax,nNature,!k1GrandeLargeuR);
		nChrono+=nCourseEffectueR(uC,pgG,sX,sY,&uTransport[0],nLargeur,nLongueur,nVitMax,nNature,!k1GrandeLargeuR);
		nChrono+=nCourseEffectueR(uC,pgG,sY,sZ,&uTransport[0],nLargeur,nLongueur,nVitMax,nNature,!k1GrandeLargeuR);
		nChrono+=nCourseEffectueR(uC,pgG,sZ,sTrappe,&uTransport[0],nLargeur,nLongueur,nVitMax,nNature,!k1GrandeLargeuR);
	}
	Assert1("nCourseEffectueR3c",nChrono>=0);
	return(nChrono);
}//nCourseEffectueR3

int nParcoursExhaustifChronometreR(graf *pgG,int sSource,int bAfficher,int *pnPisteurRequis){
	//rend le temps total requis pour explorer en "largeur d'abord" toutes les voies depuis sSource, et calcule le résultat pnPisteurRequis.
	Assert3("nParcoursExhaustifChronometreR",bGrapheSimple(pgG),bGrapheSommet(pgG,sSource),bBool(bAfficher));
	int aK,sX,sY,uF,uProfondeur,nCardinal,nPisteur,nChronoMax;
	int nRequis[1+pgG->nArcEnTout];
	//à chaque sommet atteint,pgG->sPer[sX] mémorise le temps qu'il a fallu pour l'atteindre depuis sSource 
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			pgG->sPer[sX]=0;
	//à chaque arc atteint,pgG->nPhi[sX] mémorise la distance en nombre d'arcs depuis sSource;les arcs issus de sSource devront mémoriser un 1 et… 
	//…pgG->sKus[aK] mémorise la date à laquelle l'arc aK a bien été entièrement parcouru par au moins un pisteur parti de sSource. 
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			(pgG->nPhi[aK]=0,pgG->sKus[aK]=0);
	DequeAllouer(pgG->nArcEnTout);
		for (uProfondeur=1,aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
			DequeEnfiler((pgG->nPhi[aK]=uProfondeur,sY=pgG->sSuk[aK],pgG->sKus[aK]=pgG->sPer[sY]=pgG->nCout[aK],sY));
		do//pgG->nPhi[aK]:=distance à sSource en mode d'exploration "largeur d'abord" —d'où la file d'attente
			for (nCardinal=nDequeCardinal(),uProfondeur++,uF=1;uF<=nCardinal;uF++)//NB nCardinal et non pas nDequeCardinal() ds "uF<=nCardinal"
				for (sX=sDequeDefiler(),aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
					Assert1("pgG->sPer[sX]",pgG->sPer[sX]>0);
					if (pgG->nPhi[aK]==0)
						DequeEnfiler((pgG->nPhi[aK]=uProfondeur,sY=pgG->sSuk[aK],pgG->sKus[aK]=pgG->sPer[sY]=pgG->sPer[sX]+pgG->nCout[aK],sY));
				}
		while (nDequeCardinal()>0);
	DequeAllouer(0);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		Assert1("nParcoursExhaustifChronometreRa",pgG->sPer[sX]>0);//ts les sommets ont bien été atteints depuis sSource
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		Assert2("nParcoursExhaustifChronometreRb",pgG->nPhi[aK]>0,pgG->sKus[aK]>0);//ts les arcs ont bien été atteints depuis sSource
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		nRequis[aK]=0;
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		nRequis[pgG->nPhi[aK]]++;//nRequis[P] comptabilise ts les sommets situés à la profondeur P.
	for (nPisteur=0,aK=1;aK<=pgG->nSommetEnTout;aK++)
		nPisteur=iMax(nPisteur,nRequis[aK]);//les pisteurs explorent simultanémt les arcs situés à la mm profondeur.
	for (nChronoMax=0,aK=1;aK<=pgG->nArcEnTout;aK++)
		nChronoMax=iMax(nChronoMax,pgG->sKus[aK]);
	if (bAfficher){
		for (printf("sSource %d:\n",sSource),printf("  sX:  "),sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("%4d",sX);
		for (printf("\n  sY:  "),sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("%4d",pgG->sSuk[aK]);
		Ligne();
		VecteurVoir("nCou[]",&pgG->nCout[0],1,pgG->nArcEnTout);
		VecteurVoir("nPhi[]",&pgG->nPhi[0],1,pgG->nArcEnTout);
		VecteurVoir("sKus[]",&pgG->sKus[0],1,pgG->nArcEnTout);
		VecteurVoir("Rqis[]",&nRequis[0],1,pgG->nArcEnTout);
		printf("Chrono pire cas depuis le sommet %d: %d unités de tps.\n",sSource,nChronoMax);
	}
	*pnPisteurRequis=nPisteur;
	Assert2("nParcoursExhaustifChronometreRc",nChronoMax>0,nPisteur>0);
	return(nChronoMax);
}//nParcoursExhaustifChronometreR

void TransportAfficheR(int uCoureur,int uTransport[],int nIteration){
	Assert2("TransportAfficheR",bCroit(1,uCoureur,kuCoureurMaX),nIteration>=0);
	printf("Moyens de transport viables du coureur n°%d: ",uCoureur);
		for (int uT=1;uT<=kuTransportMaX;uT++)
			printf("%s%s",sTransporT[uTransport[uT]],sChoix0(uT<kuTransportMaX,","));
	printf("%s.\n",sChoix0(nIteration>0,sC3(" (obtenu en ",sPluriel(nIteration,"tirage"),")")));
}//TransportAfficheR

void TransportViabiliseR(int uTransport[],int bGrandeLargeur,int nCoureurOuZero){
	int uT,bViable,bRoute,bChemin,bFleuve,nIteration=0;
	Assert2("TransportViabiliseR",bBool(bGrandeLargeur),bCroit(0,nCoureurOuZero,kuCoureurMaX));
	do{//puisque le nbre de moyens de transport grande largeur n'est pas imposé, on simplifie le problème en n'en prenant qu'un: trCamion1. 
		for (nIteration++,uT=1;uT<=kuTransportMaX;uT++){
			uTransport[uT]=(bGrandeLargeur)? uHasard(trOmega-1): 1+uHasard(trOmega-2);//cette ligne n'étant pas limpide, la moindre des choses est…
			Assert1("TransportViabiliseR",bCroit(trPorsche2-bGrandeLargeur,uTransport[uT],trOmega-1));//…de la faire vérifier par une assertion.
		}
		for (bRoute=kF,uT=1;uT<=kuTransportMaX;uT++)
			bRoute=bRoute || bCroit(trPorsche2-bGrandeLargeur,uTransport[uT],trMarche4);//parce que trCamion1 est judicieust placé avant trPorsche2. 
		for (bChemin=kF,uT=1;uT<=kuTransportMaX;uT++)
			bChemin=bChemin || bCroit(trScooter3,uTransport[uT],trBicyclette6);//ordonner judicieust le type énuméré pour que le code soit simple ici.
		for (bFleuve=kF,uT=1;uT<=kuTransportMaX;uT++)
			bFleuve=bFleuve || bCroit(trAviron7,uTransport[uT],trNage8);
		//teee("bRoute,bChemin,bFleuve",bRoute,bChemin,bFleuve);
		bViable=bRoute && bChemin && bFleuve;//ie au moins un moyen de transport permet au coureur nCoureur de parcourir chaque type de voie
	}while(!bViable);//les tirages étant pseudo-aléatoires, l'ordinateur trouve une solution viable avec quelques itérations,cf nIteration 
	if (nCoureurOuZero>0)
		TransportAfficheR(nCoureurOuZero,&uTransport[0],nIteration);
}//TransportViabiliseR

void GrapheCadufoua(){
	#define kuArcEnTout 20
	#define kuInfini 1e5
	#define kuSommetEnTout 8
	int uTransport[1+kuCoureurMaX][1+kuTransportMaX];
	graf *pgG;
	int nChrono,nChronoMax;
	int aK,uC;
	int sSource=4,sTrappe=1,sX=7,sY=6,sZ=5;
	int nPisteur,nPisteurRequis,uVitesseMax;
	//Classer ci-dessous les arcs par origine croissante puis par destination croissante simplifie l'encodage ainsi que la lecture du graphe.
		int nOrigine[]=    {0,   1,1,1,2,2,   2,2,3,3,3,   4,4,4,5,5,   6,6,7,8,8};
		int nDestination[]={0,   2,5,8,3,4,   7,8,6,7,8,   2,5,7,4,6,   5,1,8,1,2};
		int nLargeur[]=    {0,   2,3,4,5,3,   4,5,1,2,6,   4,5,6,1,2,   4,5,6,1,2};
		int nLongueur[]=   {0,   9,3,2,5,4,   1,1,5,1,1,   1,1,6,1,1,   4,5,6,1,1};
		int nVitMax[]=     {0,   2,3,7,4,3,   9,9,8,8,8,   4,4,6,7,4,   4,4,6,7,7};
		int nNature[]=     {0,   2,2,1,2,3,   3,3,3,3,3,   1,1,3,1,1,   1,2,3,1,1};//{naAlpha,naChemin1,naFleuve2,naRoute3,naOmega};
	//Appel0("GrapheCadufoua");
		//partie 1:créer le graphe, l'afficher et attribuer des moyens de transport viables à chaque coureur.
			GrapheCreer2(&pgG,kuSommetEnTout,kuArcEnTout,&nOrigine[0],&nDestination[0]);
			for (aK=1;aK<=pgG->nArcEnTout;aK++){
				nLongueur[aK]=yBorner(0,nLongueur[aK],9);//rend nLongueur[aK] si 0≤nLongueur[aK]≤9,ou la borne la plus proche de nLongueur[aK].
				nLargeur[aK]=yBorner(0,nLargeur[aK],9);
				nVitMax[aK]=yBorner(0,nVitMax[aK],9);
				nNature[aK]=yBorner(naAlpha+1,nNature[aK],naOmega-1);
			}
			GrapheVoirCadufouA(pgG,"Graphe Cadufoua",nLargeur,nLongueur,nVitMax,nNature);
			Assert5("GrapheCadufoua1",bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe),bGrapheSommet(pgG,sX),bGrapheSommet(pgG,sY),bGrapheSommet(pgG,sZ));
			Assert6("GrapheCadufoua2",sX!=sSource,sX!=sTrappe,sY!=sSource,sY!=sTrappe,sZ!=sSource,sZ!=sTrappe);//sX,sY,sZ distincts:cf nCourseEffectueR3
			for (uC=1;uC<=kuCoureurMaX;uC++)
				TransportViabiliseR(&uTransport[uC][0],!k1GrandeLargeuR,k1Afficher*uC);//qui affiche les moyens de transports du coureur uC.
		//partie 2:simuler la course de chaque coureur.
			for (uC=1;uC<=kuCoureurMaX;uC++){
				nChrono=nCourseEffectueR(uC,pgG,sSource,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature,!k1GrandeLargeuR);
				printf("Partie 2: Temps du coureur n°%d pour aller du sommet %d au sommet %d: %d.\n",uC,sSource,sTrappe,nChrono);
			}
		//partie 3:trois points de passage ordonnés:X, Y et Z, les mêmes pour chaque coureur.
			for (uC=1;uC<=kuCoureurMaX;uC++){
				nChrono=nCourseEffectueR3(uC,pgG,sSource,sX,sY,sZ,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature);
				printf("Partie 3: Temps du coureur n°%d passant par les sommets ordonnés %d,%d et %d: %d.\n",uC,sX,sY,sZ,nChrono);
			}
		//partie 4:trois points de passage non ordonnés:X, Y et Z, les mêmes pour chaque coureur;chaque coureur choisit l'ordre le plus avantageux.
			for (nChrono=kuInfini,uC=1;uC<=kuCoureurMaX;uC++){
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sX,sY,sZ,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sX,sZ,sY,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sY,sX,sZ,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sY,sZ,sX,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sZ,sX,sY,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				nChrono=yMin(nChrono,nCourseEffectueR3(uC,pgG,sSource,sZ,sY,sX,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature));
				printf("Partie 4: Temps du coureur n°%d passant par les sommets non ordonnés %d,%d et %d: %d.\n",uC,sX,sY,sZ,nChrono);
			}
		//partie 5:simuler la course de chaque coureur qui peut utiliser le cas échéant un moyen de transport "grande largeur"
			for (uC=1;uC<=kuCoureurMaX;uC++)
				TransportViabiliseR(&uTransport[uC][0],k1GrandeLargeuR,k1Afficher*uC);
			for (uC=1;uC<=kuCoureurMaX;uC++){
				nChrono=nCourseEffectueR(uC,pgG,sSource,sTrappe,&uTransport[uC][0],nLargeur,nLongueur,nVitMax,nNature,k1GrandeLargeuR);
				printf("Partie 5: Temps du coureur n°%d pour aller du sommet %d au sommet %d: %d.\n",uC,sSource,sTrappe,nChrono);
			}
		//partie 6: sSource:=sommet de départ idéal pour que les pisteurs visitent au plus vite (nChronoMax) tous les arcs du graphe
			//pgG->nCout[aK]:=durée du parcours de la voie aK sachant que le pisteur marge ou nage conformément à la nature de cette voie
				for (aK=1;aK<=pgG->nArcEnTout;aK++){
					uVitesseMax=iMin(nVitMax[aK],nVitesseMaX[(nNature[aK]==naFleuve2)? trNage8: trMarche4]);
					pgG->nCout[aK]=(nLongueur[aK]*kuFacteurMultiplicatiF)/uVitesseMax;
				}//N.B. kuFacteurMultiplicatiF permet de diviser sans passer par les réels: comparer 2000/3=666 et 2.0/3.0=0.667
			for (nChronoMax=kuInfini,sSource=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (nChrono=nParcoursExhaustifChronometreR(pgG,sX,!k1Afficher,&nPisteur),nChronoMax>nChrono){
					sSource=sX;
					nChronoMax=nChrono;
					nPisteurRequis=nPisteur;
				}
			Assert3("GrapheCadufoua Partie 6",sSource>0,nChronoMax>0,nPisteurRequis>0);
			printf("Partie 6: L'inspection optimale des voies part du sommet %d avec %s et prend %d unités de temps.\n",sSource,sPluriel(nPisteurRequis,"pisteur"),nChronoMax);
	//Appel1("GrapheCadufoua");
}//GrapheCadufoua
