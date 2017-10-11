//liste des #include du C. Il suffit d'un #include "Outil.h" dans les autres modules.
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <math.h>
	#include <ctype.h>
	#include <string.h>
	#include <limits.h>
	#include <assert.h>
	#include <time.h>
//fonctions de mise au point;affichent le libellé de l'expression puis l'expression;nom suggéré par le format,eg f pour float.
	#define b(Entier) printf(#Entier"=%s.\n",(Entier)? "VRAI": "FAUX")
	#define d(Entier) printf(#Entier"=%s.\n",sPar3(Entier))
	#define d2(dA,dB) printf("(" #dA "," #dB ")=(%s,%s).\n",sPar3(dA),sPar3(dB))
	#define d3(dA,dB,dC) printf("(" #dA "," #dB "," #dC ")=(%s,%s,%s).\n",sPar3(dA),sPar3(dB),sPar3(dC))
	#define d4(dA,dB,dC,dD) printf("(" #dA "," #dB "," #dC "," #dD ")=(%s,%s,%s,%s).\n",sPar3(dA),sPar3(dB),sPar3(dC),sPar3(dD))
	#define d5(dA,dB,dC,dD,dE) printf("(" #dA "," #dB "," #dC "," #dD "," #dE ")=(%s,%s,%s,%s,%s).\n",sPar3(dA),sPar3(dB),sPar3(dC),sPar3(dD),sPar3(dE))
	#define d6(dA,dB,dC,dD,dE,dF) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF ")=(%s,%s,%s,%s,%s,%s).\n",sPar3(dA),sPar3(dB),sPar3(dC),sPar3(dD),sPar3(dE),sPar3(dF))
	#define d7(dA,dB,dC,dD,dE,dF,dG) printf("(" #dA "," #dB "," #dC "," #dD "," #dE "," #dF "," #dG ")=(%s,%s,%s,%s,%s,%s,%s).\n",sPar3(dA),sPar3(dB),sPar3(dC),dsPar3(D),sPar3(dE),sPar3(dF),sPar3(dG))
	#define dd(dA,dB) printf(#dA"=%s, "#dB"=%s.\n",sPar3(dA),sPar3(dB))
	#define ddd(dA,dB,dC) printf(#dA"=%s, "#dB"=%s, "#dC"=%s.\n",sPar3(dA),sPar3(dB),sPar3(dC))
	#define dddd(dA,dB,dC,dD) printf(#dA"=%s, "#dB"=%s, "#dC"=%s, "#dD"=%s.\n",sPar3(dA),sPar3(dB),sPar3(dC),sPar3(dD))
	#define f(Reel) printf(#Reel"=%.3f.\n",Reel)
	#define f2(fA,fB) printf("(" #fA "," #fB ")=(%.3f,%.3f).\n",fA,fB)
	#define f3(fA,fB,fC) printf("(" #fA "," #fB "," #fC ")=(%.3f,%.3f,%.3f).\n",fA,fB,fC)
	#define ld(Entier) printf(#Entier"=%s.\n",sPar3(Entier))
	#define ld2(ldA,ldB) printf("(" #ldA "," #ldB ")=(%s,%s).\n",sPar3(ldA),sPar3(ldB))
	#define ld3(ldA,ldB,ldC) printf("(" #ldA "," #ldB "," #ldC ")=(%s,%s,%s).\n",sPar3(ldA),sPar3(ldB),sPar3(ldC))
	#define ld4(ldA,ldB,ldC,ldD) printf("(" #ldA "," #ldB "," #ldC "," #ldD ")=(%s,%s,%s,%s).\n",sPar3(ldA),sPar3(ldB),sPar3(ldC),sPar3(ldD))
	#define s(sTexte) printf(#sTexte"=\"%s\".\n",sTexte)
	#define s2(sA,sB) printf("(" #sA "," #sB ")=(\"%s\",\"%s\").\n",sA,sB)
	#define s3(sA,sB,sC) printf("(" #sA "," #sB "," #sC ")=(\"%s\",\"%s\",\"%s\").\n",sA,sB,sC)
	#define s4(sA,sB,sC,sD) printf("(" #sA "," #sB "," #sC "," #sD ")=(\"%s\",\"%s\",\"%s\",\"%s\").\n",sA,sB,sC,sD)
	#define s5(sA,sB,sC,sD,sE) printf("(" #sA "," #sB "," #sC "," #sD "," #sE ")=(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\").\n",sA,sB,sC,sD,sE)
	#define m0 printf("*0* franchi.\n")
	#define m1 printf("*1* franchi.\n")
	#define m2 printf("*2* franchi.\n")
	#define m3 printf("*3* franchi.\n")
	#define m4 printf("*4* franchi.\n")
	#define m5 printf("*5* franchi.\n")
	#define m6 printf("*6* franchi.\n")
	#define m7 printf("*7* franchi.\n")
	#define m8 printf("*8* franchi.\n")
	#define m9 printf("*9* franchi.\n")
