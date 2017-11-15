#include "Outil.h"
#include "Foret.h"
//Forêt de Fisher contenant jusqu'à knAntiArbreMaX anti-arbres (il en faut autant que de sommets du graphe ds l'algo de Kruskal)
#define knAntiArbreMaX kE3-1 
int bForetAmorceR;//ie le module a effectivement été amorcé
int bForetLogN;//mode optimisé
int bForetOuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un tas est actuellement alloué
int nAntiArbreMaX;//nombre effectif d'anti-arbres (donc de composantes connexes) spécifié dans l'appel de ForetINITIALISER()
int iForeT[1+knAntiArbreMaX];//si >0,index dans [1..knAntiArbreMaX];sinon,hauteur de la composante connexe (nulle si antiarbre réduit à 1 sommet)
int nForetVoiR;
int nHauteurMaX;
int nIndirectioN;//cumul courant des indirections exécutées dans nForetComposante();permet d'estimer la complexité de Kruskal dans le pire cas

int bIndexValidE(int sSommet);

void ForetAMORCER(){
	//amorce le présent module une fois pour toutes
	bForetAmorceR=kV;
	bForetOuverT=kF;
	nAntiArbreMaX=0;
	nHauteurMaX=0;
	nForetVoiR=0;
}//ForetAMORCER

int nForetComposante(int sSommet){
	//rend le numéro de composante connexe du sommet sSommet
	int nTour,iIndex,uComposante;
	//te("sSommet",sSommet);
	Assert3("nForetComposante0",bForetAmorceR,bForetOuverT,bIndexValidE(sSommet));
	iIndex=sSommet;
	nTour=0;
	While(nAntiArbreMaX);
	do{
		uComposante=iIndex;
		iIndex=iForeT[uComposante];
		nTour++;
	}while(bWhile("nForetComposante1",iIndex>0));
	nIndirectioN+=nTour;
	nHauteurMaX=iMax(nTour,nHauteurMaX);
	Assert1("nForetComposante2",bIndexValidE(uComposante));
	return(uComposante);
}//nForetComposante

int nForetComplexiteh(int *pnHauteurMaximale){
	//rend la complexité,en tant que nombre total d'itérations effectuées dans la nForetComposante().
	int nComplexiteh;
	Assert1("nForetComplexiteh",bCroit(0,nIndirectioN,kuIntegerMax));
	nComplexiteh=nIndirectioN;
	*pnHauteurMaximale=nHauteurMaX;
	return(nComplexiteh);
}//nForetComplexiteh

void ForetFusionner(int ccComposante0, int ccComposante1){
	//fusionne les deux antiarbres qui ont pour antiracines les sommets ccComposante0 et ccComposante1,réputés distincts;cc=composante connexe
	int nHauteur0,nHauteur1;
	Assert3("ForetFusionner1",bCroit(1,ccComposante0,nAntiArbreMaX),bCroit(1,ccComposante1,nAntiArbreMaX),ccComposante0!=ccComposante1);
	nHauteur0=-iForeT[ccComposante0];
	nHauteur1=-iForeT[ccComposante1];
	Assert2("ForetFusionner2",bCroit(0,nHauteur0,nHauteurMaX),bCroit(0,nHauteur1,nHauteurMaX));
	if (bForetLogN){//fusionner les anti-arbres de façon en limitant autant que possible la hauteur de l'antiarbre résultant
		if (nHauteur0==nHauteur1){//la hauteur après fusion augmente de 1 nécessairement
			iForeT[ccComposante1]=ccComposante0;
			iForeT[ccComposante0]--;//<0 puisque c'est l'opposé de la hauteur de l'antiarbre après fusion des deux anti-arbres originaux
		} else //la hauteur après fusion reste égale à la plus grande hauteur
			if (nHauteur0>nHauteur1)
				iForeT[ccComposante1]=ccComposante0;
			else iForeT[ccComposante0]=ccComposante1;
	}
	else iForeT[ccComposante1]=ccComposante0;
}//ForetFusionner

void ForetINITIALISER(int nAntiArbreMax,int bLogN){//O(?)
	//si nAntiArbreMax,alloue une foret
	int uA;
	Assert2("ForetINITIALISER2",bForetAmorceR,bCroit(0,nAntiArbreMax,knAntiArbreMaX));
	nAntiArbreMaX=0;
	if (nAntiArbreMax>0){
		Assert1("ForetINITIALISER3",!bForetOuverT);
		nAntiArbreMaX=nAntiArbreMax;
		for (uA=1;uA<=nAntiArbreMax;uA++)
			iForeT[uA]=0;//chaque antiarbre dédié à chaque sommet a une hauteur nulle
		bForetOuverT=kV;
		bForetLogN=bLogN;
		nHauteurMaX=0;
		nIndirectioN=0;
	}
	else bForetOuverT=kF;
}//ForetINITIALISER

void ForetTESTER(int iTest){
	//teste le présent module
	#define kbLogN kV
	int nComposante;
	Appel0(sC2("ForetTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 0:
				te("nIndirectioN",nIndirectioN);
				break;
			case 1:
				ForetINITIALISER(6,kbLogN);
				ForetVoir("");
				nComposante=nForetComposante(2);
				te("nComposante",nComposante);
				ForetFusionner(1,2);
				ForetVoir("fusion 12");
				ForetFusionner(2,4);
				ForetVoir("fusion 24");
				ForetFusionner(4,6);
				ForetVoir("fusion 46");
				break;
			default:
				Assert1("ForetTESTER",0);
				break;
		}
	Appel1(sC2("ForetTESTER,test n°",sEnt(iTest)));
}//ForetTESTER	

void ForetVoir(char *sMessage){//O(nCardMaX)
	int uA;
	Assert3("ForetVoir",bForetAmorceR,bForetOuverT,sMessage!=0);
	nForetVoiR++;
	printf("Foret n°%2d %s ",nForetVoiR,sMessage);
	for (uA=1;uA<=nAntiArbreMaX;uA++)
		printf("%4d",iForeT[uA]);
	printf("\n");
}//ForetVoir

int bIndexValidE(int sSommet){
	int bSommet;
	bSommet=bCroit(1,sSommet,nAntiArbreMaX);
	return (bSommet);
}//bIndexValidE

