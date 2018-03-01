import java.awt.*;
import javax.swing.*;

public class PortailConnexion extends JPanel{

	/* Panels */
	private JPanel panelName = new JPanel();
	private JPanel panelIp = new JPanel();
	private JPanel panelPort = new JPanel();

	/* Les boutons */
	private JButton connexion = new JButton("Connexion");

	/* Les champs de saisie */
	private ChampSaisie name = new ChampSaisie("Nom");
	private ChampSaisie ip = new ChampSaisie("IP");
	private ChampSaisie port = new ChampSaisie("Port");

	/* Les labels */
	private JLabel labelName = new JLabel(name.getLabel());
	private JLabel labelIp = new JLabel(ip.getLabel());
	private JLabel labelPort = new JLabel(port.getLabel());


	public PortailConnexion(){
		Dimension d1 = new Dimension(50,20);
		Dimension d2 = new Dimension(150,20);

		labelName.setPreferredSize(d1);
		labelPort.setPreferredSize(d1);
		labelIp.setPreferredSize(d1);

		name.setPreferredSize(d2);
		port.setPreferredSize(d2);
		ip.setPreferredSize(d2);
		this.setLayout(new GridLayout(2,2));

		panelName.add(labelName);
		panelName.add(name);

		panelIp.add(labelIp);
		panelIp.add(ip);

		panelPort.add(labelPort);
		panelPort.add(port);

		this.add(panelName);
		this.add(connexion);
		this.add(panelIp);
		this.add(panelPort);
	}
}