#define kF 0 //booléen FALSE
#define kV 1 //booléen TRUE
#define k1Afficher kV
#define k1Alterner kV
#define k1Areter kV
#define k1Arquer kV
#define k1Biparti kV
#define k1Bipartir kV
#define k1Boucler kV
#define kuByteLim 256
#define kuByteMax (kuByteLim-1)
#define k1Commutatif kV
#define CouleurNom  {"coAlpha  ,coJaune ,coRouge  ,coBleu   ,coVert   ,coOrange ,coViolet,coNoir   ,coOmega "}
#define CouleurType { coAlpha  ,coJaune ,coRouge  ,coBleu   ,coVert   ,coOrange ,coViolet,coNoir   ,coOmega  }
#define k1Creer kV
//Exposants de 10
	#define  kE0 1
	#define  kE1 10
	#define  kE2 100
	#define  kE3 1000
	#define  kE4 10000
	#define  kE5 100000
	#define  kE6 1000000
	#define  kE7 10000000
	#define  kE8 100000000
	#define  kE9 1000000000
	#define kE10 10000000000
	#define kE11 100000000000
	#define kE12 1000000000000
	#define kE13 10000000000000
	#define kE14 100000000000000
	#define kE15 1000000000000000
	#define kE16 10000000000000000
	#define kE17 100000000000000000
	#define kE18 1000000000000000000
	#define kE19 10000000000000000000
	#define kE20 100000000000000000000
	#define kE21 1000000000000000000000
	#define kE22 10000000000000000000000
	#define kE23 100000000000000000000000
	#define kE24 1000000000000000000000000
	#define kE25 10000000000000000000000000
	#define kE26 100000000000000000000000000
	#define kE27 1000000000000000000000000000
	#define kE28 10000000000000000000000000000
	#define kE29 100000000000000000000000000000
	#define kE30 1000000000000000000000000000000
	#define kE31 10000000000000000000000000000000
	#define kE32 100000000000000000000000000000000
#define k1Comparer kV
#define k1Cout kV
#define k1Couleur kV
#define k1Dense kV
#define k1Doublon kV
#define k1Droit kV
#define k1Droite kV
#define k1Elementaire kV
#define k1Empiler kV
#define k1Enfiler kV
#define kdEpsilon 0.00001l
#define k1Feminin kV
#define k1Gauche kV
#define k1General kV
#define k1Incidence kV
#define kuIntegerMax INT_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kxLongintMax LONG_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kiIntegerMin INT_MIN //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define k1Ligne kV
#define kyLongintMin LONG_MIN //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kuMajusculeOffset 1 //A est la 1ère lettre de l'alphabet.
#define k1Maximum kV
#define kuMinusculeOffset 27 //a est la 27ème lettre de l'alphabet à 52 lettres obtenu en complétant les majuscules par les minuscules.
//Puissances de 2
	#define  kP0 1
	#define  kP1 2
	#define  kP2 4
	#define  kP3 8
	#define  kP4 16
	#define  kP5 32
	#define  kP6 64
	#define  kP7 128
	#define  kP8 256
	#define  kP9 512
	#define kP10 1024
	#define kP11 2048
	#define kP12 4096
	#define kP13 8192
	#define kP14 16384
	#define kP15 32768
	#define kP16 65536
	#define kP17 131072
	#define kP18 262144
	#define kP19 524288
	#define kP20 1048576
