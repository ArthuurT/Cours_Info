#include "Outil.h"
#include "Graphe.h"
#include "Tp3.h"
int bTp3AmorceR;//ie le module a effectivement été amorcé
int bTp3OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp3 est actuellement alloué

void Tp3AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp3AmorceR=kV;
	bTp3OuverT=kF;
}//Tp3AMORCER

void Tp3INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp3INITIALISER",bTp3AmorceR,!bTp3OuverT);
}//Tp3INITIALISER

void Tp3TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			GrapheCreer(8,&pgG);
			GrapheCreer(0,&pgG);
			break;
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

