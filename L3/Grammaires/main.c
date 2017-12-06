#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Foret.h"
#include "Tas.h"
#include "Tp1.h"
#include "Tp3.h"
#include "Tp4.h"

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	OutilAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Outil mentionnés dans les include de main.c
		GrapheAMORCER();//avant FlotAMORCER()
		DequeAMORCER();
		ForetAMORCER();
		TasAMORCER();
		Tp1AMORCER();
		Tp3AMORCER();
		Tp4AMORCER();
}//ModuleAmorceR

int main (int argc, const char * argv[]) {
	int i;
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
		for(i = 1; i <= 7; i++)
			Tp1TESTER(i);
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}