#define k1Optimal kV
#define k1Optimum kV
#define k1Poids kV
#define k1Ponderer kV
#define kuPremierRgMax 100 //rang1 du dernier nombre premier stocké dans le tableau de nombres premiers uPremieR[] accessible par nPremier().
#define k1Simple kV
#define k1Simplifier kV
#define kuTableauLigneMax kE3
#define k1Tout kV
#define k1Un kV
#define k1Unifier kV
#define k1Unitaire kV
#define k1Verifier kV
#define k1Voir kV
int bBof;//booléen prédéclaré destiné à recevoir une valeur booléenne quelconque 
int iBof;//entier de signe quelconque prédéclaré
int nBof;//entier >=0 prédéclaré
int uBof;//entier >0 prédéclaré
long xBof;//entier long >0 prédéclaré
long yBof;//entier long de signe quelconque prédéclaré
long zBof;//entier long >=0 prédéclaré
float fBof;//float prédéclaré
double dBof;//double prédéclaré
typedef struct{
	int r;//partie réelle
	int i;//partie imaginaire
} ri;
typedef struct{
	int num;//numérateur
	int den;//dénominateur
} q;//ensemble Q des rationnels
//les routines en minuscules ci-dessous cachent les printf(),ajoutent un point final et passent à la ligne;b=booléen, e=entier, r=réel, t=texte.
	void t(char *sTexte);//affiche sTexte.
	void tb(char *sTexte,int bBooleen);//affiche sTexte puis "vrai" ou "faux" selon bBooleen.
	void tc(char *sTexte,char cCaractere);//affiche sTexte puis le cCaractere entre 2 apostrophes.
	void tri(char *sTexte,ri rComplexe);//affiche sTexte puis rComplexe: tri("riA",riA) affiche "eA:2+i" si eA vaut 2+i.
	void te(char *sTexte,long yEntier1);//affiche sTexte puis yEntier1: te("eA",eA) affiche "eA:2" si eA vaut 2.
	void tee(char *sTexte,long yEntier1,long yEntier2);
	void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3);
	void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4);
	void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5);
	void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6);
	void tq(char *sTexte,q qRationnel);
	void tr(char *sTexte,double dReel1);//affiche la valeur de sTexte puis celle du réel dReel1: tr("dA",dA) affiche dA:2.5 si dA vaut 2,5.
	void trr(char *sTexte,double dReel1,double dReel2);
	void trrr(char *sTexte,double dReel1,double dReel2,double dReel3);
	void tt(char *sTexte1,char *sTexte2);//affiche sTexte1 et sTexte2 entre virgules.
	void ttt(char *sTexte1,char *sTexte2,char *sTexte3);
	void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4);
	void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5);
