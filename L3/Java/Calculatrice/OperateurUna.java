/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 13:16:46 CET 2018
*
*/
public class OperateurUna extends Operateur{
	

	public OperateurUna(UniteCentrale u, String s){
		super(u,s); 
	}

	public int fac(int n){
		if (n <= 1)
            return 1;
        else
            return n * fac(n - 1);
	}

	public void active(){
		if(label == "fac") unite.operationUna((int i) -> fac(i));
	}
}