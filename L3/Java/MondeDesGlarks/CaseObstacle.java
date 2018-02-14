/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:16:48 CET 2018
*
*/
public class CaseObstacle extends Case{

	private String marque;

	public CaseObstacle(int x, int y){
		super(x,y);
		marque = "#";
	}

	public boolean getBlurf(){
		return false;
	}

	public boolean hasGlark(){
		return false;
	}

	public String getMarque(){
		return marque;
	}

	public boolean estObstacle(){
		return true;
	}
}