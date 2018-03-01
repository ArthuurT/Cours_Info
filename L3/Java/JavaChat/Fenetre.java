import java.awt.*;
import javax.swing.*;

public class Fenetre extends JFrame {

	private PortailConnexion pc;
	private Connected cd;

	public Fenetre(){
		pc = new PortailConnexion();
		cd = new Connected();

		/* Spécificité de la fenêtre */
		this.setTitle("Chat");
		this.setSize(450, 600);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
		this.setLayout(new GridBagLayout());
		this.setLayout(new BorderLayout());

		this.getContentPane().add(pc,BorderLayout.NORTH);
		this.getContentPane().add(cd,BorderLayout.WEST);
		this.setVisible(true);

		cd.addList("Test1");
	}
}
