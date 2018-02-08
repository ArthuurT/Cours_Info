#include "Outil.h"
#include "Alex.h"
#include "Erreur.h"
//module d'analyse lexicale
#define knAEFetatMaX 12
#define knByteLiM 256
enum eCaractereClassE {ccAlphA,ccButoiR,ccDeciT,ccMajusculE,ccMinusculE,ccPoinT,ccSeparateuR,ccGuillemeT,ccOperateuR,ccBlanC,ccDiverS,ccParenthesE,ccOmegA};
#define knClasseCaractereMaX (ccOmegA-ccAlphA+1)
#define kuCodeSourceLgMaX 100
#define knLexemeMaX	511
#define knTrancheMaX 147
#define kbVoiR kV

int iAEF[1+knAEFetatMaX][1+knClasseCaractereMaX];
int bAlexAmorceR;
int ccCaractereClassE[knByteLiM];
char *sCodeSourcE;//alloué dans AlexAMORCER
enum eLexemeClassE    {lcRieN,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcSeparateuR,lcTextE,lcParenthesE,lcFinFichieR};
char *sLexemeClassE  ="lcRieN,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdenT,lcOperH,lcSeparH,lcTextE,lcParenthesE,lcFiN";
int nLexemeEnTouT;
struct rLexemE{int classe;int indexdebut;int indexfin;int ligne;} lxmChainE[1+knLexemeMaX];//la chaîne lexicale est générée dans dans lxmChainE

void AutomateAffecteR(int bVoir);
void ClasseCaractereDefiniR(int bVoir);
int bCodeSourceAnalyseR(int bVoiR);
void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche);
void ErreurDiagnostiqueR(int uAnomalie,int uLigne);
char *sLexemE(int nLexeme);
void LexemeEmpileR();
void LexemeVoiR();

void AlexAfficher(){
	//affiche le code source ligne par ligne
	const int kbNumeroter = kV;
	int nC,nLg,iLigne,bSeparateur;
	//t("AlexAfficher");
	for (nC=0,iLigne=1,nLg=nChaineLg(sCodeSourcE);nC<nLg && (sCodeSourcE[nC]!='$');nC++){
		bSeparateur=(sCodeSourcE[nC]==';');
		if (bSeparateur){
			ErreurAfficher(abs(iLigne));
			printf("\n");
			iLigne=abs(iLigne)+1;//ie il faudra afficher iLigne avant d'afficher le prochain caractère du code source
		}else {
			if (kbNumeroter && iLigne>0){
				printf("Ligne %d: ",iLigne);
				iLigne= - iLigne;//négatif: le numéro iLigne a bien été affiché
			}
			printf("%c",sCodeSourcE[nC]);
		}
	}
	printf("\n");
}//AlexAfficher

void AlexAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	int kbVoir=kF;
	AutomateAffecteR(kbVoir);
	ClasseCaractereDefiniR(kbVoir);
	sCodeSourcE=malloc(1+kuCodeSourceLgMaX);
	bAlexAmorceR=kV;
}//AlexAMORCER

int bAlexAnalyser(char *sCode){
	int bAnalyser;
	//Appel0("bAlexAnalyser");
		strcpy(sCodeSourcE,sCode);
		//printf("   Code source analysé:\"%s\".\n",sCodeSourcE);
		//AlexAfficher();
		bAnalyser=bCodeSourceAnalyseR(kbVoiR);
		if (!bAnalyser)
			AlexDenoncer(0);
	//Appel1("bAlexAnalyser");
	return(bAnalyser);
}//bAlexAnalyser

char *sAlexChaine(int nLexeme){
	char *sChaine=sLexemE(nLexeme);
	return(sChaine);
}//sAlexChaine

int bAlexDate(int uLexeme){
	//uLexeme est bien une date de l'année 2017 (l'année de l'ouverture de la bibliothèque) et au-delà donnée sous la forme JJMMAA.
	int bDate,nEntier,nJour,nMois,nAnnee;
	int nJourEnTout[1+12]={-1,    31,28,31,    30,31,30,    31,31,30,    31,30,31};
	//te("bAlexDate",uLexeme);
	bDate=bAlexEntier(uLexeme);
	if (bDate){
		nEntier=nAlexEntier(uLexeme);
		nAnnee=nEntier%100;
		nEntier=(nEntier-nAnnee)/100;
		nMois=nEntier%100;
		nJour=(nEntier-nMois)/100;
		//teee("nJour,nMois,nAnnee",nJour,nMois,nAnnee);
		bDate=bCroit(1,nJour,31) && bCroit(1,nMois,12) && bCroit(17,nAnnee,99);
		bDate=bDate && nJour<=nJourEnTout[nMois] || (nJour==29 && nMois==2 && nAnnee%4==0);
	}
	return(bDate);
}//bAlexDate

