/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Wed Jan 31 13:16:41 CET 2018
*
*/
public class OperateurBin extends Operateur {

	public OperateurBin(UniteCentrale u, String s){
		super(u,s); 
	}

	public void active(){
		if(label == "+") unite.operationBin((int i, int j) -> i + j);
		else if(label == "-") unite.operationBin((int i, int j) -> i - j);
		else if(label == "*") unite.operationBin((int i, int j) -> i * j);
		else if(label == "/") unite.operationBin((int i, int j) -> i / j);
	}

	
}