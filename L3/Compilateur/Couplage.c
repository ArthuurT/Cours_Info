#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Couplage.h"
#include "Flot.h"
#include "Ticket.h"
//Ce module calcule un couplage maximal en temps O(S3) sur un graphe simple symétrique G (accès: pgG).
//Points pas clairs:cf ???
//L'algorithme génère des graphes G' successifs: G'(1),G'(2),etc où G'(p) est G contracté p fois, une fois par orbite créée.
//Variables de modules ——leur usage évite de créer les graphes successifs G'(i), ce qui réduit considérablt le temps d'exécution:
	int ukSommetMaX;//nombre de sommets de G,égal à pgG->nSommetEnTout, constant pendant la recherche de couplage.
	int sPseudoSommetMaX;//rang du plus grand sommet de G',égal à ukSommetMaX augmenté du nombre courant d'orbites créées.
	int alpha[kuGrapheSommetLim];//n° du 1er pseudo-sommet (dans l'ordre de formation des pseudo-sommets) ctenant sX, ou, à défaut, sX lui-même.
	int beta[kuGrapheSommetLim];//n° du 1er pseudo-sommet externe associé à sX, ou sX à défaut; il couvre sX.
	int marq[kuGrapheSommetLim];//nul si sX pair.Sinon,marq[sX]=n° vrai sommet i au bout de l'arête utilisée pr marquer k depuis j=beta[i]=beta[marq[k]]
	int couplaj[kuGrapheSommetLim];//couplaj[sX]=sY et couplaj[sY]=sX signifie que (sX,sY) est une arête du couplage; et nul si sX est non couplé.
	int s[kuGrapheSommetLim];//si k pseudo-sommet "impair",s[k]=l=vrai sommet ds k au bout de l'arête (fine) ayant permis de marquer k (pt de ctact).
							 //si k est un vrai sommet,ie beta[k]=k,on pose s[k]=k. Enfin,s[k]=0 ssi k est un pseudo-sommet pair.
	int arbralt[kuGrapheSommetLim];//ensemble Y des sommets de l'arbre alterné courant.
	int arbraltpair[kuGrapheSommetLim];//ensemble Y° des sommets pairs de l'arbre alterné courant.
	//NB Chaque sommet (vrai ou pseudo) figure au plus une fois dans une orbite et l'intersection de deux orbites qcq est vide.
	//NB Puisqu'une orbite contient au moins deux sommets, la somme "sommets + pseudo-sommets" est bornée par 3S/2 pr S sommets.
	//si k est un pseudo-sommet,couplaj[k] est le n° du vrai sommet i extrémité de l'arête du couplage incidente à k et non contenu dans k (p276).
	//un sommet est pair (resp. impair) s'il est ds l'arbre et si le chemin vers la racine (paire) a un nombre pair (resp. impair) d'arêtes.
const int kbTickeT=kV;//Le mode lent,ie sans ticket, égrène les arêtes en O(A2), vs O(S2) en mode rapide. En effet, grâce au module Ticket:
	//1° Chaque arête est scrutée au plus 2 fois. 2° La liste des sommets est initialisée en O(S2) puis accédée O(S2) fois en O(1), cf Ticket.h.
const int kbTicketVoiR=kF;
const int k1MemeSiNuL=kV;
int bAretE[kuGrapheArcLim];//dédié !kbTickeT,ie mode LENT.
int nlAreteChoiX;//cptH de cplexT, cf notO de Landau, pr cparer les performances de nAreteChoisirRapidE() et nAreteChoisirLenT() appelées selon kbTickeT 
int bCouplageAmorceR;//vrai ssi le présent module a été amorcé
void *pTickeT[kuGrapheSommetLim];//pointeurs sur les 1+pgG->nSommetEnTout listes de tickets indispensables au mode rapide (ie kbTickeT=kV)

int bArbreAlternehAugmenteR(graf *pgG,int sRacinePaire,int *psFeuille,int *pnlAreteEnTout);//O(S2) en mode rapide vs //O(S3) en mode lent
void ArbreAlternehEnracineR(graf *pgG,int sRacine);//O(S)
int nAreteChoisiR(graf *pgG,int sOrigine,int *psI,int *psJ);//O(1) amorti en mode rapide vs //O(S2) en mode lent
int nAreteChoisirLenT(graf *pgG,int *psBout0,int *psBout1);//O(S)
int nAreteChoisirRapidE(graf *pgG,int sOrigine,int *psBout0,int *psBout1);//O(S)
void AreteExtrairE(graf *pgG,int sBout0,int sBout1,int nContexte);//O(1) en mode rapide vs //O(S2) en mode lent
void CouplageMaximiserMemeSiNonBipartI(graf *pgG);//O(S3) en mode rapide vs //O(S4) en mode lent
void CouplageParfaitListeR(graf *pgG);//O(exponentiel)
int bCouplagePonderehOptimiseR(graf *pgG,int bMaximum,int bVoir,int bInterface[]);//O(S2A)
void CouplageCertifieR(graf *pgG);//O(A)
int bCouplageCompleT(graf *pgG);//O(S)
void CouplageCourtCircuiteR(graf *pgG);//O(A)
void CouplageVoiR(char *sMessage,graf *pgG,int bMemeSiNul);
void CouplageVoiR2(char *sMessage,graf *pgG,int bMemeSiNul,int bPoids,int nPoidsMaximum);
void GrapheReduirE(graf *pgG);//O(A)
void OrbiteEclateR(graf *pgG);//O(S)
int sOrbiteEclaterUN(graf *pgG,int sOrbite);//O(S)
void OrbiteEclaterDEUX(graf *pgG,int sOrbite);//O(S)
void OrbiteEclaterTROIS(graf *pgG,int sOrbite,int sK1);//O(S)
int sSommetConfluenT(graf *pgG,int sRacine,int sIpair,int sJpair,int *pnLgDepuisIpair,int *pnLgDepuisJpair);//O(S)
void SommetConflueR(int sFourchePrim,int sIpair,int sJpair,int nEtapeMax);//O(nEtapeMax), dc O(S)
int nSommetInsatureH(graf *pgG,int *psRacine);//O(S)
int nSommetInsaturehNonMarqueH(graf *pgG);//O(S)
int bSommetMarqueH(graf *pgG,int sEnquis);//O(1)
int bSommetOrbitaL(graf *pgG,int sSommet);//O(1)
int bSommetOriginaL(graf *pgG,int sSommet);//O(1)
int bSommetPaiR(graf *pgG,int sEnquis);//O(1)
int bSommetSatureH(graf *pgG,int sEnquis);//O(1)
int sSommetSatureH(graf *pgG,int sAutreBout);//O(1)
void StructureVoiR(char *sMessage);
void TransfertSurChaineAlternehDeLongueurImpairE(graf *pgG,int sK);//O(S)
void TransfertSurChaineAlternehDeLongueurPairE(graf *pgG,int sK,int sK0bout);//O(S)
void TycketAfficherTouT(graf *pgG);//O(S2)
void TycketAllouerTouT(int bAllouer,graf *pgG);//O(S2)

