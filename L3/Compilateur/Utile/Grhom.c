#include "Outil.h"
#include "Deque.h"
#include "Grhom.h"
#include "Grammaire.h"
//Grhom=GRammaire HOMogène. Scrute une grammaire homogène puis génère son code équivalent en langage C, ou teste ladite grammaire sur-le-champ.
//une grammaire est homogène ssi elle a les caractéristiques suivantes:
//  1° c'est une grammaire algébrique (il existe donc une règle qui a S pour membre gauche) dont les règles sont séparées par le symbole ";".
//  2° les non terminaux sont des majuscules dans [A..Z], et les terminaux des minuscules dans [a..z].
//  3° le symbole entre le membre gauche et le membre droit de chaque règle est le digramme insécable "->".
//	4° elle ne renferme que des règles homogènes, ie ne contenant que des opérateurs ".", ou que des opérateurs "+", en plus des règles terminales.
//	5° les opérandes entre les opérateurs "." ou "+" sont des majuscules.
//	6° les membres gauche et droit d'une règle terminale représentent le même symbole à la casse près.
//	7° les règles A->a et B->b sont présentes.
//	8° la récursivité à gauche est absente ——qu'elle soit directe ou indirecte (indirecte: dans "P->Q.R;Q->S+P", P appelle P).
//  9° dans une règle OU, eg T->P+Q, aucun mot engendré par P n'est un facteur gauche strict d'un mot engendré par Q (considérer alors "T->Q+P").
// NB: Pour obtenir aisément une grammaire homogène, donc sans mot vide, remplacer les expressions (E)* par (1+(E+)) et développer.
#define kuCaractereMaX kE2
#define k1FichieR kV
#define k1HomogenE kV
#define kuLettreMaX 26
#define kuRegleMaX kuLettreMaX
#define kuTermeMaX kE1
#define kuTypE (kuTermeMaX+1)
#define kuSymbolE (kuTermeMaX+2) //non terminal de la règle courante
FILE *fGramR;//nom du fichier (suffixe .c vital) destiné à recevoir le code généré qui explicite la grammaire homogène.
char *skFICHIER="Grammaire.c";//reçoit le code C qui explicite la grammaire homogène compilée par bGrhomCompiler() 
int bGrhomAmorceR;
int bGrhomCompileR;
enum eRegleTypE {rtAlphA,rtTerminalE,rtET,rtOU,rtOmegA};
const char kcSeparateuR=';';
int nPilE[1+kuRegleMaX][1+kuTermeMaX+2];//chaque ligne décrit une règle de la grammaire homogène. Les lignes occupées sont empilées donc consécutives. 
int nTablE[1+kuLettreMaX][1+kuTermeMaX+2];//comme nPilE,mais la ligne dédiée à un non terminal est son rang dans l'alphabet: B est ligne 2, S en 19.

void EcrirE(char *szQuoi);
void EcrirE0(int bFichier,char *szQuoi);
void EcrirE1(int bFichier,char *szQuoi);
void EcrirE3(char *sA,char *sB,char *sC);
void EcrirE7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
void EnteteGenereR(char * sGrAlgebrique,char *sGrHomogene,int nRegleRang[],int nRegleEnTout[2],char *sFichierCible);
int bFlechE(char *sGrhom,int nDebutExclu);
void GrhomAfficheR(int bFichier,char *sGrAlgebrique,char *sGrHomogene,int nRegleEnTout[2]);
int bGrhomDecideR(int uRegle,char sMot[],int iDebut,int *piFin,int bVoir,int *pnAppelEnTout);
void GrhomExpliciteR(char *sGrAlgebrique,char *sGrohm,int nRegleEnTout[2],char *szFichierCible);
int bGrhomHomogenE(char *sGrohm,int nSeparateur[]);
int bGrhomPlausiblE(char *sGrohm,int nRegleEnTout);
void GrhomTabuleR(char *sGrohm,int nRegleEnTout,int bVoir);
int bRecursivitehGauchE(int uRegle);
void RecursivitehGaucheVoiR(char *sMessage,int uDito);
int bRegleDenonceR(int nRegle,char *sGrhom,int nDebut,int nFin);
int bRegleET(int nRegle,char *sGrhom,int nDebut,int nFin);
void RegleEtGenereR(int nRegle);
int bRegleOU(int nRegle,char *sGrhom,int nDebut,int nFin);
void RegleOuGenereR(int nRegle);
int bRegleTerminalE(int nRegle,char *sGrhom,int nDebut,int nFin,int *pbA,int *pbB);
void RegleTerminaleGenereR(int nRegle);
void TexteCompacteR(char *sNonCompact,char sCompact[1+kuCaractereMaX]);

void EcrirE(char *szQuoi){
	//printf("%s",szQuoi);
	fprintf(fGramR,"%s",szQuoi);
}//EcrirE

void EcrirE0(int bFichier,char *szQuoi){
	//comme EcrirE1,mais avec un blanc final en moins
	if (bFichier)
		fprintf(fGramR,"%s",szQuoi);
	else printf("%s",szQuoi);
}//EcrirE0

void EcrirE1(int bFichier,char *szQuoi){
	//comme EcrirE0,mais avec un blanc final en plus
	if (bFichier)
		fprintf(fGramR,"%s ",szQuoi);
	else printf("%s ",szQuoi);
}//EcrirE1

void EcrirE3(char *sA,char *sB,char *sC){
	EcrirE(sC3(sA,sB,sC));
}//EcrirE3

void EcrirE7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	EcrirE(sC7(sA,sB,sC,sD,sE,sF,sG));
}//EcrirE7

