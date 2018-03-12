import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.net.SocketException;
import javax.swing.JOptionPane;

public class Client implements Runnable{

	private Fenetre fen; // INTERFACE CLIENT
	private Socket soc;
	private int port;
	private String ip;
	private String name;
	private PrintWriter writer = null;
	private BufferedInputStream reader = null;

	public void addFenetre(Fenetre fen){
		this.fen = fen;
	}

	public Fenetre getFenetre(){
		return fen;
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

            	writer = new PrintWriter(soc.getOutputStream(), true);
            	String msgConnection = "ASKCONNECTION\n" + name;
            	writer.write(msgConnection);
            	writer.flush();
            	System.out.println("Commande " + msgConnection + " envoyée au serveur");

            	Thread t = new Thread(this);
            	t.start();	

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
		try{
			writer = new PrintWriter(soc.getOutputStream(), true);
	        String msgChat = "ASKMESSAGE\n" + name + "\n" + msg;
	        writer.write(msgChat);
	        writer.flush();
	        System.out.println("Commande " + msgChat + " envoyée au serveur");
	    }catch (UnknownHostException e){
	        e.printStackTrace();
	    }catch (IOException e){
	       	e.printStackTrace();
	    }
	}

	/* SEND ASKDECONNECTION */
	public void deconnexion(){
		try{
			writer = new PrintWriter(soc.getOutputStream(), true);
	        String msgDeco = "ASKDECONNECTION\n" + name;
	        writer.write(msgDeco);
	        writer.flush();
	        System.out.println("Commande " + msgDeco + " envoyée au serveur");
	    }catch (UnknownHostException e){
	        e.printStackTrace();
	    }catch (IOException e){
	       	e.printStackTrace();
	    }
	}

	/* Lecture en permanence du serveur */
	public void run(){
		while(true){
			try{
				System.out.println("Client en lecture ...");
				reader = new BufferedInputStream(soc.getInputStream());
				String response = read();
				System.out.println("Message recu : " + response);
	            String [] parts = response.split("\n");
	            String cmd = parts[0];
	            String usr = parts[1];

				switch(cmd.toUpperCase()){
					case "ADDUSER":
	      				fen.addUser(usr);
	                  	break;
	               case "REMOVEUSER":
	     				fen.remUser(usr);
	                  	break;
	               case "ADDMESSAGE":
	               		String msg = parts[2];
	               		String allMsg = usr + " : " + msg;
	                  	fen.addTxt(allMsg);
	               default : 
	                    System.out.println("Commande inconnue");               
	                  	break;
				}

			}catch(SocketException e){
	            System.err.println("LA CONNEXION A ETE INTERROMPUE ! ");
	            break;
         	}catch(IOException e) {
            	e.printStackTrace();
            	break;
         	}  
        }
	}


	private String read() throws IOException{      

      	String response = "";
      	int stream;
      	byte[] b = new byte[4096];
      	stream = reader.read(b);
      	response = new String(b, 0, stream);      
      	return response;
   }
}