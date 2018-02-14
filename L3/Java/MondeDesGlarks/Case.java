/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:15:45 CET 2018
*
*/
abstract class Case {

	protected int x;
	protected int y;

	public Case(int x, int y){
		this.x = x;
		this.y = y;
	}

	public String getMarque(){
		return " ";
	}

	public int getx(){
		return x;
	}

	public int gety(){
		return y;
	}

	abstract boolean getBlurf();

	abstract boolean hasGlark();

	public boolean estObstacle(){
		return false;
	}	
}