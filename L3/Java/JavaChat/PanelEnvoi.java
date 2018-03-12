import javax.swing.*;
import java.util.*;
import java.awt.*;

public class PanelEnvoi extends JPanel{

	private JTextArea text = new JTextArea();
	private JButton button = new JButton("Envoyer");

	public PanelEnvoi(){
		button.setAlignmentX(CENTER_ALIGNMENT);
		text.setBorder(BorderFactory.createLineBorder(Color.black));
		text.setLineWrap(true);
		JPanel jp = new JPanel();
		jp.add(text);
		this.setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		text.setPreferredSize(new Dimension(430,100));
		this.add(jp);
		this.add(button);
	}

}