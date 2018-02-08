#include "Outil.h"

#define kuAntiSlashZerO 1 //encombrement du caractère "\0" qui délimite les chaînes de caractères
#define kuAppelMaX 63
#define kcEchappemenT1 -61
#define kcEchappemenT2 -59
#define kuEntierSizE 23 //touche pas
#define kuMallocGererLiM 512 
#define kuMallocGererMaX (kuMallocGererLiM-1) 
#define kuPileMaX 256
#define kuWhileMaX 5 //nb max de while imbriqués (si des appels récursifs imbriquent un grand nombre de while, augmenter sensiblement cette valeur)
//constantes et variables:
char *sAlphabetMajusculE="A,À,Â,Ä,B,C,Ç,D,E,É,È,Ê,Ë,F,G,H,I,Î,Ï,J,K,L,M,N,Ñ,O,Ô,Ö,P,Q,R,S,T,U,Ù,Ü,V,W,X,Y,Ÿ,Z";
char *sAlphabetMinusculE="a,à,â,ä,b,c,ç,d,e,é,è,ê,ë,f,g,h,i,î,ï,j,k,l,m,n,ñ,o,o,ö,p,q,r,s,t,u,u,ü,v,w,x,y,ÿ,z";
int bAppeL[1+kuAppelMaX];//dédié au contrôle des appels de routines Appel0() et Appel1()
int nAppeL=0;//initialisation vitale ici car OutilAmorcer n'a pas encore été appelé à l'appel de Appel0() en tête de main();dédié Appel0() et Appel1()
const int kuAppelActiF=kV;
char cChaineGarniR;//caractère de remplissage (espace blanc par défaut) utilisé dans les routines sChaine0,sChaine1 et sChaine2.
int nMallocGereR0;
long yMallocGereR0[kuMallocGererLiM];
int nMallocGereR1;
long yMallocGereR1[kuMallocGererLiM];
int zuMallocGereR;
int bOutilAmorceR;//ie le module a bien été amorcé
int iEntierPilE[1+kuPileMaX];
int ipEntierPilE;//index sur iEntierPilE 
int uPremieR[1+kuPremierRgMax];
int ipWhilE=0;//index de pile dédié While() et bWhile()
long zWhilE[1+kuWhileMaX];
//prototypes de TOUTES les routines privées,ci-dessous,en .c,puisque le .h doit être réservé aux prototypes sde routines publiques appelées effectivement depuis l'extérieur. 
void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT0(char *sContexte,int bAssertion,int nParametre);
void ChronoTesteR();
int bConsonnE2(char *sTexte,int *pnCodeCaractereRg0);
int bLettrE2(char *sTexte,int *pnCodeCaractereRg0);
void MallocGereR(char *sMalloc);//technique,gère les malloc et les free des chaînes de caractères
void PremierAmorceR();
int bVoyellE2(char *sTexte,int *pnCodeCaractereRg0);

void t(char *sTexte){
	assert(sTexte!=0);
	printf("%s.\n",sTexte);
}//t

void tb(char *sTexte,int bBooleen){
	printf("%s:%s.\n",sTexte,(bBooleen!=0)?"vrai":"faux");
}//tb

void tc(char *sTexte,char cCaractere){
	printf("%s:'%c'.\n",sTexte,cCaractere);
}//tc

void te(char *sTexte,long yEntier1){
	printf("%s:%li.\n",sTexte,yEntier1);
}//te

void tee(char *sTexte,long yEntier1,long yEntier2){
	printf("%s:%li, %ld.\n",sTexte,yEntier1,yEntier2);
}//tee

void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3){
	printf("%s:%li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3);
}//teee

void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4){
	printf("%s:%li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4);
}//teeee

void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5){
	printf("%s:%li, %li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5);
}//teeeee

void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6){
	printf("%s:%li, %li, %li, %li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5,yEntier6);
}//teeeeee

void tq(char *sTexte,q qRationnel){
	//affiche sTexte puis qRationnel: tq("qA",qA) affiche "eA:2/3" si qA vaut 2/3.
	printf("%s:%s.\n",sTexte,sQ(qRationnel));
}//tq

void tr(char *sTexte,double dReel1){
	printf("%s:%lf.\n",sTexte,dReel1);//ou %8.3lf pr 8 caractères en tout et 3 décimales
}//tr

void tri(char *sTexte,ri rComplexe){
	//affiche sTexte puis rComplexe: tri("riA",riA) affiche "eA:2+i" si eA vaut 2+i.
	printf("%s:%s.\n",sTexte,sK(rComplexe));
}//tri

void trr(char *sTexte,double dReel1,double dReel2){
	printf("%s:%lf, %lf.\n",sTexte,dReel1,dReel2);
}//trr

void trrr(char *sTexte,double dReel1,double dReel2,double dReel3){
	printf("%s:%lf, %lf, %lf.\n",sTexte,dReel1,dReel2,dReel3);
}//trrr

void tt(char *sTexte1,char *sTexte2){
	Assert2("Routine tt",sTexte1!=0,sTexte2!=0);
	printf("%s, %s.\n",sTexte1,sTexte2);
}//tt

void ttt(char *sTexte1,char *sTexte2,char *sTexte3){
	Assert3("Routine ttt",sTexte1!=0,sTexte2!=0,sTexte3!=0);
	printf("%s, %s, %s.\n",sTexte1,sTexte2,sTexte3);
}//ttt

void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4){
	Assert4("Routine tttt",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0);
	printf("%s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4);
}//tttt

void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5){
	Assert5("Routine sssss",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0,sTexte5!=0);
	printf("%s, %s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4,sTexte5);
}//ttttt

void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	//contrôle les assertions fournies en paramètres et indique toutes celles qui ne sont pas vérifiées
	int bAssertion=bAssertion1 && bAssertion2 && bAssertion3 && bAssertion4 && bAssertion5 && bAssertion6;
	if (!bAssertion){//si une assertion est fausse,afficher sContexte et le numéro de cette assertion ——afin de faciliter le débogage ultérieur.
		AsserT0(sContexte,bAssertion1,1); 
		AsserT0(sContexte,bAssertion2,2); 
		AsserT0(sContexte,bAssertion3,3);
		AsserT0(sContexte,bAssertion4,4);
		AsserT0(sContexte,bAssertion5,5);
		AsserT0(sContexte,bAssertion6,6);
	}
	assert(bAssertion);//si bAssertion est vrai,indolore;sinon,affiche un message système qui ne vous sera d'aucune utilité puis stoppe l'exécution.
}//AsserT

void AsserT0(char *sContexte,int bAssertion,int nParametre){
	if (!bAssertion){
		printf("    *** Assertion fausse (expression booléenne n°%d)",nParametre);
		if (nChaineLg(sContexte)>0)
			printf(" dans \"%s\"",sContexte);
		printf(".\n");
	}
}//AsserT0

void Assert1(char *sContexte,int bAssertion1){
	AsserT(sContexte,bAssertion1,kV,kV,kV,kV,kV);
}//Assert1

