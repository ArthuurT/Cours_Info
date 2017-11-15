#include "Outil.h"
#include "Graphe.h"
#include "Tp4.h"
int bTp4AmorceR;//ie le module a effectivement été amorcé
int bTp4OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp4AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp4AmorceR=kV;
	bTp4OuverT=kF;
}//Tp4AMORCER

void Tp4INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp4AmorceR,!bTp4OuverT);
}//Tp4INITIALISER

void Tp4TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp4TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			GrapheCreer(0,&pgG);
			break;
		default: ;
	}
	Appel1(sC2("Tp4TESTER,test n°",sEnt(iTest)));
}//Tp4TESTER	

