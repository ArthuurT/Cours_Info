
import java.util.Random;

public class Joueur{

	private int posJoueur;
	private int numJoueur;
	private Strategie stratJoueur;
	private int numStrat;
	private int dureeStrat;
	private Jeux jeu;
	private int etatJoueur;			// 0 --> en jeu // 1 --> vainqueur


	public Joueur(int numero, Jeux jeu, Strategie uneStrategie, int numStrat, int uneDuree){

		this.posJoueur = 0;
		this.numJoueur = numero;
		this.jeu = jeu;
		this.etatJoueur = 0;
		this.stratJoueur = uneStrategie;
		this.dureeStrat = uneDuree;
		this.numStrat = numStrat;

		System.out.println("Joueur n°" + numJoueur + ": Stratégie n°" + numStrat + " (Durée: " + dureeStrat + " tours)");
	} 

	public int getPosition(){
		return posJoueur;
	}

	public int getNum(){
		return numJoueur;
	}

	public Strategie getStrat(){
		return stratJoueur;
	}


	public void changerStrategie(){
		Random ran = new Random();
		int newDureeStrat = ran.nextInt(4) + 2;
		int newNumStrat = ran.nextInt(3) + 1;

		if(newDureeStrat == 1){
			this.stratJoueur = new StrategieNumeroUn(this.stratJoueur.getListeJoueur());
		}else if(newDureeStrat == 2){
			this.stratJoueur = new StrategieNumeroDeux(this.stratJoueur.getListeJoueur());
		}else{
			this.stratJoueur = new StrategieNumeroTrois(this.stratJoueur.getListeJoueur());
		}
		this.stratJoueur.setJoueur(this);
		this.numStrat = newNumStrat;
		this.dureeStrat = newDureeStrat;

		System.out.println("Joueur n°" + numJoueur + " --> Nouvelle stratégie : Numéro " + numStrat + " (Duree: " + dureeStrat + ")");

	}

	public boolean estVainqueur(){
		if(this.posJoueur >= 500){
			return true;
		}
		else return false;
	}

	private void modifierPosition(){
		int numeroDe = jeu.lancerDe();
		System.out.println("Dé:" + numeroDe + ", valeur déplacement: " + stratJoueur.calculeScore(numeroDe));
		this.posJoueur = this.posJoueur + stratJoueur.calculeScore(numeroDe);
		this.dureeStrat--;
	}

	public void jouer(){
		if(this.dureeStrat == 0) this.changerStrategie();	//On check si la stratégie est toujours valable, sinon on change
		
		modifierPosition();									//On modifie la position du joueur
		System.out.println("Joueur n°" + numJoueur + ": (Stratégie n°" + numStrat + " : reste " + dureeStrat + " tours) --> Position : " + posJoueur);

		if(this.estVainqueur()) jeu.finJeu(this);			//On check si le joueur à gagné, si oui on l'indique au jeuSystem.out.println("TEEEEEEST 3");
	}
}