int bArbreAlternehAugmenteR(graf *pgG,int sRacinePaire,int *psFeuille,int *pnlAreteEnTout){//O(S2) en mode rapide vs //O(S3) en mode lent
	//Cstruit un arbre de racine sRacinePaire en arborant de nouvelles arêtes; vrai ssi cet arbre ctient une chaîne alternée augmentante.
	const int bDire=kF;
	int bAugmenter=kF;
	int nChoix,nLgDepuisIpair,nLgDepuisJpair;
	int sI,sIprim,sJ,sJprim,sK,sKprim,sL,sOrigine;
	int sFourchePrim,sX;
	//Appel0(sC2("bArbreAlternehAugmenteR",sEnt(sRacinePaire)));
	Assert1("bArbreAlternehAugmenteR0",arbralt[sRacinePaire]==1);
	if (bDire) printf("Appel de bArbreAlternehAugmenteR pour construire un arbre alterné de racine %d.\n",sRacinePaire);
		sPseudoSommetMaX=pgG->nSommetEnTout;
		sOrigine=beta[sRacinePaire];
		//la valeur courante de pnlAreteEnTout sera incrémentée à chaque itération en li+3
		do{//li+1,choisir une arête convenable,ie de nChoix non nul, auquel cas (sI,sJ) est extraite sur-le-champ  par AreteExtrairE() depuis nAreteChoisiR.
			nChoix=nAreteChoisiR(pgG,sOrigine,&sI,&sJ);//O(1) amorti,en mode rapide,vs //O(S2) en mode lent
			(*pnlAreteEnTout)+=1;//si nChoix>0, une nouvelle arête u=(sI,sJ) a été choisie avec succès
			if (bDire) printf("Arête %s pour le choix n°%d (tour n°%d,racine %d):\n",sCouple(sI,sJ),nChoix,*pnlAreteEnTout,sRacinePaire);
			switch (nChoix) {
				case 1:	//sI est un sommet pair et sJ est un sommet INSATURÉ et non marqué (ie arbralt[sJ] est nul).
							sIprim=beta[sI];//beta[sI] est le n° du 1er pseudo-sommet externe associé à sI; il couvre le vrai sommet sI.
							sJprim=beta[sJ];
							//d3(nChoix,sIprim,sJprim);
							Assert3("bArbreAlternehAugmenteR1",bSommetPaiR(pgG,sIprim),!bSommetSatureH(pgG,sJprim),!bSommetMarqueH(pgG,sJprim));//O(1)
							//ajouter (sIprim,sJprim) à l'arbre courant 
								marq[sJprim]=sI;//ie sI est le n° du vrai sommet,au bout de l'arête (sI,sJ),utilisé pr marquer sJprim depuis sJ.
								Assert1("bArbreAlternehAugmenteR11",sJprim==sJ);
								s[sJprim]=sJ;//sJprim n'est pas un pseudo-sommet mais est un vrai sommet, donc on effectue s[sJprim]=sJ
								arbralt[sJprim]=1;//marque sJprim ——et arbraltpair[sJprim]=0 puisque sJprim est un sommet impair.
							//CouplageVoiR("Couplage après nChoix n°1",pgG,k1MemeSiNuL);
							break;
				case 2:	//sI est un sommet pair et sJ est un sommet SATURÉ et non marqué (ie arbralt[sJ] est nul).
							sIprim=beta[sI];
							sJprim=beta[sJ];
							//d3(sIprim,sJprim,nChoix);
							Assert3("bArbreAlternehAugmenteR2",bSommetPaiR(pgG,sIprim),bSommetSatureH(pgG,sJprim),!bSommetMarqueH(pgG,sJprim));//O(1)
							//ajouter d'abord l'arête (sIprim,sJprim) à l'arbre courant (comme ds le case 1) 
								marq[sJprim]=sI;//ie sI est le n° du vrai sommet au bout de l'arête (sI,sJ) utilisé pr marquer sJprim depuis sJ.
								Assert1("bArbreAlternehAugmenteR11",sJprim==sJ);
								s[sJprim]=sJ;//sJprim n'est pas un pseudo-sommet mais est un vrai sommet, donc on effectue s[sJprim]=sJ
								arbralt[sJprim]=1;//marque sJprim ——et arbraltpair[sJprim]=0 puisque sJprim est un sommet impair.
							//soit u'=(sJ,sK) l'arête du couplage incidente à sJ et donc adjacente à et au-delà de (sI,sJ).
								sK=sSommetSatureH(pgG,sJ);//tjrs défini: sJ est un sommet du couplage,dc celui-ci contient nécessairt un (sJ,sK)
								//d2(sJ,sK);
								Assert2("bArbreAlternehAugmenteR20",couplaj[sJ]==sK,couplaj[sK]==sJ);//(sJ,sK) est bien une arête du couplage courant
								//retirer (sJ,sK) des arêtes utilisB pour cstruire l'arbre alterné,puisq (sJ,sK) vient d'être utilisée ci-dessus
									//AreteExtrairE(pgG,sJ,sK,3);//O(1) en mode rapide vs //O(S2) en mode lent
							if (bDire) printf ("Case 2: ajout de deux arêtes %s et %s.\n",sCouple(sI,sJ),sCouple(sJ,sK));
							//l'arête u=(sL,sK) joint dans G' les sommets non marqués sJprim=beta[sJ]=beta[sL] et sKprim=beta[sK]=beta[couplaj[sJprim]].
							Assert1("bArbreAlternehAugmenteR22",couplaj[sJprim]==sK);
							couplaj[sJprim]=sK;
							Assert1("bArbreAlternehAugmenteRcase 24:",sK>0);
							sL=couplaj[sK];
							Assert2("bArbreAlternehAugmenteRcase 26:",sL>0,sL==sJ);
							sKprim=beta[sK];
							//marquer sKprim pair
								arbralt[sKprim]=1;arbraltpair[sKprim]=1;
							//VecteurVoir("    y",y,1,pgG->nSommetEnTout);
							//VecteurVoir("arbraltpair",arbraltpair,1,pgG->nSommetEnTout);
							//CouplageVoiR("Couplage après Cas n°2",pgG,k1MemeSiNuL);
							break;
				case 3: //sI est un sommet pair et sJ est égalt un sommet pair.
			//StructureVoiR("AVANT case 3");
							//L'arête u=(sI,sJ) joint les deux sommets "pairs" beta[sI] et beta[sJ] de G'=G(p-1)
							//sFourchePrim:=1er sommet commun aux chaînes alternées qui remontent de beta[sI] et beta[sJ] à sRacinePaire 
								sFourchePrim=sSommetConfluenT(pgG,sRacinePaire,sI,sJ,&nLgDepuisIpair,&nLgDepuisJpair);//O(S)
								//d3(sFourchePrim,beta[sI],beta[sJ]);
							//CouplageVoiR("Couplage après nChoix n°3",pgG,k1MemeSiNuL);
							//sPseudoSommetMaX++ soit la nouvelle orbite qui englobe sFourchePrim,beta[sI] et beta[sJ].
								Assert1("bArbreAlternehAugmenteR123",sPseudoSommetMaX+1<kuGrapheSommetLim);
								sPseudoSommetMaX++;
								beta[sPseudoSommetMaX]=sPseudoSommetMaX;
								alpha[sPseudoSommetMaX]=sPseudoSommetMaX;
if (bDire) teee("******************** Case 3,nLgDepuisIpair,nLgDepuisJpair,Taille de l'orbite",nLgDepuisIpair,nLgDepuisJpair,nLgDepuisIpair+nLgDepuisJpair);
	Assert1("bArbreAlternehAugmenteR Pour debugger",nLgDepuisIpair+nLgDepuisJpair<=3);//pr debugger ce qui se passe ds cycle non triangulR
							//Répercuter la formation de l'orbite de rang1 sPseudoSommetMaX dans les champs de la structure
								SommetConflueR(sFourchePrim,sI,sJ,nLgDepuisIpair);//actualise sur le chemin alpha[],marq[],s[] et arbraltpair[]
								SommetConflueR(sFourchePrim,sJ,sI,nLgDepuisJpair);//actualise sur le chemin alpha[],marq[],s[] et arbraltpair[]
								Assert1("bArbreAlternehAugmenteR9999",alpha[sFourchePrim]==sPseudoSommetMaX);//???
								//sPseudoSommetMaX soit déclaré "pair",et inclus ds le couplage étendu aux pseudo-sommets: 
									arbralt[sPseudoSommetMaX]=arbraltpair[sPseudoSommetMaX]=1;
									couplaj[sPseudoSommetMaX]=couplaj[sFourchePrim];
								//beta[] soit actualisé pr ts les pseudo-sommets externes
									for (sX=1;sX<=sPseudoSommetMaX;sX++)
										beta[sX]=alpha[beta[sX]];
			//StructureVoiR("après case 3");
							break;
				default:	//aucun sommet ne peut être marqué et aucune nouvelle orbite ne peut être créée.
							//Titrer("bArbreAlternehAugmenteR: Case default");
							//teee("nChoix,sIprim,sJprim*****************************",nChoix,sIprim,sJprim);
							break;
			}
			sOrigine=sI;
		}while( nChoix>1 ); 
	//Appel1(sC2("bArbreAlternehAugmenteR",sEnt(sRacinePaire)));
	bAugmenter=(nChoix==1);
	*psFeuille=sJ;
	Assert1("cArbreAlternehContruirE9",bBool(bAugmenter));
	return(bAugmenter);
}//bArbreAlternehAugmenteR

void ArbreAlternehEnracineR(graf *pgG,int sRacine){//O(S)
	//génère un arbre alterneh réduit à sRacine et initialise tous les tableaux utilisés pour sa construction, couplaj excepté.
	int sX;
	//marq[sX]=0 
		VecteurRazer(marq,1,pgG->nSommetEnTout);
	//alpha[]:=beta[]:=sX pour tout sX de G
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			alpha[sX]=beta[sX]=sX;
	//s[]:=sX pour tout sX de G cf p278 s[i]=i <=> vrai sommet
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			s[sX]=sX;
	//arbralt=arbraltpair={sRacine}
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			arbralt[sX]=arbraltpair[sX]=0;
		arbralt[sRacine]=arbraltpair[sRacine]=1;
	//G'=G
		sPseudoSommetMaX=pgG->nSommetEnTout;
}//ArbreAlternehEnracineR

int nAreteChoisiR(graf *pgG,int sOrigine,int *psI,int *psJ){//O(1) amorti en mode rapide vs //O(S2) en mode lent
	//rend si possible une nouvelle arête A=(*psI,*psJ);renvoie 0 si A n'existe pas,ou le type de A sinon, auquel cas A est EXTRAITE.
	const int bVoir=kF;
	int nChoix,bEncore,nTour;
	int sPivot0,sPivot=sOrigine;
	int bDito[1+pgG->nSommetEnTout];
	//NB le choix,ci-dessous,de la routine qui sélectionne une arête impacte fortt le nombre et la forme des arbres alternés qui seront construits.
	if (bVoir) Appel0("nAreteChoisiR");
		if (kbTickeT){
			sPivot=sOrigine;
			nTour=0;
			VecteurRazer(bDito,1,pgG->nSommetEnTout);
			do{
				nTour++;
				if (bVoir) d2(nTour,sOrigine);
				//nChoix=0;
				//if (bTicketContient(pTickeT[0],sPivot) && nTicketCardinal(pTickeT[sPivot]))
					nChoix=nAreteChoisirRapidE(pgG,sPivot,psI,psJ);//O(1)
				bEncore=nChoix==0;//si échec, aucune arête ayant sPivot pr extrémité n'est disponible.
				if (bVoir) d2(nChoix,bEncore);
				if (bEncore){
					bDito[sPivot]=kV;
					if (0 && kbTicketVoiR)
						TicketVoir("pTickeT[0]",pTickeT[0]);//O(S)
					bEncore=nTicketCardinal(pTickeT[0])>0;//O(1)
					if (bEncore){//changer de pivot;défini vu bEncore: Au moins une arête est encore présente dans le module Ticket
						if (bVoir) TicketVisionner("AVANT uTicketSuivant",pTickeT[0]);
						sPivot0=sPivot;
						sPivot=uTicketSuivant(pTickeT[0]);//O(1)
						if (bVoir) d2(sPivot0,sPivot);
						bEncore=!bDito[sPivot];
					}
				}
			}while (bEncore);//épuise les arêtes disponibles
		}else nChoix=nAreteChoisirLenT(pgG,psI,psJ);//O(S2)
		if (bVoir) 
			printf("%sChoix de l'arête %s dans la configuration %s.\n",sTab(14),sCouple(*psI,*psJ),(nChoix<3)? sC2("n°",sEnt(nChoix)): "TROIS");
		Assert1("nAreteChoisiR",bCroit(0,nChoix,3));
	if (bVoir) Appel1("nAreteChoisiR");
	return(nChoix);
}//nAreteChoisiR