void EnteteGenereR(char * sGrAlgebrique,char *sGrHomogene,int nRegleRang[],int nRegleEnTout[],char *sFichierCible){
	//génère includes,variables de module,protos des règles (ds l'ordre nRegleRang[]),leur code et celui de sFichierCibleAMORCER,INITIALISER,TESTER.
	int uR;
	int mPoint=mChainePos('.',sFichierCible);
	int nFichierLg=strlen(sFichierCible);
	char *sRacine=malloc(1+nFichierLg);
		strcpy(sRacine,sFichierCible);
		Assert3("EnteteGenereR",mPoint>0,sFichierCible[mPoint+1]=='c',mPoint+2==nFichierLg);
		sRacine[mPoint]='\0';
		//générer les includes
			EcrirE("#include \"Outil.h\"\n");
			EcrirE3("#include \"",sRacine,".h\"\n");
		//générer les variables de module
			EcrirE("char *sMOT;\n");
			EcrirE3("int b",sRacine,"AmorceR=kF;\n");
		//générer en commentaire les règles des deux grammaires
			GrhomAfficheR(k1FichieR,sGrAlgebrique,sGrHomogene,nRegleEnTout);
		//générer tous les prototypes associés aux règles ——à 1 règle T on associe bijectivement 1 routine bT().
			for (uR=1;uR<=nRegleEnTout[1];uR++)
				EcrirE(sC3("int b",sC(nPilE[nRegleRang[uR]][kuSymbolE]),"(int iDebut,int *piFin);\n"));
			EcrirE("\n");
		//générer le code de la routine sFichierCibleAMORCER.
			EcrirE3("void ",sRacine,"AMORCER(){\n");
				EcrirE3("    b",sRacine,"AmorceR=kV;\n");
			EcrirE3("}//",sRacine,"AMORCER\n\n");
		//générer le code de la routine sFichierCibleINITIALISER.
			EcrirE3("void ",sRacine,"INITIALISER(){\n");
				EcrirE7("    Assert1(\"",sRacine,"INITIALISER\",b",sRacine,"AmorceR);","","\n");
			EcrirE3("}//",sRacine,"INITIALISER\n\n");
		//générer le code de la routine sFichierCibleTESTER qui appelle bS() et dit si sMOT est engendré par la grammaire.
			EcrirE3("void ",sRacine,"TESTER(int iTest){\n");
				EcrirE("    int bEngendre,iFin,bSucces;\n");
				EcrirE7("    Assert1(\"",sRacine,"TESTER0\",b",sRacine,"AmorceR);","","\n");
				EcrirE("    //sMOT:=mot à tester selon iTest\n");
				EcrirE("        switch(iTest){\n");
				EcrirE("            case 1: sMOT=\"aab\";break;\n");
				EcrirE("            case 2: sMOT=\"aaba\";break;\n");
				EcrirE3("            default:Assert1(\"",sRacine,"TESTER1\",0);break;\n");
				EcrirE("        }\n");
				EcrirE("    bSucces=bS(0,&iFin);\n");
				EcrirE("    bEngendre=bSucces && nChaineLg(sMOT)==iFin;\n");
				EcrirE("    printf(\"%s: %s %s engendré par la grammaire décrite dans \\\"");
				EcrirE(sFichierCible);
				EcrirE("\\\".\\n\",(bEngendre)? \"SUCCES\": \"ECHEC \",sG(sMOT),sEst(bEngendre));\n");
			EcrirE3("}//",sRacine,"TESTER\n\n");
	free(sRacine);
}//EnteteGenereR

int bFlechE(char *sGrhom,int nDebutExclu){
	//NB les indexations ci-dessous sont valides vu les 3 appels: bRegleET,bRegleOU et bRegleTerminalE.
	int bFleche=(sGrhom[nDebutExclu+1]=='-') && (sGrhom[nDebutExclu+2]=='>');
	return(bFleche);
}//bFlechE

void GrammaireAfficheR(int cNiveau,int bFichier,char *sGrammaire,int nRegleEnTout){
	//selon bFichier,copie les grammaires sur le moniteur ou dans le fichier fGramR. La grammaire homogène est affichée à partir de nPilE[][].
	const int kuTab=2;
	int uC,nGrammaireLg,cPasse,bSeparateur,uRegle;
	Assert2("GrammaireAfficheR0",bGrhomAmorceR,!bFichier || bGrhomCompileR);//nPilE[][] est défini si bGrhomCompileR est vrai
	//grammaire algébrique
		EcrirE0(bFichier,sC5(sChoix(bFichier,"//",sTab(kuTab))," Grammaire ",(cNiveau==0)? "algébrique ": "homogène ",sP(sPluriel(nRegleEnTout,"règle")),":\n"));
		for (nGrammaireLg=nChaineLg(sGrammaire),cPasse=0;cPasse<=1;cPasse++){
			for (uRegle=1,bSeparateur=kV,uC=0;uC<=nGrammaireLg;uC++){
				if (cPasse==1 && bSeparateur)
					if (cNiveau==0)
						EcrirE1(bFichier,sC4(sTab(kuTab+1),sChoix0(bFichier,"//")," ",sP(sC('a'-1+uRegle))));//numérotation alphabétQ des règles
					else EcrirE1(bFichier,sC4(sTab(kuTab+1),sChoix0(bFichier,"//"),sE(1+uRegle<=10),sP(sEnt(uRegle))));//numérotO décimale
				bSeparateur=(sGrammaire[uC]==kcSeparateuR);
				if (bSeparateur)
					uRegle++;
				if (cPasse==1)
					EcrirE0(bFichier,sC((bSeparateur)?'\n': sGrammaire[uC]));
			}//for uC
			if (!bSeparateur && cPasse==1)
				EcrirE0(bFichier,"\n");
		}//for cPasse
	Assert1("GrammaireAfficheR1",uRegle==nRegleEnTout);
}//GrammaireAfficheR

