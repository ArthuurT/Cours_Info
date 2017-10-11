#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Tas.h"
#include "Abe.h"
#include "Tp5.h"
int bTp5AmorceR;//ie le module a effectivement été amorcé
int bTp5OuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un Tp5 est actuellement alloué

int nGrapheColorieR0(graf *pgG,int *puComplexiteh){//O(S2) ni Tas ni Abe
	const int k1Affiche=0;
	char *sCouleur[1+9]={"blanc","jaune","rouge","bleu","vert","orange","violet","marron","noir"};
	int aK,aL,sX,sY,uS,nDegrehMax,nCouleurLibre,nCouleurMax,uComplexiteh;
	int nCoche[1+pgG->nSommetEnTout];
	int nCouleur[1+pgG->nSommetEnTout];
	int nDegreh[1+pgG->nSommetEnTout];
	//Appel0("nGrapheColorieR0");
	Assert2("nGrapheColorieR0",bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	if (k1Affiche) te("pgG->nSommetEnTout",pgG->nSommetEnTout);
	uComplexiteh=1;
	DequeAllouer(pgG->nSommetEnTout);
		//nDegreh[sX]:=degré du sommet sX pour tout sX, le tout en O(A):
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				nDegreh[sX]=0;
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(A)
				//nDegreh[sX]+=degré sortant de sX,ie le nb de successeurs de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						nDegreh[pgG->sSuk[aK]]++;
				//nDegreh[sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
					for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
						nDegreh[pgG->sKus[aL]]++;
			}
			uComplexiteh+=pgG->nArcEnTout;
		//empiler les sommets en commençant par les sommets de plus haut degré, le tout en O(S2+A):
				for (uS=1;uS<=pgG->nSommetEnTout;uS++){//O(S2)
					//if (bTas) TasVoir("GrapheColorieR");
					//VecteurVoir1(sC2b("Degreh",sEnt(sX)),nDegreh,1,pgG->nSommetEnTout);
					//sX:=sommet de plus haut degré //O(S2)
						for (sX=0,nDegrehMax=-1,sY=1;sY<=pgG->nSommetEnTout;sY++)//∑=O(S2)
							if (nDegreh[sY]>=0 && nDegrehMax<=nDegreh[sY]){
								nDegrehMax=nDegreh[sY];
								sX=sY;
							}
						uComplexiteh+=pgG->nSommetEnTout;
						//printf("sommet élu: %d \n",sX);
					DequeEmpiler(sX);//O(1)
					//retirer virtuellt sX de pgG en décrémentant le degré des sommets voisins et en neutralisant sX 
						nDegreh[sX]=-1;//neutralise sX
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//∑=O(A)
							sY=pgG->sSuk[aK];
							nDegreh[sY]--;
						}
						uComplexiteh+=pgG->aHed[sX+1]-pgG->aHed[sX]+1;
				}
		//dépiler les sommets et les colorier, le tout en O(A):
			VecteurRazer(nCouleur,1,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			VecteurRazer(nCoche,0,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			for (nCouleurMax=0,uS=1;uS<=pgG->nSommetEnTout;uS++){//O(A)
				sX=sDequeDepiler();//O(1)
				//cocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=1;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
					//VecteurVoir("nCoche",nCoche,1,pgG->nSommetEnTout);
				//nCouleurLibre soit la plus petite couleur disponible 
					for (nCouleurLibre=1;nCouleurLibre<=pgG->nSommetEnTout;nCouleurLibre++)
						if (nCoche[nCouleurLibre]==0)
							break;
					uComplexiteh+=nCouleurLibre;
				nCouleur[sX]=nCouleurLibre;
				nCouleurMax=iSup(nCouleurMax,nCouleurLibre);
				if (k1Affiche) printf("Le sommet %d est coloré en %s.\n",sX,sCouleur[nCouleurLibre]);
				//décocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=0;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
			}
	DequeAllouer(0);
	if (k1Affiche) printf ("Nombre total de couleurs:%d.\n",nCouleurMax);
	*puComplexiteh=uComplexiteh;
	//Appel1("nGrapheColorieR0");
	return(nCouleurMax);
}//nGrapheColorieR0

int nGrapheColorieR1(graf *pgG,int *puComplexiteh){//O(AlgS) avec Tas
	const int k1Affiche=0;
	char *sCouleur[1+9]={"blanc","jaune","rouge","bleu","vert","orange","violet","marron","noir"};
	int aK,aL,sX,sY,uS,nCouleurLibre,nCouleurMax,uComplexiteh;
	int nCoche[1+pgG->nSommetEnTout];
	int nCouleur[1+pgG->nSommetEnTout];
	int nDegreh[1+pgG->nSommetEnTout];
	Assert2("nGrapheColorieR1",bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	if (k1Affiche) te("pgG->nSommetEnTout",pgG->nSommetEnTout);
	//Appel0("nGrapheColorieR1");
	uComplexiteh=1;
	DequeAllouer(pgG->nSommetEnTout);
		//nDegreh[sX]:=degré du sommet sX pour tout sX
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				nDegreh[sX]=0;
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(A)
				//nDegreh[sX]+=degré sortant de sX,ie le nb de successeurs de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						nDegreh[pgG->sSuk[aK]]++;
				//nDegreh[sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
					for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
						nDegreh[pgG->sKus[aL]]++;
			}
			uComplexiteh+=pgG->nArcEnTout;
		//empiler les sommets en commençant par les sommets de plus haut degré, le tout en O(SlgS+SlgS+AlgS):
			TasAllouer(pgG->nSommetEnTout);
				if (k1Affiche) VecteurVoir("Degreh",nDegreh,1,pgG->nSommetEnTout);
				for (uS=1; uS<=pgG->nSommetEnTout; uS++)
					TasInsererValuer(uS,0);
				for (sX=1; sX<=pgG->nSommetEnTout; sX++)
					TasActualiser(sX,-nDegreh[sX]);
				if (k1Affiche) TasVoir("nGrapheColorieR après");
				for (uS=1;uS<=pgG->nSommetEnTout;uS++){//O(AlgS) vs O(S2)
					//if (bTas) TasVoir("GrapheColorieR");
					//VecteurVoir1(sC2b("Degreh",sEnt(sX)),nDegreh,1,pgG->nSommetEnTout);
					//sX:=sommet de plus haut degré //O(SlgS) vs O(S2)
						sX=eTasExtraire();//∑=O(SlgS)
						//printf("sommet élu: %d \n",sX);
					DequeEmpiler(sX);//O(1)
					//retirer virtuellt sX de pgG en décrémentant le degré des sommets voisins et en neutralisant sX 
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//∑=O(AlgS) vs O(A)
							sY=pgG->sSuk[aK];
							nDegreh[sY]--;
							if (bTasContient(sY))//O(1)
								TasActualiser(sY,-nDegreh[sY]);//O(lgS),et pour for aK,∑=O(AlgS).
						}
				}
				uComplexiteh+=nTasCout()+pgG->nArcEnTout;
			TasAllouer(0);
		//dépiler les sommets et les colorier, le tout en O(A):
			VecteurRazer(nCouleur,1,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			VecteurRazer(nCoche,0,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			for (nCouleurMax=0,uS=1;uS<=pgG->nSommetEnTout;uS++){//O(A)
				sX=sDequeDepiler();//O(1)
				//cocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=1;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
					//VecteurVoir("nCoche",nCoche,1,pgG->nSommetEnTout);
				//nCouleurLibre soit la plus petite couleur disponible 
					for (nCouleurLibre=1;nCouleurLibre<=pgG->nSommetEnTout;nCouleurLibre++)
						if (nCoche[nCouleurLibre]==0)
							break;
					uComplexiteh+=nCouleurLibre;
				nCouleur[sX]=nCouleurLibre;
				nCouleurMax=iSup(nCouleurMax,nCouleurLibre);
				if (k1Affiche) printf("Le sommet %d est coloré en %s.\n",sX,sCouleur[nCouleurLibre]);
				//décocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=0;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
			}
	DequeAllouer(0);
	if (k1Affiche) printf ("Nombre total de couleurs:%d.\n",nCouleurMax);
	*puComplexiteh=uComplexiteh;
	//Appel1("nGrapheColorieR1");
	return(nCouleurMax);
}//nGrapheColorieR1

int nGrapheColorieR2(graf *pgG,int *puComplexiteh){//O(A) avec Abe
	const int k1Affiche=0;
	const int kuPoidsInfini=100;
	char *sCouleur[1+9]={"blanc","jaune","rouge","bleu","vert","orange","violet","marron","noir"};
	int aK,aL,sX,sY,uS,nCouleurLibre,nCouleurMax,uComplexiteh,ipPile;
	int nCoche[1+pgG->nSommetEnTout];
	int nCouleur[1+pgG->nSommetEnTout];
	int nDegreh[1+pgG->nSommetEnTout];
	int nPile[1+pgG->nSommetEnTout];
	//Appel0("nGrapheColorieR2");
	Assert2("nGrapheColorieR2",bGrapheSimple(pgG),bGrapheSymetrique(pgG));
	if (k1Affiche) te("pgG->nSommetEnTout",pgG->nSommetEnTout);
	uComplexiteh=1;
	VecteurRazer(nPile,1,pgG->nSommetEnTout);
		//nDegreh[sX]:=degré du sommet sX pour tout sX
			for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S)
				nDegreh[sX]=0;
			for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(A)
				//nDegreh[sX]+=degré sortant de sX,ie le nb de successeurs de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						nDegreh[pgG->sSuk[aK]]++;
				//nDegreh[sX]+=degré entrant de sX,ie le nb de prédécesseurs de sX
					for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++)
						nDegreh[pgG->sKus[aL]]++;
			}
			uComplexiteh+=pgG->nArcEnTout;
		//empiler les sommets en commençant par les sommets de plus haut degré
			AbeAllouer(pgG->nSommetEnTout,-kuPoidsInfini);
				//VecteurVoir1("Degreh",nDegreh,1,pgG->nSommetEnTout);
				for (sX=1; sX<=pgG->nSommetEnTout; sX++)
					AbeModifier(sX,nDegreh[sX]);
				//if (k1Affiche) AbeVoir("nGrapheColorieR après");
				for (ipPile=0,uS=1;uS<=pgG->nSommetEnTout;uS++){
					AbePropager();//∑=O(inf(2S,SlgS))
					//AbeVoir("GrapheColorieR2");
					//VecteurVoir1(sC2b("Degreh",sEnt(sX)),nDegreh,1,pgG->nSommetEnTout);
					//sX:=sommet de plus haut degré //O(SlgS)
						sX=eAbeExtraire();//O(lgS)
						//printf("sommet élu: %d \n",sX);
					nPile[++ipPile]=sX;//O(1)
					//retirer virtuellt sX de pgG en décrémentant le degré des sommets voisins et en neutralisant sX 
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//∑=O(A)
							sY=pgG->sSuk[aK];
							nDegreh[sY]--;
							if (bAbeContient(sY))//O(1)
								AbeModifier(sY,nDegreh[sY]);//O(1)
						}
				}
				uComplexiteh+=pgG->nArcEnTout+nAbeCout();//ie for aK et Abe
			AbeAllouer(0,-kuPoidsInfini);
			//VecteurVoir("nPile",nPile,1,ipPile);
		//dépiler les sommets et les colorier, le tout en O(A):
			VecteurRazer(nCouleur,1,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			VecteurRazer(nCoche,0,pgG->nSommetEnTout);//O(S)
			uComplexiteh+=pgG->nSommetEnTout;
			for (nCouleurMax=0,uS=1;uS<=pgG->nSommetEnTout;uS++){//O(A)
				sX=nPile[ipPile--];//O(1)
				//te("sX",sX);
				//cocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=1;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
					//VecteurVoir("nCoche",nCoche,1,pgG->nSommetEnTout);
				//nCouleurLibre soit la plus petite couleur disponible 
					for (nCouleurLibre=1;nCouleurLibre<=pgG->nSommetEnTout;nCouleurLibre++)
						if (nCoche[nCouleurLibre]==0)
							break;
					uComplexiteh+=nCouleurLibre;
				nCouleur[sX]=nCouleurLibre;
				nCouleurMax=iSup(nCouleurMax,nCouleurLibre);
				if (k1Affiche) printf("Le sommet %d est coloré en %s.\n",sX,sCouleur[nCouleurLibre]);
				//décocher les couleurs prises par les voisins de sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)//∑=O(A)
						nCoche[nCouleur[pgG->sSuk[aK]]]=0;
					uComplexiteh+=(pgG->aHed[sX+1]-pgG->aHed[sX]+1);
			}
	if (k1Affiche) printf ("Nombre total de couleurs:%d.\n",nCouleurMax);
	*puComplexiteh=uComplexiteh;
	//Appel1("nGrapheColorieR2");
	return(nCouleurMax);
}//nGrapheColorieR2

