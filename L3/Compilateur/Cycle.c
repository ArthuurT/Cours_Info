#include "Outil.h"
#include "Cycle.h"
#include "Deque.h"
#include "Graphe.h"
#include "Matrice.h"

#define kuArcEnTouT   128-1
#define kuCouleurBouT 5
#define knCouleurVersSommetFacultatiF knGrapheCouleurMax //tout sommet incident à une arête de cette couleur est facultatif
#define knCycleLiM 1000
#define kbLitteraL 1
//description des graphes pour CouplageEtudieR() et ses variantes (les couleurs attribuées aux arcs sont arbitraires)
	char kcDeuxCarreH[]="AB1AD1BC2BE2CF1DE2EF1";
	char kcDeuxCarrehTrianguleH[]="AB1AD1BC2BD2BE2CE1CF1DE2EF1";
	char kcDeuxTrianglesJuxtaposehS[]="AB1AC2BC3DE1DF2EF3";
	char kcDoubleT[]="AB1";
	char kcK24[]="AC1AD1AE1AF1BC2BD2BE2BF2";
	char kcK26[]="AC1AD1AE1AF1AG1AH1BC2BD2BE2BF2BG2BH2";
	char kcK4[]="AB1AC1AD1BC1BD1CD1";
	char kcK4plusX[]="AB1BC1CD1DA1AC2BD2";
	char kcK6[]="AB1AC1AD1AE1AF1BC1BD1BE1BF1CD1CE1CF1DE1DF1EF1";
	char kcK62plusX[]="AB1BC1CD1DE1EF1FA1AC2BD2";
	char kcK82plusX[]="AB1BC1CD1DE1EF1FG1GH1HA1AC2BD2";
	char kcK102plusX[]="AB1BC1CD1DE1EF1FG1GH1HI1IJ1JA1AC2BD2";
	char kcTroisCarreH[]="AB1AE2BC3BF3CD1CG1DH2EF1FG2GH3";
	char kcTroisCarrehsTrianguleH[]="AB1AE2BC3BE3BF3CD1CF1CG1DG2DH2EF1FG2GH3";
	char kcUnCarreH[]="AB1AD1BC1CD1";
	char kcUnLosangE[]="AC1AD2BC1BD2CD3";//2 triangles avec un côté commun
	char kcUnTrianglE[]="AB1AC2BC3";
int sCyclE[knCycleLiM][kuGrapheSommetLim];
int nCycleAfficheR=0;
int bCycleAmorceR;
int sParcourS[knCycleLiM][kuGrapheSommetLim];
int nParcoursEnTouT=0;

void CouplageEtudierPolynomialemenT();
void CouplageEtudierTouT(int nGrapheNumero);
void CouplageEtudyeR(int nGrapheNumero);
int nCouplageParfaiT(char kcArete[]);
void CouplageParfaitEnumereR(int nGrapheNumero);
void CycleAfficheR(graf gG,int nCycle,int sSousConnexe);
void CycleAfficherTouT(graf gG);
int bCycleAlternE(graf gG,int sListe[]);
int bCycleDecrirE(graf gG,int bCouleurDoitChanger,int sX,int sY,int bAfficher);
void CycleDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bAfficher);
void CycleDetecteR0(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bAfficher);
int bCycleEmpileR(int *pnCycleDistinct);
void CycleEngendreR(char *sContexte,char *sGrapheNom,char kcArc[],graf **ppgG);
void CycleGenereR(char kcArc[],int nExces,graf **ppgG,int *pbColoration,int *pnSousConnexe);
void CycleEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler);
void CycleInventorieR(graf gG,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler);
void CycleRazeR();
void CycleBiffeR(graf gG,int sSource,int sCible);
int bCycleContienT(int nCycle,int sEnquis);
void InventaireAnnonceR(graf gG,int nSousConnexe,int bSansSommetSousConnexe,int bDetailler);
void ParcoursCouvriR(char kcArc[],int nExces,graf gG);
void ParcoursEmpileR(int bAfficher);
void ParcoursVoiR();
void PisteDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bAfficher);
void PisteListeR(graf gG,int sDepuis,int szVoisin,int sListe[]);
void PisteVoirSouS(int bSous,int sListe[],int nPhase);
char cSommetLitteraL(int sX);
char *sSommetLitteraL(int sX);
void SommetListeR(int sSommet,int bVirguler);
int bSommetNonEncoreEmpileH(graf *pgG,int sOrigine,int sVierge,int *pbCycle);
int bSommetSousConnexablE(graf *pgG,int sCandidat);
int bSommetSousConnexE(graf *pgG,int sListe[],int nSousConnexe,int *psSoliton);
void VoieEnumereR(char* sMessage,char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler);
void VoieInventorieR(graf *pgG,int sSource,int sTrappe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler);

