/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 22 15:49:12 CET 2018
*
*/
import java.awt.Color;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Fenetre extends JFrame {

	private PanneauJeu pan;

	public Fenetre(Jeu unJeu){
		this.pan = new PanneauJeu(unJeu);
		this.setTitle("Monde des Glarks");
		this.setSize(900, 900);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setContentPane(pan);
		this.setVisible(true);
		}

  
}