void AlexDenoncer(int nLexeme){
	//affiche en clair la cause de l'erreur lexicale qui a fait empilé un lexème de classe lcInconnU
	int uLxm;
	int nDenonce,nLigne;
	char sLexeme[knByteLiM];
	//Appel0("AlexDenoncer");
		//nDenonce:=rang1 du premier lexème inconnu;il vérifie lxmChainE[uLxm].classe<0
			for (nDenonce=0,nLigne=1,uLxm=1;(uLxm<=nLexemeEnTouT) && (nDenonce==0);uLxm++){
				if (lxmChainE[uLxm].classe==lcInconnU)
					nDenonce=uLxm;
				if (lxmChainE[uLxm].classe==lcSeparateuR)
					nLigne++;
				if (nLexeme==uLxm)
					nDenonce=uLxm;
			}
		Assert1("AlexDenoncer",nDenonce>0);
		CodeSourceTrancheR(lxmChainE[nDenonce].indexdebut,lxmChainE[nDenonce].indexfin,kF,/**/sLexeme);
		printf("   *** ligne %d,lexème \"%s\"",nLigne,sLexeme);
	//Appel1("AlexDenoncer");
}//AlexDenoncer

int bAlexEntier(int uLexeme){
	int bEntier;
	bEntier=bAlexLexeme(uLexeme) && (lxmChainE[uLexeme].classe==lcEntieR);
	return(bEntier);
}//bAlexEntier

int nAlexEntier(int uLexeme){
	int nEntier=0;
	if (bAlexEntier(uLexeme)){
		//tt("sLexemE(uLexeme)",sLexemE(uLexeme));
		sscanf(sLexemE(uLexeme),"%d",&nEntier);
		//te("nEntier",nEntier);
	}
	return(nEntier);
}//nAlexEntier

int nAlexExpression(int uLexeme){
	//rend la pré-vision de l'instruction courante:  1 si réel, 2 si entier, 3 si identificateur, et 0 si échec
	int nExpression=0;
	if (bAlexLexeme(uLexeme)){
		switch (lxmChainE[uLexeme].classe){
			case  lcOperateuR:		nExpression=(sCodeSourcE[lxmChainE[uLexeme].indexdebut]=='?')? 1: 2;break;
			case  lcIdentificateuR:	nExpression=3;break;
		}
	};
	return(nExpression);
}//nAlexExpression

int bAlexFinFichier(int uLexeme){
	int bFinFichier;
	bFinFichier=(uLexeme>=nLexemeEnTouT);
	return(bFinFichier);
}//bAlexFinFichier

int bAlexHoraire(int uLexeme){
	#define kuHeureHeurePointMinuteMinuteLg 5
	int bHoraire;
	float rHoraire;
	int nMinute;
	char sLexeme[knByteLiM];
	bHoraire=bAlexReel(uLexeme);
	if (bHoraire){
		CodeSourceTrancheR(lxmChainE[uLexeme].indexdebut,lxmChainE[uLexeme].indexfin,kF,/**/sLexeme);
		//tt("sLexeme",sG(sLexeme));
		bHoraire=bHoraire && (nChaineLg(sLexeme)==kuHeureHeurePointMinuteMinuteLg);
		if (bHoraire){
			sscanf(sLexeme,"%f5.2",&rHoraire);
			//tr("rHoraire",rHoraire);
			nMinute=trunc(rHoraire*100);
			nMinute=nMinute%100;
			//te("nMinute",nMinute);
			bHoraire=bHoraire && bCroit(0,nMinute,59);
			//compléter le code pour valider les heures
		}
	}
	return(bHoraire);
}//bAlexHoraire

int bAlexIdentificateur(int uLexeme){
	int bIdentificateur;
	bIdentificateur=bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcIdentificateuR;
	return(bIdentificateur);
}//bAlexIdentificateur

void AlexINITIALISER(){//O(?)
	//relance le présent module
	Assert1("AlexINITIALISER",bAlexAmorceR);
}//AlexINITIALISER

