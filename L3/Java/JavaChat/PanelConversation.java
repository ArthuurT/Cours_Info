import javax.swing.*;
import java.awt.Dimension;
import java.awt.Color;

public class PanelConversation extends JPanel{
	
	private JLabel label = new JLabel("Messages");
	private JTextArea text = new JTextArea();

	public PanelConversation(){
		text.setEditable(false);
		label.setAlignmentX(CENTER_ALIGNMENT);
		text.setBorder(BorderFactory.createLineBorder(Color.black));
		JPanel jp = new JPanel();
		jp.add(text);
		this.setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		text.setPreferredSize(new Dimension(280,350));
		this.add(label);
		this.add(jp);


	}




}