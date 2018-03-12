/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 22 16:31:30 CET 2018
*
*/

import javax.swing.JPanel;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.Color;
import java.util.*;

public class PanneauJeu extends JPanel {

	private ArrayList<PanneauCase> listCase;	//both List in java.awt.* and java.util.* -> force with ArrayList
	private Jeu unJeu;

	Iterator<PanneauCase> it;

	public PanneauJeu(Jeu unJeu){
		int i,j;
		listCase = new ArrayList<PanneauCase>();
		this.unJeu = unJeu;

		for(i = 0; i < unJeu.getPlateau().getLongueur() ; i++){
			for(j = 0; j < unJeu.getPlateau().getLargeur(); j++){
				addPanneauCase(new PanneauCase(unJeu.getPlateau().getCase(i,j)));
			}
		}
	}

	public void paintComponent(Graphics g){
			super.paintComponent(g);
			it = listCase.iterator();
			while(it.hasNext()){
				it.next().paintComponent(g);
			}
			repaint();
	}

	public void addPanneauCase(PanneauCase p){
		listCase.add(p);
	}
	
}