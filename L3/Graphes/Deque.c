#include "Outil.h"
#include "Deque.h"
//NB1: Comme tout module, Deque doit être amorcé avant d'être utilisé ——via un appel à DequeAMORCER() depuis la la routine ModuleAmorceR() du main.
//NB2: Deque est optimisé pour les algorithmes de graphes qui empilent ou enfilent des numéros de sommets à valeur dans [1..kuDequeCardinalMaX].
//NB3: Pour accéder à une deque de S sommets, S>0, encadrer les accès à la deque en question par DequeOuvrir(S) et DequeOuvrir(0).
//NB4: La deque après ouverture s'utilise soit comme une pile soit comme une file. L'usage mixte est détecté et dénoncé par assertions (cf tModePileOuFilE).
//NB5: Ce module permet d'utiliser à un moment donné une deque et une seule. 

#define kuDequeCardinalMaX (kP10-1) //nb max de sommets admissible ds la deque; k pour constante;u pour Un ou plus, kP10=2**10=1024). 
int nCarD;//nombre de sommets stockés actuellement dans la dernière deque allouée.
int nCardMaX;//nombre total de sommets demandé lors de l'allocation de la deque (la dernière allocation);n comme entier naturel,donc 0 et plus.
struct DequE{
	int sNexT[1+kuDequeCardinalMaX];//s comme sommet;d'où 1+kuDequeCardinalMaX puisque l'indice 0 est inutilisé
}DequE,*pDequE;
int bDequeOuvertE;//flipflop;b comme booléen;un flipflop désigne en anglais une bascule à 2 états (état flip,d'abord, puis état flop,d'où le nom).
int bDequeAmorceR;//ie le présent module a effectivement été amorcé.
int sLasT;//si strictt positif, index sur le sommet de pile mais aussi valeur de fond de pile; cet index est un numéro de sommet, d'où le préfixe s.
int tModePileOuFilE;//>0 si usage en pile,<0 en file, =0 si usage encore indéterminé. t comme trit,ie 3 états -1, 0 et 1. 

void DequeAllouer(int nCardinalMax){//O(1)
	//Un appel avec nCardinalMax>0 alloue une deque à nCardinalMax éléments;un appel avec nCardinalMax=0 restitue la deque.
	Assert3("DequeAllouer0",bDequeAmorceR,bCroit(0,nCardinalMax,kuDequeCardinalMaX),bTrit(tModePileOuFilE));
	FlipFlop("DequeAllouer1",nCardinalMax>0,&bDequeOuvertE);
	nCardMaX=nCardinalMax;
	nCarD=0;
	sLasT=0;
	tModePileOuFilE=0;//ie le mode, pile ou file, est actuellement indéterminé.
	if (nCardinalMax>0)
		pDequE=malloc(sizeof(DequE));
	else free(pDequE);
	if (bDequeOuvertE)//ie FlipFlop() ci-dessus a été appelé avec un nCardinalMax strictt positif raisonnable,ie kuDequeCardinalMaX ou moins.
		DequeRazer(nCardMaX);//en O(nCardMaX) et non pas en O(kuDequeCardinalMaX),qui accroîtrait la complexité algorithmique pour les petits graphes.
}//DequeAllouer

void DequeAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité algorithmique n'est pas critique a priori)
	Assert1("DequeAMORCER",bFrontiere8(1+kuDequeCardinalMaX));//ie un multiple de 8 est requis
	//caractériser la deque avec des valeurs aberrantes qui seront immanquablement dénoncées par les assertions.
		pDequE=0;
		nCarD=-kuDequeCardinalMaX;//cette valeur négative impropre déclenchera immanquablement une assertion si l'appel à DequeOuvrir() est oublié.
		sLasT=-kuDequeCardinalMaX;
		tModePileOuFilE=0;//ie le mode, pile ou file, est actuellement indéterminé.
	bDequeOuvertE=kF;//vital
	bDequeAmorceR=kV;
}//DequeAMORCER

int nDequeCardinal(){//O(1)
	int nCardinal=nCarD;
	Assert3("nDequeCardinal",bDequeAmorceR,bTrit(tModePileOuFilE),bCroit(0,nCardinal,nCardMaX));
	return(nCardinal);
}//nDequeCardinal

