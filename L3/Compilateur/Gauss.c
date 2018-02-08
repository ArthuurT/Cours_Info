#include "Outil.h"

#define knLigneLiM 128
	typedef struct{int e11;int e12;int e21;int e22;}rect;
	typedef struct{
		int nColonne;
		int nLigne;
		rect Mat[knLigneLiM][knLigneLiM];//pas knColonneMaX,dédié nDuoCompteR()
	}rMatricE;

int bGaussAmorceR;
void GaussVoiR(char *sMessage,rMatricE *prmT);
void RectFoisseR(rect rB,int iFois,rect *prProduit2);
void RectMultiplieR(rect rB,rect rFois,rect *prProduit2);
int bRectNuL(rect rIndex);
void RectSommeR(rect rA,rect rB,rect *prSomme);

void GaussAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bGaussAmorceR=kV;
}//GaussAMORCER

void GaussTESTER(int iTest){
	//teste le présent module
	Appel0(sC2("GaussTESTER,test n°",sEnt(iTest)));
		Assert1("GaussTESTER",bGaussAmorceR);
		switch (iTest) {
			case  1:	break;
			default:break;
		}
	Appel1(sC2("GaussTESTER,test n°",sEnt(iTest)));
}//GaussTESTER

int bGaussTrianguleR(rMatricE *prmT,int *pnEtape){
	//rend vrai ssi le déterminant de la matrice ppmT est non nul;calcul exact sur les entiers par élimination gaussienne
	int uL,uC,uD,bDerouter,uP,nPivot,nEtape,bTrianguler,nPermutation;
	rect rIndex,rValeur,rPivot,rProduit1,rProduit2,rProduit3,rB,rC,rFois,rSomme;
	nEtape=0;//indicateur de la complexité algorithmique de la présente routine
	GaussVoiR("prmT original",prmT);
	//transformer ppmT en matrice triangulaire supérieure d'entiers;uD progresse sur la diagonale ppmT[i][i] de la matrice
		for (bDerouter=kF,nPivot=0,nPermutation=0,uD=1;uD<=prmT->nLigne && nPivot>=uD-1;uD++){
			GaussVoiR("ppmT courant",prmT);
			//nPivot:=rg du 1er terme non nul sur la ligne courante
				for (nPivot=0,uP=1;uP<=prmT->nColonne;nEtape++,uP++){
					rIndex=prmT->Mat[uD][uP];
					if (nPivot==0 && !bRectNuL(rIndex))
						nPivot=uP;
				}
			tee("uD,nPivot",uD,nPivot);
			bDerouter=(nPivot==0) && uD<prmT->nLigne; 
			if (nPivot>=uD){
				if (uD!=nPivot){//échanger les colonnes nPivot et uD
					for (nPermutation++,uL=1;uL<=prmT->nLigne;nEtape++,uL++){
						rValeur=prmT->Mat[uL][nPivot];
						prmT->Mat[uL][nPivot]=prmT->Mat[uL][uD];
						prmT->Mat[uL][uD]=rValeur;
					}
					GaussVoiR("ppmT recolonné",prmT);
				}
				rPivot=prmT->Mat[uD][uD];
				Assert1("bMatriceTrianguleR1",!bRectNuL(rPivot));
				//tee("uD,ivPivot",uD,ivPivot);
				//multiplier la ligne du pivot et celles dessous afin que les éléments sur la colonne du pivot soient égaux (leur ppcm suffit)
					//introduire des 0 en colonne uD en soustrayant la ligne du pivot de la ligne courante
						rPivot=prmT->Mat[uD][uD];//a
						for (uL=uD+1;uL<=prmT->nLigne;uL++){
							rFois=prmT->Mat[uL][uD];//d
							for (uC=uD;uC<=prmT->nColonne;uC++){//ajouter ac-bd
								rB=prmT->Mat[uD][uC];//b
								rC=prmT->Mat[uL][uC];//c
								//PolynomeVoiR("ivPivot",ivPivot,ppmT);
								//PolynomeVoiR("ivC",ivC,ppmT);
								RectMultiplieR(rPivot,rC,&rProduit1);//ac
								//PolynomeVoiR("ivProduit1",ivProduit1,ppmT);
								//PolynomeVoiR("ivB",ivB,ppmT);
								//PolynomeVoiR("ivFois",ivFois,ppmT);
								RectMultiplieR(rB,rFois,&rProduit2);//bd
								//PolynomeVoiR("ivProduit2",ivProduit2,ppmT);
								RectFoisseR(rProduit2,-1,&rProduit3);//-bd
								//PolynomeVoiR("ivProduit3",ivProduit3,ppmT);
								rSomme=prmT->Mat[uL][uC];
								RectSommeR(rProduit1,rProduit3,&rSomme);//ac-bd
								//PolynomeVoiR("ivSomme",ivSomme,ppmT);
								//nEtape+=prmT->nTerme*prmT->nTerme;//coût quadratique de PolynomeMultiplieR (on sait descendre à NlogN)
							}
						}
						//MatriceVoyR("ppmT pivoté",prmT);
				GaussVoiR(sC4b("ppmT après pivotage ligne",sEnt(uD),"colonne",sEnt(uD)),prmT);
			}else printf("Un pivot nul a été rencontré ligne %d colonne %d.\n",uD,uD);
		}
	//bTrianguler=déterminant non nul,ie aucun élément de la diagonale principale n'est le polynome nul
		for (bTrianguler=kV,uD=1;uD<=prmT->nLigne;uD++)
			bTrianguler=bTrianguler && !bRectNuL(prmT->Mat[uD][uD]);
	GaussVoiR(sC2b("ppmT triangulé",sChoix0(!bTrianguler && bDerouter,"(déroutement dû au pivot nul)")),prmT);
	*pnEtape=nEtape;
	//te("bTrianguler APRES",bTrianguler);
	return(bTrianguler);
}//bGaussTrianguleR

void GaussVoiR(char *sMessage,rMatricE *prmT){
	Assert1("GaussVoiR",bGaussAmorceR);
	//printf("%s: %s.\n",sQuoi,sFormE(fGauss));
}//GaussVoiR
	
void RectFoisseR(rect rB,int iFois,rect *prProduit2){
}//RectFoisseR

void RectMultiplieR(rect rB,rect rFois,rect *prProduit2){
}//RectMultiplieR

int bRectNuL(rect rIndex){
	int bNul;
	bNul=(rIndex.e11==0) && (rIndex.e12==0) && (rIndex.e21==0) && (rIndex.e22==0);
	return(bNul);
}//bRectNuL

void RectSommeR(rect rA,rect rB,rect *prSomme){
}//RectSommeR

