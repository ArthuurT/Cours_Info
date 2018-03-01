import java.awt.*;
import javax.swing.*;
import java.util.*;

public class Connected extends JPanel{

	private java.util.List<String> users = new ArrayList<String>();
	private JLabel label = new JLabel("Connectés");
	private JList list = new JList(users.toArray());

	public Connected(){
		JPanel content = new JPanel();
		content.add(list);
		this.setLayout(new BoxLayout(this,BoxLayout.PAGE_AXIS));
		list.setPreferredSize(new Dimension(150,400));
		this.add(label);
		this.add(content);
	}

	public void addList(String elem){
		users.add(elem);
		list.setListData(users.toArray());
	}

}
