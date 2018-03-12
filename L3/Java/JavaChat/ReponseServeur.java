import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;
import java.text.DateFormat;
import java.util.*;

public class ReponseServeur implements Runnable{

   private Socket currentSock;
   private BufferedInputStream reader = null;
   private List<Socket> lSock = null;
   
   public ReponseServeur(Socket pSock){
      currentSock = pSock;
      lSock = new ArrayList<Socket>();
   }
   
   public void run(){
      	System.err.println("Lancement du traitement de la connexion cliente");

      	boolean closeConnexion = false;
  
      	while(!currentSock.isClosed()){
         
         	try{
            
	            reader = new BufferedInputStream(currentSock.getInputStream());
	            
	            //On attend la demande du client            
	            String response = read();
	            String [] parts = response.split("\n");
	            String cmd = parts[0];
	            String usr = parts[1];

	            InetSocketAddress remote = (InetSocketAddress)currentSock.getRemoteSocketAddress();
	            
	            //On affiche quelques infos, pour le débuggage
	            String debug = "";
	            debug = "Thread : " + Thread.currentThread().getName() + ". ";
	            debug += "Demande de l'adresse : " + remote.getAddress().getHostAddress() +".";
	            debug += " Sur le port : " + remote.getPort() + ".\n";
	            debug += "\t -> Commande reçue : " + response + "\n";
	            System.err.println("\n" + debug);

	            //On traite la demande du client (ASKCONNECTION, ASKDECONNECTION, ASKMESSAGE)

	            String toSend = "";
            
	            switch(cmd.toUpperCase()){
	               case "ASKCONNECTION":
	               		lSock.add(currentSock);
	                  	toSend = "ADDUSER\n" + usr;
	                  	break;
	               case "ASKDECONNECTION":
	               		lSock.remove(currentSock);
	                  	toSend = "REMOVEUSER\n" + usr;
	                  	break;
	               case "ASKMESSAGE":
	               		String msg = parts[2];
	                  	toSend = "ADDMESSAGE\n" + usr + "\n" + msg;
	                  	break;
	               default : 
	                  	toSend = "Commande inconnu !";                     
	                  	break;
	            }
	            
	            
	            //On envoie la réponse au client
	            writerClient(toSend);
	            
	            if(closeConnexion){
	               System.err.println("COMMANDE CLOSE DETECTEE ! ");
	               reader = null;
	               currentSock.close();
	               break;
	            }

         	}catch(SocketException e){
	            System.err.println("LA CONNEXION A ETE INTERROMPUE ! ");
	            break;
         	}catch (IOException e) {
            	e.printStackTrace();
         	}         
      	}
   }
   
   
   //La méthode que nous utilisons pour lire les réponses
   private String read() throws IOException{      
      String response = "";
      int stream;
      byte[] b = new byte[4096];
      stream = reader.read(b);
      response = new String(b, 0, stream);
      return response;
   }

   private void writerClient(String s) throws IOException{

   		Iterator<Socket> it = lSock.iterator();
   		PrintWriter writer = null;

   		while(it.hasNext()){
	   		writer = new PrintWriter(it.next().getOutputStream());
	   		writer.write(s);
		    writer.flush();
   		}
   }

   
}