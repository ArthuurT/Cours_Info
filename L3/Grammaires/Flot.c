#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Flot.h"
//structure de données du graphe courant G
/*const int knArcMaX = 100;
const int knSommetMaX = 10;*/

const int k1CoutMoyeN=kV;
int aTablE[kuTableauLigneMax][kuTableauLigneMax];

void CheminBrutAfficheR(graf gG,int sSource,int sTrappe,int nFlotNumero,int nFlotRequis);
void CheminConcisAfficheR(graf gG,int sSource,int sTrappe,int nFlotNumero,int nSommetInitial);
long zCheminDeCoutMinimalCalculeR(int sSource,int sTrappe,graf *pgG,int bCoutMoyen);//O(SA)
void CoutAltereR(int bAjouter,graf *pgG);
void FlotAugmenteR(graf *pgG,int sSource,int sTrappe);

void FlotAfficherParChemiN(graf *pgG,int sSource,int sTrappe,int nEcourte,char *sMessage);
void FlotAjouteR(graf *pgG,int nHeme,int nSommetInitial);
int bFlotAmorceR;//dédié FlotAmorceR
int bFlotCalculeR2(graf *pgG,int sSource1,int sTrappe1,int nFlotRequis1,int sSource2,int sTrappe2,int nFlotRequis2);
void FlotCoupeR(graf *pgG,int nHeme,int nSommetInitial);
void FlotMatriceR(graf *pgG);
void FlotPondereR(graf *pgG,int sSource,int sDestination,int nCapaMax,int nCout,int nPrix);
void FlotTesteR2(int nTest);
void FluxAjouteR(graf *pgG,int sOrigine,int sDestination);
int bFluxSuivanT(graf *pgG,int sSource,int *psDestination,long *pzCoutTotal);
void SystemeAfficheR(graf *pgG,int sSource,int sTrappe,char cVariable);

