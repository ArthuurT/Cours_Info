#include "Outil.h"
#include "Tp1.h"

//Exercice 5
// S-> ab* + b(a+b)* = a + (ab+) + b + b(a+b)+

	// S -> C + D (TD)

	// C -> a + U		(ab*)
	// U -> b + bU

	// D -> b + T			(b(a+b)*)
	// T -> M + MT
	// M -> a + b

	/***************/

	// S -> C + D (TP)

	// D -> T + B
	// T -> E + G
	// E -> G + T
	// G -> A + B

	// C -> A + U
	// U -> B + Z
	// Z -> B.U

	// A -> a
	// B -> b

char * sMOT;

int bA(int iDebut, int * piFin);
int bB(int iDebut, int * piFin);
int bS(int iDebut, int * piFin);
int bU(int iDebut, int * piFin);
int bZ(int iDebut, int * piFin);
int bC(int iDebut, int * piFin);
int bD(int iDebut, int * piFin);
int bG(int iDebut, int * piFin);
int bE(int iDebut, int * piFin);
int bT(int iDebut, int * piFin);

int bTp1AmorceR = kF;

void Tp1AMORCER(){
	bTp1AmorceR = kV;
}

void Tp1INITIALISER(){
	Assert1("Tp1INITIALISER", bTp1AmorceR);
}

int bA(int iDebut, int * piFin){
		//A->a
		int bSucces = sMOT[iDebut] == 'a';
		*piFin = (bSucces)? iDebut+1 : iDebut;
		return(bSucces);
}

int bB(int iDebut, int * piFin){
		//B->b
		int bSucces = sMOT[iDebut] == 'b';
		*piFin = (bSucces)? iDebut+1 : iDebut;
		return(bSucces);
}

int bC(int iDebut, int * piFin){
	//D-> A + U
	int iFin;
	int bSucces = bA(iDebut, &iFin) || bU(iDebut, &iFin);
	*piFin = (bSucces)? iFin:iDebut;
	return(bSucces);
}

int bD(int iDebut, int * piFin){
		//D-> T + B
		int iFin;
		int bSucces = bT(iDebut, &iFin) || bB(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bT(int iDebut, int * piFin){
		//T-> E + G
		int iFin;
		int bSucces = bE(iDebut, &iFin) || bG(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bU(int iDebut, int * piFin){
		//U-> B + Z
		int iFin;
		int bSucces = bB(iDebut, &iFin) || bZ(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bS(int iDebut, int * piFin){
		//S-> C + D
		int iFin;
		int bSucces = bC(iDebut, &iFin) || bD(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bE(int iDebut, int * piFin){
		//E -> G + T
		int iFin;
		int bSucces = bG(iDebut, &iFin) || bT(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bG(int iDebut, int * piFin){
		//G-> A + B
		int iFin;
		int bSucces = bA(iDebut, &iFin) || bB(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bZ(int iDebut, int * piFin){
		//Z -> B.U
		int iFin, iX;
		int bSucces = bA(iDebut, &iX) && bB(iX,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}


void Tp1TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	Assert1("Tp1TESTER0",bTp1AmorceR);
	switch(iTest){
			case 1: sMOT = "aab"; break;
			case 2: sMOT = "aaba"; break;
			case 3: sMOT = "abb"; break;
			case 4: sMOT = "ab"; break;
			case 5: sMOT = "ba"; break;
			case 6: sMOT = "abbb"; break;
			case 7: sMOT = "a"; break;
			default: Assert1("Tp1TESTER1",0); break;
	}
	bSucces = bS(0,&iFin);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;
	printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT), sEst(bEngendre));
}