int bDequeContient(int sSommeT){//O(1)
	int bContient;
	Assert4("bDequeContient",bDequeAmorceR,bDequeOuvertE,bTrit(tModePileOuFilE),bCroit(1,sSommeT,nCardMaX));
	bContient=bCroit(1,sSommeT,nCardMaX) && (pDequE->sNexT[sSommeT]!=0);//ce code peut être plus concis. Mais est-ce plus clair?
	return(bContient);//le coût d'exécution des contrôles (ici, Assert3) dépasse le coût de la seule instruction "utile" (bContient=). C'est fréquent.
}//nDequeCardinal

void DequeDefiler(){//O(1)
	int iBof=sDequeDefiler();
	iBof++;
}//DequeDefiler

int sDequeDefiler(){//O(1)
	int sDefiler=0;
	Assert5("sDequeDefiler",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePileOuFilE<=0);
	tModePileOuFilE=-1;
	if (nCarD>0) {
		sDefiler=pDequE->sNexT[sLasT];//lit la tête de file
		pDequE->sNexT[sLasT]=pDequE->sNexT[sDefiler];
		pDequE->sNexT[sDefiler]=0;//vital vu les tests tels que "if (!sNexT[sSommeT])" ds DequeEmpiler
		nCarD--;
	}
	Assert2("sDequeDefiler",bCroit(1,sDefiler,kuDequeCardinalMaX),nCarD>=0);
	return(sDefiler);
}//sDequeDefiler

void DequeDepiler(){//O(1)
	int iBof=sDequeDepiler();
	iBof++;
}//DequeDepiler

int sDequeDepiler(){//O(1)
	int sDepiler=0;
	Assert5("sDequeDepiler",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePileOuFilE>=0);
	tModePileOuFilE=+1;
	if (nCarD>0) {
		sDepiler=pDequE->sNexT[sLasT];//lit le sommet de pile (alias la tête de file)
		pDequE->sNexT[sLasT]=pDequE->sNexT[sDepiler];
		pDequE->sNexT[sDepiler]=0;//vital vu les tests tels que "if (!sNexT[sSommeT])" ds DequeEmpiler
		nCarD--;
	}
	Assert2("sDequeDepiler",bCroit(1,sDepiler,kuDequeCardinalMaX),nCarD>=0);
	return(sDepiler);
}//sDequeDepiler

void DequeEmpiler(int sSommeT){//O(1)
	//empile sSommeT si celui-ci n'est pas déjà dans la deque
	//tee("nCardMaX,sSommeT à empiler",nCardMaX,sSommeT);
	Assert5("DequeEmpiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,kuDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX),tModePileOuFilE>=0);
	tModePileOuFilE=+1;
	if (!pDequE->sNexT[sSommeT]) {//le sommet en question,défini,ne figure pas déjà dans la deque ——allouée et non saturée vu Assert4()
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case mémoire disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
			sLasT=sSommeT;//seule différence avec le code de DequeEnfiler()
		}
	}
}//DequeEmpiler

int bDequeEmpiler(int sSommeT){//O(1)
	//rend vrai ssi sSommeT n'est pas déjà dans la deque;si sSommeT est effectivement absent, empile sSommet dans la deque. 
	int bEmpiler;
	Assert2("bDequeEmpiler",bDequeAmorceR,bDequeOuvertE);
	bEmpiler=!bDequeContient(sSommeT);
	if (bEmpiler)
		DequeEmpiler(sSommeT);
	return(bEmpiler);
}//bDequeEmpiler

void DequeEnfiler(int sSommeT){//O(1)
	//enfile sSommeT si celui-ci n'est pas déjà dans la deque
	Assert5("DequeEnfiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,kuDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX),tModePileOuFilE<=0);
	tModePileOuFilE=-1;
	if (!pDequE->sNexT[sSommeT]) {
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
		}
		sLasT=sSommeT;//seule différence avec le code de DequeEmpiler()
	}
}//DequeEnfiler

int bDequeEnfiler(int sSommeT){//O(1)
	//rend vrai ssi sSommeT n'est pas déjà dans la deque;si vrai, enfile sSommeT.
	Assert2("bDequeEnfiler",bDequeAmorceR,bDequeOuvertE);
	int bEnfiler=!bDequeContient(sSommeT);
	if(!bEnfiler)
		DequeEnfiler(sSommeT);
	return(bEnfiler);
}//bDequeEnfiler

