#include "Outil.h"
#include "Alex.h"
#include "Asynt.h"
#include "Erreur.h"
#include "Tds.h"
//Grammaire algébrique LL(1):
	//Programme->Instructions || FinFichier
	//		Instructions->Instruction PointVirgule Programme
	//Instruction->Emprunt || Reservation || Achat || Restitution || Radiation || Autre
	//		Emprunt->"<" LivreOuListeDeLivre Nom 						Liste de livre : (Livre1 Livre2 ... LivreN)
	//		Reservation->"?" Livre Nom 											Livre répertorié et Nom en TDS
	//		Achat->Prix	Livre 															réel>0 et Livre non encore répertorié
	//		Restitution->">" Livre Nom											Livre répertorié et Nom en TDS
	//		Radiation->Nom  																Nom en TDS
	//		Autre->Entier Suite															Entier est une durée>0 pr une Interdiction et une date pr une inscription
	//Suite->Interdiction || Inscription
	//		Interdiction->Livre	 														Livre répertorié
	//		Inscription->Nom 																Nom hors TDS
	//LivreOuListeDeLivre -> Livre || ListeDeLivre
	//		ListeDeLivre -> "(" && Liste
	//		Liste -> Livre && Suite
	//		Suite -> ")" || Liste

enum  eGrammaireRegle {grAlpha,grProgramme,grInstructions,grInstruction,grEmprunt,grReservation,grAchat,grRestitution,grRadiation,grAutre,grSuite,grInterdiction,grInscription,grOmega};
char *sGrammaireReglE="grAlpha,grProgramme,grInstructions,grInstruction,grEmprunt,grReservation,grAchat,grRestitution,grRadiation,grAutre,grSuite,grInterdiction,grInscription,grOmega";

#define bEclaireR kF
#define kbVoiR kV
int nAPPEL;//nombre total d'appels associés aux règles terminales de la grammaire,ie bAlexIdentificateur(), etc
int bAsyntAmorceR;
int mAsyntAnalyseR;
int bkEclaireuR;
char cNoM;

void ErreR(int eErreurNumero,int iDebut);

int bAchaT(int iDebut,int *piFin);
int bAutrE(int iDebut,int *piFin);
int bEmprunT(int iDebut,int *piFin);
int bFinFichieR(int iDebut,int *piFin);
int bHorairE(int iDebut,int *piFin);//dédié contrôle sémantique
int bIdentificateuR(int iDebut,int *piFin);
int bInferieurStricT(int iDebut,int *piFin);
int bInstructioN(int iDebut,int *piFin);
int bInstructionS(int iDebut,int *piFin);
int bInterdictioN(int iDebut,int *piFin);
int bInterrogatioN(int iDebut,int *piFin);
int bLivrE(int iDebut,int *piFin);
int bLivreOuListeDeLivrE(int iDebut, int * piFin);
int bListeDeLivre(int iDebut, int *piFin);
int bNoM(int iDebut,int *piFin);
int bOperateuR(char cOperateur,int iDebut,int *piFin);
int bParenthese(char cParenthese,int iDebut,int *piFin);
int bPriX(int iDebut,int *piFin);
int bProgrammE(int iDebut,int *piFin);
int bRadiatioN(int iDebut,int *piFin);
int bReeL(int iDebut,int *piFin);
int bReservatioN(int iDebut,int *piFin);
int bRestitutioN(int iDebut,int *piFin);
int bSeparateuR(int iDebut,int *piFin);
int bSuitE(int iDebut,int *piFin);
int bSuiteDeLivrE(int iDebut, int * piFin);
int bAlexParenthese(int uLexeme, char cParenthese);
int bSuperieurStricT(int iDebut,int *piFin);
int bTextE(int iDebut,int *piFin);

void ErreR(int eErreurNumero,int iDebut){
	//empile  l'erreur eErreurNumero ssi le mode correspondant à eErreurNumero est actif
	if (mAsyntAnalyseR==mAsyntSyntaxe && bCroitStrict(eSynt0,eErreurNumero,eSynt1) )
		ErreurEmpiler(eErreurNumero,iDebut);
	if (mAsyntAnalyseR==mAsyntSemantique && bCroitStrict(eSem0,eErreurNumero,eSem1) )
		ErreurEmpiler(eErreurNumero,iDebut);
}//ErreR

