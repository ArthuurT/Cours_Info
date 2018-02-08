#include "Outil.h"
#include "Ticket.h"
//NB1: Comme tout module, Ticket doit être amorcé avant d'être utilisé ——via un appel à TicketAMORCER() depuis la la routine ModuleAmorceR() du main.
//NB2: Ticket est optimisé pour les algorithmes de graphes qui gèrent N numéros de sommets distincts appartenant à [1..N].
//NB3: Pour accéder à une collection de tickets distincts, appeler pTicketAllouer(nb total de tickets).
//NB5: Ce module permet d'utiliser à un moment donné un nombre quelconque de collections de tickets. 
//NB0: ce module permet d'allouer N tickets et de les retirer en O(1) chaqie fois;sert à implémenter CouplageMaximiserMemeSiNonBipartI ds Couplage.c

#define kuTicketCardinalMaX (16-1) //nb max de tickets. 
struct TickeT{
	int quotamax;
	int quota;
	int tiquet;//index courant sur l'anneau
	int amont[1+kuTicketCardinalMaX];//1+kuTicketCardinalMaX car l'indice 0 est inutilisé
	int aval[1+kuTicketCardinalMaX];//1+kuTicketCardinalMaX car l'indice 0 est inutilisé
};
int uTickNoM[1+kuTicketCardinalMaX];
int bTicketAmorceR;//ie le présent module a effectivement été amorcé.
void TicketGarniR(void *pTicket);//O(nCardinalMax)

void *pTicketAllouer(int uCardinalMax){//O(nCardinalMax)
	//Un appel avec nCardinalMax>0 alloue une deque à nCardinalMax éléments;un appel avec nCardinalMax=0 restitue la deque.
	void* pTicket;
	Assert2("pTicketAllouer",bTicketAmorceR,bCroit(1,uCardinalMax,kuTicketCardinalMaX));
	pTicket=malloc(sizeof(struct TickeT));
	struct TickeT *pTick=pTicket;
	pTick->quotamax=pTick->quota=uCardinalMax;
	TicketGarniR(pTick);//en O(uCardinalMax) et non pas en O(kuTicketCardinalMaX),qui accroîtrait la complexité algorithmQ.
	pTick->tiquet=uCardinalMax;
	return(pTicket);
}//pTicketAllouer

void TicketAMORCER(){
	//amorce le présent module une fois pour toutes (sa complexité algorithmique n'est donc pas critique a priori)
	Assert1("TicketAMORCER",bFrontiere8(1+kuTicketCardinalMaX));//ie un multiple de 8 est requis
	for (int uT=1;uT<=kuTicketCardinalMaX;uT++)
		uTickNoM[uT]=uT;
	bTicketAmorceR=kV;
}//TicketAMORCER

int nTicketCardinal(void *pTicket){//O(1)
	int nCardinal;
	struct TickeT *pTick=pTicket;
	Assert1("nTicketCardinal",bTicketAmorceR);
	nCardinal=pTick->quota;
	return(nCardinal);
}//nTicketCardinal

int bTicketContient(void *pTicket,int uTicket){//O(1)
	//vrai ssi la deque pTicket contient le ticket uTicket
	int bContient;
	struct TickeT *pTick=pTicket;
	Assert2("bTicketContient",bTicketAmorceR,bCroit(1,uTicket,pTick->quotamax));
	bContient=pTick->amont[uTicket]!=0;
	return(bContient);
}//bTicketContient

void TicketGarniR(void *pTicket){//O(pTick->quotamax)
	//remplit amont[] et aval[] de façon à lier les éléments de *pTicket à l'aide d'un chaînage complet bilatéral
	int uT;
	struct TickeT *pTick=pTicket;
	for (uT=1;uT<=pTick->quotamax;uT++)
		pTick->amont[uT]=uT+1;
	pTick->amont[pTick->quotamax]=1;
	for (uT=1;uT<=pTick->quotamax;uT++)
		pTick->aval[uT]=uT-1;
	pTick->aval[1]=pTick->quotamax;
}//TicketGarniR

void TicketINITIALISER(){//O(?)
	//relance le présent module
	Assert1("TicketINITIALISER0",bTicketAmorceR);
}//TicketINITIALISER

void TicketRestituer(void *pTicket){//O(1)
	Assert2("TicketRestituer",bTicketAmorceR,pTicket!=0);
	free(pTicket);
}//TicketRestituer

