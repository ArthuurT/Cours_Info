/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:17:32 CET 2018
*
*/

import java.util.*;

public class CaseLibre extends Case{

	private Damier plateau;
	private boolean blurf;
	private List<Glark> listGlark;
	private String marque;

	public CaseLibre(Damier unDamier, boolean unBlurf, int x, int y){
		super(x,y);
		plateau = unDamier;
		boolean blurf = unBlurf;
		listGlark = new ArrayList<Glark>();
		marque = "-";
	}

	public Iterator<Glark> menu(){
		return listGlark.iterator();
	}

	public String getMarque(){
		if(!listGlark.isEmpty()) return listGlark.get(0).getMarque();
		else if(blurf) return "%";
		else return marque;
	}

	public boolean getBlurf(){
		return blurf;
	}

	public Damier getPlateau(){
		return plateau;
	}

	public boolean hasGlark(){
		return !listGlark.isEmpty();
	}

	public void setBlurf(boolean unBlurf){
		blurf = unBlurf;
	}
	
	public void addGlark(Glark unGlark){
		listGlark.add(unGlark);
	}

	public void removeGlark(Glark unGlark){
		listGlark.remove(unGlark);
	}

	public boolean contientGlark(Glark unGlark){
		return listGlark.contains(unGlark);
	}

	public Case getCaseNord(){
		return plateau.getCase(x-1,y);
	}
	
	public Case getCaseSud(){
		return plateau.getCase(x+1,y);
	}
	
	public Case getCaseOuest(){
		return plateau.getCase(x,y-1);
	}
	
	public Case getCaseEst(){
		return plateau.getCase(x,y+1);
	}
	
}