void ErrerSouS(int bSucces,int eErreurNumero,int iDebut){
	if (!bSucces)
		ErreR(eErreurNumero,iDebut);
}//ErrerSouS

int bAchaT(int iDebut,int *piFin){
	//Achat->Prix Livre
	int bAjouter,bSucces,iFin,iMilieu,nItem;
	char *sLivre;
	//Appel0("bAchaT");
		bSucces=bPriX(iDebut,&iMilieu) && bLivrE(iMilieu,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sLivre=sAlexChaine(iMilieu);
			bAjouter=bTdsAjouter(cNoM,sLivre);
			Assert1("bAchaT",bAjouter);
			if ( bTdsContient(cNoM,sLivre,&nItem) )
				TdsValuer(cNoM,nItem,0);//indique que ce livre est disponible.

		}
		nAPPEL++;
	//Appel1("bAchaT");
	return(bSucces);
}//bAchaT

void AsyntAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bkEclaireuR=kF;
	bAsyntAmorceR=kV;
}//AsyntAMORCER

int bAsyntAnalyser(int amMode){
	int bAnalyser;
	int iFin;
	//Appel0(sC2b("bAsyntAnalyser en mode analyse",sChoix(mAsyntAnalyseR==amMode,"syntaxique","sémantique")));
		bkEclaireuR=kF;
		mAsyntAnalyseR=amMode;
		if (mAsyntAnalyseR==mAsyntSyntaxe){
			bAnalyser=1 || bTdsAllouer(kV,&cNoM);
			bAnalyser=bAnalyser && bProgrammE(1,&iFin) && (nErreurEnTout()==0);
			te("Appels de règles",nAPPEL);
			if (bAnalyser && mAsyntAnalyseR==mAsyntSemantique){
				TdsVoir(cNoM,"TDS après analyse sémantique");
			bBof=bTdsAllouer(kF,&cNoM);
			}else if(bAnalyser && mAsyntAnalyseR==mAsyntSyntaxe){
				bProgrammE(1,&iFin) && (nErreurEnTout()==0);
				printf("Nombre d'appel = %i",nAPPEL);
			}
		}
	//Appel1(sC2b("bAsyntAnalyser en mode analyse",sChoix(mAsyntAnalyseR==amMode,"syntaxique","sémantique")));
	return(bAnalyser);
}//bAsyntAnalyser

void AsyntINITIALISER(){//O(?)
	//relance le présent module
	Assert1("AsyntINITIALISER",bAsyntAmorceR);
}//AsyntINITIALISER

void AsyntTESTER(int iTest){
	//teste le présent module
	int bAnalyser=kF;
	int iFin;
	Appel0(sC2("AsyntTESTER,test n°",sEnt(iTest)));
		nAPPEL=0;
		bkEclaireuR=kV;
		switch (iTest) {
			case  1:	bkEclaireuR=kF;bAnalyser=bProgrammE(1,&iFin);break;
			case  2:	bkEclaireuR=kV;bAnalyser=bProgrammE(1,&iFin);break;
			default:break;
		}
		printf("%s de l'analyse syntaxique après %s.\n",(bAnalyser)? "Succès":"Echec",sPluriel(nAPPEL,"appel"));
	Appel1(sC2("AsyntTESTER,test n°",sEnt(iTest)));
}//AsyntTESTER