int nAreteChoisirLenT(graf *pgG,int *psBout0,int *psBout1){//O(S2)
	//rend (*psBout0,*psBout1) s'il existe une telle arête en commençant par le cas i.
	int nChoisirLent=0;
	int aK,sX,sY;
	if (nChoisirLent==0)//balayer toutes les arêtes non encore utilisées pour le marquage pour trouver un cas 1
		for (sX=1;sX<=pgG->nSommetEnTout && nChoisirLent==0;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1] && nChoisirLent==0;nlAreteChoiX++,aK++){
				sY=pgG->sSuk[aK];
				if (bAretE[aK]==0 && bSommetPaiR(pgG,beta[sX]) && !bSommetSatureH(pgG,sY) && !bSommetMarqueH(pgG,sY) ){
					nChoisirLent=1;*psBout0=sX;*psBout1=sY;AreteExtrairE(pgG,sX,sY,1);//O(1) en mode rapide vs //O(S2) en mode lent
				}
			}
	if (nChoisirLent==0)//balayer toutes les arêtes non encore utilisées pour le marquage pour trouver un cas 2
		for (sX=1;sX<=pgG->nSommetEnTout && nChoisirLent==0;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1] && nChoisirLent==0;nlAreteChoiX++,aK++){
				sY=pgG->sSuk[aK];
				if (bAretE[aK]==0 && bSommetPaiR(pgG,sX) && bSommetSatureH(pgG,sY) && !bSommetMarqueH(pgG,sY) ){
					nChoisirLent=2;*psBout0=sX;*psBout1=sY;AreteExtrairE(pgG,sX,sY,1);//O(1) en mode rapide vs //O(S2) en mode lent
				}
			}
	if (nChoisirLent==0)//balayer toutes les arêtes non encore utilisées pour le marquage pour trouver un cas 3
		for (sX=1;sX<=pgG->nSommetEnTout && nChoisirLent==0;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1] && nChoisirLent==0;nlAreteChoiX++,aK++)
				sY=pgG->sSuk[aK];
				if (bAretE[aK]==0 && bSommetMarqueH(pgG,sX) && bSommetPaiR(pgG,beta[sX]) && bSommetMarqueH(pgG,sY) && bSommetPaiR(pgG,beta[sY]) ){
					nChoisirLent=3;*psBout0=sX;*psBout1=sY;AreteExtrairE(pgG,sX,sY,1);//O(1) en mode rapide vs //O(S2) en mode lent
				}
			}
	//te(sC3b("Arete sélectionnée",sCouple(*psBout0,*psBout1),"pour le cas n°"),nChoisirLent);
	switch (nChoisirLent) {
		case 1:	Assert3("nAreteChoisirLenT1",bSommetPaiR(pgG,beta[*psBout0]),!bSommetSatureH(pgG,*psBout1),!bSommetMarqueH(pgG,*psBout1));
				break;
		case 2:	Assert3("nAreteChoisirLenT2",bSommetPaiR(pgG,beta[*psBout0]),!bSommetMarqueH(pgG,*psBout1),bSommetSatureH(pgG,*psBout1));
				break;
		case 3:	Assert3("nAreteChoisirLenT3",bSommetPaiR(pgG,beta[*psBout0]), bSommetMarqueH(pgG,*psBout1),bSommetPaiR(pgG,beta[*psBout1]));
				break;
		default:break;
	}
	Assert1("nAreteChoisirLenT9",bCroit(0,nChoisirLent,3));
	return(nChoisirLent);
}//nAreteChoisirLenT

int nAreteChoisirRapidE(graf *pgG,int sOrigine,int *psBout0,int *psBout1){//O(S)
	//rend si possible 1 arête extraite (*psBout0,*psBout1) configurée 1, sinon 2, sinon 3, ds cet ordre. Rend la cfiguration>0, ou 0 si échec.
	int nChoisirRapide;
	int nConfiguration;
	int sX,sY;
	int bMarqueh,bSatureh;
	if (0){
		VecteurVoir("+++++++ arbralt",arbralt,1,pgG->nSommetEnTout);
		VecteurVoir("++ arbraltpair",arbraltpair,1,pgG->nSommetEnTout);
	}
	nChoisirRapide=nConfiguration=0;//d
	sX=sOrigine;
	Assert1("nAreteChoisirRapidE",kbTickeT);
	//te("nAreteChoisirRapidE:sOrigine",sOrigine);
	if (nTicketCardinal(pTickeT[sX])>0){//test en O(1)
		if ( nlAreteChoiX++, bSommetPaiR(pgG,beta[sX]) ){
			do{
				sY=uTicketSuivant(pTickeT[sX]);//O(1)
				bMarqueh=bSommetMarqueH(pgG,sY);//O(1)
				bSatureh=bSommetSatureH(pgG,sY);//O(1)
				if ( !bMarqueh )
					nConfiguration=1+bSatureh;//configurations 1 et 2
				else if ( bSommetPaiR(pgG,beta[sY]) )//O(1)
					nConfiguration=3;//configuration 3
			} while (nConfiguration==0);
			if (nConfiguration>0){
				Assert3("nAreteChoisirRapidE0",bCroit(1,sX,pgG->nSommetEnTout),bCroit(1,sY,pgG->nSommetEnTout),sX!=sY);//vu graphe simple
				*psBout0=sX;*psBout1=sY;
				AreteExtrairE(pgG,sX,sY,2);//O(1) en mode rapide
				nChoisirRapide=nConfiguration;
			}
		}
	}//if
	//te(sC3b("Arete sélectionnée",sCouple(*psBout0,*psBout1),"pour le cas"),nChoisirRapide);
	switch (nChoisirRapide) {//O(1)
		case 1:	Assert3("nAreteChoisirRapidE1",bSommetPaiR(pgG,beta[*psBout0]),!bSommetSatureH(pgG,*psBout1),!bSommetMarqueH(pgG,*psBout1));
				break;
		case 2:	Assert3("nAreteChoisirRapidE2",bSommetPaiR(pgG,beta[*psBout0]),!bSommetMarqueH(pgG,*psBout1),bSommetSatureH(pgG,*psBout1));
				break;
		case 3:	Assert3("nAreteChoisirRapidE3",bSommetPaiR(pgG,beta[*psBout0]), bSommetMarqueH(pgG,*psBout1),bSommetPaiR(pgG,beta[*psBout1]));
				break;
		default:break;
	}
	Assert1("nAreteChoisir9",bCroit(0,nChoisirRapide,3));
	return(nChoisirRapide);
}//nAreteChoisirRapidE

void AreteExtrairE(graf *pgG,int sBout0,int sBout1,int nContexte){//O(1) en mode rapide vs //O(S2) en mode lent
	//retire définitivt (sBout0,sBout1) de la liste des arêtes utilisables pour construire un arbre de chaînes alternées
	int aK;
	//printf("    Choix et retrait de l'arête %s en contexte %d.\n",sCouple(sBout0,sBout1),nContexte);
	if (kbTickeT){
		TicketRetirer0(pTickeT[0],sBout0,pTickeT[sBout0],sBout1);//O(1)
		TicketRetirer0(pTickeT[0],sBout1,pTickeT[sBout1],sBout0);//O(1)
		if (nContexte>0)
			TycketAfficherTouT(pgG);
	}else {
		aK=nGrapheArc(pgG,sBout0,sBout1);//O(S2) ——on pourrait faire mieux, mais pas mieux que le module Ticket. 
		bAretE[aK]=1;
		aK=nGrapheArc(pgG,sBout1,sBout0);//O(S2) ——on pourrait faire mieux, mais pas mieux que le module Ticket.
		bAretE[aK]=1;
	}
}//AreteExtrairE

void CouplageAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bCouplageAmorceR=kV;
}//CouplageAMORCER

void CouplageCertifieR(graf *pgG){//O(A)
	//vérifie que le couplage courant de pgG a bien du sens sachant que pgG est réputé symétrique
	const int kbAuthentifier=kF;
	int bValide;
	int aK,sX,sY;
	int nSommet[1+1][1+pgG->nSommetEnTout];
	//GrapheVoir0(pgG,"CouplageCertifieR",grCouleur);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
		nSommet[0][sX]=nSommet[1][sX]=0;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			if (pgG->coulh[aK]>0) {
				nSommet[sX<sY][sX]++;
				nSommet[sX<sY][sY]++;
			}
		}
	if (kbAuthentifier) VecteurVoir("CouplageAuthentifieR0",nSommet[0],1,pgG->nSommetEnTout);//O(S)
	if (kbAuthentifier) VecteurVoir("CouplageAuthentifieR1",nSommet[1],1,pgG->nSommetEnTout);//O(S)
	//bValide:=pgG est symétrique et les arêtes du couplage spécifié par "pgG->coulh[aK]>0" sont effectivement disjointes
		bValide=bGrapheSymetrique(pgG);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
			bValide=bValide && nSommet[0][sX]<=1 && nSommet[0][sX]==nSommet[1][sX];
	Assert1("CouplageCertifieR",bValide);
}//CouplageCertifieR

int bCouplageCompleT(graf *pgG){//O(S)
	int bComplet,nCouplage=0;
	for (int sX=1;sX<=pgG->nSommetEnTout;sX++)
		if (couplaj[sX])
			nCouplage++;
	bComplet=nCouplage==pgG->nSommetEnTout;
	return(bComplet);
}//bCouplageCompleT

void CouplageCourtCircuiteR(graf *pgG){//O(A)
	//initialise le couplage en prenant d'emblée les arêtes définies par "pgG->coulh[aK]>0" ssi "aK est une arête du couplage".
	int aK,sX,sY;
	Assert1("CouplageCourtCircuiteR",bGrapheSymetrique(pgG));
	//Appel0("CouplageCourtCircuiteR");
		CouplageCertifieR(pgG);//ie le couplage défini par "pgG->coulh[aK]>0" a du sens (les arêtes sont bien disjointes).
		VecteurRazer(bAretE,1,pgG->nArcEnTout);
		VecteurRazer(couplaj,1,pgG->nSommetEnTout);
		VecteurValuer(pgG->sPer,1,pgG->nSommetEnTout,1);//u/réduction du graphe
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (pgG->coulh[aK]>0){
					couplaj[sY]=sX;
					if (sX<sY)
						AreteExtrairE(pgG,sX,sY,0);
				}
			}
		if (kbTickeT)
			TycketAfficherTouT(pgG);
	//Appel1("CouplageCourtCircuiteR");
}//CouplageCourtCircuiteR

