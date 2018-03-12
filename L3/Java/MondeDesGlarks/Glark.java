/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 10:03:38 CET 2018
*
*/
abstract class Glark {

	protected int energie;
	protected CaseLibre caseCourante;

	public Glark(CaseLibre uneCase){
		energie = 100;
		caseCourante = uneCase;
		caseCourante.addGlark(this);
	}

	public void meurt(){
		energie = 0;
		caseCourante.removeGlark(this);
	}

	public boolean estBorne(){
		return false;
	}

	public int getEnergie(){
		return energie;
	}

	public CaseLibre getCaseCourante(){
		return caseCourante;
	}

	public void devoreBlurf(){
		if(caseCourante.getBlurf()){
			energie = energie + 100;
			caseCourante.setBlurf(false);
		}
	}

	public void jouer(){
		Sens s = trouverDestination();
		caseCourante.removeGlark(this);
		switch(s){
			case NORD: caseCourante = (CaseLibre) caseCourante.getCaseNord(); caseCourante.addGlark(this); break;
			case SUD: caseCourante = (CaseLibre) caseCourante.getCaseSud(); caseCourante.addGlark(this); break;
			case EST: caseCourante = (CaseLibre) caseCourante.getCaseEst(); caseCourante.addGlark(this); break;
			case OUEST: caseCourante = (CaseLibre) caseCourante.getCaseOuest(); caseCourante.addGlark(this); break;
		}
		energie = energie - 10;
		devoreBlurf();
		devoreGlark();
	}

	public String toString(){
		String s = "";
		s = s + this.getClass().getSimpleName() + "(" + caseCourante.getx() + "," + caseCourante.gety() + ")";
		s = s + ": " + getEnergie() + " PV";
		return s;
	}

	abstract void devoreGlark();

	abstract Sens trouverDestination();

	abstract String getMarque();
	
}