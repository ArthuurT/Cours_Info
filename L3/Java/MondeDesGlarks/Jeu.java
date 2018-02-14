/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Tue Feb 06 09:07:17 CET 2018
*
*/

import java.util.*;
import java.lang.*;

public class Jeu{

	private Damier plateau;
	private List<Glark> listeGlark;
	
	Iterator <Glark> it;

	public Jeu(){
		plateau = new Damier(9,9,this);
		listeGlark = new ArrayList<Glark>();
	}

	public void start() throws InterruptedException{

		// Cases obstacle (contour)

		int i;
		int j = 0;
		int k = 0;
		int taille = plateau.getLongueur() * plateau.getLargeur();

		for(i = 0; i < taille; i++){
			if(j == plateau.getLongueur()){
				j = 0; k += 1;
			}
			if(k == 0 || k == plateau.getLargeur() - 1) 
				plateau.setCase(new CaseObstacle(j,k),j,k);
			else if(j == 0 || j == plateau.getLongueur() -1) 
				plateau.setCase(new CaseObstacle(j,k),j,k);
			j += 1;
		}

		// Cases libres

		j = 1;
		k = 1;
		taille = (plateau.getLongueur()-2) * (plateau.getLargeur()-2);

		for(i = 0; i < taille; i++){
			if(j == plateau.getLongueur() - 1){
				j = 1; k += 1;
			}
			plateau.setCase(new CaseLibre(plateau,false,j,k),j,k);
			j += 1;
		}
	
		// Cases obstacles (dans le jeu)

		plateau.setCase(new CaseObstacle(1,3),1,3);
		plateau.setCase(new CaseObstacle(2,3),2,3);
		plateau.setCase(new CaseObstacle(3,3),3,3);
		plateau.setCase(new CaseObstacle(4,3),4,3);
		plateau.setCase(new CaseObstacle(1,5),1,5);
		plateau.setCase(new CaseObstacle(2,5),2,5);
		plateau.setCase(new CaseObstacle(6,3),6,3);
		plateau.setCase(new CaseObstacle(6,4),6,4);
		plateau.setCase(new CaseObstacle(6,5),6,5);
		plateau.setCase(new CaseObstacle(7,4),7,4);
		

		// Tas de blurf

		((CaseLibre)plateau.getCase(1,2)).setBlurf(true);
		((CaseLibre)plateau.getCase(5,1)).setBlurf(true);
		((CaseLibre)plateau.getCase(3,4)).setBlurf(true);
		((CaseLibre)plateau.getCase(4,5)).setBlurf(true);

		// Glark

		listeGlark.add(new Pirate((CaseLibre)plateau.getCase(3,2)));
		listeGlark.add(new Pirate((CaseLibre)plateau.getCase(5,4)));
		listeGlark.add(new Pirate((CaseLibre)plateau.getCase(4,6)));

		listeGlark.add(new Glouton((CaseLibre)plateau.getCase(3,6)));
		listeGlark.add(new Glouton((CaseLibre)plateau.getCase(6,6)));

		listeGlark.add(new Borne((CaseLibre)plateau.getCase(2,4)));
		listeGlark.add(new Borne((CaseLibre)plateau.getCase(5,3)));
		listeGlark.add(new Borne((CaseLibre)plateau.getCase(7,2)));
		listeGlark.add(new Borne((CaseLibre)plateau.getCase(7,7)));

		

		try        
		{
			clrscr();
			plateau.afficher();

			while(!listeGlark.isEmpty()){
				it = listeGlark.iterator();
	
				while(it.hasNext()){
					Glark unGlark = it.next();
					if(unGlark.getEnergie() <= 0){
						unGlark.getCaseCourante().removeGlark(unGlark);
						it.remove();
						
					}
					else{
						unGlark.jouer();
						Thread.sleep(500);
						clrscr();
						plateau.afficher();
					}
				}
			}
			clrscr();
			plateau.afficher();
		} 
		catch(InterruptedException ex) 
		{
		    Thread.currentThread().interrupt();
		}
		
	}

	public static void clrscr(){
	    System.out.print("\033\143");

	}
}