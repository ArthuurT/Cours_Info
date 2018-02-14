/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 11:55:52 CET 2018
*
*/

import java.util.*;


public class UniteCentrale{

	private Deque pile;
	private int buffer;
	private boolean recouvrir;

	public UniteCentrale(){
		pile = new ArrayDeque();
		buffer = 0;
		recouvrir = true;
	}

    /**
	 * Ajoute au buffer la valeur d'une touche
	 */
	public void add(int n){
		if(recouvrir){
			pile.push(buffer);
			recouvrir = false;
			buffer = 0;
		}
		buffer = buffer * 10 + n;
		afficherBuf();
		System.out.println("Pile: " + pile);
	}


	/*
	 * Exemple d'appel : operationBin((int i, int j) -> i + j);
	 */
	public void operationBin(FunctionBin func){
		int s = (int) pile.pop();
		buffer = func.calcBin(buffer,s);
		recouvrir = true;
		afficherBuf();
		System.out.println("Pile: " + pile);
	}

	/*
	 * Exemple d'appel : operationUna((int i) -> i!);
	 */
	public void operationUna(FunctionUna func){
		buffer = func.calcUna(buffer);
		recouvrir = true;
		afficherBuf();
		System.out.println("Pile: " + pile);
	}


	public void setRecouvrirTrue(){
		recouvrir = true;
	}

	/**
	 * Affiche le buffer à l'écran
	 */
	public void afficherBuf(){
		System.out.println("Ecran: " + buffer);
	}

	
}