void CouplageParfaitListeR(graf *pgG){//O(exponentiel)
	//affiche tous les couplages parfaits de pgG;
	int aK,sX,sY;
	int iCouplage,bCouplageParfait,nParfait,nPoids;
	long zAccu,zCas,zCasEnTout;
	int bConfig[1+pgG->nArcEnTout];
	Assert1("CouplageParfaitListeR",bCouplageAmorceR);
	Appel0("CouplageParfaitListeR");
		zCasEnTout=zPuissance(2,pgG->nArcEnTout);
		printf("zCasEnTout: %s.\n",sPar3(zCasEnTout));
		for (nParfait=0,zCas=zCasEnTout-1;zCas>=0;zCas--){
			//bConfig[]:=configuration de bits associée à zCas
				for (zAccu=zCas,aK=1;aK<=pgG->nArcEnTout;aK++){
					bConfig[pgG->nArcEnTout-aK+1]=zAccu%2;
					zAccu=zAccu/2;
				}
				//VecteurVoir("bConfig",bConfig,1,pgG->nArcEnTout);
			//couplaj:=couplages associés au tirage zCas et iCouplage:=nb total de couplages,ou <=0 si conflit de couplage
				VecteurRazer(couplaj,1,pgG->nArcEnTout);
				for (iCouplage=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						if (bConfig[aK]){
							sY=pgG->sSuk[aK];
							if (couplaj[sX]==0 && couplaj[sY]==0){
								couplaj[sY]=sX;couplaj[sX]=sY;iCouplage++;
							}else iCouplage=kiIntegerMin;
						}
			bCouplageParfait=(iCouplage==pgG->nSommetEnTout/2);
			//te("iCouplage",iCouplage);
			if (bCouplageParfait){//afficher le couplage parfait
				printf("Couplage parfait n°%d:",++nParfait);
				for (nPoids=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (sX<couplaj[sX]){
						printf(" %s",sCouple(sX,couplaj[sX]));
						aK=nGrapheArc(pgG,sX,couplaj[sX]);
						nPoids+=pgG->nCout[aK];
						//couplaj[sX]=0;
					}
				printf(" poids %d.\n",nPoids);
			}
		}// for nParfait
	Appel1("CouplageParfaitListeR");
}//CouplageParfaitListeR

void CouplageINITIALISER(){//O(?)
	//relance le présent module
	Assert1("CouplageINITIALISER",bCouplageAmorceR);
}//CouplageINITIALISER

void CouplageHongroisMaximiseR(graf *pgSource){
	//Maximise le couplage pondéré dans pgSource quasi non symétrique
	int knCapaciteMinimaleNulle=0,knCapaciteMaximale=1,knPoids=1;
	int sC,sL,cPasse,aK,sX,sY;
	graf *pgG;
	int sOrigine[kuGrapheArcLim];//excessif
	int nSommet,nSommetInterfacable;
	Appel0("CouplageHongroisMaximiseR");
		GrapheCreer0(&pgG,kV);
		for (nSommet=2*pgSource->nSommetEnTout,cPasse=0;cPasse<=1;cPasse++){
			if (cPasse>0){//pgG soit initialt un graphe à nSommet sommets et aucun arc
				pgG->nSommetEnTout=nSommet;	//te("pgG->nSommetEnTout",pgG->nSommetEnTout);
				for (sX=1;sX<=pgG->nSommetEnTout+1;sX++)
					pgG->aHed[sX]=1;
				pgG->nArcEnTout=0;	//tb("bGraphe(pgG)",bGraphe(pgG));
				nSommet=2*pgSource->nSommetEnTout;
			}
			//pour chaque arc de pgSource,ajouter (virtuellt si cPasse est nul) 3 arcs à pgG 
				for (sX=1;sX<=pgSource->nSommetEnTout;sX++)
					for (aK=pgSource->aHed[sX];aK<pgSource->aHed[sX+1];aK++){
						sY=pgSource->sSuk[aK];
						sL=++nSommet;sC=++nSommet;
						if (cPasse>0){
							//teeeee("aK,sX,sY,sL,sC",aK,sX,sY,sL,sC);
							sOrigine[sL]=sOrigine[sC]=aK;
							GrapheArquer3(pgG,sX,sL,knCapaciteMinimaleNulle,knCapaciteMaximale,knPoids);
							GrapheArquer3(pgG,sL,sC,knCapaciteMinimaleNulle,knCapaciteMaximale,knPoids);
							GrapheArquer3(pgG,sC,pgSource->nSommetEnTout+sY,knCapaciteMinimaleNulle,knCapaciteMaximale,knPoids);
						}
					}
		}//for cPasse
	//GrapheVoir(pgG,"Graphe de CouplageHongroisMaximiseR avant symétrisation");
	GrapheSymetriser(pgG);
	if (1){
		nSommetInterfacable=2*pgSource->nSommetEnTout;
		//négativer pgG->aHed[sX] lorsque sX n'est pas connectable à une source ou une trappe ——pour bCouplageOptimiser
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->aHed[sX]=iSignePres(nSommetInterfacable<sX,pgG->aHed[sX]);
		//VecteurVoir("pgG->aHed",pgG->aHed,1,pgG->nSommetEnTout);
		bCouplageOptimiser(pgG,k1Poids,k1Maximum);
		//VecteurVoir("pgG->aDeh",pgG->sPer[],1,pgG->nSommetEnTout);
		//négativer les éléments de pmA qui ont été choisis ——pgG->sPer[] contient une copie du couplage résultant 
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (pgG->sPer[sX]>0){
					//uL=sOrigine[sX];uC=sOrigine[pgG->sPer[sX]];
					aK=sOrigine[sX];
					/*tee("uL,uC",uL,uC);
					if (sX<pgG->sPer[sX]){
						aK=nGrapheArc(*pgSource,uL,uC);*/
					//tee("uL,uC",uL,uC);
					//te("aK",aK);
						//pgSource->sSuk[aK]=-abs(pgSource->sSuk[aK]);
						pgSource->coulh[aK]=0;
					}
		GrapheVoir1(pgSource,kV,"Graphe hongrois dans lequel chaque arc pris est décoloré");
	}
	GrapheCreer0(&pgG,kF);
	Appel1("CouplageHongroisMaximiseR");
}//CouplageHongroisMaximiseR

void CouplageMaximiserMemeSiNonBipartI(graf *pgG){//O(S3) en mode rapide vs //O(S4) en mode lent
	//rend dans couplaj[] un couplage maximal sur pgG réputé symétrique
	const int bVoir=kF;
	int nlAretePreleveh,bAugmente,bArbreAlternehComplet,bCouplageMaximum,bComplet;
	int sFeuille,sRacine;
	int nInsatureh,nInsaturehNonMarqueh;
	int nArbreAlterneh=0;
	if (bVoir) Appel0("CouplageMaximiserMemeSiNonBipartI");
		Assert1("CouplageMaximiserMemeSiNonBipartI",bGrapheSymetrique(pgG));
		TycketAllouerTouT(kV,pgG);//O(S2) ——alloue S2 arêtes puis retire les arêtes qui ne sont pas dans pgG
			CouplageCourtCircuiteR(pgG);//prend d'emblée comme couplage les arêtes aK qui vérifient "pgG->coulh[aK]>0".
			CouplageVoiR("après CouplageCourtCircuiteR",pgG,!k1MemeSiNuL);
			bArbreAlternehComplet=kF;//d
			//printf("Choix des arêtes en mode %s, %s %s.\n",(kbTickeT)?  "RAPIDE": "LENT","donc",sAvec(kbTickeT,"le module Ticket"));
			nlAreteChoiX=nlAretePreleveh=0;
			do{
				nInsatureh=nSommetInsatureH(pgG,&sRacine);//O(S)
				bCouplageMaximum=(nInsatureh<=1);//si oui, accroître le couplage est impossible
				if (!bCouplageMaximum){//accroître le couplage est peut-être possible
					//d(sRacine);
					//d2(sRacine,nInsatureh);
					ArbreAlternehEnracineR(pgG,sRacine);//O(S);//l'arbre alterné généré est réduit à sRacine
					//CouplageVoiR("avant bArbreAlternehAugmenteR",pgG,k1MemeSiNuL);
					bAugmente=bArbreAlternehAugmenteR(pgG,sRacine,&sFeuille,&nlAretePreleveh);//O(S2) en mode rapide vs //O(S3) en mode lent
					//d3(bAugmente,sRacine,sFeuille);
					if (bAugmente){//il existe une chaîne alternée augmentante entre la racine de l'arbre et un autre sommet insaturé
						//effectuer un transfert le long de cette chaîne
							TransfertSurChaineAlternehDeLongueurImpairE(pgG,sFeuille);//O(S)
							//CouplageVoiR("après transfert",pgG,k1MemeSiNuL);
						//reconstituer le couplage induit sur le graphe G initial
							OrbiteEclateR(pgG);//O(S)
							//CouplageVoiR("après éclatement",pgG,k1MemeSiNuL);
						//effacer les marques
							VecteurRazer(marq,1,pgG->nSommetEnTout);
					} else{
						bArbreAlternehComplet=kV;
						//Titrer("Accroissement du couplage impossible");
						nInsaturehNonMarqueh=nSommetInsaturehNonMarqueH(pgG);//O(S)
						bCouplageMaximum=(nInsaturehNonMarqueh<=1);
						if (!bCouplageMaximum)
							GrapheReduirE(pgG);//O(A)
					}
					//d2(nAugmente,bCouplageMaximum);
					//VecteurVoir("y final",y,1,pgG->nSommetEnTout);
					nArbreAlterneh++;
					bCouplageMaximum=bCouplageMaximum || (nArbreAlterneh>9);//augmenter ce 9 dédié mise au point
				}
			}while(!bCouplageMaximum);
		TycketAllouerTouT(kF,pgG);//O(S)
		bComplet=bCouplageCompleT(pgG);//O(S)
		CouplageVoiR(sC3b("dans le couplage",sChoix(bComplet,"complet","incomplet"),sChaineEtale1("FINAL")),pgG,k1MemeSiNuL);
		if (bVoir) printf("%sArbres alternés: %s.\n",sTab(14),sPar3(nArbreAlterneh));
		if (bVoir) printf("%sArêtes prélevées vs visitées: %s vs %s.\n",sTab(14),sPar3(nlAretePreleveh),sPar3(nlAreteChoiX));
	if (bVoir) Appel1("CouplageMaximiserMemeSiNonBipartI");
}//CouplageMaximiserMemeSiNonBipartI

int bCouplageOptimiser(graf *pgG,int bPonderer,int bMaximiserSinonMinimiser){
	//pgG->sPer[]:=le cplG qui,si bPonderer,maximise/minimise la somme des nCout[] des arcs du cplG et qui,sinon,maximise le nb de sommets couplés.
	int bBiparti,bParfait=kF;
	int bInterface[kuGrapheSommetLim];
	int sX;
	Appel0("bCouplageOptimiser");
		if (!(!bPonderer || bMaximiserSinonMinimiser)) d2(bPonderer,bMaximiserSinonMinimiser);
		Assert2("CouplageOptimiser1",bCouplageAmorceR,!bPonderer || bMaximiserSinonMinimiser);
		//bInterface[sX] soit vrai ssi sX peut être relié à la source ou à la trappe du réseau de transport créé dans bCouplagePonderehOptimiseR: 
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){
				bInterface[sX]=pgG->aHed[sX]>0;//tt sommet est normalt ds l'interface à moins que l'appelant n'ait explicitt négativé des sommets.
				pgG->aHed[sX]=nAbs(pgG->aHed[sX]);//positive pgG->aHed[] afin que le code qui suit puisse être exécuté.
			}
		//Assert1("CouplageOptimiser2",bGrapheSymetrique(pgG));//APRES bInterface[sX] soit vrai qui restaure aHed 
		bBiparti=bGrapheBiparti(pgG);
		Assert1("CouplageOptimiser2",!bPonderer || bBiparti);//************** pr le moment le couplage pondéré non biparti n'est pas implémenté.
		d3(bPonderer,bBiparti,bMaximiserSinonMinimiser);
//m1);
		if (bPonderer && bBiparti)
			bParfait=bCouplagePonderehOptimiseR(pgG,bMaximiserSinonMinimiser,!k1Voir,bInterface);//O(S2A)
		else if (bPonderer)
			CouplageHongroisMaximiseR(pgG);
		else CouplageMaximiserMemeSiNonBipartI(pgG);//O(S3)
//m2;
		//pgG->sPer[]:=une copie du couplage résultant
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				pgG->sPer[sX]=couplaj[sX];
	Appel1("bCouplageOptimiser");
	return(bParfait);
}//bCouplageOptimiser

int bCouplageParfait(graf *pgG){
	int bParfait=bCouplageOptimiser(pgG,k1Poids,k1Maximum);//appelle bCouplagePonderehOptimiseR,juste ci-dessous, car pgG est biparti.
	return(bParfait);
}//bCouplageParfait

int bCouplagePonderehOptimiseR(graf *pgG,int bMaximum,int bVoir,int bInterface[]){//O(S2A)
	//rend dans couplaj[] un couplage de poids maximal calculé sur pgG symétQ biparti pondéré par pgG->nCout[] et tel que aHed[sX]<0 ssi sX non connctB à source ou trappe
	const int knCapaMinNulle=0;
	const int kuCapaMax=1;
	int nCout;
	int nFlotObtenu,nFlotRequis;
	int cnFlotRequis[0+1];
	graf *pgH;
	int bParfait,nPoidsMax,nPoidsMaximum;
	int sSource,sTrappe;
	int aK,aL,sX,sY;
	//Appel0("bCouplagePonderehOptimiseR");
		Assert2("bCouplagePonderehOptimiseR1",bGrapheSymetrique(pgG),bGrapheBiparti(pgG));
		printf("Recherche d'un couplage de poids %s.\n",(bMaximum)?"maximum":"minimum");
		//GrapheVoir4(pgG,"bCouplagePonderehOptimiseR0");
		GrapheBipartir(pgG,k1Bipartir);//négative pgG->aHed[sX] ssi sX est un sommet de la partition X.
t( sC3("Élaboration du réseau de transport symétrique à ",sPluriel(pgG->nSommetEnTout+2,"sommet"),"..") );
			pgH=(graf *) malloc(sizeof(graf));
			//(pgH,sSource,sTrappe,nFlotRequis):=(le réseau de transport qui englobe pgG,la source,la trappe et le flot maximal théorique admissible.
				sSource=pgG->nSommetEnTout+1;
				sTrappe=pgG->nSommetEnTout+2;
				//tee("sSource,sTrappe",sSource,sTrappe);
				pgH->nSommetEnTout=pgG->nSommetEnTout+2;
				Assert1("bCouplagePonderehOptimiseR5",pgH->nSommetEnTout<kuGrapheSommetLim);
				for (sX=0;sX<=pgH->nSommetEnTout+1;sX++)
					pgH->aHed[sX]=1;
				pgH->nArcEnTout=0;
				//nPoidsMax:=poids maximum rencontré sur un arc ou un autre de pgG:
					for (nPoidsMax=0,aK=1;aK<=pgG->nArcEnTout;aK++){
						Assert1("bCouplagePonderehOptimiseR7",pgG->nCout[aK]>=0);
						//te("pgG->nCout[aK]",pgG->nCout[aK]);
						nPoidsMax=iSup(nPoidsMax,pgG->nCout[aK]);
					}
					te("nPoidsMax",nPoidsMax);
				nPoidsMaximum=(bMaximum) ? 0: nPoidsMax;
				//te("nPoidsMaximum",nPoidsMaximum);
					//relier dans pgH les sommets de X aux sommets de Y (comme dans pgG) 
				te("pgG->nArcEnTout",pgG->nArcEnTout);
						for (sX=1;sX<=pgG->nSommetEnTout;sX++)
							for (aK=abs(pgG->aHed[sX]);aK<abs(pgG->aHed[sX+1]);aK++){
								sY=pgG->sSuk[aK];
								if (sX<sY && pgG->aHed[sX]*pgG->aHed[sY]<0){
									nCout=(bMaximum)? pgG->nCout[aK]: nPoidsMaximum-pgG->nCout[aK];
									GrapheArquer3(pgH,sX,sY,knCapaMinNulle,kuCapaMax,nCout);
									GrapheArquer3(pgH,sY,sX,knCapaMinNulle,kuCapaMax,nCout);
								}
							}
					//relier sSource aux sommets de X, sTrappe à ceux de Y, et déduire le flot maximal admissible nFlotRequis:
						for (cnFlotRequis[0]=cnFlotRequis[1]=0,nCout=0,sX=1;sX<=pgG->nSommetEnTout;sX++){
							if (bInterface[sX]){
								//tee("sX,pgG->aHed[sX]<0",sX,pgG->aHed[sX]<0);
								//if (pgG->aHed[sX]>0) tee("sSource,sX",sSource,sX); else tee("sX,sTrappe",sX,sTrappe); 
								if (pgG->aHed[sX]>0)
									GrapheArquer3(pgH,sSource,sX,knCapaMinNulle,kuCapaMax,nCout);
								else GrapheArquer3(pgH,sX,sTrappe,knCapaMinNulle,kuCapaMax,nCout);
								cnFlotRequis[pgG->aHed[sX]>0]++;
							}
						}
						//tee("cnFlotRequis[0],cnFlotRequis[1]",cnFlotRequis[0],cnFlotRequis[1]);
						nFlotRequis=iInf(cnFlotRequis[0],cnFlotRequis[1]);
				te("pgH->nArcEnTout",pgH->nArcEnTout);
				//NB ne pas symétriser pgH: la source doit rester une source et la trappe doit rester une trappe.
				GrapheInverser(pgH);
				if (!bMaximum)
					printf("Chaque poids P est remplacé ci-dessous par %d-P afin de maximiser plutôt que de minimiser.\n",nPoidsMaximum); 
//bVoir=kV;
				if (bVoir)
					GrapheVoir4(pgH,sC2b("Réseau de transport conçu pour acheminer jusqu'à",sPluriel(nFlotRequis,"unité$ de flot")));
			Assert1("bCouplagePonderehOptimiseR45",bGrapheSimple(pgH));
//t("ÉTAP 5");//***************************************************************************************
t("Calcul du flot optimal..");
			nFlotObtenu=nFlotMaxCalculer(pgH,sSource,sTrappe,nFlotRequis,1 || bVoir);//O(S2A)
t("Mémorisation du couplage..");
			//te("***************nFlotObtenu",nFlotObtenu);
			//couplaj[]:=arcs de pgG qui ont un flot non nul
				Assert3("bCouplagePonderehOptimiseR8",pgH->nSommetEnTout==pgG->nSommetEnTout+2,sSource==pgG->nSommetEnTout+1,sTrappe==pgG->nSommetEnTout+2);
				te("pgG->nSommetEnTout",pgG->nSommetEnTout);
				for (sX=1;sX<=pgH->nSommetEnTout;sX++)
					couplaj[sX]=0;
				/*for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					if (pgG->aHed[sX]<0)
						for (aK=pgH->aHed[sX];aK<pgH->aHed[sX+1];aK++,sY=pgH->sSuk[aK]){
							if (pgH->nPhi[aK]>0 && sY<=pgG->nSommetEnTout ){
								Assert2("bCouplagePonderehOptimiseR",bCroit(1,sX,pgG->nSommetEnTout),bCroit(1,sY,pgG->nSommetEnTout));
								//tee("phi>0 pour sX,sY",sX,sY);
								couplaj[sY]=sX;couplaj[sX]=sY;
							}
						}*/
				//NB pgG->aInv permet de passer du graphe inverse au graphe direct ——pas dans l'autre sens
				for (sY=1;sY<=pgG->nSommetEnTout;sY++)//O(A)
					for (aL=pgH->aDeh[sY];aL<pgH->aDeh[sY+1];aL++){
						sX=pgH->sKus[aL];
						//tee("sX,sY",sX,sY);
						if (bCroit(1,sX,pgG->nSommetEnTout) && pgG->aHed[sX]<0){
							aK=pgH->aInv[aL];Assert1("bCouplagePonderehOptimiseR4",sY==pgH->sSuk[aK]);
							if (pgH->nPhi[aL]>0 /*&& pgH->nPhi[aK]==0*/){
								Assert2("bCouplagePonderehOptimiseR45",bCroit(1,sX,pgG->nSommetEnTout),bCroit(1,sY,pgG->nSommetEnTout));
								//tee("phi>0 pour sX,sY",sX,sY);
								//t("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj");
								couplaj[sY]=sX;couplaj[sX]=sY;
							}
						}
					}


			//tee("nFlotRequis et nFlotObtenu",nFlotRequis,nFlotObtenu);
			bParfait=(nFlotObtenu==nFlotRequis);
			bVoir=kV;
			if (bVoir)
				printf("Le couplage obtenu %s maximal: %d/%d.\n",sEst(bParfait),nFlotObtenu,nFlotRequis);
//t("alpha");
			if (0 && bVoir)
				CouplageVoiR2(sC2b("dans le couplage de poids",sChoix(bMaximum,"maximal","minimal")),pgH,k1MemeSiNuL,k1Poids,nPoidsMaximum);
//t("omega");
		free(pgH);
		GrapheBipartir(pgG,!k1Bipartir);//dénégative pgG->aHed[]
	//Appel1("bCouplagePonderehOptimiseR");
	return(bParfait);
}//bCouplagePonderehOptimiseR

void CouplageTESTER(int iTest){
	//teste le présent module;La couleur associée à chaque arête vaut 1 si elle fait partie du couplage initial. Sinon,elle vaut 0.
	char kcBrexitt[]="AC0AF0AH0BD0BF0BJ0CE0CI0DG0DI0EF0EH0FG0GJ0HI0IJ0";
	char kcDeltoide[]="AB0AW0AX0BC0BJ0CD0CR0DE0DL0EF0EM0FG5GZ0HI0HP0HZ0IJ0IQ0JK0KL0KS0LM0MY0NO5NY0OP0PQ0QR0RS0ST0TW0TX0UV5UY0VZ0";
	char kcDomino1[]="AB0AD0BC0BE0CF0DE0EF0";//couplage initial vide
	char kcDomino2[]="AB0AD0BC1BE0CF0DE1EF0";//couplage initial: BC et DE
	char kcComplet4[]="AB0AC0AD0BC0BD0CD0";
	char kcComplet5[]="AB0AC0AD0AE0BC0BD0BE0CD0CE0DE0";
	char kcFaible[]="AB0AC0AG0AI0BC0BH0CD0DE0DI0EF0FG0GH0HI0";
	char kcGlobe[]="AB0AU0AV0BC0BJ0CD0DE0DQ0EF0EP0FG5GX0HI0HX0IJ0JK0KL0KS0LM0MW0NO5NW0OP0PQ0QR0RS0ST0TU0TV0UV0UY0VZ0Wa0Xb0";
	char kcHerschel[]="AC0AE0AF0BC0BG0BE0CH0CI0DH0DK0DI0DJ0EJ0EK0FH0FJ0GI0GK0";
	char kcHerschelFaux[]="AE0AI0BG0BK0CE0CH0DH0DK0EF0FG0FH0HJ0IJ0JK0";
	char kcLongrine8[]="AE0BG0CK0DI0EF0FB0FI1GH0HA0HK1IJ0JC0KL0LD0";
	char kcLongrine10[]="AE0BG0CM1DJ1EF0FB1GH0HI0IA2IM3FJ3JK0KL0LC0MN0ND0";
	char kcK221[]="AC1AD1BC1BD1";
	char kcK222[]="AC2AD1BC1BD1";
	char kcMutex[]="AC1BD1CF1DF1EA1EB1";
	char kcPapillon[]="AB1AM1BC2BM1CD3CJ2DE4DI3EF4FD4FE4GH5HG5HI5IC3IG5JB2JK6LJ6KL6LK6MA1";
	int bMaximum=k1Maximum,bPonderer=k1Poids,bSymetriser=kV;
	graf *pgG;
	enum grType GrapheType;
	char *sgrNoM=GrapheNom;
	Assert1("CouplageTESTER",bCouplageAmorceR);
	iTest=60;
	Appel0(sC2("CouplageTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case  0:	Titrer("kcFigure8aPage272 alias grOmega");
						GrapheCreer1(&pgG,grOmega,k1Creer);//Gondran et Minoux Eyrolles 37
						bPonderer=kF;
						break;
			case  1:	Titrer("kcDomino1");
						GrapheGenerer(kcDomino1,&pgG);
						break;
			case  2:	Titrer("kcDomino2");
						GrapheGenerer(kcDomino2,&pgG);
						break;
			case  3:	Titrer("kcComplet4");
						GrapheGenerer(kcComplet4,&pgG);
						break;
			case  4:	Titrer("kcComplet5");
						GrapheGenerer(kcComplet5,&pgG);
						break;
			case  6:	Titrer("kcFaible");
						GrapheGenerer(kcFaible,&pgG);
						break;
			case  5:	Titrer("kcHerschelFaux");
						GrapheGenerer(kcHerschelFaux,&pgG);
						break;
			case  7:	Titrer("kcHerschel");
						GrapheGenerer(kcHerschel,&pgG);//impair, dc reste 1 sommet non couplé
						break;
			case  8:	Titrer("kcBrexitt");
						GrapheGenerer(kcBrexitt,&pgG);
						break;
			case  9:	Titrer("kcDeltoide");
						GrapheGenerer(kcDeltoide,&pgG);
						break;
			case 10:	Titrer("kcGlobe");
						GrapheGenerer(kcGlobe,&pgG);
						break;
			case 11:	Titrer("kcK221");
						GrapheGenerer(kcK221,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						break;
			case 12:	Titrer("kcK222");
						GrapheGenerer(kcK222,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						break;
			case 13:	Titrer("kcPapillon");
						GrapheGenerer(kcPapillon,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						bPonderer=k1Ponderer;
						bSymetriser=kF;
						break;
			case 20:	Titrer("kcDomino1");
						GrapheGenerer(kcDomino1,&pgG);
						//GrapheSymetriser(pgG);
						GraphePonderer0(pgG,3);
						GrapheVoir(pgG,"pgG");
						CouplageParfaitListeR(pgG);
						break;
			case 30:	Titrer("kcLongrine8");
						GrapheGenerer(kcLongrine8,&pgG);
						VecteurCopier(pgG->coulh,1,pgG->nArcEnTout,pgG->nCout);
						GrapheVoir(pgG,"pgG");
						CouplageParfaitListeR(pgG);
						break;
			case 40:	Titrer("kcLongrine10");
						GrapheGenerer(kcLongrine10,&pgG);
						GraphePonderer0(pgG,1);//tous les arcs
						GraphePonderer(pgG,6,10,3);//arc (6,10) de poids 3
						GraphePonderer(pgG,9,13,4);
						GrapheVoir(pgG,"pgG");
						CouplageParfaitListeR(pgG);
						break;
			case 50:	Titrer("kcMutex");
						GrapheGenerer(kcMutex,&pgG);
						GraphePonderer0(pgG,1);//tous les arcs
						GrapheVoir(pgG,"pgG");
						CouplageParfaitListeR(pgG);
						break;
			case 60:	Titrer("Couplage de graphes extraits de la collection grGraphe");
						printf("      NB: Choix des arêtes en mode %s, %s %s.\n\n",(kbTickeT)?  "RAPIDE": "LENT","donc",sAvec(kbTickeT,"le module Ticket"));
						for (int uG=grAlpha+1;uG<=grOmega;uG++){
							Titrer(sC2b("Graphe",sItem0(sgrNoM,uG)));
							GrapheCreer1(&pgG,uG,k1Creer);
								VecteurRazer(pgG->coulh,1,pgG->nArcEnTout);
								GrapheVoir(pgG,sC2b("Graphe",sItem0(sgrNoM,uG)));
								GrapheSymetriser(pgG);
								CouplageMaximiserMemeSiNonBipartI(pgG);
							GrapheCreer1(&pgG,uG,!k1Creer);
							Ligne();
						}
						break;
			default:	Assert1("CouplageTESTER",0);
		}
		if (iTest<20){
			GrapheVoir1(pgG,kV,"Graphe généré avant symétrisation");
			if (bSymetriser)
				GrapheSymetriser(pgG);
			GrapheVoir(pgG,sC3b("Graphe généré",sChoix(bSymetriser,"APRES","SANS"),"symétrisation"));
			//GrapheVoir1(pgG,kV,"Graphe généré après symétrisation");
			bCouplageOptimiser(pgG,bPonderer,bMaximum);
		}
	Appel1(sC2("CouplageTESTER,test n°",sEnt(iTest)));
}//CouplageTESTER	

void CouplageVoiR(char *sMessage,graf *pgG,int bMemeSiNul){
	//affiche la liste de arêtes qui appartiennent au couplage courant de pgG
	const int knPoidsNul=0;
	const int knPoidsMaximumNul=0;
	CouplageVoiR2(sMessage,pgG,bMemeSiNul,knPoidsNul,knPoidsMaximumNul);
}//CouplageVoiR	

void CouplageVoiR2(char *sMessage,graf *pgG,int bMemeSiNul,int bPoids,int nPoidsMaximum){
	//affiche la liste de arêtes (avec leurs pondérations ssi bPoids) qui appartiennent au couplage courant de pgG
	int aK,sX,sY;
	int nCouple=0,cPasse,nPoids;
	//Appel0("CouplageVoiR2");
		for (nCouple=0,cPasse=0;cPasse<=1;cPasse++){
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){
				//d(sX);
				if ( bSommetSatureH(pgG,sX) )
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
						sY=pgG->sSuk[aK];
						//d(sY);
						nPoids=(nPoidsMaximum>0)? nPoidsMaximum-pgG->nCout[aK]: pgG->nCout[aK];
						if ( sX<sY && couplaj[sY]==sX ){
							if (cPasse==0)
								nCouple++;
							else printf(" %s",(bPoids)? sTriplet(sX,sY,nPoids): sCouple(sX,sY));
						}
					}//for aK
			}
			if (!cPasse)
				if (!nCouple){
					if (bMemeSiNul)
						printf("Aucun %s à afficher %s",(bPoids)? "triplet": "couple",sMessage);
				}else printf("      %s %s:",sPluriel(nCouple,(bPoids)? "triplet": "couple"),sMessage);
		}
		printf("%s",(bMemeSiNul || nCouple>0)? ".\n": "");
	//Appel1("CouplageVoiR2");
}//CouplageVoiR2	

void GrapheReduirE(graf *pgG){//O(A)
	//supprime virtuellt ts les sommets du couplage et ts les sommets de degré libre nul
	const int bVoir=kF;
	int aK,sX,sY,nOccurrence0,nOccurrence1;
	int nDegreh[1+pgG->nSommetEnTout];
	int nIndex[1+pgG->nSommetEnTout];
	if (bVoir) Appel0("GrapheReduirE");
		t("      RÉDUCTION du graphe et POURSUITE");
		VecteurIndexer(nIndex,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("nIndex         ",nIndex,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("couplaj   AVANT",couplaj,1,pgG->nSommetEnTout);
		if (bVoir) VecteurVoir("pgG->sPer AVANT",pgG->sPer,1,pgG->nSommetEnTout);
		nOccurrence0=nVecteurOccurrence(0,pgG->sPer,1,pgG->nSommetEnTout);
//NB on peut fare mieux en calculant 1 fois pr toutes les degrés et en décrémentant ceux-ci à chaq nouveau couplage
		//supprimer virtuellt ts les sommets du couplage
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (couplaj[sX])
					pgG->sPer[sX]=0;
		//nDegreh[sX]:= degré libbre de sX
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				for (nDegreh[sX]=0,aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (sY=pgG->sSuk[aK],pgG->sPer[sY])
						nDegreh[sX]++;
		//supprimer virtuellt ts les sommets isolés au sens de nDegreh[]
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)
				if (nDegreh[sX]==0)
					pgG->sPer[sX]=0;
		if (bVoir) VecteurVoir("pgG->sPer APRES",pgG->sPer,1,pgG->nSommetEnTout);
		nOccurrence1=nVecteurOccurrence(0,pgG->sPer,1,pgG->nSommetEnTout);
		//if (bVoir) d2(nOccurrence0,nOccurrence1);
		Assert1("GrapheReduirE1",nOccurrence1>nOccurrence0);//dc le volume du graphe diminue strictement
	if (bVoir) Appel1("GrapheReduirE");
}//GrapheReduirE

void OrbiteEclateR(graf *pgG){//O(S) car les orbites sont disjointes, la somme de leurs nb de sommets ne peut excéder S
	int sK1,sOrbite;
	for (sOrbite=sPseudoSommetMaX;sOrbite>pgG->nSommetEnTout;sOrbite--){//∑ O(3o) où o est la taille de l'orbite courante
		sK1=sOrbiteEclaterUN(pgG,sOrbite);//O(o) où o est la taille de l'orbite courante en nb de sommets
		if (marq[sK1]!=0)
			OrbiteEclaterDEUX(pgG,sOrbite);//O(o) où o est la taille de l'orbite courante en nb de sommets
		else ;//le couplage sur G' est cpatible avec le couplage de l'orbite.
		OrbiteEclaterTROIS(pgG,sOrbite,sK1);//O(o) où o est la taille de l'orbite courante en nb de sommets
		//sPseudoSommetMaX--;superflu puisque ArbreAlternehEnracineR réinitialisera sPseudoSommetMaX à pgG->nSommetEnTout
		//StructureVoiR(sC2b("après éclatement de l'orbite",sEnt(sOrbite)));
	}
}//OrbiteEclateR

int sOrbiteEclaterUN(graf *pgG,int sOrbite){//O(S)
	//vérifie la cpatBT du cplG sur G' avec le couplG de sOrbite et rend sExtremiteh1, extrémité ds l'orbite sOrbite de l'arête du cplG de G'.
	int sExtremiteh0,sExtremiteh1;
	//Appel0("sOrbiteEclaterUN");
		Assert1("sOrbiteEclaterUN1",bSommetOrbitaL(pgG,sOrbite));//O(1)
		sExtremiteh0=couplaj[sOrbite];
		//sExtremiteh1 soit l'extrémité de l'arête du couplG de G' ds l'orbite de nom sOrbite.
			sExtremiteh1=couplaj[sExtremiteh0];
			While(pgG->nSommetEnTout);
			while (bWhile("sOrbiteEclaterUN 3",alpha[sExtremiteh1]!=sOrbite))
				sExtremiteh1=alpha[sExtremiteh1];
		//printf("Extrémité de l'orbite %d: le sommet %d.\n",sOrbite,sExtremiteh1);
	//Appel1("sOrbiteEclaterUN");
	return(sExtremiteh1);
}//sOrbiteEclaterUN

void OrbiteEclaterDEUX(graf *pgG,int sOrbite){//O(S)
	//modifie alpha et beta pour revenir à la plus récente situation antérieure à la création de l'orbite sOrbite.
	int sJ,sJ1,sJ2,sJ3,sJ4;
	const int kuA=1,kuB=2,kuC=3;
	int bOrbite,nEtat,nTour;
	//Appel0("OrbiteEclaterDEUX");
		Assert1("OrbiteEclaterDEUX",bSommetOrbitaL(pgG,sOrbite));//O(1)
		//alpha soit actualisé
			for (sJ=1;sJ<=sPseudoSommetMaX;sJ++)//O(S)
				if (alpha[sJ]==sOrbite)
					alpha[sJ]=sJ;
		if (0)
			{VecteurVoir("alpha",alpha,1,sPseudoSommetMaX);VecteurVoir(" beta",beta,1,sPseudoSommetMaX);}
		//beta soit actualisé
			for (nTour=0,sJ=1;sJ<=pgG->nSommetEnTout;nTour++,sJ++){//O(S)
				bOrbite=beta[sJ]==sOrbite;
				//Assert1("OrbiteEclaterDEUX",bOrbite);
				if (bOrbite){
					sJ1=sJ;
					While(pgG->nSommetEnTout);
					do{
						nTour++;
						nEtat=kuA;
						sJ2=alpha[sJ1];
						if (sJ2!=sJ1){
							if (beta[sJ2]!=sOrbite)
								nEtat=kuB;
							else sJ1=sJ2;
						}else nEtat=kuC;
					}while ( bWhile("OrbiteEclaterDEUX 1",nEtat==kuA) );
					if (nEtat==kuC) {
						beta[sJ2]=sJ2;
						sJ3=sJ2;
					}else {
						sJ3=sJ1;
						beta[sJ3]=beta[sJ2];
					}
					sJ4=sJ;
				}
				While(pgG->nSommetEnTout);
				while (bWhile("OrbiteEclaterDEUX 2",sJ4!=sJ3)){
					nTour++;
					beta[sJ4]=beta[sJ3];
					sJ4=alpha[sJ4];
				}
			}//for
			Assert1("OrbiteEclaterDEUX 3",nTour<=(5*pgG->nSommetEnTout)/2);
		//beta soit actualisé
			/*for(sJ=1;sJ<=pgG->nSommetEnTout;sJ++){
				bOrbite=beta[sJ]==sOrbite;
				//Assert1("OrbiteEclaterDEUX",bOrbite);
				if (bOrbite)
					sJ1=sJ;
				else goto D;
			A:	sJ2=alpha[sJ1];
				if (sJ2==sJ1){
					beta[sJ2]=sJ2;
					sJ3=sJ2;
					goto C;
				}else {
					if (beta[sJ2]!=sOrbite)
						goto B;
					else sJ1=sJ2; goto A;
				}
			B:	sJ3=sJ1;
				beta[sJ3]=beta[sJ2];
			C:	sJ4=sJ;
			D: if (sJ4!=sJ3){
					beta[sJ4]=beta[sJ3];
					sJ4=alpha[sJ4];
					goto D;
				}
			}*/
	//Appel1("OrbiteEclaterDEUX");
}//OrbiteEclaterDEUX

void OrbiteEclaterTROIS(graf *pgG,int sOrbite,int sK1){//O(S)
	//change le couplage et les marques sur la chaîne paire entre sK1 et l'ancienne racine de l'orbite sOrbite
	int sK0,sK2,sKprim2,sK3,sKprim3,sK4,sKprim4,sK5;
	int sL,sLprim,sL1;
	int bPoursuivre;
	//Appel0("OrbiteEclaterTROIS");
	Assert1("OrbiteEclaterTROIS",bSommetOrbitaL(pgG,sOrbite));//O(1)
		sL=marq[sK1];sLprim=beta[sL];sL1=s[sK1];sK0=couplaj[sOrbite];
		sKprim2=sK1;
		While(pgG->nSommetEnTout);
		do{
			sK3=couplaj[sKprim2];marq[sKprim2]=sK3;couplaj[sKprim2]=sK0;
			sKprim3=beta[sK3];sK4=marq[sKprim3];sKprim4=beta[sK4];
			sK2=couplaj[sKprim3];s[sKprim2]=sK2;
			if (sKprim2==sK1){
				s[sKprim2]=0;
			}
			marq[sKprim3]=sK2;couplaj[sKprim3]=sK4;sK5=s[sKprim3];//ligne entière ici ou dans le if qui précède ???
			s[sKprim3]=sK3;
			bPoursuivre=(marq[sKprim4]!=0);
			if (bPoursuivre){
				sKprim2=sKprim4;sK0=sK5;
			}
		}while (bWhile("OrbiteEclaterTROIS",bPoursuivre));
		/*if (marq[sKprim4]==0) goto B;
		else sKprim2=sKprim4;sK0=sK5;goto A;*/
	/*B:*/	marq[sK1]=0;
		couplaj[sKprim4]=sK5;
	//Appel1("OrbiteEclaterTROIS");
}//OrbiteEclaterTROIS

int sSommetConfluenT(graf *pgG,int sRacine,int sIpair,int sJpair,int *pnLgDepuisIpair,int *pnLgDepuisJpair){//O(pgG->nSommetEnTout)
	int sConfluent,sImpair,sPair,sRacinePrim;
	int sIprim,sJprim;
	int bDito,bRacine,nEtape;
	//Deux chaines alternées relient sIprim d'une part et sJprim d'autre part à la racine sRacinePrim=beta[sRacinePaire].
	//ces chaines alternées ont un premier pseudo-sommet commun sConfluent dans G'. On remonte simultanément les deux chaînes alternées.
	//Le premier sommet rencontré pour la deuxième fois est nécessairement sConfluent.
	Assert3("sSommetConfluenT0",bSommetPaiR(pgG,sRacine),bSommetPaiR(pgG,sIpair),bSommetPaiR(pgG,sJpair));
	sIprim=beta[sIpair];
	sJprim=beta[sJpair];
	sRacinePrim=beta[sRacine];
	sConfluent=0;//d
	DequeAllouer(sPseudoSommetMaX);
		//confluer depuis sIprim vers la racine sachant que précédent(sPair)=beta[marq[sImpair]] et précédent(sImpair)=beta[couplaj[sPair]]:
			sPair=sIprim;
			do{
				//te("sPair empilé",sPair);
				DequeEmpiler(sPair);
				bRacine=(sPair==sRacinePrim);
				if (!bRacine){
					Assert1("sSommetConfluenT4",couplaj[sPair]>0);
					sImpair=beta[couplaj[sPair]];//beta[couplaj] puisque sPair est pair.
					sPair=beta[marq[sImpair]];   //beta[marq] puisque sImpair est impair.
				}
			}while(!bRacine);
			*pnLgDepuisIpair=nDequeCardinal();
		//confluer depuis sJprim vers la racine sachant que précédent(sPair)=beta[marq[sImpair]] et précédent(sImpair)=beta[couplaj[sPair]]:
			sPair=sJprim;
			nEtape=0;
			do{
				//te("sPair enquis",sPair);
				bDito=bDequeContient(sPair);
				nEtape++;
				if (!bDito){
					Assert1("sSommetConfluenT5",couplaj[sPair]>0);
					sImpair=beta[couplaj[sPair]];//beta[couplaj] puisque sPair est pair.
					sPair=beta[marq[sImpair]];   //beta[marq] puisque sImpair est impair.
				}else sConfluent=sPair;
			}while(!bDito);
			*pnLgDepuisJpair=nEtape;
	DequeAllouer(0);
	//te("sSommetConfluenT",sConfluent);
	Assert4("sSommetConfluenT9",sConfluent>0,bSommetPaiR(pgG,sConfluent),bCroit(1,*pnLgDepuisIpair,pgG->nSommetEnTout),bCroit(1,*pnLgDepuisJpair,pgG->nSommetEnTout));
	return(sConfluent);//sConfluent est bien la copie du dernier sPair=beta[marq[sImpair]]
}//sSommetConfluenT

void SommetConflueR(int sFourchePrim,int sIpair,int sJpair,int nEtapeMax){//O(pgG->nSommetEnTout)
	//remonte dans Gprim de sIpair à sFourchePrim en actualisant alpha[],marq[],s[] et arbraltpair[]
	int sKprim1,sK1,sK2,sKprim2,sKprim3,sK4,sKprim4;
	sK1=sJpair;sKprim1=beta[sJpair];
	sK2=sIpair;sKprim2=beta[sIpair];//sK2 alias sIpair est le point de départ
	if (sKprim2!=sFourchePrim){
		While(nEtapeMax);
		do{ Assert1("SommetConflueR1",couplaj[sKprim2]>0);
//si k est un pseudo-sommet,couplaj[k] est le n° du vrai sommet i extrémité de l'arête du couplage incidente à k et non contenu dans k (p276).
			sKprim3=beta[couplaj[sKprim2]];//beta[couplaj] puisque sKprim2 est pair. Adéquat mm si sKprim2 est un pseudo-sommet, vu li-1.
			sK4=marq[sKprim3];//beta[marq] puisque sKprim3 est impair; la valeur intermédiaire sK4 permettra de progresser vers la racine.
			sKprim4=beta[sK4];
			Assert1("SommetConflueR2",sK1>0);
			//sKprim2 devient un sommet impair, vu sK1!=0.
	marq[sKprim2]=sK1;//sK1 est le vrai sommet extrémité de l'arête utilisée pour marquer sKprim2 à partir de j. j=beta[sK1]=beta[marq[k]]
				s[sKprim2]=sK2;//si k est pseudo-sommet marqué "impair",s[k]=l est le vrai sommet extrémT ds k de l'arête (fine) ayant permis de marquer k (point de contact).
			alpha[sKprim2]=alpha[sKprim3]=sPseudoSommetMaX;//sKprim2 et sKprim3 sont englobés par sPseudoSommetMaX.
			arbraltpair[sKprim3]=1;//sKprim3 change de statut:il devient pair.
			//progresser d'un pas vers la racine
				sKprim1=sKprim3;sK1=s[sKprim3];sKprim2=sKprim4;sK2=sK4;//sK2 alias sK4 est le nouveau point de départ
		} while ( bWhile("SommetConflueR while",sKprim2!=sFourchePrim) );
	}else alpha[sKprim2]=sPseudoSommetMaX;
}//SommetConflueR

int nSommetInsatureH(graf *pgG,int *psRacine){//O(S)
	int nSommetInsatureh,sX;
	for (nSommetInsatureh=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
		if (!bSommetSatureH(pgG,sX) && pgG->sPer[sX]>0){//O(1)
			if (nSommetInsatureh==0)
				*psRacine=sX;
			nSommetInsatureh++;
		}
	return(nSommetInsatureh);
}//nSommetInsatureH

int nSommetInsaturehNonMarqueH(graf *pgG){//O(S)
	int nSommetInsaturehNonMarqueh,sX;
	for (nSommetInsaturehNonMarqueh=0,sX=1;sX<=pgG->nSommetEnTout;sX++)
		if (!bSommetSatureH(pgG,sX) && !bSommetMarqueH(pgG,sX)){//O(1) et O(1)
			nSommetInsaturehNonMarqueh++;
		}
	return(nSommetInsaturehNonMarqueh);
}//nSommetInsaturehNonMarqueH

int bSommetMarqueH(graf *pgG,int sEnquis){//O(1)
	int bMarqueh=kF;
	Assert1("bSommetMarqueH",bCroit(1,sEnquis,sPseudoSommetMaX));
	bMarqueh=(arbralt[sEnquis]==1);
	return(bMarqueh);
}//bSommetMarqueH

int bSommetOrbitaL(graf *pgG,int sSommet){//O(1)
	//sommet ajout au graphe original
	int bOrbital;
	bOrbital=bCroit(pgG->nSommetEnTout+1,sSommet,sPseudoSommetMaX);
	return(bOrbital);
}//bSommetOrbitaL

int bSommetOriginaL(graf *pgG,int sSommet){//O(1)
	//sommet du graphe original
	int bVrai;
	bVrai=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bVrai);
}//bSommetOriginaL

int bSommetPaiR(graf *pgG,int sEnquis){//O(1)
	//sEnquis est dans arbraltpair
	if (!bCroit(1,sEnquis,sPseudoSommetMaX))
		te("Dans bSommetPaiR sEnquis",sEnquis);
	Assert1("bSommetPaiR",bCroit(1,sEnquis,sPseudoSommetMaX));
	int bPair=(arbralt[sEnquis]==1) && (arbraltpair[sEnquis]==1);
	return(bPair);
}//bSommetPaiR

int bSommetSatureH(graf *pgG,int sEnquis){//O(1)
	//sEnquis est bien un sommet de pgG situé à une extrémité d'une arête du couplage
	int bSatureh;
	if (!bCroit(1,sEnquis,pgG->nSommetEnTout))
		te("bSommetSatureH:sEnquis",sEnquis);
	Assert1("bSommetSatureH",bCroit(1,sEnquis,pgG->nSommetEnTout));
	bSatureh=couplaj[sEnquis]>0;
	return(bSatureh);
}//bSommetSatureH

int sSommetSatureH(graf *pgG,int sAutreBout){//O(1)
	//rend le sommet situé à une extrémité d'une arête du couplage autre que sAutreBout
	int sSatureh;
	Assert2("sSommetSatureH0",bCroit(1,sAutreBout,pgG->nSommetEnTout),couplaj[sAutreBout]>0);
	sSatureh=couplaj[sAutreBout];
	Assert1("sSommetSatureH1",sSatureh>0);
	return(sSatureh);
}//sSommetSatureH

void StructureVoiR(char *sMessage){
	if (1){
		t(sMessage);
		VecteurVoir("++++++ marq",marq,1,sPseudoSommetMaX);
		VecteurVoir("+++++ alpha",alpha,1,sPseudoSommetMaX);
		VecteurVoir("++++++ beta",beta,1,sPseudoSommetMaX);
		VecteurVoir("+++ couplaj",couplaj,1,sPseudoSommetMaX);
		VecteurVoir("++++ arbralt",arbralt,1,sPseudoSommetMaX);
		VecteurVoir(" arbraltpair",arbraltpair,1,sPseudoSommetMaX);
		//VecteurVoir("+++++++++ s",s,1,sPseudoSommetMaX);
	}
}//StructureVoiR

void TransfertSurChaineAlternehDeLongueurImpairE(graf *pgG,int sK){//O(S)
	//effectue un transfert le long d'une chaîne alternée impaire d'extrémité sK
	int sK0,sK1,sK2,sKprim2;
	sK1=sK;
	sK0=s[sK1];
	sK2=marq[sK1];
	sKprim2=beta[sK2];
	couplaj[sK1]=sK2;
	//tee("      ***** Transfert impair avec sK0 et sKprim2",sK0,sKprim2);
//StructureVoiR("juste AVANT transfert");
	if (couplaj[sKprim2]==0)
		couplaj[sKprim2]=sK0;
	else TransfertSurChaineAlternehDeLongueurPairE(pgG,sKprim2,sK0);
}//TransfertSurChaineAlternehDeLongueurImpairE

void TransfertSurChaineAlternehDeLongueurPairE(graf *pgG,int sK,int sK0bout){//O(S)
	//effectue un transfert le long d'une chaîne alternée paire d'extrémité sK
	int sKprim2,sK3,sKprim3,sK4,sKprim4,sK5,sK0=sK0bout;
	sKprim2=sK;
	int bPoursuivre;
	//tee("     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Transfert pair avec sK et sK0bout",sK,sK0bout);
	bPoursuivre=kV;
	While(pgG->nSommetEnTout);
	do{
		sK3=couplaj[sKprim2];sKprim3=beta[sK3];couplaj[sKprim2]=sK0;
		sK4=marq[sKprim3];sKprim4=beta[sK4];couplaj[sKprim3]=sK4;
		sK5=s[sKprim3];
		if (couplaj[sKprim4]==0){
			couplaj[sKprim4]=sK5;
			bPoursuivre=kF;
		}else {
			sK0=sK5;
			sKprim2=sKprim4;
		}
	}while (bWhile("TransfertSurChaineAlternehDeLongueurPairE",bPoursuivre));
}//TransfertSurChaineAlternehDeLongueurPairE

void TycketAfficherTouT(graf *pgG){//O(S2)
	int nT,nTicket;
	if (kbTicketVoiR) {
		for (nTicket=0,nT=1;nT<=pgG->nSommetEnTout;nT++)//O(S2)
			nTicket+=nTicketCardinal(pTickeT[nT]);//O(1)
		for (nT=0;nT<=pgG->nSommetEnTout;nT++)
			if (nT==0 || nTicketCardinal(pTickeT[nT]))
			 TicketVoir(sC2("Liste n°",sEnt(nT)),pTickeT[nT]);
		te("Tickets restants",nTicket);
	}
}//TycketAfficherTouT

void TycketAllouerTouT(int bAllouer,graf *pgG){//O(S2)
	//si pgG->nSommetEnTout alias nTicket>0,alloue 1+nTicket collections de nTicket tickets numérotés de 1 à nTicket. Sinon, restitue ces collections.
	int aK,sX,sY;
	int nT,nTicket;
	int bPresent[1+pgG->nSommetEnTout];
	if (kbTickeT){
		nTicket=pgG->nSommetEnTout;
		if (kbTicketVoiR) d(nTicket);
		if (bAllouer){//allouer S2 arêtes puis retirer de suite toutes les arêtes qui ne sont pas dans pgG
			//allouer S+1 collections de tickets; la collection 0 liste toutes les extrémités origine des arêtes
				for (nT=0;nT<=nTicket;nT++)//O(S2)
					pTickeT[nT]=pTicketAllouer(nTicket);//O(S)
			//retirer des S collections hors pTickeT[0] les arêtes absentes de pgG
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S2+A+S2)
					/*for (sY=1;sY<=pgG->nSommetEnTout;sY++)//O(S)
						bPresent[sY]=kF;*/
					VecteurRazer(bPresent,1,pgG->nSommetEnTout);//O(S)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//O(tuple dédié à sX)
						bPresent[pgG->sSuk[aK]]=kV;
					for (sY=1;sY<=pgG->nSommetEnTout;sY++)//O(S)
						if (!bPresent[sY])//pgG étant symétrique, TicketRetirer0(sY,sX) sera aussi appelé ds cette routine
							TicketRetirer0(pTickeT[0],sX,pTickeT[sX],sY);//O(1) (sX,sY) est absent
					//TicketVisionner(sC2b("Tickets pour le sommet",sEnt(sX)),pTickeT[sX]);
				}
			//if (kbTicketVoiR) TycketAfficherTouT(pgG);//O(S2)
		}else for (nT=0;nT<=nTicket;nT++)//O(S)
				TicketRestituer(pTickeT[nT]);//O(1);restitue le bloc attribué à la deque
	}
}//TycketAllouerTouT