int nAlexInstruction(int uLexeme){
	//rend la pré-vision de l'instruction courante:  1 si "?", 2 si "!", 3 si identificateur, et 0 si échec
	//Instruction->Emprunt || Reservation || Achat || Retour || Radiation || Autre
	int nInstruction=0;
	if (bAlexLexeme(uLexeme)){
		switch (lxmChainE[uLexeme].classe){
			case  lcOperateuR:		switch (sCodeSourcE[lxmChainE[uLexeme].indexdebut]){
										case '<':	nInstruction=1;break;//Emprunt
										case '>':	nInstruction=4;break;//Retour
										case '?':	nInstruction=2;break;//Reservation
									};break;
	//Programme->Instructions || FinFichier
	//		Instructions->Instruction Programme
	//Instruction->Emprunt || Reservation || Achat || Retour || Radiation || Autre
	//		Emprunt->"<" Livre Nom
	//		Reservation->"?" Livre Nom
	//		Achat->Prix Livre
	//		Retour->">" Livre Nom
	//		Radiation->Nom
	//		Autre->Entier Suite
	//Suite->Interdiction || Inscription
	//		Interdiction->Livre
	//		Inscription->Nom
			case  lcEntieR:	nInstruction=6;break;//Autre
			case  lcReeL:	nInstruction=3;break;//Achat
			case  lcIdentificateuR:	nInstruction=5;break;//Radiation
		}
	};
	return(nInstruction);
}//nAlexInstruction

int bAlexLexeme(int uLexeme){
	int bLexeme=bCroit(1,uLexeme,nLexemeEnTouT);
	return(bLexeme);
}//bAlexLexeme

int nAlexLigne(int uLexeme){
	//rend le rang1 de la ligne qui contient le lexème d'index uLexeme
	int nLigne;
	Assert1("nAlexLigne",bCroit(1,uLexeme,nLexemeEnTouT));
	nLigne=lxmChainE[uLexeme].ligne;
	return(nLigne);
}//nAlexLigne

int bAlexOperateur(int uLexeme,char cOperateur){
	int bOperateur=bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcOperateuR && sCodeSourcE[lxmChainE[uLexeme].indexdebut]==cOperateur;
	return(bOperateur);
}//bAlexOperateur

int nAlexProgramme(int uLexeme){
	int nProgramme=0;
	if (nAlexInstruction(uLexeme)>0)
		nProgramme=1;
	else if (bAlexFinFichier(uLexeme))
		nProgramme=2;
	return(nProgramme);
}//nAlexProgramme

int bAlexReel(int uLexeme){
	int bReel;
	bReel=bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcReeL;
	return(bReel);
}//bAlexReel

float fAlexReel(int uLexeme){
	float fReel;
	Assert1("fAlexReel",bAlexReel(uLexeme));
	sscanf(sLexemE(uLexeme),"%f\n",&fReel);
	//tr("fReel",fReel);
	return(fReel);
}//fAlexReel

int bAlexSeparateur(int uLexeme){
	int bSeparateur;
	bSeparateur=bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcSeparateuR;
	return(bSeparateur);
}//bAlexSeparateur

int bAlexParenthese(int uLexeme, char cParenthese){
	int bParenthese;
	bParenthese = bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcParenthesE && sCodeSourcE[lxmChainE[uLexeme].indexdebut]==cParenthese;
	return(bParenthese);
}

int nAlexSuite(int uLexeme){
	//rend la pré-vision de l'instruction courante:  1 si Interdiction, 2 si Inscription, et 0 si échec
	//Suite->Interdiction || Inscription
	//		Interdiction->Livre->Texte
	//		Inscription->Nom->Identificateur
	int nSuite=0;
	if (bAlexLexeme(uLexeme)){
		switch (lxmChainE[uLexeme].classe){
			case  lcTextE:			nSuite=1;break;//Interdiction
			case  lcIdentificateuR:	nSuite=2;break;//Inscription
		}
	};
	return(nSuite);
}//nAlexSuite

