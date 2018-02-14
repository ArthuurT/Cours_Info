/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 13:01:05 CET 2018
*
*/
abstract class Touche {

	protected String label;
	protected UniteCentrale unite;

	public Touche(UniteCentrale u, String s){
		label = s;
		unite = u;
	}

	abstract void active();

	public String toString(){
		String str = "Touche: " + label;
		return str; 
	}
	
}