/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 11:44:57 CET 2018
*
*/
import java.util.*;

public class Glouton extends Glark{

	public Glouton(CaseLibre uneCase){
		super(uneCase);
	}

	public String getMarque(){
		return "o";
	}

	public boolean estBorne(){
		return false;
	}

	public void devoreGlark(){}

	public Sens trouverDestination(){
		Case caseTempo = null;
		if(caseCourante.getCaseNord().getBlurf()) return Sens.NORD;
		else if(caseCourante.getCaseSud().getBlurf()) return Sens.SUD;
		else if(caseCourante.getCaseEst().getBlurf()) return Sens.EST;
		else if(caseCourante.getCaseOuest().getBlurf()) return Sens.OUEST;
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