void DequeINITIALISER(){//O(?)
	//relance le présent module
	Assert1("DequeINITIALISER0",bDequeAmorceR);
	if (bDequeOuvertE)
		DequeAllouer(0);
	Assert3("DequeINITIALISER1",bDequeAmorceR,!bDequeOuvertE,tModePileOuFilE==0);
}//DequeINITIALISER

void DequePileCopier(int nPile[]){//O( nDequeCardinal() )
	//recopie la deque courante utilisée en mode pile dans le vecteur nPile[1..] et copie le cardinal de la deque dans nPile[0] 
	Assert5("DequePileCopier",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,nCarD,nCardMaX),tModePileOuFilE>0);
	int uE;
	nPile[0]=nDequeCardinal();
	//d(nDequeCardinal());
	if (nPile[0]>0)
		nPile[1]=sDequeTete();
	for (uE=2;uE<=nPile[0];uE++)
		nPile[uE]=sDequeSuivant(nPile[uE-1]);
	Assert1("DequePileCopier",nPile[0]==nDequeCardinal());
}//DequePileCopier

int nDequeQuota(){
	Assert2("nDequeQuota",bDequeAmorceR,bDequeOuvertE);
	int nQuota=nCardMaX;
	return(nQuota);
}//nDequeQuota

int sDequeQueue(){//O(1)
	int sQueue=0;
	Assert5("sDequeQueue",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,nCarD,nCardMaX),tModePileOuFilE<0);
	if (nCarD>0)//ce test évite de retourner une valeur flottante (copie de LasT) au lieu d'une constante (0) quand les assertions sont désactivées
		sQueue=sLasT;
	Assert1("sDequeQueue",bCroit(1,sQueue,nCardMaX));
	return(sQueue);
}//sDequeQueue

void DequeRazer(int nCardinalMax){//O(nCardinalMax)
	int uS;
	Assert4("DequeRazer",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(0,nCardinalMax,nCardMaX));
	for (uS=1;uS<=nCardinalMax;uS++)
		pDequE->sNexT[uS]=0;
	nCarD=0;
	sLasT=0;
}//DequeRazer

int sDequeSommet(){//O(1)
	int sSommet;
	Assert5("sDequeSommet",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePileOuFilE!=0);
	sSommet=pDequE->sNexT[sLasT];
	Assert1("sDequeSommet",bCroit(1,sSommet,nCardMaX));
	return(sSommet);
}//sDequeSommet

int sDequeSuivant(int sX){//O(1)
	int sY;
	Assert3("sDequeSuivant0",bDequeAmorceR,bDequeOuvertE,bTrit(tModePileOuFilE));
	sY=pDequE->sNexT[sX];
	Assert1("sDequeSuivant1",bCroit(1,sY,nCardMaX));
	return(sY);
}//sDequeSuivant

void DequeTESTER(int iTest){
	//teste le présent module
	int sSource;
	Appel0(sC2("DequeTester,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:
				DequeAllouer(4);
					DequeVoir("Deque allouée et vide, censée être utilisée en mode pile.");
					DequeEmpiler(1);
					DequeEmpiler(2);
					DequeEmpiler(3);
					DequeVoirPile("Mode pile");
					DequeVoirFile("Mode pile");
					DequeVoirPile("Mode pile");
					DequeVoir("Deque pleine:");
					DequeVoirFile("Mode pile");
					DequeVoirPile("Mode pile");
					sSource=sDequeDepiler();
					te("Sommet dépilé",sSource);
					DequeVoir("Deque résultante:");
					sSource=sDequeDepiler();
					te("Sommet dépilé",sSource);
					DequeVoir("Deque finale:");
				DequeAllouer(0);
				DequeAllouer(12);
					DequeVoir("Deque allouée et vide, censée être utilisée en mode file.");
					DequeEnfiler(1);
					DequeEnfiler(2);
					DequeEnfiler(3);
					DequeVoirFile("Mode file");
					DequeVoirPile("Mode file");
					DequeVoir("Deque pleine:");
					DequeVoirPile("Mode file");
					DequeVoirFile("Mode file");
					sSource=sDequeDefiler();
					DequeVoir("Deque finale:");
				DequeINITIALISER();
				DequeAllouer(9);
					DequeEnfiler(7);
					DequeVoir("Deque réinitialisée:");
				DequeAllouer(0);
				break;
			default:
				DequeAllouer(12);
					DequeVoir("Deque vide");
					DequeEmpiler(5);
					DequeEnfiler(3);//déclenche une assertion car la deque censée implémenter une pile vu li-1 est utilisée maintenant en file.
				DequeAllouer(0);
				break;
		}
	Appel1(sC2("DequeTester,test n°",sEnt(iTest)));
}//DequeTESTER	

int sDequeTete(){//O(1)
	//défini sur pile et file
	int sTete;
	Assert5("sDequeTete",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,kuDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePileOuFilE!=0);
	sTete=pDequE->sNexT[sLasT];
	Assert1("sDequeTete",bCroit(1,sTete,nCardMaX));
	return(sTete);
}//sDequeTete

int bDequeVide(){//O(1)
	int bVide;
	Assert5("bDequeVide",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,kuDequeCardinalMaX),bCroit(0,nCarD,nCardMaX),bTrit(tModePileOuFilE));
	bVide=(nCarD==0);
	return(bVide);//exemple de routine où les contrôles (ici, des assertions) sont plus coûteux que le code utile.
}//bDequeVide