void CheminAfficheR(graf *pgG,char *sMessage){
	//énumère les triplets (origine,destination,flot) des arcs de pgG qui écoulent un flot non nul; si bTout, le flot considéré peut être nul.
	int bEncore,aK,nFlot,sX;
	long zCout=0;
	int bFlotNonNul;
	int cPasse;
	Assert2("CheminAfficheR",bFlotAmorceR,sMessage!=0);
	if (pgG->nArcEnTout>0){
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==1){
				//printf("%s sous la forme (source,cible≤coût) puis (source,cible:flot effectif):\n   ",sMessage);
				//printf("%s sous la forme (source,cible:flot effectif):\n   ",sMessage);
				printf("%s sous la forme (source,cible):\n   ",sMessage);
				if (0)//afficher ts les arcs sous la forme (source,cible≤coût) 
					for (sX=1;bEncore=sX<pgG->nSommetEnTout+1, !bEncore && bLigne(), bEncore;sX++)//bLigne() pr passer à la ligne en fin de boucle
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			}
			for (zCout=0,sX=1;sX<pgG->nSommetEnTout+1;sX++){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if ( nFlot=pgG->nPhi[aK], (nFlot>0) ){
						assert(nFlot==1);
						if (cPasse==1){//afficher l'arc aK car il écoule un flot non nul (ou >=0 si bTout)
							printf("(%d,%d) ",sX,pgG->sSuk[aK]);
							//printf("(%d,%d:%d*%d) ",sX,pgG->sSuk[aK],nFlot,pgG->nCout[aK]);
							if (nFlot>0)
								zCout+=nFlot*pgG->nCout[aK];
						}
						else bFlotNonNul=1;
					}
			}
			if (cPasse==1)
				printf("Coût total: %s.",sPluriel(zCout,"unité"));
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//CheminAfficheR

void CheminBrutAfficheR(graf gG,int sSource,int sTrappe,int nFlotNumero,int nFlotRequis){
	//affiche le chemin élémentaire PROVISOIRE trouvé par nFlotMaxCalculer() qui construit déconstruit pour obtenir un flot optimal.
	int nSommet,nEcourter,aK,uS,uSmax,sX,sZ;
	int bEcourter=nFlotRequis>0;//si vrai afficher -sX si sX est un sommet destination ds le graphe biparti original
	//Appel0("CheminBrutAfficheR");
		Assert1("CheminBrutAfficheR1",gG.sPer[sSource]==sSource);
		if (!bEcourter) printf("    Chemin n°%d de la source à la trappe:",nFlotNumero);
		//te("nFlotRequis",nFlotRequis);
		//afficher sommet par sommet le chemin qui relie sSource à sTrappe ——en partant de sSource:
			//te("gG.nSommetEnTout",gG.nSommetEnTout);
			//VecteurVoir("gG.sPer",gG.sPer,1,gG.nSommetEnTout);
			DequeAllouer(gG.nSommetEnTout);
				//empiler les sommets car ils jalonnent le chemin à afficher dans le sens inverse du sens requis pour l'affichage
					VecteurVoir2("CheminBrutAfficheR:pgG->sPer",gG.sPer,1,gG.nSommetEnTout);
					sX=sTrappe;
					While(gG.nSommetEnTout);
					while ( bWhile("CheminBrutAfficheR98",gG.sPer[sX]!=sX) ){
						//te("sX empilé",sX);
						DequeEmpiler(sX);
						sX=gG.sPer[sX];
					}
					//te("sX ultime empilé",sX);
					DequeEmpiler(sX);
				//afficher les sommets dans l'ordre requis pour l'affichage,ie en les dépilant: 
					uSmax=nDequeCardinal();
					for (nSommet=0,nEcourter=0,uS=uSmax;uS>0;uS--){
						sZ=sDequeDepiler();
						if (bEcourter){
							sX=( bCroit(nFlotRequis+1,sZ,2*nFlotRequis) )? -(sZ-nFlotRequis): sZ;
							if ( bCroitStrict(1,uS,uSmax) && bCroit(1,sZ,2*nFlotRequis) ){
								if (nEcourter==0) printf("(");
								printf("%d",sX);nEcourter++;
								if ( bCroit(1,sX,gG.nSommetEnTout) && bCroit(1,gG.sPer[sX],gG.nSommetEnTout) && (sX!=gG.sPer[sX]) ){
									aK=nGrapheArc(&gG,sX,gG.sPer[sX]);
									nSommet++;
									//if (gG.nCout[aK]!=0)
										printf(":%d",gG.nCout[aK]);
								}
								if ( bCroitStrict(2,uS,uSmax) )
									printf(",");else printf(") ");
							}
						}else {printf("%d",sZ);
							nSommet++;
							if ( bCroit(2,uS,uSmax) )
								printf(",");
						};
					};//for
			DequeAllouer(0);
		if (!bEcourter) printf(" (longueur %d).\n",nSommet);
	//Appel1("CheminBrutAfficheR");
}//CheminBrutAfficheR

void CheminConcisAfficheR(graf gG,int sSource,int sTrappe,int nFlotNumero,int nSommetInitial){
	//affiche le chemin élémentaire CONCIS: seuls les arcs remarquables (ie de coût unitaire) sont affichés.
	int nSommet,aK,uS,uSmax,sX,sZ;
	int nPoleEnTout=2*nSommetInitial;
	te("nPoleEnTout",nPoleEnTout);
	int uHeme0,uHeme1,nColonne0,nColonne1;
	//Appel0("CheminConcisAfficheR");
		Assert1("CheminBrutAfficheR1",gG.sPer[sSource]==sSource);
		printf("    Chemin n°%d de la source à la trappe:",nFlotNumero);
		//afficher sommet par sommet le chemin qui relie sSource à sTrappe ——en partant de sSource:
			//te("gG.nSommetEnTout",gG.nSommetEnTout);
			//VecteurVoir("gG.sPer",gG.sPer,1,gG.nSommetEnTout);
			DequeAllouer(gG.nSommetEnTout);
				//empiler les sommets car ils jalonnent le chemin à afficher dans le sens inverse du sens requis pour l'affichage
					sX=sTrappe;
					VecteurVoir2("CheminConcisAfficheR:pgG->sPer",gG.sPer,1,gG.nSommetEnTout);
					While(gG.nSommetEnTout);
					while ( bWhile("CheminConcisAfficheR67",gG.sPer[sX]!=sX) ){
						//te("sX empilé",sX);
						DequeEmpiler(sX);
						sX=gG.sPer[sX];
					}
					//te("sX ultime empilé",sX);
					DequeEmpiler(sX);
				//afficher les sommets dans l'ordre requis pour l'affichage,ie en les dépilant: 
					uSmax=nDequeCardinal();
					for (nSommet=0,uS=uSmax;uS>0;uS--){
						sZ=sDequeDepiler();
						if (gG.sPer[sZ]!=sZ)
							aK=nGrapheArc(&gG,gG.sPer[sZ],sZ);
						if ( gG.sPer[sZ]!=sZ && bCroit(nPoleEnTout+1,sZ,gG.nSommetEnTout) && bCroit(nPoleEnTout+1,gG.sPer[sZ],gG.nSommetEnTout) ){
							if (nSommetInitial>0){//afficher plutôt les colonnes source et cible de l'arc aK 
								uHeme0=1+(gG.sPer[sZ]-nPoleEnTout-1)/6;
								nColonne0=1+(uHeme0-1)%nSommetInitial;
								uHeme1=1+(sZ-nPoleEnTout-1)/6;
								nColonne1=1+(uHeme1-1)%nSommetInitial;
								if (nColonne0!=nColonne1)
									{//tee("uHeme0,uHeme1",uHeme0,uHeme1);
										printf("(%c,%c)",'@'+nColonne0,'@'+nColonne1);
										//printf(" %d %d ",gG.sPer[sZ],sZ);
									}
							}else printf("%s",sCouple(gG.sPer[sZ],sZ));
						}
						nSommet++;
					};//for
			DequeAllouer(0);
		printf(" (longueur %d).\n",nSommet);
	//Appel1("CheminConcisAfficheR");
}//CheminConcisAfficheR

long zCheminDeCoutMinimalCalculeR(int sSource,int sTrappe,graf *pgG,int bCoutMoyen){//O(SA)
	//décrit dans pgG->sPer[] un chemin améliorant de coût minimal s'il en existe;altère les champs sPer,nVal,nAugVal et aArcTo.
	const int kuInfini=kE6;//9999 pr la mise au point
	int aK,aL,sX,sY;
	int nArc[1+pgG->nSommetEnTout];
	int nCoutChallenger,nCoutDefendeur;
	long zCoutMinimal,zCoutSup;
	Assert3("zCheminDeCoutMinimalCalculeR0",bCroit(1,sSource,pgG->nSommetEnTout),bCroit(1,sTrappe,pgG->nSommetEnTout),sSource!=sTrappe);
	zCoutSup=yVecteurSup(pgG->nCout,1,pgG->nArcEnTout);
	//te("zCoutSup",zCoutSup);
	Assert1("zCheminDeCoutMinimalCalculeR (INFINI INSUFFISANT?)",zCoutSup<kuInfini);
	VecteurRazer(pgG->sPer,1,pgG->nSommetEnTout);
	VecteurValuer(pgG->nVal,1,pgG->nSommetEnTout,kuInfini);
	VecteurValuer(nArc,1,pgG->nSommetEnTout,1);
	pgG->nVal[sSource]=0;
	pgG->nAugVal[sSource]=kuInfini;
	//Appel0("zCheminDeCoutMinimalCalculeR");
		DequeAllouer(pgG->nSommetEnTout);
			DequeEnfiler(sSource);
//bCoutMoyen=kV;
			pgG->sPer[sSource]=sSource;//**************VITAL POUR RECONNAÎTRE L'EXTREMITÉ DU CHEMIN via CheminBrutAfficheR
			While(pgG->nSommetEnTout*pgG->nArcEnTout);//un multiplicande égal à 1 ne suffit pas
			do {//NB nPhi[] est invariant ds cette routine
				sX=sDequeDefiler();
				//balayer les arcs avant d'origine sX
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						if (pgG->nPhi[aK]<pgG->nCapaMax[aK]){
							sY=pgG->sSuk[aK];//extrémité de aK
							nCoutDefendeur=pgG->nVal[sY];
							nCoutChallenger=pgG->nVal[sX]+pgG->nCout[aK];
							if (bCoutMoyen){//comparer les réels A/a et B/b c'est comparer A*b et B*a
		//printf("Challenger vs Defendeur %f %f \n",nCoutChallenger/(nArc[sX]+1.0),nCoutDefendeur/(nArc[sY]+0.0));
								nCoutDefendeur*=nArc[sY];
								nCoutChallenger*=nArc[sX]+1;
		//printf("Challenger VS Defendeur %d %d \n",nCoutChallenger,nCoutDefendeur);
							}
							if (nCoutDefendeur>nCoutChallenger) {
								pgG->nVal[sY]=pgG->nVal[sX]+pgG->nCout[aK];
								nArc[sY]=nArc[sX]+1;
								//teee("Balayage avant sX,sY,pgG->nVal[sY]",sX,sY,pgG->nVal[sY]);
								pgG->sPer[sY]=sX;
								pgG->aArcTo[sY]=aK;
								pgG->nAugVal[sY]=yMin(pgG->nAugVal[sX],pgG->nCapaMax[aK]-pgG->nPhi[aK]);
								DequeEnfiler(sY);//ne fait rien si déjà enfilé
							}
						}
				//balayer les arcs arrière d'extrémité sX
					for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
						if (aL=pgG->aInv[aK],pgG->nPhi[aL]>0){
							sY=pgG->sKus[aK];//origine de aK
							nCoutDefendeur=pgG->nVal[sY];
							nCoutChallenger=pgG->nVal[sX]-pgG->nCout[aL];
							if (bCoutMoyen){
								nCoutDefendeur*=nArc[sX];
								nCoutChallenger*=nArc[sY]+1;
							}
							if (nCoutDefendeur>nCoutChallenger) {
								pgG->nVal[sY]=pgG->nVal[sX]-pgG->nCout[aL];
								nArc[sY]=nArc[sX]+1;
								//teee("Balayage arriere sX,sY,pgG->nVal[sY]",sX,sY,pgG->nVal[sY]);
								pgG->sPer[sY]=sX;
								pgG->aArcTo[sY]=aL;
								pgG->nAugVal[sY]=yMin(pgG->nAugVal[sX],pgG->nPhi[aL]);
								DequeEnfiler(sY);//ne fait rien si déjà enfilé
							}
						}
			} while (bWhile("zCheminDeCoutMinimalCalculeR",!bDequeVide()) );
		DequeAllouer(0);
		//te("pgG->sPer[sTrappe]",pgG->sPer[sTrappe]);
	//Appel1("zCheminDeCoutMinimalCalculeR");
	zCoutMinimal=pgG->nVal[sTrappe];
	if (bCoutMoyen)
		zCoutMinimal/=iSup(1,nArc[sTrappe]);//évite de diviser par 0 qd aucun chemin n'est trouvé.
	te("nArc[sTrappe]",nArc[sTrappe]);
	return(zCoutMinimal);//à ce point,sPer[sTrappe] aura ou non été mis à jour;si oui, il existe un chemin améliorant de coût minimal
}//zCheminDeCoutMinimalCalculeR

void CoutAltereR(int bAjouter,graf *pgG){
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		if (bAjouter)
			pgG->nCout[aK]+=pgG->nPoids[aK];
		else pgG->nCout[aK]-=pgG->nPoids[aK];
}//CoutAltereR

void FlotAfficher(graf *pgG,int bTout,char *sMessage){
	//énumère les triplets (origine,destination,flot) des arcs de pgG qui écoulent un flot non nul; si bTout, le flot considéré peut être nul.
	int bEncore,aK,nFlot,sX;
	long zCout=0;
	int bFlotNonNul;
	int cPasse;
	Assert3("FlotAfficher",bFlotAmorceR,sMessage!=0,bBool(bTout));
	if (pgG->nArcEnTout>0){
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==1){
				//printf("%s sous la forme (source,cible≤coût) puis (source,cible:flot effectif):\n   ",sMessage);
				//printf("%s sous la forme (source,cible:flot effectif):\n   ",sMessage);
				printf("%s sous la forme (source,cible):\n   ",sMessage);
				if (0)//afficher ts les arcs sous la forme (source,cible≤coût) 
					for (sX=1;bEncore=sX<pgG->nSommetEnTout+1, !bEncore && bLigne(), bEncore;sX++)//bLigne() pr passer à la ligne en fin de boucle
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			}
			for (zCout=0,sX=1;sX<pgG->nSommetEnTout+1;sX++){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if ( nFlot=pgG->nPhi[aK], bTout || (nFlot>0) ){
						assert(bTout || (nFlot==1));
						if (cPasse==1){//afficher l'arc aK car il écoule un flot non nul (ou >=0 si bTout)
							printf("(%d,%d) ",sX,pgG->sSuk[aK]);
							//printf("(%d,%d:%d*%d) ",sX,pgG->sSuk[aK],nFlot,pgG->nCout[aK]);
							if (nFlot>0)
								zCout+=nFlot*pgG->nCout[aK];
						}
						else bFlotNonNul=1;
					}
			}
			if (cPasse==1)
				printf("Coût total: %s.",sPluriel(zCout,"unité"));
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//FlotAfficher

void FlotAfficherParChemiN(graf *pgG,int sSource,int sTrappe,int nEcourte,char *sMessage){//O(A)
	//énumère flot élémentaire par flot élémentaire les arcs de pgG qui écoulent un flot UNITAIRE non nul.
	int nSommet,aK,nFlot,sX,sY,sZ;
	long zCout=0;
	int bEcourter=nEcourte>0;//si vrai afficher -sX si sX est un sommet destination ds le graphe biparti original
	int bFlotNonNul;
	int nFlux=0;
	int cPasse;
	Assert3("FlotAfficherParChemiN",bFlotAmorceR,bGrapheSommet(pgG,sSource),sMessage!=0);
	if (pgG->nArcEnTout>0) {
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)//O(A)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				aTablE[sX][sY]=aK;
			}
		//TableauVoir("aTablE",aTablE,1,pgG->nSommetEnTout,1,pgG->nSommetEnTout);
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==0){
				for (zCout=0,aK=1;aK<=pgG->nArcEnTout;aK++){//O(A)
					nFlot=pgG->nPhi[aK];
					if (nFlot>0) {
						//assert(nFlot==1);
						bFlotNonNul=1;
					}
				}//for zCout
			}else {printf("%s calculé par la routine \"FlotAfficherParChemiN\":\n",sMessage);
				//afficher ts les arcs sous la forme (source,cible≤coût) 
//bEcourter=kV;
					for (nFlux=0,zCout=0,aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++){
						nFlot=pgG->nPhi[aK];
						if (nFlot>0){
							//assert(nFlot==1);
							nFlux++;
							sX=sSource;
							sY=pgG->sSuk[aK];
							zCout+=pgG->nCout[aK];
							printf("   Chemin n°%d (flot élémentaire:%d): ",nFlux,nFlot);
								printf("(");
								if ( !bEcourter || bCroit(1,sX,2*nEcourte) )
									printf("%d",sX);
								nSommet=0;
								While(pgG->nSommetEnTout);
								do {
									nSommet++;
									sZ=sY;
									if ( bEcourter && bCroit(nEcourte+1,sY,2*nEcourte) )
										sZ=-(sY-nEcourte);
									//printf("%s",sCouple(sX,sY));
									if ( !bEcourter || bCroit(1,sY,2*nEcourte) )
										printf(",%d",sZ);
									sX=sY;
								} while( bWhile("FlotAfficherParChemiN",bFluxSuivanT(pgG,sX,&sY,&zCout)) );
							printf(") de longueur %d.\n",nSommet);
								//printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
	
						}
					}//for aK
				printf("Flot total: %s de flot pour un coût total de %s.",sPluriel(nFlux,"unité"),sPluriel(zCout,"unité"));
				//printf("Coût total: %s",sPluriel(zCout,"unité"));
			}
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//FlotAfficherParChemiN

void FlotAjouteR(graf *pgG,int nHeme,int nSommetInitial){
	//pgG->nPhi[aK]=1 sur tout arc qui supporte le préflot attaché à l'hème de rang0 nHeme (y compris connexions aux pôles). 
	int uLigne=1+nHeme/nSommetInitial;
	int uColonne=1+nHeme%nSommetInitial;
	int nPoleEnTout=2*nSommetInitial;
	int nOffset=nPoleEnTout+nHeme*6;
	int bGeneral=(uColonne>1) && (uLigne!=1) || (uColonne==1) && (uLigne!=nSommetInitial);
	//teeeee("FlotAjouteR:uLigne,uColonne,nHeme,nOffset,nSommetInitial",uLigne,uColonne,nHeme,nOffset,nSommetInitial);
	if (bGeneral){
		FluxAjouteR(pgG,nOffset+5,nOffset+1);
		FluxAjouteR(pgG,nOffset+4,nOffset+6);
		//pôle nord
			//tee("2*uColonne-1,nOffset+2",2*uColonne-1,nOffset+2);
			FluxAjouteR(pgG,2*uColonne-1,nOffset+2);
		//pôle sud
			FluxAjouteR(pgG,nOffset+3,2*uColonne+0);
	} else {
			FluxAjouteR(pgG,nOffset+5,nOffset+2);
			//FluxAjouteR(pgG,nOffset+1,nOffset+3);
			//FluxAjouteR(pgG,nOffset+3,nOffset+6);
	}
}//FlotAjouteR

void FlotAMORCER(){
	//amorce le présent module une fois pour toutes
	bFlotAmorceR=kV;
}//FlotAMORCER

void FlotAugmenteR(graf *pgG,int sSource,int sTrappe){
	//actualise algébriqt nPhi[] sur le chemin sSource sTrappe
	int nDelta;
	int aK;
	int sX;
	nDelta=pgG->nAugVal[sTrappe];
	Assert1("FlotAugmenteR",nDelta>0);//ie le flot augmente effectivement
	sX=sTrappe;
	While(pgG->nSommetEnTout);
	do {
		aK=pgG->aArcTo[sX];
		if (pgG->sSuk[aK]==sX)
			pgG->nPhi[aK]+=nDelta;
		else pgG->nPhi[aK]-=nDelta;
		sX=pgG->sPer[sX];
	} while (bWhile("FlotAugmenteR",sX!=sSource) );
}//FlotAugmenteR

int bFlotCalculeR2(graf *pgG,int sSource1,int sTrappe1,int nFlotRequis1,int sSource2,int sTrappe2,int nFlotRequis2){
	//calcule un biflot de coût minimal sur pgG qui décrit un graphe avec ses arcs inverses,ses capacités et ses deux coûts tous initialisés.
	//Poser x1=y1+y2-b et x2=y1-y2 pour minimiser (c1+c2)y1 + c1-c2)y2 -c1b sc (Ay1+aY2=r1+Ab , Ay1-Ay2=r2 , 0≤y1≤b , 0≤y2≤b) équivaut à minimiser...
	//...(c1+c2)y1 sc (Ay1=1/2(r1+r2+Ab) , Ay2=1/2(r1-r2+Ab) , 0≤y1≤b , 0≤y2≤b) et donc à effectuer les 2 minimisations indépendantes ci-dessous.
	int aK;
	int bFlot1=0;
	int bFlot12=0;
	int nPhi1[99];
	int nPhi2[99];
	int sSource;
	int sTrappe;
	Assert5("bFlotCalculer20",bFlotAmorceR,pgG->nArcEnTout>0,pgG->aInv[1]>0,nFlotRequis1>0,nFlotRequis2>0);
	Assert3("bFlotCalculer2a",bGrapheSommet(pgG,sSource1),bGrapheSommet(pgG,sTrappe1),sSource1!=sTrappe1);
	Assert3("bFlotCalculer2b",bGrapheSommet(pgG,sSource2),bGrapheSommet(pgG,sTrappe2),sSource2!=sTrappe2);
	//Appel0(sC8b("Flot2Calculer de",sEnt(sSource1),"à",sEnt(sTrappe1),"et de",sEnt(sSource2),"à",sEnt(sTrappe2)));
		//1° Minimiser (c1+c2)y1 sc (Ay1=1/2(r1+r2+Ab) , 0≤y1≤b) et sauvegarder les flux dans nPhi1[]
			GrapheSommer(pgG,+2);
				sSource=pgG->nSommetEnTout-1;
				GrapheArquer(pgG,sSource,sSource1);
				GrapheArquer(pgG,sSource,sSource2);
				sTrappe=pgG->nSommetEnTout;
				GrapheArquer(pgG,sTrappe,sTrappe1);
				GrapheArquer(pgG,sTrappe,sTrappe2);
				GrapheSymetriser(pgG);
				FlotPondereR(pgG,sSource,sSource1,1,0,0);
				FlotPondereR(pgG,sSource,sSource2,1,0,0);
				FlotPondereR(pgG,sTrappe,sTrappe1,1,0,0);
				FlotPondereR(pgG,sTrappe,sTrappe2,1,0,0);
				CoutAltereR(1,pgG);//ajoute les nPoids aux nCout pr obtenir (c1+c2)
					bFlot1=nFlotMaxCalculer(pgG,sSource,sTrappe,nFlotRequis1+nFlotRequis2,k1Afficher)>0;//initialise et rend pgG->nPhi[]
					if (bFlot1)
						FlotAfficher(pgG,kF,"Flot y1");
					if (bFlot1)
						FlotAfficherParChemiN(pgG,sSource1,sTrappe1,0,"Flot y1 chemin par chemin");
					for (aK=1;aK<=pgG->nArcEnTout;aK++)
						nPhi1[aK]=pgG->nPhi[aK];
					for (aK=1;aK<=pgG->nArcEnTout;aK++)
						nPhi1[aK]=pgG->nPhi[aK];
				CoutAltereR(0,pgG);//restaure les nCout
			GrapheSommer(pgG,-2);
/*
		//2° Minimiser (c1-c2)y2 sc (Ay1=1/2(r1-r2+Ab) , 0≤y2≤b) et sauvegarder les flux dans nPhi2[]
			GrapheSommer(pgG,+1);
				sSource=pgG->nSommetEnTout;
				GrapheArquer(pgG,sSource,sSource1);
				GrapheArquer(pgG,sSource,sSource2);
				GrapheSommer(pgG,+1);
					sTrappe=pgG->nSommetEnTout;
					GrapheArquer(pgG,sTrappe,sTrappe1);
					GrapheArquer(pgG,sTrappe,sTrappe2);
					CoutAltereR(0,pgG);//retranche les nPoids aux nCout pr obtenir (c1-c2)
						bFlot2=nFlotMaxCalculer(pgG,sSource,sTrappe,nFlotRequis1+nFlotRequis2)>0;//initialise et rend pgG->nPhi[]
						if (bFlot2)
							FlotAfficher(pgG,kF,"Flot y1");
						if (bFlot2)
							FlotAfficherParChemiN(pgG,sSource1,sTrappe1,"Flot y1 chemin par chemin");
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi2[aK]=pgG->nPhi[aK];
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi2[aK]=pgG->nPhi[aK];
					CoutAltereR(1,pgG);//restaure les nCout
				GrapheSommer(pgG,-1);
			GrapheSommer(pgG,-1);
		bFlot12=bFlot1 && bFlot2;
*/
bFlot12=kF;
		if (bFlot12){// Calculer les flots originaux de x1 et x2 à partir de y1 et y2
			// afficher le flux x1
				Titrer("Flot X1");
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					pgG->nPhi[aK]=nPhi1[aK]+nPhi2[aK]-pgG->nCapaMax[aK];//y1+y2-b
				FlotAfficher(pgG,kF,"Flot x1");
			// afficher le flux x2
				Titrer("Flot X2");
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					pgG->nPhi[aK]=nPhi1[aK]-nPhi2[aK];//y1-y2
				FlotAfficher(pgG,kF,"Flot x2");
				if (1)
					FlotAfficherParChemiN(pgG,sSource2,sTrappe2,0,"Flot X2 chemin par chemin");
		}
	//Appel1(sC8b("Flot2Calculer de",sEnt(sSource1),"à",sEnt(sTrappe1),"et de",sEnt(sSource2),"à",sEnt(sTrappe2)));
	return(bFlot12);
}//bFlotCalculeR2

void FlotCapaciter(graf *pgG,int sOrigine,int sDestination,int nCapacitehMaximale){
	//attribue la capacité sCapacitehMaximale à l'arc (sOrigine,sDestination) de gG, ou à tous les arcs ssi sOrigine=sDestination=0
	int  bCapaciter=kF,aK;
	Assert4("FlotCapaciter1",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCapacitehMaximale>=0);
	Assert1("FlotCapaciter2",(sOrigine==0) == (sDestination==0));
	//teee("sOrigine,sDestination,nCapacitehMaximale",sOrigine,sDestination,nCapacitehMaximale);
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nCapaMax[aK]=nCapacitehMaximale;
		bCapaciter=kV;
		}
	else for (bCapaciter=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination){
			pgG->nCapaMax[aK]=nCapacitehMaximale;
			bCapaciter=kV;
		}
	Assert1("FlotCapaciter3",bCapaciter);		
}//FlotCapaciter