void AlexTESTER(int iTest){
	//teste le présent module
	int bSucces;
	Appel0(sC2("AlexTESTER,test n°",sEnt(iTest)));
		switch (iTest) {
			case  1:	sCodeSourcE="27 + 3.14 ; CD = 5 * 8 ' $";break;
			case  2:	sCodeSourcE="24 ; 5.2 ; 3...2 ; 4$";break;
			case  3:	sCodeSourcE="";break;
			case  4:	sCodeSourcE="$";break;
			case  5:	sCodeSourcE="27+3.14;EF			=  5*8$";break;
			case  6:    sCodeSourcE="ALPHA1BETA22GAMMA333DELTA4444$$";break;
			case  7:	sCodeSourcE="27+3.14;AB=5*8$"; break;
			case  8:	sCodeSourcE="27+3.14;EF      =  5*8$$";break;
			case  9:	sCodeSourcE="(1+2) == 5$";break;
			default:	Assert1("AlexTESTER: entrée de case inconnue",0); break;
		}
		printf("sCodeSourcE=\"%s\".\n",sCodeSourcE);
		bSucces=bCodeSourceAnalyseR(kbVoiR);
		if (!bSucces)
			AlexDenoncer(0);
	Appel1(sC2("AlexTESTER,test n°",sEnt(iTest)));
}//AlexTESTER

int bAlexTexte(int uLexeme){
	int bTexte;
	bTexte=bAlexLexeme(uLexeme) && lxmChainE[uLexeme].classe==lcTextE;
	return(bTexte);
}//bAlexTexte

void AutomateAffecteR(int bVoir){
	//affecte une fois pour toutes l'automate d'états finis iAEF[]
	// char *sLexemeClassE  ="lcRieN,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdenT,lcOperH,lcSeparH,lcTextE,lcParenthesE,lcFiN";

	char *sAEF[1+knAEFetatMaX];
	const int knPas=5;//nombre total de caractères disponibles pour spécifier l'état suivant ds la i-ième ligne de texte sAEF[ligne i]
	int nL,nC;
	if (bVoir) Appel0("AutomateAffecteR");
		for (nL=0;nL<=knAEFetatMaX;nL++)
			sAEF[nL]=malloc(knPas*(1+knClasseCaractereMaX));//pas de free plus bas, mais cette routine n'est appelée qu'une fois
	    //classes:       $  0..9  AZ   az    .    ;    "  operH blc  autre ()
		sAEF[ 0]="    0   10    3    5    8    0    7   12    6    1    2    9";//dispatcheur vers les sous-automates
		sAEF[ 1]="    0    0    0    0    0    0    0    0    0    1    0    0";//lcBlanC
		sAEF[ 2]="    0    0    0    0    0    0    0    0    0    0    2    0";//lcInconnU
		sAEF[ 3]="    0    0    3    0    0   11    0    0    0    0    0    0";//lcEntieR
		sAEF[ 4]="    0    0    4    0    0    0    0    0    0    0    0    0";//lcReeL
		sAEF[ 5]="    0    0    5    5    5    0    0    0    0    0    0    0";//lcIdentificateuR
		sAEF[ 6]="    0    0    0    0    0    0    0    0    0    0    0    0";//lcOperateuR
		sAEF[ 7]="    0    0    0    0    0    0    0    0    0    0    0    0";//lcSeparateuR
		sAEF[ 8]="    0    0    0    0    8    0    0    0    0    0    0    0";//lcTextE
		sAEF[ 9]="    0    0    0    0    0    0    0    0    0    0    0    0";//lcParenthesE
		sAEF[10]="    0    0    0    0    0    0    0    0    0    0    0    0";//lcFinFichieR

		sAEF[11]="    0   -1    4   -1   -1   -2   -2   -1   -1   -1    0   -1";//un point a été rencontré;constante réelle attendue
		sAEF[12]="    0   -3   12   12   12   12   12    8   12   12    0   12";//un guillemet a été rencontré;guillemet fermant attendu
		for (nL=0;nL<=knAEFetatMaX;nL++){
			for (nC=0;nC<=knClasseCaractereMaX;nC++){
				sscanf(sAEF[nL]+knPas*nC,"%d\n",&iAEF[nL][nC]);
				if (bVoir)
					printf("[%2d,%2d]=%2d ",nL,nC,iAEF[nL][nC]);
			}
			if (bVoir)
				printf("\n");
		}
	if (bVoir) Appel1("AutomateAffecteR");
}//AutomateAffecteR

