import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.*;

public class PanelSaisie extends JPanel{

	private JLabel label;
	private JTextField text = new JTextField();

	public PanelSaisie(String unLabel){
		label = new JLabel(unLabel);
		text.setBorder(BorderFactory.createLineBorder(Color.black));
		Dimension d = new Dimension(150,20);
		text.setPreferredSize(d);
		this.add(label);
		this.add(text);
	}

	public void setText(String txt){
		text.setText(txt);
	}

	public String getPText(){
		return text.getText();
	}
}
