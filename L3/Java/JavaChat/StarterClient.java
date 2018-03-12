import java.awt.event.*;

public class StarterClient{
	public static void main(String [] args){

		Client c = new Client();

		PressConnexion aLConnexion = new PressConnexion(c);
		PressEnvoyer aLEnvoi = new PressEnvoyer(c);

		Fenetre f = new Fenetre(c,aLConnexion,aLEnvoi);
		c.addFenetre(f);

	}
}