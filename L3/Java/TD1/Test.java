class Test{

	public static void main(String[] args){

		Rationnel a = new Rationnel(1,4);
		Rationnel b = new Rationnel(1,4);
		Rationnel c = new Rationnel(1,2);
		Rationnel d = new Rationnel(2,1);
		Rationnel [] tab = new Rationnel[4];
		tab[0] = a; tab[1] = b; tab[2] = c; tab[3] = d;

		/* Test de la moyenne */

		Rationnel r = Rationnel.moyenne(tab);
		System.out.println("Moyenne : " + r.getNum() + " / " + r.getDen());

		/* Test du système */

		Rationnel [] sys = Rationnel.systeme(2,4,3,3,5,2);
		System.out.println("x = " + sys[0].getNum() + " / " + sys[0].getDen());
		System.out.println("y = " + sys[1].getNum() + " / " + sys[1].getDen());

		/* Test de sqrt */

		Rationnel sqr = Rationnel.sqrt(new Rationnel(8,5), new Rationnel(1,10)).simplifier();
		System.out.println("Arrondi = " + sqr.getNum() + " / " + sqr.getDen());

		/* Test de l'écart-type */

		Rationnel e = Rationnel.std(tab, new Rationnel(1,10));
		System.out.println("Ecart-type : " + e.getNum() + " / " + e.getDen());

		/* Test du trinôme */
		
		Rationnel[] coeffs = new Rationnel[3];
		coeffs[0] = new Rationnel(2,1);
		coeffs[1] = new Rationnel(5,1);
		coeffs[2] = new Rationnel(-2,1);
		Rationnel[] tri = Rationnel.trinome(coeffs,new Rationnel(1,10));

		System.out.println("Première racine: " +  tri[0].getNum() + " / " + tri[0].getDen());
		System.out.println("Deuxième racine: " +  tri[1].getNum() + " / " + tri[1].getDen());

	}

}