int bFlotCompatible(graf *pgG,int szSource,int szTrappe,int bAfficher){//O(S2A)
	//rend vrai ssi pgG a un flot compatible avec les capacités minimales spécifiées sur chaque arc. Si vrai, phi[aK] est le flot compatible sur l'arc aK.
	int nCapacitehDeRetour,bCompatible,nEntrance,nSortance,nSource,sSource,nTrappe,sTrappe;
	int nFlotMax,nbSommetInitial;
	int sS,sT,sU,sV;
	int aK,aL,sX,sY;
	int nFlotCompatible,nFlotCompatible0,nFlotCompatible1;
	int nCiblant[1+pgG->nSommetEnTout];
	int nSortant[1+pgG->nSommetEnTout];
	//Appel0(sC4b("bFlotCompatibleCalculer1 de la source",sEnt(sSource),"à la trappe",sEnt(sTrappe)));
		Assert3("bFlotCompatibleCalculer1",bFlotAmorceR,pgG->nArcEnTout>0,pgG->nSommetEnTout+4+!szSource+!szTrappe<kuGrapheSommetLim);
		Assert3("bFlotCompatibleCalculer2",!szSource || bGrapheSommet(pgG,szSource),!szTrappe || bGrapheSommet(pgG,szTrappe),!szSource || szSource!=szTrappe);
		sSource=szSource;
		sTrappe=szTrappe;
		if (!szSource){
			GrapheSommer(pgG,+2);
			sSource=pgG->nSommetEnTout-1;
			sTrappe=pgG->nSommetEnTout;
			//connecter à sSource tout sommet sans prédécesseur dans le graphe fourni
				for (nSource=0,sX=1;sX<=pgG->nSommetEnTout-2;sX++)
					if (pgG->aHed[sX]==pgG->aHed[sX+1]){
						GrapheArquer3(pgG,sSource,sX,0,1,0);//3 poids: capa min,capa max,coût.
						nSource++;
					}
			//connecter à sTrappe tout sommet sans successeur
				GrapheInverser(pgG);
				for (nTrappe=0,sY=1;sY<=pgG->nSommetEnTout-2;sY++)
					if (pgG->aDeh[sY]==pgG->aDeh[sY+1]){
						GrapheArquer3(pgG,sY,sTrappe,0,1,0);
						nTrappe++;
					}
			tee("nSource,nTrappe",nSource,nTrappe);
		}
		//bCompatible:= 0≤nCapaMin≤nCapaMax et nCout≥0 pour tous les arcs de pgG
			for (bCompatible=kV,aK=1;aK<=pgG->nArcEnTout;aK++){
				bCompatible=bCompatible && (pgG->nCapaMin[aK]>=0);
				bCompatible=bCompatible && (pgG->nCapaMin[aK]<=pgG->nCapaMax[aK]);
				bCompatible=bCompatible && (pgG->nCout[aK]>=0);
			}
		if (bCompatible){
			//printf("La recherche d'un flot compatible est en cours, patienter SVP.\n");
			nbSommetInitial=pgG->nSommetEnTout;
			GrapheSommer(pgG,+4);//empile 4 nouveaux sommets
				sS=pgG->nSommetEnTout-3;
				sT=pgG->nSommetEnTout-2;
				sU=pgG->nSommetEnTout-1;
				sV=pgG->nSommetEnTout;
				GrapheInverser(pgG);//notamment pr calculer nCiblant[],cf "for aL"
				GrapheVoir4(pgG,sC8("Graphe après ajout de sS=",sEnt(sS),", sT=",sEnt(sT),", sU=",sEnt(sU)," et sV=",sEnt(sV)));
				printf("Ajout des arcs incidents à sU et sV...\n");
					//pour tout sX de G initial, ajouter (sU,sX) avec pour capa max la somme des capa min des arcs qui ciblent sX
						//nCiblant[sX]:=somme des capa min des arcs qui ciblent sX dans le graphe G initial
							VecteurRazer(nCiblant,1,nbSommetInitial);
							for (sY=1;sY<=nbSommetInitial;sY++)
								for (aL=pgG->aDeh[sY];aL<pgG->aDeh[sY+1];aL++){
									sX=pgG->sKus[aL];
									aK=pgG->aInv[aL];//car pgG->nCapaMin[aL] n'est pas en général pgG->nCapaMin[aK]
									//printf("arqq (%d,%d:%d) ",sX,sY,pgG->nCapaMin[aK]);
									Assert1("bFlotCompatibleCalculer23",bGrapheArc(pgG,sX,sY));
									nCiblant[sY]+=pgG->nCapaMin[aK];
								}
							VecteurVoir1("nCiblant[]",nCiblant,1,nbSommetInitial);
						for (sX=1;sX<=nbSommetInitial;sX++)
							if (nCiblant[sX]>0){
								GrapheArquer3(pgG,sU,sX,0,nCiblant[sX],0);//3 poids: capa min,capa max,coût.
								teee("(sU,sX,capamin)",sU,sX,nCiblant[sX]);
							}
						//GrapheVoir4(pgG,sC2("Ajout des arcs d'origine sU=",sEnt(sU)));
					//pour tout sX, ajouter un arc (sX,sV) avec pour capa max la somme des capa min des arcs d'origine sX
						//nSortant:=somme des capa min des arcs d'origine sX dans le graphe G initial
							VecteurRazer(nSortant,1,nbSommetInitial);
							for (sX=1;sX<=nbSommetInitial;sX++)
								for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
									sY=pgG->sSuk[aK];
									//printf("arqq (%d,%d:%d) ",sX,sY,pgG->nCapaMin[aK]);
									nSortant[sX]+=pgG->nCapaMin[aK];
								}
							VecteurVoir1("nSortant[]",nSortant,1,nbSommetInitial);
						for (sX=1;sX<=nbSommetInitial;sX++)
							if (nSortant[sX]>0){
								GrapheArquer3(pgG,sX,sV,0,nSortant[sX],0);//3 poids: capa min,capa max,coût.
								teee("(sX,sV,capamin)",sX,sV,nSortant[sX]);
							}
						//GrapheVoir4(pgG,sC2("Ajout des arcs à destination de sV=",sEnt(sV)));
					//GrapheSymetriser(pgG);
					GrapheInverser(pgG);
				//ajouter 3 arcs (t,s),(s,sSource) et (sTrappe,t) de capa min 0 et de capa max suffisante pour accepter tout flot maximal.
					//nCapacitehDeRetour:=inf(somme des capa max des arcs qui quittent sSource, qui ciblent sTrappe).
						for (nEntrance=0,aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
							nEntrance+=pgG->nCapaMax[aK];
						for (nSortance=0,aL=pgG->aDeh[sTrappe];aL<pgG->aDeh[sTrappe+1];aL++){
							sX=pgG->sKus[aL];
							aK=pgG->aInv[aL];//car pgG->nCapaMin[aL] n'est pas en général pgG->nCapaMin[aK]
							//teee("sX,sTrappe,pgG->nCapaMax[aK]",sX,sTrappe,pgG->nCapaMax[aK]);
							nSortance+=pgG->nCapaMax[aK];
						}
						nCapacitehDeRetour=iInf(nEntrance,nSortance);
						teee("nEntrance,nSortance,nCapacitehDeRetour",nEntrance,nSortance,nCapacitehDeRetour);
					GrapheArquer3(pgG,sT,sS,0,nCapacitehDeRetour,0);
					GrapheArquer3(pgG,sS,sSource,0,nCapacitehDeRetour,0);
					GrapheArquer3(pgG,sTrappe,sT,0,nCapacitehDeRetour,0);
				//remplacer chaque capa max du graphe par la différence capamax - capamin (positive ou nulle)
					for (aK=1;aK<pgG->nArcEnTout;aK++)
						pgG->nCapaMax[aK]=pgG->nCapaMax[aK]-pgG->nCapaMin[aK];
				//nFlotCompatible:=flot maximal issu de sU et à destination sV
					for (nFlotCompatible0=0,sX=1;sX<=nbSommetInitial;sX++)
						nFlotCompatible0+=nCiblant[sX];
					for (nFlotCompatible1=0,sX=1;sX<=nbSommetInitial;sX++)
						nFlotCompatible1+=nSortant[sX];
					Assert1("bFlotCompatible41",nFlotCompatible0==nFlotCompatible1);//par construction des arcs incidents à sU et sV
					nFlotCompatible=iInf(nFlotCompatible0,nFlotCompatible1);
				GrapheVoir4(pgG,sC2b("Graphe pour lequel un flot minimal est cherché, de valeur",sEnt(nFlotCompatible)));
				nFlotMax=nFlotMaxCalculer(pgG,sU,sV,nFlotCompatible,k1Afficher);
			GrapheSommer(pgG,-4);//retire les arcs liés aux 4 derniers sommets empilés, puis ceux-ci.
			bCompatible=(nFlotMax==nFlotCompatible);
			printf("Le flot minimal requis (de valeur %d) %s atteint%s.\n",nFlotCompatible,sEst(bCompatible),sChoix0(!bCompatible,sC3(" (valeur ",sEnt(nFlotMax),")")));
		} else printf("Le flot n'est pas compatible.\n");
	//Appel1(sC4b("bFlotCompatibleCalculer1 de la source",sEnt(sSource),"à la trappe",sEnt(sTrappe)));
	return(bCompatible);
}//bFlotCompatible

