/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:40:38 CET 2018
*
*/

public class Direction {

	private Sens sens;

	public Direction(){
		sens = null;
	}

	public void directionDroite(){
		sens = sens.next();
	}

	public void directionGauche(){
		sens = sens.previous();
	}
	
	public void directionOppose(){
		sens = sens.addTwo();
	}

	public Sens getDirection(){
		return sens;
	}

	public void setDirection(Sens unSens){
		sens = unSens;
	}
	
}