//les routines ci-dessous cachent les fonctions systèmes, gèrent le contexte des appels de routines, les chaîne de caractère et les boucles sans fin
int nAbs(int iEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction abs() du C qui rend une valeur négative
long zAbs(long yEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction labs() du C qui rend une valeur négative
q qAdd(q qA,q qB);//somme de deux nombres rationnels
ri riAdd(ri riA,ri riB);//somme de deux nombres complexes à composantes entières
void Appel0(char *sMessage);//doit toujours être associé à Appel1;à placer en tête de routine (affiche le nom de la routine au début de son exécution)
void Appel1(char *sQuoi);//doit toujours être associé à Appel0;à placer en fin de routine (affiche le nom de la routine à la fin de son exécution)
long yArrondi(double dNombre);
void Assert1(char *sContexte,int bAssertion1);//comme assert() du langage C, mais affiche sContexte si bAssertion1 est faux
void Assert2(char *sContexte,int bAssertion1,int bAssertion2);//comme assert(bAssertion1 && bAssertion2);affiche sContexte si une assertion est fausse.
void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3);
void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
int bBit(char cCaractere);//rend vrai ssi cCaractere est '0' ou '1'.
int bBool(long yEntier);//rend vrai ssi yEntier vaut 0 ou 1.
char *sBool(long yValeur);//rend "faux" si yValeur est nul, et "vrai" sinon.
int iBorner(int iBorneInf,int iValeur,int iBorneSup);//rend iValeur si iBorneInf≤iValeur≤iBorneSup, ou la borne la plus proche de iValeur
long yBorner(long yBorneInf,long yValeur,long yBorneSup);//rend yValeur si yBorneInf≤yValeur≤yBorneSup, ou la borne la plus proche de yValeur
int bByte(long yEntier);//0 ≤ yEntier ≤ 255.
char *sC(char cImprimableOuEspace);//convertit un char en string.
char *sC1(char *sNonNull);//vérifie sNonNull!=NULL puis rend sNonNull.
char *sC1p(char *sA);//complète sA par un point terminal.
char *sC2(char *sA,char *sB);
char *sC2b(char *sA,char *sB);//concatène en ajoutant un blanc entre sA et sB.
char *sC2bp(char *sA,char *sB);//blanc entre sA et sB et point terminal.
char *sC2p(char *sA,char *sB);//point terminal.
char *sC2v(char *sA,char *sB);//concatène en ajoutant une virgule entre sA et sB.
char *sC3(char *sA,char *sB,char *sC);
char *sC3b(char *sA,char *sB,char *sC);
char *sC3bp(char *sA,char *sB,char *sC);
char *sC3p(char *sA,char *sB,char *sC);
char *sC3v(char *sA,char *sB,char *sC);
char *sC4(char *sA,char *sB,char *sC,char *sD);
char *sC4b(char *sA,char *sB,char *sC,char *sD);
char *sC4bp(char *sA,char *sB,char *sC,char *sD);
char *sC4p(char *sA,char *sB,char *sC,char *sD);
char *sC4v(char *sA,char *sB,char *sC,char *sD);
char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC9(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI);
char *sC9b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI);
char *sC9bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI);
char *sC9p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH,char *sI);
int nCaractere(char *sTexte);//rend le nombre de caractères (1 pour "é") contrairement à strlen() qui rend le nombre de CODES caractères (2 pour "é"). 
int nCarreh(int iValeur);
int nCas16(int bA,int bB,int bC,int bD);//rend 8*bA+4*bB+2*bC+bD,dc ds 0..15.
int nCas4(int bA,int bB);//rend 2*bA+bB,dc ds 0..3.
int nCas8(int bA,int bB,int bC);//rend 4*bA+2*bB+bC,dc ds 0..7.
char *sChaine(char cCaractere);//convertit cCaractere en char *; synonyme de sC()
char *sChaine0(char *sTexte,int nLargeurHorsTout);//rend les nLargeurHorsTout premiers caractères de sTexte
char *sChaine1(char *sTexte,int nLargeurHorsTout);//rend les nLargeurHorsTout derniers caractères de sTexte
char *sChaine2(char *sTexte,int nLargeurHorsTout);//rend sTexte centré dans nLargeurHorsTout caractères
void ChaineGarnir(char cImprimable);//change le caractère de remplissage utilisé dans les routines sChaine0,sChaine1 et sChaine2.
int bChaineEgale(char *sA,char *sB);
char *sChaineEtale(char *sChaine);//interpose 1 blanc entre 2 caractères consécutifs de sChaine
char *sChaineEtale2(char *sChaine);//interpose 2 blancs entre 2 caractères consécutifs de sChaine
char *sChaineEtaler(char *sChaine,int nEspaceEntreCaractere);//interpose nEspaceEntreCaractere blancs entre 2 caractères consécutifs de sChaine
int nChaineLg(char *sTexte);//strlen(sTexte) dans [0..kuIntegerMax]
char *sChainon(char *sChaine,int nDebutInclus,int nFinIncluse);//rend sChaine[nDebutInclus,nFinIncluse],ou une chaîne vide si non défini
int mChainePos(char cQuoi,char *sDansQuoi);//rend le rang0, c'est-à-dire la position en commençant par 0, de cQuoi dans sDansQuoi;rend -1 si échec.
int bChiffre(char cCaractere);//'0'..'9',comme bDecit
char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative);//cf (bOptionSinonAlternative)? sOption: sAlternative
char *sChoix0(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide
int nChrono(int bDemarrer);//pr chronométrer une exécution,l'encadrer avec nT=nChrono(kV) et nT=nChrono(kF); nT final donne la durée de l'exécution.
long zChrono(int bDemarrer);//pr chronométrer une exécution,l'encadrer avec zT=zChrono(kV) et zT=nChrono(kF); zT final donne la durée de l'exécution.
long zCnp(int nN,int nP);//nombre de combinaisons de nN éléments pris par paquets de nP éléments. 
void Confirmer(char *sMessage);//affiche sMessage et demande à l'utilisateur de valider
char *sCouple(long yEntierA,long yEntierB);//eg "(3,5)" 
char *sCrochet(long yEntierA,long yEntierB);//eg "[3,5]" 
char *sCrochet1(long yEntier);//eg "[3]" 
char *sCrochet2(long yEntierA,long yEntierB);//eg "[3,5]" ,comme sCrochet
char *sCrochet3(long yEntierA,long yEntierB,long yEntierC);//eg "[3,5,7]" 
void Croissant(double dMinInclus,double dDedans,double dMaxInclus);//vérifie dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissant(double dMinInclus,double dDedans,double dMaxInclus);//rend vrai ssi dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);//vérifie dMinInclus < dDedans < dMaxInclus
void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);
int bCroit(long yMinInclus,long yDedans,long yMaxInclus);//évalue et rend yMinInclus ≤ yDedans ≤ yMaxInclus
int bCroit4(long yA,long yB,long yC,long yD);//rend yA≤yB≤yC<=yD
int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu);//évalue et rend yMinInclus < yDedans < yMaxInclus
int iCube(int iValeur);//rend iValeur**3
int bDans2(int iQuoi,int iValeurA,int iValeurB);//iQuoi est iValeurA ou iValeurB
int bDans3(int iQuoi,int iValeurA,int iValeurB,int iValeurC);
int bDans4(int iQuoi,int iValeurA,int iValeurB,int iValeurC,int iValeurD);
char *sDateEnClair(int nQuantieme,int nMois,int nAnnee);//années 1900 à 2100
int bDecit(char cCaractere);//alias bChiffre
char *sDire(int bAffirmation,char *sVerbePuisBlancPuisQqch);//rend sVerbePuisBlancPuisQqch,ou nié si bAffirmation fausse: sDire(0,"est vrai")="n'est pas vrai".
int bDistinct3(long yA,long yB,long yC);
int bDistinct4(long yA,long yB,long yC,long yD);
q qDiv(q qA,q qB);//division qA/qB des deux rationnels
char *sDiv(int nNumerateur,int nDenominateur);//rend la division de nNumerateur/nDenominateur avec 2 décimales.
char *sDomaine(long yEntierA,long yEntierB);//rend [yEntierA..yEntierB]
char *sE(int nEspace);//rend nEspace blancs consécutifs
int bEgal3(long yA,long yB,long yC);//tous égaux
char *sEnt(long yEntier);
char *sEnt3(long yEntier,int nCaractere);//rend les décits groupés par paquets de 3, le tout cadré à droite sur nCaractere caractères.
char *sEntier(long yEntier,int nCaractere);//résultat sur nCaractere caractères:sEntier("24,3)=" 24".
char *sEntier0(long yEntier,int nCaractere);//résultat sur nCaractere caractères:sEntier("24,3)="024".
char *sEntier1(long yEntier,int nCaractere);//résultat centré dans une zone de nCaractere caractères:sEntier("24,5)="  24 ".
char *sEntier2(long yEntier);//résultat sur 2 caractères.
char *sEntier3(long yEntier);//résultat sur 3 caractères.
char *sEntierAvecSigne(long yEntier);// "+5" ou "-5" ou " 0".
void EntierDepiler(int *piA);
void EntierDepiler2(int *piA,int *piB);//dépile d'abord piA
void EntierDepiler3(int *piA,int *piB,int *piC);
void EntierDepiler4(int *piA,int *piB,int *piC,int *piD);
void EntierDepilerTout();
void EntierEchanger(int *piA,int *piB);
void EntierEmpiler(int iA);
void EntierEmpiler2(int iA,int iB);
void EntierEmpiler3(int iA,int iB,int iC);
void EntierEmpiler4(int iA,int iB,int iC,int iD);
int nEntierEnTout();
void EntierEchanger(int *piA,int *piB);
void EntyerEchanger(long *pyA,long *pyB);
char *sEst(int bAssertion);//rend "est" ou "n'est pas".
long zFact(int nN);//rend la factorielle de l'entier positif ou nul nN
int bFaux(int iEntier);//vrai ssi iEntier==0.
long zFib(int nIndex);//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0.
void FlipFlop(char* sContexte,int bApres,int *pbAvant);// "pb"="pointeur sur booléen";si bApres≠pbAvant,mémorise bApres dans pbAvant; sinon,déroute.
//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont R(true,…),R(false,…),R(true,…),R(false,…),etc.
char *sFois(int nFois,char cMotif);//rend cMotif juxtaposé nFois.
int bFrontiere8(long zSizeOf);//ySizeOf est un multiple de 8
char *sG(char* sTexte);//rend sTexte entre guillemets.
int nHasard(int uBorneLim);//rend un entier pseudo-aléatoire dans [0..uBorneLim[, donc borne supérieure exclue.
int uHasard(int uBorneMax);//rend un entier pseudo-aléatoire dans [1..uBorneMax], donc borne supérieure incluse.
void HasardInit(int iGerme);//si iGerme non nul,réinitialise la suite de nombres pseudo-aléatoires;sinon,ne fait rien.
int bImpair(int iEntier);
int bInteger(long yEntier);
double rInf(double dA,double dB);//inf(dA,dB).
int iInf(int iA,int iB);//identique à iMin(iA,iB).
int iInf3(int iA,int iB,int iC);
long yInf(long yA,long yB);//identique à iMin(iA,iB).
long yInf3(long yA,long yB,long yC);
q qInv(q qA);//inverse du rationnel qA
int nItem(char *sItemVirguleItemVirguleItem);//nItem(alpha,b,c)=3;nItem(a)=1;nItem(a,,c)=3.nItem(,a,)=1.nItem(,a)=1.nItem(a,)=1.nItem()=1.
char *sItem(char *sItemVirguleItemVirguleItem,int uItemRang);//sItem("a,b,c",1)="a". sItem("a,b,c",5)="". sItem("a,,c",2)="".
char *sItem4(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4);//rend l'item de numéro uItem>0 ou une chaîne vide si non défini
char *sItem8(int uItem,char* sItem1,char* sItem2,char* sItem3,char* sItem4,char* sItem5,char* sItem6,char* sItem7,char* sItem8);
int nItemRang(char *sQuoi,char *sItemVirguleItemVirguleItem);//nItemRang("deux","un,deux,trois")=2. Rend 0 si sQuoi n'est pas un item.
char *sK(ri rComplexe);
int nJourSemaine(int nQuantieme,int nMois,int nAnnee);
int bLettre(char cCaractere);
char cLettre(int nLettre);//donne le caractère de rang nLettre: "A" pour 1,"B" pour 2, etc, "a" pour 27, etc.
int nLettre(char cCaractere);//donne le rang 1 de cCaractere: 1 pour "A",2 pour "B", etc, 27 pour "a", etc.
void Ligne();//passe à la ligne.
int bLigne();//passe à la ligne et rend vrai.
int bLigne1(char *sLigneFin);//affiche sLigneFin, ajoute un point, passe à la ligne et rend vrai.
double rLog(double dN);//logarithme népérien;rend par exemple 1.0 pour rLog(2.718).
int nLog10(long yValeur);//nombre de bits requis pour coder iValeur en base 10.
int nLog2(long yValeur);//nombre de bits requis pour coder iValeur en complément à 2.
double rLog2(double dN);//logarithme en base 2;rend par exemple 4.0 pour rLog2(16).
int iMax(int iA,int iB);//sup(iA,iB).
double rMax(double dA,double dB);//sup(dA,ddB).
long yMax(long yA,long yB);//sup(yA,yB).
void MemIntRaz(int piMemOrigine[],int nItemEnTout);
void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur);
void MemLongRaz(int pyMemOrigine[],int nItemEnTout);
void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur);
int bMajuscule(char cCaractere);
char *sMajuscule(char* sCaractere);//rend la majuscule qui correspond à sCaractere 
int iMin(int iA,int iB);//inf(iA,iB).
double rMin(double dA,double dB);//inf(dA,dB).
long yMin(long yA,long yB);//inf(yA,yB).
int bMinuscule(char cCaractere);
char *sMinuscule(char *sCaractere);//rend la minuscule qui correspond à sCaractere 
int nModulo(int iDividende,int uDiviseur);//résultat dans [0..uDiviseur[
int uModulo1(int nDividende,int uDiviseur);//résultat dans [1..uDiviseur];calcule un modulo classique puis remplace le résultat éventuel 0 par uDiviseur.
q qMul(q qA,q qB);//produit de deux rationnels
ri riMul(ri riA,ri riB);//produit de deux nombres complexes à composantes entières
int bNul(double dNombre);//dNombre est très proche de zéro
q qOpp(q qA);//opposé du rationnel qA
ri riOpp(ri riA);//opposé d'un complexe
char *sOui(int bOui);//rend "oui" ou "non" selon bOui.
void OutilAMORCER();
void OutilINITIALISER();
void OutilTESTER(int iTest);
char *sP(char *sEntreParenthese);//rend sEntreParenthese entre 2 parenthèses,eg sP("oui") rend "(oui)".
int bPair(int iEntier);
char *sPar3(long yEntier);//convertit yEntier en chaîne en groupant les chiffres par 3, eg sPar3(12345) rend "12 345".
char *sPas(char *sVerbe,int bNegativer);//encadre avec "ne" et "pas" si bNegativer.
void Pause();//suspend l'exécution et attend une frappe clavier minimale.
long zPgcd(long xA,long xB);//plus grand commun diviseur.
char *sPhrase(char *sTexte);//rend sTexte avec 1ère lettre majusculée et point final
char *sPluriel(long zEffectif,char *sSingulier);//sPluriel(3,"fruit") rend "3 fruits" et sPluriel(3,"fruit$ rouge$") rend "3 fruits rouges".
char *sPluriel0(long zEffectif,char *sSingulier,int bFeminin);//idem sPluriel mais "0" est convertit en "aucun" ou "aucune"
long zPpcm(long xA,long xB);//plus petit commun multiple.
int mPoidsFort(long yEntier);//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2.
int bPremier(int iNombre);//vrai ssi iNombre est un nombre premier
int nPremier(int nRangDuNombrePremier);//rend le nombre premier de rang1 nRangDuNombrePremier,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
int bPrint(char *sPrint);//affiche sPrint suivi de "\n" et rend faux
int bPrint0(char *sPrint);//affiche sPrint et rend faux
int bPuissanceDe2(long yOperande);//yOperande est une puissance de 2 entière positive inférieure à kxLongintMax/2.
long zPuissance(long yOperande,int nExposant);//nExposant positif ou nul.
char *sQ(q qRationnel);
int nRac(int nEntier);//plus grand entier inférieur ou égal à la racine carrée de nEntier
char *sReel(float fReel);
char cSigne(long yEntier);//"+" ou "-" ou " " selon le signe de yEntier ("+" pour yEntier=0).
char *sSigne(long yEntier);//"positif" ou "négatif" ou "nul" selon le signe de yEntier.
int tSigne(int iValeur);//rend +1 si iValeur>0,-1 si iValeur<0, et 0 sinon.
int iSignePres(int bSigneInverser,int iValeur);//si bSigneInverser est vrai,rend -iValeur;sinon,rend +iValeur.
long ySignePres(int bSigneInverser,long yValeur);//si bSigneInverser est vrai,rend -yValeur;sinon,rend +yValeur.
void Stop(int byMassacre);//sortie catastrophe;affiche byMassacre compris entre 0 et 255 puis stoppe l'exécution.
q qSub(q qA,q qB);//différence de deux rationnels
ri riSub(ri riA,ri riB);//différence de deux nombres complexes à composantes entières
char *sSucces(int bSuccesSinonEchec);//rend "succès" ou "échec"
int iSup(int iA,int iB);//max(iA,iB).
int iSup3(int iA,int iB,int iC);
double rSup(double dA,double dB);//identique à rMax(dA,dB).
long ySup(long yA,long yB);//identique à yMax(yA,yB).
char *sTab(int nIndentation);//rend 4*nIndentation blancs consécutifs
void TableauVoir(char *sNom,int iQuelTableau[kuTableauLigneMax][kuTableauLigneMax],int nIndexMin1,int nIndexMax1,int nIndexMin2,int nIndexMax2);
void Titrer(char *sTitre);//affiche sTitre centré sur une ligne de 100 caractères de large et passe à la ligne.
void Titrer2(char *sTitre,char cMotif);//idem mais le caractère répété de part et d'autre du titre est cMotif
int bTrit(int tVariable);//vrai ssi tVariable est un trit à valeur dans {-1,0,+1}
char *sUn(char *sVerbe,int bUn);//si bUn,rend sVerbe suivi de "un";sinon,encadre sVerbe avec "ne" et "aucun".
char *sUnOuUne(char *sVerbe,int bUn,int bFeminin);//si bUn,rend sVerbe suivi de "un" ou "une";sinon,encadre sVerbe avec "ne" et "aucun" ou "aucune".
char *sUne(char *sVerbe,int bUne);//si bUne,rend sVerbe suivi de "une";sinon,encadre sVerbe avec "ne" et "aucune".
int bVecteurContient(int nEnquis,int iVecteur[]);//vrai ssi nEnquis est dans iVecteur[1..iVecteur[0]]
int mVecteurContient(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax);//rend le rang de nEnquis dans iVecteur[nIndexMin..nIndexMax],ou -1 si absent
int bVecteurContient1(int nEnquis,int nCardinal,int iVecteur[]);//vrai ssi nEnquis est dans iVecteur[1..nCardinal]
void VecteurCopier(int iVecteurA[],int nIndexMin,int nIndexMax,int iVecteurB[]);
int nVecteurDoublet(int iVecteur[],int nIndexMin,int nIndexMax);//nb de paires d'éléments consécutifs qui sont égaux
int nVecteurDoublon(int iVecteur[],int nIndexMin,int nIndexMax);//au moins 2 éléments de iVecteur[nIndexMin..nIndexMax] sont égaux
int nVecteurEcreter(int iVecteur[],int nIndexMin,int nIndexMax,int iPlancherMin,int iPlafondMax);
int bVecteurEgal(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax);//les vecteurs sont identiques dans [nIndexMin..nIndexMax]
void VecteurInitialiser(int iVecteur[],int nIndexMin,int nIndexMax,int iValeurInitiale);
long yVecteurInf(int iVecteur[],int nIndexMin,int nIndexMax);
int bVecteurNul(int iVecteur[],int nIndexMin,int nIndexMax);
int nVecteurOccurrence(int nEnquis,int iVecteur[],int nIndexMin,int nIndexMax);//nombre d'occurrences de nEnquis dans iVecteur[nIndexMin..nIndexMax] 
int nVecteurOccurrenceMax(int iVecteur[],int nIndexMin,int nIndexMax);//nombre d'occurrences maximal d'un élément de iVecteur[nIndexMin..nIndexMax] 
void VecteurRazer(int iVecteur[],int nIndexMin,int nIndexMax);//iVecteur[nIndexMin..nIndexMax]=0
int bVecteurSemblable(int iVecteurA[],int iVecteurB[],int nIndexMin,int nIndexMax);//iVecteurA = copie désordonnée de iVecteurB
long yVecteurSomme(int iVecteur[],int nIndexMin,int nIndexMax);
long yVecteurSup(int iVecteur[],int nIndexMin,int nIndexMax);
void VecteurTrier(int iQuelVecteur[],int nIndexMin,int nIndexMax);//trie par ordre croissant en O(N*N)
void VecteurTrier2(int iQuelVecteur[],int nIndexMin,int nIndexMax,int nIndex[]);//trie par ordre croissant en O(N*N)
void VecteurTrierVite(int iQuelVecteur[],int nIndexMin,int nIndexMax);//trie par ordre croissant en O(NlogN)
void VecteurValuer(int iVecteur[],int nIndexMin,int nIndexMax,int iValeur);//iVecteur[nIndexMin..nIndexMax]=iValeur
void VecteurVoir(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les valeurs du vecteurs d'entiers de type integer.
void VecteurVoir0(char *sNom,int iQuelVecteur[]);//affiche iQuelVecteur[1..iQuelVecteur[0]]
void VecteurVoir1(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//idem mais les numéros des index sont affichés ligne précédente
void VecteurVoir2(char *sNom,int iQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les doublets (index,iQuelVecteur[index])
int bVekteurContient(long yEnquis,int nCardinal,long yVecteur[]);//vrai ssi yEnquis est dans yVecteur[1..nCardinal]
void VekteurCopier(long yVecteurA[],int nIndexMin,int nIndexMax,long yVecteurB[]);
int bVekteurNul(long yVecteur[],int nIndexMin,int nIndexMax);
void VekteurRazer(long yVecteur[],int nIndexMin,int nIndexMax);
long yVekteurSomme(long yVecteur[],int nIndexMin,int nIndexMax);
void VekteurVoir(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les valeurs du vecteurs d'entiers de type integer.
void VekteurVoir1(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//idem mais les numéros des index sont affichés ligne précédente
void VekteurVoir2(char *sNom,long yQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les doublets (index,yQuelVecteur[index])
void Voir(char *sFormat,...);//affiche tous les paramètres mentionnés dans sFormat,eg Voir("%f,%s %d.\n",3.14,"environ",3).
int bVoyelle(char *sTexte,int nCodeCaractereRg);//vrai ssi sTexte[nCodeCaractereRg] est une voyelle.
int bVrai(int iEntier);//rend 1 ssi iEntier est non nul;rend 0 sinon.
void While(long zIterationMax);//prend note du nombre maximum d'itérations à exécuter dans le while qui suit l'appel de cette routine.
int bWhile(char *sContexte,int bExpressionBooleenne);//rend bExpressionBooleenne après avoir vérifié que l'itération en cours ne dépasse pas zIterationMax spécifié li-1.

