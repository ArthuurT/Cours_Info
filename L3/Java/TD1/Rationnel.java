public class Rationnel{

	private int p;
	private int q;

	public Rationnel(int p, int q){
		this.p = p;
		this.q = q;
	}

	public int getNum(){ return this.p;}

	public int getDen(){ return this.q;}

	public double toDouble(){
		return (this.p * 1.0) / this.q;
	}

	public Rationnel somme(Rationnel r){
		if(this.q == r.q){
			return new Rationnel(this.p + r.p, this.q);
		}else{
			return new Rationnel(this.p * r.q + r.p * this.q, r.q * this.q);
		}
	}

	public Rationnel difference(Rationnel r){
		if(this.q == r.q){
			return new Rationnel(this.p - r.p, this.q);
		}else{
			return new Rationnel(this.p * r.q - r.p * this.q, r.q * this.q);
		}
	}

	public Rationnel produit(Rationnel r){
			return new Rationnel(this.p * r.p, this.q * r.q);
	}


	public Rationnel memeDen(Rationnel r){
		return new Rationnel(this.p * r.q, this.q * r.q);
	}

	public int compareTo(Rationnel r){
		Rationnel r1 = this.memeDen(r);
		Rationnel r2 = r.memeDen(this);
		if(r1.p == (r2.p)) return 0;
		else if(r1.p > (r2.p)) return 1;
		else return -1;
	}

	public static Rationnel moyenne(Rationnel[] t){
		Rationnel som = t[0];
		Rationnel total = new Rationnel(1,t.length);
		int i;
		for(i = 1; i < t.length ; i++){
			som = som.somme(t[i]);
		}
		return som.produit(total).simplifier();
	}

	public int pgcd(){
		int r = 1;
		int a = this.p;
		int b = this.q;
		while(r != 0){
			if(a > b) r = a % b;	
			else r = b % a;

			if(r == 0) return b;
			else{
				if(a > b) a = b;
				b = r;
			}
		}
		return r;
	}

	public Rationnel simplifier(){
		return new Rationnel(this.p/this.pgcd(),this.q/this.pgcd());
	}


	public static Rationnel[] systeme(int a, int b, int c, int d, int e, int f){
		Rationnel [] res = new Rationnel[2];
		Rationnel x, y;
		int g = (a * e) - (b * d);
		if(g != 0){
			res[0] = new Rationnel(b*f - c*e, g);
			res[1] = new Rationnel(c*d - a*f, g);
		}
		else{
			System.out.println("Erreur: plusieurs solutions possibles");
		}
		return res;
	}

	public static Rationnel sqrt(Rationnel r, Rationnel precision){
		
		Rationnel z = new Rationnel(0,1);
		Rationnel u = new Rationnel(1,2).produit(r);
		Rationnel us = new Rationnel(1,2).produit(u.somme(new Rationnel(r.p * u.q, r.q * u.p)));

		while(u.difference(us).difference(precision).compareTo(z) != -1){
			u = us;
			us = new Rationnel(1,2).produit(u.somme(new Rationnel(r.p * u.q, r.q * u.p)));
		}

		return us;

	}

	public static Rationnel std(Rationnel[] t, Rationnel precision){
		int i = 1;
		Rationnel n = new Rationnel(1,t.length);
		Rationnel s = t[0].difference(Rationnel.moyenne(t));
		Rationnel sf = s.produit(s);
		Rationnel b;
		Rationnel bs;

		while(i < t.length){
			b = t[i].difference(Rationnel.moyenne(t));
			bs = s.produit(s);
			sf = sf.somme(bs);
			i++;
		}

		return Rationnel.sqrt(sf.produit(n),precision).simplifier();
	}


	
	public static Rationnel[] trinome(Rationnel[] coeffs, Rationnel precision){

		Rationnel[] res = new Rationnel[2];
		Rationnel z = new Rationnel(0,1);
		Rationnel b = coeffs[1].produit(coeffs[1]);
		Rationnel ac = coeffs[0].produit(coeffs[2]).produit(new Rationnel(4,1));
		Rationnel d = b.difference(ac);


		System.out.println("Test 1");

		if(d.compareTo(z) == 0){
			System.out.println("Test 2");
			res[0] = b.produit(new Rationnel(-1,1)).produit(new Rationnel(1,2)).produit(new Rationnel(coeffs[0].getDen(),coeffs[0].getNum())).simplifier();
			System.out.println("Test 3");
		}else if(d.compareTo(z) > 0){
			System.out.println("Test 4");
			res[0] = b.produit(new Rationnel(-1,1)).somme(sqrt(d,precision)).produit(new Rationnel(1,2)).produit(new Rationnel(coeffs[0].getDen(),coeffs[0].getNum())).simplifier();
			res[1] = b.produit(new Rationnel(-1,1)).difference(sqrt(d,precision)).produit(new Rationnel(1,2)).produit(new Rationnel(coeffs[0].getDen(),coeffs[0].getNum())).simplifier();
			System.out.println("Test 5");
		}
		System.out.println("Test 6");
		return res;
	}




}