void Tp5AMORCER(){
	//amorce le présent module une fois pour toutes
	bTp5AmorceR=kV;
	bTp5OuverT=kF;
}//Tp5AMORCER

void Tp5INITIALISER(){//O(?)
	//relance le présent module
	Assert2("Tp5INITIALISER",bTp5AmorceR,!bTp5OuverT);
}//Tp5INITIALISER

void Tp5TESTER(int iTest){
	//teste le présent module
	const int kuGrapheEnTout=50;
	const int kuSommetMax=100;
	int bArete,nColorier0,nColorier1,nColorier2,uComplexiteh0,uComplexiteh1,uComplexiteh2,uG,uSommet,sX,sY;
	int nCouleur0=0,nCouleur1=0,nCouleur2=0;
	float fDensiteh;
	graf *pgG;
	Appel0(sC2("Tp5TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul de la densité d'un graphe simple aléatoire
				for (bArete=0;bArete<=1;bArete++){//bArete=1 <=> graphe non orienté
					for (uG=1;uG<=kuGrapheEnTout;uG++){
						uSommet=uHasard(kuSommetMax);//uSommet est donc non nul
						GrapheCreer(-uSommet,&pgG);//alloue un graphe sans arc
							//ajouter à pgG des arcs pris au hasard
								for (sX=1;sX<=uSommet;sX++)
									for (sY=1;sY<=uSommet;sY++)
										if ((sX!=sY) && nHasard(2))
											GrapheArquer(pgG,sX,sY);
							if (pgG->nArcEnTout>0){
								//si le graphe est non orienté, toute arête [X,Y] doit être représentée par deux arcs (X,Y) et (Y,X)
									if (bArete && pgG->nArcEnTout>0)
										GrapheSymetriser(pgG);//si un arc (X,Y) n'a pas d'arc inverse (Y,X),ajoute cet arc.
								GrapheVoir(pgG,sC2("Graphe n°",sEnt(uG)));
								fDensiteh=fGrapheDensiteh(pgG);
								printf("densité du graphe:%.1f.\n",fDensiteh);
							}
						GrapheCreer(0,&pgG);//restitue le graphe
					}
				}
			break;
		default:
		case 2: //heuristique de coloriage de graphe non orienté
				Titrer("Test de l'heuristique de coloration de graphe par pile");
				printf("  Sommets    Densité    Nombre minimum de couleurs    Temps d'exécution de l'algo    Gain en vitesse\n");
				printf(" %8s%12s  %8s %8s %8s     %8s  %8s %8s %8s %8s \n","en tout","du graphe","RIEN","TAS ","ABE ","RIEN","TAS ","ABE ","TAS ","ABE ");
				for (uSommet=5;uSommet<=kuSommetMax;uSommet+=10){
					GrapheCreer(-uSommet,&pgG);
						for (sX=1;sX<=uSommet;sX++)
							for (sY=1;sY<=uSommet;sY++)
								if (sX<sY && nHasard(8)>=4)//**choisir une valeur dans 0..7 pour modifier la densité du graphe généré.
									GrapheArquer(pgG,sX,sY);
						if (pgG->nArcEnTout>0){
							//GrapheVoir(pgG,sC2("Graphe orienté n°",sEnt(uG)));
							GrapheSymetriser(pgG);
							//GrapheVoir(pgG,sC2("Graphe non orienté n°",sEnt(uG)));
							nCouleur0+=(nColorier0=nGrapheColorieR0(pgG,&uComplexiteh0));
							nCouleur1+=(nColorier1=nGrapheColorieR1(pgG,&uComplexiteh1));
							nCouleur2+=(nColorier2=nGrapheColorieR2(pgG,&uComplexiteh2));
							printf("%8d%10.2f    %8d %8d %8d",uSommet,fGrapheDensiteh(pgG),nColorier0,nColorier1,nColorier2);
							printf("      %8d %8d %8d",uComplexiteh0,uComplexiteh1,uComplexiteh2);
							printf("%10.2f %8.2f \n",uComplexiteh0/(1.0*uComplexiteh1),uComplexiteh0/(1.0*uComplexiteh2));
						}
					GrapheCreer(0,&pgG);//restitue le graphe
				}
				printf("Cumul couleurs:%5d %8d %8d.\n",nCouleur0,nCouleur1,nCouleur2);
			break;
			Assert1("Tp5TESTER",0);
			break;
	}
	Appel1(sC2("Tp5TESTER,test n°",sEnt(iTest)));
}//Tp5TESTER	

