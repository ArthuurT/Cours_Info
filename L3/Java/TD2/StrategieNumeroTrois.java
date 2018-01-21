public class StrategieNumeroTrois extends Strategie{

	public StrategieNumeroTrois(Joueur[] listeJoueur){
		super(listeJoueur);
	}

	public int calculeScore(int numeroDe){
		return numeroDe + (joueurCourant.getPosition() - positionDernier()) / 2;
	}
}