void GrhomAfficheR(int bFichier,char *sGrAlgebrique,char *sGrHomogene,int nRegleEnTout[2]){
	//selon bFichier,copie les grammaires sur le moniteur ou dans le fichier fGramR. La grammaire homogène est affichée à partir de nPilE[][].
	Assert2("GrhomAfficheR1",bGrhomAmorceR,!bFichier || bGrhomCompileR);//nPilE[][] est défini si bGrhomCompileR est vrai
	//grammaire algébrique
		GrammaireAfficheR(0,bFichier,sGrAlgebrique,nRegleEnTout[0]);
	//grammaire homogène
		GrammaireAfficheR(1,bFichier,sGrHomogene,nRegleEnTout[1]);
}//GrhomAfficheR

void GrhomAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bGrhomAmorceR=kV;
}//GrhomAMORCER

void GrhomCompiler(char *sGrammaireAlgebrique,char *sGrammaireHomogene){
	int bCompiler;
	int nRegleEnTout;
	bCompiler=bGrhomCompiler(sGrammaireAlgebrique,sGrammaireHomogene,k1Afficher,skFICHIER,&nRegleEnTout);
}//GrhomCompiler

int bGrhomCompiler(char *sGrammaireAlgebrique,char *sGrammaireHomogene,int bAfficher,char *szFichierCible,int *pnRegleEnTout){
	//vrai ssi sGrammaireHomogene (règles ET,OU,Terminale entre ";",blancs facultatifs) est bien une grammaire homogène d'au plus kuRegleMaX règles.
	//Si oui,et si szFichierCible est non vide, le code en C qui explicite sGrammaireHomogene est stocké dans szFichierCible.
	//Les R règles de sGrammaireHomogene sont affichées au besoin et ce nombre R est copié dans pnRegleEnTout.
	//sGrammaireAlgebrique est la grammaire algébrique que sGrammaireHomogene rend explicite et, autant que possible, exécutable. 
	int uC;//indexe le caractère courant de la grammaire considérée
	int bCompiler;
	int nGrammaireLg;
	int cPasse;//c comme couple; 0:grammaire algébrique 1:grammaire homogène
	int bSeparateur;
	int nSeparateur[1+kuRegleMaX];//indexe chaque kcSeparateuR situé dans la grammaire considérée;un kcSeparateuR final est ajouté au besoin.
	int nRegleEnTout[2];
	char sGrAlgebrique[1+kuCaractereMaX]; 
	char sGrHomogene[1+kuCaractereMaX]; 
	Appel0("bGrhomCompiler");
		Assert3("bGrhomCompiler1",bGrhomAmorceR,nChaineLg(sGrammaireAlgebrique)<kuCaractereMaX,nChaineLg(sGrHomogene)<kuCaractereMaX);
		TexteCompacteR(sGrammaireAlgebrique,sGrAlgebrique);
		TexteCompacteR(sGrammaireHomogene,sGrHomogene);
		//nSeparateur[]:=rang0 de chaque kcSeparateuR das sGrAlgebrique ou sGrHomogene selon que cPasse=0 ou cPasse=1.
			for (cPasse=0;cPasse<=1;cPasse++){
				VecteurRazer(nSeparateur,0,kuRegleMaX);
				nGrammaireLg=nChaineLg((cPasse==0)? sGrAlgebrique: sGrHomogene);
				for (nRegleEnTout[cPasse]=0,nSeparateur[1]=-2,uC=1;uC<=nGrammaireLg;uC++){
					if (cPasse==0)
						bSeparateur=(sGrAlgebrique[uC]==kcSeparateuR);
					else bSeparateur=(sGrHomogene[uC]==kcSeparateuR);
					if (bSeparateur){
						Assert1("bGrhomCompiler2",nRegleEnTout[cPasse]<kuRegleMaX);
						nSeparateur[++nRegleEnTout[cPasse]]=uC;
					};
				}
				if (nSeparateur[nRegleEnTout[cPasse]]<nGrammaireLg){
					Assert1("bGrhomCompiler3",nRegleEnTout[cPasse]<kuRegleMaX);
					nSeparateur[++nRegleEnTout[cPasse]]=nGrammaireLg;
				}
				Assert1("bGrhomCompiler4",nRegleEnTout[cPasse]<kuRegleMaX);
				nSeparateur[nRegleEnTout[cPasse]+1]=nGrammaireLg;
				Assert1("bGrhomCompiler5",nRegleEnTout[cPasse]>=0);//nombre total de règles strictes détectées dans la grammaire considérée.
				nSeparateur[0]=nRegleEnTout[cPasse];//AVANT appel li+2
			}//for cPasse
		if (bAfficher)
			GrhomAfficheR(!k1FichieR,sGrAlgebrique,sGrHomogene,nRegleEnTout);
		bCompiler=bGrhomHomogenE(sGrHomogene,nSeparateur);//si succès, décrit aussi dans nPilE[][] la structure de la grammaire homogène
		if (bCompiler){
			GrhomTabuleR(sGrHomogene,nRegleEnTout[1],!k1Voir);//remplit la variable de module nTablE[][0] 
			DequeAllouer(kuLettreMaX);
				bCompiler=bCompiler && !bRecursivitehGauchE('S'-'@');
			DequeAllouer(0);
		}
		bGrhomCompileR=bCompiler;//AVANT GrhomAfficheR li+2;variable de module
		if ( bCompiler && nChaineLg(szFichierCible)>0 )//générer ds sFichierCible le code C qui explicite sGrHomogene
			GrhomExpliciteR(sGrAlgebrique,sGrHomogene,nRegleEnTout,szFichierCible);//qui utilise nPilE[][]
		*pnRegleEnTout=nRegleEnTout[1];//nombre total de règles strictes détectées dans sGrHomogene
	Appel1("bGrhomCompiler");
	return(bCompiler);
}//bGrhomCompiler