void FlotCoupeR(graf *pgG,int nHeme,int nSommetInitial){
	//pgG->nPhi[aK]=1 sur tout arc qui supporte le préflot attaché à l'hème de rang0 nHeme (y compris connexions aux pôles). 
	int uLigne=1+nHeme/nSommetInitial;
	int uColonne=1+nHeme%nSommetInitial;
	int nPoleEnTout=2*nSommetInitial;
	int nOffset=nPoleEnTout+nHeme*6;
	int bGeneral=(uColonne>1) && (uLigne!=1) || (uColonne==1) && (uLigne!=nSommetInitial);
	//teeeeee("uLigne,uColonne,nHeme,nOffset,nPoleEnTout,nSommetInitial",uLigne,uColonne,nHeme,nOffset,nPoleEnTout,nSommetInitial);
	if (bGeneral){
		FlotCapaciter(pgG,nOffset+1,nOffset+3,0);
		FlotCapaciter(pgG,nOffset+2,nOffset+4,0);
	} else {
		FlotCapaciter(pgG,nOffset+3,nOffset+6,0);
		FlotCapaciter(pgG,nOffset+2,nOffset+4,0);
	}
}//FlotCoupeR

void FlotCouter1(graf *pgG,int sOrigine,int sDestination,int nCout){
	//attribue le coût nCout à pgG->nCout[aK] tel que aK est l'arc (sOrigine,sDestination), ou à tous les arcs ssi sOrigine=sDestination=0 
	int  bCouter1,aK;
	Assert4("FlotCouter1",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCout>=0);
	Assert1("FlotCouter11",(sOrigine==0) == (sDestination==0));
	bCouter1=kF;
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nCout[aK]=nCout;
		bCouter1=kV;
		}
	else {
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
			if (pgG->sSuk[aK]==sDestination){
				pgG->nCout[aK]=nCout;
				bCouter1=kV;
			}
		for (aK=pgG->aHed[sDestination];aK<pgG->aHed[sDestination+1];aK++)
			if (pgG->sSuk[aK]==sOrigine){
				pgG->nCout[aK]=nCout;
				bCouter1=kV;
			}
		}
	Assert1("FlotCouter1",bCouter1);		
}//FlotCouter1