int bAutrE(int iDebut,int *piFin){
	//Autre->Entier Suite
	int bSucces,iFin;
	//Appel0("bAutrE");
		bSucces=bAlexEntier(iDebut) && m1 && bSuitE(iDebut+1,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		nAPPEL++;
	//Appel1("bAutrE");
	return(bSucces);
}//bAutrE

int bDatatioN(int iDebut,int *piFin){
	//Datation->Horaire
	int bSucces,iFin;
	//Appel0("bDatatioN");
		bSucces=bReeL(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//tb("bSucces",bSucces);
		nAPPEL++;
	//Appel1("bDatatioN");
	return(bSucces);
}//bDatatioN

int bEmprunT(int iDebut,int *piFin){
	//Emprunt->"<" Livre Nom
	int bConnu,bEmprunteurInscrit,iValeur,bSucces,iFin,iMilieu,iSuivant,nItem;
	char *sLivre;
	//Appel0("bEmprunT");
		bSucces=bInferieurStricT(iDebut,&iMilieu) && bLivreOuListeDeLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){//Livre répertorié et Nom inscrit
			//TdsVoir("avant emprunt");
				sLivre=sAlexChaine(iMilieu);
				bConnu=bTdsPresent(cNoM,sLivre,&iValeur);
				if (bConnu){//répertorié = connu ET disponible
					//te("iValeur",iValeur);
					if (iValeur){
						bEmprunteurInscrit=bTdsContient(cNoM,sAlexChaine(iSuivant),&iBof);
						if (!bEmprunteurInscrit)
							ErreR(eSemNonInscrit,iSuivant);
						else if ( bTdsContient(cNoM,sLivre,&nItem) )
							TdsValuer(cNoM,nItem,30);//ie sLivre est emprunté pour une durée de 30 jours maximum.
					} else ErreR(eSemLivrePris,iMilieu);
				}else ErreR(eSemLivreInconnu,iMilieu);
			//TdsVoir("après emprunt");
		}
		*piFin=(bSucces)? iFin:iDebut;
		nAPPEL++;
	//Appel1("bEmprunT");
	return(bSucces);
}//bEmprunT

int bEntieR(int iDebut,int *piFin){
	int bSucces;
	//Appel0("bEntieR");
		bSucces=bAlexEntier(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		//tee("bEntieR debut et fin",iDebut,*piFin);
		nAPPEL++;
	//Appel1("bEntieR");
	return(bSucces);
}//bEntieR

int bFinFichieR(int iDebut,int *piFin){
	int bSucces;
	//Appel0("bFinFichieR");
		bSucces=bAlexFinFichier(iDebut);
		*piFin=(bSucces)? iDebut+1:iDebut;
		//te("bFinFichieR",iDebut);
	//Appel1("bFinFichieR");
	nAPPEL++;
	return(bSucces);
}//bFinFichieR

int bHorairE(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexReel(iDebut);
	if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
		if (!bAlexHoraire(iDebut))
			ErreR(eSemHoraire,iDebut);
	}
	*piFin=(bSucces)? iDebut+1:iDebut;
	nAPPEL++;
	return(bSucces);
}//bHoraire

int bIdentificateuR(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexIdentificateur(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bIdentificateuR",iDebut);
	nAPPEL++;
	return(bSucces);
}//bIdentificateuR

int bInferieurStricT(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexOperateur(iDebut,'<');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bInferieurStricT",iDebut);
	nAPPEL++;
	return(bSucces);
}//bInferieurStricT

int bInscriptioN(int iDebut,int *piFin){
	//Inscription->Nom
	int bAjouter,nDate,bSucces,iFin,nItem;
	char *sNom;
	//Appel0("bInscriptioN");
	bSucces=bNoM(iDebut,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
		sNom=sAlexChaine(iDebut);//nom de la personne qui s'inscrit
		nDate=nAlexEntier(iDebut-1);//date d'inscription
		bAjouter=bTdsAjouter(cNoM,sNom);
		if (!bAjouter)//puisque la TDS ne déborde pas,il n'y a qu'une explication:le…
			ErreR(eSemInscrit,iDebut);//…sNom en question est déjà en TDS,donc la personne est déjà inscrite
		else if (bTdsContient(cNoM,sNom,&nItem))
			TdsValuer(cNoM,nItem,nAlexEntier(iDebut-1));
		if (!bAlexDate(iDebut-1))
			ErreR(eSemDate,iDebut-1);
		//te("nItem",nItem);
	}
	//te("bInscriptioN",iDebut);
	//Appel1("bInscriptioN");
	nAPPEL++;
	return(bSucces);
}//bInscriptioN

int bInstructioN(int iDebut,int *piFin){
	//Instruction->Emprunt || Reservation || Achat || Restitution || Radiation || Autre
	int nChoix6,bSucces=kF,iFin=0;
	Assert1("bInstructioN0",iDebut>0);
	if (bkEclaireuR){
		nChoix6=nAlexInstruction(iDebut);//pré-vision instruction courante: 1 si Emprunt, 2 si Reservation, etc, et 0 si échec.
		if (bEclaireR) tee("iDebut et nChoix6 pr bInstructioN",iDebut,nChoix6);
		switch(nChoix6){
			case  1:	bSucces=bEmprunT(iDebut,&iFin);break;
			case  2:	bSucces=bReservatioN(iDebut,&iFin);break;
			case  3:	bSucces=bAchaT(iDebut,&iFin);break;
			case  4:	bSucces=bRestitutioN(iDebut,&iFin);break;
			case  5:	bSucces=bRadiatioN(iDebut,&iFin);break;
			case  6:	bSucces=bAutrE(iDebut,&iFin);break;
			default:	ErreR(eSyntInstruction,iDebut);break;
		}
	}
	else bSucces=bEmprunT(iDebut,&iFin) || bReservatioN(iDebut,&iFin) || bAchaT(iDebut,&iFin) || bRestitutioN(iDebut,&iFin) || bRadiatioN(iDebut,&iFin) || bAutrE(iDebut,&iFin);
	if (bSucces) m4;
	*piFin=(bSucces)? iFin:iDebut;
	Assert1("bInstructioN1",*piFin>0);
	nAPPEL++;
	return(bSucces);
}//bInstructioN

int bInstructionS(int iDebut,int *piFin){
	//Instructions->Instruction.Programme
	int bSucces,iFin,iMilieu,iSuivant;
	bSucces=bInstructioN(iDebut,&iMilieu) && bSeparateuR(iMilieu,&iSuivant) && bProgrammE(iSuivant,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	nAPPEL++;
	return(bSucces);
}//bInstructionS

int bInterdictioN(int iDebut,int *piFin){
	//Interdiction->Livre
	int nDuree,bSucces,iFin,nItem;
	char *sLivre;
	//Appel0("bInterdictioN");
		bSucces=bLivrE(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		//te("bInterdictioN",iDebut);
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			sLivre=sAlexChaine(iDebut);
			nDuree=nAlexEntier(iDebut-1);//durée en jours de l'interdiction (pour cause de réparation ou autre) de l'accès au livre
			if (bTdsContient(cNoM,sLivre,&nItem))
				TdsValuer(cNoM,nItem,nDuree);
			else ErreR(eSemLivreInconnu,iDebut);
			//te("nItem",nItem);
			TdsVoir(cNoM,"après interdiction");
		}
		nAPPEL++;
	//Appel1("bInterdictioN");
	return(bSucces);
}//bInterdictioN

int bInterrogatioN(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexOperateur(iDebut,'?');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bInterrogatioN",iDebut);
	nAPPEL++;
	return(bSucces);
}//bInterrogatioN

int bListe(int iDebut, int *piFin){
	// Liste -> Livre && Suite
	int bSucces,iFin,iSuivant;
	bSucces = bLivrE(iDebut,&iSuivant) && bSuiteDeLivrE(iSuivant,&iFin);
	*piFin = (bSucces)? iFin:iDebut;
	nAPPEL++;
	return bSucces;
}

int bListeDeLivre(int iDebut, int *piFin){
	//ListeDeLivre -> "(" && Liste
	int bSucces,iFin, iSuivant;
	bSucces = bParenthese('(',iDebut,&iSuivant) && bListe(iSuivant,&iFin);
	*piFin = (bSucces)? iFin:iDebut;
	nAPPEL++;
	return bSucces;
}

int bLivrE(int iDebut,int *piFin){
	//Livre->Texte
	int bSucces,iFin;
	//Appel0("bLivrE");
	bSucces=bTextE(iDebut,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	//Appel1("bLivrE");
	nAPPEL++;
	ErrerSouS(bSucces,eSyntLivre,iDebut);
	return(bSucces);
}//bLivrE

int bLivreOuListeDeLivrE(int iDebut, int * piFin){
	//LivreOuListeDeLivre -> Livre || ListeDeLivre
	int bSucces,iFin;
	bSucces = bLivrE(iDebut,&iFin) || bListeDeLivre(iDebut,&iFin);
	*piFin = (bSucces)? iFin:iDebut;
	nAPPEL++;
	return (bSucces);
}

int bNoM(int iDebut,int *piFin){
	//Nom->Identificateur
	int bSucces,iFin;
	//Appel0("bNoM");
		bSucces=bIdentificateuR(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		nAPPEL++;
		ErrerSouS(bSucces,eSyntNom,iDebut);
	//Appel1("bNoM");
	return(bSucces);
}//bNoM

int bOperateuR(char cOperateur,int iDebut,int *piFin){
	//Operateur->cOperateur
	int bSucces;
	//Appel0("bOperateuR");
		bSucces=bAlexOperateur(iDebut,cOperateur);
		*piFin=(bSucces)? iDebut+1:iDebut;
		nAPPEL++;
	//Appel1("bOperateuR");
	return(bSucces);
}//bOperateuR

int bParenthese(char cParenthese,int iDebut,int *piFin){
	//Operateur->cOperateur
	int bSucces;
	//Appel0("bOperateuR");
		bSucces=bAlexParenthese(iDebut,cParenthese);
		*piFin=(bSucces)? iDebut+1:iDebut;
		nAPPEL++;
	//Appel1("bOperateuR");
	return(bSucces);
}//bOperateuR

int bPriX(int iDebut,int *piFin){
	//Prix->Reel
	int bSucces,iFin;
	//Appel0("bPriX");
		bSucces=bReeL(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique && fAlexReel(iDebut)<=0.0)
			ErreR(eSemPrix,iDebut);
		nAPPEL++;
	//Appel1("bPriX");
	return(bSucces);
}//bPriX

int bProgrammE(int iDebut,int *piFin){
	//Programme->Instructions || FinFichier
	int bSucces,iFin,nChoix2;
	//Appel0("bProgrammE");
		//te("bProgrammE:iDebut",iDebut);
		if (bkEclaireuR){
			if (bEclaireR) te("iDebut pr bProgrammE",iDebut);
			nChoix2=nAlexProgramme(iDebut);
			if (bEclaireR) tee("iDebut et nChoix2 pr bProgrammE",iDebut,nChoix2);
			switch(nChoix2){
				case 1:	bSucces=bInstructionS(iDebut,&iFin);break;
				case 2:	bSucces=bFinFichieR(iDebut,&iFin);break;
				default:ErreR(eSyntProgramme,iDebut);break;
			};
		}else bSucces=bInstructionS(iDebut,&iFin) || bFinFichieR(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		nAPPEL++;
	//Appel1("bProgrammE");
	return(bSucces);
}//bProgrammE

int bRadiatioN(int iDebut,int *piFin){
	//Radiation->Nom
	int bSucces,iFin,nItem;
	char *sNom;
	//Appel0("bRadiatioN");
		bSucces=bNoM(iDebut,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant radiation");
			sNom=sAlexChaine(iDebut);
			if (bTdsContient(cNoM,sNom,&nItem))
				TdsValuer(cNoM,nItem,0);
			else ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après radiation");
		}
		nAPPEL++;
	//Appel1("bRadiatioN");
	return(bSucces);
}//bRadiatioN

int bReeL(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexReel(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bReeL",iDebut);
	nAPPEL++;
	return(bSucces);
}//bReeL

int bReservatioN(int iDebut,int *piFin){
	//Reservation->"?" Livre Nom
	int bDefini1,bDefini2,bSucces,iFin,iMilieu,iSuivant,nValeur,nItem1,nItem2;
	char *sLivre,*sNom;
	//Appel0("bReservatioN");
		bSucces=bInterrogatioN(iDebut,&iMilieu) && bLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant réservation");
			sLivre=sAlexChaine(iSuivant);
			bDefini1=bTdsContient(cNoM,sLivre,&nItem1);
			if (!bDefini1)
				ErreR(eSemLivreInconnu,iDebut);
			else if ( bTdsPresent(cNoM,sLivre,&nValeur) )
					if (nValeur==0)
						ErreR(eSemLivreDispo,iDebut);
					else TdsValuer(cNoM,nItem1,0);
			sNom=sAlexChaine(iSuivant);
			bDefini2=bTdsContient(cNoM,sNom,&nItem2);
			if (!bDefini2)
				ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après réservation");
		}
		nAPPEL++;
	//Appel1("bReservatioN");
	return(bSucces);
}//bReservatioN

int bRestitutioN(int iDebut,int *piFin){
	//Restitution->">" Livre Nom
	int bDefini1,bDefini2,bSucces,iFin,iMilieu,iSuivant,nItem1,nItem2;
	char *sNom,*sLivre;
	//Appel0("bRestitutioN");
		bSucces=bSuperieurStricT(iDebut,&iMilieu) && bLivrE(iMilieu,&iSuivant) && bNoM(iSuivant,&iFin);
		*piFin=(bSucces)? iFin:iDebut;
		if (bSucces && mAsyntAnalyseR==mAsyntSemantique){
			//TdsVoir("avant restitution");
			sLivre=sAlexChaine(iMilieu);
			bDefini1=bTdsContient(cNoM,sLivre,&nItem1);
			if (!bDefini1)
				ErreR(eSemLivreInconnu,iDebut);
			else TdsValuer(cNoM,nItem1,0);
			sNom=sAlexChaine(iSuivant);
			bDefini2=bTdsContient(cNoM,sNom,&nItem2);
			if (!bDefini2)
				ErreR(eSemNonInscrit,iDebut);
			//TdsVoir("après restitution");
		}
		nAPPEL++;
	//Appel1("bRestitutioN");
	return(bSucces);
}//bRestitutioN

int bSeparateuR(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexSeparateur(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bSeparateuR",iDebut);
	ErrerSouS(bSucces,eSyntSeparateur,iDebut);
	nAPPEL++;
	return(bSucces);
}//bSeparateuR

int bSuitE(int iDebut,int *piFin){
	//Suite->Interdiction || Inscription
	int bSucces=kF,iFin=0,nChoix2;
	if (bkEclaireuR){
		nChoix2=nAlexSuite(iDebut);//pré-vision instruction courante: 1 si Interdiction, 2 si Inscription, et 0 si échec.
		if (bEclaireR) tee("iDebut et nChoix2 pr bSuitE",iDebut,nChoix2);
		switch(nChoix2){
			case 1: bSucces=bInterdictioN(iDebut,&iFin);break;
			case 2:	bSucces=bInscriptioN(iDebut,&iFin);break;
			default:ErreR(eSyntSuite,iDebut);break;
		};
	}else bSucces=bInterdictioN(iDebut,&iFin) || bInscriptioN(iDebut,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	Assert1("bSuitE1",*piFin>0);
	//te("bSuitE",iDebut);
	nAPPEL++;
	return(bSucces);
}//bSuitE

int bSuiteDeLivrE(int iDebut, int * piFin){
	//Suite -> ")" || Liste
	int bSucces,iFin;
	bSucces = bParenthese(')',iDebut,&iFin) || bListe(iDebut,&iFin);
	*piFin = (bSucces)? iFin:iDebut;
	nAPPEL++;
	return (bSucces);
}

int bSuperieurStricT(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexOperateur(iDebut,'>');
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bSuperieurStricT",iDebut);
	nAPPEL++;
	return(bSucces);
}//bSuperieurStricT

int bTextE(int iDebut,int *piFin){
	//Texte->lexème
	int bSucces;
	bSucces=bAlexTexte(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	//te("bTextE",iDebut);
	nAPPEL++;
	return(bSucces);
}//bTextE