void GrhomDecideR(char *sGrammaireAlgebrique,char *sGrammaireHomogene,char *sMot){
	//dit (printf) si sMot est engendré ou non par sGrammaireHomogene censée expliciter sGrammaireAlgebrique.
	#define ksFichierInexistant ""
	#define nDebutEgale0 0
	int nAppel=0;
	int bCompiler,bDecider,nFin,nRegleEnTout;
	//Appel0("GrhomDecideR");
		bCompiler=bGrhomCompiler(sGrammaireAlgebrique,sGrammaireHomogene,k1Voir,ksFichierInexistant,&nRegleEnTout);
		if (bCompiler){
			GrhomTabuleR(sGrammaireHomogene,nRegleEnTout,!k1Voir);//remplit la variable de module nTablE[][0] 
			bDecider=bGrhomDecideR('S'-'@',sMot,nDebutEgale0,&nFin,!k1Voir,&nAppel) && (nFin==nChaineLg(sMot));//lit nTablE[][0]
			printf("%s: le mot %s %s engendré %s.\n",(bDecider)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecider),sP(sPluriel(nAppel,"appel$ en tout")));
		}
	//Appel1("GrhomDecideR");
}//GrhomDecideR

int bGrhomDecideR(int uRegle,char *sMot,int iDebut,int *piFin,int bVoir,int *pnAppelEnTout){
	//dit si sMot[iDebut,iFin] est engendré ou non par la grammaire décrite dans nTablE[];pnAppelEnTout compte les appels à cette routine récursive 
	const int kuAppelMax=kE4;
	int bDecider=kF;
	int uT,uTermeMax,nType;
	int iDebute,iFinit;
	Assert2("bGrhomDecideR1",bGrhomAmorceR,*pnAppelEnTout<kuAppelMax);
	*pnAppelEnTout+=1;
	uTermeMax=nTablE[uRegle][0];
	nType=nTablE[uRegle][kuTypE];
	Assert1("bGrhomDecideR2",uTermeMax>0);
	if (bVoir)
		printf("Règle %c de type ",'@'+uRegle);
	switch (nType) {
		case  rtET:			for (bDecider=kV,iDebute=iDebut,uT=1;uT<=uTermeMax && bDecider;uT++){
								if (bVoir)
									printf("ET, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuSymbolE]);
								bDecider=bDecider && bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebute,&iFinit,bVoir,pnAppelEnTout);
								iDebute=iFinit;
							}
							*piFin=(bDecider)? iFinit : iDebut;
							break;
		case  rtOU:			for (bDecider=kF,uT=1;uT<=uTermeMax && !bDecider;uT++){
								if (bVoir)
									printf("OU, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuSymbolE]);
								bDecider=bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebut,&iFinit,bVoir,pnAppelEnTout);
							}
							*piFin=(bDecider)? iFinit : iDebut;
							break;
		case  rtTerminalE:	bDecider=(sMot[iDebut]==nTablE[uRegle][1]+'@');
							if (bVoir)
								printf("Terminale, sMot[%d] %s reconnu.\n",iDebut,sEst(bDecider));
							*piFin=(bDecider)? iDebut+1 : iDebut;
							break;
		default:			Assert1("bGrhomDecideR3",0);break;
	}
	return(bDecider);
}//bGrhomDecideR

void GrhomDecliner(char *sGrammaireAlgebrique,char *sGrammaireHomogene,int uMotLgMax){
	//liste tous les mots engéndrés par sGrammaireHomogene qui ont jusqu'à uMotLgMax caractères.
	int nAppel,nAppelMax,nAppelEnTout,nC;
	const int kuBase=2;
	int nBit,bCompiler,bDecliner,bDito,iFin;
	const int kuMotLgMax=20;
	char sMot[1+uMotLgMax];
	int nM,nMot,nMotEngendreh,nMotLg,nMotMax,nMotEnTout;
	int nRegleEnTout;
	const int kuTab=2;
	Assert2("GrhomDecliner",bGrhomAmorceR,bCroitStrict(0,uMotLgMax,kuMotLgMax));//aucune grammaire homogène ne peut engendrer le mot vide
	if (bCompiler=bGrhomCompiler(sGrammaireAlgebrique,sGrammaireHomogene,k1Voir,"",&nRegleEnTout)){
		GrhomTabuleR(sGrammaireHomogene,nRegleEnTout,!k1Voir);
		printf("%sMots engendrés avec l'alphabet {",sTab(kuTab));
		for (nC=0;nC<kuBase;nC++)
			printf("%c%c",'a'+nC,(nC+1<kuBase)?',':'}');
		printf(" ayant %s au maximum:\n",sPluriel(uMotLgMax,"lettre"));
		for (nAppelMax=0,nAppelEnTout=0,nMotEngendreh=0,nMotEnTout=0,nMotLg=0;nMotLg<=uMotLgMax;nMotLg++){
			nMotMax=zPuissance(kuBase,nMotLg);
			sMot[nMotLg]='\0';
			for (bDito=kF,nMot=0;nMot<nMotMax;nMot++){
				for (nM=kuBase*nMot,nBit=0;nM=nM/kuBase,nBit<nMotLg;nBit++)
					sMot[nBit]='a'+ nM % kuBase;
				bDecliner=bGrhomDecideR('S'-'@',sMot,0,&iFin,!k1Voir,(nAppel=0,&nAppel)) && (iFin==nChaineLg(sMot));
				nAppelMax=iMax(nAppelMax,nAppel);
				nAppelEnTout+=nAppel;
				//printf("%s: le mot %s %s engendré.\n",(bDecliner)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecliner));
				nMotEngendreh+=bDecliner;
				if (bDecliner){
					printf("%s%2d: %s",sTab(1+kuTab),nMotEngendreh,sG(sMot));
					if (!bDito)//indiquer la nouvelle longueur nMotLg du mot engendré et des mots suivants
						printf(" %s %s\n",sE(uMotLgMax-nMotLg),sP(sPluriel(nMotLg,"lettre")));
					else Ligne();
					bDito=kV;
				}
			}//for nMot
			nMotEnTout+=nMotMax;
		}//for nMotLg
		if (nMotEngendreh<=0)
			printf("%s Aucun mot n'est engendré",sTab(kuTab));
		else printf("%s%d mots sur %s ont été engendrés",sTab(kuTab),nMotEngendreh,sPar3(nMotEnTout));
		printf(" (pire cas pour décider un mot: %s).\n",sPluriel(nAppelMax,"dérivation"));//"décider": transitif, ce verbe signifie "porter un… 
		//…jugement sur", "arrêter une conclusion définitive sur" et donc ici, déterminer si, oui ou non, un mot est engendré par la grammaire.
		printf("%sNombre total de dérivations exécutées pour décliner tous les mots: %s.\n",sTab(kuTab),sPar3(nAppelEnTout));
	} 
//Appel1("GrhomDecideR");
}//GrhomDecliner