void FlotCouter2(graf *pgG,int sOrigine,int sDestination,int nCout){
	//attribue le coût nCout à pgG->nPoids[aK] tel que aK est l'arc (sOrigine,sDestination), ou à tous les arcs ssi sOrigine=sDestination=0 
	int  bCouter2,aK;
	Assert4("FlotCouter2",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCout>=0);
	Assert1("FlotCouter21",(sOrigine==0) == (sDestination==0));
	bCouter2=kF;
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nPoids[aK]=nCout;
		bCouter2=kV;
		}
	else {
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
			if (pgG->sSuk[aK]==sDestination){
				pgG->nPoids[aK]=nCout;
				bCouter2=kV;
			}
		for (aK=pgG->aHed[sDestination];aK<pgG->aHed[sDestination+1];aK++)
			if (pgG->sSuk[aK]==sOrigine){
				pgG->nPoids[aK]=nCout;
				bCouter2=kV;
			}
		}
	Assert1("FlotCouter2",bCouter2);		
}//FlotCouter2

void FlotINITIALISER(){//O(?)
	//relance le présent module
	Assert1("FlotINITIALISER",bFlotAmorceR);
}//FlotINITIALISER

void FlotMatriceR(graf *pgG){
	//affiche pgG sous forme matricielle
	int uC;
	int aK;
	int bArc[1+pgG->nSommetEnTout];
	int sX;
	int sY;
	Assert1("FlotMatriceR",bFlotAmorceR);
	assert(bGrapheSimple(pgG));
	printf("Matrice du graphe direct (sommet source en ligne,sommet destination en colonne):\n");
		for (uC=0;uC<=pgG->nSommetEnTout;uC++)
			printf("%3d",uC);//colonne
		printf("\n");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (uC=1;uC<=pgG->nSommetEnTout;uC++)
				bArc[uC]=0;
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				bArc[sY]++;
			}
			//afficher la ligne courante
				printf("%3d",sX);//ligne
				for (uC=1;uC<=pgG->nSommetEnTout;uC++)
					printf("%3d",bVrai(bArc[uC]));
				printf("\n");
		}
}//FlotMatriceR

