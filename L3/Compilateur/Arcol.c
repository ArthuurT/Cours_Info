//Arcol=Graphe à arcs colorés
#include "Outil.h"
#include "Arcol.h"
#include "Graphe.h"
int bArcolAmorceR;//ie le module a effectivement été amorcé
int nArcolVoiR;


#define kuCoulMax 10
int nCoul[1+kuCoulMax];

void ArcolExpliciter(graf *pgArcol);

void ArcolAMORCER(){
	//amorce le présent module une fois pour toutes
	bArcolAmorceR=kV;
}//ArcolAMORCER

int nGadgetAttachE(graf *pgArcol,int sX,int sY){
	//rend l'attache (index relatif) de sY dans le gadget sX
	int uCoul,aK,nAttache,sZ,nYcouleur;
	VecteurRazer(nCoul,1,kuCoulMax);
	for (nYcouleur=0,aK=pgArcol->aHed[sX];aK<pgArcol->aHed[sX+1];aK++){
		Assert1("nGadgetAttachE1",bCroit(1,pgArcol->coulh[aK],kuCoulMax));
		nCoul[pgArcol->coulh[aK]]=1;
		sZ=pgArcol->sSuk[aK];
		if (sY==sZ)
			nYcouleur=pgArcol->coulh[aK];
	}
	Assert1("nGadgetAttachE2",nYcouleur>0);
	//VecteurVoir("nCoul",nCoul,1,kuCoulMax);
	for (nAttache=0,uCoul=1;uCoul<=kuCoulMax && uCoul<=nYcouleur;uCoul++)
		nAttache+=(nCoul[uCoul]>0);
	Assert1("nGadgetAttachE8",nAttache>0);
	//d3(sX,sY,nAttache);
	return(nAttache);
}//nGadgetAttachE

void GadgetGenereR(int uGadget,int bObligatoire,int nCumulParGadget[],graf *pgGadget){
	//génère les arcs du gadget courant de rg1 uGadget
	int sA=1,sB=2,sX,sY;
	int uCouleurEnTout=nCumulParGadget[uGadget]-nCumulParGadget[uGadget-1]-4;
	d(uCouleurEnTout);
	Assert1("GadgetGenereR",uCouleurEnTout);
	//générer le sélecteur: relier sA et sB aux uCouleurEnTout sommets du front.
		for (sX=sA;sX<=sB;sX++)
			for (sY=sB+1;sY<=sB+uCouleurEnTout;sY++)
				GrapheArquer(pgGadget,nCumulParGadget[uGadget-1]+sX,nCumulParGadget[uGadget-1]+sY);
	if (!bObligatoire)//fermer le fond
		GrapheArquer(pgGadget,nCumulParGadget[uGadget-1]+sA,nCumulParGadget[uGadget-1]+sB);
	//prolonger le sélecteur
		for (sY=sB+1;sY<=sB+uCouleurEnTout;sY++)
			GrapheArquer(pgGadget,nCumulParGadget[uGadget-1]+sY,nCumulParGadget[uGadget-1]+sY+uCouleurEnTout);
}//GadgetGenereR

