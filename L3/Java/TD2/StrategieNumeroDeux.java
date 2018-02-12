public class StrategieNumeroDeux extends Strategie{

	public StrategieNumeroDeux(Joueur[] listeJoueur){
		super(listeJoueur);
	}

	public int calculeScore(int numeroDe){
		if(numeroDe % 2 == 0) return numeroDe * 3;
		else return numeroDe;
	}
}