int nFlotMaxCalculer(graf *pgG,int sSource,int sTrappe,int nFlotRequis,int bAfficher){//O(S2A)
	//calcule et rend dans pgG->nPhi[] le flot nFlotRequis à coût minimal sur pgG,un graphe avec arcs inverses,capacités et coûts initialisés.
	const int bEcourter=kV;
	long zCoutTotal;
	int nFlotAtteint;
	int nFlotNumero;
	int bCalculer,aK,nEcourte;
	int bTrappeAtteinte;
	int zCoutMinimal;
//t("ENTRE");
	Appel0(sC4b("FlotCalculer de la source",sEnt(sSource),"à la trappe",sEnt(sTrappe)));
		GrapheInverser(pgG);
		Assert4("nFlotMaxCalculer1",bFlotAmorceR,pgG->nArcEnTout>0,pgG->aInv[1]>0,nFlotRequis>=0);
		Assert3("nFlotMaxCalculer2",bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe),sSource!=sTrappe);
		//GrapheInverser(pgG);
		bCalculer=(nFlotRequis>0);
		VecteurRazer(pgG->nPhi,1,pgG->nArcEnTout);//valeur du flot qui passera ds l'arc aK
		nFlotAtteint=0;
		if (bCalculer){//algo de Busacker p227
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				bCalculer=bCalculer && (pgG->nCapaMax[aK]>=0);//capacités unitaires
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				bCalculer=bCalculer && (pgG->nCout[aK]>=0);//coûts unitaires
			if (bCalculer){
				nFlotAtteint=nFlotNumero=zCoutTotal=0;
				nEcourte=(bEcourter)? nFlotRequis: 0;//si bEcourter, seules les extrémités utiles des chemins seront affichées.
				if (0 && bAfficher)
					GrapheVoir(pgG,"Graphe de flot");
				While(pgG->nSommetEnTout);
				do {//accroître le flot en ajoutant à chaque étape un flot élémentaire de coût minimal et atteindre si possible le seuil zFlotRequis.
					zCoutMinimal=zCheminDeCoutMinimalCalculeR(sSource,sTrappe,pgG,!k1CoutMoyeN);//O(SA)
					//te("zCoutMinimal",zCoutMinimal);
					bTrappeAtteinte=pgG->sPer[sTrappe]!=0;
					//tb("bTrappeAtteinte",bTrappeAtteinte);
					if (bTrappeAtteinte) {
						nFlotNumero++;
						if (0 && bAfficher)
							CheminBrutAfficheR(*pgG,sSource,sTrappe,nFlotNumero,nEcourte);
						pgG->nAugVal[sTrappe]=iMin(pgG->nAugVal[sTrappe],nFlotRequis-nFlotAtteint);
						FlotAugmenteR(pgG,sSource,sTrappe);//actualise exclusivt nPhi[] algébriqt sur le chemin sSource sTrappe
						nFlotAtteint+=pgG->nAugVal[sTrappe];
					te("                  Flot cumulé obtenu",nFlotAtteint);
						zCoutTotal+=pgG->nAugVal[sTrappe]*zCoutMinimal;
					};
				} while (bWhile("nFlotMaxCalculer",bTrappeAtteinte && (nFlotAtteint<nFlotRequis)) );
				if (0 && bAfficher)
					FlotAfficherParChemiN(pgG,sSource,sTrappe,nEcourte,"Flot optimal final décomposé chemin par chemin");
			}
		}
	Appel1(sC4b("FlotCalculer de la source",sEnt(sSource),"à la trappe",sEnt(sTrappe)));
	te("nFlotAtteint",nFlotAtteint);
	return(nFlotAtteint);
}//nFlotMaxCalculer

