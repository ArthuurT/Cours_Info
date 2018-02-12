public class StrategieNumeroUn extends Strategie{

	public StrategieNumeroUn(Joueur[] listeJoueur){
		super(listeJoueur);
	}

	public int calculeScore(int numeroDe){
		return numeroDe + (positionPremier() - joueurCourant.getPosition()) / 2;
	}

}