void ClasseCaractereDefiniR(int bVoir){
	//définit une fois pour toutes la classe ClasseDeC au caractère C en mémorisant ClasseDeC dans ccCaractereClassE[C] pour tout C.
	if (bVoir) Appel0("ClasseCaractereDefiniR");
		int nC,nClasse;
		for (nC=0;nC<knByteLiM;nC++){
			nClasse=ccDiverS;
			if (isdigit(nC)) nClasse=ccDeciT;
			if (isupper(nC)) nClasse=ccMajusculE;
			if (islower(nC)) nClasse=ccMinusculE;
			if (nC=='.') nClasse=ccPoinT;
			if (nC=='(') nClasse=ccParenthesE;
			if (nC==')') nClasse=ccParenthesE;
			if (nC==';') nClasse=ccSeparateuR;
			if (nC=='"') nClasse=ccGuillemeT;
			if ( (nC=='<') || (nC=='>') || (nC=='?') ) nClasse=ccOperateuR;
			if (nC==' ') nClasse=ccBlanC;//blanc ou assimilé
			if (nC=='$') nClasse=ccButoiR;
			ccCaractereClassE[nC]=nClasse;
			if (bVoir)
				printf("caractère %3d    classe %2d \n",nC,nClasse);
		}
	if (bVoir) Appel1("ClasseCaractereDefiniR");
}//ClasseCaractereDefiniR

int bCodeSourceAnalyseR(int bVoiR){
	//analyse le code source censé figurer dans sCodeSourcE[] et empile la chaîne lexicale dans lxmChainE
	// enum eLexemeClassE    {lcRieN,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcSeparateuR,lcTextE,lcFinFichieR};

	int bAnalyser,nC,nClasse,nClim,nEtat,nEtat0,nDebut;
	//Appel0("bCodeSourceAnalyseR");
		Assert1("bCodeSourceAnalyseR0",bAlexAmorceR);
		bAnalyser=kV;
		nLexemeEnTouT=0;
		nClim=nChaineLg(sCodeSourcE);
		for (nEtat=0,nC=0,nDebut=nC;nC<=nClim;nC++){// *** donc un caractère "\0" est lu
			nClasse=ccCaractereClassE[sCodeSourcE[nC]];
			nEtat0=nEtat;
			nEtat=iAEF[nEtat0][nClasse];
			if (!k1Afficher)
				printf("passe %d: à l'état courant %d, '%c' est lu, de classe %d, donc iAEF[%d][%d] rend %d.\n",nC,nEtat0,sCodeSourcE[nC],nClasse,nEtat0,nClasse,nEtat);
			//d2(nEtat,bAnalyser);
			if (nEtat<=0){
				if (nEtat0!=lcBlanC){//empiler le lexème courant dans la chaîne lexicale de sommet nLexemeEnTouT
					//bAnalyser=bAnalyser && (-nEtat!=lcInconnU);
					int lcClasseLexeme = (nEtat==0) ? nEtat0 : nEtat;
					if (!(lcClasseLexeme >= lcRieN && lcClasseLexeme <= lcFinFichieR)) {
						lcClasseLexeme = lcInconnU;
					}
					LexemeEmpileR(++nLexemeEnTouT,lcClasseLexeme, nDebut, nC, !k1Afficher);
					// LexemeEmpileR(++nLexemeEnTouT,(nEtat==0)? nEtat0 : nEtat, nDebut, nC, !k1Afficher);
				}
				nEtat=0;
				nDebut=nC;
				nEtat=iAEF[nEtat][nClasse];
			}
		}
		if ((nLexemeEnTouT<=0) || (lxmChainE[nLexemeEnTouT].classe!=lcFinFichieR))
			LexemeEmpileR(++nLexemeEnTouT,lcFinFichieR, nDebut, nDebut+1, !k1Afficher);
		if (k1Afficher)
			LexemeVoiR();
		if (k1Afficher && bVoiR)
			t(sC3b("      Il",sUn("y a",!bAnalyser),"lexème inconnu"));
		//te("nClim",nClim);
		//te("lcFinFichieR",lcFinFichieR);
		Assert2("bCodeSourceAnalyseR2",nLexemeEnTouT>0,(!bAnalyser || lxmChainE[nLexemeEnTouT].classe==lcFinFichieR));
		//tb("bAnalyser",bAnalyser);
	//Appel1("bCodeSourceAnalyseR");
	return bAnalyser;
}//bCodeSourceAnalyseR

