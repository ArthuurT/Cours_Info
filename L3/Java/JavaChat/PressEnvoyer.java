import java.awt.event.*;

public class PressEnvoyer implements ActionListener{

	private Client c;

	public PressEnvoyer(Client c){
		this.c = c;
	}

	public void actionPerformed(ActionEvent e){
		String msg = c.getFenetre().getTextEnvoi();
		c.sendMessage(msg);
		c.getFenetre().clearTextEnvoi();
	}
}