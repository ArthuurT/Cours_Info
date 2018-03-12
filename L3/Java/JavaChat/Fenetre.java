import java.awt.*;
import javax.swing.*;

public class Fenetre extends JFrame {

	private Client c;
	private JPanel pc;
	private JPanel cd = new PanelConnected();
	private JPanel cv = new PanelConversation();
	private JPanel sm = new PanelEnvoi();

	public Fenetre(Client c, PressConnexion acB){

		/* On relie le client à son Interface */

		this.c = c;

		pc = new PanelConnexion(acB);

		/* Spécificité de la fenêtre */

		this.setTitle("Chat");
		this.setSize(450, 600);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		this.setLayout(new BorderLayout());

		this.getContentPane().add(pc,BorderLayout.NORTH);
		this.getContentPane().add(cd,BorderLayout.WEST);
		this.getContentPane().add(cv,BorderLayout.CENTER);
		this.getContentPane().add(sm,BorderLayout.SOUTH);
		this.setVisible(true);

		//cd.addList("Test1");

	}

	public PanelConnexion getPConnexion(){
		return (PanelConnexion) pc;
	}

	public String getTextName(){
		return getPConnexion().getPName().getPText();
	}

	public String getTextPort(){
		return getPConnexion().getPPort().getPText();
	}

	public String getTextIp(){
		return getPConnexion().getPIp().getPText();
	}
}