void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche){
	//copie dans sTranche le fragment sCodeSourcE[nDebutInclus..nFinExclue[
	int nC,bValide;
	bValide=bCroit(0,nDebutInclus,nFinExclue-1) && (nFinExclue-nDebutInclus<knTrancheMaX);
	sTranche[0]='\0';
	if (bValide){
		for (nC=nDebutInclus;nC<nFinExclue;nC++)
			sTranche[nC-nDebutInclus]=sCodeSourcE[nC];
		sTranche[nFinExclue-nDebutInclus]='\0';
	}
	else Assert1(sC5p("CodeSourceTrancheR:tranche [",sEnt(nDebutInclus),"..",sEnt(nFinExclue),"[ invalide"),bValide);
}//CodeSourceTrancheR

void ErreurDiagnostiqueR(int uAnomalie,int uLigne){
	//affiche en clair un message censé aider l'utilisateur à comprendre facilement la cause de son erreur
	char *sBug;
	Appel0("ErreurDiagnostiqueR");
		Assert2("ErreurDiagnostiqueR",uAnomalie>0,uLigne>0);
		sBug=malloc(100);
		sBug="Compilateur défectueux";//signifiera que le code ci-dessous la clause "default" a été malencontreusement activée
		switch (-lxmChainE[uAnomalie].classe) {
			case  1:	sBug="Bug n°1";break;// *** remplacer ce message par quelque chose de plus constructif SVP
			case  2:	sBug="Bug n°2";break;// *** remplacer ce message par quelque chose de plus constructif SVP
			default:break;
		}
		printf("Erreur lexicale ligne %d: %s.\n",uLigne,sBug);
	Appel1("ErreurDiagnostiqueR");
}//ErreurDiagnostiqueR

char *sLexemE(int uLexeme){
	//rend le fragment sCodeSourcE[nDebutInclus..nFinExclue[
	char *sLexeme=malloc(100);
	sLexeme[0]='\0';
	CodeSourceTrancheR(lxmChainE[uLexeme].indexdebut,lxmChainE[uLexeme].indexfin,!k1Voir,sLexeme);
	return(sLexeme);
}//sLexemE

void LexemeEmpileR(int uLxmIndex,int nLxmClasse,int nLxmDebutInclus,int nLxmFinExclue, int bVoir){
	char sLexeme[knByteLiM];
	//Appel0("LexemeEmpileR");
		Assert3("LexemeEmpileR1",uLxmIndex>0,bCroit(lcRieN,nLxmClasse,lcFinFichieR),bCroit(0,nLxmDebutInclus,nLxmFinExclue));
		lxmChainE[uLxmIndex].classe=nLxmClasse;
		lxmChainE[uLxmIndex].indexdebut=nLxmDebutInclus;
		lxmChainE[uLxmIndex].indexfin=nLxmFinExclue;
		//te("uLxmIndex",uLxmIndex);
		lxmChainE[uLxmIndex].ligne=(uLxmIndex==1)? 1: lxmChainE[uLxmIndex-1].ligne;
		if (uLxmIndex>1 && lxmChainE[uLxmIndex-1].classe==lcSeparateuR)
			lxmChainE[uLxmIndex].ligne++;
		CodeSourceTrancheR(nLxmDebutInclus,nLxmFinExclue,bVoir,/**/sLexeme);
		//stocker sLexeme dans le dictionnaire
			/*  *** code à compléter ici pour remplir le dictionnaire*/
		if (bVoir)
			printf("              Empilement du lexème %2d: (classe %d, lexie \"%s\").\n",uLxmIndex,nLxmClasse,sLexeme);
	//Appel1("LexemeEmpileR");
}//LexemeEmpileR

void LexemeVoiR(){
	int uLxm;
	printf("Chaine lexicale (%s):\n",sPluriel(nLexemeEnTouT,"lexème"));
	for (uLxm=1;uLxm<=nLexemeEnTouT;uLxm++){
		//printf("   Lexème n°%2d: (%2d,%2d,%2d)\n",uLxm,lxmChainE[uLxm].classe,lxmChainE[uLxm].indexdebut,lxmChainE[uLxm].indexfin);
		printf("   Lexème n°%2d: %-7s %s ligne %d.\n",uLxm,sItem(sLexemeClassE,lxmChainE[uLxm].classe+1),sG(sLexemE(uLxm)),lxmChainE[uLxm].ligne);
	}
}//LexemeVoiR
