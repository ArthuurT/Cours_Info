#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
int bTp2AmorceR;//ie le module a effectivement été amorcé
int bTp2OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp2AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp2AmorceR=kV;
	bTp2OuverT=kF;
}//Tp2AMORCER

void Tp2INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp2AmorceR,!bTp2OuverT);
}//Tp2INITIALISER

void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			GrapheCreer(0,&pgG);
			break;
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

