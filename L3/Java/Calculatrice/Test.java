/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 15:13:50 CET 2018
*
*/
public class Test {
	public static void main(String[] args){

		// Declaration des touches de la calculatrice
		UniteCentrale u = new UniteCentrale();
		Touche zero = new Digit(u,"0");
		Touche un = new Digit(u,"1");
		Touche deux = new Digit(u,"2");
		Touche trois = new Digit(u,"3");
		Touche quatre = new Digit(u,"4");
		Touche cinq = new Digit(u,"5");
		Touche six = new Digit(u,"6");
		Touche sept = new Digit(u,"7");
		Touche huit = new Digit(u,"8");
		Touche neuf = new Digit(u,"9");
		Touche plus = new OperateurBin(u,"+");
		Touche moins = new OperateurBin(u,"-");
		Touche mult =  new OperateurBin(u,"*");
		Touche div = new OperateurBin(u,"/");
		Touche fac = new OperateurUna(u,"fac");
		Touche enter = new Entrer(u,"Entrer");
		
		// Operations

		// "35"
		trois.active();
		cinq.active();
		enter.active();

		// "3"
		trois.active();

		// "35 3 +"
		plus.active();

		// "4"
		quatre.active();
		enter.active();

		// "10"
		un.active();
		zero.active();

		// "4 10 *"
		mult.active();

		// "5"
		cinq.active();

		// "5!"
		fac.active();

		plus.active();

		moins.active();
		
	}
}