void FlotOptimiser(graf *pgG,int nSommetInitial,int sSource,int sTrappe,int bAfficher){
	// 
	long zCoutTotal;
	int nArc,bEcourter,nEcourte,zCoutMinimal,nFlot,nFlotAtteint,bTrappeAtteinte;
	int nFlotRequis=1,nPoleEnTout;
	int bCalculer,aK,sX;
	//int T[1+14]={-1,13,11,15,3,23,8,10,7,2,19,21,1,9,5};
	Appel0("FlotOptimiser");
		Assert4("FlotOptimiser1",bFlotAmorceR,nSommetInitial>0,pgG->nArcEnTout>0,nFlotRequis>=0);
		Assert3("FlotOptimiser2",bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe),sSource!=sTrappe);
		bCalculer=(nFlotRequis>0);//algo de Busacker p227
//t("0");
		//GrapheVoir0(pgG,"FlotOptimiser",grCout);
//t("1");
		nPoleEnTout=2*nSommetInitial;
//t("2");
		//désactiver les arcs médians,activer les autres arcs
			VecteurValuer(pgG->nCapaMax,1,pgG->nArcEnTout,1);
			for (nFlot=0;nFlot<nSommetInitial*nSommetInitial;nFlot++)
				FlotCoupeR(pgG,nFlot,nSommetInitial);
		//GrapheVoir0(pgG,"PREFLOT établi",grCapaMax+grCout+grPhi);
		//GrapheVoir0(pgG,"PREFLOT établi",grCapaMax);
			for (nArc=0,sX=pgG->nSommetEnTout;sX>=1;sX--)
				for (aK=pgG->aHed[sX+1]-1;aK>=pgG->aHed[sX];aK--){
					//te("aK",aK);
					if (pgG->nCapaMax[aK]==0){
						nArc++;
						//tee("sX,pgG->sSuk[aK]",sX,pgG->sSuk[aK]);
						GrapheDesarquer(pgG,sX,pgG->sSuk[aK]);
					}
				}
			te("nArc en trop",nArc);
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				Assert1("FlotOptimiser77",pgG->nCapaMax[aK]>0);
//t("3");
//t("4");
		//placer le préflot
			VecteurRazer(pgG->nPhi,1,pgG->nArcEnTout);//valeur du flot qui passera ds l'arc aK
			for (nFlot=0;nFlot<nSommetInitial*nSommetInitial;nFlot++)
				FlotAjouteR(pgG,nFlot,nSommetInitial);
		//attribuer un coût significatif au premier arc,ie celui issu de sSource
			//tee("sSource,nPoleEnTout+1",sSource,nPoleEnTout+1);
			aK=nGrapheArc(pgG,sSource+4,sSource);
			teee("sSource+4,sSource,aK",sSource+4,sSource,aK);
			//pgG->nCout[aK]=-kE3;

			aK=nGrapheArc(pgG,10,31); pgG->nCout[aK]=kE3;
			aK=nGrapheArc(pgG,10,37); pgG->nCapaMax[aK]=0;
			aK=nGrapheArc(pgG,10,12); pgG->nCapaMax[aK]=0;

		GrapheInverser(pgG);
		GrapheVoir0(pgG,"PREFLOT établi",grCout+grPhi);
		if (1){
			nFlotAtteint=zCoutTotal=0;
			bEcourter=0;
			nEcourte=(bEcourter)? nFlotRequis: 0;//si bEcourter, seules les extrémités utiles des chemins seront affichées.
			if (1)
				//GrapheVoir0(pgG,"Graphe de flot",grCapaMin+grCapaMax+grPhi+grCout);
				sSource=10;
				tee("sSource,sTrappe",sSource,sTrappe);
				zCoutMinimal=zCheminDeCoutMinimalCalculeR(sSource,sTrappe,pgG,!k1CoutMoyeN);//O(SA)
				te("zCoutMinimal",zCoutMinimal);
				bTrappeAtteinte=pgG->sPer[sTrappe]!=0;
				tb("bTrappeAtteinte",bTrappeAtteinte);
				if (bTrappeAtteinte) {
					if (1 && bAfficher)
						CheminBrutAfficheR(*pgG,sSource,sTrappe,1,nEcourte);
					if (1 && bAfficher)
						CheminConcisAfficheR(*pgG,sSource,sTrappe,1,nSommetInitial);
					pgG->nAugVal[sTrappe]=iMin(pgG->nAugVal[sTrappe],nFlotRequis-nFlotAtteint);
					FlotAugmenteR(pgG,sSource,sTrappe);//actualise exclusivt nPhi[] algébriqt sur le chemin sSource sTrappe
					nFlotAtteint+=pgG->nAugVal[sTrappe];
				te("                  Flot cumulé obtenu",nFlotAtteint);
					zCoutTotal+=pgG->nAugVal[sTrappe]*zCoutMinimal;
				};
			if (0 && bAfficher)
				FlotAfficherParChemiN(pgG,sSource,sTrappe,nEcourte,"Flot optimal final décomposé chemin par chemin");
			te("zCoutTotal",zCoutTotal);
		}
	Appel1("FlotOptimiser");
}//FlotOptimiser

void FlotPondereR(graf *pgG,int sSource,int sDestination,int nCapaMax,int nCout,int nPrix){
	FlotCapaciter(pgG,sSource,sDestination,nCapaMax);
	FlotCapaciter(pgG,sDestination,sSource,nCapaMax);
	FlotCouter1(pgG,sSource,sDestination,nCout);
	FlotCouter1(pgG,sDestination,sSource,nCout);
	FlotCouter2(pgG,sSource,sDestination,nPrix);
	FlotCouter2(pgG,sDestination,sSource,nPrix);
}//FlotPondereR

