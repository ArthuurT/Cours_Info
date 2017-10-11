#include "Outil.h"
#include "Graphe.h"
#include "Tp2.h"
#define kuSommetMax 100
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

void DistancierAvecFloyd(graf * pgG, int nDist[][1+kuSommetMax], int * pnComplexiteh){
	

		int aK,sX,sY;//a comme arc;s comme sommet
		int uL,uC;//u comme entier supérieur ou égal à un;L=ligne,C=colonne.
		int nSommet=pgG->nSommetEnTout;
		int dM[1+nSommet][1+nSommet];//matrice des distances,supposées être des entiers ou des réels déjà ramenés à des entiers
		int P[1+nSommet][1+nSommet];
		int i, j, I, J, K;
		int cpt = 0;



	
		for (uL=1;uL<=nSommet;uL++){
			cpt++;
			for (uC=1;uC<=nSommet;uC++){
				dM[uL][uC]=0;
				cpt++;
			}
		}

		for (sX=1;sX<=nSommet;sX++){
			cpt++;
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				cpt++;
				sY=pgG->sSuk[aK];
				dM[sX][sY]=pgG->coulh[aK];//distance (sX,sY)
			}
		}

		

		for(i = 1; i <= nSommet; i++){			//initialise P à 0
			cpt++;
			for(j = 1; j <= nSommet; j++){
				P[i][j] = 0;
				cpt++;
			}
		}

		for(i = 1; i <= nSommet; i++){			//initialise nDist à l'infini
			cpt++;
			for(j = 1; j <= nSommet; j++){
				if(i == j) nDist[i][j] = 0;
				else nDist[i][j] = 999999;
				cpt++;
			}
		}
	
		/* Algo de Floyd */


			for(sX = 1; sX <= nSommet; sX++){
				P[sX][sX] = 0;
				for(sY = 1; sY <= nSommet; sY++){
					if(sX != sY && dM[sX][sY]!=0){
						nDist[sX][sY] = dM[sX][sY];
						P[sX][sY] = sX;
					}						
				}
			} 

			for(K = 1; K <= nSommet; K++){
				for(I = 1; I <= nSommet; I++){
					for(J = 1; J <= nSommet; J++){
						if(nDist[I][J] > nDist[I][K] + nDist[K][J]){
							nDist[I][J] = nDist[I][K] + nDist[K][J];
							P[I][J] = P[K][J];
						}
			
					}
				}
			}

	

		for(i = 1; i <= nSommet; i++){
			for(j = 1; j <= nSommet; j++){
				printf("| %8d |",nDist[i][j]);
			}
			printf("\n");
		}


		*pnComplexiteh = cpt;
		printf("Complexite: %i",*pnComplexiteh);

}

void DistancierAvecDijkstra(graf *pgG,int sSource,int nDist[1+kuSommetMax], int *pnComplexiteh){//O(S2)
	//rend le plus court chemin qui relie sSource à sTrappe; distances élémentR dans pgG->nCout[]. Algo plus court chemin, Dijkstra AVEC tas.
	const int kuInfini=9999;
	int nDistanceParX;
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int sProche;
	int uSommet;
	int sX,sY;
	*pnComplexiteh=0;
	//initialiser bFait[], nDist[] et pgG->sPer[].
		/*for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			bFait[sX]=0;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			nDist[sX]=kuInfini;
		for (sX=1; sX<=pgG->nSommetEnTout; sX++)
			pgG->sPer[sX]=0;*/
		VecteurRazer(bFait,1,pgG->nSommetEnTout);
		VecteurValuer(nDist,1,pgG->nSommetEnTout,kuInfini);
		VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
		TasAllouer(pgG->nSommetEnTout);

		for (sX=1; sX<=pgG->nSommetEnTout; sX++){
			TasInsererValuer(sX,kuInfini);
		}
		TasActualiser(sSource,0);

		VecteurCopier(pgG->coulh,1,pgG->nSommetEnTout+1,pgG->nCout);

		//TasVoir("Tas après initialisation");
		nDist[sSource]=0;//distance entre le sommet de départ et lui-même
		pgG->sPer[sSource]=sSource;//condition d'arrêt vitale pour bGrapheCheminE()
		for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
			//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sSource ne mène à aucun nouveau sommet par un chemin quelconque)
				//TasVoir("Tas avant extraction");
				sProche=eTasExtraire();
			sX=sProche;
			if (sX!=0) {
				for (aK=pgG->aHed[sX]; aK<pgG->aHed[sX+1]; aK++) {
					sY=pgG->sSuk[aK];
					nDistanceParX=nDist[sX]+pgG->nCout[aK];
					if ( nDist[sY]>nDistanceParX ) {
						nDist[sY]=nDistanceParX;
						pgG->sPer[sY]=sX;
						//tee("sY,nDistanceParX",sY,nDistanceParX);
						TasActualiser(sY,nDistanceParX);
						//TasVoir("Tas après TasActualiser");
					}
				}
				bFait[sX]=kV;
			}
		}//chaque sProche coûte O(S) et chaque arc est consulté 1 fois,soit une complexité au pire égale à sup( O(S*S),O(A) ), dc O(S2)
		//VecteurVoir("sPer",&pgG->sPer[0],1,pgG->nSommetEnTout);
		(*pnComplexiteh)+=nTasCout();
	TasAllouer(0);
}//nGrapheCheminerTaS





void Tp2TESTER(int iTest){
	//teste le présent module
	graf *pgG;
	int nComplexiteh;
	int uD;
	int i,j;
	int nSommet;
	int nDist[1+kuSommetMax][1+kuSommetMax];
	Appel0(sC2("Tp2TESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 1: //calcul du distancier avec Floyd
			GrapheCreer(8,&pgG);
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);
			DistancierAvecFloyd(pgG,nDist,&nComplexiteh);
			GrapheCreer(0,&pgG);
			break;
		case 2:	//calcul du distancier avec Dijkstra (avec Tas)		
			GrapheCreer(8,&pgG);
			GrapheAllouerInitialiseR(1,k1Afficher,&pgG);

			for(uD = 1; uD <= pgG->nSommetEnTout; uD++) DistancierAvecDijkstra(pgG,uD,nDist[uD],&nComplexiteh);

			/* Affichage */

			nSommet = pgG->nSommetEnTout;
			for(i = 1; i <= nSommet; i++){
				for(j = 1; j <= nSommet; j++){
					printf("| %8d |",nDist[i][j]);
				}
				printf("\n");
			}

			printf("Commplexité: %i",nComplexiteh);

			/************/

			GrapheCreer(0,&pgG);			

			break;
			
		default: ;
	}
	Appel1(sC2("Tp2TESTER,test n°",sEnt(iTest)));
}//Tp2TESTER	