void GrhomExpliciteR(char *sGrAlgebrique,char *sGrHomogene,int nRegleEnTout[2],char *sFichierCible){
	//génère ds sFichierCible le code C qui décide si la variable de module sMOT est engendrée ou non par la sGrHomogene
	int nListe[1+kuRegleMaX];
	int nRang[1+kuRegleMaX];
	int uR,nRg;
	int iErreur;
	Assert4("GrhomExpliciteR0",bGrhomAmorceR,bGrhomCompileR,nRegleEnTout>0,nChaineLg(sFichierCible)>0);
	fGramR=fopen(sFichierCible,"w");
		Assert1("GrhomExpliciteR1",fGramR!=0);
		//nRang[]=rang des noms de routines classés par ordre alphabétique croissant ——afin de déclarer bA() avant bB(),lui-même avant bS(), etc.
			for (uR=1;uR<=nRegleEnTout[1];uR++)
				nListe[uR]=nPilE[uR][kuSymbolE];
			VecteurTrier2(nListe,1,nRegleEnTout[1],nRang);
			EnteteGenereR(sGrAlgebrique,sGrHomogene,nRang,nRegleEnTout,sFichierCible);
			for (uR=1;nRg=nRang[uR],uR<=nRegleEnTout[1];uR++)
				switch (nPilE[nRg][kuTypE]) {
					case  rtET:			RegleEtGenereR(nRg);break;
					case  rtOU:			RegleOuGenereR(nRg);break;
					case  rtTerminalE:	RegleTerminaleGenereR(nRg);break;
					default:			Assert1("GrhomExpliciteR",0);break;
				}
	iErreur=fclose(fGramR);
	Assert1("GrhomExpliciteR2",iErreur==0);
	printf("%sLe fichier %s contient maintenant la traduction de cette grammaire en langage C.\n",sTab(2),sG(sFichierCible));
}//GrhomExpliciteR

int bGrhomHomogenE(char *sGrohm,int nSeparateur[]){
	//vrai ssi sGrohm décrit une liste point-virgulée de règles homogènes contenant A->a et B->b et ayant des membres gauches distincts, dont S.
	int bA=kF,bB=kF;//bA vrai ssi A->a est une règle de la grammaire homogène
	int nDebut,nFin,bHomogene,uR,nRegleEnTout;
	Assert1("bGrhomHomogenE",bGrhomAmorceR);
	//bHomogene:=chaque règle est soit une règle ET soit une règle OU soit une règle terminale.
		for (bHomogene=kV,nRegleEnTout=nSeparateur[0],nDebut=0,uR=1;uR<=nRegleEnTout;uR++){
			nFin=nSeparateur[uR+0]-1;
bHomogene=bHomogene && (bRegleET(uR,sGrohm,nDebut,nFin) || bRegleOU(uR,sGrohm,nDebut,nFin) || bRegleTerminalE(uR,sGrohm,nDebut,nFin,&bA,&bB) || bRegleDenonceR(uR,sGrohm,nDebut,nFin));
			nDebut=nFin+2;
		};
	//les règle terminales contiennent au moins les règles A->a et B->b.
		if (bHomogene && !(bA && bB))
			printf("ANOMALIE: il manque %s.\n",sPluriel(2-(bA+bB),"règle$ terminale$"));
	//les membres gauches des règles sont distincts deux à deux et S est un membre gauche.
		bHomogene=bHomogene && bGrhomPlausiblE(sGrohm,nSeparateur[0]);
	return(bHomogene);
}//bGrhomHomogenE

void GrhomINITIALISER(){
	//relance le présent module
	Assert1("GrhomINITIALISER",bGrhomAmorceR);
}//GrhomINITIALISER