void CouplageEtudierPolynomialemenT(){
	//évalue le critère "un couplage parfait existe" sur tous les graphes du jeu de test ci-dessous et déroute si le critère est mal évalué.
	graf *pgG;
	int bAllocation,bSinguliere,nSousConnexe,iTest,iTest0,iTest1;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	iTest0=-3;
	iTest1=+4;
iTest0=1;iTest1=iTest0;
//iTest0=-2;iTest1=iTest0;
	for (iTest=iTest0;iTest<=iTest1;iTest++){
		Ligne();
		Titrer(sC7("Étude polynomiale du graphe ",sEnt(iTest)," tiré du jeu de test [",sEnt(iTest0),"..",sEnt(iTest1),"]"));
		bAllocation=kV;
		switch (iTest){//chaque appel à CycleGenereR alloue un graphe qui devra être désalloué à la fin du corps de la boucle for
			case -3: CycleGenereR(kcUnTrianglE,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case -2: CycleGenereR(kcK24,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case -1: CycleGenereR(kcK26,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case  0: CycleGenereR(kcDoubleT,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case +1: CycleGenereR(kcK4,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case +2: CycleGenereR(kcK6,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case +3: CycleGenereR(kcUnLosangE,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			case +4: CycleGenereR(kcTroisCarrehsTrianguleH,0,&pgG,&bCouleurChange,&nSousConnexe);break;
			default:bAllocation=kF;break;
		}
		if (bAllocation){
			GrapheSymetriser(pgG);
			bSinguliere=bMatryceSinguliere(pgG);
			//bSinguliere=bMatriceSingulariser(pgG);
			printf("Le graphe %d %s couplage parfait.\n",iTest,sUn("a",!bSinguliere));
			Assert1("CouplageEtudierPolynomialemenT",(iTest>=0)==!bSinguliere);
			GrapheCreer(0,&pgG);
		}
	}
}//CouplageEtudierPolynomialemenT

void CouplageEtudierTouT(int nGrapheNumero){
	int iTest,iTest0,iTest1;
	graf *pgG;
	char *sContexte;
	int bBiparti,nSignature;
	int emMode=maPremier0;
	//te("nGrapheNumero",nGrapheNumero);
	iTest0=iTest1=nGrapheNumero;
	if (nGrapheNumero==0)//exécuter tous les tests (hors test 0)
		{iTest0=-4;iTest1=8;}
emMode=maFormuler0;
//iTest0=2;iTest1=2;
	//tee("iTest0 et iTest1",iTest0,iTest1);
	for (iTest=iTest0;iTest<=iTest1;iTest++){
		if (emMode==maPremier0 && iTest>=0)
			emMode++;
		sContexte=sC7("——item n°",sEnt(iTest)," tiré du jeu de test [",sEnt(iTest0),"..",sEnt(iTest1),"]");
		switch (iTest){
		//test couplages imparfaits;donner 1 arc (orientation quelconque) par arête du graphe à spécifier;voir par exemple la spécification kcUnTrianglE.
			case -4:CycleEngendreR(sContexte,"kcK24",kcK24,&pgG);break;
			case -3:CycleEngendreR(sContexte,"kcK26",kcK26,&pgG);break;
			case -2:CycleEngendreR(sContexte,"kcDeuxTrianglesJuxtaposehS",kcDeuxTrianglesJuxtaposehS,&pgG);break;
			case -1:CycleEngendreR(sContexte,"kcUnTrianglE",kcUnTrianglE,&pgG);break;
		//test couplages parfaits;donner 1 arc (orientation quelconque) par arête du graphe à spécifier;voir par exemple la spécification kcK4.
			case  0:CycleEngendreR(sContexte,"kcDoubleT",kcDoubleT,&pgG);break;
			case  1:CycleEngendreR(sContexte,"kcUnCarreH",kcUnCarreH,&pgG);break;
			case  2:CycleEngendreR(sContexte,"kcDeuxCarreH",kcDeuxCarreH,&pgG);break;
			case  3:CycleEngendreR(sContexte,"kcTroisCarreH",kcTroisCarreH,&pgG);break;//exemple le plus parlant. 45 couvertures. Déterminant non polynomial non nul.
			case  4:CycleEngendreR(sContexte,"kcK4",kcK4,&pgG);break;//9 couvertures
			case  5:CycleEngendreR(sContexte,"kcK6",kcK6,&pgG);break;//265 couvertures 
			case  6:CycleEngendreR(sContexte,"kcDeuxCarrehTrianguleH",kcDeuxCarrehTrianguleH,&pgG);break;
			case  7:CycleEngendreR(sContexte,"kcUnLosangE",kcUnLosangE,&pgG);break;//exemple donné ds Balak p99 pr les cplG parfaits. Déterminant non polynomial nul.
			case  8:CycleEngendreR(sContexte,"kcTroisCarrehsTrianguleH",kcTroisCarrehsTrianguleH,&pgG);break;//exemple le plus parlant. 45 couvertures. Déterminant non polynomial non nul.
			default:break;
		}//switch (nCouplage)
		GrapheSymetriser(pgG);
		bBiparti=bGrapheBiparti(pgG);
		//printf("Ce graphe %s biparti.\n",sEst(bBiparti));
		if (bBiparti){//étudie le couplage à partir du déterminant du graphe non orienté décrit par kcArete[];ignore les couleurs des arêtes
			//bSinguliere=bMatriceSinguliere(pgG,emMode);
			//printf("Ce graphe %s couplage parfait car la matrice associée %s singulière.\n",sUn("contient",!bSinguliere),sEst(bSinguliere));
			if (emMode==maFormuler0){
				//te("nSignature0",nSignature);
				nSignature=nMatriceSignature(pgG,maFormuler1);
				//te("nSignature1",nSignature);
				//printf("Ce graphe %s couplage parfait car la matrice associée %s singulière.\n",sUn("contient",nSignature!=0),sEst(nSignature>0));
				if (nSignature==0)
					printf("Le graphe n°%d n'a aucun couplage parfait.\n",iTest);
				else printf("Le graphe n°%d a %s.\n",iTest,sPluriel(nRac(nSignature),"couplage$ parfait$"));
				Assert1("CouplageEtudierTouT",(iTest>=0)==(nSignature>0));
			};
		}
	GrapheCreer(0,&pgG);
	}
}//CouplageEtudierTouT

void CouplageEtudyeR(int nGrapheNumero){
	int iTest,iTest0,iTest1;
	graf *pgG;
	char *sContexte;
	int emMode=maPremier0;
	int bSinguliere;
	iTest0=iTest1=2;
	for (iTest=iTest0;iTest<=iTest1;iTest++){
		sContexte=sC7("——item n°",sEnt(iTest)," tiré du jeu de test [",sEnt(iTest0),"..",sEnt(iTest1),"]");
		if (emMode==maPremier0 && iTest>=0)
			emMode++;
		switch (iTest){
		//test couplages imparfaits;donner 1 arc (orientation quelconque) par arête du graphe à spécifier;voir par exemple la spécification kcUnTrianglE.
			case -4:CycleEngendreR(sContexte,"kcK24",kcK24,&pgG);break;
			case -3:CycleEngendreR(sContexte,"kcK26",kcK26,&pgG);break;
			case -2:CycleEngendreR(sContexte,"kcDeuxTrianglesJuxtaposehS",kcDeuxTrianglesJuxtaposehS,&pgG);break;
			case -1:CycleEngendreR(sContexte,"kcUnTrianglE",kcUnTrianglE,&pgG);break;
		//test couplages parfaits;donner 1 arc (orientation quelconque) par arête du graphe à spécifier;voir par exemple la spécification kcK4.
			case  0:CycleEngendreR(sContexte,"kcDoubleT",kcDoubleT,&pgG);break;
			case  1:CycleEngendreR(sContexte,"kcUnCarreH",kcUnCarreH,&pgG);break;
			case  2:CycleEngendreR(sContexte,"kcDeuxCarreH",kcDeuxCarreH,&pgG);break;
			case  3:CycleEngendreR(sContexte,"kcK4",kcK4,&pgG);break;//9 couvertures
			case  4:CycleEngendreR(sContexte,"kcK6",kcK6,&pgG);break;//265 couvertures 
			case  5:CycleEngendreR(sContexte,"kcDeuxCarrehTrianguleH",kcDeuxCarrehTrianguleH,&pgG);break;
			case  6:CycleEngendreR(sContexte,"kcUnLosangE",kcUnLosangE,&pgG);break;//exemple donné ds Balak p99 pr les cplG parfaits. Déterminant non polynomial nul.
			case  7:CycleEngendreR(sContexte,"kcTroisCarreH",kcTroisCarreH,&pgG);break;//exemple le plus parlant. 45 couvertures. Déterminant non polynomial non nul.
			case  8:CycleEngendreR(sContexte,"kcTroisCarrehsTrianguleH",kcTroisCarrehsTrianguleH,&pgG);break;//exemple le plus parlant. 45 couvertures. Déterminant non polynomial non nul.
			default:break;
		}//switch (nCouplage)
		bSinguliere=bMatriceSingulierh(pgG,emMode);
		printf("Ce graphe %s couplage parfait car la matrice associée %s singulière.\n",sUn("contient",!bSinguliere),sEst(bSinguliere));
		printf("Le graphe %d %s couplage parfait.\n",iTest,sUn("a",!bSinguliere));
		//Assert1("CouplageEtudyeR",(iTest>=0)==!bSinguliere);
	}
}//CouplageEtudyeR

int nCouplageParfaiT(char kcArete[]){
	//dénombre les couplages parfaits sur le graphe non orienté décrit par kcArete[];ignore les couleurs des arêtes
	graf *pgG;
	int aK,aL,nArete,nAretat,ipCouvre,nItem,bJointif,bParfait,bPrendre,nSousConnexe;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	int sCouvre[1000];
	int nParfait;
	long zCouvert,zCouverture;
	long zCouvertureMax;
	int sX,sX0,sX1,sY,sY0,sY1;
	CycleGenereR(kcArete,0,&pgG,&bCouleurChange,&nSousConnexe);
	GrapheVoir1(pgG,bCouleurChange,"Graphe généré avant symétrisation");
	GrapheSymetriser(pgG);
	nParfait=0;
		nAretat=pgG->nArcEnTout/2;
		Assert1("nCouplageParfaiT",bPair(pgG->nSommetEnTout));
		zCouvertureMax=zPuissance(2,pgG->nArcEnTout);
		te("zCouvertureMax",zCouvertureMax);
		for (zCouverture=1;zCouverture<=zCouvertureMax;zCouverture++){
			ipCouvre=0;
			//expliciter la couverture de numéro zCouverture
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					sCouvre[aK]=0;
				for (zCouvert=zCouverture-1,aK=1;aK<=pgG->nArcEnTout;aK++){
					bPrendre=(zCouvert%2>0);
					if (bPrendre)
						sCouvre[aK]=1;
					zCouvert=zCouvert/2;
				}
			//nArete=dénombrer les arêtes
				for (nArete=0,nItem=1;nItem<=pgG->nArcEnTout;nItem++)
					if (sCouvre[nItem]!=0)
						nArete++;
			bParfait=kF;
			if (nArete==pgG->nSommetEnTout/2){
				if (0){
					for (aK=pgG->nArcEnTout;aK>=1;aK--)
						printf("%2d",sCouvre[aK]);
					printf("\n");
					for (aK=pgG->nArcEnTout;aK>=1;aK--)
						if (sCouvre[aK]==1){
							GrapheDelimiter(pgG,aK,&sX,&sY);
							printf("(%d,%d)",sX,sY);
						}
					printf("\n");
				}
				//détecter les arêtes jointives
					for (bJointif=kF,aK=1;aK<=pgG->nArcEnTout &&!bJointif;aK++)
						if (sCouvre[aK]==1){
							//te("aK",aK);
							GrapheDelimiter(pgG,aK,&sX0,&sY0);
							for (aL=aK+1;aL<=pgG->nArcEnTout;aL++)
								if (sCouvre[aL]==1){
									//te("aL",aL);
									GrapheDelimiter(pgG,aL,&sX1,&sY1);
									bJointif=bJointif || (sX0>sY0) || (sX1>sY1) || (sX0==sX1) || (sX0==sY1) || (sY0==sX1) || (sY0==sY1);
								}
						}
				if (0 && !bJointif)
					printf("Couverture non jointive:%ld:\n",zCouverture);
				nArete=0;
				if (!bJointif)//dénombrer les arêtes
					for (nItem=1;nItem<=pgG->nArcEnTout;nItem++)
						if (sCouvre[nItem]!=0)
							nArete++;
				bParfait=(nArete==pgG->nSommetEnTout/2);			
			}
			if (bParfait){
				nParfait++;
				//afficher le couplage
					printf("Couplage parfait n°%d:",nParfait);
					for (aK=1;aK<=pgG->nArcEnTout;aK++)
						if (sCouvre[aK]==1){
							GrapheDelimiter(pgG,aK,&sX,&sY);
							printf(" (%c,%c)",'@'+sX,'@'+sY);
						}
					printf(".\n");
			}
		}
	GrapheCreer(0,&pgG);
	printf("Ce graphe a %s.\n",sPluriel(nParfait,"couplage$ parfait$"));
	return(nParfait);
}//nCouplageParfaiT

void CouplageParfaitEnumereR(int nGrapheNumero){
	int iTest,iTest0,iTest1;
	//te("nGrapheNumero",nGrapheNumero);
	iTest0=iTest1=1;
	if (nGrapheNumero==0)//exécuter tous les tests
		{iTest0=1;iTest1=4;}
	for (iTest=iTest0;iTest<=iTest1;iTest++){
		//printf("******************Étude du graphe %d tiré du jeu de test [%d..%d]:\n",iTest,iTest0,iTest1);
		Ligne();
		Titrer(sC7("Inventaire des couplages parfaits du graphe n°",sEnt(iTest)," tiré du jeu de test [",sEnt(iTest0),"..",sEnt(iTest1),"]"));
		switch (iTest){
		//test couplages imparfaits;donner 1 arc (orientation quelconque) par arête du graphe à spécifier;voir par exemple la spécification kcUnTrianglE.
			case 1:	nBof=nCouplageParfaiT(kcK4plusX);break;//3 couplages parfaits
			case 2:	nBof=nCouplageParfaiT(kcK62plusX);break;//3 couplages parfaits
			case 3:	nBof=nCouplageParfaiT(kcK82plusX);break;//3 couplages parfaits
			case 4:	nBof=nCouplageParfaiT(kcK102plusX);break;//3 couplages parfaits
			default:break;
		}//switch (nCouplage)
	}
}//CouplageParfaitEnumereR

void CycleAfficheR(graf gG,int nCycle,int sSousConnexe){
	//affiche sCyclE[nCycle],énuméré depuis le sommet de plus petit rang;si sSousConnexe>0, affiche le nom de ce sommet sous-connexe.
	int nCardinal;
	int bCycle;
	int uS;
	nCardinal=sCyclE[nCycle][0];
	bCycle=(nCycle==0);
	int nCycleNumero=(nCycle>0)?nCycle:nCycleAfficheR;
	if (sSousConnexe<0)
		nCycleNumero=-sSousConnexe;
	if (bCycle)
		printf("    Cycle n°%2d (lgr %2d): ",nCycleNumero,nCardinal);
	else printf("    Voie n°%2d (lgr %2d): ",nCycleNumero,nCardinal);
	//afficher le cycle stocké ds sCyclE[nCycle]
		printf("(");
			for (uS=1;uS<=nCardinal;uS++)
				SommetListeR(sCyclE[nCycle][uS],kV);
			SommetListeR(sCyclE[nCycle][1],kF);
		printf(")");
	if (sSousConnexe>0)
		printf("   (%c sous-connexe)",cSommetLitteraL(sSousConnexe));
	printf(".\n");
}//CycleAfficheR

void CycleAfficherTouT(graf gG){
	int nCycle;
	for (nCycle=1;nCycle<=nCycleAfficheR;nCycle++)
		CycleAfficheR(gG,nCycle,0);
	if (nCycleAfficheR==0)
		t("    Aucune voie n'a été trouvée");
}//CycleAfficherTouT

int bCycleAlternE(graf gG,int sListe[]){
	//vrai ssi les couleurs des arcs qui relient les sommets de sListe changent d'arc en arc (circulairt)
	int sDebug[1+8]={0,1,5,10,12,13,14,15,16};
	int uItem;
	int nPresent;
	int bAlterne;
	int uArc;
	int nCardinal=sListe[0];
	int nCouleur,nCouleur0;
	int sX,sY,uS;
	static int nCycleAlternE;
	nCycleAlternE++;
	//te("nCycleAlternE",nCycleAlternE);
	//GrapheVoir0(&gG,"ds bCycleAlternE",grCouleur);
	//PisteVoirSouS(sListe[0]>13,sListe,7);
	if (0){//debugger grâce au code qui suit qui repère une liste contenant les éléments de sDebug
		nPresent=0;
		for (uS=1;uS<=nCardinal;uS++)
			for (uItem=1;uItem<=8;uItem++){
				if (sListe[uS]==sDebug[uItem])
					nPresent++;
			}
		if (nCardinal==8 && nPresent==8)
			bAlterne=kF;//poser un point d'arrêt ici
	}
	bAlterne=kV;//d
	sX=sListe[nCardinal];
	sY=sListe[1];
	nCouleur=nGrapheCouleur(&gG,sX,sY);//a;rend la couleur réputée non nulle de l'arc, ou 0 si arc inexistant
	//printf("(%c,%c) a la couleur %d.\n",cSommetLitteraL(sX),cSommetLitteraL(sY),nCouleur);
	for (uArc=1;uArc<=nCardinal;uArc++){
		nCouleur0=nCouleur;
		sX=sY;
		sY=(uArc<nCardinal)?sListe[uArc+1]:sListe[1];
		nCouleur=nGrapheCouleur(&gG,sX,sY);
		//if (bAlterne) printf("(%c,%c) a la couleur %d.\n",cSommetLitteraL(sX),cSommetLitteraL(sY),nCouleur);
		bAlterne=bAlterne && (nCouleur!=nCouleur0);
	}
	//bAlterne=kV;
	return(bAlterne);
}//bCycleAlternE

void CycleAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	Assert1("CycleAMORCER",bCroit(1,knCouleurVersSommetFacultatiF,knGrapheCouleurMax));
	bCycleAmorceR=kV;
}//CycleAMORCER

void CycleBiffeR(graf gG,int sSource,int sCible){
	//biffe tout cycle qui ne contient pas à la fois sSource et sCible
	int nCardinal;
	int bContient;
	int nCycle;
	int nCycleLg;
	int uS;
	int nT;
	//Appel0("CycleBiffeR");
	nCardinal=nCycleAfficheR;
	//te("CycleBiffeR:nb cycles=",nCardinal);
	for (uS=1;uS<=nCardinal;uS++){
		bContient=bCycleContienT(uS,sSource) && bCycleContienT(uS,sCible);
		if (!bContient)
			sCyclE[uS][0]=0;
	}
	nCardinal=nCycleAfficheR;
	nCycle=0;
	for (uS=1;uS<=nCardinal;uS++){
		nCycleLg=sCyclE[uS][0];
		if (nCycleLg!=0){
			nCycle++;
			for (nT=0;nT<=nCycleLg;nT++)
				sCyclE[nCycle][nT]=sCyclE[uS][nT];
		}
	}
	sCyclE[0][0]=nCycle;
	nCycleAfficheR=nCycle;
	//Appel1("CycleBiffeR");
}//CycleBiffeR

int bCycleContienT(int nCycle,int sEnquis){
	//biffe tout cycle qui ne contient pas à la fois sSource et sCible
	int nCardinal;
	int bContient;
	int uS;
	nCardinal=sCyclE[nCycle][0];
	//tee("cycle et lgr",nCycle,nCardinal);
	for (bContient=kF,uS=1;uS<=nCardinal;uS++){
		if (sCyclE[nCycle][uS]==sEnquis)
			bContient=kV;
	}
	return(bContient);
}//bCycleContienT

int bCycleDecrirE(graf gG,int bCouleurDoitChanger,int sX,int sY,int bAfficher){
	//vrai ssi le Cycle qui traverse sX et sY est alterne de lgr>2; si vrai, le décrit en le stockant ds sCyclE[0] depuis le sommet de plus petit rang.
	int nCardinal;
	int bDecrire;
	int sListe[16+kuGrapheSommetLim];
	int nPlace;
	int sPremier;
	int nRang;
	int uS;
	static int nCycleDecrirE=0;
	bDecrire=kF;
//bAfficher=kV;
//Appel0("bCycleDecrirE");
	//te("bCycleDecrirE:bCouleurDoitChanger",bCouleurDoitChanger);
	for (uS=0;uS<kuGrapheSommetLim;uS++)
		sCyclE[0][uS]=0;
	//nCardinal:=lgr du Cycle,sListe[]:=pile de sommets
		PisteListeR(gG,sX,sY,sListe);
		nCardinal=sListe[0];
	//PisteVoirSouS(sListe[0]>13,sListe,6);
	bDecrire=(nCardinal>2) && (!bCouleurDoitChanger || bCycleAlternE(gG,sListe));
	//te("bDecrire",bDecrire);
	if (bDecrire){
		//sPremier:=sommet de plus petit rang
			sPremier=kuGrapheSommetLim;//a
			for (uS=1;uS<=nCardinal;uS++)
				if (sListe[uS]<sPremier){
					sPremier=sListe[uS];
					nRang=uS;
				}
		//sCyclE[0]:=sListe décalée, ie en commençant par sPremier
			for (nPlace=0;nPlace<kuGrapheSommetLim;nPlace++)
				sCyclE[0][nPlace]=0;
			nPlace=0;//a
			for (uS=nRang;uS<=nCardinal;uS++)
				sCyclE[0][++nPlace]=sListe[uS];
			for (uS=1;uS<=nRang;uS++)
				sCyclE[0][++nPlace]=sListe[uS];
			sCyclE[0][0]=nCardinal;
		if (bAfficher) nCycleDecrirE++;
		if (bAfficher) CycleAfficheR(gG,0,-nCycleDecrirE);/**********************/
	}
//Appel1("bCycleDecrirE");
	return(bDecrire);
}//bCycleDecrirE

void CycleDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bCycleAfficher){
	int bAfficher=bCycleAfficher;
	//if (bAfficher) te("CycleDetecteR AVANT",sDepuis);
	//bAfficher=0;
	CycleDetecteR0(gG,sDepuis,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,pnCycleEnTout,pnCycleCompatible,bAfficher);
	//if (bAfficher) te("CycleDetecteR APRES",sDepuis);
}//CycleDetecteR

void CycleDetecteR0(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bCycleAfficher){
	//détecter les ciruits en parcourant(récursivt) le graphe gG à partir de sDepuis; mémorise et affiche les cycles détectés
	int bCycle;
	int nCycleCompatible;
	int nCycleEnTout;
	int bEmpiler;
	int aK;
	int bSousConnexe;
	int sSousConnexe;
	int bVierge;
	int sVoisin;
	int sListe[16+gG.nSommetEnTout];
	//Appel0("CycleDetecteR0");
	if (0 && bCycleAfficher) {
		//d3(sDepuis,gG.nSommetEnTout,bColoration);
		PisteListeR(gG,sDepuis,0,sListe);
		PisteVoirSouS(bCycleAfficher && sListe[0]>13,sListe,1);
	}
	Assert1("CycleDetecteR0654",nCycleAfficheR<knCycleLiM);
	if (nCycleAfficheR<knCycleLiM){
		Assert1("CycleDetecteR1",bCroit(1,sDepuis,gG.nSommetEnTout));
		for (aK=gG.aHed[sDepuis]; aK<gG.aHed[sDepuis+1]; aK++) {
			sVoisin=gG.sSuk[aK];
			Assert1("CycleDetecteR2",bCroit(1,sVoisin,gG.nSommetEnTout));
			//PisteVoirSouS(bCycleAfficher && sListe[0]>13,sListe,3);
			bVierge=bSommetNonEncoreEmpileH(&gG,sDepuis,sVoisin,&bCycle);//vrai si sVoisin pas encore empilé depuis sDepuis
			if ( bVierge ) {
				//t("bCycle00");
				gG.sPer[sVoisin]=sDepuis;
				//t("bCycle11");
				CycleDetecteR0(gG,sVoisin,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,&nCycleEnTout,&nCycleCompatible,bCycleAfficher);
				//t("bCycle22");
				*pnCycleEnTout=nCycleEnTout;
				*pnCycleCompatible=nCycleCompatible;
				//t("bCycle33");
			};
			if (!bVierge && bCycle){
				//if (bCycleAfficher) d4(sDepuis,sVoisin,bVierge,bCycle);
				//PisteVoirSouS(bCycleAfficher && sListe[0]>13,sListe,5);
				//t("bCycle444");
				if (bCycleDecrirE(gG,bColoration,sDepuis,sVoisin,0 && bCycleAfficher)){
					//if (bCycleAfficher) t("@@@@@@@@@@@@@@@@@@@@@                                    bCycle555");
			//PisteVoirSouS(bCycleAfficher && sListe[0]>13,sListe,9);
					bEmpiler=bCycleEmpileR(&nCycleAfficheR);//si pas déjà fait, empile en interne le nouveau cycle au rang sCyclE[0] 
//b(bEmpiler);
					if (bEmpiler){
						//if (bCycleAfficher) t("bCycle666666666");
						if (bCycleAfficher) CycleAfficheR(gG,0,sSousConnexe);
						sSousConnexe=0;
						bSousConnexe=bSommetSousConnexE(&gG,sCyclE[0],nSousConnexe,&sSousConnexe);
				//bSousConnexe=kF;
						if (!bSousConnexe)
							(*pnCycleCompatible)++;
			//bCycleAfficher=kV;
						if (0 && bCycleAfficher && (!bSousConnexe || !bSansSommetSousConnexe && bDetailler))
							CycleAfficheR(gG,0,sSousConnexe);
						if (bSousConnexe)//dépiler ce cycle
							nCycleAfficheR--;
					}
				}
				//bExplorer=kF;
				//t("bCycle1");
			}
		}
	}
	*pnCycleEnTout=nCycleAfficheR;
	//Appel1("CycleDetecteR0");
}//CycleDetecteR0

int bCycleEmpileR(int *pnCycleDistinct){
	//empile ds sCyclE[nCycleDistinct+1] le cycle sCyclE[0] s'il est distinct de ceux stockés ds sCyclE[1..nCycleDistinct]
	int uCycle;
	int sCyclEz[kuGrapheSommetLim];
	int sCyclEs[kuGrapheSommetLim];
	int nCycleDistinct;
	int uCardinal;
	int bEmpiler;
	int nEmpiler;
	int bPareil;
	int uS;
	nCycleDistinct=*pnCycleDistinct;
	uCardinal=sCyclE[0][0];
//Appel0("bCycleEmpileR");
	Assert1("bCycleEmpileR",uCardinal>1);
	for (uS=1; uS<=uCardinal+1; uS++)
		sCyclEz[uS]=sCyclE[0][uS];//copie map
	for (nEmpiler=0,uCycle=1;(uCycle<=nCycleDistinct) && (nEmpiler==0); uCycle++)
		if (uCardinal==sCyclE[uCycle][0]){
			for (uS=1; uS<=uCardinal+1; uS++)//le sommet qui débute le Cycle (index 1) le termine aussi (index uCardinal+1)
				sCyclEs[uS]=sCyclE[uCycle][uS];//copie map
			for (bPareil=kV,uS=1; uS<=uCardinal; uS++)
				bPareil=bPareil && (sCyclEz[uS]==sCyclEs[uS]);
			if (bPareil)//cycle déjà mémorisé,parcouru ds le mm sens
				nEmpiler=uCycle;
			for (bPareil=kV,uS=1; uS<=uCardinal; uS++)
				bPareil=bPareil && (sCyclEz[uS]==sCyclEs[uCardinal-uS+2]);
			if (bPareil)//cycle déjà mémorisé,mais parcouru en sens inverse
				nEmpiler=uCycle;
		}
	bEmpiler=(nEmpiler==0);
	if (bEmpiler) {//empiler le nouveau cycle
		uCycle=1+nCycleDistinct;
		Assert1("bCycleEmpileR",uCycle<knCycleLiM);
		//te("uCycle empilé",uCycle);
		for (uS=0; uS<kuGrapheSommetLim; uS++)
			sCyclE[uCycle][uS]=sCyclE[0][uS];
		*pnCycleDistinct=uCycle;
		//bEmpiler=uCycle;
	};
//Appel1("bCycleEmpileR");
	return(bEmpiler);
}//bCycleEmpileR

void CycleEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler){
	//génère le graphe défini par (kcArc,nExces) et inventorie soit tous ses cycles soit seult ceux qui ne rendent aucun sommet sous-connexe.
	graf *pgG;
	int nSousConnexe;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
	GrapheVoir1(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec","sans"),"couleurs"));
	t("GrapheSymetriser0");
	GrapheSymetriser(pgG);
	t("GrapheSymetriser1");
	//GrapheVoir0(pgG,"Graphe symétrique colorié après symétrisation");
	InventaireAnnonceR(*pgG,nSousConnexe,bSansSommetSousConnexe,bDetailler);
	CycleInventorieR(*pgG,bSansSommetSousConnexe,bCouleurChange,nSousConnexe,k1Afficher,bDetailler);
}//CycleEnumereR

void CycleEngendreR(char *sContexte,char *sGrapheNom,char kcArc[],graf **ppgG){
	//engendre tous les cycles du graphe défini par les triplets (sommet origine,sommet destination,couleur) de kcArc et rend ce graphe.
	int bCouleurChange,nExces=0,nSousConnexe=0;
	Ligne();
	Titrer(sC3b("Étude du graphe",sG(sGrapheNom),sContexte));
	CycleGenereR(kcArc,nExces,ppgG,&bCouleurChange,&nSousConnexe);
}//CycleEngendreR

void CycleGenereR(char kcArc[],int nExces,graf **ppgG,int *pbColoration,int *pnSousConnexe){
	//génère des cycles en créant un graphe défini par les triplets (sommet origine,sommet destination,couleur) de la chaîne kcArc.
	int uArc;
	int nArc0[1+kuArcEnTouT];//NB sommet origine de l'arc
	int nArc1[1+kuArcEnTouT];//NB sommet destination de l'arc
	int uArcEnTout;
	int nC;
	int uChaineLg;
	int nCouleur;
	int sDernier;
	int sDestination;
	int nDistinct[1+kuByteMax];
	int sOrigine;
	int sPremier;
	int uS;
	char cSommet;
	int nSommet;
	uChaineLg=nChaineLg(kcArc);
	Assert2("CycleGenereR1", uChaineLg %3==0,uChaineLg<kuByteMax);
	//nSommet:=nb de sommets distincts cités ds kcArc
		for (nC=0;nC<=kuByteMax;nC++)
			nDistinct[nC]=0;
		for (nC=0;nC<uChaineLg;nC++)
			if (nC%3!=2){//nC n'indexe pas une couleur mais un sommet
				cSommet=kcArc[nC];
				nSommet=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
				nDistinct[nSommet]++;
			}
		//VecteurVoir1("nDistinct",nDistinct,1,26);
		//les sommets de kcArc[] sont réputés commencer à la lettre 'A'et être consécutifs;soit nDernier le sommet de rang maximal
			sPremier=kuIntegerMax;
			sDernier=0;
			for (uS=1;uS<=kuByteMax;uS++)
				if (nDistinct[uS]>0){
					sPremier=iMin(sPremier,uS);
					sDernier=iMax(sDernier,uS);
				}
			Assert1("CycleGenereR2", sPremier==1);
			for (uS=sPremier;uS<=sDernier;uS++)
				Assert1("CycleGenereR3", nDistinct[uS]>0);//ts les noms de sommets cités appartiennent à un sous-intervalle de [A-Za-z]
		nSommet=sDernier;
		//te("nSommet",nSommet);
	*pnSousConnexe=nSommet-nExces;//seuls les *pnSousConnexe premiers sommets pourront être déclarés sous-connexes;les autres sommets seront ignorés.
	uArcEnTout=(uChaineLg)/3;
	Assert2("CycleGenereR4", *pnSousConnexe>=0, uArcEnTout>0);
	//nArc0[]:=sommets origine listés ds cArc[]
		nArc0[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			nArc0[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//nArc1[]:=sommets destination listés ds cArc[]
		nArc1[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-2];
			nArc1[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
//te("nSommet",nSommet);
	GrapheCreer2(ppgG,nSommet,uArcEnTout,&nArc0[0],&nArc1[0]);
//te("uArcEnTout",uArcEnTout);
	//colorier chaque arc
		*pbColoration=kV;
		nArc1[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			sOrigine=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			cSommet=kcArc[3*uArc-2];
			sDestination=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			nCouleur=kcArc[3*uArc-1]-'0';
			Assert1("CycleGenereR5", bCroit(0,nCouleur,knGrapheCouleurMax));
			if (nCouleur==0)
				*pbColoration=kF;
//t(sC5("arc (",sEnt(sOrigine),",",sEnt(sDestination),")"));
			GrapheColorer(*ppgG,sOrigine,sDestination,nCouleur);
		}
	//GrapheVoir0(*ppgG,"ds CycleGenereR",grCouleur);
}//CycleGenereR

void CycleINITIALISER(){//O(?)
	//relance le présent module
	Assert1("CycleINITIALISER",bCycleAmorceR);
}//CycleINITIALISER

void CycleInventorieR(graf gG,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler){
	//inventorie (et affiche) les cycles de gG,en totalité si bSansSommetSousConnexe est faux,ou seult ceux qui ne créent pas de sommet sous-connexe sinon.
	int sArrivee;
	int nCycleEnTout=0;
	int nCycleCompatible=0;
	int sDepart;
	//Appel0("CycleInventorieR");
		CycleRazeR();//raze la pile qui mémorise les cycles jugés pertinents
//bSansSommetSousConnexe=kV;/****************************/
		//explorer en largeur d'abord en partant de chaque sommet sDepart;gG.sPer[] mémorise le chemin qui relie sDepart au sommet courant
			nCycleAfficheR=0;
			sArrivee=gG.nSommetEnTout;
			sArrivee=1;
//bAfficher=kV;
			for (sDepart=1;sDepart<=sArrivee;sDepart++){
				VecteurRazer(gG.sPer,1,gG.nSommetEnTout);
				gG.sPer[sDepart]=sDepart;//vital pour identifier le sommet origine de ts les chemins détectés par nCycleDetecteR()
				//printf("Détection de cycles depuis le sommet:%d/%d (si le graphe est connexe,1 sommet suffit:la boucle est superflue).\n",sDepart,gG.nSommetEnTout);
				CycleDetecteR(gG,sDepart,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,&nCycleEnTout,&nCycleCompatible,bAfficher);
			}//si le graphe est connexe,sDepart=1 suffit si bien que la boucle est superflue.
		if (kF && bAfficher)
			t(sC5b("Bilan:",sPluriel(nCycleCompatible,"cycle"),"sans sous-connexité","sur",sPluriel(nCycleEnTout,"cycle$ inventorié$")));
	//Appel1("CycleInventorieR");
}//CycleInventorieR

void CycleRazeR(){
	int nCycle;
	int uS;
	for (nCycle=0; nCycle<knCycleLiM; nCycle++)
		for (uS=1; uS<kuGrapheSommetLim; uS++)
			sCyclE[nCycle][uS]=0;
}//CycleRazeR

void CycleTESTER(int iTest){
	//teste le présent module
	int k1Detailler=kV;
	char kcAgape[]= "AE1AR2BO2BP1CK1CL2DH1DI2EF2FG1Fd1GH2GX1HV1IJ1If1JK2Jb1KZ1LM1MN2MT2NO1NW2OU2PQ2PS2QR1Qa2RY2ST1Sc2Te2UV5WX5YZ5ab5cd5ef5Ag2Bh2Ci1Dj1";
	char kcAgape1[]="AE1AR2BO2BP1CK1CL2DH1DI2EF2FG1Fd1GH2GX1HV1IJ1If1JK2JZ1Kb1LM1MN2MT2NO1NW2OU2PQ2PS2QR1Qa2RY2ST1Sc2Te2UV5WX5YZ5ab5cd5ef5Ag2Bh2Ci1Dj1";
	char kcAgasse[]="AE1AR2BO2BP1CK1CL2DH1DI2EF2FG1FX1GH2GV1HU1IJ1IZ1JK2JV1KU1LM1MN2MT2NO1NV2OU2PQ2PS2QR1QV2RU2ST1SW2TY2WX5YZ5Aa2Bb2Cc1Dd1";
	char kcAgave[]="AC1AL2AM1BK2BL1CF2DI1DK2EH1EJ2FG1GH2IL2IN2JK1MN5AO2BP2CQ1DR2";
	char kcAquabon[]="AB2AH1BC1BK2CD2DE1DM2EF2FG1FO2GH2HI2IJ2IP1JK1JQ2KL2LM1LS2MN2NO1NU2OP2PU2QR5RU1ST5TU1AV2CW2EX2GY2";
	char kcAquarelle[]="AB2AH1BC1BK2CD2DE1DM2EF2FG1FO2GH2HI2IJ2IP1JK1JQ2KL2LM1LR2MN2NO1NS2OP2PT2QS2QT1RS1RT2AU2CV2EW2GX2";
	char kcArachnide[]="AB2BC1CD3DE2EA1AF3BG2CH2DI1EJ1FH1HJ2JG3GI1IF2AK1BL2CM3DN1EO2";
	char kcAraya[]="AB0AD0AE0AP0BC0BG0BH0CD0CJ0CK0DM0DN0EF0EQ0FG0FR0GS0HI0HT0IJ0IV0JX0KL0KY0LM0LZ0Ma0NO0Nb0OP0Oc0Pe0Qe0Qf0Rf0Rg0ST0Sg0TU0UV0Uh0VW0WX0Wi0XY0Yj0Zj0Zk0ab0ak0bm0cd0cm0de0dn0fn0gh0go0hi0ij0ip0kl0kp0lm0ln0no0op0";
    char kcAraya1[]="AB1AD1AE2BC3BG2CJ2CK1DM1DN2EF2EQ1FG2FR1GS1HI2HT1IJ1IV1JX3KY2LM2LZ1Ma1NO1Nb3OP2Oc3Pe1Qe2Qf2Rf2Rg2ST2Sg2TU2UV1Uh3VW2WX1Yj1Zj2ab2ak3bm1cd1cm2de2dn2fn1go1hi2ip1kl1lm2ln2op2Aq5Br5Cs5Dt5";
	char kcArgamon[]="AE1AP2BG2BH1CM2CN1DJ2DK1EF2FG1FQ1GV1GT2HI2IJ1IR1JX2JZ1KL2LM1LR1MU2MS1NO2OP1OQ1PW1PY2QR2ST0UV0WX5YZ5Aa3Bb3Cc3Dd3";
	char kcBalance[]="AE1AF2BF1BG2CE2CG1CH2DG2DI1DJ2EK1EL2GM1HI9JK9LM9AN1BO2CP1DQ1";
	char kcBanzai1[]="AE2AI1BH1BI1BK2CE1CF2DG1DH2EJ1FG1FH1GI2JK9AL1BM2CN1DO1";
	char kcBanzai2[]="AE2AI1BJ2BI1CE1CF2DG1DH2EB1FG1FH1GI2HK1JK9AL1BM2CN1DO1";
	char kcBarbare1[]="AB1AE2AI2BE2BK1CE1CF2DH1DI2EL1FG1GH2GN2HM2IJ1IK1JK2JO1LM9NO9AP1BR2CQ1DS2";
	char kcBarbare2[]="AE2AI1AP2BE2BK1BQ1CE1CF2DH1DI2EL1FG1GH2GN2HM2IJ1IS2JK2JO1KR1LM9NO9PQ9RS9AT1BU2CV1DW2";

	char kcBico[]="AB2AE1BC1BF2CE2CF2DE2DF1AG2BH1CI1DJ2";
	char kcBistrine[]="AE1AF2BE2BF1BI2CG1CH2DG2DH1DL2EG2FH1FJ2HK2IJ9KL9AM2BN1CO2DP1";
	char kcBitrine[]="AC1AF1BG2BJ2CD2CM1DE3DN3EK2EM1FK3FO1FP2GM2GH1HI3HS3IL1IM2JL3JR2JQ1KT1KV2LU1LW2NO9PQ9RS9TU9VW9AX3BY3";

	char kcBizut[]="AE2AF1AG2BE2BF1BH1CE1CF2CI2DE1DF2DJ1GH9IJ9AK1BL2CM1DN2";
	char kcBrex[]="AC2AF2AH1BD1BF1BJ2CE1CI2DG2DI1EF1EH2FG2GJ1HI1IJ2AK1BL2CM1DN2";//avec max max
	char kcBrexit[]="AC1AF2AH3BD4BF3BJ2CE3CI4DG2DI1EF3EH4FG2GJ1HI1IJ4AK3BL2CM1DN4";//avec max max
	char kcBrexitt[]="AC1AF2AH3BD1BF3BJ2CE3CI3DG2DI3EF3EH1FG2GJ1HI2IJ2AK3BL2CM1DN1";
	char kcCapside[]="AE1AI2Bc1BT2CF1CV2DQ1DU2EF2EG1GH1GJ2HK2HW1IJ1IX1JN1KN1LM1LO2LP2LY2MN2NZ1OR1PQ2PS1Qa2RS2Rb2SU2TU1VW9XY9Za9bc9Ad1Be1Cf2Dg2";
	
	char kcClaustra1[]="AB1AD2AE2BC2BE1CD1CE2DE1AF1BG2CH1DI2";
	char kcClaustra2[]="AB1AE2AG2BF2BG1CD1CF2CH2DE2DH1EF1EG1EH2FG2FH1AI1BJ2CK1DL2";

	char kcComplet4[]="AB0AC0AD0BC0BD0CD0";
	char kcComplet5[]="AB1AC2AD1AE2BC2BD2BE1CD2CE1DE3";
	char kcComplet60[]="AB0AC0AD0AE0AF0BC0BD0BE0BF0CD0CE0CF0DE0DF0EF0";
	char kcComplet61[]="AB1AC2AD1AE2AF3BC2BD2BE1BF3CD2CE1CF3DE1DF2EF3";
	char kcCroisade[]="AB1AD2AE1BD2BH2CD1CF2CG1EF9GH9AI2BJ1CK2DL1";
	char kcCycle[]="AB1AD2BC2CD1";
	char kcDeltoide[]="AB2AW2AX1BC1BJ2CD2CR2DE1DL2EF2EM2FG5GZ1HI1HP2HZ2IJ2IQ2JK1KL2KS2LM1MY2NO5NY1OP2PQ1QR2RS1ST2TW1TX2UV5UY2VZ2";
	char kcDomino[]="AB1AD1BC2CD1DE2EF1FA2FG1EH1BI1CJ1";
	char kcOeil[]="AG1AE2BE2BH1CE1CF2DF1DG2FH2AI2BJ2CK2DL1";
	char kcFaible[]="AB1AC1AG2AI1BC2BH1CD1DE2DI1EF1FG2GH1HI2";

	char kcGelule1[]="AH1AO2BG2BL1CI1CJ2DK1DN2EF2EG1EI1FJ1FL1GP1HI2JM1KL2MN9OP9AQ2BR1CS1DT2";
	char kcGelule2[]="AD1AM2BC2BK1CF1CN1DE2EF1EI1FG2GH1GK1HI2HO1IQ1JL1JP2JR2KL2MN9OP9QT2Qc1RS1Ra2SV2Sd2TU1UV2UY2VW1WX2Wa2XY1Xe2Zb2Zf1ab1cd9ef9Ag2Bh1Yi2Zj1";

	char kcGlobe[]="AB2AU2AV1BC1BJ2CD2DE1DQ2EF2EP2FG5GX1HI1HX2IJ2JK1KL2KS2LM1MW2NO5NW1OP2PQ1QR2RS1ST2TU1TV2UV2UY2VZ2Wa1Xb1";
	char kcGrain24[]="AB3AE1AU2BC2BH1CD1CI1DF1DV2EF2EG1FJ1GH2HI1IJ2JX1KL2KO1LM1MN2MS2NP1NU2OP2PT1QR2QW1RS1ST2TX1UV1WX2AY1GZ1Na1Tb2";
	char kcHerschel[]="AE1AI2BG1BK2CE2CH1DH2DK1EF1FG2FH1HJ2IJ1JK2AL1BM2CN1DO2";
	char kcMessa[]="AC2AN1BC1BN2CD2DE1DH2EF2EL2FG1GH2HI1IJ2IM2JK1KL2LM1MN2AO2BP2GQ2JR2";
	char kcMessI[]="AC2AP1BC1BP2CD2DE1DH2EF2EN2FG1FL2GH2GK2HI1IJ2IO2JK1KL2LM1MN2NO1OP2AQ2BR2JS2MT2";
	char kcNabla[]="AB2AW2AX1BC1BJ2CD2CR2DE1DL2EF2EM2FG5GZ1HI1HP2HZ2IJ2IQ2JK1KL2KS2LM1MY2NO5NY1OP2PQ1QR2RS1ST2TW1TX2UV5UY2VZ2Wa2Xb2Yc1Zd1";
	char kcNabla1[]="AB2AU2AV1BC1BJ2CD2CR2DE1DL2EF2EM2FG5GX1HI1HP2HX2IJ2IQ2JK1KL2KS2LM1MW2NO5NW1OP2PQ1QR2RS1ST2TU1TV2UV2UY2VZ2Wa2Wb1Xb1";
	char kcOptionnel[]="AB2BC1BG2GH5HF2CD2DE1EF2FA1";
	char kcPanama[]="AB1AD1AC2AE2BC2BE1CD1DE2AF1BG2CH1DI2";
	char kcPetersen0[]="AD1AF2BC1BG2CE2EI1DE2FH1FI2GI2GJ1HJ2AK1BL1CM1DN1";
	char kcPetersen1[]="AB1AG1AH2BE1BI2CD1CI1CG2DE2DH1EF1FG1FJ2HJ1IJ1AK1BL1CM1DN1";
	char kcPetersen5[]="AB2BC1CD3DE2EA1AF3BG2CH2DI1EJ1FH1HJ2JG3GI1IF2";
	char kcPeterpi[]="AB3AE2AG1BC3BH1CD2CI1DJ1EF1FH2FI2GI2GJ2KJ2LI1MG1NH2";
	//char kcPiedouche0[]="AB2AE1BF1CD1CE2CG1DF1DG2EF2EG1FG2AH1BI1CJ2DK2";
	//char kcPiedouche1[]="AE2AH1BF1BH2CD1CE1CG2DC1DF2DG2EF2EG1FG1AI2BJ1CK2DL1";
	char kcPiedouche2[]="AE2AG1BF1BG2CE1CH2CI2DF2DH2DJ1EF2EH1FH1IJ9AK2BL1CM1DN1";//9:couleur indifferente
	char kcPlexe[]="AE2AF1BD2BE1BG1CH2CI1DE1DI2FG2FH1GH1HI2AJ1BK2CL2DM1";

	char kcKarre[]="AE1AF2BG2BH1CI1CJ2DK2DL1EL3FG3FT2GO2HI3JK3JQ1KW2MN1MP2MT1MW2NO1NU2OQ1OR2PQ2PV1QS2RS9TU3VW3AX2BY2CZ2Da2";

	char kcKrill[]="AB3AE2AR3BK3BM1CF2CU3CD3DO1DQ3EF3EG1FH1GI2GJ1GS2HI2HP1HT2IL1IN1JK1JL2KM2LM1NO1NP2OQ2PQ1RS9TU9AV2BW1CX2DY1";

	char kcQarre[]="AE1AB3BF2CD3CG1DH2EH3EI1FG3FO2GQ1HL2IJ3IM1JN2KL3KP1LM2MN1MP2NO1OQ1OR2PQ2QS2RS9AT1BU2CV1DW2";

	char kcRotonde[]="AC2AV1BC1BV2CA2CD2DE1DQ2EF2EP2FG1FL2GH2GR2HI1HU2IJ2IT2JK1KL2KN2LM1MN2MS2NO1OP2PQ1QR2RS1ST2TU1UV2AW2BX2JY2OZ2";
	char kcRotangle[]="AC2AV1BC1BV2CA2CD2DE1DP2EF2EQ2FG1FL2GH2GR2HI1HU2IJ2IT2JK1KL2KN2LM1MN2MS2NO1OP2PQ1QR2RS1ST2TU1UV2AW2BX2JY2OZ2";
	char kcRotocle[]="AC2AV1BC1BV2CA2CD2DE1DP2EF2EQ2FG1FL2GH2GR2HI1HT2IJ2IU2JK1KL2KN2LM1MN2MS2NO1OP2PQ1QR2RS1ST2TU1UV2AW2BX2JY2OZ2";
	char kcTonneau[]="AB1AN2BC2CD1DE2EF1ES2FG2GH1HI2IJ1IX2JK2JV2KL1LM2MN1NO2OP1OX2PQ2PW2QR2QT1RS1RV2SU2TU2TW2UV1WX1AY2DZ2Ha2Kb2";
	char kcTriangle[]="AC2AM1BC1BM2CD2DE1DO1DS2ET5FG1FJ2FT2GR1GQ2GI2IH5HJ1JU2KU5KL1LM2LN2LP1NO5PQ5RS5AV2BW2JX1FY1";
	char kcTetras[]="AC2AJ1BC1BJ2CD2DE1DF2DI1EF2EH2FG1GH2GI2HI1IJ2AK2BL2HM1EN1";
	char kcTuba[]="AB1AM2BC2BN2CD1CK2DE2DL2EF1FG2GH5HI2IJ1JK2KL1LM2MN1NO2AP2ER2JQ2";
	char kcTutteTierce[]="AD2AE1BD1BL2CM2CP1DG2EF2EH1FG1FI2GK2HI2HM1IJ1JK2JN2KL1LO2MN2NO1OQ2PQ5AR2BS2CT3";
	char kcTutteTiers[]="AD2AE1BD1BL2CM2CO2DG2EF2EH1FG1FI2GK2HI2HM1IJ1JK2JN2KL1LO2MN3NO1AP2BQ2CR1";
	char kcToutteTiers[]="AB2AD2BC1BF2CJ2DE1DG1EF1EH2FI1GH1GN2HK1IJ1IK2JM1KL3LM1LN1MO2NO1AP1CQ1FR1OS1";//2 voies seult:AF et AO
	char kcTouttePlein[]="AB1AD2BC1BF2CJ2DE1DG1EF1EH2FI1GH1GN2HK1IJ1IK2JM1KL3LM1LN1MO2NO1PQ1PS2QR1QU2RY2ST1SV1TU1TW2UX1VW1Vc2WZ1XY1XZ2Yb1Za1ab1ac3bd2cd1ef1eh2fg1fj2gn2hi1hk1ij1il2jm1kl1kr2lo1mn1mo2nq1op1pq1pr3qs2rs1Ce1Pg1dt1Ot1st3Au1Fv1Pw1Ux1";
	char kcThutteTiers[]="AB2AD2BC1BF2CJ2DE1DG1EF1EH2FI1GH1GN2HK1IJ1IK2JM1KL3LM1LN1MO2NO1AP1CQ1FR1OS1";//2 voies seult:AF et AO
	char kcThuttePlein[]="AB2AD2BC1BF2CJ2DE1DG1EF1EH2FI1GH1GN2HK1IJ1IK2JM1KL3LM1LN1MO2NO1PQ2PS2QR1QU2RY2ST1SV1TU1TW2UX1VW1Vc2WZ1XY1XZ2Yb1Za3ab1ac1bd2cd1ef2eh2fg1fj2gn2hi1hk1ij1il2jm1kl1kr2lo1mn1mo2nq1op3pq1pr1qs2rs1Ae1Pe1dt1Ot1st3Au1Fv1Pw1Ux1";//2 voies seult:AF et AO
	//char kcTricycle[]="AB2AC2AD1BC2BF1CH1DE2DI2EF2EK1FG2GH2GL1HI2IJ1JK2JL2KL2MA2NB2OG2PJ2";
	char kcTricycle[]="AB2AC2AD1BC2BF1CH1DI2EF2EK1GH2GL1IJ1JK2JL2KL2MA2NC2OL2PJ2";
	char kcTrips[]="AE1AG2BI1BL2CF1CG2CM2DK1DO2EF2FR1GH1HI2IJ1JK2JQ1LM1MN2NO1NP2OS2PQ9RS9AT2BU1CV1DW2";
	char kcVingtSix[]="AE1AL2BF1BJ1BU2CI2CM1CT1DG2DN1EF2FB1FG1GH2GO1HI1HP1HQ2IR2IS1JK2JV2JW1KL1KX1KY2LM1LZ2MN2OP9QR9ST9UV9WX9YZ9Aa2Bb2Cc2Dd2";

	char kcPeter[]="AB2AE1BG1BK2CD2CH1CL1DI2DM1EJ2EN2FH2FI1GI2GJ1GO2HJ1JP2KL9MN9OP9AQ2BR1CS2DT1";
/*
n°1: {7}, voie AC, reste 6 arêtes:    (A,B)       (C,D)	
n°4: {16}, voie BD, reste 12 arêtes:        (B,G)       (D,I)       

n°2: {9}, voie AD, reste 10 arêtes:   (A,B)				(D,I)               
n°3: {2,14}, voie BC, reste 8 arêtes:       (B,G) (C,D) 			  
*/

	int k1SansSommetSousConnexe=kV;
	iTest=94;//32 26 34 35 37NON
	Appel0(sC2("CycleTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case  1:	CycleEnumereR(kcComplet4,0,k1SansSommetSousConnexe,!k1Detailler);break;//3 cycles sur 7 inventoriés
			case  2:	CycleEnumereR(kcComplet5,0,k1SansSommetSousConnexe,k1Detailler);break;//1 cycle sur 9 inventoriés
			case  3:	CycleEnumereR(kcComplet60,0,k1SansSommetSousConnexe,k1Detailler);break;//80 cycles sur 197 inventoriés
			case  4:	CycleEnumereR(kcComplet61,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 16 inventoriés
			case  5:	CycleEnumereR(kcPetersen5,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 19 inventoriés
			case  6:	CycleEnumereR(kcPetersen5,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 19 inventoriés
			case  7:	CycleEnumereR(kcArachnide,5,k1SansSommetSousConnexe,k1Detailler);break;//7 cycles sur 19 inventoriés
			case  8:	CycleEnumereR(kcFaible,0,k1SansSommetSousConnexe,k1Detailler);break;
			case 12:	VoieEnumereR("kcPetersen0",kcPetersen0,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 13:	VoieEnumereR("kcPetersen1",kcPetersen1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 14:	VoieEnumereR("kcPeterpi",kcPeterpi,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 15:	VoieEnumereR("kcDeltoide",kcDeltoide,4,k1SansSommetSousConnexe,!k1Detailler);break;
			case 16:	VoieEnumereR("kcComplet4",kcComplet4,4,k1SansSommetSousConnexe,!k1Detailler);break;
			case 17:	VoieEnumereR("kcBalance",kcBalance,4,k1SansSommetSousConnexe,!k1Detailler);break;
			case 18:	VoieEnumereR("kcOeil",kcOeil,4,k1SansSommetSousConnexe,!k1Detailler);break;
			case 19:	VoieEnumereR("kcPlexe",kcPlexe,4,k1SansSommetSousConnexe,!k1Detailler);break;

			case 20:	VoieEnumereR("kcDomino",kcDomino,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 21:	VoieEnumereR("kcOptionnel",kcOptionnel,4,k1SansSommetSousConnexe,k1Detailler);break;//vérifie qu'un sommet peut être déclaré non sous-connexable
			case 22:	VoieEnumereR("kcNabla",kcNabla,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 23:	VoieEnumereR("kcNabla1",kcNabla1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 24:	VoieEnumereR("kcGlobe",kcGlobe,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 25:	VoieEnumereR("kcTriangle",kcTriangle,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 26:	VoieEnumereR("kcTetras",kcTetras,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 27:	VoieEnumereR("kcTuba",kcTuba,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 28:	VoieEnumereR("kcMessa",kcMessa,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 29:	VoieEnumereR("kcMessI",kcMessI,4,k1SansSommetSousConnexe,k1Detailler);break;
			
			case 30:	VoieEnumereR("kcRotonde",kcRotonde,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 31:	VoieEnumereR("kcRotangle",kcRotangle,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 32:	VoieEnumereR("kcRotocle",kcRotocle,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 33:	VoieEnumereR("kcAquabon",kcAquabon,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 34:	VoieEnumereR("kcAquarelle",kcAquarelle,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 35:	VoieEnumereR("kcTonneau",kcTonneau,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 36:	CycleEnumereR(kcAraya,0,k1SansSommetSousConnexe,k1Detailler);break;
			case 37:	VoieEnumereR("kcAraya1",kcAraya1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 38:	VoieEnumereR("kcTutteTiers",kcTutteTiers,3,k1SansSommetSousConnexe,k1Detailler);break;
			case 39:	VoieEnumereR("kcTutteTierce",kcTutteTierce,3,k1SansSommetSousConnexe,k1Detailler);break;
			
			case 40:	VoieEnumereR("kcArgamon",kcArgamon,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 41:	VoieEnumereR("kcAgape",kcAgape,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 42:	VoieEnumereR("kcAgape1",kcAgape1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 43:	VoieEnumereR("kcAgasse",kcAgasse,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 44:	VoieEnumereR("kcAgave",kcAgave,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 45:	VoieEnumereR("kcBrexit",kcBrexit,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 46:	VoieEnumereR("kcBrexitt",kcBrexitt,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 47:	VoieEnumereR("kcBrex",kcBrex,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 48:	VoieEnumereR("kcHerschel",kcHerschel,4,k1SansSommetSousConnexe,k1Detailler);break;//pas de cycle; 4 chemins:AB AD CB CD
			case 49:	VoieEnumereR("kcPiedouche2",kcPiedouche2,4,k1SansSommetSousConnexe,k1Detailler);break;
			
			case 50:	CouplageEtudierTouT(0);break;
			case 51:	CouplageEtudierPolynomialemenT();break;
			case 52:	CouplageParfaitEnumereR(0);break;
			case 54:	CouplageEtudyeR(0);break;
			case 55:	VoieEnumereR("kcBico",kcBico,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 56:	VoieEnumereR("kcBistrine",kcBistrine,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 57:	VoieEnumereR("kcBitrine",kcBitrine,2,k1SansSommetSousConnexe,k1Detailler);break;


			case 60:	VoieEnumereR("kcThuttePlein",kcThuttePlein,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 61:	VoieEnumereR("kcThutteTiers",kcThutteTiers,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 62:	VoieEnumereR("kcToutteTiers",kcToutteTiers,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 63:	VoieEnumereR("kcTouttePlein",kcTouttePlein,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 64:	VoieEnumereR("kcCroisade",kcCroisade,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 69:	CycleEnumereR(kcCycle,0,k1SansSommetSousConnexe,k1Detailler);break;
			case 70:	VoieEnumereR("kcTricycle",kcTricycle,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 75:	VoieEnumereR("kcGrain24",kcGrain24,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 76:	VoieEnumereR("kcPanama",kcPanama,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 77:	VoieEnumereR("kcBanzai1",kcBanzai1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 78:	VoieEnumereR("kcBanzai2",kcBanzai2,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 79:	VoieEnumereR("kcBarbare1",kcBarbare1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 80:	VoieEnumereR("kcBarbare2",kcBarbare2,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 81:	VoieEnumereR("kcBizut",kcBizut,4,k1SansSommetSousConnexe,k1Detailler);break;

			case 85:	VoieEnumereR("kcCapside",kcCapside,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 86:	VoieEnumereR("kcGelule1",kcGelule1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 87:	VoieEnumereR("kcGelule2",kcGelule2,4,k1SansSommetSousConnexe,k1Detailler);break;

			case 90:	VoieEnumereR("kcVingtSix",kcVingtSix,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 91:	VoieEnumereR("kcTrips",kcTrips,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 92:	VoieEnumereR("kcPeter",kcPeter,4,k1SansSommetSousConnexe,k1Detailler);break;

			case 93:	VoieEnumereR("kcClaustra1",kcClaustra1,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 94:	VoieEnumereR("kcClaustra2",kcClaustra2,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 95:	VoieEnumereR("kcKarre",kcKarre,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 96:	VoieEnumereR("kcQarre",kcQarre,4,k1SansSommetSousConnexe,k1Detailler);break;
			case 97:	VoieEnumereR("kcKrill",kcKrill,4,k1SansSommetSousConnexe,k1Detailler);break;
			default:break;
		}
	Appel1(sC2("CycleTESTER,test n°",sEnt(iTest)));
}//CycleTESTER	

/*    CycleTESTER,test n°12: tâche en cours...
Graphe généré avant symétrisation, et spécifié avec couleurs: (20 arcs)
    (A,B,r) (A,F,v) (A,K,b) (B,C,b) (B,G,r) (B,L,r) (C,D,v) (C,H,r) (C,M,v) (D,E,r) (D,I,b) (D,N,b) (E,A,b) (E,J,b) (E,O,r) (F,H,b) (G,I,b) (H,J,r) (I,F,r) (J,G,v).
Sous-connexité interdite pour les sommets A à J.
Cycle n° 3 (lgr  8): (C,H,F,I,G,J,E,D,C).
Cycle n° 9 (lgr  8): (B,G,J,H,F,I,D,C,B).
Bilan: 7 cycles exempts de sous-connexité sur 19 cycles inventoriés.
    CycleTESTER,test n°12: tâche terminée.
*/

void InventaireAnnonceR(graf gG,int nSousConnexe,int bSansSommetSousConnexe,int bDetailler){
	int bPremier;
	int nFacultatif;//dénombre les sommets techniques
	int nFacultatifMax;
	int sX;
	//Appel0("InventaireAnnonceR");
		for (nFacultatif=0,sX=1;sX<=gG.nSommetEnTout;sX++)
			if (!bSommetSousConnexablE(&gG,sX))
				nFacultatif++;
		nFacultatifMax=nFacultatif;
		//te("nFacultatifMax",nFacultatifMax);
		printf("Inventaire %sdes cycles",sChoix0(!bDetailler,"non détaillé "));
		if (bSansSommetSousConnexe)
			printf(" qui préservent la 2-connexité des sommets A à %c%s",cSommetLitteraL(nSousConnexe),sChoix0(nFacultatifMax>0," autres que "));
		for (bPremier=kV,nFacultatif=0,sX=1;sX<=gG.nSommetEnTout;sX++){
			//printf("\ninventaire pour le sommet %d en cours…",sX);
			if (!bSommetSousConnexablE(&gG,sX)){
				nFacultatif++;
				if (!bPremier)
					printf("%s",(nFacultatif<nFacultatifMax)?",":" et ");
				printf("%c",cSommetLitteraL(sX));
				bPremier=kF;
			}
		}
		if (1 && bPremier)
			printf(": aucun cycle ne préserve la 2-connexité.\n");
		else printf(":\n");
	//Appel1("InventaireAnnonceR");
}//InventaireAnnonceR

void ParcoursCouvriR(char kcArc[],int nExces,graf gG){
	//couvre le graphe avec les parcours stockés ds sParcourS[]
	int bA,bB,bC,bD,bBB,bDD;
	int nArc;
	int nArete;
	int bBiffe;
	int nCardinal;
	int bCoche[kuGrapheArcLim];
	int bCouvert;
	long zCouverture;
	long zCouvertureMax;
	long zCouvert;
	int sCouvre[kuGrapheSommetLim];
	int uParcours;
	int ipCouvre;
	int bExces;
	int nItem;
	int sItem,sItem0;
	int uItem;
	char acPole[1+nExces];
	int anPrepole[1+nExces];
	char acPrepole[1+nExces];
	int nPile[kuGrapheSommetLim];
	int uPole,bPrendre;
	int nRecouvrement=0;
	int nSommat;
	int sX,sY;
	//Appel0("ParcoursCouvriR");
	//	GrapheVoir1(&gG,kF,"Graphe pr ParcoursCouvriR");
	for (uPole=1;uPole<=nExces;uPole++)
		acPole[uPole]=kcArc[3*( (nChaineLg(kcArc)/3-nExces+uPole-1) )+1];
	for (uPole=1;uPole<=nExces;uPole++)
		anPrepole[uPole]=nLettre(kcArc[3*( (nChaineLg(kcArc)/3-nExces+uPole-1) )+0]);
	for (uPole=1;uPole<=nExces;uPole++)
		acPrepole[uPole]=cLettre(anPrepole[uPole]);
	//teeee("ParcoursCouvriR:acPole[1],acPole[2],acPole[3],acPole[4]",acPole[1],acPole[2],acPole[3],acPole[4]);
	//te("nExces",nExces);
	nSommat=gG.nSommetEnTout-nExces;
		Assert1("ParcoursCouvriR1",nSommat>0);
		zCouvertureMax=zPuissance(2,nParcoursEnTouT);
		for (zCouverture=1;zCouverture<=zCouvertureMax;zCouverture++){
			ipCouvre=0;
			if (0) te("nSommat",nSommat);
			for (nItem=1;nItem<=nSommat;nItem++)
				sCouvre[nItem]=0;
			if (zCouverture==0){
				printf("Couverture envisagée: ");
				for (zCouvert=zCouverture,uParcours=1;uParcours<=nParcoursEnTouT;uParcours++){
					bPrendre=(zCouvert%2>0);
					if (zCouvert%2==1)
						printf("%d+",uParcours);
					zCouvert=zCouvert/2;
				}
				printf("\n");
			}
			zCouvert=zCouverture;
			for (bCouvert=kF,bExces=kF,uParcours=1;(uParcours<=nParcoursEnTouT) && !bExces;uParcours++){
				bPrendre=(zCouvert%2==1);
				if (bPrendre){//ajouter si possible le parcours à la couverture courante
					nCardinal=sParcourS[uParcours][0];
					for (nItem=1;nItem<=nCardinal;nItem++){
						sItem=sParcourS[uParcours][nItem];
						if (bCroit(1,sItem,nSommat))
							bPrendre=bPrendre && (sCouvre[sItem]==0);
					}
					if (bPrendre){//ajouter effectivt le parcours à la couverture courante sCouvre[]
						if (zCouverture==0) teee("zCouverture,uParcours et Cardinal pris",zCouverture,uParcours,nCardinal);
						for (nItem=1;nItem<=nCardinal;nItem++){
							sItem=sParcourS[uParcours][nItem];
							sCouvre[sItem]=1;
						}
						nPile[++ipCouvre]=uParcours;
						if (zCouverture==0){
							//sCouvre soit affiché
								for (nItem=1;nItem<=nSommat;nItem++)
									printf("%2d",sCouvre[nItem]);
								printf("\n");
						}
						for (bCouvert=kV,nItem=1;nItem<=nSommat;nItem++)
							if (bSommetSousConnexablE(&gG,nItem))
								bCouvert=bCouvert && sCouvre[nItem]==1;
					}else bExces=kV;
				}
				zCouvert=zCouvert/2;
			}
			if (bCouvert && !bExces){
				printf("Couverture n°%d: {",++nRecouvrement,zCouverture);
				//AreteCocheR();
					for (sX=1;sX<=gG.nSommetEnTout;sX++){
						for (nArc=gG.aHed[sX];nArc<gG.aHed[sX+1];nArc++){
							sY=gG.sSuk[nArc];
							bCoche[nArc]=0;
							if (sX<sY && bCroit(1,sX,nSommat) && bCroit(1,sY,nSommat))
								bCoche[nArc]=1;
						}
					}
				for (bA=kF,bB=kF,bC=kF,bD=kF,bBB=bDD=0,nItem=1;nItem<=ipCouvre;nItem++){
					printf("%d",nPile[nItem]);
					if (nItem<ipCouvre)
						printf(",");
						uParcours=nPile[nItem];
						nCardinal=sParcourS[uParcours][0];
						//AreteBiffeR(uParcours);
							sItem=sParcourS[uParcours][nCardinal];//-1 puisque cycle
					        //printf(" First:%c Last:%c\n",cSommetLitteraL(sParcourS[uParcours][1]),cSommetLitteraL(sItem));
							for (uItem=1;uItem<=nCardinal;uItem++){
								sItem0=sItem;
								sItem=sParcourS[uParcours][uItem];
								if (bCroit(1,sItem0,nSommat) && bCroit(1,sItem,nSommat)){
									bBiffe=0;
									if (nArc=nGrapheArc(&gG,sItem0,sItem),nArc>0)
										{bCoche[nArc]=0;bBiffe+=1;}
									if (nArc=nGrapheArc(&gG,sItem,sItem0),nArc>0)
										{bCoche[nArc]=0;bBiffe+=1;}
									//printf(" Arete:%c %c %d\n",cSommetLitteraL(sItem0),cSommetLitteraL(sItem),bBiffe);
								}
							}
						for (uItem=1;uItem<=nCardinal;uItem++){
							sItem=sParcourS[uParcours][uItem];
							//te("sItem",sItem);
							if ((nExces>=2 && sItem==nLettre(acPole[2])))
								bBB=1;
							if ((nExces>=4 && sItem==nLettre(acPole[4])))
								bDD=1;
							bA=bA || (nExces>=1 && sItem==nLettre(acPole[1]));
							bB=bB || (nExces>=2 && sItem==nLettre(acPole[2]));
							bC=bC || (nExces>=3 && sItem==nLettre(acPole[3]));
							bD=bD || (nExces>=4 && sItem==nLettre(acPole[4]));
						}
				}
				printf("},");
				if (bA+bB+bC+bD>2){
					printf(" 2 voies,");
					//d4(bA,bB,bC,bD);
					if (bBB && bDD)
						printf(" BD,");
				}else if (bA || bB || bC || bD){
					printf(" voie ");
					if (bA)
						printf("%c",acPrepole[1]);
					if (bB)
						printf("%c",acPrepole[2]);
					if (bC)
						printf("%c",acPrepole[3]);
					if (bD)
						printf("%c",acPrepole[4]);
					printf(",");
				}
				//AreteEnumereR(uParcours);
					for (nArete=0,nArc=1;nArc<=gG.nArcEnTout;nArc++)
						if (bCoche[nArc]>0)
							nArete++;
					printf(" reste %s:",sPluriel(nArete,"arête"));
					for (sX=1;sX<=nSommat;sX++)
						for (nArc=gG.aHed[sX];nArc<gG.aHed[sX+1];nArc++){
							sY=gG.sSuk[nArc];
							if (sX<sY && (bCoche[nArc]>0))
								printf(" (%c,%c)",cSommetLitteraL(sX),cSommetLitteraL(sY));
						}

				printf(".\n");
			}
		}
	//Appel1("ParcoursCouvriR");
}//ParcoursCouvriR

void ParcoursEmpileR(int bAfficher){
	int nCardinal;
	int uS;
	int nItem;
	if (bAfficher)
		te("ParcoursEmpileR,nb de cycles à empiler",nCycleAfficheR);
	for (uS=1;uS<=nCycleAfficheR;uS++){
		nParcoursEnTouT++;
		nCardinal=sCyclE[uS][0];
		for (nItem=0;nItem<=nCardinal;nItem++)
			sParcourS[nParcoursEnTouT][nItem]=sCyclE[uS][nItem];
	}
}//ParcoursEmpileR

void ParcoursVoiR(){
	int nCardinal;
	int uParcours;
	int nItem;
	//Appel0("ParcoursVoiR");
		for (uParcours=1;uParcours<=nParcoursEnTouT;uParcours++){
			nCardinal=sParcourS[uParcours][0];
			printf("Parcours %2d: (",uParcours);
				for (nItem=1;nItem<=nCardinal;nItem++)
					SommetListeR(sParcourS[uParcours][nItem],kV);
				SommetListeR(sParcourS[uParcours][1],kF);
			printf(").\n");
		}
	//Appel1("ParcoursVoiR");
}//ParcoursVoiR

void PisteDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible,int bCycleAfficher){
	//détecter les ciruits en parcourant(récursivt) le graphe gG à partir de sDepuis; mémorise et affiche les cycles détectés
	CycleDetecteR(gG,sDepuis,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,pnCycleEnTout,pnCycleCompatible,bCycleAfficher);
	//if (bCycleAfficher) te("nCycleAfficheR avant CycleBiffeR",nCycleAfficheR);
	CycleBiffeR(gG,gG.nSommetEnTout-1,gG.nSommetEnTout);
	//if (bCycleAfficher) te("nCycleAfficheR après CycleBiffeR",nCycleAfficheR);
	if (bCycleAfficher)
		CycleAfficherTouT(gG);
}//PisteDetecteR

void PisteListeR(graf gG,int sDepuis,int szVoisin,int sListe[]){
	int nCardinal,sDernier;
	//nCardinal:=lgr du Cycle,sListe[]:=pile de sommets
		nCardinal=0;
		sDernier=sDepuis;
		sListe[++nCardinal]=sDernier;
		While(kuGrapheSommetLim);
		while ( bWhile("PisteListeR",gG.sPer[sDernier]!=sDernier && gG.sPer[sDernier]!=szVoisin) ) {
			sDernier=gG.sPer[sDernier];
			sListe[++nCardinal]=sDernier;
		}
		if (szVoisin!=0)
			sListe[++nCardinal]=szVoisin;
		sListe[0]=nCardinal;
}//PisteListeR

void PisteVoirSouS(int bSous,int sListe[],int nPhase){
	int nCardinal=sListe[0];
	int uS;
	if (bSous){
		printf("********************** piste provisoire,phase n°%d: ",nPhase);
		for (uS=1;uS<=nCardinal;uS++)
			printf("%c ",cSommetLitteraL(sListe[uS]));
		printf(" (%s).\n",sPluriel(nCardinal,"élément"));
	}
}//PisteVoirSouS

void SommetListeR(int sSommet,int bVirguler){
	//dédié CycleAfficheR et ParcoursVoiR
	if (kbLitteraL) 
		printf("%c",cSommetLitteraL(sSommet));
	else printf("%d",sSommet);
	if (bVirguler)
		printf(",");
}//SommetListeR

char cSommetLitteraL(int sX){
	char cLitteral;
	cLitteral=(bCroit(1,sX,kuMinusculeOffset-1))? 'A'+sX-kuMajusculeOffset : 'a'+sX-kuMinusculeOffset;
	return(cLitteral);
}//cSommetLitteraL

char* sSommetLitteraL(int sX){
	char cLitteral;
	cLitteral=cSommetLitteraL(sX);
	return(sC(cLitteral));
}//sSommetLitteraL

int bSommetNonEncoreEmpileH(graf *pgG,int sOrigine,int sVierge,int *pbCycle){
	// vrai ssi sVierge est un sommet non encore empilé,ie qui ne figure dc pas ds la paternité du sommet de pile sOrigine
	int nDistance=0;
	int bNonEncoreEmpileH=kV;
	int sX,sY;
	*pbCycle=kV;
	sY=sOrigine;
	do {
		sX=sY;
		sY=pgG->sPer[sX];
		bNonEncoreEmpileH=bNonEncoreEmpileH && (sY!=sVierge);
		nDistance++;
	} while (bNonEncoreEmpileH && pgG->sPer[sY]!=0 && pgG->sPer[sY]!=sX);
	if (!bNonEncoreEmpileH)
		*pbCycle=(nDistance>1);//exclut les cycles de lgr 2
	//*pbCycle=kV;
	return(bNonEncoreEmpileH);
}//bSommetNonEncoreEmpileH

int bSommetSousConnexablE(graf *pgG,int sCandidat){
	//vrai ssi sCandidat n'est incident dans pgG à aucun arc de couleur knCouleurVersSommetFacultatiF 
	int aK;
	int nCouleur;
	int bSousConnexable;
	int sY;
	bSousConnexable=kV;//d
	for (aK=pgG->aHed[sCandidat]; aK<pgG->aHed[sCandidat+1]; aK++) {
		sY=pgG->sSuk[aK];
		nCouleur=nGrapheCouleur(pgG,sCandidat,sY);
		if ( nCouleur==knCouleurVersSommetFacultatiF )
			bSousConnexable=kF;
	}
	return(bSousConnexable);
}//bSommetSousConnexablE

int bSommetSousConnexE(graf *pgG,int sListe[],int nSousConnexe,int *psSoliton){
	//vrai ssi un sommet sous-connexable de gG n'est plus 2-connexe ds gG\sListe
	int aK;
	int nCardinal;
	int bSousConnexe;
	int nConnexion;
	int sX,sY;
	bSousConnexe=kF;//d
	nCardinal=sListe[0];
	for (sX=1;sX<=nSousConnexe;sX++)
		if (bSommetSousConnexablE(pgG,sX) && !bVecteurContient1(sX,nCardinal,sListe)){
			nConnexion=pgG->aHed[sX+1]-pgG->aHed[sX];//d
			for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
				sY=pgG->sSuk[aK];
				if ( bVecteurContient1(sY,nCardinal,sListe) )
					nConnexion--;
			}
			if (!bSousConnexe && nConnexion<=1){
				*psSoliton=sX;
				bSousConnexe=kV;
			}
		}
	return(bSousConnexe);
}//bSommetSousConnexE

void VoieEnumereR(char* sMessage,char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler){
	//génère le graphe défini par (kcArc,nExces) et inventorie soit tous ses cycles soit seult ceux qui ne rendent aucun sommet sous-connexe.
	int bAfficher,nArc;
	graf *pgG;
	int nSousConnexe;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	int nSommet;
	int uPole,uPole0,uPole1;
	int sPole0,sPole1;
	char acPole[1+nExces];
	printf("Énumération des voies du graphe \"%s\".\n",sMessage);
	CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
	GrapheVoir1(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec des","sans"),"couleurs"));
	GrapheSymetriser(pgG);
	//GrapheVoir1(pgG,bCouleurChange,"Graphe symétrique colorié après symétrisation");
	//InventaireAnnonceR(*pgG,nSousConnexe,bSansSommetSousConnexe,bDetailler);
	CycleInventorieR(*pgG,kV || bSansSommetSousConnexe,bCouleurChange,nSousConnexe,!k1Afficher,!bDetailler);
	ParcoursEmpileR(!k1Afficher);
	//ParcoursVoiR();
	nSommet=pgG->nSommetEnTout;
	//te("pgG->nArcEnTout",pgG->nArcEnTout);te("nSommet",nSommet);te("nExces",nExces);
	nArc=pgG->nArcEnTout/2;//ie avant symétrisation
	//te("nChaineLg(kcArc)",nChaineLg(kcArc));
	for (uPole=1;uPole<=nExces;uPole++)
		acPole[uPole]=kcArc[3*( (nChaineLg(kcArc)/3-nExces+uPole-1) )+1];
	//printf("acPole[1],acPole[2],acPole[3],acPole[4]:%c,%c,%c,%c.\n",acPole[1],acPole[2],acPole[3],acPole[4]);
	if (1) for (uPole=1;uPole<=nExces;uPole++)
		printf("Pôle %d: %c.\n",uPole,acPole[uPole]);
	//GrapheVoir0(pgG,"ds VoieEnumereR",grCouleur);
	for (uPole0=1,sPole0=nLettre(acPole[uPole0]);uPole0<=nExces;sPole0++,uPole0++)
		for (uPole1=1,sPole1=nLettre(acPole[uPole1]);uPole1<=nExces;sPole1++,uPole1++)
			if (acPole[uPole0]<acPole[uPole1]){
				bAfficher=1 || (sPole0==11) && (sPole1==14);
				bAfficher=0;
				if (bAfficher) printf("**** Voie (%c,%c):\n",acPole[uPole0],acPole[uPole1]);
				//if (bAfficher) tee("sPole0,sPole1",sPole0,sPole1);
				GrapheCreer(0,&pgG);
				nCycleAfficheR=0;
				nSousConnexe=0;
				CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
				//GrapheVoir0(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec","sans"),"couleurs"));
				GrapheSymetriser(pgG);
				//GrapheVoir0(*ppgG,bCouleurChange,"Graphe symétrique colorié après symétrisation");
				//if (bAfficher) te("pgG->nSommetEnTout",pgG->nSommetEnTout);
				CycleInventorieR(*pgG,bSansSommetSousConnexe,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
				nCycleAfficheR=0;
				//te("pgG->nSommetEnTout",pgG->nSommetEnTout);
				VoieInventorieR(pgG,sPole0,sPole1,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
			}
	ParcoursVoiR();
	ParcoursCouvriR(kcArc,nExces,*pgG);
	GrapheCreer(0,&pgG);
}//VoieEnumereR

void VoieInventorieR(graf *pgG,int sSource,int sTrappe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler){
	//inventorie et affiche les artères de gG qui relient sSource à sTrappe.
	int sBut;
	int sCible;
	int nCycleEnTout=0;
	int nCycleCompatible=0;
	int sDepart;
	//CycleRazeR();//raze la pile qui mémorise les cycles jugés pertinents
	//créer deux nouveaux sommets sBut et sCible et les 3 arêtes colorées (sCible,sSource,kuCouleurBouT), (sTrappe,sBut,kuCouleurBouT) et (sBut,sCible,1).
	if (bAfficher) printf("VoieInventorieR de %s à %s.\n",sSommetLitteraL(sSource),sSommetLitteraL(sTrappe));
	//GrapheVoir0(pgG,"ds VoieInventorieR",grCouleur);
	GrapheSommer(pgG,+2);
		sCible=pgG->nSommetEnTout-1;
		sBut=pgG->nSommetEnTout;
		GrapheArquer(pgG,sCible,sSource);GrapheColorer(pgG,sCible,sSource,kuCouleurBouT);
		GrapheArquer(pgG,sTrappe,sBut);GrapheColorer(pgG,sTrappe,sBut,kuCouleurBouT);
		GrapheArquer(pgG,sCible,sBut);GrapheColorer(pgG,sCible,sBut,1);
		GrapheSymetriser(pgG);
		//if (bAfficher) GrapheVoir1(pgG,kV,sC4b(" dans le graphe augmenté de 2 sommets" ,sSommetLitteraL(sCible),"et",sSommetLitteraL(sBut)));
		sDepart=sCible;
		//explorer en largeur d'abord en partant de chaque sommet sDepart;gG.sPer[] mémorise le chemin qui relie sDepart au sommet courant
			//nCycleAfficheR=0;
			VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
			pgG->sPer[sDepart]=sDepart;//vital pour identifier le sommet origine de ts les chemins détectés par nCycleDetecteR()
			PisteDetecteR(*pgG,sDepart,kF,bColoration,nSousConnexe,bDetailler,&nCycleEnTout,&nCycleCompatible,bAfficher);
			ParcoursEmpileR(bAfficher);
	GrapheSommer(pgG,-2);
	if (kF && bAfficher)
		t(sC5b("Bilan:",sPluriel(nCycleCompatible,"voie"),"sans sous-connexité","sur",sPluriel(nCycleEnTout,"voie$ inventoriée$")));
}//VoieInventorieR

/*
[Session started at 2017-05-28 12:33:32 +0200.]
GNU gdb 6.3.50-20050815 (Apple version gdb-1461.2) (Fri Mar  5 04:43:10 UTC 2010)
Copyright 2004 Free Software Foundation, Inc.
GDB is free software, covered by the GNU General Public License, and you are
welcome to change it and/or distribute copies of it under certain conditions.
Type "show copying" to see the conditions.
There is absolutely no warranty for GDB.  Type "show warranty" for details.
This GDB was configured as "x86_64-apple-darwin".
tty /dev/ttys000
Loading program into debugger…
Program loaded.
run
[Switching to process 175]
Programme en cours...
    CycleTESTER,test n°82: tâche en cours...
Énumération des voies du graphe "kcGelule2".
Graphe généré avant symétrisation, et spécifié avec des couleurs (36 sommets et 44 arcs):
    (A,D,v) (A,M,r) (A,g,r) (B,C,r) (B,K,v) (B,h,v) (C,F,v) (C,N,v) (D,E,r) (E,F,v) (E,I,v) (F,G,r) (G,H,v) (G,K,v) (H,I,r) (H,O,v) (I,Q,v) (J,L,v) (J,P,r) (J,R,r) (K,L,r) (M,N,i) (O,P,i) (Q,T,r) (Q,c,v) (R,S,v) (R,a,r) (S,V,r) (S,d,r) (T,U,v) (U,V,r) (U,Y,r) (V,W,v) (W,X,r) (W,a,r) (X,Y,v) (X,e,r) (Y,i,r) (Z,b,r) (Z,f,v) (Z,j,v) (a,b,v) (c,d,i) (e,f,i).
Inventaire des cycles qui préservent la 2-connexité des sommets A à f autres que M,N,O,P,c,d,e et f:
Running…
    Cycle n° 1 (lgr 28): (A,M,N,C,B,K,L,J,R,S,V,W,a,b,Z,f,e,X,Y,U,T,Q,I,H,G,F,E,D,A).
**** Voie (g,h):
    Voie n° 1 (lgr 18): (A,g,k,l,h,B,C,F,G,K,L,J,P,O,H,I,E,D,A).
**** Voie (g,i):
    Voie n° 1 (lgr 18): (A,g,k,l,i,Y,X,W,V,U,T,Q,I,H,G,F,E,D,A).
    Voie n° 2 (lgr 23): (A,g,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,I,H,G,F,E,D,A).
    Voie n° 3 (lgr 23): (A,g,k,l,i,Y,X,W,V,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A).
    Voie n° 4 (lgr 32): (A,g,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,B,C,F,G,H,I,E,D,A).
**** Voie (g,j):
    Voie n° 1 (lgr 19): (A,g,k,l,j,Z,b,a,W,V,U,T,Q,I,H,G,F,E,D,A).
    Voie n° 2 (lgr 23): (A,g,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,G,F,E,D,A).
    Voie n° 3 (lgr 28): (A,g,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A).
    Voie n° 4 (lgr 19): (A,g,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,E,D,A).
    Voie n° 5 (lgr 23): (A,g,k,l,j,Z,b,a,W,V,S,R,J,L,K,B,C,F,G,H,I,E,D,A).
    Voie n° 6 (lgr 28): (A,g,k,l,j,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,B,C,F,G,H,I,E,D,A).
**** Voie (h,i):
    Voie n° 1 (lgr 27): (B,h,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,G,F,C,B).
    Voie n° 2 (lgr 27): (A,M,N,C,B,h,k,l,i,Y,X,W,V,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A).
**** Voie (h,j):
    Voie n° 1 (lgr 18): (B,h,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,C,B).
    Voie n° 2 (lgr 23): (B,h,k,l,j,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,G,F,C,B).
    Voie n° 3 (lgr 32): (A,M,N,C,B,h,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A).
    Voie n° 4 (lgr 23): (A,M,N,C,B,h,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,E,D,A).
**** Voie (i,j):
    Voie n° 1 (lgr 18): (Q,T,U,V,W,X,Y,i,k,l,j,Z,b,a,R,S,d,c,Q).
Parcours  1: (A,M,N,C,B,K,L,J,R,S,V,W,a,b,Z,f,e,X,Y,U,T,Q,I,H,G,F,E,D,A)
Parcours  2: (A,g,k,l,h,B,C,F,G,K,L,J,P,O,H,I,E,D,A)
Parcours  3: (A,g,k,l,i,Y,X,W,V,U,T,Q,I,H,G,F,E,D,A)
Parcours  4: (A,g,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,I,H,G,F,E,D,A)
Parcours  5: (A,g,k,l,i,Y,X,W,V,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A)
Parcours  6: (A,g,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,B,C,F,G,H,I,E,D,A)
Parcours  7: (A,g,k,l,j,Z,b,a,W,V,U,T,Q,I,H,G,F,E,D,A)
Parcours  8: (A,g,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,G,F,E,D,A)
Parcours  9: (A,g,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A)
Parcours 10: (A,g,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,E,D,A)
Parcours 11: (A,g,k,l,j,Z,b,a,W,V,S,R,J,L,K,B,C,F,G,H,I,E,D,A)
Parcours 12: (A,g,k,l,j,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,B,C,F,G,H,I,E,D,A)
Parcours 13: (B,h,k,l,i,Y,X,e,f,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,G,F,C,B)
Parcours 14: (A,M,N,C,B,h,k,l,i,Y,X,W,V,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A)
Parcours 15: (B,h,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,C,B)
Parcours 16: (B,h,k,l,j,Z,b,a,W,V,U,T,Q,c,d,S,R,J,L,K,G,F,C,B)
Parcours 17: (A,M,N,C,B,h,k,l,j,Z,b,a,R,S,V,W,X,Y,U,T,Q,I,H,O,P,J,L,K,G,F,E,D,A)
Parcours 18: (A,M,N,C,B,h,k,l,j,Z,b,a,W,V,S,R,J,L,K,G,F,E,D,A)
Parcours 19: (Q,T,U,V,W,X,Y,i,k,l,j,Z,b,a,R,S,d,c,Q)
Couverture n°1: {1}, reste 12 arêtes: (C,F) (E,I) (G,K) (H,O) (J,P) (O,P) (Q,c) (R,a) (S,d) (U,V) (W,X) (c,d).
Couverture n°2: {6}, voie AY, reste 13 arêtes: (A,M) (C,N) (E,F) (G,K) (H,O) (I,Q) (J,P) (M,N) (O,P) (R,a) (S,V) (U,Y) (W,X).
Couverture n°3: {17}, voie BZ, reste 13 arêtes: (B,K) (C,F) (E,I) (G,H) (J,R) (Q,c) (S,d) (U,V) (W,a) (X,e) (Z,f) (c,d) (e,f).
Couverture n°4: {2,19}, 2 voies, reste 14 arêtes: (A,M) (B,K) (C,N) (E,F) (G,H) (I,Q) (J,R) (M,N) (S,V) (U,Y) (W,a) (X,e) (Z,f) (e,f).
    CycleTESTER,test n°82: tâche terminée.
Programme terminé.

Debugger stopped.
Program exited with status value:0.
*/