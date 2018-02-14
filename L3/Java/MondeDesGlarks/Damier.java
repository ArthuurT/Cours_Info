/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:10:43 CET 2018
*
*/
public class Damier {

	private Case[][] matrice;
	private int longueur;
	private int largeur;
	private Jeu jeu;

	public Damier(int longueur, int largeur, Jeu jeu){
		matrice = new Case[longueur][largeur];
		this.longueur = longueur;
		this.largeur = largeur;
		this.jeu = jeu;
	}

	public Case getCase(int x, int y){
		return matrice[x][y];
	}

	public Jeu getJeu(){
		return jeu;
	}

	public int getLongueur(){
		return longueur;
	}
	
	public int getLargeur(){
		return largeur;
	}

	public void setCase(Case uneCase, int x, int y){
		matrice[x][y] = uneCase;
	}

	public void afficher(){
		int i,j;
		for(i = 0; i < longueur; i++){
			for(j = 0; j < largeur; j++){
				if(matrice[i][j] != null) System.out.print(matrice[i][j].getMarque() + " ");
				else System.out.print("  ");
			}
			System.out.println("");
		}
	}
	
}