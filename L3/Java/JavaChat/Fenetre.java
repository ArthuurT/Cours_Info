import java.awt.*;
import javax.swing.*;

public class Fenetre extends JFrame {

	private Client c;
	private JPanel pc;
	private PanelConnected cd = new PanelConnected();
	private PanelConversation cv = new PanelConversation();
	private PanelEnvoi sm;

	public Fenetre(Client c, PressConnexion alC, PressEnvoyer alE){

		/* On relie le client à son Interface */

		this.c = c;

		pc = new PanelConnexion(alC);
		sm = new PanelEnvoi(alE);

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

	public void addUser(String nom){
		cd.addList(nom);
	}

	public void remUser(String nom){
		cd.remList(nom);
	}

	public void addTxt(String msg){
		cv.addAreaText(msg);
	}

	public String getTextEnvoi(){
		return sm.getAreaText();
	}

	public void clearTextEnvoi(){
		sm.clearAreaText();
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
