/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Thu Feb 22 15:55:34 CET 2018
*
*/
import javax.swing.JPanel;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.Color;
import java.util.*;
import java.net.URL;
import java.awt.Toolkit;

public class PanneauCase extends JPanel{

	private Case uneCase;

	public static final Color colorCase = Color.black;
	public static final int scl = 50;
	private static Image imgGlouton, imgBorne, imgPirate, imgBlurf;

	private static final String LIEN_GLOBAL = "https://arthur.vlntn.pw/SnakebyWaren/ImageGlarks";
	private static final String LIEN_GLOUTON = LIEN_GLOBAL + "/Glouton.png";
	private static final String LIEN_BORNE = LIEN_GLOBAL + "/Borne.jpg";
	private static final String LIEN_PIRATE = LIEN_GLOBAL + "/Pirate.jpg";
	private static final String LIEN_BLURF = LIEN_GLOBAL + "/Blurf.jpg";

	static{

		System.setProperty("java.net.useSystemProxies","true");

		try{
	    	imgGlouton = ImageIO.read(new URL(LIEN_GLOUTON));
			imgBorne = ImageIO.read(new URL(LIEN_BORNE));
			imgPirate = ImageIO.read(new URL(LIEN_PIRATE));
			imgBlurf = ImageIO.read(new File("test.jpg"));

	    }catch (IOException e){
	      	e.printStackTrace();
	    }
	}

	public PanneauCase(Case uneCase){
		this.uneCase = uneCase;
	}

	public void paintComponent(Graphics g){

		g.setColor(colorCase);

		if(uneCase instanceof CaseObstacle){
			g.fillRect(scl+uneCase.gety()*scl,scl+uneCase.getx()*scl,scl,scl);
		}else if(uneCase instanceof CaseLibre){

			CaseLibre newCase = (CaseLibre) uneCase;

			if(!newCase.hasGlark()){
				if(newCase.getBlurf()){

					g.drawImage(imgBlurf,scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl,this);
					//g.setColor(Color.blue);
					//g.fillOval(scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl);
				}
				else g.drawRect(scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl);
			}else{

			//g.setColor(Color.red);

			if(newCase.getFirstGlark() instanceof Borne)
				g.drawImage(imgBorne,scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl,this);
				//g.fillOval(scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl);
			else if(newCase.getFirstGlark() instanceof Glouton)
				g.drawImage(imgGlouton,scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl,this);
				//g.fillOval(scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl);
			else if(newCase.getFirstGlark() instanceof Pirate)
				g.drawImage(imgPirate,scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl,this);
				//g.fillOval(scl+newCase.gety()*scl,scl+newCase.getx()*scl,scl,scl);
			}
		}
	}
}
