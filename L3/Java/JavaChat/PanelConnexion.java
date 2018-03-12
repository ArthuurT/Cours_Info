import java.awt.*;
import javax.swing.*;

public class PanelConnexion extends JPanel{


	/* Les boutons */
	private JButton connexion = new JButton("Connexion");

	/* Les saisies */
	private PanelSaisie name = new PanelSaisie("Nom");
	private PanelSaisie ip = new PanelSaisie("IP");
	private PanelSaisie port = new PanelSaisie("Port");

	public PanelConnexion(PressConnexion aL){
		this.setLayout(new GridLayout(2,2));
		this.add(name);
		this.add(connexion);
		this.add(ip);
		this.add(port);
		connexion.addActionListener(aL);
	}

	public PanelSaisie getPPort(){
		return port;
	}

	public PanelSaisie getPIp(){
		return ip;
	}

	public PanelSaisie getPName(){
		return name;
	} 
}