void DequeVoir(char *sMessage){//O(nCardMaX)
	int uS;
	Assert3("DequeVoir",bDequeAmorceR,bDequeOuvertE,sMessage!=0);
	printf("%s\n",sMessage);
	if (0){//afficher nCarD après affichage des index de sNexT[]
		printf("index = ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",uS);
		printf("  nCarD=%d\n",nCarD);
	}
	//afficher sLasT après affichage des valeurs de sNexT[]
		printf("valeur= ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d",pDequE->sNexT[uS]);
		printf("  sLasT=%d\n",sLasT);
}//DequeVoir

void DequeVoirFile(char *sMessage){//O(taille courante de la deque)
	//affiche la deque comme une file d'attente en commençant par la queue de file. Pour afficher en ordre inverse, appeler DequeVoirPile().
	int nCardinal,uS;
	int nFile[1+nCardMaX];
	int tMode;
	Assert4("DequeVoirFile",bDequeAmorceR,bDequeOuvertE,sMessage!=0,bTrit(tModePileOuFilE));
	printf("%s ",sMessage);
	//DequeVoir("AVANT");
		tMode=tModePileOuFilE;
			for (nCardinal=nDequeCardinal(),uS=1;uS<=nCardinal;uS++){
				tModePileOuFilE=0;//neutralise le mode courant afin de défiler même en mode pile
				nFile[uS]=sDequeDefiler();
			}
			//afficher la file stockée dans nFile[]
				//printf("Deque depuis la queue de file: ");
				for (uS=1;uS<=nCardinal;uS++)
					printf("%d%s",nFile[uS],(uS<=nCardinal)? ",":".");
				printf(" (%s)\n",sPluriel(nCardinal,"élément"));
			//reconstituer la file
				for (uS=1;uS<=nCardinal;uS++){
					tModePileOuFilE=0;
					DequeEnfiler(nFile[uS]);
				}
		tModePileOuFilE=tMode;//restaure le mode courant
	//DequeVoir("APRES");
}//DequeVoirFile

void DequeVoirPile(char *sMessage){//O(taille courante de la deque)
	//affiche la deque comme une pile en commençant par le sommet de pile. Pour afficher en ordre inverse, appeler DequeVoirFile().
	int nCardinal,uS;
	int nPile[1+nCardMaX];
	int tMode;
	Assert4("DequeVoirEnPile",bDequeAmorceR,bDequeOuvertE,sMessage!=0,bTrit(tModePileOuFilE));
	printf("%s",sMessage);
	//DequeVoir("AVANT");
		tMode=tModePileOuFilE;
			for (nCardinal=nDequeCardinal(),uS=1;uS<=nCardinal;uS++){
				tModePileOuFilE=0;//neutralise le mode courant afin de dépiler même en mode file
				nPile[uS]=sDequeDepiler();
			}
			//afficher la pile stockée dans nPile[]
				//printf("Deque depuis le fond de pile: ");
				for (uS=nCardinal;uS>=1;uS--)
					printf("%2d%s",nPile[uS]-8,(uS>1)?",":".");
				printf(" (%s)\n",sPluriel(nCardinal,"élément"));
			//reconstituer la pile
				for (uS=nCardinal;uS>=1;uS--){
					tModePileOuFilE=0;
					DequeEmpiler(nPile[uS]);
				}
		tModePileOuFilE=tMode;//restaure le mode courant
	//DequeVoir("APRES");
}//DequeVoirPile


