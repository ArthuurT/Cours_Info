import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.*;

public class ChampSaisie extends JTextField{

	private String label;
	private String data;

	public ChampSaisie(String unLabel){
		this.label = unLabel;
		this.setPreferredSize(new Dimension(150, 20));
	}

	public ChampSaisie(String defaultValue, String unLabel){
		super(defaultValue);
		this.label = unLabel;
		this.setPreferredSize(new Dimension(150, 20));
	}

	public String getLabel(){
		return label;
	}

}