void FlotTESTER(int iTest){
	graf *pgG;
	int nSommet=0;
	int sSource=1;//d
	int sTrappe=8;//d
	const long kzFlotRequis=2;
	iTest=0;
	Appel0(sC2("FlotTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
		case 0:	 nSommet=4;sSource=1;sTrappe=nSommet;break;
		case 1:	 nSommet=8;break;
		case 2:	 nSommet=9;break;
		case 3:	 nSommet=5;sSource=3;sTrappe=1;break;
		case 4:	 nSommet=6;sSource=5;sTrappe=6;break;
		default: FlotTesteR2(iTest);break;
		}
		if (nSommet!=0){
			GrapheCreer( nSommet,&pgG );
				//GrapheSymetriser(pgG);
		        //GrapheArquer(pgG, 1, 5);
				GraphePonderer3(pgG,1,1,1);
				if (iTest==0){
					GrapheDesarquer(pgG,3,1);GrapheDesarquer(pgG,3,2);
					GrapheArquer(pgG,2,3);
					GraphePonderer3(pgG,2,4,5);//capamin,capamax,cout
					GraphePonderer5(pgG,2,4,1,3,1);
					GraphePonderer5(pgG,1,3,1,2,1);
					GraphePonderer5(pgG,2,3,0,4,1);
					GraphePonderer5(pgG,3,4,1,4,1);
				}
				GrapheVoir4(pgG,sC5("Réseau de transport étudié: source ",sEnt(sSource),", trappe ",sEnt(sTrappe),", et graphe défini ci-dessous"));
				if (iTest==3)
					pgG->nCout[4]=20;
				if (iTest==4){
					FlotCouter1(pgG,5,2,52);FlotCouter1(pgG,5,3,53);FlotCouter1(pgG,5,4,54);FlotCouter1(pgG,5,6,55);FlotCouter1(pgG,5,1,10);}
				if(0)
					bBof=nFlotMaxCalculer(pgG,sSource,sTrappe,kzFlotRequis,k1Afficher);
				else bBof=bFlotCompatible(pgG,sSource,sTrappe,k1Afficher);
					//FlotAfficher(pgG,0,"flot résultant")
					;
			GrapheCreer( 0,&pgG );
		}
	Appel1(sC2("FlotTESTER,test n°",sEnt(iTest)));
}//FlotTESTER

void FlotTesteR2(int nTest){
	#define kuArcEnTout1 14
	#define kuArcEnTout3 18
	#define kzFlotRequis1 1
	#define kzFlotRequis2 1
	#define kuChemin1Lg 6
	#define kuChemin2Lg 6
	#define kuCoutProhibitif 9999
	int nArc10[1+kuArcEnTout1]={-1,1,1, 2, 3,3,3, 4,4, 5, 6,6, 7, 8, 9};//NB sommet origine de l'arc
	int nArc11[1+kuArcEnTout1]={-1,2,3, 4, 4,5,6, 6,9, 7, 8,9, 9,10,10};//NB sommet destination de l'arc
	int nArc30[1+kuArcEnTout3]={-1,1,1,1, 2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6};//NB sommet origine de l'arc
	int nArc31[1+kuArcEnTout3]={-1,4,5,6, 4,5,6, 4,5,6, 7,8,9, 7,8,9, 7,8,9};//NB sommet destination de l'arc
	int sChemin1[1+kuChemin1Lg]={-1,1,3,5,7,9,10};
	int sChemin2[1+kuChemin2Lg]={-1,1,2,4,6,8,10};
	int bEulerien;
	graf *pgG;
	int uS;
	int sSource1=1;
	int sSource2=1;
	int sTrappe1=1;
	int sTrappe2=1;
	switch (nTest) {
	case 11://1 nid d'abeille et demi, 2 sources identiques, 2 trappes identiques
			GrapheCreer2(&pgG,10,kuArcEnTout1,&nArc10[0],&nArc11[0]);
			GraphePonderer3(pgG,1,1,1);
			GrapheVoir(pgG,sC2b("GrapheSymetriser AVANT:",sPluriel(pgG->nArcEnTout,"arc")));
			GrapheSymetriser(pgG);
			GrapheVoir(pgG,sC2b("GrapheSymetriser APRES:",sPluriel(pgG->nArcEnTout,"arc")));
			FlotCapaciter(pgG,0,0,1);
			FlotCouter1(pgG,0,0,2);//couts pr x1
			FlotCouter2(pgG,0,0,1);//prix pr x2
			//le coût du chemin sChemin1 est trop élevé pour le flot 1 représenté par la variable x1
				for (uS=1; uS<kuChemin1Lg; uS++)
					FlotCouter1(pgG,sChemin1[uS],sChemin1[uS+1],50);
			//le coût du chemin sChemin2 est trop élevé pour le flot 2 représenté par la variable x2
				for (uS=1; uS<kuChemin2Lg; uS++)
					FlotCouter2(pgG,sChemin2[uS],sChemin2[uS+1],50);
			//dissuader les flots de passer par les aretes ci-dessous qui n'ont été ajoutées que pr rendre le graphe eulérien 
				FlotCouter1(pgG,3,6,kuCoutProhibitif);
				FlotCouter2(pgG,3,6,kuCoutProhibitif);
				FlotCouter1(pgG,4,9,kuCoutProhibitif);
				FlotCouter2(pgG,4,9,kuCoutProhibitif);
			sSource1=1;
			sTrappe1=10;
			break;
	case 12://graphe étagé, 2 sources identiques, 2 trappes identiques
			GrapheCreer2(&pgG,3*3,kuArcEnTout3,&nArc30[0],&nArc31[0]);
			GrapheBipartitionne(pgG);
			GraphePolariser(pgG,&sSource1,&sTrappe1);
			break;
	default:assert(1<0);
			break;
	}
	Assert3("Flot2TesteR",bGrapheSimple(pgG),bGrapheSommet(pgG,sSource1),bGrapheSommet(pgG,sTrappe1));
	sSource2=sSource1;
	sTrappe2=sTrappe1;
	GrapheInverser(pgG);
	//GrapheVoir(pgG,"Graphe dédoublé");
	bEulerien=bGrapheEulerien(pgG,sSource1,sTrappe1);
	ttt("Le graphe final",sEst(bEulerien),"eulérien.");
//bEulerien=kF;
	if (bEulerien){
		//GrapheVoir3(pgG,"Flot2TesteR");
		//FlotMatriceR(pgG);
		//SystemeAfficheR(pgG,sSource1,sTrappe1,'u');
		//SystemeAfficheR(pgG,sSource2,sTrappe2,'v');
		bFlotCalculeR2(pgG,sSource1,sTrappe1,kzFlotRequis1,sSource2,sTrappe2,kzFlotRequis2);
	}
	GrapheCreer(0,&pgG);
}//Flot2TesteR

void FluxAjouteR(graf *pgG,int sOrigine,int sDestination){
	int aK=nGrapheArc(pgG,sOrigine,sDestination);
	Assert1("FluxAjouteR",bCroit(1,aK,pgG->nArcEnTout) );
	pgG->nPhi[aK]=1;
}//FluxAjouteR

int bFluxSuivanT(graf *pgG,int sSource,int *psDestination,long *pzCoutTotal){
	//rend,s'il existe, le sommet destination qui transmet le flux élémentaire depuis sSource;vrai ssi il existe un tel flux
	const int kbVerifier=kV;
	int nFlot0,nFlot1;
	int aK,aKbis,aKter,sX,sY;
	int bSuivant=kF;
	for (aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++){
		nFlot0=pgG->nPhi[aK];
		sY=pgG->sSuk[aK];
		aKbis=aTablE[sY][sSource];//arc symétrique et non pas arc inverse
		nFlot1=pgG->nPhi[aKbis];
		if (kbVerifier){//O(A)
			GrapheDelimiter(pgG,aK,&sX,&sY);
			aKter=nGrapheArc(pgG,sY,sX);
			Assert2("bFluxSuivanT1",sSource==sX,aKbis==aKter);
		}
		//teee("aK,aL,pgG->aArcTo[aK]",aK,aL,pgG->aArcTo[aK]);
		if ( nFlot0>0 && nFlot1==0){
			//assert(nFlot==1);
			*pzCoutTotal+=pgG->nCout[aK];
			*psDestination=pgG->sSuk[aK];
			bSuivant=kV;
		}
	}
	return(bSuivant);
}//bFluxSuivanT

void SystemeAfficheR(graf *pgG,int sSource,int sTrappe,char cVariable){
	//affiche le système d'équations du flot dans pgG de demande (sSource1,sTrappe1) si flot simple,et cplétée par (sSource2,sTrappe2) si biflot
	int uC;
	int aK;
	int aL;
	int tArc[1+pgG->nArcEnTout];
	int sX;
	Assert2("SystemeAfficheR1",bFlotAmorceR,pgG!=0);
	assert(bGrapheSimple(pgG));
	GrapheInverser(pgG);//mm si déjà fait
	Assert2("SystemeAfficheR3",bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe));
	printf("Système d'équations associé au flot de demande %s",sCouple(sSource,sTrappe));
	printf(",équations sommets 1 à %d:\n",pgG->nSommetEnTout);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			//arcs entrants et sortants:>0 si sortants,<0 si sortants, et nuls si non incidents à sX
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					tArc[aK]=0;
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					tArc[aK]=+1;
				for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++){
					aK=pgG->aInv[aL];
					tArc[aK]=-1;//NB vu bGrapheSimple,un arc est soit entrant soit sortant,dc tArc[aK]=-1 n'écrasera pas un tArc[aK]=-+1
				}
			//terme droit
				tArc[0]=bVrai(sX==sSource) - bVrai(sX==sTrappe);
			//afficher la ligne courante dédiée à sX
				printf("%3d ",sX);
				for (uC=1;uC<=pgG->nArcEnTout;uC++)
					if (tArc[uC]!=0)
						printf("%s%c%d",sSigne(tArc[uC]),cVariable,uC);
					else printf("   %s",sChoix0(uC>9," "));
				printf(" = %2d",tArc[0]);//terme droit
				printf("\n");
		}
}//SystemeAfficheR
