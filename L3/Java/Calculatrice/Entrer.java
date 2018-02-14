/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 15:08:29 CET 2018
*
*/
public class Entrer extends Touche {

	public Entrer(UniteCentrale u, String s){
		super(u,s);
	}

	public void active(){
		unite.setRecouvrirTrue();
	}

}