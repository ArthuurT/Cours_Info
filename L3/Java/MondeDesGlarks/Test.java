/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 08 19:15:40 CET 2018
*
*/
public class Test {

	public static void main(String[] args) throws InterruptedException{
		Jeu j = new Jeu();
		Fenetre f = new Fenetre(j);
		j.start();
	}

}