void TicketRetirer(void *pTicket,int uTicket){//O(1)
	//retire uTicket des éléments de *pTicket, uTicket est réputé présent dans la collection de tickets désignée par pTicket.
	int nPred,nSucc;
	struct TickeT *pTick=pTicket;
	if (pTick->amont[uTicket]==0)
		te("TicketRetirer",uTicket);
	Assert3("TicketRetirer",bTicketAmorceR,bCroit(1,uTicket,pTick->quotamax),pTick->amont[uTicket]!=0);
	nSucc=pTick->amont[uTicket];
	nPred=pTick->aval[uTicket];
	pTick->amont[nPred]=nSucc;
	pTick->aval[nSucc]=nPred;
	pTick->amont[uTicket]=0;
	pTick->aval[uTicket]=0;
	pTick->tiquet=nSucc;
	pTick->quota--;
}//TicketRetirer

void TicketRetirer0(void *pTicket0,int uTicket0,void *pTicket,int uTicket){//O(1)
	//retire uTicket des éléments de *pTicket;si la collection pTicket devient vide, supprime cette collection de pTicket0.
	TicketRetirer(pTicket,uTicket);
	if ( 1 && nTicketCardinal(pTicket)==0 && bTicketContient(pTicket0,uTicket0) ){
		//TicketVisionner("AVANT TicketRetirer0",pTicket0);
		TicketRetirer(pTicket0,uTicket0);
		//TicketVisionner("APRES TicketRetirer0",pTicket0);
	}
}//TicketRetirer0

int uTicketSuivant(void *pTicket){//O(1)
	//rend (sans extraire) un ticket qcq de la collection de tickets désignée par pTicket, collection réputée non vide.
	int uSuivant;
	struct TickeT *pTick=pTicket;
	Assert3("uTicketSuivant0",bTicketAmorceR,nTicketCardinal(pTicket)>0,pTick->amont[pTick->tiquet]!=0);
	uSuivant=pTick->amont[pTick->tiquet];
	pTick->tiquet=uSuivant;
	Assert1("uTicketSuivant1",bCroit(1,uSuivant,pTick->quotamax));
	return(uSuivant);
}//uTicketSuivant

void TicketTESTER(int iTest){
	//teste le présent module
	int uTour,uT;
	struct TickeT *pTick;
	Appel0(sC2("TicketTester,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:
				pTick=pTicketAllouer(8);
					TicketVisionner("après pTicketAllouer",pTick);
					TicketRetirer(pTick,4);
					TicketVisionner("après TicketRetirer(pTick,4)",pTick);
					TicketVoir("après TicketRetirer(pTick,4)",pTick);
					TicketRetirer(pTick,3);
					TicketVisionner("après TicketRetirer(pTick,3)",pTick);
					TicketVoir("après TicketRetirer(pTick,3)",pTick);
					te("nTicketCardinal(pTick)",nTicketCardinal(pTick));
					printf("tickets restants: ");
						for (uT=5,uTour=1;uTour<=pTick->quota;uTour++){
							uT=uTicketSuivant(pTick);
							printf("%d%c",uT,(uTour<pTick->quota)?',':'.');
						}
					Ligne();
				TicketRestituer(pTick);
				break;
			case 2:
				break;
			default:
				break;
		}
	Appel1(sC2("TicketTester,test n°",sEnt(iTest)));
}//TicketTESTER	

void TicketVisionner(char *sMessage,void *pTicket){//O(pTick->quotamax)
	//affiche la structure de données qui mémorise la collection de tickets *pTicket 
	struct TickeT *pTick=pTicket;
	Assert3("TicketVoir",bTicketAmorceR,sMessage!=0,pTicket!=0);
	printf("%s %s:\n",sMessage,sP(sPluriel(pTick->quota,"ticket")));
	VecteurVoir(" noms" ,uTickNoM,1,pTick->quotamax);
	VecteurVoir("amont",pTick->amont,1,pTick->quotamax);
	VecteurVoir(" aval",pTick->aval,1,pTick->quotamax);
}//TicketVisionner

void TicketVoir(char *sMessage,void *pTicket){//O(pTick->quotamax)
	//énumère tous les tickets présents ds la collection *pTicket
	int uT;
	struct TickeT *pTick=pTicket;
	printf("%s %s",sMessage,sP(sPluriel(pTick->quota,"ticket")));
	if (pTick->quota>0)
		for (printf(": "),uT=1;uT<=pTick->quotamax;uT++)
			if (pTick->amont[uT]!=0 && pTick->aval[uT]!=0)
				printf("%3d",uT);
	printf(".\n");
}//TicketVoir
