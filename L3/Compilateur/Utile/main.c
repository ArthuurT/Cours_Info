#include "Outil.h"
#include "Alex.h"
#include "Asynt.h"
#include "Deque.h"
#include "Erreur.h"
#include "Grammaire.h"
#include "Grhom.h"

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	OutilAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Outil mentionnés dans les include de main.c
		//AbeAMORCER();
		AlexAMORCER();
		//ArcolAMORCER();
		AsyntAMORCER();
		//DagAMORCER();
		ErreurAMORCER();
		//FormeAMORCER();
		GrammaireAMORCER();
		GrhomAMORCER();
		//GrapheAMORCER();//avant FlotAMORCER()
		//QuadAMORCER();
		//MatriceAMORCER();
		//CouplageAMORCER();
		//CycleAMORCER();
		DequeAMORCER();
		//FlotAMORCER();
		//ForetAMORCER();
		//GaussAMORCER();
		//NbAMORCER();
		//TasAMORCER();
		TdsAMORCER();
		//TicketAMORCER();
		//Tp1AMORCER();
		//Tp2AMORCER();
		//Tp3AMORCER();
		//Tp4AMORCER();
}//ModuleAmorceR

void DiagnostiqueR(char *sContexte,int bSucces){
	printf("Le code source analysé %s valide %sment %s",sEst(bSucces),sContexte,sChoix0(!bSucces,sP(sPluriel(nErreurEnTout(),"erreur"))));
	printf("%c\n",(bSucces)?'.':':');
}//DiagnostiqueR

void Compiler(int nSource){
	int bSucces;
	char *sSource;
	//nSource=2;
	switch (nSource){
		case 1: sSource="19.60 livre; 8.05 autrelivre; 7.02 encoreautrelivre;$";break;
		// case 1: sSource="51.0 trac; 52 Trec ; 53.0 tric ; 54.0 troc ; Bidule ; Chose ; 0.0 machin ; 55.0 truc;$";
				//break;
		//case 2: sSource="240317 ELLE; 0.5 elle; < elle ELLE; 0 elle; < elle ELLE; > elle ELLE ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				//break;
		//case 3: sSource="240317 ELLE; 0.5 dune; < dune ELLE; 0 dune; < dune ELLE; > dune ELLE ; 440317 MOI  ; 3.5 machin ; 55 Truc ;$";
				//break;
		default: ;
	}
	bSucces=bAlexAnalyser(sSource); DiagnostiqueR("lexicale",bSucces);
	bSucces=bSucces && bAsyntAnalyser(mAsyntSyntaxe); DiagnostiqueR("syntaxique",bSucces);
	bSucces=bSucces && bAsyntAnalyser(mAsyntSemantique); DiagnostiqueR("sémantique",bSucces);
	bSucces = bSucces && bAsyntAnalyser(mAsyntGenerer);
	//ErreurAfficherTout();
	//AlexAfficher();
}//Compiler

void MacroTesteR() {
	int bSucces=1,uE=5;
	float rA=3.1, rB=5.869;
	char *sBonjour="BONJOUR";char *sBonsoir="BONSOIR";char *sSalut="SALUT";
	b(bSucces);
	d(uE);
	d(uE/(uE-3));
	d2(uE,uE-1);
	d3(uE,uE-1,uE-2);
	s(sBonjour);
	s2(sBonjour,sBonsoir);
	s3(sBonjour,sBonsoir,sSalut);
	f(rA);
	f2(rA,rB);
	uE=123456789;
	d(uE);
}//MacroTesteR

int main (int argc, const char * argv[]) {

	//enum grType GrapheType;
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
		//MacroTesteR();
		//OutilTESTER(22);
		//CycleTESTER(1);
		//FlotTESTER(0);
		//QuadTESTER(70);
		//NbTESTER(4);
		//CouplageTESTER(50);
		//CycleTESTER(90);
	//FormeTESTER(99);
		//CycleTESTER(13);
		//NbTESTER(1);
		//OutilTESTER(54);
		/*GrapheCreer1(&pgG,gr2Diam,kV);
		GrapheSymetriser(pgG);
		GrapheVoir(pgG,"pgG");
		GrapheTrier(pgG);
		GrapheExplorer(pgG,kF);
		GrapheExplorer(pgG,kV);*/
		//CouplageTESTER(0);
		//CycleTESTER(77);
		//FormeTESTER(100);//DeterminantSelecteurCalculeR
		//GrhomTESTER(11);
		//for(i = 1; i < 9 ; i++){
			//int i;
			Compiler(1);
		//}
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}
