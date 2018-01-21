import java.lang.Math;


public class EnsembleDeChiffres{

	private boolean[] present;

	public EnsembleDeChiffres(){
		present = new boolean[10];
		int i;
		for(i = 0; i < 9; i++){
			this.present[i] = false;
		}
	}

	public void ajoute(int i){
		if(i < 10 && i >= 0){
			this.present[i] = true;
			System.out.println("Ajout de " + i);
		}
		else System.out.println(i + " n'est pas un chiffre, impossible de l'ajouter");
	}

	public void retire(int i){
		if(i < 10 && i >= 0){
			this.present[i] = false;
			System.out.println("Retrait de " + i);
		} 
		else System.out.println(i + " n'est pas un chiffre, impossible de le retirer");
	}


	public void tirerAuHasard(){
		double b;
		int i;
		for(i = 0; i < 9; i++){
			b = Math.random();
			this.present[i] = b < 0.5 ? true : false;
		}
		System.out.println("Tirage au sort aléatoirement de l'ensemble");
	}

	public boolean appartient(int i){
		if(i < 10 && i >= 0) return false;
		else return this.present[i];
	}


	public EnsembleDeChiffres intersectionAvec(EnsembleDeChiffres e){
		EnsembleDeChiffres n = new EnsembleDeChiffres();
		int i;
		for(i = 0; i < 9; i++){
			if(e.present[i] && this.present[i]) n.present[i] = true;
		}
		return n;
	}

	public EnsembleDeChiffres unionAvec(EnsembleDeChiffres e){
		EnsembleDeChiffres n = new EnsembleDeChiffres();
		int i;
		for(i = 0; i < 9; i++){
			if(e.present[i] || this.present[i]) n.present[i] = true;
		}
		return n;
	}

	public boolean estInclusDans(EnsembleDeChiffres e){
		int i;
		for(i = 0; i < 9; i++){
			if(this.present[i] == true)
				if(e.present[i] == false) 
					return false;
		}
		return true;
	}

	public void affiche(){
		System.out.println(this);
	}

	public String toString(){
		String s = this.getClass().getSimpleName() + ": {";
		String m;
		int i;
		for(i = 0; i < 9; i++){
			if(this.present[i] == true) s = s + i + " ";
		}
		s = s + "}";
		m = s.replaceAll(" }","}");
		return m;
	}


	public static void main (String[] args){

		EnsembleDeChiffres e1 = new EnsembleDeChiffres();
		EnsembleDeChiffres e2 = new EnsembleDeChiffres();

		e1.ajoute(2);
		e1.ajoute(3);
		e1.ajoute(8);
		e1.affiche();
		System.out.print("\n");

		e1.ajoute(10);
		e1.retire(8);
		e1.retire(9);
		e1.affiche();
		System.out.print("\n");

		e2.tirerAuHasard();
		e2.affiche();

	}

}