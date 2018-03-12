/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Feb 07 23:09:13 CET 2018
*
*/


import java.util.*;

public class Pirate extends Glark{

	public Pirate(CaseLibre uneCase){
		super(uneCase);
	}

	public String getMarque(){
		return "P";
	}

	public boolean estBorne(){
		return false;
	}


	public void devoreGlark(){
		Iterator<Glark> menu = caseCourante.menu();
		while(menu.hasNext()){
			Glark glarkAuMenu = menu.next();
			if (glarkAuMenu != this){
				glarkAuMenu.meurt();
				energie = energie + 10;
			}
		}
	}

	public Sens trouverDestination(){
		if(caseCourante.getCaseNord().hasGlark()) return Sens.NORD;
		else if(caseCourante.getCaseSud().hasGlark()) return Sens.SUD;
		else if(caseCourante.getCaseEst().hasGlark()) return Sens.EST;
		else if(caseCourante.getCaseOuest().hasGlark()) return Sens.OUEST;
		else{
			Random rand = new Random();
			int nb_aleat = rand.nextInt(4);
			switch(nb_aleat){
					case 0: if(!caseCourante.getCaseNord().estObstacle())
								return Sens.NORD;
							else 
								return trouverDestination();
					case 1: if(!caseCourante.getCaseSud().estObstacle())
								return Sens.SUD;
							else 
								return trouverDestination();
					case 2: if(!caseCourante.getCaseEst().estObstacle())
								return Sens.EST;
							else 
								return trouverDestination();
					case 3: if(!caseCourante.getCaseOuest().estObstacle())
								return Sens.OUEST;
							else 
								return trouverDestination();
					default : return null;
			}
		}
		
	}
	
}