int bGrhomPlausiblE(char *sGrohm,int nRegleEnTout){
	//vrai ssi les membres gauches sont des majuscules distinctes 2 à 2, la règle S est présente, et les membres droits non terminaux sont définis.
	int uL,nLettre,bPlausible,uR,uT,uTermeMax;
	int nMajuscule[1+kuLettreMaX];//comptabilise les occurrences des majuscules situées en membre gauche de règle
	Assert1("bGrhomPlausiblE0",bGrhomAmorceR);
	//Appel0("bGrhomPlausiblE");
		//bPlausible & nMajuscule[X] :=les membres gauches sont des majuscules distinctes 2 à 2 & nb occurrences de X en membre gauche
			bPlausible=kV;
			for (uL=1;uL<=kuLettreMaX;uL++)
				nMajuscule[uL]=0;
			for (uR=1;uR<=nRegleEnTout;uR++){
				nLettre=nPilE[uR][kuSymbolE]-'@';
				if (!bCroit(1,nLettre,kuLettreMaX))
					printf("ANOMALIE: la règle %c commence par un symbole \"%c\" inconnu.\n",'@'+uR,nLettre);
				bPlausible=bPlausible && bCroit(1,nLettre,kuLettreMaX);
				nMajuscule[nLettre]+=1;
			}
			//VecteurVoir("nMajuscule",&nMajuscule[0],1,kuLettreMaX);
		//bPlausible &&= tout membre gauche de règle est cité au plus une fois.
		if (bPlausible)
			for (uL=1;uL<=kuLettreMaX;uL++){
				if (nMajuscule[uL]>1){
					printf("ANOMALIE: la règle \"%c\" est déclarée %d fois.\n",'@'+uL,nMajuscule[uL]);
					bPlausible=kF;
				}
			}
		//bPlausible &&= la règle S est présente
		if (bPlausible)
			if (nMajuscule['S'-'@']!=1){
				printf("ANOMALIE: la règle S manque.\n");
				bPlausible=kF;
			}
		//bPlausible &&= tout membre droit de règle non terminale est défini: c'est bien le membre gauche d'une règle.
		if (bPlausible)
			for (uR=1;uR<=nRegleEnTout;uR++)
				if ( bDans2(nPilE[uR][kuTypE],rtET,rtOU) )
					for (uTermeMax=nPilE[uR][0],uT=1;uT<=uTermeMax;uT++){
						nLettre=nPilE[uR][uT]-'@';
						//tee("uR,nLettre",uR,nLettre);
						if (nMajuscule[nLettre]!=1)
							printf("ANOMALIE: la règle %d invoque un symbole \"%c\" qui n'est pas un nom de règle.\n",uR,nPilE[uR][uT]);
						bPlausible=bPlausible && nMajuscule[nLettre]==1;
					}
	//Appel1("bGrhomPlausiblE");
	return(bPlausible);
}//bGrhomPlausiblE

void GrhomTabuleR(char *sGrohm,int nRegleEnTout,int bVoir){
	//remplit nTablE[]. La règle de nom N de nPilE est renommée N-'@' dans nTablE. L'offset '@' transforme la règle A en règle 1 dans nTablE[].
	int uL,uR,uRegle,nT,nTermeMax;
	Assert1("GrhomTabuleR",bGrhomAmorceR);
	for (uL=1;uL<=kuLettreMaX;uL++)
		for (nT=0;nT<=kuTermeMaX;nT++)
			nTablE[uL][nT]=0;
	for (uR=1;uR<=nRegleEnTout;uR++){
		uRegle=nPilE[uR][kuSymbolE]-'@';//la règle A sera la règle 1 dans nTablE[]
		nTablE[uRegle][kuTypE]=nPilE[uR][kuTypE];//type en fin de ligne
		nTablE[uRegle][kuSymbolE]=nPilE[uR][kuSymbolE];//stocke le nom quasiment au bout de la ligne nTablE[uRegle]
		nTablE[uRegle][0]=nPilE[uR][0];//stocke le nb de termes en tête de ligne
		for (nTermeMax=nPilE[uR][0],nT=1;nT<=nTermeMax;nT++)
			nTablE[uRegle][nT]=nPilE[uR][nT]-'@';//toute référence à un nom de règle devient une référence au n° de la ligne contenant cette règle.
	}
	if (bVoir){
		printf("Tabulation (type en colonne 1,membre gauche en dernière colonne) de la…\n");
		t(sC3b(sTab(1),"…grammaire homogène",sG(sGrohm)));
		for (uL=1;uL<=kuLettreMaX;uL++)
			for (printf("%s(%c) ",sTab(2),'@'+uL),nT=0;nT<=kuTypE || printf("   (%d)",uL) && !bLigne();nT++)
				printf("%3d",nTablE[uL][nT]);
	}
}//GrhomTabuleR

void GrhomTESTER(int iTest){
	//teste le présent module
	int nRegleEnTout=0;
	int bCompiler;
	if (iTest>=0){
		Appel0(sC2("GrhomTESTER,test n°",sEnt(iTest)));
			//iTest=1;
			Assert1("GrhomTESTER",bGrhomAmorceR);
				switch (iTest) {
					case  0:	GrhomCompiler("S->Aa+Ab;A->a","S->A.U;U->A+B;A->a;B->b");
								break;
					case  1:	//L1=b
								//GrhomDecliner("S->B+B","S->B;A->a;B->b",4);//**********
								GrhomCompiler("S->B+B","S->B+B;B->b;A->a");
								break;
					case  2:	//L1=a+b
								GrhomDecliner("S->A+B","S->A+B;A->a;B->b",4);//Liste tous les mots engendrés de longueur <=4
								break;
					case  3:	//L1=(a+)b
								GrhomDecliner("S->P.B;P->A.P+B","S->P.B;P->Q+A;Q->A.P;A->a;B->b",6);
								break;
					case  4:	//L1=(a+)b(a+)
								GrhomDecliner("S->P.b.P;P->aP+a","S->P.B.P;P->Q+A;Q->A.P;A->a;B->b",6);
								break;
					case  5:	//L1=anbn,n>0
								GrhomDecliner("S->A.S.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",6);
								break;
					case  6:	//L1=anb2n,n>1
								GrhomDecliner("S->A.S.B.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",8);
								break;
					case  7:	//L1=a+b+c+d
								GrhomDecliner("S->A+B+C+D;A->a;B->b;C->c;D->d","S->A+B+C+D;A->a;B->b;C->c;D->d",5);
								break;
					case  8:	//L1=anc+b2nd+,n>=0
								GrhomDecliner("S->P.Q;P->A.P.B+R;R->C.R+C;Q->D.Q+D",
									"S->P.Q;P->W+R;W->A.P.B;R->T+C;T->C.R;Q->U+D;U->D.Q;A->a;B->b;C->c;D->d",10);
								break;
					case  9:	//L1=anb2n,n>0 + a2pb*,p>0
								//L1=(a**2p)b+,p>0 + (a**2p),p>0 + a**(2q)a.b.b.b**(4q),q>0
								GrhomDecliner("S->U+V+W;U->A.A.E;E->U+K;K->B.K+B;V->A.A.V+L;L->A.A;W->A.W.B.B+M;M->A.B.B;A->a;B->b",
										"S->U+V+W;U->A.A.E;E->U+K;K->Y+B;Y->B.K;V->Z+L;Z->A.A.V;L->A.A;W->C+M;C->A.W.B.B;M->A.B.B;A->a;B->b",10);
								break;
					case 10:	//L1={mots non vides qui ont autant de a que de b ******* A TERMINER *******}
								GrhomDecliner("S->A.S.B.S + B.S.A.S + A.S.B + B.S.A + A.B + B.A;A->a;B->b",
											"S->G+H+J+K+L+M;G->A.S.B.S;H->B.S.A.S; J-> A . S.   B ; K->B.S.A;L->A.B;M->B.A;A->a;B->b",6);
								break;
					case 11:	//génère le fichier qui décrit la grammaire ci-dessous
bCompiler=bGrhomCompiler("S->A.S.B+A.B","S->P+Q;P->A.S.B;Q->A.B;A->a;B->b",k1Afficher,"Grammaire.c",&nRegleEnTout);
								break;
					default:break;
				}
		Appel1(sC2("GrhomTESTER,test n°",sEnt(iTest)));
	}else GrammaireTESTER(-iTest);
}//GrhomTESTER