void ArcolExpliciter(graf *pgArcol){
	//convertit le graphe coloré pgArcol en graphe décoloré pgExplicite;un sommet est obligatoire ssi pgArcol->aHed[sX]>0
	int aK,sX,sY,sXprim,sYprim,nCouleur,nSommet;
	int nCumulParGadget[1+pgArcol->nSommetEnTout];
	int bObligatoire[1+pgArcol->nSommetEnTout];
	graf *pgExplicite;
	for (sX=1;sX<=pgArcol->nSommetEnTout;sX++)
		bObligatoire[sX]=pgArcol->aHed[sX]>0;
	for (sX=1;sX<=pgArcol->nSommetEnTout;sX++)
		pgArcol->aHed[sX]=nAbs(pgArcol->aHed[sX]);//AVANT li+1
	Assert2("ArcolExpliciter",bArcolAmorceR,bGrapheSimple(pgArcol));//à étendre aux multigraphes 
	GrapheSymetriser(pgArcol);
	//nSommet:=nbre total de sommets du futur graphe pgExplicite
		for (nCumulParGadget[0]=0,sX=1;sX<=pgArcol->nSommetEnTout;sX++){
			//nCouleur:=nbre total de couleurs autour du sommet sX
				for (nCouleur=0,aK=pgArcol->aHed[sX];aK<pgArcol->aHed[sX+1];aK++){
					sY=pgArcol->sSuk[aK];
					Assert1("ArcolExpliciter",bCroit(1,pgArcol->coulh[aK],kuCoulMax));
					nCouleur=iSup(nCouleur,nGadgetAttachE(pgArcol,sX,sY));
				}
				Assert1("ArcolExpliciter45",nCouleur>0);
			nCumulParGadget[sX]=nCumulParGadget[sX-1]+4+nCouleur;
		}
		VecteurVoir("nCumulParGadget",nCumulParGadget,0,pgArcol->nSommetEnTout);
		nSommet=nCumulParGadget[pgArcol->nSommetEnTout];
		d(nSommet);
	GrapheCreer(-nSommet,&pgExplicite);
		//GrapheVoir(pgExplicite,"ArcolExpliciter AVANT");
		//générer les arcs internes des gadgets
			for (sX=1;sX<=pgArcol->nSommetEnTout;sX++)
				GadgetGenereR(sX,bObligatoire[sX],nCumulParGadget,pgExplicite);
		//connecter les gadgets entre eux
			for (sX=1;sX<=pgArcol->nSommetEnTout;sX++)
				for (aK=pgArcol->aHed[sX];aK<pgArcol->aHed[sX+1];aK++){
					sY=pgArcol->sSuk[aK];
					if (sX<sY){
						sXprim=nCumulParGadget[sX]-nGadgetAttachE(pgArcol,sX,sY)+1;//d(nGadgetAttachE(pgArcol,sX,sY));
						sYprim=nCumulParGadget[sY]-nGadgetAttachE(pgArcol,sY,sX)+1;//d(nGadgetAttachE(pgArcol,sY,sX));
						d4(sX,sY,sXprim,sYprim);
						GrapheArquer(pgExplicite,sXprim,sYprim);
					}
				}
		//recopier ds pgExplicite la couleur et la pondération des arcs de pgArcol qui relient les gadgets
			GraphePonderer0(pgExplicite,0);//car GrapheArquer a laissé des pondérations résiduelles
			for (sX=1;sX<=pgArcol->nSommetEnTout;sX++)
				for (aK=pgArcol->aHed[sX];aK<pgArcol->aHed[sX+1];aK++){
					sY=pgArcol->sSuk[aK];
					if (sX<sY){
						sXprim=nCumulParGadget[sX]-nGadgetAttachE(pgArcol,sX,sY)+1;//d(nGadgetAttachE(pgArcol,sX,sY));
						sYprim=nCumulParGadget[sY]-nGadgetAttachE(pgArcol,sY,sX)+1;//d(nGadgetAttachE(pgArcol,sY,sX));
						GrapheColorer(pgExplicite,sXprim,sYprim,pgArcol->coulh[aK]);
						GraphePonderer(pgExplicite,sXprim,sYprim,pgArcol->nCout[aK]);
					}
				}
	GrapheVoir0(pgExplicite,"ArcolExpliciter APRES",grCout+grCouleur);
}//ArcolExpliciter

void ArcolTESTER(int iTest){
	//teste le présent module
	graf *pgG;
	enum grTyoe GrapheType;
	enum grCoull CouleurType;
	Assert1("ArcolTESTER",bArcolAmorceR);
	Appel0(sC2("ArcolTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case 1:GrapheCreer1(&pgG,grK3,k1Creer);
				GrapheColorer(pgG,1,2,coBleu);GraphePonderer(pgG,1,2,12);
				GrapheColorer(pgG,2,3,coRouge);GraphePonderer(pgG,2,3,23);
				GrapheColorer(pgG,1,3,coVert);GraphePonderer(pgG,1,3,13);
				GrapheVoir0(pgG,"pgG",grCouleur+grCout);
				pgG->aHed[2]= - pgG->aHed[2];
				ArcolExpliciter(pgG);
				break;
			default:
				Assert1("ArcolTESTER",0);
				break;
		}
	Appel1(sC2("ArcolTESTER,test n°",sEnt(iTest)));
}//ArcolTESTER	

void ArcolVoir(char *sQuoi){//O(S)
	Assert2("ArcolVoir",bArcolAmorceR,sQuoi!=0);
	//Appel0("ArcolVoir");
	nArcolVoiR++;
	printf("Arcol n°%d %s:\n",nArcolVoiR,sQuoi);
	//Appel1("ArcolVoir");
}//ArcolVoir

