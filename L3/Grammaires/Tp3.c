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


void TP3Facturer(int sOrigine, int sDestination, int nLongueur, int nLargeur, int nHauteur){
	
	graf *pgG;
	
	int NoArc;
	int h,la,lo;
	int facture = 0;
	int co;
	
	GrapheCreer(8,&pgG);
	
	char ksPetit[] = "AE2BE3EF1FC2FD3GA8GB8CH9DH9";
	char hauteur[] = "AE8BE5EF8FC5FD8GA8GB5CH5DH8";
	char largeur[] = "AE9BE9EF9FC9FD9GA9GB9CH9DH9";
	char longueur[] = "AE9BE9EF9FC9FD9GA9GB9CH9DH9";
	
	GrapheGenerer(ksPetit,&pgG);
	GrapheVoir0(pgG,"Graphe",grCouleur);
	
	int nArc = pgG->nArcEnTout;
	
	for(NoArc = 1; NoArc <= nArc; NoArc++){
	
		h = hauteur[3*NoArc-1]-'0';
		la = largeur[3*NoArc-1]-'0';
		lo = longueur[3*NoArc-1]-'0';
		
		
		if(h < nHauteur || la < nLargeur || lo < nLongueur){
			m1;
			pgG->nCout[NoArc] = 9999;
		}else{
			m2;
			pgG->nCout[NoArc] = ksPetit[3*NoArc-1]-'0';
		}
	}
	
	
	GrapheVoir0(pgG,"Graphe_change",grCout);
	
	facture = nGrapheChemineR(pgG,sOrigine,sDestination,&co);
	
	printf("\nFACTURE : %i\n",facture);
	
	GrapheCreer(0,&pgG);
	
	
}


void Tp3TESTER(int iTest){
	//teste le présent module
	
	Appel0(sC2("Tp3TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
			TP3Facturer(1,5,7,7,7);
			
		default: ;
	}
	Appel1(sC2("Tp3TESTER,test n°",sEnt(iTest)));
}//Tp3TESTER	

