import java.awt.event.*;

public class PressConnexion implements ActionListener{

	private Client c;

	public PressConnexion(Client c){
		this.c = c;
	}

	public void actionPerformed(ActionEvent e){
		c.connexion();
	}
}