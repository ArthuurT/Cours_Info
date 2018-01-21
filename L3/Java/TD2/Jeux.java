import java.util.Random;

public class Jeux{

	private Joueur[] listeJoueur = new Joueur[4];
	private int nbTour;
	private Joueur joueurVainqueur;

	public Jeux(){
		Random ran = new Random();
		int newNumDe, newDureeDe, i;
		nbTour = 0;
		joueurVainqueur = null;

		for(i = 0; i < 4; i++){

			newNumDe = ran.nextInt(3) + 1;
			newDureeDe = ran.nextInt(4) + 2;
			if(newNumDe == 1){
				listeJoueur[i] = new Joueur(i+1,this, new StrategieNumeroUn(this.listeJoueur),1,newDureeDe);
				listeJoueur[i].getStrat().setJoueur(listeJoueur[i]);
			}else if(newNumDe == 2){
				listeJoueur[i] = new Joueur(i+1,this, new StrategieNumeroDeux(this.listeJoueur),2,newDureeDe);
				listeJoueur[i].getStrat().setJoueur(listeJoueur[i]);
			}else{
				listeJoueur[i] = new Joueur(i+1,this, new StrategieNumeroTrois(this.listeJoueur),3,newDureeDe);
				listeJoueur[i].getStrat().setJoueur(listeJoueur[i]);
			}
		}

	}

	public int lancerDe(){
		Random ran = new Random();
		int newNumDe = ran.nextInt(6) + 1;
		return newNumDe;
	}

	public void finJeu(Joueur unJoueur){
		this.joueurVainqueur = unJoueur;
		System.out.println("Fin de la partie --> Victoire du joueur n°" + this.joueurVainqueur.getNum());
		System.exit(1);
	}

	public void lancerJeu(){
		int i;
		while(joueurVainqueur == null){						// un while(1) suffirait
			for(i = 0; i < listeJoueur.length; i++){
				listeJoueur[i].jouer();
			}
		}
	}
}