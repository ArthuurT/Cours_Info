import java.awt.*;
import javax.swing.*;
import java.util.*;

public class PanelConnected extends JPanel{

	private java.util.List<String> users = new ArrayList<String>();
	private JLabel label = new JLabel("Connectés");
	private JList list = new JList(users.toArray());

	public PanelConnected(){
		JPanel content = new JPanel();
		label.setAlignmentX(CENTER_ALIGNMENT);
		list.setBorder(BorderFactory.createLineBorder(Color.black));
		content.add(list);
		this.setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		list.setPreferredSize(new Dimension(150,350));
		this.add(label);
		this.add(content);
	}

	public void addList(String elem){
		users.add(elem);
		list.setListData(users.toArray());
	}

	public void remList(String elem){
		users.remove(elem);
		list.setListData(users.toArray());
	}

}
