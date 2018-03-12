import java.awt.event.*;

public class StarterClient{
	public static void main(String [] args){

		Client c = new Client();

		PressConnexion aLConnexion = new PressConnexion(c);

		Fenetre f = new Fenetre(c,aLConnexion);
		c.addFenetre(f);

	}
}