void Assert2(char *sContexte,int bAssertion1,int bAssertion2){
	AsserT(sContexte,bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert2

void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//Assert3

void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//Assert4

void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//Assert5

void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Assert6

int nAbs(int iEntier){
	//rend la valeur absolue positive de iEntier ou déroute si iEntier est trop négatif;cache la fonction abs
	int nAbs;
	Assert1("nAbs0",iEntier!=kiIntegerMin);
	nAbs=abs(iEntier);//>=0 ssi iEntier!=kiIntegerMin
	Assert1("nAbs1",nAbs>=0);
	return(nAbs);
}//nAbs

long zAbs(long yEntier){
	//rend la valeur absolue positive ou déroute si yEntier est trop négatif;cache la fonction labs
	long zAbs;
	Assert1("zAbs0",yEntier!=kyLongintMin);
	zAbs=labs(yEntier);//>=0 ssi yEntier!=kyLongintMin
	Assert1("zAbs1",zAbs>=0);
	return(zAbs);
}//zAbs

q qAdd(q qA,q qB){
	//somme de deux rationnels
	q qAdd;
	int xPgcd;
	Assert2("qAdd1",qA.den>0,qB.den>0);
	qAdd.num=qA.num*qB.den+qB.num*qA.den;
	qAdd.den=qA.den*qB.den;
	if (qAdd.num!=0){
		xPgcd=zPgcd(abs(qAdd.num),qAdd.den);
		qAdd.den/=xPgcd;
		qAdd.num/=xPgcd;
	} else qAdd.den=1;
	Assert1("qAdd2",qA.den>0);
	return(qAdd);
}//qAdd

ri riAdd(ri riA,ri riB){
	//somme de deux nombres complexes à composantes entières
	ri riAdd;
	riAdd.r=riA.r+riB.r;
	riAdd.i=riA.i+riB.i;
	return(riAdd);
}//riAdd

ri riAff(int iReel,int iImaginaire){
	//rend le nombre complexe iReel+i.iImaginaire
	ri riAff;
	riAff.r=iReel;
	riAff.i=iImaginaire;
	return(riAff);
}//riAff

void Appel0(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Exécution en cours...". Puis passe à la ligne. Vérifie le parenthésage des appels.
	Assert2("Appel0a",sMessage!=0,nAppeL<kuAppelMaX);
	FlipFlop("Appel0b",1,&bAppeL[++nAppeL]);//vérifie que Appel0() ne suit pas un Appel0(), ie il y a 1 Appel1() entre eux
	if (kuAppelActiF){
		if (strlen(sMessage)==0){
			printf("Exécution en cours...\n");
		} else printf("%s%s: tâche en cours...\n",sE(2*nAppeL),sMessage);
	}
	//printf("Appel0 n°%d.\n",nAppeL);
}//Appel0

void Appel1(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Exécution terminée.". Puis passe à la ligne. Vérifie le parenthésage des appels.
	int nMessageLg=strlen(sMessage);
	Assert2("Appel1a",sMessage!=0,nAppeL>0);
	FlipFlop("Appel1b",0,&bAppeL[nAppeL]);//vérifie que Appel1() ne suit pas un Appel1(), ie il y a 1 Appel0() entre eux
	if (kuAppelActiF){
		if (nMessageLg)
			printf("%s%s: tâche terminée.\n",sE(2*nAppeL),sMessage);
		else printf("Exécution terminée.\n");
	}
	nAppeL--;
	Assert1("Appel1c",nAppeL>=0);
	if (!nMessageLg){
		Assert1("Appel1d",nAppeL==0);//ie Appel0() et Appel1() sont correctement parenthésés
		Assert1("Appel1e",ipWhilE>=0);//si ok,il y a bien 1° un appel à While() avant chaque while/do while et 2° un appel à bWhile() dans ladite boucle
	}
	//printf("Appel1 n°%d.\n",nAppeL);
}//Appel1

long yArrondi(double dNombre){
	Assert1("yArrondi",fabs(dNombre)<kxLongintMax);//on peut faire mieux
	long yArrondi=(dNombre>=0.0)? (long) (dNombre+0.5): (long) (dNombre-0.5);
	return(yArrondi);
}//yArrondi

char *sAvec(int bAvecSinonSans,char *sQuoi){
	char *sAvec=sC2b(sChoix(bAvecSinonSans,"avec","sans"),sQuoi);
	return(sAvec);
}//sAvec

int bBit(char cCaractere){
	int bBit=(cCaractere=='0') || (cCaractere=='1');
	assert(bBit==0 || bBit==1);
	return(bBit);
}//bBit

int bBool(long yEntier){
	int bBool=(yEntier==0) || (yEntier==1);
	assert(bBool==0 || bBool==1);
	return(bBool);
}//bBool

int iBorner(int iBorneInf,int iValeur,int iBorneSup){
	//rend iValeur si iBorneInf≤iValeur≤iBorneSup, ou la borne la plus proche de iValeur
	Assert1("iBorner",iBorneInf<=iBorneSup);
	int iBorner=iValeur;
	iBorner=iSup(iBorneInf,iBorner);
	iBorner=iInf(iBorner,iBorneSup);
	return(iBorner);
}//iBorner

long yBorner(long yBorneInf,long yValeur,long yBorneSup){
	//rend yValeur si yBorneInf≤yValeur≤yBorneSup, ou la borne la plus proche de yValeur
	Assert1("yBorner",yBorneInf<=yBorneSup);
	long yBorner=yValeur;
	yBorner=ySup(yBorneInf,yBorner);
	yBorner=yInf(yBorner,yBorneSup);
	return(yBorner);
}//yBorner

char *sBool(long yValeur){
	//rend en clair la valeur booléenne de yValeur
	if (yValeur)
		return("vrai");
	else return("faux");
}//sBool

int bByte(long yEntier){
	int bByte=bCroit(0,yEntier,kuByteMax);
	return(bByte);
}//bByte

char *sC(char cImprimableOuEspace){
	//convertit cImprimableOuEspace en string;cA est censé être soit un caractère imprimable (pas de lettre accentuée) soit un espace.
	char *sCaractere=malloc(1+kuAntiSlashZerO);
		//Assert1("sC",isprint(cImprimableOuEspace) || isspace(cImprimableOuEspace));//isspace: espace,saut page,fin ligne,retour chariot,tabulation.
		sCaractere[0]=cImprimableOuEspace;
		sCaractere[1]='\0';
	MallocGereR(sCaractere);
	return(sCaractere);
}//sC

char *sC1(char *sNonNull){
	//rend sNonNull après avoir vérifié que sNonNull n'est pas pointeur NULL
	assert(sNonNull!=NULL);
	return(sNonNull);
}//sC1

char *sC1p(char *sA){
	//concatène sA et "."
	assert(sA!=0);
	char *sAccu=sC2(sA, ".");
	return(sAccu);
}//sC1p

char *sC2(char *sA,char *sB){
	//concatène sA et sB
	int uRequis;
	Assert2("routine sC2",sA!=0,sB!=0);
	uRequis=1+nChaineLg(sA)+nChaineLg(sB);
	char *sAccu=malloc(uRequis+kuAntiSlashZerO);
		strcpy(sAccu,sA);
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2

char *sC2b(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bBlancEnSus,nRequis;
	char *sAccu;
	Assert2("routine sC2b",sA!=0,sB!=0);
	nRequis=nChaineLg(sA)+nChaineLg(sB);
	assert(nRequis>=0);
	bBlancEnSus=(nChaineLg(sA)>0) && (nChaineLg(sB)>0);
	if (bBlancEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par nChaineLg...Le 4 minimise les dégâts
		strcpy(sAccu,sA);
		if (bBlancEnSus)
			strcat(sAccu," ");
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2b

char *sC2bp(char *sA,char *sB){
	//concatène sA,sB et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC2b(sA,sB),".");//sC2b vérifie que sA et sB sont définis
	return(sAccu);
}//sC3bp

char *sC2p(char *sA,char *sB){
	//concatène sA,sB et "."
	char *sAccu=sC2(sC2(sA, sB),".");//sC2 vérifie que sA et sB sont définis
	return(sAccu);
}//sC2p

char *sC2v(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bVirguleEnSus,nRequis;
	char *sAccu;
	Assert2("routine sC2v",sA!=0,sB!=0);
	nRequis=nChaineLg(sA)+nChaineLg(sB);
	assert(nRequis>=0);
	bVirguleEnSus=(nChaineLg(sA)>0) && (nChaineLg(sB)>0);
	if (bVirguleEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par nChaineLg...Le 4 minimise les dégâts
		strcpy(sAccu,sA);
		if (bVirguleEnSus)
			strcat(sAccu,",");
		strcat(sAccu,sB);
	MallocGereR(sAccu);
	return(sAccu);
}//sC2v

char *sC3(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC
	char *sAccu=sC2(sC2(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3

char *sC3b(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC2b(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3b

char *sC3bp(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC3b(sA,sB,sC),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3bp

char *sC3p(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "."
	char *sAccu=sC4(sA,sB,sC, ".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3p

char *sC3v(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3v

char *sC4(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD
	char *sAccu=sC2(sC3(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4

char *sC4b(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC3b(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4b

char *sC4bp(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4bp

char *sC4p(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "."
	char *sAccu=sC2(sC4(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4p

char *sC4v(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC2v(sC,sD));//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4v

char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE
	char *sAccu=sC2(sC4(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5

char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5b

char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC5b(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5bp

char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5p

char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6

char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC5b(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6b

char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC6b(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6bp

char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6p

char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7

char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC6b(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7b

char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC7b(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7bp

char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "."
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7p

char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8

char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC7b(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8b

char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8bp

char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "."
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8p

char *sC9(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et sI
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),sI);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9

char *sC9b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et sI en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),sI);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9b

char *sC9bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH,sI et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC9b(sA,sB,sC,sD,sE,sF,sG,sH,sI),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9bp

char *sC9p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH,sI et "."
	char *sAccu=sC2(sC9(sA,sB,sC,sD,sE,sF,sG,sH,sI),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC9p

int nCaractere(char *sTexte){
	//rend le nbre de caractères et blancs de sTexte contrairt à strlen() et nChaineLg() qui renvoient le nbre de CODES caractères:strlen("à")=2.
	int nC=0;//index sur le code caractère courant de sTexte
	int nCaractere=0;
	int nLg;
	char cCode;
	assert(sTexte!=0);
	//Appel0("nCaractere");
	for (nLg=nChaineLg(sTexte),nC=0;nC<nLg;nC++){
		cCode=sTexte[nC];
		//printf("sTexte[%d]=cCode %c\n",nC,cCode);
		if ( bLettrE2(sTexte,&nC)//EN TETE afin d'avancer sur nC; sinon isalpha rendrait vrai et bLettrE2 ne serait pas appelé
		|| (cCode=' ') || isalpha(cCode) || isdigit(cCode) )//bLettrE2: voyelle ou consonne avec un signe diacritique
			nCaractere++;
	}
	assert(nCaractere>=0);
	//Appel1("nCaractere");
	return(nCaractere);
}//nCaractere

int nCarreh(int iValeur){
	int nCarreh=iValeur*iValeur;
	Assert1("nCarreh",nCarreh>=0);
	return(nCarreh);
}//nCarreh

int nCas16(int bA,int bB,int bC,int bD){
	//rend 8*bA+4*bB+2*bC+bD dans 0..15,soit 16 cas
	Assert4("nCas16",bBool(bA),bBool(bB),bBool(bC),bBool(bD));
	int nCas16=8*bA+4*bB+2*bC+bD;
	return(nCas16);
}//nCas16

int nCas4(int bA,int bB){
	//rend 2*bA+bB dans 0..3,soit 4 cas
	Assert2("nCas4",bBool(bA),bBool(bB));
	int nCas4=2*bA+bB;
	return(nCas4);
}//nCas4

int nCas8(int bA,int bB,int bC){
	//rend 4*bA+2*bB+bC dans 0..7,soit 8 cas
	Assert3("nCas8",bBool(bA),bBool(bB),bBool(bC));
	int nCas8=4*bA+2*bB+bC;
	return(nCas8);
}//nCas8

char *sChaine(char cCaractere){
	//convertit cCaractere en char *
	return(sC(cCaractere));
}//sChaine

char *sChaine0(char *sTexte,int nLargeurHorsTout){
	//rend sTexte cadré à droite sur nLargeurHorsTout caractères. Tronque sTexte si trop grand.
	Assert1("sChaine0",0<=nLargeurHorsTout);
	int nC,nCarLim,nOffset,nTexteLg;;
	char *sChaine0;
	sChaine0=malloc(nLargeurHorsTout+kuAntiSlashZerO);
		for (nC=0;nC<nLargeurHorsTout;nC++)
			sChaine0[nC]=cChaineGarniR;
		sChaine0[nLargeurHorsTout]='\0';
		nTexteLg=nChaineLg(sTexte);
		nCarLim=iInf(nLargeurHorsTout,nTexteLg);
		nOffset=nLargeurHorsTout-nCarLim;
		for (nC=0;nC<nCarLim;nC++){
			Assert2("sChaine00",bCroit(0,nOffset+nC,nLargeurHorsTout-1),bCroit(0,nC,nTexteLg-1));
			sChaine0[nOffset+nC]=sTexte[nC];
		}
	MallocGereR(sChaine0);
	return(sChaine0);
}//sChaine0

char *sChaine1(char *sTexte,int nLargeurHorsTout){
	//rend sTexte cadré à gauche sur nLargeurHorsTout caractères. Tronque sTexte si trop grand.
	Assert1("sChaine1 appel",0<=nLargeurHorsTout);
	int nC,nCarLim,nOffset,nTexteLg;
	char *sChaine1;
	sChaine1=malloc(nLargeurHorsTout+kuAntiSlashZerO);
		for (nC=0;nC<nLargeurHorsTout;nC++)
			sChaine1[nC]=cChaineGarniR;
		sChaine1[nLargeurHorsTout]='\0';
		nTexteLg=nChaineLg(sTexte);
		nCarLim=iInf(nLargeurHorsTout,nTexteLg);
		nOffset=iSup(0,nTexteLg-nLargeurHorsTout);
		for (nC=0;nC<nCarLim;nC++){
			Assert2("sChaine11",bCroit(0,nC,nLargeurHorsTout-1),bCroit(0,nC,nTexteLg-1));
			sChaine1[nC]=sTexte[nOffset+nC];
		}
	MallocGereR(sChaine1);
	//tt("sChaine1",sG(sChaine1));
	return(sChaine1);
}//sChaine1

char *sChaine2(char *sTexte,int nLargeurHorsTout){
	//rend nLargeurHorsTout caractères contenant sTexte centré et entouré de blancs.
	Assert1("sChaine2",0<=nLargeurHorsTout);
	int nC,nCarLim,nMarge,nTexteLg;
	char *sChaine2=malloc(nLargeurHorsTout+kuAntiSlashZerO);
		for (nC=0;nC<nLargeurHorsTout;nC++)
			sChaine2[nC]=cChaineGarniR;
		sChaine2[nLargeurHorsTout]='\0';
	nTexteLg=nChaineLg(sTexte);
	nMarge=iSup(0,nLargeurHorsTout-nTexteLg)/2;
	nCarLim=iInf(nLargeurHorsTout,nTexteLg);
	for (nC=0;nC<nCarLim;nC++){
		//d4(nMarge+nC,nLargeurHorsTout-1,nC,nTexteLg-1);
		Assert2("sChaine22",bCroit(0,nMarge+nC,nLargeurHorsTout-1),bCroit(0,nC,nTexteLg-1));
		sChaine2[nMarge+nC]=sTexte[nC];
	}
	MallocGereR(sChaine2);
	return(sChaine2);
}//sChaine2

void ChaineGarnir(char cImprimable){
	//change le caractère de remplissage utilisé dans les routines sChaine0,sChaine1 et sChaine2.
	Assert1("ChaineGarnir",isprint(cImprimable) || cImprimable==' ');
	cChaineGarniR=cImprimable;
}//ChaineGarnir

int nChaineLg(char *sTexte){
	//strlen(sTexte) dans [0..kuIntegerMax];supprime le message d'erreur du compilateur C qui exige une conversion explicite unsigned int -> int
	unsigned int uiLg=strlen(sTexte);
	Assert1("nChaineLg1",uiLg<=kuIntegerMax);
	int nLg=(int) uiLg;
	Assert1("nChaineLg2",nLg>=0);
	return(nLg);
}//nChaineLg

char *sChainon(char *sChaine,int nDebutInclus,int nFinIncluse){
	//rend sChaine[nDebutInclus,nFinIncluse],ou une chaîne vide si non défini 
	int nC;
	char *sChainon;
	int nRequis;
	Assert2("sChainon",0<=nDebutInclus,0<=nFinIncluse);
	nRequis=iMax(0,nFinIncluse-nDebutInclus+1);
	sChainon=malloc(nRequis+kuAntiSlashZerO);
		for (nC=0;nC<nRequis;nC++)
			sChainon[nC]=sChaine[nDebutInclus+nC];
		sChainon[nRequis]='\0';
	MallocGereR(sChainon);
	return(sChainon);
}//sChainon
 
int bChaineEgale(char *sA,char *sB){
	int nC;
	int bEgale=nChaineLg(sA)==nChaineLg(sB);
	if (bEgale)
		for (nC=0;nC<nChaineLg(sA);nC++)
			bEgale=bEgale && sA[nC]==sB[nC];
	return(bEgale);
}//bChaineEgale

char *sChaineEtale(char *sChaine,int nEspaceEntreCaractere){
	//interpose nEspaceEntreCaractere blancs entre 2 caractères consécutifs de sChaine
	int nC,nD,uE;
	int nCarat;
	char *sEtale;
	int nRequis;
	//tt("sChaineEtale",sG(sChaine));
	Assert2("sChaineEtale 0",nEspaceEntreCaractere>=0,nCaractere(sChaine)==nChaineLg(sChaine));//chaque caractère est codé sur 1 code caractère (pas de "é")
	nCarat=nChaineLg(sChaine);
	nRequis=(nCarat>0)? nCarat+nEspaceEntreCaractere*(nCarat-1): nCarat;
	//d2(nCarat,nRequis);
	sEtale=malloc(nRequis+kuAntiSlashZerO);
		for (nD=0,nC=0;nC<nCarat;nC++)
			for (sEtale[nD++]=sChaine[nC],uE=1;nD+1<nRequis && uE<=nEspaceEntreCaractere;uE++)
				sEtale[nD++]=' ';
		sEtale[nRequis]='\0';
		//tee("nD==nRequis",nD,nRequis);
		Assert1("sChaineEtale 1",nD==nRequis);
	MallocGereR(sEtale);
	return(sEtale);
}//sChaineEtale
 
char *sChaineEtale1(char *sChaine){
	return(sChaineEtale(sChaine,1));
}//sChaineEtale1

char *sChaineEtale2(char *sChaine){
	return(sChaineEtale(sChaine,2));
}//sChaineEtale2

int mChainePos(char cQuoi,char *sDansQuoi){
	//rend le rang0 de cQuoi dans sDansQuoi, ou -1 si échec
	int nC;
	int mPos=-1;
	for (nC=0; nC<nChaineLg(sDansQuoi) && (mPos<0); nC++)
		if (cQuoi==sDansQuoi[nC])
			mPos=nC;
	return(mPos);
}//mChainePos

int bChiffre(char cCaractere){
	//cCaractere est un chiffre décimal
	int bChiffre=bDecit(cCaractere);
	return(bChiffre);
}//bChiffre

char *sChoix0(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide.
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? nChaineLg(sOption) : 0;
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
		sCopie[0]='\0';
		if (bOption)
			strcpy(sCopie,sOption);
	MallocGereR(sCopie);
	return(sCopie);
}//sChoix0

char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative){
	//rend sOption si bOptionSinonAlternative est vrai; sinon,rend sAlternative.
	int nRequis;
	Assert2("sCoix",sOption!=0,sAlternative!=0);
	nRequis = bOptionSinonAlternative? nChaineLg(sOption) : nChaineLg(sAlternative);
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
		if (bOptionSinonAlternative)
			strcpy(sCopie,sOption);
		else strcpy(sCopie,sAlternative);
	MallocGereR(sCopie);
	return(sCopie);
}//sChoix

void ChronoTesteR(){
	long zP,zQ;
	int nT;
	Appel0("ChronoTesteR");
		nT=nChrono(kV);
			for (zP=1;zP<kE4;zP++)
				zQ++;
		nT=nChrono(kF);
		printf("Durée exécution: %d.\n",nT);
	Appel1("ChronoTesteR");
}//ChronoTesteR

int nChrono(int bDemarrer){
	//pr chronométrer une exécution,l'encadrer avec nT=nChrono(kV) et nT=nChrono(kF); nT final donne la durée de l'exécution.
	static int bChronoDemarrer=kF;
	static long zChronoDemarrer;
	int kuClockDiviseur=100;//curieux
	FlipFlop("nChrono",bDemarrer,&bChronoDemarrer);
	int nChrono=0;
	if (bDemarrer)
		zChronoDemarrer=clock();
	else nChrono=(clock()-zChronoDemarrer)/kuClockDiviseur;//convertit en unité inconnue la durée au numérateur.
	return(nChrono);
}//nChrono

long zChrono(int bDemarrer){
	//pr chronométrer une exécution,l'encadrer avec zT=zChrono(kV) et zT=nChrono(kF); zT final donne la durée de l'exécution.
	static int bChronoDemarrer=kF;
	static long zChronoDemarrer;
	FlipFlop("zChrono",bDemarrer,&bChronoDemarrer);
	long zChrono=0;
	if (bDemarrer)
		zChronoDemarrer=clock();
	else zChrono=clock()-zChronoDemarrer;
	return(zChrono);
}//zChrono

long zCnp(int nN,int nP){
	//rend le nombre de combinaisons de nN éléments pris par paquets de nP éléments. 
	Assert1("zCnp",bCroit(0,nP,nN));
	long zCnp=zFact(nN)/(zFact(nP)*zFact(nN-nP));
	return(zCnp);
}//zCnp

void Confirmer(char *sMessage){
	char cCar;
	printf("%s Valider SVP (touche entrée)",sMessage);
	scanf("%c",&cCar);
	printf(" Merci d'avoir validé.\n");
}//Confirmer

int bConsonnE2(char *sTexte,int *pnCodeCaractereRg0){
	//sTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une consonne;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knConsonne1LiM 21
    #define knConsonne2LiM 04
	int nConsonne1[knConsonne1LiM]={64,65,66,67,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,89};//consonnes sans signe diacritique
	int nConsonne2[knConsonne2LiM]={79,89,111,121};//ççÑñ";
	int bConsonne2=0;
	Assert2("bConsonnE2a",sTexte!=0,pnCodeCaractereRg0!=0);
	Assert1("bConsonnE2b",bCroit(0,2,nChaineLg(sTexte)));
	Assert1("bConsonnE2c",bCroit(0,*pnCodeCaractereRg0,nChaineLg(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg0];
	bConsonne2=isalpha(cCode);//consonne ou voyelle sans signe diacritique (accents,cédille,tilde...)
	if (bConsonne2){//consonne?
		assert(0);//ie code actuellt non exécuté vu le contexte des appels à bConsonnE2()
		for (bConsonne2=0,nCar=0; nCar<knConsonne1LiM; nCar++)
			bConsonne2=bConsonne2||(cCode==-nConsonne1[nCar]);
		}
	else if (*pnCodeCaractereRg0<nChaineLg(sTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knConsonne2LiM; nCar++)
				bConsonne2=bConsonne2||(cCode==-nConsonne2[nCar]);
			if (bConsonne2)
				(*pnCodeCaractereRg0)++;
		}
	}
	return(bConsonne2);
}//bConsonnE2

char *sCouple(long yEntierA,long yEntierB){
	//rend la chaîne "(yEntierA,yEntierB)"	
	char *sCouple=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sCouple,sC5("(",sEnt(yEntierA),",",sEnt(yEntierB),")"));
	MallocGereR(sCouple);
	return(sCouple);
}//sCouple

char *sCrochet(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA,yEntierB]"	
	char *sCrochet=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sCrochet,sC5("[",sEnt(yEntierA),",",sEnt(yEntierB),"]"));
	MallocGereR(sCrochet);
	return(sCrochet);
}//sCrochet

char *sCrochet1(long yEntier){
	//rend "[yEntier]"	
	char *sCrochet1=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sCrochet1,sC3("[",sEnt(yEntier),"]"));
	MallocGereR(sCrochet1);
	return(sCrochet1);
}//sCrochet1

char *sCrochet2(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA,yEntierB]";comme sCrochet.	
	char *sCrochet2=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sCrochet2,sC5("[",sEnt(yEntierA),",",sEnt(yEntierB),"]"));
	MallocGereR(sCrochet2);
	return(sCrochet2);
}//sCrochet2

char *sCrochet3(long yEntierA,long yEntierB,long yEntierC){
	//rend la chaîne "[yEntierA,yEntierB,yEntierC]"	
	char *sCrochet3=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sCrochet3,sC7("[",sEnt(yEntierA),",",sEnt(yEntierB),",",sEnt(yEntierC),"]"));
	MallocGereR(sCrochet3);
	return(sCrochet3);
}//sCrochet3

void Croissant(double dMinInclus,double dDedans,double dMaxInclus){
	if (!bCroissant(dMinInclus,dDedans,dMaxInclus))
		printf("BUG ds bCroissant():%lf≤%lf≤%lf est FAUX\n",dMinInclus,dDedans,dMaxInclus);
	assert(bCroissant(dMinInclus,dDedans,dMaxInclus));
}//Croissant

int bCroissant(double dMinInclus,double dDedans,double dMaxInclus){
	int bCroissant=(dMinInclus<=dDedans) && (dDedans<=dMaxInclus);
	return(bCroissant);
}//bCroissant

int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	int bCroissantStrict=(dMinExclu<dDedans) && (dDedans<dMaxExclu);
	return(bCroissantStrict);
}//bCroissantStrict

void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	if (!bCroissantStrict(dMinExclu,dDedans,dMaxExclu))
		printf("BUG ds bCroissantStrict():%lf<%lf<%lf est FAUX\n",dMinExclu,dDedans,dMaxExclu);
	assert(bCroissantStrict(dMinExclu,dDedans,dMaxExclu));
}//CroissantStrict

int bCroit(long yMinInclus,long yDedans,long yMaxInclus){
	int bCroit=(yMinInclus<=yDedans) && (yDedans<=yMaxInclus);
	return(bCroit);
}//bCroit

int bCroit4(long yA,long yB,long yC,long yD){//rend yA≤yB≤yC<=yD
	int bCroit4=bCroit(yA,yB,yC) && (yC<=yD);
	return(bCroit4);
}//bCroit4

int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu){
	int bCroitStrict=(yMinExclu<yDedans) && (yDedans<yMaxExclu);
	return(bCroitStrict);
}//bCroit

int iCube(int iValeur){
	int iCube=iValeur*iValeur*iValeur;
	return(iCube);
}//iCube

int bDans2(int iQuoi,int iValeurA,int iValeurB){
	int bDans2=(iQuoi==iValeurA) || (iQuoi==iValeurB);
	return(bDans2);
}//bDans2

int bDans3(int iQuoi,int iValeurA,int iValeurB,int iValeurC){
	int bDans3=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC);
	return(bDans3);
}//bDans3

int bDans4(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD){
	int bDans4=(iQuoi==iValeurA) || (iQuoi==iValeurB) || (iQuoi==iValeurC) || (iQuoi==iValeurD);
	return(bDans4);
}//bDans4

char *sDateEnClair(int nQuantieme,int nMois,int nAnnee){
	//années 1900 à 2100
	int nJour;
	char *sEnClair;
	char *sSemaine="dimanche,lundi,mardi,mercredi,jeudi,vendredi,samedi";
	char *sMois="janvier,février,mars,avril,mai,juin,juillet,août,septembre,octobre,novembre,décembre";
	nJour=nJourSemaine(nQuantieme,nMois,nAnnee);
	sEnClair=sC8(sItem(sSemaine,nJour)," ",sEnt(nQuantieme),(nQuantieme==1)?"er":""," ",sItem(sMois,nMois)," ",sEnt(nAnnee));
	return(sEnClair);
}//sDateEnClair

int bDecit(char cCaractere){
	//cCaractere est un chiffre décimal;cache la fonction isdigit()
	int bDecit=isdigit(cCaractere);
	return(bDecit);
}//bDecit

char *sDire(int bAffirmation,char *sVerbePuisBlancPuisQqch){
	//rend sVerbePuisBlancPuisQqch,ou nié si bAffirmation fausse: sDire(0,"est vrai")="n'est pas vrai".
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	int mBlancPosition;
	char *sDire=malloc(kuNeLg+nChaineLg(sVerbePuisBlancPuisQqch)+kuPasLg+kuAntiSlashZerO);
		if (!bAffirmation){
			strcpy(sDire,sChoix(bVoyelle(sVerbePuisBlancPuisQqch,0),"n'","ne "));
			mBlancPosition=mChainePos(' ',sVerbePuisBlancPuisQqch);
			if (mBlancPosition>0){
				strcat(sDire,sChainon(sVerbePuisBlancPuisQqch,0,mBlancPosition));
				strcat(sDire, "pas ");
				strcat(sDire,sChainon(sVerbePuisBlancPuisQqch,mBlancPosition+1,100));
				Assert1("sNePas",nChaineLg(sDire)==kuNeLg+nChaineLg(sVerbePuisBlancPuisQqch)+kuPasLg);
			}
		}
		else strcpy(sDire,sVerbePuisBlancPuisQqch);
	MallocGereR(sDire);
	return(sDire);
}//sDire

int bDistinct3(long yA,long yB,long yC){
	int bDistinct3= yA!=yB && yA!=yC && yB!=yC;
	return(bDistinct3);
}//bDistinct3

int bDistinct4(long yA,long yB,long yC,long yD){
	int bDistinct4= yA!=yB && yA!=yC && yA!=yD;
	bDistinct4=bDistinct4 && yB!=yC && yB!=yD;
	bDistinct4=bDistinct4 && yC!=yD;
	return(bDistinct4);
}//bDistinct4

q qDiv(q qA,q qB){
	//division de deux rationnels:qA/qB
	q qInverse;
	q qDiv;
	Assert3("qDiv",qA.den>0,qB.den>0,qB.num!=0);
	qInverse.den=qB.num;
	qInverse.num=qB.den;
	qDiv=qMul(qA,qInverse);
	return(qDiv);
}//qDiv

char *sDiv(int nNumerateur,int nDenominateur){
	//rend la division de nNumerateur/nDenominateur avec deux décimales.
	const int kuRequis=20;
	int uC;
	char *sDiv=malloc(kuRequis+kuAntiSlashZerO);
		sDiv[0]='\0';
		if (nDenominateur==0)
			if (nNumerateur==0)
				strcat(sDiv,"indéterminé");
			else strcat(sDiv,"infini");
		else sprintf(sDiv,"%.2f",nNumerateur/(nDenominateur*1.0));
		for (uC=1;uC<=nChaineLg(sDiv);uC++)
			if (sDiv[uC]=='.')
				sDiv[uC]=',';
	MallocGereR(sDiv);
	return(sDiv);
}//sDiv

char *sDomaine(long yEntierA,long yEntierB){
	//rend la chaîne "[yEntierA..yEntierB]"	
	char *sDomaine=malloc(1+kuEntierSizE+2+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sDomaine,sC5("[",sEnt(yEntierA),"..",sEnt(yEntierB),"]"));
	MallocGereR(sDomaine);
	return(sDomaine);
}//sDomaine

int bEgal3(long yA,long yB,long yC){
	int bEgal3=(yA==yB && yB==yC);
	return(bEgal3);
}//bEgal3

char *sE(int nEspace){
	//rend sup(0,nEspace) blancs consécutifs
	//Assert1("sE",nEspace>=0);
	char *sE=sFois(iSup(0,nEspace),' ');//sFois a appelé MallocGereR()
	return(sE);
}//sE

char *sEnt(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEnt=malloc(kuEntierSizE+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEnt,"%ld",yEntier);//yEntier tient forcément ds sEnt vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEnt);
	return(sEnt);
}//sEnt

char *sEnt3(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de chiffres décimaux groupée par paquets de 3 décits et cadre à droite.
	char *sEnt3=sChaine0(sPar3(yEntier),nCaractere);
	return(sEnt3);
}//sEnt3

char *sEntier(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de nCaractere chiffres décimaux,quitte à ajouter des blancs à gauche et à tronquer si trop de chiffres.
	Assert1("sEntier",bCroit(0,nCaractere,kuEntierSizE));
	int nC;
	char *sEntier=malloc(kuEntierSizE+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier,"%23ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
		//cadrer à gauche sur nCaractere caractères.
			int nOffset=kuEntierSizE-nCaractere;
			for (nC=0;nC<nCaractere;nC++)
				sEntier[nC]=sEntier[nC+nOffset];
			sEntier[nCaractere]='\0';
	MallocGereR(sEntier);
	return(sEntier);
}//sEntier

char *sEntier0(long yEntier,int nCaractere){
	//convertit yEntier en chaîne de nCaractere chiffres décimaux exactement,quitte à ajouter des zéros à gauche et à tronquer si trop de chiffres.
	Assert1("sEntier0",bCroit(0,nCaractere,kuEntierSizE));
	int nC;
	char *sEntier0=sEntier(yEntier,nCaractere);//rend une suite de décits précédés de blancs et d'un signe "-" éventuels
	for (nC=0;nC<nCaractere;nC++)
		if (!isdigit(sEntier0[nC]))
			sEntier0[nC]='0';//remplace les blancs mais aussi le signe "-" éventuel.
	if (yEntier<0)
		sEntier0[0]='-';
	return(sEntier0);
}//sEntier0

char *sEntier1(long yEntier,int nCaractere){
	//convertit yEntier en chaîne sPar3 centrée de nCaractere chiffres décimaux exactement.
	Assert1("sEntier1",bCroit(0,nCaractere,kuEntierSizE));
	int nC,nMarge;
	char *sEnt3=sPar3(yEntier);
	char *sEntier1;
	//d(nCaractere);tt("sEnt3",sEnt3);
	nMarge=(nCaractere-nChaineLg(sEnt3))/2;
	//d(nMarge);
	sEntier1=sE(nCaractere);//d
	for (nC=0;nC<nChaineLg(sEnt3);nC++)
		sEntier1[nMarge+nC]=sEnt3[nC];
	return(sEntier1);
}//sEntier1

char *sEntier2(long yEntier){
	//convertit yEntier en chaîne de 2 chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier2=malloc(kuEntierSizE+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier2,"%2ld",yEntier);//yEntier tient forcément ds sEntier2 vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEntier2);
	return(sEntier2);
}//sEntier2

char *sEntier3(long yEntier){
	//convertit yEntier en chaîne de 3 chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier3=malloc(kuEntierSizE+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEntier3,"%2ld",yEntier);//yEntier tient forcément ds sEntier3 vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEntier3);
	return(sEntier3);
}//sEntier3

char *sEntierAvecSigne(long yEntier){
	//// "+5" ou "-5" ou " 0"
	char *sEnt=malloc(kuEntierSizE+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
		sprintf(sEnt,"%+ld",yEntier);//yEntier tient forcément ds sEnt vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	MallocGereR(sEnt);
	return(sEnt);
}//sEntierAvecSigne

void EntierDepiler(int *piA){
	Assert1("EntierDepiler",ipEntierPilE>0);
	//d(ipEntierPilE-1);
	*piA=iEntierPilE[--ipEntierPilE];
}//EntierDepiler

void EntierDepiler2(int *piA,int *piB){
	EntierDepiler(piA);EntierDepiler(piB);
}//EntierDepiler2

void EntierDepiler3(int *piA,int *piB,int *piC){
	EntierDepiler2(piA,piB);EntierDepiler(piC);
}//EntierDepiler3

void EntierDepiler4(int *piA,int *piB,int *piC,int *piD){
	EntierDepiler2(piA,piB);EntierDepiler2(piC,piD);
}//EntierDepiler4

void EntierDepilerTout(){
	//vide (dc initialise) la pile courante
	ipEntierPilE=0;
}//EntierDepilerTout

void EntierEchanger(int *piA,int *piB){
	int iC;
	Assert2("EntierEchanger",piA!=0,piB!=0);
	iC=*piA;
	*piA=*piB;
	*piB=iC;
}//EntierEchanger

void EntierEmpiler(int iA){
	Assert1("EntierEmpiler",ipEntierPilE<kuPileMaX);
	//d(ipEntierPilE);
	iEntierPilE[ipEntierPilE++]=iA;
}//EntierEmpiler

void EntierEmpiler2(int iA,int iB){
	EntierEmpiler(iA);EntierEmpiler(iB);
}//EntierEmpiler2

void EntierEmpiler3(int iA,int iB,int iC){
	EntierEmpiler2(iA,iB);EntierEmpiler(iC);
}//EntierEmpiler3

void EntierEmpiler4(int iA,int iB,int iC,int iD){
	EntierEmpiler2(iA,iB);EntierEmpiler2(iC,iD);
}//EntierEmpiler4

int nEntierEnTout(){
	return(ipEntierPilE);
}//nEntierEnTout

void EntyerEchanger(long *pyA,long *pyB){
	long yC;
	Assert2("EntierEchanger",pyA!=0,pyB!=0);
	yC=*pyA;
	*pyA=*pyB;
	*pyB=yC;
}//EntyerEchanger

char *sEst(int bAssertion){
	//rend "est" tel quel,ou négativé avec "n'"..."pas" si bAssertion est faux 
	#define kuEstLg 3//"est"
	#define kuNestPasLg 4//"n'est pas"
	char *sEst=malloc( kuAntiSlashZerO + (bAssertion)? kuEstLg : kuNestPasLg);
		sEst[0]='\0';
		if (bAssertion)
			strcat(sEst,"est");
		else strcpy(sEst,"n'est pas");
	MallocGereR(sEst);
	return(sEst);
}//sEst

char *sEuro0(float fReel,int nCaractereEnTout){
	//convertit fReel en prix cadré à droite sur nCaractereEnTout caractères: sEuro0(0.5,6) rend "  0€50".
	int mPointPos;
	char *sEuro0=sReel0(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro0);
		Assert1("sEuro0",mPointPos>0);
		sEuro0=sC3(sChainon(sEuro0,0,mPointPos-1),"€",sChainon(sEuro0,mPointPos+1,nChaineLg(sEuro0)-1));
		//printf("sEuro0 cadré à droite:%s.\n",sG(sEuro0));
	MallocGereR(sEuro0);
	return(sEuro0);
}//sEuro0

char *sEuro1(float fReel,int nCaractereEnTout){
	//convertit fReel en prix cadré à gauche sur nCaractereEnTout caractères: sEuro1(0.5,6) rend "0€50  ".
	int mPointPos;
	char *sEuro1=sReel1(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro1);
		Assert1("sEuro1",mPointPos>0);
		sEuro1=sC3(sChainon(sEuro1,0,mPointPos-1),"€",sChainon(sEuro1,mPointPos+1,nChaineLg(sEuro1)-1));
		//printf("sEuro1 cadré à gauche:%s.\n",sG(sEuro1));
	MallocGereR(sEuro1);
	return(sEuro1);
}//sEuro1

char *sEuro2(float fReel,int nCaractereEnTout){
	//convertit fReel en prix centré sur nCaractereEnTout caractères: sEuro2(0.5,6) rend " 0€50 ".
	int mPointPos;
	char *sEuro2=sReel2(fReel,nCaractereEnTout);
		mPointPos=mChainePos('.',sEuro2);
		Assert1("sEuro2",mPointPos>0);
		sEuro2=sC3(sChainon(sEuro2,0,mPointPos-1),"€",sChainon(sEuro2,mPointPos+1,nChaineLg(sEuro2)-1));
		//printf("sEuro2 centré:%s.\n",sG(sEuro2));
	MallocGereR(sEuro2);
	return(sEuro2);
}//sEuro2

long zFact(int nN){
	//rend la factorielle de l'entier positif ou nul nN
	int uTour;
	long zFact=1;
	Assert1("zFact",nN>=0);
	for (uTour=1;uTour<=nN;uTour++)
		zFact=zFact*uTour;
	if (nN==0)
		zFact=0;
	return(zFact);
}//zFact

int bFaux(int iEntier){
	//rend la constante entière kV (vrai) si iEntier==0 et la constante kF (faux) sinon
	int bFaux=(iEntier==0) ? 1 : 0;
	return(bFaux);
}//bFaux

//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont: R(true,…),R(false,…),R(true,…),R(false,…),etc.
//Le paramère pbAvant est censé être déclaré soit en variable de module soit en static dans R(), et être initialisé une fois pour toutes à false.
void FlipFlop(char* sContexte,int bApres,int *pbAvant){
	//si bApres≠*pbAvant,mémorise bApres dans pbAvant;sinon,déroute après avoir affiché sContexte.
	Assert1(sContexte,bApres!=*pbAvant);
	*pbAvant=bApres;
}//FlipFlop

long zFib(int nIndex){//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0
	#define kuFibMax 70 //plante au-delà
	long zFib=0;
	double rPhi,rPhiBarre,rFib;
	Assert1("zFib1",bCroit(0,nIndex,kuFibMax));
	rPhi=((long) 1.0+sqrtl( (long) 5.0))/ (long)2.0;
	rPhiBarre=((long) 1.0-sqrtl((long) 5.0))/(long) 2.0;
	rFib=(powl(rPhi,nIndex)-powl(rPhiBarre,nIndex))/sqrtl((long) 5.0);
	//printf("rFib(%d)=%lf....",nIndex,rFib);
	zFib=truncl(rFib);
	//printf("rFib(%d)=%s vs %s.\n",nIndex,sPar3(zFib),sPar3(kuIntegerMax));
	//printf("rFib(%d)=%s\n",nIndex,sPar3(zFib));
	Assert1("zFib2",zFib>=0);
	return(zFib);
}//zFib

char *sFois(int nFois,char cMotif){
	//juxtapose nFois cMotif
	int nF;
	char *sFwa;
	Assert2("sFois",nFois>=0,isprint(cMotif));//implique 1 code caractère par caractère,dc cMotif ne peut coder un "é" car il est occupe 2 codes caractères.
	sFwa=malloc(nFois+kuAntiSlashZerO);
		for (nF=0;nF<nFois;nF++)
			sFwa[nF]=cMotif;
		sFwa[nFois]='\0';
	MallocGereR(sFwa);
	Assert1("sFois",nChaineLg(sFwa)==nFois);
	return(sFwa);
}//sFois

int bFrontiere8(long zSizeOf){
	//vrai ssi zSizeOf est aligné sur une frontière de 8 octets
	Assert1("bFrontiere8",zSizeOf>=0);
	int bFrontiere8=(zSizeOf%8==0);
	return(bFrontiere8);
}//bFrontiere8

char *sG(char* sTexte){
	//nEspace blancs juxtaposés
	//char *sG=sC3('"',sEntreGuillemet,'"');
	char cGuillemet[2];
	char *sG=malloc(1+nChaineLg(sTexte)+1);
		cGuillemet[0]='"';
		cGuillemet[1]='\0';
		sG[0]='\0';
		strcat(sG,cGuillemet);
		strcat(sG,sTexte);
		strcat(sG,cGuillemet);
	MallocGereR(sG);
	return(sG);
}//sG

int nHasard(int uBorneLim){
	//rend un nombre pseudo-aléatoire ds [0..uBorneLim[, donc borne supérieure exclue.
	int nHasard;
	Assert1("nHasard1",bCroit(1,uBorneLim,kuIntegerMax-1));
	nHasard=rand()%uBorneLim;
	Assert1("nHasard2",bCroit(0,nHasard,uBorneLim-1));
	return(nHasard);
}//nHasard

int uHasard(int uBorneMax){
	//rend un nombre pseudo-aléatoire ds [1..nBorneMax], donc borne supérieure incluse.
	int uHasard;
	Assert1("uHasard1",bCroit(1,uBorneMax,kuIntegerMax));
	uHasard=1+rand()%uBorneMax;
	Assert1("uHasard2",bCroit(1,uHasard,uBorneMax));
	return(uHasard);
}//uHasard

void HasardInit(int iGerme){
	//si iGerme non nul,réinitialise la suite de nombres pseudo-aléatoires en fonction de iGerme;si iGerme est nul,ne fait rien.
	Assert1("HasardInit",iGerme>=0);
	if (iGerme>0) srand(iGerme);
	else if (iGerme<0)
		srand(time(NULL));
}//HasardInit

int bImpair(int iEntier){
	int bImpair=bVrai(iEntier%2);
	assert(bBool(bImpair));
	return (bImpair);
}//bImpair

int bInteger(long yEntier){
	int bInteger=bCroit(kiIntegerMin,yEntier,kuIntegerMax);
	return (bInteger);
}//bInteger

double rInf(double dA,double dB){
	//rend inf(dA,dB)
	double rInf=(dA<dB)?dA:dB;
	return(rInf);
}//rInf

int iInf(int iA,int iB){
	//rend inf(iA,iB);identique à iMin(iA,iB).
	int iInf=(iA>iB)?iB:iA;
	return(iInf);
}//iInf

int iInf3(int iA,int iB,int iC){
	int iInf3=iInf(iA,iInf(iB,iC));
	return(iInf3);
}//iInf3

long yInf(long yA,long yB){
	//rend inf(yA,yB);identique à yMin(yA,yB)
	long yInf=(yA>yB)?yB:yA;
	return(yInf);
}//yInf

long yInf3(long yA,long yB,long yC){
	long yInf3=yInf(yA,yInf(yB,yC));
	return(yInf3);
}//yInf3

q qInv(q qA){
	//inverse du rationnel
	q qInv;
	Assert2("qInv",qA.num>0,qA.den>0);
	qInv.num=qA.den;
	qInv.den=qA.num;
	return(qInv);
}//qInv

int nItem(char *sItemVirguleItemVirguleItem){
	//rend le nb total d'items (éventuellement vides);nItem(alpha,b,c)=3;nItem(a)=1;nItem(a,,c)=3.nItem(,a,)=1.nItem(,a)=1.nItem(a,)=1.nItem()=1;
	int uC,nClim,uItem=1;
	nClim=nChaineLg(sItemVirguleItemVirguleItem);//ie les virgules éventuelles placées aux extrémités de la chaîne sont ignorées
	//t(sG(sItemVirguleItemVirguleItem));
	if (nClim>0)
		for (uC=1;uC<nClim-1;uC++)
			if (sItemVirguleItemVirguleItem[uC]==',')
				uItem++;
	//printf("nItem(%s)=%d.\n",sG(sItemVirguleItemVirguleItem),uItem);
	Assert1("nItem",uItem>0);
	return(uItem);
}//nItem

char *sItem(char *sItemVirguleItemVirguleItem,int uItemRang){
	//rend l'item de rang uItemRang ou une chaîne vide si cet item n'existe pas. sItem("a,b,c",1)="a". sItem("a,b,c",5)="". sItem("a,,c",2)="".
	int nC,nClim,nDebutInclus=0,nFinExclue=0;
	int nItemEnTout,nVirguleRang,uRequis;
	char *sItem;
	//printf("sItem(%s,%d):\n",sG(sItemVirguleItemVirguleItem),uItemRang);
	nItemEnTout=nItem(sItemVirguleItemVirguleItem);
	if (bCroit(1,uItemRang,nItemEnTout))
		for (nClim=nChaineLg(sItemVirguleItemVirguleItem),nDebutInclus=0,nFinExclue=nClim,nVirguleRang=0,nC=1;nC<nClim;nC++)
			if (sItemVirguleItemVirguleItem[nC]==','){
				nVirguleRang++;
				if (nVirguleRang==uItemRang-1)
					nDebutInclus=nC+1;
				if (nVirguleRang==uItemRang+0)
					nFinExclue=nC;
			};
	//tee("nDebutInclus,nFinExclue",nDebutInclus,nFinExclue);
	uRequis=nFinExclue-nDebutInclus;
	sItem=malloc(uRequis+kuAntiSlashZerO);
		for (nC=0;nC<nFinExclue-nDebutInclus;nC++)
			sItem[nC]=sItemVirguleItemVirguleItem[nDebutInclus+nC];
		sItem[nFinExclue-nDebutInclus]='\0';
	MallocGereR(sItem);
	return(sItem);
}//sItem

char *sItem0(char *sItemVirguleItemVirguleItem,int nItemRang){
	//rend l'item de rang nItemRang ou une chaîne vide si cet item n'existe pas. sItem("a,b,c",0)="a".
	char *sItem0=sItem(sItemVirguleItemVirguleItem,nItemRang+1);
	return(sItem0);
}//sItem0

char *sItem4(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4){
	char *sItem;
	switch (uItem) {
		case 1:	sItem=sItem1; break;
		case 2:	sItem=sItem2; break;
		case 3:	sItem=sItem3; break;
		case 4:	sItem=sItem4; break;
		default: sItem="";
	}
	return(sItem);
}//sItem4

char *sItem8(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6,char* sItem7,char* sItem8){
	char *sItem;
	switch (uItem) {
		case 1:	sItem=sItem1; break;
		case 2:	sItem=sItem2; break;
		case 3:	sItem=sItem3; break;
		case 4:	sItem=sItem4; break;
		case 5:	sItem=sItem5; break;
		case 6:	sItem=sItem6; break;
		case 7:	sItem=sItem7; break;
		case 8:	sItem=sItem8; break;
		default: sItem="";
	}
	return(sItem);
}//sItem8

int nItemRang(char *sQuoi,char *sItemVirguleItemVirguleItem){
	//rend le rang1 de sQuoi dans sItemVirguleItemVirguleItem: nItemRang("deux","un,deux,trois")=2. Rend 0 si sQuoi n'est pas un item.
	int nRang,uItem;
	int nPareil,nQuoiLg;
	int nQ,nC,nClim,nVirguleRg;
	//tt(sG(sQuoi),sG(sItemVirguleItemVirguleItem));
	nQuoiLg=nChaineLg(sQuoi);
	nClim=nChaineLg(sItemVirguleItemVirguleItem);
	if (nQuoiLg>0){
		for (nRang=0,uItem=1,nQ=0,nPareil=0,nC=0;nC<nClim && nRang==0;nC++){
			if (sItemVirguleItemVirguleItem[nC]==','){
				if (nC>0){
					if (nRang==0 && nPareil==nQuoiLg)
						nRang=uItem;
					uItem++;
					//teee("nC,nPareil,uItem",nC,nPareil,uItem);
					nPareil=0;nQ=0;
				}
			} else if (sQuoi[nQ++]==sItemVirguleItemVirguleItem[nC])
				nPareil++;
		}
		if (nRang==0 && nPareil==nQuoiLg)
			nRang=uItem;
	} else {//rang de la première chaine vide éventuelle
		for (nRang=0,uItem=1,nVirguleRg=0,nC=1;nC<nClim && nRang==0;nC++)
			if (sItemVirguleItemVirguleItem[nC]==','){
				if (nRang==0 && nVirguleRg==nC-1)
					nRang=uItem;
				//teee("nC,nPareil,uItem",nC,nPareil,uItem);
				nVirguleRg=nC;
				uItem++;
			}
		//te("nRang",nRang);
		if (nRang==0 && nClim>1 && sItemVirguleItemVirguleItem[0]==',' && sItemVirguleItemVirguleItem[1]==',')
			nRang=1;
		if (nRang==0 && nClim>1 && sItemVirguleItemVirguleItem[nClim-2]==',' && sItemVirguleItemVirguleItem[nClim-1]==',')
			nRang=uItem;
	}
	Assert1("nRang",nRang>=0);
	return(nRang);
}//nItemRang

int nJourSemaine(int nQuantieme,int nMois,int nAnnee){
	//années 1900 à 2100 incluses
	int bBissextile,nCentime,bDate,nDecalAn,nJourSemaine;
	int nDecalCumul[1+12]={-1,     0, 3, 3,     6, 1, 4,     6, 2, 5,     0, 3, 5};
	int nJourEnTout[1+12]={-1,    31,28,31,    30,31,30,    31,31,30,    31,30,31};
	//teee("********nQuantieme,nMois,nAnnee",nQuantieme,nMois,nAnnee);
	Assert3("nJourSemaine0",bCroit(1,nQuantieme,31),bCroit(1,nMois,12),bCroit(1900,nAnnee,2100));
	nCentime=nAnnee%100;
	bBissextile=(nCentime!=0)? (nCentime%4==0) : (nAnnee/100==20);
	//tee("nAnnee,bBissextile",nAnnee,bBissextile);
	bDate=nQuantieme<=nJourEnTout[nMois] || (bBissextile && nQuantieme==29 && nMois==2);
	Assert1("nJourSemaine1",bDate);
	nDecalAn=(nAnnee-1900)+(nAnnee-1900)/4;
	//tee("nDecalAn,nDecalCumul[nMois]",nDecalAn,nDecalCumul[nMois]);
	nJourSemaine=nQuantieme+nDecalCumul[nMois]+nDecalAn-(bBissextile && nMois<=2);
	nJourSemaine=1+nJourSemaine%7;
	Assert1("nJourSemaine2",bCroit(1,nJourSemaine,7));
	return(nJourSemaine);
}//nJourSemaine

char *sK(ri rComplexe){
	//convertit le nombre complexe à coefficients entiers rComplexe en chaîne de caractères: sK((2,1)) rend "2+i".
	#define kuRequis 31
	char *sK=malloc(kuRequis+kuAntiSlashZerO);
		if (abs(rComplexe.r)!=0){
			if (abs(rComplexe.i)>1)
				sprintf(sK,"%d%c%di",rComplexe.r,(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
			else if (abs(rComplexe.i)==1)
				sprintf(sK,"%d%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
			else sprintf(sK,"%d",rComplexe.r);
		}else if (abs(rComplexe.i)!=0){
			if (abs(rComplexe.i)>1)
				sprintf(sK,"%c%di",(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
			else sprintf(sK,"%si",(rComplexe.i!=0)? ((rComplexe.i>0)?"+":"-") :"");
		} else sprintf(sK,"0");
	MallocGereR(sK);
	return(sK);
}//sK

char *sK3(ri rComplexe){
	//idem sK en groupant les décits par paquets de 3.
	char *sK;
		if (abs(rComplexe.r)!=0){
			if (abs(rComplexe.i)>1)
				//sprintf(sK,"%d%c%di",rComplexe.r,(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
				sK=sC3(sPar3(rComplexe.r),(rComplexe.i>0)?"+":"-",sPar3(abs(rComplexe.i)));
			else if (abs(rComplexe.i)==1)
				//sprintf(sK,"%d%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
				sK=sC3(sPar3(rComplexe.r),(rComplexe.i>0)?"+":"-","i");
			else //sprintf(sK,"%d",rComplexe.r);
				sK=sPar3(rComplexe.r);
		}else if (abs(rComplexe.i)!=0){
			if (abs(rComplexe.i)>1)
				//sprintf(sK,"%c%di",(rComplexe.i>0)?'+':'-',abs(rComplexe.i));
				sK=sC3((rComplexe.i>0)?"+":"-",sPar3(abs(rComplexe.i)),"i");
			else //sprintf(sK,"%d%ci",rComplexe.r,(rComplexe.i>0)?'+':'-');
				sK=sC2((rComplexe.i>0)?"k+":"k-","i");
		} else //sprintf(sK,"0");
			sK=sC('0');
	return(sK);
}//sK3

int bLettre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (accent,cédille,tilde...);cache la fonction isalpha()
	int bLettre=isalpha(cCaractere);
	return(bLettre);
}//bLettre

char cLettre(int nLettre){
	//donne le caractère de rang nLettre: "A" pour 1,"B" pour 2, etc, "a" pour 27, etc.
	char cAlphabet[1+52+1]="@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	//te("cLettre:::",nLettre);
	Assert1("cLettre",bCroit(1,nLettre,52));
	char cLettre=cAlphabet[nLettre];
	//printf("cLettre VAUT %c\n",cLettre);
	return(cLettre);
}//cLettre

int nLettre(char cCaractere){
	//donne le rang1 de cCaractere: 1 pour "A",2 pour "B", etc, 27 pour "a", etc.
	//printf("Routine nLettre: la donnée est le caractère \"%c\".\n",cCaractere);
	int nLettre=0;
	if ( bCroit('A',cCaractere,'Z') )
		nLettre=cCaractere-'A'+1;
	else if ( bCroit('a',cCaractere,'z') )
		nLettre=26+cCaractere-'a'+1;
	Assert1("nLettre",nLettre>0);
	return(nLettre);
}//nLettre

int bLettrE2(char *sTexte,int *pnCodeCaractereRg0){
	//sTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une consonne;si vrai et 2 codes, passe au code suivant
	char cCode;
	int bLettrE2=0;
	assert(sTexte!=0);
	Assert1("bLettrE2",bCroit(0,*pnCodeCaractereRg0,nChaineLg(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg0];
	bLettrE2=isalpha(cCode);//vrai si consonnes ou voyelles sans signe diacritique (accent,cédille,tilde...)
	if ( !bLettrE2 && (*pnCodeCaractereRg0<nChaineLg(sTexte)) ) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		bLettrE2=bVoyellE2(sTexte,pnCodeCaractereRg0) || bConsonnE2(sTexte,pnCodeCaractereRg0);
	}
	return(bLettrE2);
}//bLettrE2

void Ligne(){
	printf("\n");
}//Ligne

int bLigne(){
	Ligne();
	return(1);
}//bLigne

int bLigne1(char *sLigneFin){
	printf("%s.\n",sLigneFin);
	return(1);
}//bLigne1

double rLog(double rN){
	//logarithme népérien
	double rLog=log(rN);
	return(rLog);
}//rLog

int nLog10(long yValeur){
	//nombre de bits requis pour coder yValeur en base 10.
	int nLog10,nV;
	nV=abs(yValeur);
	nLog10=(yValeur<=0);
	while (nV>0){
		nV=nV/10;
		nLog10++;
	}
	return(nLog10);
}//nLog10

int nLog2(long yValeur){
	//nombre de bits requis pour coder yValeur en complément à 2.
	int nLog2,nV;
	nV=abs(yValeur);
	nLog2=(yValeur<=0);
	while (nV>0){
		nV=nV/2;
		nLog2++;
	}
	return(nLog2);
}//nLog2

double rLog2(double rN){
	//logarithme en base 2
	double rLog2=log2(rN);
	return(rLog2);
}//rLog2

int bMajuscule(char cCaractere){
	//cCaractere est une lettre majuscule sans signe diacritique (accent,cédille,tilde...);cache la fonction isupper()
	int bMajuscule=isupper(cCaractere);
	return(bMajuscule);
}//bMajuscule

char *sMajuscule(char *sCaractere){
	//rend la majuscule qui correspond à sCaractere 
	int uCar,nPlace;
	char *sMajuscule;
	int nItemEnTout=nItem(sAlphabetMinusculE);
	for (nPlace=0,uCar=1;uCar<=nItemEnTout && nPlace==0;uCar++)
		if (bChaineEgale(sCaractere,sItem(sAlphabetMinusculE,uCar)))
			nPlace=uCar;
	sMajuscule=(nPlace==0)? sCaractere : sItem(sAlphabetMajusculE,nPlace);
	return(sMajuscule);
}//sMajuscule

void MallocGereR(char *sMalloc){
	//prend note de l'allocation de sMalloc sur l'espace courant et libère le demi-espace le plus ancien si cette allocation sature l'espace courant
	const int kbConfirmer=kF;
	int nAlloc;
	char *sAlloc;
	if (zuMallocGereR==0){
		yMallocGereR0[nMallocGereR0++]=(long) sMalloc;
		if (nMallocGereR0>=kuMallocGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (0 vers 1)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuMallocGererMaX; nAlloc++) {
				sAlloc=(char *) yMallocGereR1[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yMallocGereR1[nAlloc]=0;
			}
			zuMallocGereR=1-zuMallocGereR;//change de demi-espace
			nMallocGereR1=0;//premier index valide sur le futur demi-espace 
			if (kbConfirmer)
				printf("Changement de demi-espace 0 terminé.\n");
		}
	} else {
		yMallocGereR1[nMallocGereR1++]=(long) sMalloc;
		if (nMallocGereR1>=kuMallocGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (1 vers 0)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuMallocGererMaX; nAlloc++) {
				sAlloc=(char *) yMallocGereR0[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yMallocGereR0[nAlloc]=0;
			}
			zuMallocGereR=1-zuMallocGereR;//change de demi-espace
			nMallocGereR0=0;//premier index valide sur le futur demi-espace
			if (kbConfirmer)
				printf("Changement de demi-espace 1 terminé.\n");
		}
	}
}//MallocGereR

int iMax(int iA,int iB){
	//rend max(iA,iB);identique à iSup(iA,iB).
	int iMax=(iA<iB)?iB:iA;
	return(iMax);
}//iMax

double rMax(double dA,double dB){
	//rend sup(dA,dB)
	double rMax=(dA>dB)?dA:dB;
	return(rMax);
}//rMax

long yMax(long yA,long yB){
	//rend max(yA,yB);identique à ySup(yA,yB)
	long yMax=(yA>yB)?yA:yB;
	return(yMax);
}//yMax

void MemIntRaz(int piMemOrigine[],int nItemEnTout){
	Assert2("MemIntRaz",piMemOrigine!=0,nItemEnTout>=0);
	MemIntValuer(piMemOrigine,nItemEnTout,0);
}//MemIntRaz

void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur){
	int nItem;
	Assert2("MemIntValuer",piMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		piMemOrigine[nItem]=iValeur;
	}
}//MemIntValuer

void MemLongRaz(int pyMemOrigine[],int nItemEnTout){
	Assert2("MemLongRaz",pyMemOrigine!=0,nItemEnTout>=0);
	MemLongValuer(pyMemOrigine,nItemEnTout,0);
}//MemLongRaz

void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur){
	int nItem;
	Assert2("MemLongValuer",pyMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		pyMemOrigine[nItem]=yValeur;
	}
}//MemLongValuer

int iMin(int iA,int iB){
	//rend min(iA,iB);identique à iInf(iA,iB).
	int iMin=(iA>iB)?iB:iA;
	return(iMin);
}//iMin

double rMin(double dA,double dB){
	//rend inf(dA,dB)
	double rMin=(dA<dB)?dA:dB;
	return(rMin);
}//rMin

long yMin(long yA,long yB){
	//rend min(yA,yB);identique à yInf(yA,yB)
	long yMin=(yA>yB)?yB:yA;
	return(yMin);
}//yMin

int bMinuscule(char cCaractere){
	//cCaractere est une lettre minuscule signe diacritique (accent,cédille,tilde...);cache la fonction islower()
	int bMinuscule=islower(cCaractere);
	return(bMinuscule);
}//bMinuscule

char *sMinuscule(char *sCaractere){
	//rend la minuscule qui correspond à sCaractere 
	int uCar,nPlace;
	char *sMinuscule;
	int nItemEnTout=nItem(sAlphabetMajusculE);
	for (nPlace=0,uCar=1;uCar<=nItemEnTout && nPlace==0;uCar++)
		if (bChaineEgale(sCaractere,sItem(sAlphabetMajusculE,uCar)))
			nPlace=uCar;
	sMinuscule=(nPlace==0)? sCaractere : sItem(sAlphabetMinusculE,nPlace);
	return(sMinuscule);
}//sMinuscule

int nModulo(int iDividende,int uDiviseur){
	//rend le modulo standard tel que 0≤modulo<uDiviseur 
	int uDividende,nModulo;
	Assert1("nModulo",uDiviseur>0);
	uDividende=abs(iDividende);
	nModulo=uDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0)//ou 1 pr que li+1 soit exécutée 
		teee("nModulo",uDividende,uDiviseur,nModulo);
	Assert1("nModulo",bCroit(0,nModulo,uDiviseur-1));
	return(nModulo);
}//nModulo

int uModulo1(int nDividende,int uDiviseur){
	//rend le modulo standard à ceci près que le résultat 0 éventuel est remplacé par nDiviseur: uModulo1(12,4)=4 
	int nModulo;
	Assert2("uModulo1a",nDividende>=0,uDiviseur>0);
	nModulo=nDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0)//ou 1 pr que li+1 soit exécutée 
		teee("uModulo1",nDividende,uDiviseur,nModulo);
	Assert1("uModulo1b",bCroit(1,nModulo,uDiviseur));
	return(nModulo);
}//uModulo1

q qMul(q qA,q qB){
	//produit de deux rationnels
	q qMul;
	int xPgcd;
	Assert2("qMul",qA.den>0,qB.den>0);
	qMul.num=qA.num*qB.num;
	qMul.den=qA.den*qB.den;
	xPgcd=zPgcd(abs(qMul.num),abs(qMul.den));
	qMul.num/=xPgcd;
	qMul.den/=xPgcd;
	return(qMul);
}//qMul

ri riMul(ri riA,ri riB){
	//produit de deux nombres complexes à composantes entières
	ri riMul;
	riMul.r=riA.r*riB.r-riA.i*riB.i;
	riMul.i=riA.r*riB.i+riA.i*riB.r;
	return(riMul);
}//riMul

int bNul(double dNombre){
	//vrai ssi la donnée est assimilable à 0.0
	int bNul;
	double dPositif;
	dPositif=dNombre;
	if (dPositif<0.0)
		dPositif=-dPositif;
	if (dPositif<=kdEpsilon)
		bNul=kV;
	else bNul=kF;
	return(bNul);
}//bNul

int briNul(ri riA){
	int bNul=riA.r==0 && riA.i==0;
	return(bNul);
}//briNul

q qOpp(q qA){
	//opposé d'un rationnel
	q qOpp;
	qOpp.num=-qA.num;
	qOpp.den=qA.den;
	return(qOpp);
}//qOpp

ri riOpp(ri riA){
	//opposé d'un complexe
	ri riOpp;
	riOpp.r=-riA.r;
	riOpp.i=-riA.i;
	return(riOpp);
}//riOpp

char *sOui(int bOui){
	//rend "oui" ou "non" selon bOui 
	#define kuOuiOuNonLg 3
	char *sOui=malloc( kuAntiSlashZerO + kuOuiOuNonLg);
		sOui[0]='\0';
		strcat(sOui,(bOui)? "OUI": "non");
	MallocGereR(sOui);
	return(sOui);
}//sOui

void OutilAMORCER(){
	//amorce le présent module une fois pour toutes
	//NB ne toucher ni à nAppeL ni à bAppeL[] utilisés avant l'amorçage;
	assert(nAppeL==1);//dédié Appel0() et Appel1();vérifie que Appel0() a bien été exécuté 1 fois ——Appel0("") est censé débuter le main().
	assert(kuEntierSizE==23);//touche pas
	assert(strlen("à")>1);//ATTENTION: strlen("à")==2 et strlen("a")==1. strlen() ne compte plus des caractères mais des codes caractères,d'où le 2.
	PremierAmorceR();
	cChaineGarniR=' ';
	bOutilAmorceR=kV;
}//OutilAMORCER

void OutilINITIALISER(){
	//relance le présent module
	Assert1("OutilINITIALISER",bOutilAmorceR);
}//OutilINITIALISER

void OutilTESTER(int iTest){
	q qA,qB,qC,qD;
	//char *sQuoi;
	int nIndex=0;
	long yIndex;
	int uFois,iItem;
	int nT[1+10];
	int iVecteur[6]={0,9,3,7,2,6};
	int nRang[6]={0,0,0,0,0,0};
	#define kuConsonneEnTout 44
	#define kuVoyelleEnTout 47
	Appel0(sC2("OutilTESTER,test n°",sEnt(iTest)));
		char *skConsonne="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
		char *skVoyelle="ÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		char *skLettre="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		switch (iTest) {
			case  1:	printf("Le graphe %s un circuit\n",sPas("contient",1)); break;
			case  2:	printf("Le graphe %s un circuit\n",sPas("contient",0)); break;
			case  3:	printf("Il %s circuit\n",sUn("y a",1)); break;
			case  4:	printf("Il %s boucle\n",sUne("y a",0)); break;
			case  5:	VecteurVoir("iVecteur AVANT le tri",&iVecteur[0],1,5);
						//VecteurTrier(&iVecteur[0],1,5);
						VecteurTrierVite(iVecteur,1,5);
						VecteurVoir("iVecteur APRES le tri",&iVecteur[0],1,5);
						break;
			case  6:	VecteurVoir("iVecteur AVANT le tri",&iVecteur[0],1,5);
						VecteurTrier2(&iVecteur[0],1,5,&nRang[0]);
						VecteurVoir("iVecteur APRES le tri",&iVecteur[0],1,5);
						VecteurVoir("nRang APRES le tri",&nRang[0],1,5);
						break;
			case  9:	printf("%s.\n",sDateEnClair( 1, 1,1900));
						printf("%s.\n",sDateEnClair( 1, 1,1907));
						printf("%s.\n",sDateEnClair( 1, 1,1963));
						printf("%s.\n",sDateEnClair( 1, 1,2000));
						printf("%s.\n",sDateEnClair(15, 2,2016));
						printf("%s.\n",sDateEnClair(15, 2,2017));
						printf("%s.\n",sDateEnClair( 8, 4,2017));
						printf("%s.\n",sDateEnClair( 9, 4,2017));
						printf("%s.\n",sDateEnClair(10, 4,2017));
						break;
			case 10:	printf("test des fonctions de concaténation:\n");
			case 11:	printf("11AVANT%sAPRES\n",sC1("a"));
			case 12:	printf("12AVANT%sAPRES\n",sC2("b","c"));
			case 13:	printf("13AVANT%sAPRES\n",sC2b("d","e"));
			case 14:	printf("14AVANT%sAPRES\n",sC2b("f",""));
			case 15:	printf("15AVANT%sAPRES\n",sC2b("","g"));
			case 16:	printf("16AVANT%sAPRES\n",sC2b("",""));
			case 17:	printf("17AVANT%sAPRES\n",sC2bp("",""));
			case 18:	printf("18AVANT%sAPRES\n",sC1p(sC2bp("h", "i")));
			case 19:	printf("19AVANT%sAPRES\n",sC7bp("1","2","3","4","5","6","7"));break;

			case 20:	printf("nb item:%d.\n",nItem("salut,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem("salut,,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem(",salut,,bonjour,bonsoir"));
						printf("nb item:%d.\n",nItem(",salut,,bonjour,bonsoir,"));
						printf("nb item:%d.\n",nItem(",,,"));
						printf("nb item:%d.\n",nItem(""));
						for (iItem=-1;iItem<=4;iItem++)
							printf("item n°%d:\"%s\".\n",iItem,sItem("salut,bonjour,bonsoir",iItem));
						for (iItem=1;iItem<=4;iItem++){
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",,bon,bonjour,bonsoir",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",,bon,bonjour,bonsoir"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonsoir,,hello",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonsoir,,hello"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir,,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),"bon,bonjour,bonsoir,,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,,"));
printf("nItemRang(\"%s\",\"%s\")=%d.\n",sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,",nItemRang(sItem("bon,bonjour,bonsoir",iItem),",bon,bonjour,bonsoir,"));
						}
printf("nItemRang1(\"%s\",\"%s\")=%d.\n","bonjour","bonjour",nItemRang("bonjour","bonjour"));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","","",nItemRang("",""));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","",",",nItemRang("",","));
printf("nItemRang2(\"%s\",\"%s\")=%d.\n","",",,",nItemRang("",",,"));
						break;
			case 21:	ChronoTesteR();break;
			case 22:	Voir("%5.2f %s %d %s.\n",3.14,"mètres,soit environ",3,"mètres");break;
			case 23:	t("12345678"),
						t(sReel0(3.14,8));
						t(sReel1(3.14,8));
						t(sReel2(3.14,8));
						t(sG("12345678")),
						t(sG(sEuro0(3.14,8)));
						t(sG(sEuro1(3.14,8)));
						t(sG(sEuro2(3.14,8)));
						break;
			case 25:	printf("%s\n",sG(sChainon("salut",1,5)));
						printf("%s\n",sG(sChainon("salut",2,4)));
						printf("%s\n",sG(sChainon("salut",2,2)));
						printf("%s\n",sG(sChainon("salut",4,2)));
						printf("%s\n",sG(sChainon("salut",0,8)));
						printf("%s\n",sG(sChainon("salut",0,0)));
						printf("%s\n",sG(sChainon("salut",4,4)));
						//printf("%s\n",sG(sChainon("salut",-4,-2)));//déclenche les assertions 
						break;
			case 30:	assert(nChaineLg("étagé")>6);break;//e aigu occupe 2 codes caractères,vu nChaineLg()
			case 40:	printf("%s.\n",sChaine0("Bonjour",5));
						printf("%s.\n",sChaine0("Bonjour",10));
						printf("%s.\n",sChaine0("Bonjour",7));
						printf("%s.\n",sChaine1("Bonjour",5));
						printf("%s.\n",sChaine1("Bonjour",10));
						printf("%s.\n",sChaine1("Bonjour",7));
						printf("%s.\n",sChaine2("Bonjour",5));
						printf("%s.\n",sChaine2("Bonjour",10));
						printf("%s.\n",sChaine2("Bonjour",7));
						break;
			case 50:	assert(nCaractere(skVoyelle)==kuVoyelleEnTout);break;
			case 51:	assert(nCaractere(skConsonne)==kuConsonneEnTout);break;
			case 52:	assert(nCaractere(skLettre)==kuVoyelleEnTout+kuConsonneEnTout);break;
			case 54:	d(nCaractere("ABBE"));d(nCaractere("abbé"));d(nCaractere("bébé"));d(nCaractere("ébété"));
						d4(nChaineLg("ABBE"),nChaineLg("abbé"),nChaineLg("bébé"),nChaineLg("ébété"));
						break;
			case 55:	for (nIndex=0;nIndex<kuVoyelleEnTout;nIndex++)
							printf("test de bVoyellE2[%d] %d\n",nIndex,bVoyellE2("aeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã",&nIndex));break;
			case 60:	for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [0..3]: %d.\n",nHasard(3));
						for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [1..4]: %d.\n",uHasard(4));
						break;
			case 61:	zBof=zPgcd(60,32);
						zBof=zPgcd(170,153);
						zBof=zPpcm(60,32);
						zBof=zPpcm(170,153);
						break;
			case 62:	yIndex=-4;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-169;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-1234;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",-yIndex,sPar3(-yIndex));
						yIndex=kxLongintMax;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=kyLongintMin+1;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						break;
			case 65:	printf("Nombres premiers inférieurs à 100:");
						for (uFois=1;uFois<100;uFois++)
							if (bPremier(uFois))
								printf(" %d",uFois);
						printf(".\n");
						break;
			case 70:	Titrer("salut");
						Titrer("");
						Titrer("solo");
						break;
			case 80:	printf("Texte: %s.\n",sFois(4,'z'));
						break;
			case 90:	for (uFois=1;uFois<10;uFois++)
							nT[uFois]=5;
						MemIntRaz(nT,10);
						break;
			case 92:	qA.num=1;qA.den=2;qB.num=1;qB.den=3;qC.num=2;qC.den=1;
						tq("qA",qA);tq("qB",qB);tq("qC",qC);
						qD=qOpp(qA);tq("qD opp -A",qD);
						qD=qAdd(qA,qB);tq("qD A+B",qD);
						qD=qSub(qA,qB);tq("qD A-B",qD);
						qD=qAdd(qAdd(qA,qB),qSub(qA,qB));tq("qD (A+B)+(A-B)",qD);
						qD=qMul(qA,qB);tq("qD A*B",qD);
						qD=qDiv(qA,qB);tq("qD A/B",qD);
						qD=qDiv(qMul(qA,qB),qDiv(qA,qB));tq("qD (A*B)/(A/B)",qD);
						qD=qInv(qDiv(qMul(qA,qB),qDiv(qA,qB)));tq("qD (A/B)/(A*B)",qD);
						qD=qSub(qA,qA);tq("qD A-A",qD);
						break;
			case 95:	for (nIndex=0;nIndex<=50;nIndex++)
							printf("zFib(%d)=%ld\n",nIndex,zFib(nIndex));
						break;
			default:
				break;
		}
	Appel1(sC2("OutilTESTER,test n°",sEnt(iTest)));
}//OutilTESTER

int bPair(int iEntier){
	int bPair=bFaux(iEntier%2);
	assert(bBool(bPair));
	return (bPair);
}//bPair

char *sP(char *sEntreParenthese){
	//rend sEntreParenthese précédé de "(" et suivi de ")"
	assert(sEntreParenthese!=0);	
	char *sP=malloc(1+nChaineLg(sEntreParenthese)+1+kuAntiSlashZerO);
		strcpy(sP,sC3("(",sEntreParenthese,")"));
	MallocGereR(sP);
	return(sP);
}//sP

char *sPar3(long yEntier){
	//convertit yEntier en chaîne dans laquelle les groupes de 3 chiffres sont séparés par des kcSeparateur qui sont des blancs,eg 12 345.
	int uC,nChiffre,nD,nDecit,nCar;
	char kcSeparateur=' ';
	char *sP3;
	long zEntier;
	int bSigne;
	if (yEntier!=kyLongintMin){
		sP3=malloc(31+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
			bSigne=(yEntier<0);
			zEntier=zAbs(yEntier);//défini vu yEntier!=kyLongintMin
			sprintf(sP3,"%ld",zEntier);//yEntier tient forcément ds sP3 vu allocation généreuse: 4 octets alloués là où 21 bits suffisent.
			nChiffre=nChaineLg(sP3);
			nDecit=nChiffre+(nChiffre-1)/3;
			nCar=0;
			sP3[bSigne+nDecit]='\0';
			for (nD=bSigne+nDecit,uC=1;uC<=nChiffre;uC++){
				sP3[--nD]='0'+zEntier%10;
				if (nD>=bSigne && (uC%3==0))
					sP3[--nD]=kcSeparateur;
				zEntier=zEntier/10;
				nCar++;
			}
			Assert2("sPar3",zEntier==0,nD+1>=bSigne);
			if (bSigne)
				sP3[0]='-';
		MallocGereR(sP3);
	} else {//fabriquer sPar3(kyLongintMin) à partir de sPar3(kxLongintMax)
		sP3=sPar3(kxLongintMax);
		Assert1("sPar3 pour kyLongintMin",sP3[nChaineLg(sP3)-1]=='7');//dc li+1 a du sens: pas de retenue à propager.
		sP3[nChaineLg(sP3)-1]+=1;//en complément à 2, le plus petit nombre négatif est, en valeur absolue, le plus grand positif + 1.
		sP3=sC2("-",sP3);
	}
	return(sP3);
}//sPar3

char *sPas(char *sVerbe,int bNegativer){
	//rend sVerbe tel quel,ou négativé avec "ne"..."pas" si bNegativer 
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sPas=malloc(kuNeLg+nChaineLg(sVerbe)+kuPasLg+kuAntiSlashZerO);
		if (bNegativer){
			strcpy(sPas,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sPas,sVerbe);
			strcat(sPas, " pas");
		}
		else strcpy(sPas,sVerbe);
	MallocGereR(sPas);
	return(sPas);
}//sPas

void Pause(){//suspend l'exécution et attend une frappe clavier minimale
	char cCar;
	printf(" Pause affichage... valider SVP (touche entrée) ou stopper l'exécution en tapant autre chose ");
	scanf("%c",&cCar);
	if (cCar!='\n')
		Stop(1);
	//printf("\n");
}//Pause

long zPgcd(long xA,long xB){
	//rend le Plus Grand Commun Diviseur de xA et xB strictement positifs;en O(lg(Sup(xA,xB))
	long zPgcd;
	long xGrand,xPetit,zReste;
	Assert2("zPgcd1",xA>0,xB>0);
	xGrand=ySup(xA,xB);
	xPetit=yInf(xA,xB);
	while (zPgcd=xPetit,zReste=xGrand % xPetit,zReste>0){
		//teee("zPgcd,xGrand et xB",zPgcd,xGrand,xB);
		xGrand=xPetit;
		xPetit=zReste;
	};
	//printf("Le pgcd de %ld et %ld vaut %ld.\n",xA,xB,zPgcd);
	Assert3("zPgcd2", zPgcd>0, zPgcd>0 && xA % zPgcd==0, zPgcd>0 && xB % zPgcd==0);
	return(zPgcd);
}//zPgcd

char *sPhrase(char *sTexte){
	//rend sTexte avec 1ère lettre majusculée et point final si pas déjà là
	//tt("sPhrase0:",sG(sTexte));
	int nRang=0;
	int nTexteLg=nChaineLg(sTexte);
	bBof=bLettrE2(sTexte,&nRang);//ajoute k-1 à nRang si le premier caractère est codé sur k codes caractères.
	char *sDebut=sChainon(sTexte,0,nRang);
	char *sPhrase=sC3(sMajuscule(sDebut),sChainon(sTexte,nRang+1,nTexteLg),bChaineEgale(sChainon(sTexte,nTexteLg-1,nTexteLg-1),".")? "":".");
	//tt("sPhrase1:",sPhrase);
	return(sPhrase);
}//sPhrase

char *sPluriel(long zEffectif,char *sSingulier){
	//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges"
	int nC,nD;
	int nLg;
	char *sPluriel;
	int mPosition;
	Assert2("sPluriel",zEffectif>=0,sSingulier!=0);
	sPluriel=sC2b(sPar3(zEffectif),sSingulier);
	nLg=nChaineLg(sPluriel);
	mPosition=mChainePos('$',sPluriel);
	if (mPosition>=0){//si zEffectif>1,remplacer les '$' par des 's';sinon, retirer ts les '$'.
		if (zEffectif>1){
			while (mPosition=mChainePos('$',sPluriel),mPosition>=0)
				sPluriel[mPosition]='s';
			}
		else {for (nD=0,nC=0;nC<nLg;nC++)
				if (sPluriel[nC]!='$')
					sPluriel[nD++]=sPluriel[nC];
			sPluriel[nD++]='\0';
		}
	}
	else if (zEffectif>1)
		sPluriel=sC2(sPluriel,"s");
	return(sPluriel);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel

char *sPluriel0(long zEffectif,char *sSingulier,int bFeminin){
	//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges" et (0,"fruit") rend "aucun fruit".
	char *sPluriel0;
	Assert2("sPluriel0",zEffectif>=0,sSingulier!=0);
	sPluriel0=sPluriel(zEffectif,sSingulier);
	if (zEffectif==0)
		sPluriel0=sC2b((bFeminin)?"aucune": "aucun",sChainon(sPluriel0,2,nChaineLg(sPluriel0)));
	return(sPluriel0);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel0

int mPoidsFort(long yEntier){
	//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2;rend -1 si non défini
	int yE,mPoidsFort;
	mPoidsFort=-1;
	if (yEntier>0){
		yE=yEntier;
		while (yE>0){
			yE=yE/2;
			mPoidsFort++;
		}
	}
	Assert1("mPoidsFort",bCroit(-1,mPoidsFort,63));
	return(mPoidsFort);
}//mPoidsFort

long zPpcm(long xA,long xB){
	//rend le Plus Petit Commun Multiple de xA et xB strictement positifs
	long zPpcm=0;
	//tee("xA,xB",xA,xB);
	Assert3("zPpcm1",bOutilAmorceR,xA>0,xB>0);
	zPpcm=(xA*xB)/zPgcd(xA,xB);
	//printf("Le ppcm de %ld et %ld vaut %ld.\n",xA,xB,zPpcm);
	Assert1("zPpcm2",zPpcm>0);
	return(zPpcm);
}//zPpcm

int bPremier(int iNombre){//O(rac(iNombre))
	//vrai ssi iNombre est supérieur à 1 et n'est divisible que par lui-même et par 1
	int uN;
	int bPremier;
	Assert1("bPremier",bOutilAmorceR);
	bPremier=iNombre>1;
	if (bPremier)//nRac(iNombre) est calculable
		for (uN=nRac(iNombre);uN>1;uN--)
			bPremier=bPremier && iNombre%uN!=0;
	return(bPremier);
}//bPremier;

int nPremier(int nRangDuNombrePremier){
	//rend le nombre premier de rang1 nRangDuNombrePremier. Puisque le 1er nombre premier est 2,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
	int nPremier;
	Assert2("zPremier",bOutilAmorceR,bCroit(1,nRangDuNombrePremier,kuPremierRgMax));
	nPremier=uPremieR[nRangDuNombrePremier];
	return(nPremier);
}//nPremier;

void PremierAmorceR(){
	//remplit une fois pour toutes le tableau uPremieR[] avec les kuPremierMax 1ers nombres premiers 
	int uE,uFois,uMultiple,ipPremier;
	int bVoir=kF;
	#define knPremierUltime 1000
	int nPremier[1+knPremierUltime];
	//remplir nPremier[] avec les entiers consécutifs depuis 2 et rayer les multiples de chaque entier (algorithme dit du "crible d'Eratosthène")
		for (uE=2;uE<=knPremierUltime;uE++)
			nPremier[uE]=uE;
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);//entiers consécutifs depuis 1
		for (uFois=2;uFois<=knPremierUltime;uFois++){
			uMultiple=uFois+uFois;//si uFois=2, le 1er multiple à rayer est 4 qui est bien le 1er multiple de 2 strictement supérieur à 2
			while (uMultiple<knPremierUltime){
				nPremier[uMultiple]=0;
				uMultiple=uMultiple+uFois;
			};
		}
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);
	//uPremieR[] soit la copie des kuPremierMax nombres non nuls qui figurent dans le tableau nPremier[] 
		for (ipPremier=0,uE=1;uE<=knPremierUltime && ipPremier<kuPremierRgMax;uE++)
			if (nPremier[uE]!=0)
				uPremieR[++ipPremier]=nPremier[uE];
		if (bVoir) te("ipPremier",ipPremier);
		if (bVoir) VecteurVoir("uPremieR",&uPremieR[0],1,kuPremierRgMax);
	Assert2("PremierAmorceR",uPremieR[1]==2,uPremieR[kuPremierRgMax]>uPremieR[1]);
}//PremierAmorceR

int bPrint(char *sPrint){
	//affiche sPrint suivi de "\n" et rend faux ——permet d'afficher sPrint en fin de boucle For: for (nC=1;nC<5 || bPrint(".");nC++) printf("%d ",nC)…
	printf("%s\n",sPrint);										//…affiche "1 2 3 4 5" terminé par un point et passe à la ligne (contrairt à bPrint0).
	return(kF);
}//bPrint

int bPrint0(char *sPrint){
	//affiche sPrint et rend faux ——permet d'afficher sPrint en fin de boucle For: for (nC=1;nC<5 || bPrint(".");nC++) printf("%d ",nC)…
	printf("%s",sPrint);					//…affiche "1 2 3 4 5" terminé par un point (et ne passe pas à la ligne,contrairt à bPrint).
	return(kF);
}//bPrint0

int bPuissanceDe2(long yOperande){
	//yOperande est une puissance de 2 entière positive inférieure à kxLongintMax/2.
	int bPuissanceDe2;
	long zPuissance=1;
	if ( bCroit(2,yOperande,kxLongintMax/2) ){
		while (zPuissance<yOperande)
			zPuissance=zPuissance+zPuissance;//>0 car yOperande≤kxLongintMax/2 & (zPuissance<yOperande)=>zPuissance<kxLongintMax/2 dc…
		bPuissanceDe2=(yOperande==zPuissance);		   //…2*zPuissance<kxLongintMax ne devient pas <0 par dépassement de kxLongintMax.
	}else bPuissanceDe2=(yOperande==1);
	return(bPuissanceDe2);
}//bPuissanceDe2

long zPuissance(long yOperande,int nExposant){
	long zPuissance;
	Assert2("zPuissance1",nExposant>=0,yOperande!=0 || nExposant!=0);
	zPuissance=pow(yOperande,nExposant);
	//te("zPuissssssssance",zPuissance);
	Assert1("zPuissance2",zPuissance>=0);
	return(zPuissance);
}//zPuissance;

char *sQ(q qRationnel){
	//convertit qRationnel en chaîne de caractères: sQ(1/2) rend "1/2" et sQ(2/1) rend "2".
	#define kuRequis 31
	char *sQ=malloc(kuRequis+kuAntiSlashZerO);
		if (qRationnel.den!=1){
			sprintf(sQ,"%d/%d",qRationnel.num,qRationnel.den);
		}else sprintf(sQ,"%d",qRationnel.num);
	MallocGereR(sQ);
	return(sQ);
}//sQ

char *sReel(float fReel){
	//convertit fReel en chaîne de caractères: sReel(0.5) rend "0.50".
	#define kuRequis 31
	char *sR=malloc(kuRequis+kuAntiSlashZerO);
		sprintf(sR,"%.2f",fReel);
	MallocGereR(sR);
	return(sR);
}//sReel

char *sReel0(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères cadrée à droite sur nCaractereEnTout caractères: sReel0(0.5,6) rend "0.50  ".
	#define kuRequis 31
	char *sReel0=malloc(kuRequis+kuAntiSlashZerO);
		sprintf(sReel0,"%.2f",fReel);
		//f(fReel);printf("sReel2 brute:%s.\n",sG(sReel2));
		sReel0=sChaine0(sReel0,nCaractereEnTout);
		//printf("sReel1 cadrée à gauche:%s.\n",sG(sReel1));
	MallocGereR(sReel0);
	return(sReel0);
}//sReel0

char *sReel1(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères cadrée à gauche sur nCaractereEnTout caractères: sReel1(0.5,6) rend " 0.50 ".
	char *sReel1=malloc(kuRequis+kuAntiSlashZerO);
		sprintf(sReel1,"%.2f",fReel);
		//f(fReel);printf("sReel1 brute:%s.\n",sG(sReel1));
		sReel1=sChaine1(sReel1,nCaractereEnTout);
		//printf("sReel1 cadrée à gauche:%s.\n",sG(sReel1));
	MallocGereR(sReel1);
	return(sReel1);
}//sReel1

char *sReel2(float fReel,int nCaractereEnTout){
	//convertit fReel en chaîne de caractères centrée sur nCaractereEnTout caractères: sReel2(0.5,6) rend " 0.50 ".
	char *sReel2=malloc(kuRequis+kuAntiSlashZerO);
		sprintf(sReel2,"%.2f",fReel);
		//f(fReel);printf("sReel2 brute:%s.\n",sG(sReel2));
		sReel2=sChaine2(sReel2,nCaractereEnTout);
		//printf("sReel2 centrée:%s.\n",sG(sReel2));
	MallocGereR(sReel2);
	return(sReel2);
}//sReel2

int nRac(int nEntier){
	//rend le plus grand entier inférieur ou égal à la racine carrée de nEntier
	int nRac,uRac;
	Assert1("nRac",nEntier>=0);
	for (nRac=0,uRac=1;uRac*uRac<=nEntier;uRac++)
		nRac=uRac;
	return(nRac);
}//nRac

char cSigne(long yEntier){
	//"+" ou "-" ou " " selon que yEntier est soit positif ou nul, soit négatif.
	char cSigne=(yEntier>=0)? '+':'-';
	return(cSigne);
}//cSigne

char *sSigne(long yEntier){
	char *sSigne=sChoix(yEntier>=0,sChoix(yEntier>0,"positif","nul"),"négatif");
	return(sSigne);
}//sSigne

int tSigne(int iValeur){
	//rend +1 si iValeur>0,-1 si iValeur<0, et 0 sinon.
	int tSigne=0;
	if (iValeur>0)
		tSigne=+1;
	if (iValeur<0)
		tSigne=-1;
	return(tSigne);
}//tSigne

int iSignePres(int bSigneInverser,int iValeur){
	//si bSigneInverser est vrai,rend -iValeur;sinon,rend +iValeur.
	int iSignePres;
	iSignePres=(bSigneInverser)? -iValeur: iValeur;
	return(iSignePres);
}//iSignePres

long ySignePres(int bSigneInverser,long yValeur){
	//si bSigneInverser est vrai,rend -yValeur;sinon,rend +yValeur.
	long ySignePres;
	ySignePres=(bSigneInverser)? -yValeur: yValeur;
	return(ySignePres);
}//ySignePres

void Stop(int byMassacre){
	Assert1("Stop",bByte(byMassacre));
	printf("Arrêt de l'exécution, exit %d.\n",byMassacre);
	exit(byMassacre);//affiche le paramètre de exit() puis arrête l'exécution. Cache la fonction système exit().
}//Stop

q qSub(q qA,q qB){
	//différence de deux rationnels
	q qSub;
	qSub=qAdd(qA,qOpp(qB));
	return(qSub);
}//qSub

ri riSub(ri riA,ri riB){
	//différence de deux nombres complexes à composantes entières
	ri riSub;
	riSub.r=riA.r-riB.r;
	riSub.i=riA.i-riB.i;
	return(riSub);
}//riSub

char *sSucces(int bSuccesSinonEchec){
	//rend "succès" ou "échec" selon bSuccesSinonEchec 
	#define kuSuccesSinonEchecLg 6
	char *sSucces=malloc( kuAntiSlashZerO + kuSuccesSinonEchecLg);
		Assert2("sSucces",nChaineLg("succès")==6,nChaineLg("succès")==6);
		sSucces[0]='\0';
		strcat(sSucces,(bSuccesSinonEchec)? "succès": "échec");
	MallocGereR(sSucces);
	return(sSucces);
}//sSucces

int iSup(int iA,int iB){
	//rend sup(iA,iB);identique à iMax(iA,iB).
	int iSup=(iA<iB)?iB:iA;
	return(iSup);
}//iSup

int iSup3(int iA,int iB,int iC){
	int iSup3=iSup(iA,iSup(iB,iC));
	return(iSup3);
}//iSup3

double rSup(double dA,double dB){
	//rend sup(dA,dB)
	double rSup=(dA>dB)?dA:dB;
	return(rSup);
}//rSup

long ySup(long yA,long yB){
	//rend sup(yA,yB);identique à yMax(yA,yB)
	long ySup=(yA>yB)?yA:yB;
	return(ySup);
}//ySup

char *sTab(int nIndentation){
	//rend kuTabulationLargeur*nIndentation caractères blancs consécutifs
	const int kuTabulationLargeur=4;
	Assert1("sTab",nIndentation>=0);
	int uRequis=kuTabulationLargeur*nIndentation;
	char *sIndentation=malloc(uRequis+kuAntiSlashZerO);
		strcpy(sIndentation,sE(kuTabulationLargeur*nIndentation));
	MallocGereR(sIndentation);
	return(sIndentation);
}//sTab

void TableauVoir(char *sNom,int iQuelTableau[kuTableauLigneMax][kuTableauLigneMax],int nIndexMin1,int nIndexMax1,int nIndexMin2,int nIndexMax2){
	//affiche iQuelTableau[nIndexMin1..nIndexMax1][nIndexMin2..nIndexMax2],dc bornes incluses
	int nE;
	Assert4("iQuelTableau",sNom!=0,iQuelTableau!=0,bCroit4(0,nIndexMin1,nIndexMax1,kuTableauLigneMax),bCroit4(0,nIndexMin2,nIndexMax2,kuTableauLigneMax));
	printf("%s col:",sNom);
	for (nE=nIndexMin1;nE<=nIndexMax1;nE++)
		printf("%3d ",nE);
	printf("\n");
	for (nE=nIndexMin1;nE<=nIndexMax1;nE++)
		VecteurVoir(sC2(sNom,sCrochet1(nE)),iQuelTableau[nE],nIndexMin2,nIndexMax2);
}//iQuelTableau

void Titrer(char *sTitre){
	//affiche sTitre au centre d'une ligne de kuTitreLargeurPaire caractères garnie par défaut de caractères '*'
	Titrer2(sTitre,'*');
}//Titrer

void Titrer1(char *sTitre){
	//affiche sTitre étalé au centre d'une ligne de kuTitreLargeurPaire caractères garnie par défaut de caractères '*'
	Titrer2(sChaineEtale1(sTitre),'*');
}//Titrer1

void Titrer2(char *sTitre,char cMotif){
	//affiche sTitre au centre d'une ligne de kuTitreLargeurPaire caractères garnie de caractères cMotif
	const int kuTitreLargeurPaire=100;//ou un autre nombre pair
	const int kuUnBlanc=1;
	assert(sTitre!=0);//pas Assert
	int nTitreLg=nCaractere(sTitre);
	assert(nTitreLg<kuTitreLargeurPaire && kuTitreLargeurPaire%2==0);
	int nMotifDeChaqueCoteh=(kuTitreLargeurPaire-kuUnBlanc-nTitreLg-kuUnBlanc)/2;//oui,division entière
	int bUnMotifEnSus=bImpair(nTitreLg);//pour ajouter un cMotif chaque fois que la longueur du titre est impaire
	assert(nMotifDeChaqueCoteh+kuUnBlanc+nTitreLg+kuUnBlanc+nMotifDeChaqueCoteh+bUnMotifEnSus==kuTitreLargeurPaire);//pas Assert
	//teee("nTitreLg,nMotifDeChaqueCoteh,bUnMotifEnSus",nTitreLg,nMotifDeChaqueCoteh,bUnMotifEnSus);
	printf("%s %s %s\n",sFois(nMotifDeChaqueCoteh,cMotif),sTitre,sFois(nMotifDeChaqueCoteh+bUnMotifEnSus,cMotif));
}//Titrer

char *sTriplet(long yEntierA,long yEntierB,long yEntierC){
	//rend la chaîne "(yEntierA,yEntierB,yEntierC)"	
	char *sTriplet=malloc(1+kuEntierSizE+1+kuEntierSizE+1+kuEntierSizE+1+kuAntiSlashZerO);
		strcpy(sTriplet,sC7("(",sEnt(yEntierA),",",sEnt(yEntierB),",",sEnt(yEntierC),")"));
	MallocGereR(sTriplet);
	return(sTriplet);
}//sTriplet

int bTrit(int tVariable){
	//vrai ssi tVariable est un trit à valeur dans {-1,0,+1}
	int tTrit=bCroit(-1,tVariable,+1);
	return(tTrit);
}//bTrit

char *sUn(char *sVerbe,int bUn){
	//si bUn,rend sVerbe suivi de "un";sinon,encadre sVerbe avec "ne" et "aucun".
	return(sUnOuUne(sVerbe,bUn,!k1Feminin));
}//sUn

char *sUnOuUne(char *sVerbe,int bUn,int bFeminin){
	//si bUn,rend sVerbe suivi de "un" ou "une";sinon,encadre sVerbe avec "ne" et "aucun" ou "aucune".
	const int kuNegationEtBlancLgMax= 4;
	Assert2("sUn",sVerbe!=0,bBool(bUn));
	char *sUnOuUne=malloc(nChaineLg(sVerbe)+iMax(nChaineLg("un"),nChaineLg("pas de"))+bFeminin+kuNegationEtBlancLgMax);
		if (!bUn){
			strcpy(sUnOuUne,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
			strcat(sUnOuUne,sVerbe);
		}
		else strcpy(sUnOuUne,sVerbe);
		strcat(sUnOuUne," ");
		switch (nCas4(bUn,bFeminin)){
			case 0:	strcat(sUnOuUne,"pas de");break;//strcat(sUnOuUne,"aucun");break;
			case 1:	strcat(sUnOuUne,"pas de");break;//strcat(sUnOuUne,"aucune");break;
			case 2:	strcat(sUnOuUne,"un");break;
			case 3:	strcat(sUnOuUne,"une");break;
		}
	MallocGereR(sUnOuUne);
	return(sUnOuUne);
}//sUnOuUne

char *sUne(char *sVerbe,int bUne){
	//si bUn,rend sVerbe suivi de "une";sinon,encadre sVerbe avec "ne" et "aucune".
	return(sUnOuUne(sVerbe,bUne,k1Feminin));
}//sUne

int bVecteurContient(int nEnquis,int iVecteur[]){
	int nCardinal=iVecteur[0];
	//nEnquis dans iVecteur[1..nCardinal] 
	int bContient=(1<=nCardinal) && mVecteurContient(nEnquis,iVecteur,1,nCardinal)>=0;
	return(bContient);
}//bVecteurContient

int mVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le rang 1 de nEnquis dans iVecteur[nIndexMin..nIndexMax],ou -1 si nEnquis n'est pas dans iVecteur[nIndexMin..nIndexMax] 
	int uE;
	int mContient=-1;
	Assert2("mVecteurContient",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (uE=nIndexMin;uE<=nIndexMax && (mContient<0);uE++)
		if (nEnquis==iVecteur[uE])
			 mContient=uE;
	return(mContient);
}//mVecteurContient

int bVecteurContient1(int nEnquis,int nCardinal,int iVecteur[]){
	//nEnquis dans iVecteur[1..nCardinal] 
	int bContient1=(1<=nCardinal) && mVecteurContient(nEnquis,iVecteur,1,nCardinal)>=0;
	return(bContient1);
}//bVecteurContient1

void VecteurCopier(int iVecteurA[],int nIndexMin,int nIndexMax,int iVecteurB[]){
	//iVecteurB[nIndexMin..nIndexMax] := iVecteurA[nIndexMin..nIndexMax] 
	int nK;
	Assert3("VecteurCopier",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		iVecteurB[nK]=iVecteurA[nK];
}//VecteurCopier

int nVecteurDoublet(int iVecteur[],int nIndexMin,int nIndexMax){//O(N)
	//rend le nombre de paires d'éléments consécutifs de iVecteur[nIndexMin..nIndexMax] qui sont égaux
	int nDoublet,nK;
	Assert2("nVecteurDoublet",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nDoublet=0,nK=nIndexMin;nK<nIndexMax;nK++)
		nDoublet += iVecteur[nK]==iVecteur[nK+1];
	return(nDoublet);
}//nVecteurDoublet

int nVecteurDoublon(int iVecteur[],int nIndexMin,int nIndexMax){//O(N*N)
	//rend la plus petite distance deux éléments identiques de iVecteur[nIndexMin..nIndexMax]
	int nDoublon,nK,nL;
	Assert2("nVecteurDoublon",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nDoublon=kuIntegerMax,nK=nIndexMin;nK<nIndexMax;nK++)
		for (nL=nK+1;nL<=nIndexMax;nL++)
			if (iVecteur[nK]==iVecteur[nL]){
				nDoublon=iInf(nDoublon,nL-nK);
				//d5(nK,nL,iVecteur[nK],iVecteur[nL],nDoublon);
			}
	if (nDoublon==kuIntegerMax)
		nDoublon=0;
	return(nDoublon);
}//nVecteurDoublon

int nVecteurEcreter(int iVecteur[],int nIndexMin,int nIndexMax,int iPlancherMin,int iPlafondMax){
	//remplace iVecteur[X] par iPlancherMin ou iPlafondMax si iVecteur[X] est hors [iPlancherMin..iPlafondMax];rend le nombre d'éléments écrêtés. 
	int nK,nEcreter;
	Assert3("nVecteurEcreter",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax),iPlancherMin<=iPlafondMax);
	for (nEcreter=0,nK=nIndexMin;nK<=nIndexMax;nK++)
		if ( !bCroit(iPlancherMin,iVecteur[nK],iPlafondMax) ){
			iVecteur[nK]=iBorner(iPlancherMin,iVecteur[nK],iPlafondMax);
			nEcreter++;
		}
	return(nEcreter);
}//nVecteurEcreter

int bVecteurEgal(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax){
	//vrai sssi iVecteurA[nIndexMin..nIndexMax] = iVecteurB[nIndexMin..nIndexMax] 
	int nK,bEgal;
	Assert3("bVecteurEgal",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (bEgal=kV,nK=nIndexMin;nK<=nIndexMax;nK++)
		bEgal=bEgal && iVecteurA[nK]==iVecteurB[nK];
	return(bEgal);
}//bVecteurEgal

void VecteurFusionneR(int iVecteur[],int nIndexMin,int nMilieu,int nIndexMax){//O(nIndexMax-nIndexMin)
	//fusionne iVecteur[nIndexMin..nMilieu] et iQuelVecteur[nMilieu+1,nIndexMax];ordre croissant
	int iK,iL,iP;
	int iCopie[1+nIndexMax];
	//printf("fusion %s %s.\n",sDomaine(nIndexMin,nMilieu),sDomaine(nMilieu+1,nIndexMax) );
	VecteurCopier(iVecteur,nIndexMin,nIndexMax,iCopie);
	//VecteurVoir("AVANT fusion",iCopie,nIndexMin,nIndexMax);
	//VecteurRazer(iVecteur,nIndexMin,nIndexMax);
	iK=nIndexMin;
	iL=nMilieu+1;
	iP=nIndexMin-1;
	while (++iP<=nIndexMax){
		if (iK>nMilieu)
			iVecteur[iP]=iCopie[iL++];
		else if (iL>nIndexMax)
			iVecteur[iP]=iCopie[iK++];
		else if (iCopie[iK]<iCopie[iL]){
			iVecteur[iP]=iCopie[iK++];
		} else iVecteur[iP]=iCopie[iL++];
		//VecteurVoir("APRÈS while",iVecteur,nIndexMin,nIndexMax);
	}
	//VecteurVoir("APRÈS fusion",iVecteur,nIndexMin,nIndexMax);
}//VecteurFusionneR

void VecteurIndexer(int iVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VecteurIndexer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=nE;
}//VecteurIndexer

void VecteurInitialiser(int iVecteur[],int nIndexMin,int nIndexMax,int iValeurInitiale){
	int nE;
	Assert2("VecteurInitialiser",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=iValeurInitiale;
}//VecteurInitialiser

long yVecteurInf(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurInf",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long yInf;
	for (yInf=kxLongintMax,nE=nIndexMin;nE<=nIndexMax;nE++)
		yInf=yMin(yInf,iVecteur[nE]);
	return(yInf);
}//yVecteurInf

int bVecteurNul(int iVecteur[],int nIndexMin,int nIndexMax){
	//iVecteur[nIndexMin..nIndexMax] est nul partout 
	int uE;
	int bNul;
	Assert1("bVecteurNul",bCroit(0,nIndexMin,nIndexMax));
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (iVecteur[uE]!=0)
			 bNul=kF;
	return(bNul);
}//bVecteurNul

int nVecteurOccurrence(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax] 
	int uE;
	int nOccurrence;
	Assert2("nVecteurOccurrence",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (nOccurrence=0,uE=nIndexMin;uE<=nIndexMax;uE++)
		nOccurrence += nEnquis==iVecteur[uE];
	return(nOccurrence);
}//nVecteurOccurrence

int nVecteurOccurrenceMax(int iVecteur[],int nIndexMin,int nIndexMax){
	//rend le nombre d'occurrences maximal d'un élément de iVecteur[nIndexMin..nIndexMax],eg 3 si iVecteur=(1,6,1,6,6,9,8). 
	int uE;
	int nOccurrenceMax;
	Assert2("nVecteurOccurrenceMax",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax) );
	for (nOccurrenceMax=0,uE=nIndexMin;uE<=nIndexMax;uE++)
		nOccurrenceMax=iSup(nOccurrenceMax,nVecteurOccurrence(iVecteur[uE],iVecteur,nIndexMin,nIndexMax) );
	return(nOccurrenceMax);
}//nVecteurOccurrenceMax

void VecteurRazer(int iVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VecteurRazer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			iVecteur[nE]=0;
}//VecteurRazer

int bVecteurSemblable(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax){
	//vrai sssi iVecteurB[nIndexMin..nIndexMax] est une copie désordonnée de iVecteurA[nIndexMin..nIndexMax] 
	int nK,bSemblable;
	int iVecteurAbis[1+nIndexMax];
	int iVecteurBbis[1+nIndexMax];
	Assert3("bVecteurIdentique",iVecteurA!=0,iVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	VecteurCopier(iVecteurA,nIndexMin,nIndexMax,iVecteurAbis);
	VecteurCopier(iVecteurB,nIndexMin,nIndexMax,iVecteurBbis);
	VecteurTrier(iVecteurAbis,nIndexMin,nIndexMax);
	VecteurTrier(iVecteurBbis,nIndexMin,nIndexMax);
	for (bSemblable=kV,nK=nIndexMin;nK<=nIndexMax;nK++)
		bSemblable=bSemblable && iVecteurAbis[nK]==iVecteurBbis[nK];
	return(bSemblable);
}//bVecteurSemblable

long yVecteurSomme(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurSomme",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySomme;
	tee("nIndexMin,nIndexMax",nIndexMin,nIndexMax);
	for (ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySomme+=iVecteur[nE];
	return(ySomme);
}//yVecteurSomme

long yVecteurSup(int iVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurSup",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySup;
	for (ySup=kyLongintMin,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySup=yMax(ySup,iVecteur[nE]);
	return(ySup);
}//yVecteurSup

void VecteurTrier(int iQuelVecteur[],int nIndexMin,int nIndexMax){//O(N*N)
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant
	int nK,nL,nMin,nPlace;
	Assert2("VecteurTrier",iQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<nIndexMax;nK++){
		for (nMin=iQuelVecteur[nPlace=nK],nL=nK+1;nL<=nIndexMax;nL++)
			if (nMin>iQuelVecteur[nL])
				nMin=iQuelVecteur[nPlace=nL];
		//teee("nK,nPlace,nMin",nK,nPlace,nMin);
		EntierEchanger(&iQuelVecteur[nK],&iQuelVecteur[nPlace]);
	}
}//VecteurTrier

void VecteurTrier2(int iQuelVecteur[],int nIndexMin,int nIndexMax,int nIndex[]){
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant et rend dans nIndex les nouveaux index des éléments après le tri. 
	int nK,nL,nMin,nPlace;
	Assert2("VecteurTrier2",iQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		nIndex[nK]=nK;
	for (nK=nIndexMin;nK<nIndexMax;nK++){
		for (nMin=iQuelVecteur[nPlace=nK],nL=nK+1;nL<=nIndexMax;nL++)
			if (nMin>iQuelVecteur[nL])
				nMin=iQuelVecteur[nPlace=nL];
		//teee("nK,nPlace,nMin",nK,nPlace,nMin);
		EntierEchanger(&iQuelVecteur[nK],&iQuelVecteur[nPlace]);
		EntierEchanger(&nIndex[nK],&nIndex[nPlace]);
	}
}//VecteurTrier2

void VecteurTrierVite(int iQuelVecteur[],int nIndexMin,int nIndexMax){//O(N*logN)
	//trie iQuelVecteur[nIndexMin..nIndexMax] par ordre croissant
	int nMilieu=(nIndexMin+nIndexMax)/2;
	if (nIndexMin<nIndexMax){
		//printf("%s tri de iQuelVecteur%s\n",sTab(nNiveau),sDomaine(nIndexMin,nIndexMax));
		VecteurTrierVite(iQuelVecteur,nIndexMin,nMilieu);
		VecteurTrierVite(iQuelVecteur,nMilieu+1,nIndexMax);
		VecteurFusionneR(iQuelVecteur,nIndexMin,nMilieu,nIndexMax);
		//VecteurVoir("iQuelVecteur",iQuelVecteur,nIndexMin,nIndexMax);
	}
}//VecteurTrierVite

void VecteurValuer(int iVecteur[],int nIndexMin,int nIndexMax,int iValeur){
	int nE;
	Assert2("VecteurRazer",iVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nE=nIndexMin;nE<=nIndexMax;nE++)
		iVecteur[nE]=iValeur;
}//VecteurValuer

void VecteurVoir(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche iQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Assert2("VecteurVoir",sNom!=0,iQuelVecteur!=0);
	printf("%s[]: ",sNom);
		if (bCroit(0,nIndexMin,nIndexMax) )
			for (nE=nIndexMin;nE<=nIndexMax;nE++)
				printf("%3d%c ",iQuelVecteur[nE],(nE<nIndexMax)?',':'.');
			else printf("%s est un domaine vide.",sDomaine(nIndexMin,nIndexMax));
	printf("\n");
}//VecteurVoir

void VecteurVoir0(char *sNom,int iQuelVecteur[]){
	//affiche iQuelVecteur[1..iQuelVecteur[0]],dc bornes incluses
	int nE;
	Assert2("VecteurVoir0",sNom!=0,iQuelVecteur!=0);
	printf("%s%s: ",sNom,sDomaine(1,iQuelVecteur[0]));
		if ( iQuelVecteur[0]>0 )
			for (nE=1;nE<=iQuelVecteur[0];nE++)
				printf("%3d%c ",iQuelVecteur[nE],(nE<iQuelVecteur[0])?',':'.');
			else printf("ce domaine ne contient pas d'éléments.",sDomaine(1,iQuelVecteur[0]));
	printf("\n");
}//VecteurVoir0

void VecteurVoir1(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche, ligne 1, les index nIndexMin..nIndexMax puis, ligne 2, iQuelVecteur[nIndexMin..nIndexMax] ——donc nIndexMax-nIndexMin+1 éléments.
	int nE,nLargeurMax,kuIndexLg=5;
	Assert3("VecteurVoir1",sNom!=0,iQuelVecteur!=0,kuIndexLg==nChaineLg("index"));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
		//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment iQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
			for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
				nLargeurMax=iSup(nLargeurMax,nChaineLg(sEnt(iQuelVecteur[nE])));
		//NB nChaineLg ci-dessous non adapté aux sNom accentués
		//t(sNom);d(nCaractere(sNom));
		printf("index:%s ",sE(iSup(0,nCaractere(sNom)-kuIndexLg)));//affiche "index" et ajoute au besoin des espaces pour atteindre la longueur de sNom.
			for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
				printf("%s%c ",sEntier(nE,nLargeurMax),' ');
		printf("%s%s: ",sNom,sE(iSup(0,kuIndexLg-nCaractere(sNom))));//affiche sNom et ajoute au besoin des espaces pour atteindre la longueur de "index".
			for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
				printf("%s%c ",sEntier(iQuelVecteur[nE],nLargeurMax),(nE<nIndexMax)?',':'.');
	} else printf("%s: le domaine %s est vide.\n",sNom,sDomaine(nIndexMin,nIndexMax));
}//VecteurVoir1

void VecteurVoir2(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les doublets (index,iQuelVecteur[index]) dans l'intervalle [nIndexMin..nIndexMax], dc bornes incluses
	int nE;
	Assert2("VecteurVoir2",sNom!=0,iQuelVecteur!=0);
	printf("%s%s: ",sNom,sDomaine(nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) ){
			for (nE=nIndexMin;nE<=nIndexMax;nE++)
				printf("%s ",sCouple(nE,iQuelVecteur[nE]));
		printf("\n");
	}else printf("domaine sans élément.\n");
}//VecteurVoir2

int bVekteurContient(long yEnquis,int nCardinal,long yVecteur[]){
	//yEnquis dans yVecteur[1..nCardinal] 
	int uE;
	int bContient=kF;
	Assert1("bVekteurContient",nCardinal>0);
	for (uE=1;uE<=nCardinal;uE++)
		if (yEnquis==yVecteur[uE])
			 bContient=kV;
	return(bContient);
}//bVekteurContient

void VekteurCopier(long yVecteurA[],int nIndexMin,int nIndexMax,long yVecteurB[]){
	//yVecteurB[nIndexMin..nIndexMax] := yVecteurA[nIndexMin..nIndexMax] 
	int nK;
	Assert3("VekteurCopier",yVecteurA!=0,yVecteurB!=0,bCroit(0,nIndexMin,nIndexMax));
	for (nK=nIndexMin;nK<=nIndexMax;nK++)
		yVecteurB[nK]=yVecteurA[nK];
}//VekteurCopier

int bVekteurNul(long yVecteur[],int nIndexMin,int nIndexMax){
	//yVecteur[nIndexMin..nIndexMax] est nul partout 
	int uE;
	int bNul;
	Assert1("bVekteurNul",bCroit(0,nIndexMin,nIndexMax));
	for (bNul=kV,uE=nIndexMin;uE<=nIndexMax;uE++)
		if (yVecteur[uE]!=0)
			 bNul=kF;
	return(bNul);
}//bVekteurNul

void VekteurRazer(long yVecteur[],int nIndexMin,int nIndexMax){
	int nE;
	Assert2("VekteurRazer",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	if ( bCroit(0,nIndexMin,nIndexMax) )
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			yVecteur[nE]=0;
}//VekteurRazer

long yVekteurSomme(long yVecteur[],int nIndexMin,int nIndexMax){
	Assert2("yVecteurSomme",yVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	int nE;
	long ySomme;
	//tee("nIndexMin,nIndexMax",nIndexMin,nIndexMax);
	for (ySomme=0,nE=nIndexMin;nE<=nIndexMax;nE++)
		ySomme+=yVecteur[nE];
	return(ySomme);
}//yVekteurSomme

void VekteurVoir(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche yQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Assert3("VekteurVoir",sNom!=0,yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	printf("%s: ",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%2ld%c ",yQuelVecteur[nE],(nE<nIndexMax)?',':'.');
	printf("\n");
}//VekteurVoir

void VekteurVoir1(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche, ligne 1, les index nIndexMin..nIndexMax puis, ligne 2, yQuelVecteur[nIndexMin..nIndexMax] ——donc nIndexMax-nIndexMin+1 éléments.
	int nE,nLargeurMax,kuIndexLg=5;
	Assert4("VekteurVoir1",sNom!=0,yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax),kuIndexLg==nChaineLg("index"));
	//nLargeurMax:=encombrement maximal,en caractères, d'un élément du segment yQuelVecteur[nIndexMin..nIndexMax] ou de nIndexMin..nIndexMax:
		for (nLargeurMax=nChaineLg(sEnt(nIndexMax)),nE=nIndexMin;nE<=nIndexMax;nE++)
			nLargeurMax=iSup(nLargeurMax,nChaineLg(sEnt(yQuelVecteur[nE])));
	printf("index:%s ",sE(iSup(0,nChaineLg(sNom)-kuIndexLg)));//affiche "index" et ajoute au besoin des espaces pour atteindre la longueur de sNom.
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%c ",sEntier(nE,nLargeurMax),' ');
	printf("%s%s: ",sNom,sE(iSup(0,kuIndexLg-nChaineLg(sNom))));//affiche sNom et ajoute au besoin des espaces pour atteindre la longueur de "index".
		for (nE=nIndexMin;nE<=nIndexMax || bPrint("");nE++)
			printf("%s%c ",sEntier(yQuelVecteur[nE],nLargeurMax),(nE<nIndexMax)?',':'.');
}//VekteurVoir1

void VekteurVoir2(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche les doublets (index,yQuelVecteur[index]) dans l'intervalle [nIndexMin..nIndexMax], dc bornes incluses
	int nE;
	Assert3("VekteurVoir2",sNom!=0,yQuelVecteur!=0,bCroit(0,nIndexMin,nIndexMax));
	printf("%s: ",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%s ",sCouple(nE,yQuelVecteur[nE]));
	printf("\n");
}//VekteurVoir2

void Voir(char *sFormat,...){
	//sFormat indique le type des paramètres qui le suivent (utiliser le format du printf,eg "%d,%s,%f\n").
	int iEntier;
	char *pCar;
	char *sChaine;
	float fReel;
	va_list ap;//array of parameter
	va_start(ap,sFormat);
		//tt("sFormat",sG(sFormat));
		for (pCar=sFormat;*pCar;pCar++){// *pCar permet de détecter le '\0' qui termine sFormat
			if (*pCar!='%'){
				putchar(*pCar);
				continue;
			}
			switch (*++pCar){
				case 'd': iEntier=va_arg(ap,int); printf("%d",iEntier);break;//"%5d": 5 caractR en tout,dont signe "-" éventuel.
				case 'f': fReel=va_arg(ap,double); printf("%f",fReel);break;//"%.2f" pr 2 caractR après le ".". "%5.2f": 5 caractR en tout.
				case 's': sChaine=va_arg(ap,char *);printf("%s",sChaine);break;
			}
		} 
	va_end(ap);
}//Voir

int bVoyelle(char *sTexte,int nCodeCaractereRg){
	//sTexte[nCodeCaractereRg] ou Chaine[nCodeCaractereRg..nCodeCaractereRg+1] code une voyelle
	int nRg=nCodeCaractereRg;
	Assert2("bVoyelle",sTexte!=0,nCodeCaractereRg>=0);
	int bVoyelle=bVoyellE2(sTexte,&nRg);
	return(bVoyelle);
}//bVoyelle

int bVoyellE2(char *sTexte,int *pnCodeCaractereRg0){
	//sTexte[*pnCodeCaractereRg0] ou Chaine[*pnCodeCaractereRg0..*pnCodeCaractereRg0+1] code une voyelle;si vrai et 2 codes, passe au code suivant
	//pour le seul ŸaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã";//piqûre Haüy;nValide2[1] pour le seul Ÿ
	int nCar;
	char cCode;
    #define knVoyelle1LiM 12
    #define knVoyelle2LiM 33
    #define knVoyelle3LiM 01
	//nVoyelle1 dédié voyelles sans signes diacritiques";
	int nVoyelle1[knVoyelle1LiM]={'A','E','I','O','U','Y','a','e','i','o','u','y'};
	//nVoyelle2 dédié dans l'ordre à éàèùâêîôûäïöüÿÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜã";
	int nVoyelle2[knVoyelle2LiM]={87,96,88,71,94,86,82,76,69,92, 81,74,68,65,126,118,114,108,101,119, 128,103,126,118,114,108,101,124,117,113, 106,100,93};
	//nVoyelle3 pour le seul Ÿ
	int nVoyelle3[knVoyelle3LiM]={72};
	int bVoyellE2=0;
	assert(sTexte!=0);
	Assert1("bVoyellE2",bCroit(0,*pnCodeCaractereRg0,nChaineLg(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg0];
	bVoyellE2=isalpha(cCode);
	if (bVoyellE2){//voyelle ou consonne?
		for (bVoyellE2=0,nCar=0; nCar<knVoyelle1LiM; nCar++)
			bVoyellE2=bVoyellE2||(cCode==nVoyelle1[nCar]);
		}
	else if (*pnCodeCaractereRg0<nChaineLg(sTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knVoyelle2LiM; nCar++)
				bVoyellE2=bVoyellE2||(cCode==-nVoyelle2[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg0)++;//2 codes pour un seul caractère
		}
		else if (cCode==kcEchappemenT2) {
			cCode=sTexte[*pnCodeCaractereRg0+1];
			for (nCar=0; nCar<knVoyelle3LiM; nCar++)
				bVoyellE2= bVoyellE2 || (cCode==-nVoyelle3[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg0)++;//2 codes pour un seul caractère
		}
	}
	return(bVoyellE2);
}//bVoyellE2

int bVrai(int iEntier){
	//rend vrai ssi iEntier!=0
	int bVrai=(iEntier!=0) ? 1 : 0;
	return(bVrai);
}//bVrai

void While(long zIterationMax){
	//prend note du nombre maximum d'itérations acceptable dans le while ou le do while qui suit immédiatement l'appel de cette routine
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return, etc.
	Assert1("While",zIterationMax>=0);//le nombre maximum d'itérations est censé être positif
	ipWhilE++;
	Assert1("While",ipWhilE<=kuWhileMaX);//trop de boucles while/do while imbriquées (la constante kuWhileMaX est déclarée en haut de ce module)
	zWhilE[ipWhilE]=zIterationMax;
}//While

int bWhile(char *sContexte,int bExpressionBooleenne){
	//rend bExpressionBooleenne tout en gérant l'itération en cours (ie son rang ne dépasse pas zIterationMax spécifié dans l'appel à While() qui précède
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return,etc
	long zIterationRestante;
	Assert1("bWhile",bCroit(0,ipWhilE,kuWhileMaX));//la constante kuWhileMaX est déclarée en haut de ce module
	zWhilE[ipWhilE]--;//décrémente le nombre d'itérations de la boucle imbriquée de rang ipWhilE
	zIterationRestante=zWhilE[ipWhilE];
	if (zIterationRestante<0){
		printf("    *** Boucle \"while\" ou \"do while\" interrompue dans \"%s\". Le maximum spécifié a été dépassé.\n",sContexte);
		assert(zIterationRestante>=0);
	}
	if (bExpressionBooleenne==0){//la sortie imminente du while courant ramène le contexte ds la boucle imbriquée englobante,de rang ipWhilE-1
		zWhilE[ipWhilE]=0;//superflu mais ce nettoyage facilite la mise au point
		ipWhilE--;//vital
		if (ipWhilE<0){
			printf("    *** Manque un While() devant la boucle \"while\" ou \"do while\" de \"%s\" ou devant une boucle exécutée avant.\n",sContexte);
			assert(ipWhilE>=0);
		}
	}//Chaque boucle while est donc contrôlée via 1° un appel à While() avant le while et 2° un appel à bWhile() dans l'expression booléenne qui est...
	return(bExpressionBooleenne);//...attachée au while; Appel1("") à la fin du main() vérifie le bon ordonnancement des while,cf Appel1d et Appel1e.
}//bWhile