int bRecursivitehGauchE(int uRegle){
	//vrai ssi nTablE[][] permet un appel récursif à gauche
	int bGauche=kF;
	int uT,nTerme,uTermeMax,nType;
	Assert1("bRecursivitehGauchE",bCroit(1,uRegle,kuLettreMaX));
	nType=nTablE[uRegle][kuTypE];
	//printf("Regle,Type et cardinal %c (%d) h=%d.\n",'@'+uRegle,nType,nDequeCardinal());
	bGauche=bDequeContient(uRegle);
	if (!bGauche){
		DequeEmpiler(uRegle);
		//DequeVoir("bRecursivitehGauchE");
		switch (nType) {
			case  rtET:			nTerme=nTablE[uRegle][1];
								bGauche=bGauche || bRecursivitehGauchE(nTerme);
								break;
			case  rtOU:			for (uTermeMax=nTablE[uRegle][0],uT=1;uT<=uTermeMax;uT++){
									nTerme=nTablE[uRegle][uT];
									bGauche=bGauche || bRecursivitehGauchE(nTerme);
								}
								break;
			default:			nBof=sDequeDepiler();
		}
	} else RecursivitehGaucheVoiR(" ANOMALIE DÉTECTÉE: récursivité à gauche ",uRegle);
	return(bGauche);
}//bRecursivitehGauchE

void RecursivitehGaucheVoiR(char *sMessage,int uDito){//O(nCardMaX)
	int nCardinal,uS;
	int nFile[1+kuLettreMaX];
	printf("%s%s",sTab(2),sMessage);
	//DequeVoir("AVANT");
	//afficher la pile élément par élément depuis le fond de pile en dépilant temporairement la deque
		for (nCardinal=nDequeCardinal(),uS=nCardinal;uS>=1;uS--)
			nFile[uS]=sDequeDepiler();
		for (uS=1;uS<=nCardinal;uS++)
			printf("%c,",'@'+nFile[uS]);
	printf("%c.\n",'@'+uDito);
	//reconstituer la deque
		for (uS=1;uS<=nCardinal;uS++)
			DequeEmpiler(nFile[uS]);
	//DequeVoir("APRES");
}//RecursivitehGaucheVoiR

int bRegleDenonceR(int nRegle,char *sGrhom,int nDebut,int nFin){
	//rend faux;règle bidon destinée à émettre un message d'erreur
	printf("ANOMALIE: la règle %d est non homogène: \"%s\".\n",nRegle,sChainon(sGrhom,nDebut,nFin));
	return(kF);
}//bRegleDenonceR

