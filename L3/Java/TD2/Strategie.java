import java.util.Random;

abstract class Strategie{

	protected Joueur[] listeJoueur;
	protected Joueur joueurCourant;

	public Strategie(Joueur[] listeJoueur){
		this.listeJoueur = listeJoueur;
	}

	public void setJoueur(Joueur unJoueur){
		this.joueurCourant = unJoueur;
	}

	public Joueur[] getListeJoueur(){
		return listeJoueur;
	}

	abstract int calculeScore(int numeroDe);

	public int positionPremier(){
		int i;
		int max = listeJoueur[0].getPosition();
		for(i = 1; i < listeJoueur.length; i++){
			if(listeJoueur[i].getPosition() > max) max = listeJoueur[i].getPosition();
		}
		return max;
	}

	public int positionDernier(){
		int i;
		int min = listeJoueur[0].getPosition();
		for(i = 1; i < listeJoueur.length; i++){
			if(listeJoueur[i].getPosition() < min) min = listeJoueur[i].getPosition();
		}
		return min;
	}
}