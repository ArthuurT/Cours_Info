/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 15:44:55 CET 2018
*
*/
public class Digit extends Touche {

	public Digit(UniteCentrale u, String s){
		super(u,s); 
	}

	public void active(){
		int n = Integer.parseInt(label);
		unite.add(n);
	}
	
}