/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 11:06:31 CET 2018
*
*/

import java.util.*;

public class Borne extends Glark{

	private Direction dir;

	public Borne(CaseLibre uneCase){
		super(uneCase);
		Random rand = new Random();
		int nb_aleat = rand.nextInt(4);
		dir = new Direction();
		switch(nb_aleat){
			case 0 : dir.setDirection(Sens.NORD); break;
			case 1 : dir.setDirection(Sens.EST); break;
			case 2 : dir.setDirection(Sens.SUD); break;
			case 3 : dir.setDirection(Sens.OUEST); break;
		}
	}

	public String getMarque(){
		return "B";
	}

	public boolean estBorne(){
		return true;
	}

	public void devoreGlark(){
		Iterator<Glark> menu = caseCourante.menu();
		while(menu.hasNext()){
			Glark glarkAuMenu = menu.next();
			if (!glarkAuMenu.estBorne()){
				glarkAuMenu.meurt();
				energie = energie + 10;
			}
		}
	}

	public Sens trouverDestination(){
		int cpt = 0;
		Case caseTempo = null;
		do{
			if(cpt == 1) dir.directionDroite();
			else if(cpt == 2) dir.directionGauche();
			else if(cpt == 3) dir.directionOppose();
			switch(dir.getDirection()){
				case NORD : caseTempo = caseCourante.getCaseNord(); break;
				case SUD : caseTempo = caseCourante.getCaseSud(); break;
				case EST : caseTempo = caseCourante.getCaseEst(); break;
				case OUEST : caseTempo = caseCourante.getCaseOuest(); break;
			}
			cpt += 1;
		}while(caseTempo.estObstacle());
		return dir.getDirection();
	}

}