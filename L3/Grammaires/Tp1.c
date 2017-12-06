#include "Outil.h"
#include "Tp1.h"

//Exercice 1
// L1 = ba + (b^n).(a^n).b*.a		,n >= 0

	// L1 = (ba) + ((b^n).(a^n).b*.a, n >= 0)
	// L1 = (ba) + ((b*)a, n = 0) + ((b^n).(a^n).b*.a, n > 0)
	// L1 = (ba) + (((b+)+1)a, n = 0) + ((b^n).(a^n).((b+)+1).a, n > 0)
	// L1 = (((b+)a + a), n = 0) + ((b^n).(a^n).((b+)a + a), n > 0)

	/**************/

	// S -> V + Z (TD)

	// V -> Y + A			(b+)a + a
	// Y -> Ga + a
	// G -> bG + b

	// Z -> C.V				((b^n).(a^n).((b+)a + a)
	// C -> bCa + ba

	/***************/

	// S -> V + Z (TP)

	// V -> Y + W
	// Y -> C + A
	// C -> G.A
	// G -> D + B
	// D -> B.D

	// Z -> C.V
	// C -> M + N
	// M -> B.C.A
	// N -> B.A




char * sMOT;

int bA(int iDebut, int * piFin);
int bB(int iDebut, int * piFin);
int bC(int iDebut, int * piFin);
int bD(int iDebut, int * piFin);
int bU(int iDebut, int * piFin);
int bV(int iDebut, int * piFin);
int bZ(int iDebut, int * piFin);
int bN(int iDebut, int * piFin);
int bM(int iDebut, int * piFin);
int bS(int iDebut, int * piFin);
int bT(int iDebut, int * piFin);
int bY(int iDebut, int * piFin);
int bW(int iDebut, int * piFin);
int bG(int iDebut, int * piFin);

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
		//B-> b
		int bSucces = sMOT[iDebut] == 'b';
		*piFin = (bSucces)? iDebut+1 : iDebut;
		return(bSucces);
}

int bV(int iDebut, int * piFin){
		//V-> Y+W
		int iFin;
		int bSucces = bY(iDebut, &iFin) || bW(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bT(int iDebut, int * piFin){
		//T-> M + N
		int iFin;
		int bSucces = bM(iDebut, &iFin) || bN(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bN(int iDebut, int * piFin){
		//N-> B.A
		int iFin, iX;
		int bSucces = bB(iDebut, &iX) && bA(iX, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bZ(int iDebut, int * piFin){
		//D-> C.V
		int iFin, iX;
		int bSucces = bC(iDebut, &iX) && bV(iX, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bD(int iDebut, int * piFin){
		//D-> B.D
		int iFin, iX;
		int bSucces = bB(iDebut, &iX) && bD(iX, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bC(int iDebut, int * piFin){
		//C-> G + A
		int iFin;
		int bSucces = bG(iDebut, &iFin) || bA(iDebut, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bM(int iDebut, int * piFin){
		//M-> B.C.A
		int iFin, iX, iY;
		int bSucces = bB(iDebut, &iX) && bT(iX, &iY) && bA(iY, &iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bY(int iDebut, int * piFin){
		//Y -> C + A
		int iFin;
		int bSucces = bC(iDebut, &iFin) || bA(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bG(int iDebut, int * piFin){
		//G -> D + B
		int iFin;
		int bSucces = bD(iDebut, &iFin) || bB(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

int bS(int iDebut, int * piFin){
		//S-> V + Z
		int iFin;
		int bSucces = bV(iDebut, &iFin) || bZ(iDebut,&iFin);
		*piFin = (bSucces)? iFin:iDebut;
		return(bSucces);
}

void Tp1TESTER(int iTest){
	int bEngendre, iFin, bSucces;
	Assert1("Tp1TESTER0",bTp1AmorceR);
	switch(iTest){
			case 1: sMOT = "bbaaba"; break;
			case 2: sMOT = "bbbaaa"; break;
			case 3: sMOT = "bbbaaabbba"; break;
			case 4: sMOT = "ba"; break;
			case 5: sMOT = "bbab"; break;
			case 6: sMOT = "bbaaab"; break;
			case 7: sMOT = "bbbbaaaa"; break;
			default: Assert1("Tp1TESTER1",0); break;
	}
	bSucces = bS(0,&iFin);
	bEngendre = bSucces && nChaineLg(sMOT) == iFin;
	printf("%s: %s %s engendré par la grammaire décrite dans \"Grammaire.c\".\n",(bEngendre)? "SUCCES" : "ECHEC", sG(sMOT), sEst(bEngendre));
}
