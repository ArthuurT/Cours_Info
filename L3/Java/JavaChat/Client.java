import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.JOptionPane;

public class Client implements Runnable{

	private Fenetre fen; // INTERFACE CLIENT
	private Socket soc;
	private int port;
	private String ip;
	private String name;

	public void addFenetre(Fenetre fen){
		this.fen = fen;
	}

	public void connexion(){

		String portTemp = fen.getTextPort();
		ip = fen.getTextIp();
		name = fen.getTextName();

		if(!portTemp.equals("") && !ip.equals("") && !name.equals("")){

			port = Integer.parseInt(portTemp);

			try{
	            soc = new Socket(ip, port);
	            System.out.println("Connexion -> Nom: " + name + " / Port: " + port + " / IP: " + ip);

	            /* SEND ASKCONNECTION */




	        }catch (UnknownHostException e){
	            e.printStackTrace();
	        }catch (IOException e){
	        	e.printStackTrace();
	        }

	    }else{
	    	JOptionPane.showMessageDialog(fen, "Champs incorrects","ERREUR",JOptionPane.WARNING_MESSAGE);
	    }
	}

	/* SEND ASKMESSAGE */
	public void sendMessage(String msg){

	}

	/* SEND ASKDECONNECTION */
	public void deconnexion(){
		
	}

	/* Lecture en permanence du serveur */
	public void run(){

	}
}