int bRegleET(int nRegle,char * sGrhom,int nDebut,int nFin){
	//majuscule->majuscule.majuscule.majuscule
	int uC;
	int nDebut3=nDebut+3;
	int bEt;
	const int kcOperateur='.';
	int bRegle;
	int nTerme;
	bRegle=(nDebut3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
	for (uC=nDebut3;uC<=nFin;uC++)
		if ( bImpair(uC-nDebut3-1) )
			bRegle=bRegle && bMajuscule(sGrhom[uC]);
		else bRegle=bRegle && sGrhom[uC]==kcOperateur;
	bEt=bRegle && bMajuscule(sGrhom[nFin]) && sGrhom[nFin-1]==kcOperateur;
	if (bEt){
		for (nTerme=0,uC=nDebut3;uC<=nFin;uC++){
			//tc("sGrhom[uC]",sGrhom[uC]);
			if (bMajuscule(sGrhom[uC])){
				Assert1("bRegleET1",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]=sGrhom[uC];
			}
			else Assert1("bRegleET2",sGrhom[uC]==kcOperateur);
		}
		//te("****************************bET:nTerme",nTerme);
		nPilE[nRegle][kuTypE]=rtET;
		nPilE[nRegle][0]=nTerme;
		nPilE[nRegle][kuSymbolE]=sGrhom[nDebut];
	}
	//tb("bEt",bEt);
	return(bEt);
}//bRegleET

void RegleEtGenereR(int nRegle){
	int uT;
	int nTermeMax=nPilE[nRegle][0];
	EcrirE3("int b",sC(nPilE[nRegle][kuSymbolE]),"(int iDebut,int *piFin){\n");
		//recopier en commentaire le libellé de la règle
			EcrirE3("    //",sC(nPilE[nRegle][kuSymbolE]),"->");
			for (uT=1;uT<=nTermeMax;uT++){
				EcrirE(sC(nPilE[nRegle][uT]));
				if (uT<nTermeMax)
					EcrirE(".");
			}
			EcrirE("\n");
		//déclarer les variables locales autres que bSucces
			for (EcrirE("    int iA=iDebut,"),uT=1;uT<=nTermeMax;uT++){
				EcrirE3("i",sC('@'+uT+1),"");//commence avec iB
				EcrirE((uT<nTermeMax)? ",":";\n");
			}
		EcrirE("    int bSucces=");
		for (uT=1;uT<=nTermeMax;uT++){
			EcrirE7("b",sC(nPilE[nRegle][uT]),"(i",sC('@'+uT),",&i",sC('@'+uT+1),")");
			if (uT<nTermeMax)
				EcrirE(" && ");
		}
		EcrirE(";\n");
		EcrirE3("    *piFin=(bSucces)?i",sC('@'+nTermeMax+1),":iDebut;\n");
		EcrirE("    return(bSucces);\n");
	EcrirE3("}//b",sC(nPilE[nRegle][kuSymbolE]),"\n\n");
}//RegleEtGenereR

int bRegleOU(int nRegle,char *sGrhom,int nDebut,int nFin){
	//majuscule->majuscule+majuscule+majuscule
	int uC;
	int nDebut3=nDebut+3;
	int bRegle;
	int bOu;
	const int kcOperateur='+';
	int nTerme;
	bRegle=(nDebut3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
	for (uC=nDebut3;uC<=nFin;uC++)
		if ( bImpair(uC-nDebut3-1) )
			bRegle=bRegle && bMajuscule(sGrhom[uC]);
		else bRegle=bRegle && sGrhom[uC]==kcOperateur;
	bOu=bRegle && bMajuscule(sGrhom[nFin]) && sGrhom[nFin-1]==kcOperateur;
	if (bOu){
		for (nTerme=0,uC=nDebut3;uC<=nFin;uC++)
			if (bMajuscule(sGrhom[uC])){
				Assert1("bRegleOU1",nTerme<kuTermeMaX);
				nPilE[nRegle][++nTerme]=sGrhom[uC];
			}
			else Assert1("bRegleOU2",sGrhom[uC]==kcOperateur);
		//te("****************************bOU:nTerme",nTerme);
		nPilE[nRegle][kuTypE]=rtOU;
		nPilE[nRegle][0]=nTerme;
		nPilE[nRegle][kuSymbolE]=sGrhom[nDebut];
	}
	return(bOu);
}//bRegleOU

void RegleOuGenereR(int nRegle){
	int uT;
	int nTermeMax=nPilE[nRegle][0];
	EcrirE3("int b",sC(nPilE[nRegle][kuSymbolE]),"(int iDebut,int *piFin){\n");
		//rappel de la règle
			EcrirE3("    //",sC(nPilE[nRegle][kuSymbolE]),"->");
			for (uT=1;uT<=nTermeMax;uT++){
				EcrirE(sC(nPilE[nRegle][uT]));
				if (uT<nTermeMax)
					EcrirE("+");
			}
			EcrirE("\n");
		//code interne
			EcrirE("    int iFin;\n");
			EcrirE("    int bSucces=");
			for (uT=1;uT<=nTermeMax;uT++){
				EcrirE3("b",sC(nPilE[nRegle][uT]),"(iDebut,&iFin)");
				if (uT<nTermeMax)
					EcrirE(" || ");
			}
			EcrirE(";\n");
			EcrirE("    *piFin=(bSucces)?iFin:iDebut;\n");
			EcrirE("    return(bSucces);\n");
	EcrirE3("}//b",sC(nPilE[nRegle][kuSymbolE]),"\n\n");
}//RegleOuGenereR

int bRegleTerminalE(int nRegle,char *sGrhom,int nDebut,int nFin,int *pbA,int *pbB){
	//majuscule->minuscule et ce sont les mêmes lettres à la casse près; pbA passe à 1 si A->a est rencontré;idem pour pbB.
	int nDebut3=nDebut+3;
	int bRegle;
	const int kuTerme=1;
	int bTerminale;
	bRegle=(nDebut3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
	bTerminale=bRegle && (nDebut3==nFin) && bMinuscule(sGrhom[nFin]) && (sGrhom[nDebut]+0x20==sGrhom[nFin]);
	if (bTerminale){
		nPilE[nRegle][kuTerme]=sGrhom[nFin];
		//teee("nRegle,kuTerme,sGrhom[nFin]",nRegle,kuTerme,sGrhom[nFin]);
		if (sGrhom[nDebut]=='A')
			*pbA=kV;
		if (sGrhom[nDebut]=='B')
			*pbB=kV;
	}
	//te("bTerminale:kuTerme",kuTerme);
	nPilE[nRegle][kuTypE]=rtTerminalE;
	nPilE[nRegle][0]=kuTerme;
	nPilE[nRegle][kuSymbolE]=sGrhom[nDebut];
	return(bTerminale);
}//bRegleTerminalE

void RegleTerminaleGenereR(int nRegle){
	EcrirE3("int b",sC(nPilE[nRegle][kuSymbolE]),"(int iDebut,int *piFin){\n");
		//recopier en commentaire le libellé de la règle
			EcrirE3("    //",sC(nPilE[nRegle][kuSymbolE]),"->");
			EcrirE(sC(nPilE[nRegle][1]));
			EcrirE("\n");
		EcrirE3("    int bSucces = sMOT[iDebut]=='",sC(nPilE[nRegle][1]),"';\n");
		EcrirE("    *piFin = (bSucces) ? iDebut+1 : iDebut;\n");
		EcrirE("    return(bSucces);\n");
	EcrirE3("}//b",sC(nPilE[nRegle][kuSymbolE]),"\n\n");
}//RegleTerminaleGenereR

void TexteCompacteR(char *sNonCompact,char sCompact[1+kuCaractereMaX]){
	//sCompact:=sNonCompact sans blancs
	int uC,uD;
	for (uC=uD=0;uC<nChaineLg(sNonCompact);uC++)
		if (sNonCompact[uC]!=' ')
			sCompact[uD++]=sNonCompact[uC];
	sCompact[uD]='\0';
}//TexteCompacteR


